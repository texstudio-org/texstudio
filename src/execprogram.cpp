#include "execprogram.h"
#include "utilsSystem.h"

ExecProgram::ExecProgram(void) :
#ifdef Q_OS_WIN
	m_winProcModifier(nullptr),
#endif
	m_normalRun(false),
	m_exitCode(-1)
{
}

ExecProgram::ExecProgram(const QString &shellCommandLine, const QString &additionalSearchPaths, const QString &workingDirectory) :
	m_additionalSearchPaths(additionalSearchPaths),
	m_workingDirectory(workingDirectory),
#ifdef Q_OS_WIN
	m_winProcModifier(nullptr),
#endif
	m_normalRun(false),
	m_exitCode(-1)
{
	setProgramAndArguments(shellCommandLine);
}

ExecProgram::ExecProgram(const QString &progName, const QStringList &arguments, const QString &additionalSearchPaths, const QString &workingDirectory) :
	m_program(progName),
	m_arguments(arguments),
	m_additionalSearchPaths(additionalSearchPaths),
	m_workingDirectory(workingDirectory),
#ifdef Q_OS_WIN
	m_winProcModifier(nullptr),
#endif
	m_normalRun(false),
	m_exitCode(-1)
{
}

/*!
 * \brief Basic command-line parser
 * \details Basic command-line parser that splits a command-line into program name and arguments list.
 * The parsed program name and arguments are stored in class member variables.
 * TODO: Improve the parser. We need to add proper quotes processing based on the OS type (UNIX/Win).
 * \param[in] shellCommandLine Shell command line that should be parsed.
 */
void ExecProgram::setProgramAndArguments(const QString &shellCommandLine)
{
	static QRegularExpression rxLeadingSpace("\\s*");
	Q_ASSERT(rxLeadingSpace.isValid());
	static QRegularExpression rxOneToken(
		"("
			"[^[:space:]\"']+|"		// Non-whitespace string without any quotes
			"\"[^\"]*\"|"			// Double-quoted string
			"'[^']*'|"			// Single-quoted string
			"\"[^[:space:]\"]*(?=[^\"]*$)|"	// ERROR: Non-whitespace string starting with a double-quote. No other double-quotes until the end.
			"'[^[:space:]']*(?=[^']*$)"	// ERROR: Non-whitespace string starting with a single-quote. No other single-quotes until the end.
		")+",
		QRegularExpression::DontCaptureOption
	);
	Q_ASSERT(rxOneToken.isValid());

	QStringList tokens;
	int length = shellCommandLine.length();
	int offset = 0;
	for (;;) {
		if (offset >= length) {
			break;
		}
		QRegularExpressionMatch matchLeadingSpace = rxLeadingSpace.match(
			shellCommandLine,
			offset,
			QRegularExpression::NormalMatch,
			QRegularExpression::AnchoredMatchOption
		);
		offset += matchLeadingSpace.capturedLength(0);
		if (offset >= length) {
			break;
		}
		QRegularExpressionMatch matchOneToken = rxOneToken.match(
			shellCommandLine,
			offset,
			QRegularExpression::NormalMatch,
			QRegularExpression::AnchoredMatchOption
		);
		if (matchOneToken.hasMatch() == false) {
			// We should never reach this point
			Q_ASSERT(false);
			break;
		}
		offset += matchOneToken.capturedLength(0);
		QString oneToken = matchOneToken.captured(0);
		oneToken.remove('"').remove('\'');
		tokens.push_back(oneToken);
	}
	if (tokens.isEmpty()) {
		m_program = "";
		m_arguments.clear();
	} else {
		m_program = tokens.front();
		tokens.pop_front();
		m_arguments = tokens;
	}
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
	setWinProcModifier(proc);
	QString pathOrig = pathExtend();
	proc.start(m_program, m_arguments);
	pathSet(pathOrig);
}

bool ExecProgram::execDetached(void) const
{
	bool execResult;

	QString pathOrig = pathExtend();
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
	QProcess proc;
	proc.setProgram(m_program);
	proc.setArguments(m_arguments);
	if (!m_workingDirectory.isEmpty()) {
		proc.setWorkingDirectory(m_workingDirectory);
	}
	setWinProcModifier(proc);
	execResult = proc.startDetached();
#else
	execResult = QProcess::startDetached(m_program, m_arguments, m_workingDirectory);
#endif
	pathSet(pathOrig);
	return execResult;
}

QString ExecProgram::pathExtend(void) const
{
	QChar pathSep = getPathListSeparator();
	QString pathOrig = QString::fromLocal8Bit(qgetenv("PATH"));
	// We add the path from getEnvironmentPath() because it can be extended by shell startup scripts
	QString pathExtended = pathOrig + pathSep + getEnvironmentPath();
	if (!m_additionalSearchPaths.isEmpty()) {
		pathExtended += pathSep + m_additionalSearchPaths;
	}
	pathSet(pathExtended);
	return pathOrig;
}

void ExecProgram::pathSet(const QString &path)
{
	qputenv("PATH", path.toLocal8Bit());
}

void ExecProgram::setWinProcModifier(QProcess &proc) const
{
#ifdef Q_OS_WIN
	if (m_winProcModifier) {
		proc.setCreateProcessArgumentsModifier(m_winProcModifier);
	}
#else
	Q_UNUSED(proc)
#endif
}
