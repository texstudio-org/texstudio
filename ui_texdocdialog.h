/********************************************************************************
** Form generated from reading UI file 'texdocdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXDOCDIALOG_H
#define UI_TEXDOCDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TexdocDialog
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QTableWidget *tbPackages;
    QSplitter *splitter;
    QTextBrowser *packageInfoBrowser;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *languagesLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *packageDescriptions;
    QHBoxLayout *hboxWarning;
    QSpacerItem *horizontalSpacerHboxWarning;
    QLabel *lbWarnIcon;
    QLabel *lbInfo;
    QPushButton *buttonCTAN;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *hboxFilter;
    QLineEdit *lineEditSearch;
    QCheckBox *cbShowAllPackages;

    void setupUi(QDialog *TexdocDialog)
    {
        if (TexdocDialog->objectName().isEmpty())
            TexdocDialog->setObjectName(QString::fromUtf8("TexdocDialog"));
        TexdocDialog->resize(818, 640);
        gridLayout = new QGridLayout(TexdocDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(TexdocDialog);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        tbPackages = new QTableWidget(splitter_2);
        if (tbPackages->columnCount() < 1)
            tbPackages->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbPackages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tbPackages->setObjectName(QString::fromUtf8("tbPackages"));
        splitter_2->addWidget(tbPackages);
        tbPackages->horizontalHeader()->setStretchLastSection(true);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        packageInfoBrowser = new QTextBrowser(splitter);
        packageInfoBrowser->setObjectName(QString::fromUtf8("packageInfoBrowser"));
        splitter->addWidget(packageInfoBrowser);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        languagesLayout = new QHBoxLayout();
        languagesLayout->setObjectName(QString::fromUtf8("languagesLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        languagesLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        languagesLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(languagesLayout);

        packageDescriptions = new QTextBrowser(layoutWidget);
        packageDescriptions->setObjectName(QString::fromUtf8("packageDescriptions"));

        verticalLayout->addWidget(packageDescriptions);

        splitter->addWidget(layoutWidget);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 1, 0, 1, 2);

        hboxWarning = new QHBoxLayout();
        hboxWarning->setObjectName(QString::fromUtf8("hboxWarning"));
        horizontalSpacerHboxWarning = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxWarning->addItem(horizontalSpacerHboxWarning);

        lbWarnIcon = new QLabel(TexdocDialog);
        lbWarnIcon->setObjectName(QString::fromUtf8("lbWarnIcon"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbWarnIcon->sizePolicy().hasHeightForWidth());
        lbWarnIcon->setSizePolicy(sizePolicy);
        lbWarnIcon->setMaximumSize(QSize(16, 16));
        lbWarnIcon->setPixmap(QPixmap(QString::fromUtf8(":/images-ng/warning.svgz")));
        lbWarnIcon->setScaledContents(true);

        hboxWarning->addWidget(lbWarnIcon);

        lbInfo = new QLabel(TexdocDialog);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbInfo->sizePolicy().hasHeightForWidth());
        lbInfo->setSizePolicy(sizePolicy1);
        lbInfo->setMinimumSize(QSize(0, 16));
        lbInfo->setText(QString::fromUtf8("Warning message"));

        hboxWarning->addWidget(lbInfo);


        gridLayout->addLayout(hboxWarning, 2, 0, 1, 2);

        buttonCTAN = new QPushButton(TexdocDialog);
        buttonCTAN->setObjectName(QString::fromUtf8("buttonCTAN"));

        gridLayout->addWidget(buttonCTAN, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(TexdocDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Open);

        gridLayout->addWidget(buttonBox, 3, 1, 1, 1);

        hboxFilter = new QHBoxLayout();
        hboxFilter->setObjectName(QString::fromUtf8("hboxFilter"));
        lineEditSearch = new QLineEdit(TexdocDialog);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));

        hboxFilter->addWidget(lineEditSearch);

        cbShowAllPackages = new QCheckBox(TexdocDialog);
        cbShowAllPackages->setObjectName(QString::fromUtf8("cbShowAllPackages"));

        hboxFilter->addWidget(cbShowAllPackages);


        gridLayout->addLayout(hboxFilter, 0, 0, 1, 2);


        retranslateUi(TexdocDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TexdocDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TexdocDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TexdocDialog);
    } // setupUi

    void retranslateUi(QDialog *TexdocDialog)
    {
        TexdocDialog->setWindowTitle(QCoreApplication::translate("TexdocDialog", "Packages Help (Texdoc)", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbPackages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TexdocDialog", "Packages", nullptr));
        label->setText(QCoreApplication::translate("TexdocDialog", "Package descriptions", nullptr));
        lbWarnIcon->setText(QString());
        buttonCTAN->setText(QCoreApplication::translate("TexdocDialog", "open CTAN", nullptr));
#if QT_CONFIG(tooltip)
        lineEditSearch->setToolTip(QCoreApplication::translate("TexdocDialog", "Enter a term to search for in both columns.", nullptr));
#endif // QT_CONFIG(tooltip)
        cbShowAllPackages->setText(QCoreApplication::translate("TexdocDialog", "all packages", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TexdocDialog: public Ui_TexdocDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXDOCDIALOG_H
