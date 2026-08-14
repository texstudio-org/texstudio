/********************************************************************************
** Form generated from reading UI file 'maketemplatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKETEMPLATEDIALOG_H
#define UI_MAKETEMPLATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MakeTemplateDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *leName;
    QLabel *label_2;
    QLineEdit *leAuthor;
    QLabel *label_3;
    QLineEdit *leVersion;
    QLabel *label_4;
    QPlainTextEdit *leDescription;
    QLabel *label_6;
    QComboBox *cbLicense;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MakeTemplateDialog)
    {
        if (MakeTemplateDialog->objectName().isEmpty())
            MakeTemplateDialog->setObjectName(QString::fromUtf8("MakeTemplateDialog"));
        MakeTemplateDialog->resize(403, 323);
        verticalLayout = new QVBoxLayout(MakeTemplateDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(MakeTemplateDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        groupBox = new QGroupBox(MakeTemplateDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        leName = new QLineEdit(groupBox);
        leName->setObjectName(QString::fromUtf8("leName"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leName);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        leAuthor = new QLineEdit(groupBox);
        leAuthor->setObjectName(QString::fromUtf8("leAuthor"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, leAuthor);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        leVersion = new QLineEdit(groupBox);
        leVersion->setObjectName(QString::fromUtf8("leVersion"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, leVersion);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        leDescription = new QPlainTextEdit(groupBox);
        leDescription->setObjectName(QString::fromUtf8("leDescription"));
        leDescription->setTabChangesFocus(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, leDescription);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_6);

        cbLicense = new QComboBox(groupBox);
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY"));
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY-SA"));
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY-ND"));
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY-NC"));
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY-NC-SA"));
        cbLicense->addItem(QString::fromUtf8("Creative Commons CC BY-NC-ND"));
        cbLicense->addItem(QString::fromUtf8("GNU Free Documentation License"));
        cbLicense->addItem(QString());
        cbLicense->addItem(QString::fromUtf8("Public Domain"));
        cbLicense->setObjectName(QString::fromUtf8("cbLicense"));
        cbLicense->setEditable(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, cbLicense);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(MakeTemplateDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(MakeTemplateDialog);

        cbLicense->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MakeTemplateDialog);
    } // setupUi

    void retranslateUi(QDialog *MakeTemplateDialog)
    {
        MakeTemplateDialog->setWindowTitle(QCoreApplication::translate("MakeTemplateDialog", "Make Template", nullptr));
        label_5->setText(QCoreApplication::translate("MakeTemplateDialog", "Create a template from the current file.", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MakeTemplateDialog", "Meta Data", nullptr));
        label->setText(QCoreApplication::translate("MakeTemplateDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("MakeTemplateDialog", "Author", nullptr));
        label_3->setText(QCoreApplication::translate("MakeTemplateDialog", "Version", nullptr));
        label_4->setText(QCoreApplication::translate("MakeTemplateDialog", "Description", nullptr));
        label_6->setText(QCoreApplication::translate("MakeTemplateDialog", "License", nullptr));
        cbLicense->setItemText(7, QCoreApplication::translate("MakeTemplateDialog", "LaTeX Project Public License (LPPL)", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MakeTemplateDialog: public Ui_MakeTemplateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKETEMPLATEDIALOG_H
