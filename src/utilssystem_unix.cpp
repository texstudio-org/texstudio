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
	ExecProgram execProgram;

	// gnome
	execProgram.program = "gsettings";
	execProgram.arguments << "get" << "org.gnome.desktop.default-applications.terminal" << "exec";
	execProgram.execAndWait();
	if (execProgram.normalRun) {
		return execProgram.standardOutput.replace('\'', "");
	}

	// fallback
	QStringList fallbacks = QStringList() << "konsole" << "xterm";
	execProgram.program = "which";
	foreach (const QString &fallback, fallbacks) {
		execProgram.arguments.clear ();
		execProgram.arguments << fallback;
		execProgram.execAndWait();
		if (execProgram.normalRun) {
			return execProgram.standardOutput;
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
