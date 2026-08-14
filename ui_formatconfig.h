/********************************************************************************
** Form generated from reading UI file 'formatconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMATCONFIG_H
#define UI_FORMATCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormatConfig
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *m_frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *m_selector;
    QTableWidget *m_table;

    void setupUi(QWidget *FormatConfig)
    {
        if (FormatConfig->objectName().isEmpty())
            FormatConfig->setObjectName(QString::fromUtf8("FormatConfig"));
        FormatConfig->resize(539, 360);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FormatConfig->sizePolicy().hasHeightForWidth());
        FormatConfig->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(FormatConfig);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_frame = new QFrame(FormatConfig);
        m_frame->setObjectName(QString::fromUtf8("m_frame"));
        m_frame->setFrameShape(QFrame::NoFrame);
        m_frame->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(m_frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(m_frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_selector = new QComboBox(m_frame);
        m_selector->setObjectName(QString::fromUtf8("m_selector"));

        gridLayout->addWidget(m_selector, 0, 1, 1, 1);


        verticalLayout->addWidget(m_frame);

        m_table = new QTableWidget(FormatConfig);
        m_table->setObjectName(QString::fromUtf8("m_table"));
        sizePolicy.setHeightForWidth(m_table->sizePolicy().hasHeightForWidth());
        m_table->setSizePolicy(sizePolicy);
        m_table->setSelectionMode(QAbstractItemView::NoSelection);
        m_table->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(m_table);


        retranslateUi(FormatConfig);

        QMetaObject::connectSlotsByName(FormatConfig);
    } // setupUi

    void retranslateUi(QWidget *FormatConfig)
    {
        FormatConfig->setWindowTitle(QCoreApplication::translate("FormatConfig", "Form", nullptr));
        label->setText(QCoreApplication::translate("FormatConfig", "Scheme :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormatConfig: public Ui_FormatConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMATCONFIG_H
