#ifndef Header_ExecProgram
#define Header_ExecProgram

#include "mostQtHeaders.h"

class ExecProgram
{
public:
	ExecProgram(void);
	ExecProgram(const QString &shellCommandLine, const QString &additionalSearchPaths, const QString &workingDirectory = QString());
	ExecProgram(const QString &progName, const QStringList &arguments, const QString &additionalSearchPaths = QString(), const QString &workingDirectory = QString());

	bool execAndWait(void);
	void execAndNoWait(QProcess &proc) const;
	bool execDetached(void) const;

	// Input parameters
	QString m_program;
	QStringList m_arguments;
	QString m_additionalSearchPaths;
	QString m_workingDirectory;
#ifdef Q_OS_WIN
	QProcess::CreateProcessArgumentModifier m_winProcModifier;
#endif

	// Output parameters. Only assigned by synchronous execAndWait
	bool m_normalRun; // If false then program either did not run or crashed
	int m_exitCode;
	QString m_standardOutput;
	QString m_standardError;

private:
	void setProgramAndArguments(const QString &progNameAndArguments);
	QString pathExtend(void) const;
	static void pathSet(const QString &path);
	void setWinProcModifier(QProcess &proc) const;
};

#endif // EXECPROGRAM_H
