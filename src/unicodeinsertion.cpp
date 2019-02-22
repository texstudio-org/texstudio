#include "unicodeinsertion.h"

QString unicodePointToString(unsigned int u)
{
//	if (u < 0x10000) return QChar(u);
//	else //return QString(QChar(QChar::highSurrogate(u))) + QChar(QChar::lowSurrogate(u));
	return QString::fromUcs4(&u, 1);
}

QString unicodePointToUtf8Hex(unsigned int u)
{
	return unicodePointToString(u).toUtf8().toHex();
}

QLineEditWithMetaText::QLineEditWithMetaText(QWidget *parent): QLineEdit(parent)
{
}

void QLineEditWithMetaText::setMetaText(const QString &s)
{
	metaText = s;
	update();
}

void QLineEditWithMetaText::paintEvent ( QPaintEvent *ev)
{
	QLineEdit::paintEvent(ev);
	if (metaText.isEmpty()) return;
	QPainter p(this);
	QFontMetrics fm(font());
	p.setPen(QApplication::palette().windowText().color().lighter(50));
	p.drawText(width() - fm.width(metaText) - 5, (height() + fm.height()) / 2 - 2, metaText);

}


UnicodeInsertion::UnicodeInsertion(QWidget *parent, uint defCharCode): QWidget(parent), defaultCharCode(defCharCode)
{
	QLayout *lay = new QVBoxLayout();
	edit = new QLineEditWithMetaText(this);
	table = new QTableWidget(this);
	QFontMetrics fm(QApplication::font());
    int bw = (fm.maxWidth() + 1);
    int bh = qMax(fm.height(), fm.lineSpacing()) + 1;
    int bw_average=fm.averageCharWidth();
    table->setMinimumWidth(16 * bw);
    table->setMinimumHeight(3 * bh);
	table->setRowCount(3);
	table->setColumnCount(16);
	for (int i = 0; i < table->rowCount(); i++)
		table->setRowHeight(i, bh);;
    for (int i = 0; i < table->columnCount(); i++)
		table->setColumnWidth(i, bw);;
	table->horizontalHeader()->hide();
	table->verticalHeader()->hide();
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	connect(table, SIGNAL(cellClicked(int, int)), SLOT(tableCellClicked(int, int)));
	connect(table, SIGNAL(cellDoubleClicked(int, int)), SLOT(tableCellDoubleClicked(int, int)));

	lay->addWidget(edit);
	lay->addWidget(table);
    int widgetWidth=qMax(19*bw,44*bw_average);
    resize(widgetWidth, 5 * bh + 2 * edit->height());
	this->setLayout(lay);


	setFocusProxy(edit);
	connect(edit, SIGNAL(textChanged(QString)), SLOT(editChanged(QString)));
	setAttribute(Qt::WA_DeleteOnClose, true);
	if (defaultCharCode == 0) edit->setText("0x");
	else edit->setText(QString("0x%1").arg(defaultCharCode, 0, 16));
}

void UnicodeInsertion::setTableText(int r, int c, const QString &s)
{
	if (!table->item(r, c)) table->setItem(r, c, new QTableWidgetItem(s));
	else table->item(r, c)->setText(s);
}
void UnicodeInsertion::keyPressEvent(QKeyEvent *k)
{
	if (k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return) {
		if (table->item(0, 8) && table->item(0, 8)->text() != "" &&
		        table->item(0, 8)->text() != unicodePointToString(defaultCharCode))
			emit insertCharacter(table->item(0, 8)->text());
		close();
	}
	if (k->key() == Qt::Key_Escape) close();
}

void UnicodeInsertion::editChanged(const QString &newText)
{
	QString nt = newText.trimmed();
	if (nt.startsWith('\'')) {
		if (nt.length() < 2) return;
		unsigned int unicode = nt.at(1).unicode();
		if (nt.at(1).isHighSurrogate()) {
			if (nt.length() < 3) return;
			unicode = (((unicode & 0x3FF) << 10) | (nt.at(2).unicode() & 0x3FF)) + 0x10000;
		}
		edit->setText("0x" + QString::number(unicode, 16));
		return;
	}
    int base = 16;
	if (nt.startsWith("0x", Qt::CaseInsensitive)) nt.remove(0, 2);
	else if (nt.startsWith("x", Qt::CaseInsensitive)) nt.remove(0, 1);
	else base = 10;

    unsigned int c = QString(nt).toUInt(nullptr, base);

	QString utf8 = c <= 0x7f ? "" : QString(", utf-8: %1").arg(unicodePointToUtf8Hex(c));
	if (base == 16) edit->setMetaText(QString("%1 (cp: %2%3)").arg(unicodePointToString(c)).arg(c).arg(utf8));
	else edit->setMetaText(QString("%1 (cp: 0x%2%3)").arg(unicodePointToString(c)).arg(c, 0, 16).arg(utf8));

	setTableText(0, 8, unicodePointToString(c));
    for (int i = 0; i < base; i++)
		setTableText(2, i, unicodePointToString(c * base + i));
	if (nt.length() < 2)
		table->resizeRowsToContents();
	//table->resizeColumnsToContents();
	//for (int i=0;i<16;i++)
}

void UnicodeInsertion::tableCellClicked(int r, int c)
{
	if (r != 2) return;
	QChar cc = c >= 10 ? QChar('A' + c - 10) : QChar('0' + c);
	edit->setText(edit->text() + cc);
	edit->setFocus();
}

void UnicodeInsertion::tableCellDoubleClicked(int r, int c)
{
	if (r != 2 || !table->item(r, c)) return;
	insertCharacter(table->item(0, 8)->text()); //tricky, double click is reported as single click - double click and the single click sets the edit box (4.6.3 on debian)
	close();
}

