#ifndef CONFIGMANAGERINTERFACE_H
#define CONFIGMANAGERINTERFACE_H

enum PropertyType {PT_VOID = 0, PT_INT, PT_BOOL, PT_STRING, PT_STRINGLIST, PT_DATETIME, PT_DOUBLE};
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QWidget>
class ConfigManagerInterface
{
public:
	//registers an option with the given name, type and default value, stored at the given pointer
	//this has to be called before the configmanager reads the settings, and the option (*storage) will
	//automatically be read/written from the ini file.
	virtual void registerOption(const QString& name, void* storage, PropertyType type, QVariant def) = 0;
	virtual void registerOption(const QString& name, bool* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, int* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QString* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QStringList* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QDateTime* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, double* storage, QVariant def=QVariant()) = 0;

	//shows the value of an registered option in the passed widget
	//if the dialog containing widget is accepted (and not rejected), the value from the widget will be written to the option
	virtual void linkOptionToWidget(const void* optionStorage, QWidget* widget) = 0;


	//put only functions here that are needed in many different places/dialogs and called several times
	virtual QIcon getRealIcon(const QString& icon) const = 0;
};

#endif // CONFIGMANAGERINTERFACE_H
