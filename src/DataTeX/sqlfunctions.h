#ifndef SQLFUNCTIONS_H
#define SQLFUNCTIONS_H

#include<QStringList>
#include<QSql>
#include<QSqlDatabase>
#include <QSqlQueryModel>
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

class SqlFunctions
{
public:
    SqlFunctions();

    static const QString Fields_Query;
    static const QString Chapters_Query;
    static const QString Sections_Chapters_Query;
    static const QString Sections_Query;
    static const QString Exercise_Types_Query;

    static const QString CreateFieldsTablesQuery;
    static const QString CreateClassTablesQuery;
    static const QString CreateChaptersTablesQuery;
    static const QString CreateSectionsTablesQuery;
    static const QString CreateExerciseTypesTablesQuery;
    static const QString CreateDatabaseFilesTablesQuery;
    static const QString CreateSectionExercisesTablesQuery;
    static const QString CreateFileTypesTablesQuery;
    static const QString CreateSubjectTypesTablesQuery;

    static const QString SelectCurrentDataBase;
    static const QString SelectCurrentNotesFolderBase;
    static const QString GetCurrentDataBaseFields;
    static const QString GetCurrentDataBaseBasicFields;
    static const QString GetCurrentDataBaseOptionalFields;

    static const QString SelectExercises;

    static const QString CountFiles_by_Field;
    static const QString CountFiles_by_Chapter;
    static const QString CountFiles_by_Section;
    static const QString CountFiles_by_ExerciseType;
    static const QString CountFiles_by_FileType;

    static const QString Section_List_contaning_Exercises;
    static const QString GetName;
    static const QString FolderName;
    static const QString TheoryFiles;
    static const QString TheoryFiles_Chapter;
    static const QString TheoryFiles_Chapter_Section;
    static const QString ExerciseFiles;
    static const QString ExerciseFiles_Chapters;
    static const QString ExerciseFiles_Chapters_Sections;
    static const QString ExerciseFiles_Chapters_Sections_ExSubType;
    static const QString GetSubject_Types;
    static const QString GetCombFiles;
    static const QString GetTheoryFiles;
    static const QString AddTheoryFilesToEditor;
    static const QString AddExerciseFilesToEditor;
    static const QString GetFileTypeIdfromCheckBox;
    static const QString GetSectionsCombFiles;
    static const QString AddCombFilesToList;
    static const QString ShowSolvedAndUnSolvedExercises;
    static const QString ShowSolvedAndUnSolvedCombExercises;
    static const QString EmptyTable;
    static const QString UpdateSolution;
    static const QString SelestExerciseRow;
    static const QString GetDocumentTypes;
    static const QString ShowAllDatabaseFiles;
    static const QString GetPreamble;
    static const QString GetPreamble_Content;
    static const QString GetBibliographyFields;
    static const QString GetColumnNames;


public slots:

    static QList<QStringList> ComboList_Single(QString queryString,QSqlDatabase database,QString Arg1);

    static QList<QStringList> ComboList_Double_List(QString queryString,QSqlDatabase database);

    static QList<QStringList> ComboList_Exercises(QString queryString,QSqlDatabase database,
                                                  QString Arg1,QString Arg2,QString Arg3,QString Arg4);
    static const QString GetCurrentDataBase(QSqlDatabase database, QString databaseQuery);

    static QStringList Get_StringList_From_Query(QString queryString,QSqlDatabase database);

    static int ExecuteSqlScriptFile(QSqlDatabase & database, const QString & fileName);

private:


};

#endif // SQLFUNCTIONS_H
