/********************************************************************************
** Form generated from reading UI file 'pdfannotationdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFANNOTATIONDLG_H
#define UI_PDFANNOTATIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PDFAnnotationDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbUser;
    QLabel *lbModDate;
    QLabel *lbType;
    QTextEdit *textEdit;

    void setupUi(QDialog *PDFAnnotationDlg)
    {
        if (PDFAnnotationDlg->objectName().isEmpty())
            PDFAnnotationDlg->setObjectName(QString::fromUtf8("PDFAnnotationDlg"));
        PDFAnnotationDlg->resize(219, 214);
        verticalLayout = new QVBoxLayout(PDFAnnotationDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbUser = new QLabel(PDFAnnotationDlg);
        lbUser->setObjectName(QString::fromUtf8("lbUser"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbUser->setFont(font);
        lbUser->setText(QString::fromUtf8("User"));

        verticalLayout->addWidget(lbUser);

        lbModDate = new QLabel(PDFAnnotationDlg);
        lbModDate->setObjectName(QString::fromUtf8("lbModDate"));
        lbModDate->setText(QString::fromUtf8("mod Date"));

        verticalLayout->addWidget(lbModDate);

        lbType = new QLabel(PDFAnnotationDlg);
        lbType->setObjectName(QString::fromUtf8("lbType"));
        lbType->setText(QString::fromUtf8("Type"));

        verticalLayout->addWidget(lbType);

        textEdit = new QTextEdit(PDFAnnotationDlg);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);


        retranslateUi(PDFAnnotationDlg);

        QMetaObject::connectSlotsByName(PDFAnnotationDlg);
    } // setupUi

    void retranslateUi(QDialog *PDFAnnotationDlg)
    {
        PDFAnnotationDlg->setWindowTitle(QCoreApplication::translate("PDFAnnotationDlg", "Annotation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PDFAnnotationDlg: public Ui_PDFAnnotationDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFANNOTATIONDLG_H
