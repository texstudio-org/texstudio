#ifndef Header_InsertGraphics_Config
#define Header_InsertGraphics_Config

//having the configuration in a single file allows to change it,
//without having a relationship between insertgraphics and configmanager
//so modifying one doesn't lead to a recompilation of the other

#include <QSettings>

class InsertGraphicsConfig
{
public:
	QString file;
	QString includeOptions;
	bool center;
	bool useFigure;
	bool captionBelow;
	QString shortCaption;
	QString caption;
	QString label;
	bool spanTwoCols;
	QString placement;

	void readSettings(QSettings &settings);
	void saveSettings(QSettings &settings);
};


#endif // INSERTGRAPHICS_CONFIG_H
