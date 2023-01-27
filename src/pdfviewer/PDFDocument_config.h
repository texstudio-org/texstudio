#ifndef Header_PDF_Document_Config
#define Header_PDF_Document_Config

#include <QByteArray>
#include <QString>
struct PDFDocumentConfig {
	bool autoHideToolbars;
	int windowLeft, windowTop;
	int windowWidth, windowHeight;
	bool windowMaximized;
	QByteArray windowState;
	bool toolbarVisible;
	bool annotationPanelVisible;

	int cacheSizeMB;
	int loadStrategy;
	int renderBackend;
    int limitThreadNumber;

	int dpi;
	int scaleOption;
	int scale;
	bool disableHorizontalScrollingForFitToTextWidth;

	double zoomStepFactor;

    int magnifierSize;
    enum MagnifierShape {Rectangle,Circle};
    MagnifierShape magnifierShape;
	bool magnifierShadow;
	bool magnifierBorder;

	int laserPointerSize;
	QString laserPointerColor; // hex rgb

	QString syncFileMask;
	QString paperColor; // hex rgb
	QString highlightColor; // hex rgba, e.g. #FFFF003F
	int highlightDuration;

//live options
	int editTool;
	bool continuous, singlepagestep;
	bool followFromCursor, followFromScroll, syncViews;
	bool invertColors;
	bool grayscale;
	int gridx, gridy, pageOffset;
};

#endif // PDFDOCUMENT_CONFIG_H
