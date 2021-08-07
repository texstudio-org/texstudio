#include "kpathseaParser.h"
#include "execprogram.h"

PackageScanner::PackageScanner(QObject *parent) :
	SafeThread(parent)
{
	stopped = false;
}

void PackageScanner::savePackageList(std::set<QString> packages, const QString &filename)
{
	QFile f(filename);
	if (f.open(QFile::WriteOnly | QFile::Text)) {
		QTextStream out(&f);
		out << "% detected .sty and .cls filenames\n";
        for(const QString &str: packages) {
			out << str << "\n";
		}
	}
}

std::set<QString> PackageScanner::readPackageList(const QString &filename)
{
	QFile f(filename);
    std::set<QString> result;
	if (f.open(QFile::ReadOnly | QFile::Text)) {
		QTextStream in(&f);
		QString line;
		while (!in.atEnd()) {
			line = in.readLine();
			if (line.isEmpty() || line.startsWith('%')) continue;
			result.insert(line);
		}
	}
	return result;
}

void PackageScanner::stop()
{
	stopped = true;
}

KpathSeaParser::KpathSeaParser(QString kpsecmd, QObject *parent, QString additionalPaths) :
	PackageScanner(parent)
{
	kpseWhichCmd = kpsecmd;
    m_additionalPaths=additionalPaths;
}

void KpathSeaParser::run()
{
    std::set<QString> results;
	QString res = kpsewhich("--show-path ls-R");
	QStringList lstOfFiles = res.split(getPathListSeparator()); // find lcoations of ls-R (file database of tex)
	foreach (QString fn, lstOfFiles) {
		if (stopped)
			return;
		fn = fn.trimmed() + "/ls-R";
		QFile data(fn);
		QString line;
		if (data.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream stream(&data);
			while (!stream.atEnd()) {
				line = stream.readLine();
				if (line.endsWith(".sty") || line.endsWith(".cls")) {
					line.chop(4);
					results.insert(line);
				}
			}
		}
	}
	emit scanCompleted(results);
}

QString KpathSeaParser::kpsewhich(const QString &arg)
{
	ExecProgram execProgram(kpseWhichCmd + " " + arg, m_additionalPaths);
	execProgram.execAndWait();
	return execProgram.m_standardOutput;
}


MiktexPackageScanner::MiktexPackageScanner(QString mpmcmd, QString settingsDir, QObject *parent)
	: PackageScanner(parent)
{
	this->mpmCmd = mpmcmd;
	this->settingsDir = settingsDir;
}

QString MiktexPackageScanner::mpm(const QString &arg)
{
	ExecProgram execProgram(mpmCmd + " " + arg, "");
	execProgram.execAndWait();
	return execProgram.m_standardOutput;
}

void MiktexPackageScanner::savePackageMap(const QHash<QString, QStringList> &map)
{
	QFile f(ensureTrailingDirSeparator(settingsDir) + "miktexPackageNames.dat");
	if (f.open(QFile::WriteOnly | QFile::Text)) {
		QTextStream out(&f);
		out << "% This file maps the MiKTeX package names to the .sty and .cls file names.\n";
		out << "% It's used as cache for a fast lookup. It's automatically created and may be deleted without harm.\n";
		foreach (const QString &mpmName, map.keys()) {
			out << mpmName << ":" << map.value(mpmName).join(",") << "\n";
		}
	}
}

QHash<QString, QStringList> MiktexPackageScanner::loadPackageMap()
{
	QFile f(ensureTrailingDirSeparator(settingsDir) + "miktexPackageNames.dat");
	QHash<QString, QStringList> result;
	if (f.open(QFile::ReadOnly | QFile::Text)) {
		QTextStream in(&f);
		QString line;
		QStringList lst;
		while (!in.atEnd()) {
			line = in.readLine();
			if (line.isEmpty() || line.startsWith('%')) continue;
			lst = line.split(":");
			if (lst.length() < 2) continue;
			result.insert(lst[0], lst[1].split(","));
		}
	}
	return result;
}

QStringList MiktexPackageScanner::stysForPackage(const QString &pck)
{
	QStringList result;
	QStringList lines = mpm("--print-package-info " + pck).split("\n");
	bool inRunTimeFilesSection = false;
	foreach (const QString &l, lines) {
		if (!inRunTimeFilesSection) {
			if (l.startsWith("run-time files:"))
				inRunTimeFilesSection = true;
			continue;
		} else {
			QString fn = l.simplified();
			if (fn.endsWith(":")) break; // start of a new section
			fn = QFileInfo(fn).fileName();
			if (fn.endsWith(".sty") || fn.endsWith(".cls")) {
				fn.chop(4);
				result.append(fn);
			}
		}
	}
	return result;
}

void MiktexPackageScanner::run()
{
    std::set<QString> results;

	QHash<QString, QStringList> cachedStys = loadPackageMap();

	QStringList lstOfPackages = mpm("--list").split("\n");
	foreach (QString pck, lstOfPackages) {
		if (stopped)
			return;
		QStringList parts = pck.simplified().split(" "); // output format of "mpm --list": installation status, number of files, size, database name
		if (parts.count() != 4) continue;
		if (parts[0] != "i") continue; // not installed
		pck = parts[3];
		QStringList stys;
		if (cachedStys.contains(pck)) {
			stys = cachedStys.value(pck);
		} else {
			stys = stysForPackage(pck);
			cachedStys.insert(pck, stys);
		}
		foreach (const QString &sty, stys) {
			results.insert(sty);
		}
	}
	savePackageMap(cachedStys);

	emit scanCompleted(results);
}


