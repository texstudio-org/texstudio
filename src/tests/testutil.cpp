#ifndef QT_NO_DEBUG
#include "testutil.h"
namespace QTest{
MessageBoxCloser* curCloser=nullptr;
MessageBoxCloser::MessageBoxCloser(bool mustExists, QMessageBox::StandardButton button):QObject(nullptr), m_mustExists(mustExists), m_button(button){
	if (button!=QMessageBox::Ok && button!=QMessageBox::Cancel && button!=QMessageBox::NoButton && button!=QMessageBox::Yes)
		QVERIFY2(false, "invalid button for messagebox closing");
	QTimer::singleShot(1, this, SLOT(closeNow()));
}

void MessageBoxCloser::closeNow(){
	deleteLater();
	QWidget* messageWindow = QApplication::activeModalWidget();
    if (!messageWindow){
		foreach (QWidget *widget, QApplication::topLevelWidgets())
			if (widget->isModal())
				messageWindow=widget;
    }
	if (!messageWindow) {
		QVERIFY2(!m_mustExists, "messagebox doesn't exists");
		return; //keyClick crashes (assert false)  if it can't find a window
	}
	switch (m_button) {
		case QMessageBox::Ok: case QMessageBox::Yes:
			QTest::keyClick(messageWindow, Qt::Key_Return);
			break;
		default:
			QTest::keyClick(messageWindow, Qt::Key_Escape);
			break;
	}
    curCloser=nullptr;
}
void closeMessageBoxLater(bool mustExists, QMessageBox::StandardButton button){
	if (curCloser) QWARN("multiple closing calls");
	curCloser=new MessageBoxCloser(mustExists, button);
}
void messageBoxShouldBeClose(){
	QVERIFY2(!curCloser, "MessageBox couldn't be closed");
}

/**
 * \brief Process all pending events except for UI and network events.
 */
void processPendingEvents(void)
{
	QCoreApplication::processEvents(QEventLoop::AllEvents);
	// Deferred delete must be processed explicitly. Using 0 for event_type does not work.
	QCoreApplication::sendPostedEvents(Q_NULLPTR, QEvent::DeferredDelete);
}

}
#endif
