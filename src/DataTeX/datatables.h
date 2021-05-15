#ifndef DATATABLES_H
#define DATATABLES_H

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
#include "addline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DataTables; }
QT_END_NAMESPACE

class DataTables : public QDialog
{
    Q_OBJECT

public:
    DataTables(QWidget *parent = nullptr);
    ~DataTables();

public slots:

    void EditField(QStringList Line);

    void EditChapter(QStringList Line);

    void EditSection(QStringList Line);

    void EditDocumentType(QString Line);

    void EditSubjectType(QStringList Line);

private slots:
    void on_AddFieldButton_clicked();

    void on_RemFieldButton_clicked();

    void on_FieldTable_itemClicked(QTableWidgetItem *item);

    void on_ComboFields_ChapterTab_currentIndexChanged(int index);

    void on_ComboFields_SectionTab_currentIndexChanged(int index);

    void on_ComboChapters_SectionTab_currentIndexChanged(int index);

    void on_AddChapterButton_clicked();

    void on_RemoveChapterButton_clicked();

    void on_ChapterTable_itemClicked(QTableWidgetItem *item);

    void on_AddSectionButton_clicked();

    void on_SectionTable_itemClicked(QTableWidgetItem *item);

    void on_RemoveSectionButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_EditFieldButton_clicked();

    void on_EditChapterButton_clicked();

    void on_EditSectionButton_clicked();

    void on_AddDocumentTypeButton_clicked();

    void on_RemDocumentTypeButton_clicked();

    void on_EditDocumentTypeButton_clicked();

    void on_DocumentTypeTable_itemClicked(QTableWidgetItem *item);

    void on_AddSubjectTypeButton_clicked();

    void on_RemSubjectType_clicked();

    void on_EditSubjectTypeButton_clicked();

    void on_SubjectTypeTable_itemClicked(QTableWidgetItem *item);

    void AddField(QStringList Line);

    void AddChapter(QStringList Line);

    void AddSection(QStringList Line);

    void AddExerciseType(QStringList Line);

    void EditExerciseType(QStringList Line);

    void AddDocumentType(QString Line);

    void AddSubjectType(QStringList Line);

    void on_ComboFields_ExerciseTypeTab_currentIndexChanged(int index);

    void on_ComboChapters_ExerciseTypeTab_currentIndexChanged(int index);

    void on_ComboSections_ExerciseTypeTab_currentIndexChanged(int index);

    void on_AddExerciseTypeButton_clicked();

    void on_RemoveExerciseTypeButton_clicked();

    void on_EditExerciseTypeButton_clicked();

    void on_ExerciseTypeTable_itemClicked(QTableWidgetItem *item);

    void UpdateDatabaseMetadata(QString Id,QString DBField,QString oldId1,QString newId1,QString oldPath1,QString newPath1,QString oldPath2,QString newPath2);

private:
    Ui::DataTables *ui;

    AddLine * newLine;
    addfolder * newFolder;
    QSqlDatabase currentbase;
    QSqlDatabase currentbase_Notes;

signals:

    void addline(QStringList Line);//---

    void addfolder_signal(QString Line);//---
};
#endif // DATATABLES_H
