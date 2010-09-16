#ifndef CODESNIPPET_H
#define CODESNIPPET_H

#include "mostQtHeaders.h"
//#include "texmaker.h"

class QDocumentCursor;
class QEditor;
class Texmaker;

struct CodeSnippetPlaceHolder{
	int offset, length;
	int id;
	enum Flag{AutoSelect = 1, Mirrored = 2, Mirror = 4, PreferredMultilineAutoSelect = 8};
	int flags;
	int offsetEnd();
};

class CodeSnippet
{
public:
	CodeSnippet():cursorLine(-1), cursorOffset(-1),anchorOffset(-1) {}
	CodeSnippet(const CodeSnippet &cw):word(cw.word),sortWord(cw.sortWord),lines(cw.lines),cursorLine(cw.cursorLine),cursorOffset(cw.cursorOffset),anchorOffset(cw.anchorOffset),placeHolders(cw.placeHolders) {}
	CodeSnippet(const QString &newWord);
	bool operator< (const CodeSnippet &cw) const;
	bool operator== (const CodeSnippet &cw) const;

	QString word,sortWord;
	QStringList lines; 
	//TODO: Multirow selection
	int cursorLine;  //-1 => not defined
	int cursorOffset; //-1 => not defined
	int anchorOffset;
	QList<QList<CodeSnippetPlaceHolder> > placeHolders; //used to draw

	void insert(QEditor* editor);
	void insertAt(QEditor* editor, QDocumentCursor* cursor, bool usePlaceholders=true,bool byCompleter=false) const;

	void setName(const QString& name);
	QString getName();

	static bool autoReplaceCommands;

private:
	QString name;
	QDocumentCursor getCursor(QEditor* editor, const CodeSnippetPlaceHolder &ph, int snippetLine, int baseLine, int baseLineIndent, int lastLineRemainingLength) const;
};

Q_DECLARE_METATYPE(CodeSnippet);
#endif // CODESNIPPET_H
