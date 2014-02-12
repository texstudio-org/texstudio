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

	// *** real-world examples ***
	// These examples are necessary to further refine the heuristic of bracket/file detection.
	// Parts of the compiled tex file may be included in the log, which means it can be anything.
	// A good heuristic should therefore be careful and only detect filenames in situations that really
	// happen in the log. Currently we probably detect too much as filenames, e.g. does it happen that
	// a file is closed with ')' and there is plain text following?
	// When trying to narrow down the detection in the future theses examples give a lower limit
	// preventing that we will miss real filenames.
	QTest::newRow("open")
			<< (QStringList() << "(d:/data/test.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< "d:/data/test.tex";

	QTest::newRow("quoted open")
			<< (QStringList() << "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\ams\\math\\amsopn.sty\""
				)
			<< short(LatexOutputFilter::Start)
			<< QString("C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\ams\\math\\amsopn.sty");
	QTest::newRow("quoted open")
			<< (QStringList() << "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\ams\\math\\amsopn.sty\""
							  << "Package: amsopn 1999/12/14 v2.01 operator names"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\ams\\math\\amsopn.sty");
	QTest::newRow("quoted open close")
			<< (QStringList() << "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\ams\\math\\amsopn.sty\""
							  << "Package: amsopn 1999/12/14 v2.01 operator names"
							  << ")"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("quoted close open")
			<< (QStringList() << "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\base\\minimal.cls\""
							  << "Document Class: minimal 2001/05/25 Standard LaTeX minimal class"
							  << ") (\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\base\\inputenc.sty\""
				)
			<< short(LatexOutputFilter::Start)
			<< QString("C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\base\\inputenc.sty");

	QTest::newRow("open")
			<< (QStringList() << "(D:\\bugreport\\bug.aux"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("D:\\bugreport\\bug.aux");
	QTest::newRow("open close")
			<< (QStringList() << "(D:\\bugreport\\bug.aux)"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("open close")
			<< (QStringList() << "(D:\\bugreport\\bug.aux)"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("multiple closing 1")
			<< (QStringList()
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\xkeyval\\xkeyval.sty\""
				<< "Package: xkeyval 2008/08/13 v2.6a package option processing (HA)"
				<< ""
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\generic\\xkeyval\\xkeyval.tex\""
				<< "\\XKV@toks=\\toks16"
				<< "\\XKV@tempa@toks=\\toks17"
				<< "\\XKV@depth=\\count79"
				<< "File: xkeyval.tex 2008/08/13 v2.6a key=value parser (HA)"
				<< ""
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\generic\\xkeyval\\keyval.tex\"))"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\xkeyval\\xkeyval.sty");
	QTest::newRow("multiple closing 2")
			<< (QStringList()
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\latex\\xkeyval\\xkeyval.sty\""
				<< "Package: xkeyval 2008/08/13 v2.6a package option processing (HA)"
				<< ""
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\generic\\xkeyval\\xkeyval.tex\""
				<< "\\XKV@toks=\\toks16"
				<< "\\XKV@tempa@toks=\\toks17"
				<< "\\XKV@depth=\\count79"
				<< "File: xkeyval.tex 2008/08/13 v2.6a key=value parser (HA)"
				<< ""
				<< "(\"C:\\Program Files (x86)\\MiKTeX 2.9\\tex\\generic\\xkeyval\\keyval.tex\")))"
				)
			<< short(LatexOutputFilter::Start)
			<< QString();
	QTest::newRow("multiple closing with space")
			<< (QStringList()
				<< "(D:\\foo\\file1.tex"
				<< "(D:\\foo\\file2.tex"
				<< "(D:\\foo\\file.aux) )"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("D:\\foo\\file1.tex");
	QTest::newRow("close with something behind")
			<< (QStringList()
				<< "(D:\\foo\\file1.tex"
				<< "(D:\\foo\\file2.tex"
				<< ") [1{C:/Users/Foo/AppData/Local/MiKTeX/2.9/pdftex/config/pdftex.map}]"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("D:\\foo\\file1.tex");
	// Using TeXlive
	QTest::newRow("open rel.")
			<< (QStringList()
				<< "(./Tex_settings/LaTeXPackages.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./Tex_settings/LaTeXPackages.tex");
	QTest::newRow("multiple closing with open")
			<< (QStringList()
				<< "(d:/dummy.tex"
				<< "(c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfunctions.round.code.te"
				<< "x)"
				<< "(c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfunctions.misc.code.tex"
				<< ")) "
				)
			<< short(LatexOutputFilter::Start)
			<< QString("");
	QTest::newRow("multiple closing with open 2")
			<< (QStringList()
				<< "(d:/dummy.tex"
				<< "(c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfunctions.round.code.te"
				<< "x)"
				<< "(c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfunctions.misc.code.tex"
				<< ")) (c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfloat.code.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("c:/texlive/2012/texmf-dist/tex/generic/pgf/math/pgfmathfloat.code.tex");
	QTest::newRow("multiple closing with open and linebreak")
			<< (QStringList()
				<< "(d:/dummy.tex"
				<< "(c:/texlive/2012/texmf-dist/tex/latex/beamer/translator/translator-language-map"
				<< "pings.tex)) (c:/texlive/2012/texmf-dist/tex/latex/siunitx/siunitx.sty"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("c:/texlive/2012/texmf-dist/tex/latex/siunitx/siunitx.sty");
	QTest::newRow("multiple files in one line")
			<< (QStringList()
				<< "(./_Thesis_.aux (./TeX_files/0a_Cover.aux) (./TeX_files/0b_Abstract.aux)"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./_Thesis_.aux");
	QTest::newRow("whitespace open")
			<< (QStringList()
				<< " (./TeX_files/01_Introduction.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./TeX_files/01_Introduction.tex");
	QTest::newRow("close with markers in front and open")
			<< (QStringList()
				<< "(./TeX_files/0a_Cover.tex [1]"
				<< "[3] [4]) (./TeX_files/0b_Abstract.tex) [5] [6] (./_Thesis_.toc"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./_Thesis_.toc");
	QTest::newRow("close with markers in front")
			<< (QStringList()
				<< "(./TeX_files/0a_Cover.tex [1]"
				<< "[3] [4]) (./TeX_files/0b_Abstract.tex) [5] [6] "
				)
			<< short(LatexOutputFilter::Start)
			<< QString("");
	QTest::newRow("close with markers in front 2")
			<< (QStringList()
				<< "(./TeX_files/0a_Cover.tex [1]"
				<< "[3] [4]) (./TeX_files/0b_Abstract.tex)"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("");
	QTest::newRow("close with markers in front 3")
			<< (QStringList()
				<< "(./TeX_files/0a_Cover.tex [1]"
				<< "[3] [4]"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./TeX_files/0a_Cover.tex");
	QTest::newRow("unquoted file with backets")
			<< (QStringList()
				<< "(./a(balance-bracketed)file.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./a(balance-bracketed)file.tex");
	QTest::newRow("unquoted file with spaces")
			<< (QStringList()
				<< "(./a file with spaces.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./a file with spaces.tex");
	QTest::newRow("unquoted file with backets and spaces")
			<< (QStringList()
				<< "(foo.tex"
				<< ") (./a (file) with bracets and spaces.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./a (file) with bracets and spaces.tex");
	QTest::newRow("unquoted file with backets and spaces")
			<< (QStringList()
				<< "(foo.tex"
				<< ") (./a (file) with bracets and spaces.tex continued"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("./a (file) with bracets and spaces.tex");


	// synthetic examples
	// these might overconstrain the filename detection heuristic, if there cannot be found any real-world
	// example supporting those. They might get removed in the future.

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
			<< (QStringList() << "(./test.tex bar"
							  << "(./newfile.aux"
							  << ")"
				)
			<< short(LatexOutputFilter::Start)
			<< "./test.tex";
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

void LatexOutputFilterTest::fileNameLikelyComplete_data() {
	QTest::addColumn<QString>("name");
	QTest::addColumn<bool>("result");

	QTest::newRow("empty") << "" << false;
	QTest::newRow("text") << "foo" << false;
	QTest::newRow("text2") << "foo bar" << false;
	QTest::newRow("text3") << "foo bar baz." << false;
	QTest::newRow("text4") << "foo bar baz. More" << false;
	QTest::newRow("file") << "foo.tex" << true;
	QTest::newRow("file2") << "foo.bar" << true;
	QTest::newRow("file3") << "foo bar.tex" << true;
	QTest::newRow("file3") << "foo.jpeg" << true;
	QTest::newRow("expr") << "filter.parseLine" << false;
}

void LatexOutputFilterTest::fileNameLikelyComplete() {
	QFETCH(QString, name);
	QFETCH(bool, result);

	QEQUAL(LatexOutputFilter::fileNameLikelyComplete(name), result);
}

#endif
