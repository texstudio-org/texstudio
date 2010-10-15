#include "unicodeinsertion.h"

QString unicodePointToString(unsigned int u){
//	if (u < 0x10000) return QChar(u);
//	else //return QString(QChar(QChar::highSurrogate(u))) + QChar(QChar::lowSurrogate(u));
	return QString::fromUcs4(&u, 1);
}

UnicodeInsertion::UnicodeInsertion(QWidget* parent): QWidget(parent)
{
	QLayout* lay = new QVBoxLayout();
	edit=new QLineEdit(this);
	table=new QTableWidget(this);
	QFontMetrics fm(QApplication::font());
	int bw = (fm.maxWidth()+1), bh= qMax(fm.height(),fm.lineSpacing())+1;
	table->setMinimumWidth(16*bw);
	table->setMinimumHeight(3*bh);
	table->setRowCount(3);
	table->setColumnCount(16);
	for (int i=0;i<table->rowCount();i++)
		table->setRowHeight(i, bh);;
	for (int i=0;i<table->rowCount();i++)
		table->setColumnWidth(i, bw);;
	table->horizontalHeader()->hide();
	table->verticalHeader()->hide();
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	lay->addWidget(edit);
	lay->addWidget(table);
	resize(19*bw, 5*bh+2*edit->height());
	this->setLayout(lay);


	edit->setText("0x");
	setFocusProxy(edit);
	connect(edit,SIGNAL(textChanged(QString)), SLOT(editChanged(QString)));
	setAttribute(Qt::WA_DeleteOnClose,true);
}

void UnicodeInsertion::setTableText(int r, int c, const QString& s){
	if (!table->item(r,c)) table->setItem(r,c,new QTableWidgetItem(s));
	else table->item(r,c)->setText(s);
}
void UnicodeInsertion::keyPressEvent(QKeyEvent * k){
	if (k->key()==Qt::Key_Enter || k->key()==Qt::Key_Return){
		if (table->item(0,8) && table->item(0,8)->text()!="")
		emit insertCharacter(table->item(0,8)->text());
		close();
	}
	if (k->key()==Qt::Key_Escape) close();
}


void UnicodeInsertion::editChanged(const QString& newText){
	QString nt = newText;
	int base=16;
	if (newText.startsWith("0x",Qt::CaseInsensitive)) nt.remove(0,2);
	else if (newText.startsWith("x",Qt::CaseInsensitive)) nt.remove(0,1);
	else base=10;

	unsigned int c = QString(nt).toUInt(0,base);
	setTableText(0,8,unicodePointToString(c));
	for (int i=0;i<base;i++)
		setTableText(2,i,unicodePointToString(c*base+i));
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	//for (int i=0;i<16;i++)
}

