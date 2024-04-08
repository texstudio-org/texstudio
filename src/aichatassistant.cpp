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
    auto *hlayout=new QHBoxLayout();
    hlayout->addWidget(leEntry);
    auto *vl=new QVBoxLayout();
    vl->addWidget(btSend,0,Qt::AlignTop);
    vl->addWidget(btInsert,0,Qt::AlignTop);
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
 * \brief send question to ai provider
 */
void AIChatAssistant::slotSend()
{
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
    ja_messages=QJsonArray();
    ja_messages.append(ja_message);

    dd["messages"]=ja_messages;

    QJsonDocument jsonDoc(dd);
    QString data=jsonDoc.toJson();

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "TeXstudio Chat Assistant");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(config->ai_apikey).toUtf8());
    QNetworkReply *reply = networkManager->post(request,data.toUtf8());
    connect(networkManager, &QNetworkAccessManager::finished, this, &AIChatAssistant::onRequestCompleted);
#if QT_VERSION_MAJOR<6
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError(QNetworkReply::NetworkError)));
#else
    connect(reply, &QNetworkReply::errorOccurred, this, &AIChatAssistant::onRequestError);
#endif

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
            }
        }
    }else{
        // insert whole text
        emit insertText(m_response);
    }
}
/*!
 * \brief handle communication error with ai provider
 */
void AIChatAssistant::onRequestError(QNetworkReply::NetworkError code)
{
    qDebug()<<"Error:"<<code;
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
            m_response=ja_message["content"].toString();
#if QT_VERSION>=QT_VERSION_CHECK(5,14,0)
            textBrowser->setMarkdown(m_response);
#else
            textBrowser->setText(m_response); // no markdown interpretation, just keep old qt version running
#endif

        }
        nreply->deleteLater();
    }
}
