#include "editors.h"
#include "txstabwidget.h"
#include "mostQtHeaders.h"
#include "utilsSystem.h"
#include "latexeditorview.h"
#include "latexdocument.h"  // TODO: used for toolip in updateDocumentStatus. Anyway, tooltip content should be genereated dynamically. So this will go away here.


/*!
 * This class manages all editors and their positioning in tabWidgets.
 *
 * It maintains the knowledge of the currentEditor() and the currentTabWidget().
 * Also, it sends appropriate signals to the editors and tabWidgets and provides
 * singals to hook to these changes.
 *
 * Currently this class serves two purposes:
 *
 * 1) It maintains and abstract order of editors. Editors can be grouped (currently
 *    implemented as tabs in tabWidgets). The groups are ordered and the editors
 *    within a group are ordered, thus providing a complete order of all editors.
 *    The main purpose of this class it to provide an interface to this order, which
 *    can be used in the main program without having to know details on the actual
 *    organization of groups.
 *
 * 2) It contains all tabWidgets and thus editors providing a simple horizontal or
 *    vertical layout of the tab groups (there are currently 2 groups).
 *    This purpose is secondary and mainly implemented for an easier transition from
 *    the single tabGroup to more complex editor layouts. It may be changed in the
 *    future and will probably move to a separate class. The public interface of the
 *    class should depend on this as little as possible.
 */
Editors::Editors(QWidget *parent) :
	QWidget(parent), splitter(0), currentGroupIndex(-1)
{
	splitter = new QSplitter();
	splitter->setOrientation(Qt::Horizontal);
	splitter->setChildrenCollapsible(false);
	splitter->setHandleWidth(0);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(splitter);
	connect(this, SIGNAL(editorsReordered()), this, SIGNAL(listOfEditorsChanged()));
}

/*!
 * Adds the given tabWidget. This take ownership of the tabWidget.
 */
void Editors::addTabWidget(TxsTabWidget *w)
{
	splitter->addWidget(w);
	tabGroups.append(w);
	if (currentGroupIndex < 0) {
		currentGroupIndex = 0;
		w->setActive(true);
	} else {
		if (w->isEmpty()) w->hide();
	}
	connect(w, SIGNAL(currentEditorChanged()), SLOT(onTabWidgetEditorChanged()));
	connect(w, SIGNAL(editorAboutToChangeByTabClick(LatexEditorView *, LatexEditorView *)), this, SLOT(onEditorChangeByTabClick(LatexEditorView *, LatexEditorView *)));
	connect(w, SIGNAL(activationRequest()), SLOT(activateTabWidgetFromSender()));
	connect(w, SIGNAL(closeCurrentEditorRequest()), SIGNAL(closeCurrentEditorRequest()));
	connect(w, SIGNAL(tabBarContextMenuRequested(QPoint)), SLOT(tabBarContextMenu(QPoint)));
	connect(w, SIGNAL(tabMoved(int, int)), SIGNAL(editorsReordered()));
}

void Editors::addEditor(LatexEditorView *edView, bool asCurrent)
{
	insertEditor(edView, currentTabWidget(), -1, asCurrent);
}

void Editors::insertEditor(LatexEditorView *edView, int index, bool asCurrent)
{
	if (index >= 0) {
		for (int group = 0; group < tabGroups.length(); group++) {
			if (tabGroups[group]->count() > index) {
				insertEditor(edView, tabGroups[group], index, asCurrent);
				return;
			}
			index -= tabGroups[group]->count();
		}
		// index out of range: append
	}

	// append to last non-empty group
	for (int group = tabGroups.length() - 1; group >= 0; group--) {
		if (!tabGroups[group]->isEmpty() || group == 0) {
			insertEditor(edView, tabGroups[group], -1, asCurrent);
			break;
		}
	}
}

void Editors::moveEditor(LatexEditorView *edView, Editors::Position pos)
{
	switch (pos) {
	case AbsoluteFront:
		moveToTabGroup(edView, tabGroups.first(), 0);
		break;
	case AbsoluteEnd: {
		int lastNonHiddenIndex = tabGroups.size() - 1;
		while (lastNonHiddenIndex > 0 && tabGroups[lastNonHiddenIndex]->isHidden()) {
			lastNonHiddenIndex--;
		}
		if (lastNonHiddenIndex < 0) return;
		moveToTabGroup(edView, tabGroups[lastNonHiddenIndex], -1);
		break;
	}
	case GroupFront: {
		TxsTabWidget *tw = tabWidgetFromEditor(edView);
		moveToTabGroup(edView, tw, 0);
		break;
	}
	case GroupEnd: {
		TxsTabWidget *tw = tabWidgetFromEditor(edView);
		moveToTabGroup(edView, tw, -1);
		break;
	}
	}
}

/*!
 * Insert the editor in the given tabWidget at pos.
 * If tabWidget is 0, insert into the current tabWidget.
 * If pos == -1, append.
 * If asCurrent, make the editor the current editor.
 */
void Editors::insertEditor(LatexEditorView *edView, TxsTabWidget *tabWidget, int pos, bool asCurrent)
{

	if (!tabWidget) return;
	if (!tabWidget->isVisible()) {
		tabWidget->setVisible(true);
		// distribute available space
		QList<int> sizes;
		for (int i = 0; i < splitter->count(); i++) {
			sizes << 10; // excess space is distributed equally
		}
		splitter->setSizes(sizes);
	}
	tabWidget->insertEditor(edView, pos, asCurrent);
	connect(edView, SIGNAL(focusReceived()), this, SLOT(setCurrentEditorFromSender()));
	if (asCurrent) {
		setCurrentEditor(edView);
	}
	emit listOfEditorsChanged();
}

/*!
 * Remove the editor from the list of editors
 */
void Editors::removeEditor(LatexEditorView *edView)
{
	disconnect(edView, SIGNAL(focusReceived()), this, SLOT(setCurrentEditorFromSender()));
	removeEditor(edView, tabWidgetFromEditor(edView));
}

/*!
 * Remove the editor from the given tabWidget and hides the widget if its empty and not the only one.
 */
void Editors::removeEditor(LatexEditorView *edView, TxsTabWidget *tabWidget)
{
	if (!tabWidget) return;
	bool isLastEditorInGroup = (tabWidget->indexOf(edView) == tabWidget->count() - 1);
	bool isLastGroup = (currentGroupIndex == tabGroups.length() - 1);
	if (edView == currentEditor()) {
		if (isLastGroup && isLastEditorInGroup) {
			activatePreviousEditor();
		} else {
			activateNextEditor();
		}
	}
	tabWidget->removeEditor(edView);
	if (tabWidget->isEmpty() && tabWidget != tabGroups[0]) {
		tabWidget->hide();
	}
	emit listOfEditorsChanged();
}

/*!
 * Send the signal closeCurrentEditorRequest() and closes the editor.
 * This functions was inherited from the TxsTabWidget API. In contrast to removeEditor(),
 * which is a low-level function (purpose 1: maintain an abstract order of editors), this
 * is part of the purpose 2 API (editor container widget).
 *
 * TODO: Check if we really need this or if it can be simplified.
 */
void Editors::closeEditor(LatexEditorView *edView)
{
	TxsTabWidget *tabWidget = tabWidgetFromEditor(edView);
	if (!tabWidget) return;
	bool isLastEditorInGroup = (tabWidget->indexOf(edView) == tabWidget->count() - 1);
	bool isLastGroup = (currentGroupIndex == tabGroups.length() - 1);

	// lot's of workaround because claseTab assumes the edView is current
	LatexEditorView *oldEditor = currentEditor();
	if (edView == currentEditor()) {
		if (isLastGroup && isLastEditorInGroup) {
			activatePreviousEditor();
		} else {
			activateNextEditor();
		}
	}
	LatexEditorView *newEditor = currentEditor();
	setCurrentEditor(oldEditor);

	tabWidget->closeTab(edView);
	if (tabWidget->isEmpty() && tabWidget != tabGroups[0]) {
		tabWidget->hide();
	}
	setCurrentEditor(newEditor);
	emit listOfEditorsChanged();
}

bool Editors::containsEditor(LatexEditorView *edView) const
{
	return tabGroupIndexFromEditor(edView) >= 0;
}

TxsTabWidget *Editors::currentTabWidget() const
{
	if (currentGroupIndex >= 0 && currentGroupIndex < tabGroups.length())
		return tabGroups[currentGroupIndex];
	return 0;
}

/*!
 * Returns the tabText of the current editor or a null string.
 */
QString Editors::currentTabText() const
{
	TxsTabWidget *tw = currentTabWidget();
	if (tw && tw->currentIndex() >= 0)
		return tw->tabText(tw->currentIndex());
	return QString();
}

/*!
 * This updates icon tab text and tooltip.
 * This is called from the main program, when it thinks that the
 * document status of the current editor is changed.
 *
 * TODO: can we make the LatexEditorView notify us when a change is
 * necessary instead of the main program?
 */
void Editors::updateDocumentStatus()
{
	//cache icons, getRealIcon is *really* slow
	static QIcon modified = getRealIcon("modified");
	static QIcon empty = QIcon(":/images/empty.png");

	TxsTabWidget *tabGroup = currentTabWidget();
	LatexEditorView *edView = currentEditor();
	if (!tabGroup) return;
	if (!edView) return;

	// update icon
	int index = tabGroup->currentIndex();
	tabGroup->setTabIcon(index, edView->editor->isContentModified() ? modified : empty);
	// update tab text
	tabGroup->setTabText(index, edView->displayName().replace("&", "&&"));
	// update tooltip text
	LatexDocument *doc = edView->document;
	LatexDocument *rootDoc = doc->getRootDocument();
	QString tooltip = QDir::toNativeSeparators(edView->editor->fileName());
	if (doc != rootDoc) {
		tooltip += tr("\nincluded document in %1").arg(rootDoc->getName());
	}
	tabGroup->setTabToolTip(index, tooltip);
}

LatexEditorView *Editors::currentEditor() const
{
	TxsTabWidget *tabs = currentTabWidget();
	if (!tabs) return 0;
	return qobject_cast<LatexEditorView *>(tabs->currentWidget());
}

/*!
 * Sets the current editor. It is expected that (containsEditor(edView) == true).
 */
void Editors::setCurrentEditor(LatexEditorView *edView)
{
	if (currentEditor() == edView)
		return;

	int group = tabGroupIndexFromEditor(edView);
	if (group >= 0) {
		setCurrentGroup(group);
		tabGroups[group]->setCurrentEditor(edView);
		edView->setFocus();
		emit currentEditorChanged();
		return;
	}
	// catch calls in which editor is not a member tab.
	// TODO: such calls are deprecated as bad practice. We should avoid them in the long run. For the moment the fallback to do nothing is ok.
	qDebug() << "Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget";
#ifndef QT_NO_DEBUG
	txsWarning("Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget");
#endif
}

QList<LatexEditorView *> Editors::editors()
{
	QList<LatexEditorView *> editors;
	foreach (TxsTabWidget *tabGroup, tabGroups) {
		editors.append(tabGroup->editors());
	}
	return editors;
}

void Editors::setCurrentEditorFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	setCurrentEditor(act->data().value<LatexEditorView *>());
}

void Editors::setCurrentEditorFromSender()
{
	LatexEditorView *edView = qobject_cast<LatexEditorView *>(sender());
	REQUIRE(edView);
	setCurrentEditor(edView);
}

void Editors::activateNextEditor()
{
	if (currentGroupIndex < 0) return;

	if (!tabGroups[currentGroupIndex]->currentEditorViewIsLast()) {
		tabGroups[currentGroupIndex]->gotoNextDocument();
	} else {
		// find the next non-empty group
		int newIndex = currentGroupIndex;
		for (int unused = 0; unused < tabGroups.length(); unused++) { // counter is only used as a stopping criterion
			newIndex = (newIndex + 1) % tabGroups.length();
			if (!tabGroups[newIndex]->isEmpty()) {
				setCurrentGroup(newIndex);
				break;
			}
		}
		tabGroups[currentGroupIndex]->gotoFirstDocument();
	}
	emit currentEditorChanged();
}

void Editors::activatePreviousEditor()
{
	if (currentGroupIndex < 0) return;

	if (!tabGroups[currentGroupIndex]->currentEditorViewIsFirst()) {
		tabGroups[currentGroupIndex]->gotoPrevDocument();
	} else {
		// find the previous non-empty group
		int newIndex = currentGroupIndex;
		for (int unused = 0; unused < tabGroups.length(); unused++) { // counter is only used as a stopping criterion
			newIndex = (newIndex - 1) % tabGroups.length();
			if (!tabGroups[newIndex]->isEmpty()) {
				setCurrentGroup(newIndex);
				break;
			}
		}
		tabGroups[currentGroupIndex]->gotoLastDocument();
	}
	emit currentEditorChanged();
}

/*!
 * Activates the tabWidget that is the sender()
 */
void Editors::activateTabWidgetFromSender()
{
	TxsTabWidget *tabWidget = qobject_cast<TxsTabWidget *>(sender());
	//qDebug() << "activating" << tabWidget;
	if (!tabWidget) return;
	setCurrentEditor(tabWidget->currentEditorView());
}

/*!
 * Called from a tab widget when its editor changes.
 * Note: This handles the case the currentEditor changes because the current tab
 * of the tabWidget changes.
 */
void Editors::onTabWidgetEditorChanged()
{
	activateTabWidgetFromSender();
	//qDebug() << "tabWidgetEditorChanged to" << currentEditor() << "(sender: " << sender() << ")";
	emit currentEditorChanged();
}

/*!
 * Context menu handler for tabbars.
 */
void Editors::tabBarContextMenu(const QPoint &point)
{
	if (point.isNull()) return;
	TxsTabWidget *tabGroup = qobject_cast<TxsTabWidget *>(sender());
	if (!tabGroup) return;

	QMenu menu;
	foreach (LatexEditorView *edView, editors()) {
		QAction *act = menu.addAction(edView->displayName().replace("&", "&&"));
		act->setData(QVariant::fromValue<LatexEditorView *>(edView));
		connect(act, SIGNAL(triggered()), SLOT(setCurrentEditorFromAction()));
	}

	menu.addSeparator();
	QAction *act = menu.addAction(tr("Move to other view"));
	LatexEditorView *editorUnderCursor = tabGroup->editorAt(point);
	act->setData(QVariant::fromValue<LatexEditorView *>(editorUnderCursor));
	if (!editorUnderCursor) act->setEnabled(false);
	connect(act, SIGNAL(triggered()), SLOT(moveToOtherTabGroup()));

	act = menu.addAction((splitter->orientation() == Qt::Horizontal) ? tr("Split Vertically") : tr("Split Horizontally"));
	connect(act, SIGNAL(triggered()), SLOT(changeSplitOrientation()));
	menu.exec(tabGroup->mapToGlobal(point));
}

void Editors::onEditorChangeByTabClick(LatexEditorView *from, LatexEditorView *to)
{
	// the original event comes from a tab widget. from is the previously selected tab in that widget
	// which has not been the current one one if the tab widget has not been the current
	emit editorAboutToChangeByTabClick(currentEditor(), to);
}

/*!
 * Called from and action with data() set to an editor. Moves the editor to the other tabGroup.
 * This currently assumes a restriction to two tab groups.
 */
void Editors::moveToOtherTabGroup()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	LatexEditorView *edView = act->data().value<LatexEditorView *>();
	if (!edView) return;

	// NOTE: This code assumes exactly two tabGroups
	int otherGroupIndex = (tabGroups[0] == tabWidgetFromEditor(edView)) ? 1 : 0;
	moveToTabGroup(edView, tabGroups[otherGroupIndex], -1);
}

/*!
 * Move the editor to the given tabWidget at position targetIndex (if < 0, append).
 */
void Editors::moveToTabGroup(LatexEditorView *edView, TxsTabWidget *target, int targetIndex)
{
	if (!target || target->containsEditor(edView)) {
		// only move within the tab
		if (target == 0) target = tabWidgetFromEditor(edView);
		if (targetIndex < 0) targetIndex = qMax(0, target->count() - 1);
		target->moveTab(target->indexOf(edView), targetIndex);
		emit editorsReordered();
	} else {
		TxsTabWidget *source = tabWidgetFromEditor(edView);
		removeEditor(edView, source);
		insertEditor(edView, target, targetIndex, true);
		emit editorsReordered();
	}
}

void Editors::changeSplitOrientation()
{
	splitter->setOrientation((splitter->orientation() == Qt::Horizontal) ? Qt::Vertical : Qt::Horizontal);
}

/*!
 * Returns the number of the tabGroup to which the povided editor belongs or -1.
 */
int Editors::tabGroupIndexFromEditor(LatexEditorView *edView) const
{
	for (int group = 0; group < tabGroups.length(); group++) {
		int i = tabGroups[group]->indexOf(edView);
		if (i >= 0) {
			return group;
		}
	}
	return -1;
}

/*!
 * Returns a pointer to the tabWidget to which the provided editor belongs or 0.
 */
TxsTabWidget *Editors::tabWidgetFromEditor(LatexEditorView *edView) const
{
	int group = tabGroupIndexFromEditor(edView);
	if (group < 0) return 0;
	return tabGroups[group];
}

void Editors::setCurrentGroup(int index)
{
	if (currentGroupIndex >= 0) {
		tabGroups[currentGroupIndex]->setActive(false);
	}
	currentGroupIndex = index;
	tabGroups[currentGroupIndex]->setActive(true);
}
