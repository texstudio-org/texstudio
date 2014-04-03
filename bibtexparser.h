#ifndef BIBTEXPARSER_H
#define BIBTEXPARSER_H

#include "mostQtHeaders.h"

class BibTeXFileInfo{
public:
	//these are the properties of the file when it was loaded the last time (no watching)
	QDateTime lastModified;
	QStringList ids;
	QString linksTo;
	bool loadIfModified(const QFileInfo& fi);
private:
	void load(const QFileInfo& fi);
protected: //unit tests access this
	void parse(QByteArray& data);
};


#endif // BIBTEXPARSER_H
