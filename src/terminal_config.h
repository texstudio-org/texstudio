#ifndef Header_Terminal_Config
#define Header_Terminal_Config
#include <QString>
#include <QFont>
#include <QApplication>
#include <QStringList>

class InternalTerminalConfig
{
public:
#ifdef INTERNAL_TERMINAL
	// terminal
	QString terminalColorScheme;
	QString terminalFontFamily;
	int terminalFontSize;
	QString terminalShell;

	void initDefaults(const QStringList& xf){
#ifdef Q_OS_WIN32
	if (terminalFontFamily.isEmpty()) {
		if (xf.contains("Consolas", Qt::CaseInsensitive)) terminalFontFamily = "Consolas";
		else if (xf.contains("Courier New", Qt::CaseInsensitive)) terminalFontFamily = "Courier New";
		else terminalFontFamily = qApp->font().family();
	}
	if (terminalFontSize == -1) terminalFontSize = 10;
#else
	if (terminalFontFamily.isEmpty()) {
		if (xf.contains("DejaVu Sans Mono", Qt::CaseInsensitive)) terminalFontFamily = "DejaVu Sans Mono";
		else if (xf.contains("Lucida Sans Typewriter", Qt::CaseInsensitive)) terminalFontFamily = "Lucida Sans Typewriter";
		else terminalFontFamily = qApp->font().family();
	}
	if (terminalFontSize == -1) terminalFontSize = qApp->font().pointSize();
#endif
	}

#endif
};

#endif // TERMINAL_CONFIG_H

