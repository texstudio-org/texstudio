#include "editdatabasefiles.h"
#include "ui_editdatabasefiles.h"
#include <QTableWidget>
#include <QDesktopServices>
#include "texstudio.h"
#include "sqlfunctions.h"
#include <QComboBox>
#include <QAbstractSpinBox>
#include "latexdocument.h"

EditDataBaseFiles::EditDataBaseFiles(QWidget *parent,QStringList BibNames,QStringList BibDescriptions) :
    QDialog(parent),
    ui(new Ui::EditDataBaseFiles)
{
    ui->setupUi(this);
    ui->FilesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->FilesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currentbase = Texstudio::CurrentTexFilesDataBase;
    ui->CurrentBaseLabel->setText(QFileInfo(Texstudio::CurrentDataBasePath).baseName());

    bibDescriptions = BibDescriptions;
    bibNames = BibNames;
    ShowDataBaseFiles();

    QSqlQuery Select_DataBase_Basic_Metadata(Texstudio::DataTeX_Settings);

    Select_DataBase_Basic_Metadata.exec(SqlFunctions::GetCurrentDataBaseBasicFields
                                           .arg(QFileInfo(Texstudio::CurrentDataBasePath).baseName()));
    while(Select_DataBase_Basic_Metadata.next()){
        Basic_Metadata_Ids.append(Select_DataBase_Basic_Metadata.value(0).toString());
        Basic_Metadata_Names.append(Select_DataBase_Basic_Metadata.value(1).toString());
    }
    QSqlQuery Select_DataBase_Optional_Metadata(Texstudio::DataTeX_Settings);

    Select_DataBase_Optional_Metadata.exec(SqlFunctions::GetCurrentDataBaseOptionalFields
                                           .arg(QFileInfo(Texstudio::CurrentDataBasePath).baseName()));
    while(Select_DataBase_Optional_Metadata.next()){
        Optional_Metadata_Ids.append(Select_DataBase_Optional_Metadata.value(0).toString());
        Optional_Metadata_Names.append(Select_DataBase_Optional_Metadata.value(1).toString());
    }
    ui->ComboCount->addItem(tr("Field"),QVariant(SqlFunctions::CountFiles_by_Field));
    ui->ComboCount->addItem(tr("Chapter"),QVariant(SqlFunctions::CountFiles_by_Chapter));
    ui->ComboCount->addItem(tr("Section"),QVariant(SqlFunctions::CountFiles_by_Section));
    ui->ComboCount->addItem(tr("Exercise type"),QVariant(SqlFunctions::CountFiles_by_ExerciseType));
    ui->ComboCount->addItem(tr("File type"),QVariant(SqlFunctions::CountFiles_by_FileType));
    for (int i=0;i<Optional_Metadata_Ids.count();i++ ) {
        QHBoxLayout * hbox = new QHBoxLayout(this);
        QLabel * label = new QLabel(Optional_Metadata_Names.at(i),this);
        labelList.append(label);
        hLayoutList.append(hbox);
        QLineEdit * line = new QLineEdit(this);
        lineList.append(line);
        ui->verticalLayout_3->addLayout(hLayoutList.at(i),i+10);
        hLayoutList.at(i)->addWidget(labelList.at(i),0);
        hLayoutList.at(i)->addWidget(lineList.at(i),1);
        mapIdsWidgets.insert(Optional_Metadata_Ids.at(i),line);
        line->setAlignment(Qt::AlignRight);

        Metadata<<Optional_Metadata_Ids.at(i);
        LineEditList<<lineList.at(i);
    }
    QSpacerItem * vspacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->verticalLayout_3->addItem(vspacer);
    QSqlQueryModel * Model = new QSqlQueryModel(this);
    QSqlQuery query(currentbase);
    query.exec(SqlFunctions::CountFiles_by_Field);
    Model->setQuery(query);
    ui->CountFilesTable->setModel(Model);
    ui->CountFilesTable->show();
    for (int c = 0; c < ui->CountFilesTable->horizontalHeader()->count()-1; ++c)
    {
        ui->CountFilesTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    OptionalFields = Optional_Metadata_Ids.join(",");
    connect(ui->FileEdit, &QTextEdit::textChanged, this, &EditDataBaseFiles::FileEdit_Changed);
    Basic_Metadata_Ids.move(5,1);
    Basic_Metadata_Names.move(5,1);
    Basic_Metadata_Ids.removeAt(4);
    Basic_Metadata_Names.removeAt(4);

    ui->DeleteFileFromBaseButton->setEnabled(false);

    QList<QLineEdit *> FilterList;
    FilterList <<ui->FieldFilter<<ui->ChapterFilter<<ui->SectionFilter<<
                 ui->ExerciseFilter<<ui->FileTypeFilter;
    for (int i=0;i<FilterList.count();i++ ) {
        connect(FilterList.at(i), &QLineEdit::textChanged, this, &EditDataBaseFiles::Filter_textChanged);
    }
    ui->SaveTextButton->setEnabled(false);
    ui->BuildButton->setEnabled(false);
    ui->OpenInEditorButton->setEnabled(false);
    ui->ResetButton->setEnabled(false);

    QSqlQuery Select_DataBase_Bibliography(Texstudio::DataTeX_Settings);
    Select_DataBase_Bibliography.exec(QString(SqlFunctions::GetBibliographyFields)
                                           .arg(QFileInfo(Texstudio::CurrentDataBasePath).baseName()));
    while(Select_DataBase_Bibliography.next()){
        Bibliography_Ids.append(Select_DataBase_Bibliography.value(0).toString());
        Bibliography_Names.append(Select_DataBase_Bibliography.value(1).toString());
    }
    ui->CitationKeyLabel->setText(Bibliography_Names.at(0));
    ui->DocumentTypeLabel->setText(Bibliography_Names.at(1));
    for(int i=0;i<BibNames.count();i++){
        ui->DocumentTypeCombo->addItem(BibDescriptions.at(i),QVariant(BibNames.at(i)));
    }

    for (int item=2;item<Bibliography_Ids.count();item++ ) {
        QHBoxLayout * hbox2 = new QHBoxLayout(this);
        QLabel * label2 = new QLabel(Bibliography_Names.at(item),this);
        QLineEdit * line2 = new QLineEdit(this);
        BibLineEditList.append(line2);
        ui->verticalLayout->addLayout(hbox2,item);
        hbox2->addWidget(label2,0);
        hbox2->addWidget(line2,1);
        mapBibliographyWidgets.insert(Bibliography_Ids.at(item),line2);
        line2->setAlignment(Qt::AlignRight);
    }

    ui->CitationKeyLine->setReadOnly(true);
    for (int item=2;item<BibLineEditList.count();item++) {
        BibLineEditList.at(item)->setReadOnly(true);
    }

//    view = new PdfViewer(this);
//    ui->gridLayout->addWidget(view);
//    view->show();
}

void EditDataBaseFiles::ShowDataBaseFiles()
{
    QSqlQueryModel * Database = new QSqlQueryModel(this);
    QSqlQuery DatabaseQuery(currentbase);
    DatabaseQuery.exec(SqlFunctions::ShowAllDatabaseFiles);
    Database->setQuery(DatabaseQuery);
    ui->FilesTable->setModel(Database);
    ui->FilesTable->show();
    connect(ui->FilesTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &EditDataBaseFiles::FilesTable_selectionchanged);
}

void EditDataBaseFiles::updateTableView(QTableView * table,QString QueryText)
{
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery query(currentbase);
    query.exec(QueryText);
    model->setQuery(query);
    table->setModel(model);
    table->show();
    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &EditDataBaseFiles::FilesTable_selectionchanged);
}

EditDataBaseFiles::~EditDataBaseFiles()
{
    delete ui;
//    delete view;
}

void EditDataBaseFiles::FilesTable_selectionchanged()
{
    int row = ui->FilesTable->currentIndex().row();
    DatabaseFileName = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,0)).toString();
    Field = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,2)).toString();
    Chapter = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,3)).toString();
    Section = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,4)).toString();
    ExerciseType = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,5)).toString();
    FileType = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,1)).toString();
    DatabaseFilePath = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,6)).toString();
    Difficulty = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,7)).toInt();
    Date = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,8)).toString();
    Solved = ui->FilesTable->model()->data(ui->FilesTable->model()->index(row,9)).toString();
    ui->DateTimeEdit->setDateTime(QDateTime::fromString(Date,"dd/M/yyyy hh:mm"));
    ui->DifficultySpinBox->setValue(Difficulty);

    QSqlQuery OptionalValues(currentbase);
    OptionalValues.exec(QString("SELECT %1 FROM Database_Files WHERE Id = \"%2\"").arg(OptionalFields,DatabaseFileName));
    QStringList s;
    while(OptionalValues.next()){
        QSqlRecord record = OptionalValues.record();
        for(int i=0; i < record.count(); i++)
        {
            s << record.value(i).toString();
            LineEditList.at(i)->setText(record.value(i).toString());
        }
    }

    ui->NameLine->setText(DatabaseFileName);
    ui->FieldLine->setText(Field);
    ui->ChapterLine->setText(Chapter);
    ui->SectionLine->setText(Section);
    ui->ExerciseTypeLine->setText(ExerciseType);
    ui->FileTypeLine->setText(FileType);
    ui->PathLine->setText(DatabaseFilePath);
    ui->SolvedLine->setText(Solved);
    loadImageFile(DatabaseFilePath);

    QFile file(DatabaseFilePath);
    file.open(QIODevice::ReadOnly);
    QTextStream text(&file);
    text.flush();
    FileContent = text.readAll();
    file.close();
    ui->FileEdit->setText(FileContent);
    ui->SaveTextButton->setEnabled(false);
    ui->BuildButton->setEnabled(true);
    ui->OpenInEditorButton->setEnabled(true);
    ui->ResetButton->setEnabled(false);
    ui->DeleteFileFromBaseButton->setEnabled(true);

    QSqlQuery FileBibliographyQuery(currentbase);
    FileBibliographyQuery.exec(QString("SELECT * FROM \"Bibliography\" WHERE \"Citation_Key\" = \"%1\"").arg(DatabaseFileName));
    QStringList values;
    while(FileBibliographyQuery.next()){
        QSqlRecord record = FileBibliographyQuery.record();
        for(int i=0; i < record.count(); i++)
        {
            values << record.value(i).toString();
            if(i>1){
                BibLineEditList.at(i-2)->setText(record.value(i).toString());
            }
        }
    }
    ui->CitationKeyLine->setText(DatabaseFileName);
    if(values.count()>0){
        if(bibNames.contains(values.at(1)) && !values.at(1).isEmpty()){
            int doctype = bibNames.indexOf(values.at(1));
            ui->DocumentTypeCombo->setCurrentText(bibDescriptions.at(doctype));
            mapBibliographyValues.insert(Bibliography_Ids.at(0),values.at(0));
            mapBibliographyValues.insert(Bibliography_Ids.at(1),values.at(1));
        }
    }
    else{
        ui->DocumentTypeCombo->setCurrentText(bibDescriptions.last());
        mapBibliographyValues.insert(Bibliography_Ids.at(0),DatabaseFileName);
        mapBibliographyValues.insert(Bibliography_Ids.at(1),bibDescriptions.last());
    }
    for (int item=2;item<Bibliography_Ids.count();item++) {
        mapBibliographyValues.insert(Bibliography_Ids.at(item),BibLineEditList.at(item-2)->text());
    }
}

void EditDataBaseFiles::loadImageFile(QString exoFile)
{
    if (exoFile.isEmpty()) {
        return;}
    QString pdfFile = "file:///"+exoFile.replace(".tex",".pdf");
//    view->open(QUrl(pdfFile));
}

void EditDataBaseFiles::FileEdit_Changed()
{
    ui->SaveTextButton->setEnabled(true);
    ui->ResetButton->setEnabled(true);
}

void EditDataBaseFiles::on_SaveTextButton_clicked()
{
    FileContent = ui->FileEdit->toPlainText();
    QFile file(DatabaseFilePath);
    file.resize(0);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream Grammh(&file);
    Grammh << FileContent;
    file.close();
    ui->SaveTextButton->setEnabled(false);
    ui->ResetButton->setEnabled(false);
    Texstudio::SaveContentToDatabase(DatabaseFileName,FileContent);
}

void EditDataBaseFiles::on_ResetButton_clicked()
{
    ui->FileEdit->setText(FileContent);
    ui->SaveTextButton->setEnabled(false);
    ui->ResetButton->setEnabled(false);
}

void EditDataBaseFiles::Filter_textChanged()
{
    updateTableView(ui->FilesTable,QString("SELECT \"df\".\"Id\" AS 'Name',\"ft\".\"FileType\" AS 'File type',\"f\".\"Name\" AS 'Field',"
"\"c\".\"Name\" AS 'Chapter', "
"replace(group_concat(s.Name),',','-') AS 'Section',\"se\".\"Exercise_Name\" AS 'Exercise type',"
"\"df\".\"Path\" AS 'Path',\"df\".\"Difficulty\" AS 'Difficulty',"
"\"df\".\"Date\" AS 'Date',\"df\".\"Solved\" AS 'Solved'"
"FROM \"Database_Files\" \"df\" JOIN \"FileTypes\" ft ON \"ft\".\"Id\" = \"df\".\"FileType\" "
"JOIN \"Fields\" \"f\" ON \"f\".\"Id\" = \"df\".\"Field\" LEFT JOIN \"Chapters\" \"c\" ON \"c\".\"Id\" = \"df\".\"Chapter\" "
"JOIN \"Sections\" \"s\" ON \"s\".\"Id\" = \"df\".\"Section\" "
"LEFT JOIN \"Sections_Exercises\" \"se\" ON \"se\".\"Exercise_Id\" = \"df\".\"ExerciseType\" "
"WHERE \"f\".\"Name\" LIKE \"%%1%\" "
"AND (\"c\".\"Name\" LIKE \"%%2%\" OR \"df\".\"Chapter\" ISNULL) "
"AND \"s\".\"Name\" LIKE \"%%3%\" "
"AND (\"se\".\"Exercise_Name\" LIKE \"%%4%\" OR \"df\".\"ExerciseType\" ISNULL) "
"AND \"ft\".\"FileType\" LIKE \"%%5%\" "
"GROUP BY df.Id "
"ORDER BY df.rowid;").arg(ui->FieldFilter->text(),ui->ChapterFilter->text(),
                                           ui->SectionFilter->text(),ui->ExerciseFilter->text()
                                           ,ui->FileTypeFilter->text()));
}

void EditDataBaseFiles::on_AddFileToBaseButton_clicked()
{
    QString newfile = QFileDialog::getOpenFileName(this,tr("Select TeX File"),QDir::homePath(),"tex Files (*.tex)");
    QFile file(newfile);
    file.open(QIODevice::ReadOnly);
    QTextStream text(&file);
    text.flush();
    FileContent = text.readAll();
    file.close();
    qDebug()<<FileContent;
    MetadataDialog = new QDialog(this);
    layout = new QGridLayout(this);
    QLabel * Title = new QLabel(tr("Select metadata for %1").arg(QFileInfo(newfile).fileName()),this);
    QFont font = Title->font();
    font.setPointSize(11);
    font.setBold(true);
    Title->setFont(font);
    layout->addWidget(Title,0,0,1,2);

    QLabel * SectionsLabel = new QLabel(tr("Sections"),this);
    QFont font2 = SectionsLabel->font();
    font2.setBold(true);
    SectionsLabel->setFont(font2);
    layout->addWidget(SectionsLabel,0,3);

    QLabel * ContentLabel = new QLabel(tr("Content of file %1").arg(QFileInfo(newfile).fileName()),this);
    QFont font3 = ContentLabel->font();
    font3.setBold(true);
    ContentLabel->setFont(font3);
    layout->addWidget(ContentLabel,0,5);

    IdLine = new QLineEdit(this);
    FieldCombo = new QComboBox(this);
    ChapterCombo = new QComboBox(this);
    ExerciseTypeCombo = new QComboBox(this);
    FileTypeCombo = new QComboBox(this);
    DifficultySpin = new QSpinBox(this);
    PathLine = new QLineEdit;
    DateTimeEdit = new QDateTimeEdit(this);
    SolvedLine = new QLineEdit(this);
    MetadataOkButton = new QDialogButtonBox(this);
    MetaWidgets<<IdLine<<FileTypeCombo<<FieldCombo<<ChapterCombo<<ExerciseTypeCombo
              <<DifficultySpin<<PathLine<<DateTimeEdit<<SolvedLine;
    MetadataDialog->setLayout(layout);
    for (int i=0;i<Basic_Metadata_Ids.size();i++) {
        MetadataMap.insert(Basic_Metadata_Ids.at(i),Basic_Metadata_Names.at(i));
        QLabel * label = new QLabel(Basic_Metadata_Names.at(i),this);
        layout->addWidget(label,i+1,0);
        layout->addWidget(MetaWidgets.at(i),i+1,1);
    }
    QSpacerItem * vspacer = new QSpacerItem(40, 20, QSizePolicy::Minimum,QSizePolicy::Expanding);
    layout->addItem(vspacer,Basic_Metadata_Ids.count()+2,1);
    MetadataOkButton->addButton(QDialogButtonBox::Ok);
    MetadataOkButton->addButton(QDialogButtonBox::Cancel);
    MetadataOkButton->addButton(QDialogButtonBox::Reset);
    layout->addWidget(MetadataOkButton,Basic_Metadata_Ids.count()+3,5);
    layout->setMargin(19);
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    QFrame *line2 = new QFrame(this);
    line2->setFrameShape(QFrame::VLine);
    layout->addWidget(line,1,2,Basic_Metadata_Ids.count()+1,1);
    layout->addWidget(line2,1,4,Basic_Metadata_Ids.count()+1,1);

    SectionsList = new QListWidget(this);
    layout->addWidget(SectionsList,1,3,Basic_Metadata_Ids.count()+1,1);
    SectionsList->setMinimumWidth(300);

    FileText = new QTextEdit(this);
    layout->addWidget(FileText,1,5,Basic_Metadata_Ids.count()+1,1);
    FileText->setText(FileContent);

    IdLine->setReadOnly(true);
    PathLine->setReadOnly(true);
    ChapterCombo->setEnabled(false);
    ExerciseTypeCombo->setEnabled(false);
    FieldCombo->setEnabled(false);
    DifficultySpin->setMinimum(1);
    DifficultySpin->setAlignment(Qt::AlignRight);
    DateTimeEdit->setDateTime(QDateTime::QDateTime::currentDateTime());
    DateTimeEdit->setDisplayFormat("dd/M/yyyy hh:mm");
    DateTimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    DateTimeEdit->setCalendarPopup(true);
    DateTimeEdit->setAlignment(Qt::AlignRight);
    SolvedLine->setText(tr("NO"));
    SolvedLine->setAlignment(Qt::AlignRight);
        FileTypeCombo->setEnabled(true);
        FileTypeCombo->clear();
        QList<QStringList> data =
                SqlFunctions::ComboList_Double_List("SELECT \"FileType\",\"Id\""
                                    "FROM \"FileTypes\"",currentbase);
        for (int item=0;item<data[0].count() ;item++ ) {
            FileTypeCombo->addItem(data[0].at(item),QVariant(data[1].at(item)));
        }
        FileTypeCombo->setCurrentIndex(-1);
    connect(FieldCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(FieldChanged()));
    connect(ChapterCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(ChapterChanged()));
    connect(SectionsList, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(SectionChanged(QListWidgetItem*)));
    connect(ExerciseTypeCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(ExerciseTypeChanged()));
    connect(FileTypeCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(FileTypeChanged()));
    connect(MetadataOkButton,SIGNAL(accepted()),this,SLOT(OkAccept()));
    connect(MetadataOkButton,SIGNAL(rejected()),this,SLOT(OkReject()));
    MetadataDialog->exec();
}

void EditDataBaseFiles::OkAccept()
{
    QString meta_Ids = Basic_Metadata_Ids.join("\",\"");
    QStringList Values;
    QStringList SectionList;
    Values << IdLine->text()<<FileTypeCombo->currentData().toString()<<FieldCombo->currentData().toString()
                <<ChapterCombo->currentData().toString()
               <<ExerciseTypeCombo->currentData().toString()
               <<DifficultySpin->text()
               <<PathLine->text()<<DateTimeEdit->text()<<SolvedLine->text();

    for(int i=0;i<SectionsList->count();i++){
        if(SectionsList->item(i)->data(Qt::CheckStateRole) == Qt::Checked){
            SectionList.append(SectionsList->item(i)->data(Qt::UserRole).toString());
        }
    }
    QString meta_Values = Values.join("\",\"");
    QStringList WriteValues;
    foreach(QString section,SectionList){
        WriteValues.append("(\""+meta_Values+"\",\""+section+"\")");
    }
    QSqlQuery writeExercise(currentbase);
    writeExercise.prepare("INSERT INTO \"Database_Files\" "
        "(\""+meta_Ids+"\",\"Section\")"
        "VALUES "+WriteValues.join(",")+";");
    writeExercise.exec();
    qDebug()<<meta_Ids<<WriteValues;
    QString text;
    QDir dir(QFileInfo(PathLine->text()).absolutePath());
    if (!dir.exists()) dir.mkpath(".");
    QFile file(PathLine->text());
    file.open(QIODevice::ReadWrite);
    text = "%# Database File : "+QFileInfo(PathLine->text()).baseName()+"\n";
    text += FileText->toPlainText()+"\n";
    text += "%# End of file "+QFileInfo(PathLine->text()).baseName();
    QTextStream content(&file);
    content <<text;
    file.close();
    MetadataDialog->accept();
    ShowDataBaseFiles();
}

void EditDataBaseFiles::OkReject()
{
    MetadataDialog->reject();
}

void EditDataBaseFiles::FileTypeChanged()
{
    FieldCombo->setEnabled(true);
    FieldCombo->clear();
    QSqlQuery fields(currentbase);
    fields.exec(SqlFunctions::Fields_Query);
    while(fields.next()){
        FieldCombo->addItem (fields.value(0).toString(),QVariant(fields.value(1).toString()));
    }
    FieldCombo->setCurrentIndex(-1);
    if(FileTypeCombo->currentIndex()<4){
        ExerciseTypeCombo->setEnabled(false);
        ExerciseType = "-";
        SolvedLine->setText("-");
    }
    else{ExerciseTypeCombo->setEnabled(true);}
}

void EditDataBaseFiles::FieldChanged()
{
    if(FieldCombo->currentIndex()>-1){
    ChapterCombo->setEnabled(true);
    ChapterCombo->clear();
    QList<QStringList> data =
            SqlFunctions::ComboList_Single(SqlFunctions::Chapters_Query,currentbase,
                                           FieldCombo->currentText());
    for (int item=0;item<data[0].count() ;item++ ) {
        ChapterCombo->addItem(data[0].at(item),QVariant(data[1].at(item)));
    }
    ChapterCombo->setCurrentIndex(-1);}
}

void EditDataBaseFiles::ChapterChanged()
{
    SectionsList->clear();
    QList<QStringList> data2;
    if(ChapterCombo->currentIndex()>-1){
        if(FileTypeCombo->currentIndex()<12){
            data2 = SqlFunctions::ComboList_Single(SqlFunctions::Sections_Chapters_Query,currentbase,
                                                              ChapterCombo->currentText());
        }
        else {data2 = SqlFunctions::ComboList_Single(SqlFunctions::Sections_Query,currentbase,
                                                     FieldCombo->currentData().toString());
            ExerciseTypeCombo->clear();
            ExerciseTypeCombo->setEnabled(false);
        }
    for (int i=0;i<data2[0].count() ;i++ ) {
        SectionsList->addItem(data2[0].at(i));
        SectionsList->item(i)->setData(Qt::UserRole,data2[1].at(i));
        SectionsList->item(i)->setFlags(SectionsList->item(i)->flags() | Qt::ItemIsUserCheckable);
        SectionsList->item(i)->setCheckState(Qt::Unchecked);
        }
    }
}

void EditDataBaseFiles::SectionChanged(QListWidgetItem * sectionitem)
{
    if(sectionitem == nullptr)
            return;
    if(sectionitem->checkState() == Qt::Checked || sectionitem->isSelected())
    {
        sectionitem->setSelected(true);
        int previousrow = currentSectionRow;
        currentSectionRow = SectionsList->row(sectionitem);
        if(FileTypeCombo->currentIndex()<12){
            if(previousrow>-1){
                SectionsList->item(previousrow)->setData(Qt::CheckStateRole, Qt::Unchecked);
                sectionitem->setData(Qt::CheckStateRole, Qt::Checked);
            }
            else if(previousrow==-1){sectionitem->setData(Qt::CheckStateRole, Qt::Checked);}
        }
        else {sectionitem->setData(Qt::CheckStateRole, Qt::Checked);}
        ExerciseTypeCombo->setEnabled(true);
        ExerciseTypeCombo->clear();
        if(SectionsList->currentRow()>-1 && !sectionitem->text().isEmpty())
        {
            QList<QStringList> data =
                SqlFunctions::ComboList_Single(SqlFunctions::Exercise_Types_Query,currentbase,
                                               sectionitem->data(Qt::UserRole).toString());
            for (int item=0;item<data[0].count() ;item++ ) {
                ExerciseTypeCombo->addItem(data[0].at(item),QVariant(data[1].at(item)));
            }
        ExerciseTypeCombo->setCurrentIndex(-1);
        }
    }
}

void EditDataBaseFiles::ExerciseTypeChanged()
{
    if(ExerciseTypeCombo->currentIndex()!=-1){
        QString folder;
        QSqlQuery folderQuery(currentbase);
        folderQuery.exec(SqlFunctions::FolderName.arg(FileTypeCombo->currentData().toString()));
        while(folderQuery.next()){
            folder=folderQuery.value(0).toString();
        }
        QStringList SectionNamesList;
        QStringList SectionIdsList;
        for(int i=0;i<SectionsList->count();i++){
            if(SectionsList->item(i)->data(Qt::CheckStateRole) == Qt::Checked){
                SectionNamesList.append(SectionsList->item(i)->text());
                SectionIdsList.append(SectionsList->item(i)->data(Qt::UserRole).toString());
            }
        }
        QString SectionsName = SectionNamesList.join("-");
        QString SectionsId = SectionIdsList.join("-");
        IdLine->setText(FieldCombo->currentData().toString().left(3)+"-"+
                        ChapterCombo->currentData().toString()+"-"+
                        SectionsId+"-"+
                        ExerciseTypeCombo->currentData().toString()+"-"+
                        FileTypeCombo->currentData().toString()+".tex");
        PathLine->setText(QFileInfo(Texstudio::CurrentDataBasePath).absolutePath()+QDir::separator()+
                          FieldCombo->currentText()+QDir::separator()+"Ενότητες"+QDir::separator()+SectionsName+
                          QDir::separator()+folder
                          +QDir::separator()+ExerciseTypeCombo->currentText()+
                          QDir::separator()+IdLine->text());
        }
}

void EditDataBaseFiles::on_DeleteFileFromBaseButton_clicked()
{
    QCheckBox *cb = new QCheckBox(tr("Delete File"));
        QMessageBox msgbox;
        msgbox.setText(tr("Do you want to remove ;\n the file %1").arg(DatabaseFileName));
        msgbox.setIcon(QMessageBox::Icon::Question);
        msgbox.addButton(QMessageBox::Ok);
        msgbox.addButton(QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Cancel);
        msgbox.setCheckBox(cb);
    if (msgbox.exec() == QMessageBox::Ok) {
        QSqlQuery deleteQuery(currentbase);
        deleteQuery.exec(QString("DELETE FROM \"Database_Files\" WHERE \"Id\" = \"%1\"").arg(DatabaseFileName));
        ShowDataBaseFiles();
     if(cb->isChecked()==true){QDesktopServices::openUrl(QUrl("file:///"+QFileInfo(DatabaseFilePath).absolutePath()));}
    }
}

void EditDataBaseFiles::on_EditMetadataButton_clicked()
{

}

void EditDataBaseFiles::on_ComboCount_currentIndexChanged(int index)
{
    updateTableView(ui->CountFilesTable,ui->ComboCount->currentData().toString());
}

void EditDataBaseFiles::on_EditBibButton_clicked()
{
    for (int item=0;item<BibLineEditList.count();item++) {
        BibLineEditList.at(item)->setReadOnly(false);
    }
}

void EditDataBaseFiles::on_SaveBibliographyButton_clicked()
{
    QSqlQuery WriteBibliography(currentbase);
    QStringList setList;
    setList.append("\""+Bibliography_Ids.at(0)+"\" = \""+ui->CitationKeyLine->text()+"\"");
    setList.append("\""+Bibliography_Ids.at(1)+"\" = \""+ui->DocumentTypeCombo->currentData().toString()+"\"");
    for (int item=2;item<Bibliography_Ids.count();item++) {
        setList.append("\""+Bibliography_Ids.at(item)+"\" = \""+BibLineEditList.at(item-2)->text()+"\"");
        BibLineEditList.at(item-2)->setReadOnly(true);
    }
    QString query = "UPDATE \"Bibliography\" SET "+setList.join(",")+" WHERE \"Citation_Key\" = \"%1\"";
    WriteBibliography.exec(QString(query).arg(DatabaseFileName));
}

void EditDataBaseFiles::on_BuildButton_clicked()
{
    Texstudio::createPdf(DatabaseFilePath);
    loadImageFile(DatabaseFilePath);
}

void EditDataBaseFiles::on_OpenInEditorButton_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+DatabaseFilePath));
}
