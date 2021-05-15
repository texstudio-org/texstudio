#ifndef BACKUP_H
#define BACKUP_H

#include <QDialog>
#include <QDir>

namespace Ui {
class BackUp;
}

class BackUp : public QDialog
{
    Q_OBJECT

public:
    explicit BackUp(QWidget *parent = nullptr);
    ~BackUp();

    QString basenamebackup;
    QString basepathbackup;
    QString notenamebackup;
    QString notepathbackup;
    QStringList TexFiles;
    QStringList PdfFiles;

private slots:
    void on_ComboBaseBackUp_currentIndexChanged(int index);

    void on_BackUpBaseButton_clicked();

    void on_ComboNotesBackUp_currentIndexChanged(int index);

    void on_BackUpNotesButton_clicked();

    void on_BackUpZipBase_clicked(bool checked);

    void on_BackUpZipNotes_clicked(bool checked);

private:
    Ui::BackUp *ui;
};

#endif // BACKUP_H
