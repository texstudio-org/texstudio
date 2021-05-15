#ifndef NOTESDOCUMENTS_H
#define NOTESDOCUMENTS_H

#include <QDialog>
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
#include <QTableWidgetItem>
#include <QFileInfo>
#include <QDesktopServices>
#include <QList>
#include <QUrl>
#include <QDesktopServices>
#include <QGridLayout>
#include <QDebug>
#include <QModelIndex>
#include <algorithm>
#include <QtSql>
#include <QSqlDatabase>
#include "addfolder.h"
#include "texstudio.h"

namespace Ui {
class NotesDocuments;
}

class NotesDocuments : public QDialog
{
    Q_OBJECT

public:
    explicit NotesDocuments(QWidget *parent = nullptr);
    ~NotesDocuments();

public slots:
    
    void EditBasicForders_DataTex(QString line);//---

    void EditSubForders_DataTex(QString Line);//---
    void EditSubsubForders_DataTex(QString Line);

private slots:

    void showItemsTable(bool epil);

    bool isWhiteSpace(const QString & str);

    void Folder(bool checked);

    void on_FolderStructure_itemClicked(QListWidgetItem *item);

    void on_OpenPdfButton_clicked();

    void on_CheckEpiloghOlwn_clicked(bool checked);

    void on_OpenTexButton_clicked();

    void on_AddBasicButton_clicked();

    void on_BasicFoldersTable_itemSelectionChanged();

    void on_CreateBasicButton_clicked();

    void on_RemBasicButton_clicked();

    void on_AddSubButton_clicked();

    void on_CreateSubButton_clicked();

    void on_OkbuttonBoxFolders_accepted();

    void on_OkbuttonBoxFolders_rejected();

    void on_RemSubButton_clicked();

    void on_AddSubsubButton_clicked();

    void on_SubsubCheck_clicked(bool checked);

    void on_CreateSubsubButton_clicked();

    void on_SubsubFolderTable_itemSelectionChanged();

    void on_RemSubsubButton_clicked();

    void on_EditBasicButton_clicked();

    void on_EditSubButton_clicked();

    void on_EditSubsubButton_clicked();

    void on_OpenFolderButton_clicked();

    QString SavePath(bool checked);

    void enable3check();

    void Basic(QString newfolder);//---

    void SubFolder(QString newfolder);

    void SubsubFolder(QString newfolder);

    void on_CreatePdfCheckbox_toggled(bool checked);

    void on_SubFolderTable_itemSelectionChanged();

    void on_DocumentTable_itemSelectionChanged();

    void on_SolutionTexButton_clicked();

    QString getPreamble(QString fileName);

    void on_SolutionPdfButton_clicked();

private:
    Ui::NotesDocuments *ui;
    addfolder * newFolder;
    QSqlDatabase currentbase;
    QSqlDatabase currentbase_Exercises;
    QString DocumentType;
    QButtonGroup * radiogroup;
    QList<QRadioButton * >  radioList;
    QList<QCheckBox * >  checkList;
    QString BasicFolder;
    QString BasicFolderFile;
    QString NotesPath;

    QStringList Exer_List;
    QStringList Solutions_List;
    QStringList Solved_List;
    QStringList Unsolved_List;
    QStringList Hint_List;
    QStringList Hinted_List;
    QStringList UnHinted_List;

signals:
    void pathline(QString line);//---
    void openpdf(QString Line);//---
    void insertfiles();//---
    void nolines();
    void OpenSolutionFile(QString SolutionsTexFile);
};

#endif // NOTESDOCUMENTS_H
