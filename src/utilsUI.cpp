#include "utilsUI.h"
#include "utilsSystem.h"
#include "utilsVersion.h"
#include "filedialog.h"


extern void hideSplash();

namespace UtilsUi {

bool txsConfirm(const QString &message)
{
	hideSplash();
	return QMessageBox::question(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}

bool txsConfirmWarning(const QString &message)
{
	hideSplash();
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}

QMessageBox::StandardButton txsConfirmWarning(const QString &message, QMessageBox::StandardButtons buttons)
{
	hideSplash();
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, buttons, QMessageBox::Yes);
}

void txsInformation(const QString &message)
{
	hideSplash();
	QMessageBox::information(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}

void txsWarning(const QString &message)
{
	hideSplash();
	QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}

void txsWarning(const QString &message, bool &noWarnAgain)
{
	hideSplash();
	QMessageBox msgBox(QMessageBox::Warning, TEXSTUDIO, message, QMessageBox::Ok, QApplication::activeWindow());
	QCheckBox cbNoWarnAgain(QCoreApplication::translate("Texstudio", "Do not warn again.", "General warning dialog"), &msgBox);
	cbNoWarnAgain.setChecked(noWarnAgain);
	cbNoWarnAgain.blockSignals(true); // quick hack to prevent closing the message box
	msgBox.addButton(&cbNoWarnAgain, QMessageBox::ActionRole);
	msgBox.exec();
	noWarnAgain = cbNoWarnAgain.isChecked();
}

void txsCritical(const QString &message)
{
	hideSplash();
	QMessageBox::critical(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}

QToolButton *createComboToolButton(QWidget *parent, const QStringList &list, const QList<QIcon> &icons, int height, const QObject *receiver, const char *member, int defaultIndex, QToolButton *combo)
{
	Q_UNUSED(icons)
	const QFontMetrics &fm = parent->fontMetrics();
	if (height == -1) height = 0;
	else if (height == 0) {
		if (parent->property("innerButtonHeight").isValid()) height = parent->property("innerButtonHeight").toInt();
		else {
			height = parent->height() - 2;
			parent->setProperty("innerButtonHeight", height);
		}
	}

    if (combo == nullptr)
		combo = new QToolButton(parent);
	if (height != 0)
		combo->setMinimumHeight(height);
	combo->setPopupMode(QToolButton::MenuButtonPopup);
	combo->setToolButtonStyle(Qt::ToolButtonTextOnly);

	// remove old actions
	foreach (QAction *mAction, combo->actions())
		combo->removeAction(mAction);

	QMenu *mMenu = new QMenu(combo);
	int max = 0;
	bool defaultSet = false;
	for (int i = 0; i < list.length(); i++) {
		QString text = list[i];
		//QIcon icon = (i<icons.length()) ? icons[i] : QIcon();
		QAction *mAction = mMenu->addAction(text, receiver, member);
		max = qMax(max, fm.width(text + "        "));
		if (i == defaultIndex) {
			combo->setDefaultAction(mAction);
			defaultSet = true;
		}
	}
	if (!defaultSet) {
		if (list.isEmpty())
			combo->setDefaultAction(new QAction("<" + QApplication::tr("none") + ">", combo));
		else
			combo->setDefaultAction(mMenu->actions().first());
	}

	combo->setMinimumWidth(max);
	combo->setMenu(mMenu);
	return combo;
}

QToolButton *comboToolButtonFromAction(QAction *action)
{
    if (!action) return nullptr;
	QToolButton *button = qobject_cast<QToolButton *>(action->parent());
	if (!button) {
		QMenu *menu = qobject_cast<QMenu *>(action->parent());
        if (!menu) return nullptr;
		button = qobject_cast<QToolButton *>(menu->parent());
        if (!button) return nullptr;
	}
	return button;
}

QToolButton *createToolButtonForAction(QAction *action)
{
	QToolButton *tb = new QToolButton();
	if (!action->icon().isNull())
		tb->setIcon(action->icon());
	else
		tb->setText(action->text());
	tb->setToolTip(action->toolTip());
	tb->setCheckable(action->isCheckable());
	tb->setChecked(action->isChecked());
	tb->connect(tb, SIGNAL(clicked(bool)), action, SLOT(setChecked(bool)));
	tb->connect(action, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
	return tb;
}

void setSubtreeExpanded(QTreeView *view, QModelIndex idx, bool expand)
{
	for (int row = 0;; row++) {
		QModelIndex node = view->model()->index(row, 0, idx);
		if (!node.isValid())
			break;
		setSubtreeExpanded(view, node, expand);
	}
	view->setExpanded(idx, expand);
}

bool browse(QWidget *w, const QString &title, const QString &extension, const QString &startPath, bool list)
{
	QLineEdit *le = qobject_cast<QLineEdit *>(w);
	QComboBox *cb = qobject_cast<QComboBox *>(w);
	REQUIRE_RET(le || cb, false);
	QString oldpath = le ? le->text() : cb->currentText();
	QString path = oldpath;
#ifdef Q_OS_WIN32
	QString pathSep = ";";
#else
	QString pathSep = ":";
#endif
	if (list && !path.isEmpty()) path = path.split(pathSep).last();
	if (path.startsWith('"')) path.remove(0, 1);
	if (path.endsWith('"')) path.chop(1);
	if (path.isEmpty()) path = startPath;
    if (extension == "/") path = QFileDialog::getExistingDirectory(nullptr, title, path);
    else path = FileDialog::getOpenFileName(nullptr, title, path, extension, nullptr, QFileDialog::DontResolveSymlinks);
	if (!path.isEmpty()) {
		path = QDir::toNativeSeparators(path);
		if (list && !oldpath.isEmpty()) path = oldpath + pathSep + path;
		if (le) le->setText(path);
		if (cb) cb->setEditText(path);
		return true;
	}
	return false;
}

QColor colorFromRGBAstr(const QString &hex, QColor fallback)
{
	QString c = hex;
	if (c.startsWith('#'))
		c = c.mid(1);
	if (c.length() != 8) return fallback;
	bool r, g, b, a;
	QColor color(c.mid(0, 2).toInt(&r, 16), c.mid(2, 2).toInt(&g, 16), c.mid(4, 2).toInt(&b, 16), c.mid(6, 2).toInt(&a, 16));
	if (r && g && b && a)
		return color;
	return fallback;
}

/*!
  Return a color with a more medium value. The amount of change is determined by factor. I.e. for a factor > 100
  a dark color becomes lighter, a light color becomes darker. The reverse is true for factors < 100;
  This is a generalization of QColor.lighter()/darker() which should provide a reasonable change in dark as well
  as light contexts.
 */
QColor mediumLightColor(QColor color, int factor) {
	if (color.value() == 0) {  // special handling for black because lighter() does not work there [QTBUG-9343].
		factor = qMax(0, factor - 100);
		return QColor(factor, factor, factor);  // i.e. QColor(50, 50, 50) for factor 150
	}
	if (color.value() < 128) {
		return color.lighter(factor);
	} else {
		return color.darker(factor);
	}
}

/*!
 * return the window to which an object belongs or the given fallback widget
 * Note: the signature is intentionally for a gerneric QObject, so that we can
 * simply call windowForObject(sender()).
 */
QWidget *windowForObject(QObject *obj, QWidget *fallback)
{
	QWidget *w;
	QAction *act = qobject_cast<QAction *>(obj);
	if (act) {
		w = act->parentWidget();
	} else {
		w = qobject_cast<QWidget *>(obj);
	}
	if (w) {
		w = w->window();
	}
	if (w) {
		return w;
	}
	return fallback;
}


/*!
  interal
  guesses a descriptive text from a text suited for a menu entry
  This is copied from the internal function qt_strippedText() in qaction.cpp
 */
static QString strippedActionText(QString s) {
	s.remove( QString::fromLatin1("...") );
	for (int i = 0; i < s.size(); ++i) {
		if (s.at(i) == QLatin1Char('&'))
		s.remove(i, 1);
	}
	return s.trimmed();
}

/*!
  interal
  Adds possible shortcut information to the tooltip of the action.
  This provides consistent behavior both with default and custom tooltips
  when used in combination with removeShortcutToToolTip()
 */
void addShortcutToToolTip(QAction *action)
{
	if (!action->shortcut().isEmpty()) {
		QString tooltip = action->property("tooltipBackup").toString();
		if (tooltip.isEmpty()) {
			tooltip = action->toolTip();
			if (tooltip != strippedActionText(action->text())) {
				action->setProperty("tooltipBackup", action->toolTip());  // action uses a custom tooltip. Backup so that we can restore it later.
			}
		}
		QColor shortcutTextColor = QApplication::palette().color(QPalette::ToolTipText);
		QString shortCutTextColorName;
		if (shortcutTextColor.value() == 0) {
			shortCutTextColorName = "gray";  // special handling for black because lighter() does not work there [QTBUG-9343].
		} else {
			int factor = (shortcutTextColor.value() < 128) ? 150 : 50;
			shortCutTextColorName = shortcutTextColor.lighter(factor).name();
		}
		action->setToolTip(QString("<p style='white-space:pre'>%1&nbsp;&nbsp;<code style='color:%2; font-size:small'>%3</code></p>")
		                   .arg(tooltip, shortCutTextColorName, action->shortcut().toString(QKeySequence::NativeText)));
	}
}

/*!
  interal
  Removes possible shortcut information from the tooltip of the action.
  This provides consistent behavior both with default and custom tooltips
  when used in combination with addShortcutToToolTip()
 */
void removeShortcutFromToolTip(QAction *action)
{
	action->setToolTip(action->property("tooltipBackup").toString());
	action->setProperty("tooltipBackup", QVariant());
}

/*!
  Adds or removes shortcut information from the tooltip of the action.
  This provides consistent behavior both with default and custom tooltips.
 */
void updateToolTipWithShortcut(QAction *action, bool showShortcut) {
	if (showShortcut) {
		addShortcutToToolTip(action);
	} else {
		removeShortcutFromToolTip(action);
	}
}

/*!
 * \brief Adds support for a single-finger panning gesture to the widget using a QScroller.
 * \note ItemViews will be switched to ScrollPerPixel scrollMode.
 */
void enableTouchScrolling(QWidget *widget, bool enable) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)  && !defined(Q_OS_MAC)
	if (enable) {
		QAbstractItemView *view = qobject_cast<QAbstractItemView *>(widget);
		if (view) {
			// QScroller needs per pixel scrolling otherwise distances and speed
			// are calculated incorrectly.
			view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
		}
		QScroller::grabGesture(widget, QScroller::TouchGesture);
	} else {
		QScroller::ungrabGesture(widget);
	}
#endif
}

/*!
 * Resize a window with width and height given in units of the application font height.
 * This allows to scale dialogs to a size that you'll get almost the same context visible
 * independent of UI scaling parameters.
 */
void resizeInFontHeight(QWidget *w, int width, int height)
{
	int h = qApp->fontMetrics().height();
	QDesktopWidget *dw = qApp->desktop();
	QRect r = dw->availableGeometry(w);
	QSize newSize = QSize(qMin(h * width, r.width()), qMin(h * height, r.height()));
	//qDebug() << "resizeInFontHeight old size:" << w->width() / (float) h << w->height() / (float) h;
	//qDebug() << "resizeInFontHeight new size:" << newSize.width() / (float) h << newSize.height() / (float) h;
	w->resize(newSize);
}

}  // namespace UtilsUi
