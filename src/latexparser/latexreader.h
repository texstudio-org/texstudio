#ifndef Header_Latex_Reader
#define Header_Latex_Reader

#include "latexparser.h"

/*!
 * \brief class for parsing latex code
 *
 * \warning obsolete with lexer based token system
 * \note this functionality is still used in none-core methods
 */
struct LatexReader {
	LatexReader();
	LatexReader(const QString &line);
	LatexReader(const LatexParser &lp, const QString &line);
	LatexReader(const LatexParser &lp, const QString &line, QMap<QString, QString> &replacementList);

	/*! searches the next token in the line line after/at the index index
	 there are these possible kind of tokens % (which starts a comment), { or } (as parentheses), \.* (command) or .* (text)
	 \param index returns the index of the first character after the word
	 \param inOption Don't stop at eow characters
	 \param detectMath If true, returns $ $$ _ ^ & as commands
	 \returns start index of the token (or -1 if last)
	*/
	static int nextToken(const QString &line, int &index, bool inOption, bool detectMath);

	enum NextWordFlag {
		NW_NOTHING = 0,
		NW_TEXT = 1,
		NW_COMMAND = 2,
		NW_COMMENT = 3,
		NW_ENVIRONMENT = 4, ///< environment name, e.g. in \begin or \newenvironment
		NW_REFERENCE = 5,
		NW_LABEL = 6,
		NW_CITATION = 7,
		NW_PUNCTATION = 8,
		NW_PACKAGE = 9
	};

	//Returns the next word (giving meaning to the nextToken tokens)
	//line: line to be examined
	//index: start index as input and returns the first character after the found word
	//outWord: found word (length can differ from index - wordStartIndex for text words)
	//wordStartIndex: start of the word
	//returnCommands: if this is true it returns \commands (NW_COMMAND), "normal" "text"  NW_TEXT and % (NW_COMMENT)  [or NW_NOTHING at the end]
	//                "    "  is false it only returns normal text (NW_TEXT, without things like filenames after \include), environment names
	//                          (NW_ENVIRONMENT, they are treated as text in the other mode) and % (NW_COMMENT)       [or NW_NOTHING at the end]
	//returns the type of outWord
	NextWordFlag nextWord(bool returnCommands);

	//searches the next text words and ignores command options, environments or comments
	//returns false if none is found
	bool nextTextWord();

	const QString &getLine() const; ///< get current line of latexParser
	void setLine(const QString &line); ///< set line for latexParser
	QString line; ///< current line used in latexParser

	int index; ///< current used column position
	QString word; ///< currently handled word
	QString lastCommand; ///< currently active command
	int wordStartIndex; ///< index of \a word

private:
	const LatexParser *lp;
	QMap<QString, QString> mReplacementList;
};


#endif // LATEXREADER_H
