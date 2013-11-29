#ifndef LATEXOUTPUTFILTER_T_H
#define LATEXOUTPUTFILTER_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"

class LatexOutputFilter;

class LatexOutputFilterTest : public QObject
{
	Q_OBJECT
public:
	explicit LatexOutputFilterTest(QObject *parent = 0);
	
signals:
	
private slots:
	void run_data();
	void run();

	QString stackTopFilename(const LatexOutputFilter &f);
};
#endif // QT_NO_DEBUG
#endif // LATEXOUTPUTFILTER_T_H
