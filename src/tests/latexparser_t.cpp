#ifndef QT_NO_DEBUG
#include "latexparser_t.h"

TestToken LatexParserTest::env(const QString &str)
{
	return TestToken(str, LatexReader::NW_ENVIRONMENT);
}

TestToken LatexParserTest::option(const QString &str)
{
	return TestToken(str, NW_OPTION);
}

void LatexParserTest::addRow(const char *name, LatexParserTest::TokenFilter filter, QList<TestToken> tokens)
{
	QString str;
	int curpos = 0;
	int firstComment = tokens.size();
	for (int i = 0; i < tokens.size(); i++) {
		tokens[i].position = curpos;
		str += tokens[i];
		curpos += tokens[i].size();
		if (tokens[i].type == LatexReader::NW_COMMENT && i < firstComment) firstComment = i;
	}
	//remove all tokens which don't belong to the current test
	switch (filter) {
	case FILTER_NEXTTOKEN:
		for (int i = tokens.size() - 1; i >= 0; i--)
			if (tokens[i].type == NW_IGNORED_TOKEN && tokens[i] != "{" && tokens[i] != "}" && tokens[i] != "[" && tokens[i] != "]")
				tokens.removeAt(i);
		break;
	case FILTER_NEXTWORD_WITH_COMMANDS:
		for (int i = tokens.size() - 1; i >= 0; i--)
			if (tokens[i].type == NW_IGNORED_TOKEN)	tokens.removeAt(i);
			else if (tokens[i].type == LatexReader::NW_ENVIRONMENT || tokens[i].type == NW_OPTION)
				tokens[i].type = LatexReader::NW_TEXT; //nextWord in command mode don't distinguish between text, environments and options
			else if (tokens[i].type == NW_OPTION_PUNCTATION)
				tokens[i].type = LatexReader::NW_PUNCTATION;
		//else if (tokens[i].contains("\\") && tokens[i].type==NW_TEXT)
		//tokens[i].replace("\\%","%"); //unescape escaped characters
		break;
	case FILTER_NEXTWORD:
		for (int i = tokens.size() - 1; i >= 0; i--)
			if (tokens[i].type == LatexReader::NW_COMMAND || tokens[i].type == NW_OPTION || tokens[i].type == NW_OPTION_PUNCTATION || tokens[i].type == NW_IGNORED_TOKEN)
				tokens.removeAt(i);//remove tokens not returned by nextWord in text mode
		//else if (tokens[i].contains("\\") && tokens[i].type==LatexReader::NW_TEXT)
		//tokens[i].replace("\\",""); //unescape escaped characters
		break;
	case FILTER_NEXTTEXTWORD:
		for (int i = tokens.size() - 1; i >= 0; i--)
			if (tokens[i].type != LatexReader::NW_TEXT || i >= firstComment)
				tokens.removeAt(i);//remove all except text before comment start
		//else if (tokens[i].contains("\\") && tokens[i].type==LatexReader::NW_TEXT)
		//tokens[i].replace("\\",""); //unescape escaped characters
		break;
	default:
		QVERIFY2(false, "Invalid filter");
	}
	QTest::newRow(name) << str << tokens;
}

void LatexParserTest::addComplexData(LatexParserTest::TokenFilter filter)
{
	QTest::addColumn<QString >("str");
	QTest::addColumn<QList<TestToken> >("tokens");

	/*addRow("simple whitespace", filter,
	        QList<TestToken>() << "abcde" << "    " << "fghik" << "\t" << "Mice");
	    addRow("simple eow", filter,
	           QList<TestToken>() << "abcde" << ";" << ":" << ";" << "fghik" << TestToken("##", NW_IGNORED_TOKEN) << "Mice" << TestToken("///", NW_IGNORED_TOKEN) << "\\\\" << TestToken("+++", NW_IGNORED_TOKEN) );//<< "axy" << TestToken("---", "-", LatexReader::NW_PUNCTATION)); "-" is now added to the word ...
	    addRow("simple eow", filter,
	           QList<TestToken>() << "abcde." << ";" << ":" << ";" << "fghik" << TestToken("##", NW_IGNORED_TOKEN) << "Mice" << TestToken("///", NW_IGNORED_TOKEN) << "\\\\" << TestToken("+++", NW_IGNORED_TOKEN) );//<< "axy" << TestToken("---", "-", LatexReader::NW_PUNCTATION));
	    addRow("environment+comment",filter,
	        QList<TestToken>() << "Test1234" << "\\begin" << "{" << env("environment") << "}" << "{" << "add" << "}" << "XYZ" << "!" << "!" << "!" << "\\command" << "%"     << "comment" << "\\COMMENT");
	    addRow("some environments", filter,
	        QList<TestToken>() << "\\newenvironment" << "{" << env("env") << "}" << " " << "\\begin" << "{" << env("env2") << "}" << " " << "\\end" << "{" << env("env3") << "}" << "  " << "\\renewenvironment" << "{" << env("env4") << "}");
	    addRow("misc", filter, //was only for nextWord, other test will of course not ignore \\ignoreMe
	        QList<TestToken>() << "hallo" << " " << "welt" << "\\section" << "{" << "text" << "}" << "     " << "\\begin" << "{" << env("I'mXnotXthere") << "}" << " *" << "g"  << "* " << "%"     << " " << "more" << " " << "\\comment");
	    addRow("command as option", filter,
	        QList<TestToken>() << "\\includegraphics" << "[" << option("ab.") << "\\linewidth" << "]" << "{" << "\\abc" << " " << option("dfdf") << "\\xyz" << "}" << "continue");
	    addRow("command as option", filter,
	           QList<TestToken>() << "\\includegraphics" << "[" << option("ab") << TestToken(":", NW_OPTION_PUNCTATION) << "\\linewidth" << "]" << "{" << "\\abc" << " " << option("dfdf") << "\\xyz" << "}" << "continue");
	    addRow("comments", filter, QList<TestToken>() << "hallo" << " " << "welt" <<  "  " << "\\\\" << "normaltext" <<  "  " << TestToken("\\%",NW_IGNORED_TOKEN) << "!" << "!" << "!" << "stillNoComment" << "\\\\" << TestToken("\\%","%",NW_IGNORED_TOKEN) <<"  "<< "none" << "\\\\" << "%" << "comment" << "   " << "more" << " " << "comment");
	    addRow("escaped characters", filter, QList<TestToken>() << "hallo" << TestToken("\\%",NW_IGNORED_TOKEN) << "abc");
	    addRow("escaped characters", filter, QList<TestToken>() << "1234" << TestToken("\\%\\&\\_",NW_IGNORED_TOKEN)  << "567890");  */
	addRow("special characters", filter,
	       QList<TestToken>() << "lösbar" << " " << TestToken("l\"osbar", QString::fromUtf8("lösbar"), LatexReader::NW_TEXT) << " " << TestToken("l\\\"osbar", QString::fromUtf8("lösbar"), LatexReader::NW_TEXT) << " " << TestToken("l\\\"{o}sbar", QString::fromUtf8("lösbar"), LatexReader::NW_TEXT) << " " << "örtlich" << " " << TestToken("\"ortlich", QString::fromUtf8("örtlich"), LatexReader::NW_TEXT) << " " << TestToken("\\\"ortlich", QString::fromUtf8("örtlich"), LatexReader::NW_TEXT) << " " << TestToken("\\\"{o}rtlich", QString::fromUtf8("örtlich"), LatexReader::NW_TEXT) );
}

void LatexParserTest::nextWord_complex_test(bool commands)
{
	//get data
	QFETCH(QString, str);
	QFETCH(QList<TestToken>, tokens);
	int pos = 0;
	int type;
	QMap<QString, QString> replacementList;
	replacementList.insert("\"o", QString::fromUtf8("ö"));
	replacementList.insert("\"a", QString::fromUtf8("ä"));
	replacementList.insert("\"-", "");
	replacementList.insert("\"|", "");
	replacementList.insert("\"\"", "");
	LatexParser &lp = LatexParser::getInstance();
	LatexReader lr(lp, str, replacementList);
	while ((type = lr.nextWord(commands)) != LatexReader::NW_NOTHING) {
		const int &startIndex = lr.wordStartIndex;
		const QString &token = lr.word;
		if (pos >= tokens.size()) {
			QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
		} else {
			QVERIFY2(tokens[pos] == token, QString("Invalid token: \"%1\" at \"%2\" expected \"%3\"").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
			QVERIFY2(startIndex == tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
			QVERIFY2(type == tokens[pos].type, QString("Invalid type: %2 for %1").arg(token).arg(type).toLatin1().constData());
		}
		pos++;
	}
	QVERIFY2 (pos == tokens.size(), QString("Didn't find all tokens, missing: %1").arg(tokens[qMin(pos, tokens.size() - 1)]).toLatin1().constData());
}

void LatexParserTest::nextToken_complex_data()
{
	addComplexData(FILTER_NEXTTOKEN);
}

void LatexParserTest::nextToken_complex()
{
	//get data
	QFETCH(QString, str);
	QFETCH(QList<TestToken>, tokens);

	//check
	int index = 0;
	int startIndex = 0;
	int pos = 0;
	while ((startIndex = LatexReader::nextToken(str, index, false, false)) != -1) {
		QString token = str.mid(startIndex, index - startIndex);
		if (pos >= tokens.size()) {
			QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
		} else {
			QVERIFY2(token == tokens[pos], QString("Invalid token: %1 at %2 expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
			QVERIFY2(startIndex == tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
		}
		pos++;
	}
	QVERIFY2 (pos == tokens.size(), "Didn't found all tokens");
}

void LatexParserTest::nextWordWithCommands_complex_data()
{
	addComplexData(FILTER_NEXTWORD_WITH_COMMANDS);
}

void LatexParserTest::nextWordWithCommands_complex()
{
	nextWord_complex_test(true);
}

void LatexParserTest::nextWord_complex_data()
{
	addComplexData(FILTER_NEXTWORD);
}

void LatexParserTest::nextWord_complex()
{
	nextWord_complex_test(false);
}

void LatexParserTest::nextTextWord_complex_data()
{
	addComplexData(FILTER_NEXTTEXTWORD);
}

void LatexParserTest::nextTextWord_complex()
{
	//get data
	QFETCH(QString, str);
	QFETCH(QList<TestToken>, tokens);

	int pos = 0;
	QMap<QString, QString> replacementList;
	replacementList.insert("\"o", QString::fromUtf8("ö"));
	replacementList.insert("\"a", QString::fromUtf8("ä"));
	replacementList.insert("\"-", "");
	replacementList.insert("\"|", "");
	replacementList.insert("\"\"", "");
	LatexParser &lp = LatexParser::getInstance();
	LatexReader lr(lp, str, replacementList);
	while (lr.nextTextWord()) {
		const int &startIndex = lr.wordStartIndex;
		const QString &token = lr.word;
		if (pos >= tokens.size()) QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
		else {
			QVERIFY2(tokens[pos] == token, QString("Invalid token: %1 at %2, expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
			QVERIFY2(startIndex == tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
		}
		pos++;
	}

	if (pos < tokens.size())
		QVERIFY2 (pos == tokens.size(), QString("Didn't find all tokens, missing: %1").arg(tokens[qMin(pos, tokens.size() - 1)]).toLatin1().constData());
}

void LatexParserTest::nextWord_simple_data()
{
	QTest::addColumn<QString >("line");
	QTest::addColumn<int>("inIndex");
	QTest::addColumn<bool>("commands");
	QTest::addColumn<bool>("abbreviations");

	QTest::addColumn<int>("result");
	QTest::addColumn<int>("outIndex");
	QTest::addColumn<QString>("outWord");
	QTest::addColumn<int>("wordStartIndex");

	QTest::newRow("reference") << "bummerang\\ref{  xyz  }abcdef" << 9 << false << false
	                           << (int)LatexReader::NW_REFERENCE << 21 << "  xyz  " << 14;
	QTest::newRow("unknown")   << "bummerang\\adxas{  x:y:z  }abcdef" << 9 << false << false
	                           << (int)LatexReader::NW_TEXT << 32 << "abcdef" << 26;
	QTest::newRow("label")     << "bummerang\\label{  x:y:z  }abcdef" << 9 << false << false
	                           << (int)LatexReader::NW_LABEL << 25 << "  x:y:z  " << 16;
	QTest::newRow("citation0") << "012345\\cite{aaaHallob}abcdef" << 6 << false << false
	                           << (int)LatexReader::NW_CITATION << 21 << "aaaHallob" << 12;
	QTest::newRow("citation1") << "012345\\cite{   Hallo   }abcdef" << 6 << false << false
	                           << (int)LatexReader::NW_CITATION << 23 << "   Hallo   " << 12;
	QTest::newRow("citation2") << "012345\\cite{ Hallo:Welt! }abcdef" << 6  << false << false
	                           << (int)LatexReader::NW_CITATION << 25 << " Hallo:Welt! " << 12;
	QTest::newRow("citation3") << "012345\\cite[aasasadaa]{Hallo:Welt!,miau!}abcdef" << 6 << false << false
	                           << (int)LatexReader::NW_CITATION << 40 << "Hallo:Welt!,miau!" << 23;
	//QTest::newRow("no abbre.") << "+++TEST.---" << 0 << false << false << (int)LatexReader::NW_TEXT << 7 << "TEST" << 3;
	QTest::newRow("abbrev.")   << "+++TEST.---" << 0 << false << true
	                           << (int)LatexReader::NW_TEXT << 8 << "TEST." << 3;
	QTest::newRow("in cmd.")   << "\\section{text}" << 0 << false << false
	                           << (int)LatexReader::NW_TEXT << 13 << "text" << 9;
	QTest::newRow("' chars")   << " can't " << 0 << false << false
	                           << (int)LatexReader::NW_TEXT << 6 << "can't" << 1;
	QTest::newRow("' char2")   << " 'abc def' " << 0 << false << false
	                           << (int)LatexReader::NW_TEXT << 5 << "abc" << 2;
	QTest::newRow("' char3")   << " 'abc def' " << 5 << false << false << (int)LatexReader::NW_TEXT << 9 << "def" << 6;
	QTest::newRow("sepchars")  << " ha\\-llo " << 0 << false << false << (int)LatexReader::NW_TEXT << 8 << "hallo" << 1;
	QTest::newRow("sepchar2")  << " la\"-tex " << 0 << false << false << (int)LatexReader::NW_TEXT << 8 << "latex" << 1;
	QTest::newRow("sepchar3a")  << "!ab\"\"xyz!" << 0 << false << false << (int)LatexReader::NW_PUNCTATION << 1 << "!" << 0;
	QTest::newRow("sepchar3b")  << "!ab\"\"xyz!" << 1 << false << false << (int)LatexReader::NW_TEXT << 8 << "abxyz" << 1;
	QTest::newRow("sepchar4a")  << "?oz\"|di?" << 0 << false << false << (int)LatexReader::NW_PUNCTATION << 1 << "?" << 0;
	QTest::newRow("sepchar4b")  << "?oz\"|di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 7 << "ozdi" << 1;
	QTest::newRow("sepchar5")  << "?oz\"adi?" << 1 << false << false << (int)LatexReader::NW_TEXT << 7 << QString("oz%1di").arg(QChar(0xE4)) << 1;
	QTest::newRow("sepchar6")  << "?oz\\\"{a}di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 10 << QString("oz%1di").arg(QChar(0xE4)) << 1;
	QTest::newRow("sepchar7")  << "?oz\\\"adi?" << 1 << false << false << (int)LatexReader::NW_TEXT << 8 << QString("oz%1di").arg(QChar(0xE4)) << 1;
	QTest::newRow("sepchar8")  << "?oz\"\"adi?" << 1 << false << false << (int)LatexReader::NW_TEXT << 8 << "ozadi" << 1;
	//QTest::newRow("sepchar8")  << "?oz\"yxdi?" << 1 << false << false << (int)LatexReader::NW_TEXT << 8 << "ozyxdi" << 1;  //invalid combinations in german.sty
	//QTest::newRow("sepchar8")  << "?oz\"y?" << 1 << false << false << (int)LatexReader::NW_TEXT << 5 << "ozy" << 1; //invalid combinations in german.sty
	QTest::newRow("word end")  << "?no\"<di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 3 << "no" << 1;
	QTest::newRow("word end")  << "?yi''di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 3 << "yi" << 1;
	QTest::newRow("umlauts")  << "\"a\"o\"u\"A\"O\"U\\\"{a}\\\"{o}\\\"{u}\\\"{A}\\\"{O}\\\"{U}" << 0 << false << false << (int)LatexReader::NW_TEXT << 42 << (QString(QChar(0xE4)) + QString(QChar(0xF6)) + QString(QChar(0xFC)) + QString(QChar(0xC4)) + QString(QChar(0xD6)) + QString(QChar(0xDC)) + QString(QChar(0xE4)) + QString(QChar(0xF6)) + QString(QChar(0xFC)) + QString(QChar(0xC4)) + QString(QChar(0xD6)) + QString(QChar(0xDC))) << 0; //unicode to be independent from c++ character encoding
}

void LatexParserTest::nextWord_simple()
{
	QFETCH(QString, line);
	QFETCH(int, inIndex);
	QFETCH(bool, commands);

	QFETCH(int, result);
	QFETCH(int, outIndex);
	QFETCH(QString, outWord);
	QFETCH(int, wordStartIndex);

	//LatexReader lr(line);
	QMap<QString, QString> replacementList;
	replacementList.insert("\"o", QString::fromUtf8("ö"));
	replacementList.insert("\"a", QString::fromUtf8("ä"));
	replacementList.insert("\"u", QString::fromUtf8("ü"));
	replacementList.insert("\"A", QString::fromUtf8("Ä"));
	replacementList.insert("\"O", QString::fromUtf8("Ö"));
	replacementList.insert("\"U", QString::fromUtf8("Ü"));
	replacementList.insert("\"-", "");
	replacementList.insert("\"|", "");
	replacementList.insert("\"\"", "");
	LatexParser &lp = LatexParser::getInstance();
	LatexReader lr(lp, line, replacementList);
	lr.index = inIndex;
	int rs = (int)(lr.nextWord(commands));

	QEQUAL(lr.word, outWord);
	QEQUAL(rs, result);
	QEQUAL(lr.index, outIndex);
	QEQUAL(lr.wordStartIndex, wordStartIndex);
}

void LatexParserTest::cutComment_simple_data()
{
	QTest::addColumn<QString >("in");
	QTest::addColumn<QString >("out");

	QTest::newRow("comment") << "ab%cd" << "ab";
	QTest::newRow("nocomment") << "ab\\%cd" << "ab\\%cd";
	QTest::newRow("comment and newline") << "ab\\\\%cd" << "ab\\\\";
	QTest::newRow("nocomment and newline") << "ab\\\\\\%cd" << "ab\\\\\\%cd";
	QTest::newRow("comment at start of line") << "%abcd" << "";
	QTest::newRow("comment at start+1 of line") << "a%abcd" << "a";

}

void LatexParserTest::cutComment_simple()
{
	QFETCH(QString, in);
	QFETCH(QString, out);
	QString res = LatexParser::cutComment(in);
	QEQUAL(res, out);
}

void LatexParserTest::test_resolveCommandOptions_data()
{
	QTest::addColumn<QString>("line");
	QTest::addColumn<int>("column");
	QTest::addColumn<QStringList>("expectedValues");
	QTest::addColumn<QList<int> >("expectedStarts");
	QTest::addColumn<bool>("expectedComplete");

	QTest::newRow("noOption") << "\\begin nothing" << 0 << (QStringList()) << (QList<int>()) << true;
	QTest::newRow("singleOption") << "\\begin{test}" << 0 << (QStringList() << "{test}") << (QList<int>() << 6) << true;
	QTest::newRow("singleOptionSpace") << "\\begin {test}" << 0 << (QStringList() << "{test}") << (QList<int>() << 7) << true;
	QTest::newRow("multiOption") << "\\begin{test 1}{test 2}" << 0 << (QStringList() << "{test 1}" << "{test 2}") << (QList<int>() << 6 << 14) << true;
	QTest::newRow("multiOption2") << "\\begin[test 1]{test 2}" << 0 << (QStringList() << "[test 1]" << "{test 2}") << (QList<int>() << 6 << 14) << true;
	QTest::newRow("multiOption3") << "\\begin{test 1}[test 2]{test 3}" << 0 << (QStringList() << "{test 1}" << "[test 2]" << "{test 3}") << (QList<int>() << 6 << 14 << 22) << true;
	QTest::newRow("cmdStart") << "\\section{\\LaTeX rules}" << 0 << (QStringList() << "{\\LaTeX rules}") << (QList<int>() << 8) << true;
	QTest::newRow("cmdMid") << "\\section{a \\textit{nested} command}" << 0 << (QStringList() << "{a \\textit{nested} command}") << (QList<int>() << 8) << true;
	QTest::newRow("incomplete") << "\\section{text" << 0 << (QStringList()) << (QList<int>()) << false;
	QTest::newRow("incomplete2") << "\\section{text}{more" << 0 << (QStringList() << "{text}") << (QList<int>() << 8) << false;
}

void LatexParserTest::test_resolveCommandOptions()
{
	QFETCH(QString, line);
	QFETCH(int, column);
	QFETCH(QStringList, expectedValues);
	QFETCH(QList<int>, expectedStarts);
	QFETCH(bool, expectedComplete);
	QStringList values;
	QList<int> starts;
	bool complete = LatexParser::resolveCommandOptions(line, column, values, &starts);
	QEQUAL(values.length(), starts.length());
	QEQUAL(values.join("|"), expectedValues.join("|"));
	QVERIFY(starts == expectedStarts);
	QEQUAL(complete, expectedComplete);
}

void LatexParserTest::test_findClosingBracket_data()
{
	QTest::addColumn<QString>("line");
	QTest::addColumn<int>("start");
	QTest::addColumn<QChar>("oc");
	QTest::addColumn<QChar>("cc");
	QTest::addColumn<int>("out");

	QTest::newRow("simple bracket") << "{ simple} text" << 0 << QChar('{') << QChar('}') << 8;
	QTest::newRow("simple bracket2") << "  simple} text" << 0 << QChar('{') << QChar('}') << 8;
	QTest::newRow("nested bracket") << "{a {nested} simple} text" << 0 << QChar('{') << QChar('}') << 18;
	QTest::newRow("nested bracket2") << "{a {nested} simple} text" << 3 << QChar('{') << QChar('}') << 10;
	QTest::newRow("nested bracket3") << "{a {nested} simple} text" << 16 << QChar('{') << QChar('}') << 18;
	QTest::newRow("nested bracket3") << "{a {nested} simple} text" << 19 << QChar('{') << QChar('}') << -1;
	QTest::newRow("no bracket") << "No bracket in here" << 0 << QChar('{') << QChar('}') << -1;
	QTest::newRow("no bracket2") << "No {proper} bracket in here" << 0 << QChar('{') << QChar('}') << -1;
}

void LatexParserTest::test_findClosingBracket()
{
	QFETCH(QString, line);
	QFETCH(int, start);
	QFETCH(QChar, oc);
	QFETCH(QChar, cc);
	QFETCH(int, out);
	int ret = findClosingBracket(line, start, oc, cc);
    QEQUAL(ret, out);
}

void LatexParserTest::test_interpretXArgs_data()
{
    QTest::addColumn<QString>("argument");
    QTest::addColumn<QString>("result");

    QTest::newRow("simple arguments") << "moO" << "{%<arg%>}[%<arg%>][%<arg%>]";
    QTest::newRow("spaces") << " m o  O " << "{%<arg%>}[%<arg%>][%<arg%>]";
    QTest::newRow("defined brackets") << "r()R&%d)(D][" << "(%<arg%>)&%<arg%>%)%<arg%>(]%<arg%>[";
    QTest::newRow("braces") << "m{oO}" << "{%<arg%>}";
    QTest::newRow("ignored characters") << "mstb+uo" << "{%<arg%>}[%<arg%>]";
}

void LatexParserTest::test_interpretXArgs()
{
    QFETCH(QString, argument);
    QFETCH(QString, result);
    QString out=interpretXArgs(argument);
    QEQUAL(out,result);
}

#endif // QT_NO_DEBUG
