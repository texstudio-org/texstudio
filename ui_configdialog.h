/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QVBoxLayout *verticalLayout_19;
    QSplitter *mainSplitter;
    QWidget *leftPart;
    QVBoxLayout *vboxLayout;
    QListWidget *contentsWidget;
    QLineEdit *lineEditMetaFilter;
    QWidget *rightPart;
    QGridLayout *gridLayout;
    QStackedWidget *pagesWidget;
    QWidget *pageGeneral;
    QVBoxLayout *vboxLayout1;
    QScrollArea *scrollAreaGeneral;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Appearance;
    QGridLayout *gridLayout1;
    QComboBox *comboBoxInterfaceStyle;
    QLabel *label_14;
    QFontComboBox *comboBoxInterfaceFont;
    QComboBox *comboBoxLanguage;
    QLabel *label_3;
    QSpinBox *spinBoxInterfaceFontSize;
    QLabel *label_9;
    QLabel *label_5;
    QComboBox *comboBoxInterfaceModernStyle;
    QLabel *label_7;
    QHBoxLayout *hboxLayout;
    QCheckBox *checkBoxUseTexmakerPalette;
    QCheckBox *checkBoxUseSystemTheme;
    QSpacerItem *spacerItem;
    QLabel *label_27;
    QComboBox *comboBoxInterfaceIconTheme;
    QGroupBox *groupBox_Files;
    QGridLayout *gridLayout2;
    QLabel *label_10;
    QCheckBox *checkBoxRememberFileFilter;
    QSpinBox *spinBoxMaxRecentProjects;
    QLabel *label_8;
    QSpinBox *spinBoxMaxRecentFiles;
    QCheckBox *checkBoxUseNativeFileDialog;
    QCheckBox *checkBoxParseRootDoc;
    QCheckBox *checkBoxMRUDocumentChooser;
    QGroupBox *groupBox_Session;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *checkBoxRestoreSession;
    QCheckBox *checkBoxSessionStoreRelativePaths;
    QGroupBox *groupBox_Startup;
    QVBoxLayout *verticalLayout_14;
    QCheckBox *checkBoxCheckLatexConfiguration;
    QGroupBox *groupBox_Update;
    QGridLayout *gridLayout03;
    QComboBox *comboBoxUpdateLevel;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonUpdateCheckNow;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelUpdateCheckDate;
    QLabel *label_56;
    QSpinBox *spinBoxAutoUpdateCheckIntervalDays;
    QCheckBox *checkBoxAutoUpdateCheck;
    QLabel *label_74;
    QSpacerItem *spacerItem1;
    QWidget *pageCommands;
    QVBoxLayout *vboxLayout2;
    QGroupBox *groupBoxCommands;
    QLabel *label_15;
    QLabel *label_4;
    QLabel *label_17;
    QLabel *label_16;
    QWidget *pageBuild;
    QVBoxLayout *vboxLayout3;
    QScrollArea *scrollAreaBuild;
    QWidget *scrollAreaBuildContents;
    QVBoxLayout *verticalLayout_17;
    QGroupBox *groupBoxMetaCommands;
    QGroupBox *groupBoxUserCommands;
    QGroupBox *groupBoxBuildOptions;
    QFormLayout *formLayout;
    QCheckBox *checkBoxRunAfterBibTeXChange;
    QCheckBox *checkBoxShowMessagesOnCompile;
    QCheckBox *checkBoxSingleInstanceViewer;
    QGridLayout *gridLayout3;
    QLabel *label_37;
    QComboBox *comboBoxShowStdout;
    QLabel *label_38;
    QSpinBox *spinBoxRerunLatex;
    QGridLayout *gridLayout_1;
    QLineEdit *lineEditPathPDF;
    QLineEdit *lineEditPathCommands;
    QPushButton *pushButtonPathPdf;
    QLabel *label_59;
    QLabel *label_58;
    QLineEdit *lineEditPathLog;
    QPushButton *pushButtonPathLog;
    QPushButton *pushButtonPathCommands;
    QLabel *label_57;
    QLabel *label_68;
    QCheckBox *checkBoxReplaceEnvironmentVariables;
    QCheckBox *checkBoxShowLogInCaseOfCompileError;
    QCheckBox *checkBoxInterpetCommandDefinitionInMagicComment;
    QWidget *pageShortcuts;
    QVBoxLayout *vboxLayout4;
    QLabel *label_6;
    QTreeWidget *shortcutTree;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBoxCloseLogByEsc;
    QCheckBox *checkBoxCloseEmbeddedViewerByEsc;
    QCheckBox *checkBoxCloseFullscreenByEsc;
    QCheckBox *checkBoxShowShortcutsInTooltips;
    QWidget *pageLatexMenus;
    QVBoxLayout *vboxLayout5;
    QLabel *label_19;
    QTreeWidget *menuTree;
    QCheckBox *checkBoxShowAllMenus;
    QWidget *pageToolbars;
    QVBoxLayout *vboxLayout6;
    QLabel *label_20;
    QGridLayout *_2;
    QListWidget *listCustomToolBar;
    QVBoxLayout *_3;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pbToToolbar;
    QPushButton *pbFromToolbar;
    QSpacerItem *spacer;
    QComboBox *comboBoxToolbars;
    QComboBox *comboBoxActions;
    QTreeWidget *treePossibleToolbarActions;
    QWidget *pageScaling;
    QVBoxLayout *layoutScaling;
    QGroupBox *groupBox_17;
    QGridLayout *gridLayout4;
    QLabel *label_SlidersNote;
    QSlider *horizontalSliderSymbol;
    QLabel *label_11;
    QToolButton *tbRevertIcon;
    QToolButton *tbRevertCentralIcon;
    QSlider *horizontalSliderCentraIcon;
    QSlider *horizontalSliderIcon;
    QToolButton *tbRevertSymbol;
    QLabel *label_72;
    QLabel *label_71;
    QSlider *horizontalSliderPDF;
    QLabel *label_87;
    QToolButton *tbRevertPDF;
    QSpacerItem *verticalSpacer_6;
    QWidget *pageEditor;
    QVBoxLayout *verticalLayout_1;
    QScrollArea *scrollAreaEditor;
    QWidget *scrollAreaWidgetContents_1;
    QGridLayout *gridLayout5;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout6;
    QCheckBox *checkBoxRealTimeCheck;
    QLabel *label_33;
    QComboBox *comboboxLineNumbers;
    QCheckBox *checkBoxInlineCheckNonTeXFiles;
    QCheckBox *checkBoxScanInstalledLatexPackages;
    QCheckBox *checkBoxFolding;
    QCheckBox *checkBoxReplaceIndentTabByWhitespace;
    QLabel *labelFamily;
    QLabel *label_39;
    QLabel *labelEncoding;
    QLabel *label_30;
    QLabel *label_65;
    QComboBox *comboBoxEncoding;
    QCheckBox *checkBoxAutoDetectEncodingFromLatex;
    QCheckBox *checkBoxAutoDetectEncodingFromChars;
    QComboBox *comboBoxFont;
    QSpinBox *spinBoxSize;
    QSpinBox *spinBoxLineSpacingPercent;
    QLabel *labelSize;
    QLabel *label_2;
    QComboBox *comboBoxReplaceQuotes;
    QCheckBox *checkBoxShowOnlyMonospacedFonts;
    QComboBox *comboBoxAutoIndent;
    QGroupBox *groupBoxInlineChecking;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxInlineSpellCheck;
    QCheckBox *checkBoxInlineGrammarCheck;
    QCheckBox *checkBoxInlineCitationCheck;
    QCheckBox *checkBoxInlineReferenceCheck;
    QCheckBox *checkBoxInlineSyntaxCheck;
    QCheckBox *checkBoxInlinePackageCheck;
    QCheckBox *checkBoxReplaceTextTabByWhitespace;
    QCheckBox *checkBoxHideGrammarErrorsInNonText;
    QCheckBox *checkBoxHideSpellingErrorsInNonText;
    QCheckBox *checkboxRemoveTrailingWsOnSave;
    QCheckBox *checkBoxAutoLoad;
    QCheckBox *checkBoxUseCache;
    QWidget *pageAdvEditor;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollAreaAdvancedEditor;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBoxShowIndentGuides;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *checkBoxState;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_22;
    QSpinBox *sbTabSpace;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBoxShowWhitespace;
    QCheckBox *checkBoxLineState;
    QCheckBox *checkBoxBoldCursor;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBoxCloseSearchReplaceTogether;
    QCheckBox *checkBoxUseLineForSearch;
    QCheckBox *checkBoxSearchOnlyInSelection;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout7;
    QCheckBox *checkBoxShowLogMarkersWhenClickingLogEntry;
    QCheckBox *checkBoxMonitorFilesForExternalChanges;
    QCheckBox *checkBoxAutoCompleteParens;
    QCheckBox *checkOverwriteOpeningBracketFollowedByPlaceholder;
    QLabel *label_70;
    QLabel *label_82;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *checkBoxSilentReload;
    QCheckBox *checkBoxCenterDocumentInEditor;
    QLabel *label_41;
    QComboBox *comboBoxLogFileEncoding;
    QCheckBox *checkBoxInsertSymbolAsUCS;
    QCheckBox *checkBoxAllowDragAndDrop;
    QComboBox *comboBoxContextMenuSpellcheckingEntryLocation;
    QCheckBox *checkBoxImageToolTip;
    QComboBox *comboBoxLineWrap;
    QCheckBox *checkBoxDoubleClickSelectionIncludeLeadingBackslash;
    QCheckBox *checkBoxTexDocInternal;
    QComboBox *comboBoxAutoSave;
    QSpinBox *spinBoxWrapLineWidth;
    QCheckBox *checkBoxGoToErrorWhenDisplayingLog;
    QCheckBox *checkBoxUseQSaveWrite;
    QComboBox *comboBoxTripleClickSelection;
    QCheckBox *checkBoxVerticalOverScroll;
    QLabel *label_80;
    QCheckBox *checkBoxSmoothScrolling;
    QCheckBox *checkBoxToolTipHelp2;
    QLabel *label_24;
    QLabel *label_85;
    QCheckBox *checkBoxMouseWheelZoom;
    QLineEdit *lineEditCiteCommand;
    QCheckBox *checkOverwriteClosingBracketFollowingPlaceholder;
    QCheckBox *checkBoxToolTipPreview;
    QLabel *label_23;
    QCheckBox *checkBoxEnableRainbowDelimiters;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout_2;
    QComboBox *comboBoxTOCBackgroundColor;
    QCheckBox *checkBoxMarkStructureElementsBeyondEnd;
    QLabel *label_64;
    QLineEdit *leReferenceCommandsInContextMenu;
    QLineEdit *leRegExpTODO;
    QLabel *label_83;
    QCheckBox *checkBoxIndentIncludesInStructureTree;
    QCheckBox *checkBoxScrollToCurrentPosition;
    QCheckBox *checkBoxMarkStructureElementsInAppendix;
    QLabel *label_90;
    QGroupBox *groupBoxBibliography;
    QGridLayout *gridLayout_7;
    QLabel *label_73;
    QCheckBox *checkBoxParseBibTeX;
    QComboBox *comboBoxBibFileEncoding;
    QGroupBox *gbTableAutoformat;
    QGridLayout *gridLayoutTableAutoFormat;
    QCheckBox *cbTableFormatingOneLinePerCell;
    QComboBox *cbTableFormatingSpecialCommandPos;
    QLabel *label_61;
    QLineEdit *leTableFormatingSpecialCommands;
    QLabel *label_60;
    QGroupBox *gbAdditionalSearchPaths;
    QGridLayout *gridLayout71;
    QLabel *label_62;
    QLineEdit *lineEditPathBib;
    QLineEdit *lineEditPathImages;
    QLabel *label_63;
    QPushButton *pushButtonPathBib;
    QPushButton *pushButtonPathImages;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_8a;
    QCheckBox *checkBoxAutoLRM;
    QCheckBox *checkBoxVisualColumnMode;
    QLabel *labelSwitchKeyboardLayout;
    QCheckBox *checkBoxSwitchLanguagesDirection;
    QCheckBox *checkBoxSwitchLanguagesMath;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *checkBoxHackDisableAccentWorkaround;
    QCheckBox *checkBoxHackAutoRendering;
    QGridLayout *gridLayout_3;
    QComboBox *comboBoxHackRenderMode;
    QLabel *labelRenderMode;
    QCheckBox *checkBoxHackDisableFixedPitch;
    QCheckBox *checkBoxHackDisableWidthCache;
    QCheckBox *checkBoxHackDisableLineCache;
    QSpacerItem *verticalSpacer;
    QWidget *pageSyntaxHighlighting;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *formatConfigBox;
    QWidget *pageCompletion;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout8;
    QCheckBox *checkBoxAutoReplaceCommands;
    QCheckBox *checkBoxUsePlaceholders;
    QCheckBox *checkBoxToolTipCompletePreview;
    QCheckBox *checkBoxShowPlaceholders;
    QCheckBox *checkBoxToolTipHelp;
    QCheckBox *checkBoxCompletion;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_40;
    QSpinBox *spinBoxTabRelFontSize;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBoxEOWCompletes;
    QCheckBox *checkBoxCompletePrefix;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBoxPreferedTab;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBoxAutoInsertMathDelimiters;
    QCheckBox *checkBoxCompleteUserConstructs;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_12;
    QLineEdit *leCompletionFilter;
    QHBoxLayout *horizontalLayout_8;
    QListWidget *completeListWidget;
    QSpacerItem *verticalSpacer_9;
    QWidget *pageGrammar;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollAreaGrammar;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_Dictionaries;
    QGridLayout *_4;
    QLabel *label_43;
    QPushButton *pushButtonDictDir;
    QComboBox *comboBoxSpellcheckLang;
    QLabel *label_42;
    QLineEdit *leDictDir;
    QComboBox *comboBoxThesaurusFileName;
    QLabel *label_13;
    QPushButton *btSelectThesaurusFileName;
    QLabel *labelGetDic;
    QPushButton *pushButtonImportDictionary;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_8;
    QCheckBox *checkBoxGrammarRepetitionCheck;
    QLabel *label_47;
    QSpinBox *spinBoxGrammarRepetitionDistance;
    QSpinBox *spinBoxGrammarLongRangeRepetition;
    QSpinBox *spinBoxGrammarLongRangeRepetitionMinLength;
    QLabel *label_54;
    QLabel *label_55;
    QLabel *label_48;
    QCheckBox *checkBoxGrammarBadWordCheck;
    QLineEdit *lineEditGrammarWordlists;
    QPushButton *pushButtonGrammarWordlists;
    QGroupBox *groupBox_AIChat;
    QGridLayout *gl_AIChat;
    QComboBox *cbAIPreferredModel;
    QLabel *label_AIProvider;
    QPushButton *pbRetrieveModels;
    QLabel *label_AIAPI;
    QComboBox *cbAIProvider;
    QCheckBox *cbAIRecordConversation;
    QLabel *label_AIModel;
    QLineEdit *leAIAPIKey;
    QLineEdit *leAIAPIURL;
    QLabel *label_91;
    QPushButton *pbResetAIURL;
    QCheckBox *cbAIUseTools;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_9;
    QLineEdit *lineEditGrammarLTPath;
    QLabel *label_45;
    QCheckBox *checkBoxGrammarLTAutorun;
    QLabel *label_44;
    QLineEdit *lineEditGrammarLTIgnoredRules;
    QPushButton *pushButtonGrammarLTPath;
    QLabel *label_46;
    QLineEdit *lineEditGrammarSpecialRules1;
    QLineEdit *lineEditGrammarSpecialRules2;
    QLineEdit *lineEditGrammarSpecialRules4;
    QLabel *label_52;
    QLabel *label_50;
    QLineEdit *lineEditGrammarSpecialRules3;
    QLabel *label_51;
    QLabel *label_78;
    QLabel *label_53;
    QLabel *label_79;
    QLineEdit *lineEditGrammarLTJava;
    QLabel *label_49;
    QLabel *label_81;
    QPushButton *pushButtonGrammarLTJava;
    QPushButton *pushButtonResetLTURL;
    QLineEdit *lineEditGrammarLTUrl;
    QLabel *label_LTURLParams;
    QLineEdit *lineEditGrammarLTURLParams;
    QLineEdit *lineEditGrammarLTArguments;
    QPushButton *pushButtonResetLTArgs;
    QSpacerItem *verticalSpacer_4;
    QWidget *pagePreview;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollAreaPreview;
    QWidget *scrollAreaPreviewLayout;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QLabel *label_31;
    QComboBox *comboBoxDvi2PngMode;
    QLabel *label_32;
    QComboBox *comboBoxPreviewMode;
    QLabel *label_75;
    QSpinBox *spinBoxSegmentPreviewScalePercent;
    QLabel *label_35;
    QComboBox *comboBoxAutoPreview;
    QLabel *label_36;
    QSpinBox *spinBoxAutoPreviewDelay;
    QCheckBox *checkBoxReplaceBeamer;
    QCheckBox *checkBoxPrecompilePreamble;
    QSpacerItem *verticalSpacer_2;
    QWidget *pagePDFviewer;
    QVBoxLayout *verticalLayout_15;
    QScrollArea *scrollAreaPDFviewer;
    QWidget *scrollAreaPDFviewerLayout;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_4;
    QSpinBox *spinBoxPreviewScale;
    QLabel *label_29;
    QLabel *label_69;
    QCheckBox *autoRecompileFullDocument;
    QLabel *label_18;
    QSpinBox *spinBoxPreviewMagnifierSize;
    QSpinBox *spinBoxHighlightDuration;
    QSpinBox *spinBoxPreviewDPI;
    QComboBox *comboBoxPDFLoadStrategy;
    QLabel *label_66;
    QLineEdit *lineEditHighlightColor;
    QComboBox *comboBoxPreviewMagnifierShape;
    QLineEdit *lineEditPreviewSyncFileMask;
    QLabel *label_67;
    QLineEdit *lineEditPaperColor;
    QLabel *labelScreenResolution;
    QHBoxLayout *HBoxLayout_magnifier;
    QCheckBox *checkBoxPreviewMagnifierBorder;
    QCheckBox *checkBoxPreviewMagnifierShadow;
    QSpacerItem *spacerItem2;
    QComboBox *comboBoxPreviewScale;
    QSpinBox *spinBoxCacheSizeMB;
    QLabel *label_34;
    QLabel *label_84;
    QLabel *label_76;
    QLabel *label_88;
    QLabel *label_77;
    QCheckBox *checkBoxDisableHorizontalScrollingForFitToTextWidth;
    QLabel *label_28;
    QLabel *label_26;
    QComboBox *comboBoxPDFRenderBackend;
    QLabel *label_25;
    QCheckBox *autoHideToolbars;
    QLabel *label_89;
    QSpinBox *spinBoxPreviewLaserPointerSize;
    QLineEdit *lineEditLaserPointerColor;
    QSpacerItem *verticalSpacer_7;
    QWidget *pageSVN;
    QVBoxLayout *verticalLayout_18;
    QScrollArea *scrollAreaSVN;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout9;
    QGroupBox *groupBox_18;
    QVBoxLayout *vboxLayout7;
    QComboBox *comboBoxUseVCS;
    QComboBox *comboBoxAutoCheckinLevel;
    QCheckBox *cbSVNUndo;
    QCheckBox *cbKeywordSubstitution;
    QHBoxLayout *hboxLayout1;
    QLabel *label_21;
    QSpinBox *sbDirSearchDepth;
    QSpacerItem *spacerItem3;
    QWidget *pageInternalTerminal;
    QGridLayout *gridLayout10;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout11;
    QLabel *label_86;
    QComboBox *comboBoxTerminalColorScheme;
    QLabel *labelFamily_2;
    QComboBox *comboBoxTerminalFont;
    QLabel *labelSize_2;
    QSpinBox *spinBoxTerminalFontSize;
    QLabel *labelShell;
    QLineEdit *lineEditTerminalShell;
    QSpacerItem *verticalSpacer_8;
    QWidget *pageCollaborativeEdit;
    QGridLayout *gridLayout12;
    QGroupBox *groupBox_collab;
    QGridLayout *gridLayout13;
    QLabel *label_collabTool;
    QLabel *labelFamily_collabPath;
    QLabel *label_collabFolder;
    QComboBox *comboBoxCollaborativeTool;
    QLineEdit *lineEditCollaborativeClientFolder;
    QPushButton *pbSelectCollaborativeToolPath;
    QPushButton *pbSelectClientFolder;
    QLineEdit *lineEditCollaborativeToolPath;
    QLineEdit *lineEditCollaborativeUserName;
    QLabel *label_93;
    QSpacerItem *verticalSpacer_collab;
    QGridLayout *gridLayout14;
    QHBoxLayout *hboxLayout2;
    QCheckBox *checkBoxShowAdvancedOptions;
    QSpacerItem *spacerItem4;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QString::fromUtf8("ConfigDialog"));
        ConfigDialog->resize(1378, 864);
        verticalLayout_19 = new QVBoxLayout(ConfigDialog);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(9, 9, 9, 9);
        mainSplitter = new QSplitter(ConfigDialog);
        mainSplitter->setObjectName(QString::fromUtf8("mainSplitter"));
        mainSplitter->setOrientation(Qt::Orientation::Horizontal);
        mainSplitter->setHandleWidth(9);
        mainSplitter->setChildrenCollapsible(false);
        leftPart = new QWidget(mainSplitter);
        leftPart->setObjectName(QString::fromUtf8("leftPart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftPart->sizePolicy().hasHeightForWidth());
        leftPart->setSizePolicy(sizePolicy);
        vboxLayout = new QVBoxLayout(leftPart);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        contentsWidget = new QListWidget(leftPart);
        contentsWidget->setObjectName(QString::fromUtf8("contentsWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(contentsWidget->sizePolicy().hasHeightForWidth());
        contentsWidget->setSizePolicy(sizePolicy1);
        contentsWidget->setMinimumSize(QSize(40, 300));
        contentsWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        vboxLayout->addWidget(contentsWidget);

        lineEditMetaFilter = new QLineEdit(leftPart);
        lineEditMetaFilter->setObjectName(QString::fromUtf8("lineEditMetaFilter"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditMetaFilter->sizePolicy().hasHeightForWidth());
        lineEditMetaFilter->setSizePolicy(sizePolicy2);

        vboxLayout->addWidget(lineEditMetaFilter);

        mainSplitter->addWidget(leftPart);
        rightPart = new QWidget(mainSplitter);
        rightPart->setObjectName(QString::fromUtf8("rightPart"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(4);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rightPart->sizePolicy().hasHeightForWidth());
        rightPart->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(rightPart);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pagesWidget = new QStackedWidget(rightPart);
        pagesWidget->setObjectName(QString::fromUtf8("pagesWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pagesWidget->sizePolicy().hasHeightForWidth());
        pagesWidget->setSizePolicy(sizePolicy4);
        pagesWidget->setMinimumSize(QSize(400, 300));
        pageGeneral = new QWidget();
        pageGeneral->setObjectName(QString::fromUtf8("pageGeneral"));
        vboxLayout1 = new QVBoxLayout(pageGeneral);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        scrollAreaGeneral = new QScrollArea(pageGeneral);
        scrollAreaGeneral->setObjectName(QString::fromUtf8("scrollAreaGeneral"));
        scrollAreaGeneral->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaGeneral->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 823, 725));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_Appearance = new QGroupBox(scrollAreaWidgetContents);
        groupBox_Appearance->setObjectName(QString::fromUtf8("groupBox_Appearance"));
        gridLayout1 = new QGridLayout(groupBox_Appearance);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        comboBoxInterfaceStyle = new QComboBox(groupBox_Appearance);
        comboBoxInterfaceStyle->setObjectName(QString::fromUtf8("comboBoxInterfaceStyle"));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(comboBoxInterfaceStyle->sizePolicy().hasHeightForWidth());
        comboBoxInterfaceStyle->setSizePolicy(sizePolicy5);

        gridLayout1->addWidget(comboBoxInterfaceStyle, 0, 1, 1, 3);

        label_14 = new QLabel(groupBox_Appearance);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout1->addWidget(label_14, 1, 0, 1, 1);

        comboBoxInterfaceFont = new QFontComboBox(groupBox_Appearance);
        comboBoxInterfaceFont->setObjectName(QString::fromUtf8("comboBoxInterfaceFont"));
        sizePolicy4.setHeightForWidth(comboBoxInterfaceFont->sizePolicy().hasHeightForWidth());
        comboBoxInterfaceFont->setSizePolicy(sizePolicy4);

        gridLayout1->addWidget(comboBoxInterfaceFont, 5, 1, 1, 3);

        comboBoxLanguage = new QComboBox(groupBox_Appearance);
        comboBoxLanguage->setObjectName(QString::fromUtf8("comboBoxLanguage"));
        sizePolicy4.setHeightForWidth(comboBoxLanguage->sizePolicy().hasHeightForWidth());
        comboBoxLanguage->setSizePolicy(sizePolicy4);

        gridLayout1->addWidget(comboBoxLanguage, 10, 1, 1, 3);

        label_3 = new QLabel(groupBox_Appearance);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy6);

        gridLayout1->addWidget(label_3, 0, 0, 1, 1);

        spinBoxInterfaceFontSize = new QSpinBox(groupBox_Appearance);
        spinBoxInterfaceFontSize->setObjectName(QString::fromUtf8("spinBoxInterfaceFontSize"));
        sizePolicy4.setHeightForWidth(spinBoxInterfaceFontSize->sizePolicy().hasHeightForWidth());
        spinBoxInterfaceFontSize->setSizePolicy(sizePolicy4);

        gridLayout1->addWidget(spinBoxInterfaceFontSize, 6, 1, 1, 3);

        label_9 = new QLabel(groupBox_Appearance);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy6.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy6);

        gridLayout1->addWidget(label_9, 10, 0, 1, 1);

        label_5 = new QLabel(groupBox_Appearance);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy6.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy6);

        gridLayout1->addWidget(label_5, 5, 0, 1, 1);

        comboBoxInterfaceModernStyle = new QComboBox(groupBox_Appearance);
        comboBoxInterfaceModernStyle->addItem(QString());
        comboBoxInterfaceModernStyle->addItem(QString());
        comboBoxInterfaceModernStyle->addItem(QString());
        comboBoxInterfaceModernStyle->setObjectName(QString::fromUtf8("comboBoxInterfaceModernStyle"));

        gridLayout1->addWidget(comboBoxInterfaceModernStyle, 1, 1, 1, 3);

        label_7 = new QLabel(groupBox_Appearance);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy6.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy6);

        gridLayout1->addWidget(label_7, 6, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(9);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        checkBoxUseTexmakerPalette = new QCheckBox(groupBox_Appearance);
        checkBoxUseTexmakerPalette->setObjectName(QString::fromUtf8("checkBoxUseTexmakerPalette"));
        checkBoxUseTexmakerPalette->setProperty("advancedOption", QVariant(true));

        hboxLayout->addWidget(checkBoxUseTexmakerPalette);

        checkBoxUseSystemTheme = new QCheckBox(groupBox_Appearance);
        checkBoxUseSystemTheme->setObjectName(QString::fromUtf8("checkBoxUseSystemTheme"));
        checkBoxUseSystemTheme->setProperty("advancedOption", QVariant(true));

        hboxLayout->addWidget(checkBoxUseSystemTheme);

        spacerItem = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        gridLayout1->addLayout(hboxLayout, 4, 1, 1, 3);

        label_27 = new QLabel(groupBox_Appearance);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout1->addWidget(label_27, 2, 0, 1, 1);

        comboBoxInterfaceIconTheme = new QComboBox(groupBox_Appearance);
        comboBoxInterfaceIconTheme->addItem(QString());
        comboBoxInterfaceIconTheme->addItem(QString());
        comboBoxInterfaceIconTheme->addItem(QString());
        comboBoxInterfaceIconTheme->setObjectName(QString::fromUtf8("comboBoxInterfaceIconTheme"));

        gridLayout1->addWidget(comboBoxInterfaceIconTheme, 2, 1, 1, 3);

        gridLayout1->setColumnStretch(2, 1);

        verticalLayout->addWidget(groupBox_Appearance);

        groupBox_Files = new QGroupBox(scrollAreaWidgetContents);
        groupBox_Files->setObjectName(QString::fromUtf8("groupBox_Files"));
        groupBox_Files->setProperty("advancedOption", QVariant(true));
        gridLayout2 = new QGridLayout(groupBox_Files);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        label_10 = new QLabel(groupBox_Files);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy6.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy6);

        gridLayout2->addWidget(label_10, 2, 0, 1, 1);

        checkBoxRememberFileFilter = new QCheckBox(groupBox_Files);
        checkBoxRememberFileFilter->setObjectName(QString::fromUtf8("checkBoxRememberFileFilter"));
        checkBoxRememberFileFilter->setProperty("advancedOption", QVariant(true));

        gridLayout2->addWidget(checkBoxRememberFileFilter, 4, 1, 1, 1);

        spinBoxMaxRecentProjects = new QSpinBox(groupBox_Files);
        spinBoxMaxRecentProjects->setObjectName(QString::fromUtf8("spinBoxMaxRecentProjects"));
        sizePolicy4.setHeightForWidth(spinBoxMaxRecentProjects->sizePolicy().hasHeightForWidth());
        spinBoxMaxRecentProjects->setSizePolicy(sizePolicy4);
        spinBoxMaxRecentProjects->setMaximum(10000);

        gridLayout2->addWidget(spinBoxMaxRecentProjects, 2, 1, 1, 2);

        label_8 = new QLabel(groupBox_Files);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy6.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy6);

        gridLayout2->addWidget(label_8, 1, 0, 1, 1);

        spinBoxMaxRecentFiles = new QSpinBox(groupBox_Files);
        spinBoxMaxRecentFiles->setObjectName(QString::fromUtf8("spinBoxMaxRecentFiles"));
        sizePolicy4.setHeightForWidth(spinBoxMaxRecentFiles->sizePolicy().hasHeightForWidth());
        spinBoxMaxRecentFiles->setSizePolicy(sizePolicy4);
        spinBoxMaxRecentFiles->setMaximum(10000);

        gridLayout2->addWidget(spinBoxMaxRecentFiles, 1, 1, 1, 2);

        checkBoxUseNativeFileDialog = new QCheckBox(groupBox_Files);
        checkBoxUseNativeFileDialog->setObjectName(QString::fromUtf8("checkBoxUseNativeFileDialog"));

        gridLayout2->addWidget(checkBoxUseNativeFileDialog, 6, 1, 1, 1);

        checkBoxParseRootDoc = new QCheckBox(groupBox_Files);
        checkBoxParseRootDoc->setObjectName(QString::fromUtf8("checkBoxParseRootDoc"));
        checkBoxParseRootDoc->setProperty("advancedOption", QVariant(true));

        gridLayout2->addWidget(checkBoxParseRootDoc, 4, 2, 1, 1);

        checkBoxMRUDocumentChooser = new QCheckBox(groupBox_Files);
        checkBoxMRUDocumentChooser->setObjectName(QString::fromUtf8("checkBoxMRUDocumentChooser"));
        checkBoxMRUDocumentChooser->setProperty("advancedOption", QVariant(true));

        gridLayout2->addWidget(checkBoxMRUDocumentChooser, 6, 2, 1, 1);

        gridLayout2->setColumnStretch(2, 1);

        verticalLayout->addWidget(groupBox_Files);

        groupBox_Session = new QGroupBox(scrollAreaWidgetContents);
        groupBox_Session->setObjectName(QString::fromUtf8("groupBox_Session"));
        groupBox_Session->setProperty("advancedOption", QVariant(true));
        verticalLayout_10 = new QVBoxLayout(groupBox_Session);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        checkBoxRestoreSession = new QCheckBox(groupBox_Session);
        checkBoxRestoreSession->setObjectName(QString::fromUtf8("checkBoxRestoreSession"));

        verticalLayout_10->addWidget(checkBoxRestoreSession);

        checkBoxSessionStoreRelativePaths = new QCheckBox(groupBox_Session);
        checkBoxSessionStoreRelativePaths->setObjectName(QString::fromUtf8("checkBoxSessionStoreRelativePaths"));
        checkBoxSessionStoreRelativePaths->setProperty("advancedOption", QVariant(true));

        verticalLayout_10->addWidget(checkBoxSessionStoreRelativePaths);


        verticalLayout->addWidget(groupBox_Session);

        groupBox_Startup = new QGroupBox(scrollAreaWidgetContents);
        groupBox_Startup->setObjectName(QString::fromUtf8("groupBox_Startup"));
        verticalLayout_14 = new QVBoxLayout(groupBox_Startup);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        checkBoxCheckLatexConfiguration = new QCheckBox(groupBox_Startup);
        checkBoxCheckLatexConfiguration->setObjectName(QString::fromUtf8("checkBoxCheckLatexConfiguration"));

        verticalLayout_14->addWidget(checkBoxCheckLatexConfiguration);


        verticalLayout->addWidget(groupBox_Startup);

        groupBox_Update = new QGroupBox(scrollAreaWidgetContents);
        groupBox_Update->setObjectName(QString::fromUtf8("groupBox_Update"));
        gridLayout03 = new QGridLayout(groupBox_Update);
        gridLayout03->setObjectName(QString::fromUtf8("gridLayout03"));
        comboBoxUpdateLevel = new QComboBox(groupBox_Update);
        comboBoxUpdateLevel->addItem(QString());
        comboBoxUpdateLevel->addItem(QString());
        comboBoxUpdateLevel->addItem(QString());
        comboBoxUpdateLevel->setObjectName(QString::fromUtf8("comboBoxUpdateLevel"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(comboBoxUpdateLevel->sizePolicy().hasHeightForWidth());
        comboBoxUpdateLevel->setSizePolicy(sizePolicy7);

        gridLayout03->addWidget(comboBoxUpdateLevel, 0, 6, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout03->addItem(horizontalSpacer_7, 1, 4, 1, 1);

        pushButtonUpdateCheckNow = new QPushButton(groupBox_Update);
        pushButtonUpdateCheckNow->setObjectName(QString::fromUtf8("pushButtonUpdateCheckNow"));

        gridLayout03->addWidget(pushButtonUpdateCheckNow, 1, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout03->addItem(horizontalSpacer_4, 0, 3, 1, 2);

        labelUpdateCheckDate = new QLabel(groupBox_Update);
        labelUpdateCheckDate->setObjectName(QString::fromUtf8("labelUpdateCheckDate"));
        labelUpdateCheckDate->setText(QString::fromUtf8("<checkDate>"));

        gridLayout03->addWidget(labelUpdateCheckDate, 1, 1, 1, 1);

        label_56 = new QLabel(groupBox_Update);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout03->addWidget(label_56, 1, 0, 1, 1);

        spinBoxAutoUpdateCheckIntervalDays = new QSpinBox(groupBox_Update);
        spinBoxAutoUpdateCheckIntervalDays->setObjectName(QString::fromUtf8("spinBoxAutoUpdateCheckIntervalDays"));
        spinBoxAutoUpdateCheckIntervalDays->setMinimum(0);
        spinBoxAutoUpdateCheckIntervalDays->setValue(7);

        gridLayout03->addWidget(spinBoxAutoUpdateCheckIntervalDays, 0, 1, 1, 1);

        checkBoxAutoUpdateCheck = new QCheckBox(groupBox_Update);
        checkBoxAutoUpdateCheck->setObjectName(QString::fromUtf8("checkBoxAutoUpdateCheck"));

        gridLayout03->addWidget(checkBoxAutoUpdateCheck, 0, 0, 1, 1);

        label_74 = new QLabel(groupBox_Update);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        gridLayout03->addWidget(label_74, 0, 5, 1, 1);


        verticalLayout->addWidget(groupBox_Update);

        spacerItem1 = new QSpacerItem(20, 0, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout->addItem(spacerItem1);

        scrollAreaGeneral->setWidget(scrollAreaWidgetContents);

        vboxLayout1->addWidget(scrollAreaGeneral);

        pagesWidget->addWidget(pageGeneral);
        pageCommands = new QWidget();
        pageCommands->setObjectName(QString::fromUtf8("pageCommands"));
        vboxLayout2 = new QVBoxLayout(pageCommands);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        groupBoxCommands = new QGroupBox(pageCommands);
        groupBoxCommands->setObjectName(QString::fromUtf8("groupBoxCommands"));
        sizePolicy4.setHeightForWidth(groupBoxCommands->sizePolicy().hasHeightForWidth());
        groupBoxCommands->setSizePolicy(sizePolicy4);

        vboxLayout2->addWidget(groupBoxCommands);

        label_15 = new QLabel(pageCommands);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        vboxLayout2->addWidget(label_15);

        label_4 = new QLabel(pageCommands);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setIndent(15);

        vboxLayout2->addWidget(label_4);

        label_17 = new QLabel(pageCommands);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setWordWrap(true);
        label_17->setIndent(30);
        label_17->setProperty("advancedOption", QVariant(true));

        vboxLayout2->addWidget(label_17);

        label_16 = new QLabel(pageCommands);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMargin(0);
        label_16->setIndent(15);

        vboxLayout2->addWidget(label_16);

        pagesWidget->addWidget(pageCommands);
        pageBuild = new QWidget();
        pageBuild->setObjectName(QString::fromUtf8("pageBuild"));
        vboxLayout3 = new QVBoxLayout(pageBuild);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout3->setContentsMargins(0, 0, 0, 0);
        scrollAreaBuild = new QScrollArea(pageBuild);
        scrollAreaBuild->setObjectName(QString::fromUtf8("scrollAreaBuild"));
        scrollAreaBuild->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaBuild->setWidgetResizable(true);
        scrollAreaBuildContents = new QWidget();
        scrollAreaBuildContents->setObjectName(QString::fromUtf8("scrollAreaBuildContents"));
        scrollAreaBuildContents->setGeometry(QRect(0, 0, 870, 626));
        verticalLayout_17 = new QVBoxLayout(scrollAreaBuildContents);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        groupBoxMetaCommands = new QGroupBox(scrollAreaBuildContents);
        groupBoxMetaCommands->setObjectName(QString::fromUtf8("groupBoxMetaCommands"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(groupBoxMetaCommands->sizePolicy().hasHeightForWidth());
        groupBoxMetaCommands->setSizePolicy(sizePolicy8);
        groupBoxMetaCommands->setMinimumSize(QSize(0, 200));
        groupBoxMetaCommands->setBaseSize(QSize(0, 0));

        verticalLayout_17->addWidget(groupBoxMetaCommands);

        groupBoxUserCommands = new QGroupBox(scrollAreaBuildContents);
        groupBoxUserCommands->setObjectName(QString::fromUtf8("groupBoxUserCommands"));
        groupBoxUserCommands->setMinimumSize(QSize(0, 95));
        groupBoxUserCommands->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout_17->addWidget(groupBoxUserCommands);

        groupBoxBuildOptions = new QGroupBox(scrollAreaBuildContents);
        groupBoxBuildOptions->setObjectName(QString::fromUtf8("groupBoxBuildOptions"));
        groupBoxBuildOptions->setProperty("advancedOption", QVariant(true));
        formLayout = new QFormLayout(groupBoxBuildOptions);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
        checkBoxRunAfterBibTeXChange = new QCheckBox(groupBoxBuildOptions);
        checkBoxRunAfterBibTeXChange->setObjectName(QString::fromUtf8("checkBoxRunAfterBibTeXChange"));

        formLayout->setWidget(0, QFormLayout::LabelRole, checkBoxRunAfterBibTeXChange);

        checkBoxShowMessagesOnCompile = new QCheckBox(groupBoxBuildOptions);
        checkBoxShowMessagesOnCompile->setObjectName(QString::fromUtf8("checkBoxShowMessagesOnCompile"));

        formLayout->setWidget(1, QFormLayout::LabelRole, checkBoxShowMessagesOnCompile);

        checkBoxSingleInstanceViewer = new QCheckBox(groupBoxBuildOptions);
        checkBoxSingleInstanceViewer->setObjectName(QString::fromUtf8("checkBoxSingleInstanceViewer"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(checkBoxSingleInstanceViewer->sizePolicy().hasHeightForWidth());
        checkBoxSingleInstanceViewer->setSizePolicy(sizePolicy9);
        checkBoxSingleInstanceViewer->setMinimumSize(QSize(0, 0));
        checkBoxSingleInstanceViewer->setBaseSize(QSize(600, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, checkBoxSingleInstanceViewer);

        gridLayout3 = new QGridLayout();
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        label_37 = new QLabel(groupBoxBuildOptions);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout3->addWidget(label_37, 0, 0, 1, 1);

        comboBoxShowStdout = new QComboBox(groupBoxBuildOptions);
        comboBoxShowStdout->addItem(QString());
        comboBoxShowStdout->addItem(QString());
        comboBoxShowStdout->addItem(QString());
        comboBoxShowStdout->setObjectName(QString::fromUtf8("comboBoxShowStdout"));

        gridLayout3->addWidget(comboBoxShowStdout, 0, 1, 1, 1);

        label_38 = new QLabel(groupBoxBuildOptions);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout3->addWidget(label_38, 1, 0, 1, 1);

        spinBoxRerunLatex = new QSpinBox(groupBoxBuildOptions);
        spinBoxRerunLatex->setObjectName(QString::fromUtf8("spinBoxRerunLatex"));
        spinBoxRerunLatex->setValue(5);

        gridLayout3->addWidget(spinBoxRerunLatex, 1, 1, 1, 1);

        gridLayout3->setColumnStretch(1, 1);

        formLayout->setLayout(3, QFormLayout::SpanningRole, gridLayout3);

        gridLayout_1 = new QGridLayout();
        gridLayout_1->setObjectName(QString::fromUtf8("gridLayout_1"));
        gridLayout_1->setVerticalSpacing(2);
        gridLayout_1->setContentsMargins(9, 0, 0, 0);
        lineEditPathPDF = new QLineEdit(groupBoxBuildOptions);
        lineEditPathPDF->setObjectName(QString::fromUtf8("lineEditPathPDF"));

        gridLayout_1->addWidget(lineEditPathPDF, 1, 1, 1, 1);

        lineEditPathCommands = new QLineEdit(groupBoxBuildOptions);
        lineEditPathCommands->setObjectName(QString::fromUtf8("lineEditPathCommands"));

        gridLayout_1->addWidget(lineEditPathCommands, 2, 1, 1, 1);

        pushButtonPathPdf = new QPushButton(groupBoxBuildOptions);
        pushButtonPathPdf->setObjectName(QString::fromUtf8("pushButtonPathPdf"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(pushButtonPathPdf->sizePolicy().hasHeightForWidth());
        pushButtonPathPdf->setSizePolicy(sizePolicy10);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images-ng/document-open.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPathPdf->setIcon(icon);

        gridLayout_1->addWidget(pushButtonPathPdf, 1, 2, 1, 1);

        label_59 = new QLabel(groupBoxBuildOptions);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_1->addWidget(label_59, 2, 0, 1, 1);

        label_58 = new QLabel(groupBoxBuildOptions);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_1->addWidget(label_58, 1, 0, 1, 1);

        lineEditPathLog = new QLineEdit(groupBoxBuildOptions);
        lineEditPathLog->setObjectName(QString::fromUtf8("lineEditPathLog"));

        gridLayout_1->addWidget(lineEditPathLog, 0, 1, 1, 1);

        pushButtonPathLog = new QPushButton(groupBoxBuildOptions);
        pushButtonPathLog->setObjectName(QString::fromUtf8("pushButtonPathLog"));
        sizePolicy10.setHeightForWidth(pushButtonPathLog->sizePolicy().hasHeightForWidth());
        pushButtonPathLog->setSizePolicy(sizePolicy10);
        pushButtonPathLog->setIcon(icon);

        gridLayout_1->addWidget(pushButtonPathLog, 0, 2, 1, 1);

        pushButtonPathCommands = new QPushButton(groupBoxBuildOptions);
        pushButtonPathCommands->setObjectName(QString::fromUtf8("pushButtonPathCommands"));
        sizePolicy10.setHeightForWidth(pushButtonPathCommands->sizePolicy().hasHeightForWidth());
        pushButtonPathCommands->setSizePolicy(sizePolicy10);
        pushButtonPathCommands->setIcon(icon);

        gridLayout_1->addWidget(pushButtonPathCommands, 2, 2, 1, 1);

        label_57 = new QLabel(groupBoxBuildOptions);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_1->addWidget(label_57, 0, 0, 1, 1);


        formLayout->setLayout(7, QFormLayout::SpanningRole, gridLayout_1);

        label_68 = new QLabel(groupBoxBuildOptions);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        formLayout->setWidget(6, QFormLayout::SpanningRole, label_68);

        checkBoxReplaceEnvironmentVariables = new QCheckBox(groupBoxBuildOptions);
        checkBoxReplaceEnvironmentVariables->setObjectName(QString::fromUtf8("checkBoxReplaceEnvironmentVariables"));

        formLayout->setWidget(0, QFormLayout::FieldRole, checkBoxReplaceEnvironmentVariables);

        checkBoxShowLogInCaseOfCompileError = new QCheckBox(groupBoxBuildOptions);
        checkBoxShowLogInCaseOfCompileError->setObjectName(QString::fromUtf8("checkBoxShowLogInCaseOfCompileError"));

        formLayout->setWidget(1, QFormLayout::FieldRole, checkBoxShowLogInCaseOfCompileError);

        checkBoxInterpetCommandDefinitionInMagicComment = new QCheckBox(groupBoxBuildOptions);
        checkBoxInterpetCommandDefinitionInMagicComment->setObjectName(QString::fromUtf8("checkBoxInterpetCommandDefinitionInMagicComment"));

        formLayout->setWidget(2, QFormLayout::FieldRole, checkBoxInterpetCommandDefinitionInMagicComment);


        verticalLayout_17->addWidget(groupBoxBuildOptions);

        scrollAreaBuild->setWidget(scrollAreaBuildContents);

        vboxLayout3->addWidget(scrollAreaBuild);

        pagesWidget->addWidget(pageBuild);
        pageShortcuts = new QWidget();
        pageShortcuts->setObjectName(QString::fromUtf8("pageShortcuts"));
        vboxLayout4 = new QVBoxLayout(pageShortcuts);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        vboxLayout4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(pageShortcuts);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        vboxLayout4->addWidget(label_6);

        shortcutTree = new QTreeWidget(pageShortcuts);
        shortcutTree->setObjectName(QString::fromUtf8("shortcutTree"));
        shortcutTree->setAnimated(true);
        shortcutTree->setColumnCount(4);
        shortcutTree->header()->setDefaultSectionSize(150);

        vboxLayout4->addWidget(shortcutTree);

        groupBox = new QGroupBox(pageShortcuts);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBoxCloseLogByEsc = new QCheckBox(groupBox);
        checkBoxCloseLogByEsc->setObjectName(QString::fromUtf8("checkBoxCloseLogByEsc"));

        horizontalLayout_5->addWidget(checkBoxCloseLogByEsc);

        checkBoxCloseEmbeddedViewerByEsc = new QCheckBox(groupBox);
        checkBoxCloseEmbeddedViewerByEsc->setObjectName(QString::fromUtf8("checkBoxCloseEmbeddedViewerByEsc"));

        horizontalLayout_5->addWidget(checkBoxCloseEmbeddedViewerByEsc);

        checkBoxCloseFullscreenByEsc = new QCheckBox(groupBox);
        checkBoxCloseFullscreenByEsc->setObjectName(QString::fromUtf8("checkBoxCloseFullscreenByEsc"));

        horizontalLayout_5->addWidget(checkBoxCloseFullscreenByEsc);


        vboxLayout4->addWidget(groupBox);

        checkBoxShowShortcutsInTooltips = new QCheckBox(pageShortcuts);
        checkBoxShowShortcutsInTooltips->setObjectName(QString::fromUtf8("checkBoxShowShortcutsInTooltips"));

        vboxLayout4->addWidget(checkBoxShowShortcutsInTooltips);

        pagesWidget->addWidget(pageShortcuts);
        pageLatexMenus = new QWidget();
        pageLatexMenus->setObjectName(QString::fromUtf8("pageLatexMenus"));
        vboxLayout5 = new QVBoxLayout(pageLatexMenus);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        vboxLayout5->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(pageLatexMenus);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        vboxLayout5->addWidget(label_19);

        menuTree = new QTreeWidget(pageLatexMenus);
        menuTree->setObjectName(QString::fromUtf8("menuTree"));
        menuTree->setAnimated(true);
        menuTree->setColumnCount(3);
        menuTree->header()->setDefaultSectionSize(250);

        vboxLayout5->addWidget(menuTree);

        checkBoxShowAllMenus = new QCheckBox(pageLatexMenus);
        checkBoxShowAllMenus->setObjectName(QString::fromUtf8("checkBoxShowAllMenus"));

        vboxLayout5->addWidget(checkBoxShowAllMenus);

        pagesWidget->addWidget(pageLatexMenus);
        pageToolbars = new QWidget();
        pageToolbars->setObjectName(QString::fromUtf8("pageToolbars"));
        vboxLayout6 = new QVBoxLayout(pageToolbars);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        vboxLayout6->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(pageToolbars);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        vboxLayout6->addWidget(label_20);

        _2 = new QGridLayout();
        _2->setObjectName(QString::fromUtf8("_2"));
        listCustomToolBar = new QListWidget(pageToolbars);
        listCustomToolBar->setObjectName(QString::fromUtf8("listCustomToolBar"));
        listCustomToolBar->setMovement(QListView::Movement::Free);

        _2->addWidget(listCustomToolBar, 1, 1, 1, 1);

        _3 = new QVBoxLayout();
        _3->setObjectName(QString::fromUtf8("_3"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(verticalSpacer_3);

        pbToToolbar = new QPushButton(pageToolbars);
        pbToToolbar->setObjectName(QString::fromUtf8("pbToToolbar"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images-ng/left.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pbToToolbar->setIcon(icon1);

        _3->addWidget(pbToToolbar);

        pbFromToolbar = new QPushButton(pageToolbars);
        pbFromToolbar->setObjectName(QString::fromUtf8("pbFromToolbar"));
        pbFromToolbar->setText(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images-ng/right.svgz"), QSize(), QIcon::Normal, QIcon::Off);
        pbFromToolbar->setIcon(icon2);

        _3->addWidget(pbFromToolbar);

        spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(spacer);


        _2->addLayout(_3, 1, 2, 1, 1);

        comboBoxToolbars = new QComboBox(pageToolbars);
        comboBoxToolbars->setObjectName(QString::fromUtf8("comboBoxToolbars"));

        _2->addWidget(comboBoxToolbars, 0, 1, 1, 1);

        comboBoxActions = new QComboBox(pageToolbars);
        comboBoxActions->setObjectName(QString::fromUtf8("comboBoxActions"));

        _2->addWidget(comboBoxActions, 0, 3, 1, 1);

        treePossibleToolbarActions = new QTreeWidget(pageToolbars);
        treePossibleToolbarActions->setObjectName(QString::fromUtf8("treePossibleToolbarActions"));
        treePossibleToolbarActions->setRootIsDecorated(false);
        treePossibleToolbarActions->setAnimated(true);
        treePossibleToolbarActions->setAllColumnsShowFocus(true);

        _2->addWidget(treePossibleToolbarActions, 1, 3, 1, 1);


        vboxLayout6->addLayout(_2);

        pagesWidget->addWidget(pageToolbars);
        pageScaling = new QWidget();
        pageScaling->setObjectName(QString::fromUtf8("pageScaling"));
        layoutScaling = new QVBoxLayout(pageScaling);
        layoutScaling->setObjectName(QString::fromUtf8("layoutScaling"));
        layoutScaling->setContentsMargins(0, 0, 0, 0);
        groupBox_17 = new QGroupBox(pageScaling);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        gridLayout4 = new QGridLayout(groupBox_17);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        gridLayout4->setHorizontalSpacing(15);
        label_SlidersNote = new QLabel(groupBox_17);
        label_SlidersNote->setObjectName(QString::fromUtf8("label_SlidersNote"));

        gridLayout4->addWidget(label_SlidersNote, 0, 0, 1, 3);

        horizontalSliderSymbol = new QSlider(groupBox_17);
        horizontalSliderSymbol->setObjectName(QString::fromUtf8("horizontalSliderSymbol"));
        horizontalSliderSymbol->setMinimum(16);
        horizontalSliderSymbol->setMaximum(128);
        horizontalSliderSymbol->setTracking(true);
        horizontalSliderSymbol->setOrientation(Qt::Orientation::Horizontal);
        horizontalSliderSymbol->setInvertedAppearance(false);
        horizontalSliderSymbol->setInvertedControls(false);
        horizontalSliderSymbol->setTickPosition(QSlider::TickPosition::TicksBelow);
        horizontalSliderSymbol->setTickInterval(8);

        gridLayout4->addWidget(horizontalSliderSymbol, 5, 1, 1, 2);

        label_11 = new QLabel(groupBox_17);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout4->addWidget(label_11, 1, 0, 1, 1);

        tbRevertIcon = new QToolButton(groupBox_17);
        tbRevertIcon->setObjectName(QString::fromUtf8("tbRevertIcon"));

        gridLayout4->addWidget(tbRevertIcon, 1, 3, 1, 1);

        tbRevertCentralIcon = new QToolButton(groupBox_17);
        tbRevertCentralIcon->setObjectName(QString::fromUtf8("tbRevertCentralIcon"));

        gridLayout4->addWidget(tbRevertCentralIcon, 2, 3, 1, 1);

        horizontalSliderCentraIcon = new QSlider(groupBox_17);
        horizontalSliderCentraIcon->setObjectName(QString::fromUtf8("horizontalSliderCentraIcon"));
        horizontalSliderCentraIcon->setMinimum(8);
        horizontalSliderCentraIcon->setMaximum(64);
        horizontalSliderCentraIcon->setOrientation(Qt::Orientation::Horizontal);
        horizontalSliderCentraIcon->setTickPosition(QSlider::TickPosition::TicksBelow);
        horizontalSliderCentraIcon->setTickInterval(8);

        gridLayout4->addWidget(horizontalSliderCentraIcon, 2, 1, 1, 2);

        horizontalSliderIcon = new QSlider(groupBox_17);
        horizontalSliderIcon->setObjectName(QString::fromUtf8("horizontalSliderIcon"));
        horizontalSliderIcon->setMinimum(16);
        horizontalSliderIcon->setMaximum(128);
        horizontalSliderIcon->setValue(24);
        horizontalSliderIcon->setSliderPosition(24);
        horizontalSliderIcon->setOrientation(Qt::Orientation::Horizontal);
        horizontalSliderIcon->setTickPosition(QSlider::TickPosition::TicksBelow);
        horizontalSliderIcon->setTickInterval(8);

        gridLayout4->addWidget(horizontalSliderIcon, 1, 1, 1, 2);

        tbRevertSymbol = new QToolButton(groupBox_17);
        tbRevertSymbol->setObjectName(QString::fromUtf8("tbRevertSymbol"));

        gridLayout4->addWidget(tbRevertSymbol, 5, 3, 1, 1);

        label_72 = new QLabel(groupBox_17);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        gridLayout4->addWidget(label_72, 5, 0, 1, 1);

        label_71 = new QLabel(groupBox_17);
        label_71->setObjectName(QString::fromUtf8("label_71"));

        gridLayout4->addWidget(label_71, 2, 0, 1, 1);

        horizontalSliderPDF = new QSlider(groupBox_17);
        horizontalSliderPDF->setObjectName(QString::fromUtf8("horizontalSliderPDF"));
        horizontalSliderPDF->setMinimum(8);
        horizontalSliderPDF->setMaximum(128);
        horizontalSliderPDF->setTracking(true);
        horizontalSliderPDF->setOrientation(Qt::Orientation::Horizontal);
        horizontalSliderPDF->setTickPosition(QSlider::TickPosition::TicksBelow);
        horizontalSliderPDF->setTickInterval(8);

        gridLayout4->addWidget(horizontalSliderPDF, 6, 1, 1, 2);

        label_87 = new QLabel(groupBox_17);
        label_87->setObjectName(QString::fromUtf8("label_87"));

        gridLayout4->addWidget(label_87, 6, 0, 1, 1);

        tbRevertPDF = new QToolButton(groupBox_17);
        tbRevertPDF->setObjectName(QString::fromUtf8("tbRevertPDF"));

        gridLayout4->addWidget(tbRevertPDF, 6, 3, 1, 1);

        gridLayout4->setColumnStretch(1, 1);
        gridLayout4->setColumnStretch(2, 1);

        layoutScaling->addWidget(groupBox_17);

        verticalSpacer_6 = new QSpacerItem(20, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Minimum);

        layoutScaling->addItem(verticalSpacer_6);

        pagesWidget->addWidget(pageScaling);
        pageEditor = new QWidget();
        pageEditor->setObjectName(QString::fromUtf8("pageEditor"));
        verticalLayout_1 = new QVBoxLayout(pageEditor);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        scrollAreaEditor = new QScrollArea(pageEditor);
        scrollAreaEditor->setObjectName(QString::fromUtf8("scrollAreaEditor"));
        scrollAreaEditor->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaEditor->setWidgetResizable(true);
        scrollAreaWidgetContents_1 = new QWidget();
        scrollAreaWidgetContents_1->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_1"));
        scrollAreaWidgetContents_1->setGeometry(QRect(0, 0, 951, 559));
        gridLayout5 = new QGridLayout(scrollAreaWidgetContents_1);
        gridLayout5->setSpacing(6);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout5->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout5->addItem(verticalSpacer_5, 3, 0, 1, 1);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents_1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout6 = new QGridLayout(groupBox_3);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        checkBoxRealTimeCheck = new QCheckBox(groupBox_3);
        checkBoxRealTimeCheck->setObjectName(QString::fromUtf8("checkBoxRealTimeCheck"));
        sizePolicy2.setHeightForWidth(checkBoxRealTimeCheck->sizePolicy().hasHeightForWidth());
        checkBoxRealTimeCheck->setSizePolicy(sizePolicy2);
        checkBoxRealTimeCheck->setChecked(true);

        gridLayout6->addWidget(checkBoxRealTimeCheck, 13, 0, 1, 1);

        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout6->addWidget(label_33, 11, 0, 1, 1);

        comboboxLineNumbers = new QComboBox(groupBox_3);
        comboboxLineNumbers->addItem(QString());
        comboboxLineNumbers->addItem(QString());
        comboboxLineNumbers->addItem(QString());
        comboboxLineNumbers->setObjectName(QString::fromUtf8("comboboxLineNumbers"));

        gridLayout6->addWidget(comboboxLineNumbers, 11, 1, 1, 1);

        checkBoxInlineCheckNonTeXFiles = new QCheckBox(groupBox_3);
        checkBoxInlineCheckNonTeXFiles->setObjectName(QString::fromUtf8("checkBoxInlineCheckNonTeXFiles"));
        checkBoxInlineCheckNonTeXFiles->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxInlineCheckNonTeXFiles, 15, 0, 1, 2);

        checkBoxScanInstalledLatexPackages = new QCheckBox(groupBox_3);
        checkBoxScanInstalledLatexPackages->setObjectName(QString::fromUtf8("checkBoxScanInstalledLatexPackages"));
        checkBoxScanInstalledLatexPackages->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxScanInstalledLatexPackages, 17, 0, 1, 2);

        checkBoxFolding = new QCheckBox(groupBox_3);
        checkBoxFolding->setObjectName(QString::fromUtf8("checkBoxFolding"));

        gridLayout6->addWidget(checkBoxFolding, 12, 0, 1, 4);

        checkBoxReplaceIndentTabByWhitespace = new QCheckBox(groupBox_3);
        checkBoxReplaceIndentTabByWhitespace->setObjectName(QString::fromUtf8("checkBoxReplaceIndentTabByWhitespace"));

        gridLayout6->addWidget(checkBoxReplaceIndentTabByWhitespace, 7, 3, 1, 2);

        labelFamily = new QLabel(groupBox_3);
        labelFamily->setObjectName(QString::fromUtf8("labelFamily"));

        gridLayout6->addWidget(labelFamily, 0, 0, 1, 1);

        label_39 = new QLabel(groupBox_3);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout6->addWidget(label_39, 10, 0, 1, 1);

        labelEncoding = new QLabel(groupBox_3);
        labelEncoding->setObjectName(QString::fromUtf8("labelEncoding"));
        sizePolicy6.setHeightForWidth(labelEncoding->sizePolicy().hasHeightForWidth());
        labelEncoding->setSizePolicy(sizePolicy6);

        gridLayout6->addWidget(labelEncoding, 3, 0, 1, 1);

        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout6->addWidget(label_30, 7, 0, 1, 1);

        label_65 = new QLabel(groupBox_3);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        gridLayout6->addWidget(label_65, 5, 0, 1, 1);

        comboBoxEncoding = new QComboBox(groupBox_3);
        comboBoxEncoding->setObjectName(QString::fromUtf8("comboBoxEncoding"));

        gridLayout6->addWidget(comboBoxEncoding, 3, 1, 1, 2);

        checkBoxAutoDetectEncodingFromLatex = new QCheckBox(groupBox_3);
        checkBoxAutoDetectEncodingFromLatex->setObjectName(QString::fromUtf8("checkBoxAutoDetectEncodingFromLatex"));

        gridLayout6->addWidget(checkBoxAutoDetectEncodingFromLatex, 5, 1, 1, 2);

        checkBoxAutoDetectEncodingFromChars = new QCheckBox(groupBox_3);
        checkBoxAutoDetectEncodingFromChars->setObjectName(QString::fromUtf8("checkBoxAutoDetectEncodingFromChars"));

        gridLayout6->addWidget(checkBoxAutoDetectEncodingFromChars, 5, 3, 1, 2);

        comboBoxFont = new QComboBox(groupBox_3);
        comboBoxFont->setObjectName(QString::fromUtf8("comboBoxFont"));
        comboBoxFont->setEditable(true);

        gridLayout6->addWidget(comboBoxFont, 0, 1, 1, 2);

        spinBoxSize = new QSpinBox(groupBox_3);
        spinBoxSize->setObjectName(QString::fromUtf8("spinBoxSize"));
        spinBoxSize->setMinimum(1);
        spinBoxSize->setValue(12);

        gridLayout6->addWidget(spinBoxSize, 1, 1, 1, 4);

        spinBoxLineSpacingPercent = new QSpinBox(groupBox_3);
        spinBoxLineSpacingPercent->setObjectName(QString::fromUtf8("spinBoxLineSpacingPercent"));
        spinBoxLineSpacingPercent->setMinimum(100);
        spinBoxLineSpacingPercent->setMaximum(500);
        spinBoxLineSpacingPercent->setSingleStep(10);
        spinBoxLineSpacingPercent->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(spinBoxLineSpacingPercent, 2, 1, 1, 4);

        labelSize = new QLabel(groupBox_3);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));

        gridLayout6->addWidget(labelSize, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(label_2, 2, 0, 1, 1);

        comboBoxReplaceQuotes = new QComboBox(groupBox_3);
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->addItem(QString());
        comboBoxReplaceQuotes->setObjectName(QString::fromUtf8("comboBoxReplaceQuotes"));

        gridLayout6->addWidget(comboBoxReplaceQuotes, 10, 1, 1, 4);

        checkBoxShowOnlyMonospacedFonts = new QCheckBox(groupBox_3);
        checkBoxShowOnlyMonospacedFonts->setObjectName(QString::fromUtf8("checkBoxShowOnlyMonospacedFonts"));

        gridLayout6->addWidget(checkBoxShowOnlyMonospacedFonts, 0, 3, 1, 2);

        comboBoxAutoIndent = new QComboBox(groupBox_3);
        comboBoxAutoIndent->addItem(QString());
        comboBoxAutoIndent->addItem(QString());
        comboBoxAutoIndent->addItem(QString());
        comboBoxAutoIndent->setObjectName(QString::fromUtf8("comboBoxAutoIndent"));
        comboBoxAutoIndent->setProperty("advancedOption", QVariant(false));

        gridLayout6->addWidget(comboBoxAutoIndent, 7, 1, 1, 2);

        groupBoxInlineChecking = new QGroupBox(groupBox_3);
        groupBoxInlineChecking->setObjectName(QString::fromUtf8("groupBoxInlineChecking"));
        sizePolicy4.setHeightForWidth(groupBoxInlineChecking->sizePolicy().hasHeightForWidth());
        groupBoxInlineChecking->setSizePolicy(sizePolicy4);
        horizontalLayout_4 = new QHBoxLayout(groupBoxInlineChecking);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBoxInlineSpellCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlineSpellCheck->setObjectName(QString::fromUtf8("checkBoxInlineSpellCheck"));

        horizontalLayout_4->addWidget(checkBoxInlineSpellCheck);

        checkBoxInlineGrammarCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlineGrammarCheck->setObjectName(QString::fromUtf8("checkBoxInlineGrammarCheck"));

        horizontalLayout_4->addWidget(checkBoxInlineGrammarCheck);

        checkBoxInlineCitationCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlineCitationCheck->setObjectName(QString::fromUtf8("checkBoxInlineCitationCheck"));

        horizontalLayout_4->addWidget(checkBoxInlineCitationCheck);

        checkBoxInlineReferenceCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlineReferenceCheck->setObjectName(QString::fromUtf8("checkBoxInlineReferenceCheck"));

        horizontalLayout_4->addWidget(checkBoxInlineReferenceCheck);

        checkBoxInlineSyntaxCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlineSyntaxCheck->setObjectName(QString::fromUtf8("checkBoxInlineSyntaxCheck"));

        horizontalLayout_4->addWidget(checkBoxInlineSyntaxCheck);

        checkBoxInlinePackageCheck = new QCheckBox(groupBoxInlineChecking);
        checkBoxInlinePackageCheck->setObjectName(QString::fromUtf8("checkBoxInlinePackageCheck"));

        horizontalLayout_4->addWidget(checkBoxInlinePackageCheck);


        gridLayout6->addWidget(groupBoxInlineChecking, 13, 1, 1, 4);

        checkBoxReplaceTextTabByWhitespace = new QCheckBox(groupBox_3);
        checkBoxReplaceTextTabByWhitespace->setObjectName(QString::fromUtf8("checkBoxReplaceTextTabByWhitespace"));

        gridLayout6->addWidget(checkBoxReplaceTextTabByWhitespace, 8, 3, 1, 2);

        checkBoxHideGrammarErrorsInNonText = new QCheckBox(groupBox_3);
        checkBoxHideGrammarErrorsInNonText->setObjectName(QString::fromUtf8("checkBoxHideGrammarErrorsInNonText"));
        checkBoxHideGrammarErrorsInNonText->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxHideGrammarErrorsInNonText, 14, 2, 1, 3);

        checkBoxHideSpellingErrorsInNonText = new QCheckBox(groupBox_3);
        checkBoxHideSpellingErrorsInNonText->setObjectName(QString::fromUtf8("checkBoxHideSpellingErrorsInNonText"));
        checkBoxHideSpellingErrorsInNonText->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxHideSpellingErrorsInNonText, 14, 0, 1, 2);

        checkboxRemoveTrailingWsOnSave = new QCheckBox(groupBox_3);
        checkboxRemoveTrailingWsOnSave->setObjectName(QString::fromUtf8("checkboxRemoveTrailingWsOnSave"));

        gridLayout6->addWidget(checkboxRemoveTrailingWsOnSave, 9, 3, 1, 2);

        checkBoxAutoLoad = new QCheckBox(groupBox_3);
        checkBoxAutoLoad->setObjectName(QString::fromUtf8("checkBoxAutoLoad"));
        checkBoxAutoLoad->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxAutoLoad, 16, 0, 1, 2);

        checkBoxUseCache = new QCheckBox(groupBox_3);
        checkBoxUseCache->setObjectName(QString::fromUtf8("checkBoxUseCache"));
        checkBoxUseCache->setProperty("advancedOption", QVariant(true));

        gridLayout6->addWidget(checkBoxUseCache, 16, 2, 1, 1);


        gridLayout5->addWidget(groupBox_3, 1, 0, 1, 1);

        scrollAreaEditor->setWidget(scrollAreaWidgetContents_1);

        verticalLayout_1->addWidget(scrollAreaEditor);

        pagesWidget->addWidget(pageEditor);
        pageAdvEditor = new QWidget();
        pageAdvEditor->setObjectName(QString::fromUtf8("pageAdvEditor"));
        verticalLayout_2 = new QVBoxLayout(pageAdvEditor);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollAreaAdvancedEditor = new QScrollArea(pageAdvEditor);
        scrollAreaAdvancedEditor->setObjectName(QString::fromUtf8("scrollAreaAdvancedEditor"));
        scrollAreaAdvancedEditor->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaAdvancedEditor->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 858, 1825));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, -1, 0);
        groupBox_9 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_6 = new QGridLayout(groupBox_9);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBoxShowIndentGuides = new QCheckBox(groupBox_9);
        checkBoxShowIndentGuides->setObjectName(QString::fromUtf8("checkBoxShowIndentGuides"));

        horizontalLayout_6->addWidget(checkBoxShowIndentGuides);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        gridLayout_6->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        checkBoxState = new QCheckBox(groupBox_9);
        checkBoxState->setObjectName(QString::fromUtf8("checkBoxState"));
        checkBoxState->setProperty("advancedOption", QVariant(true));

        gridLayout_6->addWidget(checkBoxState, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_22 = new QLabel(groupBox_9);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_7->addWidget(label_22);

        sbTabSpace = new QSpinBox(groupBox_9);
        sbTabSpace->setObjectName(QString::fromUtf8("sbTabSpace"));
        sbTabSpace->setMinimum(1);
        sbTabSpace->setMaximum(32);
        sbTabSpace->setValue(4);

        horizontalLayout_7->addWidget(sbTabSpace);

        horizontalSpacer_5 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        gridLayout_6->addLayout(horizontalLayout_7, 1, 1, 1, 1);

        checkBoxShowWhitespace = new QCheckBox(groupBox_9);
        checkBoxShowWhitespace->setObjectName(QString::fromUtf8("checkBoxShowWhitespace"));
        checkBoxShowWhitespace->setChecked(true);
        checkBoxShowWhitespace->setProperty("advancedOption", QVariant(true));

        gridLayout_6->addWidget(checkBoxShowWhitespace, 0, 1, 1, 1);

        checkBoxLineState = new QCheckBox(groupBox_9);
        checkBoxLineState->setObjectName(QString::fromUtf8("checkBoxLineState"));
        checkBoxLineState->setProperty("advancedOption", QVariant(true));

        gridLayout_6->addWidget(checkBoxLineState, 0, 0, 1, 1);

        checkBoxBoldCursor = new QCheckBox(groupBox_9);
        checkBoxBoldCursor->setObjectName(QString::fromUtf8("checkBoxBoldCursor"));
        checkBoxBoldCursor->setChecked(true);
        checkBoxBoldCursor->setProperty("advancedOption", QVariant(true));

        gridLayout_6->addWidget(checkBoxBoldCursor, 2, 1, 1, 1);


        verticalLayout_8->addWidget(groupBox_9);

        groupBox_10 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout_5 = new QVBoxLayout(groupBox_10);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBoxCloseSearchReplaceTogether = new QCheckBox(groupBox_10);
        checkBoxCloseSearchReplaceTogether->setObjectName(QString::fromUtf8("checkBoxCloseSearchReplaceTogether"));
        checkBoxCloseSearchReplaceTogether->setProperty("advancedOption", QVariant(true));

        verticalLayout_5->addWidget(checkBoxCloseSearchReplaceTogether);

        checkBoxUseLineForSearch = new QCheckBox(groupBox_10);
        checkBoxUseLineForSearch->setObjectName(QString::fromUtf8("checkBoxUseLineForSearch"));
        checkBoxUseLineForSearch->setProperty("advancedOption", QVariant(true));

        verticalLayout_5->addWidget(checkBoxUseLineForSearch);

        checkBoxSearchOnlyInSelection = new QCheckBox(groupBox_10);
        checkBoxSearchOnlyInSelection->setObjectName(QString::fromUtf8("checkBoxSearchOnlyInSelection"));

        verticalLayout_5->addWidget(checkBoxSearchOnlyInSelection);


        verticalLayout_8->addWidget(groupBox_10);

        groupBox_11 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setCheckable(false);
        gridLayout7 = new QGridLayout(groupBox_11);
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        checkBoxShowLogMarkersWhenClickingLogEntry = new QCheckBox(groupBox_11);
        checkBoxShowLogMarkersWhenClickingLogEntry->setObjectName(QString::fromUtf8("checkBoxShowLogMarkersWhenClickingLogEntry"));

        gridLayout7->addWidget(checkBoxShowLogMarkersWhenClickingLogEntry, 21, 0, 1, 1);

        checkBoxMonitorFilesForExternalChanges = new QCheckBox(groupBox_11);
        checkBoxMonitorFilesForExternalChanges->setObjectName(QString::fromUtf8("checkBoxMonitorFilesForExternalChanges"));

        gridLayout7->addWidget(checkBoxMonitorFilesForExternalChanges, 17, 0, 1, 2);

        checkBoxAutoCompleteParens = new QCheckBox(groupBox_11);
        checkBoxAutoCompleteParens->setObjectName(QString::fromUtf8("checkBoxAutoCompleteParens"));

        gridLayout7->addWidget(checkBoxAutoCompleteParens, 3, 0, 1, 1);

        checkOverwriteOpeningBracketFollowedByPlaceholder = new QCheckBox(groupBox_11);
        checkOverwriteOpeningBracketFollowedByPlaceholder->setObjectName(QString::fromUtf8("checkOverwriteOpeningBracketFollowedByPlaceholder"));

        gridLayout7->addWidget(checkOverwriteOpeningBracketFollowedByPlaceholder, 4, 0, 1, 1);

        label_70 = new QLabel(groupBox_11);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        gridLayout7->addWidget(label_70, 24, 0, 1, 1);

        label_82 = new QLabel(groupBox_11);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        gridLayout7->addWidget(label_82, 11, 0, 1, 1);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(16, -1, -1, -1);
        checkBoxSilentReload = new QCheckBox(groupBox_11);
        checkBoxSilentReload->setObjectName(QString::fromUtf8("checkBoxSilentReload"));

        verticalLayout_12->addWidget(checkBoxSilentReload);


        gridLayout7->addLayout(verticalLayout_12, 18, 0, 1, 3);

        checkBoxCenterDocumentInEditor = new QCheckBox(groupBox_11);
        checkBoxCenterDocumentInEditor->setObjectName(QString::fromUtf8("checkBoxCenterDocumentInEditor"));

        gridLayout7->addWidget(checkBoxCenterDocumentInEditor, 13, 2, 1, 1);

        label_41 = new QLabel(groupBox_11);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout7->addWidget(label_41, 12, 0, 1, 1);

        comboBoxLogFileEncoding = new QComboBox(groupBox_11);
        comboBoxLogFileEncoding->setObjectName(QString::fromUtf8("comboBoxLogFileEncoding"));

        gridLayout7->addWidget(comboBoxLogFileEncoding, 23, 1, 1, 2);

        checkBoxInsertSymbolAsUCS = new QCheckBox(groupBox_11);
        checkBoxInsertSymbolAsUCS->setObjectName(QString::fromUtf8("checkBoxInsertSymbolAsUCS"));

        gridLayout7->addWidget(checkBoxInsertSymbolAsUCS, 20, 0, 1, 1);

        checkBoxAllowDragAndDrop = new QCheckBox(groupBox_11);
        checkBoxAllowDragAndDrop->setObjectName(QString::fromUtf8("checkBoxAllowDragAndDrop"));

        gridLayout7->addWidget(checkBoxAllowDragAndDrop, 9, 0, 1, 2);

        comboBoxContextMenuSpellcheckingEntryLocation = new QComboBox(groupBox_11);
        comboBoxContextMenuSpellcheckingEntryLocation->addItem(QString());
        comboBoxContextMenuSpellcheckingEntryLocation->addItem(QString());
        comboBoxContextMenuSpellcheckingEntryLocation->setObjectName(QString::fromUtf8("comboBoxContextMenuSpellcheckingEntryLocation"));

        gridLayout7->addWidget(comboBoxContextMenuSpellcheckingEntryLocation, 24, 1, 1, 2);

        checkBoxImageToolTip = new QCheckBox(groupBox_11);
        checkBoxImageToolTip->setObjectName(QString::fromUtf8("checkBoxImageToolTip"));

        gridLayout7->addWidget(checkBoxImageToolTip, 4, 2, 1, 2);

        comboBoxLineWrap = new QComboBox(groupBox_11);
        comboBoxLineWrap->addItem(QString());
        comboBoxLineWrap->addItem(QString());
        comboBoxLineWrap->addItem(QString());
        comboBoxLineWrap->addItem(QString());
        comboBoxLineWrap->setObjectName(QString::fromUtf8("comboBoxLineWrap"));

        gridLayout7->addWidget(comboBoxLineWrap, 12, 1, 1, 2);

        checkBoxDoubleClickSelectionIncludeLeadingBackslash = new QCheckBox(groupBox_11);
        checkBoxDoubleClickSelectionIncludeLeadingBackslash->setObjectName(QString::fromUtf8("checkBoxDoubleClickSelectionIncludeLeadingBackslash"));

        gridLayout7->addWidget(checkBoxDoubleClickSelectionIncludeLeadingBackslash, 10, 0, 1, 2);

        checkBoxTexDocInternal = new QCheckBox(groupBox_11);
        checkBoxTexDocInternal->setObjectName(QString::fromUtf8("checkBoxTexDocInternal"));

        gridLayout7->addWidget(checkBoxTexDocInternal, 6, 2, 1, 2);

        comboBoxAutoSave = new QComboBox(groupBox_11);
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->addItem(QString());
        comboBoxAutoSave->setObjectName(QString::fromUtf8("comboBoxAutoSave"));

        gridLayout7->addWidget(comboBoxAutoSave, 15, 1, 1, 1);

        spinBoxWrapLineWidth = new QSpinBox(groupBox_11);
        spinBoxWrapLineWidth->setObjectName(QString::fromUtf8("spinBoxWrapLineWidth"));
        spinBoxWrapLineWidth->setMinimum(20);
        spinBoxWrapLineWidth->setMaximum(999);

        gridLayout7->addWidget(spinBoxWrapLineWidth, 13, 1, 1, 1);

        checkBoxGoToErrorWhenDisplayingLog = new QCheckBox(groupBox_11);
        checkBoxGoToErrorWhenDisplayingLog->setObjectName(QString::fromUtf8("checkBoxGoToErrorWhenDisplayingLog"));

        gridLayout7->addWidget(checkBoxGoToErrorWhenDisplayingLog, 21, 2, 1, 1);

        checkBoxUseQSaveWrite = new QCheckBox(groupBox_11);
        checkBoxUseQSaveWrite->setObjectName(QString::fromUtf8("checkBoxUseQSaveWrite"));

        gridLayout7->addWidget(checkBoxUseQSaveWrite, 16, 0, 1, 2);

        comboBoxTripleClickSelection = new QComboBox(groupBox_11);
        comboBoxTripleClickSelection->addItem(QString());
        comboBoxTripleClickSelection->addItem(QString());
        comboBoxTripleClickSelection->addItem(QString());
        comboBoxTripleClickSelection->addItem(QString());
        comboBoxTripleClickSelection->addItem(QString());
        comboBoxTripleClickSelection->setObjectName(QString::fromUtf8("comboBoxTripleClickSelection"));

        gridLayout7->addWidget(comboBoxTripleClickSelection, 11, 1, 1, 2);

        checkBoxVerticalOverScroll = new QCheckBox(groupBox_11);
        checkBoxVerticalOverScroll->setObjectName(QString::fromUtf8("checkBoxVerticalOverScroll"));

        gridLayout7->addWidget(checkBoxVerticalOverScroll, 6, 0, 1, 2);

        label_80 = new QLabel(groupBox_11);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout7->addWidget(label_80, 23, 0, 1, 1);

        checkBoxSmoothScrolling = new QCheckBox(groupBox_11);
        checkBoxSmoothScrolling->setObjectName(QString::fromUtf8("checkBoxSmoothScrolling"));

        gridLayout7->addWidget(checkBoxSmoothScrolling, 7, 0, 1, 2);

        checkBoxToolTipHelp2 = new QCheckBox(groupBox_11);
        checkBoxToolTipHelp2->setObjectName(QString::fromUtf8("checkBoxToolTipHelp2"));

        gridLayout7->addWidget(checkBoxToolTipHelp2, 5, 2, 1, 2);

        label_24 = new QLabel(groupBox_11);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout7->addWidget(label_24, 15, 0, 1, 1);

        label_85 = new QLabel(groupBox_11);
        label_85->setObjectName(QString::fromUtf8("label_85"));

        gridLayout7->addWidget(label_85, 25, 0, 1, 1);

        checkBoxMouseWheelZoom = new QCheckBox(groupBox_11);
        checkBoxMouseWheelZoom->setObjectName(QString::fromUtf8("checkBoxMouseWheelZoom"));

        gridLayout7->addWidget(checkBoxMouseWheelZoom, 8, 0, 1, 2);

        lineEditCiteCommand = new QLineEdit(groupBox_11);
        lineEditCiteCommand->setObjectName(QString::fromUtf8("lineEditCiteCommand"));

        gridLayout7->addWidget(lineEditCiteCommand, 25, 1, 1, 2);

        checkOverwriteClosingBracketFollowingPlaceholder = new QCheckBox(groupBox_11);
        checkOverwriteClosingBracketFollowingPlaceholder->setObjectName(QString::fromUtf8("checkOverwriteClosingBracketFollowingPlaceholder"));

        gridLayout7->addWidget(checkOverwriteClosingBracketFollowingPlaceholder, 5, 0, 1, 1);

        checkBoxToolTipPreview = new QCheckBox(groupBox_11);
        checkBoxToolTipPreview->setObjectName(QString::fromUtf8("checkBoxToolTipPreview"));

        gridLayout7->addWidget(checkBoxToolTipPreview, 3, 2, 1, 2);

        label_23 = new QLabel(groupBox_11);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout7->addWidget(label_23, 13, 0, 1, 1);

        checkBoxEnableRainbowDelimiters = new QCheckBox(groupBox_11);
        checkBoxEnableRainbowDelimiters->setObjectName(QString::fromUtf8("checkBoxEnableRainbowDelimiters"));

        gridLayout7->addWidget(checkBoxEnableRainbowDelimiters, 7, 2, 1, 2);


        verticalLayout_8->addWidget(groupBox_11);

        groupBox_16 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        gridLayout_2 = new QGridLayout(groupBox_16);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBoxTOCBackgroundColor = new QComboBox(groupBox_16);
        comboBoxTOCBackgroundColor->addItem(QString());
        comboBoxTOCBackgroundColor->addItem(QString());
        comboBoxTOCBackgroundColor->addItem(QString());
        comboBoxTOCBackgroundColor->setObjectName(QString::fromUtf8("comboBoxTOCBackgroundColor"));

        gridLayout_2->addWidget(comboBoxTOCBackgroundColor, 10, 2, 1, 1);

        checkBoxMarkStructureElementsBeyondEnd = new QCheckBox(groupBox_16);
        checkBoxMarkStructureElementsBeyondEnd->setObjectName(QString::fromUtf8("checkBoxMarkStructureElementsBeyondEnd"));

        gridLayout_2->addWidget(checkBoxMarkStructureElementsBeyondEnd, 9, 0, 1, 1);

        label_64 = new QLabel(groupBox_16);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        gridLayout_2->addWidget(label_64, 6, 0, 1, 1);

        leReferenceCommandsInContextMenu = new QLineEdit(groupBox_16);
        leReferenceCommandsInContextMenu->setObjectName(QString::fromUtf8("leReferenceCommandsInContextMenu"));

        gridLayout_2->addWidget(leReferenceCommandsInContextMenu, 6, 2, 1, 1);

        leRegExpTODO = new QLineEdit(groupBox_16);
        leRegExpTODO->setObjectName(QString::fromUtf8("leRegExpTODO"));

        gridLayout_2->addWidget(leRegExpTODO, 7, 2, 1, 1);

        label_83 = new QLabel(groupBox_16);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        gridLayout_2->addWidget(label_83, 7, 0, 1, 1);

        checkBoxIndentIncludesInStructureTree = new QCheckBox(groupBox_16);
        checkBoxIndentIncludesInStructureTree->setObjectName(QString::fromUtf8("checkBoxIndentIncludesInStructureTree"));

        gridLayout_2->addWidget(checkBoxIndentIncludesInStructureTree, 0, 0, 1, 2);

        checkBoxScrollToCurrentPosition = new QCheckBox(groupBox_16);
        checkBoxScrollToCurrentPosition->setObjectName(QString::fromUtf8("checkBoxScrollToCurrentPosition"));

        gridLayout_2->addWidget(checkBoxScrollToCurrentPosition, 0, 2, 1, 1);

        checkBoxMarkStructureElementsInAppendix = new QCheckBox(groupBox_16);
        checkBoxMarkStructureElementsInAppendix->setObjectName(QString::fromUtf8("checkBoxMarkStructureElementsInAppendix"));

        gridLayout_2->addWidget(checkBoxMarkStructureElementsInAppendix, 9, 2, 1, 1);

        label_90 = new QLabel(groupBox_16);
        label_90->setObjectName(QString::fromUtf8("label_90"));

        gridLayout_2->addWidget(label_90, 10, 0, 1, 1);

        checkBoxIndentIncludesInStructureTree->raise();
        label_64->raise();
        leReferenceCommandsInContextMenu->raise();
        checkBoxMarkStructureElementsBeyondEnd->raise();
        label_83->raise();
        leRegExpTODO->raise();
        comboBoxTOCBackgroundColor->raise();
        checkBoxScrollToCurrentPosition->raise();
        checkBoxMarkStructureElementsInAppendix->raise();
        label_90->raise();

        verticalLayout_8->addWidget(groupBox_16);

        groupBoxBibliography = new QGroupBox(scrollAreaWidgetContents_2);
        groupBoxBibliography->setObjectName(QString::fromUtf8("groupBoxBibliography"));
        gridLayout_7 = new QGridLayout(groupBoxBibliography);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_73 = new QLabel(groupBoxBibliography);
        label_73->setObjectName(QString::fromUtf8("label_73"));

        gridLayout_7->addWidget(label_73, 1, 0, 1, 1);

        checkBoxParseBibTeX = new QCheckBox(groupBoxBibliography);
        checkBoxParseBibTeX->setObjectName(QString::fromUtf8("checkBoxParseBibTeX"));

        gridLayout_7->addWidget(checkBoxParseBibTeX, 0, 0, 1, 1);

        comboBoxBibFileEncoding = new QComboBox(groupBoxBibliography);
        comboBoxBibFileEncoding->setObjectName(QString::fromUtf8("comboBoxBibFileEncoding"));

        gridLayout_7->addWidget(comboBoxBibFileEncoding, 1, 1, 1, 1);


        verticalLayout_8->addWidget(groupBoxBibliography);

        gbTableAutoformat = new QGroupBox(scrollAreaWidgetContents_2);
        gbTableAutoformat->setObjectName(QString::fromUtf8("gbTableAutoformat"));
        gridLayoutTableAutoFormat = new QGridLayout(gbTableAutoformat);
        gridLayoutTableAutoFormat->setObjectName(QString::fromUtf8("gridLayoutTableAutoFormat"));
        cbTableFormatingOneLinePerCell = new QCheckBox(gbTableAutoformat);
        cbTableFormatingOneLinePerCell->setObjectName(QString::fromUtf8("cbTableFormatingOneLinePerCell"));

        gridLayoutTableAutoFormat->addWidget(cbTableFormatingOneLinePerCell, 2, 0, 1, 2);

        cbTableFormatingSpecialCommandPos = new QComboBox(gbTableAutoformat);
        cbTableFormatingSpecialCommandPos->addItem(QString());
        cbTableFormatingSpecialCommandPos->addItem(QString());
        cbTableFormatingSpecialCommandPos->addItem(QString());
        cbTableFormatingSpecialCommandPos->setObjectName(QString::fromUtf8("cbTableFormatingSpecialCommandPos"));

        gridLayoutTableAutoFormat->addWidget(cbTableFormatingSpecialCommandPos, 1, 1, 1, 1);

        label_61 = new QLabel(gbTableAutoformat);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayoutTableAutoFormat->addWidget(label_61, 1, 0, 1, 1);

        leTableFormatingSpecialCommands = new QLineEdit(gbTableAutoformat);
        leTableFormatingSpecialCommands->setObjectName(QString::fromUtf8("leTableFormatingSpecialCommands"));

        gridLayoutTableAutoFormat->addWidget(leTableFormatingSpecialCommands, 0, 1, 1, 1);

        label_60 = new QLabel(gbTableAutoformat);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayoutTableAutoFormat->addWidget(label_60, 0, 0, 1, 1);


        verticalLayout_8->addWidget(gbTableAutoformat);

        gbAdditionalSearchPaths = new QGroupBox(scrollAreaWidgetContents_2);
        gbAdditionalSearchPaths->setObjectName(QString::fromUtf8("gbAdditionalSearchPaths"));
        gridLayout71 = new QGridLayout(gbAdditionalSearchPaths);
        gridLayout71->setObjectName(QString::fromUtf8("gridLayout71"));
        gridLayout71->setVerticalSpacing(2);
        label_62 = new QLabel(gbAdditionalSearchPaths);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        gridLayout71->addWidget(label_62, 0, 0, 1, 1);

        lineEditPathBib = new QLineEdit(gbAdditionalSearchPaths);
        lineEditPathBib->setObjectName(QString::fromUtf8("lineEditPathBib"));

        gridLayout71->addWidget(lineEditPathBib, 0, 1, 1, 1);

        lineEditPathImages = new QLineEdit(gbAdditionalSearchPaths);
        lineEditPathImages->setObjectName(QString::fromUtf8("lineEditPathImages"));

        gridLayout71->addWidget(lineEditPathImages, 1, 1, 1, 1);

        label_63 = new QLabel(gbAdditionalSearchPaths);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        gridLayout71->addWidget(label_63, 1, 0, 1, 1);

        pushButtonPathBib = new QPushButton(gbAdditionalSearchPaths);
        pushButtonPathBib->setObjectName(QString::fromUtf8("pushButtonPathBib"));
        sizePolicy10.setHeightForWidth(pushButtonPathBib->sizePolicy().hasHeightForWidth());
        pushButtonPathBib->setSizePolicy(sizePolicy10);
        pushButtonPathBib->setIcon(icon);

        gridLayout71->addWidget(pushButtonPathBib, 0, 2, 1, 1);

        pushButtonPathImages = new QPushButton(gbAdditionalSearchPaths);
        pushButtonPathImages->setObjectName(QString::fromUtf8("pushButtonPathImages"));
        pushButtonPathImages->setIcon(icon);

        gridLayout71->addWidget(pushButtonPathImages, 1, 2, 1, 1);


        verticalLayout_8->addWidget(gbAdditionalSearchPaths);

        groupBox_15 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        gridLayout_8a = new QGridLayout(groupBox_15);
        gridLayout_8a->setObjectName(QString::fromUtf8("gridLayout_8a"));
        checkBoxAutoLRM = new QCheckBox(groupBox_15);
        checkBoxAutoLRM->setObjectName(QString::fromUtf8("checkBoxAutoLRM"));

        gridLayout_8a->addWidget(checkBoxAutoLRM, 0, 0, 1, 3);

        checkBoxVisualColumnMode = new QCheckBox(groupBox_15);
        checkBoxVisualColumnMode->setObjectName(QString::fromUtf8("checkBoxVisualColumnMode"));

        gridLayout_8a->addWidget(checkBoxVisualColumnMode, 1, 0, 1, 3);

        labelSwitchKeyboardLayout = new QLabel(groupBox_15);
        labelSwitchKeyboardLayout->setObjectName(QString::fromUtf8("labelSwitchKeyboardLayout"));

        gridLayout_8a->addWidget(labelSwitchKeyboardLayout, 2, 0, 1, 1);

        checkBoxSwitchLanguagesDirection = new QCheckBox(groupBox_15);
        checkBoxSwitchLanguagesDirection->setObjectName(QString::fromUtf8("checkBoxSwitchLanguagesDirection"));

        gridLayout_8a->addWidget(checkBoxSwitchLanguagesDirection, 2, 1, 1, 1);

        checkBoxSwitchLanguagesMath = new QCheckBox(groupBox_15);
        checkBoxSwitchLanguagesMath->setObjectName(QString::fromUtf8("checkBoxSwitchLanguagesMath"));

        gridLayout_8a->addWidget(checkBoxSwitchLanguagesMath, 2, 2, 1, 1);


        verticalLayout_8->addWidget(groupBox_15);

        groupBox_12 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        verticalLayout_11 = new QVBoxLayout(groupBox_12);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        checkBoxHackDisableAccentWorkaround = new QCheckBox(groupBox_12);
        checkBoxHackDisableAccentWorkaround->setObjectName(QString::fromUtf8("checkBoxHackDisableAccentWorkaround"));

        verticalLayout_11->addWidget(checkBoxHackDisableAccentWorkaround);

        checkBoxHackAutoRendering = new QCheckBox(groupBox_12);
        checkBoxHackAutoRendering->setObjectName(QString::fromUtf8("checkBoxHackAutoRendering"));

        verticalLayout_11->addWidget(checkBoxHackAutoRendering);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(16, -1, -1, -1);
        comboBoxHackRenderMode = new QComboBox(groupBox_12);
        comboBoxHackRenderMode->addItem(QString());
        comboBoxHackRenderMode->addItem(QString());
        comboBoxHackRenderMode->addItem(QString());
        comboBoxHackRenderMode->setObjectName(QString::fromUtf8("comboBoxHackRenderMode"));

        gridLayout_3->addWidget(comboBoxHackRenderMode, 3, 1, 1, 1);

        labelRenderMode = new QLabel(groupBox_12);
        labelRenderMode->setObjectName(QString::fromUtf8("labelRenderMode"));
        QSizePolicy sizePolicy11(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(labelRenderMode->sizePolicy().hasHeightForWidth());
        labelRenderMode->setSizePolicy(sizePolicy11);

        gridLayout_3->addWidget(labelRenderMode, 3, 0, 1, 1);

        checkBoxHackDisableFixedPitch = new QCheckBox(groupBox_12);
        checkBoxHackDisableFixedPitch->setObjectName(QString::fromUtf8("checkBoxHackDisableFixedPitch"));

        gridLayout_3->addWidget(checkBoxHackDisableFixedPitch, 1, 0, 1, 2);

        checkBoxHackDisableWidthCache = new QCheckBox(groupBox_12);
        checkBoxHackDisableWidthCache->setObjectName(QString::fromUtf8("checkBoxHackDisableWidthCache"));

        gridLayout_3->addWidget(checkBoxHackDisableWidthCache, 0, 0, 1, 2);

        checkBoxHackDisableLineCache = new QCheckBox(groupBox_12);
        checkBoxHackDisableLineCache->setObjectName(QString::fromUtf8("checkBoxHackDisableLineCache"));

        gridLayout_3->addWidget(checkBoxHackDisableLineCache, 2, 0, 1, 2);


        verticalLayout_11->addLayout(gridLayout_3);


        verticalLayout_8->addWidget(groupBox_12);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer);

        scrollAreaAdvancedEditor->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollAreaAdvancedEditor);

        pagesWidget->addWidget(pageAdvEditor);
        pageSyntaxHighlighting = new QWidget();
        pageSyntaxHighlighting->setObjectName(QString::fromUtf8("pageSyntaxHighlighting"));
        verticalLayout_7 = new QVBoxLayout(pageSyntaxHighlighting);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        formatConfigBox = new QGroupBox(pageSyntaxHighlighting);
        formatConfigBox->setObjectName(QString::fromUtf8("formatConfigBox"));
        sizePolicy8.setHeightForWidth(formatConfigBox->sizePolicy().hasHeightForWidth());
        formatConfigBox->setSizePolicy(sizePolicy8);
        formatConfigBox->setMinimumSize(QSize(0, 0));
        formatConfigBox->setBaseSize(QSize(0, 0));

        verticalLayout_7->addWidget(formatConfigBox);

        pagesWidget->addWidget(pageSyntaxHighlighting);
        pageCompletion = new QWidget();
        pageCompletion->setObjectName(QString::fromUtf8("pageCompletion"));
        verticalLayout_4 = new QVBoxLayout(pageCompletion);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(pageCompletion);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy12(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy12);
        gridLayout8 = new QGridLayout(groupBox_2);
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        checkBoxAutoReplaceCommands = new QCheckBox(groupBox_2);
        checkBoxAutoReplaceCommands->setObjectName(QString::fromUtf8("checkBoxAutoReplaceCommands"));

        gridLayout8->addWidget(checkBoxAutoReplaceCommands, 1, 0, 1, 1);

        checkBoxUsePlaceholders = new QCheckBox(groupBox_2);
        checkBoxUsePlaceholders->setObjectName(QString::fromUtf8("checkBoxUsePlaceholders"));
        checkBoxUsePlaceholders->setProperty("advancedOption", QVariant(true));

        gridLayout8->addWidget(checkBoxUsePlaceholders, 2, 1, 1, 1);

        checkBoxToolTipCompletePreview = new QCheckBox(groupBox_2);
        checkBoxToolTipCompletePreview->setObjectName(QString::fromUtf8("checkBoxToolTipCompletePreview"));

        gridLayout8->addWidget(checkBoxToolTipCompletePreview, 1, 1, 1, 1);

        checkBoxShowPlaceholders = new QCheckBox(groupBox_2);
        checkBoxShowPlaceholders->setObjectName(QString::fromUtf8("checkBoxShowPlaceholders"));
        checkBoxShowPlaceholders->setProperty("advancedOption", QVariant(true));

        gridLayout8->addWidget(checkBoxShowPlaceholders, 3, 1, 1, 1);

        checkBoxToolTipHelp = new QCheckBox(groupBox_2);
        checkBoxToolTipHelp->setObjectName(QString::fromUtf8("checkBoxToolTipHelp"));
        checkBoxToolTipHelp->setProperty("advancedOption", QVariant(false));

        gridLayout8->addWidget(checkBoxToolTipHelp, 0, 1, 1, 1);

        checkBoxCompletion = new QCheckBox(groupBox_2);
        checkBoxCompletion->setObjectName(QString::fromUtf8("checkBoxCompletion"));

        gridLayout8->addWidget(checkBoxCompletion, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_40 = new QLabel(groupBox_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setProperty("advancedOption", QVariant(true));

        horizontalLayout_2->addWidget(label_40);

        spinBoxTabRelFontSize = new QSpinBox(groupBox_2);
        spinBoxTabRelFontSize->setObjectName(QString::fromUtf8("spinBoxTabRelFontSize"));
        spinBoxTabRelFontSize->setSuffix(QString::fromUtf8("%"));
        spinBoxTabRelFontSize->setMaximum(10000);
        spinBoxTabRelFontSize->setValue(75);
        spinBoxTabRelFontSize->setProperty("advancedOption", QVariant(true));

        horizontalLayout_2->addWidget(spinBoxTabRelFontSize);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout8->addLayout(horizontalLayout_2, 5, 1, 1, 1);

        checkBoxEOWCompletes = new QCheckBox(groupBox_2);
        checkBoxEOWCompletes->setObjectName(QString::fromUtf8("checkBoxEOWCompletes"));
        checkBoxEOWCompletes->setProperty("advancedOption", QVariant(true));

        gridLayout8->addWidget(checkBoxEOWCompletes, 2, 0, 1, 1);

        checkBoxCompletePrefix = new QCheckBox(groupBox_2);
        checkBoxCompletePrefix->setObjectName(QString::fromUtf8("checkBoxCompletePrefix"));
        checkBoxCompletePrefix->setProperty("advancedOption", QVariant(true));

        gridLayout8->addWidget(checkBoxCompletePrefix, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxPreferedTab = new QComboBox(groupBox_2);
        comboBoxPreferedTab->addItem(QString());
        comboBoxPreferedTab->addItem(QString());
        comboBoxPreferedTab->addItem(QString());
        comboBoxPreferedTab->addItem(QString());
        comboBoxPreferedTab->setObjectName(QString::fromUtf8("comboBoxPreferedTab"));

        horizontalLayout->addWidget(comboBoxPreferedTab);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout8->addLayout(horizontalLayout, 5, 0, 1, 1);

        checkBoxAutoInsertMathDelimiters = new QCheckBox(groupBox_2);
        checkBoxAutoInsertMathDelimiters->setObjectName(QString::fromUtf8("checkBoxAutoInsertMathDelimiters"));

        gridLayout8->addWidget(checkBoxAutoInsertMathDelimiters, 4, 0, 1, 1);

        checkBoxCompleteUserConstructs = new QCheckBox(groupBox_2);
        checkBoxCompleteUserConstructs->setObjectName(QString::fromUtf8("checkBoxCompleteUserConstructs"));

        gridLayout8->addWidget(checkBoxCompleteUserConstructs, 4, 1, 1, 1);

        gridLayout8->setColumnStretch(0, 1);
        gridLayout8->setColumnStretch(1, 1);

        verticalLayout_4->addWidget(groupBox_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_12 = new QLabel(pageCompletion);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setProperty("advancedOption", QVariant(true));

        horizontalLayout_3->addWidget(label_12);

        leCompletionFilter = new QLineEdit(pageCompletion);
        leCompletionFilter->setObjectName(QString::fromUtf8("leCompletionFilter"));
        leCompletionFilter->setProperty("advancedOption", QVariant(true));

        horizontalLayout_3->addWidget(leCompletionFilter);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        completeListWidget = new QListWidget(pageCompletion);
        completeListWidget->setObjectName(QString::fromUtf8("completeListWidget"));
        sizePolicy4.setHeightForWidth(completeListWidget->sizePolicy().hasHeightForWidth());
        completeListWidget->setSizePolicy(sizePolicy4);
        completeListWidget->setFlow(QListView::Flow::TopToBottom);
        completeListWidget->setProperty("isWrapping", QVariant(true));
        completeListWidget->setResizeMode(QListView::ResizeMode::Adjust);
        completeListWidget->setUniformItemSizes(false);
        completeListWidget->setSortingEnabled(true);
        completeListWidget->setProperty("advancedOption", QVariant(true));

        horizontalLayout_8->addWidget(completeListWidget);

        verticalSpacer_9 = new QSpacerItem(0, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(verticalSpacer_9);


        verticalLayout_4->addLayout(horizontalLayout_8);

        pagesWidget->addWidget(pageCompletion);
        pageGrammar = new QWidget();
        pageGrammar->setObjectName(QString::fromUtf8("pageGrammar"));
        verticalLayout_6 = new QVBoxLayout(pageGrammar);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        scrollAreaGrammar = new QScrollArea(pageGrammar);
        scrollAreaGrammar->setObjectName(QString::fromUtf8("scrollAreaGrammar"));
        scrollAreaGrammar->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaGrammar->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 1132, 1027));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        groupBox_Dictionaries = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_Dictionaries->setObjectName(QString::fromUtf8("groupBox_Dictionaries"));
        _4 = new QGridLayout(groupBox_Dictionaries);
        _4->setObjectName(QString::fromUtf8("_4"));
        label_43 = new QLabel(groupBox_Dictionaries);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        _4->addWidget(label_43, 1, 0, 1, 1);

        pushButtonDictDir = new QPushButton(groupBox_Dictionaries);
        pushButtonDictDir->setObjectName(QString::fromUtf8("pushButtonDictDir"));
        sizePolicy10.setHeightForWidth(pushButtonDictDir->sizePolicy().hasHeightForWidth());
        pushButtonDictDir->setSizePolicy(sizePolicy10);
        pushButtonDictDir->setIcon(icon);

        _4->addWidget(pushButtonDictDir, 0, 5, 1, 1);

        comboBoxSpellcheckLang = new QComboBox(groupBox_Dictionaries);
        comboBoxSpellcheckLang->setObjectName(QString::fromUtf8("comboBoxSpellcheckLang"));

        _4->addWidget(comboBoxSpellcheckLang, 1, 1, 1, 5);

        label_42 = new QLabel(groupBox_Dictionaries);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        _4->addWidget(label_42, 0, 0, 1, 1);

        leDictDir = new QLineEdit(groupBox_Dictionaries);
        leDictDir->setObjectName(QString::fromUtf8("leDictDir"));

        _4->addWidget(leDictDir, 0, 1, 1, 4);

        comboBoxThesaurusFileName = new QComboBox(groupBox_Dictionaries);
        comboBoxThesaurusFileName->setObjectName(QString::fromUtf8("comboBoxThesaurusFileName"));
        comboBoxThesaurusFileName->setEditable(true);

        _4->addWidget(comboBoxThesaurusFileName, 3, 1, 1, 4);

        label_13 = new QLabel(groupBox_Dictionaries);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        _4->addWidget(label_13, 3, 0, 1, 1);

        btSelectThesaurusFileName = new QPushButton(groupBox_Dictionaries);
        btSelectThesaurusFileName->setObjectName(QString::fromUtf8("btSelectThesaurusFileName"));
        sizePolicy10.setHeightForWidth(btSelectThesaurusFileName->sizePolicy().hasHeightForWidth());
        btSelectThesaurusFileName->setSizePolicy(sizePolicy10);
        btSelectThesaurusFileName->setIcon(icon);

        _4->addWidget(btSelectThesaurusFileName, 3, 5, 1, 1);

        labelGetDic = new QLabel(groupBox_Dictionaries);
        labelGetDic->setObjectName(QString::fromUtf8("labelGetDic"));
        sizePolicy8.setHeightForWidth(labelGetDic->sizePolicy().hasHeightForWidth());
        labelGetDic->setSizePolicy(sizePolicy8);

        _4->addWidget(labelGetDic, 2, 2, 1, 4);

        pushButtonImportDictionary = new QPushButton(groupBox_Dictionaries);
        pushButtonImportDictionary->setObjectName(QString::fromUtf8("pushButtonImportDictionary"));
        sizePolicy10.setHeightForWidth(pushButtonImportDictionary->sizePolicy().hasHeightForWidth());
        pushButtonImportDictionary->setSizePolicy(sizePolicy10);

        _4->addWidget(pushButtonImportDictionary, 2, 1, 1, 1);

        _4->setColumnStretch(1, 1);
        _4->setColumnStretch(2, 1);
        _4->setColumnStretch(3, 1);
        _4->setColumnStretch(4, 1);
        _4->setColumnStretch(5, 1);

        verticalLayout_9->addWidget(groupBox_Dictionaries);

        groupBox_13 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        gridLayout_8 = new QGridLayout(groupBox_13);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        checkBoxGrammarRepetitionCheck = new QCheckBox(groupBox_13);
        checkBoxGrammarRepetitionCheck->setObjectName(QString::fromUtf8("checkBoxGrammarRepetitionCheck"));

        gridLayout_8->addWidget(checkBoxGrammarRepetitionCheck, 0, 0, 1, 3);

        label_47 = new QLabel(groupBox_13);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(label_47, 1, 0, 1, 1);

        spinBoxGrammarRepetitionDistance = new QSpinBox(groupBox_13);
        spinBoxGrammarRepetitionDistance->setObjectName(QString::fromUtf8("spinBoxGrammarRepetitionDistance"));
        spinBoxGrammarRepetitionDistance->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(spinBoxGrammarRepetitionDistance, 1, 1, 1, 2);

        spinBoxGrammarLongRangeRepetition = new QSpinBox(groupBox_13);
        spinBoxGrammarLongRangeRepetition->setObjectName(QString::fromUtf8("spinBoxGrammarLongRangeRepetition"));
        spinBoxGrammarLongRangeRepetition->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(spinBoxGrammarLongRangeRepetition, 2, 1, 1, 2);

        spinBoxGrammarLongRangeRepetitionMinLength = new QSpinBox(groupBox_13);
        spinBoxGrammarLongRangeRepetitionMinLength->setObjectName(QString::fromUtf8("spinBoxGrammarLongRangeRepetitionMinLength"));
        spinBoxGrammarLongRangeRepetitionMinLength->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(spinBoxGrammarLongRangeRepetitionMinLength, 3, 1, 1, 2);

        label_54 = new QLabel(groupBox_13);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(label_54, 2, 0, 1, 1);

        label_55 = new QLabel(groupBox_13);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setProperty("advancedOption", QVariant(true));

        gridLayout_8->addWidget(label_55, 3, 0, 1, 1);

        label_48 = new QLabel(groupBox_13);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_8->addWidget(label_48, 5, 0, 1, 1);

        checkBoxGrammarBadWordCheck = new QCheckBox(groupBox_13);
        checkBoxGrammarBadWordCheck->setObjectName(QString::fromUtf8("checkBoxGrammarBadWordCheck"));

        gridLayout_8->addWidget(checkBoxGrammarBadWordCheck, 4, 0, 1, 1);

        lineEditGrammarWordlists = new QLineEdit(groupBox_13);
        lineEditGrammarWordlists->setObjectName(QString::fromUtf8("lineEditGrammarWordlists"));

        gridLayout_8->addWidget(lineEditGrammarWordlists, 5, 1, 1, 1);

        pushButtonGrammarWordlists = new QPushButton(groupBox_13);
        pushButtonGrammarWordlists->setObjectName(QString::fromUtf8("pushButtonGrammarWordlists"));
        sizePolicy10.setHeightForWidth(pushButtonGrammarWordlists->sizePolicy().hasHeightForWidth());
        pushButtonGrammarWordlists->setSizePolicy(sizePolicy10);
        pushButtonGrammarWordlists->setIcon(icon);

        gridLayout_8->addWidget(pushButtonGrammarWordlists, 5, 2, 1, 1);


        verticalLayout_9->addWidget(groupBox_13);

        groupBox_AIChat = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_AIChat->setObjectName(QString::fromUtf8("groupBox_AIChat"));
        gl_AIChat = new QGridLayout(groupBox_AIChat);
        gl_AIChat->setObjectName(QString::fromUtf8("gl_AIChat"));
        cbAIPreferredModel = new QComboBox(groupBox_AIChat);
        cbAIPreferredModel->addItem(QString::fromUtf8("open-mistral-7b"));
        cbAIPreferredModel->addItem(QString::fromUtf8("open-mixtral-8x7b"));
        cbAIPreferredModel->addItem(QString::fromUtf8("mistral-small-latest"));
        cbAIPreferredModel->addItem(QString::fromUtf8("mistral-medium-latest"));
        cbAIPreferredModel->addItem(QString::fromUtf8("mistral-large-latest"));
        cbAIPreferredModel->setObjectName(QString::fromUtf8("cbAIPreferredModel"));

        gl_AIChat->addWidget(cbAIPreferredModel, 3, 3, 1, 1);

        label_AIProvider = new QLabel(groupBox_AIChat);
        label_AIProvider->setObjectName(QString::fromUtf8("label_AIProvider"));

        gl_AIChat->addWidget(label_AIProvider, 0, 0, 1, 1);

        pbRetrieveModels = new QPushButton(groupBox_AIChat);
        pbRetrieveModels->setObjectName(QString::fromUtf8("pbRetrieveModels"));

        gl_AIChat->addWidget(pbRetrieveModels, 3, 4, 1, 1);

        label_AIAPI = new QLabel(groupBox_AIChat);
        label_AIAPI->setObjectName(QString::fromUtf8("label_AIAPI"));

        gl_AIChat->addWidget(label_AIAPI, 1, 0, 1, 2);

        cbAIProvider = new QComboBox(groupBox_AIChat);
        cbAIProvider->addItem(QString());
        cbAIProvider->addItem(QString());
        cbAIProvider->addItem(QString());
        cbAIProvider->addItem(QString());
        cbAIProvider->addItem(QString());
        cbAIProvider->addItem(QString());
        cbAIProvider->setObjectName(QString::fromUtf8("cbAIProvider"));

        gl_AIChat->addWidget(cbAIProvider, 0, 3, 1, 1);

        cbAIRecordConversation = new QCheckBox(groupBox_AIChat);
        cbAIRecordConversation->setObjectName(QString::fromUtf8("cbAIRecordConversation"));

        gl_AIChat->addWidget(cbAIRecordConversation, 4, 0, 1, 1);

        label_AIModel = new QLabel(groupBox_AIChat);
        label_AIModel->setObjectName(QString::fromUtf8("label_AIModel"));

        gl_AIChat->addWidget(label_AIModel, 3, 0, 1, 1);

        leAIAPIKey = new QLineEdit(groupBox_AIChat);
        leAIAPIKey->setObjectName(QString::fromUtf8("leAIAPIKey"));

        gl_AIChat->addWidget(leAIAPIKey, 1, 3, 1, 1);

        leAIAPIURL = new QLineEdit(groupBox_AIChat);
        leAIAPIURL->setObjectName(QString::fromUtf8("leAIAPIURL"));

        gl_AIChat->addWidget(leAIAPIURL, 2, 3, 1, 1);

        label_91 = new QLabel(groupBox_AIChat);
        label_91->setObjectName(QString::fromUtf8("label_91"));

        gl_AIChat->addWidget(label_91, 2, 0, 1, 1);

        pbResetAIURL = new QPushButton(groupBox_AIChat);
        pbResetAIURL->setObjectName(QString::fromUtf8("pbResetAIURL"));

        gl_AIChat->addWidget(pbResetAIURL, 2, 4, 1, 1);

        cbAIUseTools = new QCheckBox(groupBox_AIChat);
        cbAIUseTools->setObjectName(QString::fromUtf8("cbAIUseTools"));

        gl_AIChat->addWidget(cbAIUseTools, 4, 3, 1, 1);


        verticalLayout_9->addWidget(groupBox_AIChat);

        groupBox_14 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        gridLayout_9 = new QGridLayout(groupBox_14);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        lineEditGrammarLTPath = new QLineEdit(groupBox_14);
        lineEditGrammarLTPath->setObjectName(QString::fromUtf8("lineEditGrammarLTPath"));

        gridLayout_9->addWidget(lineEditGrammarLTPath, 7, 1, 1, 1);

        label_45 = new QLabel(groupBox_14);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_9->addWidget(label_45, 7, 0, 1, 1);

        checkBoxGrammarLTAutorun = new QCheckBox(groupBox_14);
        checkBoxGrammarLTAutorun->setObjectName(QString::fromUtf8("checkBoxGrammarLTAutorun"));

        gridLayout_9->addWidget(checkBoxGrammarLTAutorun, 5, 0, 1, 4);

        label_44 = new QLabel(groupBox_14);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_9->addWidget(label_44, 1, 0, 1, 1);

        lineEditGrammarLTIgnoredRules = new QLineEdit(groupBox_14);
        lineEditGrammarLTIgnoredRules->setObjectName(QString::fromUtf8("lineEditGrammarLTIgnoredRules"));

        gridLayout_9->addWidget(lineEditGrammarLTIgnoredRules, 3, 1, 1, 3);

        pushButtonGrammarLTPath = new QPushButton(groupBox_14);
        pushButtonGrammarLTPath->setObjectName(QString::fromUtf8("pushButtonGrammarLTPath"));
        sizePolicy10.setHeightForWidth(pushButtonGrammarLTPath->sizePolicy().hasHeightForWidth());
        pushButtonGrammarLTPath->setSizePolicy(sizePolicy10);
        pushButtonGrammarLTPath->setIcon(icon);

        gridLayout_9->addWidget(pushButtonGrammarLTPath, 7, 3, 1, 1);

        label_46 = new QLabel(groupBox_14);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_9->addWidget(label_46, 3, 0, 1, 1);

        lineEditGrammarSpecialRules1 = new QLineEdit(groupBox_14);
        lineEditGrammarSpecialRules1->setObjectName(QString::fromUtf8("lineEditGrammarSpecialRules1"));
        lineEditGrammarSpecialRules1->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(lineEditGrammarSpecialRules1, 9, 1, 1, 3);

        lineEditGrammarSpecialRules2 = new QLineEdit(groupBox_14);
        lineEditGrammarSpecialRules2->setObjectName(QString::fromUtf8("lineEditGrammarSpecialRules2"));
        lineEditGrammarSpecialRules2->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(lineEditGrammarSpecialRules2, 10, 1, 1, 3);

        lineEditGrammarSpecialRules4 = new QLineEdit(groupBox_14);
        lineEditGrammarSpecialRules4->setObjectName(QString::fromUtf8("lineEditGrammarSpecialRules4"));
        lineEditGrammarSpecialRules4->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(lineEditGrammarSpecialRules4, 12, 1, 1, 3);

        label_52 = new QLabel(groupBox_14);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(label_52, 11, 0, 1, 1);

        label_50 = new QLabel(groupBox_14);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(label_50, 10, 0, 1, 1);

        lineEditGrammarSpecialRules3 = new QLineEdit(groupBox_14);
        lineEditGrammarSpecialRules3->setObjectName(QString::fromUtf8("lineEditGrammarSpecialRules3"));
        lineEditGrammarSpecialRules3->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(lineEditGrammarSpecialRules3, 11, 1, 1, 3);

        label_51 = new QLabel(groupBox_14);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(label_51, 9, 0, 1, 1);

        label_78 = new QLabel(groupBox_14);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_9->addWidget(label_78, 0, 0, 1, 1);

        label_53 = new QLabel(groupBox_14);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setProperty("advancedOption", QVariant(true));

        gridLayout_9->addWidget(label_53, 12, 0, 1, 1);

        label_79 = new QLabel(groupBox_14);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_9->addWidget(label_79, 0, 1, 1, 3);

        lineEditGrammarLTJava = new QLineEdit(groupBox_14);
        lineEditGrammarLTJava->setObjectName(QString::fromUtf8("lineEditGrammarLTJava"));

        gridLayout_9->addWidget(lineEditGrammarLTJava, 6, 1, 1, 1);

        label_49 = new QLabel(groupBox_14);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_9->addWidget(label_49, 6, 0, 1, 1);

        label_81 = new QLabel(groupBox_14);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        gridLayout_9->addWidget(label_81, 8, 0, 1, 1);

        pushButtonGrammarLTJava = new QPushButton(groupBox_14);
        pushButtonGrammarLTJava->setObjectName(QString::fromUtf8("pushButtonGrammarLTJava"));
        sizePolicy10.setHeightForWidth(pushButtonGrammarLTJava->sizePolicy().hasHeightForWidth());
        pushButtonGrammarLTJava->setSizePolicy(sizePolicy10);
        pushButtonGrammarLTJava->setIcon(icon);

        gridLayout_9->addWidget(pushButtonGrammarLTJava, 6, 3, 1, 1);

        pushButtonResetLTURL = new QPushButton(groupBox_14);
        pushButtonResetLTURL->setObjectName(QString::fromUtf8("pushButtonResetLTURL"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images-ng/edit-undo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonResetLTURL->setIcon(icon3);

        gridLayout_9->addWidget(pushButtonResetLTURL, 1, 3, 1, 1);

        lineEditGrammarLTUrl = new QLineEdit(groupBox_14);
        lineEditGrammarLTUrl->setObjectName(QString::fromUtf8("lineEditGrammarLTUrl"));

        gridLayout_9->addWidget(lineEditGrammarLTUrl, 1, 1, 1, 1);

        label_LTURLParams = new QLabel(groupBox_14);
        label_LTURLParams->setObjectName(QString::fromUtf8("label_LTURLParams"));

        gridLayout_9->addWidget(label_LTURLParams, 2, 0, 1, 1);

        lineEditGrammarLTURLParams = new QLineEdit(groupBox_14);
        lineEditGrammarLTURLParams->setObjectName(QString::fromUtf8("lineEditGrammarLTURLParams"));

        gridLayout_9->addWidget(lineEditGrammarLTURLParams, 2, 1, 1, 3);

        lineEditGrammarLTArguments = new QLineEdit(groupBox_14);
        lineEditGrammarLTArguments->setObjectName(QString::fromUtf8("lineEditGrammarLTArguments"));

        gridLayout_9->addWidget(lineEditGrammarLTArguments, 8, 1, 1, 1);

        pushButtonResetLTArgs = new QPushButton(groupBox_14);
        pushButtonResetLTArgs->setObjectName(QString::fromUtf8("pushButtonResetLTArgs"));
        pushButtonResetLTArgs->setIcon(icon3);

        gridLayout_9->addWidget(pushButtonResetLTArgs, 8, 3, 1, 1);


        verticalLayout_9->addWidget(groupBox_14);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_9->addItem(verticalSpacer_4);

        scrollAreaGrammar->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_6->addWidget(scrollAreaGrammar);

        pagesWidget->addWidget(pageGrammar);
        pagePreview = new QWidget();
        pagePreview->setObjectName(QString::fromUtf8("pagePreview"));
        verticalLayout_3 = new QVBoxLayout(pagePreview);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollAreaPreview = new QScrollArea(pagePreview);
        scrollAreaPreview->setObjectName(QString::fromUtf8("scrollAreaPreview"));
        scrollAreaPreview->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaPreview->setWidgetResizable(true);
        scrollAreaPreviewLayout = new QWidget();
        scrollAreaPreviewLayout->setObjectName(QString::fromUtf8("scrollAreaPreviewLayout"));
        scrollAreaPreviewLayout->setGeometry(QRect(0, 0, 1146, 453));
        verticalLayout_13 = new QVBoxLayout(scrollAreaPreviewLayout);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, -1);
        groupBox_5 = new QGroupBox(scrollAreaPreviewLayout);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_5->addWidget(label_31, 1, 0, 1, 1);

        comboBoxDvi2PngMode = new QComboBox(groupBox_5);
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->addItem(QString());
        comboBoxDvi2PngMode->setObjectName(QString::fromUtf8("comboBoxDvi2PngMode"));
        comboBoxDvi2PngMode->setProperty("advancedOption", QVariant(false));

        gridLayout_5->addWidget(comboBoxDvi2PngMode, 1, 1, 1, 1);

        label_32 = new QLabel(groupBox_5);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setProperty("advancedOption", QVariant(false));

        gridLayout_5->addWidget(label_32, 2, 0, 1, 1);

        comboBoxPreviewMode = new QComboBox(groupBox_5);
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->addItem(QString());
        comboBoxPreviewMode->setObjectName(QString::fromUtf8("comboBoxPreviewMode"));
        comboBoxPreviewMode->setProperty("advancedOption", QVariant(false));

        gridLayout_5->addWidget(comboBoxPreviewMode, 2, 1, 1, 1);

        label_75 = new QLabel(groupBox_5);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_5->addWidget(label_75, 3, 0, 1, 1);

        spinBoxSegmentPreviewScalePercent = new QSpinBox(groupBox_5);
        spinBoxSegmentPreviewScalePercent->setObjectName(QString::fromUtf8("spinBoxSegmentPreviewScalePercent"));
        spinBoxSegmentPreviewScalePercent->setSpecialValueText(QString::fromUtf8(""));
        spinBoxSegmentPreviewScalePercent->setMinimum(20);
        spinBoxSegmentPreviewScalePercent->setMaximum(10000);
        spinBoxSegmentPreviewScalePercent->setSingleStep(10);

        gridLayout_5->addWidget(spinBoxSegmentPreviewScalePercent, 3, 1, 1, 1);

        label_35 = new QLabel(groupBox_5);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_5->addWidget(label_35, 4, 0, 1, 1);

        comboBoxAutoPreview = new QComboBox(groupBox_5);
        comboBoxAutoPreview->addItem(QString());
        comboBoxAutoPreview->addItem(QString());
        comboBoxAutoPreview->setObjectName(QString::fromUtf8("comboBoxAutoPreview"));

        gridLayout_5->addWidget(comboBoxAutoPreview, 4, 1, 1, 1);

        label_36 = new QLabel(groupBox_5);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setProperty("advancedOption", QVariant(true));

        gridLayout_5->addWidget(label_36, 5, 0, 1, 1);

        spinBoxAutoPreviewDelay = new QSpinBox(groupBox_5);
        spinBoxAutoPreviewDelay->setObjectName(QString::fromUtf8("spinBoxAutoPreviewDelay"));
        spinBoxAutoPreviewDelay->setMinimum(40);
        spinBoxAutoPreviewDelay->setMaximum(3000);
        spinBoxAutoPreviewDelay->setProperty("advancedOption", QVariant(true));

        gridLayout_5->addWidget(spinBoxAutoPreviewDelay, 5, 1, 1, 1);

        checkBoxReplaceBeamer = new QCheckBox(groupBox_5);
        checkBoxReplaceBeamer->setObjectName(QString::fromUtf8("checkBoxReplaceBeamer"));
        checkBoxReplaceBeamer->setChecked(true);
        checkBoxReplaceBeamer->setProperty("advancedOption", QVariant(true));

        gridLayout_5->addWidget(checkBoxReplaceBeamer, 6, 0, 1, 2);

        checkBoxPrecompilePreamble = new QCheckBox(groupBox_5);
        checkBoxPrecompilePreamble->setObjectName(QString::fromUtf8("checkBoxPrecompilePreamble"));
        checkBoxPrecompilePreamble->setChecked(true);
        checkBoxPrecompilePreamble->setProperty("advancedOption", QVariant(true));

        gridLayout_5->addWidget(checkBoxPrecompilePreamble, 7, 0, 1, 2);

        gridLayout_5->setColumnStretch(1, 1);

        verticalLayout_13->addWidget(groupBox_5);

        verticalSpacer_2 = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_13->addItem(verticalSpacer_2);

        scrollAreaPreview->setWidget(scrollAreaPreviewLayout);

        verticalLayout_3->addWidget(scrollAreaPreview);

        pagesWidget->addWidget(pagePreview);
        pagePDFviewer = new QWidget();
        pagePDFviewer->setObjectName(QString::fromUtf8("pagePDFviewer"));
        verticalLayout_15 = new QVBoxLayout(pagePDFviewer);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        scrollAreaPDFviewer = new QScrollArea(pagePDFviewer);
        scrollAreaPDFviewer->setObjectName(QString::fromUtf8("scrollAreaPDFviewer"));
        scrollAreaPDFviewer->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaPDFviewer->setWidgetResizable(true);
        scrollAreaPDFviewerLayout = new QWidget();
        scrollAreaPDFviewerLayout->setObjectName(QString::fromUtf8("scrollAreaPDFviewerLayout"));
        scrollAreaPDFviewerLayout->setGeometry(QRect(0, 0, 1132, 641));
        verticalLayout_16 = new QVBoxLayout(scrollAreaPDFviewerLayout);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        groupBox_8 = new QGroupBox(scrollAreaPDFviewerLayout);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_4 = new QGridLayout(groupBox_8);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        spinBoxPreviewScale = new QSpinBox(groupBox_8);
        spinBoxPreviewScale->setObjectName(QString::fromUtf8("spinBoxPreviewScale"));
        sizePolicy9.setHeightForWidth(spinBoxPreviewScale->sizePolicy().hasHeightForWidth());
        spinBoxPreviewScale->setSizePolicy(sizePolicy9);
        spinBoxPreviewScale->setSpecialValueText(QString::fromUtf8(""));
        spinBoxPreviewScale->setMinimum(1);
        spinBoxPreviewScale->setMaximum(10000);

        gridLayout_4->addWidget(spinBoxPreviewScale, 3, 1, 1, 1);

        label_29 = new QLabel(groupBox_8);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_4->addWidget(label_29, 3, 0, 1, 1);

        label_69 = new QLabel(groupBox_8);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_69, 16, 0, 1, 1);

        autoRecompileFullDocument = new QCheckBox(groupBox_8);
        autoRecompileFullDocument->setObjectName(QString::fromUtf8("autoRecompileFullDocument"));

        gridLayout_4->addWidget(autoRecompileFullDocument, 19, 0, 1, 2);

        label_18 = new QLabel(groupBox_8);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_18, 15, 0, 1, 1);

        spinBoxPreviewMagnifierSize = new QSpinBox(groupBox_8);
        spinBoxPreviewMagnifierSize->setObjectName(QString::fromUtf8("spinBoxPreviewMagnifierSize"));
        spinBoxPreviewMagnifierSize->setMinimum(50);
        spinBoxPreviewMagnifierSize->setMaximum(10000);
        spinBoxPreviewMagnifierSize->setSingleStep(50);
        spinBoxPreviewMagnifierSize->setValue(300);

        gridLayout_4->addWidget(spinBoxPreviewMagnifierSize, 6, 1, 1, 1);

        spinBoxHighlightDuration = new QSpinBox(groupBox_8);
        spinBoxHighlightDuration->setObjectName(QString::fromUtf8("spinBoxHighlightDuration"));
        spinBoxHighlightDuration->setSuffix(QString::fromUtf8(" ms"));
        spinBoxHighlightDuration->setMaximum(86400000);
        spinBoxHighlightDuration->setValue(2000);
        spinBoxHighlightDuration->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(spinBoxHighlightDuration, 12, 1, 1, 1);

        spinBoxPreviewDPI = new QSpinBox(groupBox_8);
        spinBoxPreviewDPI->setObjectName(QString::fromUtf8("spinBoxPreviewDPI"));
        spinBoxPreviewDPI->setMaximum(600);

        gridLayout_4->addWidget(spinBoxPreviewDPI, 4, 1, 1, 1);

        comboBoxPDFLoadStrategy = new QComboBox(groupBox_8);
        comboBoxPDFLoadStrategy->addItem(QString());
        comboBoxPDFLoadStrategy->addItem(QString());
        comboBoxPDFLoadStrategy->addItem(QString());
        comboBoxPDFLoadStrategy->setObjectName(QString::fromUtf8("comboBoxPDFLoadStrategy"));
        comboBoxPDFLoadStrategy->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(comboBoxPDFLoadStrategy, 16, 1, 1, 1);

        label_66 = new QLabel(groupBox_8);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        label_66->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_66, 12, 0, 1, 1);

        lineEditHighlightColor = new QLineEdit(groupBox_8);
        lineEditHighlightColor->setObjectName(QString::fromUtf8("lineEditHighlightColor"));
        lineEditHighlightColor->setText(QString::fromUtf8("#"));
        lineEditHighlightColor->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(lineEditHighlightColor, 11, 1, 1, 1);

        comboBoxPreviewMagnifierShape = new QComboBox(groupBox_8);
        comboBoxPreviewMagnifierShape->addItem(QString());
        comboBoxPreviewMagnifierShape->addItem(QString());
        comboBoxPreviewMagnifierShape->setObjectName(QString::fromUtf8("comboBoxPreviewMagnifierShape"));

        gridLayout_4->addWidget(comboBoxPreviewMagnifierShape, 5, 1, 1, 1);

        lineEditPreviewSyncFileMask = new QLineEdit(groupBox_8);
        lineEditPreviewSyncFileMask->setObjectName(QString::fromUtf8("lineEditPreviewSyncFileMask"));
        sizePolicy2.setHeightForWidth(lineEditPreviewSyncFileMask->sizePolicy().hasHeightForWidth());
        lineEditPreviewSyncFileMask->setSizePolicy(sizePolicy2);
        lineEditPreviewSyncFileMask->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(lineEditPreviewSyncFileMask, 14, 1, 1, 1);

        label_67 = new QLabel(groupBox_8);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_67, 11, 0, 1, 1);

        lineEditPaperColor = new QLineEdit(groupBox_8);
        lineEditPaperColor->setObjectName(QString::fromUtf8("lineEditPaperColor"));
        lineEditPaperColor->setInputMask(QString::fromUtf8("\\#HHHHHH;_"));
        lineEditPaperColor->setText(QString::fromUtf8("#"));
        lineEditPaperColor->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(lineEditPaperColor, 10, 1, 1, 1);

        labelScreenResolution = new QLabel(groupBox_8);
        labelScreenResolution->setObjectName(QString::fromUtf8("labelScreenResolution"));
        labelScreenResolution->setText(QString::fromUtf8("<ScreenResolution>"));

        gridLayout_4->addWidget(labelScreenResolution, 4, 0, 1, 1);

        HBoxLayout_magnifier = new QHBoxLayout();
        HBoxLayout_magnifier->setObjectName(QString::fromUtf8("HBoxLayout_magnifier"));
        checkBoxPreviewMagnifierBorder = new QCheckBox(groupBox_8);
        checkBoxPreviewMagnifierBorder->setObjectName(QString::fromUtf8("checkBoxPreviewMagnifierBorder"));

        HBoxLayout_magnifier->addWidget(checkBoxPreviewMagnifierBorder);

        checkBoxPreviewMagnifierShadow = new QCheckBox(groupBox_8);
        checkBoxPreviewMagnifierShadow->setObjectName(QString::fromUtf8("checkBoxPreviewMagnifierShadow"));

        HBoxLayout_magnifier->addWidget(checkBoxPreviewMagnifierShadow);

        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HBoxLayout_magnifier->addItem(spacerItem2);


        gridLayout_4->addLayout(HBoxLayout_magnifier, 7, 1, 1, 1);

        comboBoxPreviewScale = new QComboBox(groupBox_8);
        comboBoxPreviewScale->addItem(QString());
        comboBoxPreviewScale->addItem(QString());
        comboBoxPreviewScale->addItem(QString());
        comboBoxPreviewScale->addItem(QString());
        comboBoxPreviewScale->addItem(QString());
        comboBoxPreviewScale->setObjectName(QString::fromUtf8("comboBoxPreviewScale"));

        gridLayout_4->addWidget(comboBoxPreviewScale, 1, 1, 1, 1);

        spinBoxCacheSizeMB = new QSpinBox(groupBox_8);
        spinBoxCacheSizeMB->setObjectName(QString::fromUtf8("spinBoxCacheSizeMB"));
        spinBoxCacheSizeMB->setMinimum(100);
        spinBoxCacheSizeMB->setMaximum(1024);
        spinBoxCacheSizeMB->setSingleStep(100);
        spinBoxCacheSizeMB->setValue(512);
        spinBoxCacheSizeMB->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(spinBoxCacheSizeMB, 15, 1, 1, 1);

        label_34 = new QLabel(groupBox_8);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_34, 14, 0, 1, 1);

        label_84 = new QLabel(groupBox_8);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_84, 10, 0, 1, 1);

        label_76 = new QLabel(groupBox_8);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(label_76, 17, 0, 1, 1);

        label_88 = new QLabel(groupBox_8);
        label_88->setObjectName(QString::fromUtf8("label_88"));

        gridLayout_4->addWidget(label_88, 8, 0, 1, 1);

        label_77 = new QLabel(groupBox_8);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_4->addWidget(label_77, 0, 0, 1, 2);

        checkBoxDisableHorizontalScrollingForFitToTextWidth = new QCheckBox(groupBox_8);
        checkBoxDisableHorizontalScrollingForFitToTextWidth->setObjectName(QString::fromUtf8("checkBoxDisableHorizontalScrollingForFitToTextWidth"));
        checkBoxDisableHorizontalScrollingForFitToTextWidth->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(checkBoxDisableHorizontalScrollingForFitToTextWidth, 2, 1, 1, 1);

        label_28 = new QLabel(groupBox_8);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_4->addWidget(label_28, 1, 0, 1, 1);

        label_26 = new QLabel(groupBox_8);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 5, 0, 1, 1);

        comboBoxPDFRenderBackend = new QComboBox(groupBox_8);
        comboBoxPDFRenderBackend->addItem(QString::fromUtf8("Splash"));
        comboBoxPDFRenderBackend->addItem(QString::fromUtf8("Arthur"));
        comboBoxPDFRenderBackend->setObjectName(QString::fromUtf8("comboBoxPDFRenderBackend"));
        comboBoxPDFRenderBackend->setProperty("advancedOption", QVariant(true));

        gridLayout_4->addWidget(comboBoxPDFRenderBackend, 17, 1, 1, 1);

        label_25 = new QLabel(groupBox_8);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_4->addWidget(label_25, 6, 0, 1, 1);

        autoHideToolbars = new QCheckBox(groupBox_8);
        autoHideToolbars->setObjectName(QString::fromUtf8("autoHideToolbars"));

        gridLayout_4->addWidget(autoHideToolbars, 18, 0, 1, 2);

        label_89 = new QLabel(groupBox_8);
        label_89->setObjectName(QString::fromUtf8("label_89"));

        gridLayout_4->addWidget(label_89, 9, 0, 1, 1);

        spinBoxPreviewLaserPointerSize = new QSpinBox(groupBox_8);
        spinBoxPreviewLaserPointerSize->setObjectName(QString::fromUtf8("spinBoxPreviewLaserPointerSize"));

        gridLayout_4->addWidget(spinBoxPreviewLaserPointerSize, 8, 1, 1, 1);

        lineEditLaserPointerColor = new QLineEdit(groupBox_8);
        lineEditLaserPointerColor->setObjectName(QString::fromUtf8("lineEditLaserPointerColor"));

        gridLayout_4->addWidget(lineEditLaserPointerColor, 9, 1, 1, 1);


        verticalLayout_16->addWidget(groupBox_8);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_16->addItem(verticalSpacer_7);

        scrollAreaPDFviewer->setWidget(scrollAreaPDFviewerLayout);

        verticalLayout_15->addWidget(scrollAreaPDFviewer);

        pagesWidget->addWidget(pagePDFviewer);
        pageSVN = new QWidget();
        pageSVN->setObjectName(QString::fromUtf8("pageSVN"));
        verticalLayout_18 = new QVBoxLayout(pageSVN);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        scrollAreaSVN = new QScrollArea(pageSVN);
        scrollAreaSVN->setObjectName(QString::fromUtf8("scrollAreaSVN"));
        scrollAreaSVN->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaSVN->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 413, 202));
        gridLayout9 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        gridLayout9->setContentsMargins(0, 0, 0, 0);
        groupBox_18 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        vboxLayout7 = new QVBoxLayout(groupBox_18);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        comboBoxUseVCS = new QComboBox(groupBox_18);
        comboBoxUseVCS->addItem(QString());
        comboBoxUseVCS->addItem(QString());
        comboBoxUseVCS->setObjectName(QString::fromUtf8("comboBoxUseVCS"));

        vboxLayout7->addWidget(comboBoxUseVCS);

        comboBoxAutoCheckinLevel = new QComboBox(groupBox_18);
        comboBoxAutoCheckinLevel->addItem(QString());
        comboBoxAutoCheckinLevel->addItem(QString());
        comboBoxAutoCheckinLevel->addItem(QString());
        comboBoxAutoCheckinLevel->setObjectName(QString::fromUtf8("comboBoxAutoCheckinLevel"));

        vboxLayout7->addWidget(comboBoxAutoCheckinLevel);

        cbSVNUndo = new QCheckBox(groupBox_18);
        cbSVNUndo->setObjectName(QString::fromUtf8("cbSVNUndo"));

        vboxLayout7->addWidget(cbSVNUndo);

        cbKeywordSubstitution = new QCheckBox(groupBox_18);
        cbKeywordSubstitution->setObjectName(QString::fromUtf8("cbKeywordSubstitution"));

        vboxLayout7->addWidget(cbKeywordSubstitution);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label_21 = new QLabel(groupBox_18);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        hboxLayout1->addWidget(label_21);

        sbDirSearchDepth = new QSpinBox(groupBox_18);
        sbDirSearchDepth->setObjectName(QString::fromUtf8("sbDirSearchDepth"));
        sizePolicy7.setHeightForWidth(sbDirSearchDepth->sizePolicy().hasHeightForWidth());
        sbDirSearchDepth->setSizePolicy(sizePolicy7);

        hboxLayout1->addWidget(sbDirSearchDepth);


        vboxLayout7->addLayout(hboxLayout1);


        gridLayout9->addWidget(groupBox_18, 0, 0, 1, 1);

        spacerItem3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout9->addItem(spacerItem3, 1, 0, 1, 1);

        scrollAreaSVN->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_18->addWidget(scrollAreaSVN);

        pagesWidget->addWidget(pageSVN);
        pageInternalTerminal = new QWidget();
        pageInternalTerminal->setObjectName(QString::fromUtf8("pageInternalTerminal"));
        gridLayout10 = new QGridLayout(pageInternalTerminal);
        gridLayout10->setSpacing(6);
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        gridLayout10->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(pageInternalTerminal);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout11 = new QGridLayout(groupBox_4);
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        label_86 = new QLabel(groupBox_4);
        label_86->setObjectName(QString::fromUtf8("label_86"));

        gridLayout11->addWidget(label_86, 0, 0, 1, 1);

        comboBoxTerminalColorScheme = new QComboBox(groupBox_4);
        comboBoxTerminalColorScheme->setObjectName(QString::fromUtf8("comboBoxTerminalColorScheme"));
        comboBoxTerminalColorScheme->setEditable(true);

        gridLayout11->addWidget(comboBoxTerminalColorScheme, 0, 1, 1, 2);

        labelFamily_2 = new QLabel(groupBox_4);
        labelFamily_2->setObjectName(QString::fromUtf8("labelFamily_2"));

        gridLayout11->addWidget(labelFamily_2, 1, 0, 1, 1);

        comboBoxTerminalFont = new QComboBox(groupBox_4);
        comboBoxTerminalFont->setObjectName(QString::fromUtf8("comboBoxTerminalFont"));
        comboBoxTerminalFont->setEditable(true);

        gridLayout11->addWidget(comboBoxTerminalFont, 1, 1, 1, 2);

        labelSize_2 = new QLabel(groupBox_4);
        labelSize_2->setObjectName(QString::fromUtf8("labelSize_2"));

        gridLayout11->addWidget(labelSize_2, 2, 0, 1, 1);

        spinBoxTerminalFontSize = new QSpinBox(groupBox_4);
        spinBoxTerminalFontSize->setObjectName(QString::fromUtf8("spinBoxTerminalFontSize"));
        spinBoxTerminalFontSize->setMinimum(1);
        spinBoxTerminalFontSize->setValue(12);

        gridLayout11->addWidget(spinBoxTerminalFontSize, 2, 1, 1, 2);

        labelShell = new QLabel(groupBox_4);
        labelShell->setObjectName(QString::fromUtf8("labelShell"));

        gridLayout11->addWidget(labelShell, 3, 0, 1, 1);

        lineEditTerminalShell = new QLineEdit(groupBox_4);
        lineEditTerminalShell->setObjectName(QString::fromUtf8("lineEditTerminalShell"));

        gridLayout11->addWidget(lineEditTerminalShell, 3, 1, 1, 1);


        gridLayout10->addWidget(groupBox_4, 0, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout10->addItem(verticalSpacer_8, 1, 0, 1, 1);

        pagesWidget->addWidget(pageInternalTerminal);
        pageCollaborativeEdit = new QWidget();
        pageCollaborativeEdit->setObjectName(QString::fromUtf8("pageCollaborativeEdit"));
        gridLayout12 = new QGridLayout(pageCollaborativeEdit);
        gridLayout12->setSpacing(6);
        gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
        gridLayout12->setContentsMargins(0, 0, 0, 0);
        groupBox_collab = new QGroupBox(pageCollaborativeEdit);
        groupBox_collab->setObjectName(QString::fromUtf8("groupBox_collab"));
        gridLayout13 = new QGridLayout(groupBox_collab);
        gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
        label_collabTool = new QLabel(groupBox_collab);
        label_collabTool->setObjectName(QString::fromUtf8("label_collabTool"));

        gridLayout13->addWidget(label_collabTool, 0, 0, 1, 1);

        labelFamily_collabPath = new QLabel(groupBox_collab);
        labelFamily_collabPath->setObjectName(QString::fromUtf8("labelFamily_collabPath"));

        gridLayout13->addWidget(labelFamily_collabPath, 1, 0, 1, 1);

        label_collabFolder = new QLabel(groupBox_collab);
        label_collabFolder->setObjectName(QString::fromUtf8("label_collabFolder"));

        gridLayout13->addWidget(label_collabFolder, 2, 0, 1, 1);

        comboBoxCollaborativeTool = new QComboBox(groupBox_collab);
        comboBoxCollaborativeTool->addItem(QString());
        comboBoxCollaborativeTool->setObjectName(QString::fromUtf8("comboBoxCollaborativeTool"));
        comboBoxCollaborativeTool->setEditable(false);

        gridLayout13->addWidget(comboBoxCollaborativeTool, 0, 2, 1, 1);

        lineEditCollaborativeClientFolder = new QLineEdit(groupBox_collab);
        lineEditCollaborativeClientFolder->setObjectName(QString::fromUtf8("lineEditCollaborativeClientFolder"));

        gridLayout13->addWidget(lineEditCollaborativeClientFolder, 2, 2, 1, 1);

        pbSelectCollaborativeToolPath = new QPushButton(groupBox_collab);
        pbSelectCollaborativeToolPath->setObjectName(QString::fromUtf8("pbSelectCollaborativeToolPath"));
        QIcon icon4(QIcon::fromTheme(QString::fromUtf8("QIcon::ThemeIcon::DocumentOpen")));
        pbSelectCollaborativeToolPath->setIcon(icon4);

        gridLayout13->addWidget(pbSelectCollaborativeToolPath, 1, 3, 1, 1);

        pbSelectClientFolder = new QPushButton(groupBox_collab);
        pbSelectClientFolder->setObjectName(QString::fromUtf8("pbSelectClientFolder"));
        QIcon icon5(QIcon::fromTheme(QString::fromUtf8("QIcon::ThemeIcon::FolderOpen")));
        pbSelectClientFolder->setIcon(icon5);

        gridLayout13->addWidget(pbSelectClientFolder, 2, 3, 1, 1);

        lineEditCollaborativeToolPath = new QLineEdit(groupBox_collab);
        lineEditCollaborativeToolPath->setObjectName(QString::fromUtf8("lineEditCollaborativeToolPath"));
        lineEditCollaborativeToolPath->setProperty("editable", QVariant(true));

        gridLayout13->addWidget(lineEditCollaborativeToolPath, 1, 2, 1, 1);

        lineEditCollaborativeUserName = new QLineEdit(groupBox_collab);
        lineEditCollaborativeUserName->setObjectName(QString::fromUtf8("lineEditCollaborativeUserName"));

        gridLayout13->addWidget(lineEditCollaborativeUserName, 3, 2, 1, 1);

        label_93 = new QLabel(groupBox_collab);
        label_93->setObjectName(QString::fromUtf8("label_93"));

        gridLayout13->addWidget(label_93, 3, 0, 1, 1);


        gridLayout12->addWidget(groupBox_collab, 0, 0, 1, 1);

        verticalSpacer_collab = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout12->addItem(verticalSpacer_collab, 1, 0, 1, 1);

        pagesWidget->addWidget(pageCollaborativeEdit);

        gridLayout->addWidget(pagesWidget, 0, 0, 2, 1);

        mainSplitter->addWidget(rightPart);

        verticalLayout_19->addWidget(mainSplitter);

        gridLayout14 = new QGridLayout();
        gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        hboxLayout2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        checkBoxShowAdvancedOptions = new QCheckBox(ConfigDialog);
        checkBoxShowAdvancedOptions->setObjectName(QString::fromUtf8("checkBoxShowAdvancedOptions"));
        checkBoxShowAdvancedOptions->setChecked(true);

        hboxLayout2->addWidget(checkBoxShowAdvancedOptions);

        spacerItem4 = new QSpacerItem(407, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem4);

        okButton = new QPushButton(ConfigDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout2->addWidget(okButton);

        cancelButton = new QPushButton(ConfigDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout2->addWidget(cancelButton);


        gridLayout14->addLayout(hboxLayout2, 2, 0, 1, 2);


        verticalLayout_19->addLayout(gridLayout14);

        QWidget::setTabOrder(scrollAreaGeneral, comboBoxInterfaceStyle);
        QWidget::setTabOrder(comboBoxInterfaceStyle, comboBoxInterfaceModernStyle);
        QWidget::setTabOrder(comboBoxInterfaceModernStyle, checkBoxUseTexmakerPalette);
        QWidget::setTabOrder(checkBoxUseTexmakerPalette, checkBoxUseSystemTheme);
        QWidget::setTabOrder(checkBoxUseSystemTheme, comboBoxInterfaceFont);
        QWidget::setTabOrder(comboBoxInterfaceFont, spinBoxInterfaceFontSize);
        QWidget::setTabOrder(spinBoxInterfaceFontSize, comboBoxLanguage);
        QWidget::setTabOrder(comboBoxLanguage, spinBoxMaxRecentFiles);
        QWidget::setTabOrder(spinBoxMaxRecentFiles, spinBoxMaxRecentProjects);
        QWidget::setTabOrder(spinBoxMaxRecentProjects, checkBoxShowAdvancedOptions);
        QWidget::setTabOrder(checkBoxShowAdvancedOptions, checkBoxRunAfterBibTeXChange);
        QWidget::setTabOrder(checkBoxRunAfterBibTeXChange, comboBoxShowStdout);
        QWidget::setTabOrder(comboBoxShowStdout, shortcutTree);
        QWidget::setTabOrder(shortcutTree, menuTree);
        QWidget::setTabOrder(menuTree, checkBoxShowAllMenus);
        QWidget::setTabOrder(checkBoxShowAllMenus, comboBoxToolbars);
        QWidget::setTabOrder(comboBoxToolbars, listCustomToolBar);
        QWidget::setTabOrder(listCustomToolBar, pbToToolbar);
        QWidget::setTabOrder(pbToToolbar, pbFromToolbar);
        QWidget::setTabOrder(pbFromToolbar, comboBoxActions);
        QWidget::setTabOrder(comboBoxActions, treePossibleToolbarActions);
        QWidget::setTabOrder(treePossibleToolbarActions, comboBoxFont);
        QWidget::setTabOrder(comboBoxFont, spinBoxSize);
        QWidget::setTabOrder(spinBoxSize, comboBoxEncoding);
        QWidget::setTabOrder(comboBoxEncoding, checkBoxFolding);
        QWidget::setTabOrder(checkBoxFolding, comboBoxAutoIndent);
        QWidget::setTabOrder(comboBoxAutoIndent, comboBoxReplaceQuotes);
        QWidget::setTabOrder(comboBoxReplaceQuotes, checkBoxRealTimeCheck);
        QWidget::setTabOrder(checkBoxRealTimeCheck, checkBoxInlineSpellCheck);
        QWidget::setTabOrder(checkBoxInlineSpellCheck, checkBoxInlineGrammarCheck);
        QWidget::setTabOrder(checkBoxInlineGrammarCheck, checkBoxInlineCitationCheck);
        QWidget::setTabOrder(checkBoxInlineCitationCheck, checkBoxInlineReferenceCheck);
        QWidget::setTabOrder(checkBoxInlineReferenceCheck, checkBoxInlineSyntaxCheck);
        QWidget::setTabOrder(checkBoxInlineSyntaxCheck, checkBoxLineState);
        QWidget::setTabOrder(checkBoxLineState, checkBoxCloseSearchReplaceTogether);
        QWidget::setTabOrder(checkBoxCloseSearchReplaceTogether, checkBoxUseLineForSearch);
        QWidget::setTabOrder(checkBoxUseLineForSearch, checkBoxSearchOnlyInSelection);
        QWidget::setTabOrder(checkBoxSearchOnlyInSelection, checkBoxAutoCompleteParens);
        QWidget::setTabOrder(checkBoxAutoCompleteParens, checkBoxMouseWheelZoom);
        QWidget::setTabOrder(checkBoxMouseWheelZoom, comboBoxLineWrap);
        QWidget::setTabOrder(comboBoxLineWrap, spinBoxWrapLineWidth);
        QWidget::setTabOrder(spinBoxWrapLineWidth, comboBoxAutoSave);
        QWidget::setTabOrder(comboBoxAutoSave, checkBoxHackDisableAccentWorkaround);
        QWidget::setTabOrder(checkBoxHackDisableAccentWorkaround, checkBoxHackAutoRendering);
        QWidget::setTabOrder(checkBoxHackAutoRendering, spinBoxTabRelFontSize);
        QWidget::setTabOrder(spinBoxTabRelFontSize, checkBoxGrammarRepetitionCheck);
        QWidget::setTabOrder(checkBoxGrammarRepetitionCheck, spinBoxGrammarRepetitionDistance);
        QWidget::setTabOrder(spinBoxGrammarRepetitionDistance, spinBoxGrammarLongRangeRepetition);
        QWidget::setTabOrder(spinBoxGrammarLongRangeRepetition, spinBoxGrammarLongRangeRepetitionMinLength);
        QWidget::setTabOrder(spinBoxGrammarLongRangeRepetitionMinLength, checkBoxGrammarBadWordCheck);
        QWidget::setTabOrder(checkBoxGrammarBadWordCheck, lineEditGrammarWordlists);
        QWidget::setTabOrder(lineEditGrammarWordlists, pushButtonGrammarWordlists);
        QWidget::setTabOrder(pushButtonGrammarWordlists, lineEditGrammarLTUrl);
        QWidget::setTabOrder(lineEditGrammarLTUrl, lineEditGrammarLTURLParams);
        QWidget::setTabOrder(lineEditGrammarLTURLParams, lineEditGrammarLTIgnoredRules);
        QWidget::setTabOrder(lineEditGrammarLTIgnoredRules, checkBoxGrammarLTAutorun);
        QWidget::setTabOrder(checkBoxGrammarLTAutorun, lineEditGrammarLTPath);
        QWidget::setTabOrder(lineEditGrammarLTPath, pushButtonGrammarLTPath);
        QWidget::setTabOrder(pushButtonGrammarLTPath, lineEditGrammarSpecialRules1);
        QWidget::setTabOrder(lineEditGrammarSpecialRules1, lineEditGrammarSpecialRules2);
        QWidget::setTabOrder(lineEditGrammarSpecialRules2, lineEditGrammarSpecialRules3);
        QWidget::setTabOrder(lineEditGrammarSpecialRules3, lineEditGrammarSpecialRules4);
        QWidget::setTabOrder(lineEditGrammarSpecialRules4, comboBoxDvi2PngMode);
        QWidget::setTabOrder(comboBoxDvi2PngMode, comboBoxPreviewMode);
        QWidget::setTabOrder(comboBoxPreviewMode, comboBoxAutoPreview);
        QWidget::setTabOrder(comboBoxAutoPreview, spinBoxAutoPreviewDelay);
        QWidget::setTabOrder(spinBoxAutoPreviewDelay, checkBoxReplaceBeamer);
        QWidget::setTabOrder(checkBoxReplaceBeamer, checkBoxPrecompilePreamble);
        QWidget::setTabOrder(checkBoxPrecompilePreamble, cbSVNUndo);
        QWidget::setTabOrder(cbSVNUndo, cbKeywordSubstitution);
        QWidget::setTabOrder(cbKeywordSubstitution, sbDirSearchDepth);
        QWidget::setTabOrder(sbDirSearchDepth, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(ConfigDialog);
        QObject::connect(okButton, SIGNAL(clicked()), ConfigDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ConfigDialog, SLOT(reject()));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlineSpellCheck, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlineCitationCheck, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlineReferenceCheck, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlineSyntaxCheck, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxHackAutoRendering, SIGNAL(toggled(bool)), checkBoxHackDisableFixedPitch, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxHackAutoRendering, SIGNAL(toggled(bool)), checkBoxHackDisableWidthCache, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxHackAutoRendering, SIGNAL(toggled(bool)), checkBoxHackDisableLineCache, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxHackAutoRendering, SIGNAL(toggled(bool)), comboBoxHackRenderMode, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlineGrammarCheck, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxAutoUpdateCheck, SIGNAL(toggled(bool)), spinBoxAutoUpdateCheckIntervalDays, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxHackAutoRendering, SIGNAL(toggled(bool)), labelRenderMode, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxRealTimeCheck, SIGNAL(toggled(bool)), checkBoxInlinePackageCheck, SLOT(setEnabled(bool)));

        contentsWidget->setCurrentRow(-1);
        pagesWidget->setCurrentIndex(10);
        comboBoxPDFLoadStrategy->setCurrentIndex(2);
        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QCoreApplication::translate("ConfigDialog", "Configure TeXstudio", nullptr));
        lineEditMetaFilter->setText(QString());
        groupBox_Appearance->setTitle(QCoreApplication::translate("ConfigDialog", "Appearance", nullptr));
        label_14->setText(QCoreApplication::translate("ConfigDialog", "Color Scheme:", nullptr));
        label_3->setText(QCoreApplication::translate("ConfigDialog", "Style:", nullptr));
        label_9->setText(QCoreApplication::translate("ConfigDialog", "Language:", nullptr));
        label_5->setText(QCoreApplication::translate("ConfigDialog", "Font:", nullptr));
        comboBoxInterfaceModernStyle->setItemText(0, QCoreApplication::translate("ConfigDialog", "Classic", nullptr));
        comboBoxInterfaceModernStyle->setItemText(1, QCoreApplication::translate("ConfigDialog", "Modern", nullptr));
        comboBoxInterfaceModernStyle->setItemText(2, QCoreApplication::translate("ConfigDialog", "Modern - dark", nullptr));

        label_7->setText(QCoreApplication::translate("ConfigDialog", "Font Size:", nullptr));
        checkBoxUseTexmakerPalette->setText(QCoreApplication::translate("ConfigDialog", "Ignore Most System Colors", nullptr));
        checkBoxUseSystemTheme->setText(QCoreApplication::translate("ConfigDialog", "Use System Theme Icons", nullptr));
        label_27->setText(QCoreApplication::translate("ConfigDialog", "Icon Theme:", nullptr));
        comboBoxInterfaceIconTheme->setItemText(0, QCoreApplication::translate("ConfigDialog", "Colibre", nullptr));
        comboBoxInterfaceIconTheme->setItemText(1, QCoreApplication::translate("ConfigDialog", "Oxygen Modern", nullptr));
        comboBoxInterfaceIconTheme->setItemText(2, QCoreApplication::translate("ConfigDialog", "Oxygen Classic", nullptr));

        groupBox_Files->setTitle(QCoreApplication::translate("ConfigDialog", "Files", nullptr));
        label_10->setText(QCoreApplication::translate("ConfigDialog", "Max. Recent Root Documents:", nullptr));
        checkBoxRememberFileFilter->setText(QCoreApplication::translate("ConfigDialog", "Remember selected file filter in open/save dialog ", nullptr));
        label_8->setText(QCoreApplication::translate("ConfigDialog", "Max. Recent Documents:", nullptr));
        checkBoxUseNativeFileDialog->setText(QCoreApplication::translate("ConfigDialog", "Use system file dialogs", nullptr));
        checkBoxParseRootDoc->setText(QCoreApplication::translate("ConfigDialog", "Always Show Structure of Root Document", nullptr));
        checkBoxMRUDocumentChooser->setText(QCoreApplication::translate("ConfigDialog", "MRU Document Chooser", nullptr));
        groupBox_Session->setTitle(QCoreApplication::translate("ConfigDialog", "Session", nullptr));
        checkBoxRestoreSession->setText(QCoreApplication::translate("ConfigDialog", "Restore Previous Session at Startup", nullptr));
        checkBoxSessionStoreRelativePaths->setText(QCoreApplication::translate("ConfigDialog", "Store relative paths", nullptr));
        groupBox_Startup->setTitle(QCoreApplication::translate("ConfigDialog", "Startup", nullptr));
        checkBoxCheckLatexConfiguration->setText(QCoreApplication::translate("ConfigDialog", "Check LaTeX Configuration", nullptr));
        groupBox_Update->setTitle(QCoreApplication::translate("ConfigDialog", "Update", nullptr));
        comboBoxUpdateLevel->setItemText(0, QCoreApplication::translate("ConfigDialog", "Stable Releases", nullptr));
        comboBoxUpdateLevel->setItemText(1, QCoreApplication::translate("ConfigDialog", "Release Candidates", nullptr));
        comboBoxUpdateLevel->setItemText(2, QCoreApplication::translate("ConfigDialog", "Development Versions", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxUpdateLevel->setToolTip(QCoreApplication::translate("ConfigDialog", "Defines the kinds of update notifications you will receive:\n"
"- Stable Releases: Choose this if stability is most important to you.\n"
"- Release Candidates: Are close to a future release in terms of features and stability. Choose this to get previews of future releases and help us by testing the version before it's been published as an official release. (Stable releases are notified as well)\n"
"- Development Versions: Contain the latest features, but might be unstable. (Stable releases and release candidates are notified as well).", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonUpdateCheckNow->setText(QCoreApplication::translate("ConfigDialog", "Check Now", nullptr));
        label_56->setText(QCoreApplication::translate("ConfigDialog", "Last Checked:", nullptr));
        spinBoxAutoUpdateCheckIntervalDays->setSuffix(QCoreApplication::translate("ConfigDialog", " days", nullptr));
        checkBoxAutoUpdateCheck->setText(QCoreApplication::translate("ConfigDialog", "Automatically check every", nullptr));
        label_74->setText(QCoreApplication::translate("ConfigDialog", "Update Level:", nullptr));
        groupBoxCommands->setTitle(QCoreApplication::translate("ConfigDialog", "Commands (%: filename without extension - @: line number - ?: extended filename options)", nullptr));
        label_15->setText(QCoreApplication::translate("ConfigDialog", "<span style=\" font-weight:600; text-decoration: underline;\">Special chars</span>", nullptr));
        label_4->setText(QCoreApplication::translate("ConfigDialog", "<b>%</b>: filename without extension; <b>@</b>: line number; <b>?[selector][pathname parts][terminating char]</b>: formated filename", nullptr));
        label_17->setText(QCoreApplication::translate("ConfigDialog", "<i>File selector (Optional. If present include the terminating colon):</i> If no selector then select root file. <b>c:</b> select current file, <b>p{ext}:</b> Find a file with same basename as root file and extension <b>ext</b>. Search is done in root file directory and additional PDF directories.<br /><i>Pathname parts:</i> a combination of <b>a</b>: absolute path, <b>m</b>: basefile name without extension,<b>e</b>: extension, <b>r</b>: path relative to root, <b>*</b>: all files matching the following pattern<br/><i>Terminating chars:</i><b>)</b>: ends selector. The following chars end the selector and have additional meaning<br/><b>&quot;</b>: enclose in double-quotes, <b>.</b> (dot) add a point at the end, (space): add a space at the end<br/><i>Examples:</i><b>?ame&quot;</b>: complete absolute filename enclosed in double-quotes, <b>?e)</b> just the extension without leading dot (e.g. tex), <br/><b>?m&quot;</b> double-quoted filename without extension (identical to <b>%</b>), <b>?me</b> filename with extensi"
                        "on (e.g. example.tex), <b>?*.aux</b>: all .aux files in the current directory", nullptr));
        label_16->setText(QCoreApplication::translate("ConfigDialog", "<b>%%</b>, <b>@@</b> and <b>?? </b> become: %, @ or ?\n"
"", nullptr));
        groupBoxMetaCommands->setTitle(QCoreApplication::translate("ConfigDialog", "Meta Commands", nullptr));
        groupBoxUserCommands->setTitle(QCoreApplication::translate("ConfigDialog", "User Commands", nullptr));
        groupBoxBuildOptions->setTitle(QCoreApplication::translate("ConfigDialog", "Build Options", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxRunAfterBibTeXChange->setToolTip(QCoreApplication::translate("ConfigDialog", "Runs txs:///recompile-bibliography, if bib-files were changed.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxRunAfterBibTeXChange->setText(QCoreApplication::translate("ConfigDialog", "Check and update bibliography before compiling", nullptr));
        checkBoxShowMessagesOnCompile->setText(QCoreApplication::translate("ConfigDialog", "Show messages when starting compiling", nullptr));
        checkBoxSingleInstanceViewer->setText(QCoreApplication::translate("ConfigDialog", "Don't launch a new instance of the viewer if the dvi/ps/pdf file is already opened", nullptr));
        label_37->setText(QCoreApplication::translate("ConfigDialog", "Show stdout:", nullptr));
        comboBoxShowStdout->setItemText(0, QCoreApplication::translate("ConfigDialog", "Never", nullptr));
        comboBoxShowStdout->setItemText(1, QCoreApplication::translate("ConfigDialog", "Only For User Commands", nullptr));
        comboBoxShowStdout->setItemText(2, QCoreApplication::translate("ConfigDialog", "Always (If not redirected > /dev/null)", nullptr));

#if QT_CONFIG(tooltip)
        label_38->setToolTip(QCoreApplication::translate("ConfigDialog", "Some LaTeX constructs (e.g. references) need multiple compilation cycles until they are displayed correctly.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_38->setText(QCoreApplication::translate("ConfigDialog", "Maximum Compile Repetitions:", nullptr));
        pushButtonPathPdf->setText(QString());
        label_59->setText(QCoreApplication::translate("ConfigDialog", "Commands ($PATH)", nullptr));
        label_58->setText(QCoreApplication::translate("ConfigDialog", "PDF File", nullptr));
        pushButtonPathLog->setText(QString());
        pushButtonPathCommands->setText(QString());
        label_57->setText(QCoreApplication::translate("ConfigDialog", "Log File", nullptr));
        label_68->setText(QCoreApplication::translate("ConfigDialog", "Additional Search Paths:", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxReplaceEnvironmentVariables->setToolTip(QCoreApplication::translate("ConfigDialog", "Replaces environment variables in commands. The behavior is OS-specific.\n"
"\n"
"Windows:\n"
"Variables are written as: %MYVAR%. They are case-insensitive.\n"
"\n"
"Linux, OS X:\n"
"Variables are written as: $MYVAR. They are case-sensitive.\n"
"", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxReplaceEnvironmentVariables->setText(QCoreApplication::translate("ConfigDialog", "Replace Environment Variables", nullptr));
        checkBoxShowLogInCaseOfCompileError->setText(QCoreApplication::translate("ConfigDialog", "Show log in case of compile error", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxInterpetCommandDefinitionInMagicComment->setToolTip(QCoreApplication::translate("ConfigDialog", "This allows redefining commands using comments of style <code>%&nbsp;!TeX&nbsp;program</code>, <code>%&nbsp;!TeX&nbsp;TS-program</code> and <code>%&nbsp;!TeX&nbsp;TXS-program</code>. For details see the manual.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxInterpetCommandDefinitionInMagicComment->setText(QCoreApplication::translate("ConfigDialog", "Interpret command definition in magic comments", nullptr));
        label_6->setText(QCoreApplication::translate("ConfigDialog", "Shortcuts", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = shortcutTree->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ConfigDialog", "4", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ConfigDialog", "3", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ConfigDialog", "2", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ConfigDialog", "1", nullptr));
#if QT_CONFIG(tooltip)
        shortcutTree->setToolTip(QCoreApplication::translate("ConfigDialog", "For editing, double-click on the entries in 'Current Shortcut' or 'Additional Shortcut'.\n"
"Then you can select a new shortcut by one of the following ways:\n"
"(1) select from the dropdown list\n"
"(2) hit the shortcut combination\n"
"(3) type the string of the shortcut", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBox->setToolTip(QCoreApplication::translate("ConfigDialog", "Close Element applies to a fixed list of GUI elements (not all shown here). The first visible element will be closed. With this setting you can exclude some elements from being closed.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("ConfigDialog", "Close Element (Esc)", nullptr));
        checkBoxCloseLogByEsc->setText(QCoreApplication::translate("ConfigDialog", "Close Log-View", nullptr));
        checkBoxCloseEmbeddedViewerByEsc->setText(QCoreApplication::translate("ConfigDialog", "Close Embedded Viewer", nullptr));
        checkBoxCloseFullscreenByEsc->setText(QCoreApplication::translate("ConfigDialog", "Close Full Screen Mode", nullptr));
        checkBoxShowShortcutsInTooltips->setText(QCoreApplication::translate("ConfigDialog", "Show Shortcuts in Tooltips", nullptr));
        label_19->setText(QCoreApplication::translate("ConfigDialog", "Menus", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = menuTree->headerItem();
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("ConfigDialog", "Slot", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("ConfigDialog", "Command", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("ConfigDialog", "Name", nullptr));
#if QT_CONFIG(tooltip)
        menuTree->setToolTip(QCoreApplication::translate("ConfigDialog", "Here the menu items are listed and can be hidden or edited.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBoxShowAllMenus->setToolTip(QCoreApplication::translate("ConfigDialog", "This controls if the list above shows all menu items or only commonly changed ones.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxShowAllMenus->setText(QCoreApplication::translate("ConfigDialog", "Show All", nullptr));
        label_20->setText(QCoreApplication::translate("ConfigDialog", "Toolbar Customization", nullptr));
#if QT_CONFIG(tooltip)
        listCustomToolBar->setToolTip(QCoreApplication::translate("ConfigDialog", "This shows all actions on the currently edited toolbar.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pbToToolbar->setToolTip(QCoreApplication::translate("ConfigDialog", "This adds an action to the toolbar.", nullptr));
#endif // QT_CONFIG(tooltip)
        pbToToolbar->setText(QString());
#if QT_CONFIG(tooltip)
        pbFromToolbar->setToolTip(QCoreApplication::translate("ConfigDialog", "This removes an action from the toolbar.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        comboBoxToolbars->setToolTip(QCoreApplication::translate("ConfigDialog", "Here you can choose a toolbar to modify.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        comboBoxActions->setToolTip(QCoreApplication::translate("ConfigDialog", "Here you can choose a list of commands that can be mapped to the toolbar.", nullptr));
#endif // QT_CONFIG(tooltip)
        QTreeWidgetItem *___qtreewidgetitem2 = treePossibleToolbarActions->headerItem();
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("ConfigDialog", "1", nullptr));
#if QT_CONFIG(tooltip)
        treePossibleToolbarActions->setToolTip(QCoreApplication::translate("ConfigDialog", "This shows available actions to map on a toolbar.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_17->setTitle(QCoreApplication::translate("ConfigDialog", "GUI Scaling", nullptr));
        label_SlidersNote->setText(QCoreApplication::translate("ConfigDialog", "Note: The change of symbols can be monitored live", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSliderSymbol->setToolTip(QCoreApplication::translate("ConfigDialog", "This changes the scaling of the symbol grid (for high resolution displays).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_11->setText(QCoreApplication::translate("ConfigDialog", "Main Toolbar", nullptr));
        tbRevertIcon->setText(QCoreApplication::translate("ConfigDialog", "Reset", nullptr));
        tbRevertCentralIcon->setText(QCoreApplication::translate("ConfigDialog", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSliderCentraIcon->setToolTip(QCoreApplication::translate("ConfigDialog", "This changes the scaling of the vertical toolbars (for high resolution displays).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        horizontalSliderIcon->setToolTip(QCoreApplication::translate("ConfigDialog", "This changes the scaling of the horizontal toolbars (for high resolution displays).", nullptr));
#endif // QT_CONFIG(tooltip)
        tbRevertSymbol->setText(QCoreApplication::translate("ConfigDialog", "Reset", nullptr));
        label_72->setText(QCoreApplication::translate("ConfigDialog", "Symbol Grid", nullptr));
        label_71->setText(QCoreApplication::translate("ConfigDialog", "Secondary Toolbars", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSliderPDF->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>This changes the scaling of the toolbar of the embedded PDF viewer (for high resolution displays).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_87->setText(QCoreApplication::translate("ConfigDialog", "Embedded PDF Toolbar", nullptr));
        tbRevertPDF->setText(QCoreApplication::translate("ConfigDialog", "Reset", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ConfigDialog", "Editor", nullptr));
        checkBoxRealTimeCheck->setText(QCoreApplication::translate("ConfigDialog", "Inline Checking:", nullptr));
        label_33->setText(QCoreApplication::translate("ConfigDialog", "Show Line Numbers:", nullptr));
        comboboxLineNumbers->setItemText(0, QCoreApplication::translate("ConfigDialog", "No Line Numbers", nullptr));
        comboboxLineNumbers->setItemText(1, QCoreApplication::translate("ConfigDialog", "All Line Numbers", nullptr));
        comboboxLineNumbers->setItemText(2, QCoreApplication::translate("ConfigDialog", "Only Important Line Numbers", nullptr));

        checkBoxInlineCheckNonTeXFiles->setText(QCoreApplication::translate("ConfigDialog", "Check non tex files", nullptr));
        checkBoxScanInstalledLatexPackages->setText(QCoreApplication::translate("ConfigDialog", "Scan LaTeX distribution for installed packages", nullptr));
        checkBoxFolding->setText(QCoreApplication::translate("ConfigDialog", "Folding", nullptr));
        checkBoxReplaceIndentTabByWhitespace->setText(QCoreApplication::translate("ConfigDialog", "Replace Indentation Tab by Spaces", nullptr));
        labelFamily->setText(QCoreApplication::translate("ConfigDialog", "Font Family:", nullptr));
        label_39->setText(QCoreApplication::translate("ConfigDialog", "Replace Double Quotes:", nullptr));
        labelEncoding->setText(QCoreApplication::translate("ConfigDialog", "Default Font Encoding:", nullptr));
        label_30->setText(QCoreApplication::translate("ConfigDialog", "Indentation Mode:", nullptr));
        label_65->setText(QCoreApplication::translate("ConfigDialog", "Automatic Encoding Detection:", nullptr));
        checkBoxAutoDetectEncodingFromLatex->setText(QCoreApplication::translate("ConfigDialog", "Analyze LaTeX (% !TeX encoding, inputenc, inputenx)", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAutoDetectEncodingFromChars->setToolTip(QCoreApplication::translate("ConfigDialog", "can only decide between utf16/utf-8 and ISO 8859-1 !", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAutoDetectEncodingFromChars->setText(QCoreApplication::translate("ConfigDialog", "Analyze Characters", nullptr));
        spinBoxLineSpacingPercent->setSuffix(QCoreApplication::translate("ConfigDialog", "%", nullptr));
        labelSize->setText(QCoreApplication::translate("ConfigDialog", "Font Size:", nullptr));
        label_2->setText(QCoreApplication::translate("ConfigDialog", "Line Spacing:", nullptr));
        comboBoxReplaceQuotes->setItemText(0, QCoreApplication::translate("ConfigDialog", "No Replacement", nullptr));
        comboBoxReplaceQuotes->setItemText(1, QCoreApplication::translate("ConfigDialog", "English Quotes:  `` ''", nullptr));
        comboBoxReplaceQuotes->setItemText(2, QCoreApplication::translate("ConfigDialog", "French Quotes:  \"< \">", nullptr));
        comboBoxReplaceQuotes->setItemText(3, QCoreApplication::translate("ConfigDialog", "German Quotes:  \"` \"'", nullptr));
        comboBoxReplaceQuotes->setItemText(4, QCoreApplication::translate("ConfigDialog", "French Quotes (babel): \\og{} \\fg{}", nullptr));
        comboBoxReplaceQuotes->setItemText(5, QCoreApplication::translate("ConfigDialog", "Reverse French Quotes: \"> \"<", nullptr));
        comboBoxReplaceQuotes->setItemText(6, QCoreApplication::translate("ConfigDialog", "Package csquotes: \\enquote{  }", nullptr));
        comboBoxReplaceQuotes->setItemText(7, QCoreApplication::translate("ConfigDialog", "English Quotes (unicode): \342\200\234 \342\200\235", nullptr));
        comboBoxReplaceQuotes->setItemText(8, QCoreApplication::translate("ConfigDialog", "Polish Quotes: ,, ''", nullptr));
        comboBoxReplaceQuotes->setItemText(9, QCoreApplication::translate("ConfigDialog", "Polish Quotes (unicode): \342\200\236 \342\200\235", nullptr));

        checkBoxShowOnlyMonospacedFonts->setText(QCoreApplication::translate("ConfigDialog", "Show Only Monospaced Fonts", nullptr));
        comboBoxAutoIndent->setItemText(0, QCoreApplication::translate("ConfigDialog", "Ignore Indentation", nullptr));
        comboBoxAutoIndent->setItemText(1, QCoreApplication::translate("ConfigDialog", "Keep Indentation", nullptr));
        comboBoxAutoIndent->setItemText(2, QCoreApplication::translate("ConfigDialog", "Indent and Unindent Automatically", nullptr));

        groupBoxInlineChecking->setTitle(QString());
        checkBoxInlineSpellCheck->setText(QCoreApplication::translate("ConfigDialog", "Spelling", nullptr));
        checkBoxInlineGrammarCheck->setText(QCoreApplication::translate("ConfigDialog", "Grammar", nullptr));
        checkBoxInlineCitationCheck->setText(QCoreApplication::translate("ConfigDialog", "Citations", nullptr));
        checkBoxInlineReferenceCheck->setText(QCoreApplication::translate("ConfigDialog", "References", nullptr));
        checkBoxInlineSyntaxCheck->setText(QCoreApplication::translate("ConfigDialog", "Syntax", nullptr));
        checkBoxInlinePackageCheck->setText(QCoreApplication::translate("ConfigDialog", "Package", nullptr));
        checkBoxReplaceTextTabByWhitespace->setText(QCoreApplication::translate("ConfigDialog", "Replace Tab in Text by Spaces", nullptr));
        checkBoxHideGrammarErrorsInNonText->setText(QCoreApplication::translate("ConfigDialog", "Hide grammar errors in non-text environments", nullptr));
        checkBoxHideSpellingErrorsInNonText->setText(QCoreApplication::translate("ConfigDialog", "Hide spelling errors in non-text environments", nullptr));
        checkboxRemoveTrailingWsOnSave->setText(QCoreApplication::translate("ConfigDialog", "Remove Trailing Whitespace on Save", nullptr));
        checkBoxAutoLoad->setText(QCoreApplication::translate("ConfigDialog", "Automatically load included files", nullptr));
        checkBoxUseCache->setText(QCoreApplication::translate("ConfigDialog", "Cache documents for faster reopening", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("ConfigDialog", "Appearance", nullptr));
        checkBoxShowIndentGuides->setText(QCoreApplication::translate("ConfigDialog", "Show Indent Guides", nullptr));
        checkBoxState->setText(QCoreApplication::translate("ConfigDialog", "Show State Panel", nullptr));
        label_22->setText(QCoreApplication::translate("ConfigDialog", "Tab Width:", nullptr));
        checkBoxShowWhitespace->setText(QCoreApplication::translate("ConfigDialog", "Show Whitespace", nullptr));
        checkBoxLineState->setText(QCoreApplication::translate("ConfigDialog", "Show Line Change State", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxBoldCursor->setToolTip(QCoreApplication::translate("ConfigDialog", "Draw cursor as a thick line", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxBoldCursor->setText(QCoreApplication::translate("ConfigDialog", "Bold Cursor", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("ConfigDialog", "Search Panel", nullptr));
        checkBoxCloseSearchReplaceTogether->setText(QCoreApplication::translate("ConfigDialog", "Close search and replace panel together", nullptr));
        checkBoxUseLineForSearch->setText(QCoreApplication::translate("ConfigDialog", "Use single line selection as Search Word", nullptr));
        checkBoxSearchOnlyInSelection->setText(QCoreApplication::translate("ConfigDialog", "Restrict search scope to an existing selection", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("ConfigDialog", "Special options", nullptr));
        checkBoxShowLogMarkersWhenClickingLogEntry->setText(QCoreApplication::translate("ConfigDialog", "Show log markers when clicking log entry", nullptr));
        checkBoxMonitorFilesForExternalChanges->setText(QCoreApplication::translate("ConfigDialog", "Monitor open files for external changes", nullptr));
        checkBoxAutoCompleteParens->setText(QCoreApplication::translate("ConfigDialog", "Auto Complete Parentheses", nullptr));
        checkOverwriteOpeningBracketFollowedByPlaceholder->setText(QCoreApplication::translate("ConfigDialog", "Overwrite Opening Bracket Followed by a Placeholder", nullptr));
        label_70->setText(QCoreApplication::translate("ConfigDialog", "Spellchecking via context menu:", nullptr));
        label_82->setText(QCoreApplication::translate("ConfigDialog", "Triple-Click Selection:", nullptr));
        checkBoxSilentReload->setText(QCoreApplication::translate("ConfigDialog", "Silently reload saved files on external changes (discards undo/redo stack)", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxCenterDocumentInEditor->setToolTip(QCoreApplication::translate("ConfigDialog", "This only has an effect if the width of the document is limited by soft or hard line wrapping.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxCenterDocumentInEditor->setText(QCoreApplication::translate("ConfigDialog", "Center Document in Editor", nullptr));
        label_41->setText(QCoreApplication::translate("ConfigDialog", "Line Wrapping:", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxInsertSymbolAsUCS->setToolTip(QCoreApplication::translate("ConfigDialog", "When using Unicode characters in the source code, LaTeX still has\n"
"to render the characters. Since Unicode is not natively supported by LaTeX, you have to include appropriate packages for Unicode characters in your document.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxInsertSymbolAsUCS->setText(QCoreApplication::translate("ConfigDialog", "Insert Symbol as Unicode", nullptr));
        checkBoxAllowDragAndDrop->setText(QCoreApplication::translate("ConfigDialog", "Allow Drag and Drop", nullptr));
        comboBoxContextMenuSpellcheckingEntryLocation->setItemText(0, QCoreApplication::translate("ConfigDialog", "Add Entries Directly To Context  Menu", nullptr));
        comboBoxContextMenuSpellcheckingEntryLocation->setItemText(1, QCoreApplication::translate("ConfigDialog", "Create Dedicated Submenu", nullptr));

        checkBoxImageToolTip->setText(QCoreApplication::translate("ConfigDialog", "Show image tooltip on image files", nullptr));
        comboBoxLineWrap->setItemText(0, QCoreApplication::translate("ConfigDialog", "No Line Wrap", nullptr));
        comboBoxLineWrap->setItemText(1, QCoreApplication::translate("ConfigDialog", "Soft Line Wrap at Window Edge", nullptr));
        comboBoxLineWrap->setItemText(2, QCoreApplication::translate("ConfigDialog", "Soft Line Wrap after max. Characters", nullptr));
        comboBoxLineWrap->setItemText(3, QCoreApplication::translate("ConfigDialog", "Hard Line Wrap after max. Characters", nullptr));

        checkBoxDoubleClickSelectionIncludeLeadingBackslash->setText(QCoreApplication::translate("ConfigDialog", "Double-Click Selection: Include Leading Backslash", nullptr));
        checkBoxTexDocInternal->setText(QCoreApplication::translate("ConfigDialog", "Show help on commands in internal pdf viewer (texdoc)", nullptr));
        comboBoxAutoSave->setItemText(0, QCoreApplication::translate("ConfigDialog", "Never", nullptr));
        comboBoxAutoSave->setItemText(1, QCoreApplication::translate("ConfigDialog", "1 minute", nullptr));
        comboBoxAutoSave->setItemText(2, QCoreApplication::translate("ConfigDialog", "2 minutes", nullptr));
        comboBoxAutoSave->setItemText(3, QCoreApplication::translate("ConfigDialog", "5 minutes", nullptr));
        comboBoxAutoSave->setItemText(4, QCoreApplication::translate("ConfigDialog", "10 minutes", nullptr));
        comboBoxAutoSave->setItemText(5, QCoreApplication::translate("ConfigDialog", "20 minutes", nullptr));
        comboBoxAutoSave->setItemText(6, QCoreApplication::translate("ConfigDialog", "60 minutes", nullptr));

        checkBoxGoToErrorWhenDisplayingLog->setText(QCoreApplication::translate("ConfigDialog", "Go to error when displaying log", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxUseQSaveWrite->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>This uses QSaveFile to prevent losing existing data if the writing operation fails. As a drawback, the current user becomes the owner of the file and extended file attributes are lost. Also, there appear to be problems with this method in Dropbox folders.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxUseQSaveWrite->setText(QCoreApplication::translate("ConfigDialog", "Safe writing of files", nullptr));
        comboBoxTripleClickSelection->setItemText(0, QCoreApplication::translate("ConfigDialog", "Select Word", nullptr));
        comboBoxTripleClickSelection->setItemText(1, QCoreApplication::translate("ConfigDialog", "Select Word or Command", nullptr));
        comboBoxTripleClickSelection->setItemText(2, QCoreApplication::translate("ConfigDialog", "Select Parentheses Content", nullptr));
        comboBoxTripleClickSelection->setItemText(3, QCoreApplication::translate("ConfigDialog", "Select Parentheses", nullptr));
        comboBoxTripleClickSelection->setItemText(4, QCoreApplication::translate("ConfigDialog", "Select Line", nullptr));

        checkBoxVerticalOverScroll->setText(QCoreApplication::translate("ConfigDialog", "Vertical Overscroll (Scroll below end of file)", nullptr));
        label_80->setText(QCoreApplication::translate("ConfigDialog", "Default Log Encoding", nullptr));
        checkBoxSmoothScrolling->setText(QCoreApplication::translate("ConfigDialog", "Smooth Scrolling", nullptr));
        checkBoxToolTipHelp2->setText(QCoreApplication::translate("ConfigDialog", "Show help as tooltip on text in editor", nullptr));
        label_24->setText(QCoreApplication::translate("ConfigDialog", "Auto Save All Files:", nullptr));
#if QT_CONFIG(tooltip)
        label_85->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>External programs (such as Zotero) can push citations into TeXstudio by calling: <span style=\" font-family:'monospace';\">texstudio --insert-cite &quot;citation&quot;</span>.</p><p>If the cursor is not already within a citation command, the &quot;command&quot; given here is used as \\cite-command.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_85->setText(QCoreApplication::translate("ConfigDialog", "Latex Command for pushed citations:", nullptr));
        checkBoxMouseWheelZoom->setText(QCoreApplication::translate("ConfigDialog", "Mouse Wheel Zoom", nullptr));
        checkOverwriteClosingBracketFollowingPlaceholder->setText(QCoreApplication::translate("ConfigDialog", "Overwrite Closing Bracket Following a Placeholder", nullptr));
        checkBoxToolTipPreview->setText(QCoreApplication::translate("ConfigDialog", "Show preview as tooltip on formulas in editor", nullptr));
        label_23->setText(QCoreApplication::translate("ConfigDialog", "Maximal Characters:", nullptr));
        checkBoxEnableRainbowDelimiters->setText(QCoreApplication::translate("ConfigDialog", "Use Rainbow colored braces", nullptr));
        groupBox_16->setTitle(QCoreApplication::translate("ConfigDialog", "Structure Panel", nullptr));
        comboBoxTOCBackgroundColor->setItemText(0, QCoreApplication::translate("ConfigDialog", "No Color Background", nullptr));
        comboBoxTOCBackgroundColor->setItemText(1, QCoreApplication::translate("ConfigDialog", "Green Background", nullptr));
        comboBoxTOCBackgroundColor->setItemText(2, QCoreApplication::translate("ConfigDialog", "Blue Background", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxTOCBackgroundColor->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>The global TOC uses different shades of background color to distinguish different files. The color scheme can be changed here.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBoxMarkStructureElementsBeyondEnd->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>Elements like &quot;\\section&quot; are highlighted with a different background color to show that they will <span style=\" font-weight:600;\">not</span> appear in the document.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxMarkStructureElementsBeyondEnd->setText(QCoreApplication::translate("ConfigDialog", "Mark structure elements beyond \\end{document}", nullptr));
        label_64->setText(QCoreApplication::translate("ConfigDialog", "Reference commands in context menu:", nullptr));
        label_83->setText(QCoreApplication::translate("ConfigDialog", "Regular expression for TODO comment: ", nullptr));
        checkBoxIndentIncludesInStructureTree->setText(QCoreApplication::translate("ConfigDialog", "Keep indentation of includes in structure tree", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxScrollToCurrentPosition->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>The current cursor position is highlighted in the structure view.</p><p>If this option is active, the entry is expanded and scrolled to be visible.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxScrollToCurrentPosition->setText(QCoreApplication::translate("ConfigDialog", "Scroll to current cursor position", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxMarkStructureElementsInAppendix->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>Elements like &quot;\\section&quot; are highlighted with a different background color to show that they will appear as appendix.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxMarkStructureElementsInAppendix->setText(QCoreApplication::translate("ConfigDialog", "Mark structure elements in appendix", nullptr));
        label_90->setText(QCoreApplication::translate("ConfigDialog", "Use color in global TOC:", nullptr));
        groupBoxBibliography->setTitle(QCoreApplication::translate("ConfigDialog", "Bibliography", nullptr));
        label_73->setText(QCoreApplication::translate("ConfigDialog", "bib File Encoding:", nullptr));
        checkBoxParseBibTeX->setText(QCoreApplication::translate("ConfigDialog", "Parse BibTeX", nullptr));
        gbTableAutoformat->setTitle(QCoreApplication::translate("ConfigDialog", "Table Autoformating", nullptr));
        cbTableFormatingOneLinePerCell->setText(QCoreApplication::translate("ConfigDialog", "One Line Per Cell", nullptr));
        cbTableFormatingSpecialCommandPos->setItemText(0, QCoreApplication::translate("ConfigDialog", "Behind Line Break", nullptr));
        cbTableFormatingSpecialCommandPos->setItemText(1, QCoreApplication::translate("ConfigDialog", "Separate Line (No Indent)", nullptr));
        cbTableFormatingSpecialCommandPos->setItemText(2, QCoreApplication::translate("ConfigDialog", "Separate Line (Indented to First Column)", nullptr));

        label_61->setText(QCoreApplication::translate("ConfigDialog", "Special Commands Position:", nullptr));
        label_60->setText(QCoreApplication::translate("ConfigDialog", "Special Commands:", nullptr));
        gbAdditionalSearchPaths->setTitle(QCoreApplication::translate("ConfigDialog", "Additional Search Paths", nullptr));
        label_62->setText(QCoreApplication::translate("ConfigDialog", "Bib Files:", nullptr));
        label_63->setText(QCoreApplication::translate("ConfigDialog", "Image Files:", nullptr));
        pushButtonPathBib->setText(QString());
        pushButtonPathImages->setText(QString());
        groupBox_15->setTitle(QCoreApplication::translate("ConfigDialog", "Bi-Di", nullptr));
        checkBoxAutoLRM->setText(QCoreApplication::translate("ConfigDialog", "Automatically insert LRM characters", nullptr));
        checkBoxVisualColumnMode->setText(QCoreApplication::translate("ConfigDialog", "Visual column cursor mode (i.e. move cursor in direction of arrow keys in rtl-text)", nullptr));
        labelSwitchKeyboardLayout->setText(QCoreApplication::translate("ConfigDialog", "Automatically switch keyboard layout: ", nullptr));
        checkBoxSwitchLanguagesDirection->setText(QCoreApplication::translate("ConfigDialog", "depending on character direction", nullptr));
        checkBoxSwitchLanguagesMath->setText(QCoreApplication::translate("ConfigDialog", "depending on text/math mode", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("ConfigDialog", "Hacks/Workarounds", nullptr));
        checkBoxHackDisableAccentWorkaround->setText(QCoreApplication::translate("ConfigDialog", "Disable work-around on accent typing (Mac OS X only)", nullptr));
        checkBoxHackAutoRendering->setText(QCoreApplication::translate("ConfigDialog", "Try to automatically choose best display options", nullptr));
        comboBoxHackRenderMode->setItemText(0, QCoreApplication::translate("ConfigDialog", "QCE (recommended)", nullptr));
        comboBoxHackRenderMode->setItemText(1, QCoreApplication::translate("ConfigDialog", "Qt", nullptr));
        comboBoxHackRenderMode->setItemText(2, QCoreApplication::translate("ConfigDialog", "Single Letter", nullptr));

        labelRenderMode->setText(QCoreApplication::translate("ConfigDialog", "Render Mode:", nullptr));
        checkBoxHackDisableFixedPitch->setText(QCoreApplication::translate("ConfigDialog", "Disable fixed pitch mode", nullptr));
        checkBoxHackDisableWidthCache->setText(QCoreApplication::translate("ConfigDialog", "Disable cache of character width", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxHackDisableLineCache->setToolTip(QCoreApplication::translate("ConfigDialog", "If the cache of rendered lines is enabled, rendered lines are stored in a cache, so they do not have to be rendered again. Leading to a speed improvement (especially on Mac), at the cost of a higher memory usage.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxHackDisableLineCache->setText(QCoreApplication::translate("ConfigDialog", "Disable cache of rendered lines", nullptr));
        formatConfigBox->setTitle(QCoreApplication::translate("ConfigDialog", "Formats", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ConfigDialog", "Completion", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAutoReplaceCommands->setToolTip(QCoreApplication::translate("ConfigDialog", "Allows in-place substitution of commands. Example:<br>\n"
"<code>\\textbf{foo}</code>\n"
"<ul>\n"
"<li>Put cursor behind \"text\"</li>\n"
"<li>Start completer by Ctrl+Space</li>\n"
"<li>Select <code>\\textrm</code><li>\n"
"<li>The result is <code>\\textrm{foo}</code><li>\n"
"</ul>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAutoReplaceCommands->setText(QCoreApplication::translate("ConfigDialog", "Auto Replace Latex-Commands", nullptr));
        checkBoxUsePlaceholders->setText(QCoreApplication::translate("ConfigDialog", "Insert Arguments", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxToolTipCompletePreview->setToolTip(QCoreApplication::translate("ConfigDialog", "Shows a tooltip with target text for labels/bibitem, previews colors or images", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxToolTipCompletePreview->setText(QCoreApplication::translate("ConfigDialog", "ToolTip-Preview", nullptr));
        checkBoxShowPlaceholders->setText(QCoreApplication::translate("ConfigDialog", "Arguments as Placeholders", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxToolTipHelp->setToolTip(QCoreApplication::translate("ConfigDialog", "Shows a tooltip with a description of the selected completer command", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxToolTipHelp->setText(QCoreApplication::translate("ConfigDialog", "ToolTip-Help", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxCompletion->setToolTip(QCoreApplication::translate("ConfigDialog", "Starts the completer as soon as '\\' is typed. Alternatively the completer can always be started manually by Ctrl+Space.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxCompletion->setText(QCoreApplication::translate("ConfigDialog", "Automatically start completer when typing LaTeX-Commands", nullptr));
#if QT_CONFIG(tooltip)
        label_40->setToolTip(QCoreApplication::translate("ConfigDialog", "Size of the tab bar at the bottom or top of the completer", nullptr));
#endif // QT_CONFIG(tooltip)
        label_40->setText(QCoreApplication::translate("ConfigDialog", "Tab Bar Size", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxTabRelFontSize->setToolTip(QCoreApplication::translate("ConfigDialog", "Size of the command set tabs at the bottom or top of the completer", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxEOWCompletes->setText(QCoreApplication::translate("ConfigDialog", "Complete selected text when non-word character is pressed", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxCompletePrefix->setToolTip(QCoreApplication::translate("ConfigDialog", "If all completer suggestions have the next characters in common, you can use <Tab> to automatically insert them.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxCompletePrefix->setText(QCoreApplication::translate("ConfigDialog", "Auto Complete Common Prefix", nullptr));
        label->setText(QCoreApplication::translate("ConfigDialog", "Preferred Commands Set:", nullptr));
        comboBoxPreferedTab->setItemText(0, QCoreApplication::translate("ConfigDialog", "Typical", nullptr));
        comboBoxPreferedTab->setItemText(1, QCoreApplication::translate("ConfigDialog", "Most Used", nullptr));
        comboBoxPreferedTab->setItemText(2, QCoreApplication::translate("ConfigDialog", "Fuzzy", nullptr));
        comboBoxPreferedTab->setItemText(3, QCoreApplication::translate("ConfigDialog", "All", nullptr));

#if QT_CONFIG(tooltip)
        checkBoxAutoInsertMathDelimiters->setToolTip(QCoreApplication::translate("ConfigDialog", "If a math command is inserted via completion outside any math environment, $$ is inserted automatically.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAutoInsertMathDelimiters->setText(QCoreApplication::translate("ConfigDialog", "Auto Insert Math Delimiters where needed", nullptr));
        checkBoxCompleteUserConstructs->setText(QCoreApplication::translate("ConfigDialog", "Make user constructs from symbols/math commands", nullptr));
#if QT_CONFIG(tooltip)
        label_12->setToolTip(QCoreApplication::translate("ConfigDialog", "TXS tries to automatically load completion files for packages if a\n"
"\\usepackage{} command is found. These automatically included files\n"
"are not shown here. Checking additional packages here is usually not\n"
"necessary. However, if automatic detection fails or you want to include\n"
"specific user completion files, you can enforce their usage by activating\n"
"them here.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_12->setText(QCoreApplication::translate("ConfigDialog", "Permanently active completion files:", nullptr));
#if QT_CONFIG(tooltip)
        leCompletionFilter->setToolTip(QCoreApplication::translate("ConfigDialog", "Filter list below", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        completeListWidget->setToolTip(QCoreApplication::translate("ConfigDialog", "TXS tries to automatically load completion files for packages if a\n"
"\\usepackage{} command is found. These automatically included files\n"
"are not shown here. Checking additional packages here is usually not\n"
"necessary. However, if automatic detection fails or you want to include\n"
"specific user completion files, you can enforce their usage by activating\n"
"them here.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_Dictionaries->setTitle(QCoreApplication::translate("ConfigDialog", "Spell Check", nullptr));
        label_43->setText(QCoreApplication::translate("ConfigDialog", "Default Language:", nullptr));
        pushButtonDictDir->setText(QString());
        label_42->setText(QCoreApplication::translate("ConfigDialog", "Spelling Dictionary Directories:", nullptr));
#if QT_CONFIG(tooltip)
        leDictDir->setToolTip(QCoreApplication::translate("ConfigDialog", "Folders with Hunspell dictionaries separated by semicolon. The special keywords [txs-settings-dir] and [txs-app-dir] will be resolved to the respective directories.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBoxThesaurusFileName->setProperty("dirFilter", QVariant(QCoreApplication::translate("ConfigDialog", "*.dat", nullptr)));
        label_13->setText(QCoreApplication::translate("ConfigDialog", "Thesaurus Database:", nullptr));
        btSelectThesaurusFileName->setText(QString());
        labelGetDic->setText(QCoreApplication::translate("ConfigDialog", "TextLabel", nullptr));
        pushButtonImportDictionary->setText(QCoreApplication::translate("ConfigDialog", "Import Dictionary...", nullptr));
        groupBox_13->setTitle(QCoreApplication::translate("ConfigDialog", "Internal Grammar Check", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxGrammarRepetitionCheck->setToolTip(QCoreApplication::translate("ConfigDialog", "Words repeated within a paragraph will be highlighted.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxGrammarRepetitionCheck->setText(QCoreApplication::translate("ConfigDialog", "Check for Word Repetitions", nullptr));
        label_47->setText(QCoreApplication::translate("ConfigDialog", "Words Between Repetitions:", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxGrammarRepetitionDistance->setToolTip(QCoreApplication::translate("ConfigDialog", "Equal words are marked as repetition if there are no more than this number of words between them.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinBoxGrammarLongRangeRepetition->setToolTip(QCoreApplication::translate("ConfigDialog", "Equal, longer words are marked as long range repetition if there are no more than this number of words between them.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinBoxGrammarLongRangeRepetitionMinLength->setToolTip(QCoreApplication::translate("ConfigDialog", "Only words with have this length are checked for long range repetitions.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_54->setText(QCoreApplication::translate("ConfigDialog", "Long Range Repetitions:", nullptr));
        label_55->setText(QCoreApplication::translate("ConfigDialog", "Min Length of Words with Long Repetition:", nullptr));
        label_48->setText(QCoreApplication::translate("ConfigDialog", "Wordlist Directory:", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxGrammarBadWordCheck->setToolTip(QCoreApplication::translate("ConfigDialog", "Certain informal or weak words will be highlighted.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxGrammarBadWordCheck->setText(QCoreApplication::translate("ConfigDialog", "Check for Bad Words", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarWordlists->setToolTip(QCoreApplication::translate("ConfigDialog", "Directory containing the lists which words are \"bad\" or may be repeated.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGrammarWordlists->setText(QString());
        groupBox_AIChat->setTitle(QCoreApplication::translate("ConfigDialog", "AI chat assistant", nullptr));

#if QT_CONFIG(tooltip)
        cbAIPreferredModel->setToolTip(QCoreApplication::translate("ConfigDialog", "AI model to use for responses. You can type custom model names for any provider.\n"
"Examples:\n"
"\342\200\242 Perplexity: sonar, sonar-pro, sonar-deep-research  \n"
"\342\200\242 Gemini: gemini-2.5-pro, gemini-2.5-flash\n"
"\342\200\242 Claude: claude-opus-4-0, claude-sonnet-4-0	\n"
"\342\200\242 Local: deepseek-r1, llama3.3", nullptr));
#endif // QT_CONFIG(tooltip)
        label_AIProvider->setText(QCoreApplication::translate("ConfigDialog", "AI provider:", nullptr));
        pbRetrieveModels->setText(QCoreApplication::translate("ConfigDialog", "Retrieve list of models", nullptr));
        label_AIAPI->setText(QCoreApplication::translate("ConfigDialog", "API key:", nullptr));
        cbAIProvider->setItemText(0, QCoreApplication::translate("ConfigDialog", "<disable AI>", nullptr));
        cbAIProvider->setItemText(1, QCoreApplication::translate("ConfigDialog", "Mistral AI", nullptr));
        cbAIProvider->setItemText(2, QCoreApplication::translate("ConfigDialog", "OpenAI", nullptr));
        cbAIProvider->setItemText(3, QCoreApplication::translate("ConfigDialog", "Custom Provider (Remote or Local)", nullptr));
        cbAIProvider->setItemText(4, QCoreApplication::translate("ConfigDialog", "Anthropic (Claude)", nullptr));
        cbAIProvider->setItemText(5, QCoreApplication::translate("ConfigDialog", "OpenRouter AI", nullptr));

#if QT_CONFIG(tooltip)
        cbAIRecordConversation->setToolTip(QCoreApplication::translate("ConfigDialog", "Store the conversation with AI provider on disk to allow later retrieval", nullptr));
#endif // QT_CONFIG(tooltip)
        cbAIRecordConversation->setText(QCoreApplication::translate("ConfigDialog", "Record Conversation", nullptr));
        label_AIModel->setText(QCoreApplication::translate("ConfigDialog", "Preferred model:", nullptr));
#if QT_CONFIG(tooltip)
        leAIAPIURL->setToolTip(QCoreApplication::translate("ConfigDialog", "API endpoint URL for custom providers\n"
"Examples:\n"
"\342\200\242 Perplexity: https://api.perplexity.ai/chat/completions\n"
"\342\200\242 Gemini: https://generativelanguage.googleapis.com/v1beta/openai/chat/completions\n"
"\342\200\242 Claude: https://api.anthropic.com/v1/chat/completions\n"
"\342\200\242 Local: http://localhost:8080/v1/chat/completions", nullptr));
#endif // QT_CONFIG(tooltip)
        label_91->setText(QCoreApplication::translate("ConfigDialog", "API URL:", nullptr));
        pbResetAIURL->setText(QCoreApplication::translate("ConfigDialog", "Default", nullptr));
#if QT_CONFIG(tooltip)
        cbAIUseTools->setToolTip(QCoreApplication::translate("ConfigDialog", "The LLM receives a list of available functions from TeXstudio.\n"
"It can ask the program to run those functions during an ai query to retrieve more information on the document.\n"
"This may lead to unwanted data transfer to the AI provider.\n"
"", nullptr));
#endif // QT_CONFIG(tooltip)
        cbAIUseTools->setText(QCoreApplication::translate("ConfigDialog", "AI may call program functions during query", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("ConfigDialog", "LanguageTool", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarLTPath->setToolTip(QCoreApplication::translate("ConfigDialog", "Path containing the LanguageTool java archive.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_45->setText(QCoreApplication::translate("ConfigDialog", "LT Path:", nullptr));
        checkBoxGrammarLTAutorun->setText(QCoreApplication::translate("ConfigDialog", "Start LanguageTool if not running", nullptr));
        label_44->setText(QCoreApplication::translate("ConfigDialog", "Server URL: ", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarLTIgnoredRules->setToolTip(QCoreApplication::translate("ConfigDialog", "Comma separated list of LanguageTool rules which will not be highlighted as errors.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGrammarLTPath->setText(QString());
        label_46->setText(QCoreApplication::translate("ConfigDialog", "Ignored Rules:", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarSpecialRules1->setToolTip(QCoreApplication::translate("ConfigDialog", "Comma separated list of LanguageTool rules which will be highlighted in a special format.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEditGrammarSpecialRules2->setToolTip(QCoreApplication::translate("ConfigDialog", "Comma separated list of LanguageTool rules which will be highlighted in a special format.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEditGrammarSpecialRules4->setToolTip(QCoreApplication::translate("ConfigDialog", "Comma separated list of LanguageTool rules which will be highlighted in a special format.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_52->setText(QCoreApplication::translate("ConfigDialog", "Special Rules 3:", nullptr));
        label_50->setText(QCoreApplication::translate("ConfigDialog", "Special Rules 2:", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarSpecialRules3->setToolTip(QCoreApplication::translate("ConfigDialog", "Comma separated list of LanguageTool rules which will be highlighted in a special format.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_51->setText(QCoreApplication::translate("ConfigDialog", "Special Rules 1:", nullptr));
        label_78->setText(QCoreApplication::translate("ConfigDialog", "Language:", nullptr));
        label_53->setText(QCoreApplication::translate("ConfigDialog", "Special Rules 4:", nullptr));
        label_79->setText(QCoreApplication::translate("ConfigDialog", "Will be inferred from the language of the spell checker used in the document.", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarLTJava->setToolTip(QCoreApplication::translate("ConfigDialog", "Java executable, used to start LanguageTool, if it is not running.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_49->setText(QCoreApplication::translate("ConfigDialog", "Java:", nullptr));
#if QT_CONFIG(tooltip)
        label_81->setToolTip(QCoreApplication::translate("ConfigDialog", "Arguments passed when starting LanguageTool. This option only has an effect if LanguageTool is started from TeXstudio (i.e. not for an already running server).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_81->setText(QCoreApplication::translate("ConfigDialog", "LT Arguments:", nullptr));
        pushButtonGrammarLTJava->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonResetLTURL->setToolTip(QCoreApplication::translate("ConfigDialog", "Restore Default", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonResetLTURL->setText(QString());
#if QT_CONFIG(tooltip)
        lineEditGrammarLTUrl->setToolTip(QCoreApplication::translate("ConfigDialog", "Url to connect to LanguageTool. ", nullptr));
#endif // QT_CONFIG(tooltip)
        label_LTURLParams->setText(QCoreApplication::translate("ConfigDialog", "URL Parameters: ", nullptr));
#if QT_CONFIG(tooltip)
        lineEditGrammarLTURLParams->setToolTip(QCoreApplication::translate("ConfigDialog", "Additional URL parameters to send with LanguageTool requests. For example: level=picky&enabledRules=CUSTOM_RULE", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lineEditGrammarLTArguments->setToolTip(QCoreApplication::translate("ConfigDialog", "Arguments passed when starting LanguageTool. This option only has an effect if LanguageTool is started from TeXstudio (i.e. not for an already running server).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButtonResetLTArgs->setToolTip(QCoreApplication::translate("ConfigDialog", "Restore Default", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonResetLTArgs->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("ConfigDialog", "Preview", nullptr));
        label_31->setText(QCoreApplication::translate("ConfigDialog", "Command:", nullptr));
        comboBoxDvi2PngMode->setItemText(0, QCoreApplication::translate("ConfigDialog", "Preview with default compiler", nullptr));
        comboBoxDvi2PngMode->setItemText(1, QCoreApplication::translate("ConfigDialog", "Preview with dvipng", nullptr));
        comboBoxDvi2PngMode->setItemText(2, QCoreApplication::translate("ConfigDialog", "Preview with dvipng --follow (parallel)", nullptr));
        comboBoxDvi2PngMode->setItemText(3, QCoreApplication::translate("ConfigDialog", "Preview with dvips/ghostscript", nullptr));
        comboBoxDvi2PngMode->setItemText(4, QCoreApplication::translate("ConfigDialog", "Preview with pdflatex", nullptr));
        comboBoxDvi2PngMode->setItemText(5, QCoreApplication::translate("ConfigDialog", "Preview with lualatex", nullptr));
        comboBoxDvi2PngMode->setItemText(6, QCoreApplication::translate("ConfigDialog", "Preview with xelatex", nullptr));

        label_32->setText(QCoreApplication::translate("ConfigDialog", "Display Mode:", nullptr));
        comboBoxPreviewMode->setItemText(0, QCoreApplication::translate("ConfigDialog", "Show preview as tooltip if panel is hidden", nullptr));
        comboBoxPreviewMode->setItemText(1, QCoreApplication::translate("ConfigDialog", "Always show preview in preview panel", nullptr));
        comboBoxPreviewMode->setItemText(2, QCoreApplication::translate("ConfigDialog", "Always show preview as tool tip", nullptr));
        comboBoxPreviewMode->setItemText(3, QCoreApplication::translate("ConfigDialog", "Always show both", nullptr));
        comboBoxPreviewMode->setItemText(4, QCoreApplication::translate("ConfigDialog", "Inline", nullptr));
        comboBoxPreviewMode->setItemText(5, QCoreApplication::translate("ConfigDialog", "Show in embedded viewer", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxPreviewMode->setToolTip(QCoreApplication::translate("ConfigDialog", "When the mode is changed, the preview on formulas is displayed accordingly (but for Inline it's still a tooltip).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_75->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_75->setText(QCoreApplication::translate("ConfigDialog", "Scaling:", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxSegmentPreviewScalePercent->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        spinBoxSegmentPreviewScalePercent->setSuffix(QCoreApplication::translate("ConfigDialog", "%", nullptr));
#if QT_CONFIG(tooltip)
        label_35->setToolTip(QCoreApplication::translate("ConfigDialog", "Update the preview on text change", nullptr));
#endif // QT_CONFIG(tooltip)
        label_35->setText(QCoreApplication::translate("ConfigDialog", "Auto Update:", nullptr));
        comboBoxAutoPreview->setItemText(0, QCoreApplication::translate("ConfigDialog", "Never", nullptr));
        comboBoxAutoPreview->setItemText(1, QCoreApplication::translate("ConfigDialog", "Previously previewed text", nullptr));

        label_36->setText(QCoreApplication::translate("ConfigDialog", "Auto Update Delay:", nullptr));
        spinBoxAutoPreviewDelay->setSuffix(QCoreApplication::translate("ConfigDialog", " ms", nullptr));
        checkBoxReplaceBeamer->setText(QCoreApplication::translate("ConfigDialog", "Replace beamer class by article", nullptr));
        checkBoxPrecompilePreamble->setText(QCoreApplication::translate("ConfigDialog", "Precompile Preamble", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("ConfigDialog", "Internal PDF Viewer", nullptr));
        spinBoxPreviewScale->setSuffix(QCoreApplication::translate("ConfigDialog", "%", nullptr));
        label_29->setText(QCoreApplication::translate("ConfigDialog", "Scaling:", nullptr));
        label_69->setText(QCoreApplication::translate("ConfigDialog", "Load Strategy:", nullptr));
        autoRecompileFullDocument->setText(QCoreApplication::translate("ConfigDialog", "Auto-recompile document on changes", nullptr));
        label_18->setText(QCoreApplication::translate("ConfigDialog", "Cache Size:", nullptr));
        spinBoxPreviewMagnifierSize->setSuffix(QCoreApplication::translate("ConfigDialog", " px", nullptr));
        spinBoxPreviewMagnifierSize->setPrefix(QString());
        spinBoxHighlightDuration->setSpecialValueText(QCoreApplication::translate("ConfigDialog", "Infinite", nullptr));
        spinBoxPreviewDPI->setSuffix(QCoreApplication::translate("ConfigDialog", " dpi", nullptr));
        comboBoxPDFLoadStrategy->setItemText(0, QCoreApplication::translate("ConfigDialog", "Buffered", nullptr));
        comboBoxPDFLoadStrategy->setItemText(1, QCoreApplication::translate("ConfigDialog", "Direct", nullptr));
        comboBoxPDFLoadStrategy->setItemText(2, QCoreApplication::translate("ConfigDialog", "Hybrid", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxPDFLoadStrategy->setToolTip(QCoreApplication::translate("ConfigDialog", "<html><head/><body><p>Defines how a PDF is loaded:</p><p><b>Buffered:</b> Load the file into a buffer and check for completeness. Then pass the data on to poppler. This was primarily introduced as a speedup for old poppler versions (&lt;0.24) which were not thread-safe. It has been reported that poppler may crash when loading large buffers. Therefore this option is deprecated.</p><p><b>Direct:</b> Use native poppler file loading. This is fastest, but does not allow checking for incomplete files.</p><p><b>Hybrid (recommended):</b> First load file into buffer and check for completeness. Use that buffer for small documents (&lt; 50MB). Large files are loaded using native poppler file loading. This combines file-checking while preventing problems with large PDF files.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_66->setText(QCoreApplication::translate("ConfigDialog", "Highlight Duration", nullptr));
#if QT_CONFIG(tooltip)
        lineEditHighlightColor->setToolTip(QCoreApplication::translate("ConfigDialog", "Specify as hexadecimal RGBA value. Note: The transparency is required because the highlighting is drawn on top of the text due to technical limitations.", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEditHighlightColor->setInputMask(QCoreApplication::translate("ConfigDialog", "\\#HHHHHHHH;_", nullptr));
        comboBoxPreviewMagnifierShape->setItemText(0, QCoreApplication::translate("ConfigDialog", "Rectangle", nullptr));
        comboBoxPreviewMagnifierShape->setItemText(1, QCoreApplication::translate("ConfigDialog", "Circle", nullptr));

        label_67->setText(QCoreApplication::translate("ConfigDialog", "Highlight Color", nullptr));
#if QT_CONFIG(tooltip)
        lineEditPaperColor->setToolTip(QCoreApplication::translate("ConfigDialog", "Default background color. Specify as hexadecimal RGB value. Note: This will only affect PDFs loaded after the change of the option. The paper color of already open PDFs is not modified.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxPreviewMagnifierBorder->setText(QCoreApplication::translate("ConfigDialog", "Border", nullptr));
        checkBoxPreviewMagnifierShadow->setText(QCoreApplication::translate("ConfigDialog", "Shadow", nullptr));
        comboBoxPreviewScale->setItemText(0, QCoreApplication::translate("ConfigDialog", "Original Size", nullptr));
        comboBoxPreviewScale->setItemText(1, QCoreApplication::translate("ConfigDialog", "Fit to Window Width", nullptr));
        comboBoxPreviewScale->setItemText(2, QCoreApplication::translate("ConfigDialog", "Fit to Window Size", nullptr));
        comboBoxPreviewScale->setItemText(3, QCoreApplication::translate("ConfigDialog", "Scaled Size", nullptr));
        comboBoxPreviewScale->setItemText(4, QCoreApplication::translate("ConfigDialog", "Fit to Text Width", nullptr));

        spinBoxCacheSizeMB->setSuffix(QCoreApplication::translate("ConfigDialog", " MB", nullptr));
        label_34->setText(QCoreApplication::translate("ConfigDialog", "Synchronized Files Types:", nullptr));
        label_84->setText(QCoreApplication::translate("ConfigDialog", "Paper Color", nullptr));
#if QT_CONFIG(tooltip)
        label_76->setToolTip(QCoreApplication::translate("ConfigDialog", "The Render Backend used by the PDF library poppler.\n"
"'Splash' is the default and suitable for most situations.\n"
"If there are rendering issues, you may try the alternative 'Arthur' backend.\n"
"Note: Changing this setting will only affect documents that are opened afterwards.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_76->setText(QCoreApplication::translate("ConfigDialog", "Render Backend:", nullptr));
        label_88->setText(QCoreApplication::translate("ConfigDialog", "Presentation Laser Pointer Size:", nullptr));
        label_77->setText(QCoreApplication::translate("ConfigDialog", "Note: Windowed/embedded mode is configured at Build -> PDF Viewer", nullptr));
        checkBoxDisableHorizontalScrollingForFitToTextWidth->setText(QCoreApplication::translate("ConfigDialog", "Disable horizontal scrolling for \"Fit to Text Width\"", nullptr));
        label_28->setText(QCoreApplication::translate("ConfigDialog", "Scale Option:", nullptr));
        label_26->setText(QCoreApplication::translate("ConfigDialog", "Magnifier Shape:", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxPDFRenderBackend->setToolTip(QCoreApplication::translate("ConfigDialog", "The Render Backend used by the PDF library poppler.\n"
"'Splash' is the default and suitable for most situations.\n"
"If there are rendering issues, you may try the alternative 'Arthur' backend.\n"
"Note: Changing this setting will only affect documents that are opened afterwards.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_25->setText(QCoreApplication::translate("ConfigDialog", "Magnifier Size:", nullptr));
        autoHideToolbars->setText(QCoreApplication::translate("ConfigDialog", "Auto-hide Toolbars in Embedded Mode", nullptr));
        label_89->setText(QCoreApplication::translate("ConfigDialog", "Presentation Laser Pointer Color:", nullptr));
        spinBoxPreviewLaserPointerSize->setSuffix(QCoreApplication::translate("ConfigDialog", " px", nullptr));
        groupBox_18->setTitle(QCoreApplication::translate("ConfigDialog", "SVN/GIT", nullptr));
        comboBoxUseVCS->setItemText(0, QCoreApplication::translate("ConfigDialog", "Use SVN", nullptr));
        comboBoxUseVCS->setItemText(1, QCoreApplication::translate("ConfigDialog", "Use GIT", nullptr));

        comboBoxAutoCheckinLevel->setItemText(0, QCoreApplication::translate("ConfigDialog", "No automatic check-in after save", nullptr));
        comboBoxAutoCheckinLevel->setItemText(1, QCoreApplication::translate("ConfigDialog", "Check-in after File/Save only", nullptr));
        comboBoxAutoCheckinLevel->setItemText(2, QCoreApplication::translate("ConfigDialog", "Check-in after all save operations, i.e. also before compiles.", nullptr));

#if QT_CONFIG(tooltip)
        comboBoxAutoCheckinLevel->setToolTip(QCoreApplication::translate("ConfigDialog", "Select how txs checks in saved files", nullptr));
#endif // QT_CONFIG(tooltip)
        cbSVNUndo->setText(QCoreApplication::translate("ConfigDialog", "Use SVN/GIT revisions to undo before last saved version", nullptr));
#if QT_CONFIG(tooltip)
        cbKeywordSubstitution->setToolTip(QCoreApplication::translate("ConfigDialog", "on svn add executes svn propset svn:keywords \"Date Author Revision HeadURL\"", nullptr));
#endif // QT_CONFIG(tooltip)
        cbKeywordSubstitution->setText(QCoreApplication::translate("ConfigDialog", "Substitute Keywords with Properties (on svn add)", nullptr));
        label_21->setText(QCoreApplication::translate("ConfigDialog", "SVN Directory Search Depth: ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ConfigDialog", "Internal Terminal", nullptr));
        label_86->setText(QCoreApplication::translate("ConfigDialog", "Color Scheme:", nullptr));
        labelFamily_2->setText(QCoreApplication::translate("ConfigDialog", "Font Family:", nullptr));
        labelSize_2->setText(QCoreApplication::translate("ConfigDialog", "Font Size:", nullptr));
        labelShell->setText(QCoreApplication::translate("ConfigDialog", "Shell:", nullptr));
        groupBox_collab->setTitle(QCoreApplication::translate("ConfigDialog", "Collaborative Editing", nullptr));
        label_collabTool->setText(QCoreApplication::translate("ConfigDialog", "Tool:", nullptr));
        labelFamily_collabPath->setText(QCoreApplication::translate("ConfigDialog", "Path:", nullptr));
        label_collabFolder->setText(QCoreApplication::translate("ConfigDialog", "Client folder:", nullptr));
        comboBoxCollaborativeTool->setItemText(0, QCoreApplication::translate("ConfigDialog", "teamtype", nullptr));

        pbSelectCollaborativeToolPath->setText(QString());
        pbSelectClientFolder->setText(QString());
        label_93->setText(QCoreApplication::translate("ConfigDialog", "User name:", nullptr));
        checkBoxShowAdvancedOptions->setText(QCoreApplication::translate("ConfigDialog", "Show Advanced Options", nullptr));
        okButton->setText(QCoreApplication::translate("ConfigDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("ConfigDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
