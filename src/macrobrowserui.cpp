#include "macrobrowserui.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QJsonDocument>
#include <QJsonArray>

const int MacroBrowserUI::FileRole = Qt::UserRole + 0;
const int MacroBrowserUI::UrlRole = Qt::UserRole + 1;
const int MacroBrowserUI::PathRole = Qt::UserRole + 2;
const int MacroBrowserUI::PopulatedRole = Qt::UserRole + 3;
#if QT_VERSION_MAJOR<6
Q_DECLARE_METATYPE(QTreeWidgetItem *)
#endif

MacroBrowserUI::MacroBrowserUI(QWidget *parent):QDialog (parent)
{
    treeWidget=new QTreeWidget(parent);
    treeWidget->setHeaderHidden(true);
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
    gridLay->addWidget(treeWidget,1,0,5,1);
    gridLay->addWidget(lblName,1,1);
    gridLay->addWidget(lblDescription,2,1);
    gridLay->addWidget(leName,1,2);
    gridLay->addWidget(teDescription,2,2,4,1);

    buttonBox=new QDialogButtonBox();
    buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    auto *layout=new QVBoxLayout();
    layout->addLayout(gridLay);
    layout->addWidget(buttonBox);
    setLayout(layout);
    setWindowTitle(tr("Browse macros from repository"));
    config=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    networkManager = new QNetworkAccessManager();

    connect(treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(slotCurrentItemChanged(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(slotItemClicked(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),SLOT(slotItemClicked(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)),SLOT(slotItemExpanded(QTreeWidgetItem*)));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    requestMacroList();
}

MacroBrowserUI::~MacroBrowserUI()
{
    if (networkManager) {
        networkManager->deleteLater();
        networkManager=nullptr;
    }
    delete treeWidget;
}

QList<Macro> MacroBrowserUI::getSelectedMacros()
{
    QList<Macro> lst;
    QTreeWidgetItemIterator it(treeWidget,QTreeWidgetItemIterator::Checked);
    while (*it) {
        QString url=(*it)->data(0,UrlRole).toString();
        QString macroJson=cache.value(url);
        if(!macroJson.isEmpty()){
            Macro m;
            m.loadFromText(macroJson);
            lst << m;
        }
        ++it;
    }
    return lst;
}

const QNetworkRequest::Attribute mbAttributeItem = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User);
const QNetworkRequest::Attribute mbAttributeIsFile = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User+1);

/* Note (1): The elements of the top level directory of the repository are added as top level items to the treeWidget. Thus they have no
 * parent item (folder). Since folder items carry the path in the tree and the (repository) url as data, it is necessary to distinguish
 * this situation where we use "" as path (think of the treeWidget as a folder).
*/
void MacroBrowserUI::requestMacroList(QTreeWidgetItem *currentItem,const bool &isFile)
{
    if(!networkManager){
        networkManager = new QNetworkAccessManager();
        if(!networkManager) return;
    }
    QString path=(currentItem ? currentItem->data(0,PathRole).toString() : "");  // s. (1)
    QString url;
    if(isFile) {
        // like https://raw.githubusercontent.com/texstudio-org/texstudio-macro/master/automatedTextmanipulation/autoLabel.txsMacro
        url=(currentItem ? currentItem->data(0,UrlRole).toString() : "");  // s. (1)
    }else{
        path=(currentItem ? currentItem->data(0,PathRole).toString() : "");  // s. (1)
        // like https://api.github.com/repos/texstudio/texstudio-macro/contents/automatedTextmanipulation
        url=config->URLmacroRepository+path;
    }

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "TeXstudio Macro Browser");
    request.setAttribute(mbAttributeIsFile,isFile);
    request.setAttribute(mbAttributeItem,QVariant::fromValue(currentItem));
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, SIGNAL(finished()), SLOT(onRequestCompleted()));
#if QT_VERSION_MAJOR<6
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError()));
#else
    connect(reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(onRequestError()));
#endif
}

void MacroBrowserUI::onRequestError()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    QString text=tr("Repository not found. Network error:%1");
    QTreeWidgetItem *currentItem=reply->request().attribute(mbAttributeItem).value<QTreeWidgetItem*>();
    if (currentItem) {
        currentItem->child(0)->setText(0,text.arg("\n"+reply->errorString()));
    }else{
        QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << text.arg("\n"+reply->errorString()));
        treeWidget->addTopLevelItem(twi);
    }

    networkManager->deleteLater();
    networkManager=nullptr;
}

void MacroBrowserUI::onRequestCompleted()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply || reply->error() != QNetworkReply::NoError) return;

    QTreeWidgetItem *currentItem=reply->request().attribute(mbAttributeItem).value<QTreeWidgetItem*>();
    bool isFile=reply->request().attribute(mbAttributeIsFile).toBool();
    QString path;
    QString url;
    if(isFile) {
        url=(currentItem ? currentItem->data(0,UrlRole).toString() : "");  // s. (1)
    }else{
        path=(currentItem ? currentItem->data(0,PathRole).toString() : "");  // s. (1)
        url=config->URLmacroRepository+path;
    }

    if(path!="" && !currentItem) return;

    QByteArray ba = reply->readAll();

    if(isFile){
        // file download requested
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
        cache.insert(url,QString(ba));
    }else{
        // folder contents requested
        QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
        QJsonArray elements=jsonDoc.array();
        if (currentItem) {     // not needed when inserting top level items, s. (1)
            currentItem->takeChildren();
            currentItem->setData(0,PopulatedRole,true);
        }
        foreach(auto element,elements){
            QJsonObject dd=element.toObject();
            if(dd["type"].toString()=="file"){
                QString name=dd["name"].toString();
                if(name.endsWith(".txsMacro")){
                    auto *twi=new QTreeWidgetItem(QStringList()<<name);
                    twi->setData(0,FileRole,true);
                    twi->setData(0,UrlRole,dd["download_url"].toString());
                    twi->setCheckState(0,Qt::Unchecked);
                    currentItem->addChild(twi);
                }
            }else{ // folder
                QString name=dd["name"].toString();
                auto *item=new QTreeWidgetItem(QStringList()<<name);
                QFont ft = item->font(0);
                ft.setBold(true);
                item->setFont(0,ft);
                item->setText(0,name);
                QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << tr("<loading...>"));
                item->addChild(twi);
                item->setData(0,FileRole,false);
                item->setData(0,UrlRole, url);
                item->setData(0,PathRole, path+name);
                if(!currentItem) treeWidget->addTopLevelItem(item);
                else item->addChild(item);
            }
        }
    }
}

void MacroBrowserUI::slotCurrentItemChanged(QTreeWidgetItem *item)
{
    bool isFile=item->data(0,FileRole).toBool();
    if(!isFile){
        leName->setText("");
        teDescription->setPlainText("");
    }else{
        QString url=item->data(0,UrlRole).toString();
        if(cache.contains(url)){
            // reuse cached
            QByteArray ba = cache.value(url).toUtf8();
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
        }
        else{
            requestMacroList(item,true);
        }
    }
}

void MacroBrowserUI::slotItemClicked(QTreeWidgetItem *item)
{
    bool isFile=item->data(0,FileRole).toBool();
    if(!isFile) return;
    treeWidget->setCurrentItem(item);       // this may trigger slotCurrentItemChanged
}

void MacroBrowserUI::slotItemExpanded(QTreeWidgetItem *item){
    bool populated=item->data(0,PopulatedRole).toBool();
    if(populated) return;
    requestMacroList(item);
}
