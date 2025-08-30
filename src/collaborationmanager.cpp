#include "collaborationmanager.h"
#include <qjsonarray.h>

CollaborationManager::CollaborationManager(QObject *parent, ConfigManager *conf,LatexDocuments *docs)
{
    m_conf=conf;
    m_docs=docs;
}

CollaborationManager::~CollaborationManager()
{
    // stop all processes
    stopClient();
    stopServer();
}
/*!
 * \brief start ethersync client process
 * \param folder directory in which to start
 * \return successful start
 */
bool CollaborationManager::startClient(const QString folder)
{
    if(isClientRunning()){
        // already running
        return false;
    }
    const QString binPath=m_conf->ce_toolPath;
    QString folderName=m_conf->ce_clientPath;
    if(!binPath.isEmpty()){
        QDir dir(folderName);
        dir.mkpath(".ethersync");
        collabClientProcess = new QProcess(this);
        collabClientProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabClientProcess, &QProcess::readyReadStandardOutput, this,&CollaborationManager::readyCollabClientStandardOutput);
        connect(collabClientProcess, qOverload<int,QProcess::ExitStatus>(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug() << "Collaboration client finished with exit code" << exitCode << "and status" << exitStatus;
            collabClientProcess = nullptr;
        });
        const QStringList args2={"client", "--directory", folderName};
        collabClientProcess->start(binPath,args2);
        if (!collabClientProcess->waitForStarted(1000)) {
            collabClientProcess = nullptr;
            return false;
        }
        return true;
    }
    return false;
}
/*!
 * \brief kill running client
 */
void CollaborationManager::stopClient()
{
    if(collabClientProcess){
        collabClientProcess->kill();
        collabClientProcess = nullptr;
    }
}
/*!
 * \brief check if client is running
 * \return
 */
bool CollaborationManager::isClientRunning()
{
    return (collabClientProcess != nullptr);
}
/*!
 * \brief start host server
 * ethersync share --directory <folder>
 * \param folder directory which is synced
 * \return successful start
 */
bool CollaborationManager::startHostServer(const QString folder)
{
    if(isServerRunning() || isClientRunning()){
        // already running
        return false;
    }
    // start server
    const QString binPath=m_conf->ce_toolPath;
    if(!binPath.isEmpty()){
        // run binPath share folder
        collabHostServerProcess = new QProcess(this);
        collabHostServerProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabHostServerProcess, &QProcess::readyReadStandardOutput, this, &CollaborationManager::readyCollabServerStandardOutput);
        connect(collabHostServerProcess, qOverload<int,QProcess::ExitStatus>(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug() << "Collaboration server finished with exit code" << exitCode << "and status" << exitStatus;
            collabHostServerProcess = nullptr;
        });
        QStringList args{"share","--directory", folder};
        collabHostServerProcess->start(binPath,args);
        if (!collabHostServerProcess->waitForStarted(1000)) {
            collabHostServerProcess = nullptr;
            return false;
        }
    }
    return false;
}
/*!
 * \brief start guest server
 * ethersync join <code> --directory <folder>
 * \param folder directory which is synced, should be empty and will be filled by the host
 * \param code the code provided by the host
 * \return successful start
 */
bool CollaborationManager::startGuestServer(const QString folder,const QString &code)
{
    if(isServerRunning() || isClientRunning()){
        // already running
        return false;
    }
    const QString binPath=m_conf->ce_toolPath;
    QString folderName=m_conf->ce_clientPath;
    QDir dir(folderName);
    dir.mkpath(".ethersync");
    if(!binPath.isEmpty()){
        // run binPath share folder
        collabGuestServerProcess = new QProcess(this);
        collabGuestServerProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabGuestServerProcess, &QProcess::readyReadStandardOutput, this, &CollaborationManager::readyCollabServerStandardOutput);
        connect(collabGuestServerProcess, &QProcess::finished, this, [this](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug() << "Collaboration client finished with exit code" << exitCode << "and status" << exitStatus;
            collabGuestServerProcess = nullptr;
        });
        const QStringList args{"join", code, "--directory", folderName};
        collabGuestServerProcess->start(binPath,args);
        if (!collabGuestServerProcess->waitForStarted(1000)) {
            collabGuestServerProcess = nullptr;
            return false;
        }
        return true;
    }
    return false;
}
/*!
 * \brief kill running server
 * Can be either host or guest server
 */
void CollaborationManager::stopServer()
{
    if(collabHostServerProcess){
        collabHostServerProcess->kill();
        collabHostServerProcess = nullptr;
    }
    if(collabGuestServerProcess){
        collabGuestServerProcess->kill();
        collabGuestServerProcess = nullptr;
    }
}
/*!
 * \brief check if server is running
 * \return
 */
bool CollaborationManager::isServerRunning()
{
    return (collabHostServerProcess!=nullptr || collabGuestServerProcess!=nullptr);
}
/*!
 * \brief send updates to client
 * \param cursor
 * \param changes
 */
void CollaborationManager::sendChanges(QDocumentCursor cursor, const QString &changes)
{
    qDebug()<<"to be implemented: send changes to client";
    if(!isClientRunning()){
        return;
    }
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="edit";
    QJsonObject jparams;
    QDocumentLineHandle *dlh=cursor.line().handle();
    LatexDocument *doc=dynamic_cast<LatexDocument*>(dlh->document());
    jparams["uri"]="file://"+doc->getFileName();
    QJsonObject jrange;
    QJsonObject jstart;
    jstart["line"]=cursor.lineNumber();
    jstart["character"]=cursor.columnNumber();
    jrange["start"]=jstart;
    QJsonObject jend;
    jstart["line"]=cursor.anchorLineNumber();
    jstart["character"]=cursor.anchorColumnNumber();
    jrange["end"]=jend;
    jrange["replacement"]=changes;
    QJsonArray jdelta;
    jdelta.append(jrange);
    jparams["delta"]=jdelta;
    jo["params"]=jparams;
    sendToClient(jo);
}
/*!
 * \brief send cursor position to client
 * \param cursor
 */
void CollaborationManager::sendCursor(QDocumentCursor cursor)
{
    if(!isClientRunning()){
        return;
    }
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="cursor";
    QJsonObject jparams;
    QDocumentLineHandle *dlh=cursor.line().handle();
    LatexDocument *doc=dynamic_cast<LatexDocument*>(dlh->document());
    jparams["uri"]="file://"+doc->getFileName();
    QJsonObject jrange;
    QJsonObject jstart;
    jstart["line"]=cursor.lineNumber();
    jstart["character"]=cursor.columnNumber();
    jrange["start"]=jstart;
    QJsonObject jend;
    jstart["line"]=cursor.anchorLineNumber();
    jstart["character"]=cursor.anchorColumnNumber();
    jrange["end"]=jend;
    QJsonArray jranges;
    jranges.append(jrange);
    jparams["ranges"]=jranges;
    jparams["user"]=m_conf->ce_userName;
    jo["params"]=jparams;
    sendToClient(jo);
}
/*!
 * \brief notify client that file was opened
 * \param fileName
 */
void CollaborationManager::fileOpened(const QString fileName)
{
    if(!isClientRunning()){
        return;
    }
    openFileInClient(fileName);
}
/*!
 * \brief notify client that file was closed
 * \param fileName
 */
void CollaborationManager::fileClosed(const QString fileName)
{
    if(!isClientRunning()){
        return;
    }
    closeFileInClient(fileName);
}

void CollaborationManager::readyCollabClientStandardOutput()
{
    QString buffer = collabClientProcess->readAllStandardOutput();
    // interpret message
    QStringList lines= buffer.split("\r\n", Qt::SkipEmptyParts);
    for(QString line : lines){
        if(line.startsWith("{\"jsonrpc\":\"2.0\"")){
            // cut potential Content-Length
            int i=line.indexOf("Content-Length:");
            if(i>0){
                line=line.left(i);
            }
            // parse line
            QJsonDocument jd=QJsonDocument::fromJson(line.toUtf8());
            QJsonObject dd=jd.object();
            QString method=dd["method"].toString();
            if(method=="cursor"){
                QJsonObject ja=dd["params"].toObject();
                // extract uri
                QString uri=ja["uri"].toString();
                // find doc from uri
                if(!uri.startsWith("file://")){
                    return;
                }
                QString fileName=uri.mid(7);
                LatexDocument *doc=findDocumentFromName(fileName);
                QJsonArray jranges=ja["ranges"].toArray();
                if(jranges.size()>0){
                    QJsonObject jcursor=jranges[0].toObject();
                    QJsonObject jstart=jcursor["start"].toObject();
                    QJsonObject jend=jcursor["end"].toObject();
                    int col=jstart["character"].toInt(-1);
                    int ln=jstart["line"].toInt(-1);
                    if(ln>=0 && col>=0){
                        QString userName=ja["user"].toString("extern");
                        QDocumentCursor c(doc);
                        c.moveTo(ln,col);
                        emit cursorMoved(c,userName);
                    }
                }
            }
            if(method=="edit"){
                QJsonObject ja=dd["params"].toObject();
                QString uri=ja["uri"].toString();
                // find doc from uri
                if(!uri.startsWith("file://")){
                    return;
                }
                QString fileName=uri.mid(7);
                LatexDocument *doc=findDocumentFromName(fileName);
                QJsonArray jdelta=ja["delta"].toArray();
                if(jdelta.size()>0){
                    QJsonObject jelem=jdelta[0].toObject();
                    QJsonObject jcursor=jelem["range"].toObject();
                    QJsonObject jstart=jcursor["start"].toObject();
                    QJsonObject jend=jcursor["end"].toObject();
                    QString replacement=jelem["replacement"].toString();
                    int col=jstart["character"].toInt(-1);
                    int ln=jstart["line"].toInt(-1);
                    int col2=jend["character"].toInt(-1);
                    int ln2=jend["line"].toInt(-1);
                    if(ln>=0 && col>=0){
                        QString userName=ja["user"].toString("extern");
                        QDocumentCursor c(doc);
                        c.moveTo(ln,col);
                        c.moveTo(ln2,col2,QDocumentCursor::KeepAnchor);
                        emit changesReceived(c,replacement,userName);
                    }
                }
            }

        }
    }
}

void CollaborationManager::readyCollabServerStandardOutput()
{
    // for now, just dump output to debug
    QString buffer = collabHostServerProcess->readAllStandardOutput();
    qDebug() << "Collab Server Output:" << buffer;
}

/*!
 * \brief send json data to client process
 * \param jo
 */
void CollaborationManager::sendToClient(const QJsonObject &jo)
{
    QJsonDocument jd(jo);
    QString json=jd.toJson(QJsonDocument::Compact);
    json.prepend("Content-Length: " + QString::number(json.length()) + "\r\n\r\n");
    // send json
    collabClientProcess->write(json.toUtf8());
}
/*!
 * \brief send notification to client that a file has been opened
 * \param fileName
 */
void CollaborationManager::openFileInClient(const QString &fileName)
{
    // open file, send json
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="open";
    QJsonObject jparams;
    jparams["uri"]="file://"+fileName;
    jparams["content"]="";
    jo["params"]=jparams;
    sendToClient(jo);
}
/*!
 * \brief send notification to client that a file has been closed
 * \param fileName
 */
void CollaborationManager::closeFileInClient(const QString &fileName)
{
    // open file, send json
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="close";
    QJsonObject jparams;
    jparams["uri"]="file://"+fileName;
    jparams["content"]="";
    jo["params"]=jparams;
    sendToClient(jo);
}
/*!
 * \brief find corresponding document from file name if open
 * Helper function
 * \param fileName
 * \return pointer to document or nullptr if not found
 */
LatexDocument *CollaborationManager::findDocumentFromName(const QString &fileName)
{
    if(m_docs==nullptr){
       return nullptr;
    }
    return m_docs->findDocumentFromName(fileName);
}
