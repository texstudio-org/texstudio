#include "latexcompleter.h"
#include "QCodeEdit/qdocumentline.h"
#include <QKeyEvent>
#include <QMessageBox>

//------------------------------Default Input Binding--------------------------------
class CompleterInputBinding: public QEditor::InputBinding{
public:
    CompleterInputBinding():active(0){}
	virtual QString id() const{return "TexMaker::CompleteInputBinding";}
    virtual QString name() const{return "TexMaker::CompleteInputBinding";}

    virtual bool mousePressEvent(QMouseEvent* mouse, QEditor *editor){
        resetBinding();
        return false;
    }

    QString getCurWord(){
        //QMessageBox::information(0,curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart),"",0);
        return curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart);
    }

    bool insertCompletedWord(){
        if (completer->list->isVisible() && maxWritten>curStart && completer->list->currentIndex().isValid()) {
            QString full=completer->list->model()->data(completer->list->currentIndex(),Qt::DisplayRole).toString();
            for (int i=maxWritten-editor->cursor().columnNumber();i>0;i--)
              editor->cursor().deleteChar();
            QString addStr=full.mid(editor->cursor().columnNumber()-curStart);
            editor->cursor().insertText(addStr);
            if (full.startsWith("\\begin")) {
                int p=full.indexOf("{");
                QString indent=editor->cursor().line().indentation();
                editor->cursor().insertText( "\n"+indent+"\n"+indent+"\\end"+full.mid(p,full.indexOf("}")-p+1));
                curLine=editor->document()->line(curLine.lineNumber()+1);
                editor->setCursorPosition(curLine.lineNumber(),curLine.length());
            } else {
                int p=addStr.indexOf('[');
                if (p<0) p =addStr.indexOf('{');
                else p=addStr.indexOf('{')<p?addStr.indexOf('{'):p;
                if (p>=0)
                    editor->setCursorPosition(editor->cursor().lineNumber(),editor->cursor().columnNumber()-(addStr.length()-p-1));
            }
            return true;
        }
        return false;
    }

    virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor)
    {
        if (event->key()==Qt::Key_Shift || event->key()==Qt::Key_Alt || event->key()==Qt::Key_Control) 
            return false;
        if (!active) return false; //we should never have been called
        bool handled=false;
        if (event->key()==Qt::Key_Backspace) {
            maxWritten--;
            editor->cursor().deletePreviousChar();
            if (editor->cursor().columnNumber()<=curStart) {
                resetBinding();
                return true;
            } else if (editor->cursor().columnNumber()+1<=curStart && !showAlways){
                completer->list->hide();
                return true;
            }
            handled=true;
        } else if (event->key()==Qt::Key_Delete) {
            if (editor->cursor().columnNumber()<maxWritten) maxWritten--;
            editor->cursor().deleteChar();
            handled=true;
        } else if (event->key()==Qt::Key_Left) {
            if (event->modifiers()) {
                resetBinding();
                return false;
            }
            editor->setCursorPosition(curLine.lineNumber(),editor->cursor().columnNumber()-1);
            if (editor->cursor().columnNumber()<=curStart) resetBinding();
            handled=true;
        } else if (event->key()==Qt::Key_Right) { 
            if (event->modifiers()) {
                resetBinding();
                return false;
            }
            editor->setCursorPosition(curLine.lineNumber(),editor->cursor().columnNumber()+1);
            if (editor->cursor().columnNumber()>maxWritten) resetBinding();
            handled=true;
        } else if (event->key()==Qt::Key_Up) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(completer->list->currentIndex().row()-1,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_Down) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(completer->list->currentIndex().row()+1,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_PageUp) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(completer->list->currentIndex().row()-5,0,QModelIndex());
            if (!ind.isValid()) ind=completer->list->model()->index(0,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_PageDown) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(completer->list->currentIndex().row()+5,0,QModelIndex());
            if (!ind.isValid()) ind=completer->list->model()->index(completer->list->model()->rowCount()-1,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_Home) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(0,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_End) { 
            if (!completer->list->isVisible()) {
                resetBinding();
                return false;
            }
            QModelIndex ind=completer->list->model()->index(completer->list->model()->rowCount()-1,0,QModelIndex());
            if (ind.isValid()) completer->list->setCurrentIndex(ind);
            return true;
        } else if (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter) { 
            if (!insertCompletedWord()) {
                editor->cursor().insertText("\n");
                curLine=editor->document()->line(curLine.lineNumber()+1);
                editor->setCursorPosition(curLine.lineNumber(),curLine.length());
            }
            resetBinding();
            return true;
        } else {
            if (event->text().length()!=1 || event->text()==" ") {
                resetBinding();
                return false;
            } 
        
            QChar written=event->text().at(0);
            if (written=='\\') {
                if (getCurWord()=="\\") {
                    curStart+=2;
                    maxWritten=curStart;
                } else if (getCurWord()=="") {
                    maxWritten=curStart+1;
                } else {
                    insertCompletedWord();
                    curStart=editor->cursor().columnNumber();
                    maxWritten=curStart+1;
                }
                editor->cursor().insertText(written);
                handled=true;
            } else if (completer->acceptChar(written,editor->cursor().columnNumber()-curStart)) { 
                maxWritten++;
                editor->cursor().insertText(written);
                if (editor->cursor().columnNumber()+1>curStart)  
                    completer->list->show();
                handled=true;
            } else {
                resetBinding();
                return false;
            }
        }
        completer->updateList(getCurWord());
        if (!completer->list->currentIndex().isValid()) 
            completer->list->setCurrentIndex(completer->list->model()->index(0,0,QModelIndex()));
        return handled;
    }

    void resetBinding(){
        if (!active) return;
        editor->setInputBinding(oldBinding);
        if (completer) completer->list->hide();
        active=false;
    }
    
    void bindTo(QEditor * edit, LatexCompleter* caller, bool forced, int start){
        if (active) resetBinding();
        active=true;
        completer=caller;
        editor=edit;
        oldBinding=editor->inputBinding();
        editor->setInputBinding(this);        
        curStart=start>0?start:0;
        maxWritten=editor->cursor().columnNumber();
        if (maxWritten<start) maxWritten=start;
        curLine=editor->cursor().line();
        showAlways=forced;//curWord!="\\";
        if (showAlways) {
            completer->updateList(getCurWord());
            completer->list->show();
            completer->list->setCurrentIndex(completer->list->model()->index(0,0,QModelIndex()));
        }
    }

private:
    bool active;
    bool showAlways;
    LatexCompleter *completer;
    QEditor * editor;
    QEditor::InputBinding* oldBinding;
    QString completionWord;
    int curStart,maxWritten;
    QDocumentLine curLine;
};

CompleterInputBinding *completerInputBinding = new CompleterInputBinding();


//----------------------------list model------------------------------------
int CompletionListModel::rowCount(const QModelIndex &parent) const{
    return words.count();
}
QVariant CompletionListModel::data(const QModelIndex &index, int role) const{
 if (!index.isValid())
     return QVariant();

 if (index.row() >= words.size())
     return QVariant();

 if (role == Qt::DisplayRole)
     return words.at(index.row());
 else
     return QVariant();
}
QVariant CompletionListModel::headerData(int section, Qt::Orientation orientation,
                     int role) const{
    return QVariant();
}
 void CompletionListModel::setWords(QStringList baselist, QString word){
     if (word==curWord) return;
     words.clear();
     foreach (QString w, baselist){
         if (w.startsWith(word,Qt::CaseInsensitive)) words.append(w);
     }
     curWord=word;
     reset();
 }

//------------------------------completer-----------------------------------
LatexCompleter::LatexCompleter(QObject *p)
 : QCodeCompletionEngine(p)
{
 //   addTrigger("\\");
    list=0;
}

void LatexCompleter::setWords(const QStringList &newwords){
    words=newwords;
}

void LatexCompleter::complete(const QDocumentCursor& c, const QString& trigger){
    if (!editor()) return;
    QDocumentLine line=c.line();
    QPoint offset=line.cursorToDocumentOffset(c.columnNumber()-1);
    offset.setY(offset.y()+line.document()->y(line)+line.document()->fontMetrics().lineSpacing());
    offset=editor()->mapFromContents(offset);
    int left;int temp;
    editor()->getPanelMargins(&left,&temp,&temp,&temp);
    offset.setX(offset.x()+left);
    if (!list) {
        list=new QListView(editor());;
        list->resize(200,100);
        listModel=new CompletionListModel(list);
        list->setModel(listModel);
    }
    list->move(offset);
    //list->show();
    
    if (c.getPreviousChar()!='\\') {
        int start=c.columnNumber()-1;
        QString eow="~!@#$%^&*()_+{}|:\"<>?,./;[]-= \n\r`+´";
        QString lineText=c.line().text();
        for (int i=c.columnNumber()-1;i>=0;i--){
            if (lineText.at(i)==QChar('\\')) {
                start=i;
                break;
            } else if (eow.contains(lineText.at(i))) 
                break;
        }
        completerInputBinding->bindTo(editor(),this,true,start);
    } else completerInputBinding->bindTo(editor(),this,false,c.columnNumber()-1);

    //line.document()->cursor(0,0).insertText(QString::number(offset.x())+":"+QString::number(offset.y()));
}

QCodeCompletionEngine* LatexCompleter::clone(){
    LatexCompleter* temp =new LatexCompleter(this);
    temp->words=words;
    return temp;
}
QString LatexCompleter::language() const{
    return "Latex";
}
QStringList LatexCompleter::extensions() const{
    return QStringList() << ".tex";
}

void LatexCompleter::updateList(QString word){
    ((CompletionListModel*)(list->model()))->setWords(words,word);
}
bool LatexCompleter::acceptChar(QChar c,int pos){
    if (((c>=QChar('a')) && (c<=QChar('z'))) ||
        ((c>=QChar('A')) && (c<=QChar('Z'))) ||
        ((c>=QChar('0')) && (c<=QChar('9')))) return true;
    if (pos<=1) return false;
    return words.join("").contains(c);
}
