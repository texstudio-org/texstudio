#ifndef SOLVEDATABASEEXERCISE_H
#define SOLVEDATABASEEXERCISE_H

#include <QDialog>
#include <QWidget>
#include <QFile>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QFile>
#include <QAbstractButton>
#include <QtSql>
#include <QSqlDatabase>
#include <QRadioButton>
//#include <QtPdf>
//#include <QPdfDocument>
//#include "pdfviewer.h"

namespace Ui {
class SolveDatabaseExercise;
}

class SolveDatabaseExercise : public QDialog
{
    Q_OBJECT

public:
    explicit SolveDatabaseExercise(QWidget *parent = nullptr);
    ~SolveDatabaseExercise();

    QString FieldsTex;
//    QString EidiThematwnTex;
    QFile FieldsTexFile;
//    QFile EidiThematwnTexFile;
    QStringList ExerciseFiles;
    QStringList SubjectFiles;
    QStringList ComExerciseFiles;
    QStringList ComSubjectFiles;

private slots:
    void on_FieldsList_itemClicked(QListWidgetItem *item);

    QString getFileType();

    void on_FileType_checked(bool checked);

    void on_SectionList_itemSelectionChanged();

    void on_ExerciseTable_itemSelectionChanged();

    void on_CreateSolutionButton_clicked();

    void loadImageFile(QString exoFile);

    void on_ExerciseRadio_toggled(bool checked);

    void on_SolvedRadio_toggled(bool checked);

    void on_RecompileButton_clicked();

    void on_CloseButton_clicked(QAbstractButton *button);

    void CreateSolution(QString solutionType,QString filetype);

    void on_CreateHintButton_clicked();

private:
    Ui::SolveDatabaseExercise *ui;
    QSqlDatabase currentbase;
    QRadioButton * radiobutton;
    QString Exercise;
    QString Solution;
    QString Hint;
    QString SolutionType;
    QString HintType;
//    PdfViewer *view;

signals:

    void SolutionFile(QString SolutionsTexFile,QMap<QString,QString> data,QStringList Sections);
};

#endif // SOLVEDATABASEEXERCISE_H
