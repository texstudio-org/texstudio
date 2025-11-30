#include "collaborationmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "qdocumentcursor_p.h"

CollaborationManager::CollaborationManager(QObject *parent, ConfigManager *conf,LatexDocuments *docs)
{
    m_conf=conf;
    m_docs=docs;
}

CollaborationManager::~CollaborationManager()
{
    // stop all processes
    if(collabClientProcess){
        collabClientProcess->terminate();
        collabClientProcess=nullptr;
    }
    if(collabServerProcess){
        collabServerProcess->terminate();
        collabServerProcess=nullptr;
    }
}
/*!
 * \brief start teamtype client process
 * \param folder directory in which to start
 * \return successful start
 */
bool CollaborationManager::startClient(const QString folder)
{
    if(m_startingEthersyncFailed || isClientRunning()){
        // already running or start failed
        return false;
    }
    const QString binPath=m_conf->ce_toolPath;
    if(!binPath.isEmpty()){
        QDir dir(folder);
        collabClientProcess = new QProcess(this);
        collabClientProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabClientProcess, &QProcess::readyReadStandardOutput, this,&CollaborationManager::readyCollabClientStandardOutput);
        connect(collabClientProcess, qOverload<int,QProcess::ExitStatus>(&QProcess::finished), this, &CollaborationManager::clientFinished);
        const QStringList args2={"client", "--directory", folder};
        collabClientProcess->start(binPath,args2);
        if (!collabClientProcess->waitForStarted(1000)) {
            m_errorMessage=collabClientProcess->readAllStandardError();
            m_startingEthersyncFailed = true;
            collabClientProcess = nullptr;
            return false;
        }
        m_collabClientFolder=folder;
        emit clientSuccessfullyStarted();
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
        collabClientProcess->terminate();
        if(!collabClientProcess->waitForFinished(2000)){
            collabClientProcess->kill();
        }
        delete collabClientProcess;
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
 * teamtype share --directory <folder>
 * \param folder directory which is synced
 * \return successful start
 */
bool CollaborationManager::startHostServer(const QString folder)
{
    if(m_startingEthersyncFailed || isServerRunning() || isClientRunning()){
        // already running
        return false;
    }
    // start server
    const QString binPath=m_conf->ce_toolPath;
    if(!binPath.isEmpty()){
        // run binPath share folder
        collabServerProcess = new QProcess(this);
        collabServerProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabServerProcess, &QProcess::readyReadStandardOutput, this, &CollaborationManager::readyCollabServerStandardOutput);
        connect(collabServerProcess, qOverload<int,QProcess::ExitStatus>(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug() << "Collaboration server finished with exit code" << exitCode << "and status" << exitStatus;
            collabServerProcess = nullptr;
        });
        QStringList args{"share","--directory", folder};
        collabServerProcess->start(binPath,args);
        if (!collabServerProcess->waitForStarted(1000)) {
            m_errorMessage=collabServerProcess->readAllStandardError();
            m_startingEthersyncFailed = true;
            collabServerProcess = nullptr;
            return false;
        }
        m_collabServerFolder=folder;
    }
    return false;
}
/*!
 * \brief start guest server
 * teamtype join <code> --directory <folder>
 * \param folder directory which is synced, should be empty and will be filled by the host
 * \param code the code provided by the host
 * \return successful start
 */
bool CollaborationManager::startGuestServer(const QString folder,const QString &code)
{
    if(m_startingEthersyncFailed || isServerRunning() || isClientRunning()){
        // already running
        return false;
    }
    const QString binPath=m_conf->ce_toolPath;
    QString folderName=m_conf->ce_clientPath;

    if(!binPath.isEmpty()){
        // run binPath share folder
        collabServerProcess = new QProcess(this);
        collabServerProcess->setProcessChannelMode(QProcess::MergedChannels);
        connect(collabServerProcess, &QProcess::readyReadStandardOutput, this, &CollaborationManager::readyCollabServerStandardOutput);
        connect(collabServerProcess, qOverload<int,QProcess::ExitStatus>(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus exitStatus){
            qDebug() << "Collaboration client finished with exit code" << exitCode << "and status" << exitStatus;
            collabServerProcess = nullptr;
        });
        const QStringList args{"join", code, "--directory", folderName};
        collabServerProcess->start(binPath,args);
        if (!collabServerProcess->waitForStarted(1000)) {
            m_errorMessage=collabServerProcess->readAllStandardError();
            m_startingEthersyncFailed = true;
            collabServerProcess = nullptr;
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
    if(collabServerProcess){
        collabServerProcess->terminate();
        if(!collabServerProcess->waitForFinished(2000)){
            collabServerProcess->kill();
        }
        delete collabServerProcess;
        collabServerProcess = nullptr;
    }
}
/*!
 * \brief check if server is running
 * \return
 */
bool CollaborationManager::isServerRunning()
{
    return (collabServerProcess!=nullptr);
}
/*!
 * \brief check if file is in a folder with .teamtype subfolder
 * This hints at a running server
 * \param filename
 * \return folder was already used with teamtype
 */
bool CollaborationManager::isFileLocatedInCollabFolder(const QString &filename)
{
    QFileInfo fi(filename);
    if(isClientRunning()){
        // in case of running client, only files in the client folder are relevant
        return fi.absolutePath()==m_collabClientFolder;
    }
    QDir dir=fi.absoluteDir();
    if(dir.exists(".ethersync")||dir.exists(".teamtype")){
        // client is not running, but server might be
        return true;
    }
    return false;
}
/*!
 * \brief reset starting check for teamtype
 * If starting failed once, all further attempts are moot
 * Here this check is reset, e.g. if user changed path in settings
 */
 void CollaborationManager::resetCollabCommand()
{
     m_startingEthersyncFailed = false;
}

/*!
 * \brief read last error message
 * \return error message
 */
QString CollaborationManager::readErrorMessage()
{
    return m_errorMessage;
}
/*!
 * \brief return current collaboration folder which is used by client
 * \return
 */
QString CollaborationManager::collabClientFolder() const
{
    return m_collabClientFolder;
}
/*!
 * \brief return current collaboration folder which is used by server
 * \return
 */
QString CollaborationManager::collabServerFolder() const
{
    return m_collabServerFolder;
}

/*!
 * \brief send updates to client
 * \param cursor
 * \param changes
 */
void CollaborationManager::sendChanges(QDocumentCursor cursor, const QString &changes)
{
    if(!isClientRunning()){
        return;
    }
    QDocumentLineHandle *dlh=cursor.line().handle();
    LatexDocument *doc=dynamic_cast<LatexDocument*>(dlh->document());
    bool ok;
    qint64 rev=doc->property("revision").toLongLong(&ok);
    if(!ok) rev=0;
    sendChanges(doc->getFileName(),cursor.lineNumber(),cursor.columnNumber(),cursor.anchorLineNumber(),cursor.anchorColumnNumber(),changes,rev);
}
/*!
 * \brief variant to send changes to connected editors
 * \param fileName
 * \param startLine
 * \param startCol
 * \param endLine
 * \param endCol
 * \param changes
 */
void CollaborationManager::sendChanges(QString fileName, int startLine, int startCol, int endLine, int endCol, const QString &changes,qint64 rev)
{
    if(!isClientRunning()){
        return;
    }
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="edit";
    QJsonObject jparams;
    jparams["uri"]="file://"+fileName;
    jparams["revision"]=rev; // for now
    QJsonObject jrange;
    QJsonObject jstart;
    jstart["line"]=startLine;
    jstart["character"]=startCol;
    jrange["start"]=jstart;
    QJsonObject jend;
    if(endCol<0 || endLine<0){
        jend=jstart;
    }else{
        jend["line"]=endLine;
        jend["character"]=endCol;
    }
    jrange["end"]=jend;
    QJsonArray jdelta;
    QJsonObject jdeltaelem;
    jdeltaelem["range"]=jrange;
    jdeltaelem["replacement"]=changes;
    jdelta.append(jdeltaelem);
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
    QJsonObject jrange;
    QJsonObject jstart;
    jstart["line"]=cursor.lineNumber();
    jstart["character"]=cursor.columnNumber();
    jrange["start"]=jstart;
    QJsonObject jend;
    jend["line"]=cursor.anchorLineNumber();
    jend["character"]=cursor.anchorColumnNumber();
    jrange["end"]=jend;
    QJsonArray jranges;
    jranges.append(jrange);
    jparams["ranges"]=jranges;
    jparams["uri"]="file://"+doc->getFileName();
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
    QFileInfo fi(fileName);
    if(fi.absolutePath()==m_collabClientFolder){
        // ignore files outside of client managed folder
        openFileInClient(fileName);
    }
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
/*!
 * \brief return the current code for connecting new guest
 * \return
 */
QString CollaborationManager::codeForConnectingGuest() const
{
    return m_code;
}

void CollaborationManager::readyCollabClientStandardOutput()
{
    if(!collabClientProcess){
        return;
    }
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
                        QString userId=ja["userid"].toString("extern");
                        QDocumentCursor c(doc);
                        c.moveTo(ln,col);
                        emit cursorMoved(c,userId);
                    }
                }else{
                    QString userId=ja["userid"].toString("extern");
                    emit cursorRemoved(doc,userId);
                }
            }
            if(method=="edit"){
                QJsonObject ja=dd["params"].toObject();
                QString uri=ja["uri"].toString();
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
                qint64 rev_received=ja["revision"].toInteger();
#else
                qint64 rev_received=ja["revision"].toInt();
#endif
                // find doc from uri
                if(!uri.startsWith("file://")){
                    return;
                }
                QString fileName=uri.mid(7);
                LatexDocument *doc=findDocumentFromName(fileName);
                // update revision number
                // apparently +1 per received changed request
                bool ok;
                qint64 rev=doc->property("revision").toLongLong(&ok);
                if(!ok) rev=0;
                doc->setProperty("revision",rev+1);
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
                        QString userName=ja["name"].toString("extern");
                        QDocumentCursor c(doc);
                        c.moveTo(ln,col);
                        c.moveTo(ln2,col2,QDocumentCursor::KeepAnchor);
                        emit changesReceived(c,replacement,userName);
                    }
                }
            }

        }else{
            if(!line.startsWith("Content-Length:")){
                // check for error
                if(line.startsWith("Error:")){
                    m_errorMessage=line;
                }else{
                    // dump everything else
                    qDebug() << "Collab Client Output:" << line;
                }
            }
        }
    }
}

void CollaborationManager::readyCollabServerStandardOutput()
{
    if(!collabServerProcess){
        return;
    }
    // for now, just dump output to debug
    QString buffer = collabServerProcess->readAllStandardOutput();
    // look for connection message
    if(buffer.contains("Connected to peer:")){
        emit guestServerSuccessfullyStarted();
    }
    if(buffer.contains("\tteamtype join")){
        // extract code
        QStringList lines= buffer.split("\n", Qt::SkipEmptyParts);
        for(QString line : lines){
            line=line.trimmed();
            if(line.startsWith("teamtype join")){
                m_code=line.mid(14);
                emit hostServerSuccessfullyStarted();
            }
        }
    }
    if(buffer.contains("Do you want to continue? (y/N):")){
        // send y
        collabServerProcess->write("y\n");
    }
    if(buffer.contains("Do you want to enable live collaboration here?") && buffer.contains("(y/N):")){
        // send y
        collabServerProcess->write("y\n");
    }
    qDebug() << "Collab Server Output:" << buffer;
}
/*!
 * \brief handle client process finished
 * \param exitCode
 * \param exitStatus
 */
void CollaborationManager::clientFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Collaboration client finished with exit code" << exitCode << "and status" << exitStatus;
    qDebug() << m_errorMessage;
    collabClientProcess = nullptr;
    emit collabClientFinished(exitCode,m_errorMessage);
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
    LatexDocument *doc=findDocumentFromName(fileName);
    if(!doc) return; // document not open
    // reset revision
    doc->setProperty("revision",0);
    // open file, send json
    QJsonObject jo;
    jo["jsonrpc"]="2.0";
    jo["method"]="open";
    QJsonObject jparams;
    jparams["uri"]="file://"+fileName;
    jparams["content"]=doc->text();
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
LatexDocument *CollaborationManager::findDocumentFromName(const QString &fileName) const
{
    if(m_docs==nullptr){
       return nullptr;
    }
    return m_docs->findDocumentFromName(fileName);
}

/* TODO
 * - extra cursor with different color -> refine?
 * - store connection info in folder to allow autoconnect for different user on same folder (shared folder NFS or cloud)
 */
