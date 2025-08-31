#ifndef COLLABORATIONMANAGER_H
#define COLLABORATIONMANAGER_H

#include "mostQtHeaders.h"
#include "qdocumentcursor.h"
#include "configmanager.h"
#include "latexdocument.h"

class CollaborationManager : public QObject
{
    Q_OBJECT
public:
    explicit CollaborationManager(QObject *parent ,ConfigManager *conf,LatexDocuments *docs);
    ~CollaborationManager();

    bool startClient(const QString folder);
    void stopClient();
    bool isClientRunning();
    bool startHostServer(const QString folder);
    bool startGuestServer(const QString folder, const QString &code);
    void stopServer();
    bool isServerRunning();

public slots:
    void sendChanges(QDocumentCursor cursor, const QString &changes);
    void sendChanges(QString fileName,int startLine,int startCol,int endLine,int endCol, const QString &changes);
    void sendCursor(QDocumentCursor cursor);
    void fileOpened(const QString fileName);
    void fileClosed(const QString fileName);
signals:
    void changesReceived(QDocumentCursor cursor, const QString changes,const QString userName);
    void cursorMoved(QDocumentCursor cursor,const QString userName);

private slots:
    void readyCollabClientStandardOutput();
    void readyCollabServerStandardOutput();

protected:
    void sendToClient(const QJsonObject &jo);
    void openFileInClient(const QString &fileName);
    void closeFileInClient(const QString &fileName);

    LatexDocument *findDocumentFromName(const QString &fileName);

    ConfigManager *m_conf=nullptr;
    LatexDocuments *m_docs=nullptr;

    QProcess *collabHostServerProcess = nullptr; /// for host server: ethersync share
    QProcess *collabGuestServerProcess = nullptr; /// for guest server: ethersync join
    QProcess *collabClientProcess = nullptr; /// for client: ethersync client
};

#endif // COLLABORATIONMANAGER_H
