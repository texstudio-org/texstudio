#ifndef PDFDOCUMENT_CONFIG_H
#define PDFDOCUMENT_CONFIG_H

#include <QByteArray>
struct PDFDocumentConfig{
	int windowLeft, windowTop;
	int windowWidth, windowHeight;
	bool windowMaximized;
	QByteArray windowState;

	int dpi;
	int scaleOption;
	int scale;


	int magnifierSize, magnifierShape;
	bool magnifierBorder;



	QString syncFileMask;


//live options
	bool continuous,singlepagestep;
	bool followFromCursor, followFromScroll, syncViews;
	int gridx,gridy;
};

#endif // PDFDOCUMENT_CONFIG_H
