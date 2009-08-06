#ifndef QT_NO_DEBUG
#include "testutil.h"
MessageBoxCloser::MessageBoxCloser(bool mustExists, QMessageBox::StandardButton button):QObject(0), m_mustExists(mustExists), m_button(button){
	if (button!=QMessageBox::Ok && button!=QMessageBox::Cancel && button!=QMessageBox::NoButton)
		QVERIFY2(false, "invalid button for messagebox closing");
	QTimer::singleShot(1, this, SLOT(closeNow()));
}

void MessageBoxCloser::closeNow(){
	deleteLater();
	QWidget* messageWindow = QApplication::activeModalWidget();
	if (!messageWindow) 
		foreach (QWidget *widget, QApplication::topLevelWidgets()) 
			if (widget->isModal())
				messageWindow=widget;
	if (!messageWindow) {
		QVERIFY2(!m_mustExists, "messagebox doesn't exists");
		return; //keyClick crashes (assert false)  if it can't find a window
	}
	switch (m_button) {
		case QMessageBox::Ok: 
			QTest::keyClick(messageWindow, Qt::Key_Return);
			break;
		default:
			QTest::keyClick(messageWindow, Qt::Key_Escape);
			break;
	}	
}

void closeMessageBoxLater(bool mustExists, QMessageBox::StandardButton button){
	new MessageBoxCloser(mustExists, button);
}
#endif


