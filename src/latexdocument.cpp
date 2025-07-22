#include "latexdocument.h"
#include "latexeditorview.h"
#include "qdocument.h"
#include "qformatscheme.h"
#include "qlanguagedefinition.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "qdocumentcursor.h"
#include "qeditor.h"
#include "latexcompleter.h"
#include "latexcompleter_config.h"
#include "configmanagerinterface.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexparsing.h"
#include "configmanager.h"
#include <QtConcurrent>


//FileNamePair::FileNamePair(const QString& rel):relative(rel){};
FileNamePair::FileNamePair(const QString &rel, const QString &abs): relative(rel), absolute(abs) {}
UserCommandPair::UserCommandPair(const QString &name, const CodeSnippet &snippet): name(name), snippet(snippet) {}

UserCommandPair::UserCommandPair(const QString &name, const QString &snippet): name(name), snippet(snippet)
{
    this->snippet.type=CodeSnippet::userCommand;
}

// languages for LaTeX syntax checking (exact name from qnfa file)
const QSet<QString> LatexDocument::LATEX_LIKE_LANGUAGES = QSet<QString>() << "(La)TeX" << "Pweave" << "Sweave" << "TeX dtx file";
/*! \brief constructor
 * sets up structure for structure view
 * starts the syntax checker in a separate thread
 */
LatexDocument::LatexDocument(QObject *parent): QDocument(parent), remeberAutoReload(false), mayHaveDiffMarkers(false), edView(nullptr), mAppendixLine(nullptr), mBeyondEnd(nullptr)
{

    /*magicCommentList->title = tr("MAGIC_COMMENTS");
	labelList->title = tr("LABELS");
	todoList->title = tr("TODO");
	bibTeXList->title = tr("BIBLIOGRAPHY");
    blockList->title = tr("BLOCKS"); */
	mLabelItem.clear();
	mBibItem.clear();
	mUserCommandList.clear();
	mMentionedBibTeXFiles.clear();
	masterDocument = nullptr;
	this->parent = nullptr;

	unclosedEnv.id = -1;
	syntaxChecking = true;

    lp = QSharedPointer<LatexParser>::create();
    *lp= LatexParser::getInstance();

    updateSettings();
    synChecker.setRUNAWAYLIMIT(ConfigManager::RUNAWAYLIMIT);
    synChecker.setLtxCommands(lp);

    connect(&synChecker, SIGNAL(checkNextLine(QDocumentLineHandle*,bool,int,int)), SLOT(checkNextLine(QDocumentLineHandle*,bool,int,int)), Qt::QueuedConnection);
}

LatexDocument::~LatexDocument()
{
    synChecker.stop();
    synChecker.wait();

	foreach (QDocumentLineHandle *dlh, mLineSnapshot) {
		dlh->deref();
	}
	mLineSnapshot.clear();

    qDeleteAll(docStructure);
}

void LatexDocument::setFileName(const QString &fileName)
{
	this->setFileNameInternal(fileName);
	this->edView = nullptr;
}

void LatexDocument::setEditorView(LatexEditorView *edView)
{
	this->setFileNameInternal(edView->editor->fileName(), edView->editor->fileInfo());
	this->edView = edView;
}

/// Set the values of this->fileName and this->this->fileInfo
/// Note: QFileInfo is cached, so the performance cost to recreate
/// QFileInfo (instead of copying it from edView) should be very small.
void LatexDocument::setFileNameInternal(const QString &fileName)
{
	setFileNameInternal(fileName, QFileInfo(fileName));
}
/// Set the values of this->fileName and this->this->fileInfo
void LatexDocument::setFileNameInternal(const QString &fileName, const QFileInfo& pairedFileInfo)
{
	Q_ASSERT(fileName.isEmpty() || pairedFileInfo.isAbsolute());
	this->fileName = fileName;
    //QFileInfo info = getNonSymbolicFileInfo(pairedFileInfo);
    this->fileInfo = pairedFileInfo;
}

LatexEditorView *LatexDocument::getEditorView() const
{
	return this->edView;
}

QString LatexDocument::getFileName() const
{
	return fileName;
}

bool LatexDocument::isHidden()
{
	return parent->hiddenDocuments.contains(this);
}

QFileInfo LatexDocument::getFileInfo() const
{
    return fileInfo;
}
/*!
 * \brief declare file as imported file
 * Imported means imported via \subimport/\import
 * Included files here are relative to this file
 * \param state
 */
void LatexDocument::setAsImportedFile(bool state)
{
    importedFile=state;
}
/*!
 * \brief read state importedFile
 * \return
 */
bool LatexDocument::getStateImportedFile()
{
    return importedFile;
}

QMultiHash<QDocumentLineHandle *, FileNamePair> &LatexDocument::mentionedBibTeXFiles()
{
	return mMentionedBibTeXFiles;
}

const QMultiHash<QDocumentLineHandle *, FileNamePair> &LatexDocument::mentionedBibTeXFiles() const
{
	return mMentionedBibTeXFiles;
}

QStringList LatexDocument::listOfMentionedBibTeXFiles() const
{
	QStringList result;
    foreach (const FileNamePair &fnp, mMentionedBibTeXFiles)
		result << fnp.absolute;
	return result;
}
/*! select a complete section with the text
 * this method is called from structureview via contex menu
 *
 */
QDocumentSelection LatexDocument::sectionSelection(StructureEntry *section)
{
	QDocumentSelection result = { -1, -1, -1, -1};

	if (section->type != StructureEntry::SE_SECTION) return result;
	int startLine = section->getRealLineNumber();

	// find next section or higher
    const int level=section->level;
    StructureEntry *se=nullptr;
    for(auto iter=docStructure.cbegin();iter!=docStructure.cend();++iter){
        se=*iter;
        if(se==section){
            do{
                ++iter;
                se=*iter;
            }while(iter!=docStructure.cend() && (se->type!=StructureEntry::SE_SECTION || se->level>level));
            if(iter==docStructure.cend()){
                se=nullptr;
            }else{
                se=*iter;
            }
            break;
        }
    }
	int endingLine = -1;
    if (se) {
        endingLine = se->getRealLineNumber();
	} else {
		// no ending section but end of document
        endingLine = findLineContaining("\\end{document}", startLine, Qt::CaseInsensitive);
		if (endingLine < 0) endingLine = lines();
	}

	result.startLine = startLine;
	result.endLine = endingLine;
	result.end = 0;
	result.start = 0;
	return result;
}

void LatexDocument::clearAppendix()
{
    mAppendixLine = nullptr;
}


/*! clear all internal data
 * preparation for rebuilding structure or for first parsing
 */
void LatexDocument::initClearStructure()
{
	mUserCommandList.clear();
	mLabelItem.clear();
	mBibItem.clear();
	mRefItem.clear();
	mMentionedBibTeXFiles.clear();

	mAppendixLine = nullptr;
	mBeyondEnd = nullptr;

    // reset line states
    for(int i=0;i<lines();++i){
        line(i).setFlag(QDocumentLine::lexedPass1,false);
        line(i).setFlag(QDocumentLine::lexedPass2Complete,false);
        line(i).setFlag(QDocumentLine::lexedPass2InComplete,false);
        line(i).setFlag(QDocumentLine::argumentsParsed,false);
    }


    emit structureUpdated();

    qDeleteAll(docStructure);
    docStructure.clear();
}
/*! rebuild structure view completely
 *  /note very expensive call
 */
void LatexDocument::updateStructure()
{
	initClearStructure();

	patchStructure(0, -1);
}

/*! Removes a deleted line from the structure view
*/
void LatexDocument::patchStructureRemoval(QDocumentLineHandle *dlh, int hint,int count)
{
	bool completerNeedsUpdate = false;
	bool bibTeXFilesNeedsUpdate = false;
	bool updateSyntaxCheck = false;
    QStringList removedUsepackages;

    for(int i=0;i<count;++i){
        if (mLabelItem.contains(dlh)) {
            QList<ReferencePair> labels = mLabelItem.values(dlh);
            completerNeedsUpdate = true;
            mLabelItem.remove(dlh);
            foreach (const ReferencePair &rp, labels)
                updateRefsLabels(rp.name);
        }
        mRefItem.remove(dlh);
        if (mMentionedBibTeXFiles.remove(dlh))
            bibTeXFilesNeedsUpdate = true;
        if (mBibItem.contains(dlh)) {
            mBibItem.remove(dlh);
            bibTeXFilesNeedsUpdate = true;
        }

        QList<UserCommandPair> commands = mUserCommandList.values(dlh);
        foreach (UserCommandPair elem, commands) {
            QString word = elem.snippet.word;
            if(word.length()==1){
                for (auto i:ltxCommands.possibleCommands["%columntypes"]) {
                    if(i.left(1)==word){
                        ltxCommands.possibleCommands["%columntypes"].remove(i);
                        break;
                    }
                }
            }else{
                if(word.startsWith("%")){
                    int i = word.indexOf('%', 1);
                    QString category = word.left(i);
                    QString elem = word.mid(i + 1);
                    lp->possibleCommands[category].remove(elem);
                    ltxCommands.possibleCommands[category].remove(elem);
                }else{
                    int i = word.indexOf("{");
                    if (i >= 0) word = word.left(i);
                    ltxCommands.possibleCommands["user"].remove(word);
                }
            }
            updateSyntaxCheck = true;
        }
        mUserCommandList.remove(dlh);

        QStringList removeIncludes = mIncludedFilesList.values(dlh);
        removeIncludes.append(mImportedFilesList.values(dlh));
        if (mIncludedFilesList.remove(dlh) > 0 || mImportedFilesList.remove(dlh)>0) {
            parent->removeDocs(removeIncludes);
            parent->updateMasterSlaveRelations(this);
        }


        removedUsepackages << mUsepackageList.values(dlh);
        mUsepackageList.remove(dlh);

        if (dlh == mAppendixLine) {
            updateContext(mAppendixLine, nullptr, StructureEntry::InAppendix);
            mAppendixLine = nullptr;
        }

        int linenr = indexOf(dlh,hint);
        if (linenr == -1) linenr = lines();

        // check if line contains bookmark
        if (edView) {
            int id=edView->hasBookmark(dlh);
            if (id>-2) {
                emit bookmarkRemoved(dlh);
                edView->removeBookmark(dlh, id);
            }
        }

        if(i+1<count){
            // not at last element yet
            dlh=line(linenr+1).handle();
        }
    }

    // cut from structure
    removeRangeFromStructure(hint,count);

    emit structureUpdated();

	if (bibTeXFilesNeedsUpdate)
		emit updateBibTeXFiles();

	if (completerNeedsUpdate || bibTeXFilesNeedsUpdate)
		emit updateCompleter();

    if (!removedUsepackages.isEmpty() || updateSyntaxCheck) {
        updateCompletionFiles();
    }

}

// workaround to prevent false command recognition in definitions:
// Example: In \newcommand{\seeref}[1]{\ref{(see #1)}} the argument of \ref is not actually a label.
// Using this function we detect this case.
// TODO: a more general solution should make this dependent on if the command is inside a definition.
// However this requires a restructuring of the patchStructure. It would also allow categorizing
// the redefined command, e.g. as "%ref"
inline bool isDefinitionArgument(const QString &arg)
{
	// equivalent to checking the regexp #[0-9], but faster:
	int pos = arg.indexOf("#");
	return (pos >= 0 && pos < arg.length() - 1 && arg[pos + 1].isDigit());
}
/*!
 * \brief first pass for lexing latex
 * Just translates text into basic tokens like commands, words, braces, etc.
 * \param lineNr
 * \param count
 */
void LatexDocument::lexLinesSimple(const int lineNr,const int count){
    QList<QDocumentLineHandle *> l_dlh;
    for (int i = lineNr; i < lineNr + count; i++) {
        if(line(i).hasFlag(QDocumentLine::lexedPass1)) continue;
        l_dlh << line(i).handle();
        line(i).setFlag(QDocumentLine::lexedPass1,true);
        line(i).setFlag(QDocumentLine::lexedPass2Complete,false);
        line(i).setFlag(QDocumentLine::lexedPass2InComplete,false);
        line(i).setFlag(QDocumentLine::argumentsParsed,false);
    }
    QtConcurrent::blockingMap(l_dlh,Parsing::simpleLexLatexLine);
}

/*!
 * \brief lex lines for latex commads
 * Translates text into tokens
 * \param lineNr
 * \param count
 * \return stoppedAtLine lexing was cut short to allow loading of packages (root document)
 */
int LatexDocument::lexLines(int &lineNr,int &count,bool recheck){
    //first pass: simple lex
    if(!recheck)
        lexLinesSimple(lineNr,count);

    TokenStack oldRemainder;
    CommandStack oldCommandStack;

    int stoppedAtLine=-1;
    TokenList l_tkFilter;
    QDocumentLineHandle *lastHandle = line(lineNr - 1).handle();
    if (lastHandle) {
        oldRemainder = lastHandle->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
        oldCommandStack = lastHandle->getCookieLocked(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
    }
    for (int i = lineNr; i < lineCount() && i < lineNr + count; ++i) {
        if (line(i).text() == "\\begin{document}"){
            if(lineNr==0 && count==lineCount() && !recheck) {
                stoppedAtLine=i;
                break; // do recheck quickly as usepackages probably need to be loaded
            }
        }
        if(line(i).hasFlag(QDocumentLine::lexedPass2Complete)){
            oldRemainder = line(i).getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
            oldCommandStack = line(i).getCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
            continue;
        }else{
            bool remainderChanged = Parsing::latexDetermineContexts2(line(i).handle(), oldRemainder, oldCommandStack, lp);
            bool leaveLoop=false;
            if(oldRemainder.size()>0){
                for(int k=0;k<oldRemainder.size();++k){
                    Token tk=oldRemainder.at(k);
                    int idx=l_tkFilter.indexOf(tk);
                    if(idx>=0){
                        oldRemainder.remove(k); // discard run-away argument
                        --k;
                        l_tkFilter.removeAt(idx);
                        leaveLoop=true;
                    }
                }
                if(leaveLoop){
                    // store filtered as remainder into line
                    QDocumentLineHandle *dlh=line(i).handle();
                    dlh->lockForWrite();
                    dlh->setCookie(QDocumentLine::LEXER_REMAINDER_COOKIE, QVariant::fromValue<TokenStack>(oldRemainder));
                    dlh->unlock();
                    continue;
                }

                for(int k=0;k<oldRemainder.size();++k){
                    Token tk=oldRemainder.at(k);
                    if(tk.type==Token::openBrace && tk.subtype!= Token::text && tk.subtype!= Token::none && tk.argLevel==0){
                        // redo with filtering out this offending
                        l_tkFilter.append(tk);
                    }
                }
                if(!l_tkFilter.isEmpty()){
                    // reset line status
                    for(int j=i-ConfigManager::RUNAWAYLIMIT;j<=i;++j){
                        line(j).setFlag(QDocumentLine::lexedPass2Complete,false);
                        line(j).setFlag(QDocumentLine::lexedPass2InComplete,false);
                        line(j).setFlag(QDocumentLine::argumentsParsed,false);
                    }
                    i=i-ConfigManager::RUNAWAYLIMIT;
                    lastHandle = line(i).handle();
                    if (lastHandle) {
                        oldRemainder = lastHandle->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
                        oldCommandStack = lastHandle->getCookieLocked(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
                    }else{
                        oldRemainder.clear();
                        oldCommandStack.clear();
                    }
                    continue;
                }
            }
            if (remainderChanged && i + 1 < lineCount()) { // remainder changed in last line which is to be checked
                line(i + 1).setFlag(QDocumentLine::lexedPass2Complete,false);
                if(i + 1 == lineNr + count){
                    ++count; // check also next line ...
                }
            }
        }
    }
    return stoppedAtLine;
}
/*!
 * \brief handle special comments (TODO, MAGIC comments)
 * comment detection moved to lexer as formats are not yet generated here (e.g. on first load)
 * \param dlh
 * \return
 */
void LatexDocument::handleComments(QDocumentLineHandle *dlh, int &curLineNr, std::list<StructureEntry*>::iterator &docStructureIter){
    //
    QPair<int,int> commentStart = dlh->getCookieLocked(QDocumentLine::LEXER_COMMENTSTART_COOKIE).value<QPair<int,int> >();
    int col = commentStart.first;
    if (col >= 0) {
        // all
        //// TODO marker
        QString curLine=dlh->text();
        QString text = curLine.mid(col);
        QString regularExpression=ConfigManagerInterface::getInstance()->getOption("Editor/todo comment regExp").toString();
        static QRegularExpression rx(regularExpression);
        if (rx.match(text).hasMatch()) {  // other todos like \todo are handled by the tokenizer below.
            StructureEntry *newTodo = new StructureEntry(this, StructureEntry::SE_TODO);
            newTodo->title = text.mid(1).trimmed();
            newTodo->setLine(dlh, curLineNr);
            replaceOrAdd(docStructureIter,dlh,newTodo);
            // save comment type into cookie
            commentStart.second=Token::todoComment;
            dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
        }
        //// parameter comment
        if (curLine.startsWith("%&")) {
            int start = curLine.indexOf("-job-name=");
            if (start >= 0) {
                int end = start + 10; // += "-job-name=".length;
                if (end < curLine.length() && curLine[end] == '"') {
                    // quoted filename
                    end = curLine.indexOf('"', end + 1);
                    if (end >= 0) {
                        end += 1;  // include closing quotation mark
                        addMagicComment(curLine.mid(start, end - start), curLineNr, docStructureIter);
                    }
                } else {
                    end = curLine.indexOf(' ', end + 1);
                    if (end >= 0) {
                        addMagicComment(curLine.mid(start, end - start), curLineNr,docStructureIter);
                    } else {
                        addMagicComment(curLine.mid(start), curLineNr, docStructureIter);
                    }
                }
            }
            commentStart.second=Token::magicComment;
            dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
        }
        //// magic comment
        static const QRegularExpression rxMagicTexComment("^%\\ ?!T[eE]X");
        static const QRegularExpression rxMagicBibComment("^%\\ ?!BIB");
        QRegularExpressionMatch matchMagicTexComment=rxMagicTexComment.match(text);
        QRegularExpressionMatch matchMagicBibComment=rxMagicBibComment.match(text);
        if (matchMagicTexComment.hasMatch()) {
            addMagicComment(text.mid(matchMagicTexComment.capturedLength()).trimmed(), curLineNr, docStructureIter);
            commentStart.second=Token::magicComment;
            dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
        } else if (matchMagicBibComment.hasMatch()) {
            // workaround to also support "% !BIB program = biber" syntax used by TeXShop and TeXWorks
            text = text.mid(matchMagicBibComment.capturedLength()).trimmed();
            QString name;
            QString val;
            splitMagicComment(text, name, val);
            if ((name == "TS-program" || name == "program") && (val == "biber" || val == "bibtex" || val == "bibtex8")) {
                addMagicComment(QString("TXS-program:bibliography = txs:///%1").arg(val), curLineNr, docStructureIter);
                commentStart.second=Token::magicComment;
                dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
            }
        }
    }
}


/*!
 * \brief interpret Command arguments and update internal data accordingly
 * \param dlh line handle
 * \param currentLineNr
 * \param data
 * \param recheckLabels
 * \param flatStructure
 */
void LatexDocument::interpretCommandArguments(QDocumentLineHandle *dlh, const int currentLineNr, HandledData &data, bool recheckLabels, std::list<StructureEntry*>::iterator & docStructureIter){
    if(dlh->hasFlag(QDocumentLine::argumentsParsed)) return;
    TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();

    const QString curLine=dlh->text();
    bool parsingComplete = true;

    for (int j = 0; j < tl.length(); j++) {
        Token tk = tl.at(j);
        // break at comment start
        if (tk.type == Token::comment)
            break;
        // work special args
        ////Ref
        //for reference counting (can be placed in command options as well ...
        if (tk.type == Token::labelRef || tk.type == Token::labelRefList) {
            ReferencePair elem;
            elem.name = tk.getText();
            elem.start = tk.start;
            mRefItem.insert(dlh, elem);
        }

        //// label ////
        if (tk.type == Token::label && tk.length > 0) {
            ReferencePair elem;
            elem.name = tk.getText();
            elem.start = tk.start;
            mLabelItem.insert(dlh, elem);
            data.completerNeedsUpdate = true;
            StructureEntry *newLabel = new StructureEntry(this, StructureEntry::SE_LABEL);
            newLabel->title = elem.name;
            newLabel->setLine(dlh, currentLineNr);
            replaceOrAdd(docStructureIter,dlh,newLabel);
        }
        //// newtheorem ////
        if (tk.type == Token::newTheorem && tk.length > 0) {
            data.completerNeedsUpdate = true;
            QStringList lst;
            QString firstArg = tk.getText();
            lst << "\\begin{" + firstArg + "}" << "\\end{" + firstArg + "}";
            foreach (const QString &elem, lst) {
                mUserCommandList.insert(dlh, UserCommandPair(firstArg, elem));
                ltxCommands.possibleCommands["user"].insert(elem);
                if (!data.removedUserCommands.removeAll(elem)) {
                    data.addedUserCommands << elem;
                }
            }
            continue;
        }
        /// bibitem ///
        if (tk.type == Token::newBibItem && tk.length > 0) {
            ReferencePair elem;
            elem.name = tk.getText();
            elem.start = tk.start;
            mBibItem.insert(dlh, elem);
            data.bibItemsChanged = true;
            continue;
        }
        /// todo ///
        if (tk.subtype == Token::todo && (tk.type == Token::braces || tk.type == Token::openBrace)) {
            StructureEntry *newTodo = new StructureEntry(this, StructureEntry::SE_TODO);
            newTodo->title = tk.getInnerText();
            newTodo->setLine(dlh, currentLineNr);
            replaceOrAdd(docStructureIter,dlh,newTodo);
            continue;
        }
        // specialArg definition
        if(tk.type == Token::defSpecialArg){
            QString cmd=Parsing::getCommandFromToken(tk);
            data.completerNeedsUpdate = true;
            QString definition = lp->specialDefCommands.value(cmd);
            if(definition.isEmpty()){
                definition = ltxCommands.specialDefCommands.value(cmd);
            }
            if(definition.isEmpty()){
                continue; // special def w/o category is not useful and actually an error
            }
            QString elem = tk.getText();
            QString completeDefinition=definition + "%" + elem;
            mUserCommandList.insert(dlh, UserCommandPair(QString(), completeDefinition));
            if (!data.removedUserCommands.removeAll(completeDefinition)) {
                data.addedUserCommands << completeDefinition;
            }
        }

        // work on general commands
        if (tk.type != Token::command && tk.type != Token::commandUnknown)
            continue; // not a command
        if(tk.type == Token::commandUnknown && tk.length>2){
            // ignore all 2 letter commands like '\ ',\\,\& etc.
            parsingComplete=false; // most likely not all commands parsed
        }
        Token tkCmd;
        TokenList args;
        QString cmd;
        int cmdStart = Parsing::findCommandWithArgsFromTL(tl, tkCmd, args, j, parent->showCommentedElementsInStructure);
        if (cmdStart < 0) break;
        cmdStart=tkCmd.start; // from here, cmdStart is line column position of command
        cmd = curLine.mid(tkCmd.start, tkCmd.length);

        QString firstArg = Parsing::getArg(args, dlh, 0, ArgumentList::Mandatory,true,currentLineNr);


        // special treatment \def
        if (cmd == "\\def" || cmd == "\\gdef" || cmd == "\\edef" || cmd == "\\xdef") {
            QString remainder = curLine.mid(cmdStart + cmd.length());
            data.completerNeedsUpdate = true;
            static const QRegularExpression rx("(\\\\\\w+)\\s*([^{%]*)");
            QRegularExpressionMatch rxMatch = rx.match(remainder);
            if (rxMatch.hasMatch()) {
                QString name = rxMatch.captured(1);
                QString nameWithoutArgs = name;
                QString optionStr = rxMatch.captured(2);
                //qDebug()<< name << ":"<< optionStr;
                ltxCommands.possibleCommands["user"].insert(name);
                if (!data.removedUserCommands.removeAll(name)) data.addedUserCommands << name;
                optionStr = optionStr.trimmed();
                if (optionStr.length()) {
                    int lastArg = optionStr[optionStr.length() - 1].toLatin1() - '0';
                    if (optionStr.length() == lastArg * 2) { //#1#2#3...
                        for (int j = 1; j <= lastArg; j++)
                            if (j == 1) name.append("{%<arg1%|%>}");
                            else name.append(QString("{%<arg%1%>}").arg(j));
                    } else {
                        QStringList args = optionStr.split('#'); //#1;#2#3:#4 => ["",1;,2,3:,4]
                        bool hadSeparator = true;
                        for (int i = 1; i < args.length(); i++) {
                            if (args[i].length() == 0) continue; //invalid
                            bool hasSeparator = (args[i].length() != 1); //only single digit variables allowed. last arg also needs a sep
                            if (!hadSeparator || !hasSeparator)
                                args[i] = QString("{%<arg") + args[i][0] + QString("%>}") + args[i].mid(1);
                            else
                                args[i] = QString("%<arg") + args[i][0] + QString("%>") + args[i].mid(1); //no need to use {} for arguments that are separated anyways
                            hadSeparator  = hasSeparator;
                        }
                        name.append(args.join(""));
                    }
                }
                mUserCommandList.insert(dlh, UserCommandPair(nameWithoutArgs, name));
            }
            continue;
        }
        if (cmd == "\\newcolumntype") {
            if(firstArg.length()==1){ // only single letter definitions are allowed/handled
                QString secondArg = Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory);
                ltxCommands.possibleCommands["%columntypes"].insert(firstArg+secondArg);
                if (!data.removedUserCommands.removeAll(firstArg)) {
                    data.addedUserCommands << firstArg;
                }
                mUserCommandList.insert(dlh, UserCommandPair(QString(), firstArg));
                continue;
            }
        }

        //// newenvironment ////
        static const QStringList envTokens = QStringList() << "\\newenvironment" << "\\renewenvironment";
        if (envTokens.contains(cmd)) {
            data.completerNeedsUpdate = true;
            TokenList argsButFirst = args;
            if(argsButFirst.isEmpty())
                continue; // no arguments present
            argsButFirst.removeFirst();
            int optionCount = Parsing::getArg(argsButFirst, dlh, 0, ArgumentList::Optional).toInt(); // results in 0 if there is no optional argument or conversion fails
            if (optionCount > 9 || optionCount < 0) optionCount = 0; // limit number of options
            mUserCommandList.insert(dlh, UserCommandPair(firstArg, "\\end{" + firstArg + "}"));
            QStringList lst;
            lst << "\\begin{" + firstArg + "}" << "\\end{" + firstArg + "}";
            foreach (const QString &elem, lst) {
                ltxCommands.possibleCommands["user"].insert(elem);
                if (!data.removedUserCommands.removeAll(elem)) {
                    data.addedUserCommands << elem;
                }
            }
            bool hasDefaultArg = !Parsing::getArg(argsButFirst, dlh, 1, ArgumentList::Optional).isNull();
            int mandatoryOptionCount = hasDefaultArg ? optionCount - 1 : optionCount;
            QString mandatoryArgString;
            for (int j = 0; j < mandatoryOptionCount; j++) {
                if (j == 0) mandatoryArgString.append("{%<1%>}");
                else mandatoryArgString.append(QString("{%<%1%>}").arg(j + 1));
            }
            mUserCommandList.insert(dlh, UserCommandPair(firstArg, "\\begin{" + firstArg + "}" + mandatoryArgString));
            if (hasDefaultArg) {
                mUserCommandList.insert(dlh, UserCommandPair(firstArg, "\\begin{" + firstArg + "}" + "[%<opt%>]" + mandatoryArgString));
            }
            continue;
        }
        //// newcounter ////
        if (cmd == "\\newcounter") {
            data.completerNeedsUpdate = true;
            QStringList lst;
            lst << "\\the" + firstArg ;
            foreach (const QString &elem, lst) {
                mUserCommandList.insert(dlh, UserCommandPair(elem, elem));
                ltxCommands.possibleCommands["user"].insert(elem);
                if (!data.removedUserCommands.removeAll(elem)) {
                    data.addedUserCommands << elem;
                }
            }
            continue;
        }
        //// newif ////
        if (cmd == "\\newif") {
            // \newif\ifmycondition also defines \myconditiontrue and \myconditionfalse
            data.completerNeedsUpdate = true;
            QStringList lst;
            lst << firstArg
                << "\\" + firstArg.mid(3) + "false"
                << "\\" + firstArg.mid(3) + "true";
            foreach (const QString &elem, lst) {
                mUserCommandList.insert(dlh, UserCommandPair(elem, elem));
                ltxCommands.possibleCommands["user"].insert(elem);
                if (!data.removedUserCommands.removeAll(elem)) {
                    data.addedUserCommands << elem;
                }
            }
            continue;
        }
        //// newcommand ////
        if (lp->possibleCommands["%definition"].contains(cmd) || ltxCommands.possibleCommands["%definition"].contains(cmd)) {
            data.completerNeedsUpdate = true;
            //Tokens cmdName;
            QString cmdName = Parsing::getArg(args, Token::def);
            cmdName.replace("@","@@"); // special treatment for commandnames containing @
            bool isDefWidth = true;
            if (cmdName.isEmpty())
                cmdName = Parsing::getArg(args, Token::defWidth);
            else
                isDefWidth = false;

            ltxCommands.possibleCommands["user"].insert(cmdName);

            if (!data.removedUserCommands.removeAll(cmdName)) {
                data.addedUserCommands << cmdName;
            }
            QString cmdNameWithoutArgs = cmdName;
            QString cmdNameWithoutOptional = cmdName;
            bool def=false;

            QString xarg=Parsing::getArg(args, Token::defXparseArg);
            if(!xarg.isEmpty()){
                // xparse style defintion
                if(lp->possibleCommands["%definition1"].contains(cmd)||ltxCommands.possibleCommands["%definition1"].contains(cmd)){
                    xarg+="m"; // special treatment for newtcbox and similar. Automatically add one mandatory argument
                }
                QString arguments=interpretXArgs(xarg);
                cmdName=cmdName+arguments;
            }else{
                int optionCount = Parsing::getArg(args, Token::defArgNumber).toInt(); // results in 0 if there is no optional argument or conversion fails
                if (optionCount > 9 || optionCount < 0) optionCount = 0; // limit number of options
                def = !Parsing::getArg(args, Token::optionalArgDefinition).isEmpty();
                if(lp->possibleCommands["%definition1"].contains(cmd)||ltxCommands.possibleCommands["%definition1"].contains(cmd)){
                    ++optionCount; // special treatment for newtcbox and similar. Automatically add one mandatory argument
                }


                for (int j = 0; j < optionCount; j++) {
                    if (j == 0) {
                        if (!def){
                            cmdName.append("{%<arg1%|%>}");
                            cmdNameWithoutOptional.append("{%<arg1%|%>}");
                        } else
                            cmdName.append("[%<opt. arg1%|%>]");
                    } else {
                        cmdName.append(QString("{%<arg%1%>}").arg(j + 1));
                        cmdNameWithoutOptional.append(QString("{%<arg%1%>}").arg(j + 1));
                    }
                }
            }
            CodeSnippet cs(cmdName);
            cs.index = qHash(cmdName);
            cs.snippetLength = cmdName.length();
            cs.type=CodeSnippet::userCommand;
            if (isDefWidth)
                cs.type = CodeSnippet::length;
            mUserCommandList.insert(dlh, UserCommandPair(cmdNameWithoutArgs, cs));
            if(def){ // optional argument, add version without that argument as well
                CodeSnippet cs(cmdNameWithoutOptional);
                cs.index = qHash(cmdNameWithoutOptional);
                cs.snippetLength = cmdNameWithoutOptional.length();
                cs.type=CodeSnippet::userCommand;
                if (isDefWidth)
                    cs.type = CodeSnippet::length;
                mUserCommandList.insert(dlh, UserCommandPair(cmdNameWithoutArgs, cs));
            }
            continue;
        }

        ///usepackage
        if (lp->possibleCommands["%usepackage"].contains(cmd)) {
            if(firstArg.contains("\\")){
                // argument contains backslash
                // hence, invalid and to be ignored
                continue;
            }
            data.completerNeedsUpdate = true;
            QStringList packagesHelper = firstArg.split(",");

            if (cmd.endsWith("theme")) { // special treatment for \usetheme
                QString preamble = cmd;
                preamble.remove(0, 4);
                preamble.prepend("beamer");
                packagesHelper.replaceInStrings(QRegularExpression("^\\s*"), preamble);
            }
            if (cmd=="\\usetikzlibrary") { // special treatment for \usetikzlibrary
                QString preamble = "tikzlibrary";
                packagesHelper.replaceInStrings(QRegularExpression("^\\s*"), preamble);
            }
            if (cmd=="\\usepgfplotslibrary") { // special treatment for \usepgfplotslibrary
                QString preamble = "pgfplotslibrary";
                packagesHelper.replaceInStrings(QRegularExpression("^\\s*"), preamble);
            }
            if (cmd=="\\tcbuselibrary") { // special treatment for \tcbuselibrary
                QString preamble = "tcolorboxlibrary";
                packagesHelper.replaceInStrings(QRegularExpression("^\\s*"), preamble);
            }
            if (cmd=="\\UseTblrLibrary") { // special treatment for \UseTblrLibrary
                QString preamble = "tabularraylibrary";
                packagesHelper.replaceInStrings(QRegularExpression("^\\s*"), preamble);
            }

            QString firstOptArg = Parsing::getArg(args, dlh, 0, ArgumentList::Optional);
            if (cmd == "\\documentclass") {
                //special treatment for documentclass, especially for the class options
                // at the moment a change here does not automatically lead to an update of corresponding definitions, here babel
                mClassOptions = firstOptArg;
                // special treatment for subfile class
                m_isSubfileRoot=(firstArg=="subfiles");
                if(firstArg=="subfiles"){
                    // optional argument points to actual root
                    // this is used to load that document
                    QString fname = findFileName(firstOptArg);
                    LatexDocument *dc = parent->findDocumentFromName(fname);
                    if (!dc) {
                        if(!fname.isEmpty()){
                            data.lstFilesToLoad << fname;
                        }
                    }
                }
            }

            QStringList packages;
            foreach (QString elem, packagesHelper) {
                elem = elem.simplified();
                if(elem.isEmpty()) continue;
                if (lp->packageAliases.contains(elem))
                    packages << lp->packageAliases.values(elem);
                else
                    packages << elem;
            }

            foreach (const QString &elem, packages) {
                if (!data.removedUsepackages.removeAll(firstOptArg + "#" + elem)){
                    if(!data.handledUsepackages.contains(firstOptArg + "#" + elem)){
                        data.addedUsepackages << firstOptArg + "#" + elem;
                    }
                }else{
                    data.handledUsepackages << firstOptArg + "#" + elem;
                }
                mUsepackageList.insert(dlh, firstOptArg + "#" + elem); // hand on option of usepackages for conditional cwl load ..., force load if option is changed
            }
            continue;
        }
        //// bibliography ////
        if (lp->possibleCommands["%bibliography"].contains(cmd)) {
            QStringList additionalBibPaths = ConfigManagerInterface::getInstance()->getOption("Files/Bib Paths").toString().split(getPathListSeparator());
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
            QStringList bibs = firstArg.split(',', Qt::SkipEmptyParts);
#else
            QStringList bibs = firstArg.split(',', QString::SkipEmptyParts);
#endif \
    //add new bibs and set bibTeXFilesNeedsUpdate if there was any change
            foreach (const QString &elem, bibs) { //latex doesn't seem to allow any spaces in file names
                QString absolutePath=getAbsoluteFilePath(elem, "bib", additionalBibPaths);
                mMentionedBibTeXFiles.insert(line(currentLineNr).handle(), FileNamePair(elem, absolutePath));
                if (data.oldBibs.removeAll(elem) == 0)
                    data.bibTeXFilesNeedsUpdate = true;
            }
            //write bib tex in tree
            foreach (const QString &bibFile, bibs) {
                StructureEntry *newFile = new StructureEntry(this, StructureEntry::SE_BIBTEX);
                newFile->title = bibFile;
                newFile->setLine(line(currentLineNr).handle(), currentLineNr);
                replaceOrAdd(docStructureIter,dlh,newFile);
            }
            continue;
        }

        //// beamer blocks ////

        if (cmd == "\\begin" && firstArg == "block") {
            StructureEntry *newBlock = new StructureEntry(this, StructureEntry::SE_BLOCK);
            newBlock->title = Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory,true,currentLineNr);
            newBlock->setLine(line(currentLineNr).handle(), currentLineNr);
            replaceOrAdd(docStructureIter,dlh,newBlock);
            continue;
        }

        //// include,input,import ////
        if (lp->possibleCommands["%include"].contains(cmd) ) {
            QString fn=Parsing::getArg(args, Token::file);
            StructureEntry *newInclude = new StructureEntry(this, StructureEntry::SE_INCLUDE);
            newInclude->level = parent && !parent->indentIncludesInStructure ? 0 : lp->structureDepth() - 1;
            fn = removeQuote(fn);
            newInclude->title = fn;
            QString name=fn;
            name.replace("\\string~",QDir::homePath());
            QString fname = findFileName(name);
            bool includeWasNotPresent = (data.removedIncludes.removeAll(fname) == 0); // don't update syntax if include was removed and reinstated
            data.updateSyntaxCheck |= includeWasNotPresent;
            mIncludedFilesList.insert(line(currentLineNr).handle(), fname);
            LatexDocument *dc = parent->findDocumentFromName(fname);
            if (dc) {
                childDocs.insert(dc);
                dc->setMasterDocument(this, recheckLabels && data.updateSyntaxCheck);
                if(includeWasNotPresent){
                    data.addedIncludes << dc;
                }
            } else {
                if(!fname.isEmpty()){
                    data.lstFilesToLoad << fname;
                }
            }
            newInclude->valid = !fname.isEmpty();
            newInclude->setLine(line(currentLineNr).handle(), currentLineNr);
            newInclude->columnNumber = cmdStart;
            replaceOrAdd(docStructureIter,dlh,newInclude);
            continue;
        }

        if (lp->possibleCommands["%import"].contains(cmd) && !isDefinitionArgument(firstArg)) {
            StructureEntry *newInclude = new StructureEntry(this, StructureEntry::SE_INCLUDE);
            newInclude->level = parent && !parent->indentIncludesInStructure ? 0 : lp->structureDepth() - 1;
            newInclude->setContext(StructureEntry::Import);
            QDir dir(firstArg);
            QFileInfo fi(dir, Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory,true,currentLineNr));
            QString file = fi.filePath();
            newInclude->title = file;
            QString fname = findFileName(file);
            data.updateSyntaxCheck = (data.removedIncludes.removeAll(fname) == 0); // don't update syntax if include was removed and reinstated
            mImportedFilesList.insert(line(currentLineNr).handle(), fname);
            LatexDocument *dc = parent->findDocumentFromName(fname);
            if (dc) {
                childDocs.insert(dc);
                dc->setMasterDocument(this, recheckLabels && data.updateSyntaxCheck);
                dc->importedFile=true;
            } else {
                data.lstFilesToLoad << fname;
            }
            newInclude->valid = !fname.isEmpty();
            newInclude->setLine(line(currentLineNr).handle(), currentLineNr);
            newInclude->columnNumber = cmdStart;
            replaceOrAdd(docStructureIter,dlh,newInclude);
            continue;
        }

        //// all sections ////
        if (cmd.endsWith("*"))
            cmd = cmd.left(cmd.length() - 1);
        int level = lp->structureCommandLevel(cmd);
        if(level<0 && cmd=="\\begin"){
            // special treatment for \begin{frame}{title}
            level=lp->structureCommandLevel(cmd+"{"+firstArg+"}");
        }
        if (level > -1 && !firstArg.isEmpty() && tkCmd.subtype == Token::none) {
            StructureEntry *newSection = new StructureEntry(this, StructureEntry::SE_SECTION);
            if (mAppendixLine && indexOf(mAppendixLine) < currentLineNr) newSection->setContext(StructureEntry::InAppendix);
            if (mBeyondEnd && indexOf(mBeyondEnd) < currentLineNr) newSection->setContext(StructureEntry::BeyondEnd);
            //QString firstOptArg = Parsing::getArg(args, dlh, 0, ArgumentList::Optional);
            QString firstOptArg = Parsing::getArg(args, Token::shorttitle);
            if (!firstOptArg.isEmpty() && firstOptArg != "[]") // workaround, actually getArg should return "" for "[]"
                firstArg = firstOptArg;
            if(cmd=="\\begin"){
                // special treatment for \begin{frame}{title}
                firstArg = Parsing::getArg(args, dlh, 1, ArgumentList::MandatoryWithBraces,false,currentLineNr);
                if(firstArg.isEmpty()){
                    // empty frame title, maybe \frametitle is used ?
                    delete newSection;
                    continue;
                }
            }
            newSection->title = latexToText(firstArg).trimmed();
            newSection->level = level;
            newSection->setLine(line(currentLineNr).handle(), currentLineNr);
            newSection->columnNumber = cmdStart;
            replaceOrAdd(docStructureIter,dlh,newSection);
            continue;
        }
        /// auto user command for \symbol_...
        if(j+2<tl.length()){
            Token tk2=tl.at(j+1);
            if(tk2.getText()=="_"){
                QString txt=cmd+"_";
                tk2=tl.at(j+2);
                txt.append(tk2.getText());
                if(tk2.type==Token::command && j+3<tl.length()){
                    Token tk3=tl.at(j+3);
                    if(tk3.level==tk2.level && tk.subtype!=Token::none)
                        txt.append(tk3.getText());
                }
                CodeSnippet cs(txt,true,true);
                cs.type=CodeSnippet::userConstruct;
                mUserCommandList.insert(dlh, UserCommandPair(QString(), cs));
                if (!data.removedUserSnippets.removeAll(txt)) {
                    data.addedUserSnippets << txt;
                }
            }
        }
        /// auto user commands of \mathcmd{one arg} e.g. \mathsf{abc} or \overbrace{abc}
        if(j+2<tl.length() && !firstArg.isEmpty() && lp->possibleCommands["math"].contains(cmd) ){
            if (lp->commandDefs.contains(cmd)) {
                CommandDescription cd = lp->commandDefs.value(cmd);
                if(cd.arguments.size()==1 && cd.args()==1){
                    QString txt=cmd+"{"+firstArg+"}";
                    CodeSnippet cs(txt,true,true);
                    cs.type=CodeSnippet::userConstruct;
                    mUserCommandList.insert(dlh, UserCommandPair(QString(), cs));
                    if (!data.removedUserSnippets.removeAll(txt)) {
                        data.addedUserSnippets << txt;
                    }
                }
            }
        }

    } // for tl
    // remove obsolete entries for this line in docStructure
    while(docStructureIter!=docStructure.end()){
        if((*docStructureIter)->getLineHandle()==dlh){
            delete *docStructureIter;
            docStructureIter=docStructure.erase(docStructureIter);
        }else{
            break;
        }
    }

    if(parsingComplete){
        dlh->setFlag(QDocumentLine::argumentsParsed,true);
    }
}
/*!
 * \brief reinterpret command arguments when packages have changed
 */
void LatexDocument::reinterpretCommandArguments(HandledData &changedCommands)
{
    std::list<StructureEntry*>::iterator docStructureIter = docStructure.begin();
    for (int i = 0; i < lineCount(); ++i) {
        QDocumentLineHandle *dlh=line(i).handle();
        for(;docStructureIter!=docStructure.end();++docStructureIter){
            StructureEntry *element=*docStructureIter;
            int ln=element->getRealLineNumber();
            if(ln>=i){
                break;
            }
        }
        bool skipRecheck=dlh->hasFlag(QDocumentLine::argumentsParsed);
        if(!dlh->hasFlag(QDocumentLine::argumentsParsed)){
            removeLineElements(dlh,changedCommands);
        }
        // handle special comments (TODO, MAGIC comments)
        handleComments(dlh,i,docStructureIter);

        interpretCommandArguments(dlh,i,changedCommands,false,docStructureIter);
        if (edView && !skipRecheck){
            edView->documentContentChanged(i, 1);
            reCheckSyntax(i,1);
        }
    }
}
/*!
 * \brief replace or add element in docStructure
 * \param docStructurePosition
 * \param dlh
 * \param newElement
 */
void LatexDocument::replaceOrAdd(std::list<StructureEntry*>::iterator &docStructureIter, QDocumentLineHandle *dlh, StructureEntry *newElement)
{
    if(docStructureIter != docStructure.end() && (*docStructureIter)->getLineHandle() == dlh && (*docStructureIter)->type == newElement->type){
        // replace old element
        (*docStructureIter)->columnNumber=newElement->columnNumber;
        (*docStructureIter)->title=newElement->title;
        (*docStructureIter)->level=newElement->level;
        (*docStructureIter)->valid=newElement->valid;
        ++docStructureIter;
        delete newElement;
    }else{
        docStructure.insert(docStructureIter,newElement);
    }
}
/*!
 * \brief decide if documents need to be rescanned (lexing and argument parsing)
 * Perform the appropriate steps
 */
void LatexDocument::handleRescanDocuments(HandledData changedCommands){
    bool loopAgain=false;
    bool updateCompleter=!changedCommands.addedUsepackages.isEmpty() || !changedCommands.removedUsepackages.isEmpty() || !changedCommands.removedIncludes.isEmpty() || !changedCommands.addedIncludes.isEmpty();
    do{
        loopAgain=false;
        // includes changed
        if(!changedCommands.lstFilesToLoad.isEmpty()){
            // lex2 & argument parsing, syntax check
            std::pair<bool,bool> result=parent->addDocsToLoad(changedCommands.lstFilesToLoad,this);
            bool newPackagesFound=result.first;
            bool newUserComamndsFound=result.second;
            changedCommands.lstFilesToLoad.clear();
            if(newPackagesFound){
                changedCommands.addedUsepackages<<"dummy"; // force handling newly included packages
            }
            if(newUserComamndsFound){
                changedCommands.addedUserCommands<<"dummy"; // force handling newly included packages
                updateCompleter=true;
            }
        }
        if(!changedCommands.removedIncludes.isEmpty() || !changedCommands.addedIncludes.isEmpty()){
            // argument parsing & syntax check
            parent->removeDocs(changedCommands.removedIncludes);
            if(!changedCommands.addedIncludes.isEmpty()){
                recheckRefsLabels();
                changedCommands.addedIncludes.clear();
            }
            updateLtxCommands(true);
        }
        // usepackage changed, lex pass2 all documents
        if(!changedCommands.addedUsepackages.isEmpty()||!changedCommands.removedUsepackages.isEmpty()||!changedCommands.addedUserCommands.isEmpty()){
            // lex2 & argument parsing, syntax check
            const bool updatePackages=!changedCommands.addedUsepackages.isEmpty()||!changedCommands.removedUsepackages.isEmpty();
            const bool updateUserCommands=!changedCommands.addedUserCommands.isEmpty()||!changedCommands.removedUserCommands.isEmpty();
            updateCompletionFiles(updatePackages,updateUserCommands);
            const int cntAddedUserCommands=changedCommands.addedUserCommands.size(); // keep track if reinterpretCommandArguments comes up with new user commands
            if(!changedCommands.addedUsepackages.isEmpty()){
                changedCommands.addedUsepackages.clear();
                int start=0;
                QList<LatexDocument *>listOfDocs = getListOfDocs();
                foreach(LatexDocument *elem, listOfDocs){
                    int cnt=elem->lineCount();
                    elem->lexLines(start,cnt,true);
                    elem->reinterpretCommandArguments(changedCommands);
                }
                if(!changedCommands.addedIncludes.isEmpty()||!changedCommands.addedUsepackages.isEmpty()||!changedCommands.lstFilesToLoad.isEmpty()){
                    loopAgain=true;
                    updateCompleter=true;
                }
            }
            if(!changedCommands.addedUserCommands.isEmpty()){
                lp->possibleCommands["user"].unite(ltxCommands.possibleCommands["user"]);
                // handle specialDef commands
                for(const QString &key: changedCommands.addedUserCommands){
                    if(key.startsWith("%")){
                        const int i = key.indexOf('%', 1);
                        QString category = key.left(i);
                        QString elem = key.mid(i + 1);
                        lp->possibleCommands[category].insert(elem);
                        ltxCommands.possibleCommands[category].insert(elem);
                    }
                }
                if(cntAddedUserCommands<changedCommands.addedUserCommands.size()){
                    // new usercommands were generated when reinterpretCommandArguments was called, fix #3885
                    updateCompletionFiles(false,true);
                }
                changedCommands.addedUserCommands.clear();
            }
            if(!changedCommands.removedUserCommands.isEmpty()){
                for(const QString &key: changedCommands.removedUserCommands){
                    if(key.startsWith("%")){
                        const int i = key.indexOf('%', 1);
                        QString category = key.left(i);
                        QString elem = key.mid(i + 1);
                        lp->possibleCommands[category].remove(elem);
                        ltxCommands.possibleCommands[category].remove(elem);
                    }
                }
                changedCommands.removedUserCommands.clear();
            }

            synChecker.setLtxCommands(lp); // redundant here, updateCompletionfiles
            reCheckSyntax();
        }
    }while(loopAgain);



    // bib files changed
    // update bibitem checking and completer
    if (changedCommands.bibTeXFilesNeedsUpdate)
        emit updateBibTeXFiles();
    // force update on citation overlays
    if (changedCommands.bibItemsChanged || changedCommands.bibTeXFilesNeedsUpdate) {
        parent->updateBibFiles(changedCommands.bibTeXFilesNeedsUpdate);
        // needs probably done asynchronously as bibteFiles needs to be loaded first ...
        foreach (LatexDocument *elem, getListOfDocs()) {
            if (elem->edView)
                elem->edView->updateCitationFormats();
        }
        updateCompleter=true;
    }
    // user commands or bibitems changed
    // update completer & syntax check
    if(updateCompleter){
        emit updateCompleterCommands();
    }
}
/*!
 * \brief remove all previously detected elements like include,bibitem,labels,usercommands, etc
 * Keep trak of removal to allow reinstating
 *
 * \param dlh
 * \param changedCommands
 */
void LatexDocument::removeLineElements(QDocumentLineHandle *dlh, HandledData &changedCommands){
    QList<UserCommandPair> commands = mUserCommandList.values(dlh);
    foreach (UserCommandPair cmd, commands) {
        QString elem = cmd.snippet.word;
        if(elem.length()==1){
            for (auto i:ltxCommands.possibleCommands["%columntypes"]) {
                if(i.left(1)==elem){
                    ltxCommands.possibleCommands["%columntypes"].remove(i);
                    break;
                }
            }
        }else{
            int i = elem.indexOf("{");
            if (i >= 0) elem = elem.left(i);
            if(countCommandDefintions(elem)==1){
                ltxCommands.possibleCommands["user"].remove(elem);
            }
        }
        if(cmd.snippet.type==CodeSnippet::userConstruct){
            changedCommands.removedUserSnippets << elem;
        }else{
            changedCommands.removedUserCommands << elem;
        }
    }
    if (mLabelItem.contains(dlh)) {
        QList<ReferencePair> labels = mLabelItem.values(dlh);
        changedCommands.completerNeedsUpdate = true;
        mLabelItem.remove(dlh);
        foreach (const ReferencePair &rp, labels)
            updateRefsLabels(rp.name);
    }
    mRefItem.remove(dlh);
    changedCommands.removedIncludes = mIncludedFilesList.values(dlh);
    changedCommands.removedIncludes.append(mImportedFilesList.values(dlh));
    mIncludedFilesList.remove(dlh);
    mImportedFilesList.remove(dlh);

    if (mUserCommandList.count(dlh) > 0) {
        changedCommands.completerNeedsUpdate = true;
        foreach (const UserCommandPair &cmd, mUserCommandList.values(dlh)) {
            QString elem = cmd.snippet.word;
            if (elem.startsWith("%")) { // insert specialArgs
                int i = elem.indexOf('%', 1);
                QString category = elem.left(i);
                elem = elem.mid(i + 1);
                ltxCommands.possibleCommands[category].remove(elem);
            }
        }
        mUserCommandList.remove(dlh);
    }
    if (mBibItem.remove(dlh))
        changedCommands.bibTeXFilesNeedsUpdate = true;

    changedCommands.removedUsepackages << mUsepackageList.values(dlh);
    if (mUsepackageList.remove(dlh) > 0) changedCommands.completerNeedsUpdate = true;

    //remove old bibs files from hash, but keeps a temporary copy
    while (mMentionedBibTeXFiles.contains(dlh)) {
        QMultiHash<QDocumentLineHandle *, FileNamePair>::iterator it = mMentionedBibTeXFiles.find(dlh);
        Q_ASSERT(it.key() == dlh);
        Q_ASSERT(it != mMentionedBibTeXFiles.end());
        if (it == mMentionedBibTeXFiles.end()) break;
        changedCommands.oldBibs.append(it.value().relative);
        mMentionedBibTeXFiles.erase(it);
    }
}

/*!
 * \brief parse lines to update syntactical and structure information
 *
 * updates structure informationen from the changed lines only
 * parses the lines to gather syntactical information on the latex content
 * e.g. find labels/references, new command definitions etc.
 * the syntax parsing has been largely changed to the token system which is tranlated here for faster information extraction \see Tokens
 * \param linenr first line to check
 * \param count number of lines to check (-1: all)
 * \param recheck method has been called a second time to handle profound syntax changes from first call (like newly loaded packages). This allows to avoid some costly operations on the second call.
 * \return true means a second run is suggested as packages are loaded which change the outcome
 *         e.g. definition of specialDef command, but packages are load at the end of this method.
 */
void LatexDocument::patchStructure(int linenr, int count, bool recheck)
{
	/* true means a second run is suggested as packages are loadeed which change the outcome
	 * e.g. definition of specialDef command, but packages are load at the end of this method.
	 */

    if(isIncompleteInMemory()) return; // no update for incomplete/cached documents

    //QElapsedTimer tm ;
    //tm.start();

	bool recheckLabels = true;
	if (count < 0) {
		count = lineCount();
		recheckLabels = false;
	}

	QDocumentLineHandle *oldLine = mAppendixLine; // to detect a change in appendix position
	QDocumentLineHandle *oldLineBeyond = mBeyondEnd; // to detect a change in end document position
	// get remainder
	TokenStack remainder;
	int lineNrStart = linenr;
	int newCount = count;
	if (linenr > 0) {
		QDocumentLineHandle *previous = line(linenr - 1).handle();
		remainder = previous->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
		if (!remainder.isEmpty() && remainder.top().subtype != Token::none) {
			QDocumentLineHandle *lh = remainder.top().dlh;
			lineNrStart = lh->document()->indexOf(lh);
			if (linenr - lineNrStart > 10) // limit search depth
				lineNrStart = linenr;
		}
	}
	// usepackage list
    HandledData changedCommands;

    //lex lines
    lexLines(linenr,count,recheck);

    if (linenr > lineNrStart) {
		newCount = linenr + count - lineNrStart;
	}
	// Note: We cannot re-use the structure elements in the updated area because if there are multiple same-type elements on the same line
	// and the user has changed their order, re-using these elements would not update their order and this would break updates of any
	// QPersistentModelIndex'es that point to these elements in the structure tree view. That is why we remove all the structure elements
	// within the updated area and then just add anew any structure elements that we find in the updated area.

    bool isLatexLike = languageIsLatexLike();
	//updateSubsequentRemaindersLatex(this,linenr,count,lp);
	// force command from all line of which the actual line maybe subsequent lines (multiline commands)
    std::list<StructureEntry*>::iterator docStructureIter = docStructure.begin();
    for (int i = lineNrStart; i < linenr + newCount; i++) {
        for(;docStructureIter!=docStructure.end();++docStructureIter){
            StructureEntry *element=*docStructureIter;
            int ln=element->getRealLineNumber();
            if(ln>=i){
                break;
            }
        }
		//update bookmarks
		if (edView && edView->hasBookmark(i, -1)) {
			emit bookmarkLineUpdated(i);
		}

		if (!isLatexLike) continue;

		QString curLine = line(i).text();
		QDocumentLineHandle *dlh = line(i).handle();
		if (!dlh)
			continue; //non-existing line ...

        // remove command,bibtex,labels at from this line
        if(!dlh->hasFlag(QDocumentLine::argumentsParsed)){
            // don't handle unchanged lines as they are not reinterpreted
            removeLineElements(dlh,changedCommands);
        }

        // handle special comments (TODO, MAGIC comments)
        handleComments(dlh,i,docStructureIter);

		// check also in command argument, als references might be put there as well...
		//// Appendix keyword
		if (curLine == "\\appendix") {
			oldLine = mAppendixLine;
			mAppendixLine = line(i).handle();

		}
		if (line(i).handle() == mAppendixLine && curLine != "\\appendix") {
			oldLine = mAppendixLine;
			mAppendixLine = nullptr;
		}
        /// \begin{document}
        /// break patchStructure at begin{document} since added usepackages need to be loaded and then the text needs to be checked
        /// only useful when loading a complete new text.
        if (curLine == "\\begin{document}"){
            if(linenr==0 && count==lineCount() && !recheck) {
                if(!changedCommands.addedUsepackages.isEmpty()){
                    break; // do recheck quickly as usepackages probably need to be loaded
                }else{
                    // oops, complete tokenlist needed !
                    // redo on time
                    int cnt=lineCount()-i;
                    lexLines(i,cnt,true);
                }
            }
        }
		/// \end{document} keyword
		/// don't add section in structure view after passing \end{document} , this command must not contains spaces nor any additions in the same line
		if (curLine == "\\end{document}") {
			oldLineBeyond = mBeyondEnd;
			mBeyondEnd = line(i).handle();
		}
		if (line(i).handle() == mBeyondEnd && curLine != "\\end{document}") {
			oldLineBeyond = mBeyondEnd;
			mBeyondEnd = nullptr;
		}
        // interpret arguments and update txs knowledge about them
        // e.g. labels, packages, etc
        interpretCommandArguments(dlh,i,changedCommands,recheckLabels,docStructureIter);

        if (!changedCommands.oldBibs.isEmpty())
            changedCommands.bibTeXFilesNeedsUpdate = true; //file name removed

	}//for each line handle

    //update appendix change
    if (oldLine != mAppendixLine) {
        updateContext(oldLine, mAppendixLine, StructureEntry::InAppendix);
    }
    //update end document change
    if (oldLineBeyond != mBeyondEnd) {
        updateContext(oldLineBeyond, mBeyondEnd, StructureEntry::BeyondEnd);
    }

    handleRescanDocuments(changedCommands);

    emit structureUpdated();

    if(changedCommands.completerNeedsUpdate){
        emit updateCompleterCommands();
    }



    //update view
    if (edView){
        edView->documentContentChanged(linenr, newCount);
        reCheckSyntax(lineNrStart,newCount);
        edView->checkGrammar(linenr,newCount);
    }
#ifndef QT_NO_DEBUG
	if (!isHidden())
		checkForLeak();
#endif
}

#ifndef QT_NO_DEBUG
void LatexDocument::checkForLeak()
{
	QSet<StructureEntry *>zw = StructureContent;
    for(auto iter=docStructure.cbegin();iter != docStructure.cend();++iter) {
        zw.remove(*iter);
	}

	// filter top level elements
	QMutableSetIterator<StructureEntry *> i(zw);
	while (i.hasNext())
		if (i.next()->type == StructureEntry::SE_OVERVIEW) i.remove();

	if (zw.count() > 0) {
		qDebug("Memory leak in structure");
	}
}
#endif

StructureEntry *LatexDocument::findSectionForLine(int currentLine)
{
    StructureEntry *newSection = nullptr;

    for(auto iter=docStructure.cbegin();iter!=docStructure.cend();++iter){
        StructureEntry *curSection = *iter;
        if (curSection->getRealLineNumber() > currentLine) break; //curSection is after newSection where the cursor is
        if (curSection->type == StructureEntry::SE_SECTION){
            newSection = curSection;
        }
    }
    if (newSection && newSection->getRealLineNumber() > currentLine) newSection = nullptr;

	return newSection;
}

void LatexDocument::setTemporaryFileName(const QString &fileName)
{
	temporaryFileName = fileName;
}

QString LatexDocument::getTemporaryFileName() const
{
	return temporaryFileName;
}

QString LatexDocument::getFileNameOrTemporaryFileName() const
{
	if (!fileName.isEmpty()) return fileName;
	return temporaryFileName;
}

QFileInfo LatexDocument::getTemporaryFileInfo() const
{
	return QFileInfo(temporaryFileName);
}

int LatexDocument::countLabels(const QString &name)
{
	int result = 0;
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QStringList items = elem->labelItems();
		result += items.count(name);
	}
	return result;
}

int LatexDocument::countRefs(const QString &name)
{
	int result = 0;
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QStringList items = elem->refItems();
		result += items.count(name);
	}
	return result;
}

bool LatexDocument::bibIdValid(const QString &name)
{
	bool result = !findFileFromBibId(name).isEmpty();
	if (!result) {
		foreach (const LatexDocument *doc, getListOfDocs()) {
			if (doc->bibItems().contains(name)) {
				result = true;
				break;
			}
		}
	}
	return result;
}

bool LatexDocument::isBibItem(const QString &name)
{
	bool result = false;
	foreach (const LatexDocument *doc, getListOfDocs()) {
		if (doc->bibItems().contains(name)) {
			result = true;
			break;
		}
	}
	return result;
}

QString LatexDocument::findFileFromBibId(const QString &bibId)
{
	QStringList collected_mentionedBibTeXFiles;
	foreach (const LatexDocument *doc, getListOfDocs())
		collected_mentionedBibTeXFiles << doc->listOfMentionedBibTeXFiles();
	const QMap<QString, BibTeXFileInfo> &bibtexfiles = parent->bibTeXFiles;
	foreach (const QString &file, collected_mentionedBibTeXFiles)
		if (bibtexfiles.value(file).ids.contains(bibId))
			return file;
	return QString();
}

QMultiHash<QDocumentLineHandle *, int> LatexDocument::getBibItems(const QString &name)
{
    QMultiHash<QDocumentLineHandle *, int> result;
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
		for (it = elem->mBibItem.constBegin(); it != elem->mBibItem.constEnd(); ++it) {
			ReferencePair rp = it.value();
			if (rp.name == name && elem->indexOf(it.key()) >= 0) {
				result.insert(it.key(), rp.start);
			}
		}
	}
	return result;
}

QMultiHash<QDocumentLineHandle *, int> LatexDocument::getLabels(const QString &name)
{
    QMultiHash<QDocumentLineHandle *, int> result;
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
		for (it = elem->mLabelItem.constBegin(); it != elem->mLabelItem.constEnd(); ++it) {
			ReferencePair rp = it.value();
			if (rp.name == name && elem->indexOf(it.key()) >= 0) {
				result.insert(it.key(), rp.start);
			}
		}
	}
	return result;
}
/*!
 * \brief find first document which defines given label
 * \param name
 * \return document
 */
LatexDocument* LatexDocument::getDocumentForLabel(const QString &name){
    foreach (LatexDocument *elem, getListOfDocs()) {
        QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
        for (it = elem->mLabelItem.constBegin(); it != elem->mLabelItem.constEnd(); ++it) {
            ReferencePair rp = it.value();
            if (rp.name == name) {
                return elem;
            }
        }
    }
    return nullptr;
}

int LatexDocument::countCommandDefintions(const QString &name,const QString word)
{
    int result=0;
    for (auto it = mUserCommandList.constBegin(); it != mUserCommandList.constEnd(); ++it) {
        if(name.isEmpty()){
            if (it.value().snippet.word == word) {
                ++result;
            }
        }else{
            if (it.value().name == name) {
                ++result;
            }
        }
    }
    return result;
}


QDocumentLineHandle *LatexDocument::findCommandDefinition(const QString &name)
{
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QMultiHash<QDocumentLineHandle *, UserCommandPair>::const_iterator it;
		for (it = elem->mUserCommandList.constBegin(); it != elem->mUserCommandList.constEnd(); ++it) {
			if (it.value().name == name && elem->indexOf(it.key()) >= 0) {
				return it.key();
			}
		}
	}
	return nullptr;
}

QDocumentLineHandle *LatexDocument::findUsePackage(const QString &name)
{
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QMultiHash<QDocumentLineHandle *, QString>::const_iterator it;
		for (it = elem->mUsepackageList.constBegin(); it != elem->mUsepackageList.constEnd(); ++it) {
			if (LatexPackage::keyToPackageName(it.value()) == name && elem->indexOf(it.key()) >= 0) {
				return it.key();
			}
		}
	}
	return nullptr;
}

QMultiHash<QDocumentLineHandle *, int> LatexDocument::getRefs(const QString &name)
{
    QMultiHash<QDocumentLineHandle *, int> result;
	foreach (const LatexDocument *elem, getListOfDocs()) {
		QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
		for (it = elem->mRefItem.constBegin(); it != elem->mRefItem.constEnd(); ++it) {
			ReferencePair rp = it.value();
			if (rp.name == name && elem->indexOf(it.key()) >= 0) {
				result.insert(it.key(), rp.start);
			}
		}
	}
	return result;
}

/*!
 * replace all given items by newName
 * an optional QDocumentCursor may be passed in, if the operation should be
 * part of a larger editBlock of that cursor.
 */
void LatexDocument::replaceItems(QMultiHash<QDocumentLineHandle *, ReferencePair> items, const QString &newName, QDocumentCursor *cursor)
{
	QDocumentCursor *cur = cursor;
	if (!cursor) {
		cur = new QDocumentCursor(this);
		cur->beginEditBlock();
	}
	QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
	int oldLineNr=-1;
	int offset=0;
    QList<int> lineNumbers;
	for (it = items.constBegin(); it != items.constEnd(); ++it) {
		QDocumentLineHandle *dlh = it.key();
		ReferencePair rp = it.value();
		int lineNo = indexOf(dlh);
		if(oldLineNr!=lineNo){
			offset=0;
		}
		if (lineNo >= 0) {
			cur->setLineNumber(lineNo);
			cur->setColumnNumber(rp.start+offset);
			cur->movePosition(rp.name.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
			cur->replaceSelectedText(newName);
			offset+=newName.length()-rp.name.length();
			oldLineNr=lineNo;
            if(lineNumbers.isEmpty() || lineNumbers.last()!=lineNo){
                lineNumbers << lineNo;
            }
		}
	}
	if (!cursor) {
		cur->endEditBlock();
		delete cur;
	}
    if(!edView){
        // explicitely call patchStructure on hidden documents with no edView
        foreach (int i, lineNumbers) {
            patchStructure(i, 1);
        }
    }
}

/*!
 * replace all labels name by newName
 * an optional QDocumentCursor may be passed in, if the operation should be
 * part of a larger editBlock of that cursor.
 */
void LatexDocument::replaceLabel(const QString &name, const QString &newName, QDocumentCursor *cursor)
{
	QMultiHash<QDocumentLineHandle *, ReferencePair> labelItemsMatchingName;
	QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
	for (it = mLabelItem.constBegin(); it != mLabelItem.constEnd(); ++it) {
		if (it.value().name == name) {
            labelItemsMatchingName.insert(it.key(), it.value());
		}
	}
	replaceItems(labelItemsMatchingName, newName, cursor);
}

/*!
 * replace all references name by newName
 * an optional QDocumentCursor may be passed in, if the operation should be
 * part of a larger editBlock of that cursor.
 */
void LatexDocument::replaceRefs(const QString &name, const QString &newName, QDocumentCursor *cursor)
{
	QMultiHash<QDocumentLineHandle *, ReferencePair> refItemsMatchingName;
	QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
	for (it = mRefItem.constBegin(); it != mRefItem.constEnd(); ++it) {
		if (it.value().name == name) {
            refItemsMatchingName.insert(it.key(), it.value());
		}
	}
	replaceItems(refItemsMatchingName, newName, cursor);
}

void LatexDocument::replaceLabelsAndRefs(const QString &name, const QString &newName)
{
	QDocumentCursor cursor(this);
	cursor.beginEditBlock();
	replaceLabel(name, newName, &cursor);
	replaceRefs(name, newName, &cursor);
	cursor.endEditBlock();
}

void LatexDocument::setMasterDocument(LatexDocument *doc, bool recheck)
{
    masterDocument = doc;
    if(doc && lp != doc->lp){
        // set lp in newly included document
        lp=doc->lp;
    }
    if (recheck) {
        QList<LatexDocument *>listOfDocs = getListOfDocs();

        QStringList items;
        foreach (const LatexDocument *elem, listOfDocs) {
            items << elem->labelItems();
        }

        foreach (LatexDocument *elem, listOfDocs) {
            elem->recheckRefsLabels(listOfDocs,items);
        }
    }
}

void LatexDocument::addChild(LatexDocument *doc)
{
	childDocs.insert(doc);
}

void LatexDocument::removeChild(LatexDocument *doc)
{
	childDocs.remove(doc);
}

bool LatexDocument::containsChild(LatexDocument *doc) const
{
	return childDocs.contains(doc);
}

LatexDocument *LatexDocument::getMasterDocument() const
{
    return masterDocument;
}

QList<LatexDocument *>LatexDocument::getListOfDocs(QSet<LatexDocument *> *visitedDocs,bool onlyChildDocs)
{
	QList<LatexDocument *>listOfDocs;
	bool deleteVisitedDocs = false;
	if (parent->masterDocument) {
		listOfDocs = parent->getDocuments();
	} else {
		LatexDocument *master = this;
		if (!visitedDocs) {
			visitedDocs = new QSet<LatexDocument *>();
			deleteVisitedDocs = true;
		}
		foreach (LatexDocument *elem, parent->getDocuments()) { // check children
			if (elem != master && !master->childDocs.contains(elem)) continue;

			if (visitedDocs && !visitedDocs->contains(elem)) {
				listOfDocs << elem;
				visitedDocs->insert(elem);
                listOfDocs << elem->getListOfDocs(visitedDocs,onlyChildDocs);
			}
		}
        if (masterDocument && !onlyChildDocs) { //check masters
			master = masterDocument;
			if (!visitedDocs->contains(master))
				listOfDocs << master->getListOfDocs(visitedDocs);
		}
	}
	if (deleteVisitedDocs)
		delete visitedDocs;
	return listOfDocs;
}
void LatexDocument::updateRefHighlight(ReferencePairEx p){
    if(!p.dlh) return;
    p.dlh->clearOverlays(p.formatList);
    for(int i=0;i<p.starts.size();++i) {
        p.dlh->addOverlay(QFormatRange(p.starts[i], p.lengths[i], p.formats[i]));
    }
}

void LatexDocument::recheckRefsLabels(QList<LatexDocument*> listOfDocs,QStringList items)
{
	// get occurences (refs)
	int referenceMultipleFormat = getFormatId("referenceMultiple");
	int referencePresentFormat = getFormatId("referencePresent");
	int referenceMissingFormat = getFormatId("referenceMissing");
    const QList<int> formatList{referenceMissingFormat,referencePresentFormat,referenceMultipleFormat};
    QList<ReferencePairEx> results;

    if(listOfDocs.isEmpty()){
        // if not empty, assume listOfDocs *and* items are provided.
        // this avoid genearting both lists for each document again
        listOfDocs=getListOfDocs();
        foreach (const LatexDocument *elem, listOfDocs) {
            items << elem->labelItems();
        }
    }


	QMultiHash<QDocumentLineHandle *, ReferencePair>::const_iterator it;
    QSet<QDocumentLineHandle*> dlhs;
	for (it = mLabelItem.constBegin(); it != mLabelItem.constEnd(); ++it) {
        if(it.key()){
            dlhs.insert(it.key());
        }
    }
    for (it = mRefItem.constBegin(); it != mRefItem.constEnd(); ++it) {
        if(it.key()){
            dlhs.insert(it.key());
        }
    }

    for(QDocumentLineHandle *dlh : dlhs){
        ReferencePairEx p;
        p.formatList=formatList;
        p.dlh=dlh;
        for(const ReferencePair &rp : mLabelItem.values(dlh)) {
            int cnt = items.count(rp.name);
            int format= referenceMissingFormat;
            if (cnt > 1) {
                format=referenceMultipleFormat;
            } else if (cnt == 1) format=referencePresentFormat;
            p.starts<<rp.start;
            p.lengths<<rp.name.length();
            p.formats<<format;
		}
        for(const ReferencePair &rp :  mRefItem.values(dlh)) {
            int cnt = items.count(rp.name);
            int format= referenceMissingFormat;
            if (cnt > 1) {
                format=referenceMultipleFormat;
            } else if (cnt == 1) format=referencePresentFormat;
            p.starts<<rp.start;
            p.lengths<<rp.name.length();
            p.formats<<format;
        }
        results<<p;
	}

    QtConcurrent::blockingMap(results,LatexDocument::updateRefHighlight);
}

QStringList LatexDocument::someItems(const QMultiHash<QDocumentLineHandle *, ReferencePair> &list)
{
	QList<ReferencePair> lst = list.values();
	QStringList result;
	foreach (const ReferencePair &elem, lst) {
		result << elem.name;
	}

	return result;
}


QStringList LatexDocument::labelItems() const
{
	return someItems(mLabelItem);
}

QStringList LatexDocument::refItems() const
{
	return someItems(mRefItem);
}

QStringList LatexDocument::bibItems() const
{
	return someItems(mBibItem);
}

QList<CodeSnippet> LatexDocument::userCommandList() const
{
	QList<CodeSnippet> csl;
    foreach (UserCommandPair cmd, mUserCommandList) {
        if(cmd.name.isEmpty() && cmd.snippet.type!=CodeSnippet::userConstruct) continue; // filter out special def
		csl.append(cmd.snippet);
	}
    std::sort(csl.begin(),csl.end());
	return csl;
}


void LatexDocument::updateRefsLabels(const QString &ref)
{
	// get occurences (refs)
	int referenceMultipleFormat = getFormatId("referenceMultiple");
	int referencePresentFormat = getFormatId("referencePresent");
	int referenceMissingFormat = getFormatId("referenceMissing");
    const QList<int> formatList{referenceMissingFormat,referencePresentFormat,referenceMultipleFormat};

	int cnt = countLabels(ref);
	QMultiHash<QDocumentLineHandle *, int> occurences = getLabels(ref);
	occurences += getRefs(ref);
	QMultiHash<QDocumentLineHandle *, int>::const_iterator it;
	for (it = occurences.constBegin(); it != occurences.constEnd(); ++it) {
		QDocumentLineHandle *dlh = it.key();
        for(const int pos : occurences.values(dlh)) {
            foreach (const auto &format, formatList) {
                dlh->removeOverlay(QFormatRange(pos, ref.length(), format));
            }
			if (cnt > 1) {
				dlh->addOverlay(QFormatRange(pos, ref.length(), referenceMultipleFormat));
			} else if (cnt == 1) dlh->addOverlay(QFormatRange(pos, ref.length(), referencePresentFormat));
			else dlh->addOverlay(QFormatRange(pos, ref.length(), referenceMissingFormat));
		}
	}
}



LatexDocuments::LatexDocuments(): masterDocument(nullptr), currentDocument(nullptr), bibTeXFilesModified(false)
{
	showLineNumbersInStructure = false;
	indentationInStructure = -1;
	showCommentedElementsInStructure = false;
	markStructureElementsBeyondEnd = true;
	markStructureElementsInAppendix = true;
	indentIncludesInStructure = false;
	m_patchEnabled = true;
}

void LatexDocuments::addDocument(LatexDocument *document, bool hidden)
{
	if (hidden) {
		hiddenDocuments.append(document);
		LatexEditorView *edView = document->getEditorView();
		if (edView) {
			QEditor *ed = edView->getEditor();
			if (ed) {
				document->remeberAutoReload = ed->silentReloadOnExternalChanges();
				ed->setSilentReloadOnExternalChanges(true);
				ed->setHidden(true);
			}
		}
	} else {
		documents.append(document);
        hiddenDocuments.removeAll(document); // make sure to avoid duplicates
	}
	connect(document, SIGNAL(updateBibTeXFiles()), SLOT(bibTeXFilesNeedUpdate()));
	document->parent = this;
	if (masterDocument) {
		// repaint all docs
		foreach (const LatexDocument *doc, documents) {
			LatexEditorView *edView = doc->getEditorView();
			if (edView) edView->documentContentChanged(0, edView->editor->document()->lines());
		}
	}
}

void LatexDocuments::deleteDocument(LatexDocument *document, bool hidden, bool purge)
{
    // save caching information
    document->saveCachingData(m_cachingFolder);
    if (!hidden)
        emit aboutToDeleteDocument(document);
    LatexEditorView *view = document->getEditorView();
    if (view)
        view->closeCompleter();
    if ((document != masterDocument)||(documents.count()==1) ) {
        // get list of all affected documents
        QList<LatexDocument *> lstOfDocs = document->getListOfDocs();
        // special treatment to remove document in purge mode (hidden doc was deleted on disc)
        if (purge) {
            Q_ASSERT(hidden); //purging non-hidden doc crashes.
            LatexDocument *rootDoc = document->getRootDocument();
            hiddenDocuments.removeAll(document);
            foreach (LatexDocument *elem, getDocuments()) {
                if (elem->containsChild(document)) {
                    elem->removeChild(document);
                }
            }
            //update children (connection to parents is severed)
            foreach (LatexDocument *elem, lstOfDocs) {
                if (elem->getMasterDocument() == document) {
                    if (elem->isHidden())
                        deleteDocument(elem, true, true);
                    else
                        elem->setMasterDocument(nullptr);
                }
            }
            delete document;
            if (rootDoc != document) {
                // update parents
                lstOfDocs = rootDoc->getListOfDocs();
                int n = 0;
                foreach (LatexDocument *elem, lstOfDocs) {
                    if (!elem->isHidden()) {
                        n++;
                        break;
                    }
                }
                if (n == 0)
                    deleteDocument(rootDoc, true, true);
                else
                    updateMasterSlaveRelations(rootDoc, true, true);
            }
            return;
        }
        // count open related (child/parent) documents
        int n = 0;
        foreach (LatexDocument *elem, lstOfDocs) {
            if (!elem->isHidden())
                n++;
        }
        if (hidden) {
            hiddenDocuments.removeAll(document);
            return;
        }
        if (n > 1 && !document->getFileName().isEmpty()) { // at least one related document will be open after removal
            hiddenDocuments.append(document);
            LatexEditorView *edView = document->getEditorView();
            if (edView) {
                QEditor *ed = edView->getEditor();
                if (ed) {
                    document->remeberAutoReload = ed->silentReloadOnExternalChanges();
                    ed->setSilentReloadOnExternalChanges(true);
                    ed->setHidden(true);
                }
            }
        } else {
            // no open document remains, remove all others as well
            foreach (LatexDocument *elem, getDocuments()) {
                if (elem->containsChild(document)) {
                    elem->removeChild(document);
                }
            }
            foreach (LatexDocument *elem, lstOfDocs) {
                if (elem->isHidden()) {
                    hiddenDocuments.removeAll(elem);
                    elem->saveCachingData(m_cachingFolder);
                    delete elem->getEditorView();
                    delete elem;
                }
            }
        }

        documents.removeAll(document);
        if (document == currentDocument) {
            currentDocument = nullptr;
        }

        if (n > 1 && !document->getFileName().isEmpty()) { // don't remove document, stays hidden instead (except if it is not saved at all,i.e. no filename)
            hideDocInEditor(document->getEditorView());
            if(masterDocument && documents.count()==1){
                // special check if masterDocument, but document is not visible
                LatexDocument *doc=documents.first();
                if(!doc->getEditorView()){
                    // no view left -> purge
                    deleteDocument(masterDocument);
                }
            }
            return;
        }
        delete view;
        delete document;
    } else {
        if (hidden) {
            hiddenDocuments.removeAll(document);
            return;
        }
        document->setFileName(document->getFileName());
        document->clearAppendix();
        delete view;
        if (document == currentDocument)
            currentDocument = nullptr;
    }
    // purge masterdocument if none is left
    if(documents.isEmpty()){
        if(masterDocument){
            masterDocument=nullptr;
        }
        hiddenDocuments.clear();
    }
}

void LatexDocuments::requestedClose()
{
	QEditor *editor = qobject_cast<QEditor *>(sender());
	LatexDocument *doc = qobject_cast<LatexDocument *>(editor->document());
	deleteDocument(doc, true, true);
}
/*!
 * \brief set \param document as new master document
 * Garcefully close old master document if set and set document as new master
 * \param document
 */
void LatexDocuments::setMasterDocument(LatexDocument *document)
{
	if (document == masterDocument) return;
	if (masterDocument != nullptr && masterDocument->getEditorView() == nullptr) {
        QString fn = masterDocument->getFileName();
		LatexDocument *doc = masterDocument;
		masterDocument = nullptr;
		deleteDocument(doc);
	}
	masterDocument = document;
	if (masterDocument != nullptr) {
		documents.removeAll(masterDocument);
		documents.prepend(masterDocument);
		// repaint doc
		foreach (LatexDocument *doc, documents) {
            LatexEditorView *edView = doc->getEditorView();
            if (edView) edView->documentContentChanged(0, doc->lines());
		}
	}
	emit masterDocumentChanged(masterDocument);
}
/*!
 * \brief return current document
 * \return current document
 */
LatexDocument *LatexDocuments::getCurrentDocument() const
{
	return currentDocument;
}
/*!
 * \brief return master document if one is set
 * \return masterDocument
 */
LatexDocument *LatexDocuments::getMasterDocument() const
{
	return masterDocument;
}

/*!
 * \brief return list of *all* open documents
 * This includes visibles and hidden documents in memory
 * \return list of documents
 */
QList<LatexDocument *> LatexDocuments::getDocuments() const
{
	QList<LatexDocument *> docs = documents + hiddenDocuments;
	return docs;
}

void LatexDocuments::move(int from, int to)
{
	documents.move(from, to);
}
/*!
 * \brief get file name of current document
 * \return file name
 */
QString LatexDocuments::getCurrentFileName() const
{
	if (!currentDocument) return "";
	return currentDocument->getFileName();
}

QString LatexDocuments::getCompileFileName() const
{
	if (masterDocument)
		return masterDocument->getFileName();
	if (!currentDocument)
		return "";
	// check for magic comment
	QString curDocFile = currentDocument->getMagicComment("root");
	if (curDocFile.isEmpty())
		curDocFile = currentDocument->getMagicComment("texroot");
	if (!curDocFile.isEmpty()) {
		return currentDocument->findFileName(curDocFile);
	}
	//
    const LatexDocument *rootDoc = currentDocument->getRootDocument(nullptr,true);
	curDocFile = currentDocument->getFileName();
	if (rootDoc)
		curDocFile = rootDoc->getFileName();
	return curDocFile;
}

QString LatexDocuments::getTemporaryCompileFileName() const
{
	QString temp = getCompileFileName();
	if (!temp.isEmpty()) return temp;
	if (masterDocument) return masterDocument->getTemporaryFileName();
	else if (currentDocument) return currentDocument->getTemporaryFileName();
	return "";
}

QString LatexDocuments::getLogFileName() const
{
	if (!currentDocument) return QString();
	LatexDocument *rootDoc = currentDocument->getRootDocument();
	QString jobName = rootDoc->getMagicComment("-job-name");
	if (!jobName.isEmpty()) {
		return ensureTrailingDirSeparator(rootDoc->getFileInfo().absolutePath()) + jobName + ".log";
	} else {
		return replaceFileExtension(getTemporaryCompileFileName(), ".log");
	}
}

QString LatexDocuments::getAbsoluteFilePath(const QString &relName, const QString &extension, const QStringList &additionalSearchPaths) const
{
	if (!currentDocument) return relName;
	return currentDocument->getAbsoluteFilePath(relName, extension, additionalSearchPaths);
}

LatexDocument *LatexDocuments::findDocumentFromName(const QString &fileName) const
{
	QList<LatexDocument *> docs = getDocuments();
	foreach (LatexDocument *doc, docs) {
		if (doc->getFileName() == fileName) return doc;
	}
    return nullptr;
}

/*!
 * Adjust the internal order of documents to the given order.
 * \param order should contain exactly the same documents as this.
 */
void LatexDocuments::reorder(const QList<LatexDocument *> &order)
{
	if (order.size() != documents.size()) qDebug() << "Warning: Size of list of documents for reordering differs from current documents";
	foreach (LatexDocument *doc, order) {
		int n = documents.removeAll(doc);
		if (n > 1) qDebug() << "Warning: document listed multiple times in LatexDocuments";
		if (n < 1) qDebug() << "Warning: encountered a document that is not listed in LatexDocuments";
		documents.append(doc);
	}
}

LatexDocument *LatexDocuments::findDocument(const QDocument *qDoc) const
{
	QList<LatexDocument *> docs = getDocuments();
	foreach (LatexDocument *doc, docs) {
		LatexEditorView *edView = doc->getEditorView();
		if (edView && edView->editor->document() == qDoc) return doc;
	}
    return nullptr;
}

LatexDocument *LatexDocuments::findDocument(const QString &fileName, bool checkTemporaryNames) const
{
    if (fileName == "") return nullptr;
	if (checkTemporaryNames) {
		LatexDocument *temp = findDocument(fileName, false);
		if (temp) return temp;
	}

	QFileInfo fi(fileName);
	fi = getNonSymbolicFileInfo(fi);
	if (fi.exists()) {
		foreach (LatexDocument *document, documents) {
			if (document->getFileInfo() == fi) {
				return document;
			}
		}
		if (checkTemporaryNames) {
			foreach (LatexDocument *document, documents) {
				if (document->getFileName().isEmpty() && document->getTemporaryFileInfo() == fi) {
					return document;
				}
			}
		}
	}

	//check for relative file names
	fi.setFile(getAbsoluteFilePath(fileName));
	if (!fi.exists()) {
		fi.setFile(getAbsoluteFilePath(fileName), ".tex");
	}
	if (!fi.exists()) {
		fi.setFile(getAbsoluteFilePath(fileName), ".bib");
	}
	if (fi.exists()) {
		foreach (LatexDocument *document, documents) {
			if (document->getFileInfo().exists() && document->getFileInfo() == fi) {
				return document;
			}
		}
	}

    return nullptr;
}

void LatexDocuments::settingsRead()
{
    return; // currently unused
}

void LatexDocuments::setCachingFolder(const QString &folder)
{
    m_cachingFolder=folder;
}

QString LatexDocuments::getCachingFolder() const
{
    return m_cachingFolder;
}

bool LatexDocuments::singleMode() const
{
	return !masterDocument;
}

void LatexDocuments::updateBibFiles(bool updateFiles)
{
	mentionedBibTeXFiles.clear();
	QStringList additionalBibPaths = ConfigManagerInterface::getInstance()->getOption("Files/Bib Paths").toString().split(getPathListSeparator());
	foreach (LatexDocument *doc, getDocuments() ) {
		if (updateFiles) {
			QMultiHash<QDocumentLineHandle *, FileNamePair>::iterator it = doc->mentionedBibTeXFiles().begin();
			QMultiHash<QDocumentLineHandle *, FileNamePair>::iterator itend = doc->mentionedBibTeXFiles().end();
			for (; it != itend; ++it) {
                if(it.value().absolute.isEmpty()){
                    it.value().absolute = getAbsoluteFilePath(it.value().relative, ".bib", additionalBibPaths).replace(QDir::separator(), "/"); // update absolute path
                }
				mentionedBibTeXFiles << it.value().absolute;
			}
		}
	}

	//bool changed=false;
	if (updateFiles) {
		QString bibFileEncoding = ConfigManagerInterface::getInstance()->getOption("Bibliography/BibFileEncoding").toString();
		QTextCodec *defaultCodec = QTextCodec::codecForName(bibFileEncoding.toLatin1());
		for (int i = 0; i < mentionedBibTeXFiles.count(); i++) {
			QString &fileName = mentionedBibTeXFiles[i];
			QFileInfo fi(fileName);
			if (!fi.isReadable()) continue; //ups...
			if (!bibTeXFiles.contains(fileName))
				bibTeXFiles.insert(fileName, BibTeXFileInfo());
			BibTeXFileInfo &bibTex = bibTeXFiles[mentionedBibTeXFiles[i]];
			// TODO: allow to use the encoding of the tex file which mentions the bib file (need to port this information from above)
			bibTex.codec = defaultCodec;
            bibTex.loadIfModified(QFileInfo(fileName));

			/*if (bibTex.loadIfModified(fileName))
				changed = true;*/
			if (bibTex.ids.empty() && !bibTex.linksTo.isEmpty())
				//handle obscure bib tex feature, a just line containing "link fileName"
				mentionedBibTeXFiles.append(bibTex.linksTo);
		}
	}
	/*
	if (changed || (newBibItems!=bibItems)) {
		allBibTeXIds.clear();
		bibItems=newBibItems;
		for (QMap<QString, BibTeXFileInfo>::const_iterator it=bibTeXFiles.constBegin(); it!=bibTeXFiles.constEnd();++it)
			foreach (const QString& s, it.value().ids)
		allBibTeXIds << s;
		allBibTeXIds.unite(bibItems);
		for (int i=0;i<documents.size();i++)
			if (documents[i]->getEditorView())
				documents[i]->getEditorView()->setBibTeXIds(&allBibTeXIds);
		bibTeXFilesModified=true;
	}*/
}

void LatexDocuments::removeDocs(QStringList removeIncludes)
{
    QSet<LatexDocument*> lstRecheckLabels;
	foreach (QString fname, removeIncludes) {
		LatexDocument *dc = findDocumentFromName(fname);
		if (dc) {
			foreach (LatexDocument *elem, getDocuments()) {
				if (elem->containsChild(dc)) {
					elem->removeChild(dc);
                    if(!dc->labelItems().isEmpty()){
                        elem->recheckRefsLabels();
                    }
				}
			}
		}
		if (dc && dc->isHidden()) {
			QStringList toremove = dc->includedFiles();
            dc->setMasterDocument(nullptr,false);
			hiddenDocuments.removeAll(dc);
			//qDebug()<<fname;
			delete dc->getEditorView();
			delete dc;
			if (!toremove.isEmpty())
				removeDocs(toremove);
		}
	}
}

/*!
 * \brief load included documents as hidden
 * Load all in parallel
 * Perform lexing only
 * \param filenames
 * \return true if newly loaded files contains packages
 */
std::pair<bool,bool> LatexDocuments::addDocsToLoad(QStringList filenames, LatexDocument *parentDocument,bool isHigherLevel)
{
    auto *conf=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    bool newPackagesFound=false;
    bool newUserCommandsFound=false;
    if(conf->autoLoadChildren){
        LatexDocument *docForUpdate=nullptr;
        for(const QString &fn:filenames){
            if(fn.isEmpty()) continue; // avoid potential crash
            LatexDocument *doc = findDocumentFromName(fn);
            if(doc==nullptr){
                doc=new LatexDocument();
                doc->parent=this;
                doc->setFileName(fn);
                addDocument(doc,true);
                if(!doc->restoreCachedData(getCachingFolder(),fn)){
                    doc->load(fn,QDocument::defaultCodec());
                }
                doc->setLtxCommands(parentDocument->lp);
                if(doc->isIncompleteInMemory()){
                    // gather all commands from all child documents
                    // needed for cached files
                    QList<LatexDocument *>listOfDocs = doc->getListOfDocs();
                    foreach (const LatexDocument *elem, listOfDocs) {
                        if(elem==doc) continue;
                        doc->lp->append(elem->ltxCommands);
                    }
                }
                if(!isHigherLevel){
                    // child document is added
                    // don't run if actually a root document is added, e.g. % texroot=...
                    doc->setMasterDocument(parentDocument,false);
                    parentDocument->addChild(doc);
                }
                doc->patchStructure(0,-1);
                doc->lp->append(doc->ltxCommands);
                docForUpdate=doc;
                newPackagesFound|=!doc->usedPackages(true).isEmpty();
                newUserCommandsFound|=!doc->userCommandList().isEmpty();
            }
        }
        if(docForUpdate){
            QList<LatexDocument *>listOfDocs = parentDocument->getListOfDocs();
            QStringList items;
            foreach (LatexDocument *elem, listOfDocs) {
                elem->setLtxCommands(parentDocument->lp);
                elem->reCheckSyntax(); //rescan as well ?
                items << elem->labelItems();
            }
            foreach (LatexDocument *elem, listOfDocs) {
                if(elem->getEditorView()){
                    elem->recheckRefsLabels(listOfDocs,items);
                    elem->getEditorView()->updateCitationFormats(); // TODO: inefficent -> improve
                }
            }
        }
    }
    return std::pair<bool,bool>{newPackagesFound,newUserCommandsFound};
}

void LatexDocuments::hideDocInEditor(LatexEditorView *edView)
{
	emit docToHide(edView);
}

/*!
 * \brief remove all structure entries in range lineNr .. lineNr+count-1
 * \param lineNr
 * \param count
 */
void LatexDocument::removeRangeFromStructure(int lineNr, int count)
{
    for(auto it=docStructure.begin();it!=docStructure.end();){
        StructureEntry *element=*it;
        int ln=element->getRealLineNumber();
        if(ln<lineNr){
            ++it;
            continue;
        }
        if(ln<lineNr+count){
            delete *it;
            it=docStructure.erase(it);
            continue;
        }
        break;
    }
}

/*!
 * \brief represent local toc with section only as stringlist
 * \return
 */
QStringList LatexDocument::unrollStructure()
{
    QStringList result;

    for(std::list<StructureEntry*>::iterator iter=docStructure.begin();iter!=docStructure.end();++iter){
        StructureEntry *curSection = *iter;
        if (curSection->type == StructureEntry::SE_SECTION){
            result<<QString("%1").arg(curSection->level)+"#"+curSection->title+"#"+QString("%1").arg(curSection->getRealLineNumber());
        }
        if (curSection->type == StructureEntry::SE_INCLUDE){
            result<<QString("%1").arg(-1)+"#"+curSection->title+"#"+QString("%1").arg(curSection->getRealLineNumber());
        }
    }
    return result;
}

/*!
  Splits a [name] = [val] string into \a name and \a val removing extra spaces.

  \return true if splitting successful, false otherwise (in that case name and val are empty)
 */
bool LatexDocument::splitMagicComment(const QString &comment, QString &name, QString &val)
{
	int sep = comment.indexOf("=");
	if (sep < 0) return false;
	name = comment.left(sep).trimmed();
	val = comment.mid(sep + 1).trimmed();
	return true;
}

/*!
  Used by the parser to add a magic comment

\a text is the comment without the leading "! TeX" declaration. e.g. "spellcheck = DE-de"
\a lineNr - line number of the magic comment
\a posMagicComment - Zero-based position of magic comment in the structure list tree view.
  */
void LatexDocument::addMagicComment(const QString &text, int lineNr, std::list<StructureEntry*>::iterator &docStructureIter)
{
	StructureEntry *newMagicComment = new StructureEntry(this, StructureEntry::SE_MAGICCOMMENT);
	QDocumentLineHandle *dlh = line(lineNr).handle();
	QString name;
	QString val;
	splitMagicComment(text, name, val);

	parseMagicComment(name, val, newMagicComment);
	newMagicComment->title = text;
	newMagicComment->setLine(dlh, lineNr);
    replaceOrAdd(docStructureIter,dlh,newMagicComment);
}

/*!
  Formats the StructureEntry and modifies the document according to the MagicComment contents
  */
void LatexDocument::parseMagicComment(const QString &name, const QString &val, StructureEntry *se)
{
	se->valid = false;
	se->tooltip = QString();

	QString lowerName = name.toLower();
	if (lowerName == "spellcheck") {
		mSpellingDictName = val;
		emit spellingDictChanged(mSpellingDictName);
		se->valid = true;
	} else if ((lowerName == "texroot") || (lowerName == "root")) {
		QString fname = findFileName(val);
        if(!fname.isEmpty()){
            LatexDocument *dc = parent->findDocumentFromName(fname);
            if (dc) {
                dc->childDocs.insert(this);
                setMasterDocument(dc);
            } else {
                parent->addDocsToLoad(QStringList(fname),this,true);
            }
            se->valid = true;
        } else {
            se->tooltip = tr("Root file not found");
        }
	} else if (lowerName == "encoding") {
		QTextCodec *codec = QTextCodec::codecForName(val.toLatin1());
		if (!codec) {
			se->tooltip = tr("Invalid codec");
			return;
		}
		setCodecDirect(codec);
		emit encodingChanged();
		se->valid = true;
	} else if (lowerName == "txs-script") {
		se->valid = true;
	} else if (lowerName == "program" || lowerName == "ts-program" || lowerName.startsWith("txs-program:")) {
		se->valid = true;
	} else if (lowerName == "-job-name") {
		if (!val.isEmpty()) {
			se->valid = true;
		} else {
			se->tooltip = tr("Missing value for -job-name");
		}
	} else {
		se->tooltip = tr("Unknown magic comment");
	}
}

void LatexDocument::updateContext(QDocumentLineHandle *oldLine, QDocumentLineHandle *newLine, StructureEntry::Context context)
{
	int endLine = newLine ? indexOf(newLine) : -1 ;
	int startLine = -1;
	if (oldLine) {
		startLine = indexOf(oldLine);
		if (endLine < 0 || endLine > startLine) {
            // remove appendix marker
            setContextForLines(startLine, endLine, context, false);
		}
	}

	if (endLine > -1 && (endLine < startLine || startLine < 0)) {
        setContextForLines(endLine, startLine, context, true);
	}
}

void LatexDocument::setContextForLines(int startLine, int endLine, StructureEntry::Context context, bool state)
{
    for (auto it = docStructure.begin(); it != docStructure.end(); ++it) {
        StructureEntry *elem = *it;
		if (endLine >= 0 && elem->getLineHandle() && elem->getRealLineNumber() > endLine) break;
        if (elem->type == StructureEntry::SE_SECTION && elem->getRealLineNumber() >= startLine) {
			elem->setContext(context, state);
		}
	}
}

bool LatexDocument::fileExits(QString fname)
{
	QString curPath = ensureTrailingDirSeparator(getFileInfo().absolutePath());
	bool exist = QFile(getAbsoluteFilePath(fname, ".tex")).exists();
	if (!exist) exist = QFile(getAbsoluteFilePath(curPath + fname, ".tex")).exists();
	if (!exist) exist = QFile(getAbsoluteFilePath(curPath + fname, "")).exists();
	return exist;
}

/*!
 * A line snapshot is a list of DocumentLineHandles at a given time.
 * For example, this is used to reconstruct the line number at latex compile time
 * allowing syncing from PDF to the correct source line also after altering the source document
 */
void LatexDocument::saveLineSnapshot()
{
	foreach (QDocumentLineHandle *dlh, mLineSnapshot) {
		dlh->deref();
	}
	mLineSnapshot.clear();
	mLineSnapshot.reserve(lineCount());
	QDocumentConstIterator it = begin(), e = end();
	while (it != e) {
		mLineSnapshot.append(*it);
		(*it)->ref();
		it++;
	}
}

// get the line with given lineNumber (0-based) from the snapshot
QDocumentLine LatexDocument::lineFromLineSnapshot(int lineNumber)
{
	if (lineNumber < 0 || lineNumber >= mLineSnapshot.count()) return QDocumentLine();
	return QDocumentLine(mLineSnapshot.at(lineNumber));
}

// returns the 0-based number of the line in the snapshot, or -1 if line is not in the snapshot
int LatexDocument::lineToLineSnapshotLineNumber(const QDocumentLine &line)
{
	return mLineSnapshot.indexOf(line.handle());
}

QString LatexDocument::findFileName(QString fname)
{
	QString curPath = ensureTrailingDirSeparator(getFileInfo().absolutePath());
    QStringList additionalInputPaths = ConfigManagerInterface::getInstance()->getOption("Files/Input Paths").toString().split(getPathListSeparator());
	QString result;
    if (QFile(getAbsoluteFilePath(fname, ".tex", additionalInputPaths)).exists())
        result = QFileInfo(getAbsoluteFilePath(fname, ".tex", additionalInputPaths)).absoluteFilePath();
    if (result.isEmpty() && QFile(getAbsoluteFilePath(curPath + fname, ".tex", additionalInputPaths)).exists())
        result = QFileInfo(getAbsoluteFilePath(curPath + fname, ".tex", additionalInputPaths)).absoluteFilePath();
    if (result.isEmpty() && QFile(getAbsoluteFilePath(curPath + fname, "", additionalInputPaths)).exists())
        result = QFileInfo(getAbsoluteFilePath(curPath + fname, "", additionalInputPaths)).absoluteFilePath();
	return result;
}

void LatexDocuments::bibTeXFilesNeedUpdate()
{
	bibTeXFilesModified = true;
}
/*!
 * \brief update parent/child relations
 * doc is removed and the child settings needs to be adapted
 * \param doc
 * \param recheckRefs
 * \param updateCompleterNow
 */
void LatexDocuments::updateMasterSlaveRelations(LatexDocument *doc, bool recheckRefs, bool updateCompleterNow)
{
	//update Master/Child relations
	//remove old settings ...
	doc->setMasterDocument(nullptr, false);
    const QList<LatexDocument *> docs = getDocuments();
    QSet<LatexDocument *> removeCandidates;
	foreach (LatexDocument *elem, docs) {
		if (elem->getMasterDocument() == doc) {
            removeCandidates.insert(elem);
		}
	}

	//check whether document is child of other docs
    QString fname = doc->getFileName();
	foreach (LatexDocument *elem, docs) {
		if (elem == doc)
			continue;
		QStringList includedFiles = elem->includedFiles();
        QStringList importedFiles = elem->includedFiles(true);
        if (includedFiles.contains(fname)) {
            if(!elem->containsChild(doc)){
                elem->addChild(doc);
            }
            doc->setMasterDocument(elem, false);
		}
        if (importedFiles.contains(fname)) {
            doc->setAsImportedFile(true);
        }
    }

	// check for already open child documents (included in this file)
	QStringList includedFiles = doc->includedFiles();
    foreach (const QString &fname, includedFiles) {
        LatexDocument *child = this->findDocumentFromName(fname);
        if (child){
            if(removeCandidates.contains(child)){
                removeCandidates.remove(child);
            }
            if(!doc->containsChild(child)) {
                doc->addChild(child);
                child->setMasterDocument(doc, false);
                if (recheckRefs)
                    child->reCheckSyntax(); // redo syntax checking (in case of defined commands)
            }
        }
    }
    foreach(LatexDocument *elem, removeCandidates){
        doc->removeChild(elem);
        elem->setMasterDocument(nullptr, recheckRefs);
    }

	//recheck references
    if(recheckRefs){
        doc->recheckRefsLabels();
    }

    if(updateCompleterNow){
		doc->emitUpdateCompleter();
    }
}
/*!
 * \brief get root document
 * Walk up through document structures
 * \param visitedDocs keep track of visisted document to break closed circles
 * \param breakAtSubfileRoot break at a dtected subfile root
 * \return detected root document
 */
const LatexDocument *LatexDocument::getRootDocument(QSet<const LatexDocument *> *visitedDocs,bool breakAtSubfileRoot) const
{
	// special handling if explicit master is set
    if(!parent) return nullptr;
	if (parent && parent->masterDocument)
		return parent->masterDocument;
    const LatexDocument *result = this;
    if(breakAtSubfileRoot && m_isSubfileRoot){
        return result;
    }
	bool deleteVisitedDocs = false;
	if (!visitedDocs) {
		visitedDocs = new QSet<const LatexDocument *>();
		deleteVisitedDocs = true;
	}
	visitedDocs->insert(this);
	if (masterDocument && !visitedDocs->contains(masterDocument))
		result = masterDocument->getRootDocument(visitedDocs);
    if (result->getFileName().endsWith("bib")){
        for(const LatexDocument *d : parent->documents) {
			QMultiHash<QDocumentLineHandle *, FileNamePair>::const_iterator it = d->mentionedBibTeXFiles().constBegin();
			QMultiHash<QDocumentLineHandle *, FileNamePair>::const_iterator itend = d->mentionedBibTeXFiles().constEnd();
			for (; it != itend; ++it) {
				//qDebug() << it.value().absolute << " <> "<<result->getFileName();
				if (it.value().absolute == result->getFileName()) {
					result = d->getRootDocument(visitedDocs);
					break;
				}
			}
			if (result == d) break;
		}
    }
	if (deleteVisitedDocs)
		delete visitedDocs;
	return result;
}

LatexDocument *LatexDocument::getRootDocument()
{
    return const_cast<LatexDocument *>(getRootDocument(nullptr));
}

LatexDocument *LatexDocument::getTopMasterDocument()
{
    return getRootDocument();    // DEPRECATED: only the for backward compatibility of user scripts
}

QStringList LatexDocument::includedFiles(bool importsOnly)
{
    QStringList helper;
    if(!importsOnly){
        helper.append(mIncludedFilesList.values());
    }
    helper.append(mImportedFilesList.values());
	QStringList result;
	foreach (const QString elem, helper) {
		if (!elem.isEmpty() && !result.contains(elem))
			result << elem;
	}

	return result;
}

QStringList LatexDocument::includedFilesAndParent()
{
	QStringList result = includedFiles();
	QString t = getMagicComment("root");
	if (!t.isEmpty() && !result.contains(t)) result << t;
	t = getMagicComment("texroot");
	if (!t.isEmpty() && !result.contains(t)) result << t;
	if (masterDocument && !result.contains(masterDocument->getFileName()))
		result << masterDocument->getFileName();
	return result;
}

CodeSnippetList LatexDocument::additionalCommandsList(QStringList &loadedFiles)
{
	LatexPackage pck;
    QStringList files = mCWLFiles.values();
	gatherCompletionFiles(files, loadedFiles, pck, true);
	return pck.completionWords;
}

bool LatexDocument::updateCompletionFiles(const bool updatePackages, const bool updateUserCommands)
{
    if(updatePackages){
        QSet<QString> userCommands=ltxCommands.possibleCommands["user"]; // keep user commands
        QSet<QString> columnCommands=ltxCommands.possibleCommands["%columntypes"];
        QHash<QString, QSet<QString> > cacheCommands;
        cacheCommands["%color"]=ltxCommands.possibleCommands["%color"];
        for(const QString &key:lp->mapSpecialArgs.values()){
            cacheCommands[key]=ltxCommands.possibleCommands[key];
        }

        QStringList files = mUsepackageList.values();
        LatexParser &latexParser = LatexParser::getInstance();

        //recheck syntax of ALL documents ...

        LatexPackage pck;
        pck.commandDescriptions = latexParser.commandDefs;
        pck.specialDefCommands = latexParser.specialDefCommands;
        QStringList loadedFiles;
        for (int i = 0; i < files.count(); i++) {
            if (!files.at(i).endsWith(".cwl"))
                files[i] = files[i] + ".cwl";
        }
        gatherCompletionFiles(files, loadedFiles, pck);
        mCWLFiles = convertStringListtoSet(loadedFiles);
        ltxCommands.optionCommands = pck.optionCommands;
        ltxCommands.specialDefCommands = pck.specialDefCommands;
        ltxCommands.possibleCommands = pck.possibleCommands;
        ltxCommands.environmentAliases = pck.environmentAliases;
        ltxCommands.commandDefs = pck.commandDescriptions;

        ltxCommands.possibleCommands["user"] = userCommands;// keep user commands
        ltxCommands.possibleCommands["%columntypes"] = columnCommands;
        for(const QString &key:cacheCommands.keys()){
            ltxCommands.possibleCommands[key].unite(cacheCommands[key]);
        }
    }
    if(updateUserCommands){
        // user commands
        QList<UserCommandPair> commands = mUserCommandList.values();
        foreach (UserCommandPair cmd, commands) {
            QString elem = cmd.snippet.word;
            if (elem.startsWith("%")) { // insert specialArgs
                int i = elem.indexOf('%', 1);
                QString category = elem.left(i);
                elem = elem.mid(i + 1);
                ltxCommands.possibleCommands[category].insert(elem);
                continue;
            }
        }
    }

    updateLtxCommands(true,updatePackages);

	return false;
}

const QSet<QString> &LatexDocument::getCWLFiles() const
{
	return mCWLFiles;
}

QString LatexDocument::spellingDictName() const
{
    return mSpellingDictName;
}

void LatexDocument::emitUpdateCompleter()
{
    emit updateCompleter();
}

void LatexDocument::gatherCompletionFiles(QStringList &files, QStringList &loadedFiles, LatexPackage &pck, bool gatherForCompleter)
{
    LatexPackage zw;
    LatexCompleterConfig *completerConfig = edView->getCompleter()->getConfig();
    foreach (const QString &elem, files) {
        if (loadedFiles.contains(elem))
            continue;
        if (parent->cachedPackages.contains(elem)) {
            zw = parent->cachedPackages.value(elem);
        } else {
            // check if package is actually not depending on options
            QString fileName = LatexPackage::keyToCwlFilename(elem);
            QStringList options = LatexPackage::keyToOptions(elem);
            bool found=false;
            if(parent->cachedPackages.contains(fileName) ){
                zw = parent->cachedPackages.value(fileName);
                found=!zw.containsOptionalSections;
            }
            if(!found){
                if(fileName.startsWith(".")){
                    // replace relative path with absolute with repsit to root document
                    QFileInfo fi=getRootDocument()->getFileInfo();
                    QFileInfo fi_cwl=QFileInfo(fi.absolutePath(),fileName);
                    fileName=fi_cwl.absoluteFilePath();
                }
                zw = loadCwlFile(fileName, completerConfig, options);
                if (!zw.notFound) {
                    fileName= zw.containsOptionalSections ? elem : fileName;
                    parent->cachedPackages.insert(fileName, zw); // cache package
                } else {
                    LatexPackage zw;
                    zw.packageName = fileName;
                    parent->cachedPackages.insert(fileName, zw); // cache package as empty/not found package
                }
            }
        }
        if (zw.notFound) {
            QString name = elem;
            LatexDocument *masterDoc = getRootDocument();
            if (masterDoc) {
                QString fn = masterDoc->getFileInfo().absolutePath();
                name += "/" + fn;
            }
            emit importPackage(name);
        } else {
            pck.unite(zw, gatherForCompleter);
            loadedFiles.append(elem);
            if (!zw.requiredPackages.isEmpty())
                gatherCompletionFiles(zw.requiredPackages, loadedFiles, pck, gatherForCompleter);
        }
    }
}

void LatexDocument::setHideNonTextGrammarErrors(bool hide)
{
    m_hideNonTextGrammarErrors=hide;
}

void LatexDocument::setGrammarFormats(const QList<int> &formats)
{
    m_grammarFormats = formats;
}

QString LatexDocument::getMagicComment(const QString &name) const
{
	QString seName;
    QString val;
    for (auto iter=docStructure.cbegin();iter!=docStructure.cend();++iter) {
        StructureEntry *se = *iter;
        if(se->type != StructureEntry::SE_MAGICCOMMENT) continue;
		splitMagicComment(se->title, seName, val);
		if (seName.toLower() == name.toLower())
			return val;
	}
	return QString();
}

StructureEntry *LatexDocument::getMagicCommentEntry(const QString &name) const
{
	QString seName;
	QString val;

    for (auto iter=docStructure.cbegin();iter!=docStructure.cend();++iter) {
        StructureEntry *se = *iter;
        if(se->type != StructureEntry::SE_MAGICCOMMENT) continue;
		splitMagicComment(se->title, seName, val);
		if (seName == name) return se;
	}
	return nullptr;
}

/*!
  replaces the value of the magic comment
 */
void LatexDocument::updateMagicComment(const QString &name, const QString &val, bool createIfNonExisting,QString prefix)
{
    QString line(QString("% %1 %2 = %3").arg(prefix,name,val));

	StructureEntry *se = getMagicCommentEntry(name);
    QDocumentLineHandle *dlh = se ? se->getLineHandle() : nullptr;
	if (dlh) {
		QString n, v;
		splitMagicComment(se->title, n, v);
		if (v != val) {
			QDocumentCursor cur(this, indexOf(dlh));
			cur.select(QDocumentCursor::LineUnderCursor);
			cur.replaceSelectedText(line);
		}
	} else {
		if (createIfNonExisting) {
			QDocumentCursor cur(this);
			cur.insertText(line + "\n");
            if(val.isEmpty()){
                cur.movePosition(1,QDocumentCursor::PreviousCharacter);
                getEditorView()->editor->setCursor(cur);
            }
		}
	}
}

void LatexDocument::updateMagicCommentScripts()
{
	localMacros.clear();

    QRegularExpression rxTrigger("^ *// *(Trigger) *[:=](.*)$");

    for (auto iter=docStructure.cbegin();iter!=docStructure.cend();++iter) {
        StructureEntry *se = *iter;
        if(se->type != StructureEntry::SE_MAGICCOMMENT) continue;
		QString seName, val;
		splitMagicComment(se->title, seName, val);
		if (seName == "TXS-SCRIPT") {
			QString name = val;
			QString trigger = "";
			QString tag;

			int l = se->getRealLineNumber() + 1;
			for (; l < lineCount(); l++) {
				QString lt = line(l).text().trimmed();
				if (lt.endsWith("TXS-SCRIPT-END") || !(lt.isEmpty() || lt.startsWith("%"))  ) break;
				lt.remove(0, 1);
				tag += lt + "\n";
                QRegularExpressionMatch rxTriggerMatch = rxTrigger.match(lt);
                if (rxTriggerMatch.hasMatch())
                    trigger = rxTriggerMatch.captured(2).trimmed();
			}

			Macro newMacro(name, Macro::Script, tag, "", trigger);
			newMacro.document = this;
			localMacros.append(newMacro);
		}
	}
}

/*!
 * Return whether the use of package \a name is declared in this document.
 */
bool LatexDocument::containsPackage(const QString &name)
{
	return containedPackages().contains(name);
}

/*!
 * Return all package names of packages that are declared in this document.
 */
QStringList LatexDocument::containedPackages()
{
	QStringList packages;
    foreach(QString elem, mUsepackageList) {
		int i = elem.indexOf('#');
		if (i >= 0) {
			elem = elem.mid(i + 1);
		}
		packages << elem;
	}
	return packages;
}

/*!
 * Return a list of packages that are available in the document.
 * This includes all packages declared in all project files.
 */
QSet<QString> LatexDocument::usedPackages(bool onlyInChildDocs)
{
	QSet<QString> packages;
    foreach (LatexDocument *doc, getListOfDocs(nullptr,onlyInChildDocs)) {
        packages.unite(convertStringListtoSet(doc->containedPackages()));
	}
	return packages;
}
/*!
 * \brief LatexDocuments::getRootDocumentForDoc
 * \param doc
 * \param breakAtSubfileRoot check if one of the parent documents is a subfiles root and use that instead of the actual root document
 * \return found "root" document
 */
LatexDocument *LatexDocuments::getRootDocumentForDoc(LatexDocument *doc,bool breakAtSubfileRoot) const   // doc==0 means current document
{
	if (masterDocument)
		return masterDocument;
	LatexDocument *current = currentDocument;
	if (doc)
		current = doc;
	if (!current)
		return current;
    return const_cast<LatexDocument *>(current->getRootDocument(nullptr,breakAtSubfileRoot));
}

QString LatexDocument::getAbsoluteFilePath(const QString &relName, const QString &extension, const QStringList &additionalSearchPaths) const
{
	QStringList searchPaths;
    const LatexDocument *rootDoc = getRootDocument(nullptr,true);
	QString compileFileName = rootDoc->getFileName();
	if (compileFileName.isEmpty()) compileFileName = rootDoc->getTemporaryFileName();
	QString fallbackPath;
	if (!compileFileName.isEmpty()) {
		fallbackPath = QFileInfo(compileFileName).absolutePath(); //when the file does not exist, resolve it relative to document (e.g. to create it there)
		searchPaths << fallbackPath;
	}
	searchPaths << additionalSearchPaths;
	return findAbsoluteFilePath(relName, extension, searchPaths, fallbackPath);
}

void LatexDocuments::lineGrammarChecked(LatexDocument *doc, QDocumentLineHandle *line, int lineNr, const QList<GrammarError> &errors)
{
    int d = documents.indexOf(doc);
	if (d == -1) return;
	if (!documents[d]->getEditorView()) return;
	documents[d]->getEditorView()->lineGrammarChecked(doc, line, lineNr, errors);
}

void LatexDocuments::requestQNFAupdate()
{
	emit updateQNFA();
}

QString LatexDocuments::findPackageByCommand(const QString command)
{
	// go through all cached packages (cwl) and find command in one of them
	QString result;
	foreach (const QString key, cachedPackages.keys()) {
		const LatexPackage pck = cachedPackages.value(key);
		foreach (const QString envs, pck.possibleCommands.keys()) {
			if (pck.possibleCommands.value(envs).contains(command)) {
				result = LatexPackage::keyToCwlFilename(key); //pck.packageName;
				break;
			}
		}
		if (!result.isEmpty())
			break;
	}
	return result;
}


void LatexDocument::updateLtxCommands(bool updateAll,bool updatePackages)
{
    QList<LatexDocument *>listOfDocs = getListOfDocs();
    if(updatePackages){
        *lp=LatexParser::getInstance(); // append commands set in config
        foreach (const LatexDocument *elem, listOfDocs) {
            lp->append(elem->ltxCommands);
        }
    }else{
        lp->possibleCommands["user"].clear();
        foreach (const LatexDocument *elem, listOfDocs) {
            lp->possibleCommands["user"].unite(elem->ltxCommands.possibleCommands["user"]);
            QStringList keys=elem->ltxCommands.possibleCommands.keys();
            for(const auto &key : keys){
                if(!key.startsWith("%")) continue; // unite possible user commands (special def like %color)
                lp->possibleCommands[key].unite(elem->ltxCommands.possibleCommands[key]);
            }
        }
    }

	if (updateAll) {
		foreach (LatexDocument *elem, listOfDocs) {
            elem->setLtxCommands(lp);
            elem->reCheckSyntax();
		}
		// check if other document have this doc as child as well (reused doc...)
		LatexDocuments *docs = parent;
		QList<LatexDocument *>lstOfAllDocs = docs->getDocuments();
		foreach (LatexDocument *elem, lstOfAllDocs) {
			if (listOfDocs.contains(elem))
				continue; // already handled
			if (elem->containsChild(this)) {
				// unhandled parent/child
                QSharedPointer<LatexParser> lp= QSharedPointer<LatexParser>::create();
                *lp=LatexParser::getInstance(); // start with commands set in config
				QList<LatexDocument *>listOfDocs = elem->getListOfDocs();
                foreach (const LatexDocument *elem, listOfDocs) {
                    lp->append(elem->ltxCommands);
				}
				foreach (LatexDocument *elem, listOfDocs) {
					elem->setLtxCommands(lp);
					elem->reCheckSyntax();
				}
			}
		}
	} else {
        synChecker.setLtxCommands(lp);
        reCheckSyntax();
	}

	LatexEditorView *view = getEditorView();
	if (view) {
        view->updateReplacementList(lp, false);
    }
}
/*!
 * \brief add latex commands from new loaded (cached) document to root document
 * Do not recreate the whole command list
 */
void LatexDocument::addLtxCommands()
{
    lp->append(this->ltxCommands);
}

void LatexDocument::setLtxCommands(QSharedPointer<LatexParser> cmds)
{
    synChecker.setLtxCommands(cmds);
	lp = cmds;

	LatexEditorView *view = getEditorView();
	if (view) {
		view->updateReplacementList(cmds, false);
    }
}

void LatexDocument::setSpeller(SpellerUtility *speller)
{
    synChecker.setSpeller(speller);
}

void LatexDocument::setReplacementList(QMap<QString, QString> replacementList)
{
    synChecker.setReplacementList(replacementList);
}

void LatexDocument::updateSettings()
{
    synChecker.setErrFormat(syntaxErrorFormat);
    QMap<QString,int> fmtList;
    QList<QPair<QString,QString> >formats;
    formats<<QPair<QString,QString>("math","numbers")<<QPair<QString,QString>("verbatim","verbatim")<<QPair<QString,QString>("pictureHighlight","picture")
            <<QPair<QString,QString>("#math","math-keyword")<<QPair<QString,QString>("#pictureHighlight","picture-keyword")<<QPair<QString,QString>("&math","math-delimiter")
            <<QPair<QString,QString>("#mathText","math-text")<<QPair<QString,QString>("align-ampersand","align-ampersand")<<QPair<QString,QString>("comment","comment");
    for(const auto &elem : formats){
        fmtList.insert(elem.first,getFormatId(elem.second));
    }
    synChecker.setFormats(fmtList);
    synChecker.setHideNonTextGrammarErrors(m_hideNonTextGrammarErrors);
    synChecker.setNonTextGrammarFormats(m_grammarFormats);
}

void LatexDocument::checkNextLine(QDocumentLineHandle *dlh, bool clearOverlay, int ticket, int hint)
{
    Q_ASSERT_X(dlh != nullptr, "checkNextLine", "empty dlh used in checkNextLine");
	if (dlh->getRef() > 1 && dlh->getCurrentTicket() == ticket) {
		StackEnvironment env;
		QVariant envVar = dlh->getCookieLocked(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
		if (envVar.isValid())
			env = envVar.value<StackEnvironment>();
        int index = indexOf(dlh,hint);
		if (index == -1) return; //deleted
		REQUIRE(dlh->document() == this);
		if (index + 1 >= lines()) {
			//remove old errror marker
			if (unclosedEnv.id != -1) {
				unclosedEnv.id = -1;
				int unclosedEnvIndex = indexOf(unclosedEnv.dlh);
				if (unclosedEnvIndex >= 0 && unclosedEnv.dlh->getCookieLocked(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE).isValid()) {
					StackEnvironment env;
					Environment newEnv;
					newEnv.name = "normal";
					newEnv.id = 1;
					env.push(newEnv);
					TokenStack remainder;
					if (unclosedEnvIndex >= 1) {
						QDocumentLineHandle *prev = line(unclosedEnvIndex - 1).handle();
						QVariant result = prev->getCookieLocked(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
						if (result.isValid())
							env = result.value<StackEnvironment>();
						remainder = prev->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
                    }
                    synChecker.putLine(unclosedEnv.dlh, env, remainder, true, unclosedEnvIndex);
				}
			}
			if (env.size() > 1) {
				//at least one env has not been closed
				Environment environment = env.top();
                unclosedEnv = env.top();
                synChecker.markUnclosedEnv(environment);
			}
			return;
		}
		TokenStack remainder = dlh->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
        synChecker.putLine(line(index + 1).handle(), env, remainder, clearOverlay,index+1);
	}
    dlh->deref();
}

bool LatexDocument::languageIsLatexLike() const
{
    QLanguageDefinition *ld = languageDefinition();
    if (!ld){
        if(fileName.endsWith(".tex")) return true; // workaround ...
        return false;
    }
	return LATEX_LIKE_LANGUAGES.contains(ld->language());
}

/*
 * \brief Forces syntax recheck of a group of lines
 * \param[in] lineStart Starting line number to be checked
 * \param[in] lineNum Total number of lines to be checked. If -1, then check all lines to the end of the document.
 */
void LatexDocument::reCheckSyntax(int lineStart, int lineNum)
{
    if(isIncompleteInMemory()) return; // no syntax check on cached documents

	// Basic sanity checks
	Q_ASSERT(lineStart >= 0);
	Q_ASSERT((lineNum == -1) || (lineNum > 0));

	// If the document does not support syntax checking just return silently
    if (!languageIsLatexLike()) {
		return;
	}

	int lineTotal = lineCount();
	int lineEnd;
	if (lineNum == -1) {
		lineEnd = lineTotal;
        // all lines are checked from start, clear queue
        synChecker.clearQueue();
	} else {
		if ((lineEnd = lineStart + lineNum) > lineTotal) {
			lineEnd = lineTotal;
		}
	}
	// Fast return if zero lines will be checked
	if (lineStart == lineEnd) {
		return;
	}
	// Delete the environment cookies for the specified lines to force their re-check
	for (int i = lineStart; i < lineEnd; ++i) {
		// We rely on the fact that QDocumentLine::removeCookie() holds a write lock of the corresponding
		// line handle while removing the cookie. Lack of write locking causes crashes due to simultaneous
		// access from the syntax checker thread.
		line(i).removeCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
    }

	// Enqueue the first line for syntax checking. The remaining lines will be enqueued automatically
	// through the checkNextLine signal because we deleted their STACK_ENVIRONMENT_COOKIE cookies.
	StackEnvironment prevEnv;
	getEnv(lineStart, prevEnv);
	TokenStack prevTokens;
	if (lineStart) {
		prevTokens = line(lineStart-1).getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack>();
    }
    synChecker.putLine(line(lineStart).handle(), prevEnv, prevTokens, true, lineStart);
}

QString LatexDocument::getErrorAt(QDocumentLineHandle *dlh, int pos, StackEnvironment previous, TokenStack stack)
{
    return synChecker.getErrorAt(dlh, pos, previous, stack);
}

int LatexDocument::syntaxErrorFormat;

void LatexDocument::getEnv(int lineNumber, StackEnvironment &env) const
{
	Environment newEnv;
	newEnv.name = "normal";
	newEnv.id = 1;
	env.push(newEnv);
	if (lineNumber > 0) {
		QDocumentLine prev = this->line(lineNumber - 1);
		REQUIRE(prev.isValid());
		QVariant result = prev.getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
		if (result.isValid())
			env = result.value<StackEnvironment>();
	}
}

QString LatexDocument::getLastEnvName(int lineNumber)
{
	StackEnvironment env;
	getEnv(lineNumber, env);
	if (env.isEmpty())
        return "";
    return env.top().name;
}

/*!
 * \brief check if env is closed in document
 * Take last line's StackEnv and check if given env is not present (i.e. closed somewhere earlier)
 * \param env
 * \return true if env was closed
 */
bool LatexDocument::isEnvClosed(const Environment &env)
{
    LatexDocument *doc = edView->document;

    int lineCount = doc->lineCount();
    if (lineCount < 1)
        return false; // general error

    StackEnvironment stackEnv_at_lastLine;
    QDocumentLineHandle *dlh = doc->line(lineCount - 1).handle();
    QVariant envVar = dlh->getCookieLocked(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
    if (envVar.isValid())
        stackEnv_at_lastLine = envVar.value<StackEnvironment>();
    else
        return true; // no env, all closed

    for(int i=0;i<stackEnv_at_lastLine.count();++i) {
        const Environment &e = stackEnv_at_lastLine.at(i);
        if (e.name==env.name && e.dlh==env.dlh && e.id==env.id && e.origName==env.origName && e.level==env.level) { //excessCol may change but name,id and dlh should be the same
            // found the environment, so it is not closed
            return false;
        }
    }
    return true;
}

void LatexDocument::enableSyntaxCheck(bool enable)
{
    syntaxChecking = enable;
    synChecker.enableSyntaxCheck(enable);
}

bool LatexDocument::isSubfileRoot(){
    return m_isSubfileRoot;
}
/*!
 * \brief save internal data for caching
 * Data contains labels,user commands and children documents
 */
bool LatexDocument::saveCachingData(const QString &folder)
{
    auto *conf=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    if(!conf || !conf->cacheDocuments ) return false;

    if(m_cachedDataOnly) return true; // don't overwrite with exact same data
    // create folder if needed
    QDir dir(folder);
    if(!dir.exists()){
        dir.mkpath(folder);
    }

    QFileInfo fi=getFileInfo();
    QFile file(folder+"/"+fi.baseName()+".json");

    // remove cache if dealing with modified, unsaved changes as saved text differs
    if(!isClean()){
        if(file.exists()){
            file.remove();
        }
        return false;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QJsonArray ja_labels;
    for(const auto &elem:mLabelItem){
        ja_labels.append(elem.name);
    }

    QJsonArray ja_refs;
    for(const auto &elem:mRefItem){
        ja_refs.append(elem.name);
    }

    QJsonArray ja_docs;
    for(const auto &elem:includedFiles()){
        ja_docs.append(elem);
    }

    QJsonArray ja_userCommands;
    for(const auto &elem:mUserCommandList.values()){
        if(elem.name.isEmpty() && elem.snippet.word.isEmpty()) continue; // skip empty values
        QJsonArray ja_CommandPair;
        ja_CommandPair.append(elem.name);
        QString word=elem.snippet.word;
        if(word.startsWith("\\begin")){
            int i=word.indexOf("\\end");
            if(i>0){
                word=word.left(i);
            }
        }
        ja_CommandPair.append(word);
        ja_userCommands.append(ja_CommandPair);
    }

    QJsonArray ja_packages;
    for(const QString &elem:mUsepackageList.values()){
        if(elem.endsWith("#subfiles") && elem != "#subfiles") continue; // filter class [file]{subfiles} as it leads to unnecessarily loading packages in cached files
        ja_packages.append(elem);
    }
    QJsonArray ja_bibitems;
    for(const auto &elem:mBibItem.values()){
        ja_bibitems.append(elem.name);
    }
    QJsonArray ja_bibtexfiles;
    for(const auto &elem:mMentionedBibTeXFiles.values()){
        ja_bibtexfiles.append(elem.absolute+"#"+elem.relative);
    }

    // store toc structure
    QStringList toc=unrollStructure();
    QJsonArray ja_toc;
    for(const QString &elem:toc){
        ja_toc.append(elem);
    }

    QJsonObject dd;
    dd["filename"]=getFileName();
    dd["labels"]=ja_labels;
    dd["refs"]=ja_refs;
    dd["childdocs"]=ja_docs;
    dd["usercommands"]=ja_userCommands;
    dd["packages"]=ja_packages;
    dd["bibitems"]=ja_bibitems;
    dd["bibtexfiles"]=ja_bibtexfiles;
    dd["toc"]=ja_toc;
    dd["modified"]=fi.lastModified().toString();

    QJsonDocument jsonDoc(dd);
    file.write(jsonDoc.toJson());

    return true;
}
/*!
 * \brief read cached data for document
 * Data contains labels,user commands, structure and children documents
 * The document is not loaded but the other data structure are generated as if it was normally loaded.
 * To be used for hidden documents
 * \param folder
 * \return successful load
 */
bool LatexDocument::restoreCachedData(const QString &folder,const QString fileName)
{
    auto *conf=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    if(!conf || !conf->cacheDocuments ) return false;

    QFileInfo fi(fileName);
    QFile file(folder+"/"+fi.baseName()+".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray data = file.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error!=QJsonParseError::NoError){
        // parser could not read input
        return false;
    }
    QJsonObject dd=jsonDoc.object();
    // check modified data
    QString modifiedDate=dd["modified"].toString();
    auto delta=fi.lastModified().toSecsSinceEpoch()-QDateTime::fromString(modifiedDate).toSecsSinceEpoch();
    if(delta>1){ // add 1 second tolerance when determine if obsolete
        // cache is obsolete
        qDebug()<<"cached data obsolete: "<<fileName<<fi.lastModified().toString()<<modifiedDate<<fi.absoluteFilePath();
        return false;
    }


    QString fn=dd["filename"].toString();
    if(fn!=fileName){
        // filename does not match exactly
        return false;
    }
    setFileName(fileName);
    QJsonArray ja=dd.value("labels").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString lbl=ja[i].toString();
        ReferencePair rp;
        rp.name=lbl;
        mLabelItem.insert(nullptr,rp);
    }
    ja=dd.value("refs").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString lbl=ja[i].toString();
        ReferencePair rp;
        rp.name=lbl;
        mRefItem.insert(nullptr,rp);
    }
    ja=dd.value("bibitems").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString lbl=ja[i].toString();
        ReferencePair rp;
        rp.name=lbl;
        mBibItem.insert(nullptr,rp);
    }
    ja=dd.value("bibtexfiles").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString lbl=ja[i].toString();
        QStringList lbls=lbl.split("#");
        if(lbls.size()==2){
            FileNamePair fnp(lbls[1],lbls[0]);
            mMentionedBibTeXFiles.insert(nullptr,fnp);
        }
    }

    ja=dd.value("childdocs").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString fn=ja[i].toString();
        mIncludedFilesList.insert(nullptr,fn);
    }
    if(!mIncludedFilesList.isEmpty()){
        QStringList files=mIncludedFilesList.values();
        parent->addDocsToLoad(files,this);
    }
    ja=dd.value("usercommands").toArray();
    const bool addedUserCommands=ja.size()>0;
    for (int i = 0; i < ja.size(); ++i) {
        const auto cmd=ja[i].toArray();
        UserCommandPair up(cmd[0].toString(),cmd[1].toString());
        mUserCommandList.insert(nullptr,up);
        if(!cmd[0].toString().isEmpty()){
            // only named commands are added for syntax checking
            if(cmd[0].toString().startsWith("\\")){
                ltxCommands.possibleCommands["user"].insert(cmd[0].toString());
            }else{
                ltxCommands.possibleCommands["user"].insert(cmd[1].toString());
            }
        }
    }
    ja=dd.value("packages").toArray();
    const bool addedPackages=ja.size()>0;
    for (int i = 0; i < ja.size(); ++i) {
        QString package=ja[i].toString();
        mUsepackageList.insert(nullptr,package);
    }
    ja=dd.value("toc").toArray();
    for (int i = 0; i < ja.size(); ++i) {
        QString section=ja[i].toString();
        QStringList l_section=section.split("#");
        if(l_section.size()<2 || l_section.size()>3){
            continue; // structure does not fit, needs to be number#text
        }
        bool ok;
        int pos=l_section[0].toInt(&ok);
        if(!ok) continue; // structure does not fit, needs to be number#text
        StructureEntry *se;
        if(pos>=0){
            se=new StructureEntry(this,StructureEntry::SE_SECTION);
        }else{
            se=new StructureEntry(this,StructureEntry::SE_INCLUDE);
            pos=1;
        }
        se->setLine(0);
        if(l_section.size()==3){
            int ln=l_section[2].toInt(&ok);
            if(ok){
                se->setLine(nullptr,ln);
            }
        }
        se->title=l_section[1];
        se->level=pos;
        docStructure.push_back(se);
    }

    updateCompletionFiles(addedPackages,addedUserCommands);

    m_cachedDataOnly=true;
    return true;
}
/*!
 * \brief check if it was restored from cached data
 * Needs to load from the beginning otherwise
 * \return
 */
bool LatexDocument::isIncompleteInMemory()
{
    return m_cachedDataOnly;
}
/*!
 * \brief start syntax checker once it becomes visible
 */
void LatexDocument::startSyntaxChecker()
{
    if(!synChecker.isRunning()){
        synChecker.start();
    }
}
