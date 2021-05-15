#ifndef NEWDATABASEFILE_H
#define NEWDATABASEFILE_H

#include <QDialog>
#include <QListWidgetItem>
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
#include <QDebug>
#include <QCloseEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QMap>
#include <QSpinBox>
#include "pdfviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NewDatabaseFile; }
QT_END_NAMESPACE

class NewDatabaseFile : public QDialog
{
    Q_OBJECT

public:
    NewDatabaseFile(QWidget *parent = nullptr);
    ~NewDatabaseFile();

//    QStringList Basic_Metadata_Ids;
//    QStringList Basic_Metadata_Names;


private slots:
    void Theory_clicked();

    void updateTableView(QTableView * table,QString QueryText);

    void on_SectionExercisesFieldComboBox_currentIndexChanged(int index);

    void Method_Example_clicked();

    void on_SectionExerciseButton_clicked();

    void on_ExerciseFileList_itemClicked(QListWidgetItem *item);

    void on_OkDialogButton_accepted();

    void on_OpenButton_clicked();

    void on_CombFieldList_currentRowChanged(int currentRow);

    void on_SectionList_itemClicked(QListWidgetItem *item);

    void on_SectionList_itemDoubleClicked(QListWidgetItem *item);

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_CombExercisesSubjectComboBox_currentIndexChanged(int index);

    void on_CombExerciseButton_clicked();

    void on_SelectedSections_itemClicked(QListWidgetItem *item);

    void on_OkDialogButton_rejected();

    void closeEvent (QCloseEvent *event);

    void on_CombExerciseRadio_toggled(bool checked);

    void on_CombSubjectRadio_toggled(bool checked);

    void on_CopyButton_clicked();

    void on_FieldTable_itemClicked(QListWidgetItem *item);

    void on_SectionExercisesSectionComboBox_currentIndexChanged(int index);

    void on_SectionExercisesExTypeComboBox_currentIndexChanged(int index);

    void on_helpButton_clicked();

    void resetselections();

    void reseteverything();

    void on_SectionExercisesChapterComboBox_currentIndexChanged(int index);

    void on_SectionSubjectCheck_clicked(bool checked);

    void on_UseExerciseTypeCheck_toggled(bool checked);

    void on_ComboChapter_Theory_currentIndexChanged(int index);

    void on_ComboSection_Theory_currentIndexChanged(int index);

    void on_FileTable_doubleClicked(const QModelIndex &index);

    void on_ExerciseFileList_doubleClicked(const QModelIndex &index);

    void on_CombExersiceTable_doubleClicked(const QModelIndex &index);

    void TableItemDoubleClicked(QTableView * table, const QModelIndex &index,int column);

    void InitialSettings();

private:
    Ui::NewDatabaseFile *ui;

    QString TexFile;
    QString PdfCommand;
    QSqlDatabase currentbase;

    QSqlTableModel * tableModel;
    QString DataBase_Path;

    QStringList Optional_Metadata_Ids;
    QStringList Optional_Metadata_Names;

    QMap<QString,QString> mapIdsNames;
    QMap<QString,QLineEdit *> mapIdsWidgets;
    QList<QList<QLabel *> *> labelList;
    QList<QList<QLineEdit *> *> lineList;
    QList<QList<QHBoxLayout *> *> hLayoutList;
    int buttonindex;
    QString FileType;
    QString ComFileType;
    QStringList SectionList;
    QStringList Bibliography_Ids;

signals:

    void acceptSignal(QString fileName, QMap<QString,QString> metadata,QStringList SectionList); //15/5

    void listChanged();
};
#endif // NEWDATABASEFILE_H
