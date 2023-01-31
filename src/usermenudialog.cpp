/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "usermenudialog.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "qlanguagefactory.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
#include "qstatuspanel.h"
#include "qgotolinepanel.h"
#include "qsearchreplacepanel.h"
#include "qfoldpanel.h"
#include "macrobrowserui.h"

#include "smallUsefulFunctions.h"
#include "utilsUI.h"

UserMenuDialog::UserMenuDialog(QWidget *parent,  QString name, QLanguageFactory *languageFactory)
    : QDialog(parent), languages(languageFactory)
{
	setWindowTitle(name);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 73, 35);

	ui.splitter->setStretchFactor(0, 4);
	ui.splitter->setStretchFactor(1, 6);

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));

	connect(ui.runScriptButton, SIGNAL(clicked()), SLOT(slotRunScript()));

	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(slotAdd()));
    connect(ui.pushButtonAddFolder, SIGNAL(clicked()), SLOT(slotAddFolder()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), SLOT(slotRemove()));
	connect(ui.pushButtonUp, SIGNAL(clicked()), SLOT(slotMoveUp()));
	connect(ui.pushButtonDown, SIGNAL(clicked()), SLOT(slotMoveDown()));

    connect(ui.pbExport,SIGNAL(clicked()), SLOT(exportMacro()));
    connect(ui.pbImport,SIGNAL(clicked()), SLOT(importMacro()));
    connect(ui.pbBrowse,SIGNAL(clicked()), SLOT(browseMacrosOnRepository()));


	connect(ui.radioButtonNormal, SIGNAL(clicked()), SLOT(changeTypeToNormal()));
	connect(ui.radioButtonEnvironment, SIGNAL(clicked()), SLOT(changeTypeToEnvironment()));
	connect(ui.radioButtonScript, SIGNAL(clicked()), SLOT(changeTypeToScript()));

	//editor options
	ui.tagEdit->setLayout(new QVBoxLayout());
	codeedit = new QCodeEdit(ui.tagEdit);
	codeedit->editor()->setFlag(QEditor::AdjustIndent, false);
	codeedit->editor()->document()->setCenterDocumentInEditor(false);
	languages->setLanguage(codeedit->editor(), "");
	//QLineMarkPanel* lineMarkPanel=new QLineMarkPanel;
	//QAction* lineMarkPanelAction=codeedit->addPanel(lineMarkPanel, QCodeEdit::West, false);
	//Q_UNUSED(lineMarkPanelAction)
	QLineNumberPanel *lineNumberPanel = new QLineNumberPanel;
	lineNumberPanel->setVerboseMode(true);
	QAction *lineNumberPanelAction = codeedit->addPanel(lineNumberPanel, QCodeEdit::West, false);
	Q_UNUSED(lineNumberPanelAction)
	QAction *lineFoldPanelAction = codeedit->addPanel(new QFoldPanel, QCodeEdit::West, false);
	Q_UNUSED(lineFoldPanelAction)
	//QAction* vlineChangePanelAction=codeedit->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	QStatusPanel *statusPanel = new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	QAction *statusPanelAction = codeedit->addPanel(statusPanel, QCodeEdit::South, false);
	Q_UNUSED(statusPanelAction)

	QGotoLinePanel *gotoLinePanel = new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	QAction *gotoLinePanelAction = codeedit->addPanel(gotoLinePanel, QCodeEdit::South, false);
	Q_UNUSED(gotoLinePanelAction)

	searchReplacePanel = new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	QAction *searchReplacePanelAction = codeedit->addPanel(searchReplacePanel, QCodeEdit::South, false);
	searchReplacePanel->display(0, false);
	Q_UNUSED(searchReplacePanelAction)

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    ui.tagEdit->layout()->setMargin(0);
#else
    ui.tagEdit->layout()->setContentsMargins(0,0,0,0);
#endif

	ui.tagEdit->layout()->addWidget(codeedit->editor());

    // limit height of description editor
    QFontMetrics m (ui.teDescription->font());
    int RowHeight = m.lineSpacing();
    ui.teDescription->setFixedHeight(4 * RowHeight);

    QStringList lst;
    for(char i=0;i<26;i++){
        lst<<QString("Ctrl+M,Ctrl+%1").arg(QChar('A'+i));
    }
    ui.cbShortcut->addItems(lst);

    connect(ui.treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(change(QTreeWidgetItem*,QTreeWidgetItem*)));
    ui.treeWidget->setDragEnabled(true);
    ui.treeWidget->setDragDropMode(QAbstractItemView::InternalMove);

	connect(codeedit->editor()->document(), SIGNAL(contentsChanged()), SLOT(textChanged()));
	connect(ui.itemEdit, SIGNAL(textEdited(QString)), SLOT(nameChanged()));
    connect(ui.teDescription, SIGNAL(textChanged()), SLOT(descriptionChanged()));
    connect(ui.cbShortcut, SIGNAL(currentTextChanged(QString)), SLOT(shortcutChanged()));

	connect(ui.abbrevEdit, SIGNAL(textEdited(QString)), SLOT(abbrevChanged()));
	connect(ui.triggerEdit, SIGNAL(textEdited(QString)), SLOT(triggerChanged()));
	connect(ui.triggerHelp, SIGNAL(linkActivated(QString)), SLOT(showTooltip()));

}

UserMenuDialog::~UserMenuDialog()
{
	delete searchReplacePanel;
	delete codeedit;
}

void UserMenuDialog::addMacro(const Macro &m,bool insertRow)
{
    auto *item=new QTreeWidgetItem();
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);
    item->setText(0,m.name);
    item->setText(1,m.shortcut());
    item->setText(2,m.trigger);
    item->setText(3,m.abbrev);
    item->setData(0,Qt::UserRole,QVariant::fromValue(m));
    if(insertRow){
        ui.treeWidget->addTopLevelItem(item);
        ui.treeWidget->setCurrentItem(item);
    }else{
        // generate tree/folder if necessary
        if(!m.menu.isEmpty()){
            QTreeWidgetItem *parent=findCreateFolder(m.menu);
            parent->addChild(item);
        }else{
            ui.treeWidget->addTopLevelItem(item);
        }
    }
}


QList<Macro> UserMenuDialog::getMacros() const
{
    QList<Macro> results;
    for(int i=0;i<ui.treeWidget->topLevelItemCount();i++){
        QTreeWidgetItem *element=ui.treeWidget->topLevelItem(i);
        results<<getMacros(element,"");
    }
    return results;
}

QList<Macro> UserMenuDialog::getMacros(QTreeWidgetItem *item, const QString &path) const
{
    QList<Macro> results;
    if(item->childCount()){
        for(int i=0;i<item->childCount();i++){
            QTreeWidgetItem *element=item->child(i);
            results<<getMacros(element,path+item->text(0)+"/");
        }
    }else{
        QVariant v=item->data(0,Qt::UserRole);
        if(v.isValid()){
            Macro m=v.value<Macro>();
            if(!m.isEmpty()){
                QString s=path;
                if(s.endsWith('/')){
                    s=s.left(s.length()-1);
                }
                m.menu=s;
                results<<m;
            }
        }
    }
    return results;
}

void UserMenuDialog::selectFirst()
{
    auto *item=ui.treeWidget->topLevelItem(0);
    ui.treeWidget->setCurrentItem(item);
}

void UserMenuDialog::setLineWrap(bool wrap)
{
    codeedit->editor()->setLineWrapping(wrap);
}

bool UserMenuDialog::getLineWrap()
{
    return codeedit->editor()->flag(QEditor::LineWrap);
}

QTreeWidgetItem *UserMenuDialog::findCreateFolder(const QString &menu)
{
    QTreeWidgetItem *parent=nullptr;
    QStringList folders=menu.split('/');
    QString topFolder=folders.takeFirst();
    QList<QTreeWidgetItem*>results=ui.treeWidget->findItems(topFolder,Qt::MatchExactly);
    bool found=false;
    foreach(parent,results){
        if(parent->type()==1){
            found=true;
            break;
        }
    }
    if(!found){
        // create folder
        parent=new QTreeWidgetItem(ui.treeWidget,1);
        parent->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
        parent->setText(0,topFolder);
        parent->setIcon(0,QIcon::fromTheme("folder"));
        ui.treeWidget->addTopLevelItem(parent);
    }
    parent=findCreateFolder(parent,folders);
    return parent;
}

QTreeWidgetItem *UserMenuDialog::findCreateFolder(QTreeWidgetItem *parent, QStringList folders)
{
    if(folders.isEmpty())
        return parent;
    QString topFolder=folders.takeFirst();
    bool found=false;
    for(int i=0;i<parent->childCount();i++){
        QTreeWidgetItem *item=parent->child(i);
        if(item->text(0)==topFolder){
            if(item->type()==1){
                found=true;
                parent=item;
                break;
            }
        }
    }
    if(!found){
        // create folder
        parent=new QTreeWidgetItem(parent,1);
        parent->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
        parent->setText(0,topFolder);
        parent->setIcon(0,QIcon::fromTheme("folder"));
    }
    parent=findCreateFolder(parent,folders);
    return parent;
}

void UserMenuDialog::change(QTreeWidgetItem *current,QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (current==nullptr) return;
    QVariant v=current->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        if (m.name != ui.itemEdit->text())
            ui.itemEdit->setText(m.name);
        if (m.abbrev != ui.abbrevEdit->text())
            ui.abbrevEdit->setText(m.abbrev);
        if (m.trigger != ui.triggerEdit->text())
            ui.triggerEdit->setText(m.trigger);

        if (m.shortcut() != ui.cbShortcut->currentText()){
            ui.cbShortcut->setCurrentText(m.shortcut());
        }
        if (m.description != ui.teDescription->toPlainText())
            ui.teDescription->setPlainText(m.description);

        if (codeedit->editor()->text() != m.typedTag()) {
            codeedit->editor()->setText(m.typedTag(), false);
            setLanguageFromText();
        }
    }
}

void UserMenuDialog::setLanguageFromText(void)
{
	QString line = codeedit->editor()->text(0);
	if (line == "%SCRIPT") {
		languages->setLanguage(codeedit->editor(), ".qs");
		ui.radioButtonScript->setChecked(true);
	} else if (line.startsWith("%") && !line.startsWith("%%")) {
		languages->setLanguage(codeedit->editor(), "");
		ui.radioButtonEnvironment->setChecked(true);
	} else {
		languages->setLanguage(codeedit->editor(), "(La)TeX Macro");
		ui.radioButtonNormal->setChecked(true);
	}
}

void UserMenuDialog::slotOk()
{
	accept();
}
void UserMenuDialog::slotRunScript()
{
	QString script = codeedit->editor()->text();
	if (script.startsWith("%SCRIPT\n"))
		script = script.mid(8);
	emit runScript(script);
}

void UserMenuDialog::slotAdd()
{
    auto *item=new QTreeWidgetItem(ui.treeWidget);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);
    item->setText(0,"");
    Macro m;
    item->setData(0,Qt::UserRole,QVariant::fromValue(m));
    ui.treeWidget->addTopLevelItem(item);
    ui.treeWidget->setCurrentItem(item);
}

void UserMenuDialog::slotRemove()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr)
        return;
    if(item->childCount()){
        UtilsUi::txsInformation(tr("Folder is not empty."));
        return;
    }
    if(item->type()==0){
        // only confirm for macros, not for folders
        if (!UtilsUi::txsConfirm(tr("Do you really want to delete the current macro?")))
            return;
    }

    QTreeWidgetItem *parent=item->parent();
    if(parent){
        int index = parent->indexOfChild(item);
        QTreeWidgetItem* child = parent->takeChild(index);
        delete child;
    }else{
        int index = ui.treeWidget->indexOfTopLevelItem(item);
        QTreeWidgetItem* child = ui.treeWidget->takeTopLevelItem(index);
        delete child;
    }
    if(ui.treeWidget->topLevelItemCount()==0){
        // add empty macro
        slotAdd();
    }
}

void UserMenuDialog::slotAddFolder(){
    auto *item=new QTreeWidgetItem(ui.treeWidget,1);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
    item->setText(0,"Folder");
    item->setIcon(0,QIcon::fromTheme("folder"));
    ui.treeWidget->addTopLevelItem(item);
    ui.treeWidget->setCurrentItem(item);
}

void UserMenuDialog::slotMoveUp()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    int row  = ui.treeWidget->currentIndex().row();
    if (item && row > 0)
    {
        QTreeWidgetItem* parent = item->parent();
        if(parent){
            int index = parent->indexOfChild(item);
            QTreeWidgetItem* child = parent->takeChild(index);
            parent->insertChild(index-1, child);
            parent->setExpanded(true);
            child->setExpanded(true);
            ui.treeWidget->setCurrentItem(item);
        }else{
            int index = ui.treeWidget->indexOfTopLevelItem(item);
            QTreeWidgetItem* child = ui.treeWidget->takeTopLevelItem(index);
            ui.treeWidget->insertTopLevelItem(index-1, child);
            ui.treeWidget->setCurrentItem(item);
        }
    }
}

void UserMenuDialog::slotMoveDown()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if (item){
        QTreeWidgetItem* parent = item->parent();
        if(parent){
            int index = parent->indexOfChild(item);
            if(index< (parent->childCount()-1)){
                QTreeWidgetItem* child = parent->takeChild(index);
                parent->insertChild(index+1, child);
                parent->setExpanded(true);
                child->setExpanded(true);
                ui.treeWidget->setCurrentItem(item);
            }
        }else{
            int index = ui.treeWidget->indexOfTopLevelItem(item);
            if(index<(ui.treeWidget->topLevelItemCount()-1)){
                QTreeWidgetItem* child = ui.treeWidget->takeTopLevelItem(index);
                ui.treeWidget->insertTopLevelItem(index+1, child);
                ui.treeWidget->setCurrentItem(item);
            }
        }
    }
}

void UserMenuDialog::importMacro()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Import macros"), "", tr("txs macro files (*.txsMacro)"));
    for(const QString &fileName:fileNames){
        Macro m;
        m.load(fileName);
        addMacro(m,true);
    }
}

void UserMenuDialog::exportMacro()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr || item->type()==1) return;
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export macro"), "", tr("txs macro files (*.txsMacro)"));
    if(!fileName.isEmpty()){
        QVariant v=item->data(0,Qt::UserRole);
        if(v.isValid()){
            Macro m=v.value<Macro>();
            m.save(fileName);
        }
    }
}

void UserMenuDialog::browseMacrosOnRepository(){
    // open special dialog for macro browser
    MacroBrowserUI *mbUI=new MacroBrowserUI(this);
    if(mbUI->exec()){
        QList<Macro> lst=mbUI->getSelectedMacros();
        foreach(const auto &m,lst){
            addMacro(m,true);
        }
    }
}

void UserMenuDialog::changeTypeToNormal()
{
	QString cur = codeedit->editor()->text();
	languages->setLanguage(codeedit->editor(), "(La)TeX Macro");
	if (cur.startsWith("%SCRIPT\n")) codeedit->editor()->setText(cur.mid(8), false);
	else if (cur.startsWith("%") && !cur.startsWith("%%")) codeedit->editor()->setText(cur.mid(1), false);
}

void UserMenuDialog::changeTypeToEnvironment()
{
	QString cur = codeedit->editor()->text();
	languages->setLanguage(codeedit->editor(), "");
	if (cur.startsWith("%SCRIPT\n")) {
		codeedit->editor()->setText("%" + cur.mid(8), false);
	} else {
		if (cur.startsWith("%") && !cur.startsWith("%%")) return;
		while (cur.startsWith("%%")) cur = cur.remove(0, 2);
		if (!cur.startsWith("%")) cur = "%" + cur;
		codeedit->editor()->setText(cur, false);
	}
}

void UserMenuDialog::changeTypeToScript()
{
	QString cur = codeedit->editor()->text();
	languages->setLanguage(codeedit->editor(), ".qs");
	if (cur.startsWith("%SCRIPT\n")) return;
	if (cur.startsWith("%") && !cur.startsWith("%%")) cur = cur.mid(1);
	codeedit->editor()->setText("%SCRIPT\n" + cur, false);
}

void UserMenuDialog::textChanged()
{
	setLanguageFromText();
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.setTypedTag(codeedit->editor()->text());
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
    }
}

void UserMenuDialog::nameChanged()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.name=ui.itemEdit->text();
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
        item->setText(0,m.name);
    }
}
void UserMenuDialog::descriptionChanged()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.description=ui.teDescription->document()->toPlainText();
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
    }
}

void UserMenuDialog::shortcutChanged()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.setShortcut(ui.cbShortcut->currentText());
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
        item->setText(1,m.shortcut());
    }
}

void UserMenuDialog::abbrevChanged()
{
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.abbrev=ui.abbrevEdit->text();
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
        item->setText(3,m.abbrev);
    }
}

void UserMenuDialog::triggerChanged()
{
    // check if trigger is a valid regex
    const QStringList fixedTriggers{"?txs-start","?new-file","?new-from-template","?load-file","?load-this-file","?save-file","?close-file","?master-changed","?after-typeset","?after-command-run"};
    const QString text=ui.triggerEdit->text();
    QRegularExpression re(text);
    if(!re.isValid() && !fixedTriggers.contains(text)){
        // syntax error in regex
        ui.triggerEdit->setToolTip(re.errorString()+tr(" (col. %1)").arg(re.patternErrorOffset()));
        ui.triggerEdit->setStyleSheet("QLineEdit { background: orange; color : black; }");

        return;
    }else{
        ui.triggerEdit->setStyleSheet(QString());
        ui.triggerEdit->setToolTip("");
    }
    // update current macro
    QTreeWidgetItem *item=ui.treeWidget->currentItem();
    if(item==nullptr) return;
    QVariant v=item->data(0,Qt::UserRole);
    if(v.isValid()){
        Macro m=v.value<Macro>();
        m.setTrigger(ui.triggerEdit->text());
        item->setData(0,Qt::UserRole,QVariant::fromValue(m));
        item->setText(2,m.trigger);
    }
}

void UserMenuDialog::showTooltip()
{
	QWidget *w = qobject_cast<QWidget *>(sender());
	if (!w) return;
	UtilsUi::txsInformation(w->toolTip());
}
