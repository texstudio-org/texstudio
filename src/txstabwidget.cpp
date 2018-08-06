#include "txstabwidget.h"
#include "latexeditorview.h"
#include "latexdocument.h"
#include "smallUsefulFunctions.h"

TxsTabWidget::TxsTabWidget(QWidget *parent) :
	QTabWidget(parent),
	m_active(false)
{
	setFocusPolicy(Qt::ClickFocus);
	setContextMenuPolicy(Qt::PreventContextMenu);

	ChangeAwareTabBar *tb = new ChangeAwareTabBar();
	tb->setContextMenuPolicy(Qt::CustomContextMenu);
	tb->setUsesScrollButtons(true);
	connect(tb, SIGNAL(customContextMenuRequested(QPoint)), this, SIGNAL(tabBarContextMenuRequested(QPoint)));
	connect(tb, SIGNAL(currentTabAboutToChange(int, int)), this, SLOT(currentTabAboutToChange(int, int)));
	connect(tb, SIGNAL(tabLeftClicked()), this, SIGNAL(activationRequested()));
	connect(tb, SIGNAL(middleMouseButtonPressed(int)), this, SLOT(onTabCloseRequest(int)));
	setTabBar(tb);

	if (hasAtLeastQt(4, 5)) {
		setDocumentMode(true);
		const QTabBar *tb = tabBar();
		connect(tb, SIGNAL(tabMoved(int, int)), this, SIGNAL(tabMoved(int, int)));
		connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequest(int)));
		setProperty("tabsClosable", true);
		setProperty("movable", true);
	}
	connect(this, SIGNAL(currentChanged(int)), this, SIGNAL(currentEditorChanged()));
}

void TxsTabWidget::moveTab(int from, int to)
{
	int cur = currentIndex();
	QString text = tabText(from);
	QWidget *wdg = widget(from);
	removeTab(from);
	insertTab(to, wdg, text);
	if (cur == from) setCurrentIndex(to);
	else if (from < to && cur >= from && cur < to)
		setCurrentIndex(cur - 1);
	else if (to < from && to && cur >= to && cur < from)
		setCurrentIndex(cur + 1);
}

QList<LatexEditorView *> TxsTabWidget::editors() const
{
	QList<LatexEditorView *> list;
	for (int i = 0; i < count(); i++) {
		LatexEditorView *edView = qobject_cast<LatexEditorView *>(widget(i));
		Q_ASSERT(edView); // there should only be editors as tabs
		list.append(edView);
	}
	return list;
}

bool TxsTabWidget::containsEditor(LatexEditorView *edView) const
{
	if (!edView) return false;
	return (indexOf(edView) >= 0);
}

LatexEditorView *TxsTabWidget::currentEditor() const
{
	return qobject_cast<LatexEditorView *>(currentWidget());
}

void TxsTabWidget::setCurrentEditor(LatexEditorView *edView)
{
	if (currentWidget() == edView)
		return;

	if (indexOf(edView) < 0) {
		// catch calls in which editor is not a member tab.
		// TODO: such calls are deprecated as bad practice. We should avoid them in the long run. For the moment the fallback to do nothing is ok.
		qDebug() << "Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget" << edView;
#ifndef QT_NO_DEBUG
		UtilsUi::txsWarning("Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget");
#endif
		return;
	}
	setCurrentWidget(edView);
}

LatexEditorView *TxsTabWidget::editorAt(QPoint p) {
	int index = tabBar()->tabAt(p);
    if (index < 0) return nullptr;
	return qobject_cast<LatexEditorView *>(widget(index));
}

/*! \brief Mark the widget as active.
 *
 * If there are multiple widgets, we want to visually indicate the active one,
 * i.e. the one containing the current editor.
 * We currently use bold on the current tab, but due to a Qt bug we're required
 * to increase the tab width all tabs in the active widget.
 * see https://bugreports.qt.io/browse/QTBUG-6905
 */
void TxsTabWidget::setActive(bool active) {
	if (active == m_active) return;
	m_active = active;
	QString baseStyle = "QTabBar::close-button {image: url(:/images-ng/close-tab.svgz)} QTabBar::close-button:hover {image: url(:/images-ng/close-tab-hover.svgz)}";
	if (active) {
		setStyleSheet(baseStyle);// + " QTabBar {font-weight: bold;} QTabBar::tab:!selected {font-weight: normal;}");
	} else {
		setStyleSheet(baseStyle + " QTabBar {color: darkgrey;}");
	}
}

bool TxsTabWidget::isEmpty() const {
	return (count() == 0);
}

bool TxsTabWidget::currentEditorViewIsFirst() const {
	return (currentIndex() == 0);
}

bool TxsTabWidget::currentEditorViewIsLast() const {
	return (currentIndex() >= count()-1);
}

void TxsTabWidget::gotoNextDocument()
{
	if (count() <= 1) return;
	int cPage = currentIndex() + 1;
	if (cPage >= count()) setCurrentIndex(0);
	else setCurrentIndex(cPage);
}

void TxsTabWidget::gotoPrevDocument()
{
	if (count() <= 1) return;
	int cPage = currentIndex() - 1;
	if (cPage < 0) setCurrentIndex(count() - 1);
	else setCurrentIndex(cPage);
}

void TxsTabWidget::gotoFirstDocument() {
	if (count() <= 1) return;
	setCurrentIndex(0);
}

void TxsTabWidget::gotoLastDocument() {
	if (count() <= 1) return;
	setCurrentIndex(count()-1);
}

void TxsTabWidget::currentTabAboutToChange(int from, int to)
{
	LatexEditorView *edFrom = qobject_cast<LatexEditorView *>(widget(from));
	LatexEditorView *edTo = qobject_cast<LatexEditorView *>(widget(to));
	REQUIRE(edFrom);
	REQUIRE(edTo);
	emit editorAboutToChangeByTabClick(edFrom, edTo);
}

/*! \brief Handler for close requests coming from the tab bar.
 *
 * The widget cannot decide if the tab can really be closed, which can only be
 * determined at top level with user interaction if there are unsaved changes to
 * the editor. So we propagate the request up.
 * In the long terms one might consider asking the editor instead.
 */
void TxsTabWidget::onTabCloseRequest(int i)
{
	emit closeEditorRequested(editorAt(i));
}

void TxsTabWidget::insertEditor(LatexEditorView *edView, int pos, bool asCurrent)
{
	Q_ASSERT(edView);
	pos = insertTab(pos, edView, "?bug?");
	updateTab(pos);
	connectEditor(edView);

	if (asCurrent) setCurrentEditor(edView);
}

void TxsTabWidget::removeEditor(LatexEditorView *edView)
{
	int i = indexOf(edView);
	if (i >= 0)
		removeTab(i);
	disconnectEditor(edView);
}

/*!
 * Returns the LatexEditorView at the given tab index or 0.
 */
LatexEditorView *TxsTabWidget::editorAt(int index)
{
	if (index < 0 || index >= count())
        return nullptr;
	return qobject_cast<LatexEditorView *>(widget(index));
}

/*!
 * Connect to signals of the editor so that the TabWidget will update the modified
 * status and the tab text when these properties of the editor change.
 *
 */
void TxsTabWidget::connectEditor(LatexEditorView *edView)
{
	connect(edView->editor, SIGNAL(contentModified(bool)), this, SLOT(updateTabFromSender()));
	connect(edView->editor, SIGNAL(readOnlyChanged(bool)), this, SLOT(updateTabFromSender()));
	connect(edView->editor, SIGNAL(titleChanged(QString)), this, SLOT(updateTabFromSender()));
}

/*!
 * Disconnect all connections from the editor to this.
 */
void TxsTabWidget::disconnectEditor(LatexEditorView *edView)
{
	edView->editor->disconnect(this);
}

/*!
 * Updates modified icon, tab text and tooltip.
 * TODO: tooltip should be dynamically generated when required because
 * this is not called always when root information changes.
 */
void TxsTabWidget::updateTab(int index)
{
	//cache icons, getRealIcon is *really* slow
	static QIcon readOnly = getRealIcon("document-locked");
	static QIcon modified = getRealIcon("modified");
	static QIcon empty = QIcon(":/images/empty.png");

	LatexEditorView *edView = editorAt(index);
	if (!edView) return;

	// update icon
	if (edView->editor->isReadOnly()) {
		setTabIcon(index, readOnly);
	} else if ((edView->editor->isContentModified())) {
		setTabIcon(index, modified);
	} else {
		setTabIcon(index, empty);
	}
	// update tab text
	setTabText(index, edView->displayNameForUI());
	// update tooltip text
	LatexDocument *doc = edView->document;
	LatexDocument *rootDoc = doc->getRootDocument();
	QString tooltip = QDir::toNativeSeparators(edView->editor->fileName());
	if (doc != rootDoc) {
		tooltip += tr("\nincluded document in %1").arg(rootDoc->getName());
	}
	setTabToolTip(index, tooltip);
}

/*!
 * Helper function. This is bound to editor signals and calls updateTab() on
 * the tab to which the sending editor belongs.
 */
void TxsTabWidget::updateTabFromSender()
{
	QEditor *editor = qobject_cast<QEditor *>(sender());
	for (int i = 0; i < count(); i++) {
		if (editorAt(i)->editor == editor) {
			updateTab(i);
			return;
		}
	}
}

void ChangeAwareTabBar::mousePressEvent(QMouseEvent *event)
{
	int current = currentIndex();
	int toIndex = tabAt(event->pos());
	if (event->button() == Qt::LeftButton) {
		if (toIndex >= 0) {
			emit currentTabAboutToChange(current, toIndex);
		}
	}
#if QT_VERSION>=0x040700
	else if (event->button() == Qt::MiddleButton) {
		int tabNr = tabAt(event->pos());
		if (tabNr >= 0) {
			emit middleMouseButtonPressed(tabNr);
		}
	}
#endif
	QTabBar::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		emit tabLeftClicked();
	}
}
