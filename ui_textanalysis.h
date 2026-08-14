/********************************************************************************
** Form generated from reading UI file 'textanalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTANALYSIS_H
#define UI_TEXTANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TextAnalysisDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout;
    QPushButton *countButton;
    QPushButton *searchSelectionButton;
    QPushButton *exportButton;
    QPushButton *closeButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout1;
    QLabel *label_2;
    QLabel *totalLinesLabel;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *textLinesLabel;
    QLabel *commentLinesLabel;
    QLabel *displayedWordLabel;
    QLabel *label;
    QLabel *differentWordLabel;
    QLabel *label_6;
    QLabel *characterInWordsLabel;
    QFrame *line;
    QTableView *resultView;
    QGroupBox *groupBox_2;
    QGridLayout *_2;
    QCheckBox *normalTextCheck;
    QCheckBox *commentsCheck;
    QCheckBox *commandsCheck;
    QComboBox *minimumLengthMeaning;
    QSpinBox *minimumLengthSpin;
    QLabel *label_9;
    QSpinBox *minimumCountSpin;
    QSpinBox *sentenceLengthSpin;
    QLabel *label_7;
    QLineEdit *sentenceEndChars;
    QCheckBox *respectEndCharsCheck;
    QComboBox *wordsPerPhraseMeaning;
    QComboBox *filter;
    QLabel *label_8;
    QComboBox *comboBox;

    void setupUi(QDialog *TextAnalysisDialog)
    {
        if (TextAnalysisDialog->objectName().isEmpty())
            TextAnalysisDialog->setObjectName(QString::fromUtf8("TextAnalysisDialog"));
        TextAnalysisDialog->resize(560, 664);
        gridLayout = new QGridLayout(TextAnalysisDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(TextAnalysisDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout = new QVBoxLayout(groupBox);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        countButton = new QPushButton(groupBox);
        countButton->setObjectName(QString::fromUtf8("countButton"));

        vboxLayout->addWidget(countButton);

        searchSelectionButton = new QPushButton(groupBox);
        searchSelectionButton->setObjectName(QString::fromUtf8("searchSelectionButton"));

        vboxLayout->addWidget(searchSelectionButton);

        exportButton = new QPushButton(groupBox);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        vboxLayout->addWidget(exportButton);

        closeButton = new QPushButton(groupBox);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        vboxLayout->addWidget(closeButton);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(TextAnalysisDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout1 = new QGridLayout(groupBox_3);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout1->addWidget(label_2, 0, 0, 1, 1);

        totalLinesLabel = new QLabel(groupBox_3);
        totalLinesLabel->setObjectName(QString::fromUtf8("totalLinesLabel"));

        gridLayout1->addWidget(totalLinesLabel, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout1->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout1->addWidget(label_4, 4, 0, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout1->addWidget(label_5, 2, 0, 1, 1);

        textLinesLabel = new QLabel(groupBox_3);
        textLinesLabel->setObjectName(QString::fromUtf8("textLinesLabel"));

        gridLayout1->addWidget(textLinesLabel, 1, 1, 1, 1);

        commentLinesLabel = new QLabel(groupBox_3);
        commentLinesLabel->setObjectName(QString::fromUtf8("commentLinesLabel"));

        gridLayout1->addWidget(commentLinesLabel, 2, 1, 1, 1);

        displayedWordLabel = new QLabel(groupBox_3);
        displayedWordLabel->setObjectName(QString::fromUtf8("displayedWordLabel"));

        gridLayout1->addWidget(displayedWordLabel, 4, 1, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 5, 0, 1, 1);

        differentWordLabel = new QLabel(groupBox_3);
        differentWordLabel->setObjectName(QString::fromUtf8("differentWordLabel"));

        gridLayout1->addWidget(differentWordLabel, 5, 1, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout1->addWidget(label_6, 6, 0, 1, 1);

        characterInWordsLabel = new QLabel(groupBox_3);
        characterInWordsLabel->setObjectName(QString::fromUtf8("characterInWordsLabel"));

        gridLayout1->addWidget(characterInWordsLabel, 6, 1, 1, 1);

        line = new QFrame(groupBox_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout1->addWidget(line, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        resultView = new QTableView(TextAnalysisDialog);
        resultView->setObjectName(QString::fromUtf8("resultView"));

        gridLayout->addWidget(resultView, 0, 1, 3, 3);

        groupBox_2 = new QGroupBox(TextAnalysisDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        _2 = new QGridLayout(groupBox_2);
        _2->setObjectName(QString::fromUtf8("_2"));
        normalTextCheck = new QCheckBox(groupBox_2);
        normalTextCheck->setObjectName(QString::fromUtf8("normalTextCheck"));
        normalTextCheck->setChecked(true);

        _2->addWidget(normalTextCheck, 0, 0, 1, 2);

        commentsCheck = new QCheckBox(groupBox_2);
        commentsCheck->setObjectName(QString::fromUtf8("commentsCheck"));

        _2->addWidget(commentsCheck, 1, 0, 1, 2);

        commandsCheck = new QCheckBox(groupBox_2);
        commandsCheck->setObjectName(QString::fromUtf8("commandsCheck"));

        _2->addWidget(commandsCheck, 2, 0, 1, 2);

        minimumLengthMeaning = new QComboBox(groupBox_2);
        minimumLengthMeaning->addItem(QString());
        minimumLengthMeaning->addItem(QString());
        minimumLengthMeaning->addItem(QString());
        minimumLengthMeaning->addItem(QString());
        minimumLengthMeaning->addItem(QString());
        minimumLengthMeaning->setObjectName(QString::fromUtf8("minimumLengthMeaning"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(minimumLengthMeaning->sizePolicy().hasHeightForWidth());
        minimumLengthMeaning->setSizePolicy(sizePolicy1);

        _2->addWidget(minimumLengthMeaning, 3, 0, 1, 2);

        minimumLengthSpin = new QSpinBox(groupBox_2);
        minimumLengthSpin->setObjectName(QString::fromUtf8("minimumLengthSpin"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(minimumLengthSpin->sizePolicy().hasHeightForWidth());
        minimumLengthSpin->setSizePolicy(sizePolicy2);
        minimumLengthSpin->setMinimumSize(QSize(40, 0));
        minimumLengthSpin->setValue(4);

        _2->addWidget(minimumLengthSpin, 3, 2, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        _2->addWidget(label_9, 4, 0, 1, 2);

        minimumCountSpin = new QSpinBox(groupBox_2);
        minimumCountSpin->setObjectName(QString::fromUtf8("minimumCountSpin"));
        sizePolicy2.setHeightForWidth(minimumCountSpin->sizePolicy().hasHeightForWidth());
        minimumCountSpin->setSizePolicy(sizePolicy2);
        minimumCountSpin->setMinimumSize(QSize(40, 0));

        _2->addWidget(minimumCountSpin, 4, 2, 1, 1);

        sentenceLengthSpin = new QSpinBox(groupBox_2);
        sentenceLengthSpin->setObjectName(QString::fromUtf8("sentenceLengthSpin"));
        sizePolicy2.setHeightForWidth(sentenceLengthSpin->sizePolicy().hasHeightForWidth());
        sentenceLengthSpin->setSizePolicy(sizePolicy2);
        sentenceLengthSpin->setMinimumSize(QSize(40, 0));
        sentenceLengthSpin->setMinimum(1);
        sentenceLengthSpin->setValue(1);

        _2->addWidget(sentenceLengthSpin, 5, 2, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        _2->addWidget(label_7, 8, 0, 1, 1);

        sentenceEndChars = new QLineEdit(groupBox_2);
        sentenceEndChars->setObjectName(QString::fromUtf8("sentenceEndChars"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sentenceEndChars->sizePolicy().hasHeightForWidth());
        sentenceEndChars->setSizePolicy(sizePolicy3);
        sentenceEndChars->setMinimumSize(QSize(40, 0));

        _2->addWidget(sentenceEndChars, 6, 2, 1, 1);

        respectEndCharsCheck = new QCheckBox(groupBox_2);
        respectEndCharsCheck->setObjectName(QString::fromUtf8("respectEndCharsCheck"));

        _2->addWidget(respectEndCharsCheck, 6, 0, 1, 2);

        wordsPerPhraseMeaning = new QComboBox(groupBox_2);
        wordsPerPhraseMeaning->addItem(QString());
        wordsPerPhraseMeaning->addItem(QString());
        wordsPerPhraseMeaning->setObjectName(QString::fromUtf8("wordsPerPhraseMeaning"));

        _2->addWidget(wordsPerPhraseMeaning, 5, 0, 1, 2);

        filter = new QComboBox(groupBox_2);
        filter->addItem(QString());
        filter->addItem(QString());
        filter->addItem(QString());
        filter->setObjectName(QString::fromUtf8("filter"));
        filter->setEditable(true);
        filter->setInsertPolicy(QComboBox::NoInsert);

        _2->addWidget(filter, 7, 1, 1, 2);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        _2->addWidget(label_8, 7, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setLayoutDirection(Qt::LeftToRight);

        _2->addWidget(comboBox, 8, 1, 1, 2);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(TextAnalysisDialog);

        minimumLengthMeaning->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TextAnalysisDialog);
    } // setupUi

    void retranslateUi(QDialog *TextAnalysisDialog)
    {
        TextAnalysisDialog->setWindowTitle(QCoreApplication::translate("TextAnalysisDialog", "Text Analysis", nullptr));
        groupBox->setTitle(QCoreApplication::translate("TextAnalysisDialog", "Actions", nullptr));
        countButton->setText(QCoreApplication::translate("TextAnalysisDialog", "Count", nullptr));
        searchSelectionButton->setText(QCoreApplication::translate("TextAnalysisDialog", "Search selection in the document", nullptr));
        exportButton->setText(QCoreApplication::translate("TextAnalysisDialog", "CSV Export", nullptr));
        closeButton->setText(QCoreApplication::translate("TextAnalysisDialog", "Close", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("TextAnalysisDialog", "Info", nullptr));
        label_2->setText(QCoreApplication::translate("TextAnalysisDialog", "Total lines", nullptr));
        totalLinesLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        label_3->setText(QCoreApplication::translate("TextAnalysisDialog", "Text lines", nullptr));
        label_4->setText(QCoreApplication::translate("TextAnalysisDialog", "Total shown phrases", nullptr));
        label_5->setText(QCoreApplication::translate("TextAnalysisDialog", "Comment lines", nullptr));
        textLinesLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        commentLinesLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        displayedWordLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        label->setText(QCoreApplication::translate("TextAnalysisDialog", "Different phrases", nullptr));
        differentWordLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        label_6->setText(QCoreApplication::translate("TextAnalysisDialog", "Characters in phrases", nullptr));
        characterInWordsLabel->setText(QCoreApplication::translate("TextAnalysisDialog", "?", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("TextAnalysisDialog", "Options", nullptr));
#if QT_CONFIG(tooltip)
        normalTextCheck->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "If this is enabled, words/phrases in the normal text (which aren't in comments) are counted", nullptr));
#endif // QT_CONFIG(tooltip)
        normalTextCheck->setText(QCoreApplication::translate("TextAnalysisDialog", "Analyse normal text", nullptr));
#if QT_CONFIG(tooltip)
        commentsCheck->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "If this is enabled, words/phrases in the comments are counted.", nullptr));
#endif // QT_CONFIG(tooltip)
        commentsCheck->setText(QCoreApplication::translate("TextAnalysisDialog", "Analyse comments", nullptr));
#if QT_CONFIG(tooltip)
        commandsCheck->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "If this is enabled, \\commands are counted.", nullptr));
#endif // QT_CONFIG(tooltip)
        commandsCheck->setText(QCoreApplication::translate("TextAnalysisDialog", "Analyse commands", nullptr));
        minimumLengthMeaning->setItemText(0, QCoreApplication::translate("TextAnalysisDialog", "Show all phrases", nullptr));
        minimumLengthMeaning->setItemText(1, QCoreApplication::translate("TextAnalysisDialog", "Minimum phrase length:", nullptr));
        minimumLengthMeaning->setItemText(2, QCoreApplication::translate("TextAnalysisDialog", "Minimum word length (one):", nullptr));
        minimumLengthMeaning->setItemText(3, QCoreApplication::translate("TextAnalysisDialog", "Minimum word length (all):", nullptr));
        minimumLengthMeaning->setItemText(4, QCoreApplication::translate("TextAnalysisDialog", "Fully ignore shorter words:", nullptr));

#if QT_CONFIG(tooltip)
        minimumLengthMeaning->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "Possible Options:\n"
"\"Show all\": All phrases are shown.\n"
"\"Minimum phrase length\": A phrase is only shown if it has at least this many characters. (e.g. \"a test\" has 6 characters)\n"
"\"Minimum word length (one)\": A phrase is only shown if it contains a word with at least this many characters. (e.g. \"a test\" has 4 characters)\n"
"\"Minimum word length (all)\": A phrase is only shown if all of its words have at least this many characters. (e.g. \"a test\" has 1 character)\n"
"\"Completely ignore\": Shorter words are completely ignored.\n"
"(e.g. with length 3, the sentence \"this is a test\" is equivalent to \"this test\", while the other options would separate it into \"this is\", \"is a\", \"a test\", even if none of these phrases would be shown.)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        minimumLengthSpin->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "<html><head/><body><p>If &quot;show all&quot; is selected, all phrases are shown.</p><p>If &quot;minimum phrase length&quot; is selected, a phrase is only shown if it has at least this many characters. (e.g. &quot;a test&quot; has 6 characters)</p><p>If &quot;minimum word length (one)&quot; is selected, a phrase is only shown if one of its words has at least this many characters. (e.g. &quot;a test&quot; has 4 characters)</p><p>If &quot;minimum word length (all)&quot; is selected, a phrase is only shown if all of its words have at least this many characters. (e.g. &quot;a test&quot; has 1 character)</p><p>If &quot;completely ignore&quot; is selected, shorter words are completely ignored.</p><p>(e.g. with length 3, the sentence &quot;this is a test&quot; is equivalent to &quot;this test&quot;, while the other options would separate it into &quot;this is&quot;, &quot;is a&quot;, &quot;a test&quot;, even if none of these phrases would be shown.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("TextAnalysisDialog", "Minimum occurrence count:", nullptr));
#if QT_CONFIG(tooltip)
        minimumCountSpin->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "Only phrases are shown which appear at least this many times in the document.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        sentenceLengthSpin->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "The controls in this row determine how many consecutive words are treated as a single phrase.\n"
"If minimum and maximum are selected, exactly this many words are taken. (e.g. with 2, in the sentence above: \"the controls\", \"controls in\",...)\n"
"If only maximum is selected, words at the beginning are also taken. (e.g. \"the\", \"the controls\", \"controls in\",...)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("TextAnalysisDialog", "Source:", nullptr));
#if QT_CONFIG(tooltip)
        sentenceEndChars->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "If \"respect phrase end chars\" is checked, words before and after a given character are always treated as words of different phrases.\n"
"If not, end characters are ignored.", nullptr));
#endif // QT_CONFIG(tooltip)
        sentenceEndChars->setText(QCoreApplication::translate("TextAnalysisDialog", ".;:?!", nullptr));
#if QT_CONFIG(tooltip)
        respectEndCharsCheck->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "If \"respect phrase end chars\" is checked, words before and after a given character are always treated as words of different phrases.\n"
"If not, end characters are ignored.", nullptr));
#endif // QT_CONFIG(tooltip)
        respectEndCharsCheck->setText(QCoreApplication::translate("TextAnalysisDialog", "Respect phrase end chars:", nullptr));
        wordsPerPhraseMeaning->setItemText(0, QCoreApplication::translate("TextAnalysisDialog", "Maximum words per phrase:", nullptr));
        wordsPerPhraseMeaning->setItemText(1, QCoreApplication::translate("TextAnalysisDialog", "Min&max words per phrase:", nullptr));

#if QT_CONFIG(tooltip)
        wordsPerPhraseMeaning->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "The controls in this row determine how many consecutive words are treated as a single phrase.\n"
"If minimum and maximum are selected, exactly this many words are taken. (e.g. with 2, in the sentence above: \"the controls\", \"controls in\",...)\n"
"If only maximum is selected, words at the beginning are also taken. (e.g. \"the\", \"the controls\", \"controls in\",...)", nullptr));
#endif // QT_CONFIG(tooltip)
        filter->setItemText(0, QCoreApplication::translate("TextAnalysisDialog", "None (.*)", nullptr));
        filter->setItemText(1, QCoreApplication::translate("TextAnalysisDialog", "No Numbers (.*[^0-9].*)", nullptr));
        filter->setItemText(2, QCoreApplication::translate("TextAnalysisDialog", "No Digits ([^0-9]*)", nullptr));

        label_8->setText(QCoreApplication::translate("TextAnalysisDialog", "Filter", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("TextAnalysisDialog", "Whole document", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TextAnalysisDialog", "Selection", nullptr));

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QCoreApplication::translate("TextAnalysisDialog", "Determines whether the whole document, only the selection, or only a certain chapter is analysed.", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class TextAnalysisDialog: public Ui_TextAnalysisDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTANALYSIS_H
