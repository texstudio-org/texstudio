#include "addline.h"
#include "ui_addline.h"
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
#include "excel.h"

QFile TomeasFileLine(QDir::currentPath().remove("bin")+"Tomeas.csv");

AddLine::AddLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLine)
{
    ui->setupUi(this);
}

AddLine::~AddLine()
{
    delete ui;
}

void AddLine::EditLine_DataTex(QStringList Line)
{
    ui->NameLine->setText(Line[0]);
    ui->CodeLine->setText(Line[1]);
}


QStringList AddLine::on_OkButton_accepted()
{
    QStringList Line;
    QString line1 = ui->NameLine->text();
    Line.append(line1);
    QString line2 = ui->CodeLine->text();
    Line.append(line2);
    emit grammhline(Line);//---
    return Line;
}
