#include "macrobrowserui.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QJsonDocument>
#include <QJsonArray>


MacroBrowserUI::MacroBrowserUI(QWidget *parent):QDialog (parent)
{
    tableWidget=new QTableWidget(4,1);
    tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Macro name"));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    connect(tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),SLOT(itemClicked(QTableWidgetItem*)));
    auto *lblName=new QLabel(tr("Name"));
    lblName->setAlignment(Qt::AlignRight);
    auto *lblDescription=new QLabel(tr("Description"));
    lblDescription->setAlignment(Qt::AlignRight|Qt::AlignTop);
    leName=new QLineEdit();
    leName->setReadOnly(true);
    teDescription=new QPlainTextEdit();
    teDescription->setReadOnly(true);
    auto *gridLay=new QGridLayout();
    gridLay->setColumnStretch(0,1);
    gridLay->setColumnStretch(1,0);
    gridLay->setColumnStretch(2,1);
    gridLay->addWidget(tableWidget,1,0,5,1);
    gridLay->addWidget(lblName,1,1);
    gridLay->addWidget(lblDescription,2,1);
    gridLay->addWidget(leName,1,2);
    gridLay->addWidget(teDescription,2,2);

    buttonBox=new QDialogButtonBox();
    buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    auto *layout=new QVBoxLayout();
    layout->addLayout(gridLay);
    layout->addWidget(buttonBox);
    setLayout(layout);
    setWindowTitle(tr("Browse macros from repository"));
    config=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    networkManager = new QNetworkAccessManager();

    requestMacroList("");
}

MacroBrowserUI::~MacroBrowserUI()
{
    networkManager->deleteLater();
    networkManager=nullptr;
    foreach(QList<QTableWidgetItem *>lst,itemCache){
        foreach(auto *item,lst){
            delete item;
        }
    }
}

QList<Macro> MacroBrowserUI::getSelectedMacros()
{
    QList<Macro> lst;
    foreach(QList<QTableWidgetItem *>listOfItems,itemCache){
        foreach(auto *item,listOfItems){
            if(item->checkState()==Qt::Checked){
                QString url=item->data(Qt::UserRole).toString();
                QString macroJson=cache.value(url);
                if(!macroJson.isEmpty()){
                    Macro m;
                    m.loadFromText(macroJson);
                    lst << m;
                }
            }
        }
    }

    return lst;
}

const QNetworkRequest::Attribute AttributeDirectURL = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User);
const QNetworkRequest::Attribute AttributeURL = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User+1);

void MacroBrowserUI::requestMacroList(const QString &path,const bool &directURL)
{
    if(!networkManager){
        return;
    }
    QString url=config->URLmacroRepository+path;
    //QString url="https://api.github.com/repos/sunderme/texstudio-macro/contents/"+path;
    if(directURL){
        url=path;
    }else{
        currentPath=path;
    }
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "TeXstudio Macro Browser");
    request.setAttribute(AttributeDirectURL,directURL);
    request.setAttribute(AttributeURL,url);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, SIGNAL(finished()), SLOT(onRequestCompleted()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onRequestError()));
}

void MacroBrowserUI::itemClicked(QTableWidgetItem *item)
{
    QString url=item->data(Qt::UserRole).toString();
    if(url.isEmpty()){
        // descend into folder
        leName->setText("");
        teDescription->setPlainText("");
        if(item->text()==".."){
            int c=currentPath.lastIndexOf('/');
            url=currentPath.left(c);
        }else{
            url=currentPath+"/"+item->text();
        }
        if(itemCache.contains(url)){
            // reuse cached
            currentPath=url;
            int i=0;
            for(int i=0;i<tableWidget->rowCount();i++){
                tableWidget->takeItem(i,0);
            }
            if(!url.isEmpty()){
                auto *item=new QTableWidgetItem(QIcon::fromTheme("file"),"..");
                tableWidget->setRowCount(i+1);
                tableWidget->setItem(i++,0,item);
            }
            foreach(QTableWidgetItem *item,itemCache.value(url)){
                tableWidget->setRowCount(i+1);
                tableWidget->setItem(i++,0,item);
            }
        }else{
            requestMacroList(url);
        }
    }else{
        requestMacroList(url,true);
    }
}

void MacroBrowserUI::onRequestError()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    QMessageBox::warning(this, tr("Browse macro repository"),
                                   tr("Repository not found. Network error:%1").arg(reply->errorString()),
                                   QMessageBox::Ok,
                                   QMessageBox::Ok);
    networkManager->deleteLater();
    networkManager=nullptr;
}

void MacroBrowserUI::onRequestCompleted()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply || reply->error() != QNetworkReply::NoError) return;

    QByteArray ba = reply->readAll();

    if(reply->request().attribute(AttributeDirectURL).toBool()){
        // download requested
        QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
        QJsonObject dd=jsonDoc.object();
        leName->setText(dd["name"].toString());
        QJsonArray array=dd["description"].toArray();
        QVariantList vl=array.toVariantList();
        QString text;
        foreach(auto v,vl){
            if(!text.isEmpty()){
                text+="\n";
            }
            text+=v.toString();
        }
        teDescription->setPlainText(text);
        // cache complete macro
        QString url=reply->request().attribute(AttributeURL).toString();
        cache.insert(url,QString(ba));
    }else{
        // folder overview requested
        //tableWidget->clearContents();
        for(int i=0;i<tableWidget->rowCount();i++){
            tableWidget->takeItem(i,0);
        }
        QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
        QJsonArray elements=jsonDoc.array();
        int i=0;
        // add .. (up)
        if(!currentPath.isEmpty()){
            auto *item=new QTableWidgetItem(QIcon::fromTheme("file"),"..");
            tableWidget->setRowCount(i+1);
            tableWidget->setItem(i++,0,item);
        }
        QList<QTableWidgetItem*> listOfItems;
        foreach(auto element,elements){
            QJsonObject dd=element.toObject();
            if(dd["type"].toString()=="file"){
                QString name=dd["name"].toString();
                if(name.endsWith(".txsMacro")){
                    auto *item=new QTableWidgetItem(QIcon::fromTheme("file"),name);
                    item->setData(Qt::UserRole,dd["download_url"].toString());
                    item->setCheckState(Qt::Unchecked);
                    tableWidget->setRowCount(i+1);
                    tableWidget->setItem(i++,0,item);
                    if(i==1){
                        requestMacroList(item->data(Qt::UserRole).toString(),true);
                    }
                    listOfItems<<item;
                }
            }else{
                // folder
                QString name=dd["name"].toString();
                auto *item=new QTableWidgetItem(QIcon::fromTheme("folder"),name);
                tableWidget->setRowCount(i+1);
                tableWidget->setItem(i++,0,item);
                listOfItems<<item;
            }
            //tableWidget->setRowCount(i);
        }
        tableWidget->setCurrentCell(0,0);
        itemCache.insert(currentPath,listOfItems);
    }
}



