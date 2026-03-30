#include "aichatassistant.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QJsonDocument>
#include <QJsonArray>
#include "aiquerystoragemodel.h"
#include <QShortcut>
#include "texstudio.h"

extern Texstudio *txsInstance;

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
    QString path=config->configBaseDir;
    if(!path.endsWith(QDir::separator())) path+=QDir::separator();
    path+=QString("ai_conversation");
    model->setStoragePath(path);
    treeView=new QTreeView();
    treeView->setModel(model);
    connect(treeView, &QTreeView::clicked, this, &AIChatAssistant::onTreeViewClicked);

    auto *vtreeLayout=new QVBoxLayout();
    vtreeLayout->addLayout(hlayoutSearch);
    vtreeLayout->addWidget(treeView);
    QWidget *wdgtTree=new QWidget();
    wdgtTree->setLayout(vtreeLayout);

    chatView = new QListView(this);
    chatmodel = new QStandardItemModel(this);

    ChatDelegate *delegate = new ChatDelegate();
    connect(delegate,&ChatDelegate::insertTextClicked,this,&AIChatAssistant::insertTextClicked);
    chatView->setItemDelegate(delegate);
    chatView->setModel(chatmodel);
    chatView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    chatView->setSelectionMode(QAbstractItemView::NoSelection);
    chatView->setSpacing(2);
    chatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    chatView->setContextMenuPolicy(Qt::CustomContextMenu);
    QShortcut *shortcutInsert = new QShortcut(QKeySequence::Copy, chatView);
    connect(shortcutInsert,&QShortcut::activated,this,&AIChatAssistant::slotCopyText);
    connect(chatView,&QListView::customContextMenuRequested,this,&AIChatAssistant::slotShowContextMenu);

    hlBrowser=new QSplitter();
    hlBrowser->addWidget(wdgtTree);
    hlBrowser->addWidget(chatView);

    // Set the stretch factors (30:70 ratio)
    int ratio=qRound(config->ai_splitter*100);
    hlBrowser->setStretchFactor(0, ratio);  // 30% for wdgtTree
    hlBrowser->setStretchFactor(1, 100-ratio);  // 70% for chatView

    leEntry=new QTextEdit();
    leEntry->setPlaceholderText(tr("Enter your query here"));
    QAction *actAccept=new QAction(leEntry);
    connect(actAccept, &QAction::triggered,this,&AIChatAssistant::slotSend);
    actAccept->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
    leEntry->addAction(actAccept);
    m_actSend=new QAction();
    m_actSend->setIcon(getRealIcon("document-send"));
    m_actSend->setToolTip(tr("Send Query to AI provider (ctrl+enter)"));
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

    resize(config->ai_width,config->ai_height);

    networkManager = new QNetworkAccessManager();

    // register AI tool functions
    registerToolFunctions();
}

AIChatAssistant::~AIChatAssistant()
{
    config->ai_width=width();
    config->ai_height=height();
    QList<int> sizes=hlBrowser->sizes();
    config->ai_splitter=sizes[0]/(double)(sizes[0]+sizes[1]);
    if (networkManager) {
        networkManager->deleteLater();
        networkManager=nullptr;
    }
}
/*!
 * \brief preset query text
 * This comes typically from a macro
 * \param text
 */
void AIChatAssistant::setQueryText(const QString &text)
{
    leEntry->setText(text);
}
/*!
 * \brief start a new conversation
 */
void AIChatAssistant::clearConversation()
{
    ja_messages=QJsonArray();
    const QString fileName=QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+"_conversation.json";
    m_conversationFileName=config->configBaseDir+"/ai_conversation/"+fileName;
    // clear result widget
    chatmodel->clear();
    // clear textedit
    leEntry->clear();
    // append new filename to list of conversations
    AIQueryStorageModel *model=dynamic_cast<AIQueryStorageModel *>(treeView->model());
    model->addFileName(fileName);
}
/*!
 * \brief execute query from outer level
 * This is used when macros are involved
 */
void AIChatAssistant::executeQuery()
{
    slotSend();
}
/*!
 * \brief send question to ai provider
 */
void AIChatAssistant::slotSend(bool fromToolCall)
{
    if(config->ai_provider==0){
        //disabled
        // TODO
        qDebug()<<"AI provider disabled. Please activate in options.";
        return;
    }
    if(m_reply){
        // if reply is active, stop it
        m_reply->abort();
        if(m_reply)
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
    chatmodel->clear(); // for now, show contain history
    // add question to treeWidget
    // TODO !

    QString url;
    switch(config->ai_provider){
        case 1: url="https://api.mistral.ai/v1/chat/completions";
            break;
        case 2: url="https://api.openai.com/v1/chat/completions";
            break;
        case 3: url=config->ai_apiurl;
            break;
        case 4: url="https://api.anthropic.com/v1/messages";
            break;
        case 5: url="https://openrouter.ai/api/v1/chat/completions";
            break;
        default:
            url="https://api.mistral.ai/v1/chat/completions";
    }

    QJsonObject dd;
    dd["model"]=config->ai_preferredModel;
    if(config->ai_provider==1){
        // check if temperature is valid
        bool ok;
        float t=config->ai_temperature.toFloat(&ok);
        if(ok && t>0 && t<=2){
            dd["temperature"]=config->ai_temperature;
        }
    }
    if(config->ai_provider==2){
        // work-around for openai
        bool ok;
        float val=config->ai_temperature.toFloat(&ok);
        if(ok && val>=0 && val<=2){
            dd["temperature"]=val;
        }
    }
    if(config->ai_streamResults){
        dd["stream"] = true;
        m_timer=new QTimer();
        m_timer->setInterval(100);
        connect(m_timer,&QTimer::timeout,this,&AIChatAssistant::slotUpdateResults);
    }
    if(config->ai_useFunctions){
        // advertise available tool calls
        QJsonArray ja_functions=makeFunctionsJsonArray();
        dd["tools"]=ja_functions;
    }
    if(ja_messages.isEmpty() and !config->ai_systemPrompt.isEmpty()){
        // add system prompt to query
        if(url.endsWith("/v1/messages")){
            // anthropic compatible API
            QString msg=config->ai_systemPrompt;
            msg.replace("%txsSelectedText%",tfGetSelection());
            dd["system"]=msg;
        }else{
            // openai compatible API, system prompt only as first message
            QJsonObject ja_message;
            ja_message["role"]="system";
            QString msg=config->ai_systemPrompt;
            msg.replace("%txsSelectedText%",tfGetSelection());
            ja_message["content"]=msg;
            ja_messages.append(ja_message);
        }

    }
    if(!fromToolCall){
        // add message from user to conversation
        // skip when called from tool call
        QJsonObject ja_message;
        ja_message["role"]="user";
        // prepend selected text to question
        ja_message["content"]=question;

        // for now single questions only
        //ja_messages=QJsonArray();
        ja_messages.append(ja_message);
    }

    dd["messages"]=ja_messages;

    QJsonDocument jsonDoc(dd);
    QString data=jsonDoc.toJson();
    if(url.endsWith("/v1/messages")){
        // anthropic compatible API
        dd["max_tokens"]=config->ai_maxTokens;

        QNetworkRequest request = QNetworkRequest(QUrl(url));
        request.setRawHeader("User-Agent", "TeXstudio Chat Assistant");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept", "application/json");
        request.setRawHeader("anthropic-version", "2023-06-01");
        request.setRawHeader("x-api-key", QString("%1").arg(config->ai_apikey).toUtf8());
        m_reply = networkManager->post(request,data.toUtf8());
    }else{
        // openAI compatible API
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        request.setRawHeader("User-Agent", "TeXstudio Chat Assistant");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept", "application/json");
        request.setRawHeader("Authorization", QString("Bearer %1").arg(config->ai_apikey).toUtf8());
        m_reply = networkManager->post(request,data.toUtf8());
    }
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
    insertTextAtCursor(m_response);
}

void AIChatAssistant::slotCopyText()
{
    // find index with selection
    QModelIndex index;
    for(int row=0;row<chatmodel->rowCount();++row){
        QModelIndex idx=chatmodel->index(row,0);
        if(idx.data(Qt::UserRole+1).toInt()>-1 && idx.data(Qt::UserRole+2).toInt()>-1){
            index=idx;
            break;
        }
    }
    if(index.isValid()){
        const QString text=index.data(Qt::DisplayRole).toString();
        int pos1=index.data(Qt::UserRole+1).toInt();
        int pos2=index.data(Qt::UserRole+2).toInt();
        if(pos1>-1 && pos2>0){
            QTextDocument doc;
            doc.setMarkdown(text);
            QTextCursor cursor(&doc);
            cursor.setPosition(pos1);
            cursor.setPosition(pos2,QTextCursor::KeepAnchor);
            QApplication::clipboard()->setText(cursor.selectedText());
        }
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
    if(!ja_messages.isEmpty()){
        leSystemPrompt->setEnabled(false);
        if(ja_messages.first()["role"]=="system")
            leSystemPrompt->setText(ja_messages.first()["content"].toString());
        leSystemPrompt->setToolTip(tr("System prompt can't be altered mid-conversation"));
    }else{
        leSystemPrompt->setText(config->ai_systemPrompt);
        if(config->ai_systemPrompt.isEmpty()){
            leSystemPrompt->setPlaceholderText(tr("System prompt"));
        }
    }
    ly->addWidget(leSystemPrompt);
    auto *leTemp=new QLineEdit();
    leTemp->setText(config->ai_temperature);
    // use validator which allow 0.0 to 1.0/2.0
    float maxTemp=1.0;
    QRegularExpression rx("0\\.[0-9]*|1");
    if(config->ai_provider==2){
        maxTemp=2.0;
        rx.setPattern("[01]\\.[0-9]*|2");
    }
    if(config->ai_provider==3){
        leTemp->setEnabled(false);
        leTemp->setText(tr("-"));
        leTemp->setToolTip(tr("Temperature not supported for local models"));
    }else{
        auto *validator=new QRegularExpressionValidator(rx);
        leTemp->setValidator(validator);
        leTemp->setToolTip(tr("Values between 0 and %1").arg(maxTemp));
    }
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
        if(ja_messages.isEmpty())
            config->ai_systemPrompt=leSystemPrompt->toPlainText();
        if(config->ai_provider!=3)
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
    if(m_reply){
        qDebug()<<m_reply->errorString();

        // present error in textBrowser
        addMessage(QString("Error: "+m_reply->errorString()),Sender::Error);

        m_actSend->setToolTip(tr("Send Query to AI provider"));
        m_actSend->setIcon(getRealIcon("document-send"));
        m_reply->deleteLater();
    }
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
    if(allData.isEmpty()) return; // work-around, seems to happen with mistral during multiple tool calls
    if(allData.startsWith("data: ")){
        updateStreamedConversation(allData);
    }else{
        QJsonDocument doc=QJsonDocument::fromJson(data);
        QJsonObject obj=doc.object();
        QJsonArray arr=obj["choices"].toArray();
        if(arr.size()>0){
            QJsonObject ja_choice=arr[0].toObject();
            if(ja_choice["finish_reason"].toString().startsWith("tool") && config->ai_useFunctions){
                // tool call, handle instead of inserting
                // completely ignored when disabled
                nreply->deleteLater();
                m_reply=nullptr;
                handleToolCall(ja_choice["message"].toObject());
                return;
            }else{
                QJsonObject ja_message=ja_choice["message"].toObject();
                ja_messages.append(ja_message); // update conversation
                m_response=ja_message["content"].toString();
                updateConversationForChatview();
                // check if macro, then execute instead of insert
                if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
                    m_actInsert->setToolTip(tr("Execute as macro"));
                }else{
                    m_actInsert->setToolTip(tr("Insert into text"));
                }
            }
        }else{
            // try anthropic api format
            if(obj.contains("type")&&obj["type"].toString()=="message"){
                QJsonArray arr=obj["content"].toArray();
                QJsonObject ja_message=arr[0].toObject();
                ja_message.remove("type"); // get to same format as openai
                ja_message["role"]=QString("assistant");
                QJsonValue content=ja_message.take("text");
                ja_message["content"]=content;
                ja_messages.append(ja_message); // update conversation
                m_response=content.toString();
                updateConversationForChatview();
                // check if macro, then execute instead of insert
                if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
                    m_actInsert->setToolTip(tr("Execute as macro"));
                }else{
                    m_actInsert->setToolTip(tr("Insert into text"));
                }
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
        updateConversationForChatview();
        // prepare last response
        QJsonObject ja_message=ja_messages.last().toObject();
        m_response=ja_message["content"].toString();
        // check if macro, then execute instead of insert
        if(m_response.contains("```javascript")||m_response.contains("```bash")){ // mistral ai sometimes declares txs macros as bash
            m_actInsert->setToolTip(tr("Execute as macro"));
        }else{
            if(m_response.contains("```latex")){
                m_actInsert->setToolTip(tr("Insert code into text"));
            }else{
                m_actInsert->setToolTip(tr("Insert into text"));
            }
        }
    }else{
        // no query sent yet
        ja_messages=QJsonArray();
        chatmodel->clear();
    }
}
/*! \brief insert text from response to editor
 * This is used when clicking the "Insert" button in the chat view
 * \param index
 */
void AIChatAssistant::insertTextClicked(const QModelIndex &index)
{
    QString text=index.data(Qt::DisplayRole).toString();
    insertTextAtCursor(text);
}
/*!
 * \brief show context menu in chat view, e.g. for copying parts of the response
 * \param pos
 */
void AIChatAssistant::slotShowContextMenu(const QPoint &pos)
{
    QModelIndex index=chatView->indexAt(pos);
    if(index.isValid()){
        QMenu menu;
        QAction *actCopy=new QAction(tr("&Copy"),&menu);
        connect(actCopy,&QAction::triggered,this,&AIChatAssistant::slotCopyText);
        menu.addAction(actCopy);
        menu.exec(chatView->viewport()->mapToGlobal(pos));
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
 * \brief AIChatAssistant::updateConversationForChatview
 * Show conversation in chatview, e.g. as bubbles
 * \return
 */
void AIChatAssistant::updateConversationForChatview()
{
    chatmodel->clear();
    for(auto it=ja_messages.begin();it!=ja_messages.end();++it){
        QJsonObject obj=it->toObject();
        QString role=obj["role"].toString();
        const QString cnt=obj["content"].toString();
        if(role=="user"){
            addMessage(cnt,Sender::Me);
        }else if(role=="assistant"){
            if(!obj.contains("tool_calls") || obj["tool_calls"].toArray().isEmpty()){
                // only normal answers
                addMessage(cnt,Sender::Them);
            }
        }
    }
}
/*!
 * \brief read streamed conversation and update textBrowser
 * \param allData
 */
void AIChatAssistant::updateStreamedConversation(const QString &allData)
{
    QStringList msgs=allData.split("data: ");
    for(const QString &elem:qAsConst(msgs)){
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
    updateConversationForChatview();
}
/*!
 * \brief generate json array with txs functions for AI provider
 * \return
 */
QJsonArray AIChatAssistant::makeFunctionsJsonArray() const
{
    QJsonArray ja_functions;
    for(ToolFunction tf:m_toolFunctions){
        QJsonObject jo_functionObject;
        jo_functionObject["type"]="function";
        QJsonObject jo_function;
        jo_function["name"]=tf.name;
        jo_function["description"]=tf.description;
        QStringList requiredParameters;
        if(tf.parameter.isEmpty()){
            jo_function["parameters"]=QJsonObject{
                {"type","object"},
                {"properties",QJsonObject()}
            };
        }else{
            QJsonObject jo_properties;
            QStringList parameters=tf.parameter.split("\n");
            foreach(const QString &param,parameters){
                QStringList parts=param.split(":");
                if(parts.size()==2){
                    QString paramName=parts[0].trimmed();
                    if(paramName.startsWith("*")){
                        paramName=paramName.mid(1);
                        requiredParameters.append(paramName);
                    }
                    QString paramDesc=parts[1].trimmed();
                    jo_properties[paramName]=QJsonObject{
                        {"type","string"},
                        {"description",paramDesc}
                    };
                }
            }
            QJsonObject jo_params=QJsonObject{
                {"type","object"},
                {"properties",jo_properties}
            };
            if(!requiredParameters.isEmpty()){
                jo_params["required"]=QJsonArray::fromStringList(requiredParameters);
            }
            jo_function["parameters"]=jo_params;
        }
        jo_functionObject["function"]=jo_function;
        ja_functions.append(jo_functionObject);
    }

    return ja_functions;
}
/*! \brief handle tool calls from AI provider
 * This is used when the AI provider returns a function call instead of a text response
 * \param jo
 */
void AIChatAssistant::handleToolCall(QJsonObject jo)
{
    QJsonArray ja_toolCalls=jo["tool_calls"].toArray();
    // iterate over tool calls and execute them
    for(const QJsonValue &toolCall:ja_toolCalls){
        QJsonObject jo_toolCall=toolCall.toObject();
        QString id=jo_toolCall["id"].toString();
        QJsonObject jo_function=jo_toolCall["function"].toObject();
        QString name=jo_function["name"].toString();
        for(ToolFunction tf:m_toolFunctions){
            if(tf.name!=name) continue;
            qDebug()<<"Tool call:"<<tf.name;

            // get file name of current file and return it to AI provider
            const QString arg=jo_function["arguments"].toString();
            QString result=tf.func(arg); // for now, no parameters
            // generate a tool call message
            {
                QJsonObject jo_message;
                jo_message["role"]="assistant";
                QJsonArray ja_toolCalls;
                QJsonObject jo_toolCall{
                    {"id",id},
                    {"type","function"},
                    {"function",jo_function}
                };
                ja_toolCalls.append(jo_toolCall);
                jo_message["tool_calls"]=ja_toolCalls;
                jo_message["content"]="";
                ja_messages.append(jo_message);
            }
            // generate answer message
            {
                QJsonObject jo_message;
                jo_message["role"]="tool";
                jo_message["tool_call_id"]=id;
                jo_message["name"]=name;
                jo_message["content"]=result;
                ja_messages.append(jo_message);
            }
        }
    }
    slotSend(true); // send updated conversation to AI provider
}

void AIChatAssistant::addMessage(const QString &text, Sender sender)
{
    QStandardItem *item = new QStandardItem(text);
    item->setData(static_cast<int>(sender), Qt::UserRole);
    chatmodel->appendRow(item);
    chatView->scrollTo(chatmodel->indexFromItem(item));
}
/*!
 * \brief AIChatAssistant::insertTextAtCursor
 * \param text
 */
void AIChatAssistant::insertTextAtCursor(const QString &text)
{
    if(text.contains("```")){
        QStringList parts=text.split("```");
        if(parts.size()>1){
            parts=parts[1].split("\n");
            if(parts.size()>1 && (parts[0]=="latex" || parts[0].isEmpty()) ){
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
        // check if text=""" ... """ is repeated
        // this is used to manipulate selected text
        const int i=text.indexOf("text=\"\"\"");
        if(i>=0){
            int l=text.indexOf("\"\"\"",i+8); // find second delimiter
            QString m_response=text.mid(i+8,l-8-i);
            emit insertText(m_response);
        }else{
            // insert whole text
            emit insertText(text);
        }
    }
}
/*!
 * \brief implementation of tool function "get_filename"
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetFilename(const QString arg) const
{
    QString fn=txsInstance->getCurrentFileName();
    return fn;
}
/*!
 * \brief list of files for the current document, e.g. for \include/\input
 * \param arg ignored
 * \return
 */
QString AIChatAssistant::tfGetListFiles(const QString arg) const
{
    QList<LatexDocument *> docs = txsInstance->currentEditorView()->document->getListOfDocs();
    QStringList fileNames;
    for(LatexDocument *doc:docs){
        fileNames.append(doc->getFileName());
    }
    return fileNames.join("\n");
}

QString AIChatAssistant::tfGetSelection(const QString arg) const
{
    QString selectedText;
    QEditor *ed = txsInstance->currentEditor();
    if(ed){
        QDocumentCursor cursor = ed->cursor();
        if(cursor.hasSelection()){
            selectedText = cursor.selectedText();
        }
    }
    return selectedText;
}
/*!
 * \brief provide complete text of current document to LLM
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetText(const QString arg) const
{
    if(arg.isEmpty()){
        LatexDocument *doc=txsInstance->documents.currentDocument;
        if(doc){
            return doc->text();
        }
    }
    return "";
}

QString AIChatAssistant::tfSetCursor(const QString arg) const
{
    qDebug()<<"set cursor to line:"<<arg;
    // split argument from { "line":"10" } to get line number
    QMap<QString, int> args=retrieveToolArguments(arg);
    if(!args.contains("line")) return "operation:failed, missing argument line";
    QEditor *ed = txsInstance->currentEditor();
    if(ed){
        QDocumentCursor cursor = ed->cursor();
        int ln=args["line"]; // line numbers start with 1 for user, but with 0 in cursor
        int col=args.value("column",0);
        cursor.moveTo(ln,col);
        ed->setCursor(cursor);
    }
    return "operation:success";
}
/*!
 * \brief perform selection from start to end position. If column is not given assume start of line of starting position, end of line for ending position
 * \param arg
 * \return
 */
QString AIChatAssistant::tfSetSelection(const QString arg) const
{
    qDebug()<<"set selection:"<<arg;
    QMap<QString, int> args=retrieveToolArguments(arg);
    if(!args.contains("startLine")) return "operation:failed, missing argument startLine";
    QEditor *ed = txsInstance->currentEditor();
    if(ed){
        QDocumentCursor cursor = ed->cursor();
        const int lineCount=ed->document()->lineCount();
        int ln=args["startLine"]; // line numbers start with 1 for user, but with 0 in cursor
        if(ln<0 || ln>=lineCount) return "operation:failed, invalid start line number";
        int col=args.value("startColumn",0);
        if(col<0 || col>ed->document()->line(ln).length()) return "operation:failed, invalid start column number";
        int endLine=args.value("endLine",ln);
        if(endLine<0 || endLine>=lineCount) return "operation:failed, invalid end line number";
        int endCol=args.value("endColumn",-1);
        if(endCol==-1){
            // assume end of line
            endCol=ed->document()->line(endLine).length();
        }
        if(endCol<0 || endCol>ed->document()->line(endLine).length()) return "operation:failed, invalid end column number";
        cursor.moveTo(ln,col);
        cursor.moveTo(endLine,endCol, QDocumentCursor::KeepAnchor);
        ed->setCursor(cursor);
    }
    return "operation:success";
}
/*!
 * \brief return position of current cursor, e.g. for tool function to set cursor position relative to it
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetCursorPosition(const QString arg) const
{
    QEditor *ed = txsInstance->currentEditor();
    if(ed){
        QDocumentCursor cursor = ed->cursor();
        int line=cursor.lineNumber(); // line numbers start with 1 for user, but with 0 in cursor
        int column=cursor.columnNumber();
        int lineAnchor=cursor.anchorLineNumber();
        int columnAnchor=cursor.anchorColumnNumber();
        return QString("line:%1,column:%2,anchorLine:%3,anchorColumn:%4").arg(line).arg(column).arg(lineAnchor).arg(columnAnchor);
    }
    return "";
}
/*!
 * \brief return text of a given line number
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetLineText(const QString arg) const
{
    QMap<QString, int> args=retrieveToolArguments(arg);
    if(!args.contains("line")) return "";
    int ln=args["line"]; // line numbers start with 1 for user, but with 0 in cursor
    LatexDocument *doc=txsInstance->currentEditorView()->document;
    if(doc){
        if(ln<0 || ln>=doc->lineCount()) return "operation:failed, invalid line number";
        return doc->line(ln).text();
    }
    return "";
}
/*!
 * \brief return length of given line number, e.g. for tool function to set cursor position relative to end of line
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetLineLength(const QString arg) const
{
    QMap<QString, int> args=retrieveToolArguments(arg);
    if(!args.contains("line")) return "";
    int ln=args["line"]; // line numbers start with 1 for user, but with 0 in cursor
    LatexDocument *doc=txsInstance->currentEditorView()->document;
    if(doc){
        if(ln<0 || ln>=doc->lineCount()) return "operation:failed, invalid line number";
        return QString::number(doc->line(ln).length());
    }
    return "";
}
/*!
 * \brief return number of lines of current document
 * \param arg
 * \return
 */
QString AIChatAssistant::tfGetNumberLines(const QString arg) const
{
    LatexDocument *doc=txsInstance->currentEditorView()->document;
    if(doc){
        return QString::number(doc->lineCount());
    }
    return "";
}
/*!
 * \brief return first line containing given text, e.g. for tool function to set cursor position relative to it
 * \param arg
 * \return
 */
QString AIChatAssistant::tfFindText(const QString arg, bool regExp) const
{
    QMap<QString, QString> args=retrieveToolArgumentsString(arg);
    if(!args.contains("text")) return "";
    QString text=args["text"]; // text to find
    // replace \\ with \ in text, as this is how it is given by LLMs in many cases
    text.replace("\\\\","\\");
    bool withinCurrentSelection=args.contains("withinCurrentSelection");
    QEditor *ed=txsInstance->currentEditor();
    if(ed){
        ed->find(text,false,regExp,false,false,true,withinCurrentSelection);
        QDocumentCursor cursor=ed->cursor();
        if(cursor.hasSelection()){
            int i=cursor.lineNumber();
            int start=cursor.startColumnNumber();
            if(regExp){
                QString selectedText=cursor.selectedText();
                QString result=QString("foundText:%1,line:%2,column:%3,length:%4").arg(selectedText).arg(i).arg(start).arg(selectedText.length());
                QRegularExpression re(text);
                QRegularExpressionMatch match=re.match(selectedText);
                if(match.hasMatch()){
                    QStringList submatches;
                    for(int i=1;i<match.lastCapturedIndex();++i){
                        submatches.append(match.captured(i));
                    }
                    if(submatches.size()>0){
                        result+=",submatches:"+submatches.join(",");
                    }
                }
                qDebug()<<result;
                return result;
            }else{
                return QString("foundText:%1,line:%2,column:%3,length:%4").arg(text).arg(i).arg(start).arg(text.length());
            }
        }
    }
    return "";
}
/*!
 * \brief replace selected text with given text
 * \param arg
 * \return
 */
QString AIChatAssistant::tfReplaceSelectedText(const QString arg) const
{
    QMap<QString, QString> args=retrieveToolArgumentsString(arg);
    if(!args.contains("text")) return "operation:failed, missing argument text";
    QString text=args["text"]; // text to replace with
    QEditor *ed=txsInstance->currentEditor();
    if(ed){
        QDocumentCursor cursor=ed->cursor();
        if(cursor.hasSelection()){
            cursor.replaceSelectedText(text);
            return "operation:success";
        }else{
            cursor.insertText(text);
            return "operation:success";
        }
    }
    return "operation:failed, no editor";
}

/*!
 * \brief return arguments for tool function, e.g. line number for set_cursor
 * Assumes integer arguments only
 * \param parameter
 * \return
 */
QMap<QString, int> AIChatAssistant::retrieveToolArguments(const QString &parameter) const
{
    QString argument=parameter.mid(1,parameter.length()-2); // remove braces
    QStringList parts=argument.split(",");
    QMap<QString, int> args;
    for(const QString &part:parts){
        QStringList kv=part.split(":");
        if(kv.size()==2){
            QString key=kv[0].trimmed();
            key=key.mid(1,key.length()-2); // remove quotes
            bool ok;
            QString val=kv[1].trimmed();
            val=val.mid(1,val.length()-2); // remove quotes
            int value=val.toInt(&ok);
            if(ok){
                args[key]=value;
            }
        }
    }
    return args;
}
/*!
 * \brief return arguments for tool function, e.g. text
 * Assumes string arguments only
 * \param parameter
 * \return
 */
QMap<QString, QString> AIChatAssistant::retrieveToolArgumentsString(const QString &parameter) const
{
    QString argument=parameter.mid(1,parameter.length()-2); // remove braces
    QStringList parts=argument.split(",");
    QMap<QString, QString> args;
    for(const QString &part:parts){
        QStringList kv=part.split(":");
        if(kv.size()==2){
            QString key=kv[0].trimmed();
            key=key.mid(1,key.length()-2); // remove quotes
            QString val=kv[1].trimmed();
            val=val.mid(1,val.length()-2); // remove quotes
            args[key]=val;
        }
    }
    return args;
}
/*!
 * \brief register functions as tools for AI provider
 */
void AIChatAssistant::registerToolFunctions()
{
    m_toolFunctions<<ToolFunction{"get_filename","Get the name of the current file","",[this](QString input) { return this->tfGetFilename(); }};
    m_toolFunctions<<ToolFunction{"get_list_of_docs","Get the names of all files which are included in the current project","",[this](QString input) { return this->tfGetListFiles(); }};
    m_toolFunctions<<ToolFunction{"get_selection","Get selected text","",[this](QString input) { return this->tfGetSelection(); }};
    m_toolFunctions<<ToolFunction{"get_text","Get complete text of current document","",[this](QString input) { return this->tfGetText(); }};
    // example for function with arguments, e.g. to set cursor position
    // arguments are given as single string "arg:descript\narg2:desc2". "*arg:desc" means required argument, "arg:desc" means optional argument
    m_toolFunctions<<ToolFunction{"set_cursor","Set cursor to given line","*line:line number to put cursor\ncolumn:column number to put cursor",[this](QString input) { return this->tfSetCursor(input); }};
    m_toolFunctions<<ToolFunction{"get_cursor_position","Get the line number and column number of current cursor. Anchor line and anchor column as well","",[this](QString input) { return this->tfGetCursorPosition(); }};
    m_toolFunctions<<ToolFunction{"get_line_text","Get text of a given line","*line:line number of which text is wanted",[this](QString input) { return this->tfGetLineText(input); }};
    m_toolFunctions<<ToolFunction{"set_selection","Select text from start to end position. If column is not given assume start of line of starting position, end of line for ending position",
                                    "*startLine:line number to start selection\nstartColumn:start column number for selection\nendLine:line number to end selection\nendColumn:end column number for selection",[this](QString input) { return this->tfSetSelection(input); }};
    m_toolFunctions<<ToolFunction{"get_line_length","Get length of a given line","*line:line number for which line length is wanted",[this](QString input) { return this->tfGetLineLength(input); }};
    m_toolFunctions<<ToolFunction{"get_number_lines","Get number of lines of current document","",[this](QString input) { return this->tfGetNumberLines(input); }};
    m_toolFunctions<<ToolFunction{"find_text","Find text in current document and return first position (line,column,length) after the current cursor position. The result is also selected with the current cursor.","*text:search text,withinCurrentSelection:true is search is limited to current selected text",[this](QString input) { return this->tfFindText(input); }};
    m_toolFunctions<<ToolFunction{"find_regexp","Find regular expresssion in current document and return first position (line,column,length) after the current cursor position. The result is also selected with the current cursor. Submatches are also returned","*text:search text that contains a regular expression\nwithinCurrentSelection:true is search is limited to current selected text",[this](QString input) { return this->tfFindText(input,true); }};
    m_toolFunctions<<ToolFunction{"replace_selected_text","Replace selected text with given text. If no text is selected, insert given text at current cursor position","*text:text to replace with",[this](QString input) { return this->tfReplaceSelectedText(input); }};
}

/*! TODO
 *  - insert packages
 *  - detect new document/insert all
 *  - add to macros
 *  - modeltree for conversations
 *   + show summary of conversation in titles ?
 */
