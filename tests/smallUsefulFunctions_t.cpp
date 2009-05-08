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
	if (pos!=tokens.length()) error("Didn't found all tokens");
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
			if (token!=tokens[pos]) error(QString("Invalid work: %1 at %2").arg(token).arg(startIndex));
			if (startIndex!=positions[pos]) error(QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex));
			if (type!=types[pos]) error(QString("Invalid type: %2 for %1").arg(token).arg(type));
		}
		pos++;
	}
	if (pos!=tokens.length()) error("Didn't found all tokens");
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
			if (token!=tokens[pos]) error(QString("Invalid token: %1 at %2").arg(token).arg(startIndex));
			if (startIndex!=positions[pos]) error(QString("Invalid startIndex: %2 for %1").arg(token).arg(startIndex));
		}
		pos++;
	}
	if (pos!=tokens.length()) error("Didn't found all tokens");
}

void tests(){
    //==================NextToken==================
	nextTokenTest("abcde    fghik\tMice",
	              QStringList() << "abcde" << "fghik" << "Mice",
				  QList<int>()  <<    0    <<     9   << 15);
	nextTokenTest("Test1234\\begin{environment}{add}XYZ!!!\\command%comment\\COMMENT",
				  QStringList() << "Test1234" << "\\begin" << "{" << "environment" << "}" << "{" << "add" << "}" << "XYZ" << "\\command" << "%" << "comment" << "\\COMMENT",
				  QList<int>() <<       0      <<  8       << 14  <<     15        << 26  << 27  << 28    << 31  <<  32   <<    38       << 46  <<   47      <<   54 );
	nextTokenTest("hallo welt! \\ignoreMe{text}     \\begin{I'mXnotXthere} *g* % more \\comment", 
				QStringList() << "hallo" << "welt" << "\\ignoreMe" << "{" << "text" << "}" << "\\begin" << "{" << "I'mXnotXthere" << "}" << "g"  << "%" << "more" << "\\comment",
				QList<int>()  <<    0    <<   6    << 12           << 21  <<  22    <<  26 <<  32        << 38 << 39              << 52  <<  55  << 58  <<  60     <<   65);
    //===================NextWord=====================				  
	const NextWordFlag NWT = NW_TEXT;
	const NextWordFlag NWE = NW_ENVIRONMENT;
	const NextWordFlag NWC = NW_COMMENT;
	const NextWordFlag NWX = NW_COMMAND;
	nextWordTest("abcde    fghik\tMice", false, 
	            QStringList() << "abcde" << "fghik" << "Mice",
				QList<int>()  <<    0    <<     9   <<  15,
				QList<int>()  <<  NW_TEXT << NW_TEXT<< NWT);
	nextWordTest("abcde    fghik\tMice", true, 
	            QStringList() << "abcde" << "fghik" << "Mice",
				QList<int>()  <<    0    <<     9   <<  15,
				QList<int>()  <<  NW_TEXT << NW_TEXT<< NWT);
	nextWordTest("hallo welt! \\ignoreMe{text}     \\begin{I'mXnotXthere} *g* % more \\comment", false,
				QStringList() << "hallo" << "welt" << "text" << "I'mXnotXthere" << "g"  << "%" << "more",
				QList<int>()  <<    0    <<   6    <<   22   <<  39             <<  55  << 58  <<  60,
				QList<int>()  <<  NWT    <<   NWT  <<  NWT   <<     NWE         << NWT  << NWC <<  NWT);
	nextWordTest("\\newenvironment{env} \\begin{env2} \\end{env3} \\renewenvironment{env4}", false,
	             QStringList() << "env" << "env2" << "env3" << "env4",
				 QList<int>() << 16 << 28 << 39 << 63,
				 QList<int>() << NWE << NWE << NWE << NWE);
	nextWordTest("hallo welt! \\ignoreMe{text}     \\begin{I'mXnotXthere} *g* % more \\comment", true,
				QStringList() << "hallo" << "welt" << "\\ignoreMe" << "text" << "\\begin" << "I'mXnotXthere" << "g"  << "%" << "more" << "\\comment",
				QList<int>()  <<    0    <<   6    << 12           <<  22   <<  32        << 39             <<  55  << 58  <<  60     <<   65,
				QList<int>()  <<  NWT    <<   NWT  <<   NWX        << NWT   <<    NWX     <<  NWT         << NWT  << NWC <<  NWT      <<  NWX);
    //=================NextTextWord=====================
	
				  
	nextTextWordTest("hallo welt! \\ignoreMe{text}     \\begin{I'mXnotXthere} *g* % more comment",
					QStringList() << "hallo" << "welt" << "text" << "g",
					QList<int>()  <<    0    <<   6    <<   22   <<  55);
}

int main(int argc, char ** argv) {
  results.open(QIODevice::WriteOnly);
  tests();
  results.close();
  return 0;
}

