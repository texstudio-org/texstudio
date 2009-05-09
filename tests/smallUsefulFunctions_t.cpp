#include "..\smallUsefulFunctions.h"
#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>

QFile results("results.txt"); 

void printStr(QString str){
	results.write((str+"\n").toAscii());
}

#define fatalError(text) {printStr(QString("ERROR: %1").arg(text)); return ;}
void error(QString text) { printStr(QString("Error: %1").arg(text));}

void nextTokenTest(QString str, QStringList tokens, QList<int> positions){
	printStr(QString("\nnextTokenTest: %1").arg(str));
	if (tokens.length()!=positions.length()) fatalError("Test Data Invalid");
	int index=0;int startIndex=0;
	int pos=0;
	while ((startIndex = nextToken(str,index)) != -1) {
		QString token=str.mid(startIndex,index-startIndex);
		if (pos>=tokens.length()) error(QString("Found additional token: %1 at %2").arg(token).arg(startIndex));
		else {
			if (token!=tokens[pos]) error(QString("Invalid token: %1 at %2").arg(token).arg(startIndex));
			if (startIndex!=positions[pos]) error(QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex));
		}
		pos++;
	}
	if (pos<tokens.length()) error("Didn't found all tokens");
}


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

const int NW_IGNORED_TOKEN=-2; //token with are no words,  { and }
const int NW_OPTION_TEXT=-3; //option text like in \include

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

