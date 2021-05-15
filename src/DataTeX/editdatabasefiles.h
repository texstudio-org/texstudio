#ifndef EDITDATABASEFILES_H
#define EDITDATABASEFILES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QLabel>
#include <QHBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>

#include <QApplication>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QPainter>
#include <QMessageBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QListWidget>
#include "pdfviewer.h"
#include "bibtexdialog.h"

namespace Ui {
class EditDataBaseFiles;
}

class EditDataBaseFiles : public QDialog
{
    Q_OBJECT

public:
    explicit EditDataBaseFiles(QWidget *parent = nullptr,
                               QStringList BibNames = QStringList(),QStringList BibDescriptions= QStringList());
    ~EditDataBaseFiles();

private slots:
    void FilesTable_selectionchanged();

    void loadImageFile(QString exoFile);

    void FileEdit_Changed();

    void on_SaveTextButton_clicked();

//    void createpdf(QString fullFilePath);

    void on_ResetButton_clicked();

    void updateTableView(QTableView * table,QString QueryText);

    void Filter_textChanged();

//    void on_FieldFilter_textChanged(const QString &arg1);

//    void on_ChapterFilter_textChanged(const QString &arg1);

//    void on_SectionFilter_textChanged(const QString &arg1);

//    void on_ExerciseFilter_textChanged(const QString &arg1);

//    void on_FileTypeFilter_textChanged(const QString &arg1);

    void on_AddFileToBaseButton_clicked();

    void on_DeleteFileFromBaseButton_clicked();

    void on_EditMetadataButton_clicked();

    void on_ComboCount_currentIndexChanged(int index);

    void ShowDataBaseFiles();

    void FieldChanged();
    void ChapterChanged();
    void SectionChanged(QListWidgetItem * sectionitem);
    void ExerciseTypeChanged();
    void FileTypeChanged();
    void OkAccept();
    void OkReject();

    void on_EditBibButton_clicked();

    void on_SaveBibliographyButton_clicked();

    void on_BuildButton_clicked();

    void on_OpenInEditorButton_clicked();

private:
    Ui::EditDataBaseFiles *ui;
    PdfViewer *view;
    QSqlTableModel * tableModel;
    QDialog * MetadataDialog;
    QMap<QString,QString> MetadataMap;
    QList<QWidget *> MetaWidgets;
    QStringList Basic_Metadata_Ids;
    QStringList Basic_Metadata_Names;
    QStringList Optional_Metadata_Ids;
    QStringList Optional_Metadata_Names;
    QStringList Bibliography_Ids;
    QStringList Bibliography_Names;
    QMap<QString,QString> mapIdsNames;
    QMap<QString,QLineEdit *> mapIdsWidgets;
    QList<QLabel *> labelList;
    QList<QLineEdit *> lineList;
    QList<QHBoxLayout *>hLayoutList;
    QString OptionalFields;
    QString DatabaseFileName;
    QString Field;
    QString Chapter;
    QString Section;
    QString ExerciseType;
    QString FileType;
    QString DatabaseFilePath;
    int Difficulty;
    QString Date;
    QString Solved;
    QStringList Metadata;
    QList<QLineEdit *> LineEditList;
    QString FileContent;
    QSqlDatabase currentbase;
    QLineEdit * IdLine;
    QComboBox * FieldCombo;
    QComboBox * ChapterCombo;
//    QComboBox * SectionCombo;
    QComboBox * ExerciseTypeCombo;
    QComboBox * FileTypeCombo;
    QLineEdit * PathLine;
    QSpinBox * DifficultySpin;
    QDateTimeEdit * DateTimeEdit;
    QLineEdit * SolvedLine;
    QTextEdit * FileText;
    QGridLayout * layout;
    QListWidget * SectionsList;
    int currentSectionRow = -1;
    QDialogButtonBox * MetadataOkButton;
    QList<QHBoxLayout *> hLayoutList2;
    QList<QLineEdit *> BibLineEditList;
    QMap<QString,QLineEdit *> mapBibliographyWidgets;
    QMap<QString,QString> mapBibliographyValues;
    QStringList bibDescriptions;
    QStringList bibNames;
};

#endif // EDITDATABASEFILES_H
