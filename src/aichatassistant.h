#ifndef AICHATASSISTANT_H
#define AICHATASSISTANT_H

#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class AIChatAssistant : public QDialog
{
    Q_OBJECT
public:
    explicit AIChatAssistant(QWidget *parent = nullptr);
    ~AIChatAssistant() override;

signals:

private slots:
    void slotSend();
    void onRequestError(QNetworkReply::NetworkError code);
    void onRequestCompleted(QNetworkReply *nreply);

protected:
    QTreeWidget *treeWidget;
    QTextBrowser *textBrowser;
    QPushButton *btSend;
    QLineEdit *leEntry;

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
};

#endif // AICHATASSISTANT_H
