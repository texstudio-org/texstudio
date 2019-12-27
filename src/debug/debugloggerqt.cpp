#include "debugloggerqt.h"

#ifdef DEBUG_LOGGER

#ifndef QT_NO_DEBUG
#if QT_VERSION >= 0x050200
#include <QLoggingCategory>
#endif
#endif // QT_NO_DEBUG

DebugLoggerQt::LogCallback DebugLoggerQt::m_callback = nullptr;

void DebugLoggerQt::start(LogCallback callback)
{
	m_callback = callback;
#ifndef QT_NO_DEBUG
	qInstallMessageHandler(messageHandlerQt5);
#if QT_VERSION >= 0x050200
	QLoggingCategory::setFilterRules("*=true");
#endif
#endif // QT_NO_DEBUG
}

void DebugLoggerQt::stop(void)
{
#ifndef QT_NO_DEBUG
	qInstallMessageHandler(nullptr);
#endif // QT_NO_DEBUG
	m_callback = nullptr;
}

#ifndef QT_NO_DEBUG

void DebugLoggerQt::messageHandlerQt5(QtMsgType msgType, const QMessageLogContext &context, const QString &message)
{
	m_callback (msgType, context.file, context.line, message.toLocal8Bit().constData());
}


#endif // QT_NO_DEBUG

#endif // DEBUG_LOGGER
