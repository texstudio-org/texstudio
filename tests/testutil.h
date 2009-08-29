#ifndef TESTUTIL_H
#define TESTUTIL_H
#ifndef QT_NO_DEBUG
#include <QtTest/QtTest>
#include <QMessageBox>
#define QSVERIFY(a,b) QVERIFY(a)
#define QSVERIFY2(a,b) QVERIFY2(a, (b).toLatin1().constData())
#define QEQUAL(a,b) QSVERIFY2((a)==(b), QString("equal failed: got \"%1\" !=expected \"%2\" ").arg(a).arg(b))
#define QEQUAL2(a,b,m) QSVERIFY2((a)==(b), QString("equal failed: got \"%1\" !=expected \"%2\"  reason:%3").arg(a).arg(b).arg(m))

namespace QTest{
class MessageBoxCloser:public QObject{
	Q_OBJECT
public:
	MessageBoxCloser(bool mustExists=false, QMessageBox::StandardButton button=QMessageBox::NoButton);
private:
	bool m_mustExists;
	QMessageBox::StandardButton m_button;
private slots: 
	void closeNow();
};
void closeMessageBoxLater(bool mustExists=false, QMessageBox::StandardButton button=QMessageBox::NoButton);
void messageBoxShouldBeClose();
}
#endif
#endif
