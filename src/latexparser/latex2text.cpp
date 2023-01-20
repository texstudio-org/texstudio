#include "latex2text.h"
#include "latexreader.h"
#include "qdocumentline_p.h"

LineInfo::LineInfo(QDocumentLineHandle* line): line(line){
	text = line->text();
	// blank irrelevant content, i.e. commands, non-text, comments, verbatim
	TokenList tl = line->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	if(tl.isEmpty()){
		// special treatment of in verbatim env, as no tokens are generated
		text.fill(' ',text.length());
	}
	foreach(const Token &tk,tl){
		if(tk.type==Token::word && (tk.subtype==Token::none||tk.subtype==Token::text))
			continue;
		if(tk.type==Token::punctuation && (tk.subtype==Token::none||tk.subtype==Token::text))
			continue;
		if(tk.type==Token::symbol && (tk.subtype==Token::none||tk.subtype==Token::text))
			continue; // don't blank symbol like '~'
		if(tk.type==Token::braces && tk.subtype==Token::text){
			//remove braces around text argument
			text.replace(tk.start,1,QString(' '));
			text.replace(tk.start+tk.length-1,1,QString(' '));
			continue;
		}
		text.replace(tk.start,tk.length,QString(tk.length,' '));
	}
}

const QString uselessPunctation = "!:?,.;-"; //useful: \"(
const QString punctuationNotPreceededBySpace = "!:?,.;)\u00A0";  // \u00A0 is non-breaking space: assuming it is not surrounded by natural space (wouldn't make sense)
const QString punctuationNotFollowedBySpace = "(\"\u00A0";


/* Determine if words[i] should be preceeded by a space in the context of words.
 * If not continue.
 * If i > words.length() break;
 * This does always increase i by one. (Note: the checks below are written based on i++)
 * This is used in loops for selectively joining words with spaces. */


#define PRECEED_WITH_SPACES(i,words)                                      \
	                                                                    \
	(i)++;                                                              \
	                                                                    \
	if((i) >= words.length())                                           \
	    break;                                                          \
	                                                                    \
	if(words[i].length() == 1                                           \
	    && punctuationNotPreceededBySpace.contains(words[i][0]))        \
	        continue;                                                   \
	                                                                    \
	if(words[(i) - 1].length() == 1                                     \
	    && punctuationNotFollowedBySpace.contains(words[(i) - 1][0]))   \
	        continue;                                                   \
	                                                                    \
	if(words[(i) - 1].length() == 2 && words[(i) - 1][1] == '.'         \
	    && words[i].length() == 2 && words[i][1] == '.')                \
	        continue;



QList<TokenizedBlock> tokenizeWords(LatexParser *latexParser, const QList<LineInfo>& inlines){
	//gather words
	int nonTextIndex = 0;
	QList<TokenizedBlock> blocks;
	QList<TokenizedBlock> resultBlocks;
	blocks << TokenizedBlock();
	//blocks.last().firstLineNr = cr.firstLineNr;
	int floatingBlocks = 0;
	//int firstLineNr = cr.firstLineNr;
	for (int l = 0; l < inlines.size(); l++) {
		TokenizedBlock &tb = blocks.last();
		LatexReader lr(*latexParser, inlines[l].text);
		int type;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) {
				if (lr.word == "figure") { //config.floatingEnvs.contains(lr.word)) {
					if (lr.lastCommand == "\\begin") {
						floatingBlocks ++;
					} else if (lr.lastCommand == "\\end") {
						floatingBlocks --;
					}
				}
				continue;
			}

			if (type == LatexReader::NW_COMMENT) break;
			if (type != LatexReader::NW_TEXT && type != LatexReader::NW_PUNCTATION) {
				//reference, label, citation
				tb.words << QString("keyxyz%1").arg(nonTextIndex++);
				tb.indices << lr.wordStartIndex;
				tb.endindices << lr.index;
				tb.lines << l;
				continue;
			}

			if (latexParser->structureCommandLevel(lr.lastCommand) >= 0) {
				//don't check captions
				QStringList temp;
				QList<int> starts;
				LatexParser::resolveCommandOptions(lr.line, lr.wordStartIndex - 1, temp, &starts);
				for (int j = 0; j < starts.count() && j < 2; j++) {
					lr.index = starts.at(j) + temp.at(j).length() - 1;
					if (temp.at(j).startsWith("{")) break;
				}
				tb.words << ".";
				tb.indices << lr.wordStartIndex;
				tb.endindices << 1;
				tb.lines << l;
				continue;
			}


			if (type == LatexReader::NW_TEXT) tb.words << lr.word;
			else if (type == LatexReader::NW_PUNCTATION) {
				if ((lr.word == "-") && !tb.words.isEmpty()) {
					//- can either mean a word-separator or a sentence -- separator
					// => if no space, join the words at both sides of the - (this could be easier handled in nextToken, but spell checking usually doesn't support - within words)
					if (lr.wordStartIndex == tb.endindices.last()) {
						tb.words.last() += lr.word;
						tb.endindices.last()++;

						int tempIndex = lr.index;
						int type = lr.nextWord(false);
						if (type == LatexReader::NW_COMMENT) break;
						if (tempIndex != lr.wordStartIndex) {
							lr.index = tempIndex;
							continue;
						}
						tb.words.last() += lr.word;
						tb.endindices.last() = lr.index;
						continue;
					}
				} else if (lr.word == "\"") {
					lr.word = "'";  // replace " by ' because " is encoded as &quot; and screws up the (old) LT position calculation
				} else if (lr.word == "~") {
					lr.word =  "\u00A0";  // rewrite LaTeX non-breaking space to unicode non-braking space
				} else if (punctuationNotPreceededBySpace.contains(lr.word) && !tb.words.isEmpty() && tb.words.last() == "\u00A0") {
					// rewrite non-breaking space followed by punctuation to punctuation only. e.g. "figure~\ref{abc}." -> "figure."
					// \ref{} is dropped by the reader and an erronous would leave "figure\u00A0."
					// As a heuristic no space before punctuation takes precedence over non-breaking space.
					// This is the best we can do for now. A complete handling of all cases is only possible with a full tokenization.
					tb.words.last() = lr.word;
					tb.endindices.last() = lr.index;
					continue;
				}
				tb.words << lr.word;
			}

			tb.indices << lr.wordStartIndex;
			tb.endindices << lr.index;
			tb.lines << l;

		}


		while (floatingBlocks > blocks.size() - 1) blocks << TokenizedBlock();
		while (floatingBlocks >= 0 && floatingBlocks < blocks.size() - 1)
			resultBlocks << blocks.takeLast();
	}
	while (blocks.size()) resultBlocks << blocks.takeLast();


	for (int b = 0; b < resultBlocks.size(); b++) {
		TokenizedBlock &tb = resultBlocks[b];
		while (!tb.words.isEmpty() && tb.words.first().length() == 1 && uselessPunctation.contains(tb.words.first()[0])) {
			tb.words.removeFirst();
			tb.indices.removeFirst();
			tb.endindices.removeFirst();
			tb.lines.removeFirst();
		}
	}
	return resultBlocks;
}


QString TokenizedBlock::toString() const{
	if (words.isEmpty()) return "";
	QString joined;
	int expectedLength = 0;
	foreach (const QString & s, words) expectedLength += s.length();
	joined.reserve(expectedLength + words.length());
	for (int i = 0;;) {
		joined += words[i];
		PRECEED_WITH_SPACES(i, words)
		joined += " ";
	}
	return joined;
}

bool TokenizedBlock::StringOffsetIterator::map(int offset, int length, int * lineIndex, int * trueOffset, int* trueLength)
{
	if (curWord >= tb.words.length()) return false;

	while (offset >= curOffset + tb.words[curWord].length()) {
		curOffset += tb.words[curWord].length();
		PRECEED_WITH_SPACES(curWord, tb.words)
		curOffset++; //space
	}
	if (curWord >= tb.words.length()) return false;

	*trueOffset = tb.indices[curWord] + qMax(0, offset - curOffset);
	*trueLength = -1;
	int offsetEnd = offset + length;
	int tempOffset = curOffset;
	for (int w = curWord; ; ) {
		tempOffset += tb.words[w].length();
		if (tempOffset >=  offsetEnd) {
			if (tb.lines[curWord] == tb.lines[w]) {
				int trueOffsetEnd = tb.endindices[w] - qMax(0, tempOffset - offsetEnd);
				*trueLength = trueOffsetEnd - *trueOffset;
			}
			break;
		}
		PRECEED_WITH_SPACES(w, tb.words)
		tempOffset++; //space
	}
	if (*trueLength == -1)
		*trueLength = inlines[tb.lines[curWord]].text.length() - *trueOffset;
	*lineIndex = tb.lines[curWord];

	return true;
}


#undef PRECEED_WITH_SPACES
