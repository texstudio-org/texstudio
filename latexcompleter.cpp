#include "latexcompleter.h"
#include "latexcompleter_p.h"
#include "latexcompleter_config.h"

#include "smallUsefulFunctions.h"

#include "qdocumentline.h"
#include "qeditorinputbinding.h"
#include "qformatfactory.h"
#include "qdocumentline_p.h"

#include "latexdocument.h"
#include "qdocument.h"

#include <algorithm>


//------------------------------Default Input Binding--------------------------------
class CompleterInputBinding: public QEditorInputBinding {
public:
	CompleterInputBinding():active(0),showAlways(false),showMostUsed(0),completer(0),editor(0),oldBinding(0),curStart(0),maxWritten(0) {}
	virtual QString id() const {
		return "TXS::CompleterInputBinding";
	}
	virtual QString name() const {
		return "TXS::CompleterInputBinding";
	}
	
	virtual bool mousePressEvent(QMouseEvent* mouse, QEditor *editor) {
		// remove unused argument warnings
		Q_UNUSED(mouse);
		Q_UNUSED(editor);
		simpleRestoreAutoOverride();
		resetBinding();
		return false;
	}
	
	QString getCurWord() {
		if (!editor) return QString();
		//QMessageBox::information(0,curLine.text().mid(curStart,editor->cursor().columnNumber()-curStart),"",0);
		return editor->text(curLineNumber).mid(curStart,editor->cursor().columnNumber()-curStart);
	}
	
	// check if current cursor/placeholder is mirrored
	bool isMirrored(){
		if (!editor) return false;
		if ( editor->currentPlaceHolder() >= 0 && editor->currentPlaceHolder()<editor->placeHolderCount() )
		{
			PlaceHolder ph = editor->getPlaceHolder(editor->currentPlaceHolder());
			return ph.mirrors.count()>0;
		}
		return false;
	}
	
	void insertText(const QString& text){
		if (!editor) return;
		maxWritten += text.length();
		if ( editor->currentPlaceHolder() >= 0 && editor->currentPlaceHolder()<editor->placeHolderCount() )
			editor->document()->beginMacro();
		editor->cursor().insertText(text);
		//cursor mirrors
		if ( editor->currentPlaceHolder() >= 0 && editor->currentPlaceHolder()<editor->placeHolderCount() )
		{
			PlaceHolder ph = editor->getPlaceHolder(editor->currentPlaceHolder());
			
			QString baseText = ph.cursor.selectedText();
			
			for ( int phm = 0; phm < ph.mirrors.count(); ++phm )
			{
				//QString s = ph.affector ?  ph.affector->affect(text, baseText, m_curPlaceHolder, phm) : baseText;
				
				ph.mirrors[phm].replaceSelectedText(baseText);
			}
			editor->document()->endMacro();
		}
		//end cursor mirrors
		if (editor->cursor().columnNumber()>curStart+1 && !completer->isVisible()){
			QString wrd=getCurWord();
			completer->filterList(wrd,showMostUsed);
			completer->widget->show();
			if(showMostUsed==1 && completer->countWords()==0){ // if prefered list is empty, take next more extensive one
				completer->setTab(0);
			}
			if(showMostUsed==0 && completer->countWords()==0){
				completer->setTab(2);
			}
			completer->adjustWidget();
		}
	}
	
	bool insertCompletedWord() {
		if (!editor) return false;
		if (completer->list->isVisible() && maxWritten>=curStart && completer->list->currentIndex().isValid()) {
			QDocumentCursor cursor=editor->cursor();
			editor->document()->beginMacro();
			QVariant v=completer->list->model()->data(completer->list->currentIndex(),Qt::DisplayRole);
			if (!v.isValid() || !v.canConvert<CompletionWord>()) return false;
			CompletionWord cw= v.value<CompletionWord>();
			completer->listModel->incUsage(completer->list->currentIndex());
			//int alreadyWrittenLen=editor->cursor().columnNumber()-curStart;
			//remove current text for correct case
			if(completer->forcedRef){
				QString line = cursor.line().text();
				int col = cursor.columnNumber();
				bool missingCloseBracket = (findClosingBracket(line, col) < 0);
				while(!cursor.atLineEnd() && cursor.nextChar()!='}'
					   && !(cursor.nextChar().isSpace() && missingCloseBracket)) // spaces are allowed in labels and should be deleted, however we stop deleting at spaces if the closing bracket is missing. otherwise it deletes the complete line.
				{
					cursor.deleteChar();
				}
				if(cursor.nextChar()=='}')
					cursor.deleteChar();
			}
			if(completer->forcedCite){
				QString line = cursor.line().text();
				int col = cursor.columnNumber();
				bool missingCloseBracket = (findClosingBracket(line, col) < 0);
				QString eow="},";
				while(!cursor.atLineEnd() && !eow.contains(cursor.nextChar())
					   && !(cursor.nextChar().isSpace() && missingCloseBracket))
					cursor.deleteChar();
			}
			if(isMirrored() && (cw.lines.first().startsWith("\\begin")||cw.lines.first().startsWith("\\end"))){
				QString text=cw.lines.first();
				int i=cursor.columnNumber()-curStart;
				text.remove(0,i);
				i=text.indexOf('}');
				if(i>=0)
					text.remove(i,text.length());
				while(!cursor.atLineEnd() && cursor.nextChar()!='}'){
					cursor.deleteChar();
				}
				insertText(text);
				editor->document()->endMacro();
				return true;
			}
			for (int i=maxWritten-cursor.columnNumber(); i>0; i--) cursor.deleteChar();
			for (int i=cursor.columnNumber()-curStart; i>0; i--) cursor.deletePreviousChar();
			if (!autoOverridenText.isEmpty()){
				cursor.insertText(autoOverridenText);
				cursor.movePosition(autoOverridenText.length(), QDocumentCursor::PreviousCharacter);
				editor->resizeAutoOverridenPlaceholder(cursor, autoOverridenText.size());
				autoOverridenText="";
			}
			//cursor.endEditBlock(); //doesn't work and lead to crash when auto indentation is enabled => TODO:figure out why
			//  cursor.setColumnNumber(curStart);
			CodeSnippet::PlaceholderMode phMode = (LatexCompleter::config && LatexCompleter::config->usePlaceholders) ? CodeSnippet::PlacehodersActive : CodeSnippet::PlaceholdersRemoved;
			cw.insertAt(editor,&cursor, phMode,!completer->startedFromTriggerKey);
			editor->document()->endMacro();
			
			return true;
		}
		return false;
	}
	
	void removeRightWordPart() {
		if (!editor) return;
		QDocumentCursor cursor=editor->cursor();
		for (int i=maxWritten-cursor.columnNumber(); i>0; i--) cursor.deleteChar();
		maxWritten=cursor.columnNumber();
		editor->setCursor(cursor);//necessary to keep the cursor at the same place (but why???)  TODO: remove this line (it cause \ to disable placeholders which other keys don't disable)
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
	
    bool completeCommonPrefix(bool reducedRange=false){
		QString my_curWord=getCurWord();
		if (my_curWord.isEmpty()) return false;
		if (!completer) return false;
		/*if (!completer->list->isVisible()) {
			resetBinding();
			return false;
		}*/
		// get list of most recent choices
		const QList<CompletionWord> &words=completer->listModel->getWords();
		// filter list for longest common characters
		if (words.count()>1) {
            QString myResult=words.first().word;
            int my_start=my_curWord.length();
            my_curWord=completer->listModel->getLastWord().word;

            if(reducedRange &&words.count()>10){
                my_curWord=words.at(10).word;
            }
            for (int j=my_start; (j<my_curWord.length()&&j<myResult.length()); j++) {
                if (myResult[j]!=my_curWord[j]) {
                    myResult=myResult.left(j);
                }
            }

            removeRightWordPart();
            insertText(myResult.right(myResult.length()-my_start));
            //maxWritten+=myResult.length()-my_start; insert text already adapt maxWritten
            completer->filterList(getCurWord(),getMostUsed());
            if (!completer->list->currentIndex().isValid())
                select(completer->list->model()->index(0,0,QModelIndex()));
            return true;
		} else {
			if(showMostUsed==1) return false;
			insertCompletedWord();
			resetBinding();
			return true;
		}
	}	
	
	void simpleRestoreAutoOverride(const QString& written="????"){ //simple means without protecting the change from undo/redo
		if (!editor) return;
		if (!autoOverridenText.isEmpty() && !editor->isAutoOverrideText(written)) {
			int curpos = editor->cursor().columnNumber();
			if (curpos < maxWritten) {
				QDocumentCursor c = editor->cursor();
				c.movePosition(maxWritten-curpos, QDocumentCursor::NextCharacter);
				editor->setCursor(c);
			}
			editor->insertText(autoOverridenText);
			QDocumentCursor c = editor->cursor();
			c.movePosition(autoOverridenText.length() + (curpos<maxWritten?maxWritten-curpos:0), QDocumentCursor::PreviousCharacter);
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
			editor->setCursorPosition(curLineNumber,editor->cursor().columnNumber()-1);
			if (editor->cursor().columnNumber()<=curStart) resetBinding();
			handled=true;
		} else if (event->key()==Qt::Key_Right) {
			if (event->modifiers()) {
				resetBinding();
				return false;
			}
			editor->setCursorPosition(curLineNumber,editor->cursor().columnNumber()+1);
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
            return completeCommonPrefix(true);
		}  else if (event->key()==Qt::Key_Space && event->modifiers()==Qt::ShiftModifier) {
			//showMostUsed=!showMostUsed;
			//handled=true;
			showMostUsed++;
			if(showMostUsed>2)
				showMostUsed=0;
			completer->tbAbove->setCurrentIndex(showMostUsed);
			completer->tbBelow->setCurrentIndex(showMostUsed);
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
				bool autoOverride = editor->isAutoOverrideText("\\");
				if (!autoOverride) editor->cursor().insertText(written);
				else { 
					QDocumentCursor c = editor->cursor();
					editor->document()->beginMacro();
					c.deleteChar();
					c.insertText("\\");
					editor->document()->endMacro();
					autoOverridenText = "\\";
				}
				//editor->insertText(written); <- can't use that since it may break the completer by auto closing brackets
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
		if (c.lineNumber()!=curLineNumber || c.columnNumber()<curStart) resetBinding();
	}
	
	void setMostUsed(int mu,bool quiet=false){
		showMostUsed=mu;
		if(quiet)
			return;
		completer->filterList(getCurWord(),showMostUsed);
		if (!completer->list->currentIndex().isValid())
			select(completer->list->model()->index(0,0,QModelIndex()));
	}
	
	int getMostUsed(){
		return showMostUsed;
	}
	
	void resetBinding() {
		completer->listModel->setEnvironMode(false);
		showMostUsed=false;
		QString curWord = getCurWord();
		if (!active) return;
		QToolTip::hideText();
		//reenable auto close chars
		editor->setFlag(QEditor::AutoCloseChars,completer->editorAutoCloseChars);
		editor->setInputBinding(oldBinding);
		if (completer && completer->widget && completer->widget->isVisible())
			editor->setFocus();
		if (completer) {
			completer->widget->hide();
			completer->disconnect(editor,SIGNAL(cursorPositionChanged()),completer,SLOT(cursorPositionChanged()));
			
		}
		active=false;
        //editor=0; this leads to a crash, as the editor is still in use after reseting the cursor
		if(completer && completer->completingGraphic() && curWord.endsWith(QDir::separator())){
			completer->complete(editor,LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_GRAPHIC));
		}
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
		curLineNumber=editor->cursor().lineNumber();
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
	int showMostUsed;
	LatexCompleter *completer;
	QEditor * editor;
	QEditorInputBindingInterface* oldBinding;
	QString completionWord;
	int curStart,maxWritten;
	int curLineNumber;
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
		QFont fPlHolder=option.font;
		//fPlHolder.setItalic(true);
		QColor normalColor, plHolderColor;
		if ((QStyle::State_HasFocus | QStyle::State_Selected) & option.state) {
			painter->fillRect(option.rect,option.palette.brush(QPalette::Highlight));
			normalColor = option.palette.color(QPalette::HighlightedText);
		} else {
			painter->fillRect(option.rect,option.palette.brush(QPalette::Base));//doesn't seem to be necessary
			normalColor = option.palette.color(QPalette::Text);
		}
		painter->setPen(normalColor);
		plHolderColor = normalColor;
		plHolderColor.setAlpha(128);

		QRect r=option.rect;
		r.setLeft(r.left()+2);
		bool drawPlaceholder = !cw.placeHolders.empty();
		QString firstLine=cw.lines[0];
		if (!cw.getName().isEmpty()) {
			drawPlaceholder = false;
			firstLine = cw.getName();
		}
		if (!drawPlaceholder)
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine);
		else {
			QFontMetrics fmn(fNormal);
			QFontMetrics fmi(fPlHolder);
			int p=0;
			for (int i=0; i<cw.placeHolders[0].size(); i++) {
				QString temp=firstLine.mid(p,cw.placeHolders[0][i].offset-p);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmn.width(temp));
				temp=firstLine.mid(cw.placeHolders[0][i].offset,cw.placeHolders[0][i].length);
				painter->setFont(fPlHolder);
				painter->setPen(plHolderColor);
				painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
				r.setLeft(r.left()+fmi.width(temp)+1);
				p=cw.placeHolders[0][i].offset+cw.placeHolders[0][i].length;
				painter->setFont(fNormal);
				painter->setPen(normalColor);
				if (p>firstLine.length()) break;
			}
			painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, firstLine.mid(p));
		}
	}
};



//----------------------------list model------------------------------------
LatexCompleterConfig* CompletionListModel::config=0;
int CompletionListModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	
	return words.count();
}
QVariant CompletionListModel::data(const QModelIndex &index, int role)const{
	if (!index.isValid())
		return QVariant();
	
	if (index.row() >= words.count())
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
	Q_UNUSED(role);
	Q_UNUSED(orientation);
	Q_UNUSED(section);
	
	return QVariant();
}
bool CompletionListModel::isNextCharPossible(const QChar &c){
	//if (words.count()>100) //probable that every char is there (especially since acceptedChars is already checked)
	//	return true;  -> leads to faulty behaviour (\b{ is supposed to be within list ...)
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	if (LatexCompleter::config && 
	              LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_CASE_SENSITIVE)
		cs=Qt::CaseSensitive;
	QString extension=curWord+c;
	foreach (const CompletionWord & cw, words)
		if (cw.word.startsWith(extension,cs)) return true;
	return false;
}
bool CompletionListModel::canFetchMore(const QModelIndex &) const{
	return mCanFetchMore;
}
void CompletionListModel::fetchMore(const QModelIndex &){
	beginInsertRows(QModelIndex(),words.count(),qMin(words.count()+100,mWordCount));
	filterList(mLastWord,mLastMU,true);
	endInsertRows();
}
CompletionWord CompletionListModel::getLastWord(){
	return mLastWordInList;
}


QString makeSortWord(const QString& normal) {
	QString res = normal.toLower();
	res.replace("{","!");//js: still using dirty hack, however order should be ' '{[* abcde...
	res.replace("}","!");// needs to be replaced as well for sorting \bgein{abc*} after \bgein{abc}
	res.replace("[","\\");//(first is a space->) !"# follow directly in the ascii table
	res.replace("*","#");
	return res;
}
void CompletionListModel::setEnvironMode(bool mode){
    mEnvMode=mode;
}

void CompletionListModel::filterList(const QString &word,int mostUsed,bool fetchMore) {
	if(mostUsed<0)
		mostUsed=LatexCompleter::config->preferedCompletionTab;
	if (word==curWord && mostUsed==mostUsedUpdated && !fetchMore) return; //don't return if mostUsed differnt from last call
	mLastWord=word;
	mLastMU=mostUsed;
	mCanFetchMore=false;
	mostUsedUpdated=mostUsed;
	if(!fetchMore)
		words.clear();
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	bool checkFirstChar=false;
	if (LatexCompleter::config){
		if (LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_CASE_SENSITIVE)
			cs=Qt::CaseSensitive;
		checkFirstChar=LatexCompleter::config->caseSensitive==LatexCompleterConfig::CCS_FIRST_CHARACTER_CASE_SENSITIVE && word.length()>1;
	}
	int cnt=0;
	QString sortWord = makeSortWord(word);
	if(!fetchMore){
        it=qLowerBound(baselist.begin(),baselist.end(),CompletionWord(word));
	}
    // special treatment for citation commands as they generated on the fly
    if(it == baselist.end() || !it->word.startsWith(word,cs)){
        int i=word.lastIndexOf("{");
        QString test=word.left(i)+"{@}";
        if (wordsCitationCommands.contains(CompletionWord(test))){
            QString citeStart=word.mid(i+1);
            foreach(const CompletionWord id,wordsCitations){
                if(id.word.startsWith(citeStart)){
                    CompletionWord cw(test);
                    cw.word.replace("@",id.word);
                    cw.sortWord.replace("@",id.word);
                    cw.lines[0].replace("@",id.word);
                    words.append(cw);
                }
            }
        }
    }
    //
	while(it!=baselist.end()){
		if (it->word.startsWith(word,cs) &&
		              (!checkFirstChar || it->word[1] == word[1]) ){

			if(mostUsed==2 || it->usageCount>=mostUsed || it->usageCount==-2){
                if(mEnvMode){
                    CompletionWord cw=*it;
                    if(cw.word.startsWith("\\begin")||cw.word.startsWith("\\end")){
                        QString text=cw.word;
                        int i=text.indexOf('}');
                        text.truncate(i+1);
                        cw.word=text;
                        cw.sortWord=text;
                        cw.lines=QStringList(text);
                        cw.placeHolders.clear();
                        cw.placeHolders.append(QList<CodeSnippetPlaceHolder>());
                    }

                    if(!words.contains(cw))
                        words.append(cw);
                }else{
                    // cite command
                    if(wordsCitationCommands.contains(*it)){
                        foreach(const CompletionWord id,wordsCitations){
                            CompletionWord cw=*it;
                            cw.word.replace("@",id.word);
                            cw.sortWord.replace("@",id.word);
                            cw.lines[0].replace("@",id.word);
                            words.append(cw);
                        }
                        cnt+=wordsCitations.length();
                    }else{
                        words.append(*it);
                    }
                }
				cnt++;
			}
		}else{
			if(!it->sortWord.startsWith(sortWord))
				break; // sorted list
		}
		++it;
		if(cnt>100){
			mCanFetchMore=true;
			break;
		}
	}
	curWord=word;
	if(!fetchMore){
		mWordCount=words.count();
		if(!words.isEmpty())
			mLastWordInList=words.last();
	}
	if(mCanFetchMore && !fetchMore){
		// calculate real number of rows
		QString wordp=word;
		if(wordp.isEmpty()){
			mWordCount=baselist.count();
			mLastWordInList=baselist.last();
		}else{
			QChar lst=wordp[wordp.length()-1];
			ushort nr=lst.unicode();
			wordp[wordp.length()-1]=QChar(nr+1);
			QList<CompletionWord>::const_iterator it2=qLowerBound(baselist,CompletionWord(wordp));
			mWordCount=it2-it;
			mLastWordInList=*(--it2);
		}
	}
	
    if(!fetchMore){
#if QT_VERSION>=QT_VERSION_CHECK(5,0,0)
        beginResetModel();
        endResetModel();
#else
		reset();
#endif
    }
}
void CompletionListModel::incUsage(const QModelIndex &index){
	if (!index.isValid())
		return ;
	
	if (index.row() >= words.size())
		return ;
	
	int j=index.row();
	CompletionWord curWord=words.at(j);
	if(curWord.usageCount<-1)
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
void CompletionListModel::setBaseWords(const QSet<QString> &newwords, CompletionType completionType) {
	QList<CompletionWord> newWordList;
	acceptedChars.clear();
	newWordList.clear();
	for(QSet<QString>::const_iterator i=newwords.constBegin();i!=newwords.constEnd();++i) {
		QString str=*i;
		CompletionWord cw(str);
		if(completionType==CT_COMMANDS){
			cw.index=qHash(str);
			cw.snippetLength=str.length();
			cw.usageCount=0;
			QList<QPair<int,int> >res=config->usage.values(cw.index);
			foreach(const PairIntInt& elem,res){
				if(elem.first==cw.snippetLength){
					cw.usageCount=elem.second;
					break;
				}
			}
		}else{
			cw.index=0;
			cw.usageCount=-2;
			cw.snippetLength=0;
		}
		newWordList.append(cw);
		foreach(const QChar& c, str) acceptedChars.insert(c);
	}
	qSort(newWordList.begin(), newWordList.end());
	
	switch(completionType){
	case CT_NORMALTEXT:
	    wordsText=newWordList;
	    break;
	case CT_CITATIONS:
	    wordsCitations=newWordList;
	    break;
	default:
	    wordsCommands=newWordList;
	}

	//if (completionType==CT_NORMALTEXT) wordsText=newWordList;
	//else wordsCommands=newWordList;
	baselist=wordsCommands;
}

void CompletionListModel::setBaseWords(const QList<CompletionWord> &newwords, CompletionType completionType) {
	QList<CompletionWord> newWordList;
	acceptedChars.clear();
	newWordList.clear();
	foreach(const CompletionWord& cw, newwords) {
		newWordList.append(cw);
		foreach(const QChar& c, cw.word) acceptedChars.insert(c);
	}
	qSort(newWordList.begin(), newWordList.end());
	
	//if (completionType==CT_NORMALTEXT) wordsText=newWordList;
	//else wordsCommands=newWordList;
	switch(completionType){
	case CT_NORMALTEXT:
	    wordsText=newWordList;
	    break;
	case CT_CITATIONS:
	    wordsCitations=newWordList;
	    break;
	default:
	    wordsCommands=newWordList;
	}

	baselist=wordsCommands;
}

void CompletionListModel::setBaseWords(const QSet<QString> &baseCommands,const QSet<QString> &newwords, CompletionType completionType) {
    QList<CompletionWord> newWordList;
    acceptedChars.clear();
    newWordList.clear();
    for(QSet<QString>::const_iterator i=baseCommands.constBegin();i!=baseCommands.constEnd();++i) {
        QString str=*i;
        CompletionWord cw(str);
        if(completionType==CT_COMMANDS){
            cw.index=qHash(str);
            cw.snippetLength=str.length();
            cw.usageCount=0;
            QList<QPair<int,int> >res=config->usage.values(cw.index);
            foreach(const PairIntInt& elem,res){
                if(elem.first==cw.snippetLength){
                    cw.usageCount=elem.second;
                    break;
                }
            }
        }else{
            cw.index=0;
            cw.usageCount=-2;
            cw.snippetLength=0;
        }
        newWordList.append(cw);
        foreach(const QChar& c, str) acceptedChars.insert(c);
    }
    for(QSet<QString>::const_iterator i=newwords.constBegin();i!=newwords.constEnd();++i) {
        QString str=*i;
        if(baseCommands.contains(str))
            continue;
        bool isReference=str.startsWith('@');
        if(isReference)
            str=str.mid(1);
        CompletionWord cw(str);
        if(completionType==CT_COMMANDS){
            cw.index=qHash(str);
            cw.snippetLength=str.length();
            cw.usageCount= isReference ? 2 : 0; // make reference always visible (most used) in completer
            QList<QPair<int,int> >res=config->usage.values(cw.index);
            foreach(const PairIntInt& elem,res){
                if(elem.first==cw.snippetLength){
                    cw.usageCount=elem.second;
                    break;
                }
            }
        }else{
            cw.index=0;
            cw.usageCount=-2;
            cw.snippetLength=0;
        }
        newWordList.append(cw);
        foreach(const QChar& c, str) acceptedChars.insert(c);
    }
    qSort(newWordList.begin(), newWordList.end());

    switch(completionType){
    case CT_NORMALTEXT:
        wordsText=newWordList;
        break;
    case CT_CITATIONS:
        wordsCitations=newWordList;
        break;
    case CT_CITATIONCOMMANDS:
        wordsCitationCommands=newWordList;
        break;
    default:
        wordsCommands=newWordList;
    }

    baselist=newWordList;
}

void CompletionListModel::setAbbrevWords(const QList<CompletionWord> &newwords) {
	wordsAbbrev=newwords;
}

void CompletionListModel::setCitationWords(const QList<CompletionWord> &newwords) {
	wordsCitations=newwords;
}

void CompletionListModel::setConfig(LatexCompleterConfig*newConfig){
	config=newConfig;
}


//------------------------------completer-----------------------------------
QString LatexCompleter::helpFile;
QHash<QString, QString> LatexCompleter::helpIndices;
QHash<QString, int> LatexCompleter::helpIndicesCache;
LatexCompleterConfig* LatexCompleter::config=0;

LatexCompleter::LatexCompleter(const LatexParser& latexParser, QObject *p): QObject(p),latexParser(latexParser),maxWordLen(0),forcedRef(false),forcedGraphic(false),startedFromTriggerKey(false) {
	//   addTrigger("\\");
	if (!qobject_cast<QWidget*>(parent()))
		QMessageBox::critical(0,"Serious PROBLEM", QString("The completer has been created without a parent widget. This is impossible!\n")+
		                      QString("Please report it ASAP to the bug tracker on texstudio.sf.net and check if your computer is going to explode!\n")+
		                      QString("(please report the bug *before* going to a safe place, you could rescue others)"),QMessageBox::Ok);
	list=new QListView(qobject_cast<QWidget*>(parent()));
	listModel=new CompletionListModel(list);
	connect(list, SIGNAL(clicked(const QModelIndex &)) , this, SLOT(selectionChanged(const QModelIndex &)));
	list->setModel(listModel);
	list->setFocusPolicy(Qt::NoFocus);
	list->setItemDelegate(new CompletionItemDelegate(list));
	list->setAutoFillBackground(true);
	editor=0;
	workingDir="/";
	dirReader=0;
    bibReader=0;
	widget=new QWidget(qobject_cast<QWidget*>(parent()));
	//widget->setAutoFillBackground(true);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setSpacing(0);
	tbAbove=new QTabBar();
	tbAbove->setShape(QTabBar::RoundedNorth);
	tbAbove->addTab(tr("typical"));
	tbAbove->addTab(tr("most used"));
	tbAbove->addTab(tr("all"));
	tbAbove->setToolTip(tr("press shift+space to change view"));
	layout->addWidget(tbAbove);
	tbAbove->hide();
	layout->addWidget(list);
	tbBelow=new QTabBar();
	tbBelow->setShape(QTabBar::RoundedSouth);
	tbBelow->addTab(tr("typical"));
	tbBelow->addTab(tr("most used"));
	tbBelow->addTab(tr("all"));
	tbBelow->setToolTip(tr("press shift+space to change view"));
	layout->addWidget(tbBelow);
	widget->setLayout(layout);
	widget->setContextMenuPolicy(Qt::PreventContextMenu);
	connect(list,SIGNAL(activated(QModelIndex)),this,SLOT(listClicked(QModelIndex)));
	// todo: change tab when shift+space is pressed ...
	//connect(tbBelow,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	//connect(tbAbove,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
}

LatexCompleter::~LatexCompleter() {
	if(dirReader){
		dirReader->quit();
		dirReader->wait();
	}
	if(bibReader){
		bibReader->quit();
		bibReader->wait();
	}
	//delete list;
}

void LatexCompleter::changeView(int pos){
	completerInputBinding->setMostUsed(pos);
}

void LatexCompleter::listClicked(QModelIndex index){

	Q_UNUSED(index);
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

void LatexCompleter::setAdditionalWords(const QSet<QString> &newwords, CompletionType completionType) {
	QSet<QString> concated;
	if (config && completionType==CT_COMMANDS) concated.unite(config->words.toSet());
	//concated.unite(newwords);
	listModel->setBaseWords(concated,newwords,completionType);
	widget->resize(200,200);
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


void LatexCompleter::updateAbbreviations(){
	REQUIRE(config);
	QList<CompletionWord> wordsAbbrev;
	foreach (const Macro &macro, config->userMacros) {
		if (macro.abbrev.isEmpty())
			continue;
		//CompletionWord cw(abbr);
		// for compatibility to texmaker ...
		QString s = macro.tag;
		if (s.left(1) == "%") {
			s = s.remove(0,1);
			s = "\\begin{"+s+"}";
		}
		CompletionWord cw(s);
		// <!compatibility>
		cw.word = macro.abbrev;
		cw.sortWord = makeSortWord(cw.word);
		cw.setName(macro.abbrev+tr(" (Usertag)"));
		wordsAbbrev << cw;
	}
	listModel->setAbbrevWords(wordsAbbrev);
}

void LatexCompleter::complete(QEditor *newEditor, const CompletionFlags& flags) {
	Q_ASSERT(list); Q_ASSERT(listModel); Q_ASSERT(completerInputBinding);
	forcedRef=flags & CF_FORCE_REF;
	forcedGraphic=flags & CF_FORCE_GRAPHIC;
	forcedCite=flags & CF_FORCE_CITE;
	startedFromTriggerKey= !(flags &CF_FORCE_VISIBLE_LIST);
	if (editor != newEditor) {
		if (editor) disconnect(editor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		if (newEditor) connect(newEditor,SIGNAL(destroyed()), this, SLOT(editorDestroyed()));
		editor=newEditor;
	}
	if (!editor) return;
	QDocumentCursor c=editor->cursor();
	if (!c.isValid()) return;
	/*int phId=editor->currentPlaceHolder();
	if(phId>-1 && phId<editor->placeHolderCount()){
		PlaceHolder ph=editor->getPlaceHolder(phId);
		if(ph.cursor.isWithinSelection(c) && !ph.mirrors.isEmpty()){
			editor->removePlaceHolder(phId);
		}
	}*/
	if (editor->cursorMirrorCount() > 0) return; // completer does not handle cursor mirrors. It would just remove them. -> don't use completer

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
	QTabBar * tbOn = above?tbAbove:tbBelow;
	QTabBar * tbOff = above?tbBelow:tbAbove;
	disconnect(tbOn,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	disconnect(tbOff,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	tbOn->show();
	tbOff->hide();
	tbOn->setCurrentIndex(config->preferedCompletionTab);
	connect(tbOn,SIGNAL(currentChanged(int)),this,SLOT(changeView(int)));
	
	completerInputBinding->setMostUsed(config->preferedCompletionTab,true);
	widget->move(editor->mapTo(qobject_cast<QWidget*>(parent()),offset));
	//widget->show();
	if(forcedGraphic){
		if(!dirReader){
			dirReader=new directoryReader(this);
			connect(dirReader,SIGNAL(directoryLoaded(QString,QSet<QString>)),this,SLOT(directoryLoaded(QString,QSet<QString>)));
			connect(this,SIGNAL(setDirectoryForCompletion(QString)),dirReader,SLOT(readDirectory(QString)));
			dirReader->start();
		}
		QSet<QString> files;
		listModel->setBaseWords(files,CT_NORMALTEXT);
		listModel->baselist=listModel->wordsText;
	}else{
		if(forcedCite){
			listModel->baselist=listModel->wordsCitations;
		}else{
			if (flags & CF_NORMAL_TEXT) listModel->baselist=listModel->wordsText;
			else listModel->baselist=listModel->wordsCommands;
			listModel->baselist << listModel->wordsAbbrev;
			QList<CompletionWord>::iterator middle=listModel->baselist.end()-listModel->wordsAbbrev.length();
			std::inplace_merge(listModel->baselist.begin(),middle,listModel->baselist.end());
		}
	}
	if ( editor->currentPlaceHolder() >= 0 && editor->currentPlaceHolder()<editor->placeHolderCount() )
	{
		PlaceHolder ph = editor->getPlaceHolder(editor->currentPlaceHolder());
		if(ph.mirrors.count()>0)
			listModel->setEnvironMode(true);
	}
	//qSort(listModel->baselist.begin(),listModel->baselist.end());
	if (c.previousChar()!='\\' || (flags & CF_FORCE_VISIBLE_LIST)) {
		int start=c.columnNumber()-1;
		if (flags & CF_NORMAL_TEXT) start=0;
		if (flags & CF_FORCE_GRAPHIC) start=0;
		QString eow="~!@#$%^&*()_+}|:\"<>?,./;[]-= \n\r`+�\t";
		if (flags & CF_NORMAL_TEXT) eow+="{";
		if (flags & CF_FORCE_CITE){
			eow+="{";
			eow.remove(".");
			eow.remove(":");
			eow.remove("_");
		}
		if (flags & CF_FORCE_GRAPHIC) {
			eow+="{";
			eow.remove("/");
			eow.remove("\\");
			eow.remove(".");
			eow.remove(":");
			eow.remove("_");
		}
		if (flags & CF_FORCE_REF) eow="\\";
		QString lineText=c.line().text();
		for (int i=c.columnNumber()-1; i>=0; i--) {
			if ((lineText.at(i)==QChar('\\'))&&!(flags & CF_FORCE_GRAPHIC)) {
				start=i;
				break;
			} else if (eow.contains(lineText.at(i))) {
				if (flags & CF_NORMAL_TEXT) start=i+1;
				if (flags & CF_FORCE_GRAPHIC) start=i+1;
				if (flags & CF_FORCE_CITE) start=i+1;
				break;
			}
		}
		QString path;
		if(flags & CF_FORCE_GRAPHIC){
			QString fn=lineText.mid(start,c.columnNumber()-start);
			int lastIndex=fn.lastIndexOf(QDir::separator());
			if(lastIndex>=0)
				start=start+lastIndex+1;
			if(fn.isEmpty())
				fn=workingDir+QDir::separator();
			QDir oldCurrent=QDir::current();
			QDir::setCurrent(workingDir);
			QFileInfo fi(fn);
			path=fi.absolutePath();
			QDir::setCurrent(oldCurrent.dirName()); //restore old current path
		}
		completerInputBinding->bindTo(editor,this,true,start);
		adjustWidget();
		
		if((flags & CF_FORCE_GRAPHIC) && !path.isEmpty()){
			emit setDirectoryForCompletion(path);
		}
	} else completerInputBinding->bindTo(editor,this,false,c.columnNumber()-1);
	
	if(completerInputBinding->getMostUsed()==1 && countWords()==0){ // if prefered list is empty, take next more extensive one
		setTab(0);
		adjustWidget();
	}
	if(completerInputBinding->getMostUsed() && countWords()==0){
		setTab(2);
		adjustWidget();
	}
	
	if (completerInputBinding->getMostUsed() == config->preferedCompletionTab)
		completerInputBinding->setMostUsed(config->preferedCompletionTab,false);		
	
	//line.document()->cursor(0,0).insertText(QString::number(offset.x())+":"+QString::number(offset.y()));
	connect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
	
	completerInputBinding->autoOverridenText = (flags & CF_OVERRIDEN_BACKSLASH)?"\\":"";
	
	if (config && config->completeCommonPrefix) completerInputBinding->completeCommonPrefix();
}

void LatexCompleter::directoryLoaded(QString ,QSet<QString> content){
	listModel->setBaseWords(content,CT_NORMALTEXT);
	listModel->baselist=listModel->wordsText;
	//setTab(2);
	completerInputBinding->setMostUsed(2);
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
	REQUIRE(config);
	this->config=config;
	listModel->setConfig(config);
	
	QFont f(QApplication::font());
	f.setPointSize( f.pointSize() * config->tabRelFontSizePercent / 100);
	tbAbove->setFont(f);
	tbBelow->setFont(f);
}
LatexCompleterConfig* LatexCompleter::getConfig() const{
	return config;
}

int LatexCompleter::countWords() {
	return listModel->getWords().count();
}

void LatexCompleter::setTab(int index){
	Q_ASSERT(index>=0 && index<3);
	if(tbBelow->isVisible())
		tbBelow->setCurrentIndex(index);
	if(tbAbove->isVisible())
		tbAbove->setCurrentIndex(index);
}

void LatexCompleter::filterList(QString word,int showMostUsed) {
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
	if (!index.isValid()) return;
    if(forcedGraphic){ // picture preview even if help is disabled (maybe the same for cite/ref ?)
        QString fn=workingDir+QDir::separator()+listModel->words[index.row()].word;
        emit showImagePreview(fn);
        return;
    }
    if (!config->tooltipHelp) return;
	if (index.row() < 0 || index.row()>=listModel->words.size()) return;
	QRegExp wordrx("^\\\\([^ {[*]+|begin\\{[^ {}]+)");
	if (!forcedCite && wordrx.indexIn(listModel->words[index.row()].word)==-1) return;
	QString cmd=wordrx.cap(0);
	QString id=helpIndices.value(cmd,"");
	if (!forcedCite && id=="") return;
	QString topic;
	if(latexParser.possibleCommands["%ref"].contains(cmd)){
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
			int l=mLine->document()->indexOf(mLine);
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
        if(forcedCite || latexParser.possibleCommands["%cite"].contains(cmd)){
            QString value=listModel->words[index.row()].word;
            int i=value.indexOf("{");
            value.remove(0,i+1);
            i=value.indexOf("}");
            value=value.left(i);
            LatexDocument *document=qobject_cast<LatexDocument *>(editor->document());
            if(!bibReader){
                bibReader=new bibtexReader(this);
                connect(bibReader,SIGNAL(sectionFound(QString)),this,SLOT(bibtexSectionFound(QString)));
                connect(this,SIGNAL(searchBibtexSection(QString,QString)),bibReader,SLOT(searchSection(QString,QString)));
                bibReader->start();
            }
            QString file=document->findFileFromBibId(value);
            if(!file.isEmpty())
                emit searchBibtexSection(file,value);
            return;
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
    }
    showTooltip(topic);
}

void LatexCompleter::showTooltip(QString topic){
    QModelIndex index=list->currentIndex();
    topic.replace("\t","    "); //if there are tabs at the position in the string, qt crashes. (13707)
    QRect r = list->visualRect(index);
    QDocumentCursor c=editor->cursor();
    //QRect screen = QApplication::desktop()->availableGeometry();
    int lineHeight=c.line().document()->getLineSpacing();
    QPoint tt=list->mapToGlobal(QPoint(list->width(), r.top()-lineHeight));
    //int lineY=editor->mapToGlobal(editor->mapFromContents(c.documentPosition())).y();
    // estimate width of coming tooltip
    // rather dirty code
    showTooltipLimited(tt,topic,list->width());
    /*
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
    lLabel.setFont(QToolTip::font());
    //lLabel.setWordWrap(true);
    //lLabel.ensurePolished();
    lLabel.setText(topic);
    lLabel.adjustSize();


    int textWidthInPixels = lLabel.width()+10; // +10 good guess

    if(lineY>tt.y()){
        tt.setY(lineY-lLabel.height()-lineHeight-5);
    }

    if (screen.width()-textWidthInPixels>=tt.x()) QToolTip::showText(tt, topic, list);//-90
    else {
        //list->mapToGlobal
        QPoint tt2=list->mapToGlobal(QPoint(-textWidthInPixels, r.top()-lineHeight));
        // check if text left from list would fit
        qDebug()<<tt2.x();
        bool reCalc=false;
        if(tt2.x()<0){
            //determine max usable width
            int w=list->mapToGlobal(QPoint(0, r.top()-lineHeight)).x();
            if(screen.width()-tt.x()>w){
                w=screen.width()-tt.x();
                tt2=tt;
            }else{
                reCalc=true;
            }
            // shorten text to fit textwidth
            QStringList lTopic=topic.split("\n");
            int maxLength=0;
            QString maxLine;
            foreach(const QString elem,lTopic){
                if(elem.length()>maxLength){
                    maxLength= elem.length();
                    maxLine=elem;
                }
            }
            while(textWidthInPixels>w && maxLength>10){
                maxLength--;
                lLabel.setText(maxLine.left(maxLength));
                lLabel.adjustSize();
                textWidthInPixels=lLabel.width()+10;
            }
            for(int i=0;i<lTopic.count();i++){
                lTopic[i]=lTopic[i].left(maxLength);
            }
            topic=lTopic.join("\n");
        }
        if(reCalc)
            tt2=list->mapToGlobal(QPoint(-textWidthInPixels, r.top()-lineHeight));
        if(lineY>tt2.y()){
            tt2.setY(lineY-lLabel.height()-lineHeight-5);
        }
        QToolTip::showText(tt2, topic, list,QRect(-300,-200,300,600));
    }*/
}

void LatexCompleter::editorDestroyed() {
	editor=0;
}

void LatexCompleter::bibtexSectionFound(QString content){
	showTooltip(content);
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

void LatexCompleterConfig::setFiles(const QStringList &newFiles) {
	files=newFiles;
}

const QStringList& LatexCompleterConfig::getLoadedFiles(){
	return files;
}

