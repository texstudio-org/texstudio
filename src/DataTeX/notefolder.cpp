#include "notefolder.h"
#include "ui_notefolder.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QCompleter>
#include <QTextStream>
#include <QComboBox>
#include <QString>
#include <QFileDialog>
#include <QLineEdit>

NoteFolder::NoteFolder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteFolder)
{
    ui->setupUi(this);
}

NoteFolder::~NoteFolder()
{
    delete ui;
}

void NoteFolder::on_NoteButton_clicked()
{
    QString notepath = QFileDialog::getExistingDirectory(this, tr("Select folder"),QDir::homePath());
    ui->NotePath->setText(notepath+QDir::separator());
}

bool NoteFolder::isWhiteSpace(const QString & str)
{
  return QRegExp(" |.").exactMatch(str);
}

void NoteFolder::on_NoteButtonBox_accepted()
{
    QString path = ui->NotePath->text();
    QString fileName = ui->NoteFileName->text();
    QString folderName = ui->NoteName->text();
    if(path.isEmpty() || isWhiteSpace(fileName) || isWhiteSpace(folderName) || fileName.isEmpty() || folderName.isEmpty()){
        QMessageBox::warning(this,tr("Error"),tr("Choose a path, afolder and a\nname for your new document database."),QMessageBox::Ok);
        return;
    }
    else{
        QDir dir(path+folderName+QDir::separator());
        if (!dir.exists())
            dir.mkpath(".");
        emit newnote(path,folderName,fileName);
        accept();
    }
}
