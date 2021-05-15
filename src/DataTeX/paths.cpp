#include "paths.h"
#include "ui_paths.h"
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
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QRadioButton>
#include <QGroupBox>
#include "basefolder.h"
#include "texstudio.h"
#include <QtSql/QSql>
#include <QSqlQueryModel>
#include "sqlfunctions.h"
#include "addline.h"


Paths::Paths(QWidget *parent, QString path)
    : QDialog(parent)
    , ui(new Ui::Paths)
{
    ui->setupUi(this);

    QStringList DatabasesFileNames;
    QStringList DatabasesNames;
    QSqlQuery fields(Texstudio::DataTeX_Settings);
    fields.exec("SELECT \"FileName\",\"Name\" FROM \"DataBases\"");
    while(fields.next()){
        DatabasesFileNames.append(fields.value(0).toString());
        DatabasesNames.append(fields.value(1).toString());
    }

    QSqlQuery currentBase(Texstudio::DataTeX_Settings);
    currentBase.exec("SELECT db.Name FROM Current_Database_Notes_Folder cd JOIN DataBases db ON cd.Value = db.FileName;");
    while(currentBase.next()){
        base = currentBase.value(0).toString();
    }

    if(DatabasesFileNames.count()>0){
        for (int i=0;i<DatabasesNames.count();i++ ) {
            ui->ComboBaseList->addItem(DatabasesNames.at(i),QVariant(DatabasesFileNames.at(i)));
        }
        ui->ComboBaseList->setCurrentText(base);
    }
    else{
        ui->ComboBaseList->setEnabled(false);
        ui->DeleteBase_2->setEnabled(false);
    }

    QStringList NotesFileNames;
    QStringList NotesNames;
    QSqlQuery fields_2(Texstudio::DataTeX_Settings);
    fields_2.exec("SELECT \"FileName\",\"Name\" FROM \"Notes_Folders\"");
    while(fields_2.next()){
        NotesFileNames.append(fields_2.value(0).toString());
        NotesNames.append(fields_2.value(1).toString());
    }

    QSqlQuery currentNotesBase(Texstudio::DataTeX_Settings);
    currentNotesBase.exec("SELECT db.Name FROM Current_Database_Notes_Folder cd JOIN Notes_Folders db ON cd.Value = db.FileName;");
    while(currentNotesBase.next()){
        note=currentNotesBase.value(0).toString();
    }

    if(NotesFileNames.count()>0){
        for (int i=0;i<NotesFileNames.count();i++ ) {
            ui->ComboNote->addItem(NotesNames.at(i),QVariant(NotesFileNames.at(i)));
        }
        ui->ComboNote->setCurrentText(note);
    }
    else{
        ui->ComboNote->setEnabled(false);
        ui->DeleteBase->setEnabled(false);
    }
    currentbase_Exercises = Texstudio::CurrentTexFilesDataBase;
    QSqlQuery LoadPreambles(currentbase_Exercises);
    LoadPreambles.exec("SELECT \"Id\",\"Name\" FROM \"Preambles\";");
    while(LoadPreambles.next()){ui->PreambleCombo->
                addItem(LoadPreambles.value(1).toString(),QVariant(LoadPreambles.value(0).toString()));}
    QString CurrentPreamble;
    QSqlQuery CurrentPreambleQuery(currentbase_Exercises);
    CurrentPreambleQuery.exec(QString("SELECT \"Name\" FROM \"Preambles\" WHERE \"Id\" = \"%1\";")
                              .arg(Texstudio::CurrentPreamble));
    while(CurrentPreambleQuery.next()){CurrentPreamble = CurrentPreambleQuery.value(0).toString();};
    ui->PreambleCombo->setCurrentText(CurrentPreamble);
    ui->ProgramPath->setText(path);
    ui->NotesPath->setText(Texstudio::CurrentNotesFolderPath);
    ui->DatabaseLineEdit->setText(Texstudio::CurrentDataBasePath);

    LoadTables(ui->ComboBaseList->currentData().toString());

    if(ui->PreambleCombo->count()==0){
        ui->PreambleText->setEnabled(false);
        ui->RemovePreambleButton->setEnabled(false);
    }
}

Paths::~Paths()
{
    delete ui;
}

void Paths::LoadTables(QString database)
{
    database = ui->ComboBaseList->currentData().toString();
    QSqlQueryModel * Metadata = new QSqlQueryModel(this);
    QSqlQueryModel * Bibliography = new QSqlQueryModel(this);
    QSqlQuery tableQuery(Texstudio::DataTeX_Settings);
    tableQuery.prepare(QString("SELECT m.Id AS 'Field Id',m.Name AS 'Name' FROM Metadata_per_Database md JOIN Metadata m ON md.Metadata_Id = m.Id WHERE Database_FileName = \"%1\"")
                       .arg(database));
    tableQuery.exec();
    Metadata->setQuery(tableQuery);
    ui->DatabaseFieldTable->setModel(Metadata);
    ui->DatabaseFieldTable->show();
    QSqlQuery tableQuery_2(Texstudio::DataTeX_Settings);
    tableQuery_2.prepare(QString("SELECT b.Id AS 'Field Id',b.Name AS 'Name' FROM Bibliographic_Fields_per_Database bd JOIN Bibliography b ON bd.Bibliographic_Field = b.Id WHERE Database = \"%1\"")
                       .arg(database));
    tableQuery_2.exec();
    Bibliography->setQuery(tableQuery_2);
    ui->BibliographyFieldsTable->setModel(Bibliography);
    ui->BibliographyFieldsTable->show();
    for (int c = 0; c < ui->DatabaseFieldTable->horizontalHeader()->count(); ++c)
    {
        ui->DatabaseFieldTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    for (int c = 0; c < ui->BibliographyFieldsTable->horizontalHeader()->count(); ++c)
    {
        ui->BibliographyFieldsTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void Paths::on_BaseButton_clicked()
{
    newbasefolder = new BaseFolder(this);
    connect(newbasefolder,SIGNAL(newbase(QString,QString,QString)),this,SLOT(CreateBaseFolder(QString,QString,QString)));
    newbasefolder->show();
    newbasefolder->activateWindow();
}

void Paths::CreateBaseFolder(QString path,QString FolderName,QString fileName)
{
    QString FullPath = path+QDir::separator()+FolderName+QDir::separator()+fileName+".db";
    QSqlQuery AddBaseQuery(Texstudio::DataTeX_Settings);
    AddBaseQuery.exec(QString("INSERT INTO \"Databases\" (\"FileName\",\"Name\",\"Path\") VALUES (\"%1\",\"%2\",\"%3\")")
                       .arg(fileName,FolderName,FullPath));
    ui->DatabaseLineEdit->setText(FullPath);
    ui->ComboBaseList->addItem(FolderName,QVariant(fileName));
    ui->ComboBaseList->setCurrentText(FolderName);
    ui->ComboBaseList->setEnabled(true);
    ui->DeleteBase_2->setEnabled(true);
}

void Paths::CreateNoteFolder(QString path,QString FolderName,QString FileName)
{
    QString FullPath = path+FolderName+QDir::separator()+FileName+".db";
    QSqlDatabase newdatabseFile;
    newdatabseFile = QSqlDatabase::addDatabase("QSQLITE","newbase");
    newdatabseFile.setDatabaseName(FullPath);
    newdatabseFile.open();
    SqlFunctions::ExecuteSqlScriptFile(newdatabseFile,":/src/DataTeX/NotesDatabase.sql");
    newdatabseFile.close();
    QSqlQuery AddNotesQuery(Texstudio::DataTeX_Settings);
    AddNotesQuery.exec(QString("INSERT INTO \"Notes_Folders\" (\"FileName\",\"Name\",\"Path\") VALUES (\"%1\",\"%2\",\"%3\")")
                       .arg(FileName,FolderName,FullPath));
    ui->NotesPath->setText(FullPath);
    ui->ComboNote->addItem(FolderName,QVariant(FileName));
    ui->ComboNote->setCurrentText(FolderName);
    ui->ComboNote->setEnabled(true);
    ui->DeleteBase->setEnabled(true);
}

void Paths::on_buttonBox_accepted()
{
    QString baseFileName = ui->ComboBaseList->currentData().toString();
    QString notesFileName = ui->ComboNote->currentData().toString();
    QSqlQuery SaveData(Texstudio::DataTeX_Settings);
    SaveData.exec(QString("UPDATE \"Current_Database_Notes_Folder\" SET \"Value\" = \"%1\" WHERE \"Setting\" = 'Current_DataBase'")
                  .arg(baseFileName));
    SaveData.exec(QString("UPDATE \"Current_Database_Notes_Folder\" SET \"Value\" = \"%1\" WHERE \"Setting\" = 'Current_Notes_Folder'")
                  .arg(notesFileName));
    Texstudio::CurrentTexFilesDataBase.close();
    Texstudio::CurrentNotesFolderDataBase.close();
    Texstudio::CurrentDataBasePath =
            SqlFunctions::GetCurrentDataBase(Texstudio::DataTeX_Settings,SqlFunctions::SelectCurrentDataBase);
    Texstudio::CurrentNotesFolderPath =
            SqlFunctions::GetCurrentDataBase(Texstudio::DataTeX_Settings,SqlFunctions::SelectCurrentNotesFolderBase);
    Texstudio::CurrentTexFilesDataBase.setDatabaseName(Texstudio::CurrentDataBasePath);
    Texstudio::CurrentTexFilesDataBase.open();
    Texstudio::CurrentNotesFolderDataBase.setDatabaseName(Texstudio::CurrentNotesFolderPath);
    Texstudio::CurrentNotesFolderDataBase.open();
    accept();
}

void Paths::on_NoteButton_clicked()
{
    newnotefolder = new NoteFolder(this);
    connect(newnotefolder,SIGNAL(newnote(QString,QString,QString)),this,SLOT(CreateNoteFolder(QString,QString,QString)));
    newnotefolder->show();
    newnotefolder->activateWindow();
}

void Paths::on_buttonBox_rejected()
{
    reject();
}

void Paths::on_ComboBaseList_currentIndexChanged(int index)
{
    if(index!=-1){
    QString basename = ui->ComboBaseList->currentData().toString();
    QString path;
    LoadTables(basename);
    QSqlQuery Path(Texstudio::DataTeX_Settings);
    Path.exec(QString("SELECT \"Path\" From \"Databases\" WHERE \"FileName\" = \"%1\"").arg(basename));
    while(Path.next()){
        path = Path.value(0).toString();
    }
    ui->DatabaseLineEdit->setText(path);
    }
}

void Paths::on_DeleteBase_2_clicked()
{
    QString Base = ui->ComboBaseList->currentText();
    QString BasePath = QFileInfo(ui->DatabaseLineEdit->text()).absolutePath();
    QCheckBox *cb = new QCheckBox(tr("Open folder"));
    QMessageBox msgbox;
    msgbox.setText(tr("The database %1 wil be deleted!\nDo you wish to proceed?").arg(Base));
    msgbox.setIcon(QMessageBox::Icon::Question);
    msgbox.addButton(QMessageBox::Ok);
    msgbox.addButton(QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Cancel);
    msgbox.setCheckBox(cb);

    if(msgbox.exec() == QMessageBox::Ok){
        QSqlQuery DeleteQuery(Texstudio::DataTeX_Settings);
        DeleteQuery.exec("PRAGMA foreign_keys = ON");
        DeleteQuery.exec(QString("DELETE FROM \"Databases\" WHERE \"FileName\" = \"%1\"").arg(ui->ComboBaseList->currentData().toString()));
        if(ui->ComboBaseList->count()==1){
            ui->ComboBaseList->clear();
            ui->DatabaseFieldTable->reset();
        }
        else {
            ui->ComboBaseList->removeItem(ui->ComboBaseList->currentIndex());
    }
    if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+BasePath));}
    }
}

void Paths::on_ComboNote_currentIndexChanged(int index)
{
    if(index!=-1){
    QString notefolder = ui->ComboNote->currentData().toString();
    QString path;
    QSqlQuery Path(Texstudio::DataTeX_Settings);
    Path.exec(QString("SELECT \"Path\" From \"Notes_Folders\" WHERE \"FileName\" = \"%1\"").arg(notefolder));
    while(Path.next()){
        path = Path.value(0).toString();
    }
    ui->NotesPath->setText(path);
    }
}

void Paths::on_DeleteBase_clicked()
{
    QString Notes = ui->ComboNote->currentText();
    QString NotesPath = QFileInfo(ui->NotesPath->text()).absolutePath();
    QCheckBox *cb = new QCheckBox(tr("Open folder"));
    QMessageBox msgbox;
    msgbox.setText(tr("The database %1 wil be deleted!\nDo you wish to proceed?").arg(Notes));
    msgbox.setIcon(QMessageBox::Icon::Question);
    msgbox.addButton(QMessageBox::Ok);
    msgbox.addButton(QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Cancel);
    msgbox.setCheckBox(cb);

    if(msgbox.exec() == QMessageBox::Ok){
        QSqlQuery DeleteQuery(Texstudio::DataTeX_Settings);
        DeleteQuery.exec("PRAGMA foreign_keys = ON");
        DeleteQuery.exec(QString("DELETE FROM \"Notes_Folders\" WHERE \"FileName\" = \"%1\"").arg(ui->ComboNote->currentData().toString()));
        if(ui->ComboNote->count()==1){
            ui->ComboNote->clear();
        }
        else {
        ui->ComboNote->removeItem(ui->ComboNote->currentIndex());
    }
    if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+NotesPath));}
    }
}

void Paths::on_AddNote_clicked()
{
    QString NotesDatabase = QFileDialog::getOpenFileName(this,tr("Select a Database File"),QDir::homePath(),"sqlite db Files (*.db)");
    if(NotesDatabase.isEmpty())return;
    QString DatabaseName = QFileInfo(NotesDatabase).baseName();
    QStringList list = QFileInfo(NotesDatabase).absolutePath().split(QDir::separator());
    QString folderName = list.last();
    QSqlQuery AddNotesQuery(Texstudio::DataTeX_Settings);
    AddNotesQuery.exec(QString("INSERT INTO \"Notes_Folders\" (\"FileName\",\"Name\",\"Path\") VALUES (\"%1\",\"%2\",\"%3\")")
                       .arg(DatabaseName,folderName,NotesDatabase));
    ui->NotesPath->setText(NotesDatabase);
    ui->ComboNote->addItem(folderName,QVariant(DatabaseName));
    ui->ComboNote->setCurrentText(folderName);

}

void Paths::on_AddBase_clicked()
{
    QString Database = QFileDialog::getOpenFileName(this,tr("Select a Database File"),QDir::homePath(),"sqlite db Files (*.db)");
    if(Database.isEmpty())return;
    QString DatabaseName = QFileInfo(Database).baseName();
    QStringList list = QFileInfo(Database).absolutePath().split(QDir::separator());
    QString folderName = list.last();
    QSqlQuery AddNotesQuery(Texstudio::DataTeX_Settings);
    AddNotesQuery.exec(QString("INSERT INTO \"Databases\" (\"FileName\",\"Name\",\"Path\") VALUES (\"%1\",\"%2\",\"%3\")")
                       .arg(DatabaseName,folderName,Database));

    QSqlDatabase addeddatabaseFile;
    addeddatabaseFile = QSqlDatabase::addDatabase("QSQLITE","addedbase");
    addeddatabaseFile.setDatabaseName(Database);
    addeddatabaseFile.open();

    QStringList MetadataIds = SqlFunctions::Get_StringList_From_Query("SELECT Id FROM BackUp WHERE Table_Id = 'Metadata'",addeddatabaseFile);
    QStringList MetadataNames = SqlFunctions::Get_StringList_From_Query("SELECT Name FROM BackUp WHERE Table_Id = 'Metadata'",addeddatabaseFile);
    QStringList BibIds = SqlFunctions::Get_StringList_From_Query("SELECT Id FROM BackUp WHERE Table_Id = 'Bibliography'",addeddatabaseFile);
    QStringList BibNames = SqlFunctions::Get_StringList_From_Query("SELECT Name FROM BackUp WHERE Table_Id = 'Bibliography'",addeddatabaseFile);
    addeddatabaseFile.close();

    QSqlQuery add(Texstudio::DataTeX_Settings);
    for (int i=0;i<MetadataIds.count();i++) {
        add.exec(QString("INSERT OR IGNORE INTO \"Metadata\" (\"Id\",\"Name\",\"Basic\") VALUES (\""+MetadataIds.at(i)+"\",\""+MetadataNames.at(i)+"\",0)"));
        add.exec("INSERT OR IGNORE INTO \"Metadata_per_Database\" (\"Database_FileName\",\"Metadata_Id\") VALUES (\""+DatabaseName+"\",\""+MetadataIds.at(i)+"\")");
    }

    for (int i=0;i<BibIds.count();i++) {
        add.exec(QString("INSERT OR IGNORE INTO \"Bibliography\" (\"Id\",\"Name\",\"Basic\") VALUES (\""+BibIds.at(i)+"\",\""+BibNames.at(i)+"\",0)"));
        add.exec("INSERT OR IGNORE INTO \"Bibliographic_Fields_per_Database\" (\"Database\",\"Bibliographic_Field\") VALUES (\""+DatabaseName+"\",\""+BibIds.at(i)+"\")");
    }

    ui->DatabaseLineEdit->setEnabled(true);
    ui->DatabaseLineEdit->setText(Database);
    ui->ComboBaseList->addItem(folderName,QVariant(DatabaseName));
    ui->ComboBaseList->setCurrentText(folderName);
    ui->DeleteBase_2->setEnabled(true);
}

void Paths::on_PreambleCombo_currentIndexChanged(const QString &arg1)
{
    QString Preambletext;
    ui->PreambleText->clear();
    QSqlQuery PreambleQuery(currentbase_Exercises);
    PreambleQuery.exec(QString("SELECT \"Preamble_Content\" FROM \"Preambles\" WHERE \"Id\" = \"%1\";")
                       .arg(ui->PreambleCombo->currentData().toString()));
    while(PreambleQuery.next()){Preambletext = PreambleQuery.value(0).toString();}
    ui->PreambleText->append(Preambletext);
}

void Paths::on_OkbuttonBoxPreamble_accepted()
{
    QString Text = ui->PreambleText->toPlainText();
    QSqlQuery WritePreambleQuery(currentbase_Exercises);
    QString preamble = ui->PreambleCombo->currentData().toString();
    QSqlQuery SaveData(Texstudio::DataTeX_Settings);
    SaveData.exec(QString("UPDATE \"Initial_Settings\" SET \"Value\" = \"%1\" WHERE \"Setting\" = 'Current_Preamble'")
                  .arg(preamble));
    WritePreambleQuery.exec(QString("UPDATE \"Preambles\" SET \"Preamble_Content\" = \"%1\" "
                                    "WHERE \"Id\" = \"%2\";").arg(Text,ui->PreambleCombo->currentData().toString()));
    if(ui->PreambleCombo->count()>0){
    Texstudio::CurrentPreamble =
            SqlFunctions::Get_StringList_From_Query(SqlFunctions::GetPreamble,Texstudio::DataTeX_Settings).at(0);
    Texstudio::CurrentPreamble_Content =
            SqlFunctions::Get_StringList_From_Query(QString(SqlFunctions::GetPreamble_Content)
                                                    .arg(Texstudio::CurrentPreamble)
                                                    ,currentbase_Exercises).at(0);
    }
    accept();
}

void Paths::on_OkbuttonBoxPreamble_rejected()
{
    reject();
}

void Paths::on_AddPreambleButton_clicked()
{
    AddLine * newPreamle = new AddLine(this);
    connect(newPreamle,SIGNAL(grammhline(QStringList)),this,SLOT(AddPreamble(QStringList)));
    newPreamle->show();
    newPreamle->activateWindow();
}

void Paths::AddPreamble(QStringList preamble)
{
    QSqlQuery AddPreamble(currentbase_Exercises);
    AddPreamble.exec(QString("INSERT OR IGNORE INTO \"Preambles\" (\"Id\",\"Name\",\"Preamble_Content\") VALUES (\"%1\",\"%2\",'')")
                     .arg(preamble[1],preamble[0]));
    ui->PreambleCombo->addItem(preamble[0],QVariant(preamble[1]));
    ui->PreambleCombo->setCurrentText(preamble[0]);
}

void Paths::on_RemovePreambleButton_clicked()
{
    QString currentPreamble = ui->PreambleCombo->currentText();
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Delete preamble"),tr("The preamble %1 will be deleted!\nDo you wish to proceed?")
                                    .arg(currentPreamble),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        QSqlQuery RemovePreamble(currentbase_Exercises);
        RemovePreamble.exec(QString("DELETE FROM Preambles WHERE Id = \"%1\"").arg(ui->PreambleCombo->currentData().toString()));
        ui->PreambleCombo->removeItem(ui->PreambleCombo->currentIndex());
    }
}

void Paths::on_OpenSettingsButton_clicked()
{
    QString Path = ui->ProgramPath->text();
    QDesktopServices::openUrl(QUrl("file:///"+Path));
}
