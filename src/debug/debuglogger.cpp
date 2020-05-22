#include "debuglogger.h"
#include <inttypes.h>

#ifdef DEBUG_LOGGER

#ifndef QT_NO_DEBUG
#if QT_VERSION >= 0x050200
#include <QLoggingCategory>
#endif
#endif // QT_NO_DEBUG

FILE * DebugLogger::m_logHandle = nullptr;

bool DebugLogger::start(const QString &pathname)
{
	if (isLogging()) {
		return false;
	}
	if ((m_logHandle = fopen(pathname.toLocal8Bit().constData(), "a")) == nullptr) {
		return false;
	}
#ifndef QT_NO_DEBUG
	qInstallMessageHandler(qMessageHandler);
#if QT_VERSION >= 0x050200
	QLoggingCategory::setFilterRules("*=true");
#endif
#endif // QT_NO_DEBUG
	return true;
}

bool DebugLogger::stop(void)
{
	if (isLogging() == false) {
		return false;
	}
#ifndef QT_NO_DEBUG
	qInstallMessageHandler(nullptr);
#endif // QT_NO_DEBUG
	fclose(m_logHandle);
	m_logHandle = nullptr;
	return true;
}

bool DebugLogger::isLogging(void)
{
	return (m_logHandle != nullptr);
}

void DebugLogger::logMessage (QtMsgType msgType, const char *file, unsigned int line, const char *message)
{
	const char * levelName;

	if (isLogging() == false) {
		return;
	}
	switch (msgType) {
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
		"[%s][%lld,0x%p][%s:%u][%s]: %s\n",
		QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toLocal8Bit().constData(),
		static_cast<long long int>(QCoreApplication::applicationPid()),
		QThread::currentThreadId(),
		file ? file : "???",
		line,
		levelName,
		message
	);
	if (msgType == QtFatalMsg) {
		fflush(nullptr);
		abort();
	}
}

void DebugLogger::logMessage (QtMsgType msgType, const char *file, unsigned int line, const QString &message)
{
	logMessage(msgType, file, line, message.toLocal8Bit().constData());
}

#ifndef QT_NO_DEBUG

void DebugLogger::qMessageHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &message)
{
	logMessage (msgType, context.file, context.line, message.toLocal8Bit().constData());
}

#endif // QT_NO_DEBUG

#endif // DEBUG_LOGGER
