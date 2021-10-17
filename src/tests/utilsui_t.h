#ifndef Header_UtilsUI_T
#define Header_UtilsUI_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "utilsUI.h"
#include "testutil.h"
#include <QtTest/QtTest>


class UtilsUITest: public QObject{
	Q_OBJECT
public:
	UtilsUITest(bool executeAllTests) : allTests(executeAllTests) {}
private slots:
	void test_mediumLightColor_data() {
		QTest::addColumn<unsigned int>("iRgb");
		QTest::addColumn<int>("factor");
		QTest::addColumn<unsigned int>("expectediRgb");

		QTest::newRow("equal") << rgb(255, 0, 0) << 100 << rgb(255, 0, 0);
		QTest::newRow("equalf") << rgbf(.2, .6, 1.) << 100 << rgbf(.2, 0.6, 1.);

		QTest::newRow("light") << rgb(240, 230, 220) << 150 << rgb(160, 153, 147);
		QTest::newRow("dark") << rgb(10 ,20, 30) << 150 << rgb(15, 30, 45);

		QTest::newRow("black") << rgb(0, 0, 0) << 150 << rgb(50, 50, 50);
		QTest::newRow("white") << rgb(255, 255, 255) << 150 << rgb(170, 170, 170);

		QTest::newRow("factor150") << rgbf(.2, .6, 1.) << 150 << rgb(34, 102, 170);
        QTest::newRow("factor120") << rgbf(.2, .6, 1.) << 120 << rgb(42, 127, 212);
		QTest::newRow("factor100") << rgbf(.2, .6, 1.) << 100 << rgb(51, 153, 255);
		QTest::newRow("factor90") << rgbf(.2, .6, 1.) << 90 << rgb(79, 167, 255);
		QTest::newRow("factor80") << rgbf(.2, .6, 1.) << 80 << rgb(115, 185, 255);
		QTest::newRow("factor70") << rgbf(.2, .6, 1.) << 70 << rgb(158, 207, 255);
        QTest::newRow("factor60") << rgbf(.2, .6, 1.) << 60 << rgb(219, 237, 255);
		QTest::newRow("factor50") << rgbf(.2, .6, 1.) << 50 << rgb(255, 255, 255);
	}

	void test_mediumLightColor() {
		QFETCH(unsigned int, iRgb);
		QFETCH(int, factor);
		QFETCH(unsigned int, expectediRgb);

		QColor resultColor = UtilsUi::mediumLightColor(QColor(static_cast<QRgb>(iRgb)), factor);
        // tolerant comparison as the result changes with QT5.14
        QVERIFY2(abs(resultColor.red()-qRed(static_cast<QRgb>(expectediRgb)))<=1,qPrintable(QString("red unexpected %1 %2").arg(resultColor.red()).arg(qRed(static_cast<QRgb>(expectediRgb)))));
        QVERIFY2(abs(resultColor.green()-qGreen(static_cast<QRgb>(expectediRgb)))<=1,qPrintable(QString("green unexpected %1 %2").arg(resultColor.green()).arg(qGreen(static_cast<QRgb>(expectediRgb)))));
        QVERIFY2(abs(resultColor.blue()-qBlue(static_cast<QRgb>(expectediRgb)))<=1,qPrintable(QString("blue unexpected %1 %2").arg(resultColor.blue()).arg(qBlue(static_cast<QRgb>(expectediRgb)))));
	}

private:
	bool allTests;
	static unsigned int rgb(int red, int green, int blue) { return static_cast<unsigned int>(qRgb(red, green, blue)); }
	static unsigned int rgbf(qreal red, qreal green, qreal blue) { return static_cast<unsigned int>(qRgb(qRound(red*255), qRound(green*255), qRound(blue*255))); }
};

#endif // QT_NO_DEBUG
#endif // UTILSUI_T_H
