#ifndef QSEARCHREPLACEPANEL_T_H
#define QSEARCHREPLACEPANEL_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QCodeEdit;
class QEditor;
class QSearchReplacePanel;
namespace Ui{class SearchReplace;}
class QSearchReplacePanelTest: public QObject{
	Q_OBJECT
	public:
		QSearchReplacePanelTest(QCodeEdit* codeedit, bool executeAllTests=true);
	private:
		QEditor *ed;
		QSearchReplacePanel *panel;
		Ui::SearchReplace *widget;
		bool allTests;
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
