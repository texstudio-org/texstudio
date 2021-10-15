#ifndef Header_PDF_Document_Config
#define Header_PDF_Document_Config

#include <QByteArray>
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
    enum MagnifierShape {Rect,CircleWithShadow,Circle};
    MagnifierShape magnifierShape;
	bool magnifierBorder;

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
	int gridx, gridy;
};

#endif // PDFDOCUMENT_CONFIG_H
