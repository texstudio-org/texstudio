/********************************************************************************
** Form generated from reading UI file 'letterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LETTERDIALOG_H
#define UI_LETTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_LetterDialog
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QComboBox *comboBoxPaper;
    QLabel *label1;
    QLabel *label3;
    QCheckBox *checkBox;
    QComboBox *comboBoxPt;
    QComboBox *comboBoxEncoding;
    QLabel *label2;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *LetterDialog)
    {
        if (LetterDialog->objectName().isEmpty())
            LetterDialog->setObjectName(QString::fromUtf8("LetterDialog"));
        LetterDialog->resize(360, 182);
        gridLayout = new QGridLayout(LetterDialog);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        comboBoxPaper = new QComboBox(LetterDialog);
        comboBoxPaper->setObjectName(QString::fromUtf8("comboBoxPaper"));

        gridLayout1->addWidget(comboBoxPaper, 1, 1, 1, 1);

        label1 = new QLabel(LetterDialog);
        label1->setObjectName(QString::fromUtf8("label1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label1->sizePolicy().hasHeightForWidth());
        label1->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label1, 0, 0, 1, 1);

        label3 = new QLabel(LetterDialog);
        label3->setObjectName(QString::fromUtf8("label3"));
        sizePolicy.setHeightForWidth(label3->sizePolicy().hasHeightForWidth());
        label3->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label3, 2, 0, 1, 1);

        checkBox = new QCheckBox(LetterDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout1->addWidget(checkBox, 3, 1, 1, 1);

        comboBoxPt = new QComboBox(LetterDialog);
        comboBoxPt->setObjectName(QString::fromUtf8("comboBoxPt"));

        gridLayout1->addWidget(comboBoxPt, 0, 1, 1, 1);

        comboBoxEncoding = new QComboBox(LetterDialog);
        comboBoxEncoding->setObjectName(QString::fromUtf8("comboBoxEncoding"));

        gridLayout1->addWidget(comboBoxEncoding, 2, 1, 1, 1);

        label2 = new QLabel(LetterDialog);
        label2->setObjectName(QString::fromUtf8("label2"));
        sizePolicy.setHeightForWidth(label2->sizePolicy().hasHeightForWidth());
        label2->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label2, 1, 0, 1, 1);

        gridLayout1->setColumnStretch(1, 1);

        gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(LetterDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(LetterDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        QWidget::setTabOrder(comboBoxPt, comboBoxPaper);
        QWidget::setTabOrder(comboBoxPaper, comboBoxEncoding);
        QWidget::setTabOrder(comboBoxEncoding, checkBox);
        QWidget::setTabOrder(checkBox, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(LetterDialog);
        QObject::connect(okButton, SIGNAL(clicked()), LetterDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), LetterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LetterDialog);
    } // setupUi

    void retranslateUi(QDialog *LetterDialog)
    {
        label1->setText(QCoreApplication::translate("LetterDialog", "Typeface Size", nullptr));
        label3->setText(QCoreApplication::translate("LetterDialog", "Encoding", nullptr));
        checkBox->setText(QCoreApplication::translate("LetterDialog", "AMS Packages", nullptr));
        label2->setText(QCoreApplication::translate("LetterDialog", "Paper Size", nullptr));
        okButton->setText(QCoreApplication::translate("LetterDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("LetterDialog", "Cancel", nullptr));
        (void)LetterDialog;
    } // retranslateUi

};

namespace Ui {
    class LetterDialog: public Ui_LetterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LETTERDIALOG_H
