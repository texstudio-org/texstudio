/********************************************************************************
** Form generated from reading UI file 'tabdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABDIALOG_H
#define UI_TABDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TabDialog
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBoxColumns;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxColumns;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QSpinBox *spinBoxNumCol;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QComboBox *comboBoxColAl;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QComboBox *comboLeftBorder;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonColumns;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QComboBox *comboBoxEndBorder;
    QSpacerItem *horizontalSpacer_8;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QSpinBox *spinBoxRows;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBoxLines;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpinBox *spinBoxNumLi;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *checkBoxBorderTop;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBoxSpan;
    QSpinBox *spinBoxSpanFrom;
    QLabel *label_8;
    QSpinBox *spinBoxSpanTo;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButtonLines;
    QSpacerItem *horizontalSpacer_12;
    QCheckBox *checkBoxBorderBottom;
    QCheckBox *checkBoxMargin;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TabDialog)
    {
        if (TabDialog->objectName().isEmpty())
            TabDialog->setObjectName(QString::fromUtf8("TabDialog"));
        TabDialog->resize(693, 572);
        gridLayout = new QGridLayout(TabDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(TabDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(TabDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxColumns = new QSpinBox(TabDialog);
        spinBoxColumns->setObjectName(QString::fromUtf8("spinBoxColumns"));
        spinBoxColumns->setMinimum(1);

        horizontalLayout->addWidget(spinBoxColumns);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBoxColumns = new QGroupBox(TabDialog);
        groupBoxColumns->setObjectName(QString::fromUtf8("groupBoxColumns"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxColumns->sizePolicy().hasHeightForWidth());
        groupBoxColumns->setSizePolicy(sizePolicy1);
        groupBoxColumns->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(groupBoxColumns);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(groupBoxColumns);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        spinBoxNumCol = new QSpinBox(groupBoxColumns);
        spinBoxNumCol->setObjectName(QString::fromUtf8("spinBoxNumCol"));

        horizontalLayout_2->addWidget(spinBoxNumCol);

        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(groupBoxColumns);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        comboBoxColAl = new QComboBox(groupBoxColumns);
        comboBoxColAl->setObjectName(QString::fromUtf8("comboBoxColAl"));

        horizontalLayout_3->addWidget(comboBoxColAl);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBoxColumns);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        comboLeftBorder = new QComboBox(groupBoxColumns);
        comboLeftBorder->setObjectName(QString::fromUtf8("comboLeftBorder"));

        horizontalLayout_4->addWidget(comboLeftBorder);

        horizontalSpacer_4 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        pushButtonColumns = new QPushButton(groupBoxColumns);
        pushButtonColumns->setObjectName(QString::fromUtf8("pushButtonColumns"));

        horizontalLayout_5->addWidget(pushButtonColumns);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBoxColumns);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(TabDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        comboBoxEndBorder = new QComboBox(TabDialog);
        comboBoxEndBorder->setObjectName(QString::fromUtf8("comboBoxEndBorder"));

        horizontalLayout_6->addWidget(comboBoxEndBorder);

        horizontalSpacer_8 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        line_3 = new QFrame(TabDialog);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(TabDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_8->addWidget(label_4);

        spinBoxRows = new QSpinBox(TabDialog);
        spinBoxRows->setObjectName(QString::fromUtf8("spinBoxRows"));

        horizontalLayout_8->addWidget(spinBoxRows);

        horizontalSpacer_7 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_8);

        groupBoxLines = new QGroupBox(TabDialog);
        groupBoxLines->setObjectName(QString::fromUtf8("groupBoxLines"));
        sizePolicy1.setHeightForWidth(groupBoxLines->sizePolicy().hasHeightForWidth());
        groupBoxLines->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(groupBoxLines);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(groupBoxLines);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        spinBoxNumLi = new QSpinBox(groupBoxLines);
        spinBoxNumLi->setObjectName(QString::fromUtf8("spinBoxNumLi"));

        horizontalLayout_7->addWidget(spinBoxNumLi);

        horizontalSpacer_9 = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);


        verticalLayout_3->addLayout(horizontalLayout_7);

        checkBoxBorderTop = new QCheckBox(groupBoxLines);
        checkBoxBorderTop->setObjectName(QString::fromUtf8("checkBoxBorderTop"));

        verticalLayout_3->addWidget(checkBoxBorderTop);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        checkBoxSpan = new QCheckBox(groupBoxLines);
        checkBoxSpan->setObjectName(QString::fromUtf8("checkBoxSpan"));

        horizontalLayout_9->addWidget(checkBoxSpan);

        spinBoxSpanFrom = new QSpinBox(groupBoxLines);
        spinBoxSpanFrom->setObjectName(QString::fromUtf8("spinBoxSpanFrom"));

        horizontalLayout_9->addWidget(spinBoxSpanFrom);

        label_8 = new QLabel(groupBoxLines);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_8);

        spinBoxSpanTo = new QSpinBox(groupBoxLines);
        spinBoxSpanTo->setObjectName(QString::fromUtf8("spinBoxSpanTo"));

        horizontalLayout_9->addWidget(spinBoxSpanTo);

        horizontalSpacer_10 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);

        pushButtonLines = new QPushButton(groupBoxLines);
        pushButtonLines->setObjectName(QString::fromUtf8("pushButtonLines"));

        horizontalLayout_10->addWidget(pushButtonLines);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);


        verticalLayout_3->addLayout(horizontalLayout_10);


        verticalLayout_4->addWidget(groupBoxLines);

        checkBoxBorderBottom = new QCheckBox(TabDialog);
        checkBoxBorderBottom->setObjectName(QString::fromUtf8("checkBoxBorderBottom"));

        verticalLayout_4->addWidget(checkBoxBorderBottom);

        checkBoxMargin = new QCheckBox(TabDialog);
        checkBoxMargin->setObjectName(QString::fromUtf8("checkBoxMargin"));

        verticalLayout_4->addWidget(checkBoxMargin);


        gridLayout->addLayout(verticalLayout_4, 1, 2, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(500, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(TabDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        hboxLayout->addWidget(buttonBox);


        gridLayout->addLayout(hboxLayout, 2, 0, 1, 3);


        retranslateUi(TabDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TabDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TabDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TabDialog);
    } // setupUi

    void retranslateUi(QDialog *TabDialog)
    {
        label_3->setText(QCoreApplication::translate("TabDialog", "Num of Columns", nullptr));
        groupBoxColumns->setTitle(QCoreApplication::translate("TabDialog", "Columns", nullptr));
        label_5->setText(QCoreApplication::translate("TabDialog", "Column :", nullptr));
        label_6->setText(QCoreApplication::translate("TabDialog", "Alignment :", nullptr));
        label->setText(QCoreApplication::translate("TabDialog", "Left Border :", nullptr));
        pushButtonColumns->setText(QCoreApplication::translate("TabDialog", "Apply to all columns", nullptr));
        label_2->setText(QCoreApplication::translate("TabDialog", "Right Border (last column) :", nullptr));
        label_4->setText(QCoreApplication::translate("TabDialog", "Num of Rows", nullptr));
        groupBoxLines->setTitle(QCoreApplication::translate("TabDialog", "Rows", nullptr));
        label_7->setText(QCoreApplication::translate("TabDialog", "Row :", nullptr));
        checkBoxBorderTop->setText(QCoreApplication::translate("TabDialog", "Top Border", nullptr));
        checkBoxSpan->setText(QCoreApplication::translate("TabDialog", "Merge columns :", nullptr));
        label_8->setText(QCoreApplication::translate("TabDialog", "->", nullptr));
        pushButtonLines->setText(QCoreApplication::translate("TabDialog", "Apply to all rows", nullptr));
        checkBoxBorderBottom->setText(QCoreApplication::translate("TabDialog", "Bottom Border (last row)", nullptr));
        checkBoxMargin->setText(QCoreApplication::translate("TabDialog", "Add vertical margin for each row", nullptr));
        (void)TabDialog;
    } // retranslateUi

};

namespace Ui {
    class TabDialog: public Ui_TabDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABDIALOG_H
