#ifndef CONFIGMANAGERINTERFACE_H
#define CONFIGMANAGERINTERFACE_H

enum PropertyType {PT_VOID = 0, PT_INT, PT_BOOL, PT_STRING, PT_STRINGLIST, PT_DATETIME};
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
class ConfigManagerInterface
{
public:
	virtual void registerOption(const QString& name, void* storage, PropertyType type, QVariant def) = 0;
	virtual void registerOption(const QString& name, bool* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, int* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QString* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QStringList* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QDateTime* storage, QVariant def=QVariant()) = 0;
};

#endif // CONFIGMANAGERINTERFACE_H
