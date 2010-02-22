#include "latexdocument.h"
#include "latexeditorview.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"
#include "qeditor.h"
#include "smallUsefulFunctions.h"

LatexDocument::LatexDocument():edView(0),text(0)
{
	baseStructure = new StructureEntry(this,StructureEntry::SE_DOCUMENT_ROOT);
	labelList = new StructureEntry(this,baseStructure, StructureEntry::SE_OVERVIEW);
	todoList = new StructureEntry(this,baseStructure, StructureEntry::SE_OVERVIEW);
	bibTeXList = new StructureEntry(this,baseStructure, StructureEntry::SE_OVERVIEW);
        labelItem.clear();
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
}
LatexEditorView *LatexDocument::getEditorView(){
	return this->edView;
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
    userCommandList.clear();
    labelItem.clear();
    mentionedBibTeXFiles.clear();

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

	userCommandList.clear();
	labelItem.clear();
	mentionedBibTeXFiles.clear();

	emit structureLost(this);

	delete baseStructure;
	baseStructure=0;

	baseStructure = new StructureEntry(this,StructureEntry::SE_DOCUMENT_ROOT);
	baseStructure->title=fileName;
	labelList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	labelList->title=tr("LABELS");
	todoList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	todoList->title=tr("TODO");
	bibTeXList = new StructureEntry(this,StructureEntry::SE_OVERVIEW);
	bibTeXList->title=tr("BIBTEX");

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
				userCommandList.append(name);
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
				userCommandList.append("\\end{"+name);
				for (int j=0; j<options; j++) {
					if (j==0) name.append("{%<1%|%>}");
					else name.append(QString("{%<%1%>}").arg(j+1));
				}
				userCommandList.append(name);
				userCommandList.append("\\begin{"+name);
			}
		}
		//// newtheorem ////
		QString s=findToken(curLine,"\\newtheorem{");
		if (s!="") {
			userCommandList.append("\\begin{"+s+"}");
			userCommandList.append("\\end{"+s+"}");
		}
		//// bibliography ////
		s=findToken(curLine,"\\bibliography{");
		if (s!="") {
			QStringList bibs=s.split(',',QString::SkipEmptyParts);
			mentionedBibTeXFiles<<bibs;
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
			labelItem.append(s);
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
		//// include,input ////
		static const QStringList inputTokens = QStringList() << "input" << "include";
		for(int header=0;header<inputTokens.count();header++){
			s=findToken(curLine,"\\"+inputTokens.at(header)+"{");
			if (s!="") {
				StructureEntry *newInclude=new StructureEntry(this,baseStructure, StructureEntry::SE_INCLUDE);
				newInclude->title=s;
//				newInclude.title=inputTokens.at(header); //texmaker distinguished include/input, doesn't seem necessary
				newInclude->lineNumber=i;
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
				if (!temporaryLoadedDocument)
					newSection->lineHandle=document->line(i).handle();
				parent_level[header]=newSection;
				for(int j=header+1;j<parent_level.size();j++)
					parent_level[j]=parent_level[header];
			}
		}
	}

	if (!bibTeXList->children.isEmpty()) baseStructure->insert(0, bibTeXList);
	if (!todoList->children.isEmpty()) baseStructure->insert(0, todoList);
	if (!labelList->children.isEmpty()) baseStructure->insert(0, labelList);

	emit structureUpdated(this);

	if (temporaryLoadedDocument)
		delete document;
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
StructureEntry::StructureEntry(LatexDocument* doc, Type newType):type(newType), lineNumber(-1), lineHandle(0), parent(0), document(doc){
}
StructureEntry::StructureEntry(LatexDocument* doc, StructureEntry* parent, Type newType):type(newType), lineNumber(-1), lineHandle(0), document(doc){
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
int StructureEntry::getRealLineNumber() const{
	if (lineHandle) {
		int nr = QDocumentLine(lineHandle).lineNumber();
		if (nr>=0) return nr;
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
	iconDocument(":/images/doc.png"), iconMasterDocument(":/images/masterdoc.png"), iconBibTeX(":/images/bibtex.png"), iconInclude(":/images/include.png"),mHighlightedEntry(0){
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
			if (entry->type==StructureEntry::SE_DOCUMENT_ROOT) //show only base file name
				return QVariant(entry->title.mid(1+qMax(entry->title.lastIndexOf("/"), entry->title.lastIndexOf(QDir::separator()))));
			//fall through to show full title in other cases
		case Qt::ToolTipRole:
			if (entry->lineNumber>-1)
				return QVariant(entry->title+QString(" (%1 %2)").arg(tr("Line")).arg(entry->lineNumber+1));
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
			if (entry==mHighlightedEntry) return QVariant(Qt::lightGray);
			else return QVariant();
		default:
			return QVariant();
	}
}
QVariant LatexDocumentsModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
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
StructureEntry* LatexDocumentsModel::highlightedEntry(){
	return mHighlightedEntry;
}
void LatexDocumentsModel::setHighlightedEntry(StructureEntry* entry){
	if (mHighlightedEntry==entry) return;
	QModelIndex i1=index(mHighlightedEntry);
	QModelIndex i2=index(entry);
	emit dataChanged(i1,i1);
	mHighlightedEntry=entry;
	emit dataChanged(i2,i2);
}

void LatexDocumentsModel::resetAll(){
	mHighlightedEntry=0;
	reset();
}

void LatexDocumentsModel::structureUpdated(LatexDocument* document){
	resetAll();
}
void LatexDocumentsModel::structureLost(LatexDocument* document){
	resetAll();
}



LatexDocuments::LatexDocuments(): model(new LatexDocumentsModel(*this)), masterDocument(0), currentDocument(0), bibTeXFilesModified(false){
}
LatexDocuments::~LatexDocuments(){
	delete model;
}
void LatexDocuments::addDocument(LatexDocument* document){
	documents.append(document);
	model->connect(document,SIGNAL(structureLost(LatexDocument*)),model,SLOT(structureLost(LatexDocument*)));
	model->connect(document,SIGNAL(structureUpdated(LatexDocument*)),model,SLOT(structureUpdated(LatexDocument*)));
}
void LatexDocuments::deleteDocument(LatexDocument* document){
	if (document->getEditorView()) delete document->getEditorView();
	if (document!=masterDocument) {
		documents.removeAll(document);
		delete document;
		model->resetAll();
		if (document==currentDocument)
			currentDocument=0;
	} else document->setFileName(document->getFileName());
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
		mentionedBibTeXFiles.append(doc->mentionedBibTeXFiles);

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
