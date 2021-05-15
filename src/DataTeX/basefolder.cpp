#include "basefolder.h"
#include "ui_basefolder.h"
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include "sqlfunctions.h"
#include  <QWizardPage>
#include <QHeaderView>
#include "texstudio.h"

QStringList BaseFolder::fields;
QStringList BaseFolder::bibfields;
QStringList BaseFolder::FieldTypesValues;
QStringList BaseFolder::BibTypesValues;
QList<QCheckBox *> DataPage::newCheckList;
QList<QLineEdit *> DataPage::newlabelList;
QList<QLineEdit * >  DataPage::newFieldLineList;
QList<int> DataPage::addedIdList;
QList<int> DataPage::removedIdList;

QList<QCheckBox *> BibliographyPage::newBibCheckList;
QList<QLineEdit *> BibliographyPage::newBiblabelList;
QList<QLineEdit * >  BibliographyPage::newBibLineList;
QList<int> BibliographyPage::addedBibIdList;
QList<int> BibliographyPage::removedBibIdList;
QList<QComboBox *> DataPage::newcomboList = QList<QComboBox *>();
QList<QComboBox *> BibliographyPage::newcomboList = QList<QComboBox *>();
QStringList BaseFolder::Metadata;
QStringList BaseFolder::BibData;
QStringList BaseFolder::MetadataNames;
QStringList BaseFolder::BibDataNames;

/* CODE BELONGS TO Gwenaël Cléon FROM THE PROGRAM TeXoMaker  */
BaseFolder::BaseFolder(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::BaseFolder)
{
    BaseFolder::fields.clear();
    BaseFolder::FieldTypesValues.clear();
    DataPage::newlabelList.clear();
    DataPage::newFieldLineList.clear();
    DataPage::newCheckList.clear();
    DataPage::newcomboList.clear();
    BibliographyPage::newBibCheckList.clear();
    BibliographyPage::newBibLineList.clear();
    BibliographyPage::newBiblabelList.clear();
    BaseFolder::bibfields.clear();
    BaseFolder::BibTypesValues.clear();

    addPage(new InfoPage);
    addPage(new DataPage);
    addPage(new BibliographyPage);
    addPage(new FinalPage);
    setWindowTitle("New Database");
}

InfoPage::InfoPage(QWidget *parent)
    : QWizardPage(parent)
{
    QSqlQuery DatabaseListQuery(Texstudio::DataTeX_Settings);
    DatabaseListQuery.exec("SELECT \"FileName\" FROM \"Databases\"");
    while (DatabaseListQuery.next()) {
        DatabaseList.append(DatabaseListQuery.value(0).toString());
    }
    setTitle("Create new Database");
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images-ng/datatex.png"));
    QLabel *label = new QLabel("This wizard will help you create a new LaTeX database for TeXStudio.");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    QLabel * DatabasePathLabel = new QLabel("DataBase Path",this);
    DatabasePath = new QLineEdit(this);
    QLabel * DatabaseFileNameLabel = new QLabel("DataBase file name",this);
    DatabaseFileName = new QLineEdit(this);
    QLabel * DatabaseNameLabel = new QLabel("DataBase name - Short Description",this);
    DatabaseName = new QLineEdit(this);
    DatabasePathButton = new QPushButton("Path",this);
    layout->addWidget(label);
    hlayout->addWidget(DatabasePathLabel);
    hlayout->addWidget(DatabasePath);
    hlayout->addWidget(DatabasePathButton);
    layout->addLayout(hlayout);
    hlayout2->addWidget(DatabaseFileNameLabel);
    hlayout2->addWidget(DatabaseFileName);
    layout->addLayout(hlayout2);
    hlayout3->addWidget(DatabaseNameLabel);
    hlayout3->addWidget(DatabaseName);
    layout->addLayout(hlayout3);
    CheckDatabaseName = new QLabel(this);
    QFont font = CheckDatabaseName->font();
    font.setPointSize(11);
    font.setBold(true);
    CheckDatabaseName->setFont(font);
    CheckDatabaseName->setStyleSheet("QLabel {color : red; }");
    layout->addWidget(CheckDatabaseName);
    setLayout(layout);
    registerField("DataΒaseFileName*", DatabaseFileName);
    registerField("DataBasePath*", DatabasePath);
    registerField("DataBaseName*", DatabaseName);
    connect(DatabasePathButton,&QPushButton::pressed,this,&InfoPage::Database_Path);
    setMinimumHeight(400);
    setMinimumWidth(700);
    layout->addStretch();
    connect(DatabaseFileName,&QLineEdit::textChanged,this, &InfoPage::CheckDatabase);
}

void InfoPage::CheckDatabase()
{
    if(DatabaseList.contains(DatabaseFileName->text())){
        CheckDatabaseName->setText(tr("The database %1 already exists.").arg(DatabaseFileName->text()));
        wizard()->button(QWizard::NextButton)->setEnabled(false);
    }
    else{
        CheckDatabaseName->clear();
    }
}

void InfoPage::Database_Path()
{
    QString path = QFileDialog::getExistingDirectory(this,"Select a folder for your new database",QDir::homePath());
    DatabasePath->setText(path);
}

DataPage::DataPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Database fields");
        QLabel *label = new QLabel("Below you can see the basic fields of the Database files table."
                                   "Select a name for each field of your new database."
                                   "Add new custom fields by selecting an id, a name and a type.");
        label->setWordWrap(true);

        QVBoxLayout *layout2 = new QVBoxLayout;
        layout2->addWidget(label);
        /*page->*/setLayout(layout2);
        DataLayout = new QGridLayout;
        QWidget *client = new QWidget;

        QScrollArea *scrollArea = new QScrollArea;
        layout2->addWidget(scrollArea);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(client);
        client->setLayout(DataLayout);

        QSqlQuery Select_DataBase_Metadata(Texstudio::DataTeX_Settings);
        Select_DataBase_Metadata.exec(QString("SELECT \"Id\",\"Name\" FROM \"Metadata\" WHERE \"Basic\"=1;"));
        while(Select_DataBase_Metadata.next()){
            BasicDataBaseFields.append(Select_DataBase_Metadata.value(0).toString());
            BasicDataBaseValues.append(Select_DataBase_Metadata.value(1).toString());
        }

        FieldTypes <<"TEXT"<<"INTEGER"<<"BLOB"<<"REAL"<<"NUMERIC";

        QFrame* hFrame = new QFrame;
        hFrame->setFrameShape(QFrame::HLine);
        DataLayout->addWidget(hFrame,0,0,1,2);
        DataLayout->addWidget(new QLabel(tr("Πεδίο")),1,0);
        DataLayout->addWidget(new QLabel(tr("Όνομα πεδίου")),1,1);
        DataLayout->addWidget(hFrame,2,0,1,2);

        for (int i=0;i<BasicDataBaseFields.size();i++) {
            QLabel * label = new QLabel(BasicDataBaseFields.at(i),this);
            CheckFieldId = new QLabel(this);
            QLineEdit * line = new QLineEdit(this);
            QComboBox * combo = new QComboBox(this);
            labelList.append(label);
            lineList.append(line);
            line->setMinimumWidth(400);
            combo->addItems(FieldTypes);
            combo->setEnabled(false);
            basiccomboList.append(combo);
            labelList.at(i)->setBuddy(lineList.at(i));
            DataLayout->addWidget(basiccomboList.at(i),i+3,2);
            BaseFolder::fields.append(label->text());
            QString rlabel = label->text();
            registerField(rlabel, line);
            QString rcombo = "Combo"+label->text();
            BaseFolder::FieldTypesValues.append(rcombo);
            registerField(rcombo, combo,"currentText", "currentTextChanged");
            DataLayout->addWidget(labelList.at(i),i+3,0);
            DataLayout->addWidget(lineList.at(i),i+3,1);
            lineList.at(i)->setText(BasicDataBaseValues.at(i));
        }
        basiccomboList.at(6)->setCurrentIndex(1);
        AddFieldButton = new QPushButton(this);
        RemoveFieldButton = new QPushButton(this);
        AddFieldButton->setIcon(QIcon::fromTheme("list-add"));
        RemoveFieldButton->setIcon(QIcon::fromTheme("list-remove"));
        QHBoxLayout *layout3 = new QHBoxLayout;
        layout2->addLayout(layout3);
        layout3->addWidget(AddFieldButton);
        layout3->addWidget(RemoveFieldButton);
        layout3->addWidget(CheckFieldId);
        layout3->addStretch();
        setMinimumHeight(400);
        setMinimumWidth(700);
        connect(AddFieldButton,SIGNAL(clicked()),this,SLOT(AddField()));
        connect(RemoveFieldButton,SIGNAL(clicked()),this,SLOT(RemoveField()));
        optfield = -1;
}

void DataPage::AddField()
{
    optfield++;
    DataPage::addedIdList.append(optfield);
    int basicFields = BasicDataBaseFields.count();
    int newlabels = DataPage::newlabelList.count();
    QLineEdit * line1 = new QLineEdit(this);
    QLineEdit * line2 = new QLineEdit(this);
    QComboBox * combo = new QComboBox(this);
    QHBoxLayout *hlayout = new QHBoxLayout;
    QCheckBox * check = new QCheckBox(this);
    line1->setPlaceholderText(tr("New field"));
    line2->setPlaceholderText(tr("Type the field's name"));
    line1->setClearButtonEnabled(true);
    line2->setClearButtonEnabled(true);
    DataLayout->addLayout(hlayout,basicFields+newlabels+3,0);
    hlayout->addWidget(check);
    hlayout->addWidget(line1);
    DataLayout->addWidget(line2,basicFields+newlabels+3,1);
    DataLayout->addWidget(combo,basicFields+newlabels+3,2);
    combo->addItems(FieldTypes);
    QString rlabel = "optField_"+QString::number(optfield)+"*";
    registerField(rlabel, line1);
    QString rlabel2 = "optValue_"+QString::number(optfield)+"*";
    registerField(rlabel2, line2);
    QString rcombo = "optCombo_"+QString::number(optfield);
    BaseFolder::FieldTypesValues.append(rcombo);
    registerField(rcombo, combo,"currentText",SIGNAL(currentIndexChanged(QString)));
    newlabelList.append(line1);
    newFieldLineList.append(line2);
    newCheckList.append(check);
    newcomboList.append(combo);
    checkGroup->addButton(check);
    checkGroup->setExclusive(false);
    check->setProperty("Id",optfield);
    for (int i=0;i<newlabelList.count();i++ ) {
        connect(newlabelList.at(i), &QLineEdit::textChanged, this, &DataPage::CheckNewField);
        connect(newlabelList.at(i), &QLineEdit::textChanged, this, &DataPage::CheckNext);
        connect(newFieldLineList.at(i), &QLineEdit::textChanged, this, &DataPage::CheckNext);
    }
    wizard()->button(QWizard::NextButton)->setEnabled(false);
}

void DataPage::CheckNewField(QString text)
{
    QSet<QString> NoDuplicates;
    FieldList.clear();
    NoDuplicates.clear();
    for (int i=0;i<newlabelList.count();i++) {
        FieldList.append(newlabelList.at(i)->text());
        NoDuplicates.insert(newlabelList.at(i)->text());
    }
    if(BaseFolder::fields.contains(text) || NoDuplicates.count()<newlabelList.count()){
        next = false;
        CheckFieldId->setText(tr("The field %1 already exists.").arg(text));
        wizard()->button(QWizard::NextButton)->setEnabled(false);
    }
    else{
        next = true;
        CheckFieldId->clear();
    }
    qDebug()<<FieldList<<NoDuplicates;
}

void DataPage::CheckNext()
{
    for (int i=0;i<newlabelList.count();i++) {
        if(newlabelList.at(i)->text().isEmpty() || newFieldLineList.at(i)->text().isEmpty() || next==false){
            wizard()->button(QWizard::NextButton)->setEnabled(false);
        }
        else{wizard()->button(QWizard::NextButton)->setEnabled(true);}
    }
}

void DataPage::RemoveField()
{
    QList<int> CheckIdList;
    for (int i=DataPage::newCheckList.count()-1;i>-1;i--) {
        if(DataPage::newCheckList.at(i)->isChecked()){
            CheckIdList.append(i);
            DataPage::removedIdList.append(DataPage::newCheckList.at(i)->property("Id").toInt());
        }
    }
    foreach(int i,CheckIdList) {
            DataLayout->removeWidget(DataPage::newlabelList.at(i));
            DataLayout->removeWidget(DataPage::newFieldLineList.at(i));
            DataLayout->removeWidget(DataPage::newCheckList.at(i));
            DataLayout->removeWidget(newcomboList.at(i));
            delete DataPage::newCheckList.takeAt(i);
            delete newlabelList.takeAt(i);
            delete DataPage::newFieldLineList.takeAt(i);
            delete newcomboList.takeAt(i);
        }
}

BibliographyPage::BibliographyPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Bibliography fields");
        QLabel *label = new QLabel("Select...");
        label->setWordWrap(true);
        QVBoxLayout *layout2 = new QVBoxLayout;
        layout2->addWidget(label);
        setLayout(layout2);
        CheckFieldId = new QLabel(this);
        BibliographyLayout = new QGridLayout;
        QWidget *client = new QWidget;
        QScrollArea *scrollArea = new QScrollArea;
        layout2->addWidget(scrollArea);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(client);
        client->setLayout(BibliographyLayout);
        FieldTypes <<"TEXT"<<"INTEGER"<<"BLOB"<<"REAL"<<"NUMERIC";
        QSqlQuery Select_DataBase_Metadata(Texstudio::DataTeX_Settings);
        Select_DataBase_Metadata.exec(QString("SELECT \"Id\",\"Name\" FROM \"Bibliography\" WHERE \"Basic\"=1"));
        while(Select_DataBase_Metadata.next()){
            BasicBibliographyFields.append(Select_DataBase_Metadata.value(0).toString());
            BasicBibliographyValues.append(Select_DataBase_Metadata.value(1).toString());
        }
        QFrame* hFrame = new QFrame;
        hFrame->setFrameShape(QFrame::HLine);
        BibliographyLayout->addWidget(hFrame,0,0,1,2);
        BibliographyLayout->addWidget(new QLabel(tr("Πεδίο")),1,0);
        BibliographyLayout->addWidget(new QLabel(tr("Όνομα πεδίου")),1,1);
        BibliographyLayout->addWidget(hFrame,2,0,1,2);

        for (int i=0;i<BasicBibliographyFields.size();i++) {
            QLabel * label = new QLabel(BasicBibliographyFields.at(i),this);
            QLineEdit * line = new QLineEdit(this);
            QComboBox * combo = new QComboBox(this);
            labelList.append(label);
            lineList.append(line);
            line->setMinimumWidth(400);
            combo->addItems(FieldTypes);
            combo->setEnabled(false);
            basiccomboList.append(combo);
            labelList.at(i)->setBuddy(lineList.at(i));
            BibliographyLayout->addWidget(basiccomboList.at(i),i+3,2);
            BaseFolder::bibfields.append(label->text());
            QString rlabel = "Bib_"+label->text();
            registerField(rlabel, line);
            QString rcombo = "Bib_Combo"+label->text();
            BaseFolder::BibTypesValues.append(rcombo);
            registerField(rcombo, combo,"currentText", "currentTextChanged");
            BibliographyLayout->addWidget(labelList.at(i),i+3,0);
            BibliographyLayout->addWidget(lineList.at(i),i+3,1);
            lineList.at(i)->setText(BasicBibliographyValues.at(i));
        }
        basiccomboList.at(6)->setCurrentIndex(1);
        basiccomboList.at(7)->setCurrentIndex(1);
        basiccomboList.at(10)->setCurrentIndex(1);
        AddBibTexButton = new QPushButton(this);
        RemoveBibTexButton = new QPushButton(this);
        AddBibTexButton->setIcon(QIcon::fromTheme("list-add"));
        RemoveBibTexButton->setIcon(QIcon::fromTheme("list-remove"));
        QHBoxLayout *layout3 = new QHBoxLayout;
        layout2->addLayout(layout3);
        layout3->addWidget(AddBibTexButton);
        layout3->addWidget(RemoveBibTexButton);
        layout3->addWidget(CheckFieldId);
        layout3->addStretch();
        setMinimumHeight(400);
        setMinimumWidth(700);
        connect(AddBibTexButton,SIGNAL(clicked()),this,SLOT(AddBibField()));
        connect(RemoveBibTexButton,SIGNAL(clicked()),this,SLOT(RemoveBibField()));
        optfield = -1;
}

void BibliographyPage::AddBibField()
{
    optfield++;
    BibliographyPage::addedBibIdList.append(optfield);
    int basicFields = BasicBibliographyFields.count();
    int newlabels = BibliographyPage::newBiblabelList.count();
    QLineEdit * line1 = new QLineEdit(this);
    QLineEdit * line2 = new QLineEdit(this);
    QComboBox * combo = new QComboBox(this);
    QHBoxLayout *hlayout = new QHBoxLayout;
    QCheckBox * check = new QCheckBox(this);
    line1->setPlaceholderText(tr("New field"));
    line2->setPlaceholderText(tr("Type the field's name"));
    line1->setClearButtonEnabled(true);
    line2->setClearButtonEnabled(true);
    BibliographyLayout->addLayout(hlayout,basicFields+newlabels+3,0);
    hlayout->addWidget(check);
    hlayout->addWidget(line1);
    BibliographyLayout->addWidget(line2,basicFields+newlabels+3,1);
    BibliographyLayout->addWidget(combo,basicFields+newlabels+3,2);
    combo->addItems(FieldTypes);
//    fields.append(label->text());
    QString rlabel = "optBibField_"+QString::number(optfield)+"*";
    registerField(rlabel, line1);
    QString rlabel2 = "optBibValue_"+QString::number(optfield)+"*";
    registerField(rlabel2, line2);
    QString rcombo = "optBibCombo_"+QString::number(optfield);
    BaseFolder::BibTypesValues.append(rcombo);
    registerField(rcombo, combo,"currentText",SIGNAL(currentIndexChanged(QString)));
    newBiblabelList.append(line1);
    newBibLineList.append(line2);
    newBibCheckList.append(check);
    newcomboList.append(combo);
    checkGroup->addButton(check);
    checkGroup->setExclusive(false);
    check->setProperty("Id",optfield);
    for (int i=0;i<newBiblabelList.count();i++ ) {
        connect(newBiblabelList.at(i), &QLineEdit::textChanged, this, &BibliographyPage::CheckNewBibField);
        connect(newBiblabelList.at(i), &QLineEdit::textChanged, this, &BibliographyPage::CheckNext);
        connect(newBibLineList.at(i), &QLineEdit::textChanged, this, &BibliographyPage::CheckNext);
    }
    wizard()->button(QWizard::NextButton)->setEnabled(false);
}

void BibliographyPage::CheckNewBibField(QString text)
{
    QSet<QString> NoDuplicates;
    FieldList.clear();
    NoDuplicates.clear();
    for (int i=0;i<newBiblabelList.count();i++) {
        FieldList.append(newBiblabelList.at(i)->text());
        NoDuplicates.insert(newBiblabelList.at(i)->text());
    }
    if(BaseFolder::bibfields.contains(text) || NoDuplicates.count()<newBiblabelList.count()){
        next = false;
        CheckFieldId->setText(tr("The field %1 already exists.").arg(text));
        wizard()->button(QWizard::NextButton)->setEnabled(false);
    }
    else{
        next = true;
        CheckFieldId->clear();
    }
}

void BibliographyPage::CheckNext()
{
    for (int i=0;i<newBiblabelList.count();i++) {
        if(newBiblabelList.at(i)->text().isEmpty() || newBibLineList.at(i)->text().isEmpty() || next==false){
            wizard()->button(QWizard::NextButton)->setEnabled(false);
        }
        else{wizard()->button(QWizard::NextButton)->setEnabled(true);}
    }
}

void BibliographyPage::RemoveBibField()
{
    QList<int> CheckIdList;
    for (int i=BibliographyPage::newBibCheckList.count()-1;i>-1;i--) {
        if(BibliographyPage::newBibCheckList.at(i)->isChecked()){
            CheckIdList.append(i);
            BibliographyPage::removedBibIdList.append(BibliographyPage::newBibCheckList.at(i)->property("Id").toInt());
        }
    }
    qDebug()<<CheckIdList<<newBibCheckList.count();
    foreach(int i,CheckIdList) {
            BibliographyLayout->removeWidget(BibliographyPage::newBiblabelList.at(i));
            BibliographyLayout->removeWidget(BibliographyPage::newBibLineList.at(i));
            BibliographyLayout->removeWidget(BibliographyPage::newBibCheckList.at(i));
            BibliographyLayout->removeWidget(newcomboList.at(i));
            delete BibliographyPage::newBibCheckList.takeAt(i);
            delete BibliographyPage::newBiblabelList.takeAt(i);
            delete BibliographyPage::newBibLineList.takeAt(i);
            delete newcomboList.at(i);
        }
}

FinalPage::FinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Database fields");
    NameLabel = new QLabel(this);
    PathLabel = new QLabel(this);
    FileNameLabel = new QLabel(this);
    label3 = new QLabel("Database Fields");
    QLabel * label4 = new QLabel("Bibliography Fields");
    QGridLayout * hlayout = new QGridLayout;
    table = new QTableWidget(this);
    table2 = new QTableWidget(this);
    layout = new QVBoxLayout;
    layout->addWidget(FileNameLabel);
    layout->addWidget(NameLabel);
    layout->addWidget(PathLabel);
    hlayout->addWidget(label3,0,0);
    hlayout->addWidget(label4,0,1);
    layout->addLayout(hlayout);
    hlayout->addWidget(table,1,0);
    hlayout->addWidget(table2,1,1);
    table->setColumnCount(3);
    QStringList horzHeaders;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setStyleSheet("alternate-background-color: #e8e8e8");
    horzHeaders << "Id"<<"Name"<<"Type";
    table->setHorizontalHeaderLabels(horzHeaders);
    table2->setColumnCount(3);
    table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table2->setAlternatingRowColors(true);
    table2->setStyleSheet("alternate-background-color: #e8e8e8");
    table2->setHorizontalHeaderLabels(horzHeaders);
    NameLabel->setWordWrap(true);
    PathLabel->setWordWrap(true);
    label3->setWordWrap(true);
    setLayout(layout);
}

void FinalPage::initializePage()
{
    BaseFolder::Metadata.clear();
    BaseFolder::BibData.clear();
    BaseFolder::MetadataNames.clear();
    BaseFolder::BibDataNames.clear();
    NameLabel->setText("Database Name : "+ field("DataBaseName").toString());
    FileNameLabel->setText("Database file name : "+ field("DataΒaseFileName").toString());
    PathLabel->setText("Database Path : "+field("DataBasePath").toString()
                       +QDir::separator()+field("DataBaseName").toString()
                       +QDir::separator()+field("DataΒaseFileName").toString()+".db");
    QStringList Names;
    table->setRowCount(0);
    for (int i=0;i<BaseFolder::fields.count();i++ ) {
        table->insertRow(i);
        table->setItem(i,0 , new QTableWidgetItem(BaseFolder::fields.at(i)));
        table->setItem(i,1 , new QTableWidgetItem(field(BaseFolder::fields.at(i)).toString()));
        table->setItem(i,2 , new QTableWidgetItem(field(BaseFolder::FieldTypesValues.at(i)).toString()));
    }
    table2->setRowCount(0);
    for (int i=0;i<BaseFolder::bibfields.count();i++ ) {
        table2->insertRow(i);
        table2->setItem(i,0 , new QTableWidgetItem(BaseFolder::bibfields.at(i)));
        table2->setItem(i,1 , new QTableWidgetItem(field("Bib_"+BaseFolder::bibfields.at(i)).toString()));
        table2->setItem(i,2 , new QTableWidgetItem(field(BaseFolder::BibTypesValues.at(i)).toString()));
    }

    QList<int> list;
    foreach(int i,DataPage::addedIdList){
        if(!DataPage::removedIdList.contains(i))
            list.append(i);
    }
    QList<int> biblist;
    foreach(int i,BibliographyPage::addedBibIdList){
        if(!BibliographyPage::removedBibIdList.contains(i))
            biblist.append(i);
    }

    for (int i=0;i<list.count();i++ ) {
        table->insertRow(BaseFolder::fields.count()+i);
        table->setItem(BaseFolder::fields.count()+i,0 , new QTableWidgetItem(field("optField_"+QString::number(list.at(i))).toString()));
        table->setItem(BaseFolder::fields.count()+i,1 , new QTableWidgetItem(field("optValue_"+QString::number(list.at(i))).toString()));
        table->setItem(BaseFolder::fields.count()+i,2 , new QTableWidgetItem(field("optCombo_"+QString::number(list.at(i))).toString()));
    }

    for (int c = 0; c < table->horizontalHeader()->count()-1; ++c)
    {
        table->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    for (int i=0;i<biblist.count();i++ ) {
        table2->insertRow(BaseFolder::bibfields.count()+i);
        table2->setItem(BaseFolder::bibfields.count()+i,0 , new QTableWidgetItem(field("optBibField_"+QString::number(biblist.at(i))).toString()));
        table2->setItem(BaseFolder::bibfields.count()+i,1 , new QTableWidgetItem(field("optBibValue_"+QString::number(biblist.at(i))).toString()));
        table2->setItem(BaseFolder::bibfields.count()+i,2 , new QTableWidgetItem(field("optBibCombo_"+QString::number(biblist.at(i))).toString()));
    }

    for (int c = 0; c < table2->horizontalHeader()->count()-1; ++c)
    {
        table2->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    for (int i=0;i<table->rowCount() ;i++ ) {
        BaseFolder::Metadata.append(table->item(i,0)->text());
        BaseFolder::MetadataNames.append(table->item(i,1)->text());
    }
    for (int i=0;i<table2->rowCount() ;i++ ) {
        BaseFolder::BibData.append(table2->item(i,0)->text());
        BaseFolder::BibDataNames.append(table2->item(i,1)->text());
    }
}

FinalPage::~FinalPage()
{
    delete table;
}

BaseFolder::~BaseFolder()
{
    delete ui;
}

DataPage::~DataPage()
{

}

BibliographyPage::~BibliographyPage()
{

}

void BaseFolder::accept()
{
    QString path = field("DataBasePath").toString();
    QString folderName = field("DataBaseName").toString();
    QString baseFileName = field("DataΒaseFileName").toString();
    QDir basedir(path+QDir::separator()+folderName+QDir::separator());
    if(!basedir.exists()){basedir.mkpath(".");}
    QString FullPath = path+QDir::separator()+folderName+QDir::separator()+baseFileName+".db";
    QSqlDatabase newdatabaseFile;
    newdatabaseFile = QSqlDatabase::addDatabase("QSQLITE","newbase");
    newdatabaseFile.setDatabaseName(FullPath);
    newdatabaseFile.open();

    SqlFunctions::ExecuteSqlScriptFile(newdatabaseFile,":/src/DataTeX/FilesDatabase.sql");
    QSqlQuery FiletypesQuery(newdatabaseFile);
    QStringList Filetypes = {"Definition","Theorem","Figure","Table","SectEx","SolSE","SectSub",
                             "SolSS","HintSE","HintSS","Method","Example","CombEx","SolCE","CombSub","SolCS","HintCE","HintCS"};
    QStringList FiletypesNames = {tr("Definition"),tr("Theorem"),tr("Figure"),tr("Table"),tr("Section exercise"),tr("Exercise solution"),
                                  tr("Section Subject"),tr("Subject solution"),tr("Exercise hint"),tr("Subject hint"),
                                  tr("Method"),tr("Example"),tr("Comb. exercise"),tr("Comb. exercise solution"),
                                  tr("Comb. subject"),tr("Comb. subject solution"),tr("Comb. exer. hint"),tr("Comb. subj. hint")};
    QStringList FolderNames = {tr("Definitions"),tr("Theorems"),tr("Figures"),tr("Tables"),tr("Exercises"),tr("Exercise solutions"),tr("Subjects"),
                             tr("Subjects solutions"),tr("Exercise hints"),tr("Subjects hints"),
                               tr("Methods"),tr("Examples"),tr("Comb. exercises"),tr("Comb. exercise solutions"),tr("Comb. subjects"),
                               tr("Comb. subj. solutions"),tr("Comb. exer. hints"),tr("Comb. subj. hints")};
    for (int i=0;i<Filetypes.count();i++ ) {
        QString Query = "INSERT INTO \"FileTypes\" (\"Id\", \"FileType\", \"FolderName\") VALUES (\""+Filetypes.at(i)+"\", \""+FiletypesNames.at(i)+"\", \""+FolderNames.at(i)+"\")";
        FiletypesQuery.exec(Query);
    }

    QSqlQuery AddExtraMetadata(newdatabaseFile);
    if(DataPage::newlabelList.count()>0){
        for (int i=0;i<DataPage::newlabelList.count();i++ ) {
            QString query = "ALTER TABLE \"Database_Files\" ADD \""+DataPage::newlabelList.at(i)->text()+"\" "+DataPage::newcomboList.at(i)->currentText();
            AddExtraMetadata.exec(query);
        }
    }
    if(BibliographyPage::newBiblabelList.count()>0){
        for (int i=0;i<BibliographyPage::newBiblabelList.count();i++ ) {
            QString query = "ALTER TABLE \"Bibliography\" ADD \""+BibliographyPage::newBiblabelList.at(i)->text()+"\" "+BibliographyPage::newcomboList.at(i)->currentText();
            AddExtraMetadata.exec(query);
        }
    }
    QSqlQuery BackUp1(newdatabaseFile);
    QString BackUpMetadata = "INSERT INTO \"BackUp\" (\"Table_Id\",\"Id\",\"Name\") VALUES ";
    QStringList BackUpMeta_Query;
    for (int i=0;i<Metadata.count();i++ ) {
        BackUpMeta_Query.append("(\"Metadata\",\""+Metadata.at(i)+"\",\""
                +MetadataNames.at(i)+"\")");
    }
    BackUpMetadata +=BackUpMeta_Query.join(",");
    BackUp1.exec(BackUpMetadata);
    QString BackUpBib = "INSERT INTO \"BackUp\" (\"Table_Id\",\"Id\",\"Name\") VALUES ";
    QStringList BackUpBib_Query;
    for (int i=0;i<BibData.count();i++ ) {
        BackUpBib_Query.append("(\"Bibliography\",\""+BibData.at(i)+"\",\""
                +BibDataNames.at(i)+"\")");
    }
    BackUpBib +=BackUpBib_Query.join(",");
    BackUp1.exec(BackUpBib);
    newdatabaseFile.close();
    QSqlQuery AddNewDatabase(Texstudio::DataTeX_Settings);
    AddNewDatabase.exec(
    QString("INSERT INTO \"DataBases\" (\"FileName\", \"Name\", \"Path\") VALUES (\"%1\", \"%2\", \"%3\");")
                .arg(baseFileName,folderName,FullPath));

    QString MetadataQuery_1 = "INSERT OR IGNORE INTO \"Metadata\" (\"Id\",\"Name\",\"Basic\") VALUES ";
    QStringList MetadataEntries_1;
    if(DataPage::newlabelList.count()>0){
        for (int i=0;i<DataPage::newlabelList.count();i++ ) {
            MetadataEntries_1.append("(\""+DataPage::newlabelList.at(i)->text()+"\",\""
                    +DataPage::newFieldLineList.at(i)->text()+"\",\"0\")");
        }
    }
    MetadataQuery_1 +=MetadataEntries_1.join(",");
    QSqlQuery Metadata_1(Texstudio::DataTeX_Settings);
    Metadata_1.exec(MetadataQuery_1);

    QString BibQuery_1 = "INSERT OR IGNORE INTO \"Bibliography\" (\"Id\",\"Name\",\"Basic\") VALUES ";
    QStringList BibEntries_1;

    if(BibliographyPage::newBiblabelList.count()>0){
        for (int i=0;i<BibliographyPage::newBiblabelList.count();i++ ) {
            BibEntries_1.append("(\""+BibliographyPage::newBiblabelList.at(i)->text()+"\",\""
                    +BibliographyPage::newBibLineList.at(i)->text()+"\",\"0\")");
        }
    }
    BibQuery_1 +=BibEntries_1.join(",");
    QSqlQuery Bibliography_1(Texstudio::DataTeX_Settings);
    Bibliography_1.exec(BibQuery_1);

    QString BibQuery_2 = "INSERT INTO \"Bibliographic_Fields_per_Database\" (\"Database\",\"Bibliographic_Field\") VALUES ";
    QStringList BibEntries_2;
    for (int i=0;i<bibfields.count();i++ ) {
        BibEntries_2.append("(\""+baseFileName+"\",\""+bibfields.at(i)+"\")");
    }
    for (int i=0;i<BibliographyPage::newBiblabelList.count();i++ ) {
        BibEntries_2.append("(\""+baseFileName+"\",\""+BibliographyPage::newBiblabelList.at(i)->text()+"\")");
    }
    BibQuery_2 +=BibEntries_2.join(",");
    QSqlQuery Bibliography_2(Texstudio::DataTeX_Settings);
    Bibliography_2.exec(BibQuery_2);

    QString MetadataQuery_2 =
            "INSERT INTO \"Metadata_per_Database\" (\"Database_FileName\",\"Metadata_Id\") VALUES ";
    QStringList MetadataEntries_2;
    for (int i=0;i<fields.count();i++ ) {
        MetadataEntries_2.append("(\""+baseFileName+"\",\""+fields.at(i)+"\")");
    }
    for (int i=0;i<DataPage::newlabelList.count();i++ ) {
        MetadataEntries_2.append("(\""+baseFileName+"\",\""+DataPage::newlabelList.at(i)->text()+"\")");
    }
    MetadataQuery_2 +=MetadataEntries_2.join(",");
    QSqlQuery Metadata_2(Texstudio::DataTeX_Settings);
    Metadata_2.exec(MetadataQuery_2);
    emit newbase(path,folderName,baseFileName);
    QDialog::accept();
}
