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

#include "smallUsefulFunctions.h"

const int TemplateSelector::FileNameRole = Qt::UserRole;


TemplateSelector::TemplateSelector(QString filter, QString name, QWidget *parent, QStringList additionalSearchPaths)
	: QDialog(parent), mFilter(filter), mAdditonalSearchPaths(additionalSearchPaths) {
	setModal(true);
	ui.setupUi(this);
	setWindowTitle(name);
	ui.listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	QAction *act = new QAction(tr("Edit"), this);
	connect(act, SIGNAL(triggered()), SLOT(editTemplate()));
	ui.listWidget->addAction(act);
	act=new QAction(tr("Remove") ,this);
	connect(act, SIGNAL(triggered()), this, SLOT(removeTemplate()));
	ui.listWidget->addAction(act);

	connect(ui.listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), SLOT(showInfo(QListWidgetItem*,QListWidgetItem*)));

	addTemplateFiles();
}

TemplateSelector::~TemplateSelector() {
}

void TemplateSelector::addTemplateFiles() {
	// works for table templates and latex templates
	QRegExp rxTemplate("(^|^.*/)(table)?(template_)?");
	QRegExp rxSuffix(".(tex|js)$");

	QStringList files=findResourceFiles("templates/", mFilter, mAdditonalSearchPaths);

	foreach(const QString &file, files) {
		QString title = file;
		title.replace(rxTemplate, "");
		title.replace(rxSuffix, "");
		QListWidgetItem *item = new QListWidgetItem(title);

		item->setData(FileNameRole, file);
		ui.listWidget->addItem(item);
	}
}

QString TemplateSelector::selectedTemplateFile() const {
	if (ui.listWidget->count() <= 0) return QString();
	if (ui.listWidget->currentItem()) {
		QString f_real = "templates/" + ui.listWidget->currentItem()->data(FileNameRole).toString();
		f_real = findResourceFile(f_real, false, mAdditonalSearchPaths);
		return f_real;
	}
	return QString();
}

void TemplateSelector::on_listWidget_itemDoubleClicked(QListWidgetItem* /*item*/) {
	accept();
}

void TemplateSelector::showInfo(QListWidgetItem *currentItem,QListWidgetItem *previousItem) {
	Q_UNUSED(previousItem);

	QHash<QString, QString> metaData;
	QString fname = selectedTemplateFile();
	if (!fname.isEmpty()) {
		getTemplateMetaData(fname, metaData);
	}

	ui.lbAuthor->setText(metaData["Author"]);
	ui.lbDate->setText(metaData["Date"]);
	ui.lbVersion->setText(metaData["Version"]);
	ui.teDescription->setText(metaData["Description"]);
}

void TemplateSelector::editTemplate() {
	QString fname = selectedTemplateFile();
	if (fname.startsWith(":")) {
		txsCritical(tr("You can not edit built-in templates."));
	} else {
		emit editTemplateRequest(fname);
		close();
	}
}

void TemplateSelector::removeTemplate() {
	QString fname = selectedTemplateFile();
	if (fname.startsWith(":")) {
		txsCritical(tr("You can not edit built-in templates."));
	} else {
		if(QMessageBox::question(this,tr("Please Confirm"), tr("Are you sure to delete the following template?")+QString("\n%1").arg(fname)
								 ,QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes) {
			ui.listWidget->takeItem(ui.listWidget->currentRow());
			QFile file(fname);
			if(!file.remove()) txsCritical(tr("You do not have permission to remove this file."));
		}
	}
}

bool TemplateSelector::getTemplateMetaData(const QString &file, QHash<QString, QString> &metaData) const {
	QString jsonData;

	if (file.endsWith(".tex")) {
		QFile f(file.left(file.length()-3)+"meta");
		if (!f.exists()) return false;
		if (!f.open(QIODevice::ReadOnly)) {
			txsWarning(tr("You do not have read permission to this file:")+QString("\n%1").arg(file));
			return false;
		}
		jsonData = f.readAll();
	} else if (file.endsWith(".js")) {
		QFile f(file);
		if (!f.open(QIODevice::ReadOnly)) {
			txsWarning(tr("You do not have read permission to this file:")+QString("\n%1").arg(file));
			return false;
		}
		jsonData = f.readLine();
		int col = jsonData.indexOf(QRegExp("\\s*var\\s+metaData\\s+=\\s+\\{"));
		qDebug() << jsonData.indexOf(QRegExp("\\s*var\\s+metaData\\s+=\\s+"));
		qDebug() << jsonData.indexOf(QRegExp("\\s*var\\s+metaData\\s+=\\s+\\{"));
		if (col < 0) return false;
		jsonData = jsonData.mid(col);
		QString all = f.readAll();
		jsonData.append(all); // works with minimalJsonParse because it stops after the first top level {}
									  // should check when switching to a real JSON parser. However with this it is
									  // easy to extract var metaData = {}
	}
	return minimalJsonParse(jsonData, metaData);

	/*
	QString line = f.readLine().trimmed();
	while (line.startsWith("//")) {
		int sep = line.indexOf(':');
		QString tag = line.mid(2,sep-2).trimmed().toLower();
		QString content = line.mid(sep+1).trimmed();

		if (metaData.contains(tag)) {
			metaData[tag] = metaData[tag] + ' ' + content;
		} else {
			metaData[tag] = content;
		}
		line = f.readLine().trimmed();
	}
	return true;*/
}
