#ifndef EXECPROGRAM_H
#define EXECPROGRAM_H

#include "mostQtHeaders.h"

class ExecProgram
{
public:
	// Input parameters
	QString program;
	QStringList arguments;
	QString additionalSearchPaths;
	QString workingDirectory;

	// Output parameters. Only assigned by synchronous execAndWait
	bool normalRun; // If false then program either did not run or crashed
	int exitCode;
	QString standardOutput;
	QString standardError;

	void execAndWait (void);
	void execAndNoWait (QProcess &proc) const;
};

#endif // EXECPROGRAM_H
