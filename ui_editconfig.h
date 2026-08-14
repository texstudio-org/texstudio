/********************************************************************************
** Form generated from reading UI file 'editconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONFIG_H
#define UI_EDITCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorConfig
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *gbFont;
    QGridLayout *gridLayout;
    QFontComboBox *cbFont;
    QSpinBox *spnFontSize;
    QLabel *lblSampleText;
    QSpacerItem *spacerItem;
    QGroupBox *gbTabs;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *lblTabWitdh;
    QSpinBox *spnTabWidth;
    QSpacerItem *spacerItem1;
    QCheckBox *chkShowLeadingWhitespace;
    QCheckBox *chkShowTabsInText;
    QCheckBox *chkShowTrailingWhitespace;
    QCheckBox *chkReplaceTabs;
    QGroupBox *gbEncodings;
    QGridLayout *_2;
    QLabel *label;
    QComboBox *cbEncoding;
    QCheckBox *chkDetectLE;
    QComboBox *cbLineEndings;
    QCheckBox *chkAutoRemoveTrailingWhitespace;
    QCheckBox *chkPreserveTrailingIndent;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *EditorConfig)
    {
        if (EditorConfig->objectName().isEmpty())
            EditorConfig->setObjectName(QString::fromUtf8("EditorConfig"));
        EditorConfig->resize(575, 586);
        vboxLayout = new QVBoxLayout(EditorConfig);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gbFont = new QGroupBox(EditorConfig);
        gbFont->setObjectName(QString::fromUtf8("gbFont"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbFont->sizePolicy().hasHeightForWidth());
        gbFont->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(gbFont);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbFont = new QFontComboBox(gbFont);
        cbFont->setObjectName(QString::fromUtf8("cbFont"));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        cbFont->setFont(font);
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        cbFont->setCurrentFont(font1);

        gridLayout->addWidget(cbFont, 0, 0, 1, 1);

        spnFontSize = new QSpinBox(gbFont);
        spnFontSize->setObjectName(QString::fromUtf8("spnFontSize"));
        spnFontSize->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spnFontSize->setMinimum(6);
        spnFontSize->setMaximum(50);
        spnFontSize->setValue(10);

        gridLayout->addWidget(spnFontSize, 0, 1, 1, 1);

        lblSampleText = new QLabel(gbFont);
        lblSampleText->setObjectName(QString::fromUtf8("lblSampleText"));
        sizePolicy.setHeightForWidth(lblSampleText->sizePolicy().hasHeightForWidth());
        lblSampleText->setSizePolicy(sizePolicy);
        lblSampleText->setFont(font);
        lblSampleText->setFrameShape(QFrame::StyledPanel);
        lblSampleText->setFrameShadow(QFrame::Sunken);
        lblSampleText->setAlignment(Qt::AlignCenter);
        lblSampleText->setMargin(0);

        gridLayout->addWidget(lblSampleText, 1, 0, 1, 3);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);


        vboxLayout->addWidget(gbFont);

        gbTabs = new QGroupBox(EditorConfig);
        gbTabs->setObjectName(QString::fromUtf8("gbTabs"));
        sizePolicy.setHeightForWidth(gbTabs->sizePolicy().hasHeightForWidth());
        gbTabs->setSizePolicy(sizePolicy);
        vboxLayout1 = new QVBoxLayout(gbTabs);
        vboxLayout1->setContentsMargins(5, 5, 5, 5);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblTabWitdh = new QLabel(gbTabs);
        lblTabWitdh->setObjectName(QString::fromUtf8("lblTabWitdh"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblTabWitdh->sizePolicy().hasHeightForWidth());
        lblTabWitdh->setSizePolicy(sizePolicy1);

        hboxLayout->addWidget(lblTabWitdh);

        spnTabWidth = new QSpinBox(gbTabs);
        spnTabWidth->setObjectName(QString::fromUtf8("spnTabWidth"));
        spnTabWidth->setValue(4);

        hboxLayout->addWidget(spnTabWidth);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout1->addLayout(hboxLayout);

        chkShowLeadingWhitespace = new QCheckBox(gbTabs);
        chkShowLeadingWhitespace->setObjectName(QString::fromUtf8("chkShowLeadingWhitespace"));
        chkShowLeadingWhitespace->setChecked(true);

        vboxLayout1->addWidget(chkShowLeadingWhitespace);

        chkShowTabsInText = new QCheckBox(gbTabs);
        chkShowTabsInText->setObjectName(QString::fromUtf8("chkShowTabsInText"));
        chkShowTabsInText->setChecked(true);

        vboxLayout1->addWidget(chkShowTabsInText);

        chkShowTrailingWhitespace = new QCheckBox(gbTabs);
        chkShowTrailingWhitespace->setObjectName(QString::fromUtf8("chkShowTrailingWhitespace"));
        chkShowTrailingWhitespace->setChecked(true);

        vboxLayout1->addWidget(chkShowTrailingWhitespace);

        chkReplaceTabs = new QCheckBox(gbTabs);
        chkReplaceTabs->setObjectName(QString::fromUtf8("chkReplaceTabs"));

        vboxLayout1->addWidget(chkReplaceTabs);


        vboxLayout->addWidget(gbTabs);

        gbEncodings = new QGroupBox(EditorConfig);
        gbEncodings->setObjectName(QString::fromUtf8("gbEncodings"));
        _2 = new QGridLayout(gbEncodings);
        _2->setObjectName(QString::fromUtf8("_2"));
        label = new QLabel(gbEncodings);
        label->setObjectName(QString::fromUtf8("label"));

        _2->addWidget(label, 0, 0, 1, 1);

        cbEncoding = new QComboBox(gbEncodings);
        cbEncoding->setObjectName(QString::fromUtf8("cbEncoding"));

        _2->addWidget(cbEncoding, 0, 1, 1, 1);

        chkDetectLE = new QCheckBox(gbEncodings);
        chkDetectLE->setObjectName(QString::fromUtf8("chkDetectLE"));
        chkDetectLE->setChecked(true);

        _2->addWidget(chkDetectLE, 1, 0, 1, 1);

        cbLineEndings = new QComboBox(gbEncodings);
        cbLineEndings->addItem(QString());
        cbLineEndings->addItem(QString());
        cbLineEndings->addItem(QString());
        cbLineEndings->addItem(QString());
        cbLineEndings->setObjectName(QString::fromUtf8("cbLineEndings"));
        cbLineEndings->setEnabled(false);

        _2->addWidget(cbLineEndings, 1, 1, 1, 1);

        chkAutoRemoveTrailingWhitespace = new QCheckBox(gbEncodings);
        chkAutoRemoveTrailingWhitespace->setObjectName(QString::fromUtf8("chkAutoRemoveTrailingWhitespace"));

        _2->addWidget(chkAutoRemoveTrailingWhitespace, 2, 0, 1, 1);

        chkPreserveTrailingIndent = new QCheckBox(gbEncodings);
        chkPreserveTrailingIndent->setObjectName(QString::fromUtf8("chkPreserveTrailingIndent"));
        chkPreserveTrailingIndent->setEnabled(false);

        _2->addWidget(chkPreserveTrailingIndent, 2, 1, 1, 1);


        vboxLayout->addWidget(gbEncodings);

        spacerItem2 = new QSpacerItem(492, 10, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        vboxLayout->addItem(spacerItem2);

#if QT_CONFIG(shortcut)
        lblTabWitdh->setBuddy(spnTabWidth);
#endif // QT_CONFIG(shortcut)

        retranslateUi(EditorConfig);
        QObject::connect(chkDetectLE, SIGNAL(toggled(bool)), cbLineEndings, SLOT(setDisabled(bool)));
        QObject::connect(chkAutoRemoveTrailingWhitespace, SIGNAL(toggled(bool)), chkPreserveTrailingIndent, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(EditorConfig);
    } // setupUi

    void retranslateUi(QWidget *EditorConfig)
    {
        gbFont->setTitle(QCoreApplication::translate("EditorConfig", "Font", nullptr));
        lblSampleText->setText(QCoreApplication::translate("EditorConfig", "text which <i>should</i> be a <b>fair</b> test of the font", nullptr));
        gbTabs->setTitle(QCoreApplication::translate("EditorConfig", "Tabulators && Whitespaces", nullptr));
        lblTabWitdh->setText(QCoreApplication::translate("EditorConfig", "Tab width", nullptr));
        chkShowLeadingWhitespace->setText(QCoreApplication::translate("EditorConfig", "Show leading whitespaces", nullptr));
        chkShowTabsInText->setText(QCoreApplication::translate("EditorConfig", "Show tabs which are neither leading nor trailing", nullptr));
        chkShowTrailingWhitespace->setText(QCoreApplication::translate("EditorConfig", "Show trailing whitespaces", nullptr));
        chkReplaceTabs->setText(QCoreApplication::translate("EditorConfig", "Replace tabs by blanks", nullptr));
        gbEncodings->setTitle(QCoreApplication::translate("EditorConfig", "Load && Save", nullptr));
        label->setText(QCoreApplication::translate("EditorConfig", "Default encoding", nullptr));
        chkDetectLE->setText(QCoreApplication::translate("EditorConfig", "Preserve line endings", nullptr));
        cbLineEndings->setItemText(0, QCoreApplication::translate("EditorConfig", "Local", nullptr));
        cbLineEndings->setItemText(1, QCoreApplication::translate("EditorConfig", "Unix/Linux", nullptr));
        cbLineEndings->setItemText(2, QCoreApplication::translate("EditorConfig", "DOS/Windows", nullptr));
        cbLineEndings->setItemText(3, QCoreApplication::translate("EditorConfig", "Old Mac", nullptr));

        chkAutoRemoveTrailingWhitespace->setText(QCoreApplication::translate("EditorConfig", "Remove trailing spaces", nullptr));
        chkPreserveTrailingIndent->setText(QCoreApplication::translate("EditorConfig", "Preserve trailing indent", nullptr));
        (void)EditorConfig;
    } // retranslateUi

};

namespace Ui {
    class EditorConfig: public Ui_EditorConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONFIG_H
