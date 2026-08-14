/********************************************************************************
** Form generated from reading UI file 'PDFDocument.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFDOCUMENT_H
#define UI_PDFDOCUMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDFDocument
{
public:
    QAction *actionAbout_TW;
    QAction *actionFirst_Page;
    QAction *actionPrevious_Page;
    QAction *actionNext_Page;
    QAction *actionLast_Page;
    QAction *actionGo_to_Page;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionFit_to_Window;
    QAction *actionActual_Size;
    QAction *actionFit_to_Width;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpen_Recent;
    QAction *actionClose;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionTypeset;
    QAction *actionExternalViewer;
    QAction *actionPreferences;
    QAction *actionStack;
    QAction *actionTile;
    QAction *actionGo_to_Source;
    QAction *actionNew_from_Template;
    QAction *actionFull_Screen;
    QAction *actionMagnify;
    QAction *actionScroll;
    QAction *actionSelect_Text;
    QAction *actionSelect_Image;
    QAction *actionUserManual;
    QAction *actionWriteToMailingList;
    QAction *actionSide_by_Side;
    QAction *actionPlace_on_Left;
    QAction *actionPlace_on_Right;
    QAction *actionQuit_TeXworks;
    QAction *actionFind;
    QAction *actionFind_Again;
    QAction *actionUpdate_Scripts;
    QAction *actionManage_Scripts;
    QAction *actionShow_Scripts_Folder;
    QAction *actionAbout_Scripts;
    QAction *actionS;
    QAction *actionCloseSomething;
    QAction *actionScrolling_follows_cursor;
    QAction *actionCursor_follows_scrolling;
    QAction *actionFind_2;
    QAction *actionFind_again;
    QAction *actionNew_Window;
    QAction *actionGrid11;
    QAction *actionGrid21;
    QAction *actionGrid12;
    QAction *actionGrid22;
    QAction *actionGrid23;
    QAction *actionGrid33;
    QAction *actionCustom;
    QAction *actionSinglePageStep;
    QAction *actionSynchronize_multiple_views;
    QAction *actionPresentation;
    QAction *actionContinuous;
    QAction *action_Print;
    QAction *actionFileOpen;
    QAction *actionBack;
    QAction *actionForward;
    QAction *actionToggleEmbedded;
    QAction *actionEnlargeViewer;
    QAction *actionShrinkViewer;
    QAction *actionInvertColors;
    QAction *actionFocus_Editor;
    QAction *actionFit_to_Text_Width;
    QAction *actionGrayscale;
    QAction *actionSplitMerge;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *PDFDocument)
    {
        if (PDFDocument->objectName().isEmpty())
            PDFDocument->setObjectName(QString::fromUtf8("PDFDocument"));
        PDFDocument->resize(1486, 600);
        PDFDocument->setAcceptDrops(true);
        actionAbout_TW = new QAction(PDFDocument);
        actionAbout_TW->setObjectName(QString::fromUtf8("actionAbout_TW"));
        actionAbout_TW->setMenuRole(QAction::AboutRole);
        actionFirst_Page = new QAction(PDFDocument);
        actionFirst_Page->setObjectName(QString::fromUtf8("actionFirst_Page"));
#if QT_CONFIG(shortcut)
        actionFirst_Page->setShortcut(QString::fromUtf8("Home"));
#endif // QT_CONFIG(shortcut)
        actionFirst_Page->setMenuRole(QAction::NoRole);
        actionPrevious_Page = new QAction(PDFDocument);
        actionPrevious_Page->setObjectName(QString::fromUtf8("actionPrevious_Page"));
        actionPrevious_Page->setMenuRole(QAction::NoRole);
        actionNext_Page = new QAction(PDFDocument);
        actionNext_Page->setObjectName(QString::fromUtf8("actionNext_Page"));
        actionNext_Page->setMenuRole(QAction::NoRole);
        actionLast_Page = new QAction(PDFDocument);
        actionLast_Page->setObjectName(QString::fromUtf8("actionLast_Page"));
#if QT_CONFIG(shortcut)
        actionLast_Page->setShortcut(QString::fromUtf8("End"));
#endif // QT_CONFIG(shortcut)
        actionLast_Page->setMenuRole(QAction::NoRole);
        actionGo_to_Page = new QAction(PDFDocument);
        actionGo_to_Page->setObjectName(QString::fromUtf8("actionGo_to_Page"));
        actionGo_to_Page->setMenuRole(QAction::NoRole);
        actionZoom_In = new QAction(PDFDocument);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        actionZoom_In->setMenuRole(QAction::NoRole);
        actionZoom_Out = new QAction(PDFDocument);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        actionZoom_Out->setMenuRole(QAction::NoRole);
        actionFit_to_Window = new QAction(PDFDocument);
        actionFit_to_Window->setObjectName(QString::fromUtf8("actionFit_to_Window"));
        actionFit_to_Window->setCheckable(true);
        actionFit_to_Window->setMenuRole(QAction::NoRole);
        actionActual_Size = new QAction(PDFDocument);
        actionActual_Size->setObjectName(QString::fromUtf8("actionActual_Size"));
        actionActual_Size->setMenuRole(QAction::NoRole);
        actionFit_to_Width = new QAction(PDFDocument);
        actionFit_to_Width->setObjectName(QString::fromUtf8("actionFit_to_Width"));
        actionFit_to_Width->setCheckable(true);
        actionFit_to_Width->setMenuRole(QAction::NoRole);
        actionNew = new QAction(PDFDocument);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setMenuRole(QAction::NoRole);
        actionOpen = new QAction(PDFDocument);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setMenuRole(QAction::NoRole);
        actionOpen_Recent = new QAction(PDFDocument);
        actionOpen_Recent->setObjectName(QString::fromUtf8("actionOpen_Recent"));
        actionOpen_Recent->setMenuRole(QAction::NoRole);
        actionClose = new QAction(PDFDocument);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setMenuRole(QAction::NoRole);
        actionUndo = new QAction(PDFDocument);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setEnabled(false);
        actionUndo->setMenuRole(QAction::NoRole);
        actionRedo = new QAction(PDFDocument);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionRedo->setEnabled(false);
        actionRedo->setMenuRole(QAction::NoRole);
        actionCut = new QAction(PDFDocument);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCut->setEnabled(false);
        actionCut->setMenuRole(QAction::NoRole);
        actionCopy = new QAction(PDFDocument);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCopy->setEnabled(false);
        actionCopy->setMenuRole(QAction::NoRole);
        actionPaste = new QAction(PDFDocument);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionPaste->setEnabled(false);
        actionPaste->setMenuRole(QAction::NoRole);
        actionClear = new QAction(PDFDocument);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionClear->setEnabled(false);
        actionClear->setMenuRole(QAction::NoRole);
        actionTypeset = new QAction(PDFDocument);
        actionTypeset->setObjectName(QString::fromUtf8("actionTypeset"));
        actionTypeset->setMenuRole(QAction::NoRole);
        actionExternalViewer = new QAction(PDFDocument);
        actionExternalViewer->setObjectName(QString::fromUtf8("actionExternalViewer"));
        actionExternalViewer->setMenuRole(QAction::NoRole);
        actionPreferences = new QAction(PDFDocument);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionPreferences->setMenuRole(QAction::PreferencesRole);
        actionStack = new QAction(PDFDocument);
        actionStack->setObjectName(QString::fromUtf8("actionStack"));
        actionStack->setMenuRole(QAction::NoRole);
        actionTile = new QAction(PDFDocument);
        actionTile->setObjectName(QString::fromUtf8("actionTile"));
        actionTile->setMenuRole(QAction::NoRole);
        actionGo_to_Source = new QAction(PDFDocument);
        actionGo_to_Source->setObjectName(QString::fromUtf8("actionGo_to_Source"));
        actionGo_to_Source->setEnabled(true);
        actionGo_to_Source->setMenuRole(QAction::NoRole);
        actionNew_from_Template = new QAction(PDFDocument);
        actionNew_from_Template->setObjectName(QString::fromUtf8("actionNew_from_Template"));
        actionNew_from_Template->setMenuRole(QAction::NoRole);
        actionFull_Screen = new QAction(PDFDocument);
        actionFull_Screen->setObjectName(QString::fromUtf8("actionFull_Screen"));
        actionFull_Screen->setCheckable(true);
        actionFull_Screen->setMenuRole(QAction::NoRole);
        actionMagnify = new QAction(PDFDocument);
        actionMagnify->setObjectName(QString::fromUtf8("actionMagnify"));
        actionMagnify->setCheckable(true);
        actionMagnify->setChecked(true);
        actionScroll = new QAction(PDFDocument);
        actionScroll->setObjectName(QString::fromUtf8("actionScroll"));
        actionScroll->setCheckable(true);
        actionSelect_Text = new QAction(PDFDocument);
        actionSelect_Text->setObjectName(QString::fromUtf8("actionSelect_Text"));
        actionSelect_Text->setCheckable(true);
        actionSelect_Image = new QAction(PDFDocument);
        actionSelect_Image->setObjectName(QString::fromUtf8("actionSelect_Image"));
        actionSelect_Image->setCheckable(true);
        actionUserManual = new QAction(PDFDocument);
        actionUserManual->setObjectName(QString::fromUtf8("actionUserManual"));
        actionWriteToMailingList = new QAction(PDFDocument);
        actionWriteToMailingList->setObjectName(QString::fromUtf8("actionWriteToMailingList"));
        actionSide_by_Side = new QAction(PDFDocument);
        actionSide_by_Side->setObjectName(QString::fromUtf8("actionSide_by_Side"));
        actionSide_by_Side->setEnabled(true);
        actionPlace_on_Left = new QAction(PDFDocument);
        actionPlace_on_Left->setObjectName(QString::fromUtf8("actionPlace_on_Left"));
        actionPlace_on_Right = new QAction(PDFDocument);
        actionPlace_on_Right->setObjectName(QString::fromUtf8("actionPlace_on_Right"));
        actionQuit_TeXworks = new QAction(PDFDocument);
        actionQuit_TeXworks->setObjectName(QString::fromUtf8("actionQuit_TeXworks"));
        actionQuit_TeXworks->setMenuRole(QAction::QuitRole);
        actionFind = new QAction(PDFDocument);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        actionFind->setShortcutContext(Qt::WindowShortcut);
        actionFind->setMenuRole(QAction::NoRole);
        actionFind_Again = new QAction(PDFDocument);
        actionFind_Again->setObjectName(QString::fromUtf8("actionFind_Again"));
        actionFind_Again->setShortcutContext(Qt::WindowShortcut);
        actionFind_Again->setMenuRole(QAction::NoRole);
        actionUpdate_Scripts = new QAction(PDFDocument);
        actionUpdate_Scripts->setObjectName(QString::fromUtf8("actionUpdate_Scripts"));
        actionUpdate_Scripts->setMenuRole(QAction::NoRole);
        actionManage_Scripts = new QAction(PDFDocument);
        actionManage_Scripts->setObjectName(QString::fromUtf8("actionManage_Scripts"));
        actionManage_Scripts->setMenuRole(QAction::NoRole);
        actionShow_Scripts_Folder = new QAction(PDFDocument);
        actionShow_Scripts_Folder->setObjectName(QString::fromUtf8("actionShow_Scripts_Folder"));
        actionShow_Scripts_Folder->setMenuRole(QAction::NoRole);
        actionAbout_Scripts = new QAction(PDFDocument);
        actionAbout_Scripts->setObjectName(QString::fromUtf8("actionAbout_Scripts"));
        actionAbout_Scripts->setMenuRole(QAction::NoRole);
        actionS = new QAction(PDFDocument);
        actionS->setObjectName(QString::fromUtf8("actionS"));
        actionCloseSomething = new QAction(PDFDocument);
        actionCloseSomething->setObjectName(QString::fromUtf8("actionCloseSomething"));
        actionScrolling_follows_cursor = new QAction(PDFDocument);
        actionScrolling_follows_cursor->setObjectName(QString::fromUtf8("actionScrolling_follows_cursor"));
        actionScrolling_follows_cursor->setCheckable(true);
        actionCursor_follows_scrolling = new QAction(PDFDocument);
        actionCursor_follows_scrolling->setObjectName(QString::fromUtf8("actionCursor_follows_scrolling"));
        actionCursor_follows_scrolling->setCheckable(true);
        actionFind_2 = new QAction(PDFDocument);
        actionFind_2->setObjectName(QString::fromUtf8("actionFind_2"));
        actionFind_again = new QAction(PDFDocument);
        actionFind_again->setObjectName(QString::fromUtf8("actionFind_again"));
        actionNew_Window = new QAction(PDFDocument);
        actionNew_Window->setObjectName(QString::fromUtf8("actionNew_Window"));
        actionGrid11 = new QAction(PDFDocument);
        actionGrid11->setObjectName(QString::fromUtf8("actionGrid11"));
        actionGrid11->setProperty("grid", QVariant(QString::fromUtf8("1x1")));
        actionGrid21 = new QAction(PDFDocument);
        actionGrid21->setObjectName(QString::fromUtf8("actionGrid21"));
        actionGrid21->setProperty("grid", QVariant(QString::fromUtf8("2x1")));
        actionGrid12 = new QAction(PDFDocument);
        actionGrid12->setObjectName(QString::fromUtf8("actionGrid12"));
        actionGrid12->setProperty("grid", QVariant(QString::fromUtf8("1x2")));
        actionGrid22 = new QAction(PDFDocument);
        actionGrid22->setObjectName(QString::fromUtf8("actionGrid22"));
        actionGrid22->setProperty("grid", QVariant(QString::fromUtf8("2x2")));
        actionGrid23 = new QAction(PDFDocument);
        actionGrid23->setObjectName(QString::fromUtf8("actionGrid23"));
        actionGrid23->setProperty("grid", QVariant(QString::fromUtf8("23")));
        actionGrid33 = new QAction(PDFDocument);
        actionGrid33->setObjectName(QString::fromUtf8("actionGrid33"));
        actionGrid33->setProperty("grid", QVariant(QString::fromUtf8("33")));
        actionCustom = new QAction(PDFDocument);
        actionCustom->setObjectName(QString::fromUtf8("actionCustom"));
        actionCustom->setProperty("grid", QVariant(QString::fromUtf8("xx")));
        actionSinglePageStep = new QAction(PDFDocument);
        actionSinglePageStep->setObjectName(QString::fromUtf8("actionSinglePageStep"));
        actionSinglePageStep->setCheckable(true);
        actionSinglePageStep->setChecked(false);
        actionSynchronize_multiple_views = new QAction(PDFDocument);
        actionSynchronize_multiple_views->setObjectName(QString::fromUtf8("actionSynchronize_multiple_views"));
        actionSynchronize_multiple_views->setCheckable(true);
        actionSynchronize_multiple_views->setChecked(true);
        actionPresentation = new QAction(PDFDocument);
        actionPresentation->setObjectName(QString::fromUtf8("actionPresentation"));
        actionPresentation->setCheckable(true);
        actionContinuous = new QAction(PDFDocument);
        actionContinuous->setObjectName(QString::fromUtf8("actionContinuous"));
        actionContinuous->setCheckable(true);
        actionContinuous->setChecked(true);
        action_Print = new QAction(PDFDocument);
        action_Print->setObjectName(QString::fromUtf8("action_Print"));
        actionFileOpen = new QAction(PDFDocument);
        actionFileOpen->setObjectName(QString::fromUtf8("actionFileOpen"));
        actionBack = new QAction(PDFDocument);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        actionForward = new QAction(PDFDocument);
        actionForward->setObjectName(QString::fromUtf8("actionForward"));
        actionToggleEmbedded = new QAction(PDFDocument);
        actionToggleEmbedded->setObjectName(QString::fromUtf8("actionToggleEmbedded"));
        actionEnlargeViewer = new QAction(PDFDocument);
        actionEnlargeViewer->setObjectName(QString::fromUtf8("actionEnlargeViewer"));
        actionShrinkViewer = new QAction(PDFDocument);
        actionShrinkViewer->setObjectName(QString::fromUtf8("actionShrinkViewer"));
        actionInvertColors = new QAction(PDFDocument);
        actionInvertColors->setObjectName(QString::fromUtf8("actionInvertColors"));
        actionInvertColors->setCheckable(true);
        actionFocus_Editor = new QAction(PDFDocument);
        actionFocus_Editor->setObjectName(QString::fromUtf8("actionFocus_Editor"));
        actionFit_to_Text_Width = new QAction(PDFDocument);
        actionFit_to_Text_Width->setObjectName(QString::fromUtf8("actionFit_to_Text_Width"));
        actionFit_to_Text_Width->setCheckable(true);
        actionGrayscale = new QAction(PDFDocument);
        actionGrayscale->setObjectName(QString::fromUtf8("actionGrayscale"));
        actionGrayscale->setCheckable(true);
        actionSplitMerge = new QAction(PDFDocument);
        actionSplitMerge->setObjectName(QString::fromUtf8("actionSplitMerge"));
        centralwidget = new QWidget(PDFDocument);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PDFDocument->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(PDFDocument);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PDFDocument->setStatusBar(statusbar);
        toolBar = new QToolBar(PDFDocument);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(24, 24));
        PDFDocument->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionTypeset);
        toolBar->addSeparator();
        toolBar->addAction(actionExternalViewer);
        toolBar->addSeparator();
        toolBar->addAction(actionMagnify);
        toolBar->addAction(actionScroll);
        toolBar->addSeparator();
        toolBar->addAction(actionBack);
        toolBar->addAction(actionForward);
        toolBar->addSeparator();
        toolBar->addAction(actionFirst_Page);
        toolBar->addAction(actionPrevious_Page);
        toolBar->addAction(actionNext_Page);
        toolBar->addAction(actionLast_Page);
        toolBar->addSeparator();
        toolBar->addAction(actionActual_Size);
        toolBar->addAction(actionFit_to_Width);
        toolBar->addAction(actionFit_to_Text_Width);
        toolBar->addAction(actionFit_to_Window);
        toolBar->addSeparator();
        toolBar->addAction(actionEnlargeViewer);
        toolBar->addAction(actionShrinkViewer);
        toolBar->addAction(actionToggleEmbedded);
        toolBar->addAction(actionClose);

        retranslateUi(PDFDocument);
        QObject::connect(actionClose, SIGNAL(triggered()), PDFDocument, SLOT(close()));

        QMetaObject::connectSlotsByName(PDFDocument);
    } // setupUi

    void retranslateUi(QMainWindow *PDFDocument)
    {
        PDFDocument->setWindowTitle(QCoreApplication::translate("PDFDocument", "untitled.pdf[*]", nullptr));
        actionAbout_TW->setText(QCoreApplication::translate("PDFDocument", "&About TeXstudio...", nullptr));
        actionFirst_Page->setText(QCoreApplication::translate("PDFDocument", "&First Page", nullptr));
        actionPrevious_Page->setText(QCoreApplication::translate("PDFDocument", "&Previous Page", nullptr));
        actionNext_Page->setText(QCoreApplication::translate("PDFDocument", "&Next Page", nullptr));
        actionLast_Page->setText(QCoreApplication::translate("PDFDocument", "&Last Page", nullptr));
        actionGo_to_Page->setText(QCoreApplication::translate("PDFDocument", "&Go to Page...", nullptr));
#if QT_CONFIG(shortcut)
        actionGo_to_Page->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+J", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_In->setText(QCoreApplication::translate("PDFDocument", "Zoom &In", nullptr));
#if QT_CONFIG(shortcut)
        actionZoom_In->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl++", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_Out->setText(QCoreApplication::translate("PDFDocument", "Zoom &Out", nullptr));
#if QT_CONFIG(shortcut)
        actionZoom_Out->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFit_to_Window->setText(QCoreApplication::translate("PDFDocument", "Fit to &Window", nullptr));
#if QT_CONFIG(shortcut)
        actionFit_to_Window->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionActual_Size->setText(QCoreApplication::translate("PDFDocument", "&Actual Size", nullptr));
#if QT_CONFIG(shortcut)
        actionActual_Size->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFit_to_Width->setText(QCoreApplication::translate("PDFDocument", "Fit to Wi&dth", nullptr));
#if QT_CONFIG(shortcut)
        actionFit_to_Width->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("PDFDocument", "New", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("PDFDocument", "Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_Recent->setText(QCoreApplication::translate("PDFDocument", "Open Recent", nullptr));
        actionClose->setText(QCoreApplication::translate("PDFDocument", "&Close", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUndo->setText(QCoreApplication::translate("PDFDocument", "&Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRedo->setText(QCoreApplication::translate("PDFDocument", "&Redo", nullptr));
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("PDFDocument", "C&ut", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("PDFDocument", "&Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("PDFDocument", "&Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("PDFDocument", "C&lear", nullptr));
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTypeset->setText(QCoreApplication::translate("PDFDocument", "Quick Build", nullptr));
        actionTypeset->setIconText(QCoreApplication::translate("PDFDocument", "Quick Build", nullptr));
#if QT_CONFIG(shortcut)
        actionTypeset->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+T", "action"));
#endif // QT_CONFIG(shortcut)
        actionExternalViewer->setText(QCoreApplication::translate("PDFDocument", "External Viewer", nullptr));
        actionExternalViewer->setIconText(QCoreApplication::translate("PDFDocument", "External Viewer", nullptr));
#if QT_CONFIG(shortcut)
        actionExternalViewer->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Alt+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPreferences->setText(QCoreApplication::translate("PDFDocument", "&Configure TeXstudio", nullptr));
        actionStack->setText(QCoreApplication::translate("PDFDocument", "Stac&k", nullptr));
        actionTile->setText(QCoreApplication::translate("PDFDocument", "&Tile", nullptr));
        actionGo_to_Source->setText(QCoreApplication::translate("PDFDocument", "&Go to Source", nullptr));
#if QT_CONFIG(shortcut)
        actionGo_to_Source->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+'", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_from_Template->setText(QCoreApplication::translate("PDFDocument", "New from Template...", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_from_Template->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Shift+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFull_Screen->setText(QCoreApplication::translate("PDFDocument", "Full &Screen", nullptr));
#if QT_CONFIG(shortcut)
        actionFull_Screen->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Shift+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMagnify->setText(QCoreApplication::translate("PDFDocument", "Magnify", nullptr));
        actionScroll->setText(QCoreApplication::translate("PDFDocument", "Scroll", nullptr));
        actionSelect_Text->setText(QCoreApplication::translate("PDFDocument", "Select Text", nullptr));
        actionSelect_Image->setText(QCoreApplication::translate("PDFDocument", "Select Image", nullptr));
        actionUserManual->setText(QCoreApplication::translate("PDFDocument", "User &Manual...", nullptr));
        actionWriteToMailingList->setText(QCoreApplication::translate("PDFDocument", "Email to the mailing list", nullptr));
        actionSide_by_Side->setText(QCoreApplication::translate("PDFDocument", "&Side by Side", nullptr));
        actionPlace_on_Left->setText(QCoreApplication::translate("PDFDocument", "Place on Left", nullptr));
        actionPlace_on_Right->setText(QCoreApplication::translate("PDFDocument", "Place on Right", nullptr));
        actionQuit_TeXworks->setText(QCoreApplication::translate("PDFDocument", "&Quit TeXstudio", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit_TeXworks->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind->setText(QCoreApplication::translate("PDFDocument", "Find...", nullptr));
#if QT_CONFIG(shortcut)
        actionFind->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind_Again->setText(QCoreApplication::translate("PDFDocument", "Find Again", nullptr));
#if QT_CONFIG(shortcut)
        actionFind_Again->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUpdate_Scripts->setText(QCoreApplication::translate("PDFDocument", "Reload Script List", nullptr));
        actionManage_Scripts->setText(QCoreApplication::translate("PDFDocument", "Manage Scripts", nullptr));
        actionShow_Scripts_Folder->setText(QCoreApplication::translate("PDFDocument", "Show Scripts Folder", nullptr));
        actionAbout_Scripts->setText(QCoreApplication::translate("PDFDocument", "About Scripts...", nullptr));
        actionS->setText(QCoreApplication::translate("PDFDocument", "s", nullptr));
        actionCloseSomething->setText(QCoreApplication::translate("PDFDocument", "&Close something", nullptr));
#if QT_CONFIG(shortcut)
        actionCloseSomething->setShortcut(QCoreApplication::translate("PDFDocument", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
        actionScrolling_follows_cursor->setText(QCoreApplication::translate("PDFDocument", "Scrolling follows cursor", nullptr));
        actionCursor_follows_scrolling->setText(QCoreApplication::translate("PDFDocument", "Cursor follows scrolling", nullptr));
        actionFind_2->setText(QCoreApplication::translate("PDFDocument", "&Find...", nullptr));
#if QT_CONFIG(shortcut)
        actionFind_2->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind_again->setText(QCoreApplication::translate("PDFDocument", "Find &again", nullptr));
#if QT_CONFIG(shortcut)
        actionFind_again->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+M, F3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_Window->setText(QCoreApplication::translate("PDFDocument", "New Window", nullptr));
        actionGrid11->setText(QCoreApplication::translate("PDFDocument", "1x1", nullptr));
        actionGrid21->setText(QCoreApplication::translate("PDFDocument", "2x1", nullptr));
        actionGrid12->setText(QCoreApplication::translate("PDFDocument", "1x2", nullptr));
        actionGrid22->setText(QCoreApplication::translate("PDFDocument", "2x2", nullptr));
        actionGrid23->setText(QCoreApplication::translate("PDFDocument", "2x3", nullptr));
        actionGrid33->setText(QCoreApplication::translate("PDFDocument", "3x3", nullptr));
        actionCustom->setText(QCoreApplication::translate("PDFDocument", "Custom...", nullptr));
        actionSinglePageStep->setText(QCoreApplication::translate("PDFDocument", "Single Page Step", nullptr));
        actionSynchronize_multiple_views->setText(QCoreApplication::translate("PDFDocument", "Synchronize multiple views", nullptr));
        actionPresentation->setText(QCoreApplication::translate("PDFDocument", "Presentation", nullptr));
#if QT_CONFIG(shortcut)
        actionPresentation->setShortcut(QCoreApplication::translate("PDFDocument", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionContinuous->setText(QCoreApplication::translate("PDFDocument", "&Continuous", nullptr));
        action_Print->setText(QCoreApplication::translate("PDFDocument", "&Print...", nullptr));
#if QT_CONFIG(shortcut)
        action_Print->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileOpen->setText(QCoreApplication::translate("PDFDocument", "&Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionFileOpen->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBack->setText(QCoreApplication::translate("PDFDocument", "Back", nullptr));
#if QT_CONFIG(tooltip)
        actionBack->setToolTip(QCoreApplication::translate("PDFDocument", "Previously shown page", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionBack->setShortcut(QCoreApplication::translate("PDFDocument", "Alt+Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionForward->setText(QCoreApplication::translate("PDFDocument", "Forward", nullptr));
#if QT_CONFIG(tooltip)
        actionForward->setToolTip(QCoreApplication::translate("PDFDocument", "Next shown page", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionForward->setShortcut(QCoreApplication::translate("PDFDocument", "Alt+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToggleEmbedded->setText(QCoreApplication::translate("PDFDocument", "Windowed/Embedded", nullptr));
        actionEnlargeViewer->setText(QCoreApplication::translate("PDFDocument", "Enlarge Viewer", nullptr));
        actionShrinkViewer->setText(QCoreApplication::translate("PDFDocument", "Shrink Viewer", nullptr));
        actionInvertColors->setText(QCoreApplication::translate("PDFDocument", "Invert Colors", nullptr));
        actionFocus_Editor->setText(QCoreApplication::translate("PDFDocument", "Focus Editor", nullptr));
#if QT_CONFIG(shortcut)
        actionFocus_Editor->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+Alt+Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFit_to_Text_Width->setText(QCoreApplication::translate("PDFDocument", "Fit to &Text Width", nullptr));
#if QT_CONFIG(tooltip)
        actionFit_to_Text_Width->setToolTip(QCoreApplication::translate("PDFDocument", "Fit to Text Width", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFit_to_Text_Width->setShortcut(QCoreApplication::translate("PDFDocument", "Ctrl+4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionGrayscale->setText(QCoreApplication::translate("PDFDocument", "Grayscale", nullptr));
        actionSplitMerge->setText(QCoreApplication::translate("PDFDocument", "Split && Merge...", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("PDFDocument", "Toolbar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PDFDocument: public Ui_PDFDocument {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFDOCUMENT_H
