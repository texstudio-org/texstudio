#include "newdatabasefile.h"
#include "ui_newdatabasefile.h"
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
#include <QGridLayout>
#include <QDebug>
#include <QModelIndex>
#include <algorithm>
#include <QCloseEvent>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QClipboard>
#include <QRadioButton>
#include "solvedatabaseexercise.h"
#include <QtSql/QSql>
#include <QSqlQueryModel>
#include "sqlfunctions.h"
#include "texstudio.h"
#include "buildmanager.h"


NewDatabaseFile::NewDatabaseFile(QWidget *parent)  //15/5
    : QDialog(parent)
    , ui(new Ui::NewDatabaseFile)
{
    ui->setupUi(this);
    ui->SectionExercisesFieldComboBox->setMaxVisibleItems (4);
    ui->SectionExercisesFieldComboBox->setEditable (false);
    ui->SectionList->setEnabled(false);
    ui->addButton->setEnabled(false);
    ui->removeButton->setEnabled(false);
    ui->CombExerciseRadio->setEnabled(false);
    ui->CombSubjectRadio->setEnabled(false);

    DataBase_Path = QFileInfo(Texstudio::CurrentDataBasePath).absolutePath()+QDir::separator();
    currentbase = Texstudio::CurrentTexFilesDataBase;
    QStringList Field_Names;
    QStringList Field_ids;
    QSqlQuery fields(currentbase);
    fields.exec(SqlFunctions::Fields_Query);
    while(fields.next()){
        Field_Names.append(fields.value(0).toString());
        Field_ids.append(fields.value(1).toString());
    }
    for (int item=0;item<Field_Names.count();item++ ) {
        ui->SectionExercisesFieldComboBox->addItem (Field_Names.at(item),QVariant(Field_ids.at(item)));
        ui->FieldTable->addItem(Field_Names.at(item));
        ui->FieldTable->item(item)->setData(Qt::UserRole,Field_ids.at(item));
        ui->CombFieldList->addItem (Field_Names.at(item));
        ui->CombFieldList->item(item)->setData(Qt::UserRole,Field_ids.at(item));
    }
    ui->FieldTable->setCurrentRow(-1);
    ui->CombFieldList->setCurrentRow(-1);
    ui->SectionExercisesFieldComboBox->setCurrentIndex(-1);
    ui->DefinitionButton->setEnabled(false);
    ui->TheoremButton->setEnabled(false);
    ui->FigureButton->setEnabled(false);
    ui->TableButton->setEnabled(false);
    ui->SectionExerciseButton->setEnabled(false);
    ui->MethodButton->setEnabled(false);
    ui->ExampleButton->setEnabled(false);
    ui->CombExerciseButton->setEnabled(false);
    ui->SectionExercisesSectionComboBox->setEnabled(false);
    ui->CombExercisesSubjectComboBox->setEnabled(false);
    ui->SectionExercisesChapterComboBox->setEnabled(false);
    ui->SectionExercisesExTypeComboBox->setEnabled(false);
    ui->TheoryDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->ExerDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->ComDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->DefinitionButton->setProperty("Name","Definition");
    ui->TheoremButton->setProperty("Name","Theorem");
    ui->FigureButton->setProperty("Name","Figure");
    ui->TableButton->setProperty("Name","Table");
    ui->DefinitionButton->setProperty("Index",1);
    ui->TheoremButton->setProperty("Index",1);
    ui->FigureButton->setProperty("Index",1);
    ui->TableButton->setProperty("Index",1);
    ui->MethodButton->setProperty("Name","Method");
    ui->MethodButton->setProperty("Index",0);
    ui->SectionExerciseButton->setProperty("Index",0);
    ui->ExampleButton->setProperty("Name","Example");
    ui->ExampleButton->setProperty("Index",0);
    ui->CombExerciseButton->setProperty("Index",2);

    connect(this,SIGNAL(listChanged()),this,SLOT(resetselections()));
    QPushButton *resetButton = ui->OkDialogButton->button(QDialogButtonBox::Reset);
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reseteverything()));
    QPushButton *helpButton = ui->OkDialogButton->button(QDialogButtonBox::Help);
    connect(helpButton, SIGNAL(clicked()), this, SLOT(on_helpButton_clicked()));
    for(int i=0;i<ui->buttonGroup_3->buttons().count();i++){
        connect(ui->buttonGroup_3->buttons().at(i), &QPushButton::clicked, this, &NewDatabaseFile::Theory_clicked);
    }
    for(int i=0;i<ui->buttonGroup_4->buttons().count();i++){
        connect(ui->buttonGroup_4->buttons().at(i), &QPushButton::clicked, this, &NewDatabaseFile::Method_Example_clicked);
    }

    QSqlQuery Select_DataBase_Optional_Metadata(Texstudio::DataTeX_Settings);
    Select_DataBase_Optional_Metadata.exec(QString(SqlFunctions::GetCurrentDataBaseOptionalFields)
                                           .arg(QFileInfo(Texstudio::CurrentDataBasePath).baseName()));
    while(Select_DataBase_Optional_Metadata.next()){
        Optional_Metadata_Ids.append(Select_DataBase_Optional_Metadata.value(0).toString());
        Optional_Metadata_Names.append(Select_DataBase_Optional_Metadata.value(1).toString());
    }

    InitialSettings();

    QList<QVBoxLayout *> VList;
    VList<<ui->verticalLayout<<ui->verticalLayout_5<<ui->verticalLayout_2;
    for (int item=0;item<VList.count();item++ ) {
        QList<QLabel *> * Labels = new QList<QLabel *>;
        QList<QLineEdit *> * Lines = new QList<QLineEdit *>;
        QList<QHBoxLayout *> * HLaouts = new QList<QHBoxLayout *>;
        labelList.append(Labels);
        lineList.append(Lines);
        hLayoutList.append(HLaouts);
        for (int i=0;i<Optional_Metadata_Ids.count();i++ ) {
            QHBoxLayout * hbox = new QHBoxLayout(this);
            QLabel * label = new QLabel(Optional_Metadata_Names.at(i),this);
            labelList[item]->append(label);
            hLayoutList[item]->append(hbox);
            QLineEdit * line = new QLineEdit(this);
            lineList[item]->append(line);
            VList.at(item)->addLayout(hLayoutList[item]->at(i),i+5);
            hLayoutList[item]->at(i)->addWidget(labelList[item]->at(i),0);
            hLayoutList[item]->at(i)->addWidget(lineList[item]->at(i),1);
            mapIdsWidgets.insert(Optional_Metadata_Ids.at(i),line);
            line->setAlignment(Qt::AlignRight);
        }
//        QSpacerItem * vspacer = new QSpacerItem(20, 20, QSizePolicy::Minimum,QSizePolicy::Expanding);
        VList.at(item)->addStretch();
    }

    ui->CombExersiceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->CombExersiceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CombExersiceTable->horizontalHeader()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->CombExersiceTable->setColumnHidden(1,true);
    ui->CombExersiceTable->setAlternatingRowColors(true);
    ui->CombExersiceTable->setStyleSheet("alternate-background-color: #e8e8e8");
}

void NewDatabaseFile::InitialSettings()
{
    QSqlQuery InitialValuesQuery(Texstudio::DataTeX_Settings);
    InitialValuesQuery.exec("SELECT * FROM \"Initial_Settings\"");
    QMap<QString,QString> InitialSettings;
    while (InitialValuesQuery.next()) {
        InitialSettings.insert(InitialValuesQuery.value(0).toString(),InitialValuesQuery.value(1).toString());
    }
    if(!InitialSettings.value("NewDatabaseFile_CurrentTab").isNull()){
        ui->tabWidget->setCurrentIndex(InitialSettings.value("NewDatabaseFile_CurrentTab").toInt());
    }
    if(InitialSettings.value("NewDatabaseFile_CurrentTab").toInt()==0)
    {
        if(!InitialSettings.value("NewDatabaseFile_Theory_CurrentField").isNull()
                && InitialSettings.value("NewDatabaseFile_Theory_CurrentField").toInt()>-1){
            ui->FieldTable->setCurrentRow(InitialSettings.value("NewDatabaseFile_Theory_CurrentField").toInt());
            on_FieldTable_itemClicked(ui->FieldTable->
                                         item(InitialSettings.value("NewDatabaseFile_Theory_CurrentField").toInt()));

        if(!InitialSettings.value("NewDatabaseFile_Theory_CurrentChapter").isNull()){
            ui->ComboChapter_Theory->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Theory_CurrentChapter").toInt());
            on_ComboChapter_Theory_currentIndexChanged(0);

        if(!InitialSettings.value("NewDatabaseFile_Theory_CurrentSection").isNull()){
            ui->ComboSection_Theory->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Theory_CurrentSection").toInt());
            on_ComboSection_Theory_currentIndexChanged(0);
        }
        }
        }
    }
    if(InitialSettings.value("NewDatabaseFile_CurrentTab").toInt()==1)
    {
        if(!InitialSettings.value("NewDatabaseFile_Exercises_CurrentField").isNull()
                && InitialSettings.value("NewDatabaseFile_Exercises_CurrentField").toInt()>-1){
            ui->SectionExercisesFieldComboBox->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Exercises_CurrentField").toInt());
            on_SectionExercisesFieldComboBox_currentIndexChanged(0);

        if(!InitialSettings.value("NewDatabaseFile_Exercises_CurrentChapter").isNull()){
            ui->SectionExercisesChapterComboBox->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Exercises_CurrentChapter").toInt());
            on_SectionExercisesChapterComboBox_currentIndexChanged(0);

        if(!InitialSettings.value("NewDatabaseFile_Exercises_CurrentSection").isNull()){
            ui->SectionExercisesSectionComboBox->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Exercises_CurrentSection").toInt());
            on_SectionExercisesSectionComboBox_currentIndexChanged(0);
            if(!InitialSettings.value("NewDatabaseFile_Exercises_CurrentFileType").isNull()){
                int box = InitialSettings.value("NewDatabaseFile_Exercises_CurrentFileType").toInt();
                ui->buttonGroup_2->buttons().at(box)->setChecked(true);
                if(box==0){
                    on_SectionSubjectCheck_clicked(true);
                }
                else{on_UseExerciseTypeCheck_toggled(true);}
                if(!InitialSettings.value("NewDatabaseFile_Exercises_CurrentExerciseType").isNull()){
                    ui->SectionExercisesExTypeComboBox->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Exercises_CurrentExerciseType").toInt());
                    on_SectionExercisesExTypeComboBox_currentIndexChanged(0);
                }
            }
        }
        }
        }
    }

    if(InitialSettings.value("NewDatabaseFile_CurrentTab").toInt()==2)
    {
        if(!InitialSettings.value("NewDatabaseFile_Comb_CurrentField").isNull()
                && InitialSettings.value("NewDatabaseFile_Comb_CurrentField").toInt()>-1){
            ui->CombFieldList->setCurrentRow(InitialSettings.value("NewDatabaseFile_Comb_CurrentField").toInt());
            on_CombFieldList_currentRowChanged(0);

        if(!InitialSettings.value("NewDatabaseFile_Comb_SelectedSections").isNull()){
            QStringList sections = InitialSettings.value("NewDatabaseFile_Comb_SelectedSections").split(",");
            for (int i=0;i<sections.count() ;i++ ) {
                QList<QListWidgetItem *> items = ui->SectionList->findItems(sections.at(i),Qt::MatchExactly);
                on_SectionList_itemDoubleClicked(items.at(0));
            }
            int box = InitialSettings.value("NewDatabaseFile_Comb_FileType").toInt();
            ui->buttonGroup->buttons().at(box)->setChecked(true);
            if(box==1){
                on_CombExerciseRadio_toggled(true);
            }
            else{
                on_CombSubjectRadio_toggled(true);
                if(!InitialSettings.value("NewDatabaseFile_Comb_CurrentSubjectType").isNull()){
                    ui->CombExercisesSubjectComboBox->setCurrentIndex(InitialSettings.value("NewDatabaseFile_Comb_CurrentSubjectType").toInt());
                    on_CombExercisesSubjectComboBox_currentIndexChanged(0);
                }
            }
        }
        }
    }
}

// ---- THEORY TAB ------------------------

void NewDatabaseFile::on_FieldTable_itemClicked(QListWidgetItem *item)
{
    if(ui->FieldTable->count()>0){
    ui->ComboChapter_Theory->setEnabled(true);
    ui->ComboChapter_Theory->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           item->text());
    for (int i=0;i<data[0].count() ;i++ ) {
        ui->ComboChapter_Theory->addItem(data[0].at(i),QVariant(data[1].at(i)));
    }
    ui->ComboChapter_Theory->setCurrentIndex(-1);

    QSqlQueryModel * Theory = new QSqlQueryModel(this);
    QSqlQuery tableQuery(currentbase);
    tableQuery.prepare(QString(SqlFunctions::TheoryFiles).arg(item->data(Qt::UserRole).toString()));
    tableQuery.exec();
    Theory->setQuery(tableQuery);
    ui->FileTable->setModel(Theory);
    ui->FileTable->show();
    ui->FileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->FileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->FileTable->horizontalHeader()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->FileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->FileTable->setColumnHidden(2,true);
    ui->FileTable->setAlternatingRowColors(true);
    ui->FileTable->setStyleSheet("alternate-background-color: #e8e8e8");
    ui->DefinitionButton->setEnabled(true);
    ui->TheoremButton->setEnabled(true);
    ui->FigureButton->setEnabled(true);
    ui->TableButton->setEnabled(true);
    }
}

void NewDatabaseFile::on_ComboChapter_Theory_currentIndexChanged(int index)
{
    if(ui->FieldTable->count()>0){
    ui->ComboSection_Theory->setEnabled(true);
    ui->ComboSection_Theory->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                           ui->ComboChapter_Theory->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboSection_Theory->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboSection_Theory->setCurrentIndex(-1);
    updateTableView(ui->FileTable,SqlFunctions::TheoryFiles_Chapter.
                    arg(ui->FieldTable->currentItem()->data(Qt::UserRole).toString(),
                        ui->ComboChapter_Theory->currentData().toString()));
    }
}

void NewDatabaseFile::on_ComboSection_Theory_currentIndexChanged(int index)
{
    if(ui->FieldTable->count()>0){
    updateTableView(ui->FileTable,SqlFunctions::TheoryFiles_Chapter_Section.
                    arg(ui->FieldTable->currentItem()->data(Qt::UserRole).toString(),
                        ui->ComboChapter_Theory->currentData().toString(),
                        ui->ComboSection_Theory->currentData().toString()));
    }
}

void NewDatabaseFile::Theory_clicked()
{
    SectionList.clear();
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    QString Id = btn->property("Name").toString();
    buttonindex = btn->property("Index").toInt();
    QString folderName = SqlFunctions::Get_StringList_From_Query(
                SqlFunctions::FolderName.arg(Id),currentbase).at(0);
    QString Field = ui->FieldTable->currentItem()->text();
    QString Chapter = ui->ComboChapter_Theory->currentText();
    QString Section = ui->ComboSection_Theory->currentText();
    if(Chapter.isEmpty() || Section.isEmpty()){
        QMessageBox::warning(this,tr("Error"),tr("Select a chapter\nand a section."),QMessageBox::Ok);
        return;
    }
    QString Path = DataBase_Path+Field+QDir::separator()+tr("Ενότητες")+QDir::separator()+Section+
            QDir::separator()+folderName+QDir::separator();
    QDir dir(Path);
    if (!dir.exists())
        dir.mkpath(".");
    QString Field_Id = ui->FieldTable->currentItem()->data(Qt::UserRole).toString();
    QString filePathName = QFileDialog::getSaveFileName(this, tr("Select a file name"),
            Path+QDir::separator()+"DTX-"+Field_Id+"-"+Id+"-"+tr("(Select a name here)")+".tex","tex Files (*.tex)");
    if (filePathName.isEmpty()) return;
    QFileInfo file(filePathName);
    ui->FilePathLine->setText(file.absolutePath()+QDir::separator());
    ui->FileNameLine->setText(file.fileName());
    ui->TheoryFieldMetadataLine->setText(Field);
    ui->TheoryChapterMetadataLine->setText(Chapter);
    ui->TheorySectionMetadataLine->setText(Section);
    ui->TheoryFileTypeMetadataLine->setText(btn->text());
    mapIdsNames.insert("Field",Field_Id);
    mapIdsNames.insert("Chapter",ui->ComboChapter_Theory->currentData().toString());
    SectionList.append(ui->ComboSection_Theory->currentData().toString());
    mapIdsNames.insert("ExerciseType","-");
    mapIdsNames.insert("FileType",Id);
    mapIdsNames.insert("Date",ui->TheoryDateTimeEdit->text());
    mapIdsNames.insert("Id",QFileInfo(ui->FileNameLine->text()).baseName());
    mapIdsNames.insert("Path",ui->FilePathLine->text()+ui->FileNameLine->text());
    mapIdsNames.insert("Solved",tr("-"));
}

//------ END OF THEORY TAB ------------------------

void NewDatabaseFile::updateTableView(QTableView * table,QString QueryText)
{
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query(currentbase);
    query.prepare(QueryText);
    query.exec();
    model->setQuery(query);
    table->setModel(model);
    table->show();
}

// -------- SECTION EXERCISE TAB -----------------------------
void NewDatabaseFile::on_SectionExercisesFieldComboBox_currentIndexChanged(int index)
{
    ui->SectionExercisesChapterComboBox->setEnabled(true);
    ui->SectionExercisesChapterComboBox->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           ui->SectionExercisesFieldComboBox->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->SectionExercisesChapterComboBox->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->SectionExercisesChapterComboBox->setCurrentIndex(-1);
    updateTableView(ui->ExerciseFileList,SqlFunctions::ExerciseFiles.arg(ui->SectionExercisesFieldComboBox->currentData().toString()));
    ui->ExerciseFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ExerciseFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->ExerciseFileList->horizontalHeader()->setStretchLastSection(true);
    ui->ExerciseFileList->setColumnHidden(2,true);
    for (int c = 0; c < ui->ExerciseFileList->horizontalHeader()->count()-1; ++c)
    {
        ui->ExerciseFileList->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->ExerciseFileList->setAlternatingRowColors(true);
    ui->ExerciseFileList->setStyleSheet("alternate-background-color: #e8e8e8");
}

void NewDatabaseFile::on_SectionExercisesChapterComboBox_currentIndexChanged(int index)
{
    ui->SectionExercisesSectionComboBox->setEnabled(true);
    ui->SectionExercisesSectionComboBox->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                           ui->SectionExercisesChapterComboBox->currentText());
        for (int item=0;item<data[0].count() ;item++ ) {
            ui->SectionExercisesSectionComboBox->addItem(data[0].at(item),QVariant(data[1].at(item)));
        }
        ui->SectionExercisesSectionComboBox->setCurrentIndex(-1);
        updateTableView(ui->ExerciseFileList,SqlFunctions::ExerciseFiles_Chapters.
                        arg(ui->SectionExercisesFieldComboBox->currentData().toString()).
                        arg(ui->SectionExercisesChapterComboBox->currentData().toString()));
}

void NewDatabaseFile::on_SectionExercisesSectionComboBox_currentIndexChanged(int index)
{
        ui->SectionExercisesExTypeComboBox->clear();
        ui->SectionExerciseButton->setEnabled(true);
        ui->MethodButton->setEnabled(true);
        ui->ExampleButton->setEnabled(true);
        ui->UseExerciseTypeCheck->setEnabled(true);
        ui->SectionSubjectCheck->setEnabled(true);
        updateTableView(ui->ExerciseFileList,SqlFunctions::ExerciseFiles_Chapters_Sections.
                        arg(ui->SectionExercisesFieldComboBox->currentData().toString()).
                        arg(ui->SectionExercisesChapterComboBox->currentData().toString()).
                        arg(ui->SectionExercisesSectionComboBox->currentData().toString()));
}

void NewDatabaseFile::on_UseExerciseTypeCheck_toggled(bool checked)
{
    if(checked){
        FileType = "SectEx";
        ui->SectionSubjectCheck->setChecked(false);
        ui->SectionExercisesExTypeComboBox->setEnabled(true);
        ui->SectionExercisesExTypeComboBox->clear();
        ui->SectionExerciseLabel->setText(tr("Exercise list"));
        QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                    SqlFunctions::Exercise_Types_Query.arg(ui->SectionExercisesSectionComboBox->currentData().toString()),currentbase);
        for (int item=0;item<data[0].count() ;item++ ) {
            ui->SectionExercisesExTypeComboBox->addItem(data[0].at(item),QVariant(data[1].at(item)));
        }
        ui->SectionExercisesExTypeComboBox->setCurrentIndex(-1);
        ui->SectionExerciseButton->setText("Section\nexercise");
    }
    else {
        ui->SectionExercisesExTypeComboBox->clear();
        ui->SectionExercisesExTypeComboBox->setEnabled(false);
    }
}

void NewDatabaseFile::on_SectionSubjectCheck_clicked(bool checked)
{
    if(checked){
        FileType = "SectSub";
        ui->UseExerciseTypeCheck->setChecked(false);
        ui->SectionExerciseLabel->setText("Subject list");
        ui->SectionExercisesExTypeComboBox->setEnabled(true);
        ui->SectionExerciseButton->setText("Section\nsubject");
        ui->SectionExercisesExTypeComboBox->clear();
        QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                    SqlFunctions::GetSubject_Types,currentbase);
        for (int item=0;item<data[0].count() ;item++ )
            {
                ui->SectionExercisesExTypeComboBox->addItem(data[0].at(item), QVariant(data[1].at(item)));
            }
        ui->SectionExercisesExTypeComboBox->setCurrentIndex(-1);
        }
}

void NewDatabaseFile::on_SectionExercisesExTypeComboBox_currentIndexChanged(int index)
{
    if(index!=-1){
        ui->SectionExerciseButton->setEnabled(true);
        updateTableView(ui->ExerciseFileList,SqlFunctions::ExerciseFiles_Chapters_Sections_ExSubType.
                        arg(ui->SectionExercisesFieldComboBox->currentData().toString()).
                        arg(ui->SectionExercisesChapterComboBox->currentData().toString()).
                        arg(ui->SectionExercisesSectionComboBox->currentData().toString()).
                        arg(FileType).arg(ui->SectionExercisesExTypeComboBox->currentData().toString()));
    }
}

void NewDatabaseFile::Method_Example_clicked()
{
    SectionList.clear();
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    QString Id = btn->property("Name").toString();
    buttonindex = btn->property("Index").toInt();
    QString folderName = SqlFunctions::Get_StringList_From_Query(
                SqlFunctions::FolderName.arg(Id),currentbase).at(0);
    QString Field = ui->SectionExercisesFieldComboBox->currentText();
    QString Chapter = ui->SectionExercisesChapterComboBox->currentText();
    QString Section = ui->SectionExercisesSectionComboBox->currentText();
    if(Chapter.isEmpty() || Section.isEmpty()){
        QMessageBox::warning(this,tr("Error"),tr("Select chapter and section"),QMessageBox::Ok);
        return;
    }
    QString FilePath = DataBase_Path+Field+QDir::separator()+tr("Ενότητες")+QDir::separator()
            +Section+QDir::separator()+folderName+QDir::separator();
    QDir dir(FilePath);
    if (!dir.exists())
        dir.mkpath(".");
    QString FieldId = ui->SectionExercisesFieldComboBox->currentData().toString().left(3);
    QString SectionId = ui->SectionExercisesSectionComboBox->currentData().toString();
    QString filePathName = QFileDialog::getSaveFileName(this, tr("Select a file name"),
            FilePath+QDir::separator()+"DTX-"+FieldId+"-"+SectionId+"-"+Id+"-"+tr("(Select a name here)")+".tex","tex Files (*.tex)");
    QFileInfo file(filePathName);
    if (filePathName.isEmpty()) return;
    ui->FilePathLine->setText(file.absolutePath()+QDir::separator());
    ui->FileNameLine->setText(file.fileName());

    ui->FieldMetadataLine->setText(Field);
    ui->ChapterMetadataLine->setText(Chapter);
    ui->SectionMetadataLine->setText(Section);
    ui->ExTypeMetadataLine->setEnabled(false);
    ui->FileTypeMetadataLine->setText(btn->text());
    mapIdsNames.insert("Field",ui->SectionExercisesFieldComboBox->currentData().toString());
    mapIdsNames.insert("Chapter",ui->SectionExercisesChapterComboBox->currentData().toString());
    SectionList.append(SectionId);
    mapIdsNames.insert("ExerciseType","-");
    mapIdsNames.insert("FileType",Id);
    mapIdsNames.insert("Date",ui->TheoryDateTimeEdit->text());
    mapIdsNames.insert("Id",QFileInfo(ui->FileNameLine->text()).baseName());
    mapIdsNames.insert("Path",ui->FilePathLine->text()+ui->FileNameLine->text());
    mapIdsNames.insert("Solved",tr("-"));
}

void NewDatabaseFile::on_SectionExerciseButton_clicked()
{
    SectionList.clear();
    QString Field = ui->SectionExercisesFieldComboBox->currentText();
    QString Chapter = ui->SectionExercisesChapterComboBox->currentText();
    QString Section = ui->SectionExercisesSectionComboBox->currentText();
    QString ExerciseType = ui->SectionExercisesExTypeComboBox->currentText();
    QString FieldId = ui->SectionExercisesFieldComboBox->currentData().toString().left(3);
    QString ChapterId = ui->SectionExercisesChapterComboBox->currentData().toString();
    QString SectionId = ui->SectionExercisesSectionComboBox->currentData().toString();
    QString ExTypeId = ui->SectionExercisesExTypeComboBox->currentData().toString();
    if(Chapter.isEmpty() || Section.isEmpty() || ExerciseType.isEmpty() || !ui->UseExerciseTypeCheck->isChecked()){
        QMessageBox::warning(this,tr("Error"),tr("Select chapter, section\nand exercise type."),QMessageBox::Ok);
        return;
    }
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    buttonindex = btn->property("Index").toInt();
    QString folderName = SqlFunctions::Get_StringList_From_Query(
                SqlFunctions::FolderName.arg(FileType),currentbase).at(0);
    QString FilePath = DataBase_Path+Field+QDir::separator()+tr("Ενότητες")+QDir::separator()
            +Section+QDir::separator()+folderName+QDir::separator()+ExerciseType+QDir::separator();
    QString exer_sub;
    if(ui->UseExerciseTypeCheck->isChecked()==true){exer_sub=ui->UseExerciseTypeCheck->text();}
    else if(ui->SectionSubjectCheck->isChecked()==true){exer_sub=ui->SectionSubjectCheck->text();}
    QDir dir(FilePath);
    if (!dir.exists())
        dir.mkpath(".");
    QStringList Files;
    QDirIterator list(FilePath,QStringList() << "*.tex", QDir::Files, QDirIterator::Subdirectories);
    while (list.hasNext()){
    Files.append(list.next());}
    int exerIndex = Files.count();
    exerIndex++;
    QString filePathName = QFileDialog::getSaveFileName(this, tr("Select file name"),
            FilePath+"DTX-"+FieldId+"-"+ChapterId+"-"+SectionId+"-"+ExTypeId+"-"+FileType+QString::number(exerIndex)+".tex","tex Files (*.tex)");
    if (filePathName.isEmpty()) return;
    QFileInfo file(filePathName);
    ui->FilePathLine->setText(file.absolutePath()+QDir::separator());
    ui->FileNameLine->setText(file.fileName());
    ui->FieldMetadataLine->setText(Field);
    ui->ChapterMetadataLine->setText(Chapter);
    ui->SectionMetadataLine->setText(Section);
    ui->ExTypeMetadataLine->setText(ExerciseType);
    ui->FileTypeMetadataLine->setText(exer_sub);
    mapIdsNames.insert("Field",ui->SectionExercisesFieldComboBox->currentData().toString());
    mapIdsNames.insert("Chapter",ChapterId);
    SectionList.append(SectionId);
    mapIdsNames.insert("ExerciseType",ExTypeId);
    mapIdsNames.insert("FileType",FileType);
    mapIdsNames.insert("Difficulty",ui->ExerSpinBox->text());
    mapIdsNames.insert("Date",ui->ExerDateTimeEdit->text());
    mapIdsNames.insert("Id",QFileInfo(ui->FileNameLine->text()).baseName());
    mapIdsNames.insert("Path",ui->FilePathLine->text()+ui->FileNameLine->text());
    mapIdsNames.insert("Solved",tr("NO"));
}

void NewDatabaseFile::on_ExerciseFileList_itemClicked(QListWidgetItem *item)
{
    ui->SectionExerciseLabel->setText("Exercise list (Double click)");
}
// ------------ END OF EXERCISES TAB ---------------

void NewDatabaseFile::on_OkDialogButton_accepted() //15/5
{
    if(ui->FilePathLine->text().isEmpty() || ui-> FileNameLine->text().isEmpty()){
    QMessageBox::warning(this,tr("Error"),tr("No file created yet."),QMessageBox::Ok);
    return;}
    for (int i=0;i<Optional_Metadata_Ids.count();i++) {
        if(!lineList[buttonindex]->at(i)->text().isEmpty()){
         mapIdsNames.insert(Optional_Metadata_Ids.at(i),lineList[buttonindex]->at(i)->text());
        }
    }
    QString fileName = mapIdsNames["Path"];

    QSqlQuery Select_DataBase_Bibliography(Texstudio::DataTeX_Settings);
    Select_DataBase_Bibliography.exec(QString(SqlFunctions::GetBibliographyFields)
                                           .arg(QFileInfo(Texstudio::CurrentDataBasePath).baseName()));
    while(Select_DataBase_Bibliography.next()){
        Bibliography_Ids.append(Select_DataBase_Bibliography.value(0).toString());
    }
    Bibliography_Ids.removeAt(0);
    QString query = "INSERT INTO \"Bibliography\" (\"Citation_Key\",\""+Bibliography_Ids.join("\",\"")+"\") VALUES(\"%1\","
                    +QString("'',").repeated(Bibliography_Ids.count()-1)+"'')";
    qDebug()<<query;
    QSqlQuery BibliographyQuery(currentbase);
    BibliographyQuery.exec(QString(query).arg(QFileInfo(fileName).baseName()));
    qDebug()<<BibliographyQuery.lastError().text();
    emit acceptSignal(fileName,mapIdsNames,SectionList);
    accept();
}

void NewDatabaseFile::on_OpenButton_clicked()
{
    QString Path = ui->FilePathLine->text();
    QDesktopServices::openUrl(QUrl("file:///"+Path));
}

// -------- COMB EXERCISE / SUBJECT TAB ------------------
void NewDatabaseFile::on_CombFieldList_currentRowChanged(int currentRow)
{
    ui->SectionList->clear();
    ui->SectionList->setEnabled(true);
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Query,currentbase,
                                           ui->CombFieldList->currentItem()->data(Qt::UserRole).toString());
        for (int item=0;item<data[0].count() ;item++ ) {
            ui->SectionList->addItem(data[0].at(item));
            ui->SectionList->item(item)->setData(Qt::UserRole,data[1].at(item));
        }
    ui->SectionList->setCurrentRow(-1);
    ui->addButton->setEnabled(false);
    ui->removeButton->setEnabled(false);
}

void NewDatabaseFile::on_SectionList_itemClicked(QListWidgetItem *item)
{
    ui->addButton->setEnabled(true);
}

void NewDatabaseFile::on_SectionList_itemDoubleClicked(QListWidgetItem *item)
{
    QString Eidos = item->text();
    int row = ui->SectionList->row(item);
    int SelectedSections = ui->SelectedSections->count();
    int SectionCount = ui->SectionList->count();
    SectionCount--;
    SelectedSections++;
    QListWidgetItem *widget = ui->SectionList->takeItem(row);
    if(SectionCount!=0){
    ui->SectionList->removeItemWidget(widget);
    ui->SelectedSections->addItem(widget);}
    else if(SectionCount==0){
        ui->SectionList->removeItemWidget(widget);
        ui->SelectedSections->addItem(widget);
        ui->addButton->setEnabled(false);
    }
    ui->SelectedSections->sortItems();

    if (SelectedSections!=0){
    ui->CombExerciseRadio->setEnabled(true);
    ui->CombSubjectRadio->setEnabled(true);} //25/6
}

void NewDatabaseFile::on_CombExerciseRadio_toggled(bool checked)
{
    if (checked){
        SectionList.clear();
        ComFileType = "CombEx";
        ui->CombExerciseButton->setEnabled(checked);
        ui->CombExerciseButton->setText(tr("Combinatorial Exercise"));
        ui->CombExercisesSubjectComboBox->setCurrentIndex(-1);
        ui->CombExercisesSubjectComboBox->setEnabled(!checked);
        ui->label_34->setText(tr("Exercise list"));
        QStringList list;
        for (int i=0;i<ui->SelectedSections->count() ;i++ ) {
            list.append(ui->SelectedSections->item(i)->text());
            SectionList.append(ui->SelectedSections->item(i)->data(Qt::UserRole).toString());
        }
        QString SectionsQuery = SectionList.join("\",\"");
        updateTableView(ui->CombExersiceTable,SqlFunctions::GetCombFiles.
                        arg(ComFileType,"\""+SectionsQuery+"\""));
    }
}

void NewDatabaseFile::on_CombSubjectRadio_toggled(bool checked)
{
    ui->label_34->setText(tr("Subject list"));
    if (checked){
        ComFileType = "CombSub";
        ui->CombExerciseButton->setEnabled(checked);
        ui->CombExerciseButton->setText(tr("Συνδ. Θέμα"));
        ui->CombExercisesSubjectComboBox->setEnabled(checked);
        ui->CombExercisesSubjectComboBox->clear();
    }
    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::GetSubject_Types,currentbase);
    for (int item=0;item<data[0].count() ;item++ )
        {
            ui->CombExercisesSubjectComboBox->addItem(data[0].at(item), QVariant(data[1].at(item)));
        }
    ui->CombExercisesSubjectComboBox->setCurrentIndex(-1);
}

void NewDatabaseFile::on_addButton_clicked()
{
    on_SectionList_itemDoubleClicked(ui->SectionList->currentItem());
    emit listChanged();
}

void NewDatabaseFile::on_removeButton_clicked()
{
    int row = ui->SelectedSections->currentRow();
    int SelectedSections = ui->SelectedSections->count();
    SelectedSections--;
    QListWidgetItem * currentItem = ui->SelectedSections->takeItem(row);
    ui->SelectedSections->sortItems();
    if(SelectedSections!=0){
        ui->SelectedSections->removeItemWidget(currentItem);
        ui->SectionList->addItem(currentItem);
        ui->SectionList->sortItems();
    }
    else if(SelectedSections==0){
        ui->SelectedSections->removeItemWidget(currentItem);
        ui->SectionList->addItem(currentItem);
        ui->SectionList->sortItems();
        ui->removeButton->setEnabled(false);
        ui->CombExercisesSubjectComboBox->setCurrentIndex(-1);
        ui->CombExercisesSubjectComboBox->setEnabled(false);
        ui->CombExerciseButton->setEnabled(false);
        ui->CombExerciseRadio->setEnabled(false);
        ui->CombSubjectRadio->setEnabled(false);
    }
    emit listChanged();
}

void NewDatabaseFile::resetselections()
{
    ui->CombExercisesSubjectComboBox->setCurrentIndex(-1);
    ui->CombExercisesSubjectComboBox->setEnabled(false);
    if(ui->CombExerciseRadio->isChecked()==true || ui->CombSubjectRadio->isChecked()==true){
        ui->buttonGroup->setExclusive(false);
        ui->buttonGroup->checkedButton()->setChecked(false);
        ui->buttonGroup->setExclusive(true);
    }
}

void NewDatabaseFile::reseteverything()
{
    int tab = ui->tabWidget->currentIndex();
    if(tab==0){
        ui->FieldTable->setCurrentRow(-1);
    }
    if(tab==1){
//        ui->ExerciseFileList->clear();
        ui->SectionExercisesExTypeComboBox->clear();
        ui->SectionExercisesSectionComboBox->clear();
        ui->MethodButton->setEnabled(false);
        ui->ExampleButton->setEnabled(false);
        ui->FieldMetadataLine->clear();
        ui->ChapterMetadataLine->clear();
        ui->SectionMetadataLine->clear();
        ui->ExTypeMetadataLine->clear();
        ui->FileTypeMetadataLine->clear();
    }
    else if(tab==2){
        ui->CombExercisesSubjectComboBox->setCurrentIndex(-1);
        ui->CombExercisesSubjectComboBox->setEnabled(false);
        if(ui->CombExerciseRadio->isChecked()==true || ui->CombSubjectRadio->isChecked()==true){
            ui->buttonGroup->setExclusive(false);
            ui->buttonGroup->checkedButton()->setChecked(false);
            ui->buttonGroup->setExclusive(true);
        }
        ui->SectionList->clear();
        ui->SelectedSections->clear();
        ui->ComExTypeMetadataLine->clear();
        ui->ComFieldMetadataLine->clear();
        ui->ComFileTypeMetadataLine->clear();
        ui->ComSectionsMetadataLine->clear();
    }
    ui->FilePathLine->clear();
    ui->FileNameLine->clear();
}

void NewDatabaseFile::on_CombExercisesSubjectComboBox_currentIndexChanged(int index)
{
    SectionList.clear();
    QStringList list;
    int length = ui->SelectedSections->count();
    for (int i=0;i<length ;i++ ) {
        list.append(ui->SelectedSections->item(i)->text());
        SectionList.append(ui->SelectedSections->item(i)->data(Qt::UserRole).toString());
    }
    if (index!=-1 && ui->SelectedSections->count()!=0){
        ui->CombExercisesSubjectComboBox->setEnabled(true);
        ui->CombExerciseButton->setEnabled(true);
        QString SectionsQuery = SectionList.join("\",\"");
        updateTableView(ui->CombExersiceTable,SqlFunctions::GetCombFiles.
                        arg(ComFileType).
                        arg("\""+SectionsQuery+"\""));
    }
    else {
        ui->CombExerciseButton->setEnabled(false);
    }
}

void NewDatabaseFile::on_CombExerciseButton_clicked()
{
    SectionList.clear();
    QString Field = ui->CombFieldList->currentItem()->text();
    QString Id = ui->CombExerciseButton->property("Name").toString();
    buttonindex = ui->CombExerciseButton->property("Index").toInt();
    QString folderName = SqlFunctions::Get_StringList_From_Query(
                SqlFunctions::FolderName.arg(ComFileType),currentbase).at(0);
    QStringList sectionslist;
    for (int i=0;i<ui->SelectedSections->count() ;i++ ) {
        sectionslist.append(ui->SelectedSections->item(i)->text());
        SectionList.append(ui->SelectedSections->item(i)->data(Qt::UserRole).toString());
    }
    QString FolderName = sectionslist.join("-");
    QString Path;
    QString SubjectType = ui->CombExercisesSubjectComboBox->currentText();
    if (ui->CombExerciseRadio->isChecked()){
    Path = DataBase_Path+Field+QDir::separator()+folderName+QDir::separator()+FolderName+"/";}
    else if (ui->CombSubjectRadio->isChecked())
    {Path = DataBase_Path+Field+QDir::separator()+folderName+QDir::separator()+FolderName+"/"+SubjectType+"/";}
    QDir dir(Path);
    if (!dir.exists()){dir.mkpath(".");}
    QStringList files;
    QDirIterator lista(Path,QStringList() << "*.tex", QDir::Files, QDirIterator::Subdirectories);
    while (lista.hasNext()){
    files.append(lista.next());}
    int count = files.count();
    count++;
    QString count_sub = QString::number(count);
    QString FieldId = ui->CombFieldList->currentItem()->data(Qt::UserRole).toString();
    QString SectionsId = SectionList.join("");
    QString SubjectTypeId = ui->CombExercisesSubjectComboBox->currentData().toString();
    QString filePathName;
    if (ui->CombSubjectRadio->isChecked()){
        filePathName = QFileDialog::getSaveFileName(this, tr("Επιλέξτε ένα όνομα αρχείου"),
                Path+"DTX-"+FieldId+"-"+SectionsId+"-"+SubjectTypeId+"-"+ComFileType+count_sub+".tex","tex Files (*.tex)");
        ui->ComExTypeMetadataLine->setText(SubjectType);
        mapIdsNames.insert("ExerciseType",SubjectTypeId);
    }
    else if (ui->CombExerciseRadio->isChecked()){
        filePathName = QFileDialog::getSaveFileName(this, tr("Επιλέξτε ένα όνομα αρχείου"),
                Path+"DTX-"+FieldId+"-"+SectionsId+"-"+ComFileType+count_sub+".tex","tex Files (*.tex)");
        ui->ComExTypeMetadataLine->setText(SubjectType);
        mapIdsNames.insert("ExerciseType","-");
    }
    QFileInfo file(filePathName);
    ui->FilePathLine->setText(file.absolutePath()+QDir::separator());
    ui->FileNameLine->setText(file.fileName());
    ui->ComFieldMetadataLine->setText(Field);
    ui->ComSectionsMetadataLine->setText(sectionslist.join(","));
    ui->ComFileTypeMetadataLine->setText(folderName);
    mapIdsNames.insert("Field",FieldId);
    mapIdsNames.insert("Chapter","-");
    mapIdsNames.insert("FileType",ComFileType);
    mapIdsNames.insert("Difficulty",ui->ExerSpinBox->text());
    mapIdsNames.insert("Date",ui->ExerDateTimeEdit->text());
    mapIdsNames.insert("Id",QFileInfo(ui->FileNameLine->text()).baseName());
    mapIdsNames.insert("Path",ui->FilePathLine->text()+ui->FileNameLine->text());
    mapIdsNames.insert("Solved",tr("NO"));

}

void NewDatabaseFile::on_SelectedSections_itemClicked(QListWidgetItem *item)
{
    ui->removeButton->setEnabled(true);
}
// --------- END OF COMB EXERCISE / SUBJECT TAB -----------------

void NewDatabaseFile::on_OkDialogButton_rejected()
{
    ui->FilePathLine->clear();

    QString radioId;
    QString radioId2;
    QStringList sections;
    QString sectionsJoined;
    for(int i=0;i<ui->buttonGroup_2->buttons().count();i++){
        if(ui->buttonGroup_2->buttons().at(i)->isChecked()){
            radioId = QString::number(i);
        }
        else{radioId = "NULL";}
    }
    for(int i=0;i<ui->buttonGroup->buttons().count();i++){
        if(ui->buttonGroup->buttons().at(i)->isChecked()){
            radioId2 = QString::number(i);
        }
        else{radioId2 = "NULL";}
    }
    if(ui->tabWidget->currentIndex()==2 && ui->SelectedSections->count()>0){
        for (int i=0;i<ui->SelectedSections->count() ;i++ ) {
            sections.append(ui->SelectedSections->item(i)->text());
        }
        sectionsJoined = "\""+sections.join(",")+"\"";
    }
    else{sectionsJoined = "NULL";}

    QSqlQuery SetInitialValues(Texstudio::DataTeX_Settings);
    SetInitialValues.exec(QString("UPDATE \"Initial_Settings\" "
                                "SET \"Value\" = CASE \"Setting\" "
                                "WHEN 'NewDatabaseFile_CurrentTab' THEN %1 "
                                "WHEN 'NewDatabaseFile_Theory_CurrentField' THEN %2 "
                                "WHEN 'NewDatabaseFile_Theory_CurrentChapter' THEN %3 "
                                "WHEN 'NewDatabaseFile_Theory_CurrentSection' THEN %4 "
"WHEN 'NewDatabaseFile_Exercises_CurrentField' THEN %5 "
"WHEN 'NewDatabaseFile_Exercises_CurrentChapter' THEN %6 "
"WHEN 'NewDatabaseFile_Exercises_CurrentSection' THEN %7 "
"WHEN 'NewDatabaseFile_Exercises_CurrentFileType' THEN %8 "
"WHEN 'NewDatabaseFile_Exercises_CurrentExerciseType' THEN %9 "
"WHEN 'NewDatabaseFile_Comb_CurrentField' THEN %10 "
"WHEN 'NewDatabaseFile_Comb_SelectedSections' THEN %11 "
"WHEN 'NewDatabaseFile_Comb_FileType' THEN %12 "
"WHEN 'NewDatabaseFile_Comb_CurrentSubjectType' THEN %13 "
                                "ELSE \"Setting\" "
                                "END "
                                "WHERE \"Setting\" IN('NewDatabaseFile_CurrentTab',"
                                "'NewDatabaseFile_Theory_CurrentField',"
                                " 'NewDatabaseFile_Theory_CurrentChapter',"
                                "'NewDatabaseFile_Theory_CurrentSection','NewDatabaseFile_Exercises_CurrentField',"
"'NewDatabaseFile_Exercises_CurrentChapter','NewDatabaseFile_Exercises_CurrentSection',"
"'NewDatabaseFile_Exercises_CurrentFileType'"
",'NewDatabaseFile_Exercises_CurrentExerciseType','NewDatabaseFile_Comb_CurrentField',"
"'NewDatabaseFile_Comb_SelectedSections','NewDatabaseFile_Comb_FileType','NewDatabaseFile_Comb_CurrentSubjectType');")
                          .arg(ui->tabWidget->currentIndex())
                          .arg(ui->FieldTable->currentRow())
                          .arg(ui->ComboChapter_Theory->currentIndex())
                          .arg(ui->ComboSection_Theory->currentIndex())
                          .arg(ui->SectionExercisesFieldComboBox->currentIndex())
                          .arg(ui->SectionExercisesChapterComboBox->currentIndex())
                          .arg(ui->SectionExercisesSectionComboBox->currentIndex())
                          .arg(radioId)
                          .arg(ui->SectionExercisesExTypeComboBox->currentIndex())
                          .arg(ui->CombFieldList->currentRow())
                          .arg(sectionsJoined)
                          .arg(radioId2)
                          .arg(ui->CombExercisesSubjectComboBox->currentIndex())
                          );
    reject();
}

NewDatabaseFile::~NewDatabaseFile()
{
    delete ui;
}

void NewDatabaseFile::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Close Window"),tr("Do you want to close the window?"),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        ui->FilePathLine->clear();
        ui->FileNameLine->clear();
        event->accept();
    }
}

void NewDatabaseFile::on_CopyButton_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->FileNameLine->text());
}

void NewDatabaseFile::on_helpButton_clicked()
{
//    QDesktopServices::openUrl(QUrl("file:///"+Path));
}

void NewDatabaseFile::TableItemDoubleClicked(QTableView * table,const QModelIndex &index,int column)
{
    int row = index.row();
    QString FilePath = table->model()->data(table->model()->index(row,column)).toString();
    QString outName = QFileInfo(FilePath).path() + QDir::separator()+ QFileInfo(FilePath).baseName()+".pdf";

    if(QFileInfo::exists(outName)){
        QDesktopServices::openUrl(QUrl("file:///"+outName));
    }
    else{Texstudio::createPdf(FilePath);QDesktopServices::openUrl(QUrl("file:///"+FilePath));}
}

void NewDatabaseFile::on_CombExersiceTable_doubleClicked(const QModelIndex &index)
{
    TableItemDoubleClicked(ui->CombExersiceTable,index,1);
}

void NewDatabaseFile::on_FileTable_doubleClicked(const QModelIndex &index)
{
    TableItemDoubleClicked(ui->FileTable,index,2);
}

void NewDatabaseFile::on_ExerciseFileList_doubleClicked(const QModelIndex &index)
{
    TableItemDoubleClicked(ui->ExerciseFileList,index,2);
}
