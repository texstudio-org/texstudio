#ifndef EXECPROGRAM_H
#define EXECPROGRAM_H

#include "mostQtHeaders.h"

class ExecProgram
{
public:
	ExecProgram(void);
	ExecProgram(const QString &progNameAndArguments, const QString &additionalSearchPaths, const QString &workingDirectory = QString());
	ExecProgram(const QString &progName, const QStringList &arguments, const QString &additionalSearchPaths = QString(), const QString &workingDirectory = QString());

	bool execAndWait(void);
	void execAndNoWait(QProcess &proc) const;

	// Input parameters
	QString m_program;
	QStringList m_arguments;
	QString m_additionalSearchPaths;
	QString m_workingDirectory;

	// Output parameters. Only assigned by synchronous execAndWait
	bool m_normalRun; // If false then program either did not run or crashed
	int m_exitCode;
	QString m_standardOutput;
	QString m_standardError;
};

#endif // EXECPROGRAM_H
