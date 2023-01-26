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
	m_darkMode(false)
{
	foreach (const QString &key, usageCountMap.keys()) {
		usageCount.insert(key, usageCountMap.value(key).toInt());
	}
	favoriteIds = favoriteList;
}
/*!
 * \brief find and load all symbols of a given category
 * \param category
 */
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
/*!
 * \brief extract meta data from SVG file and add the file directly as QIcon
 * \param fileName
 * \return
 */
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
		QString pkg = n.toElement().attribute("Packages");
		if (!pkg.isEmpty() && pkg != "")
			item.packages = pkg;
		QString cmdUnicode = n.toElement().attribute("CommandUnicode");
		if (!cmdUnicode.isEmpty() && cmdUnicode!="")
			item.unicode = cmdUnicode;
	}

	item.iconFile = fileName;
	item.icon = QIcon(fileName);
	return item;
}
/*!
 * \brief load symbols from files
 * png is inverted in dark mode.
 * Symbols are taken from symbols-ng, directory symbols is used as fall-back.
 * meta data is extracted from png/svg files.
 * \param category add symbols to given category
 * \param fileNames list of file names
 */
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
				int code = StrCode.toInt(&ok, 16);
				if (ok) {
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
					helper += QChar::fromUcs4(code);
#else
					if (code < 0x10000) {
						helper += QChar(code); // single utf-16
					} else if (code <= 0x10FFFF) {
						helper += QChar((code >> 10) + 0xD7C0); // high surrogate, 1st utf-16
						helper += QChar((code & 0x3FF) + 0xDC00); // low surrogate, 2nd utf-16
					}
#endif
				}
			}
			symbolItem.unicode = helper;
		}

		symbolItem.category = category;
		symbolItem.id = category + '/' + symbolItem.command.mid(1);  // e.g. "greek/alpha"

		symbols.append(symbolItem);
	}
	return;
}
/*!
 * \brief generate a QVariantMap of symbol ids/usage count.
 * Is used for saving info in configuration.
 * \return map
 */
QVariantMap SymbolListModel::usageCountAsQVariantMap() const {
	QVariantMap map;
	foreach (const QString &key, usageCount.keys()) {
		map.insert(key, usageCount.value(key, 0));
	}
	return map;
}
/*!
 * \brief return ids of favourites
 * \return
 */
QStringList SymbolListModel::favorites() const
{
	return favoriteIds;
}
/*!
 * \brief gives number of symbols
 * \param parent
 * \return number of symbols
 */
int SymbolListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return symbols.count();
}
/*!
 * \brief provide model data for list view
 * \param index
 * \param role
 * \return GUI data
 */
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
/*!
 * \brief increment usage count of symbol id
 * \param id
 */
void SymbolListModel::incrementUsage(const QString &id)
{
	usageCount.insert(id, usageCount.value(id, 0) + 1);
	for (int i=0; i<symbols.count(); i++) {
		if (symbols[i].id == id) {

			emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << UsageCountRole));

			break;
		}
	}
}
/*!
 * \brief activate dark mode
 * This mode basically inverts icon colors (black to white)
 * \param active true -> activate mode
 */
void SymbolListModel::setDarkmode(bool active)
{
	m_darkMode=active;
}
/*!
 * \brief add symbol with id to favourite list
 * \param id  symbol id
 */
void SymbolListModel::addFavorite(const QString &id)
{
	if (!favoriteIds.contains(id)) {
		favoriteIds.append(id);
		for (int i=0; i<symbols.count(); i++) {
			if (symbols[i].id == id) {
				emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << FavoriteRole));

				emit favoritesChanged();
				break;
			}
		}
	}
}
/*!
 * \brief remove symbol with id from favourite list
 * \param id symbol id
 */
void SymbolListModel::removeFavorite(const QString &id)
{
	if (favoriteIds.removeOne(id)) {
		for (int i=0; i<symbols.count(); i++) {
			if (symbols[i].id == id) {
				emit dataChanged(index(i, 0), index(i, 0), (QVector<int>() << FavoriteRole));

				emit favoritesChanged();
				break;
			}
		}
	}
}
/*!
 * \brief return the icon for a symbol
 * This icon is manipulated in darkmode to be inverted (SVG only)
 * \param item
 * \return icon
 */
QIcon SymbolListModel::getIcon(const SymbolItem &item) const
{
#if (defined( Q_OS_MAC ) && (QT_VERSION < QT_VERSION_CHECK(5,14,0))) || defined( MXE )
    bool use_fallback=true;
#else
    bool use_fallback=false;
#endif
    // render SVG explicitely in darkMode and as a work-around for OSX bug
    if(m_darkMode || use_fallback){
        if(item.iconFile.endsWith(".svg")){
            QSvgRenderer svgRender(item.iconFile);
            QSize svgSize=svgRender.defaultSize()*4;
            QImage img(svgSize.width(), svgSize.height(), QImage::Format_ARGB32);
            QPainter p(&img);
            img.fill(0x000000000);
            svgRender.render(&p);
            if(m_darkMode)
                img.invertPixels(QImage::InvertRgb);
            return QIcon(QPixmap::fromImage(img));
        }else{
            if(m_darkMode){
                QImage img(item.iconFile);
                img.invertPixels(QImage::InvertRgb);
                return QIcon(QPixmap::fromImage(img));
            } else{
                return item.icon;
            }
        }
    }else{
        return item.icon;
    }
}
/*!
 * \brief get tooltip text for symbolitem item
 * \param item
 * \return tooltip text
 */
QString SymbolListModel::getTooltip(const SymbolItem &item) const
{
	QStringList args, pkgs;

	QString label = item.command.toHtmlEscaped();
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
		label += "<br>" + tr("Unicode Character: ") + item.unicode.toHtmlEscaped();
	return label;
}



