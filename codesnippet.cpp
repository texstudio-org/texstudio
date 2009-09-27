#include "codesnippet.h"

#include "qeditor.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"


CodeSnippet::CodeSnippet(const QString &newWord) {
        m_cut=false;
	QString realNewWord=newWord;
	// \begin magic
	if (realNewWord.startsWith("\\begin{")&&
		!realNewWord.contains("\n")&&!realNewWord.contains("%n") //only a single line
	    && realNewWord.lastIndexOf("\\") == 0) //only one latex command in the line
	{
		int p=newWord.indexOf("{");
		QString environmentName=realNewWord.mid(p,newWord.indexOf("}")-p+1); //contains the {}
		QString content="%<"+QObject::tr("content...")+"%>";
		realNewWord+="\n"+content+"\n\\end"+environmentName;
	}

	cursorLine=-1;
	cursorOffset=-1;
	anchorOffset=-1;
	QString curLine;

	curLine.reserve(realNewWord.length());
	word.reserve(realNewWord.length());
	bool escape=false;
	bool inDescription=false;bool foundDescription=false;
	int formatStart=0;
	placeHolders.append(QList<QPair<int,int> >()); //during the creation this contains a line more than lines
	for (int i=0; i<realNewWord.length(); i++)
		if (!escape) {
			if (realNewWord.at(i)==QChar('\n')) {
				lines.append(curLine);
				placeHolders.append(QList<QPair<int,int> >());
				curLine.clear();
			} else if (realNewWord.at(i)==QChar('%')) escape=true;
			else {
				curLine+=realNewWord.at(i);
				if (!inDescription) word.append(realNewWord.at(i));
			}
		} else {
			escape=false;
			switch (realNewWord.at(i).toAscii()) {
			case '%':
				word+='%';
				curLine+='%';
				break;
			case '|':
				cursorLine=lines.count(); //first line is 0
				if (inDescription && cursorOffset==-1) anchorOffset=formatStart;
				else anchorOffset=cursorOffset;
				cursorOffset=curLine.length();
				break;
			case '<':
				inDescription=true;
				formatStart=curLine.length();
				break;
			case '>': 
				inDescription=false;
				foundDescription=true;
				placeHolders.last().append(QPair<int, int>(formatStart, curLine.length()-formatStart));
				break;
			case 'n':
				lines.append(curLine);
				placeHolders.append(QList<QPair<int,int> >());
				curLine.clear();
				//curLine+="\n";
				break;	
			default: // escape was not an escape character ...
				curLine+='%';
				curLine+=realNewWord.at(i);
				if (!inDescription) {
					word.append('%');
					word.append(realNewWord.at(i));
				}
			}
		}
	lines.append(curLine);
	if (cursorLine==-1 && foundDescription) 
		for (int i=0;i<placeHolders.count();i++)
			if (placeHolders[i].count()>0) {
				cursorLine=i;
				anchorOffset =placeHolders[i][0].first;
				cursorOffset =placeHolders[i][0].first+placeHolders[i][0].second;
				break;
			}
	if (anchorOffset==-1) anchorOffset=cursorOffset;
	sortWord=word.toLower();
	sortWord.replace("{","!");//js: still using dirty hack, however order should be ' '{[* abcde...
	sortWord.replace("}","!");// needs to be replaced as well for sorting \bgein{abc*} after \bgein{abc}
	sortWord.replace("[","\"");//(first is a space->) !"# follow directly in the ascii table
	sortWord.replace("*","#");
}

void CodeSnippet::insert(QEditor* editor){
	if (!editor) return;
	QDocumentCursor c=editor->cursor();
	insertAt(editor,&c);
}
void CodeSnippet::insertAt(QEditor* editor, QDocumentCursor* cursor, bool usePlaceholders) const{
	if (lines.empty()||!editor||!cursor) return;
	
	QStringList mLines=lines;

	if(m_cut){
		Q_ASSERT(mLines.size()>1);
		mLines.removeFirst();
	}
	int beginMagicLine=-1;//hack will made every placeholder in this line a mirror of the first placeholder and select this placeholder afterwards
	if (mLines.value(0,"")=="\\begin{environment-name}") //useful in this case (TODO: mirrors in code snippet language) (when changed, update unit test!)
		beginMagicLine=mLines.count()-1; 
		
	QString savedSelection;
	if (cursor->hasSelection()) {
		savedSelection=cursor->selectedText();
		cursor->removeSelectedText();
	}
	QDocumentCursor selector=*cursor;
	QDocumentLine curLine=cursor->line();

	int baseLine=cursor->lineNumber();
	int baseLineIndent = cursor->columnNumber(); //text before inserted word moves placeholders to the right
	int lastLineRemainingLength = curLine.text().length()-baseLineIndent; //last line will has length: indentation + codesnippet + lastLineRemainingLength
	editor->insertText(*cursor,mLines.join("\n")); //don't use cursor->insertText to keep autoindentation working
	int magicPlaceHolder=-1;
	Q_ASSERT(placeHolders.size()==mLines.count());
	if (usePlaceholders) {
		//check if there actually are placeholders to insert
		usePlaceholders=false;
		for (int l=0;l< mLines.count();l++)
			usePlaceholders|=placeHolders[l].size();
	}
	if (usePlaceholders) {
		if (editor->currentPlaceHolder()!=-1 && 
			editor->getPlaceHolder(editor->currentPlaceHolder()).cursor.isWithinSelection(*cursor))
			editor->removePlaceHolder(editor->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
		if (beginMagicLine!=-1)	
			magicPlaceHolder=editor->placeHolderCount();
		for (int l=0;l< mLines.count();l++){
			//if (l<mLines.count()-1) cursor->insertLine();
			for (int i=0; i<placeHolders[l].size(); i++) {
				QEditor::PlaceHolder ph;
				ph.length=placeHolders[l][i].second;
				ph.cursor=editor->document()->cursor(baseLine+l,placeHolders[l][i].first);
				if (l==0) ph.cursor.movePosition(baseLineIndent,QDocumentCursor::NextCharacter);
				else {
					ph.cursor.movePosition(ph.cursor.line().length()-mLines[l].length(),QDocumentCursor::NextCharacter);
					if (l+1==mLines.size())	
						ph.cursor.movePosition(lastLineRemainingLength,QDocumentCursor::PreviousCharacter);
				} 
				if (l!=beginMagicLine) {
					if (ph.cursor.isValid())
						editor->addPlaceHolder(ph);
				}	else 
					editor->addPlaceHolderMirror(magicPlaceHolder,ph.cursor);
			}
		}
	}
	//place cursor/add \end
	if (cursorOffset!=-1) {
		int realAnchorOffset=anchorOffset; //will be moved to the right if text is already inserted on this line
		if (cursorLine>0) {
			if (cursorLine>=mLines.size()) return;
			if (!selector.movePosition(cursorLine,QDocumentCursor::Down,QDocumentCursor::MoveAnchor))
				return;
			//if (editor->flag(QEditor::AutoIndent))
			realAnchorOffset += selector.line().length()-mLines[cursorLine].length();
			if (cursorLine + 1 == mLines.size())
				realAnchorOffset-=lastLineRemainingLength;
		} else realAnchorOffset += baseLineIndent;
		selector.setColumnNumber(realAnchorOffset);
		bool ok=true;
		if (cursorOffset>anchorOffset) 
			ok=selector.movePosition(cursorOffset-anchorOffset,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
		else if (cursorOffset<anchorOffset)
			ok=selector.movePosition(anchorOffset-cursorOffset,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		if (!ok) return;
		editor->setCursor(selector);
		if (!savedSelection.isEmpty()) editor->cursor().insertText(savedSelection,true);
	}	else editor->setCursor(*cursor); //place after insertion
	if (magicPlaceHolder!=-1)  //select magic placeholder if there (must be last line because there may be insertion
		editor->setPlaceHolder(magicPlaceHolder); //at another cursor position necessary)
}

