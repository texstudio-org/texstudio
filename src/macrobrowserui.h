#ifndef Header_MacroBrowser_UI
#define Header_MacroBrowser_UI

#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include "usermacro.h"

/*!
 * \brief provide simple UI to browse macros from github.com/texstudio-org/texstudio-macro
 */
class MacroBrowserUI : public QDialog
{
    Q_OBJECT

public:
    MacroBrowserUI(QWidget *parent=nullptr);
    ~MacroBrowserUI();

    QList<Macro> getSelectedMacros();

private slots:
    void onRequestError();
    void onRequestCompleted();
    void requestMacroList(QTreeWidgetItem *item=nullptr,const bool &isFile=false);
    void slotItemExpanded(QTreeWidgetItem *item);
    void slotCurrentItemChanged(QTreeWidgetItem *item);
    void slotItemClicked(QTreeWidgetItem *item);

private:
    static const int FileRole;
    static const int UrlRole;
    static const int PathRole;
    static const int PopulatedRole;

protected:
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;
    QLineEdit *leName;
    QPlainTextEdit *teDescription;
    QHash<QString,QString> cache;

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
};

#endif // MACROBROWSERUI_H
