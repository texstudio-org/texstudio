#include "directoryreader.h"

directoryReader::directoryReader(QObject *parent) :
	SafeThread(parent)
{
}

void directoryReader::readDirectory(QString path)
{
	QDir dir(path);
	QFileInfoList lst = dir.entryInfoList();
	QSet<QString> files;
	foreach (QFileInfo elem, lst) {
		if (elem.isDir()) {
            files.insert(elem.fileName() + "/");
		} else {
			files.insert(elem.fileName());
		}
	}

	emit directoryLoaded(path, files);
}

