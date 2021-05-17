#include "addfiletoeditor.h"
#include "ui_addfiletoeditor.h"
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
#include "texstudio.h"


AddFileToEditor::AddFileToEditor(QWidget *parent,QString currentTexFile) :
    QDialog(parent),
    ui(new Ui::AddFileToEditor)
{
    ui->setupUi(this);

    CurrentDatabaseFile = currentTexFile;
    checklist.clear();
    checklist.append(ui->ExercisesBox);
    checklist.append(ui->ExerciseSolutionsBox);
    checklist.append(ui->MethodsBox);
    checklist.append(ui->ExamplesBox);
    for (int i=0;i<ui->buttonGroup->buttons().count();i++ ) {
        connect(ui->buttonGroup->buttons().at(i), &QRadioButton::toggled, this, &AddFileToEditor::on_TheoryCheck_checked);
    }
    for (int i=0;i<checklist.count();i++ ) {
        connect(checklist.at(i), &QRadioButton::toggled, this, &AddFileToEditor::on_CheckBox_checked);
    }

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
        ui->FieldListTheory->addItem (Field_Names.at(item));
        ui->FieldListTheory->item(item)->setData(Qt::UserRole,Field_ids.at(item));
        ui->FieldListExercises->addItem (Field_Names.at(item));
        ui->FieldListExercises->item(item)->setData(Qt::UserRole,Field_ids.at(item));
        ui->FieldListCombExercises->addItem (Field_Names.at(item));
        ui->FieldListCombExercises->item(item)->setData(Qt::UserRole,Field_ids.at(item));
    }
    ui->DefinitionsBox->setEnabled(false);
    ui->TheoremsBox->setEnabled(false);
    ui->TablesBox->setEnabled(false);
    ui->FiguresBox->setEnabled(false);
    ui->CombSubjectsBox->setEnabled(false);
    ui->CombSubjectSolutionsBox->setEnabled(false);
    ui->CombExercisesBox->setEnabled(false);
    ui->CombExerciseSolutionsBox->setEnabled(false);
    ui->ComboChapterExercises->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->ComboSectionExercises->setEnabled(false);
    ui->ComboExTypeExercises->setEnabled(false);
    ui->ComboCombSubjectType->setEnabled(false);
    ui->CombExerciseSolutionsBox->setEnabled(false);
    ui->CombExercisesBox->setEnabled(false);
    ui->ExercisesBox->setEnabled(false);
    ui->ExerciseSolutionsBox->setEnabled(false);
    ui->MethodsBox->setEnabled(false);
    ui->ExamplesBox->setEnabled(false);
    ui->ComboSectionExercises->setMaxVisibleItems (8);
    ui->ComboExTypeExercises->setMaxVisibleItems (8);
    ui->ComboCombSubjectType->setMaxVisibleItems (8);
    ui->removeButton->setEnabled(false);
    ui->UpButton->setEnabled(false);
    ui->DownButton->setEnabled(false);
    //ui->FileList->setSelectionMode( QAbstractItemView::ExtendedSelection );

    if(ui->FieldListTheory->count()==0){
        for(int i=0;i<ui->buttonGroup->buttons().count();i++){
            ui->buttonGroup->buttons().at(i)->setEnabled(false);
        }
    }
    if(ui->FieldListCombExercises->count()==0){
        ui->CombSubjectsBox->setEnabled(false);
        ui->CombSubjectSolutionsBox->setEnabled(false);
    }
    ui->SelectedFiles->setColumnCount(3);
    QStringList horzHeaders;
    ui->SelectedFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SelectedFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SelectedFiles->setColumnWidth(0,100);
    ui->SelectedFiles->setColumnWidth(1,290);
    ui->SelectedFiles->setColumnWidth(2,200);
    ui->SelectedFiles->setColumnHidden(2,true);
    ui->SelectedFiles->setAlternatingRowColors(true);
    ui->SelectedFiles->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << tr("File type") << tr("Name")<<tr("Path");
    ui->SelectedFiles->setHorizontalHeaderLabels(horzHeaders);
    ui->SelectedFiles->horizontalHeader()->setStretchLastSection(true);

    ui->DefinitionsBox->setProperty("Name","Definition");
    ui->TheoremsBox->setProperty("Name","Theorem");
    ui->FiguresBox->setProperty("Name","Figure");
    ui->TablesBox->setProperty("Name","Table");
    ui->MethodsBox->setProperty("Name","Method");
    ui->ExamplesBox->setProperty("Name","Example");
    ui->CombExercisesBox->setProperty("Name","CombEx");
    ui->CombSubjectsBox->setProperty("Name","CombSub");
    ui->CombExerciseSolutionsBox->setProperty("Name","SolCE");
    ui->CombSubjectSolutionsBox->setProperty("Name","SolCS");

    ui->CurrentFileLabel->setText(tr("Insert files to document : ")+CurrentDatabaseFile);

//    view = new PdfViewer(this);
//    view->setMinimumWidth(620);
//    ui->gridLayout_17->addWidget(view,1,0);
//    view->show();
}

AddFileToEditor::~AddFileToEditor()
{
    delete ui;
//    delete view;
}

void AddFileToEditor::on_FieldListTheory_itemClicked(QListWidgetItem *item)
{
    ui->DefinitionsBox->setEnabled(true);
    ui->TheoremsBox->setEnabled(true);
    ui->TablesBox->setEnabled(true);
    ui->FiguresBox->setEnabled(true);
    ui->FileList->clear();
    if(ui->buttonGroup->checkedButton() != 0)
    {
       ui->buttonGroup->setExclusive(false);
       ui->buttonGroup->checkedButton()->setChecked(false);
       ui->buttonGroup->setExclusive(true);
    }
}

void AddFileToEditor::on_ComboChapterTheory_currentIndexChanged(int index)
{
    ui->comboSectionTheory->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                           ui->ComboChapterTheory->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
    ui->comboSectionTheory->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->comboSectionTheory->setCurrentIndex(-1);
}

void AddFileToEditor::on_comboSectionTheory_currentIndexChanged(int index)
{    
    ui->FileList->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Double_List(SqlFunctions::GetTheoryFiles
            .arg(ui->FieldListTheory->currentItem()->data(Qt::UserRole).toString(),FileType
                 ,ui->ComboChapterTheory->currentData().toString(),
                 ui->comboSectionTheory->currentData().toString()),currentbase);
    for(int row=0;row<data[0].count();row++)
    {
        ui->FileList->addItem(data[0].at(row));
        ui->FileList->item(row)->setData(Qt::UserRole,data[1].at(row));
    }
}

void AddFileToEditor::on_TheoryCheck_checked(bool checked)
{
    QCheckBox *btn = static_cast<QCheckBox *>(sender());
    FileType = btn->property("Name").toString();
    ui->ComboChapterTheory->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           ui->FieldListTheory->currentItem()->text());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboChapterTheory->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboChapterTheory->setCurrentIndex(-1);
}

void AddFileToEditor::on_FileList_itemSelectionChanged()
{
    PreviewFile.clear();
    QVariant data = ui->FileList->currentItem()->data(Qt::UserRole);
    QString fullFilePath = data.toString();
    QString file = fullFilePath;
    QString pdffile = file.replace(".tex",".pdf");
    PreviewFile = fullFilePath;
    if(!QFileInfo::exists(pdffile)){Texstudio::createPdf(fullFilePath);loadImageFile(fullFilePath);}
    else {loadImageFile(fullFilePath);}
}

void AddFileToEditor::loadImageFile(QString exoFile)
{
    if (exoFile.isEmpty()) {
        return;}
    QString pdfFile = "file:///"+exoFile.replace(".tex",".pdf");
//    view->open(QUrl(pdfFile));
}

void AddFileToEditor::on_FieldListExercises_itemClicked(QListWidgetItem *item)
{
    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);
    ui->radioButton->setChecked(true);
    for (int i=0;i<checklist.count() ;i++ ) {
        checklist.at(i)->setEnabled(true);
    }
    if(ui->buttonGroup_2->checkedButton() != 0)
    {ui->buttonGroup_2->setExclusive(false);
    ui->buttonGroup_2->checkedButton()->setChecked(false);
    ui->buttonGroup_2->setExclusive(true);}
}

void AddFileToEditor::on_radioButton_toggled(bool checked)
{
    ui->FileList->clear();
    if(ui->buttonGroup_2->checkedButton() != 0)
    {
       ui->buttonGroup_2->setExclusive(false);
       ui->buttonGroup_2->checkedButton()->setChecked(false);
       ui->buttonGroup_2->setExclusive(true);
    }
    ui->ComboExTypeExercises->clear();
    if(checked){
        ExSubType = "SectEx";
        SolutionFileType = "SolSE";
        ui->ExercisesBox->setText(tr("Exercises"));
        ui->ExerciseSolutionsBox->setText(tr("Exercise solutions"));
        ui->label_10->setText(tr("Exercise type"));
    }
    else{
        ExSubType = "SectSub";
        SolutionFileType = "SolSS";
        ui->ExercisesBox->setText("Subjects");
        ui->label_10->setText("Subject type");
    ui->ExerciseSolutionsBox->setText("Subject solutions");}
    ui->ExercisesBox->setProperty("Name",ExSubType);
    ui->ExerciseSolutionsBox->setProperty("Name",SolutionFileType);
}

void AddFileToEditor::on_CheckBox_checked(bool checked)
{
    if(checked){
        ui->ComboChapterExercises->setEnabled(checked);
        ui->ComboChapterExercises->clear();
            QCheckBox *btn = static_cast<QCheckBox *>(sender());
            FileType = btn->property("Name").toString();
//                    SqlFunctions::Get_StringList_From_Query(
//                        SqlFunctions::GetFileTypeIdfromCheckBox.arg(btn->text()),currentbase).at(0);
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           ui->FieldListExercises->currentItem()->text());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboChapterExercises->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboChapterExercises->setCurrentIndex(-1);
    ui->ComboSectionExercises->setEnabled(false);
    ui->ComboExTypeExercises->setEnabled(false);
    }
}

void AddFileToEditor::on_ComboChapterExercises_currentIndexChanged(int index)
{
    ui->ComboSectionExercises->setEnabled(true);
    ui->ComboSectionExercises->setCurrentIndex(-1);
    ui->ComboSectionExercises->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                           ui->ComboChapterExercises->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboSectionExercises->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->ComboSectionExercises->setCurrentIndex(-1);
    ui->ComboExTypeExercises->setEnabled(false);

}

void AddFileToEditor::on_ComboSectionExercises_currentIndexChanged(int index)
{
    ui->label_10->setEnabled(true);
    ui->ComboExTypeExercises->setEnabled(true);
    ui->ComboExTypeExercises->clear();
    if(ui->radioButton->isChecked()){}

    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::Exercise_Types_Query.arg(ui->ComboSectionExercises->currentData().toString()),currentbase);
    for (int item=0;item<data[0].count() ;item++ ) {
        ui->ComboExTypeExercises->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ui->FileList->clear();
    if(ui->MethodsBox->isChecked() || ui->ExamplesBox->isChecked()){
        ui->ComboExTypeExercises->setEnabled(false);
        ui->ComboExTypeExercises->clear();
    }
    ui->ComboExTypeExercises->setCurrentIndex(-1);
}

void AddFileToEditor::on_ComboExTypeExercises_currentIndexChanged(int index)
{
    ui->FileList->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Double_List(SqlFunctions::AddExerciseFilesToEditor
            .arg(ui->FieldListExercises->currentItem()->data(Qt::UserRole).toString())
            .arg(ui->ComboChapterExercises->currentData().toString())
            .arg(ui->ComboSectionExercises->currentData().toString())
            .arg(ui->ComboExTypeExercises->currentData().toString())
            .arg(FileType),currentbase);
    for(int row=0;row<data[0].count();row++)
    {
        ui->FileList->addItem(data[0].at(row));
        ui->FileList->item(row)->setData(Qt::UserRole,data[1].at(row));
    }
}

void AddFileToEditor::on_Okbutton_rejected()
{
    reject();
}

void AddFileToEditor::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,
                 tr("Close window"),tr("Do you want to close the window?"),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void AddFileToEditor::on_FileList_itemDoubleClicked(QListWidgetItem *item)
{
//    int rows = ui->SelectedFiles->rowCount();
//    rows++;
//    if(rows>0 && rows!=1){
//        ui->removeButton->setEnabled(true);
//        ui->UpButton->setEnabled(true);
//        ui->DownButton->setEnabled(true);
//    }
//    else if(rows==1){
//        ui->removeButton->setEnabled(true);
//        ui->UpButton->setEnabled(false);
//        ui->DownButton->setEnabled(false);
//    }
    QString fullFilePath = ui->FileList->currentItem()->data(Qt::UserRole).toString();
    QString Id = item->text();
    QString FileType = SqlFunctions::Get_StringList_From_Query(SqlFunctions::AddTheoryFilesToEditor.arg(fullFilePath),currentbase).at(0);
    int row = ui->SelectedFiles->rowCount();
    ui->SelectedFiles->insertRow(row);
    ui->SelectedFiles->setItem(row,1 , new QTableWidgetItem(Id));
    ui->SelectedFiles->setItem(row,0 , new QTableWidgetItem(FileType));
    ui->SelectedFiles->setItem(row,2 , new QTableWidgetItem(fullFilePath));
    ui->SelectedFiles->selectRow(row);
}

void AddFileToEditor::on_FieldListCombExercises_itemClicked(QListWidgetItem *item)
{
    ui->SectionsList->clear();
    ui->CombSubjectsBox->setEnabled(true);
    ui->CombSubjectSolutionsBox->setEnabled(true);
    ui->CombExercisesBox->setEnabled(true);
    ui->CombExerciseSolutionsBox->setEnabled(true);
    if(ui->buttonGroup_4->checkedButton() != 0)
    {
       ui->buttonGroup_4->setExclusive(false);
       ui->buttonGroup_4->checkedButton()->setChecked(false);
       ui->buttonGroup_4->setExclusive(true);
    }
    ui->FileList->clear();
}

void AddFileToEditor::on_ComboCombSubjectType_currentIndexChanged(int index)
{
    ui->SectionsList->clear();
    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::GetSectionsCombFiles
                .arg(ComFileType,ui->FieldListCombExercises->currentItem()->data(Qt::UserRole).toString()),currentbase);
    for(int i=0;i<data[0].count();i++){
        ui->SectionsList->addItem(data[0].at(i));
        ui->SectionsList->item(i)->setData(Qt::UserRole,data[1].at(i));
    }
}

void AddFileToEditor::on_SectionsList_itemClicked(QListWidgetItem *item)
{
    ui->FileList->clear();
    QStringList SectionList = item->data(Qt::UserRole).toString().split(",");
    QString Sections = "\""+SectionList.join("\",\"")+"\"";
    QString SectionsLength = QString::number(SectionList.length());
    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::AddCombFilesToList.arg(Sections,ComFileType,SectionsLength),currentbase);
    for(int row=0;row<data[0].count();row++)
    {
        ui->FileList->addItem(data[0].at(row));
        ui->FileList->item(row)->setData(Qt::UserRole,data[1].at(row));
    }
}

void AddFileToEditor::on_CombSubjectsBox_clicked(bool checked)
{
    if(checked){
        ComFileType = ui->CombSubjectsBox->property("Name").toString();
    ui->ComboCombSubjectType->setEnabled(true);
    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::GetSubject_Types,currentbase);
    for (int item=0;item<data[0].count() ;item++ )
        {
            ui->ComboCombSubjectType->addItem(data[0].at(item), QVariant(data[1].at(item)));
        }
    ui->ComboCombSubjectType->setCurrentIndex(-1);
    ui->SectionsList->clear();
    }
}

void AddFileToEditor::on_CombSubjectSolutionsBox_clicked(bool checked)
{
    if(checked){
        ComFileType = ui->CombSubjectSolutionsBox->property("Name").toString();
    ui->ComboCombSubjectType->setEnabled(true);
    QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                SqlFunctions::GetSubject_Types,currentbase);
    for (int item=0;item<data[0].count() ;item++ )
        {
            ui->ComboCombSubjectType->addItem(data[0].at(item), QVariant(data[1].at(item)));
        }
    ui->ComboCombSubjectType->setCurrentIndex(-1);
    ui->SectionsList->clear();
    }
}

void AddFileToEditor::on_CombExercisesBox_clicked(bool checked)
{
    if(checked){
        ComFileType = ui->CombExercisesBox->property("Name").toString();
        ui->ComboCombSubjectType->clear();
        ui->SectionsList->clear();
        ui->ComboCombSubjectType->setEnabled(false);
        QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                    SqlFunctions::GetSectionsCombFiles
                    .arg(ComFileType,ui->FieldListCombExercises->currentItem()->data(Qt::UserRole).toString()),currentbase);
        for(int i=0;i<data[0].count();i++){
            ui->SectionsList->addItem(data[0].at(i));
            ui->SectionsList->item(i)->setData(Qt::UserRole,data[1].at(i));
            }
    }
}

void AddFileToEditor::on_CombExerciseSolutionsBox_clicked(bool checked)
{
    if(checked){
        ComFileType = ui->CombExerciseSolutionsBox->property("Name").toString();
        ui->ComboCombSubjectType->clear();
        ui->SectionsList->clear();
        ui->ComboCombSubjectType->setEnabled(false);
        QList<QStringList> data = SqlFunctions::ComboList_Double_List(
                    SqlFunctions::GetSectionsCombFiles
                    .arg(ComFileType,ui->FieldListCombExercises->currentItem()->data(Qt::UserRole).toString()),currentbase);
        for(int i=0;i<data[0].count();i++){
            ui->SectionsList->addItem(data[0].at(0));
            ui->SectionsList->item(i)->setData(Qt::UserRole,data[1].at(i));
            }
    }
}

void AddFileToEditor::on_addButton_clicked()
{
    QListWidgetItem* item = ui->FileList->currentItem();
    on_FileList_itemDoubleClicked(item);
}

void AddFileToEditor::on_removeButton_clicked()
{
    int rows = ui->SelectedFiles->rowCount();
    if(rows!=1){
        int row = ui->SelectedFiles->currentRow();
        ui->SelectedFiles->removeRow(row);
        ui->SelectedFiles->selectRow(row-1);
    }
    else if(rows==1){
        ui->SelectedFiles->removeRow(0);
        ui->removeButton->setEnabled(false);
        ui->UpButton->setEnabled(false);
        ui->DownButton->setEnabled(false);
        loadImageFile("");
    }
}

void AddFileToEditor::on_SelectedFiles_itemSelectionChanged()
{
    PreviewFile.clear();
    int rows = ui->SelectedFiles->rowCount();
    if(rows>0){
        int row = ui->SelectedFiles->currentRow();
        ui->removeButton->setEnabled(true);
        if(rows!=0 && rows!=1){
            if(row == rows-1){
                ui->UpButton->setEnabled(true);
                ui->DownButton->setEnabled(false);
            }
            else if(row>0 && row<rows-1){
                ui->DownButton->setEnabled(true);
                ui->UpButton->setEnabled(true);
            }
            else if(row==0){
                ui->UpButton->setEnabled(false);
                ui->DownButton->setEnabled(true);
            }
        }
        else if(rows==1){
            ui->UpButton->setEnabled(false);
            ui->DownButton->setEnabled(false);
        }
        if(row>-1){
        QString fullFilePath = ui->SelectedFiles->item(row,2)->text();
        PreviewFile = fullFilePath;
        loadImageFile(fullFilePath);}
    }
    else if(rows==0){
        ui->removeButton->setEnabled(false);
        ui->UpButton->setEnabled(false);
        ui->DownButton->setEnabled(false);
    }
}

void AddFileToEditor::on_Okbutton_accepted()
{
    int rows = ui->SelectedFiles->rowCount();
    QStringList paths;
    for (int i=0;i<rows;i++) {
        QString path = ui->SelectedFiles->item(i,2)->text();
        paths.append(path);
    }
    emit files(paths);
    accept();
}

void AddFileToEditor::moveup(bool up)
{
    Q_ASSERT(ui->SelectedFiles->selectedItems().count() > 0);
    const int sourceRow = ui->SelectedFiles->row(ui->SelectedFiles->selectedItems().at(0));
    const int destRow = (up ? sourceRow-1 : sourceRow+1);
    Q_ASSERT(destRow >= 0 && destRow < ui->SelectedFiles->rowCount());

    // take whole rows
    QList<QTableWidgetItem*> sourceItems = takeRow(sourceRow);
    QList<QTableWidgetItem*> destItems = takeRow(destRow);

    // set back in reverse order
    setRow(sourceRow, destItems);
    setRow(destRow, sourceItems);
    ui->SelectedFiles->selectRow(destRow);
}

void AddFileToEditor::movedown(bool down)
{
    Q_ASSERT(ui->SelectedFiles->selectedItems().count() > 0);
    const int sourceRow = ui->SelectedFiles->row(ui->SelectedFiles->selectedItems().at(0));
    const int destRow = (down ? sourceRow+1 : sourceRow-1);
    Q_ASSERT(destRow >= 0 && destRow < ui->SelectedFiles->rowCount());

    // take whole rows
    QList<QTableWidgetItem*> sourceItems = takeRow(sourceRow);
    QList<QTableWidgetItem*> destItems = takeRow(destRow);

    // set back in reverse order
    setRow(sourceRow, destItems);
    setRow(destRow, sourceItems);
    ui->SelectedFiles->selectRow(destRow);
}

// takes and returns the whole row
QList<QTableWidgetItem*> AddFileToEditor::takeRow(int row)
{
    QList<QTableWidgetItem*> rowItems;
    for (int col = 0; col < ui->SelectedFiles->columnCount(); ++col)
    {
        rowItems << ui->SelectedFiles->takeItem(row, col);
    }
    return rowItems;
}

// sets the whole row
void AddFileToEditor::setRow(int row, const QList<QTableWidgetItem*>& rowItems)
{
    for (int col = 0; col < ui->SelectedFiles->columnCount(); ++col)
    {
        ui->SelectedFiles->setItem(row, col, rowItems.at(col));
    }
}

void AddFileToEditor::on_UpButton_clicked()
{
    moveup(true);
}

void AddFileToEditor::on_DownButton_clicked()
{
    movedown(true);
}

void AddFileToEditor::on_Rebuild_clicked()
{
    Texstudio::createPdf(PreviewFile);
    loadImageFile(PreviewFile);
}
