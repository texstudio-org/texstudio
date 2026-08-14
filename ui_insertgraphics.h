/********************************************************************************
** Form generated from reading UI file 'insertgraphics.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTGRAPHICS_H
#define UI_INSERTGRAPHICS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InsertGraphics
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leFile;
    QPushButton *fileSelectButton;
    QGroupBox *groupBoxOptions;
    QGridLayout *gridLayout_2;
    QRadioButton *rbWidthHeight;
    QCheckBox *cbWidth;
    QLineEdit *leWidth;
    QComboBox *cbWidthUnit;
    QCheckBox *cbHeight;
    QLineEdit *leHeight;
    QComboBox *cbHeightUnit;
    QLineEdit *leScale;
    QRadioButton *rbUser;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *cbCentering;
    QGroupBox *gbFloat;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QComboBox *cbPosition;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *teCaption;
    QLabel *label_3;
    QLineEdit *leLabel;
    QCheckBox *cbSpan;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lePlacement;
    QPushButton *pbPlaceExpand;
    QLineEdit *leShortCaption;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *placementCheckboxes;
    QGridLayout *gridLayout_4;
    QCheckBox *cbPlaceTop;
    QCheckBox *cbPlaceBottom;
    QCheckBox *cbPlacePage;
    QCheckBox *cbPlaceHere;
    QCheckBox *cbPlaceHereFloatPackage;
    QCheckBox *cbPlaceForce;
    QHBoxLayout *hboxLayout;
    QPushButton *pbSaveDefault;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *InsertGraphics)
    {
        if (InsertGraphics->objectName().isEmpty())
            InsertGraphics->setObjectName(QString::fromUtf8("InsertGraphics"));
        InsertGraphics->resize(457, 574);
        verticalLayout = new QVBoxLayout(InsertGraphics);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(InsertGraphics);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leFile = new QLineEdit(InsertGraphics);
        leFile->setObjectName(QString::fromUtf8("leFile"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leFile->sizePolicy().hasHeightForWidth());
        leFile->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(leFile, 0, 1, 1, 1);

        fileSelectButton = new QPushButton(InsertGraphics);
        fileSelectButton->setObjectName(QString::fromUtf8("fileSelectButton"));
        sizePolicy.setHeightForWidth(fileSelectButton->sizePolicy().hasHeightForWidth());
        fileSelectButton->setSizePolicy(sizePolicy);
        fileSelectButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/document-open.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        fileSelectButton->setIcon(icon);
        fileSelectButton->setIconSize(QSize(16, 16));

        gridLayout->addWidget(fileSelectButton, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        groupBoxOptions = new QGroupBox(InsertGraphics);
        groupBoxOptions->setObjectName(QString::fromUtf8("groupBoxOptions"));
        groupBoxOptions->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(groupBoxOptions);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rbWidthHeight = new QRadioButton(groupBoxOptions);
        rbWidthHeight->setObjectName(QString::fromUtf8("rbWidthHeight"));
        rbWidthHeight->setChecked(true);

        gridLayout_2->addWidget(rbWidthHeight, 0, 0, 1, 1);

        cbWidth = new QCheckBox(groupBoxOptions);
        cbWidth->setObjectName(QString::fromUtf8("cbWidth"));
        cbWidth->setChecked(true);

        gridLayout_2->addWidget(cbWidth, 0, 1, 1, 1);

        leWidth = new QLineEdit(groupBoxOptions);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));
        leWidth->setText(QString::fromUtf8("0.7"));

        gridLayout_2->addWidget(leWidth, 0, 2, 1, 1);

        cbWidthUnit = new QComboBox(groupBoxOptions);
        cbWidthUnit->setObjectName(QString::fromUtf8("cbWidthUnit"));
        cbWidthUnit->setMinimumSize(QSize(80, 0));
        cbWidthUnit->setCurrentText(QString::fromUtf8(""));

        gridLayout_2->addWidget(cbWidthUnit, 0, 3, 1, 1);

        cbHeight = new QCheckBox(groupBoxOptions);
        cbHeight->setObjectName(QString::fromUtf8("cbHeight"));

        gridLayout_2->addWidget(cbHeight, 1, 1, 1, 1);

        leHeight = new QLineEdit(groupBoxOptions);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));
        leHeight->setText(QString::fromUtf8(""));

        gridLayout_2->addWidget(leHeight, 1, 2, 1, 1);

        cbHeightUnit = new QComboBox(groupBoxOptions);
        cbHeightUnit->setObjectName(QString::fromUtf8("cbHeightUnit"));
        cbHeightUnit->setMinimumSize(QSize(80, 0));
        cbHeightUnit->setCurrentText(QString::fromUtf8(""));

        gridLayout_2->addWidget(cbHeightUnit, 1, 3, 1, 1);

        leScale = new QLineEdit(groupBoxOptions);
        leScale->setObjectName(QString::fromUtf8("leScale"));

        gridLayout_2->addWidget(leScale, 3, 0, 1, 4);

        rbUser = new QRadioButton(groupBoxOptions);
        rbUser->setObjectName(QString::fromUtf8("rbUser"));

        gridLayout_2->addWidget(rbUser, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBoxOptions);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cbCentering = new QCheckBox(InsertGraphics);
        cbCentering->setObjectName(QString::fromUtf8("cbCentering"));
        cbCentering->setChecked(true);

        horizontalLayout_2->addWidget(cbCentering);


        verticalLayout->addLayout(horizontalLayout_2);

        gbFloat = new QGroupBox(InsertGraphics);
        gbFloat->setObjectName(QString::fromUtf8("gbFloat"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gbFloat->sizePolicy().hasHeightForWidth());
        gbFloat->setSizePolicy(sizePolicy2);
        gbFloat->setMinimumSize(QSize(0, 260));
        gbFloat->setCheckable(true);
        gridLayout_3 = new QGridLayout(gbFloat);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(gbFloat);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        cbPosition = new QComboBox(gbFloat);
        cbPosition->addItem(QString());
        cbPosition->addItem(QString());
        cbPosition->setObjectName(QString::fromUtf8("cbPosition"));

        gridLayout_3->addWidget(cbPosition, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 2, 1, 1);

        teCaption = new QPlainTextEdit(gbFloat);
        teCaption->setObjectName(QString::fromUtf8("teCaption"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(teCaption->sizePolicy().hasHeightForWidth());
        teCaption->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(teCaption, 2, 1, 1, 2);

        label_3 = new QLabel(gbFloat);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        leLabel = new QLineEdit(gbFloat);
        leLabel->setObjectName(QString::fromUtf8("leLabel"));

        gridLayout_3->addWidget(leLabel, 3, 1, 1, 2);

        cbSpan = new QCheckBox(gbFloat);
        cbSpan->setObjectName(QString::fromUtf8("cbSpan"));

        gridLayout_3->addWidget(cbSpan, 14, 0, 1, 2);

        label_2 = new QLabel(gbFloat);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 8, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lePlacement = new QLineEdit(gbFloat);
        lePlacement->setObjectName(QString::fromUtf8("lePlacement"));

        horizontalLayout_4->addWidget(lePlacement);

        pbPlaceExpand = new QPushButton(gbFloat);
        pbPlaceExpand->setObjectName(QString::fromUtf8("pbPlaceExpand"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/up-arrow-circle-silver.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPlaceExpand->setIcon(icon1);

        horizontalLayout_4->addWidget(pbPlaceExpand);


        gridLayout_3->addLayout(horizontalLayout_4, 8, 1, 1, 2);

        leShortCaption = new QLineEdit(gbFloat);
        leShortCaption->setObjectName(QString::fromUtf8("leShortCaption"));

        gridLayout_3->addWidget(leShortCaption, 1, 1, 1, 2);

        label_5 = new QLabel(gbFloat);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(gbFloat);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_3->addWidget(label_6, 2, 0, 1, 1);

        placementCheckboxes = new QFrame(gbFloat);
        placementCheckboxes->setObjectName(QString::fromUtf8("placementCheckboxes"));
        placementCheckboxes->setFrameShape(QFrame::StyledPanel);
        placementCheckboxes->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(placementCheckboxes);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        cbPlaceTop = new QCheckBox(placementCheckboxes);
        cbPlaceTop->setObjectName(QString::fromUtf8("cbPlaceTop"));

        gridLayout_4->addWidget(cbPlaceTop, 0, 0, 1, 1);

        cbPlaceBottom = new QCheckBox(placementCheckboxes);
        cbPlaceBottom->setObjectName(QString::fromUtf8("cbPlaceBottom"));

        gridLayout_4->addWidget(cbPlaceBottom, 0, 1, 1, 1);

        cbPlacePage = new QCheckBox(placementCheckboxes);
        cbPlacePage->setObjectName(QString::fromUtf8("cbPlacePage"));

        gridLayout_4->addWidget(cbPlacePage, 0, 2, 1, 1);

        cbPlaceHere = new QCheckBox(placementCheckboxes);
        cbPlaceHere->setObjectName(QString::fromUtf8("cbPlaceHere"));

        gridLayout_4->addWidget(cbPlaceHere, 0, 3, 1, 1);

        cbPlaceHereFloatPackage = new QCheckBox(placementCheckboxes);
        cbPlaceHereFloatPackage->setObjectName(QString::fromUtf8("cbPlaceHereFloatPackage"));

        gridLayout_4->addWidget(cbPlaceHereFloatPackage, 0, 4, 1, 1);

        cbPlaceForce = new QCheckBox(placementCheckboxes);
        cbPlaceForce->setObjectName(QString::fromUtf8("cbPlaceForce"));

        gridLayout_4->addWidget(cbPlaceForce, 1, 0, 1, 5);


        gridLayout_3->addWidget(placementCheckboxes, 9, 1, 2, 2);


        verticalLayout->addWidget(gbFloat);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        pbSaveDefault = new QPushButton(InsertGraphics);
        pbSaveDefault->setObjectName(QString::fromUtf8("pbSaveDefault"));
        pbSaveDefault->setMinimumSize(QSize(0, 0));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/classic/images/classic/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveDefault->setIcon(icon2);

        hboxLayout->addWidget(pbSaveDefault);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(InsertGraphics);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(InsertGraphics);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);

#if QT_CONFIG(shortcut)
        label->setBuddy(leFile);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(leFile, fileSelectButton);
        QWidget::setTabOrder(fileSelectButton, rbWidthHeight);
        QWidget::setTabOrder(rbWidthHeight, cbWidth);
        QWidget::setTabOrder(cbWidth, leWidth);
        QWidget::setTabOrder(leWidth, cbWidthUnit);
        QWidget::setTabOrder(cbWidthUnit, cbHeight);
        QWidget::setTabOrder(cbHeight, leHeight);
        QWidget::setTabOrder(leHeight, cbHeightUnit);
        QWidget::setTabOrder(cbHeightUnit, rbUser);
        QWidget::setTabOrder(rbUser, leScale);
        QWidget::setTabOrder(leScale, cbCentering);
        QWidget::setTabOrder(cbCentering, gbFloat);
        QWidget::setTabOrder(gbFloat, cbPosition);
        QWidget::setTabOrder(cbPosition, leShortCaption);
        QWidget::setTabOrder(leShortCaption, teCaption);
        QWidget::setTabOrder(teCaption, leLabel);
        QWidget::setTabOrder(leLabel, lePlacement);
        QWidget::setTabOrder(lePlacement, pbPlaceExpand);
        QWidget::setTabOrder(pbPlaceExpand, cbPlaceTop);
        QWidget::setTabOrder(cbPlaceTop, cbPlaceBottom);
        QWidget::setTabOrder(cbPlaceBottom, cbPlacePage);
        QWidget::setTabOrder(cbPlacePage, cbPlaceHere);
        QWidget::setTabOrder(cbPlaceHere, cbPlaceForce);
        QWidget::setTabOrder(cbPlaceForce, cbSpan);
        QWidget::setTabOrder(cbSpan, pbSaveDefault);
        QWidget::setTabOrder(pbSaveDefault, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(InsertGraphics);
        QObject::connect(okButton, SIGNAL(clicked()), InsertGraphics, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), InsertGraphics, SLOT(reject()));

        cbWidthUnit->setCurrentIndex(-1);
        cbHeightUnit->setCurrentIndex(-1);
        cbPosition->setCurrentIndex(1);
        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(InsertGraphics);
    } // setupUi

    void retranslateUi(QDialog *InsertGraphics)
    {
        label->setText(QCoreApplication::translate("InsertGraphics", "File", nullptr));
        fileSelectButton->setText(QString());
#if QT_CONFIG(tooltip)
        groupBoxOptions->setToolTip(QCoreApplication::translate("InsertGraphics", "Defines the options for \\includegraphics[options]{file}.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxOptions->setTitle(QCoreApplication::translate("InsertGraphics", "Graphics Options", nullptr));
        rbWidthHeight->setText(QCoreApplication::translate("InsertGraphics", "Width/Height", nullptr));
        cbWidth->setText(QCoreApplication::translate("InsertGraphics", "Width", nullptr));
        cbHeight->setText(QCoreApplication::translate("InsertGraphics", "Height", nullptr));
#if QT_CONFIG(tooltip)
        leScale->setToolTip(QCoreApplication::translate("InsertGraphics", "Defines the options for \\includegraphics[options]{file}.", nullptr));
#endif // QT_CONFIG(tooltip)
        rbUser->setText(QCoreApplication::translate("InsertGraphics", "User Defined", nullptr));
        cbCentering->setText(QCoreApplication::translate("InsertGraphics", "Center Horizontally", nullptr));
        gbFloat->setTitle(QCoreApplication::translate("InsertGraphics", "Place in Figure Environment", nullptr));
        label_4->setText(QCoreApplication::translate("InsertGraphics", "Caption", nullptr));
        cbPosition->setItemText(0, QCoreApplication::translate("InsertGraphics", "Above graphic", nullptr));
        cbPosition->setItemText(1, QCoreApplication::translate("InsertGraphics", "Below graphic", nullptr));

#if QT_CONFIG(tooltip)
        teCaption->setToolTip(QCoreApplication::translate("InsertGraphics", "Caption for the image", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("InsertGraphics", "Label", nullptr));
#if QT_CONFIG(tooltip)
        leLabel->setToolTip(QCoreApplication::translate("InsertGraphics", "Identifier, which is used to reference the graphic; e.g. using \\ref{thisLabel}", nullptr));
#endif // QT_CONFIG(tooltip)
        cbSpan->setText(QCoreApplication::translate("InsertGraphics", "Span Two Columns", nullptr));
        label_2->setText(QCoreApplication::translate("InsertGraphics", "Position", nullptr));
        pbPlaceExpand->setText(QString());
#if QT_CONFIG(tooltip)
        leShortCaption->setToolTip(QCoreApplication::translate("InsertGraphics", "Caption to be displayed in the list of figures (if wanted different from the long caption)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("InsertGraphics", "  Short", nullptr));
        label_6->setText(QCoreApplication::translate("InsertGraphics", "  Long", nullptr));
        cbPlaceTop->setText(QCoreApplication::translate("InsertGraphics", "Top", nullptr));
        cbPlaceBottom->setText(QCoreApplication::translate("InsertGraphics", "Bottom", nullptr));
        cbPlacePage->setText(QCoreApplication::translate("InsertGraphics", "Page", nullptr));
        cbPlaceHere->setText(QCoreApplication::translate("InsertGraphics", "Here", nullptr));
        cbPlaceHereFloatPackage->setText(QCoreApplication::translate("InsertGraphics", "Here (H)", nullptr));
        cbPlaceForce->setText(QCoreApplication::translate("InsertGraphics", "Override Internal Layout Parameters", nullptr));
#if QT_CONFIG(tooltip)
        pbSaveDefault->setToolTip(QCoreApplication::translate("InsertGraphics", "Save current settings as default.", nullptr));
#endif // QT_CONFIG(tooltip)
        pbSaveDefault->setText(QCoreApplication::translate("InsertGraphics", "as Default", nullptr));
        okButton->setText(QCoreApplication::translate("InsertGraphics", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("InsertGraphics", "Cancel", nullptr));
        (void)InsertGraphics;
    } // retranslateUi

};

namespace Ui {
    class InsertGraphics: public Ui_InsertGraphics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTGRAPHICS_H
