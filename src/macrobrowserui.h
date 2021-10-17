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
    void requestMacroList(const QString &path="",const bool &directURL=false);
    void itemClicked(QTableWidgetItem *item);

protected:
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QLineEdit *leName;
    QPlainTextEdit *teDescription;
    QString currentPath;
    QHash<QString,QString> cache;
    QHash<QString,QList<QTableWidgetItem *> > itemCache;

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
};

#endif // MACROBROWSERUI_H
