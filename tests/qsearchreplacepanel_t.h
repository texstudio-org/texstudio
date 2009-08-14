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
		QSearchReplacePanelTest(QCodeEdit* codeedit);
	private:
		QEditor *ed;
		QSearchReplacePanel *panel;
		Ui::SearchReplace *widget;
	private slots:
		void initTestCase();
		void incrementalsearch_data();
		void incrementalsearch();
		void findNext_data();
		void findNext();
		void findReplace_data();
		void findReplace();
		void cleanupTestCase();
};

#endif
#endif
