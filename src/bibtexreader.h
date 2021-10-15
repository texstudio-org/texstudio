#ifndef Header_Bibtex_Reader
#define Header_Bibtex_Reader
#include "smallUsefulFunctions.h"
#include "mostQtHeaders.h"
#include <QThread>

class bibtexReader : public SafeThread
{
	Q_OBJECT

public:
	explicit bibtexReader(QObject *parent = 0);

signals:
	void sectionFound(QString content);

public slots:
	void searchSection(QString file, QString bibId, int truncateLimit = 150);
};

#endif // BIBTEXREADER_H
