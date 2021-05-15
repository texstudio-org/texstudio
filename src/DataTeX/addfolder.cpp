#include "addfolder.h"
#include "ui_addfolder.h"

#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QCompleter>
#include <QTextStream>
#include <QComboBox>
#include <QString>
#include <QFileDialog>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QDesktopServices>
#include <QList>
#include <QUrl>
#include <QDesktopServices>
#include <QGridLayout>
#include <QDebug>
#include <QModelIndex>
#include <algorithm>
#include <QCloseEvent>
#include <QTabWidget>
#include <QTableWidgetItem>
#include "shmeiwseis.h"

addfolder::addfolder(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addfolder)
{
    ui->setupUi(this);

}

addfolder::~addfolder()
{
    delete ui;
}

void addfolder::EditFolder(QString line)
{
    ui->NameLine->setText(line);
}

QString addfolder::on_newName()
{
    QString Name = ui->NameLine->text();
    return Name;
}

void addfolder::on_OkbuttonBoxLine_accepted()
{
    QString newfolder = ui->NameLine->text();//---
    emit grammhfolder(newfolder);//---
    accept();
}

void addfolder::on_OkbuttonBoxLine_rejected()
{
    reject();
}
