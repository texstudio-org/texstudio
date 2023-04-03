#ifndef Header_TitlePanel
#define Header_TitlePanel

#include "mostQtHeaders.h"
//#include "animatedsplitter.h"

class TitledPanelPage : public QObject
{
	Q_OBJECT

	friend class TitledPanel;

public:
	TitledPanelPage(QWidget *widget, const QString &id, const QString &title, const QIcon &icon = QIcon());
	~TitledPanelPage();

	void addToolbarAction(QAction *act);
	void addToolbarActions(const QList<QAction *>& actions);

	inline QString id() const;
	QWidget *widget();
	bool visible() const;

	static TitledPanelPage *fromId(const QString &id);
	static void updatePageTitle(const QString &id, const QString& newTitle);

signals:
	void titleChanged(QString);
	void iconChanged(QIcon);

public slots:
	void setTitle(const QString &title);
	void setIcon(const QIcon &icon);

private:
	static QHash<QString, TitledPanelPage *> allPages;

	QString m_id;
	QString m_title;
	QIcon m_icon;
	QWidget *m_widget;

	QAction *m_visibleAction;
	QAction *m_selectAction;
	QList<QAction *> *m_toolbarActions;
};
Q_DECLARE_METATYPE(TitledPanelPage *)


class TitledPanel : public QFrame
{
	Q_OBJECT

public:
	explicit TitledPanel(QWidget *parent = 0);

	enum PageSelectorStyle {ComboSelector, TabSelector};
	void appendPage(TitledPanelPage *page, bool guiUpdate = true);
	void removePage(TitledPanelPage *page, bool guiUpdate = true);
	int pageCount() const;
	TitledPanelPage *pageFromId(const QString &id);

	void setHiddenPageIds(const QStringList &hidden);
	QStringList hiddenPageIds() const;

	TitledPanelPage *currentPage() const;
	QString currentPageId() const;
	void showPage(const QString &id);
	void setCurrentPage(const QString &id);
	QAction *toggleViewAction() const;

	void setSelectorStyle(PageSelectorStyle style);

signals:
	void widgetContextMenuRequested(QWidget *widget, const QPoint &globalPosition);
	void pageChanged(const QString &id);
    void showPanel();

public slots:
	virtual void setVisible(bool visible);
	void updateTopbar();

private slots:
	void viewToggled(bool visible) { setVisible(visible); }

	void updatePageSelector(TitledPanelPage *page = 0);
	void onPageTitleChange();
	void onPageIconChange();

	void setActivePageFromAction();
	void setActivePageFromComboBox(int index);
	void setActivePageFromTabBar(int index);
	void togglePageVisibleFromAction(bool on);
	//void updateToolbarForResizing(CollapseState clState);
	void customContextMenuRequested(const QPoint &localPosition);

protected:
	QAction *mToggleViewAction;
	QAction *closeAction;

private:
	QStringList mHiddenPageIds;
	QActionGroup *pageSelectActions;    // only for visible widgets
	QList<QWidget *> widgets;

	// visual elements
	PageSelectorStyle selectorStyle;
	QVBoxLayout *vLayout; // containing title bar and contents
	QToolBar *topbar;
	QLabel *lbTopbarLabel;
	QComboBox *cbTopbarSelector;
	QTabBar *tbTopbarSelector;

	QStackedWidget *stack;

	QList<TitledPanelPage *> pages;
};

/*** class AutoCollapsingTitledPanel ***/
/*
class AutoCollapsingTitledPanel: public TitledPanel {
	Q_OBJECT
public:
	enum CollapseState {Expanded, Collapsed, Expanding, Collapsing};

	explicit AutoCollapsingTitledPanel(QWidget *parent=0) :
		TitledPanel(parent), expandedWidth(100), clState(Expanded), mCollapsingEnabled(false), mAnimatedMotion(false)
	{
		containingSplitter = qobject_cast<AnimatedSplitter *>(parent);
		if (containingSplitter)
			connect(containingSplitter, SIGNAL(animationFinished()), this, SLOT(sizingFinished()));
	}
	bool animatedMotion() const {return mAnimatedMotion;}
	bool collapsingEnabled() const {return mCollapsingEnabled;}
	bool collapsed() const {return clState == Collapsed;}
	void setCollapsed(bool collapse) {
		if (!mCollapsingEnabled) return;
		switch (clState) {
		case Expanded:
			if (collapse) {
				expandedWidth = width();
				triggerResize(Collapsing);
			}
			break;
		case Expanding:
			if (collapse) {
				// TODO: stop the animation and start collapsing
				qDebug() << "wah";
			}
			break;
		case Collapsed:
			if (!collapse) {
				triggerResize(Expanding);
			}
			break;
		case Collapsing:
			if (!collapse) {
				// TODO: stop the animation and start expanding
				qDebug() << "wahah";
			}
			break;
		}
	}
signals:
	void collapseStateChanged(CollapseState clState);
public slots:
	void setAnimatedMotion(bool enabled) { mAnimatedMotion = enabled; }
	void setCollapsingEnabled(bool enabled) {if (!enabled) setCollapsed(false); mCollapsingEnabled = enabled;}
protected:
	virtual int collapsedWidth() {qDebug() << 30; return 30;}
	virtual void enterEvent(QEvent *event) {
		TitledPanel::enterEvent(event);
		setCollapsed(false);
	}
	virtual void leaveEvent(QEvent *event) {
		TitledPanel::leaveEvent(event);
		setCollapsed(true);
	}
	virtual void resizeEvent(QResizeEvent *event) {
		TitledPanel::resizeEvent(event);
		if (clState == Collapsed && width() > collapsedWidth()) {
			clState = Expanded;
			qDebug() << "resize-event : state" << clState;
		}
	}
private slots:
	void sizingFinished() { clState = (clState==Expanding) ? Expanded : Collapsed; emit collapseStateChanged(clState);}
private:
	void triggerResize(CollapseState state) {
		if (!containingSplitter) return;
		containingSplitter->setActiveWidget(this);

		if (!mAnimatedMotion) {
			if (state == Collapsing) {
				emit collapseStateChanged(state);
				state = Collapsed;
			}
			if (state == Expanding) {
				state = Expanded;
				emit collapseStateChanged(state);
			}
		}

		qDebug() << "resize-trigg : state" << state << ", exWidth, width:"<< expandedWidth << width();

		switch (state) {
		case Expanded:
			containingSplitter->setActiveWidgetWidth(expandedWidth);
			clState = state;
			emit collapseStateChanged(state);
			break;
		case Collapsed:
			containingSplitter->setActiveWidgetWidth(collapsedWidth());
			clState = state;
			emit collapseStateChanged(state);
			break;
		case Expanding:
			clState = state;
			emit collapseStateChanged(state);
			containingSplitter->animateActiveWidgetWidth(expandedWidth);
			break;
		case Collapsing:
			clState = state;
			emit collapseStateChanged(state);
			containingSplitter->animateActiveWidgetWidth(collapsedWidth());
			break;
		}
	}

	QToolBar *collapsedTopbar;
	AnimatedSplitter *containingSplitter;
	int expandedWidth;
	CollapseState clState;
	bool mCollapsingEnabled;
	bool mAnimatedMotion;
};
*/

#endif // TITLEDPANEL_H
