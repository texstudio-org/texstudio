#include "textanalysis.h"
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

  connect(ui.countButton, SIGNAL(clicked()), SLOT(slotCount()) );
  connect(ui.closeButton, SIGNAL(clicked()), SLOT(slotClose()) );
}

TextAnalysisDialog::~TextAnalysisDialog()
{
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
    mapText.resize(2+chapters.size());
    mapComment.resize(2+chapters.size());
    mapCommand.resize(2+chapters.size());
    QString eow="~!@#$%^&*()_+{}|:\"<>?,./;'[]-= \n\r`+´";
    QString curWord = "";
    bool inComment = false;
    int totalLines=0;
    int textLines=0;
    int commentLines=0;
    bool lineCounted=false;
    int selectionState=0;
    int extraMap=0;//map for chapters
    int nextChapter=0;
    for (int i=0; i<data.size(); i++){
        if (eow.indexOf(data.at(i))>-1 || ((curWord.size()>1) && (data.at(i) == QChar('\\')))) {
            curWord=curWord.toLower();
            if (curWord.size()>0)
                if (curWord.at(0) == QChar('\\') && !inComment) {
                    mapCommand[0][curWord]=mapCommand[0][curWord]+1;
                    if (selectionState==1) mapCommand[1][curWord]=mapCommand[1][curWord]+1;
                    if (extraMap!=0) mapCommand[extraMap][curWord]=mapCommand[extraMap][curWord]+1;
                } else if (curWord.at(0) != QChar('\\')) {
                   if (inComment) {
                        mapComment[0][curWord]=mapComment[0][curWord]+1;
                        if (selectionState==1) mapComment[1][curWord]=mapComment[1][curWord]+1;
                        if (extraMap!=0) mapComment[extraMap][curWord]=mapComment[extraMap][curWord]+1;
                        if (!lineCounted) commentLines++;
                   } else {
                        mapText[0][curWord]=mapText[0][curWord]+1;
                        if (selectionState==1) mapText[1][curWord]=mapText[1][curWord]+1;
                        if (extraMap!=0) mapText[extraMap][curWord]=mapText[extraMap][curWord]+1;
                        if (!lineCounted) textLines++;
                   }
                   if (!lineCounted) lineCounted=true;
                }

            curWord.clear();
            if (selectionState==0 && i>selectionStart) selectionState=1;
            else if (selectionState==1 && i>selectionEnd) selectionState=2;
            if (data.at(i) == QChar('%')) {
                inComment=true;
                lineCounted=false;
            }
            if (data.at(i) == QChar('\n')){// || data.at(i) == QChar('\r') || data.at(i) == QChar('\u2029')) {
                inComment=false;
                lineCounted=false;
                totalLines++;
                if (nextChapter<chapters.size() && totalLines>=chapters[nextChapter].second) {
                    nextChapter++;
                    if (extraMap==0) extraMap=2;
                    else {
                      extraMap++;
                      if (extraMap>=mapText.size()) {
                          extraMap=0;
                          nextChapter=chapters.size();
                      }
                    }
                }
            }
        } else curWord+=data.at(i);
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

