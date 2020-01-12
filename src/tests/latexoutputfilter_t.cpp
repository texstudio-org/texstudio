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

QString LatexOutputFilterTest::currentMessage(const LatexOutputFilter &f)
{
	return f.m_currentItem.message;
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
	QTest::newRow("open space bracket")
			<< (QStringList() << "(./chapter1.tex (")
			<< short(LatexOutputFilter::ExpectingFileName)
			<< QString("./chapter1.tex");
	QTest::newRow("open bracket")
			<< (QStringList() << "(./chapter1.tex(")
			<< short(LatexOutputFilter::ExpectingFileName)
			<< QString("./chapter1.tex");
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
	QTest::newRow("other brace")
			<< (QStringList()
				<< "Defining command \test with sig. 'r()' on line 3"
				)
			<< short(LatexOutputFilter::Start)
			<< QString("");
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
	QTest::newRow("bracketed single character")
			<< (QStringList()
				<< "(c:/texlive/2012/texmf-dist/tex/latex/latexconfig/epstopdf-sys.cfg"
				<< "File: epstopdf-sys.cfg 2010/07/13 v1.3 Configuration of (r)epstopdf for TeX Liv"
				<< "e"
				<< ")"
				)
			<< short(LatexOutputFilter::Start)
			<< "";
	QTest::newRow("bracketed single character 2")
			<< (QStringList()
				<< "(c:/texlive/2012/texmf-dist/tex/latex/latexconfig/epstopdf-sys.cfg"
				<< "File: epstopdf-sys.cfg 2010/07/13 v1.3 Configuration of (r)epstopdf for TeX Liv"
				)
			<< short(LatexOutputFilter::Start)
			<< "c:/texlive/2012/texmf-dist/tex/latex/latexconfig/epstopdf-sys.cfg";
	QTest::newRow("badbox underfull")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Underfull \\hbox (badness 10000) in paragraph"
				)
			<< short(LatexOutputFilter::BadBox)
			<< "c:/test.tex";
	QTest::newRow("badbox underfull")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Overfull \\hbox (badness 10000) in paragraph"
				)
			<< short(LatexOutputFilter::BadBox)
			<< "c:/test.tex";
	QTest::newRow("badbox underfull complete single line")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Underfull \\hbox (badness 10000) in paragraph at line 827"
				)
			<< short(LatexOutputFilter::ExpectingBadBoxTextQoute)
			<< "c:/test.tex";
	QTest::newRow("badbox underfull complete multi line")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Underfull \\hbox (badness 10000) in paragraph at lines 827--831"
				)
			<< short(LatexOutputFilter::ExpectingBadBoxTextQoute)
			<< "c:/test.tex";
	QTest::newRow("badbox overfull complete single line")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Overfull \\hbox (badness 10000) in paragraph at line 827"
				)
			<< short(LatexOutputFilter::ExpectingBadBoxTextQoute)
			<< "c:/test.tex";
	QTest::newRow("badbox overfull complete multi line")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Overfull \\hbox (badness 10000) in paragraph at lines 827--831"
				)
			<< short(LatexOutputFilter::ExpectingBadBoxTextQoute)
			<< "c:/test.tex";
	QTest::newRow("unbalanced open bracket in badbox textqoute")
			<< (QStringList()
				<< "(c:/test.tex"
				<< ""
				<< "Underfull \\hbox (badness 10000) in paragraph at lines 827--831"
				<< "\\T1/cmr/m/n/12 against it (de-pend-ing"
				)
			<< short(LatexOutputFilter::Start)
			<< "c:/test.tex";
	QTest::newRow("unbalanced closing bracket in badbox textqoute")
			<< (QStringList()
				<< "(c:/test.tex"
				<< ""
				<< "Underfull \\hbox (badness 7925) in paragraph at lines 827--831"
				<< "\\T1/cmr/m/n/12 point of view) re-fer-"
				)
			<< short(LatexOutputFilter::Start)
			<< "c:/test.tex";
	QTest::newRow("badbox without text quote")
			<< (QStringList()
				<< "(c:/test.tex"
				<< "Underfull \\hbox (badness 10000) in paragraph at lines 827--831"
				<< "(c:/test2.tex"
				)
			<< short(LatexOutputFilter::Start)
			<< "c:/test2.tex";
	QTest::newRow("TeX open close")
			<< (QStringList()
				<< "(d:/main.tex"
				<< ":<+ file1.tex"
				<< "("
				)
			<< short(LatexOutputFilter::ExpectingFileName)
			<< "file1.tex";
	QTest::newRow("TeX open close")
			<< (QStringList()
				<< "(d:/main.tex"
				<< ":<+ file1.tex"
				<< ":<-"
				<< ""
				)
			<< short(LatexOutputFilter::Start)
			<< "d:/main.tex";
	QTest::newRow("TeX double open")
			<< (QStringList()
				<< ":<+ file1.tex"
				<< "(d:/file1.tex"
				<< ""
				)
			<< short(LatexOutputFilter::Start)
			<< "d:/file1.tex";
	QTest::newRow("TeX double open close")
			<< (QStringList()
				<< "(d:/main.tex"
				<< ":<+ file1.tex"
				<< "(d:/file1.tex"
				<< ")"
				<< ":<-"
				)
			<< short(LatexOutputFilter::Start)
			<< "d:/main.tex";
	QTest::newRow("TeX open close2")
			<< (QStringList()
				<< ":<+ Zusammenfassung.tex"
				<< ":<-"
				<< ":<+ Lebenslauf.tex"
				<< ":<-"
				<< ""
				)
			<< short(LatexOutputFilter::Start)
			<< "";
	QTest::newRow("open followed by bracket 1")
			<< (QStringList() << "(./chapter1.tex(load luc: C:/Users/Tim/AppData/Local/MiKTeX/2.9/luatex-cache/gen"
				)
			<< short(LatexOutputFilter::Start)
			<< "load";
	QTest::newRow("open followed by bracket 2")
			<< (QStringList() << "(./chapter1.tex(load luc: C:/Users/Tim/AppData/Local/MiKTeX/2.9/luatex-cache/gen"
							  << "eric/fonts/otl/lmroman17-regular.luc)"
				)
			<< short(LatexOutputFilter::Start)
			<< "./chapter1.tex";


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
	QTest::newRow("expecting filename")
			<< (QStringList() << "(test.tex some (")
			<< short (LatexOutputFilter::ExpectingFileName)
			<< "test.tex";
	QTest::newRow("empty brackets")
			<< (QStringList() << "(test.tex" << "some ()")
			<< short (LatexOutputFilter::Start)
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
			<< short(LatexOutputFilter::InQuotedFileName)
			<< QString();
	QTest::newRow("quoted continued 2")
			<< (QStringList() << "some text             *** this line has 78 chars ***     (\"/before_the_dot/aux/"
							  << "more.tex "
				)
			<< short(LatexOutputFilter::InQuotedFileName)
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

void LatexOutputFilterTest::isBadBoxTextQuote_data() {
	QTest::addColumn<QString>("line");
	QTest::addColumn<bool>("result");

	QTest::newRow("empty") << "" << false;
	QTest::newRow("text") << "foo" << false;
	QTest::newRow("qoute") << "\\T1/cmr/m/n/12 against it (de-pend-ing" << true;
	QTest::newRow("qoute2") << "[]\\T1/cmr/m/n/10.95 Fehlermeldung: over-full hbox er-stellt mit fol-gen-dem, lan-gen Satz: Es ist ganz schön schwie-" << true;
	QTest::newRow("qoute3") << "[]\\LY1/brm/m/n/10 Windows, \\LY1/brm/m/it/10 see" << true;
}

void LatexOutputFilterTest::isBadBoxTextQuote() {
	QFETCH(QString, line);
	QFETCH(bool, result);

	QEQUAL(LatexOutputFilter::isBadBoxTextQuote(line), result);
}

void LatexOutputFilterTest::detectError_data()
{
	QTest::addColumn<QStringList>("log");
	QTest::addColumn<short>("cookieAtEnd");
	QTest::addColumn<QString>("message");

	QTest::newRow("TeX error line 1")
			<< (QStringList()
				<< "! Undefined control sequence."
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "Undefined control sequence.";
	QTest::newRow("TeX error line 2")
			<< (QStringList()
				<< "! Undefined control sequence."
				<< "l.14 spam \\eggs"
				)
			<< short(LatexOutputFilter::Start)
			<< "";
	QTest::newRow("TeX error multiline 1")
			<< (QStringList()
				<< "! Error with a very long description"  // no dot at end indicating that the message continues.
				)
			<< short(LatexOutputFilter::Error)
			<< "Error with a very long description";
	QTest::newRow("TeX error multiline 2")
			<< (QStringList()
				<< "! Error with a very long description "
				<< "ending in the sceond line."
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "Error with a very long description ending in the sceond line.";
	QTest::newRow("PackageError")
			<< (QStringList()
				<< "! LaTeX Error: File `paralisy.sty' not found."
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "File `paralisy.sty' not found.";

	QTest::newRow("Undefinded control sequence II 1")
			<< (QStringList()
				<< "! Undefined control sequence."
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "Undefined control sequence.";
	QTest::newRow("Undefinded control sequence II 2")
			<< (QStringList()
				<< "! Undefined control sequence."
				<< "<recently read> \\uspackage "
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "Undefined control sequence.";
	QTest::newRow("Undefinded control sequence II 3")
			<< (QStringList()
				<< "! Undefined control sequence."
				<< "<recently read> \\uspackage "
				<< ""
				)
			<< short(LatexOutputFilter::LineNumber)
			<< "Undefined control sequence.";
	QTest::newRow("Undefinded control sequence II 4")
			<< (QStringList()
				<< "! Undefined control sequence."
				<< "<recently read> \\uspackage "
				<< ""
				<< "l.3 \\uspackage"
				)
			<< short(LatexOutputFilter::Start)
			<< "";
	QTest::newRow("Undefinded control sequence II 5")
			<< (QStringList()
				<< "! Undefined control sequence."
				<< "<recently read> \\uspackage "
				<< ""
				<< "l.3 \\uspackage"
				<< "              {paralisi}"
				)
			<< short(LatexOutputFilter::Start)
			<< "";
    QTest::newRow("Undefinded control sequence III")
            << (QStringList()
                << "! Undefined control sequence."
                << "\\qnumber ->\\qfont "
                << "                 \\ifnum 9>5{+~}\fi "
                << "l.5 }"
                )
            << short(LatexOutputFilter::Start)
            << "";
    QTest::newRow("Undefinded control sequence IV")
            << (QStringList()
                <<"! LaTeX Error: Environment verbatimr undefined."
                <<""
                <<"See the LaTeX manual or LaTeX Companion for explanation."
                <<"Type  H <return>  for immediate help."
                <<"...                                              "
                <<""
                <<"l.13 \begin{verbatimr}"
                <<""
                <<"Your command was ignored."
                <<"Type  I <command> <return>  to replace it with another command,"
                <<"or  <return>  to continue without it."
                )
            << short(LatexOutputFilter::Start)
            << "";
    QTest::newRow("Undefinded control sequence V")
            << (QStringList()
                <<"! Package tikz Error: Giving up on this path. Did you forget a semicolon?."
                <<""
                <<"See the tikz package documentation for explanation."
                <<"Type  H <return>  for immediate help."
                <<" ...                                              "
                <<""
                <<"l.6     \\draw"
                <<"                  (0, 0) -- (1, 1);"
                <<"This error message was generated by an \\errmessage"
                <<"command, so I can't give any explicit help."
                <<"Pretend that you're Hercule Poirot: Examine all clues,"
                <<"and deduce the truth by order and method."
                )
            << short(LatexOutputFilter::Start)
            << "";
    QTest::newRow("Undefinded control sequence V")
            << (QStringList()
                <<"! Undefined control sequence."
                <<"\\variable ->\\3"
                <<"              \\frac {d^{2}y}{dt^{2}}+2\\frac {dy}{dt}+y\\left ( t\\right ) = u(t)"
                <<"l.12   \\variable"
                <<""
                <<"The control sequence at the end of the top line"
                <<"of your error message was never \\def'ed. If you have"
                <<"misspelled it (e.g., `\\hobx'), type `I' and the correct"
                <<"spelling (e.g., `I\\hbox'). Otherwise just continue,"
                <<"and I'll forget about whatever was undefined."
                )
            << short(LatexOutputFilter::Start)
            << "";
}

void LatexOutputFilterTest::detectError()
{
	QFETCH(QStringList, log);
	QFETCH(short, cookieAtEnd);
	QFETCH(QString, message);

	LatexOutputFilter filter;
	short sCookie = LatexOutputFilter::Start;
	foreach (const QString &line, log) {
		sCookie = filter.parseLine(line, sCookie);
	}

	QEQUAL(sCookie, cookieAtEnd);
	QEQUAL(currentMessage(filter), message);
}

#endif
