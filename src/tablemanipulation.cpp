#include "tablemanipulation.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexparser.h"
#include "scriptengine.h"
#include "configmanager.h"
#include "latexparsing.h"
#include "latexdocument.h"

QSet<QString> LatexTables::tabularNames = QSet<QString>() << "tabular" << "array" << "longtable" << "supertabular" << "tabu" << "longtabu"
                                                          << "IEEEeqnarray" << "xtabular" << "xtabular*" << "mpxtabular" << "mpxtabular*"<<"tblr"<<"longtblr"<<"talltblr";
QSet<QString> LatexTables::tabularNamesWithOneOption = QSet<QString>() << "tabular*" << "tabularx" << "tabulary";
QSet<QString> LatexTables::mathTables = QSet<QString>() << "align" << "align*" << "array" << "matrix" << "matrix*" << "bmatrix" << "bmatrix*"
                                      << "Bmatrix" << "Bmatrix*" << "pmatrix" << "pmatrix*" << "vmatrix" << "vmatrix*"
                                      << "Vmatrix" << "Vmatrix*" << "split" << "multline" << "multline*"
                                      << "gather" << "gather*" << "flalign" << "flalign*" << "alignat" << "alignat*"
                                      << "cases" << "aligned" << "gathered" << "alignedat";

static QSet<QString> environmentsRequiringTrailingLineBreak = QSet<QString>() << "supertabular";
// Note: Apparently some environments always require a line break "\\". These should be specified here.
// Some don't want one, e.g. align, blockarray, ...
// And some can cope with both cases, e.g. tabular
// Our approach is to remove the last line break unless it's neccesary, either because the
// environment needs it, or there is additional stuff after the line break, such as "\\ \hline".
// See also: https://tex.stackexchange.com/questions/400827/should-i-use-a-line-break-after-the-last-tabular-row

/*!
 * \brief add row in tabular-like environment
 * After current cursor position, a new row is added with the given number of columns.
 * \param c
 * \param numberOfColumns
 * \param env
 */
void LatexTables::addRow(QDocumentCursor &c, Environment env)
{
    QDocumentLineHandle *dlh=env.dlh;
    QDocument *doc=dlh->document();
    int ln = doc->indexOf(dlh,c.lineNumber());
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int nextLine,nextCol;
    Token tkColDef=getDef(tl,env,ln,nextLine,nextCol,doc);
    QString def = tkColDef.getInnerText();

    if (def.isEmpty()) {
        return; // preamble empty
    }

    //add col in definition
    QStringList defs = splitColDef(def);
    int numberOfColumns = defs.count();
    // move cursor to start of tabular
    QDocumentCursor cur(doc,nextLine,nextCol);
    // find row
    for(;;){
        enum NextRowAvailable cont=findRow(cur,env);
        if(cur.isWithinSelection(c)){
            // check that c is not at the end of selection
            if(cur.anchorLineNumber()!=c.lineNumber() || cur.anchorColumnNumber()!=c.columnNumber() || cont==RowNotAvailableLazyNewLine){
                // cursor is not at end of selection
                // row found, remove it
                int row0=cur.lineNumber();
                int col0=cur.columnNumber();
                // check if row is indented
                const QString line= cur.line().text();
                QRegularExpression re("^\\s*");
                QRegularExpressionMatch match=re.match(line);
                QString indent;
                if(match.hasMatch()){
                    indent=match.captured(0);
                }
                if(cont==RowNotAvailableLazyNewLine){
                    // \\ missing, add here
                    indent.prepend("\\\\\n");
                }
                int row=cur.anchorLineNumber();
                int col=cur.anchorColumnNumber();
                cur.setLineNumber(row);
                cur.setColumnNumber(col);
                cur.beginEditBlock();
                QString str("& ");
                QString outStr(indent+ " ");
                for (int i = 1; i < numberOfColumns; i++) {
                    outStr += str;
                }
                cur.insertText(outStr);
                cur.insertText("\\\\");
                if (!cur.atLineEnd()) cur.insertText("\n");
                cur.endEditBlock();
                break;
            }
        }
        if(cont != RowAvailable) break; // no next row
        int row=cur.anchorLineNumber();
        int col=cur.anchorColumnNumber();
        cur.setLineNumber(row);
        cur.setColumnNumber(col);
    }
}

void LatexTables::removeRow(QDocumentCursor &c)
{
	QDocumentCursor cur(c);
    const QStringList tokens{"\\\\","\\tabularnewline"};
	if (cur.hasSelection()) {
		if (cur.lineNumber() > cur.anchorLineNumber() || (cur.lineNumber() == cur.anchorLineNumber() && cur.columnNumber() > cur.anchorColumnNumber())) {
			cur.moveTo(cur.anchorLineNumber(), cur.anchorColumnNumber());
		}
	}
	int result = findNextToken(cur, tokens, false, true);
    if (result >= 0){
        cur.movePosition(tokens[result].length(), QDocumentCursor::NextCharacter);
    }
	if (result == -2) cur.movePosition(1, QDocumentCursor::EndOfLine);
	bool breakLoop = false;
	while (!(breakLoop = (findNextToken(cur, tokens, true) == -1)) && c.isWithinSelection(cur) ) {
	}
	if (!breakLoop) {
		// check if end of cursor is at line end
		QDocumentCursor c2(cur.document(), cur.anchorLineNumber(), cur.anchorColumnNumber());
		if (c2.atLineEnd()) {
			c2.movePosition(1, QDocumentCursor::NextCharacter);
			cur.moveTo(c2, QDocumentCursor::KeepAnchor);
		}
		// remove text
		cur.beginEditBlock();
		cur.removeSelectedText();
		if (cur.line().text().isEmpty()) cur.deleteChar(); // don't leave empty lines
		cur.endEditBlock();
	}
}
/*! remove row in tabular-like environment
 * \param c the cursor in the tabular-like environment
 * \param env the actual environment
 */
void LatexTables::removeRow(QDocumentCursor &c, Environment env)
{
    QDocumentLineHandle *dlh=env.dlh;
    QDocument *doc=dlh->document();
    int ln = doc->indexOf(dlh,c.lineNumber());
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int nextLine,nextCol;
    Token tkColDef=getDef(tl,env,ln,nextLine,nextCol,doc);
    // move cursor to start of tabular
    QDocumentCursor cur(doc,nextLine,nextCol);
    // find row
    for(;;){
        enum NextRowAvailable cont=findRow(cur,env);
        if(cur.isWithinSelection(c)){
            // check that c is not at the end of selection
            if(cur.anchorLineNumber()!=c.lineNumber() || cur.anchorColumnNumber()!=c.columnNumber() || cont==RowNotAvailableLazyNewLine){
                // cursor is not at end of selection
                // row found, remove it
                cur.beginEditBlock();
                cur.removeSelectedText();
                if (cur.line().text().isEmpty()) cur.deleteChar(); // don't leave empty lines
                cur.endEditBlock();
                break;
            }
        }
        if(cont != RowAvailable) break; // no next row
        int row=cur.anchorLineNumber();
        int col=cur.anchorColumnNumber();
        cur.setLineNumber(row);
        cur.setColumnNumber(col);
    }
}

/*!
 * \brief add column in tabular-like environment
 * \param env the actual environment
 * \param lineNumber
 * \param afterColumn
 * \param cutBuffer
 */
void LatexTables::addColumn(Environment env, const int lineNumber, const int afterColumn, QStringList *cutBuffer)
{
    QDocumentLineHandle *dlh=env.dlh;
    QDocument *doc=dlh->document();
    int ln = doc->indexOf(dlh,lineNumber);
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int nextLine,nextCol;
    Token tkColDef=getDef(tl,env,ln,nextLine,nextCol,doc);

    QStringList pasteBuffer;
    if (cutBuffer) {
        pasteBuffer = *cutBuffer;
        if (pasteBuffer.size() == 0)
            return;
    }
    QString def = tkColDef.getInnerText();

    if (def.isEmpty()) {
        return; // begin not found
    }

    //add col in definition
    QStringList defs = splitColDef(def);
    QString addCol = "l";
    if (cutBuffer) {
        addCol = pasteBuffer.takeFirst();
    }
    def.clear();
    if (afterColumn == 0)
        def = addCol;
    for (int i = 0; i < defs.count(); i++) {
        def.append(defs[i]);
        if (i + 1 == afterColumn || (i + 1 == defs.count() && i + 1 < afterColumn))
            def.append(addCol);
    }
    QDocumentCursor cur(doc,ln,tkColDef.innerStart(),ln,tkColDef.innerStart()+tkColDef.innerLength());
    cur.beginEditBlock();
    cur.insertText(def);
    //continue adding col
    //move cursor after definition -> \begin{tabularlike}{def}|
    if(ln==nextLine) ++nextCol; // move col by one as we inserted a column
    cur.moveTo(nextLine,nextCol);
    cur.movePosition(1);
    bool breakLoop = false;
    while (!breakLoop) {
        Token tkResult;
        for (int col = 0; col < afterColumn; col++) {
            if(col>0) findNextColumn(cur,tkResult);
            tkResult = findColumn(cur, env);
            const QString txt=cur.selectedText();
            int add = 0;
            if (txt.startsWith("\\multicolumn")) {
                add = getNumOfColsInMultiColumn(txt)-1;
                if(add<0) add=0; // no negative number of columns
            }
            col+=add; // add number of columns in multicolumn
            if (tkResult.length>1) break; // end of row reached
        }
        if(afterColumn==0){
            // prepend column
            // call findColumn to move left side after potential hline
            findColumn(cur, env);
            const int c=cur.columnNumber();
            const int r=cur.lineNumber();
            cur.setColumnNumber(c);
            cur.setLineNumber(r);
        }
        // add element
        if (tkResult.length>0) { // column separator found
            const int c=cur.anchorColumnNumber();
            const int r=cur.anchorLineNumber();
            cur.setColumnNumber(c);
            cur.setLineNumber(r);
        }
        QString txt=" ";
        if(!pasteBuffer.isEmpty()){
            txt=pasteBuffer.takeFirst();
        }
        if(afterColumn==0){
            cur.insertText(txt+"&");
        }else{
            cur.insertText("&"+txt);
        }
        tkResult.start+=txt.length()+1; // shift start

        // move to next row
        // jump over &
        while(tkResult.length==1 || tkResult.length<0 /* first column*/){
            if(tkResult.length>0){
                bool success=findNextColumn(cur,tkResult);
                if(!success){
                    break;
                }
            }
            tkResult = findColumn(cur, env);
        }
        if (tkResult.getText()=="\\end{") break;
        breakLoop=!findNextColumn(cur,tkResult);
    }
    cur.endEditBlock();
}

/*!
 * \brief remove a column from a tabular-like environment
 * \param env environment in which the column is removed
 * \param lineNumber line number of the tabular-like environment
 * \param column column to be removed, starting with 0
 * \param cutBuffer buffer to store cut text, can be nullptr
 */
void LatexTables::removeColumn(Environment env, const int lineNumber, const int column, QStringList *cutBuffer)
{
    QDocumentLineHandle *dlh=env.dlh;
    QDocument *doc=dlh->document();
    int ln = doc->indexOf(dlh,lineNumber);
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int nextLine,nextCol;
    Token tkColDef=getDef(tl,env,ln,nextLine,nextCol,doc);

    QString def = tkColDef.getInnerText();

    //remove col in definition
    QStringList defs = splitColDef(def);
    def.clear();
    for (int i = 0; i < defs.count(); i++) {
        if (i == column) {
            if (cutBuffer)
                cutBuffer->append(defs[i]);
        } else {
            def.append(defs[i]);
        }
    }
    QDocumentCursor cur(doc,ln,tkColDef.innerStart(),ln,tkColDef.innerStart()+tkColDef.innerLength());
    cur.beginEditBlock();
    if(def.isEmpty()){
        cur.removeSelectedText();
    }else{
        cur.insertText(def);
    }
    //continue adding col
    //move cursor after definition -> \begin{tabularlike}{def}|
    if(ln==nextLine) --nextCol; // move col by one as we inserted a column
    cur.moveTo(nextLine,nextCol);
    cur.movePosition(1);

    const QStringList nTokens{"\\\\","\\tabularnewline","\\&","&"};
    // remove column
    QString line;
    bool breakLoop = false;
    while (!breakLoop) {
        Token tkResult;
        Token tkPrevious;
        int add=0;
        int col=0;
        for (col = 0; col <= column; col++) {
            add = 0;
            tkPrevious=tkResult;
            if(col>0) findNextColumn(cur,tkResult);
            tkResult = findColumn(cur, env);
            const QString txt=cur.selectedText();
            if (txt.startsWith("\\multicolumn")) {
                add = getNumOfColsInMultiColumn(txt)-1;
            }
            col+=add; // add number of columns in multicolumn
            if (tkResult.length>1) break; // end of row reached
        }
        if(col>=column){
            if(add>0){
                // multicolumn found, so we manipulate just the number of columns
                QString selText=cur.selectedText();
                //multicolumn handling
                QStringList values;
                resolveCommandOptions(selText, 0, values);
                if(values.isEmpty()){
                    // no multicolumn arguments found, so we bail out
                    cur.endEditBlock();
                    return;
                }
                values.takeFirst();
                values.prepend(QString("{%1}").arg(add));
                cur.insertText("\\multicolumn" + values.join(""));
                tkResult = findColumn(cur, env);
            }else{
                const QString txt=cur.selectedText();
                if(cutBuffer){
                    cutBuffer->append(txt);
                }
                // extend anchor to column separator
                if(tkResult.length==1){
                    // & found
                    cur.setAnchorColumnNumber(tkResult.start+tkResult.length);
                    tkResult=Token(); // reset token as removed
                }else{
                    if(tkPrevious.length==1){
                        // previous token was & so we extend start to that
                        int lnOld=doc->indexOf(tkPrevious.dlh,cur.lineNumber());
                        cur.setLineNumber(lnOld,QDocumentCursor::KeepAnchor);
                        cur.setColumnNumber(tkPrevious.start,QDocumentCursor::KeepAnchor);
                    }
                }

                int len;
                if(cur.lineNumber()!=cur.anchorLineNumber()){
                    // multi line selection, shifts token into new line
                    // simply search again
                    cur.removeSelectedText();
                    tkResult = findColumn(cur, env);
                }else{
                    tkResult.start-=cur.anchorColumnNumber()-cur.columnNumber(); // shift start
                    cur.removeSelectedText();
                }
            }
        }


        // move to next row
        // jump over &
        while(tkResult.length==1 || tkResult.length<0 /* first column*/){
            if(tkResult.length>0) findNextColumn(cur,tkResult);
            tkResult = findColumn(cur, env);
            if(tkResult.length<0){
                // no column separator found, run-away
                // bail out
                cur.endEditBlock();
                return;
            }
        }
        if (tkResult.getText()=="\\end{") break;
        breakLoop=!findNextColumn(cur,tkResult);
    }
    cur.endEditBlock();
}

// find next element starting from cursor whhich is in the string list "tokens". The element which is closest to the cursor is returned
// return >=0 : position of stringlist which was detected
// return -1 : end of file was found, no element detected
// return -2 : \end{...} was detected (the env-name is not tested)
//
// the cursor is moved right behind the detected token ! (or in front in case of backward search)
int LatexTables::findNextToken(QDocumentCursor &cur, QStringList tokens, bool keepAnchor, bool backwards)
{
	int pos = -1;
	int nextToken = -1;
	int offset = 0;
	QDocumentCursor::MoveOperation mvNextLine = backwards ? QDocumentCursor::PreviousLine : QDocumentCursor::NextLine;
	QDocumentCursor::MoveOperation mvNextChar = backwards ? QDocumentCursor::PreviousCharacter : QDocumentCursor::NextCharacter;
	QDocumentCursor::MoveOperation mvStartOfLine = backwards ? QDocumentCursor::EndOfLine : QDocumentCursor::StartOfLine;
	QDocumentCursor::MoveFlag mvFlag = keepAnchor ? QDocumentCursor::KeepAnchor : QDocumentCursor::MoveAnchor;
	do {
		QString line = cur.line().text();
		if (backwards) {
			offset = line.length();
		}
        line = cutComment(line);
		if (backwards) {
			offset = offset - line.length();
            std::reverse(line.begin(),line.end());
		}

		if (line.contains("\\end{") && !backwards) {
			nextToken = -2;
			break;
		}
		if (line.contains("{nigeb\\") && backwards) {
			nextToken = -2;
			break;
		}

		pos = -1;
		for (int i = 0; i < tokens.count(); i++) {
			QString elem = tokens.at(i);
            if(backwards){
                // reverse element as it was done with line
                std::reverse(elem.begin(),elem.end());
            }
			int colNumber = cur.columnNumber();
			if (backwards) colNumber = line.length() + offset - colNumber ;
			int zw = line.indexOf(elem, colNumber);
			if (zw > -1) {
				if (pos > zw || pos == -1) {
					pos = zw;
					nextToken = i;
				}
			}
		}
		if (pos < 0) {
			if (!backwards && cur.lineNumber() >= cur.document()->lineCount() - 1) break;
			if (backwards && cur.lineNumber() <= 0) break;
			cur.movePosition(1, mvNextLine, mvFlag);
			cur.movePosition(1, mvStartOfLine, mvFlag);
		}
	} while (pos < 0);
	if (pos > -1) {
		cur.movePosition(1, mvStartOfLine, mvFlag);
		cur.movePosition(pos + tokens.at(nextToken).length() + offset, mvNextChar, mvFlag);
	}
	return nextToken;
}
/*!
 * \brief find and select column in which the cursor is positioned
 * At start cursor sit at start of column,i.e. after last \\
 * Skip over \hline and similar, set cursor at first useable token
 * Scan for & or \\ (or env end) and set anchor to that position (start of token)
 * In case of tblr, handle multiline cells correctly ( {a\\b} is one cell, so we skip over the braces)
 * Result delivers the separator token (&,\\,etc.)
 * \param cur
 * \return
 */
Token LatexTables::findColumn(QDocumentCursor &cur, Environment env)
{
    int ln=cur.lineNumber();
    int col=cur.columnNumber();
    // reset anchor point
    cur.setAnchorColumnNumber(-1);
    cur.setAnchorLineNumber(-1);
    Token tkResult;
    QDocument *doc=cur.document();
    TokenList tl;
    do{
    QDocumentLineHandle *dlh=doc->line(ln).handle();
    dlh->lockForRead();
    tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    }while(tl.isEmpty() && ++ln<doc->lineCount()); // skip empty lines)
    if(tl.isEmpty()){
        // missing closing element
        return Token();
    }
    TokenList tl_prev;
    int ln_previous=-1;
    int ignoreUntilColumn=-1; // special ignore new row cmd in tblr (multi line cells)
    enum ScanMode {ScanModeSkipInitial,ScanModeInColumn};
    ScanMode mode= ScanModeSkipInitial;
    for(int i=0;i<tl.size();++i){
        tkResult=tl.at(i);
        if(tkResult.start<col){
            if(i<tl.size()-1){
                continue; // jump through tokens until we reach the column
            }
            // last token before col, so continue in next line below
            tkResult=Token(); // reset token
        }
        if(tkResult.type==Token::command){
            const QString cmd=tkResult.getText();
            if(cmd=="\\hline" && mode== ScanModeSkipInitial){
                // skip over \hline
                // todo, skip over potential optional argument
                // move cursor start
                cur.setLineNumber(ln);
                cur.setColumnNumber(tkResult.start+tkResult.length);
            }else{
                mode= ScanModeInColumn; // we are in a column now
            }
            if(cmd=="&"){
                // column end found
                cur.setAnchorColumnNumber(tkResult.start);
                cur.setAnchorLineNumber(ln);
                break;
            }
            const QStringList tokens{"\\\\","\\tabularnewline","\\end"}; // end preliminary, to be refined
            if(tokens.contains(cmd) && tkResult.start>=ignoreUntilColumn){
                // column break is found, handle like column end
                // special treatment for end if before end is empty
                if(cmd=="\\end"){
                    if(i+2>tl.size()) continue; // no next token in same line, so ignore this
                    // check for matchin env name
                    const Token &nextTk=tl.at(i+1);
                    if(nextTk.subtype==Token::env && nextTk.getInnerText()==env.name){
                        // end of env found (no nesting)
                        if(i>0 || tl_prev.isEmpty()){
                            // token in front, column selection includes that or fallback for missing previous line info
                            cur.setAnchorColumnNumber(tkResult.start);
                            cur.setAnchorLineNumber(ln);
                        }else{
                            // no token in front, so we select end of last token
                            int c=0;
                            for(int j=0; j<tl_prev.size();++j){
                                int lastCol=tl_prev.at(j).start+tl_prev.at(j).length;
                                if(c<lastCol){
                                    c=lastCol; // find last text col in previous token list, go through list to find braces
                                }
                            }
                            cur.setAnchorColumnNumber(c);
                            cur.setAnchorLineNumber(ln_previous);
                        }
                    }else{
                        continue; // different \end, ignore
                    }
                }else{
                    cur.setAnchorColumnNumber(tkResult.start);
                    cur.setAnchorLineNumber(ln);
                }
                break;
            }
        }else{
            if(tkResult.length>0){
                if(mode== ScanModeSkipInitial){
                    // column start found, so we set anchor
                    cur.setLineNumber(ln);
                    cur.setColumnNumber(tkResult.start);
                    mode= ScanModeInColumn; // we are in a column now
                }
            }
        }
        if(env.name=="tblr"){
            // skip over braces (multi line cells)
            if(tkResult.type==Token::braces && tkResult.subtype==Token::none){
                ignoreUntilColumn=tkResult.start+tkResult.length;
            }
        }
        // when at end of line, go for next line
        if(i==tl.size()-1){
            // copy to previous tokenlist, unless empty
            if(!tl.isEmpty()){
                tl_prev=tl;
                ln_previous=ln;
            }
            // no column separator found, go for next line
            i=-1;
            ++ln;
            col=0; // set to min value
            ignoreUntilColumn=-1; // reset ignore column
            QDocumentLineHandle *dlh=doc->line(ln).handle();
            dlh->lockForRead();
            tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
            dlh->unlock();
        }
    }
    return tkResult;
}

/*!
 * \brief set cursor to start of next column after tk
 * Jumps over \hline at end of row and any spaces to first character of next column.
 * \param cur
 * \param tk column separator
 * \return
 */
bool LatexTables::findNextColumn(QDocumentCursor &cur, Token &tk)
{
    int ln=cur.anchorLineNumber();
    int col=cur.anchorColumnNumber();
    QDocument *doc=cur.document();
    QDocumentLineHandle *dlh=doc->line(ln).handle();
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int i;
    int j=-1;
    for(i=0;i<tl.size();++i){
        if(tl.at(i)== tk){
            // found token
            j=i;
            break;
        }
    }
    if(j<0){
        // token not found
        return false;
    }
    // now search for next column start
    bool breakLoop=false;
    do{
        for(++i;i<tl.size();++i){
            const Token &tk2=tl.at(i);
            if(tk2.type==Token::command){
                if(tk2.getText()=="\\hline"){
                    // skip over \hline
                    // todo, skip over potential optional argument
                    continue;
                }
                if(tk2.getText()=="\\end"){
                    // end of env
                    // todo: refine
                    return false;
                }
            }
            breakLoop=true;
            cur.setLineNumber(ln);
            cur.setColumnNumber(tk2.start);
            break;
        }
        if(!breakLoop){
            // check next line
            ++ln;
            if(ln>=doc->lineCount()){
                // no next line
                return false;
            }
            dlh=doc->line(ln).handle();
            dlh->lockForRead();
            tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
            dlh->unlock();
            i=-1; // reset token index
        }
    }while(!breakLoop);

    return true;
}
/*!
 * \brief find row in tabular-like environment
 * Start at current cursor position and search for next row break (\\ or \tabularnewline).
 * Skip over \hlines,\\ and alike
 * \param cur
 * \param env
 * \return
 */
LatexTables::NextRowAvailable LatexTables::findRow(QDocumentCursor &cur, Environment env)
{
    int ln=cur.lineNumber();
    const int ln_cur=ln;
    int col=cur.columnNumber();
    // reset anchor point
    QDocument *doc=cur.document();
    TokenList tl;
    do{
        QDocumentLineHandle *dlh=doc->line(ln).handle();
        dlh->lockForRead();
        tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        dlh->unlock();
    }while(tl.isEmpty() && ++ln<doc->lineCount()); // skip empty lines)
    if(tl.isEmpty()){
        // missing closing element
        return RowNotAvailable;
    }
    enum ScanMode {ScanModeSkipInitial,ScanModeSkipNewLine,ScanModeInRow};
    ScanMode mode=ScanModeSkipInitial;
    int ignoreUntilColumn=-1; // special ignore new row cmd in tblr (multi line cells)
    const QStringList skipTokens{"\\\\","\\tabularnewline","\\hline"};
    Token prevTk; // previous token, used for end of env detection
    int prevLn=-1;
    for(int i=0;i<tl.size();++i){
        const Token &tk=tl.at(i);
        bool skip=false;
        NextRowAvailable nextRow = RowAvailable;
        if(mode==ScanModeSkipInitial){
            if(tk.start<col && ln==ln_cur){
                skip=true; // skip tokens before cursor
            }
            if(!skip && tk.type==Token::command){
                const QString cmd=tk.getText();
                int idx= skipTokens.indexOf(cmd);
                skip=idx>=2;
            }
            if(!skip){
                mode= ScanModeInRow; // we are in a row now
                cur.setLineNumber(ln);
                cur.setColumnNumber(i==0 ? 0 : tk.start); // if indented, start at start of line
            }
        }
        if(mode==ScanModeInRow){
            if(env.name=="tblr"){
                // skip over braces (multi line cells)
                if(tk.type==Token::braces && tk.subtype==Token::none){
                    ignoreUntilColumn=tk.start+tk.length;
                }
            }
            if(tk.type==Token::command  && tk.start>=ignoreUntilColumn){
                const QString cmd=tk.getText();
                int idx= skipTokens.indexOf(cmd);
                if(idx>=0){
                    // end of row reached
                    mode= ScanModeSkipNewLine;
                }
                if(checkEndEnv(tl,i,env)){
                    mode= ScanModeSkipNewLine;
                    nextRow= RowNotAvailableLazyNewLine;
                    if(prevLn>-1){
                        cur.setAnchorLineNumber(prevLn);
                        cur.setAnchorColumnNumber(prevTk.start+prevTk.length);
                        return nextRow;
                    }
                }
            }
        }
        if(mode==ScanModeSkipNewLine){
            skip=false;

            if(tk.type==Token::command){
                const QString cmd=tk.getText();
                int idx= skipTokens.indexOf(cmd);
                skip=idx>=0;
                // special treatment \end
                bool endReached=checkEndEnv(tl,i,env);

                if(endReached && i==0){
                    // no token in front, so we select end of line
                    const int len=doc->line(ln-1).length();
                    cur.setAnchorColumnNumber(len);
                    cur.setAnchorLineNumber(ln-1);
                    if(nextRow==RowAvailable) nextRow = RowNotAvailable;
                }
            }
            if(!skip){
                cur.setAnchorLineNumber(ln);
                cur.setAnchorColumnNumber(i==0 ? 0 : tk.start); // if indented, start at start of line
                return nextRow; // row found
            }
        }
        if(prevLn==ln){
            if(tk.start+tk.length>prevTk.start+prevTk.length){
                // token is further than previous token, so we update
                prevTk=tk;
            }
        }else{
            prevTk=tk;
        }
        prevLn=ln;
        // when at end of line, go for next line
        if(i==tl.size()-1){
            i=-1;
            ++ln;
            ignoreUntilColumn=-1; // reset ignore column
            QDocumentLineHandle *dlh=doc->line(ln).handle();
            dlh->lockForRead();
            tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
            dlh->unlock();
        }
    }
    return RowNotAvailable;
}
/*!
 * \brief check whether the end of the environment is reached
 * \param tl
 * \param pos
 * \param env
 * \return
 */
bool LatexTables::checkEndEnv(const TokenList &tl, int pos, const Environment &env)
{
    if(pos+2>=tl.size()){
        // no next token, so no end of env
        return false;
    }
    const QString cmd= tl.at(pos).getText();
    if(cmd=="\\end"){
        // check for matchin env name
        const Token &nextTk=tl.at(pos+1);
        if(nextTk.subtype==Token::env && nextTk.getInnerText()==env.name){
            return true;
        }
    }
    return false;
}

/*!
 * \brief get current column in which the cursor is placed
 * The position is determined by number of & after last row break (\\).
 * \param cur current cursor position
 * \return current column
 */
int LatexTables::getColumn(const QDocumentCursor &cur,const Environment env)
{
    const int ln=cur.lineNumber();
    const int col=cur.columnNumber();
    int resultColumn=env.excessCol; // starting column from previous line, generated by syntax checker
    QDocument *doc=cur.document();
    QDocumentLineHandle *dlh=doc->line(ln).handle();
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int ignoreUntilColumn=-1; // special ignore new row cmd in tblr (multi line cells)
    for(int i=0;i<tl.size();++i){
        const Token &tk=tl.at(i);
        if(tk.start>=col) break;
        if(tk.type==Token::command){
            const QString cmd=tk.getText();
            if(cmd=="&"){
                ++resultColumn;
            }
            const QStringList tokens{"\\\\","\\tabularnewline"};
            if(tokens.contains(cmd) && tk.start>=ignoreUntilColumn){
                resultColumn=0; // reset column count, new row
                if(tk.start+tk.length>col){
                    //cursor is within the row break command
                    // so we ddeclare invalid (-1)
                    resultColumn=-1;
                    break;
                }
            }
        }
        if(env.name=="tblr"){
            // skip over braces (multi line cells)
            if(tk.type==Token::braces && tk.subtype==Token::none){
                ignoreUntilColumn=tk.start+tk.length;
            }
        }
    }
    return resultColumn;
}

QString LatexTables::getDef(QDocumentCursor &cur)
{
	QDocumentCursor c(cur);
	int result = findNextToken(c, QStringList(), false, true);
	if (result != -2) return QString();
    QString line = getTableText(cur);
	QString opt;
	int pos = line.indexOf("\\begin");
	if (pos > -1) {
		QStringList values;
		QList<int> starts;
        resolveCommandOptions(line, pos, values, &starts);
		QString env = values.takeFirst();
		pos = starts.takeFirst();
		if (!env.startsWith("{") || !env.endsWith("}")) return QString();
		env = env.mid(1);
		env.chop(1);
		// special treatment for tabu/longtabu
		if ((env == "tabu" || env == "longtabu") && values.count() < 2) {
			int startExtra = pos + env.length() + 2;
			int endExtra = line.indexOf("{", startExtra);
			if (endExtra >= 0 && endExtra > startExtra) {
				QString textHelper = line;
				textHelper.remove(startExtra, endExtra - startExtra); // remove to/spread definition
                resolveCommandOptions(textHelper, pos, values, &starts);
				for (int i = 1; i < starts.count(); i++) {
					starts[i] += endExtra - startExtra;
				}
			}
		}
		int numberOfOptions = -1;
		if (tabularNames.contains(env)) numberOfOptions = 0;
		if (tabularNamesWithOneOption.contains(env)) numberOfOptions = 1;
		if (numberOfOptions >= 0) {
			while (!values.isEmpty()) {
				opt = values.takeFirst();
				pos = starts.takeFirst();
				if (opt.startsWith("[") && opt.endsWith("]")) continue;
				if (numberOfOptions > 0) {
					numberOfOptions--;
					continue;
				}
				if (!opt.startsWith("{") || !opt.endsWith("}")) return QString();
				opt = opt.mid(1);
				opt.chop(1);
				cur.moveTo(c.lineNumber(), pos + 1);
				cur.movePosition(opt.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
                break;
			}
		}
	}
    // in case of colspec, refine further
    if(opt.contains("colspec")){
        QRegularExpression re{"(colspec\\s*[=]\\s*\\{)(.*)\\}"};
        QRegularExpressionMatch match = re.match(opt);
        if (match.hasMatch()) {
            int offset=match.capturedStart(2);
            QString matched = match.captured(2);
            QString prefix=opt.left(offset);
            opt=handleColSpec(opt);
            // handle cursor selection more precisely in case of multiline arguments
            const int posColspec=line.indexOf("colspec");
            QString pre=line.left(posColspec);
            int ln=c.lineNumber();
            if(pre.contains("\n")){
                //adapt ln and offset for multiline argument
                ln+=pre.count("\n");
                int lastNewline=prefix.lastIndexOf("\n");
                offset=offset-pos-lastNewline-2;
            }
            cur.moveTo(ln, pos+1+offset);
            cur.movePosition(opt.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
        }
    }
	return opt;
}

Token LatexTables::getDef(TokenList &tl, Environment env,int &ln,int &nextLine, int &nextCol, QDocument *doc)
{
    int k=-1;
    for(int i=tl.size()-1;i>0;--i){
        if(tl.at(i).type==Token::beginEnv && tl.at(i).getInnerText()==env.name){
            k=i;
            break;
        }
    }
    if(k<0){
        // no begin found
        return Token();
    }
    // find colDef if present
    Token tkColDef;
    QString def;

    if(env.name=="tabu"||env.name=="longtabu"){
        Token tk=tl.value(k+1);
        def=tk.getText();
        if(def=="to" || def=="spread"){
            def="";
            for(k=k+3;k<tl.size();++k){
                if(tl[k].type==Token::braces){
                    tkColDef=tl[k];
                    def=tkColDef.getInnerText();
                    nextLine=ln;
                    nextCol=tkColDef.start+tkColDef.length;
                    break;
                }
            }
        }else{
            def=tk.getInnerText();
            nextLine=ln;
            nextCol=tk.start+tk.length;
            ++k;
            tkColDef=tk;
        }
    }else{
        if(env.name=="tblr"){
            TokenList result=Parsing::getArgTL(tl,Token::colDef);
            if(!result.isEmpty()){
                if(result.at(0).type==Token::braces){
                    def=result.at(0).getInnerText();
                    tkColDef=result.at(0);
                    nextLine=ln;
                    nextCol=tkColDef.start+tkColDef.length;
                }
                if(def.isEmpty() /*multilline*/ || def.contains(',')|| def.contains('=')){
                    // new interface
                    for(int i=0;i<result.size();++i){
                        const Token &tk=result.at(i);
                        if(tk.type==Token::word && tk.getText()=="colspec"){
                            // colspec found
                            ++i;
                            if(i<result.size() && result.at(i).length==1 && result.at(i).getText()=="="){
                                ++i;
                                if(i<result.size() && result.at(i).type==Token::braces){

                                    tkColDef=result.at(i);
                                    if(def.isEmpty()){
                                        // multiline handling
                                        ln=doc->indexOf(tkColDef.dlh,ln);
                                        i=result.size()-1;
                                        nextLine=doc->indexOf(result.at(i).dlh,ln);
                                        nextCol=result.at(i).start+result.at(i).length;
                                    }
                                    def=tkColDef.getInnerText();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }else{
            // try simple token analysis
            Token tk;

            for(k=k+1;k<tl.size();++k){
                if(tl[k].subtype==Token::colDef){
                    tk=tl[k];
                    def=tk.getInnerText();
                    nextLine=ln;
                    nextCol=tk.start+tk.length;
                    tkColDef=tk;
                    break;
                }
            }
        }
    }
    return tkColDef;
}

// check whether the cursor is inside a table environemnt
bool LatexTables::inTableEnv(QDocumentCursor &cur)
{
    LatexDocument *doc=dynamic_cast<LatexDocument*>(cur.document());
    StackEnvironment stackEnv;
    doc->getEnv(cur.lineNumber(),stackEnv);
    int i=LatexTables::inTableEnv(stackEnv);
    if (i<0) return false;
    return true;
}

int LatexTables::inTableEnv(StackEnvironment &stackEnv)
{
    for(int i=stackEnv.size()-1;i>0;--i){
        Environment env=stackEnv.at(i);
        if(tabularNames.contains(env.name) || tabularNamesWithOneOption.contains(env.name)){
            return i;
        }
    }
    return -1;
}

// return number of columns a \multicolumn command spans (number in first braces)
// optionally string pointers may be passed to obtain alignment and the text
int LatexTables::getNumOfColsInMultiColumn(const QString &str, QString *outAlignment, QString *outText)
{
	//return the number of columns in mulitcolumn command
	QStringList values;
	QString zw = str.trimmed();
    resolveCommandOptions(zw, 0, values);
	if (values.length() != 3) return -1;

    if (outAlignment) *outAlignment = removeOptionBrackets(values.at(1));
    if (outText) *outText = removeOptionBrackets(values.at(2));

	zw = values.takeFirst();
	if (zw.startsWith("{") && zw.endsWith("}")) {
		zw.chop(1);
		zw = zw.mid(1);
		bool ok;
		int col = zw.toInt(&ok);
		if (ok) return col;
	}
	return -1;
}

/*!
 * \brief add/remove \hline in tables
 * Works only on complete table
 * \param c
 * \param env
 * \param remove
 */
void LatexTables::addHLine(QDocumentCursor &c, const Environment &env, const bool remove)
{
    QDocumentLineHandle *dlh=env.dlh;
    QDocument *doc=dlh->document();
    int ln = doc->indexOf(dlh,c.lineNumber());
    dlh->lockForRead();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    dlh->unlock();
    int nextLine,nextCol;
    Token tkColDef=getDef(tl,env,ln,nextLine,nextCol,doc);
    // set cursor to start of first row
    QDocumentCursor cur(doc,nextLine,nextCol);
    cur.beginEditBlock();
    // find row
    for(;;){
        enum NextRowAvailable cont=findRow(cur,env);
        QString text = cur.selectedText();

        static const QRegularExpression re("(\\s*\\\\hline[ \t]*)$");
        QRegularExpressionMatch match = re.match(text);
        if (match.hasMatch()) {
            text.remove(match.capturedStart(),match.capturedLength(1));
        }
        if(!remove) {
            QString newToken=" \\hline";
            int pos=-1;
            const QStringList tokens{"\\\\","\\tabularnewline"};
            for(const QString &token:tokens){
                pos = text.lastIndexOf(token);
                if (pos >= 0){
                    pos += token.length(); // insert after token
                    break;
                }
            }
            if(pos<0) pos= text.length(); // no row break found, so insert at end
            text.insert(pos,newToken);
        }
        cur.insertText(text,true);
        if(cont != RowAvailable) break; // no next row
        int row=cur.anchorLineNumber();
        int col=cur.anchorColumnNumber();
        cur.setLineNumber(row);
        cur.setColumnNumber(col);
    }
    cur.endEditBlock();
}

QStringList LatexTables::splitColDef(QString def)
{
	QStringList result;
	bool inDef = false;
	bool inAt = false;
	bool inMultiplier = false;
	bool inMultiplied = false;
	bool appendDef = false;
	int multiplier = 0;
	QString multiplier_str;
	QString before_multiplier_str;
	int curl = 0;
	int sqrBracket = 0;
	QString col;
	for (int i = 0; i < def.length(); i++) {
		QChar ch = def.at(i);
		if (ch == '*') {
			if (curl == 0) {
				inMultiplier = true;
				multiplier_str.clear();
				multiplier = 0;
				before_multiplier_str = col;
				continue;
			}
		}
		if (!inMultiplied && !inMultiplier)
			col.append(ch);
		if (ch == '}') {
			curl--;
			if (curl == 0) {
				if (appendDef) {
					appendDef = false;
					result << col;
					col.clear();
				}
				if (inDef)
					inDef = false;
				if (inAt)
					inAt = false;
				if (inMultiplied) {
					QStringList helper = splitColDef(multiplier_str);
					inMultiplied = false;
					int zw = result.size();

					for (int k = 0; k < multiplier; k++)
						result << helper;

					if (!col.isEmpty() && result.size() > zw) {
						result[zw] = col + result[zw];
						col.clear();
					}
					before_multiplier_str.clear();
					multiplier = 0;
					multiplier_str.clear();
				}
				if (inMultiplier) {
					bool ok;
					multiplier = multiplier_str.toInt(&ok);
					if (ok) {
						inMultiplied = true;
					} else {
						multiplier = 0;
					}
					multiplier_str.clear();
					inMultiplier = false;
				}
			}
		}
		if ((inMultiplier || inMultiplied) && curl > 0) {
			multiplier_str.append(ch);
		}
		if (ch == '<' || ch == '>')
			inDef = true;
		if (ch == '{')
			curl++;
		if (inMultiplier && curl == 0) { // multiplier not in braces
			multiplier_str.append(ch);
			bool ok;
			multiplier = multiplier_str.toInt(&ok);
			if (ok) {
				inMultiplied = true;
			} else {
				multiplier = 0;
			}
			multiplier_str.clear();
			inMultiplier = false;
		}
		if (ch == 's' || ch == 'S') {

		}
		if (ch == '[')
			sqrBracket++;
		if (ch == ']')
			sqrBracket--;
		if ((ch.isLetter() || ch == ']') && !inAt && !inDef && curl == 0 && sqrBracket == 0) {
            const QString colTyes_with_optional_args = "spbmVXQS";
            if (colTyes_with_optional_args.contains(ch) && i + 1 < def.length() && def.at(i + 1) == '[')
				continue;
            if ((i + 1 < def.length()) && def.at(i + 1) == '{' )  {
				appendDef = true;
			} else {
				result << col;
				col.clear();
			}
		}



	}
	if (!result.isEmpty())
		result.last().append(col);
	return result;
}

// removes an @{} sequence form colDef, removes vertical lines '|', removes parameters in curly and square brackets
void LatexTables::simplifyColDefs(QStringList &colDefs)
{
	for (int i = 0; i < colDefs.count(); i++) {
		QString colDef = colDefs.at(i);
		colDef.remove('|');
		if (colDef.startsWith('>')) {
			if (colDef.at(1) == '{') {
				int start = 1;
				int cb = findClosingBracket(colDef, start);
				if (cb >= 0 && colDef.at(cb) == '}' && cb + 1 < colDef.length()) colDef = colDef.mid(cb + 1);
				else colDef = "l"; // fall back
			} else {
				colDef = "l"; // fall back
			}
		}
		if (colDef.startsWith('@')) {
			if (colDef.at(1) == '{') {
				int start = 1;
				int cb = findClosingBracket(colDef, start);
				if (cb >= 0 && colDef.at(cb) == '}' && cb + 1 < colDef.length()) colDef = colDef.mid(cb + 1);
				else colDef = "l"; // fall back
			} else {
				colDef = "l"; // fall back
			}
		}
		if (colDef.length() >= 2 && colDef.at(1) == '{') {
			colDef = colDef.at(0);
		}
		if (colDef.length() >= 2 && colDef.at(1) == '[') {
			colDef = colDef.at(0);
		}
		if (colDef.length() >= 2 && colDef.at(1) == '<') {
			colDef = colDef.at(0);
		}
		colDefs.replace(i, colDef);
	}
}

void LatexTables::executeScript(QString script, LatexEditorView *edView)
{
	scriptengine eng;
	eng.setEditorView(edView);
	eng.setScript(script);
	eng.run();
}

void LatexTables::generateTableFromTemplate(LatexEditorView *edView, QString templateFileName, QString def, QList<QStringList> table, QString env,QString width)
{
	//read in js template which generates the tabular code
	QFile file(templateFileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream stream(&file);
	QString templateText;
	templateText = stream.readAll();
	//env
	QString envDef = "var env=\"" + env + "\"\n";
	//tabular column definition
	QString templateDef = "var def=\"" + def + "\"\n";
    // width def (only tabu at the moment)
    QString widthDef= "var widthDef=\""+width+ "\"\n";
    widthDef.replace("\\", "\\\\");
	//tabular column definition, split
	QString templateDefSplit = "var defSplit=[";
	QStringList lst = splitColDef(def);
	templateDefSplit += "\"" + lst.join("\",\"") + "\"";
	templateDefSplit += "]\n";
	//tabular content as js array
	QString tableDef = "var tab=[\n";
	for (int i = 0; i < table.size(); i++) {
		QStringList lst = table.at(i);
		QStringList::iterator it;
        for (it = lst.begin(); it != lst.end(); ++it) {
			QString str = *it;
			str.replace("\\", "\\\\");
			str.replace("\"", "\\\"");
			str.replace("\n", "\\n");
			str.replace("\t", "\\t");
			*it = str;
		}
		tableDef += "[\"" + lst.join("\",\"") + "\"]";
		if (i < table.size() - 1)
			tableDef += ",\n";
	}
	tableDef += "]\n";
	//join js parts
	templateText.prepend(tableDef);
    templateText.prepend(widthDef);
	templateText.prepend(envDef);
	templateText.prepend(templateDefSplit);
	templateText.prepend(templateDef);
	//generate tabular in editor
	executeScript(templateText, edView);
}

QString LatexTables::getSimplifiedDef(QDocumentCursor &cur)
{
	QString def = getDef(cur);
	QStringList l_defs = splitColDef(def);
	def = l_defs.join("");
	def.remove('|');
	return def;
}

QString LatexTables::getTableText(QDocumentCursor &cur)
{
	int result = findNextToken(cur, QStringList(), false, true);
	if (result != -2) return QString();
	QString line = cur.line().text();
	int i = line.indexOf("\\begin");
	if (i >= 0)
		cur.setColumnNumber(i);
	result = findNextToken(cur, QStringList(), true, false);
	if (result != -2) return QString();
	line = cur.line().text();
    QRegularExpression rx("\\\\end\\{.*\\}");
    QRegularExpressionMatch rxm=rx.match(line);
    i = rxm.capturedStart();
	if (i >= 0)
        cur.setColumnNumber(i + rxm.capturedLength(0), QDocumentCursor::KeepAnchor);
	QString res = cur.selectedText();
	return res;
}

void LatexTables::alignTableCols(QDocumentCursor &cur)
{
	QString text = getTableText(cur);
	if (!cur.hasSelection()) return;
	QString indentation = cur.selectionStart().line().indentation();

	// split off \begin and \end parts
	int index = text.indexOf("\\begin{") + 6;
	int cellsStart;
	QList<CommandArgument> args = getCommandOptions(text, index, &cellsStart);
	if (args.count() < 1) return;
	QString tableType = args.at(0).value;
	// special treatment for tabu/longtabu
	if ((tableType == "tabu" || tableType == "longtabu") && args.count() == 1) { //special treatment for tabu to linewidth etc.
		int startExtra = cellsStart;
		int endExtra = text.indexOf("{", startExtra);
		if (endExtra >= 0 && endExtra > startExtra) {
			QString textHelper = text;
			textHelper.remove(startExtra, endExtra - startExtra); // remove to/spread definition
			args = getCommandOptions(textHelper, index, &cellsStart);
			cellsStart += endExtra - startExtra;
		}
	}

	QString alignment;
    if (args.count() < 3 && mathTables.contains(tableType)) {
		alignment = "l"; // may be more. But thats caught by the fallback (filling with additional "l").
	}
	// assume alignment in second arg except for the following environments (which have it in the third one)
    else if (tabularNamesWithOneOption.contains(tableType)) {
        if (args.count() < 3) alignment = ""; // incomplete definition -> fall back to defaults
        else alignment = args.at(2).value;
    } else if (args.count() > 1 && tabularNames.contains(tableType)) {
        int p=1;
        while(args.at(p).isOptional && args.count()>(p+1)) ++p; // skip optional arguments
        alignment = args.at(p).value;
    } else return; // not a registered table environment
    alignment=handleColSpec(alignment);
	int cellsEnd = text.indexOf("\\end{" + tableType);
	if (cellsEnd < 0) return;
	QString beginPart = text.left(cellsStart);
	QString endPart = text.mid(cellsEnd);

	LatexTableModel ltm;
	ltm.setContent(text.mid(cellsStart, cellsEnd - cellsStart));

	QStringList l_defs = splitColDef(alignment);
	simplifyColDefs(l_defs);
	bool forceNewline = environmentsRequiringTrailingLineBreak.contains(tableType);
    QString tab="\t";
    ConfigManagerInterface *cfg = ConfigManager::getInstance();
    if (cfg) {
        if(cfg->getOption("Editor/Indent with Spaces").toBool()){
            int tabs=cfg->getOption("Editor/TabStop",4).toInt();
            tab.fill(' ',tabs);
        }
    }
    QStringList content = ltm.getAlignedLines(l_defs, tab, forceNewline);

	QString result = beginPart + '\n';
	for (int i = 0; i < content.count(); i++) {
		result.append(indentation + content.at(i) + '\n');
	}
    result.append(indentation + endPart);
    cur.replaceSelectedText(result);
}

/*!
 * \brief if preamble uses colspec syntax, extract alignment, otherwise return original text
 * \param opt
 * \return refined preamble with alignment info only
 */
QString LatexTables::handleColSpec(QString opt)
{
    // in case of colspec, refine further
    if(opt.contains("colspec")){
        QRegularExpression re{"(colspec\\s*[=]\\s*)(.*)"};
        QRegularExpressionMatch match = re.match(opt);
        if (match.hasMatch()) {
            opt = match.captured(2);
            // braces are allowed in colspec
            // go through opening/closing braces and find potential comma, that splits colDef
            // see #3831
            int brace=0;
            int squareBracket=0;
            int i=0;
            for(;i<opt.length();++i){
                if(opt.at(i)=='}') --brace;
                if(opt.at(i)=='{') ++brace;
                if(opt.at(i)=='[') ++squareBracket;
                if(opt.at(i)==']') --squareBracket;
                if(opt.at(i)==',' && brace==0 && squareBracket==0) break;
            }
            opt=opt.left(i); // remove rest of coldesfinition
            // cut out braces if present
            if (opt.startsWith("{") && opt.endsWith("}")) {
                opt = opt.mid(1,opt.length()-2);
            }
        }
    }
    return opt;
}

LatexTableModel::LatexTableModel(QObject *parent) : QAbstractTableModel(parent), metaLineCommandPos(0)
{
	ConfigManagerInterface *cfg = ConfigManager::getInstance();
	if (cfg) {
		metaLineCommands = cfg->getOption("TableAutoformat/Special Commands").toString().split(',');
		metaLineCommands.removeAll("");  // make sure there are no empty commands due to double or trailing comma
		metaLineCommandPos = cfg->getOption("TableAutoformat/Special Command Position").toInt();
	}
}

// return the index of the first double backslash ("\\\\") after startCol which is on the same
// brace level as startCol (i.e. ignoring double slash within braces)
int LatexTableModel::findRowBreak(const QString &text, int startCol) const
{
	bool previousIsBackslash = false;
	int braceDepth = 0;
    for(int col=startCol; col < text.length(); ++col) {
        if(text.mid(col,2)=="\\{"){
            ++col;
            continue;
        }
        if(text.mid(col,2)=="\\}"){
            ++col;
            continue;
        }
		switch (text.at(col).toLatin1()) {
		case '{':
			braceDepth++;
			break;
		case '}':
			braceDepth--;
			break;
		case '\\':
			if (braceDepth == 0) {
				if (previousIsBackslash) {
					return col-1;
				} else {
					previousIsBackslash = true;
                    if(text.mid(col,15)=="\\tabularnewline"){
                        return col;
                    }
					continue;
				}
			}
		}
		previousIsBackslash = false;
	}
	return -1;
}

// parses text up to the end of the next line. Returns column after the line in startCol
// return value is 0 in case of error
LatexTableLine *LatexTableModel::parseNextLine(const QString &text, int &startCol)
{
	QString pre;
	QString line;
    QString lineBreakOption{"\\\\"};

	int endCol = findRowBreak(text, startCol);
	if (endCol < 0) {
		line = text.mid(startCol).trimmed();
        //endCol = text.length();
	} else {
		line = text.mid(startCol, endCol - startCol).trimmed();
        if(text.mid(endCol,2)=="\\\\"){
            endCol += 2; // now behind "\\"
        }else{
            endCol += 15;
            lineBreakOption = "\\tabularnewline";
        }
        // check for line break with * (nopagebreak, i.e. \\*)
        if (endCol < text.length() - 1 && text[endCol] == '*') {
            endCol++;
            lineBreakOption += "*";
        }
		// check for line break with option, e.g. \\[1em]
		if (endCol < text.length() - 1 && text[endCol] == '[') {
			int startOpt = endCol;
			int endOpt = findClosingBracket(text, endCol, '[', ']');
			if (endOpt < 0) {
				UtilsUi::txsWarning("Could not parse table code: Missing closing bracket: \\[");
                return nullptr;
			}
            lineBreakOption += text.mid(startOpt, endOpt - startOpt + 1).trimmed();
			endCol = endOpt + 1;
		}
	}
    if(lineBreakOption=="\\\\"){
        lineBreakOption.clear(); // default is used
    }

	// ceck for meta line commands at beginning of line
	bool recheck = true;
    if(line.startsWith("%") && recheck){
        int behind=line.indexOf(QRegularExpression("[\\n\\r]"));
        pre.append(line.left(behind));

        line = line.mid(behind).trimmed();
        recheck = true;
    }

    while (line.startsWith("\\") && recheck) {
		recheck = false;
		foreach (const QString &cmd, metaLineCommands) {
			if (line.startsWith(cmd)) {
				int behind;
				getCommandOptions(line, cmd.length(), &behind);
                if(behind>0 && pre.contains('%')){
                    pre.append('\n');
                }
				pre.append(line.left(behind));

				line = line.mid(behind).trimmed();
				recheck = true;
				break;
			}
		}
	}

	LatexTableLine *ltl = new LatexTableLine(this);
	if (!pre.isEmpty()) ltl->setMetaLine(pre);
    if (!line.isEmpty() || endCol>startCol) ltl->setColLine(line); // allow empty columns
	if (!lineBreakOption.isEmpty()) ltl->setLineBreakOption(lineBreakOption);

    startCol = endCol;
    if(startCol<0){
        startCol=text.length();
    }

	return ltl;
}

// input everything between \begin{} and \end{}
void LatexTableModel::setContent(const QString &text)
{
	int col = 0;
	while (col >= 0 && col < text.length()) {
		LatexTableLine *ltl = parseNextLine(text, col);
		if (!ltl) break;
		lines.append(ltl);
	}

	/*	*** alternative more efficient ansatz ***
	inline int skipWhitespace(const QString &line, int pos=0) {while (pos<line.length()) {if (!line.at(pos).isSpace()) return pos; else pos++;}}

	int len = text.length();
	int pos=skipWhitespace(text);
	int start = pos;
	LatexTableLine *ltl = new LatexTableLine(this);
	bool hasMetaContent = false;
	while (pos < len) {
	if (text.at(pos) == '\\') {
	if (pos < len && text.at(pos+1)  == '\\') {
	ltl->setColStr(text.mid(start, pos-start));
	pos+=2;
	start=pos;
	} else {
	QString cmd;
	int end = getCommand(text, cmd, pos);
	if (metaLineCommands.contains(cmd)) {
	 QStringList args;
	 getCommandOptions(text, end, end);
	 hasMetaContent = true;
	}

	}

	}

	pos = skipWhitespace(pos);
	}
	*/
}

QStringList LatexTableModel::getAlignedLines(const QStringList alignment, const QString &rowIndent, bool forceLineBreakAtEnd) const
{
	QString delim = " & ";
	QVector<QString> cl(lines.count());
	QVector<int> multiColStarts(lines.count());
	for (int i = 0; i < lines.count(); i++) multiColStarts[i] = -1;
	QStringList alignTokens(alignment);

	foreach (LatexTableLine *tl, lines) {
		// fallback to 'l' if more columns are there than specified in alignment
		while (alignTokens.length() < tl->colCount())
			alignTokens.append("l");
	}

	bool oneLinePerCell = ConfigManager::getInstance()->getOption("TableAutoformat/One Line Per Cell").toBool();
	QString colSep = " & ";
	if (oneLinePerCell) colSep = " &\n" + rowIndent;

	int pos = 0;
	for (int col = 0; col < alignTokens.length(); col++) {
		// col width detection
		int width = 0;
		for (int row = 0; row < lines.length(); row++) {
			LatexTableLine *tl = lines.at(row);
			if (col >= tl->colCount()) continue;
			switch (tl->multiColState(col)) {
			case LatexTableLine::MCStart:
				multiColStarts[row] = pos;
				break;
			case LatexTableLine::MCMid:
				break;
			case LatexTableLine::MCEnd: {
				int startCol = tl->multiColStart(col);
				Q_ASSERT(startCol >= 0);
				int w = tl->colWidth(startCol) - (pos - multiColStarts[row]);
				if (width < w) width = w;
			}
			break;
			default:
				int w = tl->colWidth(col);
				if (width < w) width = w;
			}
		}

		// size and append cols
		QChar align = alignTokens.at(col).at(0);
		for (int row = 0; row < lines.length(); row++) {
			LatexTableLine *tl = lines.at(row);
			if (col < tl->colCount()) {
				if (tl->multiColState(col) == LatexTableLine::MCEnd) {
					int startCol = tl->multiColStart(col);
					Q_ASSERT(startCol >= 0);
					cl[row].append(tl->colText(startCol, width + (pos - multiColStarts[row]), tl->multiColAlign(startCol)));
					if (col < alignTokens.length() - 1) cl[row].append(colSep);

					multiColStarts[row] = -1;
				} else if (tl->multiColState(col) == LatexTableLine::MCNone) {
					cl[row].append(tl->colText(col, width, align));
					if (col < alignTokens.length() - 1) cl[row].append(colSep);
				}
			}
		}
		pos += width + delim.length();
	}

	QStringList ret;
	for (int row = 0; row < lines.count(); row++) {
		QString ml = lines.at(row)->toMetaLine();
        QString lbo=lines.at(row)->toLineBreakOption();
        QString lineTerm = lbo.isEmpty() ? " \\\\" : " "+lbo;
		switch (metaLineCommandPos) {
		// keep in sync with options configdialog.ui
		case 0: // Behind line break
			if (!ml.isEmpty()) {
				if (row == 0) {
					ret.append(rowIndent + ml);
				} else {
					ret.last().append(" " + ml);
				}
			}
			if (!cl[row].isEmpty()) ret.append(rowIndent + cl[row] + lineTerm);
			break;
		case 1: // separate line (no indent)
			if (!ml.isEmpty())      ret.append(ml);
			if (!cl[row].isEmpty()) ret.append(rowIndent + cl[row] + lineTerm);
			break;
		case 2: // separate line (indent to first col)
			if (!ml.isEmpty())      ret.append(rowIndent + ml);
			if (!cl[row].isEmpty()) ret.append(rowIndent + cl[row] + lineTerm);
			break;
		default:
            qDebug("Invalid metaLineCommand pos");
		}

	}
	if (!ret.isEmpty() && !forceLineBreakAtEnd) {
		// smart removal of break "\\" at final line:
		// except for cases like "\\ \hline" and empty column
		QString &last = ret.last();
        if (last.endsWith("\\\\")||last.endsWith("\\tabularnewline")) {
            QString zw=trimRight(last.left(last.length() - 2));
            if(!zw.isEmpty())
                last = zw;
		}
	}

	return ret;
}

QVariant LatexTableModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole) return QVariant();
	return lines.at(index.row())->colText(index.column());
}


LatexTableLine::LatexTableLine(QObject *parent) : QObject(parent)
{
}

void LatexTableLine::setColLine(const QString line)
{
	colLine = line;
	int start = 0;
	for (int i = 0; i < line.length(); i++) {
		if (line.at(i) == '&' && (i == 0 || line.at(i - 1) != '\\')) { // real col delimiter
			appendCol(line.mid(start, i - start));
			if (i < line.length()) start = i + 1;
		}
	}
    if (start <= line.length()) appendCol(line.mid(start));
}

QString LatexTableLine::colText(int col, int width, const QChar &alignment)
{
	int spaceLength = width - cols.at(col).length();
	if (alignment.toLower() == 'r') {  // 'R' is used in tabulary
		return QString(spaceLength, ' ') + cols.at(col);
	} else if (alignment.toLower() == 'c') {
		return QString(spaceLength / 2, ' ') + cols.at(col) + QString((spaceLength + 1) / 2, ' ');
	} // else  'l'
	return cols.at(col) + QString(spaceLength, ' ');
}

void LatexTableLine::appendCol(const QString &col)
{
	int pos = col.indexOf("\\multicolumn");
	if (pos >= 0) {
		QString align;
		int colSpan = LatexTables::getNumOfColsInMultiColumn(col, &align);
		QChar al = (align.isEmpty()) ? 'l' : align.at(0);
		if (!QString("lcr").contains(al)) al = 'l'; // fallback
		if (colSpan > 1) {
			cols.append(col.trimmed());
			mcFlag.append(MCStart);
			mcAlign.append(al);
			// inserting dummy rows
			for (int i = 1; i < colSpan - 1; i++) {
				cols.append(QString());
				mcFlag.append(MCMid);
				mcAlign.append(al);
			}
			cols.append(QString());
			mcFlag.append(MCEnd);
			mcAlign.append(al);
		} else {
			// not really a span
			cols.append(col.trimmed());
			mcFlag.append(MCNone);
			mcAlign.append(al);
		}
	} else {
		cols.append(col.trimmed());
		mcFlag.append(MCNone);
		mcAlign.append(QChar());
	}
}

/* TODO
 * - \hline before first line (add/rem col)
*/
