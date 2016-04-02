/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "symbolgridwidget.h"
#include "icondelegate.h"
#include "smallUsefulFunctions.h"
#include "qsvgrenderer.h"

/*! \class SymbolGridWidget
 *
 * side panel widget which displays graphical symbols pertaining to one category.
 * clicking on them inserts the corresponsing latex-command into the active editor
 *
 * The actual symbols are read-in from a list of available image.
 * The actual latex-commands are embedded in the image-files.
 * svg and png images can be used. Principally svg-images should be preferred, since they are scalable.
 * However Qt does not offer a complete SVG-renderbackend which causes display errors in some symbols which are to be reoplaced with png version.
 */

/*!
 * \brief constructor
 *
 * Set-up the widget. Symbol are not yet loaded as loading is time consuming with 1000+ symbols.
 * \param parent Parent-Widget
 * \param SymbolList Category of symbols which are to be loaderd from images-ng/ * SymbolList *
 * \param Map Usage info of the symbols for most-used category
 */

SymbolGridWidget :: SymbolGridWidget(QWidget *parent, QString SymbolList, QVariantMap *Map) : QTableWidget(parent)
{
	listOfItems.clear();
	setItemDelegate(new IconDelegate(this));
	setShowGrid(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setIconSize(QSize(32, 32));
	setSelectionMode(QAbstractItemView::SingleSelection);
	mLoadedSymbols = false;
	mSymbolList = SymbolList;
	mMap = Map;
	countOfItems = 0;
	if (SymbolList.startsWith("!")) {
		loadSymbols(QStringList(), mMap);
	}
	qreal minLightness = 0.5;
	if (viewport()->palette().base().color().lightnessF() < minLightness) {
		// workaound: svgs are black glyphs on transparent backgound
		// if the widget background is too dark they cannot be read so we enforce a minimum lightness
		// Note: ideally one would not change the background, but the color of the svg dynamically, so
		// that the symbol would be rendered in text color. But that does not seem to be possible.
		QPalette p = viewport()->palette();
		QColor bc = p.base().color();
		p.setColor(QPalette::Base, QColor::fromHslF(bc.hslHueF(), bc.hslSaturationF(), minLightness, bc.alphaF()));
		viewport()->setPalette(p);
	}
}
/*!
 * \brief destructor
 */
SymbolGridWidget::~SymbolGridWidget()
{
	foreach (QTableWidgetItem *elem, listOfItems)
		delete(elem);
	listOfItems.clear();
}

/*!
 * \brief set symbol size within grid-display
 * \param size size in pixels
 */
void SymbolGridWidget::setSymbolSize(int size)
{
	setIconSize(QSize(size, size));
	if (mLoadedSymbols)
		adaptTable();
}

/*!
 * \brief latex-command of current symbol
 * \return latex-command of current symbol as Qstring
 */
QString SymbolGridWidget::getCurrentSymbol()
{
	QTableWidgetItem *cur = currentItem();
	if (!cur) return QString();
	return cur->data(Qt::UserRole + 2).toString();
}

/*!
 * \brief load symbols
 *
 * Loads all symbols from disk.
 * It searches images-ng, then images and prefers svg over png.
 * The actual latex-command is extrated from the image-file.
 * \param fileNames list of all symbol-filenames
 * \param Map usage statitics for most-used category
 */
void SymbolGridWidget::loadSymbols(const QStringList &fileNames, QVariantMap *Map)
{
	mLoadedSymbols = true;
	foreach (QTableWidgetItem *elem, listOfItems) {
		takeItem(row(elem), column(elem));
		delete(elem);
	}
	listOfItems.clear();
	setColumnCount(4);
	const int sz = iconSize().width() + 4;
	int rows = fileNames.isEmpty() ? 3 : (fileNames.size() / 4 + 1);
	setRowCount(rows);
	for (int j = 0; j < rows; ++j) setRowHeight(j, sz);
	for (int j = 0; j < 4; ++j) setColumnWidth(j, sz);
	int cols = columnCount();

	countOfItems = fileNames.size();

	for (int i = 0; i < fileNames.size(); ++i) {
		QString iconName = fileNames.at(i);
		QString fileName = findResourceFile("symbols-ng/" + iconName);
		if (fileName.isEmpty())
			fileName = findResourceFile("symbols/" + iconName);
		QTableWidgetItem *item = new QTableWidgetItem();
		QString Command, text, UniCode;

		if (fileName.endsWith("svg")) {
			QFile file( fileName );

			if ( !file.open( QIODevice::ReadOnly ) ) {
				qDebug() << "could not open file";
				continue;
			}

			QString errorMsg;
			int errorLine, errorColumn;
			QDomDocument doc( "svg" );

			if ( !doc.setContent( &file, false, &errorMsg, &errorLine, &errorColumn) ) {
				qDebug() << "could not find xml content";
				qDebug() << errorMsg;
				qDebug() << "line is " << errorLine;
				qDebug() << "column is " << errorColumn;
				file.close();
				continue;
			}
			file.close();

			// check root element
			QDomElement root = doc.documentElement();
			if ( root.tagName() != "svg" ) {
				qDebug() << "wrong format";
				continue;
			}

			QDomNodeList nl = root.elementsByTagName("title");
			if (!nl.isEmpty()) {
				QDomNode n = nl.at(0);
				Command = n.toElement().text();
			}
			nl = root.elementsByTagName("desc");
			if (!nl.isEmpty()) {
				QDomNode n = nl.at(0);
				text = n.toElement().attribute("Packages");
			}
			nl = root.elementsByTagName("additionalInfo");
			if (!nl.isEmpty()) {
				QDomNode n = nl.at(0);
				UniCode = n.toElement().attribute("CommandUnicode");

			}
		} else {
			QImage img = QImage(fileName);
			Command = img.text("Command");
			text = img.text("Packages");
			UniCode = img.text("CommandUnicode");
		}
		if (!UniCode.isEmpty()) {
			// convert to real unicode
			QString helper;
			QStringList listOfChars = UniCode.split(",");
			for (int i = 0; i < listOfChars.size(); i++) {
				QString StrCode = listOfChars.value(i, "");
				StrCode = StrCode.mid(2); // Remove U+
				bool ok;
				int code = StrCode.toInt(&ok);
				if (ok)
					helper += QChar(code);
            }
			UniCode = helper;

		}
#if defined( Q_OS_MAC ) && (QT_VERSION >= 0x050500)
        // work-around for another QT/OSX bug
        if(fileName.endsWith(".svg")){
            QSvgRenderer svgRender(fileName);
            QImage img(2*sz,2*sz,QImage::Format_ARGB32);
            //img.setDevicePixelRatio(2.0);
            img.fill(0x000000000);
            QPainter p(&img);
            QSize svgSize=svgRender.defaultSize()*4;
            if(svgSize.width()>2*sz){
                svgSize.setWidth(2*sz);
                svgSize.setHeight(svgSize.height()*2*sz/svgSize.width());
            }
            svgRender.render(&p,QRectF(QPointF((2.0*sz-svgSize.width())/2,0),svgSize));
            item->setIcon(QIcon(QPixmap::fromImage(img)));
        }else{
            item->setIcon(QIcon(fileName));
        }
#else
		item->setIcon(QIcon(fileName));
#endif
		item->setText(Command);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if (Map) {
			item->setData(Qt::UserRole, Map->value(iconName, 0).toInt());
			Map->insert(Command, 0);
		} else item->setData(Qt::UserRole, 0);
		item->setData(Qt::UserRole + 2, iconName);
		if (!UniCode.isEmpty())
			item->setData(Qt::UserRole + 4, UniCode);
		QString label;
		QStringList args, pkgs;

		Command.replace("<", "&lt;");
		label = tr("Command: ") + "<b>" + Command + "</b>";

		QRegExp rePkgs("(?:\\[(.*)\\])?\\{(.*)\\}");

		args.clear();
		pkgs.clear();

		if ( rePkgs.indexIn(text) != -1 ) {
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
		if (!UniCode.isEmpty())
			label += "<br>" + tr("Unicode Character: ") + UniCode;
		item->setToolTip(label);
		setItem(i / cols, i % cols, item);
		listOfItems << item;
	}
}

/*!
 * \brief resize widget according to external size changes
 */
void SymbolGridWidget::resizeEvent ( QResizeEvent *event )
{
	if (!mLoadedSymbols) {
		QStringList files;
		if (!mSymbolList.isEmpty() && !mSymbolList.startsWith("!")) {
			files = findResourceFiles("symbols-ng/" + mSymbolList, "img*.*");
			if (files.isEmpty()) // fallback
				files = findResourceFiles("symbols/" + mSymbolList, "img*.png");
		}

		QStringList fullNames;
		foreach (const QString &partName, files)
			fullNames << mSymbolList + "/" + partName;

		loadSymbols(fullNames, mMap);
	}
	QTableWidget::resizeEvent(event);
	adaptTable();
}

void SymbolGridWidget::adaptTable()
{
	int numberOfColumns = columnCount();
	for (int i = 0; i < rowCount()*columnCount(); i++) {
		//delete(item(i/numberOfColumns,i%numberOfColumns));
		takeItem(i / numberOfColumns, i % numberOfColumns);
	}

	const int sz = iconSize().width() + 4;
	// add items with adapted number of columns
	//numberOfColumns=event->size().width()/sz;
	numberOfColumns = qMax(1, width() / sz);
	//	qDebug("1.5");
	setColumnCount(numberOfColumns);
	setRowCount(countOfItems / numberOfColumns + 1);
	for (int j = 0; j < countOfItems / numberOfColumns + 1; ++j) setRowHeight(j, sz);
	for (int j = 0; j < numberOfColumns; ++j) setColumnWidth(j, sz);

	//	qDebug(qPrintable(QString("2:%1").arg((int)this)));
	for (int i = 0; i < listOfItems.size(); ++i) {
		//	qDebug(qPrintable(QString("%1:%2 %3").arg(listOfItems[i]->text()).arg(listOfItems[i]->column()).arg((int)listOfItems[i]->tableWidget())));
		if (!listOfItems[i]->tableWidget()) //the items aren't properly removed if the number of rows changes or the number of cols decrease (latter only if the resizeEvent is propagated to the super class) TODO: fix this correctly
			setItem(i / numberOfColumns, i % numberOfColumns, listOfItems[i]);
	}
	//qDebug("3");
}
/*!
 * \brief set-up most used page
 *
 * Set up symbolgridwidget as most-used symbol page
 * \param ulist list of symbols
 */
void SymbolGridWidget::SetUserPage(usercodelist ulist)
{
	foreach (QTableWidgetItem *elem, listOfItems) {
		takeItem(row(elem), column(elem));
	}
	listOfItems.clear();
	int numberOfColumns = columnCount();
	//setColumnCount(numberOfColumns);
	setRowCount(12 / numberOfColumns);

	for (int i = 0; i < qMin(12, ulist.count()); i++) {
		QTableWidgetItem *item = ulist.at(i);
		setItem(i / numberOfColumns, i % numberOfColumns, item);
		listOfItems << item;
	}
	countOfItems = listOfItems.count();
}

