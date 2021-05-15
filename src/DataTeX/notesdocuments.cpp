#include "notesdocuments.h"
#include "ui_notesdocuments.h"
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
#include <QDebug>
#include <QCloseEvent>
#include <QRadioButton>
#include <QButtonGroup>
#include "addfolder.h"
#include "sqlfunctions.h"
#include "addfiletoeditor.h"


NotesDocuments::NotesDocuments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotesDocuments)
{
    radiogroup = new QButtonGroup;
    NotesPath = QFileInfo(Texstudio::CurrentNotesFolderPath).absolutePath()+QDir::separator();
    currentbase = Texstudio::CurrentNotesFolderDataBase;
    currentbase_Exercises = Texstudio::CurrentTexFilesDataBase;
    radioList.clear();
    checkList.clear();
    ui->setupUi(this);
    ui->DocumentTable->setColumnCount(3);
    QStringList horzHeaders;
    horzHeaders << tr("File type") << tr("Name")<<"Path";
    ui->DocumentTable->setHorizontalHeaderLabels(horzHeaders);
    ui->DocumentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DocumentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int c = 0; c < ui->DocumentTable->horizontalHeader()->count()-1; ++c)
    {
        ui->DocumentTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->DocumentTable->setAlternatingRowColors(true);
    ui->DocumentTable->setStyleSheet("alternate-background-color: #e8e8e8");
    ui->DocumentTable->horizontalHeader()->setStretchLastSection(true);
    QStringList horzHeaders2;
    horzHeaders2 << tr("File Id") << tr("Section")<<tr("Exercise type");
    ui->TexFileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TexFileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int c = 0; c < ui->TexFileTable->horizontalHeader()->count()-1; ++c)
    {
        ui->TexFileTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->TexFileTable->setAlternatingRowColors(true);
    ui->TexFileTable->setStyleSheet("alternate-background-color: #e8e8e8");
    ui->CheckEpiloghOlwn->setEnabled(false);
    ui->CheckEpiloghOlwn->setChecked(false);
    ui->OpenFolderButton->setEnabled(false);
    QStringList list;
    ui->FolderStructure->sortItems();
    ui->OpenPdfButton->setEnabled(false);
    ui->OpenTexButton->setEnabled(false);
    ui->BasicFoldersTable->setColumnCount(1);
    QStringList Headers;
    ui->BasicFoldersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->BasicFoldersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->BasicFoldersTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->BasicFoldersTable->setAlternatingRowColors(true);
    ui->BasicFoldersTable->setStyleSheet("alternate-background-color: #e8e8e8");
    Headers << tr("Folder name");
    ui->BasicFoldersTable->setHorizontalHeaderLabels(Headers);
    ui->BasicFoldersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SubFolderTable->setEnabled(false);
    ui->SubsubFolderTable->setEnabled(false);
    ui->AddSubButton->setEnabled(false);
    ui->AddSubsubButton->setEnabled(false);
    ui->RemBasicButton->setEnabled(false);
    ui->RemSubButton->setEnabled(false);
    ui->RemSubsubButton->setEnabled(false);
    ui->EditBasicButton->setEnabled(false);
    ui->EditSubButton->setEnabled(false);
    ui->EditSubsubButton->setEnabled(false);
    ui->SubsubCheck->setEnabled(false);
    ui->CreateSubButton->setEnabled(false);
    ui->CreateSubsubButton->setEnabled(false);
    ui->NameLine->setEnabled(false);
    ui->pathline->setEnabled(false);
    ui->CreatePdfCheckbox->setEnabled(false);
    ui->InsertFilesCheckBox->setEnabled(false);
    ui->SolutionRadioButton->setEnabled(false);
    ui->HintRadioButton->setEnabled(false);

    QStringList BasicFolders;
    QSqlQuery fields(currentbase);
    fields.exec("SELECT \"Name\" FROM \"Basic_Folders\";");
    while(fields.next()){
        BasicFolders.append(fields.value(0).toString());
    }
    for (int item=0;item<BasicFolders.count();item++ ) {
        ui->BasicFoldersTable->insertRow(item);
        ui->BasicFoldersTable->setItem(item,0, new QTableWidgetItem(BasicFolders.at(item)));}
    QStringList FileTypeList;
    QSqlQuery DocTypes(currentbase);
    DocTypes.exec(SqlFunctions::GetDocumentTypes);
    while(DocTypes.next()){
        FileTypeList.append(DocTypes.value(0).toString());
    }
    double items = FileTypeList.count();
    int half = ceil(items/2);
    for (int i=0;i<half;i++) {
        QRadioButton * radio = new QRadioButton(FileTypeList.at(i));
        radioList.append(radio);
        ui->gridLayout->addWidget(radioList.at(i),i,0);
        radioList.at(i)->setEnabled(false);
        radiogroup->addButton(radioList.at(i));
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::Folder);
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::SavePath);
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::enable3check);}
    for (int i=0;i<items-half;i++) {
        QRadioButton * radio = new QRadioButton(FileTypeList.at(i+half));
        radioList.append(radio);
        ui->gridLayout->addWidget(radioList.at(i+half),i,1);
        radioList.at(i+half)->setEnabled(false);
        radiogroup->addButton(radioList.at(i+half));
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::Folder);
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::SavePath);
    connect(radio, &QRadioButton::toggled, this, &NotesDocuments::enable3check);}

    for (int i=0;i<int(items);i++) {
        QCheckBox * check = new QCheckBox(FileTypeList.at(i));
        checkList.append(check);
        ui->gridLayout_2->addWidget(checkList.at(i),i,0);
        checkList.at(i)->setEnabled(false);
    connect(check, &QCheckBox::toggled, this, &NotesDocuments::showItemsTable);}

    QStringList BasicFolderNames;
    QStringList names;
    QSqlQuery folders(currentbase);
    folders.exec("SELECT (\"Basic_Id\" || ' - ' || \"Sub_Id\"),\"Basic_Id\" FROM \"SubFolders_per_Basic\" ORDER BY 1;");
    while(folders.next()){
        names.append(folders.value(0).toString());
        BasicFolderNames.append(folders.value(1).toString());
    }

    ui->FolderStructure->clear();
    for (int i=0;i<names.count();i++ ) {
        ui->FolderStructure->addItem(names.at(i));
        ui->FolderStructure->item(i)->setData(Qt::UserRole,BasicFolderNames.at(i));
    }
    ui->OpenPdfButton->setEnabled(false);
    ui->OpenTexButton->setEnabled(false);
}

NotesDocuments::~NotesDocuments()
{
    delete ui;
}

void NotesDocuments::on_FolderStructure_itemClicked(QListWidgetItem *item)
{
    ui->CheckEpiloghOlwn->setEnabled(true);
    ui->CheckEpiloghOlwn->setChecked(false);
    for (int i=0;i<checkList.count();i++) {
        checkList.at(i)->setEnabled(true);
        checkList.at(i)->setChecked(false);}
    ui->DocumentTable->clear();
    ui->DocumentTable->setRowCount(0);
    QStringList horzHeaders;
    horzHeaders << tr("File type") << tr("Name");
    ui->DocumentTable->setHorizontalHeaderLabels(horzHeaders);
    QStringList line = item->text().split(" - ");
    QStringList Document_Types;
    QStringList Documents;
    QStringList DocumentPath;
    QSqlQuery DocumentsQuery(currentbase);
        DocumentsQuery.prepare(QString("SELECT \"Document_Type\" AS 'File type',\"Id\" AS 'Name',\"Path\""
"FROM \"Documents\" WHERE \"Basic_Folder\" = :basic AND \"SubFolder\" = :sub;"));
        DocumentsQuery.bindValue(":basic",line.at(0));
        DocumentsQuery.bindValue(":sub",line.at(1));
        DocumentsQuery.exec();
        while(DocumentsQuery.next()){
            Document_Types.append(DocumentsQuery.value(0).toString());
            Documents.append(DocumentsQuery.value(1).toString());
            DocumentPath.append(DocumentsQuery.value(2).toString());
        }

        for (int row=0;row<Document_Types.count();row++ ) {
        ui->DocumentTable->insertRow(row);
        ui->DocumentTable->setItem(row,0 , new QTableWidgetItem(Document_Types.at(row)));
        ui->DocumentTable->setItem(row,2 , new QTableWidgetItem(DocumentPath.at(row)));
        ui->DocumentTable->setItem(row,1 , new QTableWidgetItem(Documents.at(row)));
        ui->DocumentTable->setRowHidden(row,true);
        }
    ui->OpenPdfButton->setEnabled(false);
    ui->OpenTexButton->setEnabled(false);
    ui->OpenFolderButton->setEnabled(false);
}

void NotesDocuments::on_OpenTexButton_clicked()
{
    QString path = ui->DocumentTable->item(ui->DocumentTable->currentRow(), 2)->text();
    QDesktopServices::openUrl(QUrl("file:///"+path));
    accept();
}

void NotesDocuments::on_CheckEpiloghOlwn_clicked(bool checked)
{
    if(checked){
        for (int i=0;i<checkList.count();i++) {
            QCheckBox *btn = static_cast<QCheckBox *>(sender());
            checkList.at(i)->setChecked(true);
        }
}
    else {
        for (int i=0;i<checkList.count();i++) {
            QCheckBox *btnn = static_cast<QCheckBox *>(sender());
            checkList.at(i)->setChecked(false);}
    }
}

void NotesDocuments::showItemsTable(bool show)
{
    QString file;
    if(show){
    QRadioButton *btn = static_cast<QRadioButton *>(sender());
    file = btn->text();
    for (int i=0;i<ui->DocumentTable->rowCount() ;i++ ) {
        bool hidden = ui->DocumentTable->isRowHidden(i);
        QTableWidgetItem *item = ui->DocumentTable->item( i, 0 );
        if( item->text()==file && hidden ){
            int row = ui->DocumentTable->row(item);
        ui->DocumentTable->setRowHidden( row, false );}
    }
}
    else {QRadioButton *btn = static_cast<QRadioButton *>(sender());
        file = btn->text();
        for (int i=0;i<ui->DocumentTable->rowCount() ;++i ) {
         bool hidden = ui->DocumentTable->isRowHidden(i);
         QTableWidgetItem *item = ui->DocumentTable->item( i, 0 );
         if( item->text()==file && !hidden ){
             int row = ui->DocumentTable->row(item);
         ui->DocumentTable->setRowHidden( row, true );}}
        }
}

void NotesDocuments::on_OpenPdfButton_clicked()
{
    QString path = ui->DocumentTable->item(ui->DocumentTable->currentRow(), 2)->text().replace(".tex",".pdf");
    QDesktopServices::openUrl(QUrl("file:///"+path));
}

void NotesDocuments::on_AddBasicButton_clicked()
{
    int rows = ui->BasicFoldersTable->rowCount();
    QString folder = QFileDialog::getExistingDirectory(this, tr("Select folder"),NotesPath);
    QString BasicFolder = folder.remove(NotesPath);
    if (folder.isEmpty()) return;
    QStringList folders;
    for (int i=0;i<rows;i++) {
        folders.append(ui->BasicFoldersTable->item(i,0)->text());
    }
    if(folders.contains(folder.remove(NotesPath))){
        QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(BasicFolder));
    return;}
    ui->BasicFoldersTable->insertRow(rows);
    ui->BasicFoldersTable->setItem(rows,0, new QTableWidgetItem(folder.remove(NotesPath)));
    QSqlQuery AddQuery(currentbase);
    AddQuery.prepare(QString("INSERT INTO \"Basic_Folders\" (\"Name\") VALUES(:basic);").arg(BasicFolder));
    AddQuery.bindValue(":basic",BasicFolder);
    AddQuery.exec();
}

void NotesDocuments::on_BasicFoldersTable_itemSelectionChanged()
{
    ui->RemBasicButton->setEnabled(true);
    ui->EditBasicButton->setEnabled(true);
    ui->SubFolderTable->setEnabled(true);
    ui->SubFolderTable->setRowCount(0);
    ui->SubsubFolderTable->setRowCount(0);
    ui->CreateSubButton->setEnabled(true);
    ui->AddSubButton->setEnabled(true);
    ui->SubFolderTable->setColumnCount(1);
    QStringList HeadersSub;
    ui->SubFolderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SubFolderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SubFolderTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->SubFolderTable->setAlternatingRowColors(true);
    ui->SubFolderTable->setStyleSheet("alternate-background-color: #e8e8e8");
    HeadersSub << tr("Subfolder name");
    ui->SubFolderTable->setHorizontalHeaderLabels(HeadersSub);
    if(ui->BasicFoldersTable->rowCount()>0 && ui->BasicFoldersTable->currentRow()!=-1){
        int row = ui->BasicFoldersTable->currentRow();
        QString baseFolder= ui->BasicFoldersTable->item(row,0)->text();
        QStringList SubFolders;
        QSqlQuery fields(currentbase);
        fields.prepare(QString("SELECT \"Sub_Id\" FROM \"SubFolders_per_Basic\" WHERE \"Basic_Id\" = :basic;"));
        fields.bindValue(":basic",baseFolder);
        fields.exec();
        while(fields.next()){
            SubFolders.append(fields.value(0).toString());
        }
        for (int item=0;item<SubFolders.count();item++ ) {
            ui->SubFolderTable->insertRow(item);
            ui->SubFolderTable->setItem(item,0, new QTableWidgetItem(SubFolders.at(item)));
        }
    }
    else if(ui->BasicFoldersTable->currentRow()==-1){
        ui->SubFolderTable->setEnabled(false);
        ui->SubsubFolderTable->setEnabled(false);
        ui->SubsubCheck->setChecked(false);
        ui->SubsubCheck->setEnabled(false);
        ui->RemBasicButton->setEnabled(false);
        ui->EditBasicButton->setEnabled(false);
        ui->RemSubButton->setEnabled(false);
        ui->EditSubButton->setEnabled(false);
        ui->RemSubsubButton->setEnabled(false);
        ui->EditSubsubButton->setEnabled(false);
    }
    if(ui->SubFolderTable->currentRow()==-1){
        ui->RemSubButton->setEnabled(false);
        ui->EditSubButton->setEnabled(false);
    }
}

void NotesDocuments::on_CreateBasicButton_clicked()
{
    newFolder = new addfolder(this);
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(Basic(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::Basic(QString newfolder)
{
    QFile BasF(BasicFolderFile);
    QStringList folders;
    for (int i=0;i<ui->BasicFoldersTable->rowCount();i++) {
        folders.append(ui->BasicFoldersTable->item(i,0)->text());
    }
    if(folders.contains(newfolder)){
        QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(newfolder));
    return;}

    QSqlQuery CreateQuery(currentbase);
    CreateQuery.prepare(QString("INSERT INTO \"Basic_Folders\" (\"Name\") VALUES(:folder);"));
    CreateQuery.bindValue(":folder",newfolder);
    CreateQuery.exec();
    int i = ui->BasicFoldersTable->rowCount();
    ui->BasicFoldersTable->insertRow(i);
    ui->BasicFoldersTable->setItem(i,0 , new QTableWidgetItem(newfolder));
    QDir dir(NotesPath+newfolder);
    if (!dir.exists())
        dir.mkpath(".");
}

void NotesDocuments::on_RemBasicButton_clicked()
{
    int row = ui->BasicFoldersTable->currentRow();
    QCheckBox *cb = new QCheckBox("Μετάβαση στο φάκελο");
        QMessageBox msgbox;
        msgbox.setText(tr("The folder will be deleted from the database!\nDelete the folder manually in case it contains files.\nDo you wish to proceed?"));
        msgbox.setIcon(QMessageBox::Icon::Question);
        msgbox.addButton(QMessageBox::Ok);
        msgbox.addButton(QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Cancel);
        msgbox.setCheckBox(cb);

    if (msgbox.exec() == QMessageBox::Ok) {
    ui->BasicFoldersTable->removeRow(row);
    QSqlQuery RemQuery(currentbase);
    RemQuery.exec("PRAGMA foreign_keys = ON");
    RemQuery.prepare(QString("DELETE FROM \"Basic_Folders\" WHERE \"Name\" = :basic;"));
    RemQuery.bindValue(":basic",ui->BasicFoldersTable->currentItem()->text());
    RemQuery.exec();
     if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+NotesPath));}
    }
}

void NotesDocuments::on_AddSubButton_clicked()
{
    int rows = ui->SubFolderTable->rowCount();
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString folder = QFileDialog::getExistingDirectory(this, tr("Choose folder"),NotesPath+BasicFolder+QDir::separator());
    if (folder.isEmpty()) return;
    QString SubFolder = folder.remove(NotesPath+BasicFolder+QDir::separator());
    ui->SubFolderTable->insertRow(rows);
    ui->SubFolderTable->setItem(rows,0, new QTableWidgetItem(SubFolder));

    QSqlQuery AddSubQuery(currentbase);
    QSqlQuery AddSub_per_BasicQuery(currentbase);
    AddSubQuery.prepare(QString("INSERT OR IGNORE INTO \"SubFolders\" (Name) VALUES(:subfolder);"));
    AddSubQuery.bindValue(":subfolder",SubFolder);
    AddSubQuery.exec();
    AddSub_per_BasicQuery.prepare(QString("INSERT OR IGNORE INTO \"SubFolders_per_Basic\" (\"Sub_Id\",\"Basic_Id\") VALUES(:basic,:sub);"));
    AddSubQuery.bindValue(":basic",BasicFolder);
    AddSubQuery.bindValue(":sub",SubFolder);
    AddSubQuery.exec();
}

void NotesDocuments::on_CreateSubButton_clicked()
{
    newFolder = new addfolder(this);
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(SubFolder(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::SubFolder(QString newfolder)
{
    QString GrammhText;
    QString BasFakelos = ui->BasicFoldersTable->currentItem()->text();
    QStringList folders;
    int rows = ui->SubFolderTable->rowCount();
    for (int i=0;i<rows;i++) {
        folders.append(ui->SubFolderTable->item(i,0)->text());
    }
    if(folders.contains(newfolder)){
        QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(newfolder));
    return;}
    QSqlQuery AddSubQuery(currentbase);
    QSqlQuery AddSub_per_BasicQuery(currentbase);
    AddSubQuery.prepare(QString("INSERT OR IGNORE INTO \"SubFolders\" (\"Name\") VALUES(:sub);"));
    AddSubQuery.bindValue(":sub",newfolder);
    AddSubQuery.exec();
    AddSub_per_BasicQuery.prepare(QString("INSERT OR IGNORE INTO \"SubFolders_per_Basic\" (\"Sub_Id\",\"Basic_Id\") VALUES(:sub,:basic);"));
    AddSub_per_BasicQuery.bindValue(":sub",newfolder);
    AddSub_per_BasicQuery.bindValue(":basic",BasFakelos);
    AddSub_per_BasicQuery.exec();
    ui->SubFolderTable->insertRow(rows);
    ui->SubFolderTable->setItem(rows,0 , new QTableWidgetItem(newfolder));
    QDir dir(NotesPath+BasFakelos+QDir::separator()+newfolder);
    if (!dir.exists())
        dir.mkpath(".");
}

void NotesDocuments::on_OkbuttonBoxFolders_accepted()
{
    if(ui->NameLine->isEnabled()==true){
        QString texname = ui->NameLine->text();
        QString name;
        int row1 = ui->BasicFoldersTable->currentRow();
        int row2 = ui->SubFolderTable->currentRow();
        QString BasicFolder = ui->BasicFoldersTable->item(row1,0)->text();
        QString SubFolder = ui->SubFolderTable->item(row2,0)->text();
        QString SubsubFolfer;
        if(ui->SubsubCheck->isChecked()){
            SubsubFolfer = "\""+ui->SubsubFolderTable->currentItem()->text()+"\"";
        }
        else{SubsubFolfer = "NULL";}
        if(texname.isEmpty()==false && isWhiteSpace(texname)==false){
            name = ui->pathline->text()+"DTX-"+texname+".tex";
            QFileInfo OnomaArxeiou(name);
            QDir path = OnomaArxeiou.absoluteDir();
        if (!path.exists())
            path.mkpath(".");
        QString pathpdf = ui->pathline->text();
        QString FilePath = pathpdf+"DTX-"+texname+".tex";
        QString date = QDateTime::currentDateTime().toString("dd/M/yyyy hh:mm");
        QStringList valuesList;
        valuesList << "DTX-"+texname<<DocumentType<<BasicFolder<<SubFolder<<FilePath<<date;
        qDebug()<<valuesList;
        QString Values = "(\""+valuesList.join("\",\"")+"\","+SubsubFolfer+")";
        qDebug()<<Values;
        QSqlQuery AddDocument(currentbase);
        AddDocument.exec(QString("INSERT OR IGNORE INTO \"Documents\" "
"(\"Id\",\"Document_Type\",\"Basic_Folder\",\"SubFolder\",\"Path\",\"Date\",\"SubsubFolder\") "
"VALUES %1;").arg(Values));
        emit openpdf(FilePath);
        if(ui->InsertFilesCheckBox->isChecked()){
            emit insertfiles();}
        accept();}
        else if (texname.isEmpty()==true || isWhiteSpace(texname) ==true) {
        QMessageBox::warning(this,tr("Error"),tr("Select a file name.\nThe name is "
                                           "empty or contains\nempty space or dot \".\"."),QMessageBox::Ok);}
}
    else if(ui->NameLine->isEnabled()==false){accept();}
}

void NotesDocuments::on_OkbuttonBoxFolders_rejected()
{
    reject();
}

void NotesDocuments::on_RemSubButton_clicked()
{
    QString folder = ui->SubFolderTable->currentItem()->text();
    QString BasicFolder= ui->BasicFoldersTable->currentItem()->text();
    int row = ui->SubFolderTable->currentRow();
    QCheckBox *cb = new QCheckBox(tr("Open folder"));
    QMessageBox msgbox;
    msgbox.setText(tr("The folder will be deleted from the database!\nDelete the folder manually in case it contains files.\nDo you wish to proceed?"));
    msgbox.setIcon(QMessageBox::Icon::Question);
    msgbox.addButton(QMessageBox::Ok);
    msgbox.addButton(QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Cancel);
    msgbox.setCheckBox(cb);

    if(msgbox.exec() == QMessageBox::Ok){
    ui->SubFolderTable->removeRow(row);
    QSqlQuery RemQuery(currentbase);
    QSqlQuery Rem_per_BasicQuery(currentbase);
    RemQuery.exec("PRAGMA foreign_keys = ON");
    RemQuery.prepare(QString("DELETE FROM \"SubFolders\" WHERE \"Name\" = :sub;"));
    RemQuery.bindValue(":sub",folder);
    RemQuery.exec();
    Rem_per_BasicQuery.prepare(QString("DELETE FROM \"SubFolders_per_Basic\" WHERE \"Sub_Id\" = :sub;"));
    Rem_per_BasicQuery.bindValue(":sub",folder);
    Rem_per_BasicQuery.exec();
    if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+NotesPath+QDir::separator()+BasicFolder+QDir::separator()));}
    }
}

void NotesDocuments::on_SubFolderTable_itemSelectionChanged()
{
    ui->RemSubsubButton->setEnabled(false);
    ui->EditSubsubButton->setEnabled(false);
    if(ui->SubFolderTable->rowCount()>0 && ui->SubFolderTable->currentRow()!=-1){
    ui->SubsubCheck->setEnabled(true);
    ui->CreatePdfCheckbox->setEnabled(true);
    ui->InsertFilesCheckBox->setEnabled(true);
    ui->RemSubButton->setEnabled(true);
    ui->EditSubButton->setEnabled(true);
    if (ui->SubsubCheck->isChecked()){
        ui->CreatePdfCheckbox->setEnabled(false);
        ui->InsertFilesCheckBox->setEnabled(false);
        on_SubsubCheck_clicked(true);
    }
    }
    else if(ui->SubFolderTable->currentRow()==-1){
        ui->SubsubFolderTable->setRowCount(0);
        ui->SubsubFolderTable->setEnabled(false);
        ui->SubsubCheck->setChecked(false);
        ui->SubsubCheck->setEnabled(false);
        ui->RemSubButton->setEnabled(false);
        ui->EditSubButton->setEnabled(false);
    }
}

void NotesDocuments::on_AddSubsubButton_clicked()
{
    int rows = ui->SubsubFolderTable->rowCount();
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    QString folder = QFileDialog::getExistingDirectory(this, tr("Select folder"),NotesPath+BasicFolder+QDir::separator()+SubFolder);
    if (folder.isEmpty()) return;
    QString Subsubfolder = folder.remove(NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator());
    ui->SubsubFolderTable->insertRow(rows);
    ui->SubsubFolderTable->setItem(rows,0, new QTableWidgetItem(folder.remove(NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator())));
    QSqlQuery AddSubQuery(currentbase);
    QSqlQuery AddSub_per_BasicQuery(currentbase);
    AddSubQuery.prepare(QString("INSERT OR IGNORE INTO \"SubsubFolders\" (\"Name\") VALUES(:subsub);"));
    AddSubQuery.bindValue(":subsub",Subsubfolder);
    AddSubQuery.exec();
    AddSub_per_BasicQuery.prepare(QString("INSERT OR IGNORE INTO \"SubsubFolders_per_Sub_perBasic\" (\"Subsub_Id\",\"Sub_Id\",\"Basic_Id\") VALUES(:subsub,:sub,:basic);"));
    AddSubQuery.bindValue(":subsub",Subsubfolder);
    AddSubQuery.bindValue(":sub",SubFolder);
    AddSubQuery.bindValue(":basic",BasicFolder);
    AddSubQuery.exec();
}

void NotesDocuments::on_SubsubCheck_clicked(bool checked)
{
    if(checked==true){
    ui->RemBasicButton->setEnabled(true);
    ui->EditBasicButton->setEnabled(true);
    ui->SubsubFolderTable->setEnabled(true);
    ui->SubsubFolderTable->setRowCount(0);
    ui->CreateSubsubButton->setEnabled(true);
    ui->AddSubsubButton->setEnabled(true);
    ui->CreatePdfCheckbox->setEnabled(false);
    ui->SubsubFolderTable->setColumnCount(1);
    QStringList HeadersSub;
    ui->SubsubFolderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SubsubFolderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SubsubFolderTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->SubsubFolderTable->setAlternatingRowColors(true);
    ui->SubsubFolderTable->setStyleSheet("alternate-background-color: #e8e8e8");
    HeadersSub << tr("Subfolder name");
    ui->SubsubFolderTable->setHorizontalHeaderLabels(HeadersSub);
    int row1 = ui->BasicFoldersTable->currentRow();
    int row2 = ui->SubFolderTable->currentRow();
    QString basicFolder= ui->BasicFoldersTable->item(row1,0)->text();
    QString subFolder = ui->SubFolderTable->item(row2,0)->text();

    QStringList SubSubFolders;
    QSqlQuery fields(currentbase);
    fields.prepare(QString("SELECT \"Subsub_Id\" FROM \"SubsubFolders_per_Sub_perBasic\" WHERE \"Sub_Id\" = :sub"
                        " AND \"Basic_Id\" = :basic"));
    fields.bindValue(":sub",subFolder);
    fields.bindValue(":basic",basicFolder);
    fields.exec();
    while(fields.next()){
        SubSubFolders.append(fields.value(0).toString());
    }
    for (int item=0;item<SubSubFolders.count();item++ ) {
        ui->SubsubFolderTable->insertRow(item);
        ui->SubsubFolderTable->setItem(item,0, new QTableWidgetItem(SubSubFolders.at(item)));
    }
}
    else if(checked==false){
        ui->SubsubFolderTable->setEnabled(false);
        ui->SubsubFolderTable->setRowCount(0);
        ui->CreateSubsubButton->setEnabled(false);
        ui->AddSubsubButton->setEnabled(false);
        ui->RemSubsubButton->setEnabled(false);
        ui->EditSubsubButton->setEnabled(false);
        ui->InsertFilesCheckBox->setEnabled(true);
    }
}

void NotesDocuments::on_CreateSubsubButton_clicked()
{
    newFolder = new addfolder(this);
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(SubsubFolder(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::SubsubFolder(QString newfolder)
{
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    QStringList folders;
    int rows = ui->SubsubFolderTable->rowCount();
    for (int i=0;i<rows;i++) {
        folders.append(ui->SubsubFolderTable->item(i,0)->text());
    }
    if(folders.contains(newfolder)){
        QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(newfolder));
    return;}
    QSqlQuery AddSubQuery(currentbase);
    QSqlQuery AddSub_per_BasicQuery(currentbase);
    AddSubQuery.prepare(QString("INSERT OR IGNORE INTO \"SubsubFolders\" (\"Name\") VALUES(:subsub);"));
    AddSubQuery.bindValue(":subsub",newfolder);
    AddSubQuery.exec();
    AddSub_per_BasicQuery.prepare(QString("INSERT OR IGNORE INTO \"SubsubFolders_per_Sub_perBasic\" (\"Subsub_Id\",\"Sub_Id\",\"Basic_Id\") VALUES(:subsub,:sub,:basic);"));
    AddSub_per_BasicQuery.bindValue(":subsub",newfolder);
    AddSub_per_BasicQuery.bindValue(":sub",SubFolder);
    AddSub_per_BasicQuery.bindValue(":basic",BasicFolder);
    AddSub_per_BasicQuery.exec();
    ui->SubsubFolderTable->insertRow(rows);
    ui->SubsubFolderTable->setItem(rows,0 , new QTableWidgetItem(newfolder));

    QDir dir(NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator()+newfolder);
    if (!dir.exists())
        dir.mkpath(".");
}

void NotesDocuments::on_SubsubFolderTable_itemSelectionChanged()
{
    if(ui->SubsubFolderTable->currentRow()!=-1){
        ui->RemSubsubButton->setEnabled(true);
        ui->EditSubsubButton->setEnabled(true);
        ui->CreatePdfCheckbox->setEnabled(true);
        ui->InsertFilesCheckBox->setEnabled(true);}
    else{
        ui->RemSubsubButton->setEnabled(false);
        ui->EditSubsubButton->setEnabled(false);
        ui->CreatePdfCheckbox->setEnabled(false);
        ui->InsertFilesCheckBox->setEnabled(false);
    }
}

void NotesDocuments::on_RemSubsubButton_clicked()
{
    QString SubSubfolder = ui->SubsubFolderTable->currentItem()->text();
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    int row = ui->SubsubFolderTable->currentRow();
    QCheckBox *cb = new QCheckBox(tr("Open folder"));
    QMessageBox msgbox;
    msgbox.setWindowTitle(tr("Delete folder"));
    msgbox.setText(tr("The folder will be deleted from the database!\nDelete the folder manually in case it contains files.\nDo you wish to proceed?"));
    msgbox.setIcon(QMessageBox::Icon::Question);
    msgbox.addButton(QMessageBox::Ok);
    msgbox.addButton(QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Cancel);
    msgbox.setCheckBox(cb);

    if(msgbox.exec() == QMessageBox::Ok){
    ui->SubsubFolderTable->removeRow(row);
    QSqlQuery RemQuery(currentbase);
    QSqlQuery Rem_per_BasicQuery(currentbase);
    RemQuery.exec("PRAGMA foreign_keys = ON");
    RemQuery.prepare(QString("DELETE FROM \"SubsubFolders\" WHERE \"Name\" = :subsub;"));
    RemQuery.bindValue(":subsub",SubSubfolder);
    RemQuery.exec();
    Rem_per_BasicQuery.prepare(QString("DELETE FROM \"SubsubFolders_per_Sub_perBasic\" WHERE \"Subsub_Id\" = :subsub;"));
    Rem_per_BasicQuery.bindValue(":subsub",SubSubfolder);
    Rem_per_BasicQuery.exec();
    if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+NotesPath+QDir::separator()+BasicFolder+QDir::separator()+SubFolder+QDir::separator()));}
    }
}

void NotesDocuments::Folder(bool checked)
{
    if(checked){
    QRadioButton *btn = static_cast<QRadioButton *>(sender());
    DocumentType = btn->text();}
}

bool NotesDocuments::isWhiteSpace(const QString & str)
{
  return QRegExp("\t | \n | \v | \f | \r | |.").exactMatch(str);
}

void NotesDocuments::enable3check()
{
    ui->NameLine->setEnabled(true);
}

void NotesDocuments::EditBasicForders_DataTex(QString Line)
{
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    int row = ui->BasicFoldersTable->currentRow();
        QStringList folders;
        for (int i=0;i<ui->BasicFoldersTable->rowCount();i++) {
            folders.append(ui->BasicFoldersTable->item(i,0)->text());
        }
        if(folders.contains(Line)){
            QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(Line));
        return;}
        ui->BasicFoldersTable->item(row,0)->setText(QString(Line));
        QFile::rename(NotesPath+BasicFolder+QDir::separator(),NotesPath+Line+QDir::separator());
        QSqlQuery EditQuery(currentbase);
        EditQuery.exec("PRAGMA foreign_keys = ON");
        EditQuery.prepare(QString("UPDATE \"Basic_Folders\" SET \"Name\" = :newname WHERE \"Name\" = :name;"));
        EditQuery.bindValue(":newname",Line);
        EditQuery.bindValue(":name",BasicFolder);
        EditQuery.exec();
        EditQuery.prepare(QString("UPDATE \"Documents\" SET \"Path\" = replace(\"Path\",:basic,:line) WHERE \"Basic_Folder\" = :line;"));
        EditQuery.bindValue(":line",Line);
        EditQuery.bindValue(":basic",BasicFolder);
        EditQuery.exec();
        emit pathline(Line);
}

void NotesDocuments::on_EditBasicButton_clicked()
{
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    newFolder = new addfolder(this);
    newFolder->EditFolder(BasicFolder);
    connect(this,SIGNAL(pathline(QString)),newFolder,SLOT(EditFolder(QString)));
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(EditBasicFolders_DataTex(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::EditSubForders_DataTex(QString Line)
{
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    int row = ui->SubFolderTable->currentRow();
        QStringList folders;
        for (int i=0;i<ui->SubFolderTable->rowCount();i++) {
            folders.append(ui->SubFolderTable->item(i,0)->text());
        }
        if(folders.contains(Line)){
            QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(Line));
        return;}
        ui->SubFolderTable->item(row,0)->setText(QString(Line));
        QSqlQuery EditQuery(currentbase);
        EditQuery.exec("PRAGMA foreign_keys = ON");
        EditQuery.prepare(QString("UPDATE \"SubFolders\" SET \"Name\" = :newname WHERE \"Name\" = :name;"));
        EditQuery.bindValue(":newname",Line);
        EditQuery.bindValue(":name",SubFolder);
        EditQuery.exec();
        EditQuery.prepare(QString("UPDATE \"Documents\" SET \"Path\" = replace(\"Path\",:sub,:line) "
"WHERE \"Basic_Folder\" = :basic AND \"SubFolder\" = :line;"));
        EditQuery.bindValue(":sub",SubFolder);
        EditQuery.bindValue(":line",Line);
        EditQuery.bindValue(":basic",BasicFolder);
        EditQuery.exec();
        QFile::rename(NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator(),NotesPath+BasicFolder+QDir::separator()+Line+QDir::separator());
        emit pathline(Line);
}

void NotesDocuments::on_EditSubButton_clicked()
{
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    newFolder = new addfolder(this);
    newFolder->EditFolder(SubFolder);
    connect(this,SIGNAL(pathline(QString)),newFolder,SLOT(EditFolder(QString)));
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(EditSubForders_DataTex(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::EditSubsubForders_DataTex(QString Line)
{
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString SubFolder = ui->SubFolderTable->currentItem()->text();
    QString SubSubfolder = ui->SubsubFolderTable->currentItem()->text();
    int row = ui->SubsubFolderTable->currentRow();
    QStringList folders;
    for (int i=0;i<ui->SubsubFolderTable->rowCount();i++) {
        folders.append(ui->SubsubFolderTable->item(i,0)->text());
    }
    if(folders.contains(Line)){
        QMessageBox::warning(this,tr("Attention"),tr("The folder %1 already exists").arg(Line));
    return;}
        ui->SubsubFolderTable->item(row,0)->setText(QString(Line));
        QSqlQuery EditQuery(currentbase);
        EditQuery.exec("PRAGMA foreign_keys = ON");
        EditQuery.prepare(QString("UPDATE \"SubsubFolders\" SET \"Name\" = :line WHERE \"Name\" = :subsub;"));
        EditQuery.bindValue(":line",Line);
        EditQuery.bindValue(":subsub",SubSubfolder);
        EditQuery.exec();
        EditQuery.prepare(QString("UPDATE \"Documents\" SET \"Path\" = replace(\"Path\",:subsub,:line)"
"WHERE \"Basic_Folder\" = :basic AND \"SubFolder\" = :sub AND \"SubsubFolder\" = :line;"));
        EditQuery.bindValue(":subsub",SubSubfolder);
        EditQuery.bindValue(":line",Line);
        EditQuery.bindValue(":sub",SubFolder);
        EditQuery.bindValue(":basic",BasicFolder);
        EditQuery.exec();
        QFile::rename(NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator()+SubSubfolder+QDir::separator(),NotesPath+BasicFolder+QDir::separator()+SubFolder+QDir::separator()+Line+QDir::separator());
}

void NotesDocuments::on_EditSubsubButton_clicked()
{
    QString SubSubfolder = ui->SubsubFolderTable->currentItem()->text();
    newFolder = new addfolder(this);
    newFolder->EditFolder(SubSubfolder);
    connect(this,SIGNAL(pathline(QString)),newFolder,SLOT(EditFolder(QString)));
    connect(newFolder,SIGNAL(grammhfolder(QString)),this,SLOT(EditSubsubForders_DataTex(QString)));
    newFolder->show();
    newFolder->activateWindow();
}

void NotesDocuments::on_OpenFolderButton_clicked()
{
    int row = ui->DocumentTable->currentRow();
    QString path = ui->DocumentTable->item(row,2)->text();
    QFileInfo Path(path);
    QString Folder = Path.absolutePath();
    QDesktopServices::openUrl(QUrl("file:///"+Folder));
}

QString NotesDocuments::SavePath(bool checked)
{
    QString path;
    QString BasicFolder = ui->BasicFoldersTable->currentItem()->text();
    QString Subfolder = ui->SubFolderTable->currentItem()->text();
    QString SubSubfolder;
    if(ui->SubsubCheck->isChecked()==true && ui->SubsubFolderTable->rowCount()!=0){
        SubSubfolder = ui->SubsubFolderTable->currentItem()->text();
        path = NotesPath+BasicFolder+QDir::separator()+Subfolder+QDir::separator()+SubSubfolder+QDir::separator()+
                DocumentType+QDir::separator();}
    else if(ui->SubsubCheck->isChecked()==false){
        path = NotesPath+BasicFolder+QDir::separator()+Subfolder+QDir::separator()+DocumentType+QDir::separator();}
    ui->pathline->setText(path);
    return path;
}

void NotesDocuments::on_CreatePdfCheckbox_toggled(bool checked)
{
    if(checked==true){for (int i=0;i<radioList.count();i++ ) {
            radioList.at(i)->setEnabled(true);}
            ui->pathline->setEnabled(true);
            ui->NameLine->setEnabled(true);
            ui->InsertFilesCheckBox->setEnabled(true);
        }
    else{for (int i=0;i<radioList.count();i++ ) {
            radioList.at(i)->setEnabled(false);}
            ui->pathline->setEnabled(false);
            ui->NameLine->setEnabled(false);
            ui->InsertFilesCheckBox->setEnabled(false);}
}

void NotesDocuments::on_DocumentTable_itemSelectionChanged()
{
    int row = ui->DocumentTable->currentRow();
    ui->OpenPdfButton->setEnabled(true);
    ui->OpenTexButton->setEnabled(true);
    ui->OpenFolderButton->setEnabled(true);
    QString TexFilePath = ui->DocumentTable->item(row,2)->text();
    QFile TexFile(TexFilePath);
    QStringList filepaths;
    QString path_rem = "%# Database File : ";
    TexFile.open (QIODevice::ReadOnly | QIODevice::Text);
    QTextStream Line(&TexFile);
    while (!Line.atEnd()){
    QString GrammhText=Line.readLine();
    if(GrammhText.contains(path_rem))filepaths.append(GrammhText.remove(path_rem).remove("----"));}
    TexFile.close();
    qDebug()<<filepaths;
    QString files = "(\""+filepaths.join("\",\"")+"\")";

    QSqlQueryModel * Files = new QSqlQueryModel(this);
    QSqlQuery FilesQuery(currentbase_Exercises);
    FilesQuery.exec(QString("SELECT DISTINCT \"df\".\"Id\",\"ft\".\"FileType\","
                            "IIF(\"df\".\"FileType\" IN ('CombEx','SolCE','CombSub','SolCS','HintCE','HintCS'),"
                            "replace(group_concat(\"s\".\"Name\"),',','-'),\"s\".\"Name\") AS 'Section',"
                            "\"se\".\"Exercise_Name\","
                            "\"Path\",\"Solved\",\"df\".\"FileType\" "
                            "FROM \"Database_Files\" \"df\" "
                            "JOIN \"FileTypes\" \"ft\" ON \"ft\".\"Id\" = \"df\".\"FileType\" "
                            "JOIN \"Sections\" \"s\" ON \"s\".\"Id\" = \"df\".\"Section\""
                            "LEFT JOIN \"Sections_Exercises\" \"se\" ON \"se\".\"Exercise_Id\" = \"df\".\"ExerciseType\" "
                            "WHERE \"df\".\"Id\" IN %1"
                            "GROUP BY \"df\".\"Id\""
                            "ORDER BY \"df\".rowid;").arg(files));
    Files->setQuery(FilesQuery);
    ui->TexFileTable->setModel(Files);
    ui->TexFileTable->show();
    Exer_List.clear();
    Solutions_List.clear();
    Solved_List.clear();
    Unsolved_List.clear();
    Hint_List.clear();
    UnHinted_List.clear();
    QStringList Ids;
    QStringList solIds;
    QStringList hintIds;
    QStringList folders;
    QStringList solfolders;
    Ids<<"SectEx"<<"SectSub"<<"CombEx"<<"CombSub";
    solIds<<"SolSE"<<"SolSS"<<"SolCE"<<"SolCS";
    hintIds<<"HintSE"<<"HintSS"<<"HintCE"<<"HintCS";
    for (int i =0;i<filepaths.count();i++){
        QString FileType = ui->TexFileTable->model()->data(ui->TexFileTable->model()->index(i,6)).toString();
        if(Ids.contains(FileType)){
            QString exercise = ui->TexFileTable->model()->data(ui->TexFileTable->model()->index(i,4)).toString();
            QString solved = exercise;
//            QString Solution_Exists = ui->TexFileTable->model()->data(ui->TexFileTable->model()->index(i,5)).toString();
            QString Hint = exercise;
            for (int i=0;i<Ids.count();i++ ) {
                QString folderName = SqlFunctions::Get_StringList_From_Query(
                            SqlFunctions::FolderName.arg(Ids.at(i)),currentbase_Exercises).at(0);
                folders.append(folderName);
                QString solfolderName = SqlFunctions::Get_StringList_From_Query(
                            SqlFunctions::FolderName.arg(solIds.at(i)),currentbase_Exercises).at(0);
                solfolders.append(solfolderName);
                solved.replace("-"+Ids.at(i),"-"+solIds.at(i));
                solved.replace(folders.at(i),solfolders.at(i));
                Hint.replace("-"+Ids.at(i),"-"+hintIds.at(i));
                Hint.replace(folders.at(i),solfolders.at(i));
            }
            Exer_List.append(exercise);
            Solutions_List.append(solved);
            Hint_List.append(Hint);
        }
    }
    for (int i=0;i<Exer_List.count();i++) {
        QFile pathfile;
        if(!pathfile.exists(Solutions_List.at(i))){
            Unsolved_List.append(Exer_List.at(i));}
        if(pathfile.exists(Solutions_List.at(i))){
            Solved_List.append(Solutions_List.at(i));}
        if(!pathfile.exists(Hint_List.at(i))){
            UnHinted_List.append(Exer_List.at(i));}
        if(pathfile.exists(Hint_List.at(i))){
            Hinted_List.append(Hint_List.at(i));}
    }
    if(Exer_List.size()>0){ui->SolutionTexButton->setEnabled(true);}
    else if(Exer_List.size()==0){ui->SolutionTexButton->setEnabled(false);}

    QString solutionsname = QFileInfo(TexFilePath).baseName()+"_Solutions";
    QString SolutionsPdfFile = QFileInfo(TexFilePath).absolutePath()+QDir::separator()+solutionsname+".pdf";
    QString PdfFile = QFileInfo(TexFilePath).absolutePath()+QDir::separator()+QFileInfo(TexFilePath).baseName()+".pdf";
    QFile file;
    if(!file.exists(PdfFile)){
        ui->OpenPdfButton->setEnabled(false);
    }
    QFile solfile;
    if(!solfile.exists(SolutionsPdfFile)){
        ui->SolutionPdfButton->setEnabled(false);
    }
    else{ui->SolutionPdfButton->setEnabled(true);}
    if(TexFilePath.contains("_Solutions")){
        ui->SolutionPdfButton->setEnabled(false);
        ui->SolutionTexButton->setEnabled(false);
    }
}

QString NotesDocuments::getPreamble(QString fileName)
{
    QString Content;
    QFile File(fileName);
    File.open (QIODevice::ReadOnly | QIODevice::Text);
    QTextStream Line(&File);
    while (!Line.atEnd()){
        QString GrammhText=Line.readLine();
        Content.append(GrammhText+"\n");
        if(GrammhText.contains("\\begin{document}")){break;}
        }

    File.close();
    return Content;
}

void NotesDocuments::on_SolutionTexButton_clicked()
{
    int row = ui->DocumentTable->currentRow();
    QString TexFilePath = ui->DocumentTable->item(row,2)->text();
    QString Content = getPreamble(TexFilePath);
    QString pdfType;
    if(ui->SolutionRadioButton->isChecked()){pdfType = "_Solutions";}
    else if(ui->HintRadioButton->isChecked()){pdfType = "_Hints";}
    QString solutionsname = QFileInfo(TexFilePath).baseName()+pdfType;
    QString SolutionsTexFile = QFileInfo(TexFilePath).absolutePath()+QDir::separator()+solutionsname+".tex";
    QStringList solutionList;
    QStringList unsolvedList;
    if(ui->SolutionRadioButton->isChecked()){solutionList = Solved_List;unsolvedList = Unsolved_List;}
    else if(ui->HintRadioButton->isChecked()){solutionList = Hinted_List;unsolvedList = UnHinted_List;}
    foreach(QString solved,solutionList){
        QFile file(solved);
        file.open (QIODevice::ReadOnly | QIODevice::Text);
        QTextStream line(&file);
        while (!line.atEnd()){
            QString GrammhText=line.readLine();
            Content.append(GrammhText+"\n");
        }
        file.close();
    }

    foreach(QString unsolved,unsolvedList){
    Content.append("\nThe exercise "+QFileInfo(unsolved).baseName()+" is not solved\n");
    }
    Content.append(+"\n\\end{document}");

    QFile SolutionFile(SolutionsTexFile);
    SolutionFile.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream text(&SolutionFile);
        text<<Content;
    SolutionFile.close();
    emit OpenSolutionFile(SolutionsTexFile);
    accept();
}

void NotesDocuments::on_SolutionPdfButton_clicked()
{
    QString pdfType;
    if(ui->SolutionRadioButton->isChecked()){pdfType = "_Solutions";}
    else if(ui->HintRadioButton->isChecked()){pdfType = "_Hints";}
    QString path = ui->DocumentTable->item(ui->DocumentTable->currentRow(), 2)->text().replace(".tex",pdfType+".pdf");
    QDesktopServices::openUrl(QUrl("file:///"+path));
}
