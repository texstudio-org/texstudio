/********************************************************************************
** Form generated from reading UI file 'userquickdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERQUICKDIALOG_H
#define UI_USERQUICKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserQuickDialog
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *commandWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *addButton;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *labelList;
    QListWidget *listWidget;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *deleteButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UserQuickDialog)
    {
        if (UserQuickDialog->objectName().isEmpty())
            UserQuickDialog->setObjectName(QString::fromUtf8("UserQuickDialog"));
        UserQuickDialog->resize(622, 283);
        gridLayout_2 = new QGridLayout(UserQuickDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        commandWidget = new QListWidget(UserQuickDialog);
        commandWidget->setObjectName(QString::fromUtf8("commandWidget"));

        verticalLayout_2->addWidget(commandWidget);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        addButton = new QPushButton(UserQuickDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/right.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);

        verticalLayout->addWidget(addButton);

        verticalSpacer = new QSpacerItem(88, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelList = new QLabel(UserQuickDialog);
        labelList->setObjectName(QString::fromUtf8("labelList"));

        gridLayout->addWidget(labelList, 0, 0, 1, 3);

        listWidget = new QListWidget(UserQuickDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 3);

        upButton = new QPushButton(UserQuickDialog);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images-ng/up.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon1);

        gridLayout->addWidget(upButton, 2, 0, 1, 1);

        downButton = new QPushButton(UserQuickDialog);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images-ng/down.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        downButton->setIcon(icon2);

        gridLayout->addWidget(downButton, 2, 1, 1, 1);

        deleteButton = new QPushButton(UserQuickDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        gridLayout->addWidget(deleteButton, 2, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 2, 1, 1);

        buttonBox = new QDialogButtonBox(UserQuickDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 3);

        QWidget::setTabOrder(commandWidget, addButton);
        QWidget::setTabOrder(addButton, upButton);
        QWidget::setTabOrder(upButton, downButton);
        QWidget::setTabOrder(downButton, deleteButton);
        QWidget::setTabOrder(deleteButton, buttonBox);
        QWidget::setTabOrder(buttonBox, listWidget);

        retranslateUi(UserQuickDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UserQuickDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UserQuickDialog, SLOT(reject()));
        QObject::connect(commandWidget, SIGNAL(doubleClicked(QModelIndex)), addButton, SLOT(click()));

        QMetaObject::connectSlotsByName(UserQuickDialog);
    } // setupUi

    void retranslateUi(QDialog *UserQuickDialog)
    {
        UserQuickDialog->setWindowTitle(QCoreApplication::translate("UserQuickDialog", "Quick Build Command", nullptr));
        addButton->setText(QCoreApplication::translate("UserQuickDialog", "Add", nullptr));
        labelList->setText(QCoreApplication::translate("UserQuickDialog", "Ordered list of commands:", nullptr));
        upButton->setText(QCoreApplication::translate("UserQuickDialog", "Up", nullptr));
        downButton->setText(QCoreApplication::translate("UserQuickDialog", "Down", nullptr));
        deleteButton->setText(QCoreApplication::translate("UserQuickDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserQuickDialog: public Ui_UserQuickDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERQUICKDIALOG_H
