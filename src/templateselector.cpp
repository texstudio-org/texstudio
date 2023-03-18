/***************************************************************************
 *   copyright       : (C) 2009 by Jan Sundermeyer                         *
 *   http://texstudio.sourceforge.net/                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "templateselector.h"
#include "qnetworkreply.h"
#include "qnetworkrequest.h"
#include "smallUsefulFunctions.h"
#include "templatemanager_p.h"

#include <QJsonDocument>
#include <QJsonArray>

const int TemplateSelector::TemplateHandleRole = Qt::UserRole;
const int TemplateSelector::ResourceRole = Qt::UserRole + 1;
const int TemplateSelector::UrlRole = Qt::UserRole + 2;
const int TemplateSelector::PathRole = Qt::UserRole + 3;
const int TemplateSelector::DownloadRole = Qt::UserRole + 4;
const int TemplateSelector::PreviewRole = Qt::UserRole + 5;
const int TemplateSelector::TexRole = Qt::UserRole + 6;
const int TemplateSelector::PopulatedRole = Qt::UserRole + 7;


void PreviewLabel::setScaledPixmap(const QPixmap &pm)
{
	currentPixmap = pm;
	setPixmapWithResizing(pm);
}

void PreviewLabel::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event)
	setPixmapWithResizing(currentPixmap);
}

void PreviewLabel::setPixmapWithResizing(const QPixmap &pm)
{
	if (pm.isNull()) {
		setText(TemplateSelector::tr("No Preview"));
		return;
	}

    double relWidth = pm.width() / static_cast<double>( contentsRect().width());
    double relHeight = pm.height() / static_cast<double>(contentsRect().height());
	if (relWidth > 1.0 || relHeight > 1.0) {
		setPixmap(pm.scaled(contentsRect().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	} else {
		setPixmap(pm);
	}
}


TemplateSelector::TemplateSelector(QString name, QWidget *parent)
    : QDialog(parent), previewLabel(nullptr)
{
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 61, 36);
	setWindowTitle(name);

	QGridLayout *gl = qobject_cast<QGridLayout *>(layout());
	if (gl) {
		// TODO is there a more elegant way to replace the label?
		gl->removeWidget(ui.previewLabelDummy);
		delete ui.previewLabelDummy;

		previewLabel = new PreviewLabel(this);
		previewLabel->setFrameShape(QFrame::Box);
		previewLabel->setFrameShadow(QFrame::Plain);
		previewLabel->setAlignment(Qt::AlignCenter);
		previewLabel->setMargin(5);
		previewLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		gl->addWidget(previewLabel, 0, 2);
	}

    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &TemplateSelector::acceptResult);
    connect(ui.buttonBox, SIGNAL(rejected()), SLOT(reject()));

	ui.templatesTree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.templatesTree, SIGNAL(customContextMenuRequested(QPoint)), SLOT(templatesTreeContextMenu(QPoint)));
    connect(ui.templatesTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(showInfo(QTreeWidgetItem*,QTreeWidgetItem*)));

	ui.lePath->setText(getUserDocumentFolder());

	connect(ui.rbCreateInFolder, SIGNAL(toggled(bool)), ui.lePath, SLOT(setEnabled(bool)));
	connect(ui.rbCreateInFolder, SIGNAL(toggled(bool)), ui.btPath, SLOT(setEnabled(bool)));
	connect(ui.rbCreateInFolder, SIGNAL(toggled(bool)), this, SLOT(checkTargetPath()));
	connect(ui.lePath, SIGNAL(textChanged(QString)), this, SLOT(checkTargetPath()));
	ui.warningIcon->hide();
	ui.warningText->hide();
	QString warnTooltip = tr("It is recommended to instantiate templates in a new folder. Otherwise, existing files may be overwritten.");
	ui.warningIcon->setToolTip(warnTooltip);
	ui.warningText->setToolTip(warnTooltip);

    showInfo(nullptr, nullptr);
}

TemplateSelector::~TemplateSelector()
{
}

void TemplateSelector::addResource(AbstractTemplateResource *res)
{
	QTreeWidgetItem *topitem = new QTreeWidgetItem(QStringList() << res->name());
	topitem->setIcon(0, res->icon());
	QFont ft = topitem->font(0);
	ft.setBold(true);
	topitem->setFont(0, ft);
	topitem->setData(0, ResourceRole, QVariant::fromValue<AbstractTemplateResource *>(res));
	ui.templatesTree->addTopLevelItem(topitem);

	foreach (TemplateHandle th, res->getTemplates()) {
		QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << th.name());
		twi->setData(0, TemplateHandleRole, QVariant::fromValue<TemplateHandle>(th));
		topitem->addChild(twi);
	}
    topitem->setExpanded(true);
}

void TemplateSelector::addOnlineRepository()
{
    QTreeWidgetItem *topitem = new QTreeWidgetItem(QStringList() << tr("Online Repository"));
    //topitem->setIcon(0, res->icon());
    QFont ft = topitem->font(0);
    ft.setBold(true);
    topitem->setFont(0, ft);
    topitem->setData(0, UrlRole, QString("https://api.github.com/repos/texstudio-org/texstudio-template/contents"));
    topitem->setData(0, PathRole, QString(""));
    ui.templatesTree->addTopLevelItem(topitem);
    QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << tr("<loading...>"));
    topitem->addChild(twi);
    topitem->setExpanded(false);
    // do connect here as it is only needed for online repository
    connect(ui.templatesTree,&QTreeWidget::itemExpanded,this,&TemplateSelector::itemExpanded);
    networkManager = new QNetworkAccessManager();
}

const QNetworkRequest::Attribute tplAttributeDirectURL = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User);
const QNetworkRequest::Attribute tplAttributeURL = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User+1);
const QNetworkRequest::Attribute tplAttributePath = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User+2);
const QNetworkRequest::Attribute tplAttributeItem = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User+3);

/*!
 * \brief send a network request for online data of the template repository
 * Used cached files if present
 * \param url
 * \param path
 * \param item
 * \param download
 */
void TemplateSelector::makeRequest(QString url, QString path,QTreeWidgetItem *item,bool download)
{

    QString m_url=appendPath(url,path);
    if(download){
        // check if cached
        if(inCache(path)){
            QFile file(appendPath(m_cachingDir,path));
            if(file.open(QFile::ReadOnly)){
                QByteArray ba=file.readAll();
                onCachedRequestCompleted(ba,item,url);
                return;
            }
        }
        m_url=url;
    }
    QNetworkRequest request = QNetworkRequest(QUrl(m_url));
    request.setRawHeader("User-Agent", "TeXstudio Template Browser");
    request.setAttribute(tplAttributeDirectURL,download);
    request.setAttribute(tplAttributeURL,url);
    request.setAttribute(tplAttributePath,path);
    request.setAttribute(tplAttributeItem,QVariant::fromValue(item));
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &TemplateSelector::onRequestCompleted);
}

/*!
 * \brief write bytearray as file at path
 * Serves as cached data
 * Generates all intermediate folders
 * \param data
 * \param path
 */
void TemplateSelector::saveToCache(const QByteArray &data, const QString &path)
{
    const QString fn=appendPath(m_cachingDir,path);
    int i=fn.lastIndexOf("/");
    QDir dir(fn.left(i));
    if(!dir.exists()){
        dir.mkpath(fn.left(i));
    }
    QFile file(fn);
    if(file.open(QFile::WriteOnly)){
        file.write(data);
        file.close();
    }
}


void TemplateSelector::itemExpanded(QTreeWidgetItem* item){
    bool populated=item->data(0,PopulatedRole).toBool();
    if(populated) return;
    QString path=item->data(0,PathRole).toString();
    QString url=item->data(0,UrlRole).toString();
    if(url.isEmpty()) return; // not an online resource

    makeRequest(url,path,item);
}

void TemplateSelector::onRequestCompleted()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply || reply->error() != QNetworkReply::NoError) {
        if(reply) qDebug()<<"Network error:"<<reply->errorString();
        return;
    }

    QTreeWidgetItem *rootItem=reply->request().attribute(tplAttributeItem).value<QTreeWidgetItem*>();
    QString path=reply->request().attribute(tplAttributePath).toString();
    QString url=reply->request().attribute(tplAttributeURL).toString();
    if(!rootItem) return;

    QByteArray ba = reply->readAll();

    if(reply->request().attribute(tplAttributeDirectURL).toBool()){
        // download requested
        if(url.endsWith("json")){
            QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
            OnlineFileTemplate *tmpl=new OnlineFileTemplate(jsonDoc);
            tmpl->setURL(rootItem->data(0,TexRole).toString());

            TemplateHandle th=TemplateHandle(tmpl);
            rootItem->setData(0, TemplateHandleRole, QVariant::fromValue<TemplateHandle>(th));
            showInfo(rootItem,nullptr);
            QString previewURL=rootItem->data(0, PreviewRole).toString();
            makeRequest(previewURL,path,rootItem,true);
            // cache json
            QString fn=rootItem->data(0, PathRole).toString();
            saveToCache(ba,fn);
        }
        if(url.endsWith("png")){
            TemplateHandle th=rootItem->data(0, TemplateHandleRole).value<TemplateHandle>();
            OnlineFileTemplate *tpl=static_cast<OnlineFileTemplate *>(th.getHandle());
            QImage img=QImage::fromData(ba);
            tpl->setPreviewImage(QPixmap::fromImage(img));
            showInfo(rootItem,nullptr);
            // cache png
            QString path=rootItem->data(0, PathRole).toString();
            path.chop(4);
            path+="png";
            saveToCache(ba,path);
        }
        if(url.endsWith("tex")||url.endsWith("zip")){
            QString path=rootItem->data(0, PathRole).toString();
            path.chop(4);
            path+=url.right(3);
            const QString fn=appendPath(m_cachingDir,path);
            saveToCache(ba,path);
            TemplateHandle th=rootItem->data(0, TemplateHandleRole).value<TemplateHandle>();
            OnlineFileTemplate *tpl=static_cast<OnlineFileTemplate *>(th.getHandle());
            tpl->setURL(fn);
            accept();
        }
    }else{
        // folder overview requested
        QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
        QJsonArray elements=jsonDoc.array();

        rootItem->takeChildren();
        rootItem->setData(0,PopulatedRole,true);
        foreach(auto element,elements){
            QJsonObject dd=element.toObject();
            if(dd["type"].toString()=="file"){
                QString name=dd["name"].toString();
                if(name.endsWith(".json")){
                    auto *item=new QTreeWidgetItem();
                    item->setText(0,name.left(name.length()-5));
                    item->setIcon(0,QIcon::fromTheme("file"));
                    item->setData(0,DownloadRole,dd["download_url"].toString());
                    item->setData(0,UrlRole, url);
                    item->setData(0,PathRole, appendPath(path,name));
                    rootItem->addChild(item);
                }
                if(name.endsWith(".png")){
                    // add to last item
                    // naming scheme needs to be followed and then abc.json is before abc.png ...
                    // i.e. this needs to be improved.
                    int i=rootItem->childCount()-1;
                    if(i<0) continue;
                    auto *item=rootItem->child(i);
                    item->setData(0,PreviewRole,dd["download_url"].toString());
                }
                if(name.endsWith(".tex")||name.endsWith(".zip")){
                    // add to last item
                    // naming scheme needs to be followed and then abc.json is before abc.png ...
                    // i.e. this needs to be improved.
                    int i=rootItem->childCount()-1;
                    if(i<0) continue;
                    auto *item=rootItem->child(i);
                    item->setData(0,TexRole,dd["download_url"].toString());
                }
            }else{
                // folder
                QString name=dd["name"].toString();
                auto *item=new QTreeWidgetItem();
                QFont ft = item->font(0);
                ft.setBold(true);
                item->setFont(0, ft);
                item->setText(0,name);
                item->setIcon(0,QIcon::fromTheme("folder"));
                QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << tr("<loading...>"));
                item->addChild(twi);
                item->setData(0, UrlRole, url);
                item->setData(0, PathRole, appendPath(path,name));
                rootItem->addChild(item);
            }
        }
    }
}

void TemplateSelector::onCachedRequestCompleted(const QByteArray &ba,QTreeWidgetItem *rootItem,const QString &url)
{
    if(url.endsWith("json")){
        QJsonDocument jsonDoc=QJsonDocument::fromJson(ba);
        OnlineFileTemplate *tmpl=new OnlineFileTemplate(jsonDoc);
        tmpl->setURL(rootItem->data(0,TexRole).toString());

        TemplateHandle th=TemplateHandle(tmpl);
        rootItem->setData(0, TemplateHandleRole, QVariant::fromValue<TemplateHandle>(th));
        showInfo(rootItem,nullptr);
        QString previewURL=rootItem->data(0, PreviewRole).toString();
        QString path=rootItem->data(0, PathRole).toString();
        path.chop(4);
        path+="png";
        makeRequest(previewURL,path,rootItem,true);
    }
    if(url.endsWith("png")){
        TemplateHandle th=rootItem->data(0, TemplateHandleRole).value<TemplateHandle>();
        OnlineFileTemplate *tpl=static_cast<OnlineFileTemplate *>(th.getHandle());
        QImage img=QImage::fromData(ba);
        tpl->setPreviewImage(QPixmap::fromImage(img));
        showInfo(rootItem,nullptr);
    }
    if(url.endsWith("tex")||url.endsWith("zip")){
        QString path=rootItem->data(0, PathRole).toString();
        path.chop(4);
        path+=url.right(3);
        const QString fn=appendPath(m_cachingDir,path);
        TemplateHandle th=rootItem->data(0, TemplateHandleRole).value<TemplateHandle>();
        OnlineFileTemplate *tpl=static_cast<OnlineFileTemplate *>(th.getHandle());
        tpl->setURL(fn);
        accept();
    }
}
/*!
 * \brief checks if path is already cached
 * \param path
 * \return
 */
bool TemplateSelector::inCache(const QString &path)
{
    const QString fn=appendPath(m_cachingDir,path);
    return QFileInfo::exists(fn);
}
/*!
 * \brief add path to base with "/"
 * Make sure that only one "/" is between the  two
 * and the construct does not end with an slash
 * \param base
 * \param path
 * \return base+"/"+path
 */
QString TemplateSelector::appendPath(QString base, QString path)
{
    QString result=base;
    if(!result.endsWith("/")){
        result+="/";
    }
    if(path.startsWith("/")){
        result.chop(1); // "/" is provided by path
    }
    result+=path;
    if(result.endsWith("/")){
        result.chop(1);
    }
    return result;
}

void TemplateSelector::acceptResult()
{
    auto *item=ui.templatesTree->currentItem();
    if(item && item->data(0,UrlRole).isValid()){
                    QString path=item->data(0,PathRole).toString();
                    path.chop(4);
                    path+="tex";
                    QString url=item->data(0,UrlRole).toString();
                    QString downloadUrl=item->data(0,DownloadRole).toString();
                    QString texUrl=item->data(0,TexRole).toString();
                    makeRequest(texUrl,path,item,true);
    }else{
        accept();
    }
}

TemplateHandle TemplateSelector::selectedTemplate() const
{
	if (!ui.templatesTree->currentItem())
		return TemplateHandle();

	return ui.templatesTree->currentItem()->data(0, TemplateHandleRole).value<TemplateHandle>();
}

bool TemplateSelector::createInFolder() const
{
	return ui.rbCreateInFolder->isChecked();
}

QString TemplateSelector::creationFolder() const
{
	return ui.lePath->text();
}

void TemplateSelector::on_templatesTree_doubleClicked(const QModelIndex & /*item*/)
{
	QPushButton *pbOk = ui.buttonBox->button(QDialogButtonBox::Ok);
	Q_ASSERT(pbOk);
	if (pbOk->isEnabled())
		accept();
}

void TemplateSelector::hideFolderSelection()
{
	ui.rbCreateInFolder->hide();
	ui.rbCreateInEditor->hide();
	ui.lePath->hide();
    ui.btPath->hide();
}

void TemplateSelector::setCachingDir(const QString &path)
{
    m_cachingDir=path;
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }
}

void TemplateSelector::on_btPath_clicked()
{
	UtilsUi::browse(ui.lePath, tr("Select Target Folder"), "/");
}

void TemplateSelector::checkTargetPath()
{
	bool showWarning = false;
	if (ui.rbCreateInFolder->isChecked()) {
		QDir dir(ui.lePath->text());
		if (dir.exists()) {
			showWarning = !dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files).isEmpty();
		}
	}
	ui.warningIcon->setVisible(showWarning);
	ui.warningText->setVisible(showWarning);
}

void TemplateSelector::showInfo(QTreeWidgetItem *currentItem, QTreeWidgetItem *previousItem)
{
	Q_UNUSED(previousItem)

	QPushButton *pbOk = ui.buttonBox->button(QDialogButtonBox::Ok);
	Q_ASSERT(pbOk);

	QVariant varth = (currentItem) ? currentItem->data(0, TemplateHandleRole) : QVariant();

	if (varth.isValid()) {
		// selected template
		TemplateHandle th = varth.value<TemplateHandle>();

		pbOk->setEnabled(true);
		ui.lbName->setText(orDefault(th.name(), tr("<No Name>")));
		ui.lbDescription->setText(orDefault(th.description(), "<No Description>"));
		ui.lbAuthor->setText(orDefault(th.author(), "<Unknown Author>"));
		ui.lbDate->setText(tr("Date") + ": " + th.date().toString(Qt::ISODate));
		ui.lbVersion->setText(tr("Version") + ": " + th.version());
		ui.lbLicense->setText(tr("License") + ": " + th.license());
		ui.lbAuthorTag->setVisible(true);
		if (previewLabel)
			previewLabel->setScaledPixmap(QPixmap(th.previewImage()));

		if (th.isMultifile()) {
			ui.rbCreateInFolder->setChecked(true);
			ui.rbCreateInEditor->setEnabled(false);
		} else {
			ui.rbCreateInEditor->setEnabled(true);
		}
	} else {
        if(currentItem && currentItem->data(0,UrlRole).isValid()){
            QString path=currentItem->data(0,PathRole).toString();
            QString url=currentItem->data(0,UrlRole).toString();
            QString downloadUrl=currentItem->data(0,DownloadRole).toString();
            if(!downloadUrl.isEmpty()){
                makeRequest(downloadUrl,path,currentItem,true);
            }
        }else{
            AbstractTemplateResource *res = (currentItem) ? (currentItem->data(0, ResourceRole).value<AbstractTemplateResource *>()) : nullptr;
            // if !res the currentItem is invalid
            pbOk->setEnabled(false);
            ui.lbName->setText(res ? res->name() : "");
            ui.lbDescription->setText(res ? res->description() : "");
            ui.lbAuthor->setText("");
            ui.lbDate->setText("");
            ui.lbVersion->setText("");
            ui.lbLicense->setText("");
            ui.lbAuthorTag->setVisible(false);
            if (previewLabel)
                previewLabel->setScaledPixmap(QPixmap());
        }
	}
}

void TemplateSelector::templatesTreeContextMenu(QPoint point)
{
	TemplateHandle th = selectedTemplate();
	if (!th.isValid()) return;

	QMenu menu(this);
	if (th.isEditable()) {
		menu.addAction(tr("Edit Template"), this, SLOT(editTemplate()));
		menu.addAction(tr("Edit Template Info"), this, SLOT(editTemplateInfo()));
		menu.addAction(tr("Remove"), this , SLOT(removeTemplate()));
		menu.addSeparator();
	}
	menu.addAction(tr("Open Template Location"), this, SLOT(openTemplateLocation()));
	menu.exec(ui.templatesTree->mapToGlobal(point));
}

void TemplateSelector::editTemplate()
{
	TemplateHandle th = selectedTemplate();
	if (th.isMultifile()) {
		UtilsUi::txsInformation("Editing of multi-file templates is not supported.\n"
		               "Please open the template location and unzip the\n"
		               "template to edit individual files.");
		return;
	}
	if (!th.isEditable()) {
		UtilsUi::txsCritical(tr("This template cannot be edited."));
		return;
	}
	emit editTemplateRequest(th);
	close();
}

void TemplateSelector::editTemplateInfo()
{
	TemplateHandle th = selectedTemplate();
	if (!th.isEditable()) {
		UtilsUi::txsCritical(tr("This template cannot be edited."));
		return;
	}
	emit editTemplateInfoRequest(th);
	close();
}

void TemplateSelector::removeTemplate()
{
	TemplateHandle th = selectedTemplate();
	if (!th.isEditable()) {
		UtilsUi::txsCritical(tr("This template cannot be edited."));
		return;
	}
	QString fname = th.file();

	if (QMessageBox::question(this, tr("Please Confirm"), tr("Are you sure to delete the following template?") + QString("\n%1").arg(fname)
	                          , QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
		QTreeWidgetItem *currentItem = ui.templatesTree->currentItem();
		if (currentItem) {
			currentItem->parent()->removeChild(currentItem);
		}
		QFile file(fname);
		if (!file.remove()) UtilsUi::txsCritical(tr("You do not have permission to remove this file.") + "\n" + fname);
		QFileInfo fi(fname);
		QFileInfo metafi(fi.dir(), fi.baseName() + ".json");
		if (metafi.exists()) {
			file.setFileName(metafi.absoluteFilePath());
			if (!file.remove()) UtilsUi::txsCritical(tr("You do not have permission to remove this file.") + "\n" + fname);
		}
	}
}

void TemplateSelector::openTemplateLocation()
{
	TemplateHandle th = selectedTemplate();
	QString url = "file:///" + QFileInfo(th.file()).absolutePath();
	if (!QDesktopServices::openUrl(QUrl(url))) {
		UtilsUi::txsCritical(tr("Could not open location:") + QString("\n%1").arg(url));
	}
}

