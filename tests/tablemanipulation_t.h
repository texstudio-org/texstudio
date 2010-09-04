#ifndef TABLEMANIPULATION_T_H
#define TABLEMANIPULATION_T_H
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
		void addCol_data();
		void addCol();
		void addRow_data();
		void addRow();
};

#endif
#endif
