/********************************************************************************
** Form generated from reading UI file 'arraydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRAYDIALOG_H
#define UI_ARRAYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ArrayDialog
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QLabel *label_3;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QSpinBox *spinBoxColumns;
    QLabel *label;
    QComboBox *comboAlignment;
    QSpinBox *spinBoxRows;
    QLabel *label_4;
    QComboBox *comboEnvironment;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ArrayDialog)
    {
        if (ArrayDialog->objectName().isEmpty())
            ArrayDialog->setObjectName(QString::fromUtf8("ArrayDialog"));
        ArrayDialog->resize(472, 393);
        gridLayout = new QGridLayout(ArrayDialog);
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
        label_3 = new QLabel(ArrayDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout1->addWidget(label_3, 2, 0, 1, 1);

        tableWidget = new QTableWidget(ArrayDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);

        gridLayout1->addWidget(tableWidget, 0, 0, 1, 2);

        label_2 = new QLabel(ArrayDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout1->addWidget(label_2, 5, 0, 1, 1);

        spinBoxColumns = new QSpinBox(ArrayDialog);
        spinBoxColumns->setObjectName(QString::fromUtf8("spinBoxColumns"));
        spinBoxColumns->setMinimum(1);

        gridLayout1->addWidget(spinBoxColumns, 2, 1, 1, 1);

        label = new QLabel(ArrayDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 4, 0, 1, 1);

        comboAlignment = new QComboBox(ArrayDialog);
        comboAlignment->setObjectName(QString::fromUtf8("comboAlignment"));
        comboAlignment->setMaxVisibleItems(11);

        gridLayout1->addWidget(comboAlignment, 5, 1, 1, 1);

        spinBoxRows = new QSpinBox(ArrayDialog);
        spinBoxRows->setObjectName(QString::fromUtf8("spinBoxRows"));

        gridLayout1->addWidget(spinBoxRows, 1, 1, 1, 1);

        label_4 = new QLabel(ArrayDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout1->addWidget(label_4, 1, 0, 1, 1);

        comboEnvironment = new QComboBox(ArrayDialog);
        comboEnvironment->setObjectName(QString::fromUtf8("comboEnvironment"));
        comboEnvironment->setMaxVisibleItems(16);

        gridLayout1->addWidget(comboEnvironment, 4, 1, 1, 1);

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

        okButton = new QPushButton(ArrayDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(ArrayDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(ArrayDialog);
        QObject::connect(okButton, SIGNAL(clicked()), ArrayDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ArrayDialog, SLOT(reject()));

        comboAlignment->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ArrayDialog);
    } // setupUi

    void retranslateUi(QDialog *ArrayDialog)
    {
        label_3->setText(QCoreApplication::translate("ArrayDialog", "Num of Columns", nullptr));
        label_2->setText(QCoreApplication::translate("ArrayDialog", "Columns Alignment", nullptr));
        label->setText(QCoreApplication::translate("ArrayDialog", "Environment", nullptr));
#if QT_CONFIG(tooltip)
        comboAlignment->setToolTip(QCoreApplication::translate("ArrayDialog", "In case of an array environment sets the alignment for the column of the currently selected cell.\n"
"For matrix* and the like (package mathtools) sets the alignment for all columns at once.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("ArrayDialog", "Num of Rows", nullptr));
#if QT_CONFIG(tooltip)
        comboEnvironment->setToolTip(QCoreApplication::translate("ArrayDialog", "Choose environment to be created (s. window title).\n"
"Package amsmath supports alignedat, matrix, pmatrix, bmatrix, Bmatrix, vmatrix, Vmatrix.\n"
"Package mathtools supports alignedat, matrix*, pmatrix*, bmatrix*, Bmatrix*, vmatrix*, Vmatrix*.", nullptr));
#endif // QT_CONFIG(tooltip)
        okButton->setText(QCoreApplication::translate("ArrayDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("ArrayDialog", "Cancel", nullptr));
        (void)ArrayDialog;
    } // retranslateUi

};

namespace Ui {
    class ArrayDialog: public Ui_ArrayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARRAYDIALOG_H
