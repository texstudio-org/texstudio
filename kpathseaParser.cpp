#include "kpathseaParser.h"

void PackageListReader::run() {
	if(cmd.isEmpty()) return;

	QProcess proc(0);
	proc.start(cmd, arguments);
	proc.waitForFinished();
	QString output;
	if (proc.exitCode() == 0) {
		output = proc.readAllStandardOutput();
	}
	QStringList packages = parseOutput(output);
	emit scanCompleted(packages);
}

QStringList PackageListReader::parseOutput(const QString &output) {
	Q_UNUSED(output);
	return QStringList();
}


KpathSeaParser::KpathSeaParser(QObject *parent, QString kpsecmd) :
	PackageListReader(parent)
{
	cmd = kpsecmd;
	arguments = QStringList() << "-show-path" << "ls-R";;
}

QStringList KpathSeaParser::parseOutput(const QString &output) {
	if (output.isEmpty()) return QStringList();
	QStringList lstOfFiles = output.split(":");
	QStringList results;
	QStringList::iterator it;
	foreach (QString fn, lstOfFiles) {
		fn=fn.trimmed()+"/ls-R";
		QFile data(fn);
		QString line;
		if (data.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream stream(&data);
			while (!stream.atEnd()) {
				line = stream.readLine();
				if (line.endsWith(".sty") || line.endsWith(".cls")) {
					line.chop(4);
					it=qLowerBound(results.begin(),results.end(),line);
					if(it==results.end() || *it!=line)
						results.insert(it,line);
				}
			}
		}
	}
	return results;
}


MiktexPackageListReader::MiktexPackageListReader(QObject *parent) :
	PackageListReader(parent)
{
	cmd = "mpm.exe";
	arguments = QStringList() << "--list-package-names";
}

QStringList MiktexPackageListReader::parseOutput(const QString &output) {
	QStringList packages = output.split("\r\n");
	packages.removeAll("");
	return packages;
}
