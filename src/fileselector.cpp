#include "fileselector.h"
#include "utilsUI.h"

FileSelector::FileSelector(QWidget *parent, bool multiselect) :
	QWidget(parent), multiselect(multiselect)
{
	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
	QVBoxLayout *vlayout = new QVBoxLayout();
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->setSpacing(0);
	setLayout(vlayout);

	list = new QListWidget(this);
	vlayout->addWidget(list);
	filter = new QLineEdit(this);
	vlayout->addWidget(filter);
	connect(filter, SIGNAL(textChanged(QString)), SLOT(filterChanged(QString)));
	filter->installEventFilter(this);

	QPalette p = QApplication::palette(); //let the list appear selected (does not work with gtk+ style)
	p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
	p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));
	list->setPalette(p);
	connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(emitChoosen()));

	setAttribute(Qt::WA_DeleteOnClose);

	if (multiselect)
		list->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void FileSelector::init(const QStringList &files, int current)
{
	filter->setFocus();
	rawFiles = files;
	filterChanged(filter->text());
	if (current >= 0 && current < rawFiles.count()) {
		int r = 0;
		for (int i = 0; i < current; i++)
			if (list->item(i)->text() == rawFiles[i]) r++;
		if (list->item(r)->text() == rawFiles[current])
			list->setCurrentRow(r);
	}
}

void FileSelector::setCentered()
{
	if (parentWidget()) {
		QRect rect = parentWidget()->geometry();
		QSize s = rect.size();
		QPoint p = parentWidget()->mapToGlobal(rect.topLeft());  // popups live in global coordinates

		int fsw = s.width() / 2;
		int scrollbarwidth = 50; //value that works on my computer...
		/*if (list->verticalScrollBar()) {
			QStyleOptionSlider sos;
			sos.initFrom(list->verticalScrollBar());
			scrollbarwidth = qAbs(list->verticalScrollBar()->style()->subControlRect(QStyle::CC_ScrollBar, &sos,  QStyle::SC_ScrollBarGroove, list->verticalScrollBar()).width());
		}*/
		QFontMetrics fm = list->fontMetrics();
		for (int i = 0; i < rawFiles.size(); i++)
			fsw = qMax(fsw, UtilsUi::getFmWidth(fm, rawFiles[i]) + scrollbarwidth );
		fsw = qMin(fsw, s.width());

		setGeometry(s.width() / 2 - fsw / 2 + p.x(), s.height() / 8 + p.y(), fsw, s.height() / 2);
		setMinimumWidth(fsw); //set geometry alone leads to a too small window. but we need to call setGeometry first, or it crashes if fsw = s.width()
	}
}

void FileSelector::filterChanged(const QString &newFilter)
{
	QString nf = newFilter;
	if (newFilter.contains(':') && QRegExp(".*:[0-9; ]*").exactMatch(newFilter))
		nf = newFilter.left(newFilter.lastIndexOf(':'));

	QStringList filterList = nf.split(" ");

	QList<QPair<QString, int> > oldFiles = currentFiles();
	list->clear();
	foreach (const QString &s, rawFiles) {
		bool skip = false;
		foreach (const QString &tf, filterList)
			if (!s.contains(tf, Qt::CaseInsensitive)) {
				skip = true;
				break;
			}
		if (skip) continue;
		list->addItem(s);
	}

	if (!oldFiles.isEmpty()) {
		bool foundOne = false;
		for (int o = 0; o < oldFiles.size(); o++) {
			const QPair<QString, int> &oldFile = oldFiles[o];
			int duplicate = oldFile.second;
			for (int i = 0; i < list->count(); i++)
				if (list->item(i)->text() == oldFile.first) {
					duplicate -= 1;
					if (duplicate < 0) {
						if (!foundOne) list->setCurrentRow(i);
						else if (list->selectionModel() && list->model()) list->selectionModel()->select(list->model()->index(i, 0), QItemSelectionModel::Select);
						foundOne = true;
						break;
					}
				}
		}
		if (foundOne)
			return;
	}

	list->setCurrentRow(0);
}

void FileSelector::showEvent(QShowEvent *event)
{
	setCentered();
	QWidget::showEvent(event);
}

bool FileSelector::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		int key = static_cast<QKeyEvent *>(event)->key();
		switch (key) {
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_PageUp:
		case Qt::Key_PageDown:
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
		case Qt::Key_Return:
		case Qt::Key_Enter:
			emitChoosen();
			return true;
		case Qt::Key_Escape:
			close();
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

typedef QPair<QString, int> QPairStringInt;

void FileSelector::emitChoosen()
{
	QString jumpTo = filter->text().mid(filter->text().lastIndexOf(':') + 1);
	int line = -1, col = -1;
	if (!jumpTo.isEmpty()) {
		if (!jumpTo.contains(';')) line = jumpTo.trimmed().toInt() - 1;
		else {
			QStringList sl = jumpTo.split(';');
			line = sl[0].trimmed().toInt() - 1;
			col = sl[1].trimmed().toInt();
		}
	}
	foreach (const QPairStringInt &p, currentFiles())
		emit fileChoosen(p.first, p.second, line, col);
	close();
}

QList<QPair<QString, int> > FileSelector::currentFiles()
{
	QList<QPair<QString, int> > result;
	int cindex = list->currentRow();
	if (cindex < 0 || cindex >= rawFiles.count()) return result;
	QList<int> indices;
    if (!multiselect){
        indices << cindex;
    } else {
        if (list->selectionModel()){
            foreach (const QModelIndex &index, list->selectionModel()->selectedIndexes()){
                indices << index.row();
            }
        }
    }
	foreach (int index, indices) {
		QString file = list->item(index)->text();
		int duplicate = 0;
		for (int i = 0; i < index; i++)
			if (list->item(i)->text() == file)
				duplicate++;
		result << QPair<QString, int>(file, duplicate);
	}
	return result;
}
