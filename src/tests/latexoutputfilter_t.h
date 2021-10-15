#ifndef Header_Latex_OutputFilter_T
#define Header_Latex_OutputFilter_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"

class LatexOutputFilter;

class LatexOutputFilterTest : public QObject
{
	Q_OBJECT
public:
    explicit LatexOutputFilterTest(QObject *parent = nullptr);
	
signals:
	
private slots:
	void run_data();
	void run();

	void fileNameLikelyComplete_data();
	void fileNameLikelyComplete();


	void isBadBoxTextQuote_data();
	void isBadBoxTextQuote();

	void detectError_data();
	void detectError();

	QString stackTopFilename(const LatexOutputFilter &f);
	QString currentMessage(const LatexOutputFilter &f);
};
#endif // QT_NO_DEBUG
#endif // LATEXOUTPUTFILTER_T_H
