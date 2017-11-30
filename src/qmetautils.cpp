#include "qmetautils.h"

void QMetaObjectInvokeMethod(QObject *p, const char *signature, const QList<QGenericArgument> &args)
{
	//qDebug("found.");

	// TODO : ask trolltech to provide an overloaded invokeMetaMethod()
	// taking a QList<> instead of nine defaulted args...

	if ( args.isEmpty() )
		QMetaObject::invokeMethod(p, signature);
	else if ( args.count() == 1 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0));
	else if ( args.count() == 2 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1));
	else if ( args.count() == 3 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2));
	else if ( args.count() == 4 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3));
	else if ( args.count() == 5 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4));
	else if ( args.count() == 6 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4),
		                            args.at(5));
	else if ( args.count() == 7 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4),
		                            args.at(5),
		                            args.at(6));
	else if ( args.count() == 8 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4),
		                            args.at(5),
		                            args.at(6),
		                            args.at(7));
	else if ( args.count() == 9 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4),
		                            args.at(5),
		                            args.at(7),
		                            args.at(8));
	else if ( args.count() == 10 )
		QMetaObject::invokeMethod(	p, signature,
		                            args.at(0),
		                            args.at(1),
		                            args.at(2),
		                            args.at(3),
		                            args.at(4),
		                            args.at(5),
		                            args.at(7),
		                            args.at(8),
		                            args.at(9));

}

void QMetaObjectInvokeMethod(QObject *o, const char *signature, const QList<QVariant> &args)
{
	QList<QGenericArgument> temp;
	foreach (const QVariant &a, args)
		temp << QGenericArgument(a.typeName(), a.data());
	QMetaObjectInvokeMethod(o, signature, temp);
}

QByteArray createMethodSignature(const char *methodName, const QList<QVariant> &args)
{
	QByteArray signature = methodName;
	if (args.isEmpty()) signature.append("()");
	else {
		signature.append("(");
		for (int i = 0; i < args.size(); i++) {
			if (i != 0) signature.append(",");
			signature.append(args[i].typeName());
		}
		signature.append(")");
	}
	return signature;
}


ConnectionWrapper::ConnectionWrapper(QObject *parent, QObject *receiver, const char *slot) :
	QObject(parent), realReceiver(receiver), realSlot(slot)
{
}

ConnectionWrapper::ConnectionWrapper(QObject *receiver, const char *slot) :
	QObject(receiver), realReceiver(receiver), realSlot(slot)
{
}

void ConnectionWrapper::activated()
{
	QMetaObjectInvokeMethod(realReceiver, realSlot, args);
}

void connectWithAdditionalArguments(QObject *sender, const char *signal, QObject *receiver, const char *slot, const QList<QVariant> &arguments)
{
	ConnectionWrapper *wrapper = new ConnectionWrapper(receiver, receiver, slot);
	wrapper->args = arguments;
	sender->connect(sender, signal, wrapper, SLOT(activated()));
}
