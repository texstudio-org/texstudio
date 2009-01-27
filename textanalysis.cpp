#include "textanalysis.h"
#include "qdocumentline.h"
#include "latexeditorview.h"
//#include <QMessageBox>
Word::Word (QString nw, int nc){
  word=nw;
  count=nc;
}
bool Word::operator<(const  Word &cmpTo) const{
    if (count > cmpTo.count) return true;
    else if (count < cmpTo.count) return false;
    else return word.localeAwareCompare(cmpTo.word)<0;
}

int TextAnalysisModel::rowCount ( const QModelIndex & parent ) const{
    if (parent.isValid()) return 0;
    else return words.size();
}
bool TextAnalysisModel::hasChildren ( const QModelIndex & parent) const {
    return !parent.isValid();
}
QVariant TextAnalysisModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid() || (index.parent().isValid()))
        return QVariant();

    if (index.row() >= words.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column()==0) return words[index.row()].word;
        else if (index.column()==1)  return words[index.row()].count;
        else if (index.column()==2 && wordCount>0)  return QString::number(words[index.row()].count*relativeProzentMultipler,'g',3)+" %";
    }
    return QVariant();
}
QVariant TextAnalysisModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
         return QVariant();

    if (orientation != Qt::Horizontal) return QString::number(section);
    else if (section == 0) return QString("word");
    else if (section == 1) return QString("count");
    else if (section == 2) return QString("count relative");
}
int TextAnalysisModel::columnCount ( const QModelIndex & parent) const {
  return 3;
}
void TextAnalysisModel::updateAll(){
    wordCount=0;
    characterInWords=0;
    for (int i=0;i<words.size();i++) {
      wordCount+=words[i].count;
      characterInWords+=words[i].count*words[i].word.size();
    }
    qSort(words);
    if (words.size()>0) relativeProzentMultipler=100.0/words[0].count;
    else relativeProzentMultipler=0;
    //emit dataChanged?
}

TextAnalysisDialog::TextAnalysisDialog( QWidget* parent,  QString name)
    : QDialog( parent)
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);

ui.resultView->setWordWrap (false);
//connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));


document=0;

  connect(ui.countButton, SIGNAL(clicked()), SLOT(slotCount()) );
  connect(ui.closeButton, SIGNAL(clicked()), SLOT(slotClose()) );
}

TextAnalysisDialog::~TextAnalysisDialog()
{
}

void TextAnalysisDialog::setData(const QDocument* doc, const QDocumentCursor &cur){
    document=doc;
    cursor=cur;
}

void TextAnalysisDialog::interpretStructureTree(QTreeWidgetItem *item){
    if (item->text(1)==QString("chapter")) {
        chapters.append(QPair<QString,int> (item->text(0), item->text(3).toUInt()));
        ui.comboBox->addItem(item->text(0));
    } else for (int i=0;i<item->childCount();i++)
        interpretStructureTree(item->child(i));
}

void TextAnalysisDialog::init()
{
    alreadyCount=false;
    chapters.clear();
}

void TextAnalysisDialog::needCount(){
    if (alreadyCount) return;
    int totalLines=document->lines();
    int textLines=0;
    int commentLines=0;
    mapText.resize(2+chapters.size());
    mapComment.resize(2+chapters.size());
    mapCommand.resize(2+chapters.size());

    int selectionStartLine=-1;
    int selectionEndLine=-1;
    int selectionStartIndex;
    int selectionEndIndex;
    if (cursor.hasSelection()){
        QDocumentSelection sel = cursor.selection();
        selectionStartLine=sel.startLine;
        selectionEndLine=sel.endLine;
        selectionStartIndex=sel.start;
        selectionEndIndex=sel.end;
        if (selectionStartLine>selectionEndLine) {
            int temp=selectionStartLine;selectionStartLine=selectionEndLine;selectionEndLine=temp;
            temp=selectionStartIndex;selectionStartIndex=selectionEndIndex;selectionEndIndex=temp;
        } else if (selectionStartLine == selectionEndLine && selectionStartIndex>selectionEndIndex) {
            int temp=selectionStartIndex;selectionStartIndex=selectionEndIndex;selectionEndIndex=temp;
        }
    }

    int nextChapter=0;
    int extraMap=0;
    for (int l=0;l<document->lines();l++){
        if (nextChapter<chapters.size() && l+1>=chapters[nextChapter].second) {
            if (nextChapter==0) extraMap=2;
            else extraMap++;
            nextChapter++;
            if (extraMap>=mapText.size()) extraMap=0;
        }
        QString line=document->line(l).text();
        bool commentReached=false;
        int nextIndex=0;
        int wordStartIndex;
        bool lineCountedAsText=false;        
        QString curWord;
        int state;
        while ((state=LatexEditorView::nextWord(line,nextIndex,curWord,wordStartIndex,LatexEditorView::NW_TEXT|LatexEditorView::NW_COMMENT|LatexEditorView::NW_COMMAND))!=LatexEditorView::NW_NOTHING){
            bool inSelection;
            if (selectionStartLine!=selectionEndLine) 
                inSelection=((l<selectionEndLine) && (l>selectionStartLine)) ||
                            ((l==selectionStartLine) && (nextIndex>selectionStartIndex)) ||
                            ((l==selectionEndLine) && (wordStartIndex<=selectionEndIndex));
             else 
                inSelection=(l==selectionStartLine) && (nextIndex>selectionStartIndex) && (wordStartIndex<=selectionEndIndex);
            curWord=curWord.toLower();
            if (state & LatexEditorView::NW_COMMENT || commentReached) {
                mapComment[0][curWord]=mapComment[0][curWord]+1;
                if (inSelection) mapComment[1][curWord]=mapComment[1][curWord]+1;
                if (extraMap!=0) mapComment[extraMap][curWord]=mapComment[extraMap][curWord]+1;
                if (!commentReached){
                    commentReached=true;
                    commentLines++;
                }
            } else if (state&LatexEditorView::NW_COMMAND) {
                mapCommand[0][curWord]=mapCommand[0][curWord]+1;
                if (inSelection) mapCommand[1][curWord]=mapCommand[1][curWord]+1;
                if (extraMap!=0) mapCommand[extraMap][curWord]=mapCommand[extraMap][curWord]+1;
            } else if (state&LatexEditorView::NW_TEXT){
                mapText[0][curWord]=mapText[0][curWord]+1;
                if (inSelection) mapText[1][curWord]=mapText[1][curWord]+1;
                if (extraMap!=0) mapText[extraMap][curWord]=mapText[extraMap][curWord]+1;
                if (!lineCountedAsText) {
                    textLines++;
                    lineCountedAsText=true;
                }
            }
        };
    }
    
    alreadyCount=true;

    ui.totalLinesLabel->setText(QString::number(totalLines));
    ui.textLinesLabel->setText(QString::number(textLines));
    ui.commentLinesLabel->setText(QString::number(commentLines));
}

void TextAnalysisDialog::insertDisplayData(const QMap<QString,int> & map){
    int minLen=0;
    if (ui.minWordLenCheck->isChecked()) minLen=ui.smallWordsSpin->value()+1;
    for(QMap<QString, int>::const_iterator it = map.constBegin(); it!=map.constEnd(); ++it)
        if (it.key().size()>=minLen)
            displayed.words.append(Word(it.key(),it.value()));
}
void TextAnalysisDialog::slotCount()
{
    needCount();
    displayed.words.clear(); //insert into map to sort
    if (ui.normalTextCheck->isChecked()) insertDisplayData(mapText[ui.comboBox->currentIndex()]);
    if (ui.commandsCheck->isChecked()) insertDisplayData(mapCommand[ui.comboBox->currentIndex()]);
    if (ui.commentsCheck->isChecked()) insertDisplayData(mapComment[ui.comboBox->currentIndex()]);

    displayed.updateAll();

    ui.resultView->setModel(NULL);
    ui.resultView->setModel(&displayed);

    ui.resultView->setShowGrid(false);
    ui.resultView->resizeRowsToContents ();


    ui.displayedWordLabel->setText(QString::number(displayed.wordCount));
    ui.differentWordLabel->setText(QString::number(displayed.words.size()));
    ui.characterInWordsLabel->setText(QString::number(displayed.characterInWords));
}

void TextAnalysisDialog::slotClose(){
    reject();
}

