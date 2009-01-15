/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *   addons by Luis Silvestre                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "latexeditor.h"

#include <QPainter>
#include <QTextLayout>
#include <QMetaProperty>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QMimeData>
#include <QClipboard>
#include <QPalette>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>

LatexEditor::LatexEditor(QWidget *parent,QFont & efont, QColor colMath, QColor colCommand, QColor colKeyword) : QTextEdit(parent),c(0)
{
QPalette p = palette();
p.setColor(QPalette::Inactive, QPalette::Highlight,p.color(QPalette::Active, QPalette::Highlight));
p.setColor(QPalette::Inactive, QPalette::HighlightedText,p.color(QPalette::Active, QPalette::HighlightedText));
setPalette(p);
setAcceptRichText(false);
setLineWidth(0);
setFrameShape(QFrame::NoFrame);
for (int i = 0; i < 3; ++i) UserBookmark[i]=0;
encoding="";
setFont(efont);
setTabStopWidth(fontMetrics().width("    "));
setTabChangesFocus(false);
highlighter = new LatexHighlighter(document());
highlighter->setColors(colMath,colCommand,colKeyword);
//c=0;
connect(this, SIGNAL(cursorPositionChanged()), viewport(), SLOT(update()));
 matcher = new ParenMatcher;
 connect(this, SIGNAL(cursorPositionChanged()), matcher, SLOT(matchFromSender()));
//grabShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Tab), Qt::WidgetShortcut);
setFocus();
}
LatexEditor::~LatexEditor(){
delete matcher;
}

 void LatexEditor::clearMarkerFormat(const QTextBlock &block, int markerId)
 {
     QTextLayout *layout = block.layout();
     QList<QTextLayout::FormatRange> formats = layout->additionalFormats();
     bool formatsChanged = false;
     for (int i = 0; i < formats.count(); ++i)
         if (formats.at(i).format.hasProperty(markerId)) {
             formats[i].format.clearBackground();
             formats[i].format.clearProperty(markerId);
             if (formats.at(i).format.properties().isEmpty()) {
                 formats.removeAt(i);
                 --i;
             }
             formatsChanged = true;
         }
 
     if (formatsChanged)
         layout->setAdditionalFormats(formats);
 }

void LatexEditor::paintEvent(QPaintEvent *event)
{
QRect rect = cursorRect();
rect.setX(0);
rect.setWidth(viewport()->width());
QPainter painter(viewport());
const QBrush brush(QColor("#ececec"));
painter.fillRect(rect, brush);
painter.end();
QTextEdit::paintEvent(event);
}

void LatexEditor::contextMenuEvent(QContextMenuEvent *e)
{
QMenu *menu=new QMenu(this);
QAction *a;
a = menu->addAction(tr("Undo"), this, SLOT(undo()));
a->setShortcut(Qt::CTRL+Qt::Key_Z);
a->setEnabled(document()->isUndoAvailable());
a = menu->addAction(tr("Redo") , this, SLOT(redo()));
a->setShortcut(Qt::CTRL+Qt::Key_Y);
a->setEnabled(document()->isRedoAvailable());
menu->addSeparator();
a = menu->addAction(tr("Cut"), this, SLOT(cut()));
a->setShortcut(Qt::CTRL+Qt::Key_X);
a->setEnabled(textCursor().hasSelection());
a = menu->addAction(tr("Copy"), this, SLOT(copy()));
a->setShortcut(Qt::CTRL+Qt::Key_C);
a->setEnabled(textCursor().hasSelection());
a = menu->addAction(tr("Paste") , this, SLOT(paste()));
a->setShortcut(Qt::CTRL+Qt::Key_P);
const QMimeData *md = QApplication::clipboard()->mimeData();
a->setEnabled(md && canInsertFromMimeData(md));
menu->addSeparator();
a = menu->addAction(tr("Select All"), this, SLOT(selectAll()));
a->setShortcut(Qt::CTRL+Qt::Key_A);
a->setEnabled(!document()->isEmpty());
menu->addSeparator();
a = menu->addAction(tr("Check Spelling Word"), this, SLOT(checkSpellingWord()));
a->setEnabled(!document()->isEmpty());
a = menu->addAction(tr("Check Spelling Selection"), this, SLOT(checkSpellingDocument()));
a->setEnabled(textCursor().hasSelection());
a = menu->addAction(tr("Check Spelling Document"), this, SLOT(checkSpellingDocument()));
a->setEnabled(!document()->isEmpty() && !textCursor().hasSelection());
menu->exec(e->globalPos());
delete menu;
}

bool LatexEditor::search( const QString &expr, bool cs, bool wo, bool forward, bool startAtCursor )
{
QTextDocument::FindFlags flags = 0;
if (cs) flags |= QTextDocument::FindCaseSensitively;
if (wo) flags |= QTextDocument::FindWholeWords;
QTextCursor c = textCursor();
//if (!c.hasSelection()) 
//	{
//	if (forward) c.movePosition(QTextCursor::Start);
//	else c.movePosition(QTextCursor::End);
//	setTextCursor(c);
//	}
QTextDocument::FindFlags options;
if (! startAtCursor) 
	{
	c.movePosition(QTextCursor::Start);
	setTextCursor(c);
	}
if (forward == false) flags |= QTextDocument::FindBackward;
QTextCursor found = document()->find(expr, c, flags);

if (found.isNull()) return false;
else 
	{
	setTextCursor(found);
	return true;
	}
}

void LatexEditor::replace( const QString &r)
{
int start;
QTextCursor c = textCursor();
if (c.hasSelection()) 
	{
	start=c.selectionStart();
	c.removeSelectedText();
	c.insertText(r);
	c.setPosition(start,QTextCursor::MoveAnchor);
	c.setPosition(start+r.length(),QTextCursor::KeepAnchor);
//	c.movePosition(QTextCursor::NextWord,QTextCursor::KeepAnchor);
	setTextCursor(c);
	}
}

void LatexEditor::gotoLine( int line )
{
if (line<=numoflines()) setCursorPosition( line, 0 );
}

void LatexEditor::commentSelection()
{
bool go=true;
QTextCursor cur=textCursor();
if (cur.hasSelection())
	{
	int start=cur.selectionStart();
	int end=cur.selectionEnd();
	cur.setPosition(start,QTextCursor::MoveAnchor);
	cur.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
	while ( cur.position() < end && go)
		{
		cur.insertText("%");
		end++;
		go=cur.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor);
		}
}	
}

void LatexEditor::indentSelection()
{
bool go=true;
QTextCursor cur=textCursor();
if (cur.hasSelection())
	{
	int start=cur.selectionStart();
	int end=cur.selectionEnd();
	cur.setPosition(start,QTextCursor::MoveAnchor);
	cur.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
	while ( cur.position() < end && go)
		{
		cur.insertText("\t");
		end++;
		go=cur.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor);
		}
	}
}

void LatexEditor::uncommentSelection()
{
bool go=true;
QTextCursor cur=textCursor();
if (cur.hasSelection())
	{
	int start=cur.selectionStart();
	int end=cur.selectionEnd();
	cur.setPosition(start,QTextCursor::MoveAnchor);
	cur.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
	while ( cur.position() < end && go)
		{
		cur.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
		if (cur.selectedText()=="%") 
			{
			cur.removeSelectedText();
			end--;
			}
		go=cur.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor);
		}
	}
}

void LatexEditor::unindentSelection()
{
bool go=true;
QTextCursor cur=textCursor();
if (cur.hasSelection())
	{
	int start=cur.selectionStart();
	int end=cur.selectionEnd();
	cur.setPosition(start,QTextCursor::MoveAnchor);
	cur.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
	while ( cur.position() < end && go)
		{
		cur.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor);
		if (cur.selectedText()=="\t") 
			{
			cur.removeSelectedText();
			end--;
			}
		go=cur.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor);
		}
	}
}

void LatexEditor::changeFont(QFont & new_font)
{
setFont(new_font);
}

QString LatexEditor::getEncoding()
{
 return encoding;
}

void LatexEditor::setEncoding(QString enc)
{
 encoding=enc;
}  

int LatexEditor::getCursorPosition(int para, int index)
{
int i = 0;
QTextBlock p = document()->begin();
while ( p.isValid() ) 
	{
	if (para==i) break;
	i++;
	p = p.next();
	}
return p.position()+index;
}

void LatexEditor::setCursorPosition(int para, int index)
{
int pos=getCursorPosition(para,index);
QTextCursor cur=textCursor();
cur.setPosition(pos,QTextCursor::MoveAnchor);
setTextCursor(cur);
ensureCursorVisible();
setFocus();
}

void LatexEditor::removeOptAlt()
{
QTextCursor cur=textCursor();
QTextBlock p = document()->begin();
QString s;
while (p.isValid())
	{
	s = p.text();
	s=s.left(3);
	if (s=="OPT" || s=="ALT")
		{
		int pos=p.position();
		p = p.next();
		cur.setPosition(pos,QTextCursor::MoveAnchor);
		cur.select(QTextCursor::BlockUnderCursor);
		cur.removeSelectedText();	
		}
	else 
		{
		p = p.next();
		}
	}
setFocus();
}

int LatexEditor::numoflines()
{
int num=0;
QTextBlock p;
for (p = document()->begin(); p.isValid(); p = p.next()) ++num;
return num;
}

int LatexEditor::linefromblock(const QTextBlock& p)
{
if (!p.isValid()) return -1;
int num = 1;
QTextBlock block=document()->begin();
while (block.isValid())
	{
	if ( p == block ) return num;
	num++;
	block = block.next();
	}
return -1;
}

void LatexEditor::selectword(int line, int col, QString word)
{
QTextCursor cur=textCursor();
int i = 0;
QTextBlock p = document()->begin();
while ( p.isValid() ) 
	{
	if (line==i) break;
	i++;
	p = p.next();
	}
int pos=p.position();
int offset=word.length();
cur.setPosition(pos+col,QTextCursor::MoveAnchor);
cur.setPosition(pos+col+offset,QTextCursor::KeepAnchor);
setTextCursor(cur);
ensureCursorVisible();
}

void LatexEditor::checkSpellingWord()
{
QTextCursor cur=textCursor();
cur.select(QTextCursor::WordUnderCursor);
setTextCursor(cur);
if (cur.hasSelection()) emit spellme();
}

void LatexEditor::checkSpellingDocument()
{
emit spellme();
}

QString LatexEditor::textUnderCursor() const
 {
QTextCursor tc = textCursor();
int oldpos=tc.position();
tc.select(QTextCursor::WordUnderCursor);
int newpos = tc.selectionStart();
tc.setPosition(newpos, QTextCursor::MoveAnchor);
tc.setPosition(oldpos, QTextCursor::KeepAnchor);
QString word=tc.selectedText();
QString sword=word.trimmed();
if (word.right(1)!=sword.right(1)) word="";
return word;
 }

void LatexEditor::keyPressEvent ( QKeyEvent * e ) 
{
if (c && c->popup()->isVisible()) 
	{
	// The following keys are forwarded by the completer to the widget
	switch (e->key()) 
		{
		case Qt::Key_Enter:
		case Qt::Key_Return:
		case Qt::Key_Escape:
		case Qt::Key_Tab:
		case Qt::Key_Backtab:
		e->ignore();
		return; // let the completer do default behavior
		default:
		break;
		}
	}

//bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
//if (!c || !isShortcut) 
//	{
	if ((e->key()==Qt::Key_Backtab))
		{
		QTextCursor cursor=textCursor();
		cursor.movePosition(QTextCursor::PreviousCharacter,QTextCursor::KeepAnchor);
		if (cursor.selectedText()=="\t") 
				{
				cursor.removeSelectedText();
				}
		}
	else if ((e->key()==Qt::Key_Enter)||(e->key()==Qt::Key_Return))
		{
		QTextEdit::keyPressEvent(e);
		QTextCursor cursor=textCursor();
		cursor.joinPreviousEditBlock();
		QTextBlock block=cursor.block();
		QTextBlock blockprev=block.previous();
		if (blockprev.isValid()) 
			{
			QString txt=blockprev.text();
			//QString newLine;
			int j=0;
			while ( (j<txt.count()) && ((txt[j]==' ') || txt[j]=='\t') ) 
				{
				//newLine+=(QString(txt[j]));
				cursor.insertText(QString(txt[j]));
				j++;
				}
            		/**** Added to complete \begin and \end *****/
/*            		bool completingBeginEnd = false;
            		int shift = txt.indexOf("\\begin{");
            		int notthere = txt.indexOf("\\end{");
            		if((txt.length()>0)&&(shift!=-1)&&(notthere<shift))
				{
                		int finish = txt.indexOf("}",shift);
                		if(finish != -1)
					{
                        		j = shift+7;
                        		newLine+="\\end{";
                        		while (j<=finish)
						{
                        	    		newLine+=QString(txt[j]);
                        	    		j++;
                        			}
                        		newLine = " \n" + newLine;
                        		completingBeginEnd = true;
                			}
            			}
            		cursor.insertText(newLine);
            		if(completingBeginEnd)
				{
		                cursor.movePosition(QTextCursor::Up);
		                setTextCursor(cursor);
			        }
*/
           		 /********************************************/
			}
		cursor.endEditBlock();
		}
	else QTextEdit::keyPressEvent(e);
//	}// dont process the shortcut when we have a completer

const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
if (!c || (ctrlOrShift && e->text().isEmpty())) return;

//static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]-= "); // end of word
bool hasModifier = (e->modifiers() & ( Qt::ControlModifier | Qt::AltModifier ));
//bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
QString completionPrefix = textUnderCursor();
if (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3 || eow.contains(e->text().right(1)))
//if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3 || eow.contains(e->text().right(1)))) 
	{
	c->popup()->hide();
	return;
	}
if (completionPrefix != c->completionPrefix()) 
	{
	c->setCompletionPrefix(completionPrefix);
	c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
	}
QRect cr = cursorRect();
cr.setWidth(c->popup()->sizeHintForColumn(0)+ c->popup()->verticalScrollBar()->sizeHint().width());
c->complete(cr); // popup it up!
}

QCompleter *LatexEditor::completer() const
 {
     return c;
 }

void LatexEditor::setCompleter(QCompleter *completer)
{
if (c) QObject::disconnect(c, 0, this, 0);
c = completer;
if (!c) return;
c->setWidget(this);
c->setCompletionMode(QCompleter::PopupCompletion);
c->setCaseSensitivity(Qt::CaseInsensitive);
QObject::connect(c, SIGNAL(activated(const QString&)),this, SLOT(insertCompletion(const QString&)));
}

 void LatexEditor::insertCompletion(const QString& completion)
{
if (c->widget() != this) return;
QTextCursor tc = textCursor();
int extra = completion.length() - c->completionPrefix().length();
//tc.movePosition(QTextCursor::Left);
//tc.movePosition(QTextCursor::EndOfWord);
int pos=tc.position();
QString insert_word = "";
QString original_word=completion.right(extra);
bool skipfirst=(completion.startsWith("\\begin{") || completion.startsWith("\\end{") || completion.startsWith("\\ref{") || completion.startsWith("\\pageref{"));
QString character;
bool ignore = false;
int offset=0;
for ( int i = 0; i < original_word.length(); ++i )
	{
	character=original_word.mid(i,1);
	if (character=="[" || character=="{" || character=="(" || character=="<") 
		{
		insert_word += character;
		if (!skipfirst) 
			{
			ignore = true;
			if (offset==0) offset=i;
			}
		else skipfirst=false;
		}
	else if (character=="]" || character=="}" || character==")" || character==">") 
		{
		insert_word += character;
		ignore = false;
		}
	else if (character==",")
		{
		insert_word += character;
		}
	else if ( ! ignore ) insert_word += character;
	}
QRegExp rbb("begin\\{\\s*([A-Za-z_]+)\\}");
if (completion.contains(rbb)) 
	{
	insert_word+="\n\n\\end{"+rbb.cap(1)+"}";
	tc.insertText(insert_word);
	tc.movePosition(QTextCursor::Up,QTextCursor::MoveAnchor,1);
	}
else
	{
	tc.insertText(insert_word);
	if (offset!=0) tc.setPosition(pos+offset+1,QTextCursor::MoveAnchor);
	}
setTextCursor(tc);
}

 void LatexEditor::focusInEvent(QFocusEvent *e)
{
if (c) c->setWidget(this);
QTextEdit::focusInEvent(e);
}
