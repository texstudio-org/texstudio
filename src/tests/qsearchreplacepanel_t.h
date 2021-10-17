#ifndef Header_QSearch_ReplacePanel
#define Header_QSearch_ReplacePanel
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QCodeEdit;
class QEditor;
class QSearchReplacePanel;
class QSearchReplacePanelProtectedBreaker;

class QSearchReplacePanelTest: public QObject{
	Q_OBJECT
	public:
		QSearchReplacePanelTest(QCodeEdit* codeedit, bool executeAllTests=true);
		~QSearchReplacePanelTest();
	private:
		QEditor *ed;
		QSearchReplacePanel *panel;
		QSearchReplacePanelProtectedBreaker *widget;
		bool allTests;
		QStringList oldFindHistory, oldReplaceHistory;
	private slots:
		void initTestCase();
		void incrementalsearch_data();
		void incrementalsearch();
		void findNext_data();
		void findNext();
		void findReplace_data();
		void findReplace();
		void findReplaceSpecialCase();
		void findSpecialCase2();
		void selectionHighlighting();
		void cleanupTestCase();
};

#endif
#endif
