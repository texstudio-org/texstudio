#ifndef PATHS_H
#define PATHS_H

#include <QDialog>
#include "basefolder.h"
#include "notefolder.h"
#include "buildmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Paths; }
QT_END_NAMESPACE

class Paths : public QDialog
{
    Q_OBJECT

public:
    Paths(QWidget *parent = nullptr,QString path = QString());
    ~Paths();

public slots:

    void CreateBaseFolder(QString path, QString FolderName, QString fileName);

    void CreateNoteFolder(QString path, QString FolderName, QString FileName);

private slots:
    void on_BaseButton_clicked();

    void on_buttonBox_accepted();

    void on_NoteButton_clicked();

    void on_buttonBox_rejected();

    void on_ComboBaseList_currentIndexChanged(int index);

    void on_DeleteBase_clicked();

    void on_ComboNote_currentIndexChanged(int index);

    void on_DeleteBase_2_clicked();

    void on_AddNote_clicked();

    void on_AddBase_clicked();

    void on_OkbuttonBoxPreamble_accepted();

    void on_OkbuttonBoxPreamble_rejected();

    void on_PreambleCombo_currentIndexChanged(const QString &arg1);

    void on_AddPreambleButton_clicked();

    void on_RemovePreambleButton_clicked();

    void on_OpenSettingsButton_clicked();

    void AddPreamble(QStringList preamble);

    void LoadTables(QString database);

private:
    Ui::Paths *ui;
    BaseFolder * newbasefolder;
    NoteFolder * newnotefolder;
    QSqlDatabase currentbase_Exercises;
    QString DataBase_Path;

    QString prog;
    QString base;
    QString note;

};
#endif // PATHS_H
