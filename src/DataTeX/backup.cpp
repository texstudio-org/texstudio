#include "backup.h"
#include "ui_backup.h"
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <QDebug>
#include <qmath.h>
#include <QRadioButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDesktopServices>
#include <QDate>
#include "quazip.h"
#include "quazipfile.h"

BackUp::BackUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackUp)
{
    ui->setupUi(this);
    QStringList Baseis;
    QDirIterator Baseis_list(QDir::homePath()+"/.TexoMakerFiles/Βάσεις/" , QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);
    while (Baseis_list.hasNext()){
        QFileInfo filepath(Baseis_list.next());
        QString bash = filepath.baseName();
    Baseis.append(bash);}
    ui->ComboBaseBackUp->addItems(Baseis);
    ui->ComboBaseBackUp->setCurrentIndex(-1);

    QStringList Notes;
    QDirIterator Notes_list(QDir::homePath()+"/.TexoMakerFiles/Σημειώσεις/" , QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);
    while (Notes_list.hasNext()){
        QFileInfo filepath(Notes_list.next());
        QString note = filepath.baseName();
    Notes.append(note);}
    ui->ComboNotesBackUp->addItems(Notes);
    ui->ComboNotesBackUp->setCurrentIndex(-1);
    qDebug()<<ui->ComboBaseBackUp->currentIndex();
    ui->BackUpBaseButton->setEnabled(false);
    ui->BackUpNotesButton->setEnabled(false);
    ui->BackUpFolderBase->setEnabled(false);
    ui->BackUpFolderNotes->setEnabled(false);
    ui->BackUpZipBase->setEnabled(false);
    ui->BackUpZipNotes->setEnabled(false);
    ui->IncludePdfBase->setEnabled(false);
    ui->IncludePdfNotes->setEnabled(false);
}

BackUp::~BackUp()
{
    delete ui;
}

void BackUp::on_ComboBaseBackUp_currentIndexChanged(int index)
{
    basenamebackup.clear();
    basepathbackup.clear();
    if(index>-1){
        ui->BackUpBaseButton->setEnabled(true);
        ui->BackUpFolderBase->setEnabled(true);
        ui->BackUpZipBase->setEnabled(true);
        ui->IncludePdfBase->setEnabled(true);
    basenamebackup = ui->ComboBaseBackUp->currentText();
    QString PathFile = QDir::homePath()+"/.TexoMakerFiles/Βάσεις/"+basenamebackup+".txt";
    QFile basefile(PathFile);
    QStringList diadromesbase;

    basefile.open (QIODevice::ReadWrite | QIODevice::Text);
        {
        QTextStream textStream(&basefile);
        while (!textStream.atEnd()){
          QString GrammhText=textStream.readLine();
          diadromesbase.append(GrammhText);
        }}
    basefile.close();
    basepathbackup = QString(diadromesbase.at(0)).remove("Base=");}
}

void BackUp::on_BackUpBaseButton_clicked()
{
    TexFiles.clear();
    PdfFiles.clear();
    QString destination = QFileDialog::getSaveFileName(this, tr("Επιλέξτε φάκελο αποθήκευσης"),
                                                       basenamebackup+"-files.csv","csv Files (*.csv)");
    if(destination.isEmpty()) return;
    QString line;
    QDirIterator tex_list(basepathbackup , QStringList() << "*.tex", QDir::Files, QDirIterator::Subdirectories);
    while (tex_list.hasNext()){
    TexFiles.append(tex_list.next());}
    if(ui->IncludePdfBase->isChecked()){
        QDirIterator pdf_list(basepathbackup , QStringList() << "*.pdf", QDir::Files, QDirIterator::Subdirectories);
        while (pdf_list.hasNext()){
        PdfFiles.append(pdf_list.next());}
    }
    QFileInfo dest(destination);
    QString rembase = basepathbackup;
    QString RemovePath = rembase.remove(basenamebackup+"/");
    QString path;

    QProcess *copyprocess = new QProcess;
    copyprocess->start("cp",QStringList()<<"-avr"<<basepathbackup << dest.absolutePath()+"/");
    copyprocess->waitForBytesWritten();
    copyprocess->waitForFinished(-1);
    qDebug() << copyprocess->readAll();

    if(ui->BackUpFolderBase->isChecked()){
    QDir dir(dest.absolutePath()+"/"+basenamebackup+"-Μόνο τα αρχεία/Αρχεία TeX/");
    if (!dir.exists())
        dir.mkpath(".");
        foreach(QString arxeio,TexFiles){
        QFileInfo texfile(arxeio);
        path = texfile.absoluteFilePath().remove(RemovePath);
        line.append(path+"\n");
        QFile newfile(arxeio);
        newfile.copy(dest.absolutePath()+"/"+basenamebackup+"-Μόνο τα αρχεία/Αρχεία TeX/"+texfile.fileName());
        }
    }

    if(ui->IncludePdfBase->isChecked()){
    QDir dir(dest.absolutePath()+"/"+basenamebackup+"-Μόνο τα αρχεία/Αρχεία Pdf/");
    if (!dir.exists())
        dir.mkpath(".");
        foreach(QString arxeio,PdfFiles){
        QFileInfo pdffile(arxeio);
        path = pdffile.absoluteFilePath().remove(RemovePath);
        line.append(path+"\n");
        QFile newfile(arxeio);
        newfile.copy(dest.absolutePath()+"/"+basenamebackup+"-Μόνο τα αρχεία/Αρχεία Pdf/"+pdffile.fileName());
        }
    }

    QFile destinationfile(destination);
    destinationfile.open(QIODevice::ReadWrite | QIODevice::Text);
    {
        QTextStream textStream(&destinationfile);
          destinationfile.resize(0);
          textStream << line;
    }
    destinationfile.close();

    if(ui->BackUpZipBase->isChecked()){
        QString date = QString::number( QDate::currentDate().day() )+"-"+QString::number( QDate::currentDate().month() )
        +"-"+QString::number( QDate::currentDate().year() );
        QString zipfile = dest.absolutePath()+"/"+basenamebackup+"-"+date+".zip";
        QProcess *process = new QProcess;
        process->setWorkingDirectory(RemovePath);
        process->start("zip",QStringList()<<"-r7" << zipfile<< basenamebackup<<"*");
        process->waitForBytesWritten();
        process->waitForFinished(-1);
        qDebug() << process->readAll();
    }
    if(ui->OpenFolder->isChecked()){QDesktopServices::openUrl(QUrl("file:///"+dest.absolutePath()));}
}

void BackUp::on_ComboNotesBackUp_currentIndexChanged(int index)
{
    notenamebackup.clear();
    notepathbackup.clear();
    if(index>-1){
        ui->BackUpNotesButton->setEnabled(true);
        ui->BackUpFolderNotes->setEnabled(true);
        ui->BackUpZipNotes->setEnabled(true);
        ui->IncludePdfNotes->setEnabled(true);
    notenamebackup = ui->ComboNotesBackUp->currentText();
    QString PathFile = QDir::homePath()+"/.TexoMakerFiles/Σημειώσεις/"+notenamebackup+".txt";
    QFile notefile(PathFile);
    QStringList diadromesnotes;

    notefile.open (QIODevice::ReadWrite | QIODevice::Text);
        {
        QTextStream textStream(&notefile);
        while (!textStream.atEnd()){
          QString GrammhText=textStream.readLine();
          diadromesnotes.append(GrammhText);
        }}
    notefile.close();
    notepathbackup = QString(diadromesnotes.at(0)).remove("Notes=");}
}

void BackUp::on_BackUpNotesButton_clicked()
{
    TexFiles.clear();
    PdfFiles.clear();
    QString destination = QFileDialog::getSaveFileName(this, tr("Επιλέξτε φάκελο αποθήκευσης"),
                                                       notenamebackup+"-files.csv","csv Files (*.csv)");
    if(destination.isEmpty()) return;
    QString line;
    QDirIterator tex_list(notepathbackup , QStringList() << "*.tex", QDir::Files, QDirIterator::Subdirectories);
    while (tex_list.hasNext()){
    TexFiles.append(tex_list.next());}
    if(ui->IncludePdfNotes->isChecked()){
        QDirIterator pdf_list(notepathbackup , QStringList() << "*.pdf", QDir::Files, QDirIterator::Subdirectories);
        while (pdf_list.hasNext()){
        PdfFiles.append(pdf_list.next());}
    }
    QFileInfo dest(destination);
    QString remnote = notepathbackup;
    QString RemovePath = remnote.remove(notenamebackup+"/");
    QString path;

    QProcess *copyprocess = new QProcess;
    copyprocess->start("cp",QStringList()<<"-avr"<<notepathbackup << dest.absolutePath()+"/");
    copyprocess->waitForBytesWritten();
    copyprocess->waitForFinished(-1);
    qDebug() << copyprocess->readAll();

    if(ui->BackUpFolderNotes->isChecked()){
    QDir dir(dest.absolutePath()+"/"+notenamebackup+"-Μόνο τα αρχεία/Αρχεία TeX/");
    if (!dir.exists())
        dir.mkpath(".");
        foreach(QString arxeio,TexFiles){
        QFileInfo texfile(arxeio);
        path = texfile.absoluteFilePath().remove(RemovePath);
        line.append(path+"\n");
        QFile newfile(arxeio);
        newfile.copy(dest.absolutePath()+"/"+notenamebackup+"-Μόνο τα αρχεία/Αρχεία TeX/"+texfile.fileName());
        }
    }

    if(ui->IncludePdfNotes->isChecked()){
    QDir dir(dest.absolutePath()+"/"+notenamebackup+"-Μόνο τα αρχεία/Αρχεία Pdf/");
    if (!dir.exists())
        dir.mkpath(".");
        foreach(QString arxeio,PdfFiles){
        QFileInfo pdffile(arxeio);
        path = pdffile.absoluteFilePath().remove(RemovePath);
        line.append(path+"\n");
        QFile newfile(arxeio);
        newfile.copy(dest.absolutePath()+"/"+notenamebackup+"-Μόνο τα αρχεία/Αρχεία Pdf/"+pdffile.fileName());
        }
    }

    QFile destinationfile(destination);
    destinationfile.open(QIODevice::ReadWrite | QIODevice::Text);
    {
        QTextStream textStream(&destinationfile);
          destinationfile.resize(0);
          textStream << line;
    }
    destinationfile.close();

    if(ui->BackUpZipNotes->isChecked()){
        QString date = QString::number( QDate::currentDate().day() )+"-"+QString::number( QDate::currentDate().month() )
        +"-"+QString::number( QDate::currentDate().year() );
        QString zipfile = dest.absolutePath()+"/"+notenamebackup+"-"+date+".zip";
        QProcess *process = new QProcess;
        process->setWorkingDirectory(RemovePath);
        process->start("zip",QStringList()<<"-r7" << zipfile<< notenamebackup<<"*");
        process->waitForBytesWritten();
        process->waitForFinished(-1);
        qDebug() << process->readAll();
    }
    if(ui->OpenFolder->isChecked()){QDesktopServices::openUrl(QUrl("file:///"+dest.absolutePath()));}
}

void BackUp::on_BackUpZipBase_clicked(bool checked)
{
    if(checked==true){ui->ZipWarning->setText("Απαιτείται εγκατάσταση της εντολής\nzip unzip μέσω του τερματικού.");}
    else if (checked==false){ui->ZipWarning->clear();}
}

void BackUp::on_BackUpZipNotes_clicked(bool checked)
{
    on_BackUpZipBase_clicked(checked);
}
