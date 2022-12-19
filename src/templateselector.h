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

#ifndef Header_Template_Selector
#define Header_Template_Selector

#include "mostQtHeaders.h"
#include "qnetworkaccessmanager.h"
#include "templatemanager.h"
#include "ui_templateselector.h"

// a label to show pixmaps. It shinks the pixmap if necessary to fit it into the available space.
// but it does not magnify it if more space is available
class PreviewLabel : public QLabel
{
	Q_OBJECT

public:
	explicit PreviewLabel(QWidget *parent = 0): QLabel(parent)
	{
		setScaledPixmap(QPixmap());
	}
	void setScaledPixmap(const QPixmap &pm);

protected:
	virtual void resizeEvent(QResizeEvent *event);

private:
	void setPixmapWithResizing(const QPixmap &pm);
	QPixmap currentPixmap;
};


class TemplateSelector : public QDialog
{
	Q_OBJECT

public:
	explicit TemplateSelector(QString name = "", QWidget *parent = 0);
	~TemplateSelector();

	TemplateHandle selectedTemplate() const;
	bool createInFolder() const;
	QString creationFolder() const;
	void addResource(AbstractTemplateResource *res);
    void addOnlineRepository();
	void hideFolderSelection();
    void setCachingDir(const QString &path);

signals:
	void editTemplateRequest(TemplateHandle th);
	void editTemplateInfoRequest(TemplateHandle th);

private slots:
	void showInfo(QTreeWidgetItem *currentItem, QTreeWidgetItem *previousItem);
	void templatesTreeContextMenu(QPoint point);
    void itemExpanded(QTreeWidgetItem *item);
    void onRequestCompleted();

    void acceptResult();

	void on_templatesTree_doubleClicked(const QModelIndex &index);
	void on_btPath_clicked();
	void checkTargetPath();

	void editTemplate();
	void editTemplateInfo();
	void removeTemplate();
	void openTemplateLocation();

private:
	QString orDefault(const QString &val, const QString &defaultIfValEmpty) const
	{
		return (val.isEmpty()) ? defaultIfValEmpty : val;
	}

    void makeRequest(QString url, QString path, QTreeWidgetItem *item=nullptr, bool download=false);
    void saveToCache(const QByteArray &data,const QString &path);
    void onCachedRequestCompleted(const QByteArray &ba,QTreeWidgetItem *rootItem,const QString &url);
    bool inCache(const QString &path);
    QString appendPath(QString base,QString path);

	Ui::templateSelectorDialog ui;
	PreviewLabel *previewLabel;

    QNetworkAccessManager *networkManager;

    QString m_cachingDir;

	static const int TemplateHandleRole;
	static const int ResourceRole;
    static const int UrlRole;
    static const int PathRole;
    static const int DownloadRole;
    static const int PreviewRole;
    static const int TexRole;
    static const int PopulatedRole;
};

#if QT_VERSION_MAJOR<6
Q_DECLARE_METATYPE(QTreeWidgetItem *)
#endif

#endif // TEMPLATESELECTOR_H
