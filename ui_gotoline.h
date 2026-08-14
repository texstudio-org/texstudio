/********************************************************************************
** Form generated from reading UI file 'gotoline.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOTOLINE_H
#define UI_GOTOLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GotoLine
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *bClose;
    QLabel *label;
    QSpinBox *spLine;
    QPushButton *bGo;
    QSlider *slLine;

    void setupUi(QWidget *GotoLine)
    {
        if (GotoLine->objectName().isEmpty())
            GotoLine->setObjectName(QString::fromUtf8("GotoLine"));
        GotoLine->resize(513, 45);
        horizontalLayout = new QHBoxLayout(GotoLine);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        bClose = new QToolButton(GotoLine);
        bClose->setObjectName(QString::fromUtf8("bClose"));

        horizontalLayout->addWidget(bClose);

        label = new QLabel(GotoLine);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spLine = new QSpinBox(GotoLine);
        spLine->setObjectName(QString::fromUtf8("spLine"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spLine->sizePolicy().hasHeightForWidth());
        spLine->setSizePolicy(sizePolicy);
        spLine->setMinimum(1);

        horizontalLayout->addWidget(spLine);

        bGo = new QPushButton(GotoLine);
        bGo->setObjectName(QString::fromUtf8("bGo"));

        horizontalLayout->addWidget(bGo);

        slLine = new QSlider(GotoLine);
        slLine->setObjectName(QString::fromUtf8("slLine"));
        slLine->setMinimum(1);
        slLine->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slLine);

#if QT_CONFIG(shortcut)
        label->setBuddy(spLine);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(spLine, bGo);
        QWidget::setTabOrder(bGo, bClose);
        QWidget::setTabOrder(bClose, slLine);

        retranslateUi(GotoLine);

        QMetaObject::connectSlotsByName(GotoLine);
    } // setupUi

    void retranslateUi(QWidget *GotoLine)
    {
        GotoLine->setWindowTitle(QCoreApplication::translate("GotoLine", "Form", nullptr));
        bClose->setText(QString());
        label->setText(QCoreApplication::translate("GotoLine", "&Go to line :", nullptr));
        spLine->setPrefix(QString());
        bGo->setText(QCoreApplication::translate("GotoLine", "G&o", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GotoLine: public Ui_GotoLine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOTOLINE_H
