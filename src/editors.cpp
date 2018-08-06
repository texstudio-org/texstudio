#include "editors.h"
#include "txstabwidget.h"
#include "mostQtHeaders.h"
#include "utilsSystem.h"
#include "latexeditorview.h"
#include "minisplitter.h"


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
    QWidget(parent), splitter(nullptr), currentGroupIndex(-1)
{
	splitter = new MiniSplitter(Qt::Horizontal);
	splitter->setChildrenCollapsible(false);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(splitter);

	changes = new EditorChangeProxy(this);
	connect(changes, SIGNAL(currentEditorChanged()), this, SIGNAL(currentEditorChanged()));
	connect(changes, SIGNAL(listOfEditorsChanged()), this, SIGNAL(listOfEditorsChanged()));
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
	connect(w, SIGNAL(currentEditorChanged()), changes, SLOT(currentEditorChange()));
	connect(w, SIGNAL(editorAboutToChangeByTabClick(LatexEditorView *, LatexEditorView *)), this, SLOT(onEditorChangeByTabClick(LatexEditorView *, LatexEditorView *)));
	connect(w, SIGNAL(activationRequested()), SLOT(activateTabWidgetFromSender()));
	connect(w, SIGNAL(closeEditorRequested(LatexEditorView*)), SLOT(requestCloseEditor(LatexEditorView *)));
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

	bool b = changes->block();
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
	if (b) changes->release();
}

/*! \brief request to close the given editor.
 *
 * The widget cannot decide if the tab can really be closed, which can only be
 * determined at top level with user interaction if there are unsaved changes to
 * the editor. So we propagate the request up.
 */
void Editors::requestCloseEditor(LatexEditorView *edView)
{
	LatexEditorView *originalCurrent = currentEditor();

	if (edView == originalCurrent) {
		// request to close the current editor
		emit closeCurrentEditorRequested();
	} else {
		// request to close a non-current editor
		setCurrentEditor(edView);
		emit closeCurrentEditorRequested();
		if (currentEditor() != edView) {
			// closing (of the originally non-current) editor was successful.
			// Therefore we activate the originally current editor again.
			setCurrentEditor(originalCurrent);
		}
	}
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
	bool b = changes->block();
	bool isLastEditorInGroup = (tabWidget->indexOf(edView) == tabWidget->count() - 1);
	if (edView == currentEditor()) {
		if (isLastEditorInGroup) {
			activatePreviousEditor();
		} else {
			activateNextEditor();
		}
	}
	tabWidget->removeEditor(edView);
	if (tabWidget->isEmpty() && tabWidget != tabGroups[0]) {
		tabWidget->hide();
	}
	if (b) changes->release();
}

bool Editors::containsEditor(LatexEditorView *edView) const
{
	return tabGroupIndexFromEditor(edView) >= 0;
}

TxsTabWidget *Editors::currentTabWidget() const
{
	if (currentGroupIndex >= 0 && currentGroupIndex < tabGroups.length())
		return tabGroups[currentGroupIndex];
    return nullptr;
}

LatexEditorView *Editors::currentEditor() const
{
	TxsTabWidget *tabs = currentTabWidget();
    if (!tabs) return nullptr;
	return qobject_cast<LatexEditorView *>(tabs->currentWidget());
}

/*!
 * Sets the current editor. It is expected that (containsEditor(edView) == true).
 * if setFocus, the focus will be changed to the new editor
 */
void Editors::setCurrentEditor(LatexEditorView *edView, bool setFocus)
{
	if (currentEditor() == edView) {
		return;
	}

	int group = tabGroupIndexFromEditor(edView);
	if (group >= 0) {
		bool b = changes->block();
		setCurrentGroup(group);
		tabGroups[group]->setCurrentEditor(edView);
		if (setFocus) {
			edView->setFocus();
		}
		if (b) changes->release();
		return;
	}
	// catch calls in which editor is not a member tab.
	// TODO: such calls are deprecated as bad practice. We should avoid them in the long run. For the moment the fallback to do nothing is ok.
	qDebug() << "Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget";
#ifndef QT_NO_DEBUG
	UtilsUi::txsWarning("Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget");
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

void Editors::closeEditorFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	LatexEditorView *edView = act->data().value<LatexEditorView *>();
	requestCloseEditor(edView);
}

void Editors::closeOtherEditorsFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	LatexEditorView *editorToKeep = act->data().value<LatexEditorView *>();

	foreach (TxsTabWidget *tabWidget, tabGroups) {
		foreach (LatexEditorView *edView, tabWidget->editors()) {
			if (edView != editorToKeep) {
				requestCloseEditor(edView);
			}
		}
	}
}

void Editors::toggleReadOnlyFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	LatexEditorView *edView = act->data().value<LatexEditorView *>();
	edView->editor->setReadOnly(!edView->editor->isReadOnly());
}

bool Editors::activateNextEditor()
{
	if (currentGroupIndex < 0) return false;

	bool b = changes->block();
	if (!tabGroups[currentGroupIndex]->currentEditorViewIsLast()) {
		tabGroups[currentGroupIndex]->gotoNextDocument();
	} else {
		// find the next non-empty group
		int newIndex = currentGroupIndex;
		for (int unused = 0; unused < tabGroups.length(); unused++) { // counter is only used as a stopping criterion
			newIndex = (newIndex + 1) % tabGroups.length();
			if (!tabGroups[newIndex]->isEmpty()) {
				if (newIndex == currentGroupIndex && tabGroups[currentGroupIndex]->count() == 1) {
					if (b) changes->release();
					return false;  // only one editor: we cannot change
				}
				setCurrentGroup(newIndex);
				break;
			}
		}
		tabGroups[currentGroupIndex]->gotoFirstDocument();
	}
	if (b) changes->release();
	return true;
}

bool Editors::activatePreviousEditor()
{
	if (currentGroupIndex < 0) return false;

	bool b = changes->block();
	if (!tabGroups[currentGroupIndex]->currentEditorViewIsFirst()) {
		tabGroups[currentGroupIndex]->gotoPrevDocument();
	} else {
		// find the previous non-empty group
		int newIndex = currentGroupIndex;
		for (int unused = 0; unused < tabGroups.length(); unused++) { // counter is only used as a stopping criterion
			newIndex = (newIndex == 0) ? (tabGroups.length() -1) : (newIndex - 1);
			if (!tabGroups[newIndex]->isEmpty()) {
				if (newIndex == currentGroupIndex && tabGroups[currentGroupIndex]->count() == 1) {
					return false;  // only one editor: we cannot change
				}
				setCurrentGroup(newIndex);
				break;
			}
		}
		tabGroups[currentGroupIndex]->gotoLastDocument();
	}
	if (b) changes->release();
	return true;
}

/*!
 * Activates the tabWidget that is the sender(). Returns true if the widget could be activated.
 */
bool Editors::activateTabWidgetFromSender()
{
	TxsTabWidget *tabWidget = qobject_cast<TxsTabWidget *>(sender());
	if (!tabWidget) return false;
	LatexEditorView *edView = tabWidget->currentEditor();
	if (!edView) return false;
	setCurrentEditor(tabWidget->currentEditor());
	return true;
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
		QAction *act = menu.addAction(edView->displayNameForUI());
		act->setData(QVariant::fromValue<LatexEditorView *>(edView));
		connect(act, SIGNAL(triggered()), SLOT(setCurrentEditorFromAction()));
	}

	menu.addSeparator();
	QAction *act = menu.addAction(tr("Move to other view"));
	LatexEditorView *editorUnderCursor = tabGroup->editorAt(point);
	act->setData(QVariant::fromValue<LatexEditorView *>(editorUnderCursor));
	if (!editorUnderCursor) act->setEnabled(false);
	connect(act, SIGNAL(triggered()), SLOT(moveToOtherTabGroup()));

	act = menu.addAction(tr("Move all to other view"));
	act->setData(QVariant::fromValue<TxsTabWidget *>(tabGroup));
	if (!editorUnderCursor) act->setEnabled(false);
	connect(act, SIGNAL(triggered()), SLOT(moveAllToOtherTabGroup()));

	act = menu.addAction((splitter->orientation() == Qt::Horizontal) ? tr("Split Vertically") : tr("Split Horizontally"));
	connect(act, SIGNAL(triggered()), SLOT(changeSplitOrientation()));

	if (editorUnderCursor) {
		menu.addSeparator();
		QString text = tr("Set Read-Only");
		if (editorUnderCursor->editor->isReadOnly())
			text = tr("Unset Read-Only");
		act = menu.addAction(text);
		act->setData(QVariant::fromValue<LatexEditorView *>(editorUnderCursor));
		connect(act, SIGNAL(triggered()), SLOT(toggleReadOnlyFromAction()));
		menu.addSeparator();
		act = menu.addAction(tr("Close"));
		act->setData(QVariant::fromValue<LatexEditorView *>(editorUnderCursor));
		connect(act, SIGNAL(triggered()), SLOT(closeEditorFromAction()));
		act = menu.addAction(tr("Close All Other Documents"));
		act->setData(QVariant::fromValue<LatexEditorView *>(editorUnderCursor));
		connect(act, SIGNAL(triggered()), SLOT(closeOtherEditorsFromAction()));
	}
	menu.exec(tabGroup->mapToGlobal(point));
}

void Editors::onEditorChangeByTabClick(LatexEditorView *from, LatexEditorView *to)
{
	Q_UNUSED(from);
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

void Editors::moveAllToOtherTabGroup() {
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	TxsTabWidget *tabGroup = act->data().value<TxsTabWidget *>();
	if (!tabGroup) return;

	// NOTE: This code assumes exactly two tabGroups
	int otherGroupIndex = (tabGroups[0] == tabGroup) ? 1 : 0;
	foreach (LatexEditorView *edView, tabGroup->editors())
		moveToTabGroup(edView, tabGroups[otherGroupIndex], -1);
}


/*!
 * Move the editor to the given tabWidget at position targetIndex (if < 0, append).
 */
void Editors::moveToTabGroup(LatexEditorView *edView, int groupIndex, int targetIndex)
{
	if (groupIndex < 0)
		groupIndex = 0;
	if (groupIndex > tabGroups.length() -1)
		groupIndex = tabGroups.length() -1;
	moveToTabGroup(edView, tabGroups[groupIndex], targetIndex);
}

/*!
 * Move the editor to the given tabWidget at position targetIndex (if < 0, append).
 */
void Editors::moveToTabGroup(LatexEditorView *edView, TxsTabWidget *target, int targetIndex)
{
	if (!target || target->containsEditor(edView)) {
		// only move within the tab
        if (target == nullptr) target = tabWidgetFromEditor(edView);
		if (targetIndex < 0) targetIndex = qMax(0, target->count() - 1);
		int currentIndex = target->indexOf(edView);
		if (currentIndex != targetIndex) {  // nothing todo otherwise
			target->moveTab(target->indexOf(edView), targetIndex);
			emit editorsReordered();
		}
	} else {
		bool b = changes->block();
		TxsTabWidget *source = tabWidgetFromEditor(edView);
		removeEditor(edView, source);
		insertEditor(edView, target, targetIndex, true);
		if (b) changes->release();
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
    if (group < 0) return nullptr;
	return tabGroups[group];
}

void Editors::setCurrentGroup(int index)
{
	if (index == currentGroupIndex) return;
	if (currentGroupIndex >= 0) {
		tabGroups[currentGroupIndex]->setActive(false);
	}
	currentGroupIndex = index;
	tabGroups[currentGroupIndex]->setActive(true);
}



/*! \class EditorChangeProxy
 *
 * This class handles changes of the currentEditor
 *
 * There are two ways that can lead to emission of the signal currentEditorChanged():
 *
 * 1) First, other components can connect to the slot editorChange(). These signals are
 * just propagated, except if the EditorChangeProxy is blocked.
 *
 * 2) Second, one can block() the propagation of changes and release() later on. At release(),
 * the proxy checks if the currentEditor has changed from the one at blocking. If so, the
 * currentEditorChanged() signal is emitted.
 * Use the block/release mechanism to perform complex actions that consist of multiple
 * editor changes (potentially even with inconsistent intermediate states) during which
 * you don't want to emit currentEditorChanged().
 * You have to make sure that you release the block if and only if you acquired it. Therefore,
 * blocking should always use this pattern:
 *
 *     bool b = changes->block();
 *     ...
 *     if (b) changes->release();
 *
 * If you have return statements in the intermediate code, be sure to place the release command
 * also before every return.
 */
EditorChangeProxy::EditorChangeProxy(Editors *e) : editors(e), currentEditorAtBlock(nullptr), blocked(false) {}

//#define ecpDebug(x) qDebug(x)
#define ecpDebug(x)
bool EditorChangeProxy::block()
{
	if (blocked) {
		ecpDebug("already blocked");
		return false;
	}
	blocked = true;
	currentEditorAtBlock = editors->currentEditor();
	listOfEditorsAtBlock = editors->editors();
	ecpDebug("block activated");
	return true;
}

void EditorChangeProxy::release()
{
	ecpDebug("release");
	if (blocked) {
		blocked = false;
		if (editors->currentEditor() != currentEditorAtBlock) {
			ecpDebug("currentEditorChanged signaled at release");
			emit currentEditorChanged();
		}
		if (editors->editors() != listOfEditorsAtBlock) {
			ecpDebug("listOfEditorsChanged signaled at release");
			emit listOfEditorsChanged();
		}
	} else {
		// can only happen if the above mentioned blocking pattern was not used.
		qDebug("WARNING: trying to realease an unblocked EditorChangeProxy. This hints at inconsistent code.");
	}
}

void EditorChangeProxy::currentEditorChange()
{
	if (!blocked) {
		ecpDebug("currentEditorChanged passed");
		emit currentEditorChanged();
	} else {
		ecpDebug("currentEditorChanged blocked");
	}
}

void EditorChangeProxy::listOfEditorsChange()
{
	if (!blocked) {
		ecpDebug("listOfEditorsChanged passed");
		emit listOfEditorsChanged();
	} else {
		ecpDebug("listOfEditorsChanged blocked");
	}
}
#undef ecpDebug

