#include "bibtexreader.h"
#include "configmanagerinterface.h"

bibtexReader::bibtexReader(QObject *parent) :
	SafeThread(parent)
{
}

/*!
 * Makes sure, that the returned string is not longer than lengthLimit.
 * Longer strings will be truncated and an ellipsis [...] is added to the end.
 */
QString truncateLine(const QString &line, int lengthLimit) {
	if (line.length() < lengthLimit) {
		return line;
	}
	int pos = line.lastIndexOf(' ', lengthLimit - 3);
	if (pos < 0) pos = lengthLimit - 3;
	return line.left(pos+1) + '[' + QChar(8230) + ']';
}

void bibtexReader::searchSection(QString file, QString bibId, int truncateLimit)
{
	QFile f(file);
	if (!f.open(QFile::ReadOnly)) return; //ups...
	QTextStream stream(&f);
	QString bibFileEncoding = ConfigManagerInterface::getInstance()->getOption("Bibliography/BibFileEncoding").toString();
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    std::optional<QStringConverter::Encoding> codec=QStringConverter::encodingForName(bibFileEncoding.toLocal8Bit());
    if (!codec.has_value()){
        qDebug()<<"bibtexReader::searchSection text codec not recognized in QT6:"<<bibFileEncoding;
        return; // some warning ?
    }
    stream.setEncoding(codec.value());
#else
	QTextCodec *codec = QTextCodec::codecForName(bibFileEncoding.toLatin1());
	if (!codec) return;
	stream.setCodec(codec);
#endif
	QString line;
	QString result;
	int found = -1;
	do {
		line = stream.readLine();
		if (line.startsWith('%'))
			continue;
		if (found == -1 && line.contains(bibId)) {
			int p = line.indexOf('{');
			if (p < 0)
				continue;
			QString id = line.mid(p + 1).trimmed();
			if (id.endsWith(','))
				id.remove(id.length() - 1, 1);
			if (id != bibId)
				continue;
			found = 10;
			result = truncateLine(line, truncateLimit);
			continue;
		}
		if (found == 0 || (found > 0 && (line.startsWith('@') || line.isEmpty())))
			break;
		if (found >= 0) {
			result += "\n" + truncateLine(line, truncateLimit);
			found--;
		}
	} while (!line.isNull());
	if (!result.isEmpty())
		emit sectionFound(result);
}
