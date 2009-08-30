#include "latexcompleter.h"
#include "latexcompleter_p.h"
#include "latexcompleter_config.h"

#include "smallUsefulFunctions.h"

#include "qdocumentline.h"
#include "qeditorinputbinding.h"
#include "qformatfactory.h"


//------------------------------Default Input Binding--------------------------------
class CompleterInputBinding: public QEditorInputBinding {
public:
	CompleterInputBinding():active(0) {}
	virtual QString id() const {
		return "TexMakerX::CompleteInputBinding";
	}
	virtual QString name() const {
		return "TexMakerX::CompleteInputBinding";
	}

	virtual bool mousePressEvent(QMouseEvent* mouse, QEditor *editor) {
		// remove unused argument warnings
		(void) mouse;
		(void) editor;

		resetBinding();
		return false;
	}

	QString getCurWord() {
		//QMessageBox::information(0,curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart),"",0);
		return curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart);
	}

	bool insertCompletedWord() {
		if (completer->list->isVisible() && maxWritten>curStart && completer->list->currentIndex().isValid()) {
			QDocumentCursor cursor=editor->cursor();
			cursor.beginEditBlock();
			QVariant v=completer->list->model()->data(completer->list->currentIndex(),Qt::DisplayRole);
			if (!v.isValid() || !v.canConvert<CompletionWord>()) return false;
			CompletionWord cw= v.value<CompletionWord>();
			//int alreadyWrittenLen=editor->cursor().columnNumber()-curStart;
			//remove current text for correct case
			for (int i=maxWritten-cursor.columnNumber(); i>0; i--) cursor.deleteChar();
			for (int i=cursor.columnNumber()-curStart; i>0; i--) cursor.deletePreviousChar();
			//  cursor.setColumnNumber(curStart);
			cw.insertAt(editor,&cursor);

			cursor.endEditBlock();

			return true;
		}
		return false;
	}

	void removeRightWordPart() {
		QDocumentCursor cursor=editor->cursor();
		for (int i=maxWritten-cursor.columnNumber(); i>0; i--) cursor.deleteChar();
		maxWritten=cursor.columnNumber();
		editor->setCursor(cursor);//necessary to keep the cursor at the same place (but why???)
	}

	//selects an index in the completion suggestion list
	void select(const QModelIndex &ind) {
		if (!completer || !completer->list) return;
		completer->list->setCurrentIndex(ind);
		completer->selectionChanged(ind);
	}

	//moves the selection index to the next/previous delta-th entry in the suggestion list
	bool selectDelta(const int delta){
		if (!completer || !completer->list || !completer->list->isVisible()) {
			resetBinding();
			return false;
		}
		QModelIndex ind=completer->list->model()->index(completer->list->currentIndex().row()+delta,0,QModelIndex());
		if (!ind.isValid()) {
			if (delta<0) ind=completer->list->model()->index(0,0,QModelIndex());
			else if (delta>0) ind=completer->list->model()->index(completer->list->model()->rowCount()-1,0,QModelIndex());
		}
		if (ind.isValid()) select(ind);
		return true;
	}
	
	bool completeCommonPrefix(){
		QString my_curWord=getCurWord();
		if (my_curWord.isEmpty()) return false;
		if (!completer) return false;
		/*if (!completer->list->isVisible()) {
			resetBinding();
			return false;
		}*/
		// get list of most recent choices
		QStringList my_words;
		const QList<CompletionWord> &words=completer->listModel->getWords();
		for (int i=0; i<words.count(); i++) {
			if (words[i].word.startsWith(my_curWord,Qt::CaseInsensitive))
				my_words.append(words[i].word);
		}
		// filter list for longest common characters
		if (my_words.count()>1) {
			QString myResult=my_words[0];
			int my_start=my_curWord.length();
			for (int i=1; i<my_words.count(); i++) {
				my_curWord=my_words[i];

				for (int j=my_start; (j<my_curWord.length()&&j<myResult.length()); j++) {
					if (myResult[j]!=my_curWord[j]) {
						myResult=myResult.left(j);

					}
				}
			}

			removeRightWordPart();
			editor->cursor().insertText(myResult.right(myResult.length()-my_start));
			maxWritten+=myResult.length()-my_start;
			completer->filterList(getCurWord());
			if (!completer->list->currentIndex().isValid())
				select(completer->list->model()->index(0,0,QModelIndex()));
			return true;
		} else {
			insertCompletedWord();
			resetBinding();
			return true;
		}
	}	
	
	virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor) {
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
			} else if (editor->cursor().columnNumber()+1<=curStart && !showAlways) {
				completer->list->hide();
				return true;
			}
			handled=true;
		} else if (event->key()==Qt::Key_Escape) {
			resetBinding();
			return true;
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
		} else if (event->key()==Qt::Key_Up) return selectDelta(-1);
		else if (event->key()==Qt::Key_Down) return selectDelta(+1);
		else if (event->key()==Qt::Key_PageUp) return  selectDelta(-5);
		else if (event->key()==Qt::Key_PageDown) return  selectDelta(+5);
		else if (event->key()==Qt::Key_Home) {
			if (!completer->list->isVisible()) {
				resetBinding();
				return false;
			}
			QModelIndex ind=completer->list->model()->index(0,0,QModelIndex());
			if (ind.isValid()) select(ind);
			return true;
		} else if (event->key()==Qt::Key_End) {
			if (!completer->list->isVisible()) {
				resetBinding();
				return false;
			}
			QModelIndex ind=completer->list->model()->index(completer->list->model()->rowCount()-1,0,QModelIndex());
			if (ind.isValid()) select(ind);
			return true;
		}  else if (event->key()==Qt::Key_Tab) {
			return completeCommonPrefix();
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
					QDocumentCursor edc=editor->cursor();
					if (edc.hasSelection()) {
						edc.removeSelectedText();
						editor->setCursor(edc);
					}
					curStart=edc.columnNumber();
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
			} else if (LatexCompleter::config && LatexCompleter::config->eowCompletes && 
		           event->text().length()==1 && getCommonEOW().contains(event->text().at(0))) {
				insertCompletedWord();
				resetBinding();
				return false; //return false to let the default implementation handle it and insert the new character
			} else {
				resetBinding();
				return false;
			}
		}
		completer->filterList(getCurWord());
		if (!completer->list->currentIndex().isValid())
			select(completer->list->model()->index(0,0,QModelIndex()));
		return handled;
	}

	void cursorPositionChanged(QEditor* edit) {
		if (edit!=editor) return; //should never happen
		QDocumentCursor c=editor->cursor();
		if (c.line()!=curLine || c.columnNumber()<curStart) resetBinding();
	}

	void resetBinding() {
		if (!active) return;
		QToolTip::hideText();
		editor->setInputBinding(oldBinding);
		editor->setFocus();
		if (completer) {
			completer->list->hide();
			completer->disconnect(editor,SIGNAL(cursorPositionChanged()),completer,SLOT(cursorPositionChanged()));
		}
		active=false;
		curLine=QDocumentLine(); //prevent crash if the editor is destroyed
	}

	void bindTo(QEditor * edit, LatexCompleter* caller, bool forced, int start) {
		if (active) resetBinding();
		active=true;
		completer=caller;
		editor=edit;
		oldBinding=(editor->inputBindings().count()>0?editor->inputBindings()[0]:0);
		editor->setInputBinding(this);
		curStart=start>0?start:0;
		maxWritten=editor->cursor().columnNumber();
		if (maxWritten<start) maxWritten=start;
		curLine=editor->cursor().line();
		showAlways=forced;//curWord!="\\";
		completer->filterList(getCurWord());
		if (showAlways) {
			completer->list->show();
			select(completer->list->model()->index(0,0,QModelIndex()));
		}
	}


	bool isActive() {
		return active;
	}
private:
	bool active;
	bool showAlways;
	LatexCompleter *completer;
	QEditor * editor;
	QEditorInputBindingInterface* oldBinding;
	QString completionWord;
	int curStart,maxWritten;
	QDocumentLine curLine;
};

CompleterInputBinding *completerInputBinding = new CompleterInputBinding();
//------------------------------Item Delegate--------------------------------
class CompletionItemDelegate: public QItemDelegate {
public:
	CompletionItemDelegate(QObject* parent = 0): QItemDelegate(parent) {
	}

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
		QVariant v=index.model()->data(index);
		if (!v.isValid() || !v.canConvert<CompletionWord>()) return;
		CompletionWord cw=v.value<CompletionWord>();
		if (cw.lines.empty()||cw.placeHolders.empty()) return;
		QFont fNormal=option.font;
		QFont fItalic=option.font;
		fItalic.setItalic(true);
		if ((QStyle::State_HasFocus | QStyle::State_Selected) & option.state) {
			//painter->setBackground(option.palette.brush(QPalette::Highlight));
			painter->fillRect(option.rect,option.palette.brush(QPalette::Highlight));
			painter->setPen(option.palette.color(QPalette::HighlightedText));
		} else {
			//painter->setBackground(option.palette.brush(QPalette::Base));
			painter->fillRect(option.rect,option.palette.brush(QPalette::Base));//doesn't seem to be necessary
			painter->setPen(option.palette.color(QPalette::Text));
		}
		QRect r=option.rect;
		r.setLeft(r.left()+2);
		QString firstLine=cw.lines[0];
		if (cw.placeHolders.empty())
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine);
		else {
			QFontMetrics fmn(fNormal);
			QFontMetrics fmi(fItalic);
			int p=0;
			for (int i=0; i<cw.placeHolders[0].size(); i++) {
				QString temp=firstLine.mid(p,cw.placeHolders[0][i].first-p);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmn.width(temp));
				temp=firstLine.mid(cw.placeHolders[0][i].first,cw.placeHolders[0][i].second);
				painter->setFont(fItalic);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmi.width(temp)+1);
				p=cw.placeHolders[0][i].first+cw.placeHolders[0][i].second;
				painter->setFont(fNormal);
				if (p>firstLine.length()) break;
			}
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine.mid(p));
		}
	}
};



//----------------------------list model------------------------------------
int CompletionListModel::rowCount(const QModelIndex &parent) const {
	// remove unused argument warning
	(void) parent;

	return words.count();
}
QVariant CompletionListModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid())
		return QVariant();

	if (index.row() >= words.size())
		return QVariant();

	if (role == Qt::DisplayRole) {
		QVariant temp;
		temp.setValue(words.at(index.row()));
		return temp;
	} else
		return QVariant();
}
QVariant CompletionListModel::headerData(int section, Qt::Orientation orientation,
        int role) const {
	// remove unused argument warnings
	(void) role;
	(void) orientation;
	(void) section;

	return QVariant();
}
bool CompletionListModel::isNextCharPossible(const QChar &c){
	if (words.count()>100) //probable that every char is there (especially since acceptedChars is already checked)
		return true; 
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	if (LatexCompleter::config && 
		LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_CASE_SENSITIVE)
		cs=Qt::CaseSensitive;
	QString extension=curWord+c;
	foreach (const CompletionWord & cw, words)
		if (cw.word.startsWith(extension,cs)) return true;
	return false;
}
void CompletionListModel::filterList(const QString &word) {
	if (word==curWord) return;
	words.clear();
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	bool checkFirstChar=false;
	if (LatexCompleter::config){
		if (LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_CASE_SENSITIVE)
			cs=Qt::CaseSensitive;
		checkFirstChar=LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_FIRST_CHARACTER_CASE_SENSITIVE && word.length()>1;
	}
	for (int i=0; i<baselist.count(); i++) {
		if (baselist[i].word.isEmpty()) continue;
		if (baselist[i].word.startsWith(word,cs) &&
			(!checkFirstChar || baselist[i].word[1] == word[1]) )
			words.append(baselist[i]);
	}
	/*if (words.size()>=2) //prefer matching case
	   if (!words[0].word.startsWith(word,Qt::CaseSensitive) && words[1].word.startsWith(word,Qt::CaseSensitive))
	   	words.swap(0,1);*/
	curWord=word;
	reset();
}
void CompletionListModel::setBaseWords(const QStringList &newwords, bool normalTextList) {
	QList<CompletionWord> newWordList;
	acceptedChars.clear();
	newWordList.clear();
	foreach(QString str, newwords) {
		newWordList.append(CompletionWord(str));
		foreach(QChar c, str) acceptedChars.insert(c);
	}
	qSort(newWordList.begin(), newWordList.end());

	if (normalTextList) wordsText=newWordList;
	else wordsCommands=newWordList;
	baselist=wordsCommands;
}

void CompletionListModel::setBaseWords(const QList<CompletionWord> &newwords, bool normalTextList) {
	QList<CompletionWord> newWordList;
	acceptedChars.clear();
	newWordList.clear();
	foreach(CompletionWord cw, newwords) {
		newWordList.append(cw);
		foreach(QChar c, cw.word) acceptedChars.insert(c);
	}
	qSort(newWordList.begin(), newWordList.end());

        if (normalTextList) wordsText=newWordList;
	else wordsCommands=newWordList;
	baselist=wordsCommands;
}

void CompletionListModel::setAbbrevWords(const QList<CompletionWord> &newwords) {
        wordsAbbrev=newwords;
}

//------------------------------completer-----------------------------------
QString LatexCompleter::helpFile;
QHash<QString, QString> LatexCompleter::helpIndices;
QHash<QString, int> LatexCompleter::helpIndicesCache;
const LatexCompleterConfig* LatexCompleter::config=0;

LatexCompleter::LatexCompleter(QObject *p): QObject(p),maxWordLen(0) {
//   addTrigger("\\");
	if (!qobject_cast<QWidget*>(parent()))
		QMessageBox::critical(0,"Serious PROBLEM", QString("The completer has been created without a parent widget. This is impossible!\n")+
		                      QString("Please report it ASAP to the bug tracker on texmakerx.sf.net and check if your computer is going to explode!\n")+
		                      QString("(please report the bug *before* going to a safe place, you could rescue others)"),QMessageBox::Ok);
	list=new QListView(qobject_cast<QWidget*>(parent()));
	listModel=new CompletionListModel(list);
	connect(list, SIGNAL(clicked(const QModelIndex &)) , this, SLOT(selectionChanged(const QModelIndex &)));
	list->setModel(listModel);
	list->setFocusPolicy(Qt::NoFocus);
	list->setItemDelegate(new CompletionItemDelegate(list));
	editor=0;
}
LatexCompleter::~LatexCompleter() {
	//delete list;
}


void LatexCompleter::setAdditionalWords(const QStringList &newwords, bool normalTextList) {
	QStringList concated = newwords;
	if (config && !normalTextList) concated << config->words;
	listModel->setBaseWords(concated,normalTextList);
	if (maxWordLen==0 && !normalTextList) {
		int newWordMax=0;
		QFont f=QApplication::font();
		f.setItalic(true);
		QFontMetrics fm(f);
		const QList<CompletionWord> & words=listModel->getWords();
		for (int i=0; i<words.size(); i++) {
			if (words[i].lines.empty() || words[i].placeHolders.empty()) continue;
			int temp=fm.width(words[i].lines[0])+words[i].placeHolders[0].size()+10;
			if (temp>newWordMax) newWordMax=temp;
		}
		maxWordLen=newWordMax;
		list->resize(200>maxWordLen?200:maxWordLen,100);
	}
}

void LatexCompleter::setAbbreviations(const QStringList &Abbrevs,const QStringList &Tags){
    QList<CompletionWord> wordsAbbrev;
    wordsAbbrev.clear();
    for(int i=0;i<Abbrevs.size();i++){
        QString abbr=Abbrevs.value(i,"");
        if(!abbr.isEmpty()){
            CompletionWord cw(abbr);
            cw.lines=(abbr+tr(" (Usertag)")+"\n"+Tags.value(i)).split("\n");
            cw.setCut(true);
            wordsAbbrev << cw;
        }
    }
    listModel->setAbbrevWords(wordsAbbrev);
}

void LatexCompleter::complete(QEditor *newEditor,bool forceVisibleList, bool normalText, bool forceRef) {
	if (editor != newEditor) {
		if (editor) disconnect(editor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		if (newEditor) connect(newEditor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		editor=newEditor;
	}
	if (!editor) return;
	QDocumentCursor c=editor->cursor();
	if (!c.isValid()) return;
	if (c.hasSelection()) {
		c.setColumnNumber(qMax(c.columnNumber(),c.anchorColumnNumber()));
		editor->setCursor(c);
	}
	QDocumentLine line=c.line();
	if (c.columnNumber()<0 || c.columnNumber()>line.length()) return;
	QPoint offset=line.cursorToDocumentOffset(c.columnNumber()-1);
	offset.setY(offset.y()+line.document()->y(c.lineNumber())+line.document()->fontMetrics().lineSpacing());
	offset=editor->mapFromContents(offset);
	int left;
	int temp;
	editor->getPanelMargins(&left,&temp,&temp,&temp);
	offset.setX(offset.x()+left);
	//list->resize(200>maxWordLen?200:maxWordLen,100);
	//list->setParent(editor);
	if (offset.y()+list->height()>editor->height()) {
		offset.setY(offset.y()-line.document()->fontMetrics().lineSpacing()-list->height());
	}
	list->move(editor->mapTo(qobject_cast<QWidget*>(parent()),offset));
	//list->show();
	if (normalText) listModel->baselist=listModel->wordsText;
	else listModel->baselist=listModel->wordsCommands;
        listModel->baselist+=listModel->wordsAbbrev;
        qSort(listModel->baselist.begin(),listModel->baselist.end());
	if (c.previousChar()!='\\' || forceVisibleList) {
		int start=c.columnNumber()-1;
		if (normalText) start=0;
		QString eow="~!@#$%^&*()_+}|:\"<>?,./;[]-= \n\r`+�";
		if (normalText) eow+="{";
		if(forceRef) eow="\\";
		QString lineText=c.line().text();
		for (int i=c.columnNumber()-1; i>=0; i--) {
			if (lineText.at(i)==QChar('\\')) {
				start=i;
				break;
			} else if (eow.contains(lineText.at(i))) {
				if (normalText) start=i+1;
				break;
			}
		}
		completerInputBinding->bindTo(editor,this,true,start);
	} else completerInputBinding->bindTo(editor,this,false,c.columnNumber()-1);

	//line.document()->cursor(0,0).insertText(QString::number(offset.x())+":"+QString::number(offset.y()));
	connect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
	
	if (config && config->completeCommonPrefix) completerInputBinding->completeCommonPrefix();
}

void LatexCompleter::parseHelpfile(QString text) {
	helpFile="<invalid>";
	//search alpabetical index label and remove everything before the next tabel
	int start=text.indexOf("<a name=\"alpha\">");
	if (start==-1) return;
	text=text.remove(0,start);
	text=text.remove(0,text.indexOf("<table>")-1);
	//split into index and remaining teext
	int end=text.indexOf("</table>");
	if (end==-1) return; //no remaining text
	QString index=text.left(end);
	helpFile=text.mid(end);
	//read index, searching for <li><a href="#SEC128">\!</a></li>
	QRegExp rx("<li><a\\s+(name=\"index.\")?\\s*href=\"#([^\"]+)\">([^> ]+)[^>]*</a></li>");
	int pos = 0;    // where we are in the string
	while (pos >= 0) {
		pos = rx.indexIn(index, pos);
		if (pos >= 0) {
			QString id=rx.cap(3);
			if (!id.startsWith("\\")) id="\\begin{"+id;
			helpIndices.insert(id.toLower(),rx.cap(2));
			pos += rx.matchedLength();
		}
	}
//    QMessageBox::information(0,QString::number(helpIndices.size()),"",0);
}
bool LatexCompleter::hasHelpfile() {
	return !helpFile.isEmpty();
}
bool LatexCompleter::acceptTriggerString(const QString& trigger){
	return trigger=="\\" && (!config || config->enabled);;
}
void LatexCompleter::setConfig(const LatexCompleterConfig* config){
	this->config=config;
}

void LatexCompleter::filterList(QString word) {
	QString cur=""; //needed to preserve selection
	if (list->isVisible() && list->currentIndex().isValid())
		cur=list->model()->data(list->currentIndex(),Qt::DisplayRole).toString();
	listModel->filterList(word);
	if (cur!="") {
		int p=listModel->getWords().indexOf(cur);
		if (p>=0) list->setCurrentIndex(list->model()->index(p,0,QModelIndex()));
	}
}
bool LatexCompleter::acceptChar(QChar c,int pos) {
	//always accept alpha numerical characters
	if (((c>=QChar('a')) && (c<=QChar('z'))) ||
	        ((c>=QChar('A')) && (c<=QChar('Z'))) ||
	        ((c>=QChar('0')) && (c<=QChar('9')))) return true;
	if (pos<=1) return false;
	if (!listModel->getAcceptedChars().contains(c)) 
		return false; //if no word contains the character don't accept it
	if (listModel->isNextCharPossible(c)) 
		return true; //only accept non standard character, if one of the current words contains it
	return false;
}

void LatexCompleter::cursorPositionChanged() {
	if (!completerInputBinding || !completerInputBinding->isActive()) {
		disconnect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
		return;
	}
	completerInputBinding->cursorPositionChanged(editor);
}
//called when item is clicked, more important: normal (not signal/slot) called when completerbinding change selection
void LatexCompleter::selectionChanged(const QModelIndex & index) {
	if (helpIndices.empty()) return;
	QToolTip::hideText();
	if (!config->tooltipHelp) return;
	if (!index.isValid()) return;
	if (index.row() < 0 || index.row()>=listModel->words.size()) return;
	QRegExp wordrx("^\\\\([^ {[*]+|begin\\{[^ {}]+)");
	if (wordrx.indexIn(listModel->words[index.row()].word)==-1) return;
	QString id=helpIndices.value(wordrx.cap(0),"");
	if (id=="") return;
	QString aim="<a name=\""+id;
	int pos=helpIndicesCache.value(wordrx.cap(0),-2);
	if (pos==-2) {
		//search id in help file
		//QRegExp aim ("<a\\s+name=\""+id);
		pos=helpFile.indexOf(aim);// aim.indexIn(helpFile);
		helpIndicesCache.insert(wordrx.cap(0),pos);
	}
	if (pos<0) return;
	//get whole topic of the line
	int opos=pos;
	while (pos>=1 && helpFile.at(pos)!=QChar('\n')) pos--;
	QString topic=helpFile.mid(pos);
	if (topic.left(opos-pos).contains("<dt>")) topic=topic.left(topic.indexOf("</dd>"));
	else {
		QRegExp anotherLink("<a\\s+name=\\s*\"[^\"]*\"(\\s+href=\\s*\"[^\"]*\")?>\\s*[^< ][^<]*</a>");
		int nextpos=anotherLink.indexIn(topic,opos-pos+aim.length());
		topic=topic.left(nextpos);
	}
	QRect r = list->visualRect(index);
	QDocumentCursor c=editor->cursor();
	QRect screen = QApplication::desktop()->availableGeometry();
	int lineHeight=c.line().document()->fontMetrics().lineSpacing();
	QPoint tt=list->mapToGlobal(QPoint(list->width(), r.top()-lineHeight));
	int lineY=editor->mapToGlobal(editor->mapFromContents(c.documentPosition())).y();
	// estimate width of coming tooltip
	// rather dirty code
	QLabel lLabel(0,Qt::ToolTip);
#if QT_VERSION >= 0x040400
	lLabel.setForegroundRole(QPalette::ToolTipText);
	lLabel.setBackgroundRole(QPalette::ToolTipBase);
#else
	lLabel.setForegroundRole(QPalette::Text);
	lLabel.setBackgroundRole(QPalette::AlternateBase);
#endif
	lLabel.setPalette(QToolTip::palette());
	lLabel.setMargin(1 + lLabel.style()->pixelMetric(QStyle::PM_ToolTipLabelFrameWidth, 0, &lLabel));
	lLabel.setFrameStyle(QFrame::StyledPanel);
	lLabel.setAlignment(Qt::AlignLeft);
	lLabel.setIndent(1);
	lLabel.setWordWrap(true);
	lLabel.ensurePolished();
	lLabel.setText(topic);
	lLabel.adjustSize();


	int textWidthInPixels = lLabel.width()+10; // +10 good guess

	if(lineY>tt.y()){
		tt.setY(lineY-lLabel.height()-lineHeight-5);
	}

	if (screen.width()-textWidthInPixels>=tt.x()) QToolTip::showText(tt, topic, list);//-90
	else {
		//list->mapToGlobal
		QPoint tt=list->mapToGlobal(QPoint(-textWidthInPixels, r.top()-lineHeight));
		if(lineY>tt.y()){
			tt.setY(lineY-lLabel.height()-lineHeight-5);
		}
		QToolTip::showText(tt, topic, list,QRect(-300,-200,300,600));
	}
}
void LatexCompleter::editorDestroyed() {
	editor=0;
}








void LatexCompleterConfig::loadFiles(const QStringList &newFiles) {
	files=newFiles;
	words.clear();
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	foreach(QString file, files) {
		QString fn=findResourceFile("completion/"+file);
		QFile tagsfile(fn);
		if (tagsfile.open(QFile::ReadOnly)) {
			QString line;
			while (!tagsfile.atEnd()) {
				line = tagsfile.readLine();
				if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith(" ")) {
					if (line.startsWith("\\pageref")||line.startsWith("\\ref")) continue;
					if (!line.contains("%")){
						if (line.contains("{")) {
							line.replace("{","{%<");
							line.replace("}","%>}");
							line.replace("{%<%>}", "{%<something%>}");
						}
						if (line.contains("(")) {
							line.replace("(","(%<");
							line.replace(")","%>)");
							line.replace("(%<%>)", "(%<something%>)");
						}
						if (line.contains("[")) {
							line.replace("[","[%<");
							line.replace("]","%>]");
							line.replace("[%<%>]", "[%<something%>]");
						}
						int i;
						if (line.startsWith("\\begin")||line.startsWith("\\end")) {
							i=line.indexOf("%<",0);
							line.replace(i,2,"");
							i=line.indexOf("%>",0);
							line.replace(i,2,"");
							if (line.endsWith("\\item\n")) {
								line.chop(6);
							}
						}
					}
					words.append(line.trimmed());
				}
			}
		}
	}
	QApplication::restoreOverrideCursor();
}

const QStringList& LatexCompleterConfig::getLoadedFiles(){
	return files;
}

QString LatexCompleter::lookupWord(QString text){
	QRegExp wordrx("^\\\\([^ {[*]+|begin\\{[^ {}]+)");
	if (wordrx.indexIn(text)==-1) return "";
	QString id=helpIndices.value(wordrx.cap(0),"");
	if (id=="") return "";
	QString aim="<a name=\""+id;
	int pos=helpIndicesCache.value(wordrx.cap(0),-2);
	if (pos==-2) {
		//search id in help file
		//QRegExp aim ("<a\\s+name=\""+id);
		pos=helpFile.indexOf(aim);// aim.indexIn(helpFile);
		helpIndicesCache.insert(wordrx.cap(0),pos);
	}
	if (pos<0) return "";
	//get whole topic of the line
	int opos=pos;
	while (pos>=1 && helpFile.at(pos)!=QChar('\n')) pos--;
	QString topic=helpFile.mid(pos);
	if (topic.left(opos-pos).contains("<dt>")) topic=topic.left(topic.indexOf("</dd>"));
	else {
		QRegExp anotherLink("<a\\s+name=\\s*\"[^\"]*\"(\\s+href=\\s*\"[^\"]*\")?>\\s*[^< ][^<]*</a>");
		int nextpos=anotherLink.indexIn(topic,opos-pos+aim.length());
		topic=topic.left(nextpos);
	}
	return topic;
}
//ends completion (closes the list) and returns true if there was any
bool LatexCompleter::close(){
	if (completerInputBinding->isActive()){
		completerInputBinding->resetBinding();
		list->setVisible(false);
		return true;
	} else return false;
}
