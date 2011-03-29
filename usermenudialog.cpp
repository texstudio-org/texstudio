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

class StringListTableModel: public QAbstractTableModel{
public:
	StringListTableModel(QObject* p):QAbstractTableModel(p){}
	virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void addStringList(QStringList* list, const QString& name);

	virtual void insertRow(int row, const QModelIndex &parent=QModelIndex());
	virtual void removeRow(int row, const QModelIndex &parent=QModelIndex());
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	int listId(const QStringList* sl) const;
private:
	QList<QPair<QString, QStringList*> > lists;
};

int StringListTableModel::rowCount ( const QModelIndex & parent) const{
	if (parent.isValid() || lists.isEmpty()) return 0;
	return lists.first().second->size();
}
int StringListTableModel::columnCount ( const QModelIndex & parent) const{
	return parent.isValid()?0:lists.size();
}
QVariant StringListTableModel::data ( const QModelIndex & index, int role) const{
	if (role != Qt::DisplayRole) return QVariant();
	if (index.column() >= lists.size()) return QVariant();
	if (index.row() >= lists[index.column()].second->size()) return QVariant();
	return lists[index.column()].second->at(index.row());
}

QVariant StringListTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (orientation == Qt::Vertical || role != Qt::DisplayRole) {
		return QAbstractTableModel::headerData(section,orientation,role);
	}
	if (section >= lists.size()) return QVariant();
	return lists[section].first;
}

void StringListTableModel::insertRow(int row, const QModelIndex &parent){
	if (parent.isValid()) return;
	beginInsertRows(parent,row,row);
	for (int i=0;i<lists.size();i++)
		lists[i].second->insert(row, "");
	endInsertRows();
}

void StringListTableModel::removeRow(int row, const QModelIndex &parent){
	if (parent.isValid() || row < 0) return;
	beginRemoveRows(parent,row,row);
	for (int i=0;i<lists.size();i++)
		lists[i].second->removeAt(row);
	endRemoveRows();
	//reset(); //begin/end removerows crashes
}

bool StringListTableModel::setData(const QModelIndex &index, const QVariant &value, int role){
	if (!index.isValid()) return false;
	lists[index.column()].second->replace(index.row(), value.toString());
	emit dataChanged(index,index);
	return true;
}

int StringListTableModel::listId(const QStringList* sl) const{
	for (int i=0;i<lists.size();i++)
		if (lists[i].second == sl) return i;
	return -1;
}

void StringListTableModel::addStringList(QStringList* list, const QString& name){
	lists << QPair<QString, QStringList*>(name,list);
}

UserMenuDialog::UserMenuDialog(QWidget* parent,  QString name, QLanguageFactory* languageFactory)
		: QDialog(parent), languages(languageFactory) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));

	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(slotAdd()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), SLOT(slotRemove()));


	connect(ui.radioButtonNormal, SIGNAL(clicked()), SLOT(changeTypeToNormal()));
	connect(ui.radioButtonEnvironment, SIGNAL(clicked()), SLOT(changeTypeToEnvironment()));
	connect(ui.radioButtonScript, SIGNAL(clicked()), SLOT(changeTypeToScript()));

	//editor options
	ui.tagEdit->setLayout(new QVBoxLayout());
	codeedit = new QCodeEdit(ui.tagEdit);
	QLineMarkPanel* lineMarkPanel=new QLineMarkPanel;
	QAction* lineMarkPanelAction=codeedit->addPanel(lineMarkPanel, QCodeEdit::West, false);
	Q_UNUSED(lineMarkPanelAction)
	QLineNumberPanel* lineNumberPanel=new QLineNumberPanel;
	QAction* lineNumberPanelAction=codeedit->addPanel(lineNumberPanel, QCodeEdit::West, false);;
	Q_UNUSED(lineNumberPanelAction)
	QAction* lineFoldPanelAction=codeedit->addPanel(new QFoldPanel, QCodeEdit::West, false);
	Q_UNUSED(lineFoldPanelAction)
	//QAction* vlineChangePanelAction=codeedit->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	QStatusPanel* statusPanel=new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	QAction* statusPanelAction=codeedit->addPanel(statusPanel, QCodeEdit::South, false);
	Q_UNUSED(statusPanelAction)

	QGotoLinePanel* gotoLinePanel=new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	QAction* gotoLinePanelAction=codeedit->addPanel(gotoLinePanel, QCodeEdit::South, false);
	Q_UNUSED(gotoLinePanelAction)

	searchReplacePanel=new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	QAction* searchReplacePanelAction=codeedit->addPanel(searchReplacePanel, QCodeEdit::South,false);
	searchReplacePanel->display(0,false);
	Q_UNUSED(searchReplacePanelAction)

	ui.tagEdit->layout()->addWidget(codeedit->editor());

	connect(codeedit->editor()->document(), SIGNAL(contentsChanged()), SLOT(textChanged()));
	connect(ui.itemEdit, SIGNAL(textEdited(QString)), SLOT(nameChanged()));
	connect(ui.abbrevEdit, SIGNAL(textEdited(QString)), SLOT(abbrevChanged()));
	connect(ui.triggerEdit, SIGNAL(textEdited(QString)), SLOT(triggerChanged()));

}

UserMenuDialog::~UserMenuDialog() {
	delete searchReplacePanel;
	delete codeedit;
}

void UserMenuDialog::init() {
	model = new StringListTableModel(this);
	model->addStringList(&names,tr("Name"));
	model->addStringList(&abbrevs,tr("Abbrev"));
	model->addStringList(&triggers,tr("Trigger"));
	model->addStringList(&tags,tr("Tag"));
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents();
	ui.tableView->resizeRowsToContents();
	connect(ui.tableView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(change(const QModelIndex&,const QModelIndex&)));
	if (model->rowCount()>0) ui.tableView->setCurrentIndex(model->index(0,0));
}

void UserMenuDialog::change(const QModelIndex& modelIndex,const QModelIndex&) {
	int index = modelIndex.row();
	if (index<0) return;
	codeedit->editor()->setText(tags.value(index,""));
	ui.itemEdit->setText(names.value(index,""));
	ui.abbrevEdit->setText(abbrevs.value(index,""));
	ui.triggerEdit->setText(triggers.value(index,""));

	if (languages){
		if (codeedit->editor()->text(0)=="%SCRIPT") languages->setLanguage(codeedit->editor(), ".qs");
		else if (codeedit->editor()->text(0).startsWith("%")) languages->setLanguage(codeedit->editor(), "");
		else languages->setLanguage(codeedit->editor(), "(La-)TeX Macro");
	}
}

void UserMenuDialog::slotOk() {
	accept();
}
void UserMenuDialog::slotAdd(){
	model->insertRow(ui.tableView->currentIndex().row()+1);
	if (model->rowCount() == 1) {
		model->setData(model->index(0, model->listId(&tags)), codeedit->editor()->text());
		model->setData(model->index(0, model->listId(&names)), ui.itemEdit->text());
		model->setData(model->index(0, model->listId(&abbrevs)), ui.abbrevEdit->text());
		model->setData(model->index(0, model->listId(&triggers)), ui.triggerEdit->text());
	}
	ui.tableView->setCurrentIndex(model->index(ui.tableView->currentIndex().row()+1,0));
}

void UserMenuDialog::slotRemove(){
	if (QMessageBox::question(this, "TexMakerX", "Do you really want to delete the current macro?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
		int index = ui.tableView->currentIndex().row();
		if (index < 0) return;
		model->removeRow(index);
		change(ui.tableView->currentIndex(),QModelIndex());
	}
}

void UserMenuDialog::changeTypeToNormal(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), "(La-)TeX Macro");
	if (cur.startsWith("%SCRIPT\n")) codeedit->editor()->setText(cur.mid(8));
	else if (cur.startsWith("%")) codeedit->editor()->setText(cur.mid(1));
}
void UserMenuDialog::changeTypeToEnvironment(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), "");
	if (cur.startsWith("%SCRIPT")) {
		codeedit->editor()->setText("%"+cur.mid(8));
	} else {
		if (cur.startsWith("%")) return;
		codeedit->editor()->setText("%"+cur);
	}
}
void UserMenuDialog::changeTypeToScript(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), ".qs");
	if (cur.startsWith("%SCRIPT\n")) return;
	if (cur.startsWith("%")) cur = cur.mid(1);
	codeedit->editor()->setText("%SCRIPT\n"+cur);
}
void UserMenuDialog::textChanged(){
	QString line = codeedit->editor()->text(0);
	if (line=="%SCRIPT") ui.radioButtonScript->setChecked(true);
	else if (line.startsWith("%")) ui.radioButtonEnvironment->setChecked(true);
	else ui.radioButtonNormal->setChecked(true);
	if (!ui.tableView->currentIndex().isValid()) return;
	int i = ui.tableView->currentIndex().row();
	model->setData(model->index(i, model->listId(&tags)), codeedit->editor()->text());

}
void UserMenuDialog::nameChanged(){
	if (!ui.tableView->currentIndex().isValid()) return;
	int i = ui.tableView->currentIndex().row();
	model->setData(model->index(i, model->listId(&names)), ui.itemEdit->text());
}
void UserMenuDialog::abbrevChanged(){
	if (!ui.tableView->currentIndex().isValid()) return;
	int i = ui.tableView->currentIndex().row();
	model->setData(model->index(i, model->listId(&abbrevs)), ui.abbrevEdit->text());
}
void UserMenuDialog::triggerChanged(){
	if (!ui.tableView->currentIndex().isValid()) return;
	int i = ui.tableView->currentIndex().row();
	model->setData(model->index(i, model->listId(&triggers)), ui.triggerEdit->text());
}
