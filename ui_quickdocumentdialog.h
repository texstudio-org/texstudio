/********************************************************************************
** Form generated from reading UI file 'quickdocumentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKDOCUMENTDIALOG_H
#define UI_QUICKDOCUMENTDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickDocumentDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabClass;
    QHBoxLayout *horizontalLayout;
    QGridLayout *_2;
    QLabel *labelTitle;
    QLineEdit *lineEditAuthor;
    QLabel *labelBabel;
    QComboBox *comboBoxClass;
    QLabel *labelClass;
    QPushButton *pushButtonClass;
    QLabel *labelSize;
    QLabel *labelOptions;
    QPushButton *pushButtonBabel;
    QComboBox *comboBoxSize;
    QPushButton *pushButtonPaper;
    QPushButton *pushButtonOptions;
    QListWidget *listWidgetOptions;
    QLabel *labelPaper;
    QLineEdit *lineEditTitle;
    QComboBox *comboBoxBabel;
    QComboBox *comboBoxPaper;
    QLabel *labelAuthor;
    QLabel *labelFontEncoding;
    QComboBox *comboBoxFontEncoding;
    QPushButton *pushButtonFontEncoding;
    QWidget *tabPackages;
    QHBoxLayout *HboxPackages;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tableWidgetPackages;
    QPushButton *pushButtonPackages;
    QWidget *tabGeometry;
    QVBoxLayout *verticalLayout;
    QLabel *geometryPreviewLabel;
    QGroupBox *groupBox;
    QGridLayout *_3;
    QCheckBox *checkBoxGeometryPageWidth;
    QDoubleSpinBox *spinBoxGeometryPageWidth;
    QComboBox *comboBoxUnitGeometryPageWidth;
    QComboBox *comboBoxUnitGeometryPageHeight;
    QDoubleSpinBox *spinBoxGeometryPageHeight;
    QCheckBox *checkBoxGeometryPageHeight;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBoxGeometryMarginLeft;
    QDoubleSpinBox *spinBoxGeometryMarginLeft;
    QComboBox *comboBoxUnitGeometryMarginLeft;
    QCheckBox *checkBoxGeometryMarginRight;
    QDoubleSpinBox *spinBoxGeometryMarginRight;
    QComboBox *comboBoxUnitGeometryMarginRight;
    QDoubleSpinBox *spinBoxGeometryMarginTop;
    QComboBox *comboBoxUnitGeometryMarginTop;
    QCheckBox *checkBoxGeometryMarginTop;
    QCheckBox *checkBoxGeometryMarginBottom;
    QDoubleSpinBox *spinBoxGeometryMarginBottom;
    QComboBox *comboBoxUnitGeometryMarginBottom;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QuickDocumentDialog)
    {
        if (QuickDocumentDialog->objectName().isEmpty())
            QuickDocumentDialog->setObjectName(QString::fromUtf8("QuickDocumentDialog"));
        QuickDocumentDialog->resize(511, 513);
        verticalLayout_3 = new QVBoxLayout(QuickDocumentDialog);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(9, 9, 9, 9);
        tabWidget = new QTabWidget(QuickDocumentDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabClass = new QWidget();
        tabClass->setObjectName(QString::fromUtf8("tabClass"));
        horizontalLayout = new QHBoxLayout(tabClass);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _2 = new QGridLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        labelTitle = new QLabel(tabClass);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy);

        _2->addWidget(labelTitle, 7, 0, 1, 1);

        lineEditAuthor = new QLineEdit(tabClass);
        lineEditAuthor->setObjectName(QString::fromUtf8("lineEditAuthor"));

        _2->addWidget(lineEditAuthor, 8, 1, 1, 1);

        labelBabel = new QLabel(tabClass);
        labelBabel->setObjectName(QString::fromUtf8("labelBabel"));

        _2->addWidget(labelBabel, 5, 0, 1, 1);

        comboBoxClass = new QComboBox(tabClass);
        comboBoxClass->setObjectName(QString::fromUtf8("comboBoxClass"));

        _2->addWidget(comboBoxClass, 0, 1, 1, 1);

        labelClass = new QLabel(tabClass);
        labelClass->setObjectName(QString::fromUtf8("labelClass"));
        sizePolicy.setHeightForWidth(labelClass->sizePolicy().hasHeightForWidth());
        labelClass->setSizePolicy(sizePolicy);

        _2->addWidget(labelClass, 0, 0, 1, 1);

        pushButtonClass = new QPushButton(tabClass);
        pushButtonClass->setObjectName(QString::fromUtf8("pushButtonClass"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/list-add.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonClass->setIcon(icon);

        _2->addWidget(pushButtonClass, 0, 2, 1, 1);

        labelSize = new QLabel(tabClass);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));
        sizePolicy.setHeightForWidth(labelSize->sizePolicy().hasHeightForWidth());
        labelSize->setSizePolicy(sizePolicy);

        _2->addWidget(labelSize, 1, 0, 1, 1);

        labelOptions = new QLabel(tabClass);
        labelOptions->setObjectName(QString::fromUtf8("labelOptions"));
        sizePolicy.setHeightForWidth(labelOptions->sizePolicy().hasHeightForWidth());
        labelOptions->setSizePolicy(sizePolicy);

        _2->addWidget(labelOptions, 9, 0, 1, 1);

        pushButtonBabel = new QPushButton(tabClass);
        pushButtonBabel->setObjectName(QString::fromUtf8("pushButtonBabel"));
        pushButtonBabel->setIcon(icon);

        _2->addWidget(pushButtonBabel, 5, 2, 1, 1);

        comboBoxSize = new QComboBox(tabClass);
        comboBoxSize->setObjectName(QString::fromUtf8("comboBoxSize"));

        _2->addWidget(comboBoxSize, 1, 1, 1, 1);

        pushButtonPaper = new QPushButton(tabClass);
        pushButtonPaper->setObjectName(QString::fromUtf8("pushButtonPaper"));
        pushButtonPaper->setIcon(icon);

        _2->addWidget(pushButtonPaper, 2, 2, 1, 1);

        pushButtonOptions = new QPushButton(tabClass);
        pushButtonOptions->setObjectName(QString::fromUtf8("pushButtonOptions"));
        pushButtonOptions->setIcon(icon);

        _2->addWidget(pushButtonOptions, 9, 2, 1, 1);

        listWidgetOptions = new QListWidget(tabClass);
        listWidgetOptions->setObjectName(QString::fromUtf8("listWidgetOptions"));

        _2->addWidget(listWidgetOptions, 9, 1, 1, 1);

        labelPaper = new QLabel(tabClass);
        labelPaper->setObjectName(QString::fromUtf8("labelPaper"));
        sizePolicy.setHeightForWidth(labelPaper->sizePolicy().hasHeightForWidth());
        labelPaper->setSizePolicy(sizePolicy);

        _2->addWidget(labelPaper, 2, 0, 1, 1);

        lineEditTitle = new QLineEdit(tabClass);
        lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

        _2->addWidget(lineEditTitle, 7, 1, 1, 1);

        comboBoxBabel = new QComboBox(tabClass);
        comboBoxBabel->setObjectName(QString::fromUtf8("comboBoxBabel"));

        _2->addWidget(comboBoxBabel, 5, 1, 1, 1);

        comboBoxPaper = new QComboBox(tabClass);
        comboBoxPaper->setObjectName(QString::fromUtf8("comboBoxPaper"));

        _2->addWidget(comboBoxPaper, 2, 1, 1, 1);

        labelAuthor = new QLabel(tabClass);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));
        sizePolicy.setHeightForWidth(labelAuthor->sizePolicy().hasHeightForWidth());
        labelAuthor->setSizePolicy(sizePolicy);

        _2->addWidget(labelAuthor, 8, 0, 1, 1);

        labelFontEncoding = new QLabel(tabClass);
        labelFontEncoding->setObjectName(QString::fromUtf8("labelFontEncoding"));

        _2->addWidget(labelFontEncoding, 4, 0, 1, 1);

        comboBoxFontEncoding = new QComboBox(tabClass);
        comboBoxFontEncoding->setObjectName(QString::fromUtf8("comboBoxFontEncoding"));

        _2->addWidget(comboBoxFontEncoding, 4, 1, 1, 1);

        pushButtonFontEncoding = new QPushButton(tabClass);
        pushButtonFontEncoding->setObjectName(QString::fromUtf8("pushButtonFontEncoding"));
        pushButtonFontEncoding->setIcon(icon);

        _2->addWidget(pushButtonFontEncoding, 4, 2, 1, 1);


        horizontalLayout->addLayout(_2);

        tabWidget->addTab(tabClass, QString());
        tabPackages = new QWidget();
        tabPackages->setObjectName(QString::fromUtf8("tabPackages"));
        HboxPackages = new QHBoxLayout(tabPackages);
        HboxPackages->setObjectName(QString::fromUtf8("HboxPackages"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableWidgetPackages = new QTableWidget(tabPackages);
        if (tableWidgetPackages->columnCount() < 2)
            tableWidgetPackages->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPackages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPackages->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetPackages->setObjectName(QString::fromUtf8("tableWidgetPackages"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidgetPackages->sizePolicy().hasHeightForWidth());
        tableWidgetPackages->setSizePolicy(sizePolicy1);
        tableWidgetPackages->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        horizontalLayout_2->addWidget(tableWidgetPackages);

        pushButtonPackages = new QPushButton(tabPackages);
        pushButtonPackages->setObjectName(QString::fromUtf8("pushButtonPackages"));
        pushButtonPackages->setIcon(icon);

        horizontalLayout_2->addWidget(pushButtonPackages);


        HboxPackages->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabPackages, QString());
        tabGeometry = new QWidget();
        tabGeometry->setObjectName(QString::fromUtf8("tabGeometry"));
        verticalLayout = new QVBoxLayout(tabGeometry);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        geometryPreviewLabel = new QLabel(tabGeometry);
        geometryPreviewLabel->setObjectName(QString::fromUtf8("geometryPreviewLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(geometryPreviewLabel->sizePolicy().hasHeightForWidth());
        geometryPreviewLabel->setSizePolicy(sizePolicy2);
        geometryPreviewLabel->setMinimumSize(QSize(0, 93));
        geometryPreviewLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(geometryPreviewLabel);

        groupBox = new QGroupBox(tabGeometry);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        _3 = new QGridLayout(groupBox);
        _3->setObjectName(QString::fromUtf8("_3"));
        checkBoxGeometryPageWidth = new QCheckBox(groupBox);
        checkBoxGeometryPageWidth->setObjectName(QString::fromUtf8("checkBoxGeometryPageWidth"));

        _3->addWidget(checkBoxGeometryPageWidth, 0, 0, 2, 1);

        spinBoxGeometryPageWidth = new QDoubleSpinBox(groupBox);
        spinBoxGeometryPageWidth->setObjectName(QString::fromUtf8("spinBoxGeometryPageWidth"));
        spinBoxGeometryPageWidth->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryPageWidth->setMaximum(99999.990000000005239);

        _3->addWidget(spinBoxGeometryPageWidth, 0, 1, 1, 1);

        comboBoxUnitGeometryPageWidth = new QComboBox(groupBox);
        comboBoxUnitGeometryPageWidth->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryPageWidth->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryPageWidth->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryPageWidth->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryPageWidth->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryPageWidth->setObjectName(QString::fromUtf8("comboBoxUnitGeometryPageWidth"));
        comboBoxUnitGeometryPageWidth->setEditable(false);

        _3->addWidget(comboBoxUnitGeometryPageWidth, 0, 2, 1, 1);

        comboBoxUnitGeometryPageHeight = new QComboBox(groupBox);
        comboBoxUnitGeometryPageHeight->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryPageHeight->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryPageHeight->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryPageHeight->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryPageHeight->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryPageHeight->setObjectName(QString::fromUtf8("comboBoxUnitGeometryPageHeight"));
        comboBoxUnitGeometryPageHeight->setEditable(false);

        _3->addWidget(comboBoxUnitGeometryPageHeight, 1, 2, 2, 1);

        spinBoxGeometryPageHeight = new QDoubleSpinBox(groupBox);
        spinBoxGeometryPageHeight->setObjectName(QString::fromUtf8("spinBoxGeometryPageHeight"));
        spinBoxGeometryPageHeight->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryPageHeight->setMaximum(99999.990000000005239);

        _3->addWidget(spinBoxGeometryPageHeight, 1, 1, 2, 1);

        checkBoxGeometryPageHeight = new QCheckBox(groupBox);
        checkBoxGeometryPageHeight->setObjectName(QString::fromUtf8("checkBoxGeometryPageHeight"));

        _3->addWidget(checkBoxGeometryPageHeight, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tabGeometry);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBoxGeometryMarginLeft = new QCheckBox(groupBox_2);
        checkBoxGeometryMarginLeft->setObjectName(QString::fromUtf8("checkBoxGeometryMarginLeft"));

        gridLayout_2->addWidget(checkBoxGeometryMarginLeft, 0, 0, 1, 1);

        spinBoxGeometryMarginLeft = new QDoubleSpinBox(groupBox_2);
        spinBoxGeometryMarginLeft->setObjectName(QString::fromUtf8("spinBoxGeometryMarginLeft"));
        spinBoxGeometryMarginLeft->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryMarginLeft->setMaximum(99999.990000000005239);
        spinBoxGeometryMarginLeft->setValue(20.000000000000000);

        gridLayout_2->addWidget(spinBoxGeometryMarginLeft, 0, 1, 1, 1);

        comboBoxUnitGeometryMarginLeft = new QComboBox(groupBox_2);
        comboBoxUnitGeometryMarginLeft->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryMarginLeft->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryMarginLeft->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryMarginLeft->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryMarginLeft->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryMarginLeft->setObjectName(QString::fromUtf8("comboBoxUnitGeometryMarginLeft"));
        comboBoxUnitGeometryMarginLeft->setEditable(false);

        gridLayout_2->addWidget(comboBoxUnitGeometryMarginLeft, 0, 2, 1, 1);

        checkBoxGeometryMarginRight = new QCheckBox(groupBox_2);
        checkBoxGeometryMarginRight->setObjectName(QString::fromUtf8("checkBoxGeometryMarginRight"));

        gridLayout_2->addWidget(checkBoxGeometryMarginRight, 1, 0, 2, 1);

        spinBoxGeometryMarginRight = new QDoubleSpinBox(groupBox_2);
        spinBoxGeometryMarginRight->setObjectName(QString::fromUtf8("spinBoxGeometryMarginRight"));
        spinBoxGeometryMarginRight->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryMarginRight->setMaximum(99999.990000000005239);
        spinBoxGeometryMarginRight->setValue(20.000000000000000);

        gridLayout_2->addWidget(spinBoxGeometryMarginRight, 1, 1, 1, 1);

        comboBoxUnitGeometryMarginRight = new QComboBox(groupBox_2);
        comboBoxUnitGeometryMarginRight->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryMarginRight->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryMarginRight->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryMarginRight->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryMarginRight->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryMarginRight->setObjectName(QString::fromUtf8("comboBoxUnitGeometryMarginRight"));
        comboBoxUnitGeometryMarginRight->setEditable(false);

        gridLayout_2->addWidget(comboBoxUnitGeometryMarginRight, 1, 2, 1, 1);

        spinBoxGeometryMarginTop = new QDoubleSpinBox(groupBox_2);
        spinBoxGeometryMarginTop->setObjectName(QString::fromUtf8("spinBoxGeometryMarginTop"));
        spinBoxGeometryMarginTop->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryMarginTop->setMaximum(99999.990000000005239);
        spinBoxGeometryMarginTop->setValue(20.000000000000000);

        gridLayout_2->addWidget(spinBoxGeometryMarginTop, 2, 1, 2, 1);

        comboBoxUnitGeometryMarginTop = new QComboBox(groupBox_2);
        comboBoxUnitGeometryMarginTop->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryMarginTop->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryMarginTop->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryMarginTop->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryMarginTop->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryMarginTop->setObjectName(QString::fromUtf8("comboBoxUnitGeometryMarginTop"));
        comboBoxUnitGeometryMarginTop->setEditable(false);

        gridLayout_2->addWidget(comboBoxUnitGeometryMarginTop, 2, 2, 2, 1);

        checkBoxGeometryMarginTop = new QCheckBox(groupBox_2);
        checkBoxGeometryMarginTop->setObjectName(QString::fromUtf8("checkBoxGeometryMarginTop"));

        gridLayout_2->addWidget(checkBoxGeometryMarginTop, 3, 0, 1, 1);

        checkBoxGeometryMarginBottom = new QCheckBox(groupBox_2);
        checkBoxGeometryMarginBottom->setObjectName(QString::fromUtf8("checkBoxGeometryMarginBottom"));

        gridLayout_2->addWidget(checkBoxGeometryMarginBottom, 4, 0, 1, 1);

        spinBoxGeometryMarginBottom = new QDoubleSpinBox(groupBox_2);
        spinBoxGeometryMarginBottom->setObjectName(QString::fromUtf8("spinBoxGeometryMarginBottom"));
        spinBoxGeometryMarginBottom->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxGeometryMarginBottom->setMaximum(99999.990000000005239);
        spinBoxGeometryMarginBottom->setValue(20.000000000000000);

        gridLayout_2->addWidget(spinBoxGeometryMarginBottom, 4, 1, 1, 1);

        comboBoxUnitGeometryMarginBottom = new QComboBox(groupBox_2);
        comboBoxUnitGeometryMarginBottom->addItem(QString::fromUtf8("mm"));
        comboBoxUnitGeometryMarginBottom->addItem(QString::fromUtf8("cm"));
        comboBoxUnitGeometryMarginBottom->addItem(QString::fromUtf8("pt"));
        comboBoxUnitGeometryMarginBottom->addItem(QString::fromUtf8("bp"));
        comboBoxUnitGeometryMarginBottom->addItem(QString::fromUtf8("in"));
        comboBoxUnitGeometryMarginBottom->setObjectName(QString::fromUtf8("comboBoxUnitGeometryMarginBottom"));
        comboBoxUnitGeometryMarginBottom->setEditable(false);

        gridLayout_2->addWidget(comboBoxUnitGeometryMarginBottom, 4, 2, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        tabWidget->addTab(tabGeometry, QString());

        verticalLayout_3->addWidget(tabWidget);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(QuickDocumentDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        hboxLayout->addWidget(buttonBox);


        verticalLayout_3->addLayout(hboxLayout);

        QWidget::setTabOrder(comboBoxClass, pushButtonClass);
        QWidget::setTabOrder(pushButtonClass, comboBoxSize);
        QWidget::setTabOrder(comboBoxSize, comboBoxPaper);
        QWidget::setTabOrder(comboBoxPaper, pushButtonPaper);
        QWidget::setTabOrder(pushButtonPaper, comboBoxFontEncoding);
        QWidget::setTabOrder(comboBoxFontEncoding, pushButtonFontEncoding);
        QWidget::setTabOrder(pushButtonFontEncoding, comboBoxBabel);
        QWidget::setTabOrder(comboBoxBabel, pushButtonBabel);
        QWidget::setTabOrder(pushButtonBabel, lineEditTitle);
        QWidget::setTabOrder(lineEditTitle, lineEditAuthor);
        QWidget::setTabOrder(lineEditAuthor, listWidgetOptions);
        QWidget::setTabOrder(listWidgetOptions, pushButtonOptions);

        retranslateUi(QuickDocumentDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuickDocumentDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuickDocumentDialog, SLOT(reject()));
        QObject::connect(checkBoxGeometryPageWidth, SIGNAL(toggled(bool)), spinBoxGeometryPageWidth, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryPageWidth, SIGNAL(toggled(bool)), comboBoxUnitGeometryPageWidth, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryPageHeight, SIGNAL(toggled(bool)), spinBoxGeometryPageHeight, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryPageHeight, SIGNAL(toggled(bool)), comboBoxUnitGeometryPageHeight, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginLeft, SIGNAL(toggled(bool)), spinBoxGeometryMarginLeft, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginLeft, SIGNAL(toggled(bool)), comboBoxUnitGeometryMarginLeft, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginRight, SIGNAL(toggled(bool)), spinBoxGeometryMarginRight, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginRight, SIGNAL(toggled(bool)), comboBoxUnitGeometryMarginRight, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginTop, SIGNAL(toggled(bool)), spinBoxGeometryMarginTop, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginTop, SIGNAL(toggled(bool)), comboBoxUnitGeometryMarginTop, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginBottom, SIGNAL(toggled(bool)), spinBoxGeometryMarginBottom, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxGeometryMarginBottom, SIGNAL(toggled(bool)), comboBoxUnitGeometryMarginBottom, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QuickDocumentDialog);
    } // setupUi

    void retranslateUi(QDialog *QuickDocumentDialog)
    {
        labelTitle->setText(QCoreApplication::translate("QuickDocumentDialog", "Title", nullptr));
        labelBabel->setText(QCoreApplication::translate("QuickDocumentDialog", "Language", nullptr));
        labelBabel->setToolTip(QCoreApplication::translate("QuickDocumentDialog", "Adds language support to your document with Babel package", nullptr));
        labelClass->setText(QCoreApplication::translate("QuickDocumentDialog", "Document Class", nullptr));
        pushButtonClass->setText(QString());
        labelSize->setText(QCoreApplication::translate("QuickDocumentDialog", "Typeface Size", nullptr));
        labelOptions->setText(QCoreApplication::translate("QuickDocumentDialog", "Other Options", nullptr));
        pushButtonBabel->setText(QString());
        pushButtonPaper->setText(QString());
        pushButtonOptions->setText(QString());
        labelPaper->setText(QCoreApplication::translate("QuickDocumentDialog", "Paper Size", nullptr));
        labelAuthor->setText(QCoreApplication::translate("QuickDocumentDialog", "Author", nullptr));
        labelFontEncoding->setText(QCoreApplication::translate("QuickDocumentDialog", "Font Encoding", nullptr));
        pushButtonFontEncoding->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabClass), QCoreApplication::translate("QuickDocumentDialog", "&Class Options", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPackages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("QuickDocumentDialog", "Package", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPackages->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("QuickDocumentDialog", "Description", nullptr));
        pushButtonPackages->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabPackages), QCoreApplication::translate("QuickDocumentDialog", "&Packages", nullptr));
        geometryPreviewLabel->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("QuickDocumentDialog", "Page", nullptr));
        checkBoxGeometryPageWidth->setText(QCoreApplication::translate("QuickDocumentDialog", "Width:", nullptr));


        checkBoxGeometryPageHeight->setText(QCoreApplication::translate("QuickDocumentDialog", "Height:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QuickDocumentDialog", "Margins", nullptr));
        checkBoxGeometryMarginLeft->setText(QCoreApplication::translate("QuickDocumentDialog", "Left:", nullptr));

        checkBoxGeometryMarginRight->setText(QCoreApplication::translate("QuickDocumentDialog", "Right:", nullptr));


        checkBoxGeometryMarginTop->setText(QCoreApplication::translate("QuickDocumentDialog", "Top:", nullptr));
        checkBoxGeometryMarginBottom->setText(QCoreApplication::translate("QuickDocumentDialog", "Bottom:", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tabGeometry), QCoreApplication::translate("QuickDocumentDialog", "&Geometry", nullptr));
        (void)QuickDocumentDialog;
    } // retranslateUi

};

namespace Ui {
    class QuickDocumentDialog: public Ui_QuickDocumentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKDOCUMENTDIALOG_H
