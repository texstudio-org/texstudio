#include "execprogram.h"
#include "utilsSystem.h"

void ExecProgram::execAndWait (void)
{
	QProcess proc;

	execAndNoWait(proc);
	proc.waitForFinished();
	normalRun =
		(proc.error() == QProcess::UnknownError) &&
		(proc.exitStatus() == QProcess::NormalExit);
	exitCode = proc.exitCode();
	standardOutput = proc.readAllStandardOutput();
	standardError = proc.readAllStandardError();
}

void ExecProgram::execAndNoWait (QProcess &proc) const
{
	if (!workingDirectory.isEmpty()) {
		proc.setWorkingDirectory(workingDirectory);
	}
	QChar pathSep = getPathListSeparator();
	QString pathOrig = QString::fromLocal8Bit(qgetenv("PATH"));
	// We add the path from getEnvironmentPath() because it can be extended by shell startup scripts
	QString pathExtended = pathOrig + pathSep + getEnvironmentPath();
	if (!additionalSearchPaths.isEmpty()) {
		pathExtended += pathSep + additionalSearchPaths;
	}
	qputenv("PATH", pathExtended.toLocal8Bit());
	// If there are no arguments specified separately assume that the program name
	// also contains all the arguments (if any)
	if (arguments.isEmpty()) {
		proc.start(program);
	} else {
		proc.start(program, arguments);
	}
	qputenv("PATH", pathOrig.toLocal8Bit());
}
