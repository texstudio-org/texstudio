#ifndef Header_QMetaUtils
#define Header_QMetaUtils

#include "modifiedQObject.h"
#include "QList"
#include "QVariant"
#include "QByteArray"
#include "QGenericArgument"


void QMetaObjectInvokeMethod(QObject *o, const char *signature, const QList<QGenericArgument> &args);
void QMetaObjectInvokeMethod(QObject *o, const char *signature, const QList<QVariant> &args);
QByteArray createMethodSignature(const char *methodName, const QList<QVariant> &args);


class ConnectionWrapper : public QObject
{
	Q_OBJECT

public:
	explicit ConnectionWrapper(QObject *parent, QObject *receiver, const char *slot);
	explicit ConnectionWrapper(QObject *parentAndReceiver, const char *slot);

	QObject *realReceiver;
	const char *realSlot;
	QList<QVariant> args;

public slots:
	void activated();
};


void connectWithAdditionalArguments(QObject *sender, const char *signal, QObject *receiver, const char *slot, const QList<QVariant> &arguments);

#endif // QMETAUTILS_H
