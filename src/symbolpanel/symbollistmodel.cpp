#include "symbollistmodel.h"
#include "smallUsefulFunctions.h"
#include "qsvgrenderer.h"

/*!
 * A model for providing all the symbols. Specializations can be done using
 * QSortFilterProxyModels. This means that we have to maintain all the relevant
 * information (also usage count and favorites) within the model.
 *
 * This may be a bit heavy and inefficient but does the job so far. It reliefs
 * us from providing extra specialized models for "most used" and "favorites"
 * based on the same data.
 */

SymbolListModel::SymbolListModel(QVariantMap usageCountMap, QStringList favoriteList) :
	iconSizeHint(32)
{
	foreach (const QString &key, usageCountMap.keys()) {
		usageCount.insert(key, usageCountMap.value(key).toInt());
	}
	favoriteIds = favoriteList;
}

void SymbolListModel::load(QString category)
{
	QStringList files;
	files = findResourceFiles("symbols-ng/" + category, "img*.*");
	if (files.isEmpty()) // fallback
		files = findResourceFiles("symbols/" + category, "img*.png");

	QStringList fullNames;
	foreach (const QString &partName, files)
		fullNames << category + "/" + partName;
	if (fullNames.length() == 0) {
		qDebug() << ("No symbols found for category: " + category);
	}

	loadSymbols(category, fullNames);
}

SymbolItem loadSymbolFromSvg(QString fileName)
{
	QFile file(fileName);

	if (!file.open( QIODevice::ReadOnly)) {
		qDebug() << "could not open file";
		return SymbolItem();
	}

	QString errorMsg;
	int errorLine, errorColumn;
	QDomDocument doc("svg");

	if (!doc.setContent( &file, false, &errorMsg, &errorLine, &errorColumn) ) {
		qDebug() << "could not find xml content";
		qDebug() << errorMsg;
		qDebug() << "line is " << errorLine;
		qDebug() << "column is " << errorColumn;
		file.close();
		return SymbolItem();
	}
	file.close();

	// check root element
	QDomElement root = doc.documentElement();
	if ( root.tagName() != "svg" ) {
		qDebug() << "wrong format";
		return SymbolItem();
	}

	SymbolItem item;

	QDomNodeList nl = root.elementsByTagName("title");
	if (!nl.isEmpty()) {
		QDomNode n = nl.at(0);
		item.command = n.toElement().text();
	}
	nl = root.elementsByTagName("desc");
	if (!nl.isEmpty()) {
		QDomNode n = nl.at(0);
		item.packages = n.toElement().attribute("Packages");
	}
	nl = root.elementsByTagName("additionalInfo");

	if (!nl.isEmpty()) {
		QDomNode n = nl.at(0);
		item.unicode = n.toElement().attribute("CommandUnicode");

	}

	item.iconFile = fileName;
	item.icon = QIcon(fileName);
	return item;
}

void SymbolListModel::loadSymbols(const QString &category, const QStringList &fileNames)
{
	for (int i = 0; i < fileNames.size(); ++i) {
		QString iconName = fileNames.at(i);
		QString fileName = findResourceFile("symbols-ng/" + iconName);
		if (fileName.isEmpty())
			fileName = findResourceFile("symbols/" + iconName);

		SymbolItem symbolItem;

		if (fileName.endsWith("svg")) {
			symbolItem = loadSymbolFromSvg(fileName);
		} else {
			QImage img = QImage(fileName);
			symbolItem.command = img.text("Command");
			symbolItem.packages = img.text("Packages");
			symbolItem.unicode = img.text("CommandUnicode");
			symbolItem.iconFile = fileName;
			symbolItem.icon = QIcon(fileName);
		}
		if (!symbolItem.unicode.isEmpty()) {
			// convert to real unicode
			QString helper;
			QStringList listOfChars = symbolItem.unicode.split(",");
			for (int i = 0; i < listOfChars.size(); i++) {
				QString StrCode = listOfChars.value(i, "");
				StrCode = StrCode.mid(2); // Remove U+
				bool ok;
				int code = StrCode.toInt(&ok);
				if (ok)
					helper += QChar(code);
			}
			symbolItem.unicode = helper;

		}

		symbolItem.category = category;
		symbolItem.id = category + '/' + symbolItem.command.mid(1);  // e.g. "greek/alpha"

		symbols.append(symbolItem);
	}
	return;
}

QVariantMap SymbolListModel::usageCountAsQVariantMap() const {
	QVariantMap map;
	foreach (const QString &key, usageCount.keys()) {
		map.insert(key, usageCount.value(key, 0));
	}
	return map;
}

QStringList SymbolListModel::favorites() const
{
	return favoriteIds;
}

int SymbolListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return symbols.count();
}

QVariant SymbolListModel::data(const QModelIndex &index, int role) const
{
	int r = index.row();
	if (r < 0 || r >= symbols.count())
		return QVariant();

	switch (role) {
	case Qt::DisplayRole:
		return QVariant();  // we do only want symbols, so we do not return a text
		//return symbols[r].command;
	case Qt::DecorationRole:
		return getIcon(symbols[r]);
	case Qt::ToolTipRole:
		return getTooltip(symbols[r]);
	case IdRole:
		return symbols[r].id;
	case CommandRole:
		return symbols[r].command;
	case UnicodeRole:
		return symbols[r].unicode;
	case CategoryRole:
		return symbols[r].category;
	case UsageCountRole:
		return usageCount.value(symbols[r].id, 0);
	case FavoriteRole:
		return QVariant(favoriteIds.contains(symbols[r].id));
	}
	return QVariant();
}

void SymbolListModel::incrementUsage(const QString &id)
{
	usageCount.insert(id, usageCount.value(id, 0) + 1);
	for (int i=0; i<symbols.count(); i++) {
		if (symbols[i].id == id) {
#if QT_VERSION > 0x050000
			emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << UsageCountRole));
#else
			emit dataChanged(index(i, 0), index(i, 0));
#endif
			break;
		}
	}
}

void SymbolListModel::addFavorite(const QString &id)
{
	if (!favoriteIds.contains(id)) {
		favoriteIds.append(id);
		for (int i=0; i<symbols.count(); i++) {
			if (symbols[i].id == id) {
#if QT_VERSION > 0x050000
				emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << FavoriteRole));
#else
				emit dataChanged(index(i, 0), index(i, 0));
#endif
				break;
			}
		}
	}
}

void SymbolListModel::removeFavorite(const QString &id)
{
	if (favoriteIds.removeOne(id)) {
		for (int i=0; i<symbols.count(); i++) {
			if (symbols[i].id == id) {
#if QT_VERSION > 0x050000
				emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << FavoriteRole));
#else
				emit dataChanged(index(i, 0), index(i, 0));
#endif
				break;
			}
		}
	}
}

QIcon SymbolListModel::getIcon(const SymbolItem &item) const
{
#if defined( Q_OS_MAC ) && (QT_VERSION >= 0x050500)
	// work-around for another QT/OSX bug
	if(item.iconFile.endsWith(".svg")){
		const int sz = iconSizeHint + 4;
		QSvgRenderer svgRender(item.iconFile);
		QImage img(2*sz, 2*sz, QImage::Format_ARGB32);
		//img.setDevicePixelRatio(2.0);
		img.fill(0x000000000);
		QPainter p(&img);
		QSize svgSize=svgRender.defaultSize()*4;
		if(svgSize.width()>2*sz){
			svgSize.setWidth(2*sz);
			svgSize.setHeight(svgSize.height()*2*sz/svgSize.width());
		}
		svgRender.render(&p,QRectF(QPointF((2.0*sz-svgSize.width())/2,0),svgSize));
		return QIcon(QPixmap::fromImage(img));
	}else{
		return QIcon(item.iconFile);
	}
#else
	//QIcon *icon = new QIcon(item.iconFile);
	//qDebug() << item.command << icon.actualSize(QSize(iconSizeHint, iconSizeHint));
	return item.icon;
#endif
}

QString SymbolListModel::getTooltip(const SymbolItem &item) const
{
	QStringList args, pkgs;

	QString label = item.command;
	label.replace("<", "&lt;");
	label = tr("Command: ") + "<b>" + label + "</b>";

	QRegExp rePkgs("(?:\\[(.*)\\])?\\{(.*)\\}");

	args.clear();
	pkgs.clear();

	if ( rePkgs.indexIn(item.packages) != -1 ) {
		args = rePkgs.cap(1).split(",");
		pkgs = rePkgs.cap(2).split(",");
	}
	if ( pkgs.count() > 0 ) {
		if (pkgs.count() == 1)
			label += "<br>" + tr("Package: ");
		else
			label += "<br>" + tr("Packages: ");

		for ( int j = 0; j < pkgs.count() ; j++ ) {
			if (j > 0) label += "\n";
			if ( j < args.count() && !args[j].isEmpty())
				label = label + "[" + args[j] + "]" + pkgs[j];
			else
				label = label + pkgs[j] ;
		}
	}
	if (!item.unicode.isEmpty())
		label += "<br>" + tr("Unicode Character: ") + item.unicode;
	return label;
}



