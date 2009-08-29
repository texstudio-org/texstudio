#ifndef SMALLUSEFULFUNCTIONS_T_H
#define SMALLUSEFULFUNCTIONS_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "testutil.h"
#include <QtTest/QtTest>

const int NW_IGNORED_TOKEN=-2; //token with are no words,  { and }
const int NW_OPTION=-3; //option text like in \include

class TestToken: public QString{
	static const QRegExp simpleTextRegExp; //defined in testmanager.cpp
	static const QRegExp commandRegExp;
	static const QRegExp ignoredTextRegExp;
	void guessType(){
		if (simpleTextRegExp.exactMatch(*this)) type=NW_TEXT;
		else if (commandRegExp.exactMatch(*this)) type=NW_COMMAND;
		else if (ignoredTextRegExp.exactMatch(*this)) type=NW_IGNORED_TOKEN;
		else if (*this=="%") type=NW_COMMENT;
		else QVERIFY2(false, QString("invalid test data: \"%1\"").arg(*this).toLatin1().constData());
	}
public:
	int type,position;
	TestToken():QString(), type(NW_IGNORED_TOKEN){ }
	TestToken(const TestToken& token):QString(token), type(token.type), position(token.position){ }
	TestToken(const QString& str):QString(str){
		guessType();
	}
	TestToken(const char* cstr):QString(cstr){
		guessType();
	}
	TestToken(const QString& str, int atype):QString(str),type(atype){}
};

Q_DECLARE_METATYPE(TestToken);
Q_DECLARE_METATYPE(QList<TestToken>);

/*QList<TestToken>& operator<< (QList<TestToken> & list, const char* str){
	return list << TestToken(str);
}*/

class SmallUsefulFunctionsTest: public QObject{
	Q_OBJECT
	TestToken env(const QString& str){
		return TestToken(str, NW_ENVIRONMENT);
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
			if (tokens[i].type==NW_COMMENT && i<firstComment) firstComment=i;
		}
		//remove all tokens which don't belong to the current test
		switch (filter){
			case FILTER_NEXTTOKEN:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN && tokens[i]!="{" && tokens[i]!="}")	
						tokens.removeAt(i);
				break;
			case FILTER_NEXTWORD_WITH_COMMANDS:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN)	tokens.removeAt(i);
					else if (tokens[i].type==NW_ENVIRONMENT || tokens[i].type==NW_OPTION)
						tokens[i].type=NW_TEXT;//nextWord in command mode don't distinguish between text, environments and options
					else if (tokens[i].contains("\\") && tokens[i].type==NW_TEXT) 
						tokens[i].replace("\\",""); //unescape escaped characters
				break;
			case FILTER_NEXTWORD:
				for (int i=tokens.size()-1;i>=0;i--) 
					if (tokens[i].type==NW_COMMAND || tokens[i].type==NW_OPTION || tokens[i].type==NW_IGNORED_TOKEN) 
						tokens.removeAt(i);//remove tokens not returned by nextWord in text mode
					else if (tokens[i].contains("\\") && tokens[i].type==NW_TEXT) 
						tokens[i].replace("\\",""); //unescape escaped characters
				break;
			case FILTER_NEXTTEXTWORD:
				for (int i=tokens.size()-1;i>=0;i--)
					if (tokens[i].type!=NW_TEXT || i>=firstComment)  
						tokens.removeAt(i);//remove all except text before comment start
					else if (tokens[i].contains("\\") && tokens[i].type==NW_TEXT) 
						tokens[i].replace("\\",""); //unescape escaped characters
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
		addRow("environment+comment",filter,
			QList<TestToken>() << "Test1234" << "\\begin" << "{" << env("environment") << "}" << "{" << "add" << "}" << "XYZ" << "!!!" << "\\command" << "%"     << "comment" << "\\COMMENT");
		addRow("some environments", filter,
			QList<TestToken>() << "\\newenvironment" << "{" << env("env") << "}" << " " << "\\begin" << "{" << env("env2") << "}" << " " << "\\end" << "{" << env("env3") << "}" << "  " << "\\renewenvironment" << "{" << env("env4") << "}");
		addRow("misc", filter, //was only for nextWord, other test will of course not ignore \\ignoreMe 
			QList<TestToken>() << "hallo" << " " << "welt" << "\\ignoreMe" << "{" << "text" << "}" << "     " << "\\begin" << "{" << env("I'mXnotXthere") << "}" << " *" << "g"  << "* " << "%"     << " " << "more" << " " << "\\comment");
		addRow("command as option", filter,
			QList<TestToken>() << "\\includegraphics" << "[" << option("ab") << "." << "\\linewidth" << "]" << "{" << "\\abc" << " " << option("dfdf") << "\\xyz" << "}" << "continue");
		addRow("comments", filter, QList<TestToken>() << "hallo" << " " << "welt" <<  "  " << "\\\\" << "normaltext" <<  "  " << TestToken("\\%",NW_TEXT) << "!!!" << "stillNoComment" << "\\\\" << TestToken("\\%",NW_TEXT) <<"  "<< "none" << "\\\\" << "%" << "comment" << "   " << "more" << " " << "comment");
		addRow("escaped characters", filter, QList<TestToken>() << TestToken("hallo\\%abc",NW_TEXT));
	}
	void nextWord_complex_test(bool commands){
		//get data
		QFETCH(QString, str);	
		QFETCH(QList<TestToken>, tokens);	
		int index=0;int startIndex=0;
		int pos=0; int type;
		QString token;
		while ((type=nextWord(str, index, token, startIndex, commands))!=NW_NOTHING) {
			if (pos>=tokens.size()) {
				QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			} else {
				QVERIFY2(token==tokens[pos], QString("Invalid token: %1 at %2 expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
				QVERIFY2(type==tokens[pos].type, QString("Invalid type: %2 for %1").arg(token).arg(type).toLatin1().constData());
			}
			pos++;
		}
		QVERIFY2 (pos==tokens.size(), "Didn't found all tokens");
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
		while ((startIndex = nextToken(str,index)) != -1) {
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
		
		int index=0;int startIndex=0;
		int pos=0;
		QString token;
		while (nextTextWord(str, index, token, startIndex)) {
			if (pos>=tokens.size()) QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			else {
				QVERIFY2(token==tokens[pos], QString("Invalid token: %1 at %2, expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
			}
			pos++;
		}
		QVERIFY2 (pos==tokens.size(), "Didn't found all tokens");
	}
	
	
	void nextWordSimple_simple_data(){
		QTest::addColumn<QString >("line");
		QTest::addColumn<int>("inIndex");
		QTest::addColumn<bool>("commands");
		QTest::addColumn<bool>("abbreviations");

		QTest::addColumn<int>("result");
		QTest::addColumn<int>("outIndex");
		QTest::addColumn<QString>("outWord");
		QTest::addColumn<int>("wordStartIndex");
		
		QTest::newRow("reference") << "bummerang\\ref{  xyz  }abcdef" << 9 << false << false
		                           << (int)NW_REFERENCE << 21 << "  xyz  " << 14;
		QTest::newRow("label")     << "bummerang\\label{  x:y:z  }abcdef" << 9 << false << false
		                           << (int)NW_LABEL << 25 << "  x:y:z  " << 16;
		QTest::newRow("citation0") << "012345\\cite{aaaHallob}abcdef" << 6 << false << false
		                           << (int)NW_CITATION << 21 << "aaaHallob" << 12;
		QTest::newRow("citation1") << "012345\\cite{   Hallo   }abcdef" << 6 << false << false
		                           << (int)NW_CITATION << 23 << "   Hallo   " << 12;
		QTest::newRow("citation2") << "012345\\textcite{ Hallo:Welt! }abcdef" <<6  << false << false
		                           << (int)NW_CITATION << 29 << " Hallo:Welt! " << 16;
		QTest::newRow("citation3") << "012345\\cite[aasasadaa]{Hallo:Welt!,miau!}abcdef" << 6 << false << false
		                           << (int)NW_CITATION << 40 << "Hallo:Welt!,miau!" << 23;
	}
	void nextWordSimple_simple(){
		QFETCH(QString, line);
		QFETCH(int, inIndex);
		QFETCH(bool, commands);
		QFETCH(bool, abbreviations);

		QFETCH(int, result);
		QFETCH(int, outIndex);
		QFETCH(QString, outWord);
		QFETCH(int, wordStartIndex);
		
		QString row;
		int wsi;
		int rs=(int)(nextWord(line,inIndex,row,wsi,commands,abbreviations));

		QEQUAL(rs, result);
		QEQUAL(inIndex,outIndex);
		QEQUAL(row,outWord);
		QEQUAL(wsi,wordStartIndex);
	}
};

#endif
#endif
