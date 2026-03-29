#ifndef AICHATASSISTANT_H
#define AICHATASSISTANT_H

#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "chatdelegate.h"

extern bool darkMode;

class AIChatAssistant : public QDialog
{
    Q_OBJECT
public:
    explicit AIChatAssistant(QWidget *parent = nullptr);
    ~AIChatAssistant() override;

    void setQueryText(const QString &text);
    void clearConversation();
    void executeQuery();

signals:
    void insertText(QString text);
    void executeMacro(QString script);

private slots:
    void slotSend(bool fromToolCall=false);
    void slotInsert();
    void slotCopyText();
    void slotOptions();
    void slotSearch();
    void slotUpdateResults();
    void onRequestError(QNetworkReply::NetworkError code);
    void onRequestCompleted(QNetworkReply *nreply);
    void onTreeViewClicked(const QModelIndex &index);
    void insertTextClicked(const QModelIndex &index);
    void slotShowContextMenu(const QPoint &pos);

protected:
    QTreeView *treeView;
    QToolButton *m_btSend;
    QAction *m_actSend;
    QToolButton *m_btInsert;
    QAction *m_actInsert;
    QToolButton *m_btOptions;
    QAction *m_actOptions;
    QTextEdit *leEntry;
    QLineEdit *m_leSearch;
    QToolButton *m_btSearch;
    QAction *m_actSearch;
    QListView *chatView;
    QStandardItemModel *chatmodel;
    QSplitter *hlBrowser;

    QString m_response;
    QString m_conversationFileName;

    QJsonArray ja_messages;

    QTimer *m_timer = nullptr;

    ConfigManager *config;

    QNetworkAccessManager *networkManager;
    QNetworkReply *m_reply = nullptr;
    void writeToFile(QString filename, QString content);
    QString makeJsonDoc() const;
    void updateConversationForChatview();
    void updateStreamedConversation(const QString &allData);
    QJsonArray makeFunctionsJsonArray() const;
    void handleToolCall(QJsonObject jo);

    void addMessage (const QString &text, Sender sender);
    void insertTextAtCursor(const QString &text);

    QString tfGetFilename(const QString arg=QString()) const;
    QString tfGetListFiles(const QString arg=QString()) const;
    QString tfGetSelection(const QString arg=QString()) const;
    QString tfRunMacro(const QString arg) const; //TODO ?
    QString tfGetLog(const QString arg=QString()) const; // TODO ? fails only ?
    QString tfGetText(const QString arg=QString()) const;
    QString tfSetCursor(const QString arg) const;
    QString tfSetSelection(const QString arg) const;
    QString tfGetCursorPosition(const QString arg=QString()) const;
    QString tfGetLineText(const QString arg) const;
    QString tfGetLineLength(const QString arg) const;
    QString tfGetNumberLines(const QString arg) const;

    QMap<QString,int> retrieveToolArguments(const QString &parameter) const;

    struct ToolFunction
    {
        QString name;
        QString description;
        QString parameter;
        std::function<QString(const QString)> func;
    };
    QList<ToolFunction> m_toolFunctions;
    /*!
     * \brief register functions as tools for AI provider
     */
    void registerToolFunctions();
};

#endif // AICHATASSISTANT_H
