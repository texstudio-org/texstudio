/********************************************************************************
** Form generated from reading UI file 'pdfsplittool.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFSPLITTOOL_H
#define UI_PDFSPLITTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PDFSplitTool
{
public:
    QGridLayout *gridLayout;
    QLineEdit *outputFileEdit;
    QVBoxLayout *inputFileLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *go;
    QLabel *label;
    QRadioButton *backendGS;
    QRadioButton *backendPDFLatex;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;
    QLabel *label_2;
    QPushButton *addInput;
    QPushButton *outputFileButton;

    void setupUi(QDialog *PDFSplitTool)
    {
        if (PDFSplitTool->objectName().isEmpty())
            PDFSplitTool->setObjectName(QString::fromUtf8("PDFSplitTool"));
        PDFSplitTool->resize(691, 174);
        gridLayout = new QGridLayout(PDFSplitTool);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        outputFileEdit = new QLineEdit(PDFSplitTool);
        outputFileEdit->setObjectName(QString::fromUtf8("outputFileEdit"));

        gridLayout->addWidget(outputFileEdit, 0, 1, 1, 2);

        inputFileLayout = new QVBoxLayout();
        inputFileLayout->setObjectName(QString::fromUtf8("inputFileLayout"));

        gridLayout->addLayout(inputFileLayout, 2, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        go = new QPushButton(PDFSplitTool);
        go->setObjectName(QString::fromUtf8("go"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(go->sizePolicy().hasHeightForWidth());
        go->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        go->setFont(font);

        horizontalLayout->addWidget(go);

        label = new QLabel(PDFSplitTool);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        backendGS = new QRadioButton(PDFSplitTool);
        backendGS->setObjectName(QString::fromUtf8("backendGS"));
        backendGS->setText(QString::fromUtf8("Ghostscript"));
        backendGS->setChecked(true);

        horizontalLayout->addWidget(backendGS);

        backendPDFLatex = new QRadioButton(PDFSplitTool);
        backendPDFLatex->setObjectName(QString::fromUtf8("backendPDFLatex"));
        backendPDFLatex->setText(QString::fromUtf8("pdfpages"));

        horizontalLayout->addWidget(backendPDFLatex);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel = new QPushButton(PDFSplitTool);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout->addWidget(cancel);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 4);

        label_2 = new QLabel(PDFSplitTool);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        addInput = new QPushButton(PDFSplitTool);
        addInput->setObjectName(QString::fromUtf8("addInput"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addInput->sizePolicy().hasHeightForWidth());
        addInput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(addInput, 3, 0, 1, 1);

        outputFileButton = new QPushButton(PDFSplitTool);
        outputFileButton->setObjectName(QString::fromUtf8("outputFileButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/document-open.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        outputFileButton->setIcon(icon);

        gridLayout->addWidget(outputFileButton, 0, 3, 1, 1);


        retranslateUi(PDFSplitTool);

        QMetaObject::connectSlotsByName(PDFSplitTool);
    } // setupUi

    void retranslateUi(QDialog *PDFSplitTool)
    {
        PDFSplitTool->setWindowTitle(QCoreApplication::translate("PDFSplitTool", "Split & Merge", nullptr));
        go->setText(QCoreApplication::translate("PDFSplitTool", "Split && Merge", nullptr));
        label->setText(QCoreApplication::translate("PDFSplitTool", "Backend:", nullptr));
        cancel->setText(QCoreApplication::translate("PDFSplitTool", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("PDFSplitTool", "Output file:", nullptr));
        addInput->setText(QCoreApplication::translate("PDFSplitTool", "Add input file", nullptr));
        outputFileButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PDFSplitTool: public Ui_PDFSplitTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFSPLITTOOL_H
