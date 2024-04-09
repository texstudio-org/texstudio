#include "aichatassistant.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QJsonDocument>
#include <QJsonArray>

AIChatAssistant::AIChatAssistant(QWidget *parent)
    : QDialog{parent}
{
    treeWidget=new QTreeWidget();
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel(tr("Date"));
    topItem=new QTreeWidgetItem(treeWidget);
    topItem->setText(0,tr("Today"));
    textBrowser=new QTextBrowser();
    auto *hlBrowser=new QSplitter();
    hlBrowser->addWidget(treeWidget);
    hlBrowser->addWidget(textBrowser);

    leEntry=new QTextEdit();
    btSend=new QPushButton(tr("Send"));
    connect(btSend,&QPushButton::clicked,this,&AIChatAssistant::slotSend);
    btInsert=new QPushButton(tr("Insert"));
    connect(btInsert,&QPushButton::clicked,this,&AIChatAssistant::slotInsert);
    btOptions=new QPushButton(tr("Options"));
    connect(btOptions,&QPushButton::clicked,this,&AIChatAssistant::slotOptions);
    auto *hlayout=new QHBoxLayout();
    hlayout->addWidget(leEntry);
    auto *vl=new QVBoxLayout();
    vl->addWidget(btSend,0,Qt::AlignTop);
    vl->addWidget(btInsert,0,Qt::AlignTop);
    auto *vspacer=new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Expanding);
    vl->addSpacerItem(vspacer);
    vl->addWidget(btOptions,0,Qt::AlignBottom);
    hlayout->addLayout(vl);
    auto *wdgt=new QWidget();
    wdgt->setLayout(hlayout);

    auto *splt=new QSplitter();
    splt->setOrientation(Qt::Vertical);
    splt->addWidget(hlBrowser);
    splt->addWidget(wdgt);

    auto *ly=new QVBoxLayout();
    ly->addWidget(splt);
    setLayout(ly);
    setWindowTitle(tr("AI chat assistant"));
    config=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    networkManager = new QNetworkAccessManager();
}

AIChatAssistant::~AIChatAssistant()
{
    if (networkManager) {
        networkManager->deleteLater();
        networkManager=nullptr;
    }
}
/*!
 * \brief set selected text
 * To be used as "text" in AI questions
 * \param text
 */
void AIChatAssistant::setSelectedText(QString text)
{
    m_selectedText=text;
}
/*!
 * \brief start a new conversation
 */
void AIChatAssistant::clearConversation()
{
    ja_messages=QJsonArray();
    m_conversationFileName=config->configBaseDir+"/ai_conversation/"+QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+"_conversation.json";
}
/*!
 * \brief send question to ai provider
 */
void AIChatAssistant::slotSend()
{
    if(m_reply){
        // if reply is active, stop it
        m_reply->abort();
        m_reply->deleteLater();
        m_reply=nullptr;
        btSend->setText(tr("Send"));
        // remove last message from conversation
        ja_messages.removeLast();
        return;
    }
    QString question=leEntry->toPlainText();
    if(question.isEmpty()){
        return;
    }
    if(!networkManager){
        networkManager = new QNetworkAccessManager();
        if(!networkManager) return;
    }
    // clear previous response
    m_response.clear();
    textBrowser->clear(); // for now, show contain history
    // add question to treeWidget
    QTreeWidgetItem *item=new QTreeWidgetItem(topItem);
    item->setText(0,question);

    QString url;
    switch(config->ai_provider){
        case 0: url="https://api.mistral.ai/v1/chat/completions";
        break;
        case 1: url="https://api.openai.com/v1/chat/completions";
        break;
        default:
            url="https://api.mistral.ai/v1/chat/completions";
    }

    QJsonObject dd;
    dd["model"]=config->ai_preferredModel;
    //dd["stream"] = "True";
    if(!config->ai_systemPrompt.isEmpty()){
        // add system prompt to query
        QJsonObject ja_message;
        ja_message["role"]="system";
        ja_message["content"]=config->ai_systemPrompt;
    }
    QJsonObject ja_message;
    ja_message["role"]="user";
    // prepend selected text to question
    if(!m_selectedText.isEmpty()){
        question="text=\"\"\""+m_selectedText+"\"\"\"\n"+question;
    }
    ja_message["content"]=question;

    // for now single questions only
    //ja_messages=QJsonArray();
    ja_messages.append(ja_message);

    dd["messages"]=ja_messages;

    QJsonDocument jsonDoc(dd);
    QString data=jsonDoc.toJson();

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "TeXstudio Chat Assistant");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(config->ai_apikey).toUtf8());
    m_reply = networkManager->post(request,data.toUtf8());
    connect(networkManager, &QNetworkAccessManager::finished, this, &AIChatAssistant::onRequestCompleted);
#if QT_VERSION_MAJOR<6
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError(QNetworkReply::NetworkError)));
#else
    connect(m_reply, &QNetworkReply::errorOccurred, this, &AIChatAssistant::onRequestError);
#endif
    // use btSend as stop button
    btSend->setText(tr("Stop"));
}
/*!
 * \brief insert response
 * Cut response to meanigful part and insert it to the editor
 */
void AIChatAssistant::slotInsert()
{
    if(m_response.isEmpty()) return;
    if(m_response.contains("```")){
        QStringList parts=m_response.split("```");
        if(parts.size()>1){
            parts=parts[1].split("\n");
            if(parts.size()>1 && parts[0]=="latex"){
                // insert latex code
                // only insert part after begin/end document as AI tends to give complete example documents
                parts.removeFirst();
                int start=parts.indexOf("\\begin{document}");
                int end=parts.indexOf("\\end{document}");
                if(start>=0 && end>=0){
                    // look for usepackage
                    auto usepackage=parts.filter("\\usepackage");
                    qDebug()<<"Usepackage:"<<usepackage; // insert usepackage
                    parts=parts.mid(start+1,end-start-1);
                    // remove empty lines at beginning and end
                    while(parts.size()>0 && parts.first().isEmpty()){
                        parts.removeFirst();
                    }
                    while(parts.size()>0 && parts.last().isEmpty()){
                        parts.removeLast();
                    }
                }
                QString text=parts.join("\n");
                emit insertText(text);
                return;
            }
            if(parts.size()>1 && parts[0]=="javascript"){
                parts.removeFirst();
                QString script=parts.join("\n");
                emit executeMacro(script);
                return;
            }
            if(parts.size()>1 && parts[0]=="bash"){
                parts.removeFirst();
                // filter out all lines starting with %, e.g. %SCRIPT
                for(int i=0;i<parts.size();++i){
                    if(parts[i].startsWith("%")){
                        parts.removeAt(i);
                        --i;
                    }
                }
                QString script=parts.join("\n");
                emit executeMacro(script);
            }
        }
    }else{
        // insert whole text
        emit insertText(m_response);
    }
}
/*!
 * \brief show a dialog
 * Ask for textedit with systemprompt
 * Slider with temperature
 */
void AIChatAssistant::slotOptions()
{
    QDialog dlg;
    auto *ly=new QVBoxLayout();
    auto *leSystemPrompt=new QTextEdit();
    leSystemPrompt->setText(config->ai_systemPrompt);
    ly->addWidget(leSystemPrompt);
    auto *leTemp=new QLineEdit();
    leTemp->setText(config->ai_temperature);
    // add label in front of slider
    auto *lblTemp=new QLabel(tr("Temperature"));
    auto *hl=new QHBoxLayout();
    hl->addWidget(lblTemp);
    hl->addWidget(leTemp);
    ly->addLayout(hl);
    auto *btOk=new QPushButton(tr("OK"));
    connect(btOk,&QPushButton::clicked,[&](){
        config->ai_systemPrompt=leSystemPrompt->toPlainText();
        config->ai_temperature=leTemp->text();
        dlg.close();
    });
    ly->addWidget(btOk);
    dlg.setLayout(ly);
    dlg.exec();
}
/*!
 * \brief handle communication error with ai provider
 */
void AIChatAssistant::onRequestError(QNetworkReply::NetworkError code)
{
    qDebug()<<"Error:"<<code;
    qDebug()<<m_reply->errorString();
    btSend->setText(tr("Send"));
    m_reply->deleteLater();
    m_reply=nullptr;
}
/*!
 * \brief handle received data from AI provider
 */
void AIChatAssistant::onRequestCompleted(QNetworkReply *nreply)
{
    if (!nreply || nreply->error() != QNetworkReply::NoError) return;
    QByteArray data=nreply->readAll();
    QString allData(data);
    if(allData.startsWith("data: ")){
        QStringList msgs=allData.split("data: ");
        qDebug()<<msgs;
    }else{
        QJsonDocument doc=QJsonDocument::fromJson(data);
        QJsonObject obj=doc.object();
        QJsonArray arr=obj["choices"].toArray();
        if(arr.size()>0){
            QJsonObject ja_choice=arr[0].toObject();
            QJsonObject ja_message=ja_choice["message"].toObject();
            ja_messages.append(ja_message); // update conversation
            m_response=ja_message["content"].toString();
#if QT_VERSION>=QT_VERSION_CHECK(5,14,0)
            textBrowser->setMarkdown(m_response);
#else
            textBrowser->setText(m_response); // no markdown interpretation, just keep old qt version running
#endif
            // check if macro, then execute instead of insert
            if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
                btInsert->setText(tr("Execute"));
            }else{
                btInsert->setText(tr("Insert"));
            }
        }
    }
    nreply->deleteLater();
    m_reply=nullptr;
    btSend->setText(tr("Send"));
    // update record of conversation
    if(config->ai_recordConversation){
        QString conv=makeJsonDoc();
        writeToFile(m_conversationFileName,conv);
    }
}
/*!
 * \brief write content to file
 * \param filename
 * \param content
 */
void AIChatAssistant::writeToFile(QString filename, QString content)
{
    QFileInfo fi(filename);
    QDir dir=fi.dir();
    if(!dir.exists()){
        dir.mkpath(fi.absolutePath());
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << content;
        file.close();
    }
}
/*!
 * \brief construct json document
 * \return
 */
QString AIChatAssistant::makeJsonDoc() const
{
    QJsonObject dd;
    dd["model"]=config->ai_preferredModel;
    if(!config->ai_systemPrompt.isEmpty()){
        // add system prompt to query
        QJsonObject ja_message;
        ja_message["role"]="system";
        ja_message["content"]=config->ai_systemPrompt;
    }
    //ja_messages is updated externally
    dd["messages"]=ja_messages;

    QJsonDocument jsonDoc(dd);
    QString data=jsonDoc.toJson();
    return data;
}

/*! TODO
 *  - insert packages
 *  - detect new document/insert all
 *  - add to macros
 *  - history with Q/A , nicer
 *  - persistant storage of questions/conversations
 *  - search in questions/answers
 *  - icons/QToolbuttons for actions
 */
