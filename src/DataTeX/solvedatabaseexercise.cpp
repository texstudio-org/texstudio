#include "solvedatabaseexercise.h"
#include "ui_solvedatabaseexercise.h"
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QDebug>
#include <QDirIterator>
#include <QVector>
#include <QMessageBox>
#include <QCloseEvent>
#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QProcess>
#include <QAbstractButton>
#include "sqlfunctions.h"
#include "texstudio.h"

SolveDatabaseExercise::SolveDatabaseExercise(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolveDatabaseExercise)
{
    ui->setupUi(this);
    currentbase = Texstudio::CurrentTexFilesDataBase;
    QStringList Field_Names;
    QStringList Field_ids;
    QSqlQuery fields(currentbase);
    fields.exec(SqlFunctions::Fields_Query);
    while(fields.next()){
        Field_Names.append(fields.value(0).toString());
        Field_ids.append(fields.value(1).toString());
    }
        for(int row=0;row<Field_Names.count();row++)
        {
            ui->FieldsList->addItem(Field_Names.at(row));
            ui->FieldsList->item(row)->setData(Qt::UserRole,Field_ids.at(row));
        }
    for (int i=0;i<ui->buttonGroup->buttons().count();i++ ) {
        connect(ui->buttonGroup->buttons().at(i), &QRadioButton::toggled, this, &SolveDatabaseExercise::on_FileType_checked);
    }
    ui->ExerciseRadio->setEnabled(false);
    ui->SolvedRadio->setEnabled(false);

    for (int i=0;i<ui->buttonGroup->buttons().count();i++ ) {
        ui->buttonGroup->buttons().at(i)->setEnabled(false);
    }
    ui->ExeciseRadioButton->setProperty("Name","SectEx");
    ui->SubjectRadioButton->setProperty("Name","SectSub");
    ui->ComExerciseRadioButton->setProperty("Name","CombEx");
    ui->ComSubjectRadioButton->setProperty("Name","CombSub");
    ui->ExeciseRadioButton->setProperty("Solution","SolSE");
    ui->SubjectRadioButton->setProperty("Solution","SolSS");
    ui->ComExerciseRadioButton->setProperty("Solution","SolCE");
    ui->ComSubjectRadioButton->setProperty("Solution","SolCS");
    ui->ExeciseRadioButton->setProperty("Hint","HintSE");
    ui->SubjectRadioButton->setProperty("Hint","HintSS");
    ui->ComExerciseRadioButton->setProperty("Hint","HintCE");
    ui->ComSubjectRadioButton->setProperty("Hint","HintCS");
    ui->ExeciseRadioButton->setProperty("Query",SqlFunctions::Section_List_contaning_Exercises);
    ui->ExeciseRadioButton->setProperty("header","\"et\".\"Name\" AS ");
    ui->ExeciseRadioButton->setProperty("title",tr("'Exercise type'"));
    ui->SubjectRadioButton->setProperty("Query",SqlFunctions::Section_List_contaning_Exercises);
    ui->SubjectRadioButton->setProperty("header","\"et\".\"Name\" AS ");
    ui->SubjectRadioButton->setProperty("title",tr("'Subject type'"));
    ui->ComExerciseRadioButton->setProperty("Query",SqlFunctions::GetSectionsCombFiles);
    ui->ComExerciseRadioButton->setProperty("header","group_concat(\"Sections\".\"Name\") AS ");
    ui->ComExerciseRadioButton->setProperty("title",tr("'Sections'"));
    ui->ComSubjectRadioButton->setProperty("Query",SqlFunctions::GetSectionsCombFiles);
    ui->ComSubjectRadioButton->setProperty("header","group_concat(\"Sections\".\"Name\") AS ");
    ui->ComSubjectRadioButton->setProperty("title",tr("'Sections'"));

   connect(ui->ExerciseTable->selectionModel(), &QItemSelectionModel::selectionChanged,
           this, &SolveDatabaseExercise::on_ExerciseTable_itemSelectionChanged);
   view = new PdfViewer(this);
   view->setMinimumWidth(700);
   ui->gridLayout_4->addWidget(view);
   view->show();
}

SolveDatabaseExercise::~SolveDatabaseExercise()
{
    delete ui;
//    currentbase.close();
    delete view;
}

QString SolveDatabaseExercise::getFileType()
{
    QString filetype;
    for (int i=0;i<ui->buttonGroup->buttons().count();i++ ) {
        if(ui->buttonGroup->buttons().at(i)->isChecked()==true){
            filetype = ui->buttonGroup->buttons().at(i)->text();
        }
    }
    return filetype;
}

void SolveDatabaseExercise::on_FileType_checked(bool checked)
{
    ExerciseFiles.clear();
    ui->SectionList->clear();
    if (checked){
        QSqlQueryModel * emptyModel = new QSqlQueryModel(this);
        QSqlQuery emptytable(currentbase);
        emptytable.exec(SqlFunctions::EmptyTable);
        emptyModel->setQuery(emptytable);
        ui->ExerciseTable->setModel(emptyModel);
        ui->ExerciseTable->show();

        QRadioButton *btn = static_cast<QRadioButton *>(sender());
        radiobutton = btn;
        SolutionType = btn->property("Solution").toString();
        HintType = btn->property("Hint").toString();
        QSqlQuery getFileType(currentbase);
        QString fileType = btn->property("Name").toString();
        QSqlQuery sectionList(currentbase);
        QStringList Section_Names;
        QStringList Section_Ids;
        if(ui->ExeciseRadioButton->isChecked() || ui->SubjectRadioButton->isChecked()){
        sectionList.prepare(btn->property("Query").toString().
                            arg(ui->FieldsList->currentItem()->data(Qt::UserRole).toString(),fileType));
        }
        else{sectionList.prepare(btn->property("Query").toString()
                                 .arg(fileType,ui->FieldsList->currentIndex().data(Qt::UserRole).toString()));}
        sectionList.exec();
        while (sectionList.next()) {
            Section_Names.append(sectionList.value(0).toString());
            Section_Ids.append(sectionList.value(1).toString());
        }
        for(int row=0;row<Section_Names.count();row++)
        {
            ui->SectionList->addItem(Section_Names.at(row));
            ui->SectionList->item(row)->setData(Qt::UserRole,Section_Ids.at(row));
        }
    }
}

void SolveDatabaseExercise::on_FieldsList_itemClicked(QListWidgetItem *item)
{
    for (int i=0;i<ui->buttonGroup->buttons().count();i++ ) {
        ui->buttonGroup->buttons().at(i)->setEnabled(true);
    }
    if(ui->buttonGroup->checkedButton() != 0)
    {
       ui->buttonGroup->setExclusive(false);
       ui->buttonGroup->checkedButton()->setChecked(false);
       ui->buttonGroup->setExclusive(true);
    }
    QSqlQueryModel * emptyModel = new QSqlQueryModel(this);
    QSqlQuery emptytable(currentbase);
    emptytable.exec(SqlFunctions::EmptyTable);
    emptyModel->setQuery(emptytable);
    ui->ExerciseTable->setModel(emptyModel);
    ui->ExerciseTable->show();
}

void SolveDatabaseExercise::on_SectionList_itemSelectionChanged()
{
    QString title = radiobutton->property("header").toString()+radiobutton->property("title").toString();
    QSqlQueryModel * Model = new QSqlQueryModel(this);
    QSqlQuery tableQuery(currentbase);
    if(ui->ExeciseRadioButton->isChecked() || ui->SubjectRadioButton->isChecked()){
    tableQuery.prepare(QString(SqlFunctions::ShowSolvedAndUnSolvedExercises).
                       arg(title,radiobutton->property("Name").toString(),
                       ui->SectionList->currentItem()->data(Qt::UserRole).toString()));
    }
    else{tableQuery.prepare(QString(SqlFunctions::ShowSolvedAndUnSolvedCombExercises).
                            arg(radiobutton->property("Name").toString(),ui->SectionList->currentItem()->text()));}
    tableQuery.exec();
    Model->setQuery(tableQuery);
    ui->ExerciseTable->setModel(Model);
    ui->ExerciseTable->show();
    ui->ExerciseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ExerciseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ExerciseTable->setColumnHidden(3,true);
    ui->ExerciseTable->setAlternatingRowColors(true);
    ui->ExerciseTable->setStyleSheet("alternate-background-color: #e8e8e8");
    for (int c = 0; c < ui->ExerciseTable->horizontalHeader()->count()-1; ++c)
    {
        ui->ExerciseTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->ExerciseTable->setSelectionMode( QAbstractItemView::SingleSelection );
    if(ui->buttonGroup_2->checkedButton() != 0)
    {
       ui->buttonGroup_2->setExclusive(false);
       ui->buttonGroup_2->checkedButton()->setChecked(false);
       ui->buttonGroup_2->setExclusive(true);
    }
    connect(ui->ExerciseTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SolveDatabaseExercise::on_ExerciseTable_itemSelectionChanged);
}

void SolveDatabaseExercise::on_ExerciseTable_itemSelectionChanged()
{
    if(ui->ExerciseTable->currentIndex().row()>-1){
        Exercise.clear();
        Solution.clear();
        Hint.clear();
        int row = ui->ExerciseTable->currentIndex().row();
        Exercise = ui->ExerciseTable->model()->data(ui->ExerciseTable->model()->index(row,3)).toString();
        Solution = Exercise;
        Hint = Exercise;
        QStringList Ids;
        QStringList solIds;
        QStringList hintIds;
        QStringList folders;
        QStringList solfolders;
        Ids<<"SectEx"<<"SectSub"<<"CombEx"<<"CombSub";
        solIds<<"SolSE"<<"SolSS"<<"SolCE"<<"SolCS";
        hintIds<<"HintSE"<<"HintSS"<<"HintCE"<<"HintCS";
        for (int i=0;i<Ids.count();i++ ) {

            QString folderName = SqlFunctions::Get_StringList_From_Query(
                        SqlFunctions::FolderName.arg(Ids.at(i)),currentbase).at(0);
            folders.append(folderName);

            QString solfolderName = SqlFunctions::Get_StringList_From_Query(
                        SqlFunctions::FolderName.arg(solIds.at(i)),currentbase).at(0);
            solfolders.append(solfolderName);
            Solution.replace("-"+Ids.at(i),"-"+solIds.at(i));
            Solution.replace(folders.at(i),solfolders.at(i));
            Hint.replace("-"+Ids.at(i),"-"+hintIds.at(i));
            Hint.replace(folders.at(i),solfolders.at(i));
        }

    ui->ExerciseRadio->setEnabled(true);
    ui->ExerciseRadio->setChecked(true);
    ui->SolvedRadio->setEnabled(true);
    loadImageFile(Exercise);
    if(ui->ExerciseTable->model()->data(ui->ExerciseTable->model()->index(row,2)).toString()=="YES") /* && exists */
    {ui->CreateSolutionButton->setText(tr("Open solution"));}
    else{ui->CreateSolutionButton->setText(tr("Create solution"));}
    if(QFileInfo::exists(Hint)){ui->CreateHintButton->setText(tr("Open hint"));}
    else{ui->CreateHintButton->setText(tr("Create hint"));}
    }
    else{if(ui->buttonGroup_2->checkedButton() != 0)
        {
           ui->buttonGroup_2->setExclusive(false);
           ui->buttonGroup_2->checkedButton()->setChecked(false);
           ui->buttonGroup_2->setExclusive(true);
        }
        ui->ExerciseRadio->setEnabled(false);
        ui->SolvedRadio->setEnabled(false);
    }
}

void SolveDatabaseExercise::on_CreateSolutionButton_clicked()
{
    CreateSolution(Solution,SolutionType);
}

void SolveDatabaseExercise::on_CreateHintButton_clicked()
{
    CreateSolution(Hint,HintType);
}

void SolveDatabaseExercise::CreateSolution(QString solutionType,QString filetype)
{
    QStringList Sections;
    QString FileName;
    if(ui->ExerciseTable->model()->rowCount()>0){
    Sections<<ui->SectionList->currentItem()->data(Qt::UserRole).toString().split(",");
    FileName = QFileInfo(Exercise).baseName();
    QSqlQuery solved(currentbase);
    solved.exec(SqlFunctions::UpdateSolution.arg(QFileInfo(Exercise).baseName()));
    QSqlQuery RowValues(currentbase);
    QStringList valuesList;
    RowValues.exec(SqlFunctions::SelestExerciseRow.arg(FileName));
    while (RowValues.next())
    {
        QSqlRecord record = RowValues.record();
        for(int i=0; i < record.count(); i++)
        {
            valuesList << record.value(i).toString();
        }
    }
    QSqlQuery Columns(currentbase);
    QStringList ColumnNames;
    Columns.exec("SELECT \"name\" FROM pragma_table_info(\'Database_Files\');");
    while (Columns.next()){ColumnNames.append(Columns.value(0).toString());}
    QMap<QString,QString> mapValues;
    for(int i=0;i<ColumnNames.count();i++){
        mapValues.insert(ColumnNames.at(i),valuesList.at(i));
    }
    mapValues.insert("Date",QDateTime::currentDateTime().toString("dd/M/yyyy hh:mm"));
    mapValues.insert("FileType",filetype);
    mapValues.insert("Path",solutionType);
    mapValues.insert("Solved","-");
    mapValues.insert("Id",QFileInfo(solutionType).baseName());
    mapValues.remove("Section");

    QDir path(QFileInfo(solutionType).absolutePath());
    if (!path.exists()){path.mkpath(".");}
        QFile SFile;
        if(!SFile.exists(solutionType)){
            emit SolutionFile(solutionType,mapValues,Sections);
        }
        else{QDesktopServices::openUrl(QUrl("file:///"+solutionType));}
    }
    else{if(ui->buttonGroup_2->checkedButton() != 0)
        {
           ui->buttonGroup_2->setExclusive(false);
           ui->buttonGroup_2->checkedButton()->setChecked(false);
           ui->buttonGroup_2->setExclusive(true);
        }
    }
}

void SolveDatabaseExercise::loadImageFile(QString exoFile)
{
    if (exoFile.isEmpty()) {
        return;}
    QString pdfFile = "file:///"+exoFile.replace(".tex",".pdf");
    view->open(QUrl(pdfFile));
}

void SolveDatabaseExercise::on_ExerciseRadio_toggled(bool checked)
{
    if(checked){
    loadImageFile(Exercise);}
}

void SolveDatabaseExercise::on_SolvedRadio_toggled(bool checked)
{
    if(checked){
    loadImageFile(Solution);
    }
}

void SolveDatabaseExercise::on_RecompileButton_clicked()
{
    if(ui->ExerciseRadio->isChecked()){Texstudio::createPdf(Exercise);loadImageFile(Exercise);}
    else {Texstudio::createPdf(Solution);loadImageFile(Solution);}
}

void SolveDatabaseExercise::on_CloseButton_clicked(QAbstractButton *button)
{
    accept();
}
