#ifndef SMALLUSEFULFUNCTIONS_T_H
#define SMALLUSEFULFUNCTIONS_T_H
#ifndef QT_NO_DEBUG
#include "..\smallUsefulFunctions.h"
#include <QList>
#include <QRegExp>
#include <QString>
#include <QStringList>
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
		int firstComment=tokens.length();
		for (int i=0;i<tokens.length();i++){
			tokens[i].position=curpos;
			str+=tokens[i];
			curpos+=tokens[i].length();
			if (tokens[i].type==NW_COMMENT && i<firstComment) firstComment=i;
		}
		//remove all tokens which don't belong to the current test
		switch (filter){
			case FILTER_NEXTTOKEN:
				for (int i=tokens.length()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN && tokens[i]!="{" && tokens[i]!="}")	
						tokens.removeAt(i);
				break;
			case FILTER_NEXTWORD_WITH_COMMANDS:
				for (int i=tokens.length()-1;i>=0;i--)
					if (tokens[i].type==NW_IGNORED_TOKEN)	tokens.removeAt(i);
					else if (tokens[i].type==NW_ENVIRONMENT || tokens[i].type==NW_OPTION)
						tokens[i].type=NW_TEXT;//nextWord in command mode don't distinguish between text, environments and options
				break;
			case FILTER_NEXTWORD:
				for (int i=tokens.length()-1;i>=0;i--)
					if (tokens[i].type==NW_COMMAND || tokens[i].type==NW_OPTION || tokens[i].type==NW_IGNORED_TOKEN) 
						tokens.removeAt(i);//remove tokens not returned by nextWord in text mode
				break;
			case FILTER_NEXTTEXTWORD:
				for (int i=tokens.length()-1;i>=0;i--)
					if (tokens[i].type!=NW_TEXT || i>=firstComment)  
						tokens.removeAt(i);//remove all except text before comment start
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
			if (pos>=tokens.length()) {
				QFAIL(QString("Found additional token: %1 at %2").arg(token).arg(startIndex).toLatin1().constData());
			} else {
				QVERIFY2(token==tokens[pos], QString("Invalid token: %1 at %2 expected %3").arg(token).arg(startIndex).arg(tokens[pos]).toLatin1().constData());
				QVERIFY2(startIndex==tokens[pos].position, QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex).toLatin1().constData());
			}
			pos++;
		}
		QVERIFY2 (pos==tokens.length(), "Didn't found all tokens");
	}
	
};

/*

void printStr(QString str){
	results.write((str+"\n").toAscii());
}

#define fatalError(text) {printStr(QString("ERROR: %1").arg(text)); return ;}
void error(QString text) { printStr(QString("Error: %1").arg(text));}



void nextWordTest(QString str, bool commands, QStringList tokens, QList<int> positions, QList<int> types){
	printStr(QString("\nnextWordTest: %1 %2").arg(str).arg(commands));
	if (tokens.length()!=positions.length()) fatalError("Test Data Invalid, length mismatch tokens <> positions");
	if (tokens.length()!=types.length()) fatalError("Test Data Invalid, length mismatch tokens <> types");
	int index=0;int startIndex=0;
	int pos=0; int type;
	QString token;
	while ((type=nextWord(str, index, token, startIndex, commands))!=NW_NOTHING) {
		if (pos>=tokens.length()) error(QString("Found additional word: %1 at %2").arg(token).arg(startIndex));
		else {
			if (token!=tokens[pos]) error(QString("Invalid word: %1 at %2, expected %3").arg(token).arg(startIndex).arg(tokens[pos]));
			if (startIndex!=positions[pos]) error(QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex));
			if (type!=types[pos]) error(QString("Invalid type: %2 for %1").arg(token).arg(type));
		}
		pos++;
	}
	if (pos<tokens.length()) error("Didn't found all tokens");
}

void nextTextWordTest(QString str, QStringList tokens, QList<int> positions){
	printStr(QString("\nnextTextWordTest: %1").arg(str));
	if (tokens.length()!=positions.length()) fatalError("Test Data Invalid");
	int index=0;int startIndex=0;
	int pos=0;
	QString token;
	while (nextTextWord(str, index, token, startIndex)) {
		if (pos>=tokens.length()) error(QString("Found additional token: %1 at %2").arg(token).arg(startIndex));
		else {
			if (token!=tokens[pos]) error(QString("Invalid token: %1 at %2, expected").arg(token).arg(startIndex).arg(tokens[pos]));
			if (startIndex!=positions[pos]) error(QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex));
		}
		pos++;
	}
	if (pos<tokens.length()) error("Didn't found all tokens");
}


void testStringParsers(QString str, QStringList tokens, QList<int> positions, QList<int> types){
	nextTokenTest(str,tokens,positions); //next token will return all tokens
	QList<int> newTypes;
	for (int i=types.length()-1;i>=0;i--)  
		switch (types[i]) { //remove all tokens only returned by nextToken ({ and })
			case NW_IGNORED_TOKEN: 
				tokens.removeAt(i);
				positions.removeAt(i);
				types.removeAt(i);
				break;
			case NW_ENVIRONMENT:  //nextWord in command mode don't distinguish between text and environments
			case NW_OPTION_TEXT:  //and return options text
				newTypes.push_front(NW_TEXT); 
				break;
			default: 
				newTypes.push_front(types[i]);
		}
	nextWordTest(str,true,tokens,positions,newTypes);
	for (int i=types.length()-1;i>=0;i--)  
		if (types[i]==NW_OPTION_TEXT || types[i]==NW_COMMAND) { //remove tokens not returned by nextWord in text mode
			tokens.removeAt(i);
			positions.removeAt(i);
			types.removeAt(i);
		}
	nextWordTest(str,false,tokens,positions,types);
	int comment=types.indexOf(NW_COMMENT);
	if (comment>-1) //remove comments, ignored by nextTextWord
		for (int i=types.length()-1;i>=comment;i--){
			tokens.removeLast();
			positions.removeLast();
			types.removeLast();
		}
	for (int i=types.length()-1;i>=0;i--)  
		if (types[i]!=NW_TEXT) { //remove everything which is no text
			tokens.removeAt(i);
			positions.removeAt(i);
			types.removeAt(i);
		}
	nextTextWordTest(str,tokens,positions);
}

void tests(){
	const NextWordFlag NWT = NW_TEXT;
	const NextWordFlag NWE = NW_ENVIRONMENT;
	const NextWordFlag NWC = NW_COMMENT;
	const NextWordFlag NWX = NW_COMMAND;
	const int NWO = NW_OPTION_TEXT;
	const int NWI = NW_IGNORED_TOKEN;
	testStringParsers("abcde    fghik\tMice",
	              QStringList() << "abcde" << "fghik" << "Mice",
				  QList<int>()  <<    0    <<     9   << 15,
				  QList<int>()  <<  NWT << NWT << NWT);
	testStringParsers("Test1234\\begin{environment}{add}XYZ!!!\\command%comment\\COMMENT",
				  QStringList() << "Test1234" << "\\begin" << "{" << "environment" << "}" << "{" << "add" << "}" << "XYZ" << "\\command" << "%" << "comment" << "\\COMMENT",
				  QList<int>() <<       0      <<  8       << 14  <<     15        << 26  << 27  << 28    << 31  <<  32   <<    38       << 46  <<   47      <<   54 ,
				  QList<int>() <<     NWT      <<  NWX     << NWI <<    NWE        << NWI << NWI <<  NWT  << NWI <<  NWT  <<    NWX      << NWC <<   NWT     <<   NWX   );
	testStringParsers("\\newenvironment{env} \\begin{env2} \\end{env3} \\renewenvironment{env4}", 
	             QStringList() << "\\newenvironment" << "{" << "env" << "}" << "\\begin" << "{" << "env2" << "}" << "\\end" << "{" << "env3" << "}" << "\\renewenvironment" << "{" << "env4" << "}",
				 QList<int>() <<       0             << 15  <<  16   << 19  <<   21      << 27  <<   28   <<  32 <<   34    << 38  <<  39    << 43  <<    45                << 62  <<  63    << 67 ,
				 QList<int>() <<       NWX           << NWI <<  NWE  << NWI <<   NWX     << NWI <<  NWE   << NWI <<  NWX    << NWI << NWE    << NWI <<    NWX               << NWI <<  NWE   << NWI);
	testStringParsers("hallo welt! \\ignoreMe{text}     \\begin{I'mXnotXthere} *g* % more \\comment", 
				QStringList() << "hallo" << "welt" << "\\ignoreMe" << "{" << "text" << "}" << "\\begin" << "{" << "I'mXnotXthere" << "}" << "g"  << "%" << "more" << "\\comment",
				QList<int>()  <<    0    <<   6    << 12           << 21  <<  22    << 26  <<  32       << 38  << 39              << 52  <<  55  << 58  <<  60     <<   65,
				QList<int>()  <<  NWT    <<   NWT  <<   NWX        << NWI << NWT    << NWI <<   NWX     << NWI << NWE             << NWI << NWT  << NWC <<  NWT      <<  NWX);
	testStringParsers("\\includegraphics[ab.\\linewidth]{\\abc dfdf\\xyz}continue", 
				QStringList() << "\\includegraphics" << "ab" << "\\linewidth" << "{" << "\\abc" << "dfdf" << "\\xyz" << "}" << "continue",
				QList<int>()  <<    0                << 17   <<   20          <<  31 <<   32    <<  37    <<  41     << 45  << 46,
				QList<int>()  <<    NWX              << NWO  <<   NWX        <<  NWI <<   NWX   <<  NWO   << NWX     << NWI <<  NWT);
}

int main(int argc, char ** argv) {
  results.open(QIODevice::WriteOnly);
  tests();
  results.close();
  return 0;
}
*/
#endif
#endif
