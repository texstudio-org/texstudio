#ifndef DEBUGLOGGERMAIN_H
#define DEBUGLOGGERMAIN_H

#include "mostQtHeaders.h"

#ifdef DEBUG_LOGGER

#define debugLoggerStart(pathname) DebugLoggerMain::start(pathname)
#define debugLoggerStop() DebugLoggerMain::stop()
#define debugLoggerIsLogging() DebugLoggerMain::isLogging()

#define DLOG_DEBUG(message) DebugLoggerMain::logMessage(QtDebugMsg, __FILE__, __LINE__, message)
#define DLOG_INFO(message) DebugLoggerMain::logMessage(QtInfoMsg, __FILE__, __LINE__, message)
#define DLOG_WARNING(message) DebugLoggerMain::logMessage(QtWarningMsg, __FILE__, __LINE__, message)
#define DLOG_CRITICAL(message) DebugLoggerMain::logMessage(QtCriticalMsg, __FILE__, __LINE__, message)
#define DLOG_FATAL(message) DebugLoggerMain::logMessage(QtFatalMsg, __FILE__, __LINE__, message)

class DebugLoggerMain
{
public:
	static bool start(const QString &pathname);
	static bool stop(void);
	static bool isLogging(void);

	static void logMessage (QtMsgType logLevel, const char *file, unsigned int line, const char *message);
	static void logMessage (QtMsgType logLevel, const char *file, unsigned int line, const QString &message);

private:
	DebugLoggerMain(void);

	static FILE *m_logHandle;
};

#else // DEBUG_LOGGER

#define debugLoggerStart(pathname)
#define debugLoggerStop()
#define debugLoggerIsLogging() false

#define DLOG_DEBUG(message)
#define DLOG_INFO(message)
#define DLOG_WARNING(message)
#define DLOG_CRITICAL(message)
#define DLOG_FATAL(message)

#endif // DEBUG_LOGGER

#endif // DEBUGLOGGERMAIN_H
