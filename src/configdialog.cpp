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
#include "configmanager.h"

#include "updatechecker.h"

#include "qdocument.h"

#include "spellerutility.h"
#include "latexeditorview_config.h"
#include "smallUsefulFunctions.h"
#include "qformatconfig.h"

#include "filedialog.h"

const QString ShortcutDelegate::addRowButton = "<internal: add row>";
const QString ShortcutDelegate::deleteRowButton = "<internal: delete row>";

static const QString nameSeparator = "separator";

ShortcutComboBox::ShortcutComboBox(QWidget *parent): QComboBox(parent)
{
	const Qt::Key SpecialKeys[]  = {Qt::Key_Tab, Qt::Key_Backspace, Qt::Key_Delete};
	const int SpecialKeysCount = 3;

	setObjectName("ShortcutComboBox");
	setMaxVisibleItems(15);
	addItem(tr("<default>"));
	addItem(tr("<none>"));
	for (int k = Qt::Key_F1; k <= Qt::Key_F12; k++)
		addItem(QKeySequence(k).toString(SHORTCUT_FORMAT));
	for (int m = 0; m <= 1; m++)
		for (int c = 0; c <= 1; c++)
			for (int s = 0; s <= 1; s++)
				for (int a = 0; a <= 1; a++) {
					if (a || c || s || m) {
						for (int k = Qt::Key_F1; k <= Qt::Key_F12; k++)
							addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + k).toString(SHORTCUT_FORMAT));
						for (int k = Qt::Key_0; k <= Qt::Key_9; k++)
							addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + k).toString(SHORTCUT_FORMAT));
						for (int k = Qt::Key_A; k <= Qt::Key_Z; k++)
							addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + k).toString(SHORTCUT_FORMAT));
						if (a || c) {
							for (int k = Qt::Key_Left; k <= Qt::Key_Down; k++)
								addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + k).toString(SHORTCUT_FORMAT));
							for (int k = Qt::Key_PageUp; k <= Qt::Key_PageDown; k++)
								addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + k).toString(SHORTCUT_FORMAT));
						}
					}
					for (int ik = 0; ik < SpecialKeysCount; ik++)
						addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META
														  + SpecialKeys[ik]).toString(SHORTCUT_FORMAT));
					//addItem(QKeySequence(c * Qt::CTRL + s * Qt::SHIFT + a * Qt::ALT + m * Qt::META + Qt::Key_Tab).toString(SHORTCUT_FORMAT));
				}
	setEditable(true);
}

void ShortcutComboBox::keyPressEvent(QKeyEvent *e)
{
	if ( (e->modifiers() != 0 && e->text() != "+" && e->key() != Qt::Key_Alt && e->key() != Qt::Key_Shift && e->key() != Qt::Key_Control && e->key() != Qt::Key_AltGr && e->key() != Qt::Key_Meta && e->key() != 0 && e->key() != Qt::Key_Super_L && e->key() != Qt::Key_Super_R)
	        || (e->key() >= Qt::Key_F1 &&  e->key() <= Qt::Key_F35)
	        || (e->key() == Qt::Key_Home)
	        || (e->key() == Qt::Key_End)
	        || (e->key() == Qt::Key_PageUp)
	        || (e->key() == Qt::Key_PageDown)
	        || (e->key() == Qt::Key_Up)
	        || (e->key() == Qt::Key_Down)
	   ) {
		// FIXME: Qt currently does not handle KeypadModifier correctly.
		// as a workaround we just take it away, so there is no difference between keypad and non-keypad keys,
		// but at least keypad keys don't produce rubbish. See also sf.net bug item 3525266
		QString newShortCut = QKeySequence((e->modifiers() | e->key()) & ~Qt::KeypadModifier).toString(SHORTCUT_FORMAT);
		int index = findText(newShortCut);
		if (index != -1) setCurrentIndex(index);
		else setEditText(newShortCut);
		return;
	}
	QComboBox::keyPressEvent(e);
}

void ShortcutComboBox::focusInEvent(QFocusEvent *e)
{
	Q_UNUSED(e);
	this->lineEdit()->selectAll();
}


ShortcutDelegate::ShortcutDelegate(QObject *parent): treeWidget(nullptr)
{
	Q_UNUSED(parent);
}
QWidget *ShortcutDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option ,
                                        const QModelIndex &index) const
{
	Q_UNUSED(option);

    if (!index.isValid()) return nullptr;
	const QAbstractItemModel *model = index.model();
	if (model->index(index.row(), 0, index.parent()).isValid() &&
	        model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole) == deleteRowButton) {
		//editor key replacement
        if (index.column() == 0) return nullptr;
		return new QLineEdit(parent);
	}

	//basic key
	if (isBasicEditorKey(index)) {
		if (index.column() == 0) {
			QComboBox *ops = new QComboBox(parent);
			foreach (int o, LatexEditorViewConfig::possibleEditOperations()) {
				ops->addItem(LatexEditorViewConfig::translateEditOperation(o), o);
			}
			return ops;
		}
        if (index.column() != 2) return nullptr;
		//continue as key
	}

	//menu shortcut key
	if (index.column() != 2 && index.column() != 3) {
		UtilsUi::txsWarning(tr("To change a shortcut, edit the column \"Current Shortcut\" or \"Additional Shortcut\"."));
        return nullptr;
	}
	ShortcutComboBox *editor = new ShortcutComboBox(parent);

	return editor;
}

void ShortcutDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
	QComboBox *box = qobject_cast<QComboBox *>(editor);
	//basic editor key
	if (box && isBasicEditorKey(index) && index.column() == 0) {
		box->setCurrentIndex(LatexEditorViewConfig::possibleEditOperations().indexOf(index.model()->data(index, Qt::UserRole).toInt()));
		return;
	}
	QString value = index.model()->data(index, Qt::EditRole).toString();
	//menu shortcut key
	if (box) {
		QString normalized = QKeySequence(value).toString(SHORTCUT_FORMAT);
		int pos = box->findText(normalized);
		if (pos == -1) box->setEditText(value);
		else box->setCurrentIndex(pos);
		if (box->lineEdit()) box->lineEdit()->selectAll();
		return;
	}
	//editor key replacement
	QLineEdit *le = qobject_cast<QLineEdit *>(editor);
	if (le) {
		le->setText(value);
	}
}

void ShortcutDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
	REQUIRE(model);
	QComboBox *box = qobject_cast<QComboBox *>(editor);
	//basic editor key
	if (box && isBasicEditorKey(index) && index.column() == 0) {
		model->setData(index, box->itemData(box->currentIndex(), Qt::UserRole), Qt::UserRole);
		model->setData(index, box->itemText(box->currentIndex()), Qt::EditRole);
		model->setData(index, box->itemText(box->currentIndex()), Qt::DisplayRole);
		return;
	}
	//editor key replacement
	QLineEdit *le = qobject_cast<QLineEdit *>(editor);
	if (le) {
		if (le->text().size() != 1 && index.column() == 1) {
			UtilsUi::txsWarning(tr("Only single characters are allowed as key"));
			return;
		}
		model->setData(index, le->text(), Qt::EditRole);
		return;
	}
	//menu shortcut key
	if (index.column() != 2 && index.column() != 3) return;
	if (!box) return;
	QString value = box->currentText();
	if (value == "" || value == "none" || value == tr("<none>")) value = "";
	else if (value == "<default>") ;
	else {
		value = QKeySequence(box->currentText()).toString(SHORTCUT_FORMAT);
		if (value == "" || (value.endsWith("+") && !value.endsWith("++"))) { //Alt+wrong=>Alt+
			UtilsUi::txsWarning(ConfigDialog::tr("The shortcut you entered is invalid."));
			return;
		}
		QString value_alternative = QKeySequence(box->currentText()).toString(QKeySequence::PortableText);
		QRegExp rxCharKey("(Shift\\+)?."); // matches all single characters and single characters with shift like "Shift+A", should not match e.g. "F1" or "DEL"
		if (rxCharKey.exactMatch(value_alternative)) {
			if (!UtilsUi::txsConfirmWarning(ConfigDialog::tr("The shortcut you entered is a standard character key.\n"
			                                        "You will not be able to type this character. Do you wish\n"
			                                        "to set the key anyway?"))) {
				return;
			}
		}

		/*int r=-1;
		for (int i=0;i<model->rowCount();i++)
		    if (model->data(model->index(i,2))==value) {
		        r=i;
		        break;
		        }*/
		if (treeWidget) {
			QList<QTreeWidgetItem *> li = treeWidget->findItems(value, Qt::MatchRecursive | Qt::MatchFixedString, 2);
			if (!li.empty() && li[0] && li[0]->text(0) == model->data(model->index(index.row(), 0, index.parent()))) li.removeFirst();
			QList<QTreeWidgetItem *> li2 = treeWidget->findItems(value, Qt::MatchRecursive | Qt::MatchFixedString, 3);
			if (!li2.empty() && li2[0] && li2[0]->text(0) == model->data(model->index(index.row(), 0, index.parent()))) li2.removeFirst();
			li << li2;
            // filter out elements which belong to other window i.e. pdfviewer <-> editor
            QModelIndex idx=model->index(index.row(),0,index.parent());
            QString id=idx.data(Qt::UserRole).toString();
            QStringList ids=id.split("/");
            QString progType=ids.value(0);
            for(int k=(li.size()-1);k>=0;k--){
                QTreeWidgetItem *item=li.at(k);
                QString id = item->data(0, Qt::UserRole).toString();
                QStringList ids=id.split("/");
                if(ids.value(0,"")!=progType)
                    li.removeAll(item);
            }
			REQUIRE(treeWidget->topLevelItem(1));
			REQUIRE(treeWidget->topLevelItem(1)->childCount() >= 1);
			QTreeWidgetItem *editorKeys = treeWidget->topLevelItem(1)->child(0);
			REQUIRE(editorKeys);
			if (!li.empty() && li.first()) {
				QStringList duplicates;
				foreach (QTreeWidgetItem *twi, li) {
					if (twi) duplicates << twi->text(0);
				}
				QString duplicate = duplicates.join("\n");
				if (UtilsUi::txsConfirmWarning(QString(ConfigDialog::tr("The shortcut <%1> is already assigned to the command:")).arg(value) + "\n" + duplicate + "\n\n" + ConfigDialog::tr("Do you wish to remove the old assignment and bind the shortcut to the new command?"))) {
					//model->setData(mil[0],"",Qt::DisplayRole);
					foreach (QTreeWidgetItem *twi, li) {
						if (twi and twi->text(2) == value) twi->setText(2, "");
					}
				} else {
					return;
				}
			}
		}
	}
	model->setData(index, value, Qt::EditRole);
}

void ShortcutDelegate ::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void ShortcutDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
	QStyle *style = QApplication::style();
	if (!style) QItemDelegate::drawDisplay(painter, option, rect, text);
	else if (text == "<internal: delete row>") {
		QStyleOptionButton sob;
		sob.text = tr("delete row");
		sob.state = QStyle::State_Enabled;
		sob.rect = rect;
		style->drawControl(QStyle::CE_PushButton, &sob, painter);
	} else if (text == "<internal: add row>") {
		QStyleOptionButton sob;
		sob.text = tr("add row");
		sob.state = QStyle::State_Enabled;
		sob.rect = rect;
		style->drawControl(QStyle::CE_PushButton, &  sob, painter);
	} else QItemDelegate::drawDisplay(painter, option, rect, text);
}

void ShortcutDelegate::treeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
	Q_ASSERT(item);
	if (column != 0 || !item) return;
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
	if (item->text(0) == deleteRowButton) {
		if (UtilsUi::txsConfirm(ConfigDialog::tr("Do you really want to delete this row?"))) {
			Q_ASSERT(item->parent());
			if (!item->parent()) return;
			item->parent()->removeChild(item);
		}
	} else if (item->text(0) == addRowButton) {
		REQUIRE(item->parent());
		REQUIRE(item->treeWidget());
		REQUIRE(item->treeWidget()->topLevelItem(1));
		QString newText = item->parent() == item->treeWidget()->topLevelItem(1)->child(1) ? deleteRowButton : "";
        QTreeWidgetItem *twi = new QTreeWidgetItem((QTreeWidgetItem *)nullptr, QStringList() << newText);
		twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
		item->parent()->insertChild(item->parent()->childCount() - 1, twi);
	}
}

bool ShortcutDelegate::isBasicEditorKey(const QModelIndex &index) const
{
#ifdef NO_POPPLER_PREVIEW
    const int cRow=1;
#else
    const int cRow=2;
#endif
	return index.parent().isValid() && index.parent().parent().isValid() &&
	       !index.parent().parent().parent().isValid() &&
	       index.parent().row() == 0 &&
           index.parent().parent().row() == cRow;
}


ComboBoxDelegate::ComboBoxDelegate(QObject *parent): QItemDelegate(parent)
{
	activeColumn = 2;
}
QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.column() != activeColumn)
		return QItemDelegate::createEditor(parent, option, index);
	QComboBox *editor = new QComboBox(parent);
	editor->addItems(defaultItems);
	editor->setEditable(true);

	return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (index.column() != activeColumn) {
		QItemDelegate::setEditorData(editor, index);
		return;
	}
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	REQUIRE(cb);
	QString s = index.data(Qt::EditRole).toString();
	if (s.contains('(')) s = s.left(s.indexOf('('));
	for (int i = 0; i < cb->count(); i++)
		if (cb->itemText(i).startsWith(s)) {
			cb->setCurrentIndex(i);
			break;
		}
	cb->setEditText(index.data(Qt::EditRole).toString());
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (index.column() != activeColumn) {
		QItemDelegate::setModelData(editor, model, index);
		return;
	}
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	REQUIRE(cb);
	model->setData(index, cb->currentText());
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.column() != activeColumn) {
		QItemDelegate::updateEditorGeometry(editor, option, index);
		return;
	}
	editor->setGeometry(option.rect);
}


int ConfigDialog::lastUsedPage = 0;

ConfigDialog::ConfigDialog(QWidget *parent): QDialog(parent), checkboxInternalPDFViewer(nullptr), riddled(false), oldToolbarIndex(-1), mBuildManager(nullptr)
{
	setModal(true);
	ui.setupUi(this);

	UtilsUi::enableTouchScrolling(ui.scrollAreaGeneral);
	UtilsUi::enableTouchScrolling(ui.scrollAreaBuild);
	UtilsUi::enableTouchScrolling(ui.menuTree);
	UtilsUi::enableTouchScrolling(ui.scrollAreaAdvancedEditor);
	UtilsUi::enableTouchScrolling(ui.twHighlighEnvirons);
	UtilsUi::enableTouchScrolling(ui.twCustomSyntax);
	UtilsUi::enableTouchScrolling(ui.scrollAreaGrammar);
	UtilsUi::enableTouchScrolling(ui.scrollAreaPreview);
	UtilsUi::enableTouchScrolling(ui.scrollAreaPDFviewer);

#ifdef Q_OS_MAC
	ui.labelSwitchKeyboardLayout->setDisabled(true);
	ui.checkBoxSwitchLanguagesDirection->setChecked(false);
	ui.checkBoxSwitchLanguagesDirection->setDisabled(true);
	ui.checkBoxSwitchLanguagesMath->setChecked(false);
	ui.checkBoxSwitchLanguagesMath->setDisabled(true);
#endif

#ifdef Q_OS_WIN
	ui.checkBoxUseQSaveWrite->setVisible(false);
#endif

	ui.contentsWidget->setIconSize(QSize(32, 32));
	//ui.contentsWidget->setViewMode(QListView::ListMode);
	//ui.contentsWidget->setMovement(QListView::Static);

	//pageGeneral
	connect(ui.pushButtonImportDictionary, SIGNAL(clicked()), this, SLOT(importDictionary()));
	connect(ui.pushButtonUpdateCheckNow, SIGNAL(clicked()), this, SLOT(updateCheckNow()));
	connect(UpdateChecker::instance(), SIGNAL(checkCompleted()), this, SLOT(refreshLastUpdateTime()));
	refreshLastUpdateTime();

	//pageditor
	populateComboBoxFont(false);
	connect(ui.checkBoxShowOnlyMonospacedFonts, SIGNAL(toggled(bool)), this, SLOT(populateComboBoxFont(bool)));

	QComboBox * encodingBoxes[3] = {ui.comboBoxEncoding, ui.comboBoxBibFileEncoding, ui.comboBoxLogFileEncoding};
	ui.comboBoxLogFileEncoding->addItem("Document"); //not translated so the config is language independent
	for (int i=0;i<3;i++) encodingBoxes[i]->addItem("UTF-8");
	foreach (int mib, QTextCodec::availableMibs()) {
		QTextCodec *codec = QTextCodec::codecForMib(mib);
		if (!codec) continue;
		if (codec->name() != "UTF-8") {
			for (int i=0;i<3;i++)
				encodingBoxes[i]->addItem(codec->name());
		}
	}

    ui.comboBoxThesaurusFileName->setCompleter(nullptr);

	connect(ui.pushButtonDictDir, SIGNAL(clicked()), this, SLOT(browseDictDir()));
	connect(ui.leDictDir, SIGNAL(textChanged(QString)), this, SLOT(updateDefaultDictSelection(QString)));

	connect(ui.btSelectThesaurusFileName, SIGNAL(clicked()), this, SLOT(browseThesaurus()));

	connect(ui.pushButtonPathLog, SIGNAL(clicked()), this, SLOT(browsePathLog()));
	connect(ui.pushButtonPathBib, SIGNAL(clicked()), this, SLOT(browsePathBib()));
	connect(ui.pushButtonPathImages, SIGNAL(clicked()), this, SLOT(browsePathImages()));
	connect(ui.pushButtonPathPdf, SIGNAL(clicked()), this, SLOT(browsePathPdf()));
	connect(ui.pushButtonPathCommands, SIGNAL(clicked()), this, SLOT(browsePathCommands()));

	connect(ui.comboBoxThesaurusFileName, SIGNAL(editTextChanged(QString)), this, SLOT(comboBoxWithPathEdited(QString)));
	connect(ui.comboBoxThesaurusFileName, SIGNAL(highlighted(QString)), this, SLOT(comboBoxWithPathHighlighted(QString)));


	ui.labelGetDic->setText(tr("Download additional dictionaries from %1 or %2").arg("<a href=\"http://extensions.openoffice.org/de/search?f[0]=field_project_tags%3A157\">OpenOffice</a>").arg("<a href=\"https://extensions.libreoffice.org/extensions?getCategories=Dictionary&getCompatibility=any\">LibreOffice</a>"));
	ui.labelGetDic->setOpenExternalLinks(true);
	//page custom environment
	connect(ui.pbAddLine, SIGNAL(clicked()), this, SLOT(custEnvAddLine()));
	connect(ui.pbRemoveLine, SIGNAL(clicked()), this, SLOT(custEnvRemoveLine()));
	connect(ui.pbAddSyntaxLine, SIGNAL(clicked()), this, SLOT(custSyntaxAddLine()));
	connect(ui.pbRemoveSyntaxLine, SIGNAL(clicked()), this, SLOT(custSyntaxRemoveLine()));
    environModes = nullptr;
	//pagequick
	connect(ui.pushButtonGrammarWordlists, SIGNAL(clicked()), this, SLOT(browseGrammarWordListsDir()));
	connect(ui.pushButtonGrammarLTPath, SIGNAL(clicked()), this, SLOT(browseGrammarLTPath()));
	connect(ui.pushButtonGrammarLTJava, SIGNAL(clicked()), this, SLOT(browseGrammarLTJavaPath()));
    connect(ui.pushButtonResetLTURL, SIGNAL(clicked()), this, SLOT(resetLTURL()));
    connect(ui.pushButtonResetLTArgs, SIGNAL(clicked()), this, SLOT(resetLTArgs()));


	fmConfig = new QFormatConfig(ui.formatConfigBox, parent->styleSheet().isEmpty());
	fmConfig->setToolTip(tr("Here the syntax highlighting for various commands, environments and selections can be changed."));
	fmConfig->addCategory(tr("Basic highlighting")) << "normal" << "background" << "comment" << "magicComment" << "commentTodo" << "keyword" << "extra-keyword" << "math-delimiter" << "math-keyword" << "numbers" << "text" << "align-ampersand" << "environment" << "structure" << "link" << "escapeseq" << "verbatim" << "picture" << "picture-keyword" << "preedit";
	fmConfig->addCategory(tr("LaTeX checking")) << "braceMatch" << "braceMismatch" << "latexSyntaxMistake" << "referencePresent" << "referenceMissing" << "referenceMultiple" << "citationPresent" << "citationMissing" << "packagePresent" << "packageMissing" << "temporaryCodeCompletion";
	fmConfig->addCategory(tr("Language checking")) << "spellingMistake" << "wordRepetition" << "wordRepetitionLongRange" << "badWord" << "grammarMistake" << "grammarMistakeSpecial1" << "grammarMistakeSpecial2" << "grammarMistakeSpecial3" << "grammarMistakeSpecial4";
	fmConfig->addCategory(tr("Line highlighting"))     << "line:error" << "line:warning" << "line:badbox" << "line:bookmark" << "line:bookmark0" << "line:bookmark1" << "line:bookmark2" << "line:bookmark3" << "line:bookmark4" << "line:bookmark5" << "line:bookmark6"  << "line:bookmark7" << "line:bookmark8" << "line:bookmark9" << "current";
	fmConfig->addCategory(tr("Search")) << "search" << "replacement" << "selection";
	fmConfig->addCategory(tr("Diff")) << "diffDelete" << "diffAdd" << "diffReplace";
	fmConfig->addCategory(tr("Preview")) << "previewSelection";
	fmConfig->addCategory(tr("DTX files")) << "dtx:guard" << "dtx:macro" << "dtx:verbatim" << "dtx:specialchar" << "dtx:commands";
	fmConfig->addCategory(tr("Sweave / Pweave")) << "sweave-delimiter" << "sweave-block" << "pweave-delimiter" << "pweave-block";
	fmConfig->addCategory(tr("Asymptote")) << "asymptote:block" << "asymptote:keyword" << "asymptote:type" << "asymptote:numbers" << "asymptote:string" << "asymptote:comment";
	fmConfig->addCategory(tr("Lua")) << "lua:keyword" << "lua:comment";
	fmConfig->addCategory(tr("QtScript")) << "qtscript:comment" << "qtscript:string" << "qtscript:number" << "qtscript:keyword" << "qtscript:txs-variable" << "qtscript:txs-function";

	connect(ui.spinBoxSize, SIGNAL(valueChanged(int)), fmConfig, SLOT(setBasePointSize(int)));

	//fmConfig->setMaximumSize(490,300);
	//fmConfig->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom, ui.formatConfigBox);
	layout->setMargin(0);
	layout->insertWidget(0, fmConfig);

	ui.shortcutTree->setHeaderLabels(QStringList() << tr("Command") << tr("Default Shortcut") << tr("Current Shortcut") << tr("Additional Shortcut"));
	ui.shortcutTree->setColumnWidth(0, 200);

	//create icons
	createIcon(tr("General"), getRealIcon("config_general"));
	createIcon(tr("Commands"), getRealIcon("config_commands"));
	createIcon(tr("Build"), getRealIcon("config_quickbuild"));
	createIcon(tr("Shortcuts"), getRealIcon("config_shortcut"));
	createIcon(tr("Menus"), getRealIcon("config_latexmenus"), true);
	createIcon(tr("Toolbars"), getRealIcon("config_toolbars"), true);
	createIcon(tr("GUI Scaling"), getRealIcon("config_toolbars"), true);
	createIcon(tr("Editor"), getRealIcon("config_editor"));
	createIcon(tr("Adv. Editor"), getRealIcon("config_advancededitor"), true);
	createIcon(tr("Syntax Highlighting"), getRealIcon("config_highlighting"));
	createIcon(tr("Custom Highlighting"), getRealIcon("config_highlighting"), true);
	createIcon(tr("Completion"), getRealIcon("config_completion"));
	createIcon(tr("Language Checking"), getRealIcon("config_editor"));
	createIcon(tr("Preview"), getRealIcon("config_preview"));
	createIcon(tr("Internal PDF Viewer"), getRealIcon("config_preview"));
	createIcon(tr("SVN"), getRealIcon("config_svn"));

	connect(ui.contentsWidget,
	        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
	        this, SLOT(changePage(QListWidgetItem *, QListWidgetItem *)));
	ui.contentsWidget->setCurrentRow(lastUsedPage);
	connect(ui.checkBoxShowAdvancedOptions, SIGNAL(toggled(bool)), this, SLOT(advancedOptionsToggled(bool)));
	connect(ui.checkBoxShowAdvancedOptions, SIGNAL(clicked(bool)), this, SLOT(advancedOptionsClicked(bool)));

	// custom toolbars
	connect(ui.comboBoxToolbars, SIGNAL(currentIndexChanged(int)), SLOT(toolbarChanged(int)));
	ui.listCustomToolBar->setIconSize(QSize(22, 22));
	ui.listCustomToolBar->setViewMode(QListView::ListMode);
	ui.listCustomToolBar->setMovement(QListView::Snap);
	ui.listCustomToolBar->setDragDropMode(QAbstractItemView::InternalMove);
	connect(this, SIGNAL(accepted()), SLOT(checkToolbarMoved()));
	connect(ui.pbToToolbar, SIGNAL(clicked()), this, SLOT(toToolbarClicked()));
	connect(ui.pbFromToolbar, SIGNAL(clicked()), this, SLOT(fromToolbarClicked()));
	ui.listCustomToolBar->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.listCustomToolBar, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
	connect(ui.listCustomToolBar, SIGNAL(doubleClicked(QModelIndex)), SLOT(fromToolbarClicked()));

	connect(ui.comboBoxActions, SIGNAL(currentIndexChanged(int)), SLOT(actionsChanged(int)));
	connect(ui.treePossibleToolbarActions, SIGNAL(doubleClicked(QModelIndex)), SLOT(toToolbarClicked()));

#if QT_VERSION >= 0x040400
	ui.treePossibleToolbarActions->setHeaderHidden(true);
#endif
	//	ui.listCustomToolBar->setSelectionMode(QAbstractItemView::ExtendedSelection);
	//	ui.treePossibleToolbarActions->setSelectionMode(QAbstractItemView::ExtendedSelection);

#if (QT_VERSION < 0x040600) || (!defined(Q_WS_X11)&&!defined(Q_OS_UNIX))
	ui.checkBoxUseSystemTheme->setVisible(false);
#endif

#if QT_VERSION < 0x040800
	ui.checkBoxVisualColumnMode->setChecked(false);
	ui.checkBoxVisualColumnMode->setEnabled(false);
#endif

#if QT_VERSION >= 0x040603
	ui.lineEditMetaFilter->setPlaceholderText(tr("(option filter)"));
#endif
	connect(ui.lineEditMetaFilter, SIGNAL(textChanged(QString)), SLOT(metaFilterChanged(QString)));

	// poppler preview
#ifdef NO_POPPLER_PREVIEW
	int l = ui.comboBoxDvi2PngMode->count();
	ui.comboBoxDvi2PngMode->removeItem(l - 1);
	l = ui.comboBoxPreviewMode->count();
	ui.comboBoxPreviewMode->removeItem(l - 1);
	// maybe add some possibility to disable some preview modes in poppler mode
#endif

	// set-up GUI scaling
	connect(ui.tbRevertIcon, SIGNAL(clicked()), this, SLOT(revertClicked()));
	connect(ui.tbRevertCentralIcon, SIGNAL(clicked()), this, SLOT(revertClicked()));
	connect(ui.tbRevertSymbol, SIGNAL(clicked()), this, SLOT(revertClicked()));

	// limit dialog size
	QRect screen = QApplication::desktop()->screenGeometry();
	if (!screen.isEmpty()) {
		int nwidth = width(), nheight = height();
		if (nwidth > screen.width()) nwidth = screen.width();
		if (nheight > screen.height()) nheight = screen.height();
		if (nwidth == width() && nheight == height()) return;
		resize(nwidth, nheight);
		move(frameGeometry().right() > screen.right() ? screen.left() : x(),
		     frameGeometry().bottom() > screen.bottom() ? screen.left() : y());
	}
}

ConfigDialog::~ConfigDialog()
{
}

QListWidgetItem *ConfigDialog::createIcon(const QString &caption, const QIcon &icon, bool advancedOption)
{
	QListWidgetItem *button = new QListWidgetItem(ui.contentsWidget);
	button->setIcon(icon);
	button->setText(caption);
	button->setToolTip(caption);
	//button->setTextAlignment(Qt::AlignVCenter);
	button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	if (advancedOption) {
		//button->setHidden(true);
		button->setData(Qt::UserRole, true);
	}
	return button;
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	lastUsedPage = ui.contentsWidget->row(current);
	ui.pagesWidget->setCurrentIndex(lastUsedPage);
}

void ConfigDialog::revertClicked()
{
	QToolButton *bt = qobject_cast<QToolButton *>(sender());
	if (bt) {
		if (bt->objectName() == "tbRevertIcon") {
			ui.horizontalSliderIcon->setValue(22);
		}
		if (bt->objectName() == "tbRevertCentralIcon") {
			ui.horizontalSliderCentraIcon->setValue(16);
		}
		if (bt->objectName() == "tbRevertSymbol") {
			ui.horizontalSliderSymbol->setValue(32);
		}
	}
}

//sets the items of a combobox to the filenames and sub-directory names in the directory which name
//is the current text of the combobox
void ConfigDialog::comboBoxWithPathEdited(const QString &newText)
{
	if (newText.isEmpty()) return;
	QComboBox *box = qobject_cast<QComboBox *>(sender());
	if (!box) return;
	if (box->property("lastDirInDropDown").toString() == newText && !newText.endsWith("/") && !newText.endsWith(QDir::separator())) {
		box->setEditText(newText + QDir::separator());
		box->setProperty("lastDirInDropDown", "");
		return;
	}
	QString path;
	int lastSep = qMax(newText.lastIndexOf("/"), newText.lastIndexOf(QDir::separator()));
	if ((lastSep > 0) || (newText == "") || (QDir::separator() != '/') ) path = newText.mid(0, lastSep);
	else path = "/";
	QString oldPath = box->property("dir").toString();
	if (path == oldPath) return;
	//prevent endless recursion + dir caching
	box->setProperty("dir", path);
	int curPos = box->lineEdit()->cursorPosition();
	box->clear();
	box->addItem(newText); //adding a new item in the empty list will set the edit text to it
	box->lineEdit()->setCursorPosition(curPos); // set Cursor to position before clearing

	QDir dir(path);
	QString absPath = dir.absolutePath();
	if (absPath == oldPath || (absPath + QDir::separator()) == oldPath) return;
	if (!absPath.endsWith("/") && !absPath.endsWith(QDir::separator())) absPath += QDir::separator();
	QStringList entries = dir.entryList(QStringList() << box->property("dirFilter").toString(), QDir::Files);
	foreach (const QString &file, entries)
		if (absPath + file != newText)
			box->addItem(absPath + file);
	entries = dir.entryList(QStringList(), QDir::AllDirs);
	foreach (const QString &file, entries)
		if (absPath + file != newText && file != ".")
			box->addItem(absPath + file);
}

void ConfigDialog::comboBoxWithPathHighlighted(const QString &newText)
{
	QComboBox *cb = qobject_cast<QComboBox *> (sender());
	Q_ASSERT(cb);
	if (!cb) return;
	if (!QFileInfo(newText).isDir()) {
		cb->setProperty("lastDirInDropDown", "");
		return;
	}
	cb->setProperty("lastDirInDropDown", newText);
}

void ConfigDialog::browseThesaurus()
{
	UtilsUi::browse(ui.comboBoxThesaurusFileName, tr("Select thesaurus database"), "Database (*.dat)");
}

void ConfigDialog::browseGrammarWordListsDir()
{
	UtilsUi::browse(ui.lineEditGrammarWordlists, tr("Select the grammar word lists dir"), "/");
}

void ConfigDialog::browseGrammarLTPath()
{
	UtilsUi::browse(ui.lineEditGrammarLTPath, tr("Select the LanguageTool jar"), "Java-Program (*.jar)");
}

void ConfigDialog::browseGrammarLTJavaPath()
{
	UtilsUi::browse(ui.lineEditGrammarLTJava, tr("Select java"), "Java (*)");
}

void ConfigDialog::resetLTArgs(){
    ui.lineEditGrammarLTArguments->setText("org.languagetool.server.HTTPServer -p 8081");
}

void ConfigDialog::resetLTURL(){
    ui.lineEditGrammarLTUrl->setText("http://localhost:8081/");
}

void ConfigDialog::browseDictDir()
{
	UtilsUi::browse(ui.leDictDir, tr("Select dictionary directory"), "/");
}

void ConfigDialog::browsePathLog()
{
	UtilsUi::browse(ui.lineEditPathLog, tr("Search Path for Logs"), "/", QDir::currentPath(), true);
}

void ConfigDialog::browsePathBib()
{
	UtilsUi::browse(ui.lineEditPathBib, tr("Search Path .bib Files"), "/", QDir::currentPath(), true);
}

void ConfigDialog::browsePathImages()
{
	UtilsUi::browse(ui.lineEditPathImages, tr("Search Path for Images"), "/", QDir::currentPath(), true);
}

void ConfigDialog::browsePathPdf()
{
	UtilsUi::browse(ui.lineEditPathPDF, tr("Search Path for PDFs"), "/", QDir::currentPath(), true);
}

void ConfigDialog::browsePathCommands()
{
	UtilsUi::browse(ui.lineEditPathCommands, tr("Search Path for Commands"), "/", QDir::rootPath(), true);
}

void ConfigDialog::updateDefaultDictSelection(const QString &dictPaths, const QString &newDefault)
{
	QString lang = ui.comboBoxSpellcheckLang->currentText();
	ui.comboBoxSpellcheckLang->clear();

	ConfigManager *config = dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
	if (!config) return;
	SpellerManager sm;
	sm.setDictPaths(config->parseDirList(dictPaths));
	ui.comboBoxSpellcheckLang->addItems(sm.availableDicts());
	if (ui.comboBoxSpellcheckLang->count() == 0) {
		ui.comboBoxSpellcheckLang->addItem("<none>");
	}

	// update selected language
	int index = -1;
	if (!newDefault.isNull()) index = ui.comboBoxSpellcheckLang->findText(newDefault);
	if (index < 0) index = ui.comboBoxSpellcheckLang->findText(lang); // keep selected language
	if (index >= 0) {
		ui.comboBoxSpellcheckLang->setCurrentIndex(index);
	}
}

void ConfigDialog::hideShowAdvancedOptions(QWidget *w, bool on)
{
	foreach (QObject *o, w->children()) {
		QWidget *w = qobject_cast<QWidget *> (o);
		if (!w) continue;
		if (w->property("advancedOption").toBool()) {
			bool realOn = on && !w->property("hideWidget").toBool();
			w->setVisible(realOn);
		}
		// special treatment for metacommads
		static QStringList simpleMetaOptions = QStringList() << "quick" << "compile" << "view" << "view-pdf" << "bibliography";
		if (simpleMetaOptions.contains(w->objectName())) {
			QComboBox *cb = qobject_cast<QComboBox *> (o);
			if (cb) {
				if (on) {
					CommandMapping tempCommands = mBuildManager->getAllCommands();
					CommandInfo cmd = tempCommands.value(w->objectName());
					QString text = cb->currentText();
					int i = cb->findText(text);
					if (i >= 0)
						text = cmd.metaSuggestionList.value(i, tr("<unknown>"));
					cb->clear();
					cb->addItems(cmd.metaSuggestionList);
					cb->setEditable(true);
					cb->setEditText(text);
				} else {
					CommandMapping tempCommands = mBuildManager->getAllCommands();
					CommandInfo cmd = tempCommands.value(w->objectName());
					QString text = cb->currentText();
					int i = cmd.metaSuggestionList.indexOf(text);
					//if(i>=0)
					//   text=cmd.simpleDescriptionList.value(i,tr("<unknown>"));
					cb->clear();
					if (i >= 0) {
						foreach (QString elem, cmd.simpleDescriptionList) {
							elem = qApp->translate("BuildManager", qPrintable(elem));
							cb->addItem(elem);
						}
						cb->setCurrentIndex(i);
						cb->setEditable(false);
					} else {
						cb->addItems(cmd.metaSuggestionList);
						cb->setEditable(true);
						cb->setEditText(text);
					}
				}
			}
		}
		hideShowAdvancedOptions(w, on);
	}
}

void ConfigDialog::advancedOptionsToggled(bool on)
{
	QListWidgetItem *currentPage = ui.contentsWidget->currentItem();

	hideShowAdvancedOptions(this, on);
	ui.contentsWidget->reset();
	for (int i = 0; i < ui.contentsWidget->count(); i++)
		if (ui.contentsWidget->item(i)->data(Qt::UserRole).toBool())
			ui.contentsWidget->item(i)->setHidden(!on);

	if (currentPage && !currentPage->isHidden()) {
		currentPage->setSelected(true);
		ui.contentsWidget->setCurrentItem(currentPage);
	} else {
		ui.contentsWidget->setCurrentRow(0);
	}
}

void ConfigDialog::advancedOptionsClicked(bool on)
{
	if (on) {
		if (!askRiddle()) ui.checkBoxShowAdvancedOptions->setChecked(false);
		else riddled = true;
	}
}

bool ConfigDialog::metaFilterRecurseWidget(const QString &filter, QWidget *widget)
{
	if (!widget) return false;
	bool showThis = widget->property("text").toString().contains(filter, Qt::CaseInsensitive)
	                || widget->property("toolTip").toString().contains(filter, Qt::CaseInsensitive)
	                || widget->property("title").toString().contains(filter, Qt::CaseInsensitive);
	if (!showThis) {
		QComboBox *comboBoxCast;
		if ((comboBoxCast = qobject_cast<QComboBox *>(widget))) {
			for (int i = 0; i < comboBoxCast->count() && !showThis; i++)
				if (comboBoxCast->itemText(i).contains(filter, Qt::CaseInsensitive))
					showThis = true;
		}
	}
	//check type, some widgets have internal widgets that freeze when they become visible
	if (qobject_cast<QGroupBox *>(widget)) showThis |= metaFilterRecurseLayout(filter, widget->layout());
	else if (qobject_cast<QScrollArea *>(widget)) showThis |= metaFilterRecurseLayout(filter, (qobject_cast<QScrollArea *>(widget))->widget()->layout());
	if (!widget->property("hideWidget").toBool())
		widget->setVisible(showThis);
	return showThis;
}

bool ConfigDialog::metaFilterRecurseLayout(const QString &filter, QLayout *layout)
{
	if (!layout) return false;
	bool showThis = false;
	QList<int> visibles;
	for (int i = 0; i < layout->count(); i++) {
		QLayoutItem *item = layout->itemAt(i);
		bool show = metaFilterRecurseWidget(filter, item->widget());
		show |= metaFilterRecurseLayout(filter, item->layout());
		showThis |= show;

		if (show && !filter.isEmpty()) visibles << i;
	}
	if (visibles.count() != layout->count()) {
		// show related widgets in the same row
		// check boxes are self-contained and have no relations
		QGridLayout *grid = qobject_cast<QGridLayout *>(layout);
		if (grid) {
			foreach (int item, visibles) {
				if (qobject_cast<QCheckBox *>(grid->itemAt(item)->widget())) continue;
				int row, col, rowSpan, colSpan;
				grid->getItemPosition(item, &row, &col, &rowSpan, &colSpan);
				for (int c = 0; c < grid->columnCount(); c++) {
					QLayoutItem *li = grid->itemAtPosition(row, c);
					if (li && li->widget()) li->widget()->setVisible(true);
				}
			}
			return showThis;
		}
		QHBoxLayout *hbox = qobject_cast<QHBoxLayout *>(layout);
		if (hbox) {
			for (int i = 0; i < hbox->count(); i++) {
				QWidget *w = hbox->itemAt(i)->widget();
				if (w)
					w->setVisible(!w->property("hideWidget").toBool());
			}
			return showThis;
		}
	}
	return showThis;
}

void ConfigDialog::metaFilterChanged(const QString &filter)
{
	QListWidgetItem *currentPage = ui.contentsWidget->currentItem();

	ui.checkBoxShowAdvancedOptions->setEnabled(filter.isEmpty());

	for (int i = 0; i < ui.pagesWidget->count(); i++) {
		bool shown = metaFilterRecurseLayout(filter, ui.pagesWidget->widget(i)->layout());
		/*QWidget * page = ui.pagesWidget->widget(i);
		foreach (QObject* o, page->children()){
			QWidget* w = qobject_cast<QWidget*>(o);
			if (w) shown |= metaFilterRecurse(filter,  w);
		}*/
		ui.contentsWidget->item(i)->setHidden(!shown);
	}

	if (currentPage && !currentPage->isHidden()) {
		currentPage->setSelected(true);
		ui.contentsWidget->setCurrentItem(currentPage);
	} else for (int i = 0; i < ui.contentsWidget->count(); i++)
			if (!ui.contentsWidget->item(i)->isHidden()) {
				ui.contentsWidget->setCurrentRow(i);
				break;
			}
	if (filter.isEmpty()) advancedOptionsToggled(ui.checkBoxShowAdvancedOptions->isChecked());
}

void ConfigDialog::toolbarChanged(int toolbar)
{
	if (toolbar < 0 || toolbar >= customizableToolbars.size()) return;
	checkToolbarMoved();
	ui.listCustomToolBar->clear();
	foreach (const QString &actName, customizableToolbars[toolbar]) {
		QAction *act = menuParent->findChild<QAction *>(actName);
		QListWidgetItem *item;
		if (act) {
			QIcon i = act->icon().pixmap(22, 22);
			item = new QListWidgetItem(i, act->text().replace("&", ""));
		} else item = new QListWidgetItem(actName);
		item->setData(Qt::UserRole, actName);
		if (actName == nameSeparator) item->setIcon(QIcon(":/images/separator.png"));
		ui.listCustomToolBar->addItem(item);
	}
	oldToolbarIndex = toolbar;
}

void ConfigDialog::actionsChanged(int actionClass)
{
	ui.treePossibleToolbarActions->clear();
	ui.treePossibleToolbarActions->setRootIsDecorated(actionClass != 0);
	if (actionClass == 2) {
		//TODO: allow other tags, no hard coding
		QTreeWidgetItem *twi;
		twi = new QTreeWidgetItem(QStringList() << "tags/brackets/left");
		twi->setData(0, Qt::UserRole, "tags/brackets/left");
		ui.treePossibleToolbarActions->addTopLevelItem(twi);
		twi = new QTreeWidgetItem(QStringList() << "tags/brackets/right");
		twi->setData(0, Qt::UserRole, "tags/brackets/right");
		ui.treePossibleToolbarActions->addTopLevelItem(twi);
		return;
	}

	const QList<QMenu *> &menus = (actionClass == 0) ? standardToolbarMenus : allMenus;
	foreach (const QMenu *menu, menus)
        populatePossibleActions(nullptr, menu, actionClass != 0);
}

void ConfigDialog::toToolbarClicked()
{
	if (!ui.treePossibleToolbarActions->currentItem()) return;
	if (ui.comboBoxToolbars->currentIndex() < 0 || ui.comboBoxToolbars->currentIndex() >= customizableToolbars.size()) return;
	checkToolbarMoved();
	QTreeWidgetItem *twi = ui.treePossibleToolbarActions->currentItem();
	QString actName = twi->data(0, Qt::UserRole).toString();
	QAction *act = menuParent->findChild<QAction *>(actName);
	QListWidgetItem *item;
	if (act) item = new QListWidgetItem(twi->icon(0), act->text().replace("&", ""));
	else item = new QListWidgetItem(twi->icon(0), actName);
	item->setData(Qt::UserRole, actName);
	ui.listCustomToolBar->addItem(item);
	customizableToolbars[ui.comboBoxToolbars->currentIndex()].append(actName);
}

void ConfigDialog::fromToolbarClicked()
{
	if (!ui.listCustomToolBar->currentItem()) return;
	if (ui.comboBoxToolbars->currentIndex() < 0 || ui.comboBoxToolbars->currentIndex() >= customizableToolbars.size()) return;
	checkToolbarMoved();
	customizableToolbars[ui.comboBoxToolbars->currentIndex()].removeAt(ui.listCustomToolBar->currentRow());
	delete ui.listCustomToolBar->takeItem(ui.listCustomToolBar->currentRow());
}

void ConfigDialog::checkToolbarMoved()
{
	if (oldToolbarIndex < 0 || oldToolbarIndex >= customizableToolbars.size()) return;
	REQUIRE(ui.listCustomToolBar->count() == customizableToolbars[oldToolbarIndex].size());
	for (int i = 0; i < ui.listCustomToolBar->count(); i++)
		customizableToolbars[oldToolbarIndex][i] = ui.listCustomToolBar->item(i)->data(Qt::UserRole).toString();

}

void ConfigDialog::customContextMenuRequested(const QPoint &p)
{
	QMenu menu;
	menu.addAction(tr("Load Other Icon"), this, SLOT(loadOtherIcon()));
	menu.addAction(tr("Insert Separator"), this, SLOT(insertSeparator()));
	menu.exec(ui.listCustomToolBar->mapToGlobal(p));
}

void ConfigDialog::loadOtherIcon()
{
	QListWidgetItem *item = ui.listCustomToolBar->currentItem();
	if (!item) {
		UtilsUi::txsWarning(tr("You need to add an action to the toolbar (from the list of actions on the right side), before you can load an icon for that item."));
		return;
	}
	QString fn = FileDialog::getOpenFileName(this, tr("Select a File"), "", tr("Images") + " (*.png *.xpm *.jpg *.jpeg *.bmp *.svg)");

	if (!fn.isEmpty()) {
		item->setIcon(QIcon(fn));
		fn = ConfigManager::getInstance()->reverseParseDir(fn);
		replacedIconsOnMenus->insert(item->data(Qt::UserRole).toString(), fn);
		ui.listCustomToolBar->reset();
		// set the same icon on other list
		//TODO QList<QListWidgetItem *>result=ui.listCustomIcons->findItems(item->text(),Qt::MatchExactly);
		//foreach(QListWidgetItem *elem,result){
		//  elem->setIcon(QIcon(fn));
		//}
	}
}

void ConfigDialog::insertSeparator()
{
	int row = ui.listCustomToolBar->currentRow();
	if (row < 0) return;
	ui.listCustomToolBar->insertItem(row, nameSeparator);
	ui.listCustomToolBar->item(row)->setData(Qt::UserRole, nameSeparator);
	ui.listCustomToolBar->item(row)->setIcon(QIcon(":/images/separator.png"));
	customizableToolbars[ui.comboBoxToolbars->currentIndex()].insert(row, nameSeparator);
}

void ConfigDialog::populatePossibleActions(QTreeWidgetItem *parent, const QMenu *menu, bool keepHierarchy)
{
	if (!menu) return;
	QList<QAction *> acts = menu->actions();
	if (keepHierarchy) {
		QTreeWidgetItem *twi = new QTreeWidgetItem(parent, QStringList() << menu->title().replace("&", ""));
		twi->setData(0, Qt::UserRole, menu->objectName());
		if (parent) parent->addChild(twi);
		else ui.treePossibleToolbarActions->addTopLevelItem(twi);
		parent = twi;
	}
	for (int i = 0; i < acts.size(); i++)
		if (acts[i]->menu()) {
			populatePossibleActions(parent, acts[i]->menu(), keepHierarchy);
		} else {
			//if(acts[i]->data().isValid()){
			QTreeWidgetItem *twi = new QTreeWidgetItem(parent, QStringList() << acts[i]->text().replace("&", ""));
			if (acts[i]->isSeparator()) {
				twi->setIcon(0, QIcon(":/images/separator.png"));
			} else {
				if (!acts[i]->icon().isNull()) twi->setIcon(0, acts[i]->icon());
				else twi->setIcon(0, QIcon(":/images/appicon.png"));
			}
			twi->setToolTip(0, acts[i]->text());
			if (acts[i]->isSeparator()) twi->setData(0, Qt::UserRole, nameSeparator);
			else twi->setData(0, Qt::UserRole, acts[i]->objectName());
			if (parent) parent->addChild(twi);
			else ui.treePossibleToolbarActions->addTopLevelItem(twi);
		}
}

void ConfigDialog::importDictionary()
{
    QString filename = FileDialog::getOpenFileName(this, tr("Import Dictionary"), QString(), tr("OpenOffice Dictionary") + " (*.oxt)", nullptr, QFileDialog::DontResolveSymlinks);
	if (filename.isNull()) return;

	ConfigManager *config = dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
	if (!config) return;

	QString targetDir = config->parseDir("[txs-settings-dir]/dictionaries");
	targetDir.replace("//", "/");  // resolution of [txs-settings-dir] may lead to duplicate path separators
	SpellerManager::importDictionary(filename, targetDir);

	if (!config->parseDirList(ui.leDictDir->text()).contains(targetDir)) {
		if (UtilsUi::txsConfirm(tr("The dictionary files have been imported to\n%1.\nHowever this path is not contained in the dictionary path list. Do you want to add it?").arg(targetDir))) {
			ui.leDictDir->setText(ui.leDictDir->text() + ";[txs-settings-dir]/dictionaries");
		}
	}

	updateDefaultDictSelection(ui.leDictDir->text(), QFileInfo(filename).baseName()); // TODO: better detection for new dictionary name (.dic filename may be different from .oxt filename)
}

void ConfigDialog::updateCheckNow()
{
	UpdateChecker::instance()->check(false);
}

void ConfigDialog::refreshLastUpdateTime()
{
	ui.labelUpdateCheckDate->setText(UpdateChecker::lastCheckAsString());
}

void ConfigDialog::populateComboBoxFont(bool onlyMonospaced)
{
	QString currentFont = ui.comboBoxFont->currentText();
	ui.comboBoxFont->clear();
	QFontDatabase fdb;
	if (onlyMonospaced) {
		foreach (const QString &font, fdb.families()) {
			if (fdb.isFixedPitch(font)) {
				ui.comboBoxFont->addItem(font);
			}
		}
	} else {
		ui.comboBoxFont->addItems(fdb.families());
	}
	// restore font setting if possible
	int idx = ui.comboBoxFont->findText(currentFont);
	if (idx >= 0) ui.comboBoxFont->setCurrentIndex(idx);

}

void ConfigDialog::custEnvAddLine()
{
	int i = ui.twHighlighEnvirons->rowCount();
	ui.twHighlighEnvirons->setRowCount(i + 1);

	QStringList lst;
	if (environModes)
		lst = *environModes;
	else
		lst << "verbatim" << "math";

	QTableWidgetItem *item = new QTableWidgetItem("");
	ui.twHighlighEnvirons->setItem(i, 0, item);
    QComboBox *cb = new QComboBox(nullptr);
	cb->insertItems(0, lst);
	ui.twHighlighEnvirons->setCellWidget(i, 1, cb);
}

void ConfigDialog::custEnvRemoveLine()
{
	int i = ui.twHighlighEnvirons->currentRow();
	if (i < 0)
		i = ui.twHighlighEnvirons->rowCount() - 1;

	ui.twHighlighEnvirons->removeRow(i);

	i = ui.twHighlighEnvirons->rowCount();
	if (i == 0) {
		ui.twHighlighEnvirons->setRowCount(i + 1);

		QStringList lst;
		if (environModes)
			lst = *environModes;
		else
			lst << "verbatim" << "math";

		QTableWidgetItem *item = new QTableWidgetItem("");
		ui.twHighlighEnvirons->setItem(i, 0, item);
        QComboBox *cb = new QComboBox(nullptr);
		cb->insertItems(0, lst);
		ui.twHighlighEnvirons->setCellWidget(i, 1, cb);
	}
}

void ConfigDialog::custSyntaxAddLine()
{
	int i = ui.twCustomSyntax->rowCount();
	ui.twCustomSyntax->setRowCount(i + 1);

	QTableWidgetItem *item = new QTableWidgetItem("");
	ui.twCustomSyntax->setItem(i, 0, item);
}

void ConfigDialog::custSyntaxRemoveLine()
{
	int i = ui.twCustomSyntax->currentRow();
	if (i < 0)
		i = ui.twCustomSyntax->rowCount() - 1;
	ui.twCustomSyntax->removeRow(i);

	i = ui.twCustomSyntax->rowCount();
	if (i == 0) {
		ui.twCustomSyntax->setRowCount(i + 1);

		QTableWidgetItem *item = new QTableWidgetItem("");
		ui.twCustomSyntax->setItem(i, 0, item);
	}
}

bool ConfigDialog::askRiddle()
{
	UtilsUi::txsInformation(tr("You have enabled the advanced options. This allows one to\n"
	                  "configure TXS in great detail. Disable the advanced\n"
	                  "options again to only view the most common settings."));
	return true;

	/*
	QString solution = QInputDialog::getText(this, tr("Riddle"), tr(
			"You come to a magic island where you meet three strange and wise friends. \n"
			"One of them is always telling the truth, another one is always lying, and the third is deaf, so he answers randomly and cannot lie(!). \n"
			"You ask the first: \"Are you lying?\", and he answers: \"No\".\n"
			"You ask the second: \"Is the first one lying?\", and he answers: \"No\".\n"
			"You ask the last: \"Is the second one lying?\", and he answers: \"No\".\n\n"
	              "Which one of the three wise will always tell the truth?"), QLineEdit::Normal, riddled?"3":"");
	if (solution.isEmpty()) return false;
	bool a1 = solution.contains("1") || solution.contains(tr("first"),Qt::CaseInsensitive) || solution.contains(tr("one"),Qt::CaseInsensitive);
	bool a2 = solution.contains("2") || solution.contains(tr("second"),Qt::CaseInsensitive) || solution.contains(tr("two"),Qt::CaseInsensitive);
	bool a3 = solution.contains("3") || solution.contains(tr("third"),Qt::CaseInsensitive) || solution.contains(tr("three"),Qt::CaseInsensitive) || solution.contains(tr("last"),Qt::CaseInsensitive);
	if (!a1 && !a2 && !a3) { QMessageBox::warning(this,tr("Riddle"),tr("Please answer 1, 2 or 3")); return false; }
	if ((a1 && a2) || (a1 && a3) || (a2 && a3)) { QMessageBox::warning(this,tr("Riddle"),tr("Only one answer allowed")); return false; }
	if (a3) return true;
	return false;
	*/
}

