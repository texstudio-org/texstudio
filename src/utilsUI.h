#ifndef Header_UtilsUI
#define Header_UtilsUI

#include "mostQtHeaders.h"


namespace UtilsUi {

enum txsWarningState {DontRemember,RememberFalse,RememberTrue};

bool txsConfirm(const QString &message);
bool txsConfirmWarning(const QString &message);
bool txsConfirmWarning(const QString &message,txsWarningState &rememberChoice);
QMessageBox::StandardButton txsConfirmWarning(const QString &message, QMessageBox::StandardButtons buttons);
void txsInformation(const QString &message);
void txsWarning(const QString &message);
void txsWarning(const QString &message, bool &noWarnAgain);
void txsCritical(const QString &message);

//setup toolbutton as substitute for const combobox
QToolButton* createComboToolButton(QWidget *parent, const QStringList &list, const QStringList &infos, const QList<QIcon> &icons, int height, const QObject *receiver, const char *member, int defaultIndex = -1, QToolButton *combo = nullptr);

//find the tool button which contains a given action
QToolButton *comboToolButtonFromAction(QAction *action);

QToolButton *createToolButtonForAction(QAction *action);

void setSubtreeExpanded(QTreeView *view, QModelIndex idx, bool expand);
void setSubtreeExpanded(QTreeWidgetItem *item, bool expand);

// opens a selection dialog and inserts the selected file(s) or path into widget
bool browse(QWidget *w, const QString &title, const QString &extension, const QString &startPath = QDir::homePath(), bool list = false);

QColor colorFromRGBAstr(const QString &hex, QColor fallback = QColor());
QColor mediumLightColor(QColor color, int factor = 150);

QWidget *windowForObject(QObject *obj, QWidget *fallback);

void updateToolTipWithShortcut(QAction *action, bool showShortcut);

void enableTouchScrolling(QWidget *w, bool enable = true);

void resizeInFontHeight(QWidget *w, int width, int height);

// Given font metrics returns the text pixel size
int getFmWidth(const QFontMetrics &fm, QChar ch);
qreal getFmWidth(const QFontMetricsF &fm, QChar ch);
int getFmWidth(const QFontMetrics &fm, const QString &text, int len = -1);
qreal getFmWidth(const QFontMetricsF &fm, const QString &text, int len = -1);

// Return the screen geometry for a given point
QRect getAvailableGeometryAt(const QPoint &pos);

}  // namespace UtilsUi

#endif // UTILSUI_H
