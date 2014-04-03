#ifndef SMALLUSEFULFUNCTIONS_T_H
#define SMALLUSEFULFUNCTIONS_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "testutil.h"
#include <QtTest/QtTest>

const int NW_IGNORED_TOKEN=-2; //token that are not words,  { and }
const int NW_OPTION=-3; //option text like in \include
const int NW_OPTION_PUNCTATION=-4; //option punctation like in \include

class TestToken: public QString{
	static const QRegExp simpleTextRegExp; //defined in testmanager.cpp
	static const QRegExp commandRegExp;
	static const QRegExp ignoredTextRegExp;
	static const QRegExp specialCharTextRegExp;
	static const QRegExp punctationRegExp;
	void guessType(){
		if (simpleTextRegExp.exactMatch(*this)) type=LatexReader::NW_TEXT;
		else if (commandRegExp.exactMatch(*this)) type=LatexReader::NW_COMMAND;
		else if (punctationRegExp.exactMatch(*this)) type=LatexReader::NW_PUNCTATION;
		else if (ignoredTextRegExp.exactMatch(*this)) type=NW_IGNORED_TOKEN;
		else if (*this=="%") type=LatexReader::NW_COMMENT;
		else if (specialCharTextRegExp.exactMatch(*this)) type=LatexReader::NW_TEXT;
		else QVERIFY2(false, QString("invalid test data: \"%1\"").arg(*this).toLatin1().constData());
	}
public:
	int type,position;
	TestToken():QString(), type(NW_IGNORED_TOKEN),soll(QString()){ }
	TestToken(const TestToken& token):QString(token), type(token.type), position(token.position), soll(token.soll) { }
	TestToken(const QString& str):QString(str),soll(str) {
		guessType();
	}
	TestToken(const char* cstr):QString(cstr), soll(QString(cstr)){
		guessType();
	}
	TestToken(const QString& str, int atype):QString(str),type(atype),soll(str){}
	TestToken(const QString& str, const QString result, int atype):QString(str),type(atype),soll(result){}
	bool operator ==(const QString &other) {
        return soll.compare(other)==0;
	}
private:
	QString soll;
};

Q_DECLARE_METATYPE(TestToken);
Q_DECLARE_METATYPE(QList<TestToken>);
Q_DECLARE_METATYPE(QList<int>);

/*QList<TestToken>& operator<< (QList<TestToken> & list, const char* str){
	return list << TestToken(str);
}*/

class SmallUsefulFunctionsTest: public QObject{
	Q_OBJECT
	TestToken env(const QString& str){
		return TestToken(str, LatexReader::NW_ENVIRONMENT);
	}
	TestToken option(const QString& str){
		return TestToken(str, NW_OPTION);
	}
	enum TokenFilter {FILTER_NEXTTOKEN,FILTER_NEXTWORD_WITH_COMMANDS,FILTER_NEXTWORD,FILTER_NEXTTEXTWORD};
	void addRow(const char* name, TokenFilter filter, QList<TestToken> tokens){
		QString str;
		int curpos=0;
		int firstComment=tokens.size();
		for (int i=0;i<tokens.size();i++){
			tokens[i].position=curpos;
			str+=tokens[i];
			curpos+=tokens[i].size();
			if (tokens[i].type==LatexReader::NW_COMMENT && i<firstComment) firstComment=i;
		}
		//remove all tokens which don't belong to the current test
		switch (filter){
			case FILTER_NEXTTOKEN:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN && tokens[i]!="{" && tokens[i]!="}" && tokens[i]!="[" && tokens[i]!="]")
						tokens.removeAt(i);
				break;
			case FILTER_NEXTWORD_WITH_COMMANDS:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN)	tokens.removeAt(i);
					else if (tokens[i].type==LatexReader::NW_ENVIRONMENT || tokens[i].type==NW_OPTION)
						tokens[i].type=LatexReader::NW_TEXT;//nextWord in command mode don't distinguish between text, environments and options
					else if (tokens[i].type==NW_OPTION_PUNCTATION)
						tokens[i].type=LatexReader::NW_PUNCTATION;
					//else if (tokens[i].contains("\\") && tokens[i].type==NW_TEXT)
						//tokens[i].replace("\\%","%"); //unescape escaped characters
				break;
			case FILTER_NEXTWORD:
				for (int i=tokens.size()-1;i>=0;i--) 
					if (tokens[i].type==LatexReader::NW_COMMAND || tokens[i].type==NW_OPTION || tokens[i].type==NW_OPTION_PUNCTATION || tokens[i].type==NW_IGNORED_TOKEN) 
						tokens.removeAt(i);//remove tokens not returned by nextWord in text mode
					//else if (tokens[i].contains("\\") && tokens[i].type==LatexReader::NW_TEXT)
						//tokens[i].replace("\\",""); //unescape escaped characters
				break;
			case FILTER_NEXTTEXTWORD:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type!=LatexReader::NW_TEXT || i>=firstComment)  
						tokens.removeAt(i);//remove all except text before comment start
					//else if (tokens[i].contains("\\") && tokens[i].type==LatexReader::NW_TEXT)
						//tokens[i].replace("\\",""); //unescape escaped characters
				break;
			default:
				QVERIFY2(false, "Invalid filter");
		}
		QTest::newRow(name) << str << tokens;
	}
	void addComplexData(TokenFilter filter){
		QTest::addColumn<QString >("str");
		QTest::addColumn<QList<TestToken> >("tokens");

		addRow("simple whitespace", filter,
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
		addRow("escaped characters", filter, QList<TestToken>() << "1234" << TestToken("\\%\\&\\_",NW_IGNORED_TOKEN)  << "567890");
		addRow("special characters", filter,
               QList<TestToken>() << QString::fromUtf8("lösbar") << " " << TestToken("l\"osbar",QString::fromUtf8("lösbar"),LatexReader::NW_TEXT) << " " << TestToken("l\\\"osbar",QString::fromUtf8("lösbar"),LatexReader::NW_TEXT) << " " << TestToken("l\\\"{o}sbar",QString::fromUtf8("lösbar"),LatexReader::NW_TEXT) << " " << QString::fromUtf8("örtlich") <<" " <<TestToken("\"ortlich",QString::fromUtf8("örtlich"),LatexReader::NW_TEXT)<<" " <<TestToken("\\\"ortlich",QString::fromUtf8("örtlich"),LatexReader::NW_TEXT)<<" " <<TestToken("\\\"{o}rtlich",QString::fromUtf8("örtlich"),LatexReader::NW_TEXT) );
	}
	void nextWord_complex_test(bool commands){
		//get data
		QFETCH(QString, str);	
		QFETCH(QList<TestToken>, tokens);	
		int pos=0; int type;
		LatexReader lr(str);
		while ((type=lr.nextWord(commands))!=LatexReader::NW_NOTHING) {
			const int& startIndex = lr.wordStartIndex;
			const QString& token = lr.word;
			if (pos>=tokens.size()) {
				QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			} else {
				QVERIFY2(tokens[pos]==token, QString("Invalid token: \"%1\" at \"%2\" expected \"%3\"").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
				QVERIFY2(type==tokens[pos].type, QString("Invalid type: %2 for %1").arg(token).arg(type).toLatin1().constData());
			}
			pos++;
		}
		QVERIFY2 (pos==tokens.size(), QString("Didn't find all tokens, missing: %1").arg(tokens[qMin(pos, tokens.size()-1)]).toLatin1().constData());
	}
private slots:
	void nextToken_complex_data(){ addComplexData(FILTER_NEXTTOKEN); }
	void nextToken_complex(){
		//get data
		QFETCH(QString, str);	
		QFETCH(QList<TestToken>, tokens);	
		
		//check
		int index=0;int startIndex=0;
		int pos=0;
		while ((startIndex = LatexReader::nextToken(str,index,false,false)) != -1) {
			QString token=str.mid(startIndex,index-startIndex);
			if (pos>=tokens.size()) {
				QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			} else {
				QVERIFY2(token==tokens[pos], QString("Invalid token: %1 at %2 expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
			}
			pos++;
		}
		QVERIFY2 (pos==tokens.size(), "Didn't found all tokens");
	}
	void nextWordWithCommands_complex_data(){ addComplexData(FILTER_NEXTWORD_WITH_COMMANDS); }
	void nextWordWithCommands_complex(){ 
		nextWord_complex_test(true);
	}
	void nextWord_complex_data(){ addComplexData(FILTER_NEXTWORD); }
	void nextWord_complex(){ 
		nextWord_complex_test(false);
	}
	void nextTextWord_complex_data(){ addComplexData(FILTER_NEXTTEXTWORD); }
	void nextTextWord_complex(){ 
		//get data
		QFETCH(QString, str);	
		QFETCH(QList<TestToken>, tokens);	
		
		int pos=0;
		LatexReader lr(str);
		while (lr.nextTextWord()) {
			const int& startIndex = lr.wordStartIndex;
			const QString& token = lr.word;
			if (pos>=tokens.size()) QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			else {
				QVERIFY2(tokens[pos]==token, QString("Invalid token: %1 at %2, expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
			}
			pos++;
		}
		
		if (pos < tokens.size())
			QVERIFY2 (pos==tokens.size(), QString("Didn't find all tokens, missing: %1").arg(tokens[qMin(pos, tokens.size()-1)]).toLatin1().constData());
	}
	
	
	void nextWord_simple_data(){
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
		QTest::newRow("citation2") << "012345\\cite{ Hallo:Welt! }abcdef" <<6  << false << false
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
		QTest::newRow("sepchar8")  << "?oz\"yxdi?" << 1 << false << false << (int)LatexReader::NW_TEXT << 8 << "ozyxdi" << 1;
		QTest::newRow("sepchar8")  << "?oz\"y?" << 1 << false << false << (int)LatexReader::NW_TEXT << 5 << "ozy" << 1;
		QTest::newRow("word end")  << "?no\"<di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 3 << "no" << 1;
		QTest::newRow("word end")  << "?yi''di?" << 1 << false << false << (int)LatexReader::NW_TEXT << 3 << "yi" << 1;
		QTest::newRow("umlauts")  << "\"a\"o\"u\"A\"O\"U\\\"{a}\\\"{o}\\\"{u}\\\"{A}\\\"{O}\\\"{U}" << 0 << false << false << (int)LatexReader::NW_TEXT << 42 << (QString(QChar(0xE4))+QString(QChar(0xF6))+QString(QChar(0xFC))+QString(QChar(0xC4))+QString(QChar(0xD6))+QString(QChar(0xDC))+QString(QChar(0xE4))+QString(QChar(0xF6))+QString(QChar(0xFC))+QString(QChar(0xC4))+QString(QChar(0xD6))+QString(QChar(0xDC))) << 0; //unicode to be independent from c++ character encoding
	}
	void nextWord_simple(){
		QFETCH(QString, line);
		QFETCH(int, inIndex);
		QFETCH(bool, commands);

		QFETCH(int, result);
		QFETCH(int, outIndex);
		QFETCH(QString, outWord);
		QFETCH(int, wordStartIndex);
		
		LatexReader lr(line);
		lr.index = inIndex;
		int rs=(int)(lr.nextWord(commands));

		QEQUAL(lr.word,outWord);
		QEQUAL(rs, result);
		QEQUAL(lr.index,outIndex);
		QEQUAL(lr.wordStartIndex,wordStartIndex);
	}
	void cutComment_simple_data(){
		QTest::addColumn<QString >("in");
		QTest::addColumn<QString >("out");

		QTest::newRow("comment") << "ab%cd" << "ab";
		QTest::newRow("nocomment") << "ab\\%cd" << "ab\\%cd";
		QTest::newRow("comment and newline") << "ab\\\\%cd" << "ab\\\\";
		QTest::newRow("nocomment and newline") << "ab\\\\\\%cd" << "ab\\\\\\%cd";
		QTest::newRow("comment at start of line") << "%abcd" << "";
		QTest::newRow("comment at start+1 of line") << "a%abcd" << "a";

	}
	void cutComment_simple(){
		QFETCH(QString, in);
		QFETCH(QString, out);
		QString res=LatexParser::cutComment(in);
		QEQUAL(res,out);
	}
	void test_findContext_data(){
		QTest::addColumn<QString >("in");
		QTest::addColumn<int>("pos");
		QTest::addColumn<int>("out");

		QTest::newRow("command") << "\\begin{test}" << 3 << 1;
		QTest::newRow("content") << "\\begin{test}" << 8 << 2;
                QTest::newRow("option") << "\\begin[abc]{test}" << 8 << 3;
		QTest::newRow("content with option") << "\\begin[abc]{test}" << 13 << 2;
                QTest::newRow("content with option2") << "\\begin[\\abc]{test}" << 14 << 2;
		QTest::newRow("command with option") << "\\begin[abc]{test}" << 3 << 1;
		QTest::newRow("nothing") << "\\begin{test}" << 0 << 0;
	}
	void test_findContext(){
		QFETCH(QString, in);
		QFETCH(int, pos);
		QFETCH(int, out);
		int res=LatexParser::getInstance().findContext(in,pos);
		QEQUAL(res,out);
	}
	void test_findContext2_data(){
		QTest::addColumn<QString >("in");
		QTest::addColumn<int>("pos");
		QTest::addColumn<int>("out");
		QTest::addColumn<QString>("command");
		QTest::addColumn<QString>("value");

		QTest::newRow("command") << "\\begin{test}" << 3 << (int)LatexParser::Command << "\\begin" <<"test";
		QTest::newRow("content") << "\\begin{test}" << 8 << (int)LatexParser::Environment << "\\begin" <<"test";
		QTest::newRow("ref") << "\\ref{test}" << 8 << (int)LatexParser::Reference << "\\ref" <<"test";
		QTest::newRow("label") << "\\label{test}" << 8 << (int)LatexParser::Label << "\\label" <<"test";
		QTest::newRow("cite") << "\\cite{test}" << 8 << (int)LatexParser::Citation << "\\cite" <<"test";
		QTest::newRow("cite") << "\\cite{test}" << 3 << (int)LatexParser::Command << "\\cite" <<"test";
                QTest::newRow("abcd option") << "\\abcd{test}" << 7 << (int)LatexParser::Option << "\\abcd" <<"test";
                QTest::newRow("abcd option2") << "\\abcd[abc]{test}" << 12 << (int)LatexParser::Option << "\\abcd" <<"test";
                QTest::newRow("abcd option3") << "\\abcd[\\abc]{test}" << 12 << (int)LatexParser::Option << "\\abcd" <<"test";
	}
	void test_findContext2(){
		QFETCH(QString, in);
		QFETCH(int, pos);
		QFETCH(int, out);
		QFETCH(QString, command);
		QFETCH(QString, value);
		QString cmd;
		QString val;
		LatexParser::ContextType res=LatexParser::getInstance().findContext(in,pos,cmd,val);
		QEQUAL((int)res,out);
		QEQUAL(cmd,command);
		QEQUAL(val,value);
	}
	void test_lineStart_data(){
		QTest::addColumn<QString>("text");
		QTest::addColumn<int>("pos");
		QTest::addColumn<int>("start");

		QTest::newRow("empty") << "" << 0 << 0;
		QTest::newRow("start") << "foo bar" << 0 << 0;
		QTest::newRow("text") << "foo bar" << 6 << 0;
		QTest::newRow("newline") << "foo\nbar" << 6 << 4;
		QTest::newRow("cr") << "foo\rbar" << 6 << 4;
		QTest::newRow("cr_newline") << "foo\r\nbar" << 6 << 5;
		QTest::newRow("start_newline") << "foo\nbar" << 4 << 4;
	}
	void test_lineStart(){
		QFETCH(QString, text);
		QFETCH(int, pos);
		QFETCH(int, start);
		QEQUAL(LatexParser::lineStart(text.toLatin1(), pos), start);
	}
	void test_lineEnd_data(){
		QTest::addColumn<QString>("text");
		QTest::addColumn<int>("pos");
		QTest::addColumn<int>("end");

		QTest::newRow("empty") << "" << 0 << 0;
		QTest::newRow("end") << "foo bar" << 7 << 7;
		QTest::newRow("text") << "foo bar" << 1 << 7;
		QTest::newRow("newline") << "foo\nbar" << 1 << 3;
		QTest::newRow("cr") << "foo\rbar" << 1 << 3;
		QTest::newRow("cr_newline") << "foo\r\nbar" << 1 << 3;
		QTest::newRow("end_newline") << "foo\nbar" << 3 << 3;
	}
	void test_lineEnd(){
		QFETCH(QString, text);
		QFETCH(int, pos);
		QFETCH(int, end);
		QEQUAL(LatexParser::lineEnd(text.toLatin1(), pos), end);
	}
	void test_getEncodingFromPackage_data() {
		QTest::addColumn<QString>("text");
		QTest::addColumn<QString>("encodingName");

		QTest::newRow("empty") << "" << "";
		QTest::newRow("no info") << "foo bar\nbaz" << "";
		QTest::newRow("simple") << "\\usepackage[latin1]{inputenc}" << "latin1";
		QTest::newRow("simple2") << "foo bar\nbaz\n\\usepackage[latin1]{inputenc}" << "latin1";
		QTest::newRow("spaces") << "  \\usepackage[utf8]{inputenc}  " << "utf8";
		QTest::newRow("multiple") << "\\usepackage[latin1]{inputenc}\n\\usepackage[utf8]{inputenc}" << "latin1";
		QTest::newRow("commented") << "  %\\usepackage[latin1]{inputenc}" << "";
		QTest::newRow("commented2") << "% \\usepackage[latin1]{inputenc}\n\\usepackage[utf8]{inputenc}" << "utf8";
	}
	void test_getEncodingFromPackage() {
		QFETCH(QString, text);
		QFETCH(QString, encodingName);
		QEQUAL(encodingName, LatexParser::getEncodingFromPackage(text.toLatin1(), text.length(), "inputenc"));
	}
	void test_guessEncoding_data() {
		QTest::addColumn<QString>("text");
		QTest::addColumn<QString>("encodingName");
		QTest::newRow("empty") << "" << "";
		QTest::newRow("no info") << "foo bar\nbaz" << "";
		QTest::newRow("inputenc") << "\\usepackage[latin1]{inputenc}" << "ISO-8859-1";
		QTest::newRow("inputenx") << "\\usepackage[utf8]{inputenx}" << "UTF-8";
	}
	void test_guessEncoding() {
		QFETCH(QString, text);
		QFETCH(QString, encodingName);

		QTextCodec *encoding = 0;
		int sure = 0;
		LatexParser::guessEncoding(text.toLatin1(), encoding, sure);
		if (encodingName.isEmpty()) {
            int b = (encoding==0) ? 0 : 1 ;
            QEQUAL(0, b);
		} else {
			QEQUAL(encodingName, QString(encoding->name()));
		}
	}
	void test_findClosingBracket_data(){
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
	void test_findClosingBracket(){
		QFETCH(QString, line);
		QFETCH(int, start);
		QFETCH(QChar, oc);
		QFETCH(QChar, cc);
		QFETCH(int, out);
		int ret = findClosingBracket(line, start, oc, cc);
		QEQUAL(ret, out);
	}
	void test_getCommand_data(){
		QTest::addColumn<QString>("line");
		QTest::addColumn<int>("pos");
		QTest::addColumn<QString>("outCmd");
		QTest::addColumn<int>("out");

		QTest::newRow("before") << "test \\section{sec}" << 0 << QString() << 0;
		QTest::newRow("before 2") << "test \\section{sec}" << 3 << QString() << 3;
		QTest::newRow("before 3") << "test \\section{sec}" << 4 << QString() << 4;
		QTest::newRow("at cmd start") << "\\section{sec}" << 0 << "\\section" << 8;
		QTest::newRow("at cmd start 2") << "test \\section{sec}" << 5 << "\\section" << 13;
		QTest::newRow("at cmd end") << "\\section{sec} end" << 7 << "\\section" << 8;
		QTest::newRow("at cmd end2") << "\\section nothing" << 7 << "\\section" << 8;
		QTest::newRow("at cmd end3") << "\\section" << 7 << "\\section" << 8;
		QTest::newRow("on brace") << "\\section{sec}" << 8 << QString() << 8;
		QTest::newRow("on optional brace") << "\\section[opt]{sec}" << 8 << QString() << 8;
		QTest::newRow("in argument") << "\\section{sec}" << 10 << QString() << 10;
	}
	void test_getCommand(){
		QFETCH(QString, line);
		QFETCH(int, pos);
		QFETCH(QString, outCmd);
		QFETCH(int, out);
		QString retCmd;
		int ret = getCommand(line, retCmd, pos);
		QEQUAL(ret, out);
		QEQUAL(retCmd, outCmd);
	}
	void test_trimLeft_data(){
		QTest::addColumn<QString>("line");
		QTest::addColumn<QString>("trimmedLine");

		QTest::newRow("leftSpace") << " ab" << "ab";
		QTest::newRow("rightSpace") << "ab " << "ab ";
		QTest::newRow("bothSpace") << " ab " << "ab ";
	}
	void test_trimLeft(){
		QFETCH(QString, line);
		QFETCH(QString, trimmedLine);
		QEQUAL(trimLeft(line), trimmedLine);
	}
	void test_trimRight_data(){
		QTest::addColumn<QString>("line");
		QTest::addColumn<QString>("trimmedLine");

		QTest::newRow("leftSpace") << " ab" << " ab";
		QTest::newRow("rightSpace") << "ab " << "ab";
		QTest::newRow("bothSpace") << " ab " << " ab";
	}
	void test_trimRight(){
		QFETCH(QString, line);
		QFETCH(QString, trimmedLine);
		QEQUAL(trimRight(line), trimmedLine);
	}
	void test_joinLinesExceptCommentsAndEmptyLines_data(){
		QTest::addColumn<QStringList>("in");
		QTest::addColumn<QStringList>("out");

		QTest::newRow("simple")
				<< (QStringList() << "ab" << "cd")
				<< (QStringList() << "ab cd");
		QTest::newRow("spaces")
				<< (QStringList() << "\tab " << "\tcd\t" << "ef\n")
				<< (QStringList() << "\tab cd ef");
		QTest::newRow("lineAsSeparator")
				<< (QStringList() << "\tab" << "" << "ef\n")
				<< (QStringList() << "\tab" << "" << "ef");
	}
	void test_joinLinesExceptCommentsAndEmptyLines(){
		QFETCH(QStringList, in);
		QFETCH(QStringList, out);
		QStringList joinedLines = joinLinesExceptCommentsAndEmptyLines(in);
		QEQUAL(joinedLines.length(), out.length());
		for (int i=0; i<joinedLines.count(); i++) {
			QEQUAL2(joinedLines[i], out[i], QString("in join #%1").arg(i));
		}
	}
	void test_splitLines_data() {
		QTest::addColumn<int>("maxChars");
		QTest::addColumn<QStringList>("in");
		QTest::addColumn<QStringList>("out");

		QTest::newRow("splitPosition") << 10
				<< (QStringList() << "01234 6789 12")
				<< (QStringList() << "01234 6789" << "12");
		QTest::newRow("splitPosition2") << 9
				<< (QStringList() << "01234 6789 12")
				<< (QStringList() << "01234" << "6789 12");
		QTest::newRow("commentContinuation") << 24
				<< (QStringList() << "this is a wrap % inside a comment")
				<< (QStringList() << "this is a wrap % inside" << "% a comment");
		QTest::newRow("keepIndentSpace") << 11
				<< (QStringList() << "  01234 6789 12")
				<< (QStringList() << "  01234" << "  6789 12");
		QTest::newRow("keepIndentTab") << 10
				<< (QStringList() << "\t01234 6789 12")
				<< (QStringList() << "\t01234" << "\t6789 12");
		QTest::newRow("keepIndentComment") << 26
				<< (QStringList() << "  this is a wrap % inside a comment")
				<< (QStringList() << "  this is a wrap % inside" << "  % a comment");
	}
	void test_splitLines(){
		QFETCH(int, maxChars);
		QFETCH(QStringList, in);
		QFETCH(QStringList, out);
		QRegExp breakChars("[ \t\n\r]");
		QStringList splittedLines = splitLines(in, maxChars, breakChars);
		QEQUAL(splittedLines.length(), out.length());
		for (int i=0; i<splittedLines.count(); i++) {
			QEQUAL2(splittedLines[i], out[i], QString("in split #%1").arg(i));
		}
	}
    /*
	void test_getSimplifiedSVNVersion_data(){
		QTest::addColumn<QString>("versionString");
		QTest::addColumn<int>("out");

		QTest::newRow("plain") << "1314" << 1314;
		QTest::newRow("modified") << "1314M" << 1314;
		QTest::newRow("mixed") << "1314:1315" << 1314;
		QTest::newRow("unknown") << "Unknown" << 0;
	}
	void test_getSimplifiedSVNVersion(){
		QFETCH(QString, versionString);
		QFETCH(int, out);
		QEQUAL(getSimplifiedSVNVersion(versionString), out);
    }*/
	void test_minimalJsonParse_data(){
		QTest::addColumn<QString>("jsonData");
		QTest::addColumn<bool>("retVal");
		QTest::addColumn<QStringList>("keys");
		QTest::addColumn<QStringList>("vals");

		QTest::newRow("empty") << "" << true << QStringList() << QStringList();
		QTest::newRow("empty") << "{}" << true << QStringList() << QStringList();
		QTest::newRow("single") << " { \"key\"  : \"val\" } " << true << (QStringList() << "key") << (QStringList() << "val");
		QTest::newRow("two") << "{\"key\":\"val\",\"key2\":\"val2\"} " << true << (QStringList() << "key" << "key2") << (QStringList() << "val" << "val2");
		QTest::newRow("escapedQoute") << "{\"key\":\"val\\\"more\"}" << true << (QStringList() << "key") << (QStringList() << "val\"more");
		QTest::newRow("missingClose") << "{\"key\":\"val\"" << false << (QStringList() << "key") << (QStringList() << "val");
		QTest::newRow("missingQuote1") << "{key:\"val\"}" << false << QStringList() << QStringList();
		QTest::newRow("missingQuote2") << "{\"key:\"val\"}" << false << QStringList() << QStringList();
		QTest::newRow("missingQuote3") << "{key\":\"val\"}" << false << QStringList() << QStringList();
	}
	void test_minimalJsonParse(){
		QFETCH(QString, jsonData);
		QFETCH(bool, retVal);
		QFETCH(QStringList, keys);
		QFETCH(QStringList, vals);

		QHash<QString, QString> data;
		QEQUAL(minimalJsonParse(jsonData, data), retVal);
		for (int i=0; i<keys.count(); i++) {
			QEQUAL2(data[keys[i]], vals[i], QString("for key: %1").arg(keys[i]));
		}
	}

	void test_enquoteDequoteString_data(){
		QTest::addColumn<QString>("in");
		QTest::addColumn<QString>("out");

		QTest::newRow("empty") << "" << "\"\"";
		QTest::newRow("plain") << "plain" << "\"plain\"";
		QTest::newRow("insideQuote") << "inside \"quote" << "\"inside \\\"quote\"";
		QTest::newRow("startQuote") << "\"startQuote" << "\"\\\"startQuote\"";
		QTest::newRow("endQuote") << "endQuote\"" << "\"endQuote\\\"\"";
	}
	void test_enquoteDequoteString(){
		QFETCH(QString, in);
		QFETCH(QString, out);

		QString quoted = enquoteStr(in);
		QEQUAL2(quoted, out, "while enqouting");
		QString unquoted = dequoteStr(quoted);
		QEQUAL2(unquoted, in, "while dequoting");
	}

	void test_replaceFileExtension_data(){
		QTest::addColumn<bool>("appendIfNoExtension");
		QTest::addColumn<QString>("file");
		QTest::addColumn<QString>("ext");
		QTest::addColumn<QString>("result");

		QTest::newRow("noExtension") << false << "c:/test" << "log" << QString();
		QTest::newRow("noExtensionAdd") << true << "c:/test" << "log" << "c:/test.log";
		QTest::newRow("simple") << false << "c:/test.tex" << "log" << "c:/test.log";
		QTest::newRow("relative") << false << "../dir/test.tex" << "log" << "../dir/test.log";
		QTest::newRow("doubleExtSrc") << false << "test.synctex.gz" << "log" << "test.log";
		QTest::newRow("doubleExtTarget") << false << "test.tex" << "synctex.gz" << "test.synctex.gz";
		QTest::newRow("dotExt") << false << "test.tex" << ".log" << "test.log";
		QTest::newRow("dotExtAdd") << true << "c:/test" << ".log" << "c:/test.log";
	}
	void test_replaceFileExtension() {
		QFETCH(bool, appendIfNoExtension);
		QFETCH(QString, file);
		QFETCH(QString, ext);
		QFETCH(QString, result);

		QEQUAL(replaceFileExtension(file, ext, appendIfNoExtension), result);
	}

	void test_getParamItem_data() {
		QTest::addColumn<QString>("line");
		QTest::addColumn<int>("pos");
		QTest::addColumn<bool>("stopAtWhiteSpace");
		QTest::addColumn<QString>("result");

		QTest::newRow("singleStart") << "\\section{Single}" << 9 << false << "Single";
		QTest::newRow("singleMid") << "\\section{Single}" << 11 << false << "Single";
		QTest::newRow("singleEnd") << "\\section{Single}" << 15 << false << "Single";

		QTest::newRow("singleSpaced") << "\\section{With Space}" << 9 << false << "With Space";
		QTest::newRow("singleSpaceStop") << "\\section{With Space}" << 9 << true << "With";
		QTest::newRow("singleSpaceStop2") << "\\section{With Space}" << 16 << true << "Space";

		QTest::newRow("optArg") << "\\caption[short]{long}" << 9 << false << "short";
		QTest::newRow("optArg") << "\\caption[short]{long}" << 11 << false << "short";
		QTest::newRow("optArg") << "\\caption[short]{long}" << 14 << false << "short";

		QTest::newRow("firstListParam") << "\\cmd{one, two, three}" << 5 << false << "one";
		QTest::newRow("secondListParam") << "\\cmd{one, two, three}" << 10 << false << " two";
		QTest::newRow("secondListParam2") << "\\cmd{one, two, three}" << 10 << true << "two";
		QTest::newRow("thirdListParam") << "\\cmd{one, two, three}" << 16 << true << "three";

		QTest::newRow("internalArg") << "\\cmd{an \\internal[opt]{cmd}}" << 6 << false << "an \\internal[opt]{cmd}";
		QTest::newRow("internalArg2") << "\\cmd{an \\internal[opt]{cmd}}" << 12 << true << "\\internal[opt]{cmd}";
		QTest::newRow("internalArg3") << "{\\cmd{an \\internal[opt]{cmd}} end}" << 33 << false << "\\cmd{an \\internal[opt]{cmd}} end";

		// Behavior for pos outside of a parameter is not part of the specification and subject to later change.
		// The following tests just document the current behavior.
		QTest::newRow("outside") << "\\section{Single}" << 8 << false << "\\section{Single}";
		QTest::newRow("outsideEnd") << "\\section{Single}" << 16 << false << "\\section{Single}";
		QTest::newRow("betweenArg") << "\\caption[short]{long}" << 15 << false << "\\caption[short]{long}";
		QTest::newRow("betweenColonAndSpaceArg") << "\\cmd{one, two}" << 9 << false << " two";
		QTest::newRow("betweenColonAndSpaceArg") << "\\cmd{one, two}" << 9 << true << "";
	}

	void test_getParamItem() {
		QFETCH(QString, line);
		QFETCH(int, pos);
		QFETCH(bool, stopAtWhiteSpace);
		QFETCH(QString, result);

		QEQUAL(getParamItem(line, pos, stopAtWhiteSpace), result);
	}

	void test_addMostRecent_data() {
		QTest::addColumn<QString>("item");
		QTest::addColumn<QStringList>("list");
		QTest::addColumn<int>("maxLength");
		QTest::addColumn<QStringList>("result");

		QTest::newRow("addEmpty") << "item1" << QStringList() << 2 << (QStringList() << "item1");
		QTest::newRow("addMax") << "item2" << (QStringList() << "item1") << 2 << (QStringList() << "item2" << "item1");
		QTest::newRow("addBeyondMax") << "item3" << (QStringList() << "item1" << "item2") << 2 << (QStringList() << "item3" << "item1");
		QTest::newRow("addExisting1") << "item1" << (QStringList() << "item1" << "item2") << 2 << (QStringList() << "item1" << "item2");
		QTest::newRow("addExisting2") << "item2" << (QStringList() << "item1" << "item2") << 2 << (QStringList() << "item2" << "item1");
	}

	void test_addMostRecent() {
		QFETCH(QString, item);
		QFETCH(QStringList, list);
		QFETCH(int, maxLength);
		QFETCH(QStringList, result);

		addMostRecent(item, list, maxLength);
		QEQUAL(list.length(), result.length());
		for (int i=0; i<list.length(); i++) {
			QEQUAL(list[i], result[i]);
		}
	}

	void test_indicesOf_data() {
		QTest::addColumn<QString>("line");
		QTest::addColumn<QString>("word");
		QTest::addColumn<bool>("caseSensitive");
		QTest::addColumn<QList<int> >("result");

		QTest::newRow("noMatch") << "A test, a test, a test" << "foo" << false << (QList<int>());
		QTest::newRow("multiCS") << "A test, a test, a test" << "a" << true << (QList<int>() << 8 << 16);
		QTest::newRow("multiCSI") << "A test, a test, a test" << "a" << false << (QList<int>() << 0 << 8 << 16);
		QTest::newRow("multiCS_end") << "A test, a test, a test" << "test" << true << (QList<int>() << 2 << 10 << 18);
	}

	void test_indicesOf() {
		QFETCH(QString, line);
		QFETCH(QString, word);
		QFETCH(bool, caseSensitive);
		QFETCH(QList<int>, result);

		QList<int> indices = indicesOf(line, word, caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
		QEQUAL(indices.length(), result.length());
		for (int i=0; i<indices.length(); i++) {
			QEQUAL(indices[i], result[i]);
		}
	}

	void test_indicesOf_RegExp_data() {
		QTest::addColumn<QString>("line");
		QTest::addColumn<QString>("rxString");
		QTest::addColumn<QList<int> >("result");

		QTest::newRow("noMatch") << "A test, a test, a test" << "foo" << (QList<int>());
		QTest::newRow("multi1") << "A test, a test, a test" << "a\\s+t" << (QList<int>() << 8 << 16);
		QTest::newRow("multi2") << "A test, a test, a test" << "[aA]\\s+t" << (QList<int>() << 0 << 8 << 16);
		QTest::newRow("multi3") << "A test, a test, a test" << "test" << (QList<int>() << 2 << 10 << 18);
	}

	void test_indicesOf_RegExp() {
		QFETCH(QString, line);
		QFETCH(QString, rxString);
		QFETCH(QList<int>, result);

		QList<int> indices = indicesOf(line, QRegExp(rxString));
		QEQUAL(indices.length(), result.length());
		for (int i=0; i<indices.length(); i++) {
			QEQUAL(indices[i], result[i]);
		}
	}

};


#endif
#endif
