#include "fileselector.h"

FileSelector::FileSelector(QWidget *parent) :
		QWidget(parent)
{
	setLayout(new QVBoxLayout());
	list = new QListWidget(this);
	layout()->addWidget(list);
	filter = new QLineEdit(this);
	layout()->addWidget(filter);
	connect(filter, SIGNAL(textChanged(QString)), SLOT(filterChanged(QString)));

	filter->installEventFilter(this);
	list->installEventFilter(this);

	QPalette p = QApplication::palette(); //let the list appear selected (does not work with gtk+ style)
	p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
	p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));
	list->setPalette(p);

	setAttribute(Qt::WA_DeleteOnClose);
}

void FileSelector::init(const QStringList& files, int current){
	filter->setFocus();
	rawFiles = files;
	filterChanged(filter->text());
	if (current >= 0 && current < rawFiles.count()) {
		int r = 0;
		for (int i=0;i<current;i++)
			if (list->item(i)->text() == rawFiles[i]) r++;
		if (list->item(r)->text() == rawFiles[current])
			list->setCurrentRow(r);
	}
}

void FileSelector::filterChanged(const QString& newFilter){
	QString nf = newFilter;
	if (newFilter.contains(':') && QRegExp(".*:[0-9; ]*").exactMatch(newFilter))
		nf = newFilter.left(newFilter.lastIndexOf(':'));

	QPair<QString, int> oldFile = currentFile();
	list->clear();
	foreach (const QString& s, rawFiles)
		if (s.contains(nf, Qt::CaseInsensitive))
			list->addItem(s);

	if (oldFile.second >= 0) {
		for (int i=0;i<list->count();i++)
			if (list->item(i)->text() == oldFile.first) {
				oldFile.second-=1;
				if (oldFile.second < 0){
					list->setCurrentRow(i);
					return;
				}
			}
	}

	list->setCurrentRow(0);
}

bool FileSelector::eventFilter(QObject * obj, QEvent * event){
	if (event->type() == QEvent::KeyPress) {
		int key = static_cast<QKeyEvent*>(event)->key();
		switch (key) {
			case Qt::Key_Up: case Qt::Key_Down:
			case Qt::Key_PageUp: case Qt::Key_PageDown:
				if (obj != filter) break;
				{
					int offset = -1;
					if (key == Qt::Key_Down) offset = 1;
					else if (key == Qt::Key_PageUp) offset = - list->height() / qMax(1, list->fontMetrics().height());
					else if (key == Qt::Key_PageDown) offset = list->height() / qMax(1, list->fontMetrics().height());
					int row = list->currentRow() + offset;
					if (row + offset < 0) row = 0;
					else if (row >= list->count()) row = list->count() - 1;
					if (row == list->currentRow()) break;
					list->setCurrentRow(row);
					return true;
				}
			case Qt::Key_Return: case Qt::Key_Enter:
				emitChoosen();
				return true;
			case Qt::Key_Escape:
				close();
				return true;
		}
	} else if (obj == list && event->type() == QEvent::MouseButtonDblClick) {
		qDebug() << "??? todo, why is this not called ??";
		emitChoosen();
		return true;
	}
	return QObject::eventFilter(obj, event);
}

void FileSelector::emitChoosen(){
	QString jumpTo = filter->text().mid(filter->text().lastIndexOf(':')+1);
	int line = -1, col = -1;
	if (!jumpTo.isEmpty()) {
		if (!jumpTo.contains(';')) line = jumpTo.trimmed().toInt() - 1;
		else {
			QStringList sl = jumpTo.split(';');
			line = sl[0].trimmed().toInt() - 1;
			col = sl[1].trimmed().toInt();
		}
	}
	emit fileChoosen(currentFile().first, currentFile().second, line, col);
	close();
}

QPair<QString, int> FileSelector::currentFile(){
	int index = list->currentRow();
	if (index < 0 || index >= rawFiles.count()) return QPair<QString, int>("", -1);
	QString file = list->item(index)->text();
	int duplicate = 0;
	for (int i=0;i<index;i++)
		if (list->item(i)->text() == file)
			duplicate++;
	return QPair<QString, int>(file, duplicate);
}
