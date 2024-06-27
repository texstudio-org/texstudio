#include "aichatassistant.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QJsonDocument>
#include <QJsonArray>
#include "aiquerystoragemodel.h"

AIChatAssistant::AIChatAssistant(QWidget *parent)
    : QDialog{parent}
{
    config=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());

    m_btSearch=new QToolButton();
    m_actSearch=new QAction();
    m_actSearch->setIcon(getRealIcon("edit-find"));
    m_actSearch->setToolTip(tr("Search in previous conversations"));
    connect(m_actSearch,&QAction::triggered,this,&AIChatAssistant::slotSearch);
    m_btSearch->setDefaultAction(m_actSearch);
    m_leSearch=new QLineEdit();
    m_leSearch->setPlaceholderText(tr("Search in conversations"));
    auto *hlayoutSearch=new QHBoxLayout();
    hlayoutSearch->addWidget(m_leSearch);
    hlayoutSearch->addWidget(m_btSearch);

    AIQueryStorageModel *model=new AIQueryStorageModel(this);
    QString path=config->configBaseDir+QString("/ai_conversation");
    model->setStoragePath(path);
    treeView=new QTreeView();
    treeView->setModel(model);
    connect(treeView, &QTreeView::clicked, this, &AIChatAssistant::onTreeViewClicked);

    auto *vtreeLayout=new QVBoxLayout();
    vtreeLayout->addLayout(hlayoutSearch);
    vtreeLayout->addWidget(treeView);
    QWidget *wdgtTree=new QWidget();
    wdgtTree->setLayout(vtreeLayout);

    textBrowser=new QTextBrowser();
    auto *hlBrowser=new QSplitter();
    hlBrowser->addWidget(wdgtTree);
    hlBrowser->addWidget(textBrowser);

    leEntry=new QTextEdit();
    leEntry->setPlaceholderText(tr("Enter your query here"));
    m_actSend=new QAction();
    m_actSend->setIcon(getRealIcon("document-send"));
    m_actSend->setToolTip(tr("Send Query to AI provider"));
    connect(m_actSend,&QAction::triggered,this,&AIChatAssistant::slotSend);
    m_btSend=new QToolButton();
    m_btSend->setDefaultAction(m_actSend);

    m_actInsert=new QAction();
    m_actInsert->setIcon(getRealIcon("download"));
    m_actInsert->setToolTip(tr("Insert response"));
    connect(m_actInsert,&QAction::triggered,this,&AIChatAssistant::slotInsert);
    m_btInsert=new QToolButton();
    m_btInsert->setDefaultAction(m_actInsert);
    m_actOptions=new QAction();
    m_actOptions->setIcon(getRealIcon("configure"));
    m_actOptions->setToolTip(tr("Options"));
    connect(m_actOptions,&QAction::triggered,this,&AIChatAssistant::slotOptions);
    m_btOptions=new QToolButton();
    m_btOptions->setDefaultAction(m_actOptions);



    auto *hlayout=new QHBoxLayout();
    hlayout->addWidget(leEntry);
    auto *vl=new QVBoxLayout();
    vl->addWidget(m_btSend,0,Qt::AlignTop);
    vl->addWidget(m_btInsert,0,Qt::AlignTop);
    auto *vspacer=new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Expanding);
    vl->addSpacerItem(vspacer);
    vl->addWidget(m_btOptions,0,Qt::AlignBottom);
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
    leEntry->setFocus();

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
    const QString fileName=QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+"_conversation.json";
    m_conversationFileName=config->configBaseDir+"/ai_conversation/"+fileName;
    // clear textbrowser
    textBrowser->clear();
    // clear textedit
    leEntry->clear();
    // append new filename to list of conversations
    AIQueryStorageModel *model=dynamic_cast<AIQueryStorageModel *>(treeView->model());
    model->addFileName(fileName);
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
        m_actSend->setToolTip(tr("Send Query to AI provider"));
        m_actSend->setIcon(getRealIcon("document-send"));
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
    // TODO !

    QString url;
    switch(config->ai_provider){
        case 0: url="https://api.mistral.ai/v1/chat/completions";
            break;
        case 1: url="https://api.openai.com/v1/chat/completions";
            break;
        case 2: url="http://localhost:8080/v1/chat/completions";
            break;
        default:
            url="https://api.mistral.ai/v1/chat/completions";
    }

    QJsonObject dd;
    dd["model"]=config->ai_preferredModel;
    if(config->ai_provider==0){
        // work-around for llamafile for now
        dd["temperature"]=config->ai_temperature;
    }
    if(config->ai_provider==1){
        // work-around for openai
        bool ok;
        float val=config->ai_temperature.toFloat(&ok);
        if(ok){
            dd["temperature"]=val;
        }
    }
    if(config->ai_streamResults){
        dd["stream"] = "True";
        m_timer=new QTimer();
        m_timer->setInterval(100);
        connect(m_timer,&QTimer::timeout,this,&AIChatAssistant::slotUpdateResults);
    }
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
    m_actSend->setToolTip(tr("Stop current query !"));
    m_actSend->setIcon(getRealIcon("stop"));
    if(m_timer){
        m_timer->start();
    }
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
    if(config->ai_systemPrompt.isEmpty()){
        leSystemPrompt->setPlaceholderText(tr("System prompt"));
    }
    ly->addWidget(leSystemPrompt);
    auto *leTemp=new QLineEdit();
    leTemp->setText(config->ai_temperature);
    // use validator which allow 0.0 to 1.0/2.0
    float maxTemp=1.0;
    QRegularExpression rx("0\\.[0-9]*|1");
    if(config->ai_provider==1){
        maxTemp=2.0;
        rx.setPattern("[01]\\.[0-9]*|2");
    }
    auto *validator=new QRegularExpressionValidator(rx);
    leTemp->setValidator(validator);
    leTemp->setToolTip(tr("Values between 0 and %1").arg(maxTemp));
    // add label in front of slider
    auto *lblTemp=new QLabel(tr("Temperature"));
    auto *hl=new QHBoxLayout();
    hl->addWidget(lblTemp);
    hl->addWidget(leTemp);
    ly->addLayout(hl);
    auto *cbStream=new QCheckBox(tr("Stream results"));
    cbStream->setChecked(config->ai_streamResults);
    ly->addWidget(cbStream);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted,[&](){
        config->ai_systemPrompt=leSystemPrompt->toPlainText();
        config->ai_temperature=leTemp->text();
        config->ai_streamResults=cbStream->isChecked();
        dlg.close();
    });
    connect(buttonBox, &QDialogButtonBox::rejected, [&](){
        dlg.close();
    });
    ly->addWidget(buttonBox);
    dlg.setLayout(ly);
    dlg.exec();
}
/*!
 * \brief filter old conversations
 */
void AIChatAssistant::slotSearch()
{
    QString text=m_leSearch->text();
    AIQueryStorageModel *model=dynamic_cast<AIQueryStorageModel *>(treeView->model());
    model->setFilter(text);
}
/*!
 * \brief read stream results from ai provider
 */
 void AIChatAssistant::slotUpdateResults()
{
     if (!m_reply || m_reply->error() != QNetworkReply::NoError) return;
     QByteArray data=m_reply->readAll();
     QString allData(data);
     if(allData.startsWith("data: ")){
         updateStreamedConversation(allData);
     }
}
/*!
 * \brief handle communication error with ai provider
 */
void AIChatAssistant::onRequestError(QNetworkReply::NetworkError code)
{
    qDebug()<<"Error:"<<code;
    qDebug()<<m_reply->errorString();
    // present error in textBrowser
    textBrowser->setHtml("<p style=\"background-color: red\">Error: "+m_reply->errorString()+"</p>");

    m_actSend->setToolTip(tr("Send Query to AI provider"));
    m_actSend->setIcon(getRealIcon("document-send"));
    m_reply->deleteLater();
    m_reply=nullptr;
    if(m_timer){
        m_timer->stop();
        delete m_timer;
        m_timer=nullptr;
    }
}
/*!
 * \brief handle received data from AI provider
 */
void AIChatAssistant::onRequestCompleted(QNetworkReply *nreply)
{
    if(m_timer){
        m_timer->stop();
        delete m_timer;
        m_timer=nullptr;
    }
    if (!nreply || nreply->error() != QNetworkReply::NoError) return;
    QByteArray data=nreply->readAll();
    QString allData(data);
    if(allData.startsWith("data: ")){
        updateStreamedConversation(allData);
    }else{
        QJsonDocument doc=QJsonDocument::fromJson(data);
        QJsonObject obj=doc.object();
        QJsonArray arr=obj["choices"].toArray();
        if(arr.size()>0){
            QJsonObject ja_choice=arr[0].toObject();
            QJsonObject ja_message=ja_choice["message"].toObject();
            ja_messages.append(ja_message); // update conversation
            m_response=ja_message["content"].toString();
            QString responseText=getConversationForBrowser();
            textBrowser->setHtml(responseText);
            // check if macro, then execute instead of insert
            if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
                m_actInsert->setToolTip(tr("Execute as macro"));
            }else{
                m_actInsert->setToolTip(tr("Insert into text"));
            }
        }
    }
    nreply->deleteLater();
    m_reply=nullptr;
    m_actSend->setToolTip(tr("Send Query to AI provider"));
    m_actSend->setIcon(getRealIcon("document-send"));
    // update record of conversation
    if(config->ai_recordConversation){
        QString conv=makeJsonDoc();
        writeToFile(m_conversationFileName,conv);
    }
}
/*!
 * \brief show query and results of recorded conversation
 * \param index
 */
void AIChatAssistant::onTreeViewClicked(const QModelIndex &index)
{
    AIQueryStorageModel *model=dynamic_cast<AIQueryStorageModel *>(treeView->model());
    QString filename=model->getFileName(index);
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        QJsonObject obj=doc.object();
        ja_messages=obj["messages"].toArray();
        QString responseText=getConversationForBrowser();
        textBrowser->setHtml(responseText);
        // prepare last response
        QJsonObject ja_message=ja_messages.last().toObject();
        m_response=ja_message["content"].toString();
        // check if macro, then execute instead of insert
        if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
            m_actInsert->setToolTip(tr("Execute as macro"));
        }else{
            m_actInsert->setToolTip(tr("Insert into text"));
        }
    }else{
        // no query sent yet
        textBrowser->clear();
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
/*!
 * \brief convert conversation in ja_messages to markdown string for presentation in QTextBrowser
 * \return
 */
QString AIChatAssistant::getConversationForBrowser()
{
    QString result;
    for(auto it=ja_messages.begin();it!=ja_messages.end();++it){
        QJsonObject obj=it->toObject();
        QString role=obj["role"].toString();
#if QT_VERSION>=QT_VERSION_CHECK(5,14,0)
        const QString content=QString("%%%txs%%%")+(obj["content"].toString())+QString("%%%txs%%%");
        QTextDocument td;
        td.setMarkdown(content);
        const QString contentHTML=td.toHtml();
        // strip html from surrounding default tags
        const auto parts=contentHTML.split("%%%txs%%%");
        const QString cnt=parts.value(1);
#else
        const QString cnt=obj["content"].toString();
#endif
        if(role=="user"){
            if(darkMode){
                result.append("<p style=\"background-color: darkorange\">\n");
            }else{
                result.append("<p style=\"background-color: bisque\">\n");
            }
            result.append(cnt);
            result.append("\n</p>\n");
        }else if(role=="assistant"){
            if(darkMode){
                result.append("<p style=\"background-color: cornflowerblue;margin-left: 20px\">\n");
            }else{
                result.append("<p style=\"background-color: aliceblue;margin-left: 20px\">\n");
            }
            result.append(cnt);
            result.append("\n</p>\n");
        }
    }
    return result;
}
/*!
 * \brief read streamed conversation and update textBrowser
 * \param allData
 */
void AIChatAssistant::updateStreamedConversation(const QString &allData)
{
    QStringList msgs=allData.split("data: ");
    for(const QString &elem:msgs){
        QJsonDocument doc=QJsonDocument::fromJson(elem.toUtf8());
        QJsonObject obj=doc.object();
        QJsonArray arr=obj["choices"].toArray();
        if(arr.size()>0){
            QJsonObject ja_choice=arr[0].toObject();
            QJsonObject jo_delta=ja_choice["delta"].toObject();
            QString delta_text=jo_delta["content"].toString();
            m_response+=delta_text;
        }
    }
    // check if last message is a question
    // add a new message to conversation
    QJsonObject ja_message=ja_messages.last().toObject();
    if(ja_message["role"]=="user"){
        ja_message=QJsonObject();
    }else{
        ja_messages.removeLast();
    }
    ja_message["role"]="assistant";
    ja_message["content"]=m_response;
    ja_messages.append(ja_message);
    QString responseText=getConversationForBrowser();
    textBrowser->setHtml(responseText);
}

/*! TODO
 *  - insert packages
 *  - detect new document/insert all
 *  - add to macros
 *  - modeltree for conversations
 *   + show summary of conversation in titles ?
 *  - overlay buttons insert/etc.
 */
