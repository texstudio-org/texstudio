#include "syntaxcheck.h"
#include "latexdocument.h"
#include "latexeditorview_config.h"
#include "spellerutility.h"
#include "tablemanipulation.h"
#include "latexparser/latexparsing.h"

/*! \class SyntaxCheck
*
* asynchrnous thread which checks latex syntax of the text lines
* It gets the linehandle via a queue, together with a ticket number.
* The ticket number is increased with every change of the text of a line, thus it can be determined of the processed handle is still unchanged and can be discarded otherwise.
* Syntaxinformation are stated via markers on the text.
* Furthermore environment information, especially tabular information are stored in "cookies" as they are needed in subsequent lines.
*
*/

/*!
* \brief contructor
* \param parent
*/
SyntaxCheck::SyntaxCheck(QObject *parent) :
    SafeThread(parent), mSyntaxChecking(true), syntaxErrorFormat(-1), ltxCommands(nullptr), newLtxCommandsAvailable(false), speller(nullptr), newSpeller(nullptr)
{
	mLinesLock.lock();
	stopped = false;
	mLines.clear();
	mLinesEnqueuedCounter.fetchAndStoreOrdered(0);
	mLinesLock.unlock();
}

/*!
* \brief set the errorformat for syntax errors
* \param errFormat
*/
void SyntaxCheck::setErrFormat(int errFormat)
{
	syntaxErrorFormat = errFormat;
}

/*!
* \brief add line to queue
* \param dlh linehandle
* \param previous linehandle of previous line
* \param stack tokenstack at line start (for handling open arguments of previous commands)
* \param clearOverlay clear syntaxcheck overlay
*/
void SyntaxCheck::putLine(QDocumentLineHandle *dlh, StackEnvironment previous, TokenStack stack, bool clearOverlay, int hint)
{
	REQUIRE(dlh);
    if(previous.isEmpty()) return; // sanity check as activeEnv at least contains "normal"
	SyntaxLine newLine;
	dlh->ref(); // impede deletion of handle while in syntax check queue
	dlh->lockForRead();
	newLine.ticket = dlh->getCurrentTicket();
	dlh->unlock();
	newLine.stack = stack;
	newLine.dlh = dlh;
	newLine.prevEnv = previous;
	newLine.clearOverlay = clearOverlay;
    newLine.hint=hint;
	mLinesLock.lock();
	mLines.enqueue(newLine);
	mLinesEnqueuedCounter.ref();
	mLinesLock.unlock();
	//avoid reading of any results before this execution is stopped
	//mResultLock.lock(); not possible under windows
	mLinesAvailable.release();
}

/*!
* \brief stop processing syntax checks
*/
void SyntaxCheck::stop()
{
	stopped = true;
	mLinesAvailable.release();
}

/*!
* \brief actual thread loop
*/
void SyntaxCheck::run()
{
	ltxCommands = new LatexParser();

	forever {
		//wait for enqueued lines
		mLinesAvailable.acquire();
		if (stopped) break;

		if (newLtxCommandsAvailable) {
			mLtxCommandLock.lock();
			if (newLtxCommandsAvailable) {
				newLtxCommandsAvailable = false;
				*ltxCommands = newLtxCommands;
                speller=newSpeller;
                mReplacementList=newReplacementList;
                mFormatList=newFormatList;
			}
			mLtxCommandLock.unlock();
		}

		// get Linedata
		mLinesLock.lock();
		SyntaxLine newLine = mLines.dequeue();
		mLinesLock.unlock();
		// do syntax check
		newLine.dlh->lockForRead();
		QString line = newLine.dlh->text();
		if (newLine.dlh->hasCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE)) {
			newLine.dlh->unlock();
			newLine.dlh->lockForWrite();
			newLine.dlh->removeCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE); //remove possible errors from unclosed envs
		}
		TokenList tl = newLine.dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        QPair<int,int> commentStart = newLine.dlh->getCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE).value<QPair<int,int> >();
		newLine.dlh->unlock();

		StackEnvironment activeEnv = newLine.prevEnv;
		Ranges newRanges;

        checkLine(line, newRanges, activeEnv, newLine.dlh, tl, newLine.stack, newLine.ticket,commentStart.first);
		// place results
        if (newLine.clearOverlay){
            QList<int> fmtList={syntaxErrorFormat,SpellerUtility::spellcheckErrorFormat};
            fmtList.append(mFormatList.values());
            newLine.dlh->clearOverlays(fmtList);
        }
		//if(newRanges.isEmpty()) continue;
		newLine.dlh->lockForWrite();
		if (newLine.ticket == newLine.dlh->getCurrentTicket()) { // discard results if text has been changed meanwhile
            newLine.dlh->setCookie(QDocumentLine::LEXER_COOKIE,QVariant::fromValue<TokenList>(tl));
            foreach (const Error &elem, newRanges){
                if(!mSyntaxChecking && (elem.type!=ERR_spelling) && (elem.type!=ERR_highlight) ){
                    // skip all syntax errors
                    continue;
                }
                int fmt= elem.type == ERR_spelling ? SpellerUtility::spellcheckErrorFormat : syntaxErrorFormat;
                fmt= elem.type == ERR_highlight ? elem.format : fmt;
                newLine.dlh->addOverlayNoLock(QFormatRange(elem.range.first, elem.range.second, fmt));
            }
            // add comment hightlight if present
            if(commentStart.first>=0){
                newLine.dlh->addOverlayNoLock(QFormatRange(commentStart.first, newLine.dlh->length()-commentStart.first, mFormatList["comment"]));
            }
			// active envs
			QVariant oldEnvVar = newLine.dlh->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
			StackEnvironment oldEnv;
			if (oldEnvVar.isValid())
				oldEnv = oldEnvVar.value<StackEnvironment>();
			bool cookieChanged = !equalEnvStack(oldEnv, activeEnv);
			//if excessCols has changed the subsequent lines need to be rechecked.
            // don't on initial check
            if (cookieChanged) {
				QVariant env;
				env.setValue(activeEnv);
				newLine.dlh->setCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE, env);
				newLine.dlh->ref(); // avoid being deleted while in queue
				//qDebug() << newLine.dlh->text() << ":" << activeEnv.size();
                emit checkNextLine(newLine.dlh, true, newLine.ticket, newLine.hint);
            }
		}
		newLine.dlh->unlock();

		newLine.dlh->deref(); //if deleted, delete now
	}

	delete ltxCommands;
	ltxCommands = nullptr;
}

/*!
* \brief get error description for syntax error in line 'dlh' at column 'pos'
* \param dlh linehandle
* \param pos column
* \param previous environment stack at start of line
* \param stack tokenstack at start of line
* \return error description
*/
QString SyntaxCheck::getErrorAt(QDocumentLineHandle *dlh, int pos, StackEnvironment previous, TokenStack stack)
{
	// do syntax check
	QString line = dlh->text();
	QStack<Environment> activeEnv = previous;
	TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
    QPair<int,int> commentStart = dlh->getCookieLocked(QDocumentLine::LEXER_COMMENTSTART_COOKIE).value<QPair<int,int> >();
	Ranges newRanges;
    checkLine(line, newRanges, activeEnv, dlh, tl, stack, dlh->getCurrentTicket(),commentStart.first);
	// add Error for unclosed env
	QVariant var = dlh->getCookieLocked(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE);
	if (var.isValid()) {
		activeEnv = var.value<StackEnvironment>();
		Q_ASSERT_X(activeEnv.size() == 1, "SyntaxCheck", "Cookie error");
		Environment env = activeEnv.top();
		QString cmd = "\\begin{" + env.name + "}";
		int index = line.lastIndexOf(cmd);
		if (index >= 0) {
			Error elem;
			elem.range = QPair<int, int>(index, cmd.length());
			elem.type = ERR_EnvNotClosed;
			newRanges.append(elem);
		}
	}
	// find Error at Position
	ErrorType result = ERR_none;
	foreach (const Error &elem, newRanges) {
		if (elem.range.second + elem.range.first < pos) continue;
		if (elem.range.first > pos) break;
		result = elem.type;
	}
    if(result==ERR_highlight){
        result=ERR_none; // filter out accidental highlight detection (test only)
    }
	// now generate Error message

	QStringList messages;  // indices have to match ErrorType
	messages << tr("no error")
			<< tr("unrecognized environment")
			<< tr("unrecognized command")
			<< tr("unrecognized math command")
			<< tr("unrecognized tabular command")
			<< tr("tabular command outside tabular env")
			<< tr("math command outside math env")
			<< tr("tabbing command outside tabbing env")
			<< tr("more cols in tabular than specified")
			<< tr("cols in tabular missing")
			<< tr("\\\\ missing")
			<< tr("closing environment which has not been opened")
			<< tr("environment not closed")
			<< tr("unrecognized key in key option")
			<< tr("unrecognized value in key option")
            << tr("command outside suitable env")
            << tr("spelling")
            << "highlight"; // mock message for arbitrary highlight. Will not be shown.
	Q_ASSERT(messages.length() == ERR_MAX);
	return messages.value(int(result), tr("unknown"));
}

/*!
* \brief set latex commands which are referenced for syntax checking
* \param cmds
*/
void SyntaxCheck::setLtxCommands(const LatexParser &cmds)
{
	if (stopped) return;
	mLtxCommandLock.lock();
	newLtxCommandsAvailable = true;
	newLtxCommands = cmds;
    mLtxCommandLock.unlock();
}

/*!
* \brief set new spellchecker engine (language)
* \param su new spell checker
*/
void SyntaxCheck::setSpeller(SpellerUtility *su)
{
    if (stopped) return;
    mLtxCommandLock.lock();
    newLtxCommandsAvailable = true;
    newSpeller=su;
    mLtxCommandLock.unlock();
}
/*!
 * \brief enable showing of Syntax errors
 * Since the syntax checker is also used for asynchronous syntax highligting/spell checking, it will not be disabled any more. Only syntax error will not be shown any more.
 * \param enable
 */
void SyntaxCheck::enableSyntaxCheck(const bool enable){
    if (stopped) return;
    mSyntaxChecking=enable;
}
/*!
 * \brief set character/text replacementList for spell checking
 * \param replacementList Map for characater/text replacement prior to spellchecking words. E.g. "u -> ü when german is activated
 */
void SyntaxCheck::setReplacementList(QMap<QString, QString> replacementList)
{
    if (stopped) return;
    mLtxCommandLock.lock();
    newLtxCommandsAvailable = true;
    newReplacementList=replacementList;
    mLtxCommandLock.unlock();
}

void SyntaxCheck::setFormats(QMap<QString, int> formatList)
{
    if (stopped) return;
    mLtxCommandLock.lock();
    newLtxCommandsAvailable = true;
    newFormatList=formatList;
    mLtxCommandLock.unlock();
}

#ifndef NO_TESTS

/*!
* \brief Wait for syntax checker to finish processing.
* \details Wait for syntax checker to finish processing. This method should be used only in self-tests because
* in some rare cases it could return too early before the syntax checker queue is fully processsed.
*/
void SyntaxCheck::waitForQueueProcess(void)
{
	int linesBefore, linesAfter;

	/*
	 * The logic in the following loop is not perfect because it could terminate the loop too early if it takes more
	 * than 10ms between the call to mLinesAvailable.acquire() and the following call to mLinesAvailable.release().
	 * Implementing the check properly requires bi-directional communication with the worker thread with commands to
	 * pause/unpause the worker thread which complicates the code too much just to handle testing.
	 */
	linesBefore = mLinesEnqueuedCounter.fetchAndAddOrdered(0);
	forever {
		for (int i = 0; i < 2; ++i) {
			QCoreApplication::processEvents(QEventLoop::AllEvents, 1000); 			// Process queued checkNextLine events
			QCoreApplication::sendPostedEvents(Q_NULLPTR, QEvent::DeferredDelete);		// Deferred delete must be processed explicitly. Using 0 for event_type does not work.
			wait(5); // Give the checkNextLine signal handler time to queue the next line
		}
		linesAfter = mLinesEnqueuedCounter.fetchAndAddOrdered(0);
		if ((linesBefore == linesAfter) && !mLinesAvailable.available()) {
			break;
		}
		linesBefore = linesAfter;
	}
}

#endif

/*!
* \brief check if top-most environment in 'envs' is `name`
* \param name environment name which is checked
* \param envs stack of environments
* \param id check for `id` of the environment, <0 means check is disabled
* \return environment id or 0
*/
int SyntaxCheck::topEnv(const QString &name, const StackEnvironment &envs, const int id)
{
	if (envs.isEmpty())
		return 0;

	Environment env = envs.top();
	if (env.name == name) {
		if (id < 0 || env.id == id)
			return env.id;
	}
	if (id < 0 && ltxCommands->environmentAliases.contains(env.name)) {
		QStringList altEnvs = ltxCommands->environmentAliases.values(env.name);
		foreach (const QString &altEnv, altEnvs) {
			if (altEnv == name)
				return env.id;
		}
	}
	return 0;
}

/*!
* \brief check if the environment stack contains a environment with name `name`
* \param parser reference to LatexParser. It is used to access environment aliases, e.g. equation is also a math environment
* \param name name of the checked environment
* \param envs stack of environements
* \param id if >=0 check if the env has the given id.
* \return environment id of  found env otherwise 0
*/
int SyntaxCheck::containsEnv(const LatexParser &parser, const QString &name, const StackEnvironment &envs, const int id)
{
	for (int i = envs.size() - 1; i > -1; --i) {
		Environment env = envs.at(i);
		if (env.name == name) {
			if (id < 0 || env.id == id)
				return env.id;
		}
		if (id < 0 && parser.environmentAliases.contains(env.name)) {
			QStringList altEnvs = parser.environmentAliases.values(env.name);
			foreach (const QString &altEnv, altEnvs) {
				if (altEnv == name)
					return env.id;
			}
		}
	}
    return 0;
}
/*!
 * \brief check if math env is active
 *
 * Similar to containsEnv, but determines if math is active as it can be disabled by a virtual text env
 * e.g. $abc \textbf{text}$
 * \param parser reference to LatexParser. It is used to access environment aliases, e.g. equation is also a math environment
 * \param envs stack of environements
 * \return math is active (true) or not (false)
 */
bool SyntaxCheck::checkMathEnvActive(const LatexParser &parser, const StackEnvironment &envs)
{
    for (int i = envs.size() - 1; i > -1; --i) {
        Environment env = envs.at(i);
        if (env.name == "math") {
                return true;
        }
        if (env.name == "text") {
                return false;
        }
        if (parser.environmentAliases.contains(env.name)) {
            QStringList altEnvs = parser.environmentAliases.values(env.name);
            foreach (const QString &altEnv, altEnvs) {
                if (altEnv == "math")
                    return true;
            }
        }
    }
    return false;
}

/*!
* \brief check if the command is valid in the environment stack
* \param cmd name of command
* \param envs environment stack
* \return is valid
*/
bool SyntaxCheck::checkCommand(const QString &cmd, const StackEnvironment &envs)
{
	for (int i = 0; i < envs.size(); ++i) {
		Environment env = envs.at(i);
		if (ltxCommands->possibleCommands.contains(env.name) && ltxCommands->possibleCommands.value(env.name).contains(cmd))
			return true;
		if (ltxCommands->environmentAliases.contains(env.name)) {
			QStringList altEnvs = ltxCommands->environmentAliases.values(env.name);
			foreach (const QString &altEnv, altEnvs) {
				if (ltxCommands->possibleCommands.contains(altEnv) && ltxCommands->possibleCommands.value(altEnv).contains(cmd))
					return true;
			}
		}
	}
	return false;
}

/*!
* \brief compare two environment stacks
* \param env1
* \param env2
* \return are equal
*/
bool SyntaxCheck::equalEnvStack(StackEnvironment env1, StackEnvironment env2)
{
	if (env1.isEmpty() || env2.isEmpty())
		return env1.isEmpty() && env2.isEmpty();
	if (env1.size() != env2.size())
		return false;
	for (int i = 0; i < env1.size(); i++) {
		if (env1.value(i) != env2.value(i))
			return false;
	}
	return true;
}

/*!
* \brief mark environment start
*
* This function is used to mark unclosed environment,i.e. environments which are unclosed at the end of the text
* \param env used environment
*/
void SyntaxCheck::markUnclosedEnv(Environment env)
{
	QDocumentLineHandle *dlh = env.dlh;
	if (!dlh)
		return;
	dlh->lockForWrite();
	if (dlh->getCurrentTicket() == env.ticket) {
		QString line = dlh->text();
		line = ltxCommands->cutComment(line);
		QString cmd = "\\begin{" + env.name + "}";
		int index = line.lastIndexOf(cmd);
		if (index >= 0) {
			Error elem;
			elem.range = QPair<int, int>(index, cmd.length());
			elem.type = ERR_EnvNotClosed;
            int fmt= elem.type == ERR_spelling ? SpellerUtility::spellcheckErrorFormat : syntaxErrorFormat;
            fmt= elem.type == ERR_highlight ? elem.format : fmt;
            dlh->addOverlayNoLock(QFormatRange(elem.range.first, elem.range.second, fmt));
			QVariant var_env;
			StackEnvironment activeEnv;
			activeEnv.append(env);
			var_env.setValue(activeEnv);
			dlh->setCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE, var_env); //ERR_EnvNotClosed;
		}
	}
	dlh->unlock();
}

/*!
* \brief check if the tokenstack contains a definition-token
* \param stack tokenstack
* \return contains a definition
*/
bool SyntaxCheck::stackContainsDefinition(const TokenStack &stack) const
{
	for (int i = 0; i < stack.size(); i++) {
		if (stack[i].subtype == Token::definition)
			return true;
	}
	return false;
}

/*!
* \brief check one line
*
* Checks one line. Context information needs to be given by newRanges,activeEnv,dlh and ticket.
* This method is obsolete as the new system relies on tokens.
* \param line text of line as string
* \param newRanges will return the result as ranges
* \param activeEnv environment context
* \param dlh linehandle
* \param tl tokenlist of line
* \param stack token stack at start of line
* \param ticket ticket number for current processed line
*/
void SyntaxCheck::checkLine(const QString &line, Ranges &newRanges, StackEnvironment &activeEnv, QDocumentLineHandle *dlh, TokenList &tl, TokenStack stack, int ticket,int commentStart)
{
	// do syntax check on that line
    //int cols = containsEnv(*ltxCommands, "tabular", activeEnv);

    // special treatment for empty lines with $/$$ math environmens
    // latex treats them as error, so do we
    if(tl.length()==0 && line.simplified().isEmpty() && !activeEnv.isEmpty() && activeEnv.top().name=="math"){
        if(activeEnv.top().origName=="$" || activeEnv.top().origName=="$$"){
            Environment env=activeEnv.pop();
            /* how to present an error without character present ?
            Error elem;
            elem.type = ERR_highlight;
            elem.format=mFormatList["math"];
            elem.range = QPair<int, int>(0, 0);
            newRanges.prepend(elem);
            */
        }
    }

    // check command-words
	for (int i = 0; i < tl.length(); i++) {
        Token &tk = tl[i];
        // remove top env if column exceeds columnlimit
        // used for formula -> brace -> {....}
        if(!activeEnv.isEmpty() && activeEnv.top().endingColumn>=0 && tk.start>activeEnv.top().endingColumn){
            Environment env=activeEnv.pop();
        }
		// ignore commands in definition arguments e.g. \newcommand{cmd}{definition}
		if (stackContainsDefinition(stack)) {
			Token top = stack.top();
			if (top.dlh != tk.dlh) {
				if (tk.type == Token::closeBrace) {
					stack.pop();
				} else
					continue;
			} else {
				if (tk.start < top.start + top.length)
					continue;
				else
					stack.pop();
			}
		}
		if (tk.subtype == Token::definition ) { // don't check command definitions
			if(tk.type == Token::braces || tk.type == Token::openBrace){
				stack.push(tk);
			}
			continue;
		}
        if (tk.type == Token::verbatim ) { // don't check command definitions
            // highlight
            Error elem;
            elem.range = QPair<int, int>(tk.start, tk.length);
            elem.type = ERR_highlight;
            elem.format=mFormatList["verbatim"];
            newRanges.append(elem);
            continue;
        }
		if (tk.type == Token::punctuation || tk.type == Token::symbol) {
			QString word = line.mid(tk.start, tk.length);
			QStringList forbiddenSymbols;
			forbiddenSymbols<<"^"<<"_";
            if(forbiddenSymbols.contains(word) && !checkMathEnvActive(*ltxCommands, activeEnv) && tk.subtype!=Token::formula){
				Error elem;
				elem.range = QPair<int, int>(tk.start, tk.length);
				elem.type = ERR_MathCommandOutsideMath;
				newRanges.append(elem);
			}
		}
        // math highlighting of formula
        if(tk.subtype==Token::formula){
            // highlight
            Error elem;
            elem.range = QPair<int, int>(tk.start, tk.length);
            elem.type = ERR_highlight;
            if(tk.type==Token::command){
                elem.format=mFormatList["#math"];
            }else{
                elem.format=mFormatList["math"];
            }
            if(tk.type==Token::braces || tk.type==Token::openBrace){
                // add to active env
                Environment env;
                env.name = "math";
                env.id = 1; // to be changed
                env.dlh = dlh;
                env.ticket = ticket;
                env.level = tk.level;
                env.startingColumn=tk.start+1;
                env.endingColumn=tk.start+tk.length-1;
                if(tk.type==Token::openBrace){
                    env.endingColumn=-1;
                }
                // avoid stacking same env (e.g. braces in braces, see #2411 )
                Environment topEnv=activeEnv.top();
                if(topEnv.name!=env.name)
                    activeEnv.push(env);
            }
            if(tk.type==Token::closeBrace){
                if(activeEnv.top().name=="math"){
                    activeEnv.pop();
                }
            }
            newRanges.append(elem);
        }
        // force text != math when text command is used, i.e. \textbf in math env, see #2603
        if(tk.subtype==Token::text){
            if(tk.type==Token::braces){
                // add to active env
                // invalidates math env as active
                Environment env;
                env.name = "text";
                env.id = 1; // to be changed
                env.dlh = dlh;
                env.ticket = ticket;
                env.level = tk.level;
                env.startingColumn=tk.start+1;
                env.endingColumn=tk.start+tk.length-1;
                // avoid stacking same env (e.g. braces in braces, see #2411 )
                Environment topEnv=activeEnv.top();
                if(topEnv.name!=env.name)
                    activeEnv.push(env);
            }
        }
        // spell checking
        if (speller->inlineSpellChecking && tk.type == Token::word && (tk.subtype == Token::text || tk.subtype == Token::title || tk.subtype == Token::shorttitle || tk.subtype == Token::todo || tk.subtype == Token::none)  && speller) {
            int tkLength=tk.length;
            QString word = tk.getText();
            if(i+1 < tl.length()){
                //check if next token is . or -
                Token tk1 = tl.at(i+1);
                if(tk1.type==Token::punctuation && tk1.start==(tk.start+tk.length) && !word.endsWith("\"")){
                    QString add=tk1.getText();
                    if(add=="."||add=="-"){
                        word+=add;
                        i++;
                        tkLength+=tk1.length;
                    }
                    if(add=="'"){
                        if(i+2 < tl.length()){
                            Token tk2 = tl.at(i+2);
                            if(tk2.type==Token::word && tk2.start==(tk1.start+tk1.length)){
                                add+=tk2.getText();
                                word+=add;
                                i+=2;
                                tkLength+=tk1.length+tk2.length;
                            }
                        }
                    }
                }
            }
            word = latexToPlainWordwithReplacementList(word, mReplacementList); //remove special chars
            if (speller->hideNonTextSpellingErrors && (checkMathEnvActive(*ltxCommands, activeEnv)||containsEnv(*ltxCommands, "picture", activeEnv)) ){
                word.clear();
                tk.ignoreSpelling=true;
            }else{
                tk.ignoreSpelling=false;
                if(containsEnv(*ltxCommands, "math", activeEnv)){
                    // in math env, highlight as math-text !
                    Error elem;
                    elem.type = ERR_highlight;
                    elem.format=mFormatList["#mathText"];
                    elem.range = QPair<int, int>(tk.start, tk.length);
                    newRanges.append(elem);
                }
            }
            if (tkLength>=3 && !word.isEmpty() && !speller->check(word) ) {
                if (word.endsWith('-') && speller->check(word.left(word.length() - 1)))
                    continue; // word ended with '-', without that letter, word is correct (e.g. set-up / german hypehantion)
                if(word.endsWith('.')){
                    tkLength--; // don't take point into misspelled word
                }
                Error elem;
                elem.range = QPair<int, int>(tk.start, tkLength);
                elem.type = ERR_spelling;
                newRanges.append(elem);
            }
        }
		if (tk.type == Token::commandUnknown) {
			QString word = line.mid(tk.start, tk.length);
			if (word.contains('@')) {
				continue; //ignore commands containg @
			}
			if (ltxCommands->mathStartCommands.contains(word) && (activeEnv.isEmpty() || activeEnv.top().name != "math")) {
				Environment env;
				env.name = "math";
				env.origName=word;
				env.id = 1; // to be changed
				env.dlh = dlh;
				env.ticket = ticket;
				env.level = tk.level;
                env.startingColumn=tk.start+tk.length;
				activeEnv.push(env);
                // highlight delimiter
                Error elem;
                elem.type = ERR_highlight;
                elem.format=mFormatList["&math"];
                elem.range = QPair<int, int>(tk.start, tk.length);
                newRanges.append(elem);
                continue;
			}
			if (ltxCommands->mathStopCommands.contains(word) && !activeEnv.isEmpty() && activeEnv.top().name == "math") {
				int i=ltxCommands->mathStopCommands.indexOf(word);
				QString txt=ltxCommands->mathStartCommands.value(i);
				if(activeEnv.top().origName==txt){
                    Environment env=activeEnv.pop();
                    Error elem;
                    elem.type = ERR_highlight;
                    elem.format=mFormatList["math"];
                    if(dlh == env.dlh){
                        //inside line
                        elem.range = QPair<int, int>(env.startingColumn, tk.start-env.startingColumn);
                    }else{
                        elem.range = QPair<int, int>(0, tk.start);
                    }
                    newRanges.prepend(elem);
                    // highlight delimiter
                    elem.type = ERR_highlight;
                    elem.format=mFormatList["&math"];
                    elem.range = QPair<int, int>(tk.start, tk.length);
                    newRanges.append(elem);
				}// ignore mismatching mathstop commands
				continue;
			}
			if (word == "\\\\" && topEnv("tabular", activeEnv) != 0 && tk.level == activeEnv.top().level) {
				if (activeEnv.top().excessCol < (activeEnv.top().id - 1)) {
					Error elem;
					elem.range = QPair<int, int>(tk.start, tk.length);
					elem.type = ERR_tooLittleCols;
					newRanges.append(elem);
				}
				if (activeEnv.top().excessCol >= (activeEnv.top().id)) {
					Error elem;
					elem.range = QPair<int, int>(tk.start, tk.length);
					elem.type = ERR_tooManyCols;
					newRanges.append(elem);
				}
				activeEnv.top().excessCol = 0;
				continue;
			}
            // command highlighing
            // this looks slow
            // TODO: optimize !
            foreach(const Environment &env,activeEnv){
                if(!env.dlh)
                    continue; //ignore "normal" env
                if(env.name=="document")
                    continue; //ignore "document" env
                foreach(const QString &key, mFormatList.keys()){
                    if(key.at(0)=='#'){
                        QStringList altEnvs = ltxCommands->environmentAliases.values(env.name);
                        altEnvs<<env.name;
                        if(altEnvs.contains(key.mid(1))){
                            Error elem;
                            elem.range = QPair<int, int>(tk.start, tk.length);
                            elem.type = ERR_highlight;
                            elem.format=mFormatList.value(key);
                            newRanges.append(elem);
                        }
                    }
                }
            }
			if (ltxCommands->possibleCommands["user"].contains(word) || ltxCommands->customCommands.contains(word))
				continue;
			if (!checkCommand(word, activeEnv)) {
				Error elem;
				elem.range = QPair<int, int>(tk.start, tk.length);
				elem.type = ERR_unrecognizedCommand;
				newRanges.append(elem);
				continue;
			}
		}
		if (tk.type == Token::env) {
			QString env = line.mid(tk.start, tk.length);
			// corresponds \end{env}
			if (!activeEnv.isEmpty()) {
				Environment tp = activeEnv.top();
				if (tp.name == env) {
                    Environment closingEnv=activeEnv.pop();
					if (tp.name == "tabular" || ltxCommands->environmentAliases.values(tp.name).contains("tabular")) {
						// correct length of col error if it exists
						if (!newRanges.isEmpty()) {
							Error &elem = newRanges.last();
							if (elem.type == ERR_tooManyCols && elem.range.first + elem.range.second > tk.start) {
								elem.range.second = tk.start - elem.range.first;
							}
						}
						// get new cols
                        //cols = containsEnv(*ltxCommands, "tabular", activeEnv);
					}
                    // handle higlighting
                    QStringList altEnvs = ltxCommands->environmentAliases.values(env);
                    altEnvs<<env;
                    foreach(const QString &key, mFormatList.keys()){
                        if(altEnvs.contains(key)){
                            Error elem;
                            int start= closingEnv.dlh==dlh ? closingEnv.startingColumn : 0;
                            int end=tk.start-1;
                            if(i>1){
                                Token tk=tl.at(i-2);
                                if(tk.type==Token::command && line.mid(tk.start, tk.length)=="\\end"){
                                    end=tk.start;
                                }
                            }
                            // trick to avoid coloring of end
                            if(!newRanges.isEmpty() && newRanges.last().type==ERR_highlight){
                                if(i>1){
                                    Token tk=tl.at(i-2); // skip over brace
                                    if(tk.type==Token::command && line.mid(tk.start,tk.length)=="\\end"){
                                        //previous token is end
                                        // see whether it was colored with *-keyword i.e. #math or #picture
                                        if(newRanges.last().range==QPair<int,int>(tk.start,tk.length)){
                                            // yes, remove !
                                            newRanges.removeLast();
                                        }
                                    }
                                }
                            }
                            elem.range = QPair<int, int>(start, end-start);
                            elem.type = ERR_highlight;
                            elem.format=mFormatList.value(key);
                            newRanges.append(elem);
                        }
                    }
				} else {
					Error elem;
					elem.range = QPair<int, int>(tk.start, tk.length);
					elem.type = ERR_closingUnopendEnv;
					newRanges.append(elem);
				}
			} else {
				Error elem;
				elem.range = QPair<int, int>(tk.start, tk.length);
				elem.type = ERR_closingUnopendEnv;
				newRanges.append(elem);
			}
		}

		if (tk.type == Token::beginEnv) {
			QString env = line.mid(tk.start, tk.length);
			// corresponds \begin{env}
			Environment tp;
			tp.name = env;
			tp.id = 1; //needs correction
			tp.excessCol = 0;
			tp.dlh = dlh;
            tp.startingColumn=tk.start+tk.length+1; // after closing brace
			tp.ticket = ticket;
			tp.level = tk.level-1; // tk is the argument, not the command, hence -1
			if (env == "tabular" || ltxCommands->environmentAliases.values(env).contains("tabular")) {
				// tabular env opened
				// get cols !!!!
				QString option;
				if ((env == "tabu") || (env == "longtabu")) { // special treatment as the env is rather not latex standard
					for (int k = i + 1; k < tl.length(); k++) {
						Token elem = tl.at(k);
						if (elem.level < tk.level-1)
							break;
						if (elem.level > tk.level)
							continue;
						if (elem.type == Token::braces) { // take the first mandatory argument at the correct level -> TODO: put colDef also for tabu correctly in lexer
							option = line.mid(elem.start + 1, elem.length - 2); // strip {}
							break; // first argument only !
						}
					}
				} else {
					if(env=="tikztimingtable"){
						option="ll"; // is always 2 columns
					}else{
						for (int k = i + 1; k < tl.length(); k++) {
							Token elem = tl.at(k);
							if (elem.level < tk.level)
								break;
							if (elem.level > tk.level)
								continue;
							if (elem.subtype == Token::colDef) {
								option = line.mid(elem.start + 1, elem.length - 2); // strip {}
								break;
							}
						}
					}
				}
				QSet<QString> translationMap=ltxCommands->possibleCommands.value("%columntypes");
				QStringList res = LatexTables::splitColDef(option);
				QStringList res2;
                foreach(const auto &elem, res){
					bool add=true;
                    foreach(const auto &i, translationMap){
						if(i.left(1)==elem && add){
							res2 << LatexTables::splitColDef(i.mid(1));
							add=false;
						}
					}
					if(add){
						res2<<elem;
					}
				}
                int cols = res2.count();
				tp.id = cols;
			}
			activeEnv.push(tp);
		}


        if (tk.type == Token::command) {
			QString word = line.mid(tk.start, tk.length);
			if(!tk.optionalCommandName.isEmpty()){
				word=tk.optionalCommandName;
			}
			Token tkEnvName;

			if (word == "\\begin" || word == "\\end") {
				// check complete expression e.g. \begin{something}
				if (tl.length() > i + 1 && tl.at(i + 1).type == Token::braces) {
					tkEnvName = tl.at(i + 1);
					word = word + line.mid(tkEnvName.start, tkEnvName.length);
				}
			}
            // special treatment for & in math
            if(word=="&" && containsEnv(*ltxCommands, "math", activeEnv)){
                Error elem;
                elem.range = QPair<int, int>(tk.start, tk.length);
                elem.type = ERR_highlight;
                elem.format=mFormatList.value("align-ampersand");
                newRanges.append(elem);
                continue;
            }

			if (ltxCommands->mathStartCommands.contains(word) && (activeEnv.isEmpty() || activeEnv.top().name != "math")) {
				Environment env;
				env.name = "math";
				env.origName=word;
				env.id = 1; // to be changed
				env.dlh = dlh;
				env.ticket = ticket;
				env.level = tk.level;
                env.startingColumn=tk.start+tk.length;
				activeEnv.push(env);
                // highlight delimiter
                Error elem;
                elem.type = ERR_highlight;
                elem.format=mFormatList["&math"];
                elem.range = QPair<int, int>(tk.start, tk.length);
                newRanges.append(elem);
				continue;
			}
			if (ltxCommands->mathStopCommands.contains(word) && !activeEnv.isEmpty() && activeEnv.top().name == "math") {
				int i=ltxCommands->mathStopCommands.indexOf(word);
				QString txt=ltxCommands->mathStartCommands.value(i);
				if(activeEnv.top().origName==txt){
                    Environment env=activeEnv.pop();
                    Error elem;
                    elem.type = ERR_highlight;
                    elem.format=mFormatList["math"];
                    if(dlh == env.dlh){
                        //inside line
                        elem.range = QPair<int, int>(env.startingColumn, tk.start-env.startingColumn);
                    }else{
                        elem.range = QPair<int, int>(0, tk.start);
                    }
                    newRanges.prepend(elem);
                    // highlight delimiter
                    elem.type = ERR_highlight;
                    elem.format=mFormatList["&math"];
                    elem.range = QPair<int, int>(tk.start, tk.length);
                    newRanges.append(elem);
				}// ignore mismatching mathstop commands
				continue;
			}

			//tabular checking
			if (topEnv("tabular", activeEnv) != 0) {
				if (word == "&") {
					activeEnv.top().excessCol++;
					if (activeEnv.top().excessCol >= activeEnv.top().id) {
						Error elem;
						elem.range = QPair<int, int>(tk.start, tk.length);
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
                    }else{
                        Error elem;
                        elem.range = QPair<int, int>(tk.start, tk.length);
                        elem.type = ERR_highlight;
                        elem.format=mFormatList.value("align-ampersand");
                        newRanges.append(elem);
                    }
					continue;
				}

				if ((word == "\\\\") || (word == "\\tabularnewline")) {
					if (activeEnv.top().excessCol < (activeEnv.top().id - 1)) {
						Error elem;
						elem.range = QPair<int, int>(tk.start, tk.length);
						elem.type = ERR_tooLittleCols;
						newRanges.append(elem);
					}
					if (activeEnv.top().excessCol >= (activeEnv.top().id)) {
						Error elem;
						elem.range = QPair<int, int>(tk.start, tk.length);
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
					}
					activeEnv.top().excessCol = 0;
					continue;
				}
				if (word == "\\multicolumn") {
					QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
					rxMultiColumn.setMinimal(true);
					int res = rxMultiColumn.indexIn(line, tk.start);
					if (res > -1) {
						// multicoulmn before &
						bool ok;
						int c = rxMultiColumn.cap(1).toInt(&ok);
						if (ok) {
							activeEnv.top().excessCol += c - 1;
						}
					}
					if (activeEnv.top().excessCol >= activeEnv.top().id) {
						Error elem;
						elem.range = QPair<int, int>(tk.start, tk.length);
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
					}
					continue;
				}

			}

            // command highlighing
            // this looks slow
            // TODO: optimize !
            foreach(const Environment &env,activeEnv){
                if(!env.dlh)
                    continue; //ignore "normal" env
                if(env.name=="document")
                    continue; //ignore "document" env
                foreach(const QString &key, mFormatList.keys()){
                    if(key.at(0)=='#'){
                        QStringList altEnvs = ltxCommands->environmentAliases.values(env.name);
                        altEnvs<<env.name;
                        if(altEnvs.contains(key.mid(1))){
                            Error elem;
                            elem.range = QPair<int, int>(tk.start, tk.length);
                            elem.type = ERR_highlight;
                            elem.format=mFormatList.value(key);
                            newRanges.append(elem);
                        }
                    }
                }
            }

			if (ltxCommands->possibleCommands["user"].contains(word) || ltxCommands->customCommands.contains(word))
				continue;

			if (!checkCommand(word, activeEnv)) {
				Error elem;
				if (tkEnvName.type == Token::braces) {
					Token tkEnvName = tl.at(i+1);
					elem.range = QPair<int, int>(tkEnvName.innerStart(), tkEnvName.innerLength());
					elem.type = ERR_unrecognizedEnvironment;
				} else {
					elem.range = QPair<int, int>(tk.start, tk.length);
					elem.type = ERR_unrecognizedCommand;
				}


				if (ltxCommands->possibleCommands["math"].contains(word))
					elem.type = ERR_MathCommandOutsideMath;
				if (ltxCommands->possibleCommands["tabular"].contains(word))
					elem.type = ERR_TabularCommandOutsideTab;
				if (ltxCommands->possibleCommands["tabbing"].contains(word))
					elem.type = ERR_TabbingCommandOutside;
				if(elem.type== ERR_unrecognizedEnvironment){
					// try to find command in unspecified envs
					QStringList keys=ltxCommands->possibleCommands.keys();
					keys.removeAll("math");
					keys.removeAll("tabular");
					keys.removeAll("tabbing");
					keys.removeAll("normal");
					foreach (QString key, keys) {
						if(key.contains("%"))
							continue;
						if(ltxCommands->possibleCommands[key].contains(word)){
							elem.type = ERR_commandOutsideEnv;
							break;
						}
					}
				}
                if(elem.type != ERR_MathCommandOutsideMath || tk.subtype!=Token::formula){
                    newRanges.append(elem);
                }
			}
		}
		if (tk.type == Token::specialArg) {
			QString value = line.mid(tk.start, tk.length);
			QString special = ltxCommands->mapSpecialArgs.value(int(tk.type - Token::specialArg));
			if (!ltxCommands->possibleCommands[special].contains(value)) {
				Error elem;
				elem.range = QPair<int, int>(tk.start, tk.length);
				elem.type = ERR_unrecognizedKey;
				newRanges.append(elem);
			}
		}
		if (tk.type == Token::keyVal_key) {
			// special treatment for key val checking
			QString command = tk.optionalCommandName;
			QString value = line.mid(tk.start, tk.length);

			// search stored keyvals
			QString elem;
            foreach(elem, ltxCommands->possibleCommands.keys()) {
				if (elem.startsWith("key%") && elem.mid(4) == command)
					break;
				if (elem.startsWith("key%") && elem.mid(4, command.length()) == command && elem.mid(4 + command.length(), 1) == "/" && !elem.endsWith("#c")) {
					// special treatment for distinguishing \command[keyvals]{test} where argument needs to equal test (used in yathesis.cwl)
					// now find mandatory argument
					QString subcommand;
					for (int k = i + 1; k < tl.length(); k++) {
						Token tk_elem = tl.at(k);
						if (tk_elem.level > tk.level)
							continue;
						if (tk_elem.level < tk.level)
							break;
						if (tk_elem.type == Token::braces) {
							subcommand = line.mid(tk_elem.start + 1, tk_elem.length - 2);
							if (elem == "key%" + command + "/" + subcommand) {
								break;
							} else {
								subcommand.clear();
							}
						}
					}
					if (!subcommand.isEmpty())
						elem = "key%" + command + "/" + subcommand;
					else
						elem.clear();
					break;
				}
				elem.clear();
			}
			if (!elem.isEmpty()) {
				QStringList lst = ltxCommands->possibleCommands[elem].values();
				QStringList::iterator iterator;
				QStringList toAppend;
				for (iterator = lst.begin(); iterator != lst.end(); ++iterator) {
					int i = iterator->indexOf("#");
					if (i > -1)
						*iterator = iterator->left(i);

					i = iterator->indexOf("=");
					if (i > -1) {
						*iterator = iterator->left(i);
					}
					if (iterator->startsWith("%")) {
						toAppend << ltxCommands->possibleCommands[*iterator].values();
					}
				}
				lst << toAppend;
				if (!lst.contains(value)) {
					Error elem;
					elem.range = QPair<int, int>(tk.start, tk.length);
					elem.type = ERR_unrecognizedKey;
					newRanges.append(elem);
				}
			}
		}
		if (tk.subtype == Token::keyVal_val) {
			//figure out keyval
			QString word = line.mid(tk.start, tk.length);
            if(word=="{" || tk.type==Token::braces){
                continue; // assume open brace is always valid or element in braces can't be checked (will get here again w/o braces)
            }
			// first get command
            QString command = tk.optionalCommandName;
            int index=command.indexOf('/');
            QString key=command.mid(index+1);
            command=command.left(index);
			// find if values are defined
			QString elem;
            foreach(elem, ltxCommands->possibleCommands.keys()) {
				if (elem.startsWith("key%") && elem.mid(4) == command)
					break;
				if (elem.startsWith("key%") && elem.mid(4, command.length()) == command && elem.mid(4 + command.length(), 1) == "/" && !elem.endsWith("#c")) {
					// special treatment for distinguishing \command[keyvals]{test} where argument needs to equal test (used in yathesis.cwl)
					// now find mandatory argument
					QString subcommand;
					for (int k = i + 1; k < tl.length(); k++) {
						Token tk_elem = tl.at(k);
						if (tk_elem.level > tk.level - 2)
							continue;
						if (tk_elem.level < tk.level - 2)
							break;
						if (tk_elem.type == Token::braces) {
							subcommand = line.mid(tk_elem.start + 1, tk_elem.length - 2);
							if (elem == "key%" + command + "/" + subcommand) {
								break;
							} else {
								subcommand.clear();
							}
						}
					}
					if (!subcommand.isEmpty())
						elem = "key%" + command + "/" + subcommand;
					break;
				}
				elem.clear();
			}
			if (!elem.isEmpty()) {
				// check whether keys is valid
				QStringList lst = ltxCommands->possibleCommands[elem].values();
				QStringList::iterator iterator;
				QString options;
				for (iterator = lst.begin(); iterator != lst.end(); ++iterator) {
					int i = iterator->indexOf("#");
					options.clear();
					if (i > -1) {
						options = iterator->mid(i + 1);
						*iterator = iterator->left(i);
					}

					if (iterator->endsWith("=")) {
						iterator->chop(1);
					}
					if (*iterator == key)
						break;
				}
				if (iterator != lst.end() && !options.isEmpty()) {
					if(options.startsWith("#")){
						continue; // ignore type keys, like width#L
					}
                    if(options.startsWith("%")){
                        if (!ltxCommands->possibleCommands[options].contains(word)) {
                            // special treatement for %color (mix)
                            if(options=="%color"){
                                if(word=="!") continue;
                                bool ok;
                                word.toInt(&ok);
                                if(ok) continue; // number !
                            }
                            Error elem;
                            elem.range = QPair<int, int>(tk.start, tk.length);
                            elem.type = ERR_unrecognizedKeyValues;
                            newRanges.append(elem);
                        }
                    }else{
                        QStringList l = options.split(",");
                        if (!l.contains(word)) {
                            Error elem;
                            elem.range = QPair<int, int>(tk.start, tk.length);
                            elem.type = ERR_unrecognizedKeyValues;
                            newRanges.append(elem);
                        }
                    }
				}
			}
		}
	}
    if(!activeEnv.isEmpty()){
        //check active env for env highlighting (math,verbatim)
        QStack<Environment>::Iterator it=activeEnv.begin();
        while(it!=activeEnv.end()){
            QStringList altEnvs = ltxCommands->environmentAliases.values(it->name);
            altEnvs<<it->name;
            foreach(const QString &key, mFormatList.keys()){
                if(altEnvs.contains(key)){
                    Error elem;
                    int start= it->dlh==dlh ? it->startingColumn : 0;
                    int length= it->endingColumn-start;
                    if(length<0){
                            length= commentStart>=0 ? commentStart-start : line.length()-start;
                    }
                    elem.range = QPair<int, int>(start, length);
                    elem.type = ERR_highlight;
                    elem.format=mFormatList.value(key);
                    newRanges.prepend(elem);  // draw this first and then other on top (e.g. keyword highlighting) !
                }
            }
            if(it->endingColumn>-1){
                activeEnv.erase(it);
            }else{
                ++it;
            }
        }

    }
}
