#include "utilsUI.h"
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

QToolButton* createComboToolButton(QWidget *parent,const QStringList& list, int height, const QObject * receiver, const char * member,QString defaultElem,QToolButton *combo){
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

	// remove old actions
	foreach(QAction * mAction, combo->actions())
		combo->removeAction(mAction);

	QMenu *mMenu=new QMenu(combo);
	int max=0;
	bool defaultSet = false;
	foreach(const QString& elem,list){
		QAction* mAction=mMenu->addAction(elem,receiver,member);
		max=qMax(max,fm.width(elem+"        "));
		if(elem==defaultElem) {
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
