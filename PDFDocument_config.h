#ifndef PDFDOCUMENT_CONFIG_H
#define PDFDOCUMENT_CONFIG_H

#include <QByteArray>
struct PDFDocumentConfig{
	int windowLeft, windowTop;
	int windowWidth, windowHeight;
	QByteArray windowState;

	int dpi;
	int scaleOption;
	int scale;


	int magnifierSize, magnifierShape;


	bool followFromCursor, followFromScroll;
};

#endif // PDFDOCUMENT_CONFIG_H
