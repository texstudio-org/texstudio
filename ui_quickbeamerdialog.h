/********************************************************************************
** Form generated from reading UI file 'quickbeamerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKBEAMERDIALOG_H
#define UI_QUICKBEAMERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickBeamerDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelTheme;
    QLabel *labelTitle;
    QLineEdit *lineEditAuthor;
    QLabel *labelEncoding;
    QLabel *labelSize;
    QLineEdit *lineEditTitle;
    QComboBox *comboBoxSize;
    QLabel *labelAuthor;
    QListWidget *listWidgetBabel;
    QCheckBox *checkBoxBabel;
    QComboBox *comboBoxEncoding;
    QComboBox *comboBoxTheme;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QuickBeamerDialog)
    {
        if (QuickBeamerDialog->objectName().isEmpty())
            QuickBeamerDialog->setObjectName(QString::fromUtf8("QuickBeamerDialog"));
        QuickBeamerDialog->resize(940, 474);
        gridLayout_2 = new QGridLayout(QuickBeamerDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelTheme = new QLabel(QuickBeamerDialog);
        labelTheme->setObjectName(QString::fromUtf8("labelTheme"));

        gridLayout->addWidget(labelTheme, 0, 0, 1, 1);

        labelTitle = new QLabel(QuickBeamerDialog);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        gridLayout->addWidget(labelTitle, 5, 0, 1, 1);

        lineEditAuthor = new QLineEdit(QuickBeamerDialog);
        lineEditAuthor->setObjectName(QString::fromUtf8("lineEditAuthor"));

        gridLayout->addWidget(lineEditAuthor, 4, 1, 1, 1);

        labelEncoding = new QLabel(QuickBeamerDialog);
        labelEncoding->setObjectName(QString::fromUtf8("labelEncoding"));

        gridLayout->addWidget(labelEncoding, 3, 0, 1, 1);

        labelSize = new QLabel(QuickBeamerDialog);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));

        gridLayout->addWidget(labelSize, 1, 0, 1, 1);

        lineEditTitle = new QLineEdit(QuickBeamerDialog);
        lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

        gridLayout->addWidget(lineEditTitle, 5, 1, 1, 1);

        comboBoxSize = new QComboBox(QuickBeamerDialog);
        comboBoxSize->setObjectName(QString::fromUtf8("comboBoxSize"));

        gridLayout->addWidget(comboBoxSize, 1, 1, 1, 1);

        labelAuthor = new QLabel(QuickBeamerDialog);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));

        gridLayout->addWidget(labelAuthor, 4, 0, 1, 1);

        listWidgetBabel = new QListWidget(QuickBeamerDialog);
        listWidgetBabel->setObjectName(QString::fromUtf8("listWidgetBabel"));

        gridLayout->addWidget(listWidgetBabel, 6, 1, 1, 1);

        checkBoxBabel = new QCheckBox(QuickBeamerDialog);
        checkBoxBabel->setObjectName(QString::fromUtf8("checkBoxBabel"));

        gridLayout->addWidget(checkBoxBabel, 6, 0, 1, 1);

        comboBoxEncoding = new QComboBox(QuickBeamerDialog);
        comboBoxEncoding->setObjectName(QString::fromUtf8("comboBoxEncoding"));

        gridLayout->addWidget(comboBoxEncoding, 3, 1, 1, 1);

        comboBoxTheme = new QComboBox(QuickBeamerDialog);
        comboBoxTheme->setObjectName(QString::fromUtf8("comboBoxTheme"));

        gridLayout->addWidget(comboBoxTheme, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        scrollArea = new QScrollArea(QuickBeamerDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(520, 0));
        scrollArea->setMaximumSize(QSize(520, 16777215));
        scrollArea->setAutoFillBackground(false);
        scrollArea->setWidgetResizable(false);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 510, 474));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(QuickBeamerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 2);

        QWidget::setTabOrder(comboBoxTheme, comboBoxSize);
        QWidget::setTabOrder(comboBoxSize, comboBoxEncoding);
        QWidget::setTabOrder(comboBoxEncoding, lineEditAuthor);
        QWidget::setTabOrder(lineEditAuthor, lineEditTitle);
        QWidget::setTabOrder(lineEditTitle, listWidgetBabel);
        QWidget::setTabOrder(listWidgetBabel, checkBoxBabel);
        QWidget::setTabOrder(checkBoxBabel, buttonBox);
        QWidget::setTabOrder(buttonBox, scrollArea);

        retranslateUi(QuickBeamerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuickBeamerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuickBeamerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuickBeamerDialog);
    } // setupUi

    void retranslateUi(QDialog *QuickBeamerDialog)
    {
        QuickBeamerDialog->setWindowTitle(QCoreApplication::translate("QuickBeamerDialog", "Dialog", nullptr));
        labelTheme->setText(QCoreApplication::translate("QuickBeamerDialog", "Theme", nullptr));
        labelTitle->setText(QCoreApplication::translate("QuickBeamerDialog", "Title", nullptr));
        labelEncoding->setText(QCoreApplication::translate("QuickBeamerDialog", "Encoding", nullptr));
        labelSize->setText(QCoreApplication::translate("QuickBeamerDialog", "Typeface Size", nullptr));
        labelAuthor->setText(QCoreApplication::translate("QuickBeamerDialog", "Author", nullptr));
        checkBoxBabel->setText(QCoreApplication::translate("QuickBeamerDialog", "babel Package", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuickBeamerDialog: public Ui_QuickBeamerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKBEAMERDIALOG_H
