#ifndef QT_NO_DEBUG

#include "latexoutputfilter_t.h"
#include "latexoutputfilter.h"
#include "testutil.h"
#include <QtTest/QtTest>

LatexOutputFilterTest::LatexOutputFilterTest(QObject *parent) :
	QObject(parent)
{
}


QString LatexOutputFilterTest::stackTopFilename(const LatexOutputFilter &f) {
	if (f.m_stackFile.count() == 0)
		return QString();
	return f.m_stackFile.top().file();
}


void LatexOutputFilterTest::run_data() {
	QTest::addColumn<QStringList>("log");
	QTest::addColumn<short>("cookieAtEnd");
	QTest::addColumn<QString>("stackTopFile");

	QTest::newRow("open")
			<< (QStringList() << "(d:/data/test.tex")
			<< short(LatexOutputFilter::Start)
			<< "d:/data/test.tex";
	QTest::newRow("open with text")
			<< (QStringList() << "(d:/data/test.tex with text")
			<< short(LatexOutputFilter::Start)
			<< "d:/data/test.tex";
	QTest::newRow("open 77")
			<< (QStringList() << "(d:/56789_123456789_123456789_123456789_12345678___74_chars_before_the_dot.au")
			<< short(LatexOutputFilter::Start)
			<< "d:/56789_123456789_123456789_123456789_12345678___74_chars_before_the_dot.au";
	QTest::newRow("open 78")
			<< (QStringList() << "(d:/56789_123456789_123456789_123456789_12345678___74_chars_before_the_dot.aux")
			<< short(LatexOutputFilter::InFileName)
			<< QString();
	QTest::newRow("open close")
			<< (QStringList() << "(test.tex)")
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("open close next line")
			<< (QStringList() << "(test.tex"
							  << ")"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("open close next line 2")
			<< (QStringList() << "(test.tex bar"
							  << ") foo"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("open close next line 3")
			<< (QStringList() << "(test.tex bar"
							  << ") (newfile.aux"
				)
			<< short(LatexOutputFilter::Start)
			<< "newfile.aux";
	QTest::newRow("nested 1")
			<< (QStringList() << "(test.tex (newfile.aux"
				)
			<< short(LatexOutputFilter::Start)
			<< "newfile.aux";
	QTest::newRow("nested 2")
			<< (QStringList() << "(test.tex bar"
							  << "(newfile.aux"
				)
			<< short(LatexOutputFilter::Start)
			<< "newfile.aux";
	QTest::newRow("nested 3")
			<< (QStringList() << "(test.tex bar"
							  << "(newfile.aux"
							  << ")"
				)
			<< short(LatexOutputFilter::Start)
			<< "test.tex";
	QTest::newRow("continued 1")
			<< (QStringList() << "foo bar blub            *** this line has 78 chars ***             (/some/path/w"
				)
			<< short(LatexOutputFilter::InFileName)
			<< QString();
	QTest::newRow("continued 2")
			<< (QStringList() << "foo bar blub            *** this line has 78 chars ***             (/some/path/w"
							  << "ith/file.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< "/some/path/with/file.tex";
	QTest::newRow("continued 3")
			<< (QStringList() << "foo bar blub            *** this line has 78 chars ***             (/some/path/w"
							  << "ith/file.tex and text"
				)
			<< short(LatexOutputFilter::Start)
			<< "/some/path/with/file.tex";
	QTest::newRow("quoted 1")
			<< (QStringList() << "(\"test bar.tex\"")
			<< short(LatexOutputFilter::Start)
			<< "test bar.tex";
	QTest::newRow("quoted 2")
			<< (QStringList() << "(\"test bar.tex\" more")
			<< short(LatexOutputFilter::Start)
			<< "test bar.tex";
	QTest::newRow("quoted 78")
			<< (QStringList() << "(\"d:/56789_123456789 123456789 123456789 12345678__73_chars_before_the_dot.aux\"")
			<< short(LatexOutputFilter::Start)
			<< "d:/56789_123456789 123456789 123456789 12345678__73_chars_before_the_dot.aux";
	QTest::newRow("quoted brackets 1")
			<< (QStringList() << "(foo (\"test (bar).tex\"")
			<< short(LatexOutputFilter::Start)
			<< "test (bar).tex";
	QTest::newRow("quoted brackets 2")
			<< (QStringList() << "(foo (\"test bar).tex\"")
			<< short(LatexOutputFilter::Start)
			<< "test bar).tex";
	QTest::newRow("quoted brackets 3")
			<< (QStringList() << "(foo (\"test (bar.tex\"")
			<< short(LatexOutputFilter::Start)
			<< "test (bar.tex";
	QTest::newRow("quoted continued 1")
			<< (QStringList() << "some text             *** this line has 78 chars ***     (\"/before_the_dot/aux/"
				)
			<< short(LatexOutputFilter::InQoutedFileName)
			<< QString();
	QTest::newRow("quoted continued 2")
			<< (QStringList() << "some text             *** this line has 78 chars ***     (\"/before_the_dot/aux/"
							  << "more.tex "
				)
			<< short(LatexOutputFilter::InQoutedFileName)
			<< QString();
	QTest::newRow("quoted continued 3")
			<< (QStringList() << "some text             *** this line has 78 chars ***     (\"/before_the_dot/aux/"
							  << "more.tex\""
				)
			<< short(LatexOutputFilter::Start)
			<< "/before_the_dot/aux/more.tex";
	QTest::newRow("quoted continued 4")
			<< (QStringList() << "some text             *** this line has 78 chars ***     (\"/before_the_dot/aux/"
							  << "more.tex\" other"
				)
			<< short(LatexOutputFilter::Start)
			<< "/before_the_dot/aux/more.tex";
}

void LatexOutputFilterTest::run() {

	QFETCH(QStringList, log);
	QFETCH(short, cookieAtEnd);
	QFETCH(QString, stackTopFile);

	LatexOutputFilter filter;
	short sCookie = LatexOutputFilter::Start;
	foreach (const QString &line, log) {
		sCookie = filter.parseLine(line, sCookie);
	}

	QEQUAL(sCookie, cookieAtEnd);
	QEQUAL(stackTopFilename(filter), stackTopFile);

}



#endif
