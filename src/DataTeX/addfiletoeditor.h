#ifndef ADDFILETOEDITOR_H
#define ADDFILETOEDITOR_H

#include <QDialog>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QFile>
#include <QtSql/QSql>
#include <QSqlQueryModel>
#include "sqlfunctions.h"
#include "texstudio.h"
#include <QtPdf>
#include <QPdfDocument>
#include "pdfviewer.h"

namespace Ui {
class AddFileToEditor;
}

class AddFileToEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AddFileToEditor(QWidget *parent = nullptr,QString currentTexFile = QString());
    ~AddFileToEditor();

public slots:

private slots:

    void on_FieldListTheory_itemClicked(QListWidgetItem *item);

    void on_TheoryCheck_checked(bool checked);

    void on_FileList_itemSelectionChanged();

    void on_FieldListCombExercises_itemClicked(QListWidgetItem *item);

    void on_FieldListExercises_itemClicked(QListWidgetItem *item);

    void on_Okbutton_rejected();

    void on_ComboCombSubjectType_currentIndexChanged(int index);

    void on_SectionsList_itemClicked(QListWidgetItem *item);

    void closeEvent (QCloseEvent *event);

    void on_FileList_itemDoubleClicked(QListWidgetItem *item);

    void on_ComboSectionExercises_currentIndexChanged(int index);

    void on_ComboExTypeExercises_currentIndexChanged(int index);

    void on_radioButton_toggled(bool checked);

    void on_ComboChapterExercises_currentIndexChanged(int index);

    void on_CheckBox_checked(bool checked);

    void on_CombSubjectsBox_clicked(bool checked);

    void on_CombSubjectSolutionsBox_clicked(bool checked);

    void on_CombExercisesBox_clicked(bool checked);

    void on_CombExerciseSolutionsBox_clicked(bool checked);

    void loadImageFile(QString exoFile);

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_SelectedFiles_itemSelectionChanged();

    void on_Okbutton_accepted();

    void on_UpButton_clicked();

    void moveup(bool up);

    void movedown(bool up);

    // takes and returns the whole row
    QList<QTableWidgetItem*> takeRow(int row);

    void setRow(int row, const QList<QTableWidgetItem*>& rowItems);

    void on_DownButton_clicked();

    void on_Rebuild_clicked();

    void on_ComboChapterTheory_currentIndexChanged(int index);

    void on_comboSectionTheory_currentIndexChanged(int index);

private:
    Ui::AddFileToEditor *ui;

    QSqlDatabase currentbase;

    QSqlTableModel * tableModel;

    QString PreviewFile;
    QString FileType;
    QString ExSubType;
    QString SolutionFileType;
    QString ComFileType;
    QList<QCheckBox *> checklist;
    QString CurrentDatabaseFile;

    PdfViewer *view;

signals:

    void files(QStringList paths);
};

#endif // ADDFILETOEDITOR_H
