#ifndef DEBUGLOGGERQT_H
#define DEBUGLOGGERQT_H

#include "mostQtHeaders.h"

#ifdef DEBUG_LOGGER

class DebugLoggerQt
{
public:
	typedef void (*LogCallback)(QtMsgType logLevel, const char *file, unsigned int line, const char *message);

	static void start (LogCallback callback);
	static void stop (void);

private:
	DebugLoggerQt(void);

#ifndef QT_NO_DEBUG
	static void messageHandlerQt5(QtMsgType msgType, const QMessageLogContext &context, const QString &message);
#endif // QT_NO_DEBUG

	static LogCallback m_callback;
};

#endif // DEBUG_LOGGER

#endif // DEBUGLOGGERQT_H
