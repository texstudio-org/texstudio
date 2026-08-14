/********************************************************************************
** Form generated from reading UI file 'templateselector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATESELECTOR_H
#define UI_TEMPLATESELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_templateSelectorDialog
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *lbName;
    QLabel *lbDescription;
    QLabel *lbAuthorTag;
    QLabel *lbAuthor;
    QLabel *lbVersion;
    QLabel *lbDate;
    QLabel *lbLicense;
    QLabel *previewLabelDummy;
    QTreeWidget *templatesTree;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbCreateInFolder;
    QLineEdit *lePath;
    QPushButton *btPath;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbCreateInEditor;
    QHBoxLayout *horizontalLayout_3;
    QLabel *warningIcon;
    QLabel *warningText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *templateSelectorDialog)
    {
        if (templateSelectorDialog->objectName().isEmpty())
            templateSelectorDialog->setObjectName(QString::fromUtf8("templateSelectorDialog"));
        templateSelectorDialog->resize(793, 462);
        gridLayout = new QGridLayout(templateSelectorDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(templateSelectorDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbName = new QLabel(frame);
        lbName->setObjectName(QString::fromUtf8("lbName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbName->sizePolicy().hasHeightForWidth());
        lbName->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        lbName->setFont(font);
        lbName->setText(QString::fromUtf8("Template Title"));

        verticalLayout->addWidget(lbName);

        lbDescription = new QLabel(frame);
        lbDescription->setObjectName(QString::fromUtf8("lbDescription"));
        lbDescription->setText(QString::fromUtf8("The template description will be displayed here."));
        lbDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lbDescription->setWordWrap(true);

        verticalLayout->addWidget(lbDescription);

        lbAuthorTag = new QLabel(frame);
        lbAuthorTag->setObjectName(QString::fromUtf8("lbAuthorTag"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbAuthorTag->sizePolicy().hasHeightForWidth());
        lbAuthorTag->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lbAuthorTag);

        lbAuthor = new QLabel(frame);
        lbAuthor->setObjectName(QString::fromUtf8("lbAuthor"));
        lbAuthor->setText(QString::fromUtf8("This is the author description. You may use basic HTML."));
        lbAuthor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lbAuthor->setWordWrap(true);
        lbAuthor->setOpenExternalLinks(true);

        verticalLayout->addWidget(lbAuthor);

        lbVersion = new QLabel(frame);
        lbVersion->setObjectName(QString::fromUtf8("lbVersion"));
        sizePolicy1.setHeightForWidth(lbVersion->sizePolicy().hasHeightForWidth());
        lbVersion->setSizePolicy(sizePolicy1);
        lbVersion->setText(QString::fromUtf8("Version: 1.0"));

        verticalLayout->addWidget(lbVersion);

        lbDate = new QLabel(frame);
        lbDate->setObjectName(QString::fromUtf8("lbDate"));
        sizePolicy1.setHeightForWidth(lbDate->sizePolicy().hasHeightForWidth());
        lbDate->setSizePolicy(sizePolicy1);
        lbDate->setText(QString::fromUtf8("Date: 25.10.2012"));

        verticalLayout->addWidget(lbDate);

        lbLicense = new QLabel(frame);
        lbLicense->setObjectName(QString::fromUtf8("lbLicense"));
        sizePolicy1.setHeightForWidth(lbLicense->sizePolicy().hasHeightForWidth());
        lbLicense->setSizePolicy(sizePolicy1);
        lbLicense->setText(QString::fromUtf8("License: suggested Public Domain or Creative Commons"));

        verticalLayout->addWidget(lbLicense);


        gridLayout->addWidget(frame, 0, 1, 1, 1);

        previewLabelDummy = new QLabel(templateSelectorDialog);
        previewLabelDummy->setObjectName(QString::fromUtf8("previewLabelDummy"));
        previewLabelDummy->setMinimumSize(QSize(243, 310));
        previewLabelDummy->setFrameShape(QFrame::Box);
        previewLabelDummy->setFrameShadow(QFrame::Plain);
        previewLabelDummy->setText(QString::fromUtf8("dummy - will be replaced programmatically"));
        previewLabelDummy->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(previewLabelDummy, 0, 2, 1, 1);

        templatesTree = new QTreeWidget(templateSelectorDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        templatesTree->setHeaderItem(__qtreewidgetitem);
        templatesTree->setObjectName(QString::fromUtf8("templatesTree"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(templatesTree->sizePolicy().hasHeightForWidth());
        templatesTree->setSizePolicy(sizePolicy2);
        templatesTree->header()->setVisible(false);

        gridLayout->addWidget(templatesTree, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rbCreateInFolder = new QRadioButton(templateSelectorDialog);
        rbCreateInFolder->setObjectName(QString::fromUtf8("rbCreateInFolder"));

        horizontalLayout_2->addWidget(rbCreateInFolder);

        lePath = new QLineEdit(templateSelectorDialog);
        lePath->setObjectName(QString::fromUtf8("lePath"));
        lePath->setEnabled(false);

        horizontalLayout_2->addWidget(lePath);

        btPath = new QPushButton(templateSelectorDialog);
        btPath->setObjectName(QString::fromUtf8("btPath"));
        btPath->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/document-open.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        btPath->setIcon(icon);

        horizontalLayout_2->addWidget(btPath);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rbCreateInEditor = new QRadioButton(templateSelectorDialog);
        rbCreateInEditor->setObjectName(QString::fromUtf8("rbCreateInEditor"));
        rbCreateInEditor->setChecked(true);

        horizontalLayout->addWidget(rbCreateInEditor);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        warningIcon = new QLabel(templateSelectorDialog);
        warningIcon->setObjectName(QString::fromUtf8("warningIcon"));
        warningIcon->setMaximumSize(QSize(16, 16));
        warningIcon->setPixmap(QPixmap(QString::fromUtf8(":/images-ng/warning.svgz")));
        warningIcon->setScaledContents(true);

        horizontalLayout_3->addWidget(warningIcon);

        warningText = new QLabel(templateSelectorDialog);
        warningText->setObjectName(QString::fromUtf8("warningText"));

        horizontalLayout_3->addWidget(warningText);

        buttonBox = new QDialogButtonBox(templateSelectorDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 3);

        gridLayout->setColumnStretch(0, 2);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 3);

        retranslateUi(templateSelectorDialog);

        QMetaObject::connectSlotsByName(templateSelectorDialog);
    } // setupUi

    void retranslateUi(QDialog *templateSelectorDialog)
    {
        templateSelectorDialog->setWindowTitle(QCoreApplication::translate("templateSelectorDialog", "Dialog", nullptr));
        lbAuthorTag->setText(QCoreApplication::translate("templateSelectorDialog", "Author:", nullptr));
        rbCreateInFolder->setText(QCoreApplication::translate("templateSelectorDialog", "Create in Folder:", nullptr));
        btPath->setText(QString());
        rbCreateInEditor->setText(QCoreApplication::translate("templateSelectorDialog", "Create in Editor", nullptr));
        warningIcon->setText(QString());
        warningText->setText(QCoreApplication::translate("templateSelectorDialog", "Target folder not empty.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class templateSelectorDialog: public Ui_templateSelectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATESELECTOR_H
