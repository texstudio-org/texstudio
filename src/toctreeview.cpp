#include "toctreeview.h"
#include "latexstructure.h"
#include "latexdocument.h"
#include "configmanager.h"
#include "utilsUI.h"
#include "utilsSystem.h"
#include "editors.h"
#include "latexeditorview.h"
#include "tocitemtree.h"

TocTreeView::TocTreeView(const ConfigManager &config, QWidget *parent) :
	QTreeView(parent),
	configManager(config)
{
	header()->hide();
	setObjectName("TocTree");
	UtilsUi::enableTouchScrolling(this);

	if (configManager.indentationInStructure > 0)
		setIndentation(configManager.indentationInStructure);

}

void TocTreeView::refresh(LatexDocument* main)
{
	if (main == nullptr) return;
	setModel(new QTocItemTree(main->getFileInfo().absoluteFilePath()));
}