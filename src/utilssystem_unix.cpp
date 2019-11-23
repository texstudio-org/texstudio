#include "utilsSystem.h"
#include "utilsUI.h"
#include "execprogram.h"


QString getTerminalCommand()
{
#ifdef Q_OS_MAC
	QString command = "open -a /Applications/Utilities/Terminal.app/";
	return command;
#else // Linux
	// Linux does not have a uniform way to determine the default terminal application

	// gnome
	ExecProgram execGsettings("gsettings get org.gnome.desktop.default-applications.terminal exec", "");
	if (execGsettings.execAndWait()) {
		// "gsettings" terminates with exit code 0 if settings were fetched successfully
		return execGsettings.m_standardOutput.replace('\'', "");
	}

	// fallback
	QStringList fallbacks = QStringList() << "konsole" << "xterm";
	foreach (const QString &fallback, fallbacks) {
		ExecProgram execWhich("which " + fallback, "");
		if (execWhich.execAndWait()) {
			// "which" terminates with exit code 0 if settings were fetched successfully
			return execWhich.m_standardOutput;
		}
	}
	return QString();
#endif
}

bool startTerminalEmulator(const QString &workingDir)
{
	QString command = getTerminalCommand();
	if (command.isEmpty()) {
		UtilsUi::txsCritical("Unable to detect a terminal application.");
		return false;
	}
	QStringList args;
	args = command.split(' ');
	command = args.takeFirst();
#ifdef Q_OS_MAC
	// for Terminal.app to open in a specific path it is not sufficent that the
	// workingDir is set. We have to pass it explicitly as argument.
	args << workingDir;
	return QProcess::startDetached(command, args, workingDir);
#else
	return QProcess::startDetached(command, args, workingDir);
#endif
}
