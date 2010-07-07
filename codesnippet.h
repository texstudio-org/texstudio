#ifndef CODESNIPPET_H
#define CODESNIPPET_H

#include "mostQtHeaders.h"
//#include "texmaker.h"

class QDocumentCursor;
class QEditor;
class Texmaker;
class CodeSnippet
{
public:
	CodeSnippet():cursorLine(-1), cursorOffset(-1),anchorOffset(-1),m_cut(false) {}
	CodeSnippet(const CodeSnippet &cw):word(cw.word),sortWord(cw.sortWord),lines(cw.lines),cursorLine(cw.cursorLine),cursorOffset(cw.cursorOffset),anchorOffset(cw.anchorOffset),placeHolders(cw.placeHolders),m_cut(cw.m_cut) {}
	CodeSnippet(const QString &newWord);
	bool operator< (const CodeSnippet &cw) const {
		return cw.sortWord > sortWord;
	}
	bool operator== (const CodeSnippet &cw) const {
		return cw.word == word;
	}

	QString word,sortWord;
	QStringList lines; 
	//TODO: Multirow selection
	int cursorLine;  //-1 => not defined
	int cursorOffset; //-1 => not defined
	int anchorOffset;
	QList<QList<QPair<int, int> > > placeHolders; //used to draw

	void insert(QEditor* editor);
	void insertAt(QEditor* editor, QDocumentCursor* cursor, bool usePlaceholders=true,bool byCompleter=false) const;

	void setCut(bool cut) {m_cut=cut;}

	static bool autoReplaceCommands;

private:
        bool m_cut;
};

Q_DECLARE_METATYPE(CodeSnippet);
#endif // CODESNIPPET_H
