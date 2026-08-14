/********************************************************************************
** Form generated from reading UI file 'webpublishdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBPUBLISHDIALOG_H
#define UI_WEBPUBLISHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_WebPublishDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit_2;
    QLabel *label;
    QGroupBox *latexgroupBox;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QSpinBox *compilationspinBox;
    QLabel *contentLabel;
    QLabel *startindexLabel;
    QLabel *tocdepthLabel;
    QLineEdit *contentEdit;
    QSpinBox *startindexspinBox;
    QSpinBox *tocdepthspinBox;
    QLabel *compilationLabel;
    QGroupBox *groupBoxHtml;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QLabel *navigationLabel;
    QLabel *footnoteLabel;
    QComboBox *navigationBox;
    QLabel *alignmentLabel;
    QComboBox *indexcomboBox;
    QLineEdit *footnoteEdit;
    QComboBox *alignmentcomboBox;
    QLabel *indexLabel;
    QGridLayout *gridLayout5;
    QLineEdit *browserEdit;
    QSpacerItem *spacerItem;
    QPushButton *LaunchButton;
    QTextEdit *messagetextEdit;
    QLabel *inputfileLabel;
    QPushButton *inputfileButton;
    QPushButton *quitButton;
    QLabel *browserLabel;
    QLineEdit *inputfileEdit;
    QGroupBox *imagegroupBox;
    QHBoxLayout *hboxLayout;
    QLabel *widthLabel;
    QSpinBox *widthspinBox;

    void setupUi(QDialog *WebPublishDialog)
    {
        if (WebPublishDialog->objectName().isEmpty())
            WebPublishDialog->setObjectName(QString::fromUtf8("WebPublishDialog"));
        WebPublishDialog->resize(841, 454);
        gridLayout = new QGridLayout(WebPublishDialog);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        textEdit_2 = new QTextEdit(WebPublishDialog);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setReadOnly(true);
        textEdit_2->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Bitstream Vera Sans'; font-weight:600; color:#000000;\">LaTeX to Html conversion tool</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Bitstream Vera Sans'; color:#000000;\">Copyright 2004-2006 P.Brachet &amp; J.Amblard</span></p></body></html>"));

        gridLayout->addWidget(textEdit_2, 3, 2, 1, 1);

        label = new QLabel(WebPublishDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/webpublish.png")));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        latexgroupBox = new QGroupBox(WebPublishDialog);
        latexgroupBox->setObjectName(QString::fromUtf8("latexgroupBox"));
        gridLayout1 = new QGridLayout(latexgroupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        compilationspinBox = new QSpinBox(latexgroupBox);
        compilationspinBox->setObjectName(QString::fromUtf8("compilationspinBox"));
        compilationspinBox->setMinimum(1);
        compilationspinBox->setMaximum(3);
        compilationspinBox->setValue(1);

        gridLayout2->addWidget(compilationspinBox, 0, 2, 1, 1);

        contentLabel = new QLabel(latexgroupBox);
        contentLabel->setObjectName(QString::fromUtf8("contentLabel"));

        gridLayout2->addWidget(contentLabel, 3, 0, 1, 1);

        startindexLabel = new QLabel(latexgroupBox);
        startindexLabel->setObjectName(QString::fromUtf8("startindexLabel"));

        gridLayout2->addWidget(startindexLabel, 2, 0, 1, 1);

        tocdepthLabel = new QLabel(latexgroupBox);
        tocdepthLabel->setObjectName(QString::fromUtf8("tocdepthLabel"));

        gridLayout2->addWidget(tocdepthLabel, 1, 0, 1, 1);

        contentEdit = new QLineEdit(latexgroupBox);
        contentEdit->setObjectName(QString::fromUtf8("contentEdit"));

        gridLayout2->addWidget(contentEdit, 3, 1, 1, 2);

        startindexspinBox = new QSpinBox(latexgroupBox);
        startindexspinBox->setObjectName(QString::fromUtf8("startindexspinBox"));
        startindexspinBox->setMinimum(1);
        startindexspinBox->setMaximum(5000);
        startindexspinBox->setValue(1);

        gridLayout2->addWidget(startindexspinBox, 2, 2, 1, 1);

        tocdepthspinBox = new QSpinBox(latexgroupBox);
        tocdepthspinBox->setObjectName(QString::fromUtf8("tocdepthspinBox"));
        tocdepthspinBox->setMinimum(1);
        tocdepthspinBox->setMaximum(3);
        tocdepthspinBox->setValue(2);

        gridLayout2->addWidget(tocdepthspinBox, 1, 2, 1, 1);

        compilationLabel = new QLabel(latexgroupBox);
        compilationLabel->setObjectName(QString::fromUtf8("compilationLabel"));

        gridLayout2->addWidget(compilationLabel, 0, 0, 1, 2);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);


        gridLayout->addWidget(latexgroupBox, 2, 0, 2, 1);

        groupBoxHtml = new QGroupBox(WebPublishDialog);
        groupBoxHtml->setObjectName(QString::fromUtf8("groupBoxHtml"));
        gridLayout3 = new QGridLayout(groupBoxHtml);
        gridLayout3->setSpacing(6);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        gridLayout4 = new QGridLayout();
        gridLayout4->setSpacing(6);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        gridLayout4->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(groupBoxHtml);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        gridLayout4->addWidget(titleLabel, 3, 0, 1, 1);

        titleEdit = new QLineEdit(groupBoxHtml);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));

        gridLayout4->addWidget(titleEdit, 3, 1, 1, 1);

        navigationLabel = new QLabel(groupBoxHtml);
        navigationLabel->setObjectName(QString::fromUtf8("navigationLabel"));

        gridLayout4->addWidget(navigationLabel, 2, 0, 1, 1);

        footnoteLabel = new QLabel(groupBoxHtml);
        footnoteLabel->setObjectName(QString::fromUtf8("footnoteLabel"));

        gridLayout4->addWidget(footnoteLabel, 4, 0, 1, 1);

        navigationBox = new QComboBox(groupBoxHtml);
        navigationBox->setObjectName(QString::fromUtf8("navigationBox"));

        gridLayout4->addWidget(navigationBox, 2, 1, 1, 1);

        alignmentLabel = new QLabel(groupBoxHtml);
        alignmentLabel->setObjectName(QString::fromUtf8("alignmentLabel"));

        gridLayout4->addWidget(alignmentLabel, 0, 0, 1, 1);

        indexcomboBox = new QComboBox(groupBoxHtml);
        indexcomboBox->setObjectName(QString::fromUtf8("indexcomboBox"));

        gridLayout4->addWidget(indexcomboBox, 1, 1, 1, 1);

        footnoteEdit = new QLineEdit(groupBoxHtml);
        footnoteEdit->setObjectName(QString::fromUtf8("footnoteEdit"));

        gridLayout4->addWidget(footnoteEdit, 4, 1, 1, 1);

        alignmentcomboBox = new QComboBox(groupBoxHtml);
        alignmentcomboBox->setObjectName(QString::fromUtf8("alignmentcomboBox"));

        gridLayout4->addWidget(alignmentcomboBox, 0, 1, 1, 1);

        indexLabel = new QLabel(groupBoxHtml);
        indexLabel->setObjectName(QString::fromUtf8("indexLabel"));

        gridLayout4->addWidget(indexLabel, 1, 0, 1, 1);


        gridLayout3->addLayout(gridLayout4, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxHtml, 0, 0, 1, 1);

        gridLayout5 = new QGridLayout();
        gridLayout5->setSpacing(6);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout5->setContentsMargins(0, 0, 0, 0);
        browserEdit = new QLineEdit(WebPublishDialog);
        browserEdit->setObjectName(QString::fromUtf8("browserEdit"));

        gridLayout5->addWidget(browserEdit, 1, 1, 1, 2);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout5->addItem(spacerItem, 3, 2, 1, 1);

        LaunchButton = new QPushButton(WebPublishDialog);
        LaunchButton->setObjectName(QString::fromUtf8("LaunchButton"));

        gridLayout5->addWidget(LaunchButton, 3, 0, 1, 2);

        messagetextEdit = new QTextEdit(WebPublishDialog);
        messagetextEdit->setObjectName(QString::fromUtf8("messagetextEdit"));
        messagetextEdit->setReadOnly(true);

        gridLayout5->addWidget(messagetextEdit, 2, 0, 1, 4);

        inputfileLabel = new QLabel(WebPublishDialog);
        inputfileLabel->setObjectName(QString::fromUtf8("inputfileLabel"));

        gridLayout5->addWidget(inputfileLabel, 0, 0, 1, 1);

        inputfileButton = new QPushButton(WebPublishDialog);
        inputfileButton->setObjectName(QString::fromUtf8("inputfileButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/document-open.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        inputfileButton->setIcon(icon);
        inputfileButton->setAutoDefault(true);

        gridLayout5->addWidget(inputfileButton, 0, 3, 1, 1);

        quitButton = new QPushButton(WebPublishDialog);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        gridLayout5->addWidget(quitButton, 3, 3, 1, 1);

        browserLabel = new QLabel(WebPublishDialog);
        browserLabel->setObjectName(QString::fromUtf8("browserLabel"));

        gridLayout5->addWidget(browserLabel, 1, 0, 1, 1);

        inputfileEdit = new QLineEdit(WebPublishDialog);
        inputfileEdit->setObjectName(QString::fromUtf8("inputfileEdit"));

        gridLayout5->addWidget(inputfileEdit, 0, 1, 1, 2);


        gridLayout->addLayout(gridLayout5, 0, 1, 3, 2);

        imagegroupBox = new QGroupBox(WebPublishDialog);
        imagegroupBox->setObjectName(QString::fromUtf8("imagegroupBox"));
        hboxLayout = new QHBoxLayout(imagegroupBox);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(9, 9, 9, 9);
        widthLabel = new QLabel(imagegroupBox);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        hboxLayout->addWidget(widthLabel);

        widthspinBox = new QSpinBox(imagegroupBox);
        widthspinBox->setObjectName(QString::fromUtf8("widthspinBox"));
        widthspinBox->setMinimum(10);
        widthspinBox->setMaximum(2048);
        widthspinBox->setSingleStep(10);
        widthspinBox->setValue(700);

        hboxLayout->addWidget(widthspinBox);


        gridLayout->addWidget(imagegroupBox, 1, 0, 1, 1);

        QWidget::setTabOrder(alignmentcomboBox, indexcomboBox);
        QWidget::setTabOrder(indexcomboBox, navigationBox);
        QWidget::setTabOrder(navigationBox, titleEdit);
        QWidget::setTabOrder(titleEdit, footnoteEdit);
        QWidget::setTabOrder(footnoteEdit, widthspinBox);
        QWidget::setTabOrder(widthspinBox, compilationspinBox);
        QWidget::setTabOrder(compilationspinBox, tocdepthspinBox);
        QWidget::setTabOrder(tocdepthspinBox, startindexspinBox);
        QWidget::setTabOrder(startindexspinBox, contentEdit);
        QWidget::setTabOrder(contentEdit, inputfileEdit);
        QWidget::setTabOrder(inputfileEdit, inputfileButton);
        QWidget::setTabOrder(inputfileButton, browserEdit);
        QWidget::setTabOrder(browserEdit, LaunchButton);
        QWidget::setTabOrder(LaunchButton, quitButton);
        QWidget::setTabOrder(quitButton, textEdit_2);
        QWidget::setTabOrder(textEdit_2, messagetextEdit);

        retranslateUi(WebPublishDialog);

        QMetaObject::connectSlotsByName(WebPublishDialog);
    } // setupUi

    void retranslateUi(QDialog *WebPublishDialog)
    {
        WebPublishDialog->setWindowTitle(QCoreApplication::translate("WebPublishDialog", "Convert to Html", nullptr));
        label->setText(QString());
        latexgroupBox->setTitle(QCoreApplication::translate("WebPublishDialog", "LaTeX options", nullptr));
#if QT_CONFIG(tooltip)
        compilationspinBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Number of LaTeX compilations for the input file", nullptr));
#endif // QT_CONFIG(tooltip)
        contentLabel->setText(QCoreApplication::translate("WebPublishDialog", "Content name :", nullptr));
        startindexLabel->setText(QCoreApplication::translate("WebPublishDialog", "Start Index :", nullptr));
        tocdepthLabel->setText(QCoreApplication::translate("WebPublishDialog", "Tocdepth :", nullptr));
#if QT_CONFIG(tooltip)
        contentEdit->setToolTip(QCoreApplication::translate("WebPublishDialog", "LaTeX code for the title of the table of contents", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        startindexspinBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "The number of the ps page corresponding to the first numberline indexed in the toc file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tocdepthspinBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Set the value of the LaTeX tocdepth counter", nullptr));
#endif // QT_CONFIG(tooltip)
        compilationLabel->setText(QCoreApplication::translate("WebPublishDialog", "Number of compilations :", nullptr));
        groupBoxHtml->setTitle(QCoreApplication::translate("WebPublishDialog", "Html options", nullptr));
        titleLabel->setText(QCoreApplication::translate("WebPublishDialog", "Title :", nullptr));
#if QT_CONFIG(tooltip)
        titleEdit->setToolTip(QCoreApplication::translate("WebPublishDialog", "Title of the html files", nullptr));
#endif // QT_CONFIG(tooltip)
        navigationLabel->setText(QCoreApplication::translate("WebPublishDialog", "Navigation :", nullptr));
        footnoteLabel->setText(QCoreApplication::translate("WebPublishDialog", "Footnote :", nullptr));
#if QT_CONFIG(tooltip)
        navigationBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Navigation mode", nullptr));
#endif // QT_CONFIG(tooltip)
        alignmentLabel->setText(QCoreApplication::translate("WebPublishDialog", "Alignment :", nullptr));
#if QT_CONFIG(tooltip)
        indexcomboBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Create an index page ?", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        footnoteEdit->setToolTip(QCoreApplication::translate("WebPublishDialog", "Text displayed at the bottom of each html files ", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        alignmentcomboBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Alignment in the html files", nullptr));
#endif // QT_CONFIG(tooltip)
        indexLabel->setText(QCoreApplication::translate("WebPublishDialog", "Create index :", nullptr));
#if QT_CONFIG(tooltip)
        browserEdit->setToolTip(QCoreApplication::translate("WebPublishDialog", "<html><head/><body><p>Browser command. Leave empty to not run the browser at the end of the conversion</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        LaunchButton->setText(QCoreApplication::translate("WebPublishDialog", "Launch", nullptr));
        inputfileLabel->setText(QCoreApplication::translate("WebPublishDialog", "Input File :", nullptr));
        inputfileButton->setText(QString());
        quitButton->setText(QCoreApplication::translate("WebPublishDialog", "Close", nullptr));
        browserLabel->setText(QCoreApplication::translate("WebPublishDialog", "Browser :", nullptr));
        imagegroupBox->setTitle(QCoreApplication::translate("WebPublishDialog", "Images options", nullptr));
        widthLabel->setText(QCoreApplication::translate("WebPublishDialog", "Images Width :", nullptr));
#if QT_CONFIG(tooltip)
        widthspinBox->setToolTip(QCoreApplication::translate("WebPublishDialog", "Width of the largest image", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class WebPublishDialog: public Ui_WebPublishDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBPUBLISHDIALOG_H
