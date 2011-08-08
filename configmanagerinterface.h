#ifndef CONFIGMANAGERINTERFACE_H
#define CONFIGMANAGERINTERFACE_H

enum PropertyType {PT_VOID = 0, PT_VARIANT, PT_INT, PT_BOOL, PT_STRING, PT_STRINGLIST, PT_DATETIME, PT_DOUBLE, PT_BYTEARRAY, PT_LIST};
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QWidget>
#include <QByteArray>

enum LinkOption{
	LO_NONE = 0,
	LO_UPDATE_ALL = 1, //if the property is changed (through the config manager), update all displaying objects
	LO_DIRECT_OVERRIDE = 2 //if one object is changed, update property (if not set, the property is updated if a majority of objects is changed)
};
Q_DECLARE_FLAGS(LinkOptions, LinkOption);

class ConfigManagerInterface
{
public:
	//registers an option with the given name, type and default value, stored at the given pointer
	//this has to be called before the configmanager reads the settings, and the option (*storage) will
	//automatically be read/written from the ini file.
	virtual void registerOption(const QString& name, void* storage, PropertyType type, QVariant def) = 0;
	virtual void registerOption(const QString& name, QVariant* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, bool* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, int* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QString* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QStringList* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QDateTime* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, double* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QByteArray* storage, QVariant def=QVariant()) = 0;
	virtual void registerOption(const QString& name, QList<QVariant>* storage, QVariant def=QVariant()) = 0;
	virtual bool existsOption(const QString& name) const = 0;
	//shows the value of an registered option in the passed widget
	//if the dialog containing widget is accepted (and not rejected), the value from the widget will be written to the option
	virtual void linkOptionToDialogWidget(const void* optionStorage, QWidget* widget) = 0;
	//Displays the option in the object.
	//Each option can be linked to several objects;
	//If the object representation changes => (If fullsync => the option and all linked objects are changed
	//                                         If !fullsync => the option is changed to the value of the majority of the objects)
	//Setting a link changes the object value to the current option value
	virtual void linkOptionToObject(const void* optionStorage, QObject* widget, LinkOptions options=0) = 0;

	virtual void updateAllLinkedObjects(const void* optionStorage) = 0;
	
	static ConfigManagerInterface* getInstance();
};

#define CONFIG_DECLARE_OPTION_WITH_OBJECT(config, type,name,defaultvalue,configname,object) static type name; config->registerOption(configname, &name, defaultvalue); config->linkOptionToObject(&name, object);

#endif // CONFIGMANAGERINTERFACE_H
