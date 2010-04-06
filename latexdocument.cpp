#include "latexdocument.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "qdocumentcursor.h"
#include "qeditor.h"
#include "smallUsefulFunctions.h"

LatexDocument::LatexDocument():edView(0),text(0),mAppendixLine(0)
{
	baseStructure = new StructureEntry(this,StructureEntry::SE_DOCUMENT_ROOT);
	labelList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	todoList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	bibTeXList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	blockList = new StructureEntry(this, StructureEntry::SE_OVERVIEW);
	mLabelItem.clear();
	mUserCommandList.clear();
	mMentionedBibTeXFiles.clear();
}
LatexDocument::~LatexDocument(){
	delete baseStructure;
}

void LatexDocument::setFileName(const QString& fileName){
	//clear all references to old editor
	if (this->edView || this->text){
		StructureEntryIterator iter(baseStructure);
		while (iter.hasNext()) iter.next()->lineHandle=0;
	}

	this->fileName=fileName;
	this->fileInfo=QFileInfo(fileName);
	this->edView=0;
	this->text=0;
}
void LatexDocument::setEditorView(LatexEditorView* edView){
	this->fileName=edView->editor->fileName();
	this->fileInfo=edView->editor->fileInfo();
	this->edView=edView;
	this->text=edView->editor->document();
        if(baseStructure){
            baseStructure->title=fileName;
            emit updateElement(baseStructure);
        }
}
LatexEditorView *LatexDocument::getEditorView(){
	return this->edView;
}
QDocument *LatexDocument::getText(){
	return text;
}
QString LatexDocument::getFileName(){
	return fileName;
}
QFileInfo LatexDocument::getFileInfo(){
	return fileInfo;
}

QDocumentSelection LatexDocument::sectionSelection(StructureEntry* section){
	QDocumentSelection result;
	result.endLine=-1;result.startLine=-1;

	if (section->type!=StructureEntry::SE_SECTION) return result;
	int startLine=section->getRealLineNumber();

	// find next section or higher
	StructureEntry* parent;
	int index;
	do {
		parent=section->parent;
		if (parent) {
			index=parent->children.indexOf(section);
			section=parent;
		} else index=-1;
	} while ((index>=0)&&(index>=parent->children.count()-1)&&(parent->type==StructureEntry::SE_SECTION));

	int endingLine=-1;
	if (index>=0 && index<parent->children.count()-1) {
		endingLine=parent->children.at(index+1)->getRealLineNumber();
	} else if (text) {
		// no ending section but end of document
		endingLine=text->findLineContaining("\\end{document}",startLine,Qt::CaseInsensitive);
		if (endingLine<0) endingLine=text->lines();
	} else return result;

	result.startLine=startLine;
	result.endLine=endingLine;
	result.end=0;
	result.start=0;
	return result;
}

void LatexDocument::clearStructure() {
    mUserCommandList.clear();
    mLabelItem.clear();
    mMentionedBibTeXFiles.clear();
    
    mAppendixLine=0;

    emit structureLost(this);

    delete baseStructure;
    baseStructure=0;
}

void LatexDocument::updateStructure() {

	QDocument* document=text;
	bool temporaryLoadedDocument=false;
	if (!document) {
		if (fileName=="" || !fileInfo.exists())
			return;
		temporaryLoadedDocument=true;
		document=new QDocument();
		document->load(fileName,QDocument::defaultCodec());
	}

	mUserCommandList.clear();
	mLabelItem.clear();
	mMentionedBibTeXFiles.clear();

	//emit structureLost(this); does removal cause problems ????

	delete baseStructure;
	baseStructure=0;

	mAppendixLine=0;

	baseStructure = new StructureEntry(this,StructureEntry::SE_DOCUMENT_ROOT);
	baseStructure->title=fileName;
	labelList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	labelList->title=tr("LABELS");
	todoList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	todoList->title=tr("TODO");
	bibTeXList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	bibTeXList->title=tr("BIBTEX");
	blockList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	blockList->title=tr("BLOCKS");

	QVector<StructureEntry*> parent_level(LatexParser::structureCommands.count());
	for (int i=0;i<parent_level.size();i++)
		parent_level[i]=baseStructure;

	//TODO: This assumes one command per line, which is not necessary true
	for (int i=0; i<document->lines(); i++) {
		const QString curLine = document->line(i).text(); //TODO: use this instead of s
		//// newcommand ////
		//TODO: handle optional arguments
		static const QStringList commandTokens = QStringList() << "\\newcommand{" << "\\renewcommand{" << "\\providecommand{{";
		for (int j=0; j< commandTokens.size();j++){
			QString name;
			QString arg;
			if (findTokenWithArg(curLine,commandTokens[j],name,arg)) {
				int options=arg.toInt(); //returns 0 if conversion fails
				for (int j=0; j<options; j++) {
					if (j==0) name.append("{%<arg1%|%>}");
					else name.append(QString("{%<arg%1%>}").arg(j+1));
				}
				mUserCommandList.insert(document->line(i).handle(),name);
			}
		}
		//// newenvironment ////
		static const QStringList envTokens = QStringList() << "\\newenvironment{" << "\\renewenvironment{";
		for (int j=0; j< envTokens.size();j++){
			QString name;
			QString arg;
			if (findTokenWithArg(curLine,envTokens[j],name,arg)) {
				int options=arg.toInt(); //returns 0 if conversion fails
				name.append("}");
				mUserCommandList.insert(document->line(i).handle(),"\\end{"+name);
				for (int j=0; j<options; j++) {
					if (j==0) name.append("{%<1%|%>}");
					else name.append(QString("{%<%1%>}").arg(j+1));
				}
				mUserCommandList.insert(document->line(i).handle(),name);
				mUserCommandList.insert(document->line(i).handle(),"\\begin{"+name);
			}
		}
		//// newtheorem ////
		QString s=findToken(curLine,"\\newtheorem{");
		if (s!="") {
			mUserCommandList.insert(document->line(i).handle(),"\\begin{"+s+"}");
			mUserCommandList.insert(document->line(i).handle(),"\\end{"+s+"}");
		}
		//// bibliography ////
		s=findToken(curLine,"\\bibliography{");
		if (s!="") {
			QStringList bibs=s.split(',',QString::SkipEmptyParts);
			foreach(QString elem,bibs){
			    mMentionedBibTeXFiles.insert(document->line(i).handle(),elem);
			}
			foreach (const QString& bibFile, bibs) {
				StructureEntry *newFile=new StructureEntry(this,bibTeXList, StructureEntry::SE_BIBTEX);
				newFile->title=bibFile;
				newFile->lineNumber=i;
				if (!temporaryLoadedDocument)
					newFile->lineHandle=document->line(i).handle();
			}
		}
		//// label ////
		//TODO: Use label from dynamical reference checker
		s=findToken(curLine,"\\label{");
		if (s!="") {
			mLabelItem.insert(document->line(i).handle(),s);
			StructureEntry *newLabel=new StructureEntry(this,labelList, StructureEntry::SE_LABEL);
			newLabel->title=s;
			newLabel->lineNumber=i;
			if (!temporaryLoadedDocument)
				newLabel->lineHandle=document->line(i).handle();
		}
		//// TODO marker
		s=curLine;
		int l=s.indexOf("%TODO");
		if (l>=0) {
			s=s.mid(l+6,s.length());
			StructureEntry *newTodo=new StructureEntry(this,todoList, StructureEntry::SE_TODO);
			newTodo->title=s;
			newTodo->lineNumber=i;
			if (!temporaryLoadedDocument)
				newTodo->lineHandle=document->line(i).handle();
		}
		//// Appendix keyword
		if (curLine=="\\appendix") {
			mAppendixLine=document->line(i).handle();
		}
		//// beamer blocks ////
		s=findToken(curLine,"\\begin{block}{");
		if (s!="") {
			StructureEntry *newBlock=new StructureEntry(this,blockList, StructureEntry::SE_BLOCK);
			newBlock->title=s;
			newBlock->lineNumber=i;
			if (!temporaryLoadedDocument)
				newBlock->lineHandle=document->line(i).handle();
		}

		//// include,input ////
		static const QStringList inputTokens = QStringList() << "input" << "include";
		for(int header=0;header<inputTokens.count();header++){
			s=findToken(curLine,"\\"+inputTokens.at(header)+"{");
			if (s!="") {
				StructureEntry *newInclude=new StructureEntry(this,baseStructure, StructureEntry::SE_INCLUDE);
				newInclude->title=s;
//				newInclude.title=inputTokens.at(header); //texmaker distinguished include/input, doesn't seem necessary
				newInclude->lineNumber=i;
				newInclude->level=fileExits(s)? 0 : 1;
				if (!temporaryLoadedDocument)
					newInclude->lineHandle=document->line(i).handle();
			}
		}//for
		//// all sections ////
		for(int header=0;header<LatexParser::structureCommands.count();header++){
			QRegExp regexp = QRegExp("\\"+LatexParser::structureCommands[header]+"\\*?[\\{\\[]");
			s=findToken(curLine,regexp);
			if (s!="") {
				s=extractSectionName(s);
				StructureEntry* parent=header == 0 ? baseStructure : parent_level[header-1];
				StructureEntry *newSection=new StructureEntry(this,parent,StructureEntry::SE_SECTION);
				newSection->title=s;
				newSection->level=header;
				newSection->lineNumber=i;
				if (!temporaryLoadedDocument){
					newSection->lineHandle=document->line(i).handle();
					if(mAppendixLine &&mAppendixLine->line()<i) newSection->appendix=true;
				    }
				parent_level[header]=newSection;
				for(int j=header+1;j<parent_level.size();j++)
					parent_level[j]=parent_level[header];
			}
		}
	}

	if (!bibTeXList->children.isEmpty()) baseStructure->insert(0, bibTeXList);
	if (!todoList->children.isEmpty()) baseStructure->insert(0, todoList);
	if (!labelList->children.isEmpty()) baseStructure->insert(0, labelList);
	if (!blockList->children.isEmpty()) baseStructure->insert(0, blockList);

	emit structureUpdated(this);

	if (temporaryLoadedDocument)
		delete document;
}

void LatexDocument::patchStructureRemoval(QDocumentLineHandle* dlh) {

	if(!baseStructure) return;
    mLabelItem.remove(dlh);
    mMentionedBibTeXFiles.remove(dlh);
    mUserCommandList.remove(dlh);

	if(dlh==mAppendixLine){
		updateAppendix(mAppendixLine,0);
		mAppendixLine=0;
	}

	int linenr=dlh->line();
	if (linenr==-1) linenr=text->lines();

	QList<StructureEntry*> categories=QList<StructureEntry*>() << labelList << todoList << blockList << bibTeXList;
	foreach (StructureEntry* sec, categories) {
		int l=0;
		QMutableListIterator<StructureEntry*> iter(sec->children);
		while (iter.hasNext()){
			StructureEntry* se=iter.next();
			if(dlh==se->lineHandle) {
				iter.remove();
				removeElement(se,l);
				delete se;
			} else l++;
		}
	}

	QVector<StructureEntry*> parent_level(LatexParser::structureCommands.count());
	QVector<QList<StructureEntry*> > remainingChildren(LatexParser::structureCommands.count());
	QMap<StructureEntry*,int> toBeDeleted;
	QMultiHash<QDocumentLineHandle*,StructureEntry*> MapOfElements;
	StructureEntry* se=baseStructure;
	splitStructure(se,parent_level,remainingChildren,toBeDeleted,MapOfElements,linenr,1);

	// append structure remainder ...
	for(int i=parent_level.size()-1;i>=0;i--){
		while(!remainingChildren[i].isEmpty() && remainingChildren[i].first()->level>i){
		se=remainingChildren[i].takeFirst();
		parent_level[se->level]->add(se);
		}
		parent_level[i]->children.append(remainingChildren[i]);
		foreach(StructureEntry *elem,remainingChildren[i]){
		elem->parent=parent_level[i];
		}
	}
	// purge unconnected elements
	foreach(se,toBeDeleted.keys()){
		emit removeElement(se,toBeDeleted.value(se));
		delete se;
	}

    emit structureUpdated(this);
}

void LatexDocument::patchStructure(int linenr, int count) {

	QDocument* document=text;
	if (!document || !baseStructure) return;

	bool completerNeedsUpdate=false;

	QDocumentLineHandle *oldLine=mAppendixLine; // to detect a change in appendix position

	QMutableListIterator<StructureEntry*> iter_label(labelList->children);
	findStructureEntryBefore(iter_label,linenr,count);

	QMutableListIterator<StructureEntry*> iter_todo(todoList->children);
	findStructureEntryBefore(iter_todo,linenr,count);

	QMutableListIterator<StructureEntry*> iter_block(blockList->children);
	findStructureEntryBefore(iter_block,linenr,count);

	QMutableListIterator<StructureEntry*> iter_bibTeX(bibTeXList->children);
	findStructureEntryBefore(iter_bibTeX,linenr,count);

	QVector<StructureEntry*> parent_level(LatexParser::structureCommands.count());
	QVector<QList<StructureEntry*> > remainingChildren(LatexParser::structureCommands.count());
	QMap<StructureEntry*,int> toBeDeleted;
	QMultiHash<QDocumentLineHandle*,StructureEntry*> MapOfElements;
	StructureEntry* se=baseStructure;
	splitStructure(se,parent_level,remainingChildren,toBeDeleted,MapOfElements,linenr,count);

	//TODO: This assumes one command per line, which is not necessary true
	for (int i=linenr; i<linenr+count; i++) {
		const QString curLine = document->line(i).text(); //TODO: use this instead of s

		// remove command,bibtex,labels at from this line
		QDocumentLineHandle* dlh=document->line(i).handle();
		completerNeedsUpdate=completerNeedsUpdate || (mLabelItem.remove(dlh)>0);
		completerNeedsUpdate=completerNeedsUpdate || (mMentionedBibTeXFiles.remove(dlh)>0);
		completerNeedsUpdate=completerNeedsUpdate || (mUserCommandList.remove(dlh)>0);
		//find entries prior to changed lines



		//// newcommand ////
		//TODO: handle optional arguments
		static const QStringList commandTokens = QStringList() << "\\newcommand{" << "\\renewcommand{" << "\\providecommand{{";
		for (int j=0; j< commandTokens.size();j++){
			QString name;
			QString arg;
			if (findTokenWithArg(curLine,commandTokens[j],name,arg)) {
				completerNeedsUpdate=true;
				int options=arg.toInt(); //returns 0 if conversion fails
				for (int j=0; j<options; j++) {
					if (j==0) name.append("{%<arg1%|%>}");
					else name.append(QString("{%<arg%1%>}").arg(j+1));
				}
				mUserCommandList.insert(document->line(i).handle(),name);
			}
		}
		//// newenvironment ////
		static const QStringList envTokens = QStringList() << "\\newenvironment{" << "\\renewenvironment{";
		for (int j=0; j< envTokens.size();j++){
			QString name;
			QString arg;
			if (findTokenWithArg(curLine,envTokens[j],name,arg)) {
				completerNeedsUpdate=true;
				int options=arg.toInt(); //returns 0 if conversion fails
				name.append("}");
				mUserCommandList.insert(document->line(i).handle(),"\\end{"+name);
				for (int j=0; j<options; j++) {
					if (j==0) name.append("{%<1%|%>}");
					else name.append(QString("{%<%1%>}").arg(j+1));
				}
				mUserCommandList.insert(document->line(i).handle(),name);
				mUserCommandList.insert(document->line(i).handle(),"\\begin{"+name);
			}
		}
		//// newtheorem ////
		QString s=findToken(curLine,"\\newtheorem{");
		if (s!="") {
			completerNeedsUpdate=true;
			mUserCommandList.insert(document->line(i).handle(),"\\begin{"+s+"}");
			mUserCommandList.insert(document->line(i).handle(),"\\end{"+s+"}");
		}
		//// bibliography ////
		s=findToken(curLine,"\\bibliography{");
		if (s!="") {
			QStringList bibs=s.split(',',QString::SkipEmptyParts);
			completerNeedsUpdate=true;
			foreach(QString elem,bibs){
			    mMentionedBibTeXFiles.insert(document->line(i).handle(),elem);
			}
			foreach (const QString& bibFile, bibs) {
				StructureEntry *newFile=new StructureEntry(this, StructureEntry::SE_BIBTEX);
				newFile->title=bibFile;
				newFile->lineNumber=i;
				newFile->lineHandle=document->line(i).handle();
				newFile->parent=bibTeXList;
				iter_bibTeX.insert(newFile);
			}
		}
		//// label ////
		//TODO: Use label from dynamical reference checker
		s=findToken(curLine,"\\label{");
		if (s!="") {
			mLabelItem.insert(document->line(i).handle(),s);
			completerNeedsUpdate=true;
			StructureEntry *newLabel=new StructureEntry(this, StructureEntry::SE_LABEL);
			newLabel->title=s;
			newLabel->lineNumber=i;
			newLabel->lineHandle=document->line(i).handle();
			newLabel->parent=labelList;
			iter_label.insert(newLabel);
		}
		//// TODO marker
		s=curLine;
		int l=s.indexOf("%TODO");
		if (l>=0) {
			s=s.mid(l+6,s.length());
			StructureEntry *newTodo=new StructureEntry(this, StructureEntry::SE_TODO);
			newTodo->title=s;
			newTodo->lineNumber=i;
			newTodo->lineHandle=document->line(i).handle();
			newTodo->parent=todoList;
			iter_todo.insert(newTodo);
		}
		//// Appendix keyword
		if (curLine=="\\appendix") {
			oldLine=mAppendixLine;
			mAppendixLine=document->line(i).handle();

		}
		if(document->line(i).handle()==mAppendixLine && curLine!="\\appendix"){
			oldLine=mAppendixLine;
			mAppendixLine=0;
		}
		//// beamer blocks ////
		s=findToken(curLine,"\\begin{block}{");
		if (s!="") {
			StructureEntry *newBlock=new StructureEntry(this, StructureEntry::SE_BLOCK);
			newBlock->title=s;
			newBlock->lineNumber=i;
			newBlock->lineHandle=document->line(i).handle();
			newBlock->parent=blockList;
			iter_block.insert(newBlock);
		}

		//// include,input ////
		static const QStringList inputTokens = QStringList() << "input" << "include";
		for(int header=0;header<inputTokens.count();header++){
			s=findToken(curLine,"\\"+inputTokens.at(header)+"{");
			if (s!="") {
				StructureEntry *newInclude=new StructureEntry(this,baseStructure, StructureEntry::SE_INCLUDE);
				newInclude->title=s;
//				newInclude.title=inputTokens.at(header); //texmaker distinguished include/input, doesn't seem necessary
				newInclude->lineNumber=i;
				newInclude->level=fileExits(s)? 0 : 1;
				newInclude->lineHandle=document->line(i).handle();
			}
		}//for
		//// all sections ////
		for(int header=0;header<LatexParser::structureCommands.count();header++){
			QRegExp regexp = QRegExp("\\"+LatexParser::structureCommands[header]+"\\*?[\\{\\[]");
			s=findToken(curLine,regexp);
			if (s!="") {
				bool reuse=false;
				s=extractSectionName(s);
				StructureEntry* parent=header == 0 ? baseStructure : parent_level[header];
				StructureEntry *newSection;
				if(MapOfElements.contains(dlh)){
				    newSection=MapOfElements.value(dlh);
				    parent->add(newSection);
				    newSection->type=StructureEntry::SE_SECTION;
				    toBeDeleted.remove(newSection);
				    MapOfElements.remove(dlh,newSection);
				    reuse=true;
				}else{
				    newSection=new StructureEntry(this,parent,StructureEntry::SE_SECTION);
				}
				if(mAppendixLine &&mAppendixLine->line()<i) newSection->appendix=true;
				else newSection->appendix=false;
				newSection->title=s;
				newSection->level=header;
				newSection->lineNumber=i;
				newSection->lineHandle=document->line(i).handle();
				if(header+1<parent_level.size()) parent_level[header+1]=newSection;
				for(int j=header+2;j<parent_level.size();j++)
					parent_level[j]=parent_level[header];

				if(!reuse) emit addElement(parent,parent->children.size()-1);
			}
		}
	}
	// append structure remainder ...
	for(int i=parent_level.size()-1;i>=0;i--){
		if (!parent_level[i]) break;
	    while(!remainingChildren[i].isEmpty() && remainingChildren[i].first()->level>i){
			se=remainingChildren[i].takeFirst();
			parent_level[se->level]->add(se);
	    }
	    parent_level[i]->children.append(remainingChildren[i]);
	    foreach(StructureEntry *elem,remainingChildren[i]){
		elem->parent=parent_level[i];
	    }
	}
	// purge unconnected elements
	foreach(se,toBeDeleted.keys()){
		emit removeElement(se,toBeDeleted[se]);
		delete se;
	}
	
	baseStructure->children.removeOne(bibTeXList);
	baseStructure->children.removeOne(labelList);
	baseStructure->children.removeOne(todoList);
	baseStructure->children.removeOne(blockList);
	if (!bibTeXList->children.isEmpty()) baseStructure->insert(0, bibTeXList);
	if (!todoList->children.isEmpty()) baseStructure->insert(0, todoList);
	if (!labelList->children.isEmpty()) baseStructure->insert(0, labelList);
	if (!blockList->children.isEmpty()) baseStructure->insert(0, blockList);

	//update appendix change
	if(oldLine!=mAppendixLine){
	    updateAppendix(oldLine,mAppendixLine);
	}

	emit structureUpdated(this);

	if (completerNeedsUpdate)
		emit updateCompleter();

}

/*
void LatexDocument::includeDocument(LatexDocument* includedDocument){
	includedDocument->deleteLater();
	if (texFiles.contains(includedDocument->fileName))
		return; //this should never happen

	texFiles.unite(includedDocument->texFiles);
	containedLabels.unite(includedDocument->containedLabels);
	containedReferences.unite(includedDocument->containedReferences);
	mentionedBibTeXFiles.unite(includedDocument->mentionedBibTeXFiles);
	allBibTeXIds.unite(includedDocument->allBibTeXIds);

}
*/
StructureEntry::StructureEntry(LatexDocument* doc, Type newType):type(newType),level(0), lineNumber(-1), lineHandle(0), parent(0), document(doc),appendix(false){
}
StructureEntry::StructureEntry(LatexDocument* doc, StructureEntry* parent, Type newType):type(newType),level(0), lineNumber(-1), lineHandle(0), document(doc),appendix(false){
	parent->add(this);
}
StructureEntry::~StructureEntry(){
	foreach (StructureEntry* se, children)
		delete se;
}
void StructureEntry::add(StructureEntry* child){
	Q_ASSERT(child!=0);
	children.append(child);
	child->parent=this;
}
void StructureEntry::insert(int pos, StructureEntry* child){
	Q_ASSERT(child!=0);
	children.insert(pos,child);
	child->parent=this;
}
int StructureEntry::getRealLineNumber(){
	if (document && document->getText() && document->getText()->line(lineNumber).handle() == lineHandle)
		return lineNumber; //return cached line number if it is still correct
	if (lineHandle) {
		int nr = QDocumentLine(lineHandle).lineNumber();
		if (nr>=0) {
			lineNumber=nr; //correct cached line number if necessary
			return nr;
		}
	}
	return lineNumber;
}

StructureEntryIterator::StructureEntryIterator(StructureEntry* entry){
	if (!entry) return;
	while (entry->parent){
		entryHierarchy.prepend(entry);
		indexHierarchy.prepend(entry->parent->children.indexOf(entry));
		entry=entry->parent;
	}
	entryHierarchy.prepend(entry);
	indexHierarchy.prepend(0);
}
bool StructureEntryIterator::hasNext(){
	return !entryHierarchy.isEmpty();
}
StructureEntry* StructureEntryIterator::next(){
	if (!hasNext()) return 0;
	StructureEntry* result=entryHierarchy.last();
	if (!result->children.isEmpty()) { //first child is next element, go a level deeper
		entryHierarchy.append(result->children.at(0));
		indexHierarchy.append(0);
	} else { //no child, go to next on same level
		entryHierarchy.removeLast();
		indexHierarchy.last()++;
		while (!entryHierarchy.isEmpty() && indexHierarchy.last()>=entryHierarchy.last()->children.size()) {
			//doesn't exists, proceed to travel upwards
			entryHierarchy.removeLast();
			indexHierarchy.removeLast();
			indexHierarchy.last()++;
		}
		if (!entryHierarchy.isEmpty())
			entryHierarchy.append(entryHierarchy.last()->children.at(indexHierarchy.last()));
	}
	return result;
}

LatexDocumentsModel::LatexDocumentsModel(LatexDocuments& docs):documents(docs),
	iconDocument(":/images/doc.png"), iconMasterDocument(":/images/masterdoc.png"), iconBibTeX(":/images/bibtex.png"), iconInclude(":/images/include.png"){
	mHighlightIndex=QModelIndex();
	iconSection.resize(LatexParser::structureCommands.count());
	for (int i=0;i<LatexParser::structureCommands.count();i++)
		iconSection[i]=QIcon(":/images/"+LatexParser::structureCommands[i].mid(1)+".png");
}
Qt::ItemFlags LatexDocumentsModel::flags ( const QModelIndex & index ) const{
	if (index.isValid()) return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
	else return 0;
}
QVariant LatexDocumentsModel::data ( const QModelIndex & index, int role) const{
	if (!index.isValid()) return QVariant();
	StructureEntry* entry = (StructureEntry*) index.internalPointer();
	if (!entry) return QVariant();
	switch (role) {
		case Qt::DisplayRole:
		if (entry->type==StructureEntry::SE_DOCUMENT_ROOT){ //show only base file name
				QString title=entry->title.mid(1+qMax(entry->title.lastIndexOf("/"), entry->title.lastIndexOf(QDir::separator())));
				if(title.isEmpty()) title="untitled";
				return QVariant(title);
			}
			//fall through to show full title in other cases
		case Qt::ToolTipRole:
			if (entry->lineNumber>-1)
				return QVariant(entry->title+QString(" (%1 %2)").arg(tr("Line")).arg(entry->getRealLineNumber()+1));
			else
				return QVariant(entry->title);
		case Qt::DecorationRole:
			switch (entry->type){
				case StructureEntry::SE_BIBTEX: return iconBibTeX;
				case StructureEntry::SE_INCLUDE: return iconInclude;
				case StructureEntry::SE_SECTION:
					if (entry->level>=0 && entry->level<iconSection.count())
						return iconSection[entry->level];
					else
						return QVariant();
				case StructureEntry::SE_DOCUMENT_ROOT:
					if (documents.masterDocument==entry->document)
						return iconMasterDocument;
					else
						return iconDocument;
				default: return QVariant();
			}
		case Qt::BackgroundRole:
			if (index==mHighlightIndex) return QVariant(Qt::lightGray);
			if (entry->appendix) return QVariant(QColor(200,230,200));
			else return QVariant();
		case Qt::ForegroundRole:
			if((entry->type==StructureEntry::SE_INCLUDE) && (entry->level==1)) {
				return QVariant(Qt::red);
			}else return QVariant();
		case Qt::FontRole:
			if(entry->type==StructureEntry::SE_DOCUMENT_ROOT) {
			    QFont f=QApplication::font();
				if(entry->document==documents.currentDocument) f.setBold(true);
				if(entry->title.isEmpty()) f.setItalic(true);
			    return QVariant(f);
			}
			return QVariant();
		default:
			return QVariant();
	}
}
QVariant LatexDocumentsModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	Q_UNUSED(orientation);
	if (section!=0) return QVariant();
	if (role!=Qt::DisplayRole) return QVariant();
	return QVariant("Structure");
}
int LatexDocumentsModel::rowCount ( const QModelIndex & parent ) const{
	if (!parent.isValid()) return documents.documents.count();
	else {
		StructureEntry* entry = (StructureEntry*) parent.internalPointer();
		if (!entry) return 0;
		return entry->children.size();
	}
}
int LatexDocumentsModel::columnCount ( const QModelIndex & parent ) const{
	Q_UNUSED(parent);
	return 1;
}
QModelIndex LatexDocumentsModel::index ( int row, int column, const QModelIndex & parent ) const{
	if (column!=0) return QModelIndex(); //one column
	if (row<0) return QModelIndex(); //shouldn't happen
	if (parent.isValid()) {
		const StructureEntry* entry = (StructureEntry*) parent.internalPointer();
		if (!entry) return QModelIndex(); //should never happen
		if (row>=entry->children.size()) return QModelIndex(); //shouldn't happen in a correct view
		return createIndex(row,column, entry->children.at(row));
	} else {
		if (row>=documents.documents.size()) return QModelIndex();
		return createIndex(row, column, documents.documents.at(row)->baseStructure);
	}
}
QModelIndex LatexDocumentsModel::index ( StructureEntry* entry ) const{
	if (!entry) return QModelIndex();
	if (entry->parent==0 && entry->type==StructureEntry::SE_DOCUMENT_ROOT) {
		int row=documents.documents.indexOf(entry->document);
		if (row<0) return QModelIndex();
		return createIndex(row, 0, entry);
	} else if (entry->parent!=0 && entry->type!=StructureEntry::SE_DOCUMENT_ROOT) {
		int row=entry->parent->children.indexOf(entry);
		if (row<0) return QModelIndex(); //shouldn't happen
		return createIndex(row, 0, entry);
	} else return QModelIndex(); //shouldn't happen
}
QModelIndex LatexDocumentsModel::parent ( const QModelIndex & index ) const{
	if (!index.isValid()) return QModelIndex();
	const StructureEntry* entry = (StructureEntry*) index.internalPointer();
	if (!entry) return QModelIndex();
	if (!entry->parent) return QModelIndex();
	if(entry->level>LatexParser::structureCommands.count()){
		qDebug("Structure broken!");
		return QModelIndex();
	}
	if(entry->parent->level>LatexParser::structureCommands.count()){
		qDebug("Structure broken!");
		return QModelIndex();
	}
	if (entry->parent->parent)
		return createIndex(entry->parent->parent->children.indexOf(entry->parent), 0, entry->parent);
	else {
		for (int i=0; i < documents.documents.count(); i++)
			if (documents.documents.at(i)->baseStructure==entry->parent)
				return createIndex(i, 0, entry->parent);
		return QModelIndex();
	}
}

StructureEntry* LatexDocumentsModel::indexToStructureEntry(const QModelIndex & index ){
	if (!index.isValid()) return 0;
	StructureEntry* result=(StructureEntry*)index.internalPointer();
	if (!result || !result->document) return 0;
	return result;
}
QModelIndex LatexDocumentsModel::highlightedEntry(){
	return mHighlightIndex;
}
void LatexDocumentsModel::setHighlightedEntry(StructureEntry* entry){

	QModelIndex i1=mHighlightIndex;
	QModelIndex i2=index(entry);
	if (i1==i2) return;
	emit dataChanged(i1,i1);
	mHighlightIndex=i2;
	emit dataChanged(i2,i2);
}

void LatexDocumentsModel::resetAll(){
	mHighlightIndex=QModelIndex();
	reset();
}

void LatexDocumentsModel::structureUpdated(LatexDocument* document){
	Q_UNUSED(document);
	//resetAll();
	mHighlightIndex=QModelIndex();
	emit layoutChanged();
}
void LatexDocumentsModel::structureLost(LatexDocument* document){
	Q_UNUSED(document);
	resetAll();
}

void LatexDocumentsModel::removeElement(StructureEntry *se,int row){
	StructureEntry *par_se=se->parent;
	removeRow(row,index(par_se));
}

void LatexDocumentsModel::addElement(StructureEntry *se,int row){
	insertRow(row,index(se));
}
void LatexDocumentsModel::updateElement(StructureEntry *se){
    emit dataChanged(index(se),index(se));
}

LatexDocuments::LatexDocuments(): model(new LatexDocumentsModel(*this)), masterDocument(0), currentDocument(0), bibTeXFilesModified(false),Label(0),Ref(0){
}
LatexDocuments::~LatexDocuments(){
	delete model;
	delete Label;
	delete Ref;
}
void LatexDocuments::addDocument(LatexDocument* document){
	documents.append(document);
	model->connect(document,SIGNAL(structureLost(LatexDocument*)),model,SLOT(structureLost(LatexDocument*)));
	model->connect(document,SIGNAL(structureUpdated(LatexDocument*)),model,SLOT(structureUpdated(LatexDocument*)));
	model->connect(document,SIGNAL(removeElement(StructureEntry*,int)),model,SLOT(removeElement(StructureEntry*,int)));
	model->connect(document,SIGNAL(addElement(StructureEntry*,int)),model,SLOT(addElement(StructureEntry*,int)));
	model->connect(document,SIGNAL(updateElement(StructureEntry*)),model,SLOT(updateElement(StructureEntry*)));
	document->parent=this;
	if(masterDocument){
		if(Ref && Label){
			LatexEditorView *edView=document->getEditorView();
			if (edView) edView->setReferenceDatabase(Ref,Label);
		}
		// repaint all docs
		foreach(LatexDocument *doc,documents){
			LatexEditorView *edView=doc->getEditorView();
			if (edView) edView->documentContentChanged(0,edView->editor->document()->lines());
		}
	}
	model->structureUpdated(document);
}
void LatexDocuments::deleteDocument(LatexDocument* document){
	LatexEditorView *view=document->getEditorView();
	if (document!=masterDocument) {
		documents.removeAll(document);
		model->resetAll();
		if(masterDocument){
			Label->purgeLinksTo(view->editor->document());
			Ref->purgeLinksTo(view->editor->document());
		}
		if (document==currentDocument)
			currentDocument=0;
		delete document;
		if (view) delete view;
	} else {
		document->setFileName(document->getFileName());
		model->resetAll();
		document->clearAppendix();
		view->purgeLinksTo(view->editor->document()); // unsatisfying work around of crash ...
		if (view) delete view;
		if (document==currentDocument)
			currentDocument=0;
	}
}
void LatexDocuments::setMasterDocument(LatexDocument* document){
	if (document==masterDocument) return;
	if (masterDocument!=0 && masterDocument->getEditorView()==0){
		documents.removeAll(masterDocument);
		delete masterDocument;
	}
	masterDocument=document;
	if (masterDocument!=0) {
		documents.removeAll(masterDocument);
		documents.prepend(masterDocument);
		// set Ref/Labeldatabase to common database
		LatexEditorView *edView=masterDocument->getEditorView();
		Q_ASSERT(edView);
		edView->getReferenceDatabase(Ref,Label);
		Ref->numberOfViews++;
		Label->numberOfViews++;
		foreach(LatexDocument *doc,documents){
			if(doc!=masterDocument){
				edView=doc->getEditorView();
				if (edView) edView->setReferenceDatabase(Ref,Label);
				//edView->editor->document()->markFormatCacheDirty();
			}
		}
		// repaint doc
		foreach(LatexDocument *doc,documents){
			edView=doc->getEditorView();
			if (edView) edView->documentContentChanged(0,edView->editor->document()->lines());
		}
	}else{
		if(documents.size()>0){
			foreach(LatexDocument *doc,documents){
				LatexEditorView *edView=doc->getEditorView();
				if (edView) edView->resetReferenceDatabase();
			}
			delete Label;
			delete Ref;
			Label=0;
			Ref=0;
		}
	}
	model->resetAll();
}

QString LatexDocuments::getCurrentFileName() {
	if (!currentDocument) return "";
	return currentDocument->getFileName();
}
QString LatexDocuments::getCompileFileName(){
	if (!masterDocument) return getCurrentFileName();
	else return masterDocument->getFileName();
}
QString LatexDocuments::getAbsoluteFilePath(const QString & relName, const QString &extension){
	QString s=relName;
	if (!s.endsWith(extension,Qt::CaseInsensitive)) s+=extension;
	QFileInfo fi(s);
	if (!fi.isRelative()) return s;
	QString compileFileName=getCompileFileName();
	if (compileFileName.isEmpty()) return s; //what else can we do?
	QString compilePath=QFileInfo(compileFileName).absolutePath();
	if (!compilePath.endsWith("\\") && !compilePath.endsWith("/"))
		compilePath+=QDir::separator();
	return  compilePath+s;
}

LatexDocument* LatexDocuments::findDocument(const QDocument *qDoc){
	foreach(LatexDocument *doc,documents){
		LatexEditorView *edView=doc->getEditorView();
		if(edView && edView->editor->document()==qDoc) return doc;
	}
	return 0;
}

LatexDocument* LatexDocuments::findDocument(const QString& fileName){
	if (fileName=="") return 0;
	QString fnorm = fileName;
	fnorm.replace("/",QDir::separator()).replace("\\",QDir::separator());
	//fast check for absolute file names
#ifdef Q_WS_WIN
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
#else
	Qt::CaseSensitivity cs = Qt::CaseSensitive;
#endif
	foreach (LatexDocument* document, documents)
		if (document->getFileName().compare(fnorm,cs)==0)
			return document;

	//check for relative file names
	QFileInfo fi(getAbsoluteFilePath(fileName));
	if (!fi.exists()) {
		if (QFileInfo(getAbsoluteFilePath(fileName),".tex").exists())
			fi=QFileInfo(getAbsoluteFilePath(fileName),".tex");
		else if (QFileInfo(getAbsoluteFilePath(fileName),".bib").exists())
			fi=QFileInfo(getAbsoluteFilePath(fileName),".bib");
		else return 0;
	}
	//check for same file infos (is not reliable in qt < 4.5, because they just compare absoluteFilePath)
	foreach (LatexDocument* document, documents)
		if (document->getFileInfo().exists() && document->getFileInfo()==fi)
			return document;

	//check for canonical file path (unnecessary in qt 4.5)
	fnorm = fi.canonicalFilePath();
	foreach (LatexDocument* document, documents)
		if (document->getFileInfo().canonicalFilePath().compare(fnorm,cs)==0)
			return document;

	return 0;
}
void LatexDocuments::settingsRead(){
	model->iconSection.resize(LatexParser::structureCommands.count());
	for (int i=0;i<LatexParser::structureCommands.count();i++)
		model->iconSection[i]=QIcon(":/images/"+LatexParser::structureCommands[i].mid(1)+".png");
}


void LatexDocuments::updateBibFiles(){
	mentionedBibTeXFiles.clear();
	foreach (const LatexDocument* doc, documents)
		mentionedBibTeXFiles.append(doc->mentionedBibTeXFiles());

	bool changed=false;
	for (int i=0; i<mentionedBibTeXFiles.count();i++){
		mentionedBibTeXFiles[i]=getAbsoluteFilePath(mentionedBibTeXFiles[i],".bib").replace(QDir::separator(), "/"); //store absolute
		QString &fileName=mentionedBibTeXFiles[i];
		QFileInfo fi(fileName);
		if (!fi.isReadable()) continue; //ups...
		if (!bibTeXFiles.contains(fileName))
			bibTeXFiles.insert(fileName,BibTeXFileInfo());
		BibTeXFileInfo& bibTex=bibTeXFiles[mentionedBibTeXFiles[i]];
		changed=changed|bibTex.loadIfModified(fileName);
		if (bibTex.ids.empty() && !bibTex.linksTo.isEmpty())
			//handle obscure bib tex feature, a just line containing "link fileName"
			mentionedBibTeXFiles.append(bibTex.linksTo);
	}
	if (changed) {
		allBibTeXIds.clear();
		for (QMap<QString, BibTeXFileInfo>::const_iterator it=bibTeXFiles.constBegin(); it!=bibTeXFiles.constEnd();++it)
			foreach (const QString& s, it.value().ids)
				allBibTeXIds << s;
		for (int i=0;i<documents.size();i++)
			if (documents[i]->getEditorView())
				documents[i]->getEditorView()->setBibTeXIds(&allBibTeXIds);
		bibTeXFilesModified=true;
	}
}

void LatexDocument::findStructureEntryBefore(QMutableListIterator<StructureEntry*> &iter,int linenr,int count){
    bool goBack=false;
	int l=0;
    while(iter.hasNext()){
		StructureEntry* se=iter.next();
		QDocumentLineHandle* dlh=se->lineHandle;
		if((dlh->line()>=linenr) && (dlh->line()<linenr+count) ){
			iter.remove();
			removeElement(se,l);
			delete se;
			l--;
		}
		if(dlh->line()>=linenr+count) {
			goBack=true;
			break;
		}
		l++;
    }
    if(goBack && iter.hasPrevious()) iter.previous();
}

void LatexDocument::splitStructure(StructureEntry* se,QVector<StructureEntry*> &parent_level,QVector<QList<StructureEntry*> > &remainingChildren,QMap<StructureEntry*,int> &toBeDeleted,QMultiHash<QDocumentLineHandle*,StructureEntry*> &MapOfElements,int linenr,int count,int lvl,bool front,bool back){
	if (!se) return;

	if(front){
		for(int k=lvl;k<parent_level.size();k++){
			parent_level[k]=se;
		}
	}

	if(se->children.empty()) return;

	StructureEntry* parent=se;

	if(lvl>=parent_level.size()) return;

	// determine range of structure entry which encompass the to be updated region
	int start=-1;
	int end=-1;
	for(int l=0;l<se->children.size();l++){
		StructureEntry *elem=se->children.at(l);
		if(!elem->lineHandle || elem->lineHandle->line()<linenr) {
			start=l;
			continue;
		}
		if(elem->lineHandle->line()>=linenr+count){
			end=l;
			break;
		}
	}

	if(start>-1){
		StructureEntry *elem=se->children.at(start);
		if(elem->type==StructureEntry::SE_SECTION){
			for(;lvl<elem->level;++lvl){
				parent_level[lvl+1]=parent;
			}
		}
	}

	// store remainder of children
	if(back && (end>-1))
		remainingChildren[lvl].append(se->children.mid(end));
	// get StructureEntry to look deeper in
	StructureEntry *next=0;
	if(end>0) {
		next=se->children.value(end-1,0);// needs changing
		if(next && next->type!=StructureEntry::SE_SECTION) next=0;
		parent=se->children.value(start,parent_level[lvl]);
		if(parent->type!=StructureEntry::SE_SECTION) parent=parent_level[lvl];
	}
	if(end<0){
		next=se->children.value(se->children.size()-1,0);// needs changing
		if(next && next->type!=StructureEntry::SE_SECTION) next=0;
		parent=next;
		if(!parent) parent=parent_level[lvl];
		if(parent->type!=StructureEntry::SE_SECTION) parent=parent_level[lvl];
	}

	// add elements which are deleted later to a list
	if(end-1>start) {
		toBeDeleted.insert(se->children[end-1],end-1);
		MapOfElements.insert(se->children[end-1]->lineHandle,se->children[end-1]);
	}
	//delete elements which are completely embedded in the to be updated region
	int tmp_end=end;
	if(tmp_end<0 && start>-1) tmp_end=se->children.size()+1;
	for(int l=start+1;l<tmp_end-1;l++) {
		toBeDeleted.insert(se->children[l],l);
		MapOfElements.insert(se->children[l]->lineHandle,se->children[l]);
		//delete se->children[l];
	}

	int tmp=se->children.size();
	for(int l=start+1;l<tmp;l++) {
		se->children.removeAt(start+1);
	}

	// take a look a children
	bool newFront=start>-1;
	if(newFront && end-start==1)
		splitStructure(next,parent_level,remainingChildren,toBeDeleted,MapOfElements,linenr,count,lvl+1);
	else{
		if(newFront && (se->children[start]->type==StructureEntry::SE_SECTION)) splitStructure(se->children[start],parent_level,remainingChildren,toBeDeleted,MapOfElements,linenr,count,lvl+1,newFront,false);
		int next_level= next ? next->level+1 : lvl;
		splitStructure(next,parent_level,remainingChildren,toBeDeleted,MapOfElements,linenr,count,next_level,false,true);
	}

}

void LatexDocument::updateAppendix(QDocumentLineHandle *oldLine,QDocumentLineHandle *newLine){
    int endLine=-1;
    int startLine=-1;
    if(newLine) endLine=newLine->line();
    if(oldLine){
	startLine=oldLine->line();
	if(endLine<0 || endLine>startLine){
	    // remove appendic marker
	    StructureEntry *se=baseStructure;
	    setAppendix(se,startLine,endLine,false);
	}
    }

    if(endLine>-1 && (endLine<startLine || startLine<0)){
	StructureEntry *se=baseStructure;
	setAppendix(se,endLine,startLine,true);
    }
}

void LatexDocument::setAppendix(StructureEntry *se,int startLine,int endLine,bool state){
    bool first=false;
    for(int i=0;i<se->children.size();i++){
	StructureEntry *elem=se->children[i];
	if(endLine>=0 && elem->lineHandle && elem->lineHandle->line()>endLine) break;
	if(elem->type==StructureEntry::SE_SECTION && elem->lineHandle->line()>startLine){
	    if(!first && i>0) setAppendix(se->children[i-1],startLine,endLine,state);
	    elem->appendix=state;
	    emit updateElement(elem);
	    setAppendix(se->children[i],startLine,endLine,state);
	    first=true;
	}
    }
    if(!first && !se->children.isEmpty()) {
	StructureEntry *elem=se->children.last();
	if(elem->type==StructureEntry::SE_SECTION) setAppendix(elem,startLine,endLine,state);
    }
}

bool LatexDocument::fileExits(QString fname){
	QString curPath=ensureTrailingDirSeparator(getFileInfo().absolutePath());
	bool exist=QFile(parent->getAbsoluteFilePath(fname,".tex")).exists();
	if (!exist) exist=QFile(parent->getAbsoluteFilePath(curPath+fname,".tex")).exists();
	return exist;
}


void LatexDocuments::updateStructure(){
    foreach(LatexDocument* doc,documents){
	model->updateElement(doc->baseStructure);
    }
}

