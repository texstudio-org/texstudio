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
connect( ui.comboBoxStyles, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectStyle(QString)));

connect(ui.lineEditAspellCommand, SIGNAL(textChanged(QString)), this, SLOT(lineEditAspellChanged(QString)));

ui.labelGetDic->setText( tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
ui.labelGetDic->setOpenExternalLinks(true);


connect( ui.pushButtonColorText, SIGNAL(clicked()), this, SLOT(configureColorText()));
connect( ui.pushButtonColorDecoration, SIGNAL(clicked()), this, SLOT(configureColorDecoration()));

connect (ui.checkBoxBold,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));
connect (ui.checkBoxItalic,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));
connect (ui.checkBoxUnderline,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));
connect (ui.checkBoxOverline,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));
connect (ui.checkBoxStrikeout,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));
connect (ui.checkBoxWaveUnderline,SIGNAL(clicked ()),this,SLOT(textStyleChanged()));

connect( ui.shorttableWidget, SIGNAL(itemChanged(QTableWidgetItem * )), this, SLOT(shortCutItemChanged(QTableWidgetItem * )));

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


createIcons();
ui.contentsWidget->setCurrentRow(0);


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
void ConfigDialog::selectStyle(QString style){
    QFormat &format=editorFormats[style];
    ui.pushButtonColorText->setPalette(QPalette(format.foreground));
    ui.pushButtonColorDecoration->setPalette(QPalette(format.linescolor));
    ui.checkBoxBold->setChecked(format.weight==QFont::Bold);
    ui.checkBoxItalic->setChecked(format.italic);
    ui.checkBoxUnderline->setChecked(format.underline);
    ui.checkBoxOverline->setChecked(format.overline);
    ui.checkBoxStrikeout->setChecked(format.strikeout);
    ui.checkBoxWaveUnderline->setChecked(format.waveUnderline);
}
void ConfigDialog::configureColorText()
{
QColor color = QColorDialog::getColor(ui.pushButtonColorText->palette().background().color(), this);
if (color.isValid())
	{
	ui.pushButtonColorText->setPalette(QPalette(color));
	ui.pushButtonColorText->setAutoFillBackground(true);
	textStyleChanged();
	}
}

void ConfigDialog::configureColorDecoration()
{
QColor color = QColorDialog::getColor(ui.pushButtonColorDecoration->palette().background().color(), this);
if (color.isValid())
	{
	ui.pushButtonColorDecoration->setPalette(QPalette(color));
	ui.pushButtonColorDecoration->setAutoFillBackground(true);
	textStyleChanged();
	}
}
void ConfigDialog::textStyleChanged(){
    QString style=ui.comboBoxStyles->currentText();
    QFormat format;
    format.foreground=ui.pushButtonColorText->palette().color(QPalette::Button);
    format.linescolor=ui.pushButtonColorDecoration->palette().color(QPalette::Button);
    if (ui.checkBoxBold->isChecked()) format.weight=QFont::Bold;
    else format.weight=QFont::Normal;
    format.italic=ui.checkBoxItalic->isChecked();
    format.underline=ui.checkBoxUnderline->isChecked();
    format.overline=ui.checkBoxOverline->isChecked();
    format.strikeout=ui.checkBoxStrikeout->isChecked();
    format.waveUnderline=ui.checkBoxWaveUnderline->isChecked();
    editorFormats[style]=format;
}
void ConfigDialog::lineEditAspellChanged(QString newText)
{
    if (QFile(newText).exists()) 
        ui.labelGetDic->setText( tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
    else 
        ui.labelGetDic->setText( "<font color=\"red\">"+tr("(Dictionary doesn't exists)")+"</font><br>"+tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>") );
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


void ConfigDialog::shortCutItemChanged ( QTableWidgetItem * item ){
    if (item==NULL) return;
    if (QString("none").compare(item->text(),Qt::CaseInsensitive)==0) return;
    if (ui.shorttableWidget->currentItem ()==NULL) return;

    QKeySequence newSeq(item->text());
    if (QKeySequence(item->text()) == QKeySequence()){
        QMessageBox::warning(this, tr("Texmaker"),
                   tr("The shortcut you entered is invalid."),
                   QMessageBox::Ok, QMessageBox::Ok);
        item->setText(item->data(Qt::UserRole).toString());
        return;
    }
    QString identicalShortcuts = "";
    for (int i=0;i<ui.shorttableWidget->rowCount();i++)
        if (QKeySequence(ui.shorttableWidget->item(i,1)->text())==newSeq && i!=item->row())
            identicalShortcuts+=ui.shorttableWidget->item(i,0)->text()+"\n";
    if (identicalShortcuts=="") return;

    switch (QMessageBox::warning(this, tr("Texmaker"),
                                 tr("The shortcut you entered is the same as the one of this command: \n")+identicalShortcuts+tr("\n Should I delete this other shortcut?"),
                                 QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes))
    {
        case QMessageBox::Yes:
            for (int i=0;i<ui.shorttableWidget->rowCount();i++)
                if (QKeySequence(ui.shorttableWidget->item(i,1)->text())==newSeq && i!=item->row())
                    ui.shorttableWidget->item(i,1)->setText("none");
        break;
    }
}
