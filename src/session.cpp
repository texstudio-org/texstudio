#include "session.h"
#include "configmanager.h"
#include "smallUsefulFunctions.h"

#include <QJsonDocument>
#include <QJsonArray>

Session::Session(const Session &s)
{
	m_files.append(s.m_files);
	m_masterFile = s.m_masterFile;
	m_currentFile = s.m_currentFile;

	m_bookmarks = s.m_bookmarks;
	m_pdfFile = s.m_pdfFile;
	m_pdfEmbedded = s.m_pdfEmbedded;
}

bool Session::load(const QString &fileName){
    if (!QFileInfo(fileName).isReadable()) return false;
    if(fileName.endsWith(".txss")){
        return load_v1(fileName);
    }else{
        return load_v2(fileName);
    }
}

bool Session::load_v1(const QString &file)
{
	if (!QFileInfo(file).isReadable()) return false;
	QSettings s(file, QSettings::IniFormat);
	if (!s.childGroups().contains("Session")) return false;
	m_files.clear();
	s.beginGroup("Session");
	QStringList groups = s.childGroups();
	QDir dir = QFileInfo(file).dir();
	for (int i = 0; i < 1000; i++) {
		if (!groups.contains(QString("File%1").arg(i)))
			break;
		s.beginGroup(QString("File%1").arg(i));
		FileInSession f;
		QString filename = s.value("FileName").toString();
		if (filename.isEmpty()) continue;
		f.fileName = QDir::cleanPath(dir.filePath(filename));
		f.editorGroup = s.value("EditorGroup", 0).toInt();
		f.cursorLine = s.value("Line", 0).toInt();
		f.cursorCol = s.value("Col", 0).toInt();
		f.firstLine = s.value("FirstLine", 0).toInt();
		f.foldedLines = strToIntList(s.value("FoldedLines").toString());
		m_files.append(f);
		s.endGroup();
	}
	m_masterFile = QDir::cleanPath(dir.filePath(s.value("MasterFile").toString()));
	m_currentFile = QDir::cleanPath(dir.filePath(s.value("CurrentFile").toString()));

    foreach (const QVariant &v, s.value("Bookmarks").value<QList<QVariant> >()) {
        Bookmark bm = Bookmark::fromStringList(v.toStringList());
        bm.filename = QDir::cleanPath(dir.filePath(bm.filename));
        m_bookmarks << bm;
    }

	s.endGroup();

	s.beginGroup("InternalPDFViewer");
	QString pdfFileName(s.value("File").toString());
	m_pdfFile = (pdfFileName.trimmed().isEmpty()) ? "" : QDir::cleanPath(dir.filePath(pdfFileName));
	m_pdfEmbedded = s.value("Embedded").toBool();
	s.endGroup();
    return true;
}

bool Session::load_v2(const QString &file)
{
    QFile loadFile(file);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

    QByteArray data = loadFile.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error!=QJsonParseError::NoError){
        // parser could not read input
        return false;
    }
    QDir dir = QFileInfo(file).dir();
    QJsonObject dd=jsonDoc.object();
    QJsonObject j_pdf=dd["InternalPDFViewer"].toObject();

    QString pdfFileName(j_pdf.value("File").toString());
    m_pdfFile = (pdfFileName.trimmed().isEmpty()) ? "" : QDir::cleanPath(dir.filePath(pdfFileName));
    m_pdfEmbedded = j_pdf.value("Embedded").toBool();

    QJsonObject j_session=dd["Session"].toObject();

    m_masterFile = QDir::cleanPath(dir.filePath(j_session.value("MasterFile").toString()));
    m_currentFile = QDir::cleanPath(dir.filePath(j_session.value("CurrentFile").toString()));

    m_splitVertical = j_session.value("VerticalSplit").toBool();

    QJsonArray ja=j_session.value("Files").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QJsonObject jo=ja[i].toObject();
        FileInSession f;
        QString filename = jo.value("FileName").toString();
        if (filename.isEmpty()) continue;
        f.fileName = QDir::cleanPath(dir.filePath(filename));
        f.editorGroup = jo.value("EditorGroup").toInt();
        f.cursorLine = jo.value("Line").toInt();
        f.cursorCol = jo.value("Col").toInt();
        f.firstLine = jo.value("FirstLine").toInt();
        f.foldedLines = strToIntList(jo.value("FoldedLines").toString());
        m_files.append(f);
    }

    QJsonArray ja2=j_session.value("Bookmarks").toArray();
    for(int i=0;i<ja2.size();++i) {
        QJsonObject jo=ja2[i].toObject();
        Bookmark bm = Bookmark::fromJSON(jo);
        bm.filename = QDir::cleanPath(dir.filePath(bm.filename));
        m_bookmarks << bm;
    }

    return true;
}

bool Session::save(const QString &fileName, bool relPaths) const
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QDir dir = QFileInfo(file).dir();

    QJsonObject j_pdf;
    j_pdf["File"]=fmtPath(dir, m_pdfFile, relPaths);
    j_pdf["Embedded"]=m_pdfEmbedded;

    QJsonObject j_session;
    j_session["FileVersion"]=1;
    j_session["MasterFile"]=fmtPath(dir, m_masterFile, relPaths);
    j_session["CurrentFile"]=fmtPath(dir, m_currentFile, relPaths);
    j_session["VerticalSplit"]=m_splitVertical;

    QJsonArray ja;
    QJsonObject j_file;
    for (int i = 0; i < m_files.count(); i++) {
        j_file["FileName"]=fmtPath(dir, m_files[i].fileName, relPaths);
        j_file["EditorGroup"]=m_files[i].editorGroup;
        j_file["Line"]=m_files[i].cursorLine;
        j_file["Col"]= m_files[i].cursorCol;
        j_file["FirstLine"]=m_files[i].firstLine;
        j_file["FoldedLines"]=intListToStr(m_files[i].foldedLines);
        ja.append(j_file);
    }
    j_session.insert("Files",ja);

    QJsonArray ja2;
    QJsonObject j_bm;
    foreach (Bookmark bm, m_bookmarks) {
        if (relPaths) {
            bm.filename = fmtPath(dir, bm.filename, relPaths);
        }
        j_bm=bm.toJSON();
        ja2.append(j_bm);
    }
    j_session.insert("Bookmarks",ja2);

    QJsonObject dd;
    dd.insert("InternalPDFViewer",j_pdf);
    dd.insert("Session",j_session);

    QJsonDocument jsonDoc(dd);
    file.write(jsonDoc.toJson());

    return true;
}

void Session::addFile(FileInSession f)
{
	m_files.append(f);
}

QString Session::fmtPath(const QDir &dir, const QString &file, bool relPath)
{
	if (!relPath)
		return file;
	else
		return dir.relativeFilePath(file);
}

