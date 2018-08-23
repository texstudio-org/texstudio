#include "latexparsing.h"
#include "qdocumentline_p.h"
#include "qdocument.h"
#include "latexparser/latexparser.h"
#include "configmanager.h"

/*!
 * This is the new Token-based parser.
 */

namespace Parsing {


//const int RUNAWAYLIMIT = 30; // limit lines to process multi-line arguments in order to prevent processing to the end of document if the argument is unclosed


/*!
 * Realizes the first pass lexing
 * Following functionality is implemented:
 * + separate the the text into words,symbols
 * + assign each symbol/word a basic context like word,command,symbol,open/close brace etc.
 * + set tokenlist as LEXER_RAW_COOKIE on line
 * + remove cookie LEXER_COOKIE (as it is invalid)
 * \param dlh linehandle
 * \return tokenlist
 */
TokenList simpleLexLatexLine(QDocumentLineHandle *dlh)
{
	// dumbed down lexer in order to allow full parallelization and full change of verbatim/non-verbatim later on
	TokenList lexed;
	if (!dlh)
		return lexed;
	dlh->lockForWrite();
	QString s = dlh->text();
	Token present, previous;
	present.type = Token::none;
	present.dlh = dlh;
	present.argLevel = 0;
	QChar verbatimSymbol;
	const QString specialChars = "{([})]";
	int i = 0;
	for (; i < s.length(); i++) {
		QChar c = s.at(i);
		if (!verbatimSymbol.isNull()) {
			if (c == verbatimSymbol) {
				present.length = 1;
				lexed.append(present);
				present.type = Token::none;
				verbatimSymbol = QChar();
				continue;
			}
		}
		if (present.type == Token::command && c == '@') {
			continue; // add @ as letter to command
		}
		if (present.type == Token::command && present.start == i - 1 && (c.isSymbol() || c.isPunct())) {
			// handle \$ etc
			present.length = i - present.start + 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c == '%') {
			if (present.type != Token::none) {
				present.length = i - present.start;
				lexed.append(present);
			}
			present.type = Token::comment;
			present.length = 1;
            present.start = i;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}

		if (specialChars.contains(c) || c.isSpace() || c.isPunct() || c.isSymbol()) {
			//close token
			if (present.type != Token::none) {
				present.length = i - present.start;
				lexed.append(present);
				present.type = Token::none;
			}
		} else {
			if (present.type == Token::none) {
				if (c.isLetter()) {
					present.type = Token::word;
				} else {
					present.type = Token::number;
				}
				present.start = i;
			} else { // separate numbers and text (latex considers \test1 as two tokens ...)
				if (c.isDigit() && present.type != Token::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Token::number;
					continue;
				}
				if (c.isLetter() && present.type == Token::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Token::word;
					continue;
				}
			}
			continue;
		}
		//start new Token
		present.start = i;
		if (c == '\\') {
			present.type = Token::command;
			continue;
		}

		int l = specialChars.indexOf(c);
		if (l > -1 && l < 3) {
			present.type = Token::TokenType(int(Token::openBrace) + l);
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (l > 2) {
			present.type = Token::TokenType(int(Token::closeBrace) + (l - 3));
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c.isSymbol()) {
			present.type = Token::symbol;
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c.isPunct()) {
			present.type = Token::punctuation;
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}

	}
	if (present.type != Token::none) {
		present.length = i - present.start;
		lexed.append(present);
		previous = present;
	}
	dlh->setCookie(QDocumentLine::LEXER_RAW_COOKIE, QVariant::fromValue<TokenList>(lexed));
    dlh->removeCookie(QDocumentLine::LEXER_COOKIE);
	dlh->unlock();
	return lexed;
}


bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const LatexParser &lp)
{
	if (!dlh)
	    return false;
	dlh->lockForWrite();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_RAW_COOKIE).value<TokenList>();
	TokenStack oldRemainder = dlh->getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
	CommandStack oldCommandStack = dlh->getCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
	QString line = dlh->text();
	bool verbatimMode = false;
	int level = 0;
	if (!stack.isEmpty()) {
	    if (stack.top().type == Token::verbatim) {
		verbatimMode = true;
	    } else {
		level = stack.top().level + 1;
	    }
	}
	TokenList lexed;

	QString verbatimSymbol;
	int lastComma = -1;
	int lastEqual = -1e6;
	QString keyName;

	int lineLength=line.length();

	for (int i = 0; i < tl.length(); i++) {
	    Token &tk = tl[i];
	    /* parse tokenlist
	     * check commands (1. syn check)
	     * tie options/arguments to commands
	     * lex otpions (key/val, comma separation,words,single arg,label etc)
	     * => reclassification of arguments
	     */
        if (!verbatimSymbol.isNull()) {
            // handle \verb+ ... +  etc.
            if (tk.type == Token::symbol) {
                QString smb = line.mid(tk.start, 1);
                if (smb == verbatimSymbol) {
                    // stop verbatimSymbol mode
                    verbatimSymbol.clear();
                    continue;
                }
            }
            tk.type = Token::verbatim;
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
            }
            tk.level = level;
            lexed << tk;
            continue;
        }
	    // different handling for verbatimMode (verbatim-env, all content is practically ignored)
        if (verbatimMode) {
            // verbatim handling
            // just look for closing (\end{verbatim})
            if (tk.type != Token::command)
                continue;
            QString cmd = line.mid(tk.start, tk.length);
            if (cmd != "\\end")
                continue;
            if (i + 2 >= tl.length()) // not enough tokens to handle \end{verbatim
                continue;
            Token tk2 = tl.at(i + 1);
            Token tk3 = tl.at(i + 2);
            if (tk2.type == Token::openBrace && tk3.type == Token::word) {
                QString env = line.mid(tk3.start, tk3.length);
                if (lp.possibleCommands["%verbatimEnv"].contains(env)) { // incomplete check if closing correspondents to open !
                    verbatimMode = false;
                    stack.pop();
                } else
                    continue;
            } else
                continue;
        }
	    // non-verbatim handling
	    if (tk.type == Token::comment){
            lineLength=tk.start; // limit linelength to comment start
            break; // stop at comment start
	    }
        // special definition handling, is not interpreted !!
        if(!stack.isEmpty() && stack.top().subtype==Token::definition){
            if(tk.type==Token::openBrace){
                tk.subtype=Token::definition;
                tk.level = level; // push old level on stack in order to restore that level later and to distinguish between arguments and arbitrary braces
                tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention
                stack.push(tk);
                tk.level++;
                lexed << tk;
                level++;
                continue;
            }else{
                if(tk.type==Token::closeBrace){
                    Token tk1=stack.pop();
                    if(!stack.isEmpty() && stack.top().subtype==Token::definition){ // check if more than openBrace/defintion are on the stack, if yes , juts pop it and continue in definition mode
                        tk.subtype=Token::definition;
                        lexed << tk;
                        level=tk1.level; // restore original level
                        continue; // still definition mode
                    }else{
                        stack.push(tk1); // restore stack, so that the following code can handle brace fusion
                    }
                }else{
                    continue; // ignore tokens in definition
                }
            }
        }
        // continue normal operation
	    if (tk.type == Token::command) {
            QString command = line.mid(tk.start, tk.length);
            if (tl.length() > i + 1 && tl.at(i + 1).type == Token::punctuation && line.mid(tl.at(i + 1).start, 1) == "*") {
                // add * to command
                i++;
                command.append("*");
            }
            if (command == "\\verb" || command == "\\verb*") {
                // special treament for verb
                if (i + 1 < tl.length() && tl.at(i + 1).type == Token::symbol && tl.at(i + 1).start == tk.start + tk.length) {
                    // well formed \verb
                    verbatimSymbol = line.mid(tl.at(i + 1).start, 1);
                    i++;
                }
                // not valid \verb
                if (!stack.isEmpty()) {
                    tk.subtype = stack.top().subtype;
                    if (tk.subtype == Token::keyValArg && lastEqual > -1) {
                        tk.subtype = Token::keyVal_val;
                    }
                }
                tk.level = level;
                lexed << tk;

                continue;
            } else {
                if (!stack.isEmpty()) {
                    tk.subtype = stack.top().subtype;
                    if (tk.subtype == Token::keyValArg && lastEqual > -1) {
                        tk.subtype = Token::keyVal_val;
                        if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                            CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                            tk.subtype = cd.argTypes.value(0, Token::keyVal_val);
                        }
                    }

                }
                tk.level = level;
                if (!commandStack.isEmpty() && commandStack.top().level == level) {
                    //possible command argument without brackets
                    CommandDescription &cd = commandStack.top();
                    if (cd.args > 0) {
                        cd.optionalArgs = 0; // no optional arguments after mandatory
                        cd.bracketArgs = 0;
                        cd.args--;
                        tk.subtype = cd.argTypes.takeFirst();
                        tk.level++;
                    }
                    if (cd.args <= 0) {
                        // unknown arg, stop handling this command
                        commandStack.pop();
                    }
                }
                if (lp.commandDefs.contains(command)) {
                    CommandDescription cd = lp.commandDefs.value(command);
                    cd.level = level;
                    if(cd.bracketCommand){
                        //command like \left
                        if (tl.length() > i + 1 && tl.at(i + 1).length == 1 && tl.at(i + 1).start==tk.start+tk.length) {
                            // add [( etc to command
                            Token tk2=tl.at(i + 1);
                            if(Token::tkOpen().contains(tk2.type)||Token::tkClose().contains(tk2.type)){
                                tk.optionalCommandName=command;
                                command.append(line.mid(tk2.start, 1));
                                tk.length++;
                                i++;
                            }
                        }

                    }
                    if ((cd.args > 0 || cd.optionalArgs > 0 || cd.bracketArgs > 0 ) && tk.subtype != Token::def) { // don't interpret commands in defintion (\newcommand{def})
                        cd.optionalCommandName=command;
                        commandStack.push(cd);
                    }
                } else {
                    tk.type = Token::commandUnknown;
                }
                lexed << tk;
            }
            continue;
        }
        if (Token::tkOpen().contains(tk.type)) {
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                CommandDescription &cd = commandStack.top();
                if (tk.type == Token::openBrace) {
                    if (cd.args > 0) {
                        //cd.optionalArgs=0; // argument order (option/mandatory) is not checked, e.g \newcommad{cmd}[argNumber][default]{definition}
                        cd.args--;
                        tk.subtype = cd.argTypes.takeFirst();
                    } else {
                        // ignore
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openSquare) {
                    if (cd.optionalArgs > 0) {
                        cd.optionalArgs--;
                        tk.subtype = cd.optTypes.takeFirst();
                    } else {
                        // unexpected optional argument
                        // ignore
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openBracket) {
                    if (cd.bracketArgs > 0) {
                        cd.bracketArgs--;
                        tk.subtype = cd.bracketTypes.takeFirst();
                    } else {
                        lexed << tk;
                        continue;
                    }
                }

                tk.level = level; // push old level on stack in order to restore that level later and to distinguish between arguments and arbitrary braces
                tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention
                stack.push(tk);
                tk.level++;
                lexed << tk;
                level++;
            }else{
                if(tk.type==Token::openBrace){ // check braces within arguments, not brackets/squareBrackets
                    //level++; // not an argument
                    tk.level = level;
                    tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention, needs to be >0 as otherwise closing barces are misinterpreted
                    if (!stack.isEmpty()) {
                        tk.subtype = stack.top().subtype;
                    }
                    stack.push(tk);
                    lexed << tk;
                }
            }
            continue;
        }
	    if (Token::tkClose().contains(tk.type)) {
		// special treament for brackets as they don't have any syntaxtical meaning except with some commands
            if (tk.type == Token::closeBracket ) {
                if (stack.isEmpty())
                    continue;
                if (stack.top().type != Token::opposite(tk.type))
                    continue; //closing bracket is ignored if no correct open is present
            }
            if (!stack.isEmpty() && stack.top().type == Token::opposite(tk.type)) {
                Token tk1 = stack.pop();

                if (Token::tkCommalist().contains(tk1.subtype)) {
                    lastComma = -1;
                }
                if (tk1.subtype == Token::keyValArg) {
                    lastComma = -1;
                    if (lastEqual > -1e6) {
                        if (!lexed.isEmpty() && lexed.last().type == Token::keyVal_key) {
                            // no value added, add empty key_val
                            Token tk0;
                            tk0.start = tk.start;
                            tk0.length = 0;
                            tk0.dlh = dlh;
                            tk0.type = Token::keyVal_val;
                            tk0.subtype = Token::keyVal_val;
                            tk0.level = level;
                            lexed << tk0;
                        }
                        level = lastEqual;
                    }
                    lastEqual = -1e6;
                }
                if (tk1.dlh == dlh) { // same line
                    int j = lexed.length() - 1;
                    while (j >= 0 && lexed.at(j).start > tk1.start)
                        j--;
                    bool forceContinue=false;
                    if (j >= 0 && lexed.at(j).start == tk1.start) {
                        if (Token::tkSingleArg().contains(tk1.subtype) || tk1.subtype >= Token::specialArg) { // all special args are assumed single word arguments
                            // join all args for intended single word argument
                            // first remove all argument tokens
                            for (int k = j + 1; k < lexed.length();) {
                                lexed.removeAt(k);
                            }
                            Token tk2;
                            tk2.dlh = dlh;
                            tk2.start = lexed[j].start + 1;
                            tk2.length = tk.start - lexed[j].start - 1;
                            tk2.type = tk1.subtype;
                            tk2.level = level;
                            lexed << tk2;
                            if (tk2.type == Token::beginEnv) {
                                // special treatment for \begin ...
                                QString env = line.mid(tk2.start, tk2.length);
                                // special treatment for verbatim
                                if (lp.possibleCommands["%verbatimEnv"].contains(env)) {
                                    verbatimMode = true;
                                    Token tk3;
                                    tk3.dlh = dlh;
                                    tk3.level = level - 1;
                                    tk3.type = Token::verbatim;
                                    stack.push(tk3);
                                } else { // only care for further arguments if not in verbatim mode (see minted)
                                    CommandDescription cd = lp.commandDefs.value("\\begin{" + env + "}", CommandDescription());
                                    if ((cd.args > 1)||(cd.args==1 && cd.optionalArgs>0)) {
                                        cd.args--;
                                        cd.argTypes.takeFirst();
                                        cd.optionalCommandName="\\begin{" + env + "}";
                                        commandStack.push(cd);
                                        forceContinue=true;
                                    }
                                }
                            }
                        }
                        lexed[j].length = tk.start - tk1.start + 1;
                        lexed[j].type = Token::closed(tk.type);
                        level=tk1.level; // restore original level
                        // remove commands from commandstack with higher level, as they can't have any valid arguments anymore
                        while (!commandStack.isEmpty() && commandStack.top().level > level) {
                            commandStack.pop();
                        }
                        if(forceContinue){
                            forceContinue=false;
                            continue;
                        }
                    } else { // opening not found, whyever (should not happen)
                        //level--;
                        tk.level = level;
                        lexed.append(tk);
                    }
                } else {
                    // closing brace in later line ...
                    tk.level = level;
                    tk.subtype=tk1.subtype;
                    level=tk1.level; // restore original level
                    lexed.append(tk);
                }
                if (!commandStack.isEmpty() && commandStack.top().level == level) {
                    CommandDescription &cd = commandStack.top();
                    if (cd.args <= 0 && cd.bracketArgs <= 0) {
                        // all args handled, stop handling this command
                        commandStack.pop();
                    }
                }
                continue;
            }
            // ignore unopened close
        }
        if (!stack.isEmpty() && stack.top().level == level - 1 && Token::tkCommalist().contains(stack.top().subtype)) {
            // handle commalist
            if (tk.type == Token::punctuation && line.mid(tk.start, 1) == ",") {
                lastComma = -1;
                continue;
            }
            if (lastComma < 0) {
                tk.level = level;
                tk.type = stack.top().subtype;
                lexed << tk;
                lastComma = lexed.length() - 1;
            } else {
                lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
            }
            continue;
        }
        if (!stack.isEmpty() && stack.top().level < level && stack.top().subtype == Token::keyValArg) {
            // handle keyval
            if (tk.type == Token::punctuation && line.mid(tk.start, 1) == ",") {
                lastComma = -1;
                if (lastEqual > -1e6) {
                    if (!lexed.isEmpty() && lexed.last().type == Token::keyVal_key) {
                        // no value added, add empty key_val
                        Token tk0;
                        tk0.start = tk.start;
                        tk0.length = 0;
                        tk0.type = Token::keyVal_val;
                        tk0.subtype = Token::keyVal_val;
                        tk0.level = level;
                        lexed << tk0;
                    }
                    level = lastEqual;
                }
                lastEqual = -1e6;
                continue;
            }
            if (tk.type == Token::symbol && line.mid(tk.start, 1) == "=") {
                //lastComma = -1;
                lastEqual = level;
                level++;
                continue;
            }
            if (lastComma < 0 ) {
                tk.level = level;
                tk.type = Token::keyVal_key;
                if(!commandStack.isEmpty()){
                    CommandDescription &cd = commandStack.top();
                    tk.optionalCommandName=cd.optionalCommandName;
                }
                keyName = line.mid(tk.start, tk.length);
                lexed << tk;
                lastComma = lexed.length() - 1;
            } else {
                if (lastEqual <= -1e6) {
                    lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
                    keyName= line.mid(tk.start, lexed[lastComma].length);
                } else {
                    tk.level = level;
                    tk.subtype = Token::keyVal_val;
                    // special treatment for "-"
                    if (tk.type == Token::punctuation && line.mid(tk.start, 1) == "-") {
                        if(lastComma==(lexed.length()-2)){
                            if((lexed[lastComma+1].start+lexed[lastComma+1].length==tk.start)&&lexed[lastComma+1].type==Token::word){
                                // "-" directly follows previous word
                                lexed[lastComma+1].length++;
                                continue;
                            }
                        }
                    }
                    // special treatment for word if is adjacent to "-"
                    if (tk.type == Token::word) {
                        if(lastComma==(lexed.length()-2)){
                            if((lexed[lastComma+1].start+lexed[lastComma+1].length==tk.start)&&lexed[lastComma+1].type==Token::word && line.mid(tk.start-1,1)=="-"){
                                Token tk2=lexed.takeLast();
                                tk2.length+=tk.length;
                                tk=tk2; // allow handling by the code below
                            }
                        }
                    }
                    if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                        CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                        tk.type = cd.argTypes.value(0, Token::keyVal_val); // only types can be set in key_val as they need to be recognized later
                        if(!lexed.isEmpty() && lexed.last().type==tk.type && lexed.last().subtype==tk.subtype){
                            lexed.last().length=tk.start+tk.length-lexed.last().start;
                            continue;
                        }
                    }
                    lexed << tk;
                }
            }
            continue;
        }
        if (tk.type == Token::symbol) {
            // special treatment for $ as mathstart
            if (line.mid(tk.start, 2) == "$$") {
                tk.type = Token::command;
                tk.level = level;
                tk.length=2;
                lexed << tk;
                i++;
                continue;
            }
            if (line.mid(tk.start, 1) == "$") {
                tk.type = Token::command;
                tk.level = level;
                if(i+1<tl.length()){
                    if(line.mid(tk.start,2)=="$$"){
                        i=i+1;
                        tk.length=2;
                    }
                }
                lexed << tk;
                continue;
            }
        }
        if (tk.type == Token::punctuation) {
            if (line.mid(tk.start, 1) == "&") {
                // special treatment for & in tabular
                tk.type = Token::command;
                tk.level = level;
                lexed << tk;
                continue;
            }
            if (line.mid(tk.start, 1) == "\"") {
                // special treatment for " (used for umlauts in german)
                if (i + 1 < tl.length()) {
                    Token tk2 = tl.at(i + 1);
                    if (tk2.start == tk.start + 1 && tk2.type == Token::word) {
                        i = i + 1;
                        tk.length = tk2.length + 1;
                        tk.type = Token::word;
                    }
                    if (!lexed.isEmpty() && lexed.last().type == Token::word) {
                        if (lexed.last().start + lexed.last().length == tk.start) {
                            lexed.last().length += tk.length;
                            continue;
                        }
                    }
                }
            }
        }
        if (tk.type == Token::word || tk.type == Token::number || tk.type == Token::symbol || tk.type == Token::punctuation) {
            tk.level = level;
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
                tk.argLevel=-1; // tk is part of brace
            }
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                //possible command argument without brackets
                CommandDescription &cd = commandStack.top();
                if (cd.args > 0) {
                    cd.optionalArgs = 0; // no optional arguments after mandatory
                    cd.args--;
                    tk.subtype = cd.argTypes.takeFirst();
                }
                if (cd.args <= 0) {
                    // unknown arg, stop handling this command
                    commandStack.pop();
                }
                tk.level++; // needs tk level be increased
            }
            lexed << tk;
        }
    }
    {
        // remove tokens from stack which are not intended for mulitline: (
        QMutableVectorIterator<Token> i(stack);
        while (i.hasNext()) {
            Token &tk = i.next();
            if (tk.type == Token::openBracket) {
                i.remove();
            } else if ((tk.type == Token::openBrace || tk.type == Token::openSquare ) && tk.dlh == dlh) {
                // set length to whole line after brace
                tk.length = lineLength - tk.start;
            }
        }
    }
    {
        // change length of openBrace/openBracket (length to end of line)
        QMutableListIterator<Token> i(lexed);
        while (i.hasNext()) {
            Token &tk = i.next();
            if ((tk.type == Token::openBrace || tk.type == Token::openSquare ) && tk.dlh == dlh) {
                // set length to whole line after brace
                tk.length = lineLength - tk.start;
            }
        }
    }

    dlh->setCookie(QDocumentLine::LEXER_COOKIE, QVariant::fromValue<TokenList>(lexed));
    // run-away prevention
    // reduce argLevel by 1, remove all elements with level <0
    // TODO: needs to be applied on commandStack as well !!!
    for (int i = 0; i < stack.size(); i++) {
        if (stack[i].type == Token::verbatim)
            continue;
        stack[i].argLevel = stack[i].argLevel - 1;
        if (stack[i].argLevel < 0) {
            stack.remove(i);
            i--;
        }
    }
    dlh->setCookie(QDocumentLine::LEXER_REMAINDER_COOKIE, QVariant::fromValue<TokenStack>(stack));
    dlh->setCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE, QVariant::fromValue<CommandStack>(commandStack));
    dlh->unlock();

    bool remainderChanged = (stack != oldRemainder) || (commandStack != oldCommandStack) ;

    return remainderChanged;
}


/*!
 * returns the position of the first command token after offset
 * args  Tokenlist with all token after command at the same level (top level args, no content)
 *
 */
int findCommandWithArgsFromTL(const TokenList &tl, Token &cmd, TokenList &args, int offset, bool parseComment)
{
	int result = -1;
	for (int i = 0; i < tl.length(); i++) {
		cmd = tl.at(i);
		if (!parseComment && cmd.type == Token::comment)
			return -1;
		if (i < offset)
			continue;
        if (cmd.type == Token::commandUnknown){
            return i;
        }
		if (cmd.type != Token::command)
			continue;
		// Token is command
		result = i;
		// now, collect arguments
		i++;
        int level = cmd.level+1;
        QDocumentLineHandle *t_dlh=cmd.dlh;
        int t_end=cmd.start+cmd.length;
		for (; i < tl.length(); i++) {
			Token tk = tl.at(i);
			if (tk.type == Token::comment)
				break;
			if (tk.level < level)
				break;
			if (tk.level == level) {
                if( (tk.start>=t_end) || (tk.dlh!=t_dlh) ){
                    args.append(tk);
                    t_dlh=tk.dlh;
                    t_end=tk.start+tk.length;
                }
			}
		}
		break;
	}
	return result;
}


QString getArg(const TokenList &tl, Token::TokenType type)
{
    foreach (Token tk, tl) {
        if (tk.subtype==type) {
            QString result;
            QString line=tk.getText();
            if (Token::tkBraces().contains(tk.type)) {
                result = line.mid(1, line.length() - 2);
            }
            if (Token::tkOpen().contains(tk.type)) {
                result = line.mid( 1) + findRestArg(tk.dlh, Token::opposite(tk.type), ConfigManager::RUNAWAYLIMIT);
            }
            if (Token::tkClose().contains(tk.type)) {
                result = line.left(line.length()-1);
            }
            if (result.isEmpty()) {
                result = line;
            }
            return result;
        }
    }
    return QString();
}


QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type,bool enableMultiLineSearch)
{
	// argNumber 0 -> first argument
    QDocument *doc=dlh->document();
    int lineNr=doc->indexOf(dlh);

	// do only create the relevant token sets once and keep them around for later use for speedup.
	static const QSet<Token::TokenType> tokensForMandatoryArg = QSet<Token::TokenType>()
														  << Token::braces
														  << Token::word
														  << Token::command
														  << Token::commandUnknown
														  << Token::number
														  << Token::openBrace;
	static const QSet<Token::TokenType> tokensForMandatoryBraceArg = QSet<Token::TokenType>() << Token::braces;
	static const QSet<Token::TokenType> tokensForOptionalArg = QSet<Token::TokenType>() << Token::squareBracket << Token::openSquare;

    const QSet<Token::TokenType> *searchTokens = nullptr;

	if (type == ArgumentList::Mandatory) {
		searchTokens = &tokensForMandatoryArg;
	} else if (type == ArgumentList::MandatoryWithBraces) {
		searchTokens = &tokensForMandatoryBraceArg;
	} else {
		searchTokens = &tokensForOptionalArg;
	}
	if (!searchTokens)
		return QString();

    int cnt=0;
	int k = 0;
    int level=1;
    if(!tl.isEmpty()){
        level=tl.first().level;
    }
    while( (lineNr)<doc->lineCount() && cnt<ConfigManager::RUNAWAYLIMIT){
        QString line = dlh->text();
        foreach (Token tk,tl) {
            if(tk.level>level)
                continue; //only use tokens from the same option-level


            if (searchTokens->contains(tk.type)) {
                if(tk.argLevel==-1)
                    continue; // token is part of argument
                QString result;
                if (Token::tkBraces().contains(tk.type) || Token::tkOpen().contains(tk.type) || Token::tkClose().contains(tk.type)) {
                    if (Token::tkOpen().contains(tk.type)) {
                        int len=tk.innerStart()+ tk.innerLength();
                        if(len<line.length()){
                            // comment ends line
                            result=line.mid(tk.innerStart(), tk.innerLength());
                        }else{
                            // line break acts as space in latex
                            result=line.mid(tk.innerStart(), tk.innerLength())+" ";
                        }
                        result.append(findRestArg(dlh, Token::opposite(tk.type), ConfigManager::RUNAWAYLIMIT));
                    }else{
                        result = line.mid(tk.innerStart(), tk.innerLength());
                    }
                }
                if (result.isEmpty()) {
                    result = line.mid(tk.start, tk.length);
                }
                if (k == argNumber)
                    return result;
                else
                    k++;
			} else {
                if (type == ArgumentList::Optional)
                    return QString(); //optional argument can't follow mandatory one
                if (type==ArgumentList::MandatoryWithBraces && tk.type!=Token::squareBracket){
                    //mandatorywithbraces can't have other arguments except optional
                    return QString();
                }
			}
        }
        if(!enableMultiLineSearch)
            break;
        lineNr++;
        dlh=doc->line(lineNr).handle();
        if(dlh)
            tl= dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        cnt++;
    }

    return QString();
}


QString findRestArg(QDocumentLineHandle *dlh, Token::TokenType type, int count)
{
	// dlh is current line, next line will be checked here!!!
    if (count <= 0)
		return QString(); // limit search depth
	QDocument *document = dlh->document();
	int index = document->indexOf(dlh);
	if (index + 1 >= document->lines())
		return QString(); // last line reached
	dlh = document->line(index + 1).handle();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	QString result = dlh->text();
    if(!tl.isEmpty()){
        int len=tl.last().start+tl.last().length;
        if(len<result.length()){// comment present or untranslated characters (e.g. comma)
            // make sure it is a comment !!!!
            int j=result.indexOf("%",len);
            if(j>=len){
                result=result.left(j); // avoid comments
            }else{
                result.append(" "); // in case of multiline arguments, linebreak is considered as space in latex
            }
        }else{
            result.append(" "); // in case of multiline arguments, linebreak is considered as space in latex
        }
    }
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
		if (tk.type == type) {
			// closing found
			return result.left(tk.start);
		}
		if (Token::tkClose().contains(tk.type)) {
			// wrong closing found/ syntax problem
			//return value anyway
			return result.left(tk.start + 1);
		}
	}
	return result + findRestArg(dlh, type, count - 1);
}


/*!
 * \brief get token at column
 * \param dlh linehandle
 * \param pos columns number
 * \param first get first token that encompasses \a pos, otherwise the latest token which fulfils the condition is returned
 * \return found token
 */
Token getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first)
{
	if (!dlh) return Token();
	TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	Token tk;
	for (int i = 0; i < tl.length(); i++) {
		Token elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length >= pos) {
			tk = elem; // get deepest element at col
			if (first)
				break;
		}
		if (!Token::tkBraces().contains(elem.type) && !Token::tkClose().contains(elem.type) && elem.start + elem.length >= pos) { // get abc|} -> abc
			tk = elem; // get deepest element at col
			if (first)
				break;
		}
	}
	return tk;
}


/*!
 * \brief get token at column
 * \param tl tokenlist of line
 * \param pos column
 * \param first first get first token that encompasses \a pos, otherwise the latest token which fulfils the condition is returned
 * \return number of token, -1 if not found
 */
int getTokenAtCol(TokenList &tl, int pos, bool first)
{
	int result = -1;
	for (int i = 0; i < tl.length(); i++) {
		Token elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length >= pos) {
			result = i; // get deepest element at col
			if (first)
				break;
		}
	}
	return result;
}


/*!
 * \brief get content of argument
 *
 * Handles multiline arguments.
 * To avoid performance impact on unclosed arguments, the maximum number of processed lines is limited to 10.
 * This is called run-away prevention.
 * \param tk argument top-level
 * \return tokenlist with all tokens within the argument
 */
TokenList getArgContent(Token &tk)
{
	TokenList results;
	QDocumentLineHandle *dlh = tk.dlh;
	if (!dlh)
		return results;
	dlh->lockForRead();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	dlh->unlock();
	for (int i = 0; i < tl.length(); i++) {
		if (tk == tl.at(i)) {
			results = getArgContent(tl, i, tk.level);
			break;
		}
	}
	return results;
}


/*!
 * \brief get content of argument
 *
 * Handles multiline arguments.
 * To avoid performance impact on unclosed arguments, the maximum number of processed lines is limited to 10.
 * This is called run-away prevention.
 * \param tl tokenlist of current line
 * \param pos number of token in tokenlist
 * \param level of argument
 * \param runAwayPrevention counts down to zero for subsequent lines to prevent unlimited processing of lines on unclosed arguments
 * \return tokenlist with all tokens within the argument
 */
TokenList getArgContent(TokenList &tl, int pos, int level, int runAwayPrevention)
{
	TokenList result;
	if (runAwayPrevention < 0)
		return result;
	bool finished = false;
	Token tk;
	// adapt strategy after token type (word, closed , open)
	if (pos >= 0 && pos < tl.length()) {
		tk = tl.at(pos);
		if (tk.type == Token::word) {
			result.append(tk);
			return result;
		}
		if (Token::tkBraces().contains(tk.type)) {
			//closed , no spill in next line
			runAwayPrevention = 0; // in case there is no token after the last usable one
		}
	}

	for (int i = pos + 1; i < tl.length(); i++) {
		tk = tl.at(i);
		if (tk.level < level) {
			finished = true;
			break; // end reached
		}
		if (tk.level == level) {
			result.append(tk);
		}
		//ignore other levels
	}
	if (!finished && tk.dlh) {
		//getRestArgfrom
		QDocument *document = tk.dlh->document();
		int index = document->indexOf(tk.dlh);
		TokenList tl;
		while (index + 1 < document->lines()) {
			QDocumentLineHandle *dlh = document->line(index + 1).handle();
			tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
			if (!tl.isEmpty())
				break;
			index++;
		}
		if (!tl.isEmpty())
			result.append(getArgContent(tl, -1, level - tk.level, runAwayPrevention - 1));
	}
	return result;
}


/*!
 * \brief get context at line/column
 *
 * return a tokenstack of the context situation
 * It contains (possibly) command/argument/word
 * \param dlh linehandle
 * \param pos column
 * \return tokenstack
 */
TokenStack getContext(QDocumentLineHandle *dlh, int pos)
{
	if (!dlh) return TokenStack();
	dlh->lockForRead();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	dlh->unlock();
	QDocument *doc = dlh->document();
	int lineNr = doc->indexOf(dlh);
	TokenStack stack;
	if (lineNr > 0) {
		QDocumentLineHandle *previous = doc->line(lineNr - 1).handle();
		previous->lockForRead();
		stack = previous->getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
		previous->unlock();
	}
	// find innermost token at pos
	TokenStack ts;
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
		if (tk.start > pos) {
			break;
		}
		if (Token::tkOpen().contains(tk.type)) {
			stack.push(tk);
		}
        if (Token::tkClose().contains(tk.type) && !stack.isEmpty() ) {
            if (stack.top().type == Token::opposite(tk.type) && (tk.start<pos)) {
				stack.pop();
			}
            continue;
        }



		if (ts.isEmpty()) {
			ts.push(tk);
		} else {
			// if level identical, replace top
			// if level > , add
			// if level < , remove and replace
			if (ts.top().level == tk.level) {
                int top_end=ts.top().start+ts.top().length;
                if(top_end<pos){
                    ts.pop();
                }
				ts.push(tk);
			} else {
				if (ts.top().level < tk.level) {
					ts.push(tk);
				} else {
					ts.pop();
					if (ts.isEmpty()) {
						ts.push(tk);
					} else {
						ts.pop();
						ts.push(tk);
					}
				}
			}

		}
	} //for
	while (!ts.isEmpty()) {
		// check that pos is within stack
		if (ts.top().start + ts.top().length > pos)
			break;
		if (ts.top().start + ts.top().length == pos && !Token::tkBraces().contains(ts.top().type)) // equal is accceptable for other than braces
			break;
		ts.pop();
	}
	stack << ts;
	return stack;
}


/*!
 * tk is an argument token (inner content)
 * it assumes that the command is at level--
 * at the moment, only single line detection
 */
QString getCommandFromToken(Token tk)
{
    // don't use outside of main thread as "previous" may be invalid
    if(!tk.optionalCommandName.isEmpty())
        return tk.optionalCommandName;

    QString cmd;
	QDocumentLineHandle *dlh = tk.dlh;
	if (dlh) {
        TokenList tl;
        QDocument *doc = dlh->document();
        if(doc){ // doc is NULL if line was deleted in the meantime
            int lineNr = doc->indexOf(dlh);
            if (lineNr > 0) {
                QDocumentLineHandle *previous = doc->line(lineNr - 1).handle();
                TokenStack stack=previous->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
                if(!stack.isEmpty()){
                    Token tk_group=stack.top();
                    if(tk_group.dlh){
                        tl<< tk_group.dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
                    }
                }
            }
            tl<< dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();

            Token result = getCommandTokenFromToken(tl, tk);
            if (result.type == Token::command) {
                cmd = result.getText();
            }
        }
	}
	return cmd;
}


/*!
 * \brief get token which represents the command of which \a tk is a argument
 * \param tl tokenlist of line
 * \param tk token which is argument of a command
 * \return token of command
 */
Token getCommandTokenFromToken(TokenList tl, Token tk)
{
	Token result;
	int tkPos = tl.indexOf(tk);
	int level = tk.level - 1;
	if (tk.subtype == Token::keyVal_val) {
		level = tk.level - 2; // command is 2 levels up
	}
	for (int i = tkPos - 1; i >= 0; i--) {
		Token elem = tl.at(i);
		if (elem.level == level && (elem.type == Token::command || elem.type == Token::commandUnknown) ) {
			result = elem;
			break;
		}
		if (elem.level < level)
			break;
	}
	return result;
}


/*!
 * \brief get completer context
 * \param dlh linehandle
 * \param column
 * \return 512 if token at column is 'width'
 */
int getCompleterContext(QDocumentLineHandle *dlh, int column)
{
	TokenStack ts = getContext(dlh, column);
	Token tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
		if (tk.type == Token::word && tk.subtype == Token::none && ts.size() > 1) {

			// set brace type
			ts.pop();
			tk = ts.top();
		}
	}

	Token::TokenType type = tk.type;
	if (tk.subtype != Token::none && tk.subtype != Token::keyVal_val)
		type = tk.subtype;

	int result = 0;
	switch (type) {
	case Token::width:
		result = 512;
		break;
	default:
		;
	}
	return result;
}

}  // namespace Parsing
