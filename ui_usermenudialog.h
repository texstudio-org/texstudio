/********************************************************************************
** Form generated from reading UI file 'usermenudialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMENUDIALOG_H
#define UI_USERMENUDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMenuDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *tbExport;
    QPushButton *pbImport;
    QPushButton *pbBrowse;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonAddFolder;
    QPushButton *pushButtonRemove;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QWidget *verticalLayoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *itemEdit;
    QLabel *label_3;
    QLineEdit *abbrevEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLabel *triggerHelp;
    QLineEdit *triggerEdit;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButtonNormal;
    QRadioButton *radioButtonEnvironment;
    QRadioButton *radioButtonScript;
    QRadioButton *radioButtonAIQuery;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_1;
    QWidget *tagEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *runScriptButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *cbShortcut;
    QPlainTextEdit *teDescription;

    void setupUi(QDialog *UserMenuDialog)
    {
        if (UserMenuDialog->objectName().isEmpty())
            UserMenuDialog->setObjectName(QString::fromUtf8("UserMenuDialog"));
        UserMenuDialog->resize(942, 456);
        QFont font;
        font.setUnderline(false);
        UserMenuDialog->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(UserMenuDialog);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter = new QSplitter(UserMenuDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Orientation::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(verticalLayoutWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        treeWidget->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        treeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        treeWidget->setHeaderHidden(false);
        treeWidget->setColumnCount(4);
        treeWidget->header()->setVisible(true);

        verticalLayout->addWidget(treeWidget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        tbExport = new QToolButton(verticalLayoutWidget);
        tbExport->setObjectName(QString::fromUtf8("tbExport"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbExport->sizePolicy().hasHeightForWidth());
        tbExport->setSizePolicy(sizePolicy1);
        tbExport->setMinimumSize(QSize(100, 0));
        tbExport->setPopupMode(QToolButton::ToolButtonPopupMode::MenuButtonPopup);
        tbExport->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
        tbExport->setArrowType(Qt::ArrowType::DownArrow);

        horizontalLayout_7->addWidget(tbExport);

        pbImport = new QPushButton(verticalLayoutWidget);
        pbImport->setObjectName(QString::fromUtf8("pbImport"));

        horizontalLayout_7->addWidget(pbImport);

        pbBrowse = new QPushButton(verticalLayoutWidget);
        pbBrowse->setObjectName(QString::fromUtf8("pbBrowse"));

        horizontalLayout_7->addWidget(pbBrowse);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonAdd = new QPushButton(verticalLayoutWidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonAdd->sizePolicy().hasHeightForWidth());
        pushButtonAdd->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/list-add.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAdd->setIcon(icon);

        horizontalLayout->addWidget(pushButtonAdd);

        pushButtonAddFolder = new QPushButton(verticalLayoutWidget);
        pushButtonAddFolder->setObjectName(QString::fromUtf8("pushButtonAddFolder"));
        pushButtonAddFolder->setIcon(icon);

        horizontalLayout->addWidget(pushButtonAddFolder);

        pushButtonRemove = new QPushButton(verticalLayoutWidget);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));
        sizePolicy2.setHeightForWidth(pushButtonRemove->sizePolicy().hasHeightForWidth());
        pushButtonRemove->setSizePolicy(sizePolicy2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images-ng/list-remove.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemove->setIcon(icon1);

        horizontalLayout->addWidget(pushButtonRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonUp = new QPushButton(verticalLayoutWidget);
        pushButtonUp->setObjectName(QString::fromUtf8("pushButtonUp"));
        sizePolicy2.setHeightForWidth(pushButtonUp->sizePolicy().hasHeightForWidth());
        pushButtonUp->setSizePolicy(sizePolicy2);
        pushButtonUp->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images-ng/up.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUp->setIcon(icon2);

        horizontalLayout->addWidget(pushButtonUp);

        pushButtonDown = new QPushButton(verticalLayoutWidget);
        pushButtonDown->setObjectName(QString::fromUtf8("pushButtonDown"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButtonDown->sizePolicy().hasHeightForWidth());
        pushButtonDown->setSizePolicy(sizePolicy3);
        pushButtonDown->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images-ng/down.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDown->setIcon(icon3);

        horizontalLayout->addWidget(pushButtonDown);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(verticalLayoutWidget);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        gridLayout = new QGridLayout(verticalLayoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        itemEdit = new QLineEdit(verticalLayoutWidget_2);
        itemEdit->setObjectName(QString::fromUtf8("itemEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(itemEdit->sizePolicy().hasHeightForWidth());
        itemEdit->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(itemEdit, 0, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        abbrevEdit = new QLineEdit(verticalLayoutWidget_2);
        abbrevEdit->setObjectName(QString::fromUtf8("abbrevEdit"));

        gridLayout->addWidget(abbrevEdit, 2, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        triggerHelp = new QLabel(verticalLayoutWidget_2);
        triggerHelp->setObjectName(QString::fromUtf8("triggerHelp"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(triggerHelp->sizePolicy().hasHeightForWidth());
        triggerHelp->setSizePolicy(sizePolicy5);
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(118, 118, 117, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        triggerHelp->setPalette(palette);
        triggerHelp->setFrameShape(QFrame::Shape::Box);
        triggerHelp->setText(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Bright'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"#\"><span style=\" text-decoration: underline; color:#0000ff;\">?</span></a></p></body></html>"));

        horizontalLayout_5->addWidget(triggerHelp);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        triggerEdit = new QLineEdit(verticalLayoutWidget_2);
        triggerEdit->setObjectName(QString::fromUtf8("triggerEdit"));

        gridLayout->addWidget(triggerEdit, 3, 1, 1, 1);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButtonNormal = new QRadioButton(verticalLayoutWidget_2);
        radioButtonNormal->setObjectName(QString::fromUtf8("radioButtonNormal"));

        horizontalLayout_4->addWidget(radioButtonNormal);

        radioButtonEnvironment = new QRadioButton(verticalLayoutWidget_2);
        radioButtonEnvironment->setObjectName(QString::fromUtf8("radioButtonEnvironment"));

        horizontalLayout_4->addWidget(radioButtonEnvironment);

        radioButtonScript = new QRadioButton(verticalLayoutWidget_2);
        radioButtonScript->setObjectName(QString::fromUtf8("radioButtonScript"));

        horizontalLayout_4->addWidget(radioButtonScript);

        radioButtonAIQuery = new QRadioButton(verticalLayoutWidget_2);
        radioButtonAIQuery->setObjectName(QString::fromUtf8("radioButtonAIQuery"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(radioButtonAIQuery->sizePolicy().hasHeightForWidth());
        radioButtonAIQuery->setSizePolicy(sizePolicy6);

        horizontalLayout_4->addWidget(radioButtonAIQuery);


        gridLayout->addLayout(horizontalLayout_4, 5, 1, 1, 1);

        groupBox = new QGroupBox(verticalLayoutWidget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_1 = new QHBoxLayout(groupBox);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(1, 1, 1, 1);
        tagEdit = new QWidget(groupBox);
        tagEdit->setObjectName(QString::fromUtf8("tagEdit"));
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(tagEdit->sizePolicy().hasHeightForWidth());
        tagEdit->setSizePolicy(sizePolicy7);

        horizontalLayout_1->addWidget(tagEdit);


        gridLayout->addWidget(groupBox, 6, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        runScriptButton = new QPushButton(verticalLayoutWidget_2);
        runScriptButton->setObjectName(QString::fromUtf8("runScriptButton"));
        runScriptButton->setEnabled(true);

        horizontalLayout_2->addWidget(runScriptButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        okButton = new QPushButton(verticalLayoutWidget_2);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(verticalLayoutWidget_2);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout_2, 7, 0, 1, 2);

        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        cbShortcut = new QComboBox(verticalLayoutWidget_2);
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->addItem(QString());
        cbShortcut->setObjectName(QString::fromUtf8("cbShortcut"));
        cbShortcut->setEditable(true);

        gridLayout->addWidget(cbShortcut, 4, 1, 1, 1);

        teDescription = new QPlainTextEdit(verticalLayoutWidget_2);
        teDescription->setObjectName(QString::fromUtf8("teDescription"));
        teDescription->setMinimumSize(QSize(0, 192));

        gridLayout->addWidget(teDescription, 1, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        splitter->addWidget(verticalLayoutWidget_2);

        horizontalLayout_3->addWidget(splitter);

        QWidget::setTabOrder(treeWidget, itemEdit);
        QWidget::setTabOrder(itemEdit, teDescription);
        QWidget::setTabOrder(teDescription, abbrevEdit);
        QWidget::setTabOrder(abbrevEdit, triggerEdit);
        QWidget::setTabOrder(triggerEdit, cbShortcut);
        QWidget::setTabOrder(cbShortcut, radioButtonNormal);
        QWidget::setTabOrder(radioButtonNormal, radioButtonEnvironment);
        QWidget::setTabOrder(radioButtonEnvironment, radioButtonScript);
        QWidget::setTabOrder(radioButtonScript, radioButtonAIQuery);
        QWidget::setTabOrder(radioButtonAIQuery, pushButtonAdd);
        QWidget::setTabOrder(pushButtonAdd, pushButtonAddFolder);
        QWidget::setTabOrder(pushButtonAddFolder, pushButtonRemove);
        QWidget::setTabOrder(pushButtonRemove, tbExport);
        QWidget::setTabOrder(tbExport, pbImport);
        QWidget::setTabOrder(pbImport, pbBrowse);
        QWidget::setTabOrder(pbBrowse, pushButtonUp);
        QWidget::setTabOrder(pushButtonUp, pushButtonDown);
        QWidget::setTabOrder(pushButtonDown, runScriptButton);
        QWidget::setTabOrder(runScriptButton, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(UserMenuDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), UserMenuDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UserMenuDialog);
    } // setupUi

    void retranslateUi(QDialog *UserMenuDialog)
    {
        UserMenuDialog->setWindowTitle(QCoreApplication::translate("UserMenuDialog", "Edit Macros", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("UserMenuDialog", "Abbreviation", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("UserMenuDialog", "Trigger", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("UserMenuDialog", "Shortcut", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("UserMenuDialog", "Name", nullptr));
#if QT_CONFIG(tooltip)
        tbExport->setToolTip(QCoreApplication::translate("UserMenuDialog", "Export macro(s) to file(s)", nullptr));
#endif // QT_CONFIG(tooltip)
        tbExport->setText(QCoreApplication::translate("UserMenuDialog", "Export", nullptr));
#if QT_CONFIG(tooltip)
        pbImport->setToolTip(QCoreApplication::translate("UserMenuDialog", "Import macro from file", nullptr));
#endif // QT_CONFIG(tooltip)
        pbImport->setText(QCoreApplication::translate("UserMenuDialog", "Import", nullptr));
#if QT_CONFIG(tooltip)
        pbBrowse->setToolTip(QCoreApplication::translate("UserMenuDialog", "Browse offered macros on txs site.", nullptr));
#endif // QT_CONFIG(tooltip)
        pbBrowse->setText(QCoreApplication::translate("UserMenuDialog", "Browse", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("UserMenuDialog", "Add", nullptr));
        pushButtonAddFolder->setText(QCoreApplication::translate("UserMenuDialog", "Folder", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("UserMenuDialog", "Remove", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("UserMenuDialog", "Up", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("UserMenuDialog", "Down", nullptr));
        label->setText(QCoreApplication::translate("UserMenuDialog", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("UserMenuDialog", "Abbreviation", nullptr));
        label_5->setText(QCoreApplication::translate("UserMenuDialog", "Trigger", nullptr));
#if QT_CONFIG(tooltip)
        triggerHelp->setToolTip(QCoreApplication::translate("UserMenuDialog", "If this trigger string is written in any tex document, \n"
"it is replaced by the current tag.\n"
"\n"
"If the trigger starts with (?<=something), this only happens \n"
"if something is written before the remaining part of the trigger.\n"
"\n"
"Since this trigger is not a plain string, but a regular expression, \n"
"(?<=\\S) can be used to mark replacements which should only occur after a word, \n"
"and (?<=\\s|^) to mark replacements which should only occur before a word.\n"
"\n"
"\n"
"You can use the special value ?txs-start to start the script at txs start.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("UserMenuDialog", "Type", nullptr));
        radioButtonNormal->setText(QCoreApplication::translate("UserMenuDialog", "Normal", nullptr));
        radioButtonEnvironment->setText(QCoreApplication::translate("UserMenuDialog", "Environment", nullptr));
        radioButtonScript->setText(QCoreApplication::translate("UserMenuDialog", "Script", nullptr));
        radioButtonAIQuery->setText(QCoreApplication::translate("UserMenuDialog", "AI Query", nullptr));
        runScriptButton->setText(QCoreApplication::translate("UserMenuDialog", "Exec Macro", nullptr));
        okButton->setText(QCoreApplication::translate("UserMenuDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("UserMenuDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("UserMenuDialog", "Description", nullptr));
        label_7->setText(QCoreApplication::translate("UserMenuDialog", "Shortcut", nullptr));
        cbShortcut->setItemText(0, QString());
        cbShortcut->setItemText(1, QCoreApplication::translate("UserMenuDialog", "Shift+F1", nullptr));
        cbShortcut->setItemText(2, QCoreApplication::translate("UserMenuDialog", "Shift+F2", nullptr));
        cbShortcut->setItemText(3, QCoreApplication::translate("UserMenuDialog", "Shift+F4", nullptr));
        cbShortcut->setItemText(4, QCoreApplication::translate("UserMenuDialog", "Shift+F5", nullptr));
        cbShortcut->setItemText(5, QCoreApplication::translate("UserMenuDialog", "Shift+F5", nullptr));
        cbShortcut->setItemText(6, QCoreApplication::translate("UserMenuDialog", "Shift+F6", nullptr));
        cbShortcut->setItemText(7, QCoreApplication::translate("UserMenuDialog", "Shift+F7", nullptr));
        cbShortcut->setItemText(8, QCoreApplication::translate("UserMenuDialog", "Shift+F8", nullptr));
        cbShortcut->setItemText(9, QCoreApplication::translate("UserMenuDialog", "Shift+F9", nullptr));
        cbShortcut->setItemText(10, QCoreApplication::translate("UserMenuDialog", "Shift+F10", nullptr));
        cbShortcut->setItemText(11, QCoreApplication::translate("UserMenuDialog", "Shift+F11", nullptr));
        cbShortcut->setItemText(12, QCoreApplication::translate("UserMenuDialog", "Shift+F12", nullptr));

    } // retranslateUi

};

namespace Ui {
    class UserMenuDialog: public Ui_UserMenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMENUDIALOG_H
