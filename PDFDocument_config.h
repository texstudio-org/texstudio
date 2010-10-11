#ifndef PDFDOCUMENT_CONFIG_H
#define PDFDOCUMENT_CONFIG_H

#include <QByteArray>
struct PDFDocumentConfig{
	int windowLeft, windowTop;
	int windowWidth, windowHeight;
	QByteArray windowState;

	int dpi;//QApplication::desktop()->logicalDpiX()
	int scaleOption;//kDefault_PreviewScaleOption
	int scale; //kDefault_PreviewScale


	int magnifierSize, magnifierShape;
};

#endif // PDFDOCUMENT_CONFIG_H
