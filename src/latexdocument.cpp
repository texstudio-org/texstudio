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

// languages for LaTeX syntax checking (exact name from qnfa file)
const QSet<QString> LatexDocument::LATEX_LIKE_LANGUAGES = QSet<QString>() << "(La)TeX" << "Pweave" << "Sweave" << "TeX dtx file";
/*! \brief constructor
 * sets up structure for structure view
 * starts the syntax checker in a separate thread
 */
LatexDocument::LatexDocument(QObject *parent): QDocument(parent), remeberAutoReload(false), mayHaveDiffMarkers(false), edView(nullptr), mAppendixLine(nullptr), mBeyondEnd(nullptr)
{
	baseStructure = new StructureEntry(this, StructureEntry::SE_DOCUMENT_ROOT);
	magicCommentList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	labelList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	todoList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	bibTeXList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	blockList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);

	magicCommentList->title = tr("MAGIC_COMMENTS");
	labelList->title = tr("LABELS");
	todoList->title = tr("TODO");
	bibTeXList->title = tr("BIBLIOGRAPHY");
	blockList->title = tr("BLOCKS");
	mLabelItem.clear();
	mBibItem.clear();
	mUserCommandList.clear();
	mMentionedBibTeXFiles.clear();
	masterDocument = nullptr;
	this->parent = nullptr;

	unclosedEnv.id = -1;
	syntaxChecking = true;

	lp = LatexParser::getInstance();

	SynChecker.setLtxCommands(LatexParser::getInstance());
    updateSettings();
	SynChecker.start();

    connect(&SynChecker, SIGNAL(checkNextLine(QDocumentLineHandle*,bool,int,int)), SLOT(checkNextLine(QDocumentLineHandle*,bool,int,int)), Qt::QueuedConnection);
}

LatexDocument::~LatexDocument()
{
	SynChecker.stop();
	SynChecker.wait();

	foreach (QDocumentLineHandle *dlh, mLineSnapshot) {
		dlh->deref();
	}
	mLineSnapshot.clear();

	if (!magicCommentList->parent) delete magicCommentList;
	if (!labelList->parent) delete labelList;
	if (!todoList->parent) delete todoList;
	if (!bibTeXList->parent) delete bibTeXList;
	if (!blockList->parent) delete blockList;

	delete baseStructure;
}

void LatexDocument::setFileName(const QString &fileName)
{
	//clear all references to old editor
    /*if (this->edView) {
		StructureEntryIterator iter(baseStructure);
		while (iter.hasNext()) iter.next()->setLine(nullptr);
    }*/

	this->setFileNameInternal(fileName);
	this->edView = nullptr;
}

void LatexDocument::setEditorView(LatexEditorView *edView)
{
	this->setFileNameInternal(edView->editor->fileName(), edView->editor->fileInfo());
	this->edView = edView;
	if (baseStructure) {
		baseStructure->title = fileName;
	}
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
	StructureEntry *parent;
	int index;
	do {
		parent = section->parent;
		if (parent) {
			index = section->getRealParentRow();
			section = parent;
		} else index = -1;
	} while ((index >= 0) && (index >= parent->children.count() - 1) && (parent->type == StructureEntry::SE_SECTION));

	int endingLine = -1;
	if (index >= 0 && index < parent->children.count() - 1) {
		endingLine = parent->children.at(index + 1)->getRealLineNumber();
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

class LatexStructureMerger{
public:
	LatexStructureMerger (LatexDocument* document, int maxDepth):
		document(document), parent_level(maxDepth)
	{
	}

protected:
	LatexDocument* document;
	QVector<StructureEntry *> parent_level;
	void updateParentVector(StructureEntry *se);
	void moveToAppropiatePositionWithSignal(StructureEntry *se);
};


class LatexStructureMergerMerge: public LatexStructureMerger{
public:
        LatexStructureMergerMerge (LatexDocument* doc, int maxDepth, int linenr, int count):
	        LatexStructureMerger(doc, maxDepth), linenr(linenr), count(count), flatStructure(nullptr)
	{
	}
	void operator ()(QList<StructureEntry *> &flatStructure){
		this->flatStructure = &flatStructure;
		parent_level.fill(document->baseStructure);
		mergeStructure(document->baseStructure);
	}
private:
	const int linenr;
	const int count;
	QList<StructureEntry *> *flatStructure;
	void mergeStructure(StructureEntry *se);
	void mergeChildren(StructureEntry *se, int start = 0);
};



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


	emit structureUpdated(this, nullptr);

	const int CATCOUNT = 5;
	StructureEntry *categories[CATCOUNT] = {magicCommentList, labelList, todoList, bibTeXList, blockList};
	for (int i = 0; i < CATCOUNT; i++)
		if (categories[i]->parent == baseStructure) {
            removeElement(categories[i]);
			foreach (StructureEntry *se, categories[i]->children)
				delete se;
			categories[i]->children.clear();
		}

	for (int i = 0; i < baseStructure->children.length(); i++) {
		StructureEntry *temp = baseStructure->children[i];
        removeElement(temp);
		delete temp;
	}

	baseStructure->title = fileName;
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
	if (!baseStructure) return;
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
                int i = word.indexOf("{");
                if (i >= 0) word = word.left(i);
                ltxCommands.possibleCommands["user"].remove(word);
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

        QList<StructureEntry *> categories = QList<StructureEntry *>() << magicCommentList << labelList << todoList << blockList << bibTeXList;
        foreach (StructureEntry *sec, categories) {
            int l = 0;
            QMutableListIterator<StructureEntry *> iter(sec->children);
            while (iter.hasNext()) {
                StructureEntry *se = iter.next();
                if (dlh == se->getLineHandle()) {
                    iter.remove();
                    delete se;
                } else l++;
            }
        }
        if(i+1<count){
            // not at last element yet
            dlh=line(linenr+1).handle();
        }
    }

    // cut from structure
    StructureEntry *seSplit=splitStructure(baseStructure,hint+count);
    StructureEntry *seRemove=splitStructure(baseStructure,hint);
    delete seRemove;
    appendStructure(baseStructure,seSplit);

	// rehighlight current cursor position
	StructureEntry *newSection = nullptr;
	if (edView) {
		int i = edView->editor->cursor().lineNumber();
		if (i >= 0) {
			newSection = findSectionForLine(i);
		}
	}

	emit structureUpdated(this, newSection);

	if (bibTeXFilesNeedsUpdate)
		emit updateBibTeXFiles();

	if (completerNeedsUpdate || bibTeXFilesNeedsUpdate)
		emit updateCompleter();

    if (!removedUsepackages.isEmpty() || updateSyntaxCheck) {
		updateCompletionFiles(updateSyntaxCheck);
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
 * \brief parse lines to update syntactical and structure information
 *
 * updates structure informationen from the changed lines only
 * parses the lines to gather syntactical information on the latex content
 * e.g. find labels/references, new command definitions etc.
 * the syntax parsing has been largely changed to the token system which is tranlated here for faster information extraction \see Tokens
 * \param linenr first line to check
 * \param count number of lines to check (-1: all)
 * \param recheck method has been called a second time to handle profound syntax changes from first call (like newly loaded packages). This allows to avoid some costly operations on the second call.
 * \return true means a second run is suggested as packages are loadeed which change the outcome
 *         e.g. definition of specialDef command, but packages are load at the end of this method.
 */
bool LatexDocument::patchStructure(int linenr, int count, bool recheck)
{
	/* true means a second run is suggested as packages are loadeed which change the outcome
	 * e.g. definition of specialDef command, but packages are load at the end of this method.
	 */

	if (!parent->patchEnabled())
		return false;

	if (!baseStructure) return false;

    //QElapsedTimer tm ;
    //tm.start();

	static QRegExp rxMagicTexComment("^%\\ ?!T[eE]X");
	static QRegExp rxMagicBibComment("^%\\ ?!BIB");

	bool reRunSuggested = false;
	bool recheckLabels = true;
	if (count < 0) {
		count = lineCount();
		recheckLabels = false;
	}

	bool completerNeedsUpdate = false;
	bool bibTeXFilesNeedsUpdate = false;
	bool bibItemsChanged = false;

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
	bool updateSyntaxCheck = false;
	QList<StructureEntry *> flatStructure;

	// usepackage list
	QStringList removedUsepackages;
	QStringList addedUsepackages;
	QStringList removedUserCommands, addedUserCommands;
	QStringList lstFilesToLoad;
	//first pass: lex
    TokenStack oldRemainder;
    CommandStack oldCommandStack;
	if (!recheck) {
		QList<QDocumentLineHandle *> l_dlh;
//#pragma omp parallel for shared(l_dlh)
		for (int i = linenr; i < linenr + count; i++) {
			l_dlh << line(i).handle();
            //Parsing::simpleLexLatexLine(line(i).handle());
		}
        QtConcurrent::blockingMap(l_dlh,Parsing::simpleLexLatexLine);
	}
    int stoppedAtLine=-1;
    TokenList l_tkFilter;
    QDocumentLineHandle *lastHandle = line(linenr - 1).handle();
    if (lastHandle) {
        oldRemainder = lastHandle->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
        oldCommandStack = lastHandle->getCookieLocked(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
    }
    for (int i = linenr; i < lineCount() && i < linenr + count; ++i) {
        if (line(i).text() == "\\begin{document}"){
            if(linenr==0 && count==lineCount() && !recheck) {
                stoppedAtLine=i;
                break; // do recheck quickly as usepackages probably need to be loaded
            }
        }
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
        if (remainderChanged && i + 1 == linenr + count && i + 1 < lineCount()) { // remainder changed in last line which is to be checked
            count++; // check also next line ...
        }
    }
	if (linenr >= lineNrStart) {
		newCount = linenr + count - lineNrStart;
	}
	// Note: We cannot re-use the structure elements in the updated area because if there are multiple same-type elements on the same line
	// and the user has changed their order, re-using these elements would not update their order and this would break updates of any
	// QPersistentModelIndex'es that point to these elements in the structure tree view. That is why we remove all the structure elements
	// within the updated area and then just add anew any structure elements that we find in the updated area.

	QList<StructureEntry *> removedMagicComments;
	int posMagicComment = findStructureParentPos(magicCommentList->children, removedMagicComments, lineNrStart, newCount);

	QList<StructureEntry *> removedLabels;
	int posLabel = findStructureParentPos(labelList->children, removedLabels, lineNrStart, newCount);

	QList<StructureEntry *> removedTodo;
	int posTodo = findStructureParentPos(todoList->children, removedTodo, lineNrStart, newCount);

	QList<StructureEntry *> removedBlock;
	int posBlock = findStructureParentPos(blockList->children, removedBlock, lineNrStart, newCount);

	QList<StructureEntry *> removedBibTeX;
	int posBibTeX = findStructureParentPos(bibTeXList->children, removedBibTeX, lineNrStart, newCount);

	bool isLatexLike = languageIsLatexLike();
	//updateSubsequentRemaindersLatex(this,linenr,count,lp);
	// force command from all line of which the actual line maybe subsequent lines (multiline commands)
	for (int i = lineNrStart; i < linenr + count; i++) {
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
			    ltxCommands.possibleCommands["user"].remove(elem);
			}
			if(cmd.snippet.type==CodeSnippet::userConstruct)
				continue;
			removedUserCommands << elem;
			//updateSyntaxCheck=true;
		}
		if (mLabelItem.contains(dlh)) {
			QList<ReferencePair> labels = mLabelItem.values(dlh);
			completerNeedsUpdate = true;
			mLabelItem.remove(dlh);
			foreach (const ReferencePair &rp, labels)
				updateRefsLabels(rp.name);
		}
		mRefItem.remove(dlh);
		QStringList removedIncludes = mIncludedFilesList.values(dlh);
        removedIncludes.append(mImportedFilesList.values(dlh));
		mIncludedFilesList.remove(dlh);
        mImportedFilesList.remove(dlh);

		if (mUserCommandList.remove(dlh) > 0) completerNeedsUpdate = true;
		if (mBibItem.remove(dlh))
			bibTeXFilesNeedsUpdate = true;

		removedUsepackages << mUsepackageList.values(dlh);
		if (mUsepackageList.remove(dlh) > 0) completerNeedsUpdate = true;

		//remove old bibs files from hash, but keeps a temporary copy
		QStringList oldBibs;
		while (mMentionedBibTeXFiles.contains(dlh)) {
			QMultiHash<QDocumentLineHandle *, FileNamePair>::iterator it = mMentionedBibTeXFiles.find(dlh);
			Q_ASSERT(it.key() == dlh);
			Q_ASSERT(it != mMentionedBibTeXFiles.end());
			if (it == mMentionedBibTeXFiles.end()) break;
			oldBibs.append(it.value().relative);
			mMentionedBibTeXFiles.erase(it);
		}

        // handle special comments (TODO, MAGIC comments)
        // comment detection moved to lexer as formats are not yet generated here (e.g. on first load)
        QPair<int,int> commentStart = dlh->getCookieLocked(QDocumentLine::LEXER_COMMENTSTART_COOKIE).value<QPair<int,int> >();
        int col = commentStart.first;
		if (col >= 0) {
            // all
            //// TODO marker
            QString text = curLine.mid(col);
			QString regularExpression=ConfigManagerInterface::getInstance()->getOption("Editor/todo comment regExp").toString();
			QRegExp rx(regularExpression);
			if (rx.indexIn(text)==0) {  // other todos like \todo are handled by the tokenizer below.
				StructureEntry *newTodo = new StructureEntry(this, StructureEntry::SE_TODO);
				newTodo->title = text.mid(1).trimmed();
				newTodo->setLine(line(i).handle(), i);
                insertElement(todoList, posTodo++, newTodo);
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
                            addMagicComment(curLine.mid(start, end - start), i, posMagicComment++);
                        }
                    } else {
                        end = curLine.indexOf(' ', end + 1);
                        if (end >= 0) {
                            addMagicComment(curLine.mid(start, end - start), i, posMagicComment++);
                        } else {
                            addMagicComment(curLine.mid(start), i, posMagicComment++);
                        }
                    }
                }
                commentStart.second=Token::magicComment;
                dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
            }
            //// magic comment
            if (rxMagicTexComment.indexIn(text) == 0) {
                addMagicComment(text.mid(rxMagicTexComment.matchedLength()).trimmed(), i, posMagicComment++);
                commentStart.second=Token::magicComment;
                dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
            } else if (rxMagicBibComment.indexIn(text) == 0) {
                // workaround to also support "% !BIB program = biber" syntax used by TeXShop and TeXWorks
                text = text.mid(rxMagicBibComment.matchedLength()).trimmed();
                QString name;
                QString val;
                splitMagicComment(text, name, val);
                if ((name == "TS-program" || name == "program") && (val == "biber" || val == "bibtex" || val == "bibtex8")) {
                    addMagicComment(QString("TXS-program:bibliography = txs:///%1").arg(val), i, posMagicComment++);
                    commentStart.second=Token::magicComment;
                    dlh->setCookie(QDocumentLine::LEXER_COMMENTSTART_COOKIE, QVariant::fromValue<QPair<int,int> >(commentStart));
                }
            }
		}

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
                if(!addedUsepackages.isEmpty()){
                    break; // do recheck quickly as usepackages probably need to be loaded
                }else{
                    // oops, complete tokenlist needed !
                    // redo on time
                    for (int i = stoppedAtLine; i < lineCount(); i++) {
                        Parsing::latexDetermineContexts2(line(i).handle(), oldRemainder, oldCommandStack, lp);
                    }
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

        TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();

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
				mRefItem.insert(line(i).handle(), elem);
			}

			//// label ////
			if (tk.type == Token::label && tk.length > 0) {
				ReferencePair elem;
				elem.name = tk.getText();
				elem.start = tk.start;
				mLabelItem.insert(line(i).handle(), elem);
				completerNeedsUpdate = true;
				StructureEntry *newLabel = new StructureEntry(this, StructureEntry::SE_LABEL);
				newLabel->title = elem.name;
				newLabel->setLine(line(i).handle(), i);
                insertElement(labelList, posLabel++, newLabel);
			}
			//// newtheorem ////
			if (tk.type == Token::newTheorem && tk.length > 0) {
				completerNeedsUpdate = true;
				QStringList lst;
				QString firstArg = tk.getText();
				lst << "\\begin{" + firstArg + "}" << "\\end{" + firstArg + "}";
				foreach (const QString &elem, lst) {
					mUserCommandList.insert(line(i).handle(), UserCommandPair(firstArg, elem));
					ltxCommands.possibleCommands["user"].insert(elem);
					if (!removedUserCommands.removeAll(elem)) {
						addedUserCommands << elem;
					}
				}
				continue;
			}
			/// bibitem ///
			if (tk.type == Token::newBibItem && tk.length > 0) {
				ReferencePair elem;
				elem.name = tk.getText();
				elem.start = tk.start;
				mBibItem.insert(line(i).handle(), elem);
				bibItemsChanged = true;
				continue;
			}
			/// todo ///
			if (tk.subtype == Token::todo && (tk.type == Token::braces || tk.type == Token::openBrace)) {
				StructureEntry *newTodo = new StructureEntry(this, StructureEntry::SE_TODO);
				newTodo->title = tk.getInnerText();
				newTodo->setLine(line(i).handle(), i);
                insertElement(todoList, posTodo++, newTodo);
			}
            // specialArg definition
            if(tk.type == Token::defSpecialArg){
                QString cmd=Parsing::getCommandFromToken(tk);
                completerNeedsUpdate = true;
                QString definition = ltxCommands.specialDefCommands.value(cmd);
                QString elem = tk.getText();
                mUserCommandList.insert(line(i).handle(), UserCommandPair(QString(), definition + "%" + elem));
                if (!removedUserCommands.removeAll(elem)) {
                    addedUserCommands << elem;
                }
            }

			// work on general commands
			if (tk.type != Token::command && tk.type != Token::commandUnknown)
				continue; // not a command
			Token tkCmd;
			TokenList args;
			QString cmd;
			int cmdStart = Parsing::findCommandWithArgsFromTL(tl, tkCmd, args, j, parent->showCommentedElementsInStructure);
			if (cmdStart < 0) break;
			cmdStart=tkCmd.start; // from here, cmdStart is line column position of command
			cmd = curLine.mid(tkCmd.start, tkCmd.length);

            QString firstArg = Parsing::getArg(args, dlh, 0, ArgumentList::Mandatory,true,i);

			//// newcommand ////
			if (lp.possibleCommands["%definition"].contains(cmd) || ltxCommands.possibleCommands["%definition"].contains(cmd)) {
				completerNeedsUpdate = true;
				//Tokens cmdName;
				QString cmdName = Parsing::getArg(args, Token::def);
				cmdName.replace("@","@@"); // special treatment for commandnames containing @
				bool isDefWidth = true;
				if (cmdName.isEmpty())
					cmdName = Parsing::getArg(args, Token::defWidth);
				else
					isDefWidth = false;

                ltxCommands.possibleCommands["user"].insert(cmdName);

                if (!removedUserCommands.removeAll(cmdName)) {
                    addedUserCommands << cmdName;
                }
                QString cmdNameWithoutArgs = cmdName;
                QString cmdNameWithoutOptional = cmdName;
                bool def=false;

                QString xarg=Parsing::getArg(args, Token::defXparseArg);
                if(!xarg.isEmpty()){
                    // xparse style defintion
                    QString arguments=interpretXArgs(xarg);
                    cmdName=cmdName+arguments;
                }else{
                    int optionCount = Parsing::getArg(args, Token::defArgNumber).toInt(); // results in 0 if there is no optional argument or conversion fails
                    if (optionCount > 9 || optionCount < 0) optionCount = 0; // limit number of options
                    def = !Parsing::getArg(args, Token::optionalArgDefinition).isEmpty();


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
                if (isDefWidth)
                    cs.type = CodeSnippet::length;
                mUserCommandList.insert(line(i).handle(), UserCommandPair(cmdNameWithoutArgs, cs));
                if(def){ // optional argument, add version without that argument as well
                    CodeSnippet cs(cmdNameWithoutOptional);
                    cs.index = qHash(cmdNameWithoutOptional);
                    cs.snippetLength = cmdNameWithoutOptional.length();
                    if (isDefWidth)
                        cs.type = CodeSnippet::length;
                    mUserCommandList.insert(line(i).handle(), UserCommandPair(cmdNameWithoutArgs, cs));
                }

				// remove obsolete Overlays (maybe this can be refined
				//updateSyntaxCheck=true;
				continue;
			}
			// special treatment \def
			if (cmd == "\\def" || cmd == "\\gdef" || cmd == "\\edef" || cmd == "\\xdef") {
				QString remainder = curLine.mid(cmdStart + cmd.length());
				completerNeedsUpdate = true;
				QRegExp rx("(\\\\\\w+)\\s*([^{%]*)");
				if (rx.indexIn(remainder) > -1) {
					QString name = rx.cap(1);
					QString nameWithoutArgs = name;
					QString optionStr = rx.cap(2);
					//qDebug()<< name << ":"<< optionStr;
					ltxCommands.possibleCommands["user"].insert(name);
					if (!removedUserCommands.removeAll(name)) addedUserCommands << name;
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
					mUserCommandList.insert(line(i).handle(), UserCommandPair(nameWithoutArgs, name));
					// remove obsolete Overlays (maybe this can be refined
					//updateSyntaxCheck=true;
				}
				continue;
			}
			if (cmd == "\\newcolumntype") {
				if(firstArg.length()==1){ // only single letter definitions are allowed/handled
					QString secondArg = Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory);
					ltxCommands.possibleCommands["%columntypes"].insert(firstArg+secondArg);
					if (!removedUserCommands.removeAll(firstArg)) {
						addedUserCommands << firstArg;
					}
					mUserCommandList.insert(line(i).handle(), UserCommandPair(QString(), firstArg));
					continue;
				}
			}

			//// newenvironment ////
			static const QStringList envTokens = QStringList() << "\\newenvironment" << "\\renewenvironment";
			if (envTokens.contains(cmd)) {
				completerNeedsUpdate = true;
				TokenList argsButFirst = args;
				if(argsButFirst.isEmpty())
					continue; // no arguments present
				argsButFirst.removeFirst();
				int optionCount = Parsing::getArg(argsButFirst, dlh, 0, ArgumentList::Optional).toInt(); // results in 0 if there is no optional argument or conversion fails
				if (optionCount > 9 || optionCount < 0) optionCount = 0; // limit number of options
				mUserCommandList.insert(line(i).handle(), UserCommandPair(firstArg, "\\end{" + firstArg + "}"));
				QStringList lst;
				lst << "\\begin{" + firstArg + "}" << "\\end{" + firstArg + "}";
				foreach (const QString &elem, lst) {
					ltxCommands.possibleCommands["user"].insert(elem);
					if (!removedUserCommands.removeAll(elem)) {
						addedUserCommands << elem;
					}
				}
				bool hasDefaultArg = !Parsing::getArg(argsButFirst, dlh, 1, ArgumentList::Optional).isNull();
				int mandatoryOptionCount = hasDefaultArg ? optionCount - 1 : optionCount;
				QString mandatoryArgString;
				for (int j = 0; j < mandatoryOptionCount; j++) {
					if (j == 0) mandatoryArgString.append("{%<1%>}");
					else mandatoryArgString.append(QString("{%<%1%>}").arg(j + 1));
				}
				mUserCommandList.insert(line(i).handle(), UserCommandPair(firstArg, "\\begin{" + firstArg + "}" + mandatoryArgString));
				if (hasDefaultArg) {
					mUserCommandList.insert(line(i).handle(), UserCommandPair(firstArg, "\\begin{" + firstArg + "}" + "[%<opt%>]" + mandatoryArgString));
				}
				continue;
			}
			//// newcounter ////
			if (cmd == "\\newcounter") {
				completerNeedsUpdate = true;
				QStringList lst;
				lst << "\\the" + firstArg ;
				foreach (const QString &elem, lst) {
					mUserCommandList.insert(line(i).handle(), UserCommandPair(elem, elem));
					ltxCommands.possibleCommands["user"].insert(elem);
					if (!removedUserCommands.removeAll(elem)) {
						addedUserCommands << elem;
					}
				}
				continue;
			}
			//// newif ////
			if (cmd == "\\newif") {
				// \newif\ifmycondition also defines \myconditiontrue and \myconditionfalse
				completerNeedsUpdate = true;
				QStringList lst;
				lst << firstArg
					<< "\\" + firstArg.mid(3) + "false"
					<< "\\" + firstArg.mid(3) + "true";
				foreach (const QString &elem, lst) {
					mUserCommandList.insert(line(i).handle(), UserCommandPair(elem, elem));
					ltxCommands.possibleCommands["user"].insert(elem);
					if (!removedUserCommands.removeAll(elem)) {
						addedUserCommands << elem;
					}
				}
				continue;
			}
			/// specialDefinition ///
			/// e.g. definecolor
            /*if (ltxCommands.specialDefCommands.contains(cmd)) {
				if (!args.isEmpty() ) {
					completerNeedsUpdate = true;
					QString definition = ltxCommands.specialDefCommands.value(cmd);
					Token::TokenType type = Token::braces;
					if (definition.startsWith('(')) {
						definition.chop(1);
						definition = definition.mid(1);
						type = Token::bracket;
					}
					if (definition.startsWith('[')) {
						definition.chop(1);
						definition = definition.mid(1);
						type = Token::squareBracket;
					}

					foreach (Token mTk, args) {
						if (mTk.type != type)
							continue;
                        if(mTk.subtype == Token::defSpecialArg){
                            // handled elsewhere
                            break;
                        }
						QString elem = mTk.getText();
						elem = elem.mid(1, elem.length() - 2); // strip braces
						mUserCommandList.insert(line(i).handle(), UserCommandPair(QString(), definition + "%" + elem));
						if (!removedUserCommands.removeAll(elem)) {
							addedUserCommands << elem;
						}
						break;
					}
				}
            }*/

			///usepackage
            if (lp.possibleCommands["%usepackage"].contains(cmd)) {
                if(firstArg.contains("\\")){
                    // argument contains backslash
                    // hence, invalid and to be ignored
                    continue;
                }
                completerNeedsUpdate = true;
                QStringList packagesHelper = firstArg.split(",");

                if (cmd.endsWith("theme")) { // special treatment for \usetheme
                    QString preambel = cmd;
                    preambel.remove(0, 4);
                    preambel.prepend("beamer");
                    packagesHelper.replaceInStrings(QRegularExpression("^"), preambel);
                }
                if (cmd=="\\usetikzlibrary") { // special treatment for \usetikzlibrary
                    QString preambel = "tikzlibrary";
                    packagesHelper.replaceInStrings(QRegularExpression("^"), preambel);
                }
                if (cmd=="\\usepgfplotslibrary") { // special treatment for \usepgfplotslibrary
                    QString preambel = "pgfplotslibrary";
                    packagesHelper.replaceInStrings(QRegularExpression("^"), preambel);
                }
                if (cmd=="\\tcbuselibrary") { // special treatment for \tcbuselibrary
                    QString preambel = "tcolorboxlibrary";
                    packagesHelper.replaceInStrings(QRegularExpression("^"), preambel);
                }
                if (cmd=="\\UseTblrLibrary") { // special treatment for \UseTblrLibrary
                    QString preambel = "tabularraylibrary";
                    packagesHelper.replaceInStrings(QRegularExpression("^"), preambel);
                }

                QString firstOptArg = Parsing::getArg(args, dlh, 0, ArgumentList::Optional);
                if (cmd == "\\documentclass") {
                    //special treatment for documentclass, especially for the class options
                    // at the moment a change here soes not automatically lead to an update of corresponding definitions, here babel
                    mClassOptions = firstOptArg;
                }

                QStringList packages;
				foreach (QString elem, packagesHelper) {
					elem = elem.simplified();
					if (lp.packageAliases.contains(elem))
						packages << lp.packageAliases.values(elem);
					else
						packages << elem;
				}

				foreach (const QString &elem, packages) {
					if (!removedUsepackages.removeAll(firstOptArg + "#" + elem))
						addedUsepackages << firstOptArg + "#" + elem;
                    mUsepackageList.insert(dlh, firstOptArg + "#" + elem); // hand on option of usepackages for conditional cwl load ..., force load if option is changed
				}
				continue;
			}
			//// bibliography ////
			if (lp.possibleCommands["%bibliography"].contains(cmd)) {
				QStringList additionalBibPaths = ConfigManagerInterface::getInstance()->getOption("Files/Bib Paths").toString().split(getPathListSeparator());
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
                QStringList bibs = firstArg.split(',', Qt::SkipEmptyParts);
#else
				QStringList bibs = firstArg.split(',', QString::SkipEmptyParts);
#endif
				//add new bibs and set bibTeXFilesNeedsUpdate if there was any change
				foreach (const QString &elem, bibs) { //latex doesn't seem to allow any spaces in file names
					mMentionedBibTeXFiles.insert(line(i).handle(), FileNamePair(elem, getAbsoluteFilePath(elem, "bib", additionalBibPaths)));
					if (oldBibs.removeAll(elem) == 0)
						bibTeXFilesNeedsUpdate = true;
				}
				//write bib tex in tree
				foreach (const QString &bibFile, bibs) {
					StructureEntry *newFile = new StructureEntry(this, StructureEntry::SE_BIBTEX);
					newFile->title = bibFile;
					newFile->setLine(line(i).handle(), i);
                    insertElement(bibTeXList, posBibTeX++, newFile);
				}
				continue;
			}

			//// beamer blocks ////

			if (cmd == "\\begin" && firstArg == "block") {
				StructureEntry *newBlock = new StructureEntry(this, StructureEntry::SE_BLOCK);
                newBlock->title = Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory,true,i);
				newBlock->setLine(line(i).handle(), i);
                insertElement(blockList, posBlock++, newBlock);
				continue;
			}

			//// include,input,import ////
            if (lp.possibleCommands["%include"].contains(cmd) ) {
                QString fn=Parsing::getArg(args, Token::file);
				StructureEntry *newInclude = new StructureEntry(this, StructureEntry::SE_INCLUDE);
				newInclude->level = parent && !parent->indentIncludesInStructure ? 0 : lp.structureDepth() - 1;
                fn = removeQuote(fn);
                newInclude->title = fn;
                QString name=fn;
                name.replace("\\string~",QDir::homePath());
                QString fname = findFileName(name);
                updateSyntaxCheck = (removedIncludes.removeAll(fname) == 0); // don't update syntax if include was removed and reinstated
				mIncludedFilesList.insert(line(i).handle(), fname);
				LatexDocument *dc = parent->findDocumentFromName(fname);
				if (dc) {
					childDocs.insert(dc);
                    dc->setMasterDocument(this, recheckLabels && updateSyntaxCheck);
				} else {
					lstFilesToLoad << fname;
					//parent->addDocToLoad(fname);
				}
				newInclude->valid = !fname.isEmpty();
				newInclude->setLine(line(i).handle(), i);
				newInclude->columnNumber = cmdStart;
				flatStructure << newInclude;
				continue;
			}

			if (lp.possibleCommands["%import"].contains(cmd) && !isDefinitionArgument(firstArg)) {
				StructureEntry *newInclude = new StructureEntry(this, StructureEntry::SE_INCLUDE);
				newInclude->level = parent && !parent->indentIncludesInStructure ? 0 : lp.structureDepth() - 1;
                newInclude->setContext(StructureEntry::Import);
				QDir dir(firstArg);
                QFileInfo fi(dir, Parsing::getArg(args, dlh, 1, ArgumentList::Mandatory,true,i));
				QString file = fi.filePath();
				newInclude->title = file;
				QString fname = findFileName(file);
                updateSyntaxCheck = (removedIncludes.removeAll(fname) == 0); // don't update syntax if include was removed and reinstated
                mImportedFilesList.insert(line(i).handle(), fname);
				LatexDocument *dc = parent->findDocumentFromName(fname);
				if (dc) {
					childDocs.insert(dc);
                    dc->setMasterDocument(this, recheckLabels && updateSyntaxCheck);
                    dc->importedFile=true;
				} else {
					lstFilesToLoad << fname;
					//parent->addDocToLoad(fname);
				}
				newInclude->valid = !fname.isEmpty();
				newInclude->setLine(line(i).handle(), i);
				newInclude->columnNumber = cmdStart;
				flatStructure << newInclude;
				continue;
			}

			//// all sections ////
			if (cmd.endsWith("*"))
				cmd = cmd.left(cmd.length() - 1);
			int level = lp.structureCommandLevel(cmd);
			if(level<0 && cmd=="\\begin"){
				// special treatment for \begin{frame}{title}
				level=lp.structureCommandLevel(cmd+"{"+firstArg+"}");
			}
			if (level > -1 && !firstArg.isEmpty() && tkCmd.subtype == Token::none) {
				StructureEntry *newSection = new StructureEntry(this, StructureEntry::SE_SECTION);
				if (mAppendixLine && indexOf(mAppendixLine) < i) newSection->setContext(StructureEntry::InAppendix);
				if (mBeyondEnd && indexOf(mBeyondEnd) < i) newSection->setContext(StructureEntry::BeyondEnd);
				//QString firstOptArg = Parsing::getArg(args, dlh, 0, ArgumentList::Optional);
				QString firstOptArg = Parsing::getArg(args, Token::shorttitle);
				if (!firstOptArg.isEmpty() && firstOptArg != "[]") // workaround, actually getArg should return "" for "[]"
					firstArg = firstOptArg;
				if(cmd=="\\begin"){
					// special treatment for \begin{frame}{title}
                    firstArg = Parsing::getArg(args, dlh, 1, ArgumentList::MandatoryWithBraces,false,i);
					if(firstArg.isEmpty()){
						// empty frame title, maybe \frametitle is used ?
						delete newSection;
						continue;
					}
				}
				newSection->title = latexToText(firstArg).trimmed();
				newSection->level = level;
				newSection->setLine(line(i).handle(), i);
				newSection->columnNumber = cmdStart;
				flatStructure << newSection;
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
					mUserCommandList.insert(line(i).handle(), UserCommandPair(QString(), cs));
				}
			}
			/// auto user commands of \mathcmd{one arg} e.g. \mathsf{abc} or \overbrace{abc}
			if(j+2<tl.length() && !firstArg.isEmpty() && lp.possibleCommands["math"].contains(cmd) ){
				if (lp.commandDefs.contains(cmd)) {
					CommandDescription cd = lp.commandDefs.value(cmd);
					if(cd.args==1 && cd.bracketArgs==0 && cd.optionalArgs==0){
						QString txt=cmd+"{"+firstArg+"}";
                        CodeSnippet cs(txt,true,true);
						cs.type=CodeSnippet::userConstruct;
						mUserCommandList.insert(line(i).handle(), UserCommandPair(QString(), cs));
					}
				}
			}

		} // while(findCommandWithArgs())

		if (!oldBibs.isEmpty())
			bibTeXFilesNeedsUpdate = true; //file name removed

		if (!removedIncludes.isEmpty()) {
			parent->removeDocs(removedIncludes);
			parent->updateMasterSlaveRelations(this);
		}
	}//for each line handle
	StructureEntry *se;
	foreach (se, removedTodo) {
        removeElement(se);
		delete se;
	}
	foreach (se, removedBibTeX) {
        removeElement(se);
		delete se;
	}
	foreach (se, removedBlock) {
        removeElement(se);
		delete se;
	}
	foreach (se, removedLabels) {
        removeElement(se);
		delete se;
	}
	foreach (se, removedMagicComments) {
        removeElement(se);
		delete se;
	}
	StructureEntry *newSection = nullptr;

    // always generate complete structure, also for hidden, as needed for globalTOC
    LatexStructureMergerMerge(this, lp.structureDepth(), lineNrStart, newCount)(flatStructure);

    const QList<StructureEntry *> categories =
            QList<StructureEntry *>() << magicCommentList << blockList << labelList << todoList << bibTeXList;

    for (int i = categories.size() - 1; i >= 0; i--) {
        StructureEntry *cat = categories[i];
        if (cat->children.isEmpty() == (cat->parent == nullptr)) continue;
        if (cat->children.isEmpty()) removeElement(cat);
        else insertElement(baseStructure, 0, cat);
    }

    //update appendix change
    if (oldLine != mAppendixLine) {
        updateContext(oldLine, mAppendixLine, StructureEntry::InAppendix);
    }
    //update end document change
    if (oldLineBeyond != mBeyondEnd) {
        updateContext(oldLineBeyond, mBeyondEnd, StructureEntry::BeyondEnd);
    }

    // rehighlight current cursor position
    if (edView) {
        int i = edView->editor->cursor().lineNumber();
        if (i >= 0) {
            newSection = findSectionForLine(i);
        }
    }

	emit structureUpdated(this, newSection);
	bool updateLtxCommands = false;
	if (!addedUsepackages.isEmpty() || !removedUsepackages.isEmpty() || !addedUserCommands.isEmpty() || !removedUserCommands.isEmpty()) {
		bool forceUpdate = !addedUserCommands.isEmpty() || !removedUserCommands.isEmpty();

        reRunSuggested = (count > 1) && (!addedUsepackages.isEmpty() || !removedUsepackages.isEmpty());     
        updateLtxCommands = updateCompletionFiles(forceUpdate, false, true);
        if(!addedUsepackages.isEmpty() || !removedUsepackages.isEmpty()){
            emit updateCompleterCommands();
        }
	}
	if (bibTeXFilesNeedsUpdate)
		emit updateBibTeXFiles();
	// force update on citation overlays
	if (bibItemsChanged || bibTeXFilesNeedsUpdate) {
		parent->updateBibFiles(bibTeXFilesNeedsUpdate);
		// needs probably done asynchronously as bibteFiles needs to be loaded first ...
		foreach (LatexDocument *elem, getListOfDocs()) {
			if (elem->edView)
				elem->edView->updateCitationFormats();
		}
	}
	if (completerNeedsUpdate || bibTeXFilesNeedsUpdate)
		emit updateCompleter();
	if ((!recheck && updateSyntaxCheck) || updateLtxCommands) {
	    this->updateLtxCommands(true);
	}
    //update view (unless patchStructure is run again anyway)
    if (edView && !reRunSuggested)
		edView->documentContentChanged(linenr, count);
#ifndef QT_NO_DEBUG
	if (!isHidden())
		checkForLeak();
#endif
	foreach (QString fname, lstFilesToLoad) {
		parent->addDocToLoad(fname);
	}
	if (reRunSuggested && !recheck){
		patchStructure(0, -1, true); // expensive solution for handling changed packages (and hence command definitions)
	}
	if(!recheck){
		reCheckSyntax(lineNrStart, newCount);
	}
    //qDebug()<<"fin"<<tm.elapsed();

	return reRunSuggested;
}

#ifndef QT_NO_DEBUG
void LatexDocument::checkForLeak()
{
	StructureEntryIterator iter(baseStructure);
	QSet<StructureEntry *>zw = StructureContent;
	while (iter.hasNext()) {
		zw.remove(iter.next());
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
	StructureEntryIterator iter(baseStructure);
    StructureEntry *newSection = nullptr;

	while (/*iter.hasNext()*/true) {
        StructureEntry *curSection = nullptr;
		while (iter.hasNext()) {
			curSection = iter.next();
			if (curSection->type == StructureEntry::SE_SECTION)
				break;
		}
        if (curSection == nullptr || curSection->type != StructureEntry::SE_SECTION)
			break;

		if (curSection->getRealLineNumber() > currentLine) break; //curSection is after newSection where the cursor is
		else newSection = curSection;
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
			//if(doc->getEditorView()->containsBibTeXId(name)){
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
		//if(doc->getEditorView()->containsBibTeXId(name)){
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
		}
	}
	if (!cursor) {
		cur->endEditBlock();
		delete cur;
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

QList<LatexDocument *>LatexDocument::getListOfDocs(QSet<LatexDocument *> *visitedDocs)
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
				listOfDocs << elem->getListOfDocs(visitedDocs);
			}
		}
		if (masterDocument) { //check masters
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
        dlhs.insert(it.key());
    }
    for (it = mRefItem.constBegin(); it != mRefItem.constEnd(); ++it) {
        dlhs.insert(it.key());
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
        dlh->clearOverlays(formatList);
        for(const int pos : occurences.values(dlh)) {
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
                    delete elem->getEditorView();
                    delete elem;
                }
            }
        }

        /*int row = documents.indexOf(document);
        //qDebug()<<document->getFileName()<<row;
        if (!document->baseStructure) row = -1; //may happen directly after reload (but won't)
        */

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
		addDocToLoad(fn);
		LatexDocument *doc = masterDocument;
		masterDocument = nullptr;
		deleteDocument(doc);
		//documents.removeAll(masterDocument);
		//delete masterDocument;
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
	const LatexDocument *rootDoc = currentDocument->getRootDocument();
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
				it.value().absolute = getAbsoluteFilePath(it.value().relative, ".bib", additionalBibPaths).replace(QDir::separator(), "/"); // update absolute path
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

void LatexDocuments::addDocToLoad(QString filename)
{
	emit docToLoad(filename);
}

void LatexDocuments::hideDocInEditor(LatexEditorView *edView)
{
	emit docToHide(edView);
}

int LatexDocument::findStructureParentPos(const QList<StructureEntry *> &children, QList<StructureEntry *> &removedElements, int linenr, int count)
{
	QListIterator<StructureEntry *> iter(children);
	int parentPos = 0;
	while (iter.hasNext()) {
		StructureEntry *se = iter.next();
		int realline = se->getRealLineNumber();
		Q_ASSERT(realline >= 0);
		if (realline >= linenr + count) {
			break;
		}
		if (realline >= linenr) {
			removedElements.append(se);
		}
		++parentPos;
	}
    return parentPos;
}

/*!
 * \brief split the tree structure at lineNr
 * Base structure children are removed if they are among the split off elements
 * \param root element of structure to split
 * \param lineNr
 * \return structure after lineNr referenced to new root element
 */
StructureEntry *LatexDocument::splitStructure(StructureEntry *base, int lineNr)
{
    StructureEntry *result=nullptr;
    if(base->children.isEmpty()){
        // no children to check
        return nullptr;
    }
    // find last element before lineNr
    int i;
    for(i=base->children.count()-1;i>=0;--i){
        StructureEntry *element=base->children.at(i);
        if(element->type!=StructureEntry::SE_SECTION && element->type!=StructureEntry::SE_INCLUDE){
            // non-sections are always "before", except include
            break;
        }
        int ln=element->getRealLineNumber();
        if(ln>=lineNr){
            continue;
        }
        break;
    }
    if(i<0){
        // all elements after lineNr
        result=base->children.takeFirst();
        for(int k=0;k<base->children.count();++k){
            result->add(base->children.at(k));
        }
        base->children.clear();
        result->parent=nullptr;
        return result;
    }
    if(i==base->children.count()-1){
        // all elements before lineNr
        result=splitStructure(base->children.last(),lineNr);
        return result;
    }
    // split found
    result=splitStructure(base->children.at(i),lineNr);
    // resort elements after split
    int offset=1;
    if(!result){
        result=base->children.at(i+1);
        offset=2;
    }
    result->parent=nullptr;
    for(int k=i+offset;k<base->children.count();++k){
        result->add(base->children.at(k));
    }
#if QT_VERSION_MAJOR>5
    base->children.remove(i+1,base->children.count()-i-1);
#else
    const int cnt=base->children.count();
    for(int n=i+1;n<cnt;++n){
        base->children.removeAt(i+1);
    }
#endif

    return result;
}
/*!
 * \brief add second structure to first one
 * Assumes that all elements are after all elements of the first structure
 * \param base
 * \param addition
 */
void LatexDocument::appendStructure(StructureEntry *base, StructureEntry *addition)
{
    if(!addition) return;
    // get last element on different levels
    QVector<StructureEntry *> parent_level(lp.structureDepth()+1);
    parent_level.fill(base);
    StructureEntry *se=base;
    for(int i=0;i<lp.structureDepth();++i){
        if(se->children.isEmpty()){
            break; // no further level to go down
        }
        se=se->children.last();
        for(int j=se->level;j<lp.structureDepth();++j){
            parent_level[j+1]=se;
        }
    }
    int level=addition->level;
    parent_level[level]->add(addition);
    /* check that level are not distorted as first element was too high a level
    *  e.g. \subsection
    *       \section
    */
    for(int i=0;i<addition->children.count();++i){
        se=addition->children.at(i);
        if(se->type != StructureEntry::SE_SECTION){
            continue; // don't touch non-section for now
        }
        if(se->level<=level){
            // move element to appropriate parent level
            level=se->level;
            parent_level[se->level]->add(se);
            addition->children.takeAt(i);
            --i;
        }
    }
}

void LatexStructureMergerMerge::mergeStructure(StructureEntry *se)
{
	if (!se) return;
	if (se->type != StructureEntry::SE_DOCUMENT_ROOT && se->type != StructureEntry::SE_SECTION && se->type != StructureEntry::SE_INCLUDE) return;
	int se_line = se->getRealLineNumber();
	if (se_line < linenr || se->type == StructureEntry::SE_DOCUMENT_ROOT) {
		//se is before updated region, but children might still be in it
		updateParentVector(se);

		//if (!se->children.isEmpty() && se->children.last()->getRealLineNumber() >= linenr) {
		int start = -1;
		for (int i = 0; i < se->children.size(); i++) {
			StructureEntry *c = se->children[i];
			if (c->type != StructureEntry::SE_SECTION && c->type != StructureEntry::SE_INCLUDE) continue;
			if (c->getRealLineNumber() < linenr)
				updateParentVector(c);
			start = i;
			break;
		}
		if (start >= 0) {
			if (start > 0) start--;
			mergeChildren(se, start);
		}
	} else {
		//se is within or after the region
		// => insert flatStructure.first() before se or replace se with it (don't insert after since there might be another "se" to replace)
		while (!flatStructure->isEmpty() && se->getRealLineNumber() >= flatStructure->first()->getRealLineNumber() ) {
			StructureEntry * next = flatStructure->takeFirst();
			if (se->getRealLineNumber() == next->getRealLineNumber()) {
				//copy next to se except for parent/children
				next->parent = se->parent;
				next->children = se->children;
				*se = *next;
				next->children.clear();
				delete next;
				moveToAppropiatePositionWithSignal(se);
				//	qDebug()<<"a"<<se->children.size() << ":"<<se->title<<" von "<<linenr<<count;
				mergeChildren(se);
				return;
			}
			moveToAppropiatePositionWithSignal(next);
		}

		if (se_line < linenr + count) {
			//se is within the region (delete if necessary and then merge children)
			if (flatStructure->isEmpty() || se->getRealLineNumber() < flatStructure->first()->getRealLineNumber()) {
				QList<StructureEntry *> oldChildren = se->children;
				int oldrow = se->getRealParentRow();
				for (int i = se->children.size() - 1; i >= 0; i--)
					document->moveElementWithSignal(se->children[i], se->parent, oldrow);
                document->removeElement(se);
				delete se;
				for (int i = 1; i < parent_level.size(); i++)
					if (parent_level[i] == se)
						parent_level[i] = parent_level[i - 1];
				foreach (StructureEntry *next, oldChildren)
					mergeStructure(next);
				return;
			}
		}

		//se not replaced or deleted => se is after everything the region => keep children
		moveToAppropiatePositionWithSignal(se);
		QList<StructureEntry *> oldChildren = se->children;
		foreach (StructureEntry *c, oldChildren)
			moveToAppropiatePositionWithSignal(c);

	}

	//insert unprocessed elements of flatStructure at the end of the structure
	if (se->type == StructureEntry::SE_DOCUMENT_ROOT && !flatStructure->isEmpty()) {
		foreach (StructureEntry *s, *flatStructure) {
            document->addElement(parent_level[s->level], s);
			updateParentVector(s);
		}
		flatStructure->clear();
	}
}

void LatexStructureMergerMerge::mergeChildren(StructureEntry *se, int start){
	QList<StructureEntry *> oldChildren = se->children; //need to cow-protected list, in case se will be changed by mergeStructure
	for (int i = start; i < oldChildren.size(); i++)
		mergeStructure(oldChildren[i]);
}

void LatexDocument::removeElement(StructureEntry *se)
{
	int parentRow = se->getRealParentRow();
	REQUIRE(parentRow >= 0);

	se->parent->children.removeAt(parentRow);
	se->parent = nullptr;
}

void LatexDocument::addElement(StructureEntry *parent, StructureEntry *se)
{
	parent->children.append(se);
	se->parent = parent;
}

void LatexDocument::insertElement(StructureEntry *parent, int pos, StructureEntry *se)
{
    if(pos>parent->children.size()){
        pos=parent->children.size();
    }
	parent->children.insert(pos, se);
	se->parent = parent;
}

void LatexDocument::moveElementWithSignal(StructureEntry *se, StructureEntry *parent, int pos)
{
    removeElement(se);
    insertElement(parent, pos, se);
}

void LatexStructureMerger::updateParentVector(StructureEntry *se)
{
	REQUIRE(se);
	if (se->type == StructureEntry::SE_DOCUMENT_ROOT
					|| (se->type == StructureEntry::SE_INCLUDE && document->parent && !document->parent->indentIncludesInStructure))
		parent_level.fill(document->baseStructure);
	else if (se->type == StructureEntry::SE_SECTION)
		for (int j = se->level + 1; j < parent_level.size(); j++)
			parent_level[j] = se;
}

class LessThanRealLineNumber
{
public:
	inline bool operator()(const StructureEntry *const se1, const StructureEntry *const se2) const
	{
		int l1 = se1->getRealLineNumber();
		int l2 = se2->getRealLineNumber();
		if (l1 < l2) return true;
		if (l1 == l2 && (se1->columnNumber < se2->columnNumber)) return true;
		return false;
	}
};

void LatexStructureMerger::moveToAppropiatePositionWithSignal(StructureEntry *se)
{
	REQUIRE(se);
	StructureEntry *newParent = parent_level.value(se->level, nullptr);
	if (!newParent) {
		qDebug("structure update failed!");
		return;
	}
	int oldPos, newPos;
	LessThanRealLineNumber compare;
	if (se->parent == newParent) {
		//the construction somehow ensures that in this case
		//se is already at the correct position regarding line numbers.
		//but not necessarily regarding the column position
		oldPos = se->getRealParentRow();
		if ((oldPos == 0 || compare(newParent->children[oldPos - 1], se )) &&
				(oldPos == newParent->children.size() - 1 || compare(se, newParent->children[oldPos + 1] ))
			)
			newPos = oldPos;
		else {
            newPos = std::upper_bound(newParent->children.begin(), newParent->children.end(), se, compare) - newParent->children.begin();
			while (newPos > 0
				 && newParent->children[newPos-1]->getRealLineNumber() == se->getRealLineNumber()
				 && newParent->children[newPos-1]->columnNumber == se->columnNumber
			)
				newPos--; //upperbound always returns the position after se if it is in newParent->children
		}
	} else {
		oldPos = -1;
		if (newParent->children.size() > 0 &&
				newParent->children.last()->getRealLineNumber() >= se->getRealLineNumber())
            newPos = std::upper_bound(newParent->children.begin(), newParent->children.end(), se, compare) - newParent->children.begin();
		else
			newPos = newParent->children.size();
	}


	//qDebug() << "auto insert " << se->title <<" at " << newPos;
	if (se->parent) {
		if (newPos != oldPos)
			document->moveElementWithSignal(se, newParent, newPos);
    } else document->insertElement(newParent, newPos, se);

	updateParentVector(se);
	return;
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
void LatexDocument::addMagicComment(const QString &text, int lineNr, int posMagicComment)
{
	StructureEntry *newMagicComment = new StructureEntry(this, StructureEntry::SE_MAGICCOMMENT);
	QDocumentLineHandle *dlh = line(lineNr).handle();
	QString name;
	QString val;
	splitMagicComment(text, name, val);

	parseMagicComment(name, val, newMagicComment);
	newMagicComment->title = text;
	newMagicComment->setLine(dlh, lineNr);
    insertElement(magicCommentList, posMagicComment, newMagicComment);
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
		LatexDocument *dc = parent->findDocumentFromName(fname);
		if (dc) {
			dc->childDocs.insert(this);
			setMasterDocument(dc);
		} else {
			parent->addDocToLoad(fname);
		}
		se->valid = true;
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
			// remove appendic marker
			StructureEntry *se = baseStructure;
			setContextForLines(se, startLine, endLine, context, false);
		}
	}

	if (endLine > -1 && (endLine < startLine || startLine < 0)) {
		StructureEntry *se = baseStructure;
		setContextForLines(se, endLine, startLine, context, true);
	}
}

void LatexDocument::setContextForLines(StructureEntry *se, int startLine, int endLine, StructureEntry::Context context, bool state)
{
	bool first = false;
	for (int i = 0; i < se->children.size(); i++) {
		StructureEntry *elem = se->children[i];
		if (endLine >= 0 && elem->getLineHandle() && elem->getRealLineNumber() > endLine) break;
		if (elem->type == StructureEntry::SE_SECTION && elem->getRealLineNumber() > startLine) {
			if (!first && i > 0) setContextForLines(se->children[i - 1], startLine, endLine, context, state);
			elem->setContext(context, state);
			setContextForLines(se->children[i], startLine, endLine, context, state);
			first = true;
		}
	}
	if (!first && !se->children.isEmpty()) {
		StructureEntry *elem = se->children.last();
		if (elem->type == StructureEntry::SE_SECTION) setContextForLines(elem, startLine, endLine, context, state);
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
	QString result;
	if (QFile(getAbsoluteFilePath(fname, ".tex")).exists())
		result = QFileInfo(getAbsoluteFilePath(fname, ".tex")).absoluteFilePath();
	if (result.isEmpty() && QFile(getAbsoluteFilePath(curPath + fname, ".tex")).exists())
		result = QFileInfo(getAbsoluteFilePath(curPath + fname, ".tex")).absoluteFilePath();
	if (result.isEmpty() && QFile(getAbsoluteFilePath(curPath + fname, "")).exists())
		result = QFileInfo(getAbsoluteFilePath(curPath + fname, "")).absoluteFilePath();
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

const LatexDocument *LatexDocument::getRootDocument(QSet<const LatexDocument *> *visitedDocs) const
{
	// special handling if explicit master is set
    if(!parent) return nullptr;
	if (parent && parent->masterDocument)
		return parent->masterDocument;
	const LatexDocument *result = this;
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

bool LatexDocument::updateCompletionFiles(const bool forceUpdate, const bool forceLabelUpdate, const bool delayUpdate)
{

	QStringList files = mUsepackageList.values();
	bool update = forceUpdate;
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
	update = true;

    mCWLFiles = convertStringListtoSet(loadedFiles);
	QSet<QString> userCommandsForSyntaxCheck = ltxCommands.possibleCommands["user"];
	QSet<QString> columntypeForSyntaxCheck = ltxCommands.possibleCommands["%columntypes"];
	ltxCommands.optionCommands = pck.optionCommands;
	ltxCommands.specialTreatmentCommands = pck.specialTreatmentCommands;
	ltxCommands.specialDefCommands = pck.specialDefCommands;
	ltxCommands.possibleCommands = pck.possibleCommands;
	ltxCommands.environmentAliases = pck.environmentAliases;
	ltxCommands.commandDefs = pck.commandDescriptions;
	QSet<QString> pckSet = pck.possibleCommands["user"];
	ltxCommands.possibleCommands["user"] = userCommandsForSyntaxCheck.unite(pckSet);
	ltxCommands.possibleCommands["%columntypes"] = columntypeForSyntaxCheck;

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
		if (!elem.startsWith("\\begin{") && !elem.startsWith("\\end{")) {
            int i = elem.indexOf(QRegularExpression("\\W"), 1);
			//int j=elem.indexOf("[");
			if (i >= 0) elem = elem.left(i);
			//if(j>=0 && j<i) elem=elem.left(j);
		}
	}

	//patch lines for new commands (ref,def, etc)

	QStringList categories;
    categories << "%ref" << "%label" << "%definition" << "%cite" << "%citeExtendedCommand" << "%usepackage" << "%graphics" << "%file" << "%bibliography" << "%include" << "%url" << "%todo" << "%replace";
	foreach (const QString elem, categories) {
		QStringList cmds = ltxCommands.possibleCommands[elem].values();
		foreach (const QString cmd, cmds) {
			if (!latexParser.possibleCommands[elem].contains(cmd) || forceLabelUpdate) {
				latexParser.possibleCommands[elem] << cmd;
			}
		}
	}
	bool needQNFAupdate = false;
    QStringList cmdsToUpdate;
	for (int i = 0; i < latexParser.MAX_STRUCTURE_LEVEL; i++) {
		QString elem = QString("%structure%1").arg(i);
		QStringList cmds = ltxCommands.possibleCommands[elem].values();
		foreach (const QString cmd, cmds) {
			bool update = !latexParser.possibleCommands[elem].contains(cmd);
			if (update) {
				latexParser.possibleCommands[elem] << cmd;
                cmdsToUpdate<<cmd;
				//only update QNFA for added commands. When the default commands are not in ltxCommands.possibleCommands[elem], ltxCommands.possibleCommands[elem] and latexParser.possibleCommands[elem] will always differ and regenerate the QNFA needlessly after every key press
                needQNFAupdate = true;
                cmdsToUpdate<<cmd;
            }
		}
	}
    if (needQNFAupdate)
		parent->requestQNFAupdate();

    if (delayUpdate && cmdsToUpdate.isEmpty()) // force update here if structure commands are changed
		return update;

	if (update) {
		updateLtxCommands(true);
	}
    if(!cmdsToUpdate.isEmpty()){
        patchLinesContaining(cmdsToUpdate);
    }

	return false;
}

const QSet<QString> &LatexDocument::getCWLFiles() const
{
	return mCWLFiles;
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
                // TODO: oha, the key can be even more complex: option#filename.cwl/masterfile
                // consider this in the key-handling functions of LatexPackage
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

QString LatexDocument::getMagicComment(const QString &name) const
{
	QString seName;
	QString val;
	StructureEntryIterator iter(magicCommentList);
	while (iter.hasNext()) {
		StructureEntry *se = iter.next();
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

	if (!magicCommentList) return nullptr;

	StructureEntryIterator iter(magicCommentList);
	while (iter.hasNext()) {
		StructureEntry *se = iter.next();
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
	if (!magicCommentList) return;

	localMacros.clear();

	QRegExp rxTrigger(" *// *(Trigger) *[:=](.*)");

	StructureEntryIterator iter(magicCommentList);
	while (iter.hasNext()) {
		StructureEntry *se = iter.next();
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
				if (rxTrigger.exactMatch(lt))
					trigger = rxTrigger.cap(2).trimmed();
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
QSet<QString> LatexDocument::usedPackages()
{
	QSet<QString> packages;
	foreach (LatexDocument *doc, getListOfDocs()) {
        packages.unite(convertStringListtoSet(doc->containedPackages()));
	}
	return packages;
}

LatexDocument *LatexDocuments::getRootDocumentForDoc(LatexDocument *doc) const   // doc==0 means current document
{
	if (masterDocument)
		return masterDocument;
	LatexDocument *current = currentDocument;
	if (doc)
		current = doc;
	if (!current)
		return current;
	return current->getRootDocument();
}

QString LatexDocument::getAbsoluteFilePath(const QString &relName, const QString &extension, const QStringList &additionalSearchPaths) const
{
	QStringList searchPaths;
	const LatexDocument *rootDoc = getRootDocument();
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

void LatexDocument::patchLinesContaining(const QStringList cmds)
{
	foreach (LatexDocument *elem, getListOfDocs()) {
		// search all cmds in all lines, patch line if cmd is found
		for (int i = 0; i < elem->lines(); i++) {
			QString text = elem->line(i).text();
			foreach (const QString cmd, cmds) {
				if (text.contains(cmd)) {
					elem->patchStructure(i, 1);
					//patchStructure(i,1);
					break;
				}
			}
		}
	}
}

void LatexDocuments::enablePatch(const bool enable)
{
	m_patchEnabled = enable;
}

bool LatexDocuments::patchEnabled()
{
	return m_patchEnabled;
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


void LatexDocument::updateLtxCommands(bool updateAll)
{
	lp.init();
	lp.append(LatexParser::getInstance()); // append commands set in config
	QList<LatexDocument *>listOfDocs = getListOfDocs();
	foreach (const LatexDocument *elem, listOfDocs) {
		lp.append(elem->ltxCommands);
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
				LatexParser lp;
				lp.init();
				lp.append(LatexParser::getInstance()); // append commands set in config
				QList<LatexDocument *>listOfDocs = elem->getListOfDocs();
				foreach (const LatexDocument *elem, listOfDocs) {
					lp.append(elem->ltxCommands);
				}
				foreach (LatexDocument *elem, listOfDocs) {
					elem->setLtxCommands(lp);
					elem->reCheckSyntax();
				}
			}
		}
	} else {
		SynChecker.setLtxCommands(lp);
	}

	LatexEditorView *view = getEditorView();
	if (view) {
		view->updateReplamentList(lp, false);
	}
}

void LatexDocument::setLtxCommands(const LatexParser &cmds)
{
	SynChecker.setLtxCommands(cmds);
	lp = cmds;

	LatexEditorView *view = getEditorView();
	if (view) {
		view->updateReplamentList(cmds, false);
    }
}

void LatexDocument::setSpeller(SpellerUtility *speller)
{
    SynChecker.setSpeller(speller);
}

void LatexDocument::setReplacementList(QMap<QString, QString> replacementList)
{
    SynChecker.setReplacementList(replacementList);
}

void LatexDocument::updateSettings()
{
	SynChecker.setErrFormat(syntaxErrorFormat);
    QMap<QString,int> fmtList;
    QList<QPair<QString,QString> >formats;
    formats<<QPair<QString,QString>("math","numbers")<<QPair<QString,QString>("verbatim","verbatim")<<QPair<QString,QString>("pictureHighlight","picture")
            <<QPair<QString,QString>("#math","math-keyword")<<QPair<QString,QString>("#pictureHighlight","picture-keyword")<<QPair<QString,QString>("&math","math-delimiter")
            <<QPair<QString,QString>("#mathText","math-text")<<QPair<QString,QString>("align-ampersand","align-ampersand")<<QPair<QString,QString>("comment","comment");
    for(const auto &elem : formats){
        fmtList.insert(elem.first,getFormatId(elem.second));
    }
    SynChecker.setFormats(fmtList);
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
					SynChecker.putLine(unclosedEnv.dlh, env, remainder, true, unclosedEnvIndex);
				}
			}
			if (env.size() > 1) {
				//at least one env has not been closed
				Environment environment = env.top();
				unclosedEnv = env.top();
				SynChecker.markUnclosedEnv(environment);
			}
			return;
		}
		TokenStack remainder = dlh->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
        SynChecker.putLine(line(index + 1).handle(), env, remainder, clearOverlay,index+1);
	}
    dlh->deref();
}

bool LatexDocument::languageIsLatexLike() const
{
	QLanguageDefinition *ld = languageDefinition();
	if (!ld) return false;
	return LATEX_LIKE_LANGUAGES.contains(ld->language());
}

/*
 * \brief Forces syntax recheck of a group of lines
 * \param[in] lineStart Starting line number to be checked
 * \param[in] lineNum Total number of lines to be checked. If -1, then check all lines to the end of the document.
 */
void LatexDocument::reCheckSyntax(int lineStart, int lineNum)
{
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
    } //crash in qt6, looks like race coming from patchLines...

	// Enqueue the first line for syntax checking. The remaining lines will be enqueued automatically
	// through the checkNextLine signal because we deleted their STACK_ENVIRONMENT_COOKIE cookies.
	StackEnvironment prevEnv;
	getEnv(lineStart, prevEnv);
	TokenStack prevTokens;
	if (lineStart) {
		prevTokens = line(lineStart-1).getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack>();
	}
	SynChecker.putLine(line(lineStart).handle(), prevEnv, prevTokens, true, lineStart);
}

QString LatexDocument::getErrorAt(QDocumentLineHandle *dlh, int pos, StackEnvironment previous, TokenStack stack)
{
	return SynChecker.getErrorAt(dlh, pos, previous, stack);
}

int LatexDocument::syntaxErrorFormat;

void LatexDocument::getEnv(int lineNumber, StackEnvironment &env)
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
