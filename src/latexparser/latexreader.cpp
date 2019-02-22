#include "latexreader.h"
#include "smallUsefulFunctions.h"


const QString PUNCTUATION = "!():\"?,.;-~";
const QString ESCAPED_CHARS = "%&_";
const QString CHARACTER_ALTERING_CHARS = "\"'^`";


LatexReader::LatexReader(): index(0), wordStartIndex(0), lp(&LatexParser::getInstance())
{
	Q_ASSERT(this->lp);
}

LatexReader::LatexReader(const QString &line): lp(&LatexParser::getInstance())
{
	Q_ASSERT(this->lp);
	setLine(line);
}

LatexReader::LatexReader(const LatexParser &lp, const QString &line): lp(&lp)
{
	Q_ASSERT(this->lp);
	setLine(line);
}

LatexReader::LatexReader(const LatexParser &lp, const QString &line, QMap<QString, QString> &replacementList): lp(&lp)
{
	Q_ASSERT(this->lp);
	setLine(line);
	mReplacementList = replacementList;
}

int LatexReader::nextToken(const QString &line, int &index, bool inOption, bool detectMath)
{
	bool inWord = false;
	bool inCmd = false;
	//bool reparse=false;
	bool singleQuoteChar = false;
	bool doubleQuoteChar = false;
	bool ignoreBrace = false;
	bool ignoreClosingBrace = false;
	int start = -1;
	int i = index;
	for (i = (i > 0 ? i : 0); i < line.size(); i++) {
		QChar cur = line.at(i);
		if (ignoreBrace && cur == '{') {
			ignoreBrace = false;
			ignoreClosingBrace = true;
			continue;
		} else ignoreBrace = false;
		if (ignoreClosingBrace && cur == '}') {
			ignoreClosingBrace = false;
			continue;
		}
		if (doubleQuoteChar)
			//if (cur == '\'') break; // check for words starting with "' (german quotation mark)
			if (getCommonEOW().contains(cur)) break; // check for all quotation marks
		doubleQuoteChar = false;
		if (inCmd) {
			if (getCommonEOW().indexOf(cur) >= 0 || cur.isDigit()) {
				if (i - start == 1) i++;
				break;
			}
		} else if (inWord) {
			if (cur == '\\') {
				if (i + 1 >= line.size()) break;
				const QChar &c = line.at(i + 1);
				if (c == '-' || c == '&') i++; //allow \& in the middle/end of words, e.g. C&A
				else if (CHARACTER_ALTERING_CHARS.contains(c)) {
					ignoreBrace = true;
					i++;//ignore word separation marker
				} else break;
			} else if (cur == '"') { //ignore " like in "-, "", "| "a
				if (i + 1 < line.size()) {
					QChar nextChar = line.at(i + 1);
					if (nextChar == '-' || nextChar == '"' || nextChar == '|')  i++;
					else if (!nextChar.isLetterOrNumber()) break;
				} else break;
			} else if (cur == '\'') {
				if (singleQuoteChar) break;	 //no word's with two '' => output
				else singleQuoteChar = true; //but accept one
			} else if (cur == '.' || cur == '-') {
				if (i > 0 && line.at(i - 1).isLetter())
					i++; //take '.' or '-' into word, so that abbreviations/hyphenations, at least German ones, are checked correctly
				if (cur == '-' &&  i < line.size() && line.at(i).isLetter())
					; // continue with composite words
				else
					break;
			} else if (getCommonEOW().indexOf(cur) >= 0 && !inOption) {
				break;
			} else if (cur == '}' || cur == ']') break;

		} else if (cur == '\\') {
			if (i + 1 >= line.size()) break;
			const QChar &nextc = line.at(i + 1);
			if (CHARACTER_ALTERING_CHARS.contains(nextc))  {
				inWord = true;
				start = i;
				ignoreBrace = true;
				i++;
			} else if (ESCAPED_CHARS.contains(nextc)) {
				i++;
				Q_ASSERT(start == -1);
			} else {
				start = i;
				inCmd = true;
			}
		} else if (cur == '{' || cur == '}' || cur == '%' || cur == '[' || cur == ']') {
			index = i + 1;
			return i;
		} else if (detectMath && cur == '$') {
			start = i;
			i++;
			if (i < line.size() && line[i] == '$')
				i++; //detect $$
			break;
		} else if (detectMath && (cur == '_' || cur == '^' || cur == '&')) {
			start = i;
			i++;
			break;
		} else if ((getCommonEOW().indexOf(cur) < 0 && cur != '\'' ) || cur == '"') {
			start = i;
			inWord = true;
			doubleQuoteChar = ( cur == '"');
		} else if (PUNCTUATION.contains(cur)) {
			start = i;
			i++;
			while (i < line.length() && line.at(i) == '-') i++; //convert LaTeX --- to a single -
			break;
		}
	}
	if (singleQuoteChar && i - 1 < line.size() && i > 0 && line.at(i - 1) == '\'')
		i--; //remove ' when a word ends with it  (starting is handled because ' does not start a word)
	index = i;
	return start;
}

/*! Returns the next word (giving meaning to the nextToken tokens)
 * line: line to be examined
 * index: start index as input and returns the first character after the found word
 * outWord: found word (length can differ from index - wordStartIndex for text words)
 * wordStartIndex: start of the word
 * returnCommands: if this is true it returns \commands (NW_COMMAND), "normal" "text"  NW_TEXT and % (NW_COMMENT)  [or NW_NOTHING at the end]
 *                 "    "  is false it only returns normal text (NW_TEXT, without things like filenames after \include), environment names
 *                           (NW_ENVIRONMENT, they are treated as text in the other mode) and % (NW_COMMENT)       [or NW_NOTHING at the end]
 * \return the type of outWord
 * \warning obsolete with lexer based token system
 */
LatexReader::NextWordFlag LatexReader::nextWord(bool returnCommands)
{
	int reference = -1;
	bool inOption = false;
	bool inEnv = false;
	bool inReferenz = false;
	int inReferenzExt = 0;
	while ((wordStartIndex = nextToken(line, index, inEnv, !inReferenz)) != -1) {
		word = line.mid(wordStartIndex, index - wordStartIndex);
		if (word.length() == 0) return NW_NOTHING; //should never happen
		switch (word.at(0).toLatin1()) {
		case '%':
			return NW_COMMENT; //return comment start
		case '[':
			if (!lastCommand.isEmpty()) inOption = true;
			break;
		case ']':
			inOption = false;
			break;
		case '{':
			if (reference != -1)
				reference = wordStartIndex + 1;
			if (!lastCommand.isEmpty()) inOption = true;
			if (lp->environmentCommands.contains(lastCommand)) inEnv = true;
			break; //ignore
		case '}':
			if (inReferenzExt > 1) {
				inReferenzExt--;
			} else {
				if (reference != -1) {
					NextWordFlag result = NW_NOTHING;
					if (lp->possibleCommands["%ref"].contains(lastCommand)) result = NW_REFERENCE;
					else if (lp->possibleCommands["%label"].contains(lastCommand)) result = NW_LABEL;
					else if (lp->possibleCommands["%cite"].contains(lastCommand)) result = NW_CITATION;
					else if (lp->possibleCommands["%usepackage"].contains(lastCommand)) result = NW_PACKAGE;
					else if (lp->possibleCommands["%citeExtendedCommand"].contains(lastCommand)) result = NW_CITATION;
					if (result != NW_NOTHING) {
						wordStartIndex = reference;
						--index;
						word = line.mid(reference, index - reference);
						return result;
					}
				}
				lastCommand = "";
				inOption = false;
				inEnv = false;
			}
			break;//command doesn't matter anymore
		case '$':
		case '^':
		case '&':
			return NW_COMMAND;
		case '_':
			if (!inOption) {
				return NW_COMMAND;
			}
			break;
		case '\\':
			if (word.length() == 1 || !(ESCAPED_CHARS.contains(word.at(1)) || CHARACTER_ALTERING_CHARS.contains(word.at(1)))) {
				if (returnCommands) return NW_COMMAND;
				if (lp->possibleCommands["%ref"].contains(word) || lp->possibleCommands["%label"].contains(word) || lp->possibleCommands["%cite"].contains(word) || lp->possibleCommands["%usepackage"].contains(word)) {
					reference = index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
					lastCommand = word;
					inReferenz = true;
				}
				if (lp->possibleCommands["%citeExtendedCommand"].contains(word)) {
					QString line;
					foreach (line, lp->possibleCommands["%citeExtended"]) {
						if (line.startsWith(word))
							break;
						line.clear();
					}
					if (!line.isEmpty()) {
						reference = index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
						lastCommand = word;
						line = line.remove(QRegExp("[.*]"));
						int pos = line.indexOf("%<bibid%>");
						line = line.left(pos);
						inReferenzExt = line.count("{");
					}
				}
				if (lp->optionCommands.contains(lastCommand) || lastCommand.isEmpty() || word == "\\begin" || word == "\\end") {
					lastCommand = word;
				}
				break;
			} else {
                [[clang::fallthrough]];   //first character is escaped, fall through to default case
			}
		default:
			//if (reference==-1) {
			if (!inOption && !lastCommand.isEmpty()) {
				inOption = false;
				lastCommand = "";
			}
			//if (word.length() == 2 && word[0] == '"' && CommonEOW.contains(word[1]))
			//	return NW_PUNCTATION; //some quotation mark
			if (word.length() > 1 && (word.contains('\\') || word.contains('"'))) {
				//word=latexToPlainWord(word); //remove special chars
				word = latexToPlainWordwithReplacementList(word, mReplacementList); //remove special chars
				if (word.isEmpty()) continue;
			}
			if (lp->environmentCommands.contains(lastCommand))
				return NW_ENVIRONMENT;
			if (lastCommand.isEmpty() || lp->optionCommands.contains(lastCommand)) {
				if (word.length() && PUNCTUATION.contains(word[0])) {
					if (word.length() > 1) word = word[0];
					return NW_PUNCTATION;
				}
				return NW_TEXT;
			}
			//}
		}
	}
	return NW_NOTHING;
}

/*! searches the next text words and ignores command options, environments or comments
 * returns false if none is found
 * \warning obsolete with lexer based token system
 */
bool LatexReader::nextTextWord()
{
	NextWordFlag flag = NW_PUNCTATION;
	//flag can be nothing, text, comment, environment/punctation
	//text/comment returns false, text returns true, environment/punctation is ignored
	while (flag == NW_ENVIRONMENT || flag == NW_PUNCTATION)
		flag = nextWord(false);
	return flag == NW_TEXT;
}

const QString &LatexReader::getLine() const
{
	return line;
}

void LatexReader::setLine(const QString &line)
{
	this->line = line;
	this->index = 0;
	this->wordStartIndex = 0;
}
