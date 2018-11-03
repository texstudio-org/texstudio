#ifndef MACROBROWSERUI_H
#define MACROBROWSERUI_H

#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QNetworkAccessManager>
#include <QPlainTextEdit>

class MacroBrowserUI : public QDialog
{
    Q_OBJECT

public:
    MacroBrowserUI(QWidget *parent=nullptr);
    ~MacroBrowserUI();

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

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
};

#endif // MACROBROWSERUI_H
