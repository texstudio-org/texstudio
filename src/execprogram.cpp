#include "execprogram.h"
#include "utilsSystem.h"

ExecProgram::ExecProgram(void) :
	m_normalRun(false),
	m_exitCode(-1)
{
}

ExecProgram::ExecProgram(const QString &progNameAndArguments, const QString &additionalSearchPaths, const QString &workingDirectory) :
	m_program(progNameAndArguments),
	m_additionalSearchPaths(additionalSearchPaths),
	m_workingDirectory(workingDirectory),
	m_normalRun(false),
	m_exitCode(-1)
{
}

ExecProgram::ExecProgram(const QString &progName, const QStringList &arguments, const QString &additionalSearchPaths, const QString &workingDirectory) :
	m_program(progName),
	m_arguments(arguments),
	m_additionalSearchPaths(additionalSearchPaths),
	m_workingDirectory(workingDirectory),
	m_normalRun(false),
	m_exitCode(-1)
{
}

bool ExecProgram::execAndWait(void)
{
	QProcess proc;

	execAndNoWait(proc);
	proc.waitForFinished();
	m_normalRun =
		(proc.error() == QProcess::UnknownError) &&
		(proc.exitStatus() == QProcess::NormalExit);
	m_exitCode = proc.exitCode();
	m_standardOutput = proc.readAllStandardOutput();
	m_standardError = proc.readAllStandardError();
	return m_normalRun && (m_exitCode == 0);
}

void ExecProgram::execAndNoWait(QProcess &proc) const
{
	if (!m_workingDirectory.isEmpty()) {
		proc.setWorkingDirectory(m_workingDirectory);
	}
	QChar pathSep = getPathListSeparator();
	QString pathOrig = QString::fromLocal8Bit(qgetenv("PATH"));
	// We add the path from getEnvironmentPath() because it can be extended by shell startup scripts
	QString pathExtended = pathOrig + pathSep + getEnvironmentPath();
	if (!m_additionalSearchPaths.isEmpty()) {
		pathExtended += pathSep + m_additionalSearchPaths;
	}
	qputenv("PATH", pathExtended.toLocal8Bit());
	// If there are no arguments specified separately assume that the program name
	// also contains all the arguments (if any)
    proc.start(m_program, m_arguments);

	qputenv("PATH", pathOrig.toLocal8Bit());
}
