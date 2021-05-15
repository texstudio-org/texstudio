#include "datatables.h"
#include "ui_datatables.h"
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
#include "addline.h"
#include "addfolder.h"
#include "texstudio.h"
#include "sqlfunctions.h"


DataTables::DataTables(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataTables)
{
    ui->setupUi(this);
    currentbase = Texstudio::CurrentTexFilesDataBase;
    currentbase_Notes = Texstudio::CurrentNotesFolderDataBase;
    ui->FieldTable->setColumnCount(2);
    QStringList horzHeaders;
    ui->FieldTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->FieldTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FieldTable->setColumnWidth(0,340);
    ui->FieldTable->setColumnWidth(1,130);
    ui->FieldTable->setAlternatingRowColors(true);
    ui->FieldTable->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << tr("Field name") << tr("Primary key");
    ui->FieldTable->setHorizontalHeaderLabels(horzHeaders);
    ui->FieldTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->RemFieldButton->setEnabled(false);
    ui->RemoveChapterButton->setEnabled(false);
    ui->RemoveSectionButton->setEnabled(false);
    ui->RemFieldButton->setEnabled(false);
    ui->EditFieldButton->setEnabled(false);
    ui->EditChapterButton->setEnabled(false);
    ui->EditSectionButton->setEnabled(false);
    ui->RemoveExerciseTypeButton->setEnabled(false);
    ui->EditExerciseTypeButton->setEnabled(false);
    ui->RemDocumentTypeButton->setEnabled(false);
    ui->EditDocumentTypeButton->setEnabled(false);
    ui->RemSubjectType->setEnabled(false);
    ui->EditSubjectTypeButton->setEnabled(false);
    int item=-1;
    QStringList BasicFolders;
    QSqlQuery fields(currentbase);
    fields.exec(SqlFunctions::Fields_Query);
    while(fields.next()){
        item++;
        ui->FieldTable->insertRow(item);
        ui->FieldTable->setItem(item,0 , new QTableWidgetItem(fields.value(0).toString()));
        ui->FieldTable->setItem(item,1 , new QTableWidgetItem(fields.value(1).toString()));
        ui->ComboFields_ChapterTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
        ui->ComboFields_SectionTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
        ui->ComboFields_ExerciseTypeTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
        ui->ComboFields_ExerciseTypeTab->setCurrentIndex(-1);
        ui->ComboFields_ChapterTab->setCurrentIndex(-1);
        ui->ComboFields_SectionTab->setCurrentIndex(-1);
    }
        ui->DocumentTypeTable->setColumnCount(1);
        QStringList horzHeaderspdf;
        ui->DocumentTypeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->DocumentTypeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->DocumentTypeTable->setColumnWidth(0,220);
        ui->DocumentTypeTable->setAlternatingRowColors(true);
        ui->DocumentTypeTable->setStyleSheet("alternate-background-color: #e8e8e8");
        horzHeaderspdf << tr("Document type");
        ui->DocumentTypeTable->setHorizontalHeaderLabels(horzHeaderspdf);
        ui->DocumentTypeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int row=-1;
        QSqlQuery DocumentTypes(currentbase_Notes);
        DocumentTypes.exec(SqlFunctions::GetDocumentTypes);
        while(DocumentTypes.next()){
            row++;
        ui->DocumentTypeTable->insertRow(row);
        ui->DocumentTypeTable->setItem(row,0 , new QTableWidgetItem(DocumentTypes.value(0).toString()));}
        ui->SubjectTypeTable->setColumnCount(2);
        QStringList horzHeaderseidos;
        ui->SubjectTypeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->SubjectTypeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->SubjectTypeTable->setColumnWidth(0,190);
        ui->SubjectTypeTable->setColumnWidth(1,130);
        ui->SubjectTypeTable->setAlternatingRowColors(true);
        ui->SubjectTypeTable->setStyleSheet("alternate-background-color: #e8e8e8");
        horzHeaderseidos << tr("Subject type")<<tr("Primary key");
        ui->SubjectTypeTable->setHorizontalHeaderLabels(horzHeaderseidos);
        ui->SubjectTypeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int line=-1;
        QSqlQuery SubjectTypes(currentbase);
        SubjectTypes.exec(SqlFunctions::GetSubject_Types);
        while(SubjectTypes.next()){
            line++;
        ui->SubjectTypeTable->insertRow(line);
        ui->SubjectTypeTable->setItem(line,0 , new QTableWidgetItem(SubjectTypes.value(0).toString()));
        ui->SubjectTypeTable->setItem(line,1 , new QTableWidgetItem(SubjectTypes.value(1).toString()));}
        ui->FieldTable->sortItems(0);
        ui->DocumentTypeTable->sortItems(0);
        ui->SubjectTypeTable->sortItems(0);

        ui->AddChapterButton->setEnabled(false);
        ui->AddSectionButton->setEnabled(false);
        ui->AddExerciseTypeButton->setEnabled(false);
}

DataTables::~DataTables()
{
    delete ui;
}

void DataTables::on_AddFieldButton_clicked()
{
    newLine = new AddLine(this);
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(AddField(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::AddField(QStringList Line)
{
    QSqlQuery AddField(currentbase);
    AddField.prepare(QString("INSERT INTO \"Fields\" (\"Id\",\"Name\") VALUES(\"%1\",\"%2\")")
                  .arg(Line[1],Line[0]));
    int i = ui->FieldTable->rowCount();
    if(AddField.exec()){
        ui->FieldTable->insertRow(i);
        ui->FieldTable->setItem(i,0 , new QTableWidgetItem(Line[0]));
        ui->FieldTable->setItem(i,1 , new QTableWidgetItem(Line[1]));
        ui->ComboFields_ChapterTab->addItem(Line[0],QVariant(Line[1]));
        ui->ComboFields_ChapterTab->setCurrentIndex(-1);
        ui->ComboFields_SectionTab->addItem(Line[0],QVariant(Line[1]));
        ui->ComboFields_SectionTab->setCurrentIndex(-1);
        ui->ComboFields_ExerciseTypeTab->addItem(Line[0],QVariant(Line[1]));
        ui->ComboFields_ExerciseTypeTab->setCurrentIndex(-1);
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddField.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_RemFieldButton_clicked()
{
    int row = ui->FieldTable->currentRow();
    QString item = ui->FieldTable->item(row, 1)->text();
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Delete field"),tr("The field %1 will be deleted!\n Possible data loss.\nDo you wish to proceed?")
                                    .arg(item),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        QSqlQuery RemoveField(currentbase);
        RemoveField.exec("PRAGMA foreign_keys = ON");
        RemoveField.exec(QString("DELETE FROM \"Fields\" WHERE \"Id\" = \"%1\"").arg(item));
        ui->FieldTable->removeRow(row);
        ui->ComboFields_ChapterTab->removeItem(row);
        ui->ComboFields_SectionTab->removeItem(row);
        ui->ComboFields_ExerciseTypeTab->removeItem(row);
    }
}

void DataTables::on_FieldTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemFieldButton->setEnabled(true);
    ui->EditFieldButton->setEnabled(true);
}

void DataTables::on_ComboFields_ChapterTab_currentIndexChanged(int index)
{
    QString chapter = ui->ComboFields_ChapterTab->currentText();
    ui->ChapterTable->setRowCount(0);
    ui->ChapterTable->setColumnCount(2);
    QStringList horzHeaders;
    ui->ChapterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ChapterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ChapterTable->setColumnWidth(0,340);
    ui->ChapterTable->setColumnWidth(1,130);
    ui->ChapterTable->setAlternatingRowColors(true);
    ui->ChapterTable->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << tr("Chapter name") << tr("Primary key");
    ui->ChapterTable->setHorizontalHeaderLabels(horzHeaders);
    ui->ChapterTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSqlQuery ChaptersQuery(currentbase);
    int i=-1;
    ChaptersQuery.exec(SqlFunctions::Chapters_Query.arg(chapter));
    while(ChaptersQuery.next()){
        i++;
         ui->ChapterTable->insertRow(i);
         ui->ChapterTable->setItem(i,0 , new QTableWidgetItem(ChaptersQuery.value(0).toString()));
         ui->ChapterTable->setItem(i,1 , new QTableWidgetItem(ChaptersQuery.value(1).toString()));
    }
    ui->ChapterTable->sortItems(0);
    if(index>-1){ui->AddChapterButton->setEnabled(true);}
}

void DataTables::on_ComboFields_SectionTab_currentIndexChanged(int index)
{
    ui->SectionTable->setRowCount(0);
    ui->ComboChapters_SectionTab->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           ui->ComboFields_SectionTab->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboChapters_SectionTab->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboChapters_SectionTab->setCurrentIndex(-1);
    ui->AddSectionButton->setEnabled(false);
}

void DataTables::on_ComboChapters_SectionTab_currentIndexChanged(int index)
{
    ui->SectionTable->setRowCount(0);
    ui->SectionTable->setColumnCount(2);
    QString section = ui->ComboChapters_SectionTab->currentText();
    QStringList horzHeaders;
    ui->SectionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SectionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SectionTable->setColumnWidth(0,340);
    ui->SectionTable->setColumnWidth(1,100);
    ui->SectionTable->setAlternatingRowColors(true);
    ui->SectionTable->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << tr("Section name") << tr("Primary key");
    ui->SectionTable->setHorizontalHeaderLabels(horzHeaders);
    ui->SectionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int i=-1;
     QSqlQuery SectionsQuery(currentbase);
     SectionsQuery.exec(SqlFunctions::Sections_Chapters_Query.arg(section));
     while (SectionsQuery.next()){
         i++;
        ui->SectionTable->insertRow(i);
        ui->SectionTable->setItem(i,0 , new QTableWidgetItem(SectionsQuery.value(0).toString()));
        ui->SectionTable->setItem(i,1 , new QTableWidgetItem(SectionsQuery.value(1).toString()));
    }
     ui->SectionTable->sortItems(0);
     if(index>-1){ui->AddSectionButton->setEnabled(true);}
}

void DataTables::AddChapter(QStringList Line)
{
    QStringList list;
    QString field = ui->ComboFields_ChapterTab->currentData().toString();
    QSqlQuery AddChapter(currentbase);
    AddChapter.prepare(QString("INSERT INTO \"Chapters\" (\"Id\",\"Name\",\"Field\") VALUES(\"%1\",\"%2\",\"%3\")")
                  .arg(Line[1],Line[0],field));
    int i = ui->ChapterTable->rowCount();
    if(AddChapter.exec()){
        ui->ChapterTable->insertRow(i);
        ui->ChapterTable->setItem(i,0 , new QTableWidgetItem(Line[0]));
        ui->ChapterTable->setItem(i,1 , new QTableWidgetItem(Line[1]));
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddChapter.lastError().text(),QMessageBox::Ok);
    }
    ui->ComboFields_SectionTab->setCurrentIndex(-1);
}

void DataTables::on_AddChapterButton_clicked()
{
    newLine = new AddLine(this);
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(AddChapter(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::on_RemoveChapterButton_clicked()
{
    int row = ui->ChapterTable->currentRow();
    QString ChapterId = ui->ChapterTable->item(row, 1)->text();
    QString FieldId = ui->ComboFields_ChapterTab->currentData().toString();
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Delete chapter"),tr("The chapter %1 will be deleted!\nPossible data loss.\nDo you wish to proceed?")
                                      .arg(ChapterId),
                  QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        QSqlQuery RemoveChapter(currentbase);
        RemoveChapter.exec("PRAGMA foreign_keys = ON");
        RemoveChapter.exec(QString("DELETE FROM \"Chapters\" WHERE \"Id\" = \"%1\" AND \"Field\" = \"%2\"")
                         .arg(ChapterId,FieldId));
        ui->ChapterTable->removeRow(row);
    }
}

void DataTables::on_ChapterTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemoveChapterButton->setEnabled(true);
    ui->EditChapterButton->setEnabled(true);
}


void DataTables::AddSection(QStringList Line)
{
    QString FieldId = ui->ComboFields_SectionTab->currentData().toString();
    QString ChapterId = ui->ComboChapters_SectionTab->currentData().toString();
    QSqlQuery AddSection(currentbase);
    AddSection.prepare(QString("INSERT INTO \"Sections\" (\"Id\",\"Name\",\"Field\",\"Chapter\") VALUES(\"%1\",\"%2\",\"%3\",\"%4\")")
                    .arg(Line[1],Line[0],FieldId,ChapterId));
        int i = ui->SectionTable->rowCount();
    if(AddSection.exec()){
    ui->SectionTable->insertRow(i);
    ui->SectionTable->setItem(i,0 , new QTableWidgetItem(Line[0]));
    ui->SectionTable->setItem(i,1 , new QTableWidgetItem(Line[1]));
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddSection.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_AddSectionButton_clicked()
{
    newLine = new AddLine(this);
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(AddSection(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::on_SectionTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemoveSectionButton->setEnabled(true);
    ui->EditSectionButton->setEnabled(true);
}

void DataTables::on_RemoveSectionButton_clicked()
{
    int row = ui->SectionTable->currentRow();
    QString kwdikos = ui->SectionTable->item(row, 1)->text();
    QString field = ui->ComboFields_SectionTab->currentData().toString();
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Delete section"),tr("The section %1 will be deleted!\nPossible data loss.\nDo you wish to proceed?")
                                     .arg(kwdikos),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        QSqlQuery RemoveSection(currentbase);
        RemoveSection.exec("PRAGMA foreign_keys = ON");
        RemoveSection.exec(QString("DELETE FROM \"Sections\" WHERE \"Id\" = \"%1\" AND \"Field\" = \"%2\"")
                           .arg(kwdikos,field));
        ui->SectionTable->removeRow(row);
    }
}

void DataTables::on_buttonBox_accepted()
{
    accept();
}

void DataTables::on_buttonBox_rejected()
{
    reject();
}

void DataTables::on_EditFieldButton_clicked()
{
    int row = ui->FieldTable->currentRow();
    QStringList line;
    line.append(ui->FieldTable->item(row, 0)->text());
    line.append(ui->FieldTable->item(row, 1)->text());
    newLine = new AddLine(this);
    newLine->EditLine_DataTex(line);
    connect(this,SIGNAL(addline(QStringList)),newLine,SLOT(EditLine_DataTex(QStringList)));
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(EditField(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::EditField(QStringList Line)
{
    int row = ui->FieldTable->currentRow();
    QString FieldName = ui->FieldTable->item(row, 0)->text();
    QString FieldId = ui->FieldTable->item(row, 1)->text();
    QSqlQuery EditField(currentbase);
    EditField.exec("PRAGMA foreign_keys = ON");
    EditField.prepare(QString("UPDATE \"Fields\" SET \"Id\" = \"%1\",\"Name\" = \"%2\" WHERE \"Id\" = \"%3\" AND \"Name\" = \"%4\"")
                   .arg(Line[1],Line[0],FieldId,FieldName));
    if(EditField.exec()){
        ui->FieldTable->item(row,0)->setText(QString(Line[0]));
        ui->FieldTable->item(row,1)->setText(QString(Line[1]));
        ui->ComboFields_ChapterTab->clear();
        ui->ComboFields_SectionTab->clear();

        UpdateDatabaseMetadata("Field",Line[1],FieldId+"-",Line[1]+"-",
                "/DTX-"+FieldId+"-","/DTX-"+Line[1]+"-",
                "/"+FieldName+"/","/"+Line[0]+"/");

        QSqlQuery fields(currentbase);
        fields.exec(SqlFunctions::Fields_Query);
        while(fields.next()){
            ui->ComboFields_ChapterTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
            ui->ComboFields_SectionTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
            ui->ComboFields_ExerciseTypeTab->addItem(fields.value(0).toString(), QVariant(fields.value(1).toString()));
            ui->ComboFields_ChapterTab->setCurrentIndex(-1);
            ui->ComboFields_SectionTab->setCurrentIndex(-1);
            ui->ComboFields_ExerciseTypeTab->setCurrentIndex(-1);
        }
        emit addline(Line);
        }
    else{
        QMessageBox::warning(this,tr("Error"),EditField.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::UpdateDatabaseMetadata(QString Id, QString DBField, QString oldId1, QString newId1, QString oldPath1, QString newPath1, QString oldPath2, QString newPath2)
{
    QStringList Paths;
    QStringList Ids;
    QSqlQuery EditFileMetadata(currentbase);
    EditFileMetadata.exec(QString("SELECT \"Id\",\"Path\" FROM \"Database_Files\" WHERE \"%1\" = \"%2\"").arg(DBField,Id));
    while(EditFileMetadata.next()){
        Ids.append(EditFileMetadata.value(0).toString());
        Paths.append(EditFileMetadata.value(1).toString());
    }
    for(int i=0;i<Ids.count();i++){
        QString id = Ids.at(i);
        QString oldId = id;
        QString path = Paths.at(i);
        QString oldpath = path;
        id.replace(oldId1,newId1);
        path.replace(oldPath1,newPath1);
        path.replace(oldPath2,newPath2);
        QSqlQuery Replace(currentbase);
        Replace.exec(QString("UPDATE \"Database_Files\" SET \"Id\" = \"%1\" WHERE \"Id\" = \"%2\"")
                       .arg(id,oldId));
        Replace.exec(QString("UPDATE \"Database_Files\" SET \"Path\" = \"%1\" WHERE \"Id\" = \"%2\"")
                       .arg(path,id));
        QDir dir(QFileInfo(path).absolutePath()); if (!dir.exists()){dir.mkpath(".");}
        QFile file(oldpath);
        file.rename(oldpath,path);
        QFile newfile(path);
        newfile.open(QIODevice::ReadWrite);
        QTextStream content(&newfile);
        QString text = content.readAll();
        text.replace("%# Database File : "+oldId,"%# Database File : "+id);
        text.replace("%# End of file "+oldId,"%# End of file "+id);
        newfile.resize(0);
        content << text;
        newfile.close();
    }
}

void DataTables::on_EditChapterButton_clicked()
{
    int row = ui->ChapterTable->currentRow();
    QStringList line;
    line.append(ui->ChapterTable->item(row, 0)->text());
    line.append(ui->ChapterTable->item(row, 1)->text());
    newLine = new AddLine(this);
    newLine->EditLine_DataTex(line);
    connect(this,SIGNAL(addline(QStringList)),newLine,SLOT(EditLine_DataTex(QStringList)));
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(EditChapter(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::EditChapter(QStringList Line)
{
    int row = ui->ChapterTable->currentRow();
    QString ChapterId = ui->ChapterTable->item(row, 1)->text();
    QString ChapterName = ui->ChapterTable->item(row, 0)->text();
    QSqlQuery EditChapter(currentbase);
    EditChapter.exec("PRAGMA foreign_keys = ON");
    EditChapter.prepare(QString("UPDATE \"Chapters\" SET \"Id\" = \"%1\",\"Name\" = \"%2\" WHERE \"Id\" = \"%3\"")
                     .arg(Line[1],Line[0],ChapterId));
    if(EditChapter.exec()){
        ui->ChapterTable->item(row,0)->setText(QString(Line[0]));
        ui->ChapterTable->item(row,1)->setText(QString(Line[1]));
        ui->ComboChapters_SectionTab->clear();
        QSqlQuery ChaptersQuery(currentbase);
        ChaptersQuery.exec(SqlFunctions::Chapters_Query.arg(ChapterId));
        while(ChaptersQuery.next()){
            ui->ComboChapters_SectionTab->addItem(ChaptersQuery.value(0).toString(), QVariant(ChaptersQuery.value(1).toString()));
            ui->ComboChapters_ExerciseTypeTab->addItem(ChaptersQuery.value(0).toString(), QVariant(ChaptersQuery.value(1).toString()));
        }
        ui->ComboChapters_SectionTab->setCurrentIndex(-1);
        ui->ComboChapters_ExerciseTypeTab ->setCurrentIndex(-1);

        UpdateDatabaseMetadata("Chapter",Line[1],"-"+ChapterId+"-","-"+Line[1]+"-",
                "-"+ChapterId+"-","-"+Line[1]+"-",
                "","");

        emit addline(Line);
    }
    else{
        QMessageBox::warning(this,tr("Error"),EditChapter.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_EditSectionButton_clicked()
{
    int row = ui->SectionTable->currentRow();
    QStringList line;
    line.append(ui->SectionTable->item(row, 0)->text());
    line.append(ui->SectionTable->item(row, 1)->text());
    newLine = new AddLine(this);
    newLine->EditLine_DataTex(line);
    connect(this,SIGNAL(addline(QStringList)),newLine,SLOT(EditLine_DataTex(QStringList)));
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(EditSection(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::EditSection(QStringList Line)
{
    int row = ui->SectionTable->currentRow();
    QString SectionId = ui->SectionTable->item(row, 1)->text();
    QString SectionName = ui->SectionTable->item(row, 0)->text();
    QSqlQuery EditSection(currentbase);
    EditSection.exec("PRAGMA foreign_keys = ON");
    EditSection.prepare(QString("UPDATE \"Sections\" SET \"Id\" = \"%1\",\"Name\" = \"%2\" WHERE \"Id\" = \"%3\"")
                     .arg(Line[1],Line[0],SectionId));
    if(EditSection.exec()){
        ui->SectionTable->item(row,0)->setText(QString(Line[0]));
        ui->SectionTable->item(row,1)->setText(QString(Line[1]));
        QSqlQuery SectionsQuery(currentbase);
        SectionsQuery.exec(SqlFunctions::Sections_Chapters_Query.arg(SectionId));
        while(SectionsQuery.next()){
            ui->ComboSections_ExerciseTypeTab->addItem(SectionsQuery.value(0).toString(), QVariant(SectionsQuery.value(1).toString()));
        }
        ui->ComboSections_ExerciseTypeTab ->setCurrentIndex(-1);

        UpdateDatabaseMetadata("Section",Line[1],SectionId,Line[1],
                SectionId,Line[1],
                SectionName,Line[0]);

        emit addline(Line);
    }
    else{
        QMessageBox::warning(this,tr("Error"),EditSection.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_AddDocumentTypeButton_clicked()
{
    newFolder = new addfolder(this);
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(AddDocumentType(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void DataTables::AddDocumentType(QString Line)
{
    QSqlQuery AddDocumentType(currentbase_Notes);
    AddDocumentType.exec("PRAGMA foreign_keys = ON");
    AddDocumentType.prepare(QString("INSERT INTO \"Document_Types\" (\"Name\") VALUES(\"%1\")")
                    .arg(Line));
    int i = ui->DocumentTypeTable->rowCount();
    if(AddDocumentType.exec()){
        ui->DocumentTypeTable->insertRow(i);
        ui->DocumentTypeTable->setItem(i,0 , new QTableWidgetItem(Line));
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddDocumentType.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_RemDocumentTypeButton_clicked()
{
    int row = ui->DocumentTypeTable->currentRow();
    QString DocumentType = ui->DocumentTypeTable->item(row, 0)->text();
    QSqlQuery RemoveDocumentType(currentbase_Notes);
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                 tr("Delete document type"),tr("The document type %1 will be deleted!\nPossible data loss.\nDo you wish to prceed?")
                                    .arg(DocumentType),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        RemoveDocumentType.exec("PRAGMA foreign_keys = ON");
        RemoveDocumentType.exec(QString("DELETE FROM \"Document_Types\" WHERE \"Name\" = \"%1\"")
                        .arg(DocumentType));
        ui->DocumentTypeTable->removeRow(row);
    }
}

void DataTables::on_EditDocumentTypeButton_clicked()
{
    QString eidos = ui->DocumentTypeTable->currentItem()->text();
    newFolder = new addfolder(this);
    newFolder->EditFolder(eidos);
    connect(this,SIGNAL(addfolder_signal(QString)),newFolder,SLOT(EditFolder(QString)));
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(EditDocumentType(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void DataTables::EditDocumentType(QString Line)
{
    int row = ui->DocumentTypeTable->currentRow();
    QString DocumentType = ui->DocumentTypeTable->item(row, 0)->text();
    ui->DocumentTypeTable->item(row,0)->setText(QString(Line));
    QSqlQuery EditDocumentType(currentbase_Notes);
    if(EditDocumentType.exec()){
        EditDocumentType.exec("PRAGMA foreign_keys = ON");
        EditDocumentType.prepare(QString("UPDATE \"Document_Types\" SET \"Name\" = \"%1\" WHERE \"Name\" = \"%2\"")
                         .arg(Line,DocumentType));
        emit addfolder_signal(Line);
    }
    else{
        QMessageBox::warning(this,tr("Error"),EditDocumentType.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_DocumentTypeTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemDocumentTypeButton->setEnabled(true);
    ui->EditDocumentTypeButton->setEnabled(true);
}

void DataTables::on_AddSubjectTypeButton_clicked()//23/9
{
    newLine = new AddLine(this);
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(AddSubjectType(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::AddSubjectType(QStringList Line)
{
    QSqlQuery AddSubjectType(currentbase);
    AddSubjectType.exec("PRAGMA foreign_keys = ON");
    AddSubjectType.prepare(QString("INSERT INTO \"Subject_Types\" (\"Id\",\"Name\") VALUES(:id,:name)"));
    AddSubjectType.bindValue(":id",Line[1]);
    AddSubjectType.bindValue(":name",Line[0]);
    int i = ui->SubjectTypeTable->rowCount();
    if(AddSubjectType.exec()){
        QSqlQuery AddExType(currentbase);
        AddExType.exec("PRAGMA foreign_keys = ON");
        AddExType.prepare(QString("INSERT INTO \"Exercise_Types\" (\"Id\",\"Name\") VALUES(:id,:name)"));
        AddExType.bindValue(":id",Line[1]);
        AddExType.bindValue(":name",Line[0]);
        AddExType.exec();
        ui->SubjectTypeTable->insertRow(i);
        ui->SubjectTypeTable->setItem(i,0 , new QTableWidgetItem(Line[0]));
        ui->SubjectTypeTable->setItem(i,1 , new QTableWidgetItem(Line[1]));
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddSubjectType.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_RemSubjectType_clicked()
{
    int row = ui->SubjectTypeTable->currentRow();
    QString SubjectType = ui->SubjectTypeTable->item(row, 0)->text();
    QSqlQuery RemoveDocumentType(currentbase);
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 "Delete subject type",tr("The subject type %1 will be deleted!\nPossible data loss.\nDo you wish to proceed?")
                                        .arg(SubjectType)
                                        ,QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        RemoveDocumentType.exec("PRAGMA foreign_keys = ON");
        RemoveDocumentType.exec(QString("DELETE FROM \"Subject_Types\" WHERE \"Name\" = \"%1\"")
                        .arg(SubjectType));
        ui->SubjectTypeTable->removeRow(row);
    }
}

void DataTables::on_EditSubjectTypeButton_clicked()
{
    int row = ui->SubjectTypeTable->currentRow();
    QStringList line;
    line.append(ui->SubjectTypeTable->item(row, 0)->text());
    line.append(ui->SubjectTypeTable->item(row, 1)->text());
    newLine = new AddLine(this);
    newLine->EditLine_DataTex(line);
    connect(this,SIGNAL(addline(QStringList)),newLine,SLOT(EditLine_DataTex(QStringList)));
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(EditSubjectType(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::EditSubjectType(QStringList Line)
{
    int row = ui->SubjectTypeTable->currentRow();
    QString SubjectType = ui->SubjectTypeTable->item(row, 1)->text();
    ui->SubjectTypeTable->item(row,0)->setText(QString(Line[0]));
    ui->SubjectTypeTable->item(row,1)->setText(QString(Line[1]));
    QSqlQuery EditSubjectType(currentbase);
    if(EditSubjectType.exec()){
        EditSubjectType.exec("PRAGMA foreign_keys = ON");
        EditSubjectType.prepare(QString("UPDATE \"Document_Types\" SET \"Id\" = \"%1\",\"Name\" = \"%2\" WHERE \"Id\" = \"%3\"")
                         .arg(Line[1],Line[0],SubjectType));
        emit addline(Line);
    }
    else{
        QMessageBox::warning(this,tr("Error"),EditSubjectType.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_SubjectTypeTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemSubjectType->setEnabled(true);
    ui->EditSubjectTypeButton->setEnabled(true);
}

void DataTables::on_ComboFields_ExerciseTypeTab_currentIndexChanged(int index)
{
    ui->ExerciseTypeTable->setRowCount(0);
    ui->ComboChapters_ExerciseTypeTab->clear();
    QString kef = ui->ComboFields_ExerciseTypeTab->currentData().toString();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           ui->ComboFields_ExerciseTypeTab->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboChapters_ExerciseTypeTab->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboChapters_ExerciseTypeTab->setCurrentIndex(-1);
    ui->AddExerciseTypeButton->setEnabled(false);
}

void DataTables::on_ComboChapters_ExerciseTypeTab_currentIndexChanged(int index)
{
    ui->ExerciseTypeTable->setRowCount(0);
    ui->ComboSections_ExerciseTypeTab->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                           ui->ComboChapters_ExerciseTypeTab->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboSections_ExerciseTypeTab->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboSections_ExerciseTypeTab->setCurrentIndex(-1);
    ui->AddExerciseTypeButton->setEnabled(false);
}

void DataTables::on_ComboSections_ExerciseTypeTab_currentIndexChanged(int index)
{
    ui->ExerciseTypeTable->setRowCount(0);
    ui->ExerciseTypeTable->setColumnCount(2);
    QString field = ui->ComboFields_ExerciseTypeTab->currentText();
    QString enot = ui->ComboSections_ExerciseTypeTab->currentData().toString();
    QStringList horzHeaders;
    ui->ExerciseTypeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ExerciseTypeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ExerciseTypeTable->setAlternatingRowColors(true);
    ui->ExerciseTypeTable->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << tr("Exercise type") << tr("Primary key");
    ui->ExerciseTypeTable->setHorizontalHeaderLabels(horzHeaders);
    ui->ExerciseTypeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int i=-1;
    QSqlQuery ExerciseTypes(currentbase);
    ExerciseTypes.exec(SqlFunctions::Exercise_Types_Query.arg(enot));
    while(ExerciseTypes.next()){
        i++;
        ui->ExerciseTypeTable->insertRow(i);
        ui->ExerciseTypeTable->setItem(i,0 , new QTableWidgetItem(ExerciseTypes.value(0).toString()));
        ui->ExerciseTypeTable->setItem(i,1 , new QTableWidgetItem(ExerciseTypes.value(1).toString()));
    }
    ui->ExerciseTypeTable->sortItems(0);
    if(index>-1){ui->AddExerciseTypeButton->setEnabled(true);}
}

void DataTables::on_AddExerciseTypeButton_clicked()
{
    newLine = new AddLine(this);
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(AddExerciseType(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::AddExerciseType(QStringList Line)
{
    QStringList list;
    QString section = ui->ComboSections_ExerciseTypeTab->currentData().toString();
    QSqlQuery AddSection1(currentbase);
    QSqlQuery AddSection2(currentbase);
    AddSection1.prepare(QString("INSERT OR IGNORE INTO \"Exercise_Types\" (\"Id\",\"Name\") VALUES(\"%1\",\"%2\")")
                    .arg(Line[1],Line[0]));
    AddSection2.prepare(QString("INSERT OR IGNORE INTO \"Sections_Exercises\" (\"Exercise_Id\",\"Exercise_Name\",\"Section_Id\") VALUES(\"%1\",\"%2\",\"%3\")")
                    .arg(Line[1],Line[0],section));
    int i = ui->ExerciseTypeTable->rowCount();
    if(AddSection1.exec() && AddSection2.exec()){
        ui->ExerciseTypeTable->insertRow(i);
        ui->ExerciseTypeTable->setItem(i,0 , new QTableWidgetItem(Line[0]));
        ui->ExerciseTypeTable->setItem(i,1 , new QTableWidgetItem(Line[1]));
    }
    else{
        QMessageBox::warning(this,tr("Error"),AddSection2.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_RemoveExerciseTypeButton_clicked()
{
    int row = ui->ExerciseTypeTable->currentRow();
    QString ExerciseType = ui->ExerciseTypeTable->item(row, 1)->text();
    QString SectionId = ui->ComboSections_ExerciseTypeTab->currentData().toString();
    QSqlQuery RemoveExerciseType(currentbase);
    RemoveExerciseType.exec(QString("DELETE FROM \"Sections_Exercises\" WHERE \"Exercise_Id\" = \"%1\" AND \"Section_Id\" = \"%2\"")
                     .arg(ExerciseType,SectionId));
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 "Delete exercise type",tr("The exercise type %1 will be deleted!\nDo you wish to proceed?").arg(ExerciseType),
                  QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        ui->ExerciseTypeTable->removeRow(row);
    }
}

void DataTables::on_EditExerciseTypeButton_clicked()
{
    int row = ui->ExerciseTypeTable->currentRow();
    QStringList line;
    line.append(ui->ExerciseTypeTable->item(row, 0)->text());
    line.append(ui->ExerciseTypeTable->item(row, 1)->text());
    newLine = new AddLine(this);
    newLine->EditLine_DataTex(line);
    connect(this,SIGNAL(addline(QStringList)),newLine,SLOT(EditLine_DataTex(QStringList)));
    connect(newLine,SIGNAL(grammhline(QStringList)),this,SLOT(EditExerciseType(QStringList)));
    newLine->show();
    newLine->activateWindow();
}

void DataTables::EditExerciseType(QStringList Line)
{
    QString section = ui->ComboSections_ExerciseTypeTab->currentData().toString();
    int row = ui->ExerciseTypeTable->currentRow();
    QString ExerciseTypeId = ui->ExerciseTypeTable->item(row, 1)->text();
    QSqlQuery EditExerciseType1(currentbase);
    QSqlQuery EditExerciseType2(currentbase);
    EditExerciseType1.exec(QString("INSERT OR IGNORE INTO \"Exercise_Types\" (\"Id\",\"Name\") VALUES(\"%1\",\"%2\")")
                     .arg(Line[1],Line[0]));
    EditExerciseType2.prepare(QString("UPDATE \"Sections_Exercises\" SET \"Exercise_Id\" = \"%1\",\"Exercise_Name\" = \"%2\""
                             " WHERE \"Exercise_Id\" = \"%3\" "
                             "AND \"Section_Id\" = \"%4\"")
                     .arg(Line[1],Line[0],ExerciseTypeId,section));
    if(EditExerciseType2.exec()){
        ui->ExerciseTypeTable->item(row,0)->setText(QString(Line[0]));
        ui->ExerciseTypeTable->item(row,1)->setText(QString(Line[1]));
        emit addline(Line);
    }
    else{
        QMessageBox::warning(this,tr("Error"),EditExerciseType1.lastError().text()+EditExerciseType2.lastError().text(),QMessageBox::Ok);
    }
}

void DataTables::on_ExerciseTypeTable_itemClicked(QTableWidgetItem *item)
{
    ui->RemoveExerciseTypeButton->setEnabled(true);
    ui->EditExerciseTypeButton->setEnabled(true);
}
