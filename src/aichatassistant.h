#ifndef AICHATASSISTANT_H
#define AICHATASSISTANT_H

#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>

class AIChatAssistant : public QDialog
{
    Q_OBJECT
public:
    explicit AIChatAssistant(QWidget *parent = nullptr);
    ~AIChatAssistant() override;

    void setSelectedText(QString text);

signals:
    void insertText(QString text);

private slots:
    void slotSend();
    void slotInsert();
    void slotOptions();
    void onRequestError(QNetworkReply::NetworkError code);
    void onRequestCompleted(QNetworkReply *nreply);

protected:
    QTreeWidget *treeWidget;
    QTreeWidgetItem *topItem;
    QTextBrowser *textBrowser;
    QPushButton *btSend;
    QPushButton *btInsert;
    QPushButton *btOptions;
    QTextEdit *leEntry;

    QString m_response;
    QString m_selectedText;

    QJsonArray ja_messages;

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
};

#endif // AICHATASSISTANT_H
