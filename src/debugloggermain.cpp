#include "debugloggermain.h"
#include "debugloggerqt.h"
#include <inttypes.h>

#ifdef DEBUG_LOGGER

FILE * DebugLoggerMain::m_logHandle = nullptr;

bool DebugLoggerMain::start(const QString &pathname)
{
	if (isLogging()) {
		return false;
	}
	if ((m_logHandle = fopen(pathname.toLocal8Bit().constData(), "a")) == nullptr) {
		return false;
	}
	DebugLoggerQt::start(logMessage);
	return true;
}

bool DebugLoggerMain::stop(void)
{
	if (isLogging() == false) {
		return false;
	}
	DebugLoggerQt::stop();
	fclose(m_logHandle);
	m_logHandle = nullptr;
	return true;
}

bool DebugLoggerMain::isLogging(void)
{
	return (m_logHandle != nullptr);
}

void DebugLoggerMain::logMessage (QtMsgType logLevel, const char *file, unsigned int line, const char *message)
{
	const char * levelName;

	if (isLogging() == false) {
		return;
	}
	switch (logLevel) {
	case QtDebugMsg:
		levelName = "DEBUG";
		break;
	case QtInfoMsg:
		levelName = "INFO";
		break;
	case QtWarningMsg:
		levelName = "WARNING";
		break;
	case QtCriticalMsg:
		levelName = "CRITICAL";
		break;
	case QtFatalMsg:
		levelName = "FATAL";
		break;
	default:
		levelName = "UNKNOWN";
		break;
	}
	fprintf (
		m_logHandle,
		"[%s][%lld][%s:%u][%s]: %s\n",
		QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toLocal8Bit().constData(),
		static_cast<long long int>(QCoreApplication::applicationPid()),
		file ? file : "???",
		line,
		levelName,
		message
	);
	if (logLevel == QtFatalMsg) {
		fflush(nullptr);
		abort();
	}
}

void DebugLoggerMain::logMessage (QtMsgType logLevel, const char *file, unsigned int line, const QString &message)
{
	logMessage(logLevel, file, line, message.toLocal8Bit().constData());
}

#endif // DEBUG_LOGGER
