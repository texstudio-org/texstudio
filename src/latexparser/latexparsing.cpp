#include "latexparsing.h"
#include "qdocumentline_p.h"
#include "qdocument.h"
#include "latexparser/latexparser.h"
#include "configmanager.h"

/*!
 * This is the new Token-based parser.
 */

namespace Parsing {


/*!
 * Realizes the first pass lexing
 * Following functionality is implemented:
 * + separate the text into words,symbols
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
    const QString specialChars = "{([<})]>";
	int i = 0;
	for (; i < s.length(); i++) {
		QChar c = s.at(i);
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
                    // special case 0x... 0b....
                    if((c=='x' || c=='b')   && i-present.start==1 && s[present.start]=='0'){
                        continue;
                    }
                    if(QString("abcdef").contains(c.toLower()) && s[present.start]=='0' && s[present.start+1]=='x'){
                        continue;
                    }
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
        if (l > -1 && l < 4) {
			present.type = Token::TokenType(int(Token::openBrace) + l);
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
        if (l > 3) {
            present.type = Token::TokenType(int(Token::closeBrace) + (l - 4));
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


bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const QSharedPointer<LatexParser> lp)
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
    int lastComma = -1;
    int lastEqual = -1e6;
    int commentStart=-1;
    QString keyVal_keyString;
    if (!stack.isEmpty()) {
        if (stack.top().type == Token::verbatim) {
            verbatimMode = true;
        } else {
            level = stack.top().level + 1;
        }
        if (stack.top().type == Token::keyVal_val && stack.top().length==0) {
            // hand over lastEqual
            lastEqual=stack.top().level;
            lastComma=1e6;
            keyVal_keyString=stack.top().optionalCommandName;
            stack.pop();
        }
    }

	TokenList lexed;
	QString verbatimSymbol;
	QString keyName;
    // extra stack for storing lastComma/lastEqual in case of new argument is introduced
    // this works single line only (for now)
    // see issue #4074
    struct ArgumentSeparator
    {
        int lastComma;
        int lastEqual;
    };
    QStack<ArgumentSeparator> argumentStack;

    bool unknownCommandsPresent = false;

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
            if (tk.type == Token::symbol || tk.type == Token::punctuation) {
                QString smb = line.mid(tk.start, 1);
                if (smb == verbatimSymbol) {
                    // stop verbatimSymbol mode
                    verbatimSymbol.clear();
                    tk.subtype=Token::verbatimStop;
                    tk.level = level;
                    lexed << tk;
                    continue;
                }
            }
            if(tk.type == Token::command && tk.length>1){
                // special treatment of slash verbatim-symbol
                // \verb+ .... \+ ...
                QString smb = line.mid(tk.start, tk.length);
                if (smb[1] == verbatimSymbol) {
                    // stop verbatimSymbol mode
                    verbatimSymbol.clear();
                    Token tk1;
                    tk1.start=tk.start;
                    tk1.length=1;
                    tk1.type=Token::verbatim;
                    tk1.dlh=tk.dlh;
                    tk.type=Token::symbol;
                    tk.subtype=Token::verbatimStop;
                    tk.level = level;
                    ++tk.start;
                    tk.length=1;

                    lexed << tk1 << tk;
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
            // search for closing brace (#2528)
            Token tk_closing;
            bool closingFound=false;
            for(int j=i+3;j<tl.length();++j){
                tk_closing=tl.at(j);
                if(tk_closing.type == Token::closeBrace){
                    closingFound=true;
                    break;
                }
            }
            if (tk2.type == Token::openBrace && closingFound) {
                QString env = line.mid(tk3.start, tk_closing.start-tk3.start);
                if (lp->possibleCommands["%verbatimEnv"].contains(env)) { // incomplete check if closing corresponds to open !
                    Token verbatimStart=stack.top();
                    // second option, env in optionalCommandName
                    if(verbatimStart.optionalCommandName.isEmpty() || verbatimStart.optionalCommandName==env){
                        verbatimMode = false;
                        stack.pop();
                    }else{
                        continue;
                    }
                } else
                    continue;
            } else
                continue;
        }
        // non-verbatim handling
        // handle comments after definition/url as % may appear there ...
        if (tk.type == Token::comment){
            if(stack.isEmpty() || stack.top().subtype!=Token::url) { // no comments in URL
                lineLength=tk.start; // limit linelength to comment start
                commentStart=tk.start;
                break; // stop at comment start
            }
        }
        // special definition handling, is not interpreted !!
        if(!stack.isEmpty() && (stack.top().subtype==Token::definition||stack.top().subtype==Token::url) ){
            EnumsTokenType::TokenType tokenType=stack.top().subtype;
            if(tk.type==Token::openBrace){
                tk.subtype=tokenType;
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
                    if(!stack.isEmpty() && stack.top().subtype==tokenType){ // check if more than openBrace/defintion are on the stack, if yes , just pop it and continue in definition mode
                        tk.subtype=tokenType;
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
            // special treatment for character changing commands like \"a (ä)
            if(tk.length==2 && command[1].isPunct() && command[1]!=QChar('\\') && !QString("()[]{}").contains(command[1])){
                if (i + 1 < tl.length()) {
                    Token tk2 = tl.at(i + 1);
                    if (tk2.start == tk.start + tk.length && tk2.type == Token::word) {
                        i = i + 1;
                        tk.length += tk2.length ;
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
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
                if (tk.subtype == Token::keyValArg && lastEqual > -1) {
                    tk.subtype = Token::keyVal_val;
                    if (!commandStack.isEmpty() && lp->commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                        CommandDescription cd = lp->commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                        ArgumentDescription ad=cd.arguments.value(0, ArgumentDescription{ArgumentDescription::MANDATORY,Token::keyVal_val});
                        tk.subtype = ad.tokenType;
                    }
                }

            }
            tk.level = level;
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                //possible command argument without brackets
                CommandDescription &cd = commandStack.top();
                // skip over optional arguments
                while(!cd.arguments.isEmpty() && (cd.arguments.first().type >= ArgumentDescription::OPTIONAL)) {
                    cd.arguments.takeFirst();
                }
                // check for mandatory argument
                if (!cd.arguments.isEmpty() && cd.arguments[0].type==ArgumentDescription::MANDATORY) {
                    ArgumentDescription ad=cd.arguments.takeFirst();
                    tk.subtype = ad.tokenType;
                    tk.level++;
                }else{
                    // unknown arg, stop handling this command
                    cd.arguments.clear();
                }
                if (cd.arguments.isEmpty()) {
                    // command has been handled
                    commandStack.pop();
                }
            }
            if (lp->commandDefs.contains(command) && tk.subtype != Token::definition) {
                CommandDescription cd = lp->commandDefs.value(command);
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
                if (cd.arguments.size() > 0 && tk.subtype != Token::def) { // don't interpret commands in definition (\newcommand{def})
                    cd.optionalCommandName=command;
                    commandStack.push(cd);
                }
            } else {
                if(tk.type==Token::command && tk.subtype == Token::none){
                    if(command!="\\\\"){
                        // skip "\\"
                        tk.type = Token::commandUnknown;
                        unknownCommandsPresent=true;
                    }
                }
            }
            lexed << tk;
            continue;
        }
        if (Token::tkOpen().contains(tk.type)) {
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                CommandDescription &cd = commandStack.top();
                if (tk.type == Token::openBrace) {
                    // skip over optional arguments, here assume optional arguments as [],<> and ()
                    while(!cd.arguments.isEmpty() && (cd.arguments.first().type >= ArgumentDescription::OPTIONAL) ) {
                        cd.arguments.takeFirst();
                    }
                    // check for mandatory argument
                    if (!cd.arguments.isEmpty() && cd.arguments.first().type == ArgumentDescription::MANDATORY) {
                        ArgumentDescription ad= cd.arguments.takeFirst();
                        tk.subtype = ad.tokenType;
                        // special treatment for keyval
                        if(tk.subtype==Token::keyValArg){
                            int indexOfKeyValArg=determineKeyValIndex(cd);
                            if(indexOfKeyValArg>0){
                                tk.optionalCommandName=cd.optionalCommandName+QString("#o%1").arg(indexOfKeyValArg);
                            }
                        }
                    } else {
                        // handle as independet braces, like commandless brace below
                        // e.g. \hline {... (\hline accepts optional arguments, but no braces)
                        tk.level = level;
                        tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention, needs to be >0 as otherwise closing barces are misinterpreted
                        if (!stack.isEmpty()) {
                            tk.subtype = stack.top().subtype;
                            if(tk.subtype==Token::text){
                                tk.subtype=Token::none; //avoid assignening text subtype to just arbitrary braces inside an argument, see #3040 (#2603)
                            }
                            if(stack.top().subtype==Token::keyValArg){
                                // still the generic argument, needs to be broken down to key or val
                                if(lastComma>=0){
                                    // -> val
                                    tk.subtype=Token::keyVal_val;
                                    if(lastComma>=1e6){
                                        tk.optionalCommandName=keyVal_keyString;
                                    }else{
                                        QString cmd=lexed[lastComma].optionalCommandName;
                                        QString key=line.mid(lexed[lastComma].start, lexed[lastComma].length);
                                        tk.optionalCommandName=cmd+"/"+key;
                                    }
                                }else{
                                    tk.subtype=Token::keyVal_key; // not sure if that is a real scenario
                                }
                            }
                        }
                        stack.push(tk);
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openSquare) {
                    bool handled=false;
                    while(!handled && !cd.arguments.isEmpty() && (cd.arguments.first().type == ArgumentDescription::OVERLAY || cd.arguments.first().type == ArgumentDescription::BRACKET)) {
                        cd.arguments.takeFirst();
                    }
                    if (!cd.arguments.isEmpty() && cd.arguments.first().type == ArgumentDescription::DEFAULT_OVERLAY) {
                        // check next token to be less
                        if (i + 1 < tl.length() && tl[i + 1].type == Token::less) {
                            ArgumentDescription ad= cd.arguments.takeFirst();
                            tk.subtype = ad.tokenType;
                            ++i;
                            handled=true;
                        } else {
                            cd.arguments.takeFirst();
                        }
                    }
                    if (!handled && !cd.arguments.isEmpty() && cd.arguments.first().type == ArgumentDescription::OPTIONAL) {
                        ArgumentDescription ad= cd.arguments.takeFirst();
                        tk.subtype = ad.tokenType;
                        handled=true;
                        // special treatment for keyval
                        if(tk.subtype==Token::keyValArg){
                            int indexOfKeyValArg=determineKeyValIndex(cd);
                            if(indexOfKeyValArg>0){
                                tk.optionalCommandName=cd.optionalCommandName+QString("#o%1").arg(indexOfKeyValArg);
                            }
                        }
                    }
                    if(!handled){
                        // unexpected optional argument
                        // ignore
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openBracket) {
                    // skip over optional arguments
                    while(!cd.arguments.isEmpty() && (cd.arguments.first().type == ArgumentDescription::OPTIONAL || cd.arguments.first().type == ArgumentDescription::OVERLAY || cd.arguments.first().type == ArgumentDescription::DEFAULT_OVERLAY)) {
                        cd.arguments.takeFirst();
                    }
                    // check for mandatory argument
                    if (!cd.arguments.isEmpty() && cd.arguments.first().type == ArgumentDescription::BRACKET) {
                        ArgumentDescription ad= cd.arguments.takeFirst();
                        tk.subtype = ad.tokenType;
                        // special treatment for keyval
                        if(tk.subtype==Token::keyValArg){
                            int indexOfKeyValArg=determineKeyValIndex(cd);
                            if(indexOfKeyValArg>0){
                                tk.optionalCommandName=cd.optionalCommandName+QString("#o%1").arg(indexOfKeyValArg);
                            }
                        }
                    } else {
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::less) {
                    if (!cd.arguments.isEmpty() && cd.arguments.first().type == ArgumentDescription::OVERLAY) {
                        ArgumentDescription ad= cd.arguments.takeFirst();
                        tk.subtype = ad.tokenType;
                    } else {
                        lexed << tk;
                        continue;
                    }
                }

                tk.level = level; // push old level on stack in order to restore that level later and to distinguish between arguments and arbitrary braces
                tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention
                if(tk.subtype==Token::beginEnv || tk.subtype==Token::env){
                    // cut runaway as is must stay within one line
                    tk.argLevel = 0;
                }
                stack.push(tk);
                tk.level++;
                lexed << tk;
                level++;
                // stack lastEqual/lastComma
                ArgumentSeparator argSep;
                argSep.lastComma=lastComma;
                argSep.lastEqual=lastEqual;
                argumentStack.push(argSep);
                lastComma = -1;
                lastEqual = -1e6;
            }else{
                if(tk.type==Token::openBrace){ // check braces within arguments, not brackets/squareBrackets
                    tk.level = level;
                    level++; // not an argument
                    tk.argLevel = ConfigManager::RUNAWAYLIMIT; // run-away prevention, needs to be >0 as otherwise closing barces are misinterpreted
                    if (!stack.isEmpty()) {
                        tk.subtype = stack.top().subtype;
                        if(tk.subtype==Token::text){
                            tk.subtype=Token::none; //avoid assignening text subtype to just arbitrary braces inside an argument, see #3040 (#2603)
                        }
                        if(stack.top().subtype==Token::keyValArg){
                            // still the generic argument, needs to be broken down to key or val
                            if(lastComma>=0){
                                // -> val
                                tk.subtype=Token::keyVal_val;
                                if(lastComma>=1e6){
                                    tk.optionalCommandName=keyVal_keyString;
                                }else{
                                    QString cmd=lexed[lastComma].optionalCommandName;
                                    QString key=line.mid(lexed[lastComma].start, lexed[lastComma].length);
                                    tk.optionalCommandName=cmd+"/"+key;
                                }
                            }else{
                                tk.subtype=Token::keyVal_key; // not sure if that is a real scenario
                            }
                        }else{
                            tk.optionalCommandName="NA"; // mark as non-argument brace
                        }
                    }
                    stack.push(tk);
                    ++tk.level;
                    lexed << tk;
                }
            }
            continue;
        }
	    if (Token::tkClose().contains(tk.type)) {
            // special treament for brackets as they don't have any syntactic meaning except with some commands
            if (tk.type == Token::closeBracket || tk.type == Token::greater ) {
                if (stack.isEmpty())
                    continue;
                if (stack.top().type != Token::opposite(tk.type))
                    continue; //closing bracket/> is ignored if no correct open is present
            }
            // special treatment for beamer default overlay [< >]
            if(tk.type==Token::greater && stack.top().type == Token::openSquare){
                if(!commandStack.isEmpty() && commandStack.top().arguments.size()>0 && commandStack.top().arguments.first().type==ArgumentDescription::DEFAULT_OVERLAY){
                    // check if closing bracket is expected
                    if(i+1<tl.length() && tl[i+1].type==Token::closeSquareBracket){
                        // closing bracket found
                        ++i;
                        tk=tl[i]; // use outer closing square bracket
                    }else{
                        // closing bracket not found, ignore token
                        continue;
                    }
                }
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
                // handle stacked lastComma/lastEqual
                if(!argumentStack.isEmpty()){
                    ArgumentSeparator argSep=argumentStack.pop();
                    lastComma=argSep.lastComma;
                    lastEqual=argSep.lastEqual;
                }

                if (tk1.dlh == dlh) { // same line
                    int j = lexed.length() - 1;
                    while (j >= 0 && lexed.at(j).start > tk1.start)
                        j--;
                    bool forceContinue=false;
                    if (j >= 0 && lexed.at(j).start == tk1.start) {
                        if (Token::tkSingleArg().contains(tk1.subtype) || (tk1.subtype >= Token::specialArg && lp->mapSpecialArgumentTypes.value(tk1.subtype-Token::specialArg)==LatexParser::singleArgument)) { // all special args are assumed single word arguments
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
                                CommandDescription cd = lp->commandDefs.value("\\begin{" + env + "}", CommandDescription());
                                // special treatment for verbatim
                                if (lp->possibleCommands["%verbatimEnv"].contains(env)) {
                                    if(cd.args()>=1 && cd.args(ArgumentDescription::OPTIONAL)==1 && i<(tl.length()-1) && tl[i+1].type==Token::openSquare){ // next Token needs to be [ i.e. optional arg, otherwise start verbatim directly
                                        // special treatment for \begin{abc}[...]
                                        cd.verbatimAfterOptionalArg=true;
                                        cd.arguments.takeFirst();
                                        cd.optionalCommandName="\\begin{" + env + "}";
                                        cd.level=tk1.level;
                                        commandStack.push(cd);
                                        forceContinue=true;
                                    }else{
                                        verbatimMode = true;
                                        Token tk3;
                                        tk3.dlh = dlh;
                                        tk3.level = level - 1;
                                        tk3.type = Token::verbatim;
                                        tk3.optionalCommandName=env; // store verbatim env name (fix #2386, \end{diffVerbatim} was falsely used to close verbatim)
                                        stack.push(tk3);
                                    }
                                } else { // only care for further arguments if not in verbatim mode (see minted)
                                    if ((cd.args() > 1)||(cd.args()==1 && cd.args(ArgumentDescription::OPTIONAL)>0)) {
                                        cd.arguments.takeFirst();
                                        cd.optionalCommandName="\\begin{" + env + "}";
                                        cd.level=tk1.level;
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
                            continue;
                        }
                    } else { // opening not found, whyever (should not happen)
                        //level--;
                        tk.level = level;
                        lexed.append(tk);
                    }
                } else {
                    // closing brace in later line ...
                    level=tk1.level; // restore original level
                    tk.level = level+1; // force level+1 (maybe +2 in case of keyval_val
                    tk.subtype=tk1.subtype;
                    lexed.append(tk);
                    // clean up command stack (unrealized arguments)
                    while (!commandStack.isEmpty() && commandStack.top().level > level) {
                        commandStack.pop();
                    }
                }
                if (!commandStack.isEmpty() && commandStack.top().level == level) {
                    CommandDescription cd = commandStack.top();
                    if (cd.arguments.isEmpty()) {
                        // all args handled, stop handling this command
                        commandStack.pop();
                        if(cd.verbatimAfterOptionalArg){ // delayed verbatim start to handle optional argument
                            verbatimMode = true;
                            Token tk3;
                            tk3.dlh = dlh;
                            tk3.level = level - 1;
                            tk3.type = Token::verbatim;
                            QString env=cd.optionalCommandName.mid(7,cd.optionalCommandName.length()-8); // dirty solution, does not use tokens as it should
                            tk3.optionalCommandName=env;
                            stack.push(tk3);
                        }
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
                if(lastComma<1e6){
                    lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
                }
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
                        tk0.dlh=dlh;
                        tk0.type = Token::keyVal_val;
                        tk0.subtype = Token::keyVal_val;
                        tk0.level = level;
                        lexed << tk0;
                    }
                    // remove potential command from stack as keyval argument is closed
                    if(!commandStack.isEmpty() && commandStack.top().level == level) {
                        commandStack.pop();
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
                if(!commandStack.isEmpty() && lp->commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)){
                    // handle keyval values with normal commandStack mechanism (mandatory argument only!!)
                    // allows argument classification
                    CommandDescription cd = lp->commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                    cd.optionalCommandName=commandStack.top().optionalCommandName;
                    if(cd.arguments[0].tokenType==Token::width){
                        // special treatment for length for now
                        continue;
                    }
                    cd.level=level;
                    commandStack.push(cd);
                }
                continue;
            }
            if (lastComma < 0 ) {
                tk.level = level;
                tk.type = Token::keyVal_key;
                if(!commandStack.isEmpty()){
                    const CommandDescription &cd = commandStack.top();
                    int indexOfKeyValArg=determineKeyValIndex(cd);
                    if(indexOfKeyValArg>0){
                        tk.optionalCommandName=cd.optionalCommandName+QString("#o%1").arg(indexOfKeyValArg);
                    }else{
                        tk.optionalCommandName=cd.optionalCommandName;
                    }
                }
                keyName = line.mid(tk.start, tk.length);
                lexed << tk;
                lastComma = lexed.length() - 1;
            } else {
                if (lastEqual <= -1e6) {
                    if(lastComma<1e6){
                        lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
                        keyName= line.mid(tk.start, lexed[lastComma].length);
                    }
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
                    // special treatment for numbers after word (join them to word, see https://github.com/texstudio-org/texstudio/issues/2306 )
                    if (tk.type == Token::number) {
                        if(lastComma==(lexed.length()-2)){
                            if((lexed[lastComma+1].start+lexed[lastComma+1].length==tk.start)&&lexed[lastComma+1].type==Token::word){
                                lexed[lastComma+1].length+=tk.length;
                                continue;
                            }
                        }
                    }
                    // special treatment for $ as mathstart
                    if (line.mid(tk.start, 1) == "$") {
                        tk.type = Token::command;
                        if(i+1<tl.length()){
                            if(line.mid(tk.start,2)=="$$"){
                                i=i+1;
                                tk.length=2;
                            }
                        }
                        lexed << tk;
                        continue;
                    }
                    // add cmd/key as optionalCommandName
                    if(lastComma>=1e6){
                        // continued from earlier line
                        tk.optionalCommandName=keyVal_keyString;
                    }else{
                        QString cmd=lexed[lastComma].optionalCommandName;
                        QString key=line.mid(lexed[lastComma].start, lexed[lastComma].length);
                        tk.optionalCommandName=cmd+"/"+key;
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
                    //basically used for length values
                    if (!commandStack.isEmpty() && lp->commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                        CommandDescription cd = lp->commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                        auto ad=cd.arguments.value(0, ArgumentDescription{ArgumentDescription::MANDATORY,Token::keyVal_val});
                        if(ad.tokenType==Token::text){
                            // for now special treatment of text, but basically all multi-token types should be handled here
                            // don't merge with previous token
                            tk.subtype=ad.tokenType;
                        }else{
                            tk.type = ad.tokenType; // only types can be set in key_val as they need to be recognized later
                            if(!lexed.isEmpty() && lexed.last().type==tk.type && lexed.last().subtype==tk.subtype){
                                lexed.last().length=tk.start+tk.length-lexed.last().start;
                                continue;
                            }
                        }
                    }
                    lexed << tk;
                }
            }
            continue;
        }
        if (tk.type == Token::symbol) {
            // special treatment for $ as mathstart
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

                        if (!lexed.isEmpty() && lexed.last().type == Token::word) {
                            if (lexed.last().start + lexed.last().length == tk.start) {
                                lexed.last().length += tk.length;
                                continue;
                            }
                        }
                    }
                }
            }
        }
        if (tk.type == Token::word || tk.type == Token::number || tk.type == Token::symbol || tk.type == Token::punctuation) {
            tk.level = level;
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
                tk.optionalCommandName = stack.top().optionalCommandName;
                tk.argLevel=-1; // tk is part of brace
            }
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                //possible command argument without brackets
                CommandDescription &cd = commandStack.top();
                // skip over optional arguments, here assume optional arguments as [],<> and ()
                while(!cd.arguments.isEmpty() && (cd.arguments.first().type >= ArgumentDescription::OPTIONAL) ) {
                    cd.arguments.takeFirst();
                }
                if (cd.arguments.size() && cd.arguments.first().type==ArgumentDescription::MANDATORY) {
                    auto ad=cd.arguments.takeFirst();
                    tk.subtype = ad.tokenType;
                    tk.level++; // needs tk level be increased
                }else{
                    cd.arguments.clear(); // unknown arg, stop handling this command
                }
                if (cd.arguments.isEmpty()) {
                    // command has been handled completely
                    commandStack.pop();
                }
            }

            if(tk.subtype==Token::keyVal_val && tk.type==Token::punctuation && line.mid(tk.start, tk.length)==",") continue; // exception for comma in keyVal braces
            lexed << tk;
            if(tk.subtype==Token::verbatimStart){
                verbatimSymbol = line.mid(tk.start, 1);
            }
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
    if (!commandStack.isEmpty() && commandStack.top().level == level) {
        CommandDescription &cd = commandStack.top();
        if(cd.verbatimAfterOptionalArg){ //optional arg not found
            Token tk3;
            tk3.dlh = dlh;
            tk3.level = level;
            tk3.type = Token::verbatim;
            cd.verbatimAfterOptionalArg=false; // don't search again on next line
            stack.push(tk3);
        }
    }

    dlh->setCookie(QDocumentLine::LEXER_COOKIE, QVariant::fromValue<TokenList>(lexed));

    for (int i = 0; i < stack.size(); i++) {
        if (stack[i].type == Token::verbatim)
            continue;
        stack[i].argLevel = stack[i].argLevel - 1;
        if (stack[i].argLevel < 0) {
            stack.remove(i);
            i--;
        }
    }
    // simply add lastEqual to stack
    if(lastEqual>-1e6 && stack.size() && stack.top().subtype==Token::keyValArg){
        Token tk;
        tk.dlh=dlh;
        tk.type=EnumsTokenType::keyVal_val;
        tk.subtype=EnumsTokenType::keyVal_val;
        tk.start=0;
        tk.length=0;
        tk.level=lastEqual;
        if(lastComma>=1e6){
            tk.optionalCommandName=keyVal_keyString;
        }else{
            if(lastComma>=0){
                QString cmd=lexed[lastComma].optionalCommandName;
                QString key=line.mid(lexed[lastComma].start, lexed[lastComma].length);
                tk.optionalCommandName=cmd+"/"+key;
            }
        }
        stack.push(tk);
    }
    dlh->setCookie(QDocumentLine::LEXER_REMAINDER_COOKIE, QVariant::fromValue<TokenStack>(stack));
    dlh->setCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE, QVariant::fromValue<CommandStack>(commandStack));
    dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >({commentStart, Token::unknownComment}));
    dlh->setFlag(QDocumentLine::lexedPass2InComplete,unknownCommandsPresent);
    dlh->setFlag(QDocumentLine::lexedPass2Complete,!unknownCommandsPresent);
    dlh->setFlag(QDocumentLine::argumentsParsed,false);
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
                result = line.mid( 1) + findRestArg(tk.dlh, Token::opposite(tk.type), -1,ConfigManager::RUNAWAYLIMIT);
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

/*!
 * \brief get complete argument, possibly spanning multiple lines
 * Can be limited to mandatory/optional arguments
 * \param tl of the arguments
 * \param dlh
 * \param argNumber, 0 based
 * Only the relevant argument types are counted, e.g \abc[opt]{mand} -> mand is argument 0 in case that only mandatory arguments are requested
 * \param type
 * \param enableMultiLineSearch
 * \param hint which is the linenumber in the document for faster searching
 * \return
 */
QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type,bool enableMultiLineSearch,int hint)
{
	// argNumber 0 -> first argument
    QDocument *doc=dlh->document();
    int lineNr=-1;

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

    bool skipOptionalArgument=false;
    int cnt=0;
	int k = 0;
    int level=1;
    if(!tl.isEmpty()){
        level=tl.first().level;
    }
    while( cnt<ConfigManager::RUNAWAYLIMIT){
        QString line = dlh ? dlh->text() : "";
        foreach (Token tk,tl) {
            if(tk.level>level)
                continue; //only use tokens from the same option-level
            if(tk.level<level){
                // something wrong with the parsed arguments, abort procedure
                return "";
            }
            if(skipOptionalArgument) {
                if(tk.type==Token::closeSquareBracket && tk.level==level){
                    skipOptionalArgument=false;
                }
                continue;
            }
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
                        result.append(findRestArg(dlh, Token::opposite(tk.type), lineNr<0 ? hint : lineNr ,ConfigManager::RUNAWAYLIMIT));
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
                if (type==ArgumentList::Mandatory && tk.type==Token::openSquare && tk.level==level){
                    // gracefully jump over multiline optional argument
                    skipOptionalArgument=true;
                    break; // skip rest of current line as close squareBracket can't be in there
                }
			}
        }
        if(!enableMultiLineSearch)
            break;
        if(lineNr<0){
            lineNr=doc->indexOf(dlh,hint); // perform lineNr search only when really needed
        }
        lineNr++;
        if(lineNr>=doc->lineCount()){
            break;
        }
        dlh=doc->line(lineNr).handle();
        if(dlh)
            tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        cnt++;
    }

    return QString();
}


QString findRestArg(QDocumentLineHandle *dlh, Token::TokenType type, int hint, int count)
{
	// dlh is current line, next line will be checked here!!!
    if (count <= 0)
		return QString(); // limit search depth
	QDocument *document = dlh->document();
    int index = document->indexOf(dlh,hint);
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
    return result + findRestArg(dlh, type, index+1, count - 1);
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
            // check non-argument braces
            if(
                (tk.type==Token::braces && tk.subtype==Token::none) ||
                (tk.type==Token::openBrace && tk.subtype==Token::none)){
                finished = true;
                break; // end reached
            }
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
            tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
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
        // adapt level for open braces
        for(int i=0;i<stack.size();++i){
            if(Token::tkOpen().contains(stack[i].type)){
                ++stack[i].level;
            }
        }
	}
	// find innermost token at pos
	TokenStack ts;
    bool inBrace=false;
    int skipAhead=-1; // skip tokens which are part of a brace,etc. when pos is outside that brace, e.g  {abc} |
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
        if (tk.start > pos) {
			break;
		}
        if(tk.start == pos && tk.length>0){
            // break if token is right of cursor, fix #3967
            // also fix #4017
            break;
        }
        if(tk.start<skipAhead){
            continue;
        }
        if(Token::tkBraces().contains(tk.type)){
            if(tk.start+tk.length<pos){
                skipAhead=tk.start+tk.length;
                continue;
            }else{
                inBrace=true;
            }
        }
        if(Token::tkOpen().contains(tk.type) && tk.start+tk.length>=pos){
            // not completed brace contains position, e.g. {abc  |  \n
            inBrace=true;
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
    if(!inBrace && std::any_of(stack.constBegin(),stack.constEnd(),[](const Token &tk){return Token::tkOpen().contains(tk.type);})){
        // handle open braces in stack
        inBrace=true;
    }
    if(!inBrace && !ts.isEmpty() && ts.top().start+ts.top().length<pos){
        // position is not touching token nor part of an encompassing brace
        ts.clear();
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
    if(!tk.optionalCommandName.isEmpty() && tk.optionalCommandName.startsWith("\\")){
        QString cmd=tk.optionalCommandName;
        int i=cmd.indexOf('/');
        if(i>-1){
            cmd=cmd.left(i);
        }
        return cmd;
    }

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
 * tk is an argument token (inner content)
 * it assumes that the command is at level--
 * \return command token
 */
Token getCommandTokenFromToken(Token tk)
{
    Token cmd;
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
                cmd = result;
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
    for (int i = tkPos; i >= 0; i--) {
		Token elem = tl.at(i);
        if(elem.level==level && (elem.type==Token::braces||elem.type==Token::openBrace) && tk.optionalCommandName=="NA"){
            // non-argument braces
            // reduce level
            --level;
        }
		if (elem.level == level && (elem.type == Token::command || elem.type == Token::commandUnknown) ) {
			result = elem;
			break;
		}
		if (elem.level < level)
			break;
	}
    // handle special case that open is not in the same line as the command token (e.g. issue #4030)
    if(result.dlh==nullptr){
        // search for command in previous lines
        QDocumentLineHandle *dlh=tl.first().dlh;
        if(dlh){
            QDocument *doc = dlh->document();
            int lineNr = doc->indexOf(dlh);
            while(lineNr>0){
                QDocumentLineHandle *previous = doc->line(lineNr - 1).handle();
                TokenList tl= previous->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
                for(int i=tl.length()-1;i>=0;--i){
                    Token elem = tl.at(i);
                    if (elem.level == level && (elem.type == Token::command || elem.type == Token::commandUnknown) ) {
                        result = elem;
                        return result;
                    }
                    if (elem.level < level)
                        break;
                }
                --lineNr;
            }
        }
    }
	return result;
}


/*!
 * \brief get completer context
 * \param dlh linehandle
 * \param column
 * \return 512 if token at column is 'width'
 */
EnumsTokenType::TokenType getCompleterContext(QDocumentLineHandle *dlh, int column)
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

    EnumsTokenType::TokenType type = tk.type;
	if (tk.subtype != Token::none && tk.subtype != Token::keyVal_val)
		type = tk.subtype;

    return type;
}
/*!
 * \brief return argument as a token list
 * \param tl initial token list, starting with the first token of an argument
 * \param type which is searched
 * \return argument as tokenlist
 */
TokenList getArgTL(const TokenList &tl, EnumsTokenType::TokenType type)
{
    for(int i=0;i<tl.size();++i) {
        Token tk=tl.value(i);
        if (tk.subtype==type) {
            TokenList result;
            if (Token::tkBraces().contains(tk.type)) {
                // braces token and all within
                int j=i+1;
                for(;j<tl.size();++j){
                    if(tl.value(j).start>(tk.start+tk.length)){
                        break;
                    }
                }
                result = tl.mid(i, j-i);
            }
            if (Token::tkOpen().contains(tk.type)) {
                result = tl.mid(i) + findRestArgTL(tk.dlh, Token::opposite(tk.type), -1,ConfigManager::RUNAWAYLIMIT);
            }
            if (Token::tkClose().contains(tk.type)) {
                result = tl.mid(0,i+1); // include closing token
            }
            return result;
        }
    }
    return TokenList();
}

TokenList findRestArgTL(QDocumentLineHandle *dlh, Token::TokenType type, int hint, int count)
{
    // dlh is current line, next line will be checked here!!!
    if (count <= 0)
        return TokenList(); // limit search depth
    QDocument *document = dlh->document();
    int index = document->indexOf(dlh,hint);
    if (index + 1 >= document->lines())
        return TokenList(); // last line reached
    dlh = document->line(index + 1).handle();
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    for (int i = 0; i < tl.length(); i++) {
        Token tk = tl.at(i);
        if (tk.type == type) {
            // closing found
            return tl.mid(0,i+1); // include closing token
        }
        if (Token::tkClose().contains(tk.type)) {
            // wrong closing found/ syntax problem
            //return value anyway
            return tl.mid(0,i+1); // include closing token
        }
    }
    return tl + findRestArgTL(dlh, type, index+1, count - 1);
}
/*!
 * \brief determine the number of available keyval arguments
 * In case more than 1 is defined
 * \param cd
 * \return number of keyval arguments
 */
int determineKeyValIndex(const CommandDescription &cd)
{
    int cnt=0;
    for(int i=0;i<cd.arguments.length();++i){
        if(cd.arguments.at(i).tokenType==Token::keyValArg){
            ++cnt;
        }
    }
    return cnt;
}


}  // namespace Parsing
