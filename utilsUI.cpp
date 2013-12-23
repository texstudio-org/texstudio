#include "utilsUI.h"
#include "utilsSystem.h"
#include "utilsVersion.h"

bool txsConfirm(const QString &message){
	return QMessageBox::question(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}
bool txsConfirmWarning(const QString &message){
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}
QMessageBox::StandardButton txsConfirmWarning(const QString &message, QMessageBox::StandardButtons buttons){
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, buttons, QMessageBox::Yes);
}
void txsInformation(const QString &message){
	QMessageBox::information(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}
void txsWarning(const QString &message){
	QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}
void txsWarning(const QString &message, bool &noWarnAgain){
	QMessageBox msgBox(QMessageBox::Warning, TEXSTUDIO, message, QMessageBox::Ok, QApplication::activeWindow());
	QCheckBox cbNoWarnAgain(QCoreApplication::translate("Texmaker", "Do not warn again.", "General warning dialog"), &msgBox);
	cbNoWarnAgain.setChecked(noWarnAgain);
	cbNoWarnAgain.blockSignals(true); // quick hack to prevent closing the message box
	msgBox.addButton(&cbNoWarnAgain, QMessageBox::ActionRole);
	msgBox.exec();
	noWarnAgain = cbNoWarnAgain.isChecked();
}

void txsCritical(const QString &message){
	QMessageBox::critical(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}

QToolButton* createComboToolButton(QWidget *parent,const QStringList& list, const QList<QIcon>& icons, int height, const QObject * receiver, const char * member,QString defaultElem,QToolButton *combo){
    Q_UNUSED(icons)
	const QFontMetrics &fm = parent->fontMetrics();
	if (height == -1) height = 0;
	else if (height == 0) {
		if (parent->property("innerButtonHeight").isValid()) height =parent->property("innerButtonHeight").toInt();
		else {
			height = parent->height() - 2;
			parent->setProperty("innerButtonHeight", height);
		}
	}

	if (combo==0)
		combo=new QToolButton(parent);
	if (height != 0)
		combo->setMinimumHeight(height);
	combo->setPopupMode(QToolButton::MenuButtonPopup);
	combo->setToolButtonStyle(Qt::ToolButtonTextOnly);

	// remove old actions
	foreach(QAction * mAction, combo->actions())
		combo->removeAction(mAction);

	QMenu *mMenu=new QMenu(combo);
	int max=0;
	bool defaultSet = false;
	for (int i=0; i<list.length(); i++) {
		QString text = list[i];
        //QIcon icon = (i<icons.length()) ? icons[i] : QIcon();
        QAction* mAction=mMenu->addAction(text, receiver, member);
		max = qMax(max, fm.width(text+"        "));
		if (text == defaultElem) {
			combo->setDefaultAction(mAction);
			defaultSet = true;
		}
	}
	if (!defaultSet){
		if(list.isEmpty())
			combo->setDefaultAction(new QAction("<"+QApplication::tr("none")+">",combo));
		else
			combo->setDefaultAction(mMenu->actions().first());
	}

	combo->setMinimumWidth(max);
	combo->setMenu(mMenu);
	return combo;
}

QToolButton* comboToolButtonFromAction(QAction* action){
	if (!action) return 0;
	QToolButton *button = qobject_cast<QToolButton*>(action->parent());
	if (!button) {
		QMenu* menu=qobject_cast<QMenu*>(action->parent());
		if (!menu) return 0;
		button=qobject_cast<QToolButton*>(menu->parent());
		if (!button) return 0;
	}
	return button;
}

QToolButton* createToolButtonForAction(QAction* action) {
	QToolButton *tb = new QToolButton();
	if (!action->icon().isNull())
		tb->setIcon(action->icon());
	else
		tb->setText(action->text());
	tb->setToolTip(action->toolTip());
	tb->setCheckable(action->isCheckable());
	tb->setChecked(action->isChecked());
	tb->connect(tb, SIGNAL(clicked(bool)), action, SLOT(setChecked(bool)));
	tb->connect(action, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
	return tb;
}

void setSubtreeExpanded(QTreeView *view, QModelIndex idx, bool expand) {
	for (int row=0;; row++) {
		QModelIndex node = view->model()->index(row, 0, idx);
		if (!node.isValid())
			break;
		setSubtreeExpanded(view, node, expand);
	}
	view->setExpanded(idx, expand);
}

bool browse(QWidget* w, const QString& title, const QString& extension, const QString& startPath, bool list) {
	QLineEdit* le = qobject_cast<QLineEdit*>(w);
	QComboBox* cb = qobject_cast<QComboBox*>(w);
	REQUIRE_RET(le || cb, false);
	QString oldpath = le ? le->text() : cb->currentText();
	QString path = oldpath;
#ifdef Q_OS_WIN32
	QString pathSep = ";";
#else
	QString pathSep = ":";
#endif
	if (list && !path.isEmpty()) path = path.split(pathSep).last();
	if (path.startsWith('"')) path.remove(0,1);
	if (path.endsWith('"')) path.chop(1);
	if (path.isEmpty()) path = startPath;
	if (extension == "/") path = QFileDialog::getExistingDirectory(0, title, path);
	else path = QFileDialog::getOpenFileName(0, title, path, extension, 0, QFileDialog::DontResolveSymlinks);
	if (!path.isEmpty()) {
		if (!list) path.replace(QString("\\"), QString("/"));
		else if (!oldpath.isEmpty()) path = oldpath + pathSep + path;
		if (le) le->setText(path);
		if (cb) cb->setEditText(path);
		return true;
	}
	return false;
}

QColor colorFromRGBAstr(const QString &hex, QColor fallback) {
	QString c = hex;
	if (c.startsWith('#'))
		c = c.mid(1);
	if (c.length() != 8) return fallback;
	bool r,g,b,a;
	QColor color(c.mid(0,2).toInt(&r, 16), c.mid(2,2).toInt(&g, 16), c.mid(4,2).toInt(&b, 16), c.mid(6,2).toInt(&a, 16));
	if (r && g && b && a)
		return color;
	return fallback;
}
