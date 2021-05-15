#ifndef ADDLINE_H
#define ADDLINE_H

#include <QDialog>

namespace Ui {
class AddLine;
}

class AddLine : public QDialog
{
    Q_OBJECT

public:
    explicit AddLine(QWidget *parent = nullptr);
    ~AddLine();

public slots:

    void EditLine_DataTex(QStringList Line);

private slots:

    QStringList on_OkButton_accepted();

private:
    Ui::AddLine *ui;

signals:

    void grammhline(QStringList);//---
};

#endif // ADDLINE_H
