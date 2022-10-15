#ifndef Header_TestUtil
#define Header_TestUtil
#ifndef QT_NO_DEBUG
#include <QtTest/QtTest>
#include <QMessageBox>
#include <QObject>
//#define QSVERIFY(a,b) QVERIFY(a)
#define QSVERIFY2(a,b) QVERIFY2(a, qPrintable(QString("%1").arg(b)))
#define QEQUAL(a,b) QSVERIFY2((a)==(b), QString("equal failed: got \"%1\" !=expected \"%2\" ").arg(a).arg(b))
#define QEQUAL2(a,b,m) QSVERIFY2((a)==(b), QString("equal failed: got \"%1\" !=expected \"%2\"  reason:%3").arg(a).arg(b).arg(m))
#define QEQUALLIST(a,b) QVERIFY2((a)==(b), qPrintable(QString("list equal failed: got \"%1\" !=expected \"%2\" ").arg(a.join("||")).arg(b.join("||"))))

#define Q__POSITION__ QString(__FILE__ ": %1").arg(__LINE__)

//Q_DECLARE_METATYPE(QList<int>);

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

void processPendingEvents(void);
}

extern bool globalExecuteAllTests;
#endif
#endif
