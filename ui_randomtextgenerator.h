/********************************************************************************
** Form generated from reading UI file 'randomtextgenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOMTEXTGENERATOR_H
#define UI_RANDOMTEXTGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_RandomTextGenerator
{
public:
    QHBoxLayout *hboxLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *spacerItem;
    QLineEdit *exportFileNameLineEdit;
    QSpinBox *wordOrderSpinBox;
    QRadioButton *characterOrder1RadioButton;
    QPushButton *generateButton;
    QCheckBox *upperCaseCheckBox;
    QRadioButton *wordOrderXRadioButton;
    QSpacerItem *spacerItem1;
    QRadioButton *wordOrder1RadioButton;
    QRadioButton *characterOrderXRadioButton;
    QCheckBox *exportCheckBox;
    QSpinBox *characterOrderSpinBox;
    QRadioButton *characterOrder3RadioButton;
    QRadioButton *characterOrder2RadioButton;
    QCheckBox *punctationCheckBox;
    QRadioButton *wordOrder2RadioButton;
    QPushButton *closeButton;
    QLabel *label;
    QSpinBox *lengthSpinBox;
    QCheckBox *latexInput;
    QRadioButton *wordOrder3RadioButton;
    QSpacerItem *spacerItem2;
    QSpacerItem *verticalSpacer;
    QRadioButton *loremIpsumRadioButton;
    QTextEdit *outputEdit;

    void setupUi(QDialog *RandomTextGenerator)
    {
        if (RandomTextGenerator->objectName().isEmpty())
            RandomTextGenerator->setObjectName(QString::fromUtf8("RandomTextGenerator"));
        RandomTextGenerator->resize(534, 584);
        hboxLayout = new QHBoxLayout(RandomTextGenerator);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        groupBox = new QGroupBox(RandomTextGenerator);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spacerItem = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 4, 0, 1, 1);

        exportFileNameLineEdit = new QLineEdit(groupBox);
        exportFileNameLineEdit->setObjectName(QString::fromUtf8("exportFileNameLineEdit"));

        gridLayout->addWidget(exportFileNameLineEdit, 18, 2, 1, 1);

        wordOrderSpinBox = new QSpinBox(groupBox);
        wordOrderSpinBox->setObjectName(QString::fromUtf8("wordOrderSpinBox"));
        wordOrderSpinBox->setMinimum(1);
        wordOrderSpinBox->setValue(4);

        gridLayout->addWidget(wordOrderSpinBox, 8, 2, 1, 1);

        characterOrder1RadioButton = new QRadioButton(groupBox);
        characterOrder1RadioButton->setObjectName(QString::fromUtf8("characterOrder1RadioButton"));

        gridLayout->addWidget(characterOrder1RadioButton, 0, 0, 1, 3);

        generateButton = new QPushButton(groupBox);
        generateButton->setObjectName(QString::fromUtf8("generateButton"));

        gridLayout->addWidget(generateButton, 23, 0, 1, 3);

        upperCaseCheckBox = new QCheckBox(groupBox);
        upperCaseCheckBox->setObjectName(QString::fromUtf8("upperCaseCheckBox"));

        gridLayout->addWidget(upperCaseCheckBox, 16, 0, 1, 3);

        wordOrderXRadioButton = new QRadioButton(groupBox);
        wordOrderXRadioButton->setObjectName(QString::fromUtf8("wordOrderXRadioButton"));

        gridLayout->addWidget(wordOrderXRadioButton, 8, 0, 1, 1);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 22, 0, 1, 3);

        wordOrder1RadioButton = new QRadioButton(groupBox);
        wordOrder1RadioButton->setObjectName(QString::fromUtf8("wordOrder1RadioButton"));

        gridLayout->addWidget(wordOrder1RadioButton, 5, 0, 1, 3);

        characterOrderXRadioButton = new QRadioButton(groupBox);
        characterOrderXRadioButton->setObjectName(QString::fromUtf8("characterOrderXRadioButton"));

        gridLayout->addWidget(characterOrderXRadioButton, 3, 0, 1, 1);

        exportCheckBox = new QCheckBox(groupBox);
        exportCheckBox->setObjectName(QString::fromUtf8("exportCheckBox"));

        gridLayout->addWidget(exportCheckBox, 18, 0, 1, 1);

        characterOrderSpinBox = new QSpinBox(groupBox);
        characterOrderSpinBox->setObjectName(QString::fromUtf8("characterOrderSpinBox"));
        characterOrderSpinBox->setMinimum(1);
        characterOrderSpinBox->setValue(4);

        gridLayout->addWidget(characterOrderSpinBox, 3, 2, 1, 1);

        characterOrder3RadioButton = new QRadioButton(groupBox);
        characterOrder3RadioButton->setObjectName(QString::fromUtf8("characterOrder3RadioButton"));

        gridLayout->addWidget(characterOrder3RadioButton, 2, 0, 1, 3);

        characterOrder2RadioButton = new QRadioButton(groupBox);
        characterOrder2RadioButton->setObjectName(QString::fromUtf8("characterOrder2RadioButton"));

        gridLayout->addWidget(characterOrder2RadioButton, 1, 0, 1, 3);

        punctationCheckBox = new QCheckBox(groupBox);
        punctationCheckBox->setObjectName(QString::fromUtf8("punctationCheckBox"));

        gridLayout->addWidget(punctationCheckBox, 11, 0, 1, 3);

        wordOrder2RadioButton = new QRadioButton(groupBox);
        wordOrder2RadioButton->setObjectName(QString::fromUtf8("wordOrder2RadioButton"));
        wordOrder2RadioButton->setChecked(false);

        gridLayout->addWidget(wordOrder2RadioButton, 6, 0, 1, 3);

        closeButton = new QPushButton(groupBox);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        gridLayout->addWidget(closeButton, 24, 0, 1, 3);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 20, 0, 1, 1);

        lengthSpinBox = new QSpinBox(groupBox);
        lengthSpinBox->setObjectName(QString::fromUtf8("lengthSpinBox"));
        lengthSpinBox->setMinimum(1);
        lengthSpinBox->setMaximum(2147483647);
        lengthSpinBox->setValue(40);

        gridLayout->addWidget(lengthSpinBox, 20, 2, 1, 1);

        latexInput = new QCheckBox(groupBox);
        latexInput->setObjectName(QString::fromUtf8("latexInput"));
        latexInput->setChecked(true);

        gridLayout->addWidget(latexInput, 17, 0, 1, 3);

        wordOrder3RadioButton = new QRadioButton(groupBox);
        wordOrder3RadioButton->setObjectName(QString::fromUtf8("wordOrder3RadioButton"));
        wordOrder3RadioButton->setChecked(true);

        gridLayout->addWidget(wordOrder3RadioButton, 7, 0, 1, 3);

        spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem2, 19, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 3);

        loremIpsumRadioButton = new QRadioButton(groupBox);
        loremIpsumRadioButton->setObjectName(QString::fromUtf8("loremIpsumRadioButton"));

        gridLayout->addWidget(loremIpsumRadioButton, 9, 0, 1, 1);


        hboxLayout->addWidget(groupBox);

        outputEdit = new QTextEdit(RandomTextGenerator);
        outputEdit->setObjectName(QString::fromUtf8("outputEdit"));

        hboxLayout->addWidget(outputEdit);


        retranslateUi(RandomTextGenerator);
        QObject::connect(closeButton, SIGNAL(clicked()), RandomTextGenerator, SLOT(reject()));

        QMetaObject::connectSlotsByName(RandomTextGenerator);
    } // setupUi

    void retranslateUi(QDialog *RandomTextGenerator)
    {
        RandomTextGenerator->setWindowTitle(QCoreApplication::translate("RandomTextGenerator", "Random Text Generator", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RandomTextGenerator", "Options", nullptr));
        characterOrder1RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "First Order Characters", nullptr));
        generateButton->setText(QCoreApplication::translate("RandomTextGenerator", "Generate", nullptr));
        upperCaseCheckBox->setText(QCoreApplication::translate("RandomTextGenerator", "Ignore Case", nullptr));
        wordOrderXRadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Higher Order:", nullptr));
        wordOrder1RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "First Order Word", nullptr));
        characterOrderXRadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Higher Order:", nullptr));
        exportCheckBox->setText(QCoreApplication::translate("RandomTextGenerator", "Save to:", nullptr));
        characterOrder3RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Third Order Characters", nullptr));
        characterOrder2RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Second Order Characters", nullptr));
        punctationCheckBox->setText(QCoreApplication::translate("RandomTextGenerator", "Punctation", nullptr));
        wordOrder2RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Second Order Words", nullptr));
        closeButton->setText(QCoreApplication::translate("RandomTextGenerator", "Close", nullptr));
        label->setText(QCoreApplication::translate("RandomTextGenerator", "Length:", nullptr));
        latexInput->setText(QCoreApplication::translate("RandomTextGenerator", "LaTeX Input", nullptr));
        wordOrder3RadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Third Order Words", nullptr));
        loremIpsumRadioButton->setText(QCoreApplication::translate("RandomTextGenerator", "Lorem Ipsum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RandomTextGenerator: public Ui_RandomTextGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOMTEXTGENERATOR_H
