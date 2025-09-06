#ifndef COLLABORATIONMANAGER_H
#define COLLABORATIONMANAGER_H

//#include "mostQtHeaders.h"
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
    bool isFileLocatedInCollabFolder(const QString &filename);
    void resetCollabCommand();
    QString readErrorMessage();
    QString collabClientFolder() const;

    void fileOpened(const QString fileName);
    void fileClosed(const QString fileName);

public slots:
    void sendChanges(QDocumentCursor cursor, const QString &changes);
    void sendChanges(QString fileName,int startLine,int startCol,int endLine,int endCol, const QString &changes);
    void sendCursor(QDocumentCursor cursor);

signals:
    void changesReceived(QDocumentCursor cursor, const QString changes,const QString userName);
    void cursorMoved(QDocumentCursor cursor,const QString userId);
    void clientSuccessfullyStarted();
    void guestServerSuccessfullyStarted();
    void collabClientFinished(int exitCode,QString m_errorMessage);

private slots:
    void readyCollabClientStandardOutput();
    void readyCollabServerStandardOutput();

    void clientFinished(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    void sendToClient(const QJsonObject &jo);
    void openFileInClient(const QString &fileName);
    void closeFileInClient(const QString &fileName);

    LatexDocument *findDocumentFromName(const QString &fileName) const;

    ConfigManager *m_conf=nullptr;
    LatexDocuments *m_docs=nullptr;

    QProcess *collabServerProcess = nullptr; /// for host server: ethersync share
    QProcess *collabClientProcess = nullptr; /// for client: ethersync client

    bool m_startingEthersyncFailed = false; /// if command start fails, all further attempts are moot
    QString m_errorMessage; /// last error message
    QString m_collabClientFolder; /// folder for which collab client was started
};

#endif // COLLABORATIONMANAGER_H
