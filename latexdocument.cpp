#include "latexdocument.h"
#include "latexeditorview.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "smallUsefulFunctions.h"

QStringList struct_level = QStringList() << "part" << "chapter" << "section" << "subsection" << "subsubsection"; //TODO

LatexDocument::LatexDocument()
{
	baseStructure = new StructureEntry(StructureEntry::SE_DOCUMENT_ROOT);
	labelList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
	todoList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
	bibTeXList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
        labelItem.clear();
}
LatexDocument::~LatexDocument(){
	delete baseStructure;
}
void LatexDocument::updateStructure() {

	QDocument* document=edView->editor->document();//TODO

	userCommandList.clear();
        labelItem.clear();

	delete baseStructure;
	baseStructure = new StructureEntry(StructureEntry::SE_DOCUMENT_ROOT);
	baseStructure->title=edView->editor->fileName();
	labelList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
	labelList->title=tr("LABELS");
	todoList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
	todoList->title=tr("TODO");
	bibTeXList = new StructureEntry(baseStructure, StructureEntry::SE_OVERVIEW);
	bibTeXList->title=tr("BIBTEX");

	QVector<StructureEntry*> parent_level(struct_level.count());
	for (int i=0;i<parent_level.size();i++)
		parent_level[i]=baseStructure;

	//TODO: Use a cache to prevent reparsing (especially important for mastermode, where more structures are shown) (perhaps it makes sense to show the structure of every open file)
	//TODO: This assumes one command per line, which is not necessary true
	//TODO: Move this in a latex parser class
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
			//TODO: mentionedBibTeXFiles<<bibs;
			foreach (const QString& bibFile, bibs) {
				StructureEntry *newFile=new StructureEntry(bibTeXList, StructureEntry::SE_BIBTEX);
				newFile->title=bibFile;
				newFile->lineNumber=i;
				newFile->lineHandle=document->line(i).handle();
			}
		}
		//// label ////
		//TODO: Use label from dynamical reference checker
		s=findToken(curLine,"\\label{");
		if (s!="") {
			labelItem.append(s);
			StructureEntry *newLabel=new StructureEntry(labelList, StructureEntry::SE_LABEL);
			newLabel->title=s;
			newLabel->lineNumber=i;
			newLabel->lineHandle=document->line(i).handle();
		}
		//// TODO marker
		s=curLine;
		int l=s.indexOf("%TODO");
		if (l>=0) {
			s=s.mid(l+6,s.length());
			StructureEntry *newTodo=new StructureEntry(todoList, StructureEntry::SE_TODO);
			newTodo->title=s;
			newTodo->lineNumber=i;
			newTodo->lineHandle=document->line(i).handle();
		}
		//// include,input ////
		static const QStringList inputTokens = QStringList() << "input" << "include";
		for(int header=0;header<inputTokens.count();header++){
			s=findToken(curLine,"\\"+inputTokens.at(header)+"{");
			if (s!="") {
				StructureEntry *newInclude=new StructureEntry(baseStructure, StructureEntry::SE_INCLUDE);
				newInclude->title=s;
//				newInclude.title=inputTokens.at(header); //texmaker distinguished include/input, doesn't seem necessary
				newInclude->lineNumber=i;
				newInclude->lineHandle=document->line(i).handle();
			}
		}//for
		//// all sections ////
		for(int header=0;header<struct_level.count();header++){
			QRegExp regexp = QRegExp("\\\\"+struct_level[header]+"\\*?[\\{\\[]");
			s=findToken(curLine,regexp);
			if (s!="") {
				s=extractSectionName(s);
				StructureEntry* parent=header == 0 ? baseStructure : parent_level[header-1];
				StructureEntry *newSection=new StructureEntry(parent,StructureEntry::SE_SECTION);
				newSection->title=s;
				newSection->level=header;
				newSection->lineNumber=i;
				newSection->lineHandle=document->line(i).handle();
				parent_level[header]=newSection;
				for(int j=header+1;j<parent_level.size();j++)
					parent_level[j]=parent_level[header];
			}
		}
	}
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
StructureEntry::StructureEntry(Type newType):type(newType), lineNumber(-1), lineHandle(0), parent(0){
}
StructureEntry::StructureEntry(StructureEntry* parent, Type newType):type(newType), lineNumber(-1), lineHandle(0){
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

/*
  QIcon(":/images/doc.png"));
  static const QIcon structureBibTeXIcon(":/images/bibtex.png");
				Child->setIcon(0,QIcon(":/images/include.png"));
				parent_level[header]->setIcon(0,);
*/

LatexDocumentsModel::LatexDocumentsModel(LatexDocuments& docs):documents(docs),
	iconDocument(":/images/doc.png"), iconBibTeX(":/images/bibtex.png"), iconInclude(":/images/include.png"){
	iconSection.resize(struct_level.count());
	for (int i=0;i<struct_level.count();i++)
		iconSection[i]=QIcon(":/images/"+struct_level[i]+".png");
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
		case Qt::DisplayRole: case Qt::ToolTipRole:
			if (entry->lineNumber>-1)
				return QVariant(entry->title+QString(" (%1 %2)").arg(tr("Zeile")).arg(entry->lineNumber+1));
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
					return iconDocument;
				default: return QVariant();
			}
		default:
			return QVariant();
	}
}
QVariant LatexDocumentsModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	if (section!=0) return QVariant();
	if (role!=Qt::DisplayRole) return QVariant();
	return QVariant("Structure (experimental)");
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


LatexDocuments::LatexDocuments(): model(new LatexDocumentsModel(*this)){
}
LatexDocuments::~LatexDocuments(){
	delete model;
}
void LatexDocuments::deleteDocument(LatexDocument* document){
	documents.removeAll(document);
	if (document->edView) delete document->edView;
	delete document;
	model->reset();
}

