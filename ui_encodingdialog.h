/********************************************************************************
** Form generated from reading UI file 'encodingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCODINGDIALOG_H
#define UI_ENCODINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EncodingDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *view;
    QPushButton *reload;
    QPushButton *cancel;
    QPushButton *change;
    QSpacerItem *horizontalSpacer;
    QTableWidget *encodings;

    void setupUi(QDialog *EncodingDialog)
    {
        if (EncodingDialog->objectName().isEmpty())
            EncodingDialog->setObjectName(QString::fromUtf8("EncodingDialog"));
        EncodingDialog->resize(717, 342);
        gridLayout = new QGridLayout(EncodingDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(EncodingDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        view = new QPushButton(EncodingDialog);
        view->setObjectName(QString::fromUtf8("view"));

        gridLayout->addWidget(view, 2, 2, 1, 1);

        reload = new QPushButton(EncodingDialog);
        reload->setObjectName(QString::fromUtf8("reload"));

        gridLayout->addWidget(reload, 2, 3, 1, 1);

        cancel = new QPushButton(EncodingDialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        gridLayout->addWidget(cancel, 2, 4, 1, 1);

        change = new QPushButton(EncodingDialog);
        change->setObjectName(QString::fromUtf8("change"));

        gridLayout->addWidget(change, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(47, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        encodings = new QTableWidget(EncodingDialog);
        if (encodings->columnCount() < 2)
            encodings->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        encodings->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        encodings->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        encodings->setObjectName(QString::fromUtf8("encodings"));
        encodings->setEditTriggers(QAbstractItemView::NoEditTriggers);
        encodings->setProperty("showDropIndicator", QVariant(false));
        encodings->setSelectionBehavior(QAbstractItemView::SelectRows);
        encodings->setCornerButtonEnabled(false);
        encodings->horizontalHeader()->setHighlightSections(false);
        encodings->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(encodings, 1, 0, 1, 5);

        QWidget::setTabOrder(encodings, change);
        QWidget::setTabOrder(change, view);
        QWidget::setTabOrder(view, reload);
        QWidget::setTabOrder(reload, cancel);

        retranslateUi(EncodingDialog);

        change->setDefault(true);


        QMetaObject::connectSlotsByName(EncodingDialog);
    } // setupUi

    void retranslateUi(QDialog *EncodingDialog)
    {
        EncodingDialog->setWindowTitle(QCoreApplication::translate("EncodingDialog", "Select File Encoding", nullptr));
        label->setText(QCoreApplication::translate("EncodingDialog", "TextLabel", nullptr));
        view->setText(QCoreApplication::translate("EncodingDialog", "View With", nullptr));
        reload->setText(QCoreApplication::translate("EncodingDialog", "Reload With", nullptr));
        cancel->setText(QCoreApplication::translate("EncodingDialog", "Cancel", nullptr));
        change->setText(QCoreApplication::translate("EncodingDialog", "Change To", nullptr));
        QTableWidgetItem *___qtablewidgetitem = encodings->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EncodingDialog", "File Encoding", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = encodings->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EncodingDialog", "inputenc Parameter", nullptr));
#if QT_CONFIG(tooltip)
        ___qtablewidgetitem1->setToolTip(QCoreApplication::translate("EncodingDialog", "The codec names as the inputenc package expects them. The names are only given for reference.\n"
"You have to make sure yourself that the file encoding and the value passed to the inputenc package match together.", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class EncodingDialog: public Ui_EncodingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCODINGDIALOG_H
