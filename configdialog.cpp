/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "configdialog.h"

#include <QFontDatabase>
#include <QTextCodec>
#include <QFileDialog>
#include <QColorDialog>
#include <QDir>
#include <QKeySequence>
#include <QMessageBox>
#include <QList>
#include <QPainter>

#include "qdocument.h"
const QString ShortcutDelegate::addRowButton="<internal: add row>";
const QString ShortcutDelegate::deleteRowButton="<internal: delete row>";

ShortcutDelegate::ShortcutDelegate(QObject *parent): treeWidget(0){
	// remove unused argument warning
	(void) parent;
}
QWidget *ShortcutDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option ,
     const QModelIndex & index ) const
{
	// remove unused argument warning
	(void) option;

    if (!index.isValid()) return 0;
    const QAbstractItemModel *model = index.model();
    if (model->index(index.row(),0,index.parent()).isValid() && model->data(model->index(index.row(),0,index.parent()),Qt::DisplayRole) == deleteRowButton) {
        //editor key replacement
        if (index.column()==0) return 0;
        return new QLineEdit(parent);
    }
    //menu shortcut key
    if (index.column()!=2 && index.column()!=3) return 0;
    QComboBox *editor = new QComboBox(parent);
    for (int k=Qt::Key_F1;k<=Qt::Key_F12;k++)
        editor->addItem(QKeySequence(k).toString(QKeySequence::NativeText));
    for (int c=0;c<=1;c++)
        for (int s=0;s<=1;s++)
            for (int a=0;a<=1;a++){
                if (!c && !s && !a) continue;
                for (int k=Qt::Key_F1;k<=Qt::Key_F12;k++)
                    editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
                for (int k=Qt::Key_0;k<=Qt::Key_9;k++)
                    editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
                for (int k=Qt::Key_A;k<=Qt::Key_Z;k++)
                    editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
            }
    editor->setEditable(true);

    return editor;
}

 void ShortcutDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
    QString value = index.model()->data(index, Qt::EditRole).toString();
    //menu shortcut key
    QComboBox *box = qobject_cast<QComboBox*>(editor);
    if (box) {
        QString normalized=QKeySequence(value).toString(QKeySequence::NativeText);
        int pos=box->findText(normalized);
        if (pos==-1) box->setEditText(value);
        else box->setCurrentIndex(pos);
        return;
    }
    //editor key replacement
    QLineEdit *le = qobject_cast<QLineEdit*>(editor);
    if (le) {
        le->setText(value);
    }
 }
  void ShortcutDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
    //editor key replacement
    QLineEdit *le = qobject_cast<QLineEdit*>(editor);
    if (le) {
        if (le->text().size()!=1 && index.column()==1) {
            QMessageBox::warning(editor,"TexMakerX",tr("Only single characters are allowed as key"),QMessageBox::Ok);
            return;
        }
        model->setData(index, le->text(), Qt::EditRole);
        return;
    }
    //menu shortcut key
    if (index.column()!=2 && index.column()!=3) return;
    QComboBox *box = qobject_cast<QComboBox*>(editor);
    if (!box) return;
    QString value=box->currentText();
    if (value=="" || value=="none") value="";
    else {
        value=QKeySequence(box->currentText()).toString(QKeySequence::NativeText);
        if (value=="" || (value.endsWith("+") && !value.endsWith("++"))) { //Alt+wrong=>Alt+
            QMessageBox::warning(editor, ConfigDialog::tr("TexMakerX"),
                ConfigDialog::tr("The shortcut you entered is invalid."),
                QMessageBox::Ok, QMessageBox::Ok);
                return;
        }

        /*int r=-1;
        for (int i=0;i<model->rowCount();i++)
            if (model->data(model->index(i,2))==value) {
                r=i;
                break;
                }*/
        if (treeWidget) {
            QList<QTreeWidgetItem *> li=treeWidget->findItems ( value, Qt::MatchRecursive |Qt::MatchFixedString, 2);
            if (!li.empty() && li[0]->text(0) == model->data(model->index(index.row(),0,index.parent()))) li.removeFirst();
            QList<QTreeWidgetItem *> li2=treeWidget->findItems ( value, Qt::MatchRecursive |Qt::MatchFixedString, 3);
            if (!li2.empty() && li2[0]->text(0) == model->data(model->index(index.row(),0,index.parent()))) li2.removeFirst();
            li << li2;
            if (!li.empty()) {
                QString duplicate=li[0]->text(0);//model->data(model->index(mil[0].row(),0,mil[0].parent()),Qt::DisplayRole).toString();
                switch (QMessageBox::warning(editor, ConfigDialog::tr("TexMakerX"),
                                             ConfigDialog::tr("The shortcut you entered is the same as the one of this command:") +"\n"+duplicate+"\n"+ConfigDialog::tr("Should I delete this other shortcut?"),
                                             QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes))
                {
                    case QMessageBox::Yes:
                        //model->setData(mil[0],"",Qt::DisplayRole);
                        if (li[0]->text(2) == value)  li[0]->setText(2,"");
                        else if (li[0]->text(3) == value)  li[0]->setText(3,"");
                        break;
                    default:;
                }
            }
        }
    }
    model->setData(index, value, Qt::EditRole);
}
 void ShortcutDelegate ::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

void ShortcutDelegate::drawDisplay ( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text ) const
{
    QStyle *style = QApplication::style ();
    if (!style) QItemDelegate::drawDisplay (painter, option, rect, text);
    else if (text=="<internal: delete row>") {
       QStyleOptionButton sob;
       sob.text = tr("delete row");
       sob.state = QStyle::State_Enabled;
       sob.rect = rect;
       style->drawControl(QStyle::CE_PushButton, &sob, painter);
    } else if (text=="<internal: add row>"){
       QStyleOptionButton sob;
       sob.text = tr("add row");
       sob.state = QStyle::State_Enabled;
       sob.rect = rect;
       style->drawControl(QStyle::CE_PushButton, &  sob, painter);
    } else QItemDelegate::drawDisplay (painter, option, rect, text);
}

void ShortcutDelegate::treeWidgetItemClicked ( QTreeWidgetItem * item, int column ){
    if (column!=0) return;
    /*QStyle *style = QApplication::style ();
    QPainter p(item->treeWidget ());
    QStyleOptionButton sob;
    sob.rect=item->treeWidget ()->visualItemRect(item);
    sob.state = QStyle::State_Enabled|QStyle::State_Sunken;
    if (style)
        if (item->text(0)=="<internal: delete row>") {
           sob.text = tr("delete row");
           style->drawControl(QStyle::CE_PushButton, &sob, &p);
        } else if (item->text(0)=="<internal: add row>"){
           sob.text = tr("add row");
           style->drawControl(QStyle::CE_PushButton, &  sob, &p);
        }*/
    if (item->text(0)==deleteRowButton) {
        switch (QMessageBox::question(item->treeWidget(), ConfigDialog::tr("TexMakerX"),
                                             ConfigDialog::tr("Do you really want to delete this row?"),
                                             QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes))
                {
                    case QMessageBox::Yes:
                        item->parent()->removeChild(item);
                        break;
                    default:;
                }
    } else if (item->text(0)==addRowButton) {
        QTreeWidgetItem *twi = new QTreeWidgetItem((QTreeWidgetItem*)0,QStringList() << "<internal: delete row>");
        twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
        item->parent()->insertChild(item->parent()->childCount()-1, twi);
    }
}

ConfigDialog::ConfigDialog(QWidget* parent): QDialog( parent)
{
setModal(true);
ui.setupUi(this);

ui.contentsWidget->setIconSize(QSize(96, 96));
ui.contentsWidget->setViewMode(QListView::IconMode);
ui.contentsWidget->setMovement(QListView::Static);

//pageditor
QFontDatabase fdb;
ui.comboBoxFont->addItems( fdb.families() );

ui.comboBoxEncoding->addItem("UTF-8");
foreach (int mib, QTextCodec::availableMibs())
	{
	QTextCodec *codec = QTextCodec::codecForMib(mib);
	if (codec->name()!="UTF-8") ui.comboBoxEncoding->addItem(codec->name());
	}


connect( ui.pushButtonAspell, SIGNAL(clicked()), this, SLOT(browseAspell()));
connect(ui.lineEditAspellCommand, SIGNAL(textChanged(QString)), this, SLOT(lineEditAspellChanged(QString)));

ui.labelGetDic->setText( tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
ui.labelGetDic->setOpenExternalLinks(true);

//pagequick
connect(ui.radioButton6, SIGNAL(toggled(bool)),ui.lineEditUserquick, SLOT(setEnabled(bool)));

//pagetools
connect( ui.pushButtonLatex, SIGNAL(clicked()), this, SLOT(browseLatex()));
connect( ui.pushButtonDvips, SIGNAL(clicked()), this, SLOT(browseDvips()));
connect( ui.pushButtonBibtex, SIGNAL(clicked()), this, SLOT(browseBibtex()));
connect( ui.pushButtonMakeindex, SIGNAL(clicked()), this, SLOT(browseMakeindex()));
connect( ui.pushButtonDviviewer, SIGNAL(clicked()), this, SLOT(browseDviviewer()));
connect( ui.pushButtonPsviewer, SIGNAL(clicked()), this, SLOT(browsePsviewer()));
connect( ui.pushButtonPdflatex, SIGNAL(clicked()), this, SLOT(browsePdflatex()));
connect( ui.pushButtonDvipdfm, SIGNAL(clicked()), this, SLOT(browseDvipdfm()));
connect( ui.pushButtonPs2pdf, SIGNAL(clicked()), this, SLOT(browsePs2pdf()));
connect( ui.pushButtonPdfviewer, SIGNAL(clicked()), this, SLOT(browsePdfviewer()));
connect( ui.pushButtonMetapost, SIGNAL(clicked()), this, SLOT(browseMetapost()));
connect( ui.pushButtonGhostscript, SIGNAL(clicked()), this, SLOT(browseGhostscript()));
connect( ui.pushButtonExecuteBeforeCompiling, SIGNAL(clicked()), this, SLOT(browsePrecompiling()));


fmConfig=new QFormatConfig(ui.formatConfigBox);
fmConfig->addScheme("",QDocument::formatFactory());
//fmConfig->setMaximumSize(490,300);
//fmConfig->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
(new QBoxLayout(QBoxLayout::TopToBottom, ui.formatConfigBox))->insertWidget(0,fmConfig);

createIcons();
ui.contentsWidget->setCurrentRow(0);

ui.shortcutTree->setHeaderLabels(QStringList()<<tr("Command")<<tr("Default Shortcut")<<tr("Current Shortcut")<<tr("Additional Shortcut"));
ui.shortcutTree->setColumnWidth(0,200);
}

ConfigDialog::~ConfigDialog(){
}

void ConfigDialog::createIcons()
{
QListWidgetItem *commandButton = new QListWidgetItem(ui.contentsWidget);
commandButton->setIcon(QIcon(":/images/configtools.png"));
commandButton->setText(tr("Commands"));
commandButton->setTextAlignment(Qt::AlignHCenter);
commandButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

QListWidgetItem *quickButton = new QListWidgetItem(ui.contentsWidget);
quickButton->setIcon(QIcon(":/images/configquick.png"));
quickButton->setText(tr("Quick Build"));
quickButton->setTextAlignment(Qt::AlignHCenter);
quickButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

QListWidgetItem *keysButton = new QListWidgetItem(ui.contentsWidget);
keysButton->setIcon(QIcon(":/images/configkeys.png"));
keysButton->setText(tr("Shortcuts"));
keysButton->setTextAlignment(Qt::AlignHCenter);
keysButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

QListWidgetItem *editorButton = new QListWidgetItem(ui.contentsWidget);
editorButton->setIcon(QIcon(":/images/configeditor.png"));
editorButton->setText(tr("Editor"));
editorButton->setTextAlignment(Qt::AlignHCenter);
editorButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

connect(ui.contentsWidget,
	SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
	this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui.pagesWidget->setCurrentIndex(ui.contentsWidget->row(current));
}

//pageditor
void ConfigDialog::browseAspell()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse dictionary"),QDir::homePath(),"Dictionary (*.dic)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
 	location.replace(QString("\\"),QString("/"));
//	location="\""+location+"\"";
	ui.lineEditAspellCommand->setText( location );
	}
}
void ConfigDialog::lineEditAspellChanged(QString newText)
{
    if (QFile(newText).exists()) {
        ui.lineEditAspellCommand->setStyleSheet(QString());
        ui.labelGetDic->setText( tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
    } else {
        ui.lineEditAspellCommand->setStyleSheet(QString("QLineEdit {background: red}"));
        ui.labelGetDic->setText( "<font color=\"red\">"+tr("(Dictionary doesn't exists)")+"</font><br>"+tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
    }
}
//pagetools
void ConfigDialog::browseLatex()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" -interaction=nonstopmode %.tex";
	ui.lineEditLatex->setText( location );
	}
}

void ConfigDialog::browseDvips()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" -o %.ps %.dvi";
	ui.lineEditDvips->setText( location );
	}
}

void ConfigDialog::browseBibtex()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.aux";
	ui.lineEditBibtex->setText( location );
	}
}

void ConfigDialog::browseMakeindex()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.idx";
	ui.lineEditMakeindex->setText( location );
	}
}

void ConfigDialog::browseDviviewer()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.dvi";
	ui.lineEditDviviewer->setText( location );
	}
}

void ConfigDialog::browsePsviewer()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.ps";
	ui.lineEditPsviewer->setText( location );
	}
}

void ConfigDialog::browsePdflatex()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" -interaction=nonstopmode %.tex";
	ui.lineEditPdflatex->setText( location );
	}
}

void ConfigDialog::browseDvipdfm()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.dvi";
	ui.lineEditDvipdfm->setText( location );
	}
}

void ConfigDialog::browsePs2pdf()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.ps";
	ui.lineEditPs2pdf->setText( location );
	}
}

void ConfigDialog::browsePdfviewer()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" %.pdf";
	ui.lineEditPdfviewer->setText( location );
	}
}

void ConfigDialog::browseMetapost()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\" --interaction nonstopmode ";
	ui.lineEditMetapost->setText( location );
	}
}

void ConfigDialog::browseGhostscript()
{
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\"";
	ui.lineEditGhostscript->setText( location );
	}
}
void ConfigDialog::browsePrecompiling(){
QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),QDir::rootPath(),"Program (*)",0,QFileDialog::DontResolveSymlinks);
if ( !location.isEmpty() )
	{
	location.replace(QString("\\"),QString("/"));
	location="\""+location+"\"";
	ui.lineEditExecuteBeforeCompiling->setText( location );
	}
}

