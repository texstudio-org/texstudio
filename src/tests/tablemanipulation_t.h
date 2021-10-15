#ifndef Header_TableManipulation_T
#define Header_TableManipulation_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"

class QEditor;
class TableManipulationTest: public QObject{
	Q_OBJECT
	public:
		TableManipulationTest(QEditor* editor);
	private:
		QEditor *ed;
	private slots:
		void splitColDef_data();
		void splitColDef();
		void simplifyColDef_data();
		void simplifyColDef();
		void addCol_data();
		void addCol();
		void addRow_data();
		void addRow();
		void remCol_data();
		void remCol();
		void remRow_data();
		void remRow();
		void getCol_data();
		void getCol();
		void getNumberOfCol_data();
		void getNumberOfCol();
		void findNextToken_data();
		void findNextToken();
		void findNextTokenBackwards_data();
		void findNextTokenBackwards();
		void addHLine_data();
		void addHLine();
		void splitCol_data();
		void splitCol();
		void getDef_data();
		void getDef();
		void parseTableLine_data();
		void parseTableLine();
};

#endif
#endif
