#ifndef NOTEFOLDER_H
#define NOTEFOLDER_H

#include <QDialog>

namespace Ui {
class NoteFolder;
}

class NoteFolder : public QDialog
{
    Q_OBJECT

public:
    explicit NoteFolder(QWidget *parent = nullptr);
    ~NoteFolder();

private slots:
    void on_NoteButton_clicked();

    void on_NoteButtonBox_accepted();

    bool isWhiteSpace(const QString & str);

signals:

    void newnote(QString FolderPath,QString FolderName,QString FileName);

private:
    Ui::NoteFolder *ui;
};

#endif // NOTEFOLDER_H
