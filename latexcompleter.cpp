#include "latexcompleter.h"
#include "latexcompleter_p.h"
#include "latexcompleter_config.h"

#include "smallUsefulFunctions.h"

#include "qdocumentline.h"
#include "qeditorinputbinding.h"
#include "qformatfactory.h"
#include "qdocumentline_p.h"

#include "latexdocument.h"


//------------------------------Default Input Binding--------------------------------
class CompleterInputBinding: public QEditorInputBinding {
public:
	CompleterInputBinding():active(0),showMostUsed(false) {}
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
		simpleRestoreAutoOverride();
		resetBinding();
		return false;
	}

	QString getCurWord() {
		//QMessageBox::information(0,curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart),"",0);
		return curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart);
	}

	void insertText(const QString& text){
		maxWritten += text.length();
		editor->cursor().insertText(text);
		if (editor->cursor().columnNumber()+1>curStart && !completer->isVisible()){
			QString wrd=getCurWord();
			completer->filterList(wrd,showMostUsed);
			completer->widget->show();
			completer->adjustWidget();
		}
	}

	bool insertCompletedWord() {
		if (completer->list->isVisible() && maxWritten>curStart && completer->list->currentIndex().isValid()) {
			QDocumentCursor cursor=editor->cursor();
			editor->document()->beginMacro();
			QVariant v=completer->list->model()->data(completer->list->currentIndex(),Qt::DisplayRole);
			if (!v.isValid() || !v.canConvert<CompletionWord>()) return false;
			CompletionWord cw= v.value<CompletionWord>();
			completer->listModel->incUsage(completer->list->currentIndex());
			//int alreadyWrittenLen=editor->cursor().columnNumber()-curStart;
			//remove current text for correct case
			if(completer->forcedRef){
			    while(!cursor.atLineEnd() && cursor.nextChar()!='}')
				cursor.deleteChar();
			    if(cursor.nextChar()=='}')
				cursor.deleteChar();
			}
			for (int i=maxWritten-cursor.columnNumber(); i>0; i--) cursor.deleteChar();
			for (int i=cursor.columnNumber()-curStart; i>0; i--) cursor.deletePreviousChar();
			if (!autoOverridenText.isEmpty()){
				cursor.insertText(autoOverridenText);
				cursor.movePosition(autoOverridenText.length(), QDocumentCursor::Left);
				editor->resizeAutoOverridenPlaceholder(cursor, autoOverridenText.size());
				autoOverridenText="";
			}
			//cursor.endEditBlock(); //doesn't work and lead to crash when auto indentation is enabled => TODO:figure out why
			//  cursor.setColumnNumber(curStart);
			cw.insertAt(editor,&cursor,LatexCompleter::config && LatexCompleter::config->usePlaceholders,true);
			editor->document()->endMacro();

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
			editor->insertText(myResult.right(myResult.length()-my_start));
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
	
	void simpleRestoreAutoOverride(const QString& written="????"){ //simple means without protecting the change from undo/redo
		if (!autoOverridenText.isEmpty() && !editor->isAutoOverrideText(written)) {
			int curpos = editor->cursor().columnNumber();
			if (curpos < maxWritten) {
				QDocumentCursor c = editor->cursor();
				c.movePosition(maxWritten-curpos, QDocumentCursor::Right);
				editor->setCursor(c);
			}
			editor->insertText(autoOverridenText);
			QDocumentCursor c = editor->cursor();
			c.movePosition(autoOverridenText.length() + (curpos<maxWritten?maxWritten-curpos:0), QDocumentCursor::Left);
			editor->setCursor(c);
			editor->resizeAutoOverridenPlaceholder(c, autoOverridenText.size());
		}
	}

	virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor) {
		Q_ASSERT (completer && completer->listModel);
		if (!completer || !completer->listModel) return false;
		if (event->key()==Qt::Key_Shift || event->key()==Qt::Key_Alt || event->key()==Qt::Key_AltGr || event->key()==Qt::Key_Control)
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
				completer->widget->hide();
				return true;
			}
			handled=true;
		} else if (event->key()==Qt::Key_Escape) {
			simpleRestoreAutoOverride("");
			resetBinding();
			return true;
		} else if (event->key()==Qt::Key_Delete) {
			if (editor->cursor().columnNumber()<maxWritten) maxWritten--;
			if(completer->forcedRef){
			    if(editor->cursor().nextChar()=='}')
				completer->forcedRef=false;
			}
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
		}  else if (event->key()==Qt::Key_Space && event->modifiers()==Qt::ShiftModifier) {
			//showMostUsed=!showMostUsed;
			//handled=true;
			completer->tbAbove->setCurrentIndex(showMostUsed ? 0 : 1 );
			completer->tbBelow->setCurrentIndex(showMostUsed ? 0 : 1 );
			return true;
		} else if (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter) {
			if (!insertCompletedWord()) {
				editor->insertText("\n");
				//curLine=editor->document()->line(curLine.lineNumber()+1);
				//editor->setCursorPosition(curLine.lineNumber(),curLine.length());
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
					resetBinding();
					return false;
				} else if (getCurWord()=="") {
					maxWritten=curStart+1;
				} else {
					if (LatexCompleter::config && LatexCompleter::config->eowCompletes) {
					    insertCompletedWord();
					}
					QDocumentCursor edc=editor->cursor();
					if (edc.hasSelection()) {
						edc.removeSelectedText();
						editor->setCursor(edc);
					}
					curStart=edc.columnNumber();
					maxWritten=curStart+1;
				}
				editor->cursor().insertText(written);
				//editor->insertText(written);
				handled=true;
			} else if (completer->acceptChar(written,editor->cursor().columnNumber()-curStart)) {
				insertText(written);
				handled=true;
			} else if (event->text().length()==1 && getCommonEOW().contains(event->text().at(0)) ) {
				QString curWord = getCurWord();
				if (curWord=="\\" || !LatexCompleter::config || !LatexCompleter::config->eowCompletes) {
					resetBinding();
					simpleRestoreAutoOverride(written);
					return false;
				}
				const QList<CompletionWord> &words=completer->listModel->getWords();
				QString newWord;
				int eowchars = 10000;
				foreach (const CodeSnippet& w, words){
					if (!w.word.startsWith(curWord)) continue;
					if (w.word.length() == curWord.length()) {
						newWord = w.word;
						break;
					}
					int newoffset = w.lines.first().indexOf(written, curWord.length());
					if (newoffset < 0) continue;
					int neweowchars=0;
					for (int i=curWord.length(); i<newoffset; i++)
						if (getCommonEOW().contains(w.lines.first()[i]))
							neweowchars++;
					if (neweowchars<eowchars) {
						newWord = w.word;
						eowchars = neweowchars;
						if (eowchars==1) break;
					}
				}

				if (!newWord.isEmpty() && newWord.length()!=curWord.length()) {
					QString insertion = newWord.mid(curWord.length(), newWord.indexOf(written, curWord.length()) - curWord.length() + 1); //choose text until written eow character
					insertText(insertion);
					//insertText(written);
					handled = true;
				} else {
					insertCompletedWord();
					if (newWord.isEmpty())
						simpleRestoreAutoOverride(written);
					//insertText(written);
					resetBinding();
					return false;//oldBinding->keyPressEvent(event,editor); //call old input binding for long words (=> key replacements after completions, but the user can still write \")
				}
			} else {
				int curLength = getCurWord().length();
				resetBinding();
				return curLength >= 2 &&  oldBinding->keyPressEvent(event,editor); //call old input binding for long words (=> key replacements after completions, but the user can still write \")
			}
		}
		completer->filterList(getCurWord(),showMostUsed);
		if (!completer->list->currentIndex().isValid())
			select(completer->list->model()->index(0,0,QModelIndex()));
		return handled;
	}

	void cursorPositionChanged(QEditor* edit) {
		if (edit!=editor) return; //should never happen
		QDocumentCursor c=editor->cursor();
		if (c.line()!=curLine || c.columnNumber()<curStart) resetBinding();
	}

	void setMostUsed(bool mu){
	    showMostUsed=mu;
	    completer->filterList(getCurWord(),showMostUsed);
	    if (!completer->list->currentIndex().isValid())
		    select(completer->list->model()->index(0,0,QModelIndex()));
	}

	bool getMostUsed(){
	    return showMostUsed;
	}

	void resetBinding() {
		showMostUsed=false;
		QString curWord = getCurWord();
		if (!active) return;
		QToolTip::hideText();
		//reenable auto close chars
		editor->setFlag(QEditor::AutoCloseChars,completer->editorAutoCloseChars);
		editor->setInputBinding(oldBinding);
		editor->setFocus();
		if (completer) {
			completer->widget->hide();
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
			completer->widget->show();
			select(completer->list->model()->index(0,0,QModelIndex()));
		}
	}


	bool isActive() {
		return active;
	}

	QString autoOverridenText;
private:
	bool active;
	bool showAlways;
	bool showMostUsed;
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
		bool drawPlaceholder = cw.placeHolders.empty();
		QString firstLine=cw.lines[0];
		if (!cw.getName().isEmpty()) {
			drawPlaceholder = false;
			firstLine = cw.getName();
		}
		if (!drawPlaceholder)
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine);
		else {
			QFontMetrics fmn(fNormal);
			QFontMetrics fmi(fItalic);
			int p=0;
			for (int i=0; i<cw.placeHolders[0].size(); i++) {
				QString temp=firstLine.mid(p,cw.placeHolders[0][i].offset-p);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmn.width(temp));
				temp=firstLine.mid(cw.placeHolders[0][i].offset,cw.placeHolders[0][i].length);
				painter->setFont(fItalic);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmi.width(temp)+1);
				p=cw.placeHolders[0][i].offset+cw.placeHolders[0][i].length;
				painter->setFont(fNormal);
				if (p>firstLine.length()) break;
			}
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine.mid(p));
		}
	}
};



//----------------------------list model------------------------------------
LatexCompleterConfig* CompletionListModel::config=0;
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
void CompletionListModel::filterList(const QString &word,bool mostUsed) {
	if (word==curWord && mostUsed==mostUsedUpdated) return; //don't return if mostUsed differnt from last call
	mostUsedUpdated=mostUsed;
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
		    (!checkFirstChar || baselist[i].word[1] == word[1]) ){
			if(!mostUsed || baselist[i].usageCount>0)
			    words.append(baselist[i]);
		    }
	}
	/*if (words.size()>=2) //prefer matching case
	   if (!words[0].word.startsWith(word,Qt::CaseSensitive) && words[1].word.startsWith(word,Qt::CaseSensitive))
	   	words.swap(0,1);*/
	curWord=word;
	reset();
}
void CompletionListModel::incUsage(const QModelIndex &index){
    if (!index.isValid())
	    return ;

    if (index.row() >= words.size())
	    return ;

    int j=index.row();
    CompletionWord curWord=words.at(j);
    if(curWord.usageCount<0)
	return; // don't count text words

    for (int i=0; i<wordsCommands.count(); i++) {
	if(wordsCommands[i].word==curWord.word){
	    wordsCommands[i].usageCount++;
	    if(curWord.snippetLength<=0)
		break; // no ref commands etc. are stored permanently
	    bool replaced=false;
	    QList<QPair<int,int> >res=config->usage.values(curWord.index);
	    for (int j = 0; j < res.size(); ++j) {
		if (res.at(j).first == curWord.snippetLength){
		    config->usage.remove(curWord.index,res.at(j));
		    config->usage.insert(curWord.index,qMakePair(curWord.snippetLength,wordsCommands[i].usageCount));
		    replaced=true;
		    break;
		}
	    }
	    if(!replaced)
		config->usage.insert(curWord.index,qMakePair(curWord.snippetLength,wordsCommands[i].usageCount)); // new word
	    break;
	}
    }
}

typedef QPair<int,int> PairIntInt;
void CompletionListModel::setBaseWords(const QStringList &newwords, bool normalTextList) {
	QList<CompletionWord> newWordList;
	acceptedChars.clear();
	newWordList.clear();
	for(int i=0;i<newwords.count();i++) {
		QString str=newwords.at(i);
		CompletionWord cw=CompletionWord(str);
		if(!normalTextList){
		    cw.index=qHash(str);
		    cw.snippetLength=str.length();
		    cw.usageCount=0;
		    QList<QPair<int,int> >res=config->usage.values(cw.index);
		    foreach(const PairIntInt elem,res){
			if(elem.first==cw.snippetLength){
			    cw.usageCount=elem.second;
			    break;
			}
		    }
		}else{
		    cw.index=0;
		    cw.usageCount=-1;
		    cw.snippetLength=0;
		}
		newWordList.append(cw);
		foreach(const QChar c, str) acceptedChars.insert(c);
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
	foreach(const CompletionWord cw, newwords) {
		newWordList.append(cw);
		foreach(const QChar c, cw.word) acceptedChars.insert(c);
	}
	qSort(newWordList.begin(), newWordList.end());

	if (normalTextList) wordsText=newWordList;
	else wordsCommands=newWordList;
	baselist=wordsCommands;
}

void CompletionListModel::setAbbrevWords(const QList<CompletionWord> &newwords) {
	wordsAbbrev=newwords;
}

void CompletionListModel::setConfig(LatexCompleterConfig*newConfig){
	config=newConfig;
}


//------------------------------completer-----------------------------------
QString LatexCompleter::helpFile;
QHash<QString, QString> LatexCompleter::helpIndices;
QHash<QString, int> LatexCompleter::helpIndicesCache;
LatexCompleterConfig* LatexCompleter::config=0;

LatexCompleter::LatexCompleter(QObject *p): QObject(p),maxWordLen(0),forcedRef(false) {
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
	list->setAutoFillBackground(true);
	editor=0;
	widget=new QWidget(qobject_cast<QWidget*>(parent()));
	//widget->setAutoFillBackground(true);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setSpacing(0);
	tbAbove=new QTabBar();
	tbAbove->setShape(QTabBar::RoundedNorth);
	tbAbove->addTab(tr("all"));
	tbAbove->addTab(tr("most used"));
	tbAbove->setToolTip(tr("press shift+space to change view"));
	layout->addWidget(tbAbove);
	tbAbove->hide();
	layout->addWidget(list);
	tbBelow=new QTabBar();
	tbBelow->setShape(QTabBar::RoundedSouth);
	tbBelow->addTab(tr("all"));
	tbBelow->addTab(tr("most used"));
	tbBelow->setToolTip(tr("press shift+space to change view"));
	layout->addWidget(tbBelow);
	widget->setLayout(layout);
	connect(list,SIGNAL(clicked(QModelIndex)),this,SLOT(listClicked(QModelIndex)));
	// todo: change tab when shift+space is pressed ...
	//connect(tbBelow,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	//connect(tbAbove,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
}

LatexCompleter::~LatexCompleter() {
	//delete list;
}

void LatexCompleter::changeView(int pos){
	completerInputBinding->setMostUsed(pos>0);
}

void LatexCompleter::listClicked(QModelIndex index){
    if (!completerInputBinding->insertCompletedWord()) {
	editor->insertText("\n");
    }
    completerInputBinding->resetBinding();
}

void LatexCompleter::insertText(QString txt){
    if(!isVisible())
	return;
    completerInputBinding->insertText(txt);
    QString cur=completerInputBinding->getCurWord();
    filterList(cur,completerInputBinding->getMostUsed());
}

void LatexCompleter::setAdditionalWords(const QStringList &newwords, bool normalTextList) {
	QStringList concated;
	if (config && !normalTextList) concated << config->words;
	//avoid duplicates !!!
	foreach(const QString elem,newwords){
	    if(!concated.contains(elem))
		concated << elem;
	}
	listModel->setBaseWords(concated,normalTextList);
	widget->resize(200,200);
	/*if (maxWordLen==0 && !normalTextList) {
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
		int wd=200>maxWordLen?200:maxWordLen;
		wd+=10;

	}*/
}

void LatexCompleter::adjustWidget(){
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
    int wd=200>maxWordLen?200:maxWordLen;
    QScrollBar *bar=list->verticalScrollBar();
    if(bar && bar->isVisible()){
	wd+=bar->width()*2;
    }
    widget->resize(wd,200);
}

void LatexCompleter::setAbbreviations(const QStringList &Abbrevs,const QStringList &Tags){
	QList<CompletionWord> wordsAbbrev;
	wordsAbbrev.clear();
	for(int i=0;i<Abbrevs.size();i++){
		QString abbr=Abbrevs.value(i,"");
		if(!abbr.isEmpty()){
			//CompletionWord cw(abbr);
			// for compatibility to texmaker ...
			QString s=Tags.value(i);
			if (s.left(1)=="%") {
				s=s.remove(0,1);
				s="\\begin{"+s+"}";
			}
			CompletionWord cw(s);
			// <!compatibility>
			cw.word=abbr;
			cw.sortWord=cw.word.toLower();
			cw.sortWord.replace("{","!");//js: still using dirty hack, however order should be ' '{[* abcde...
			cw.sortWord.replace("}","!");// needs to be replaced as well for sorting \bgein{abc*} after \bgein{abc}
			cw.sortWord.replace("[","\"");//(first is a space->) !"# follow directly in the ascii table
			cw.sortWord.replace("*","#");
			cw.setName(abbr+tr(" (Usertag)"));
			wordsAbbrev << cw;
		}
	}
	listModel->setAbbrevWords(wordsAbbrev);
}

void LatexCompleter::complete(QEditor *newEditor, const CompletionFlags& flags) {
	Q_ASSERT(list); Q_ASSERT(listModel); Q_ASSERT(completerInputBinding);
	forcedRef=flags & CF_FORCE_REF;
	if (editor != newEditor) {
		if (editor) disconnect(editor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		if (newEditor) connect(newEditor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		editor=newEditor;
	}
	if (!editor) return;
	QDocumentCursor c=editor->cursor();
	if (!c.isValid()) return;
	int phId=editor->currentPlaceHolder();
	if(phId>-1){
	    PlaceHolder ph=editor->getPlaceHolder(phId);
	    if(ph.cursor.isWithinSelection(c) && !ph.mirrors.isEmpty()){
		editor->removePlaceHolder(phId);
	    }
	}
	if (c.hasSelection()) {
		c.setColumnNumber(qMax(c.columnNumber(),c.anchorColumnNumber()));
		editor->setCursor(c);
	}
	QPoint offset;
	bool above=false;
	if (!editor->getPositionBelowCursor(offset, widget->width(), widget->height(),above))
		return;

	//disable auto close char while completer is open
	editorAutoCloseChars=editor->flag(QEditor::AutoCloseChars);
	editor->setFlag(QEditor::AutoCloseChars,false);

	//list->move(editor->mapTo(qobject_cast<QWidget*>(parent()),offset));
	disconnect(tbBelow,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	disconnect(tbAbove,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	if(above){
	    tbAbove->show();
	    tbBelow->hide();
	    tbAbove->setCurrentIndex(0);
	    connect(tbAbove,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	}else{
	    tbAbove->hide();
	    tbBelow->show();
	    tbBelow->setCurrentIndex(0);
	    connect(tbBelow,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	}
	widget->move(editor->mapTo(qobject_cast<QWidget*>(parent()),offset));
	//widget->show();
	if (flags & CF_NORMAL_TEXT) listModel->baselist=listModel->wordsText;
	else listModel->baselist=listModel->wordsCommands;
	listModel->baselist+=listModel->wordsAbbrev;
	qSort(listModel->baselist.begin(),listModel->baselist.end());
	if (c.previousChar()!='\\' || (flags & CF_FORCE_VISIBLE_LIST)) {
		int start=c.columnNumber()-1;
		if (flags & CF_NORMAL_TEXT) start=0;
		QString eow="~!@#$%^&*()_+}|:\"<>?,./;[]-= \n\r`+�\t";
		if (flags & CF_NORMAL_TEXT) eow+="{";
		if (flags & CF_FORCE_REF) eow="\\";
		QString lineText=c.line().text();
		for (int i=c.columnNumber()-1; i>=0; i--) {
			if (lineText.at(i)==QChar('\\')) {
				start=i;
				break;
			} else if (eow.contains(lineText.at(i))) {
				if (flags & CF_NORMAL_TEXT) start=i+1;
				break;
			}
		}
		completerInputBinding->bindTo(editor,this,true,start);
		adjustWidget();
	} else completerInputBinding->bindTo(editor,this,false,c.columnNumber()-1);

	//line.document()->cursor(0,0).insertText(QString::number(offset.x())+":"+QString::number(offset.y()));
	connect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
	
	completerInputBinding->autoOverridenText = (flags & CF_OVERRIDEN_BACKSLASH)?"\\":"";

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
void LatexCompleter::setConfig(LatexCompleterConfig* config){
	this->config=config;
	listModel->setConfig(config);
}
const LatexCompleterConfig* LatexCompleter::getConfig() const{
	return config;
}

void LatexCompleter::filterList(QString word,bool showMostUsed) {
	QString cur=""; //needed to preserve selection
	if (list->isVisible() && list->currentIndex().isValid())
		cur=list->model()->data(list->currentIndex(),Qt::DisplayRole).toString();
	listModel->filterList(word,showMostUsed);
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
	if (listModel->getAcceptedChars().contains(c))
		return true; //if no word contains the character don't accept it
	//if (listModel->isNextCharPossible(c))
	//	return true; //only accept non standard character, if one of the current words contains it
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
	QString cmd=wordrx.cap(0);
	QString id=helpIndices.value(cmd,"");
	if (id=="") return;
	QString topic;
	if(LatexParser::refCommands.contains(cmd)){
		QString value=listModel->words[index.row()].word;
		int i=value.indexOf("{");
		value.remove(0,i+1);
		i=value.indexOf("}");
		value=value.left(i);
		LatexDocument *document=qobject_cast<LatexDocument *>(editor->document());
		int cnt=document->countLabels(value);
		topic="";
		if(cnt==0){
		    topic=tr("label missing!");
		} else if(cnt>1) {
		    topic=tr("label multiple times defined!");
		} else {
		    QMultiHash<QDocumentLineHandle*,int> result=document->getLabels(value);
		    QDocumentLineHandle *mLine=result.keys().first();
		    int l=mLine->line();
		    if(mLine->document()!=editor->document()){
			//LatexDocument *doc=document->parent->findDocument(mLine->document());
			LatexDocument *doc=qobject_cast<LatexDocument *>(mLine->document());
			Q_ASSERT_X(doc,"missing latexdoc","qdoc is not latex document !");
			if(doc) topic=tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
		    }
		    for(int i=qMax(0,l-2);i<qMin(mLine->document()->lines(),l+3);i++){
			topic+=mLine->document()->line(i).text().left(80);
			if(mLine->document()->line(i).text().length()>80) topic+="...";
			if(i<l+2) topic+="\n";
		    }
		}
	}else{
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
		topic=helpFile.mid(pos);
		if (topic.left(opos-pos).contains("<dt>")) topic=topic.left(topic.indexOf("</dd>"));
		else {
			QRegExp anotherLink("<a\\s+name=\\s*\"[^\"]*\"(\\s+href=\\s*\"[^\"]*\")?>\\s*[^< ][^<]*</a>");
			int nextpos=anotherLink.indexIn(topic,opos-pos+aim.length());
			topic=topic.left(nextpos);
		}
	}
	topic.replace("\t","    "); //if there are tabs at the position in the string, qt crashes. (13707)
	QRect r = list->visualRect(index);
	QDocumentCursor c=editor->cursor();
	QRect screen = QApplication::desktop()->availableGeometry();
	int lineHeight=c.line().document()->getLineSpacing();
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

void LatexCompleterConfig::setFiles(const QStringList &newFiles) {
	files=newFiles;
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
		completerInputBinding->simpleRestoreAutoOverride();
		completerInputBinding->resetBinding();
		widget->setVisible(false);
		listModel->curWord="";
		return true;
	} else return false;
}
