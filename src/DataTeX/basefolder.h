#ifndef BASEFOLDER_H
#define BASEFOLDER_H

#include <QDialog>
#include <QMap>
#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QLayout>
#include <QtSql>
#include <QSqlDatabase>
#include <QWizard>
#include <QWizardPage>
#include <QCheckBox>
#include <QTableWidget>

namespace Ui {
class BaseFolder;
}

class BaseFolder : public  QWizard
{
    Q_OBJECT

public:
    explicit BaseFolder(QWidget *parent = nullptr);
    ~BaseFolder();

    void accept() override;

    static QStringList fields;
    static QStringList bibfields;
    static QStringList FieldTypesValues;
    static QStringList BibTypesValues;
    static QStringList Metadata;
    static QStringList BibData;
    static QStringList MetadataNames;
    static QStringList BibDataNames;

private slots:

public slots:

signals:

    void newbase(QString Path,QString FolderName,QString FileName);

private:
    Ui::BaseFolder *ui;
};

class InfoPage : public QWizardPage
{
    Q_OBJECT

public:
    InfoPage(QWidget *parent = nullptr);

private:
    QLabel * CheckDatabaseName;

    QLineEdit * DatabasePath;
    QLineEdit * DatabaseFileName;
    QLineEdit * DatabaseName;
    QPushButton * DatabasePathButton;
    QStringList DatabaseList;

private slots:
    void Database_Path();

    void CheckDatabase();
};

class DataPage : public QWizardPage
{
    Q_OBJECT

public:
    DataPage(QWidget *parent = nullptr);

    static QList<QCheckBox *> newCheckList;
    static QList<QLineEdit *> newlabelList;
    static QList<QLineEdit * >  newFieldLineList;
    static QList<int> addedIdList;
    static QList<int> removedIdList;
    static QList<QComboBox *> newcomboList;

    ~DataPage();

private:
    QStringList BasicDataBaseFields;
    QStringList BasicDataBaseValues;
    QStringList OptionalDataBaseFields;
    QStringList OptionalDataBaseValues;
    QList<QLabel *> labelList;

    QList<QLineEdit * >  lineList;
    QList<QComboBox *> basiccomboList = QList<QComboBox *>();

    QList<QHBoxLayout *> hLayoutList;
    QButtonGroup *editorGroup;
    QButtonGroup * checkGroup = new QButtonGroup();
    QPushButton * AddFieldButton;
    QPushButton * RemoveFieldButton;

    QGridLayout *DataLayout;
    QStringList FieldTypes;
    int optfield;
    QStringList FieldList;
    QLabel * CheckFieldId;
    bool next;

private slots:
    void AddField();
    void RemoveField();
    void CheckNewField(QString text);
    void CheckNext();
};

class BibliographyPage : public QWizardPage
{
    Q_OBJECT

public:
    BibliographyPage(QWidget *parent = nullptr);

    static QList<QCheckBox *> newBibCheckList;
    static QList<QLineEdit *> newBiblabelList;
    static QList<QLineEdit * >  newBibLineList;
    static QList<int> addedBibIdList;
    static QList<int> removedBibIdList;
    static QList<QComboBox *> newcomboList;

//    void initializePage() override;

    ~BibliographyPage();

private:
    QStringList BasicBibliographyFields;
    QStringList BasicBibliographyValues;
    QGridLayout * BibliographyLayout;
    QPushButton * AddBibTexButton;
    QPushButton * RemoveBibTexButton;
    QStringList FieldTypes;
    int optfield;
    QList<QLabel *> labelList;
    QList<QLineEdit * >  lineList;
    QList<QComboBox *> basiccomboList = QList<QComboBox *>();

    QList<QHBoxLayout *> hLayoutList;
    QButtonGroup *editorGroup;
    QButtonGroup * checkGroup = new QButtonGroup();
    QStringList FieldList;
    QLabel * CheckFieldId;
    bool next;

private slots:
    void AddBibField();
    void RemoveBibField();
    void CheckNewBibField(QString text);
    void CheckNext();
};

class FinalPage : public QWizardPage
{
    Q_OBJECT

public:
    FinalPage(QWidget *parent = nullptr);

    void initializePage() override;

    ~FinalPage();

private:
    QStringList BasicDataBaseFields;
    QList<QLabel *> labelList;
    QVBoxLayout *layout;
    QTableWidget * table;
    QTableWidget * table2;
    QLabel *PathLabel;
    QLabel *FileNameLabel;
    QLabel *NameLabel;
    QLabel *label3;

private slots:
//    void Database_Path();
};

#endif // BASEFOLDER_H
