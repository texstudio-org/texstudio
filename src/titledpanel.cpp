#include "titledpanel.h"
#include "utilsSystem.h"

Q_DECLARE_METATYPE(QAction *)

QHash<QString, TitledPanelPage *> TitledPanelPage::allPages;

TitledPanelPage::TitledPanelPage(QWidget *widget, const QString &id, const QString &text, const QIcon &icon) :
    m_widget(nullptr), m_visibleAction(nullptr), m_selectAction(nullptr), m_toolbarActions(nullptr)
{
#ifndef QT_NO_DEBUG
	if (allPages.contains(id)) {
		qDebug() << "Duplicate TitledPanelPage ID:" << id;
	}
	if (!widget) qDebug() << "Page does not have widget!" << id;
#endif
	allPages.insert(id, this);

	m_widget = widget;
    Q_ASSERT(m_widget);
	m_widget->setProperty("containingPage", QVariant::fromValue<TitledPanelPage *>(this));
	QFrame *f = qobject_cast<QFrame *>(m_widget); // remove frame form widget if it has one
	if (f) f->setFrameShape(QFrame::NoFrame);

	m_id = id;
	m_title = text;
	m_icon = icon;

	m_visibleAction = new QAction(text, this);
	m_visibleAction->setCheckable(true);
	m_visibleAction->setChecked(true);
	m_visibleAction->setData(id);

	// select action
	// TODO check
	m_selectAction = new QAction(text, this);
	m_selectAction->setData(id);
	m_selectAction->setIcon(icon);
	m_selectAction->setToolTip(text);
	m_selectAction->setCheckable(true);

	m_toolbarActions = new QList<QAction *>();
}

TitledPanelPage::~TitledPanelPage()
{
	allPages.remove(m_id);
	delete m_toolbarActions; // only deletes the list. The actions themselves are not owned by the page
}

void TitledPanelPage::addToolbarAction(QAction *act)
{
	m_toolbarActions->append(act);
}

void TitledPanelPage::addToolbarActions(QList<QAction *> actions)
{
	m_toolbarActions->append(actions);
}

QString TitledPanelPage::id() const
{
	return m_id;
}

QWidget *TitledPanelPage::widget()
{
	return m_widget;
}

bool TitledPanelPage::visible() const
{
	return m_visibleAction->isChecked();
}

TitledPanelPage *TitledPanelPage::fromId(const QString &id)
{
	TitledPanelPage *page = allPages.value(id);
	if (!page) qDebug() << "Requested TitledPanelPage does not exist:" << id;
	return page;
}

void TitledPanelPage::updatePageTitle(const QString &id, const QString newTitle)
{
	TitledPanelPage *page = allPages.value(id);
	if (page) page->setTitle(newTitle);
}

void TitledPanelPage::setTitle(const QString &title)
{
	if (m_title != title) {
		m_title = title;
		m_visibleAction->setText(title);
		m_selectAction->setText(title);
		m_selectAction->setToolTip(title);
		emit titleChanged(title);
	}
}

void TitledPanelPage::setIcon(const QIcon &icon)
{
	m_icon = icon;
	m_selectAction->setIcon(icon);
	emit iconChanged(icon);
}


/*** class TitledPanel ***/

TitledPanel::TitledPanel(QWidget *parent) :
    QFrame(parent), mToggleViewAction(nullptr), closeAction(0), pageSelectActions(0), selectorStyle(ComboSelector), vLayout(0),
    topbar(nullptr), lbTopbarLabel(nullptr), cbTopbarSelector(nullptr), tbTopbarSelector(nullptr), stack(nullptr)
{
	setFrameShape(QFrame::Box);
	setFrameShadow(QFrame::Plain);

	mToggleViewAction = new QAction(this);
	mToggleViewAction->setCheckable(true);
	mToggleViewAction->setChecked(true);
	connect(mToggleViewAction, SIGNAL(toggled(bool)), this, SLOT(viewToggled(bool)));

	pageSelectActions = new QActionGroup(this);

	closeAction = new QAction(this);
	closeAction->setIcon(getRealIcon("close"));
	closeAction->setToolTip(tr("Close"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(hide()));

	stack = new QStackedWidget();

	vLayout = new QVBoxLayout(this);
	vLayout->setSpacing(0);
	vLayout->setMargin(0);
	vLayout->addWidget(stack);
	setLayout(vLayout);

	updateTopbar();
}

/* note: the panel takes ownership of the page */
void TitledPanel::appendPage(TitledPanelPage *page, bool guiUpdate)
{
	page->setParent(this);
	pages.append(page);
	stack->addWidget(page->m_widget);
	page->m_widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);

	// TODO adapt for horizontal or vertical panels
	page->m_widget->setMinimumWidth(0);

	connect(page, SIGNAL(titleChanged(QString)), this, SLOT(onPageTitleChange()));
	connect(page, SIGNAL(iconChanged(QIcon)), this, SLOT(onPageIconChange()));
	connect(page->m_selectAction, SIGNAL(toggled(bool)), this, SLOT(setActivePageFromAction()));
	connect(page->m_visibleAction, SIGNAL(toggled(bool)), this, SLOT(togglePageVisibleFromAction(bool)));

	if (guiUpdate) updateTopbar();
}

/* note: the panel doesn't have a parent anymore. You are responsible for deleting */
void TitledPanel::removePage(TitledPanelPage *page, bool guiUpdate)
{
	disconnect(page, SIGNAL(titleChanged()), this, SLOT(onPageTitleChange()));
	disconnect(page, SIGNAL(iconChanged()), this, SLOT(onPageIconChange()));
	disconnect(page->m_selectAction, SIGNAL(toggled(bool)), this, SLOT(onPageSelectRequest()));
	disconnect(page->m_visibleAction, SIGNAL(toggled(bool)), this, SLOT(togglePageVisibleFromAction(bool)));

	stack->removeWidget(page->m_widget);
    page->setParent(nullptr);

	int i = pages.indexOf(page);
	if (i >= 0) pages.removeAt(i);

	if (guiUpdate) updateTopbar();
}

int TitledPanel::pageCount() const
{
	return pages.count();
}

TitledPanelPage *TitledPanel::pageFromId(const QString &id)
{
	TitledPanelPage *page = TitledPanelPage::fromId(id);
	if (!page || !pages.contains(page))
        return nullptr;
	return page;
}

// TODO
void TitledPanel::setHiddenPageIds(const QStringList &hiddenIds)
{
	mHiddenPageIds = hiddenIds;
	qDebug() << "hidden pages not yet implemented";
}

// TODO
QStringList TitledPanel::hiddenPageIds() const
{
	qDebug() << "hidden pages not yet implemented";
	return mHiddenPageIds;
}

void TitledPanel::setCurrentPage(const QString &id)
{
	TitledPanelPage *page = TitledPanelPage::fromId(id);
	if (!page) {
		qDebug() << "TitledPanel: trying to access invalid page" << id;
		return;
	}
	if (currentPage() == page)
		return;

	stack->setCurrentWidget(page->m_widget);
	page->m_selectAction->setChecked(true);

	updateTopbar();

	emit pageChanged(id);
}

TitledPanelPage *TitledPanel::currentPage() const
{
	QWidget *w = stack->currentWidget();
    if (!w) return nullptr;
	return qvariant_cast<TitledPanelPage *>(w->property("containingPage"));
}

QString TitledPanel::currentPageId() const
{
	TitledPanelPage *page = currentPage();
	if (page) return page->id();
	return QString();
}

void TitledPanel::showPage(const QString &id)
{
	setCurrentPage(id);
	show();
}

QAction *TitledPanel::toggleViewAction() const
{
	return mToggleViewAction;
}

void TitledPanel::setSelectorStyle(TitledPanel::PageSelectorStyle style)
{
	selectorStyle = style;
	updateTopbar();
}

void TitledPanel::setVisible(bool visible)
{
	QFrame::setVisible(visible);
	mToggleViewAction->setChecked(visible);
}

void TitledPanel::updateTopbar()
{
	QToolBar *oldTopbar = topbar;

	// did not manage to remove and add again widgets to the toolbar properly
	// widgets added by toolbar->addWidget seem to have a bit weird behaviour
	// on toolbar->clear() or reparenting
	// so we create a new toolbar
	// alternatively do not use a toolbar, but a widget styled like one, as QtCreator does
	topbar = new QToolBar(this);
	topbar->setOrientation(Qt::Horizontal);
	topbar->setFloatable(false);
	topbar->setMovable(false);
	topbar->setIconSize(QSize(16, 16));
	topbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	QList<QAction *> acts = pageSelectActions->actions();
	foreach (QAction *act, acts) {
		pageSelectActions->removeAction(act);
	}

	int visiblePageCount = 0;
    TitledPanelPage *firstVisiblePage = nullptr;
	foreach (TitledPanelPage *p, pages) {
		if (p->visible()) {
			if (!firstVisiblePage) firstVisiblePage = p;
			visiblePageCount++;
		}
	}

	// will be deleted together with oldTopbar because they are children of it
    lbTopbarLabel = nullptr;
    cbTopbarSelector = nullptr;
    tbTopbarSelector = nullptr;

	if (visiblePageCount == 1) {
		lbTopbarLabel = new QLabel(firstVisiblePage->m_title);
		lbTopbarLabel->setIndent(4);
		topbar->addWidget(lbTopbarLabel);
	} else if (visiblePageCount > 1) {
		switch (selectorStyle) {
		case ComboSelector:
			cbTopbarSelector = new QComboBox(topbar);
			cbTopbarSelector->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			cbTopbarSelector->setMinimumWidth(0);
			cbTopbarSelector->setMaxVisibleItems(25);
			connect(cbTopbarSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(setActivePageFromComboBox(int)));
			break;
		case TabSelector:
			tbTopbarSelector = new QTabBar(topbar);
			connect(tbTopbarSelector, SIGNAL(currentChanged(int)), this, SLOT(setActivePageFromTabBar(int)));
		}

		foreach (TitledPanelPage *p, pages) {
			if (p->visible()) {
				pageSelectActions->addAction(p->m_selectAction);

				// create selector (items)
				if (cbTopbarSelector) {
					bool old = cbTopbarSelector->blockSignals(true);
					cbTopbarSelector->addItem(p->m_title, p->id());
					cbTopbarSelector->blockSignals(old);
				} else if (tbTopbarSelector) {
					bool old = tbTopbarSelector->blockSignals(true);
					int idx = tbTopbarSelector->addTab(p->m_title);
					tbTopbarSelector->setTabData(idx, p->id());
					tbTopbarSelector->blockSignals(old);
				}
			}
		}

		// update selector
		if (cbTopbarSelector) {
			int index = cbTopbarSelector->findData(currentPageId());
			if (index >= 0) {
				cbTopbarSelector->setCurrentIndex(index);
			} else {
				QString id = cbTopbarSelector->itemData(0).toString();
				stack->setCurrentWidget(TitledPanelPage::fromId(id)->m_widget);
			}
			topbar->addWidget(cbTopbarSelector);
		} else if (tbTopbarSelector) {
			int index;
			for (index = 0; index < tbTopbarSelector->count(); index++) {
				if (tbTopbarSelector->tabData(index).toString() == currentPageId()) {
					tbTopbarSelector->setCurrentIndex(index);
					break;
				}
			}
			if (index >= tbTopbarSelector->count()) { // currentPage not visible any more: fall back to first page
				QString id = tbTopbarSelector->tabData(0).toString();
				stack->setCurrentWidget(TitledPanelPage::fromId(id)->m_widget);
			}
			topbar->addWidget(tbTopbarSelector);
#ifdef Q_OS_MAC
			topbar->layout()->itemAt(topbar->layout()->count() - 1)->setAlignment(Qt::AlignVCenter);
#else
			topbar->layout()->itemAt(topbar->layout()->count() - 1)->setAlignment(Qt::AlignBottom);
#endif
		}


		/* TODO alternative selectors:

		QActionGroup *sel = new QActionGroup(this);
		QAction *act = sel->addAction("Hallo");
		act->setCheckable(true);
		topbar->addAction(act);
		act = sel->addAction("Welt");
		act->setCheckable(true);
		topbar->addAction(act);
		act = sel->addAction("Fuzzy");
		act->setCheckable(true);
		topbar->addAction(act); */
	}

	if (currentPage()) {
		foreach (QAction *act, *currentPage()->m_toolbarActions) {
			topbar->addAction(act);
		}
	}

	QWidget *topbarSpacer = new QWidget(topbar);
	topbarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	topbar->addWidget(topbarSpacer);
	topbar->addAction(closeAction);

	if (oldTopbar) {
		oldTopbar->hide();
		vLayout->removeWidget(oldTopbar);
		oldTopbar->deleteLater();
	}
	vLayout->insertWidget(0, topbar);
}

void TitledPanel::updatePageSelector(TitledPanelPage *page)
{
	if (!page) {
		foreach (TitledPanelPage *p, pages) {
			updatePageSelector(p);
		}
		return;
	}

	if (lbTopbarLabel) {
		lbTopbarLabel->setText(page->m_title);
	}

	if (cbTopbarSelector) {
		int index = cbTopbarSelector->findData(page->id());
		if (index >= 0) {
			cbTopbarSelector->setItemText(index, page->m_title);
		}
	}
}

void TitledPanel::onPageTitleChange()
{
	TitledPanelPage *page = qobject_cast<TitledPanelPage *>(sender());
	if (!page) return;

	updatePageSelector(page);
}

void TitledPanel::onPageIconChange()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		// TODO update page select controls
		qDebug() << "Page icon change not yet implemented";
	}
}

void TitledPanel::setActivePageFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;
	setCurrentPage(act->data().toString());
}

void TitledPanel::setActivePageFromComboBox(int index)
{
	QComboBox *box = qobject_cast<QComboBox *>(sender());
	if (box)
		setCurrentPage(box->itemData(index).toString());
}

void TitledPanel::setActivePageFromTabBar(int index)
{
	QTabBar *tabBar = qobject_cast<QTabBar *>(sender());
	if (tabBar)
		setCurrentPage(tabBar->tabData(index).toString());
}

void TitledPanel::togglePageVisibleFromAction(bool on)
{
	Q_UNUSED(on);
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act || act->data().toString() == "") return;

	// TODO maybe just remove(id)
	//updateTopbar();
}

// TODO check: can't we directly set the context menu on the widget?
void TitledPanel::customContextMenuRequested(const QPoint &localPosition)
{
	QWidget *widget = stack->currentWidget();
	if (widget && widget->underMouse()) { //todo?: use a more reliable function than underMouse (see qt bug 260000)
		emit widgetContextMenuRequested(widget, mapToGlobal(localPosition));
	} else {
		QMenu menu;
		foreach (TitledPanelPage *page, pages) {
			menu.addAction(page->m_visibleAction);
		}
		menu.exec(mapToGlobal(localPosition));
	}
}








