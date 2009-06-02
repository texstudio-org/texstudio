#ifndef CODESNIPPET_H
#define CODESNIPPET_H

#include "qeditor.h"
#include "qdocumentcursor.h"

//currently implemented in latexcompleter.cpp should be moved
class CompletionWord {
public:
	CompletionWord():cursorPos(-1),anchorPos(-1) {}
	CompletionWord(const CompletionWord &cw):word(cw.word),sortWord(cw.sortWord),shownWord(cw.shownWord),cursorPos(cw.cursorPos),anchorPos(cw.anchorPos),descriptiveParts(cw.descriptiveParts) {}
	CompletionWord(const QString &newWord);//see cpp
	bool operator< (const CompletionWord &cw) const {
		return cw.sortWord > sortWord;
	}
	bool operator== (const CompletionWord &cw) const {
		return cw.word == word;
	}

	QString word,sortWord,shownWord;
	int cursorPos; //-1 => not defined
	int anchorPos;
	QList<QPair<int, int> > descriptiveParts; //used to draw

	void insertAt(QEditor* editor, QDocumentCursor* cursor);
};
Q_DECLARE_METATYPE(CompletionWord);

class CodeSnippet
{
public:
    CodeSnippet();
};

#endif // CODESNIPPET_H
