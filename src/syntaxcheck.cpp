#include "syntaxcheck.h"
#include "latexdocument.h"
#include "tablemanipulation.h"
#include "latexparser/latexreader.h"
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
    SafeThread(parent), syntaxErrorFormat(-1), ltxCommands(nullptr), newLtxCommandsAvailable(false)
{
	mLinesLock.lock();
	stopped = false;
	mLines.clear();
	mLinesLock.unlock();
	verbatimFormat = 0;
	//mLtxCommandLock.unlock();
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
void SyntaxCheck::putLine(QDocumentLineHandle *dlh, StackEnvironment previous, TokenStack stack, bool clearOverlay)
{
	REQUIRE(dlh);
	SyntaxLine newLine;
	dlh->ref(); // impede deletion of handle while in syntax check queue
	dlh->lockForRead();
	newLine.ticket = dlh->getCurrentTicket();
	dlh->unlock();
	newLine.stack = stack;
	newLine.dlh = dlh;
	newLine.prevEnv = previous;
	newLine.clearOverlay = clearOverlay;
	mLinesLock.lock();
	mLines.enqueue(newLine);
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
		if (newLine.dlh->hasCookie(3)) {
			newLine.dlh->unlock();
			newLine.dlh->lockForWrite();
			newLine.dlh->removeCookie(3); //remove possible errors from unclosed envs
		}
		TokenList tl = newLine.dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
		newLine.dlh->unlock();

		StackEnvironment activeEnv = newLine.prevEnv;
		Ranges newRanges;

		checkLine(line, newRanges, activeEnv, newLine.dlh, tl, newLine.stack, newLine.ticket);
		// place results
		if (newLine.clearOverlay) newLine.dlh->clearOverlays(syntaxErrorFormat);
		//if(newRanges.isEmpty()) continue;
		newLine.dlh->lockForWrite();
		if (newLine.ticket == newLine.dlh->getCurrentTicket()) { // discard results if text has been changed meanwhile
			foreach (const Error &elem, newRanges)
				newLine.dlh->addOverlayNoLock(QFormatRange(elem.range.first, elem.range.second, syntaxErrorFormat));

			// active envs
			QVariant oldEnvVar = newLine.dlh->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
			StackEnvironment oldEnv;
			if (oldEnvVar.isValid())
				oldEnv = oldEnvVar.value<StackEnvironment>();
			bool cookieChanged = !equalEnvStack(oldEnv, activeEnv);
			//if excessCols has changed the subsequent lines need to be rechecked.
			if (cookieChanged) {
				QVariant env;
				env.setValue(activeEnv);
				newLine.dlh->setCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE, env);
				newLine.dlh->ref(); // avoid being deleted while in queue
				//qDebug() << newLine.dlh->text() << ":" << activeEnv.size();
				emit checkNextLine(newLine.dlh, true, newLine.ticket);
			}
		}
		newLine.dlh->unlock();

		newLine.dlh->deref(); //if deleted, delete now
	}

	delete ltxCommands;
    ltxCommands = nullptr;
}

/*!
 * \brief check one line
 *
 * Checks one line. Context information needs to be given by newRanges,activeEnv,dlh and ticket.
 * This method is obsolete as the new system relies on tokens.
 * \warning obsolete method
 * \param line text of line as string
 * \param newRanges will return the result as ranges
 * \param activeEnv environmwent context
 * \param dlh linehandle
 * \param ticket ticket number for current processed line
 */
void SyntaxCheck::checkLine(const QString &line, Ranges &newRanges, StackEnvironment &activeEnv, QDocumentLineHandle *dlh, int ticket)
{
	// do syntax check on that line
	int cols = containsEnv(*ltxCommands, "tabular", activeEnv);
	LatexReader lr(*ltxCommands, line);
	int status;
	// check command-words
	while ((status = lr.nextWord(true))) {
		const QString &word = lr.word;
		const int &wordstart = lr.wordStartIndex;
		if (status == LatexReader::NW_COMMAND) {
			if (word == "\\begin" || word == "\\end") {
				QStringList options;
				QList<int> starts;
				ltxCommands->resolveCommandOptions(line, wordstart, options, &starts);
				if (options.size() > 0) {
					// adapt env stack
					QString env = options.first();
					if (env.startsWith("{"))
						env = env.remove(0, 1);
					if (env.endsWith("}"))
						env.chop(1);
					if (word == "\\begin") {
						Environment tp;
						tp.name = env;
						tp.id = 1; //needs correction
						tp.excessCol = 0;
						tp.dlh = dlh;
						tp.ticket = ticket;
						if (env == "tabular" || ltxCommands->environmentAliases.values(env).contains("tabular")) {
							// tabular env opened
							// get cols !!!!
							if (((env == "tabu") || (env == "longtabu")) && options.size() == 1) { // special treatment as the env is rather not latex standard
								QString helper = line.mid(starts.first() + options.first().length());
								helper = helper.trimmed();
								if (helper.startsWith("to ") || helper.startsWith("spread ")) {
									int i = helper.indexOf("{");
									if (i > -1) {
										QStringList options_zw;
										ltxCommands->resolveCommandOptions(helper, i, options_zw);
										if (!options_zw.isEmpty()) {
											options << options_zw.first();
										}
									}
								}
							}
							cols = LatexTables::getNumberOfColumns(options);
							tp.id = cols;
						}
						activeEnv.push(tp);
					} else {
						if (!activeEnv.isEmpty()) {
							Environment tp = activeEnv.top();
							if (tp.name == env) {
								activeEnv.pop();
								if (tp.name == "tabular" || ltxCommands->environmentAliases.values(tp.name).contains("tabular")) {
									// correct length of col error if it exists
									if (!newRanges.isEmpty()) {
										Error &elem = newRanges.last();
										if (elem.type == ERR_tooManyCols && elem.range.first + elem.range.second > wordstart) {
											elem.range.second = wordstart - elem.range.first;
										}
									}
									// get new cols
									cols = containsEnv(*ltxCommands, "tabular", activeEnv);
								}
							} else {
								Error elem;
								elem.range = QPair<int, int>(wordstart, word.length());
								elem.type = ERR_closingUnopendEnv;
								newRanges.append(elem);
							}
						} else {
							Error elem;
							elem.range = QPair<int, int>(wordstart, word.length());
							elem.type = ERR_closingUnopendEnv;
							newRanges.append(elem);
						}
					}
					// add env-name for syntax checking to "word"
					lr.word += options.first();
				}
			}
			if (ltxCommands->possibleCommands["%definition"].contains(word)) { // don't check in command definition
				QStringList options;
				QList<int> starts;
				ltxCommands->resolveCommandOptions(line, wordstart, options, &starts);
				for (int i = 1; i < options.count() && i < 4; i++) {
					QString option = options.at(i);
					if (option.startsWith("[")) {
						continue;
					}
					lr.index = starts.at(i) + option.length();
					break;
				}
			}
			if ( ltxCommands->possibleCommands["%ref"].contains(word) ||
			        ltxCommands->possibleCommands["%label"].contains(word) ||
			        ltxCommands->possibleCommands["%file"].contains(word) ||
			        ltxCommands->possibleCommands["%cite"].contains(word) ||
			        ltxCommands->possibleCommands["%bibitem"].contains(word) ||
			        ltxCommands->possibleCommands["%url"].contains(word)
			   ) { //don't check syntax in reference, label or include
				QStringList options;
				QList<int> starts;
				bool complete = ltxCommands->resolveCommandOptions(line, wordstart, options, &starts);
				while (options.size() > 0) {
					QString option = options.takeFirst();
					int start = starts.takeFirst();
					lr.index = start + option.length();
					if (!option.startsWith("[")) {  // handling of includegraphics should be improved !!! This impedes keyval checking
						break;
					}
				}
				if (!complete) {
					lr.index = line.length();  // last option continues beyond end of line: stop all further checking for this line
					break;
				}
			}
			if (ltxCommands->mathStartCommands.contains(word) && (activeEnv.isEmpty() || activeEnv.top().name != "math")) {
				Environment env;
				env.name = "math";
                env.origName=word;
				env.id = 1; // to be changed
				env.dlh = dlh;
				env.ticket = ticket;
				activeEnv.push(env);
				continue;
			}
			if (ltxCommands->mathStopCommands.contains(word) && !activeEnv.isEmpty() && activeEnv.top().name == "math") {
                int i=ltxCommands->mathStopCommands.indexOf(word);
                QString txt=ltxCommands->mathStartCommands.value(i);
                if(activeEnv.top().origName==txt){
                    activeEnv.pop();
                }// ignore mismatching mathstop commands
				continue;
			}

			//tabular checking
			if (topEnv("tabular", activeEnv) != 0) {
				if (word == "&") {
					activeEnv.top().excessCol++;
					if (activeEnv.top().excessCol >= activeEnv.top().id) {
						Error elem;
						elem.range = QPair<int, int>(wordstart, word.length());
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
					}
					continue;
				}
				if ((word == "\\\\") || (word == "\\tabularnewline")) {
					if (activeEnv.top().excessCol < (activeEnv.top().id - 1)) {
						Error elem;
						elem.range = QPair<int, int>(wordstart, word.length());
						elem.type = ERR_tooLittleCols;
						newRanges.append(elem);
					}
					if (activeEnv.top().excessCol >= (activeEnv.top().id)) {
						Error elem;
						elem.range = QPair<int, int>(wordstart, word.length());
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
					}
					activeEnv.top().excessCol = 0;
					continue;
				}
				if (word == "\\multicolumn") {
					QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
					rxMultiColumn.setMinimal(true);
					int res = rxMultiColumn.indexIn(line, wordstart);
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
						elem.range = QPair<int, int>(wordstart, word.length());
						elem.type = ERR_tooManyCols;
						newRanges.append(elem);
					}
					continue;
				}

			}
			// ignore commands containing @
			if (word.contains('@'))
				continue;

            // don't highlight custom commands
            if (ltxCommands->possibleCommands["user"].contains(word) || ltxCommands->customCommands.contains(word))
                continue;

			if (!checkCommand(word, activeEnv)) {
				Error elem;
				elem.range = QPair<int, int>(wordstart, word.length());
				elem.type = ERR_unrecognizedCommand;

				if (ltxCommands->possibleCommands["math"].contains(word))
					elem.type = ERR_MathCommandOutsideMath;
				if (ltxCommands->possibleCommands["tabular"].contains(word))
					elem.type = ERR_TabularCommandOutsideTab;
				if (ltxCommands->possibleCommands["tabbing"].contains(word))
					elem.type = ERR_TabbingCommandOutside;
				newRanges.append(elem);
			}
		}
		if (status != LatexReader::NW_COMMAND) {
			// special treatment for key val checking
			QString command, value;
			LatexParser::ContextType ctx = ltxCommands->findContext(line, lr.wordStartIndex, command, value);
			if (ctx == LatexParser::Keyval) {
				// search stored keyvals
				QString elem = "key%" + command;
				if (elem.endsWith("#c"))
					elem.clear();
				if (!elem.isEmpty()) {
					// check whether keys is valid
					QStringList lst = ltxCommands->possibleCommands[elem].values();
					QStringList::iterator iterator;
					for (iterator = lst.begin(); iterator != lst.end(); ++iterator) {
						int i = iterator->indexOf("#");
						if (i > -1)
							*iterator = iterator->left(i);

						if (iterator->endsWith("=")) {
							iterator->chop(1);
						}
					}
					if (!lst.contains(word)) {
						Error elem;
						elem.range = QPair<int, int>(wordstart, word.length());
						elem.type = ERR_unrecognizedKey;
						newRanges.append(elem);
					}

				}

			}
			if (ctx == LatexParser::KeyvalValue && word.simplified() != "," && !command.endsWith("#c")) {
				//figure out keyval
				int i = lr.wordStartIndex;
				while (i > 0 && line.at(i - 1).isLetter())
					i--;
				if (i > 0 && line.at(i - 1) == QChar('=')) {
					int j = --i;
					while (i > 0 && line.at(i - 1).isLetter())
						i--;
					QString key = line.mid(i, j - i);

					QString elem;
					foreach (elem, ltxCommands->possibleCommands.keys()) {
						if (elem.startsWith("key%") && elem.mid(4) == command)
							break;
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
							QStringList l = options.split(",");
							if (!l.contains(word)) {
								Error elem;
								elem.range = QPair<int, int>(wordstart, word.length());
								elem.type = ERR_unrecognizedKeyValues;
								newRanges.append(elem);
							}
						}
					}
				}
			}
		}
	}
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
	Ranges newRanges;
	checkLine(line, newRanges, activeEnv, dlh, tl, stack, dlh->getCurrentTicket());
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
	         << tr("command outside suitable env");
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
 * \brief wait for queue to be empty. Used for self-test only.
 */
void SyntaxCheck::waitForQueueProcess()
{
	while (!crashed && mLinesAvailable.available() > 0) {
		wait(1);
	}
}

/*!
 * \brief check if queue is empty. Used for self-test only.
 * \return queue is not empty
 */
bool SyntaxCheck::queuedLines()
{
	return mLinesAvailable.available() > 0;
}

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
			dlh->addOverlayNoLock(QFormatRange(elem.range.first, elem.range.second, syntaxErrorFormat));
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
void SyntaxCheck::checkLine(const QString &line, Ranges &newRanges, StackEnvironment &activeEnv, QDocumentLineHandle *dlh, TokenList tl, TokenStack stack, int ticket)
{
	// do syntax check on that line
	int cols = containsEnv(*ltxCommands, "tabular", activeEnv);

	// check command-words
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
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
        if (tk.type == Token::punctuation || tk.type == Token::symbol) {
            QString word = line.mid(tk.start, tk.length);
            QStringList forbiddenSymbols;
            forbiddenSymbols<<"^"<<"_";
            if(forbiddenSymbols.contains(word) && !containsEnv(*ltxCommands, "math", activeEnv)){
                Error elem;
                elem.range = QPair<int, int>(tk.start, tk.length);
                elem.type = ERR_MathCommandOutsideMath;
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
				activeEnv.push(env);
				continue;
			}
			if (ltxCommands->mathStopCommands.contains(word) && !activeEnv.isEmpty() && activeEnv.top().name == "math") {
                int i=ltxCommands->mathStopCommands.indexOf(word);
                QString txt=ltxCommands->mathStartCommands.value(i);
                if(activeEnv.top().origName==txt){
                    activeEnv.pop();
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
					activeEnv.pop();
					if (tp.name == "tabular" || ltxCommands->environmentAliases.values(tp.name).contains("tabular")) {
						// correct length of col error if it exists
						if (!newRanges.isEmpty()) {
							Error &elem = newRanges.last();
							if (elem.type == ERR_tooManyCols && elem.range.first + elem.range.second > tk.start) {
								elem.range.second = tk.start - elem.range.first;
							}
						}
						// get new cols
						cols = containsEnv(*ltxCommands, "tabular", activeEnv);
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
				QStringList res = LatexTables::splitColDef(option);
				cols = res.count();
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

			if (ltxCommands->mathStartCommands.contains(word) && (activeEnv.isEmpty() || activeEnv.top().name != "math")) {
				Environment env;
				env.name = "math";
                env.origName=word;
				env.id = 1; // to be changed
				env.dlh = dlh;
				env.ticket = ticket;
                env.level = tk.level;
				activeEnv.push(env);
				continue;
			}
			if (ltxCommands->mathStopCommands.contains(word) && !activeEnv.isEmpty() && activeEnv.top().name == "math") {
                int i=ltxCommands->mathStopCommands.indexOf(word);
                QString txt=ltxCommands->mathStartCommands.value(i);
                if(activeEnv.top().origName==txt){
                    activeEnv.pop();
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
				newRanges.append(elem);
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
			foreach (elem, ltxCommands->possibleCommands.keys()) {
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
			// first get command
			Token cmd = Parsing::getCommandTokenFromToken(tl, tk);
			QString command = line.mid(cmd.start, cmd.length);
			// figure out key
			QString key;
			for (int k = i - 1; k >= 0; k--) {
				Token elem = tl.at(k);
				if (elem.level == tk.level - 1) {
					if (elem.type == Token::keyVal_key) {
						key = line.mid(elem.start, elem.length);
					}
					break;
				}
			}
			// find if values are defined
			QString elem;
			foreach (elem, ltxCommands->possibleCommands.keys()) {
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
