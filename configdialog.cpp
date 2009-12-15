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

#include "configdialog.h"

#include <QCompleter>
#if QT_VERSION >= 0x040400
#include <QFileSystemModel>
#else
#include <QDirModel>
#endif

#include "qdocument.h"

#if QT_VERSION >= 0x040400
class FileSystemCompleter: public QCompleter{
public:
	FileSystemCompleter(QObject *p=0);
    virtual QString pathFromIndex(const QModelIndex &index) const;
    virtual QStringList splitPath(const QString &path) const;
};
//copied from Qt source
FileSystemCompleter::FileSystemCompleter(QObject *p): QCompleter(p){
	#ifdef Q_WS_WIN
		setCaseSensitivity ( Qt::CaseInsensitive);
	#endif
}
QString FileSystemCompleter::pathFromIndex(const QModelIndex& index) const
{
    if (!index.isValid())
        return QString();

    QFileSystemModel *dirModel = qobject_cast<QFileSystemModel*>(model());
    if (!dirModel)
        return model()->data(index, Qt::EditRole).toString();

    QModelIndex idx = index;
    QStringList list;
    do {
        QString t = dirModel->data(idx, Qt::EditRole).toString();
        list.prepend(t);
        QModelIndex parent = idx.parent();
        idx = parent.sibling(parent.row(), index.column());
    } while (idx.isValid());

#if !defined(Q_OS_WIN) || defined(Q_OS_WINCE)
    if (list.count() == 1) // only the separator or some other text
        return list[0];
    list[0].clear() ; // the join below will provide the separator
#endif

    return list.join(QDir::separator());
}

QStringList FileSystemCompleter::splitPath(const QString& path) const
{
	QFileSystemModel *fsm = qobject_cast<QFileSystemModel *>(model());
    bool isDirModel = fsm;
    if (!isDirModel || path.isEmpty())
        return QStringList(completionPrefix());

    QString pathCopy = QDir::toNativeSeparators(path);
    QString sep = QDir::separator();
#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    if (pathCopy == QLatin1String("\\") || pathCopy == QLatin1String("\\\\"))
        return QStringList(pathCopy);
    QString doubleSlash(QLatin1String("\\\\"));
    if (pathCopy.startsWith(doubleSlash))
        pathCopy = pathCopy.mid(2);
    else
        doubleSlash.clear();
#endif

    QRegExp re(QLatin1String("[") + QRegExp::escape(sep) + QLatin1String("]"));
    QStringList parts = pathCopy.split(re);

#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    if (!doubleSlash.isEmpty())
        parts[0].prepend(doubleSlash);
#else
    if (pathCopy[0] == sep[0]) // readd the "/" at the beginning as the split removed it
        parts[0] = QDir::fromNativeSeparators(QString(sep[0]));
#endif

	fsm->setRootPath(path.mid(0,path.lastIndexOf(re)).replace("\\","/"));

    return parts;
}
#endif

const QString ShortcutDelegate::addRowButton="<internal: add row>";
const QString ShortcutDelegate::deleteRowButton="<internal: delete row>";

ShortcutDelegate::ShortcutDelegate(QObject *parent): treeWidget(0) {
	// remove unused argument warning
	(void) parent;
}
QWidget *ShortcutDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem & option ,
                                        const QModelIndex & index) const {
	// remove unused argument warning
	(void) option;

	if (!index.isValid()) return 0;
	const QAbstractItemModel *model = index.model();
	if (model->index(index.row(),0,index.parent()).isValid() && model->data(model->index(index.row(),0,index.parent()),Qt::DisplayRole) == deleteRowButton) {
		//editor key replacement
		if (index.column()==0) return 0;
		return new QLineEdit(parent);
	}
	//menu shortcut key
	if (index.column()!=2 && index.column()!=3) return 0;
	QComboBox *editor = new QComboBox(parent);
	editor->addItem(tr("<default>"));
	editor->addItem(tr("<none>"));
	for (int k=Qt::Key_F1; k<=Qt::Key_F12; k++)
		editor->addItem(QKeySequence(k).toString(QKeySequence::NativeText));
	for (int c=0; c<=1; c++)
		for (int s=0; s<=1; s++)
			for (int a=0; a<=1; a++) {
				if (!c && !s && !a) continue;
				for (int k=Qt::Key_F1; k<=Qt::Key_F12; k++)
					editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
				for (int k=Qt::Key_0; k<=Qt::Key_9; k++)
					editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
				for (int k=Qt::Key_A; k<=Qt::Key_Z; k++)
					editor->addItem(QKeySequence(c*Qt::CTRL+s*Qt::SHIFT+a*Qt::ALT+k).toString(QKeySequence::NativeText));
			}
	editor->setEditable(true);

	return editor;
}

void ShortcutDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
	QString value = index.model()->data(index, Qt::EditRole).toString();
	//menu shortcut key
	QComboBox *box = qobject_cast<QComboBox*>(editor);
	if (box) {
		QString normalized=QKeySequence(value).toString(QKeySequence::NativeText);
		int pos=box->findText(normalized);
		if (pos==-1) box->setEditText(value);
		else box->setCurrentIndex(pos);
		return;
	}
	//editor key replacement
	QLineEdit *le = qobject_cast<QLineEdit*>(editor);
	if (le) {
		le->setText(value);
	}
}
void ShortcutDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
	//editor key replacement
	QLineEdit *le = qobject_cast<QLineEdit*>(editor);
	if (le) {
		if (le->text().size()!=1 && index.column()==1) {
			QMessageBox::warning(editor,"TexMakerX",tr("Only single characters are allowed as key"),QMessageBox::Ok);
			return;
		}
		model->setData(index, le->text(), Qt::EditRole);
		return;
	}
	//menu shortcut key
	if (index.column()!=2 && index.column()!=3) return;
	QComboBox *box = qobject_cast<QComboBox*>(editor);
	if (!box) return;
	QString value=box->currentText();
	if (value=="" || value=="none" || value==tr("<none>")) value="";
	else if (value=="<default>") ;
	else {
		value=QKeySequence(box->currentText()).toString(QKeySequence::NativeText);
		if (value=="" || (value.endsWith("+") && !value.endsWith("++"))) { //Alt+wrong=>Alt+
			QMessageBox::warning(editor, ConfigDialog::tr("TexMakerX"),
			                     ConfigDialog::tr("The shortcut you entered is invalid."),
			                     QMessageBox::Ok, QMessageBox::Ok);
			return;
		}

		/*int r=-1;
		for (int i=0;i<model->rowCount();i++)
		    if (model->data(model->index(i,2))==value) {
		        r=i;
		        break;
		        }*/
		if (treeWidget) {
			QList<QTreeWidgetItem *> li=treeWidget->findItems(value, Qt::MatchRecursive |Qt::MatchFixedString, 2);
			if (!li.empty() && li[0]->text(0) == model->data(model->index(index.row(),0,index.parent()))) li.removeFirst();
			QList<QTreeWidgetItem *> li2=treeWidget->findItems(value, Qt::MatchRecursive |Qt::MatchFixedString, 3);
			if (!li2.empty() && li2[0]->text(0) == model->data(model->index(index.row(),0,index.parent()))) li2.removeFirst();
			li << li2;
			if (!li.empty()) {
				QString duplicate=li[0]->text(0);//model->data(model->index(mil[0].row(),0,mil[0].parent()),Qt::DisplayRole).toString();
				switch (QMessageBox::warning(editor, ConfigDialog::tr("TexMakerX"),
				                             ConfigDialog::tr("The shortcut you entered is the same as the one of this command:") +"\n"+duplicate+"\n"+ConfigDialog::tr("Should I delete this other shortcut?"),
				                             QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes)) {
				case QMessageBox::Yes:
					//model->setData(mil[0],"",Qt::DisplayRole);
					if (li[0]->text(2) == value)  li[0]->setText(2,"");
					else if (li[0]->text(3) == value)  li[0]->setText(3,"");
					break;
				default:
					;
				}
			}
		}
	}
	model->setData(index, value, Qt::EditRole);
}
void ShortcutDelegate ::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &/* index */) const {
	editor->setGeometry(option.rect);
}

void ShortcutDelegate::drawDisplay(QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text) const {
	QStyle *style = QApplication::style();
	if (!style) QItemDelegate::drawDisplay(painter, option, rect, text);
	else if (text=="<internal: delete row>") {
		QStyleOptionButton sob;
		sob.text = tr("delete row");
		sob.state = QStyle::State_Enabled;
		sob.rect = rect;
		style->drawControl(QStyle::CE_PushButton, &sob, painter);
	} else if (text=="<internal: add row>") {
		QStyleOptionButton sob;
		sob.text = tr("add row");
		sob.state = QStyle::State_Enabled;
		sob.rect = rect;
		style->drawControl(QStyle::CE_PushButton, &  sob, painter);
	} else QItemDelegate::drawDisplay(painter, option, rect, text);
}

void ShortcutDelegate::treeWidgetItemClicked(QTreeWidgetItem * item, int column) {
	if (column!=0) return;
	/*QStyle *style = QApplication::style ();
	QPainter p(item->treeWidget ());
	QStyleOptionButton sob;
	sob.rect=item->treeWidget ()->visualItemRect(item);
	sob.state = QStyle::State_Enabled|QStyle::State_Sunken;
	if (style)
	    if (item->text(0)=="<internal: delete row>") {
	       sob.text = tr("delete row");
	       style->drawControl(QStyle::CE_PushButton, &sob, &p);
	    } else if (item->text(0)=="<internal: add row>"){
	       sob.text = tr("add row");
	       style->drawControl(QStyle::CE_PushButton, &  sob, &p);
	    }*/
	if (item->text(0)==deleteRowButton) {
		switch (QMessageBox::question(item->treeWidget(), ConfigDialog::tr("TexMakerX"),
		                              ConfigDialog::tr("Do you really want to delete this row?"),
		                              QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes)) {
		case QMessageBox::Yes:
			item->parent()->removeChild(item);
			break;
		default:
			;
		}
	} else if (item->text(0)==addRowButton) {
		QTreeWidgetItem *twi = new QTreeWidgetItem((QTreeWidgetItem*)0,QStringList() << "<internal: delete row>");
		twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
		item->parent()->insertChild(item->parent()->childCount()-1, twi);
	}
}

ConfigDialog::ConfigDialog(QWidget* parent): QDialog(parent) {
	setModal(true);
	ui.setupUi(this);

	ui.contentsWidget->setIconSize(QSize(96, 96));
	ui.contentsWidget->setViewMode(QListView::IconMode);
	ui.contentsWidget->setMovement(QListView::Static);

//pageditor
	QFontDatabase fdb;
	ui.comboBoxFont->addItems(fdb.families());

	ui.comboBoxEncoding->addItem("UTF-8");
	foreach(int mib, QTextCodec::availableMibs()) {
		QTextCodec *codec = QTextCodec::codecForMib(mib);
		if (codec->name()!="UTF-8") ui.comboBoxEncoding->addItem(codec->name());
	}


	connect(ui.pushButtonAspell, SIGNAL(clicked()), this, SLOT(browseAspell()));
	connect(ui.btSelectThesaurusFileName, SIGNAL(clicked()), this, SLOT(browseThesaurus()));
	connect(ui.lineEditAspellCommand, SIGNAL(textChanged(QString)), this, SLOT(lineEditAspellChanged(QString)));

	ui.labelGetDic->setText(tr("Get dictionaries at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>"));
	ui.labelGetDic->setOpenExternalLinks(true);

//pagequick
	connect(ui.radioButton6, SIGNAL(toggled(bool)),ui.lineEditUserquick, SLOT(setEnabled(bool)));

	connect(ui.pushButtonExecuteBeforeCompiling, SIGNAL(clicked()), this, SLOT(browsePrecompiling()));


	fmConfig=new QFormatConfig(ui.formatConfigBox);
	fmConfig->addScheme("",QDocument::formatFactory());
//fmConfig->setMaximumSize(490,300);
//fmConfig->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
	(new QBoxLayout(QBoxLayout::TopToBottom, ui.formatConfigBox))->insertWidget(0,fmConfig);


	ui.shortcutTree->setHeaderLabels(QStringList()<<tr("Command")<<tr("Default Shortcut")<<tr("Current Shortcut")<<tr("Additional Shortcut"));
	ui.shortcutTree->setColumnWidth(0,200);
/*
	//QFileSystemModel is faster than QDirModel but requires Qt4.4
	#if QT_VERSION >= 0x040400
		QCompleter* dictionaryCompleter = new FileSystemCompleter(this);
		QFileSystemModel* dictionaryModel = new QFileSystemModel(dictionaryCompleter);
		dictionaryModel->setFilter(QDir::AllDirs | QDir::Files);
		dictionaryModel->setNameFilters (QStringList()<<"*.dic");
		dictionaryModel->setNameFilterDisables(false);
		dictionaryModel->setRootPath(ui.lineEditAspellCommand->text());
	#else
		QCompleter* dictionaryCompleter = new QCompleter(this);
		QDirModel * dictionaryModel =new QDirModel(QStringList()<<"*.dic",QDir::AllDirs | QDir::Files,QDir::Name | QDir::IgnoreCase | QDir::DirsFirst, dictionaryCompleter);
		dictionaryModel->setReadOnly(true);
		dictionaryModel->setLazyChildCount(true);
	#endif
	dictionaryCompleter->setModel(dictionaryModel);
	ui.lineEditAspellCommand->setCompleter(dictionaryCompleter);
	
	#if QT_VERSION >= 0x040400
		QCompleter* thesaurusCompleter = new FileSystemCompleter(this);
		QFileSystemModel* thesaurusModel = new QFileSystemModel(thesaurusCompleter);
		thesaurusModel->setFilter(QDir::AllDirs | QDir::Files);
		thesaurusModel->setNameFilters (QStringList()<<"*.dat");
		thesaurusModel->setNameFilterDisables(false);
		dictionaryModel->setRootPath(ui.thesaurusFileName->text());
	#else
		QCompleter* thesaurusCompleter = new QCompleter(this);
		QDirModel * thesaurusModel =new QDirModel(QStringList()<<"*.dat",QDir::AllDirs | QDir::Files,QDir::Name | QDir::IgnoreCase | QDir::DirsFirst, thesaurusCompleter);
		thesaurusModel->setReadOnly(true);
		thesaurusModel->setLazyChildCount(true);
	#endif
	thesaurusCompleter->setModel(thesaurusModel);
	ui.thesaurusFileName->setCompleter(thesaurusCompleter);
	*/
	
	//create icons
	createIcon(tr("General"),QIcon(":/images/configgeneral.png"));
	createIcon(tr("Commands"),QIcon(":/images/configtools.png"));
	createIcon(tr("Quick Build"),QIcon(":/images/configquick.png"));
	createIcon(tr("Shortcuts"),QIcon(":/images/configkeys.png"));
	createIcon(tr("Editor"),QIcon(":/images/configeditor.png"));
	createIcon(tr("Completion"),QIcon(":/images/configcompletion.png"));

	connect(ui.contentsWidget,
	        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
	        this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
	ui.contentsWidget->setCurrentRow(0);
	connect(ui.checkBoxShowAdvancedOptions, SIGNAL(toggled(bool)), this, SLOT(advancedOptionsToggled(bool)));
}

ConfigDialog::~ConfigDialog() {
}

QListWidgetItem * ConfigDialog::createIcon(const QString &caption, const QIcon &icon){
	QListWidgetItem * button=new QListWidgetItem(ui.contentsWidget);
	button->setIcon(icon);
	button->setText(caption);
	button->setTextAlignment(Qt::AlignHCenter);
	button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	return button;
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous) {
	if (!current)
		current = previous;

	ui.pagesWidget->setCurrentIndex(ui.contentsWidget->row(current));
}


//pageditor
void ConfigDialog::browseAspell() {
	QString path=ui.lineEditAspellCommand->text();
	if (path.isEmpty()) path=QDir::homePath();
	QString location=QFileDialog::getOpenFileName(this,tr("Browse dictionary"),path,"Dictionary (*.dic)",0,QFileDialog::DontResolveSymlinks);
	if (!location.isEmpty()) {
		location.replace(QString("\\"),QString("/"));
//	location="\""+location+"\"";
		ui.lineEditAspellCommand->setText(location);
	}
}
void ConfigDialog::lineEditAspellChanged(QString newText) {
	if (QFile(newText).exists()) {
		ui.lineEditAspellCommand->setStyleSheet(QString());
		ui.labelGetDic->setText(tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>"));
	} else {
		ui.lineEditAspellCommand->setStyleSheet(QString("QLineEdit {background: red}"));
		ui.labelGetDic->setText("<font color=\"red\">"+tr("(Dictionary doesn't exists)")+"</font><br>"+tr("Get dictionary at: %1").arg("<br><a href=\"http://wiki.services.openoffice.org/wiki/Dictionaries\">http://wiki.services.openoffice.org/wiki/Dictionaries</a>"));
	}
}

void ConfigDialog::browseThesaurus() {
	QString path=ui.thesaurusFileName->text();
	if (path.isEmpty()) path=QDir::homePath();
	QString location=QFileDialog::getOpenFileName(this,tr("Browse thesaurus database"),path,"Database (*.dat)",0,QFileDialog::DontResolveSymlinks);
	if (!location.isEmpty()) {
		location.replace(QString("\\"),QString("/"));
//	location="\""+location+"\"";
		ui.thesaurusFileName->setText(location);
	}
}

void ConfigDialog::browsePrecompiling() {
	QString path=ui.lineEditExecuteBeforeCompiling->text();
	if (path.startsWith('"')) path.remove(0,1);
	if (path.endsWith('"')) path.chop(1);
	if (path.isEmpty()) path=QDir::rootPath();
	QString location=QFileDialog::getOpenFileName(this,tr("Browse program"),path,"Program (*)",0,QFileDialog::DontResolveSymlinks);
	if (!location.isEmpty()) {
		location.replace(QString("\\"),QString("/"));
		location="\""+location+"\"";
		ui.lineEditExecuteBeforeCompiling->setText(location);
	}
}

void hideShowAdvancedOptions(QWidget* w, bool on){
	foreach (QObject* o, w->children()){
		QWidget* w = qobject_cast<QWidget*> (o);
		if (!w) continue;
		if (w->property("advancedOption").isValid() && w->property("advancedOption").toBool())
			w->setVisible(on);
		hideShowAdvancedOptions(w,on);
	}
}

void ConfigDialog::advancedOptionsToggled(bool on){
	hideShowAdvancedOptions(this,on);
}


