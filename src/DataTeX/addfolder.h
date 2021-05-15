#ifndef ADDFOLDER_H
#define ADDFOLDER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class addfolder; }
QT_END_NAMESPACE

class addfolder : public QDialog
{
    Q_OBJECT

public:
    explicit addfolder(QWidget *parent = nullptr);
    ~addfolder();

public slots:

    QString on_newName();

    void on_OkbuttonBoxLine_accepted();

    void EditFolder(QString line);//---

private slots:
    void on_OkbuttonBoxLine_rejected();

private:
    Ui::addfolder *ui;
    
signals:
    
    void grammhfolder(QString);//---
};
#endif // ADDFOLDER_H
