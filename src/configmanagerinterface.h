#ifndef CONFIGMANAGERINTERFACE_H
#define CONFIGMANAGERINTERFACE_H


typedef QMap<QString, QString> StringStringMap;

#define PROPERTY_TYPE_FOREACH_MACRO_SIMPLE(M) \
	M(QVariant, PT_VARIANT) \
	M(int, PT_INT) \
	M(bool, PT_BOOL) \
	M(QString, PT_STRING) \
	M(QStringList, PT_STRINGLIST) \
	M(QDateTime, PT_DATETIME) \
	M(float, PT_FLOAT) \
	M(double, PT_DOUBLE) \
	M(QByteArray, PT_BYTEARRAY) \
	M(QList<QVariant>, PT_LIST)

#define PROPERTY_TYPE_FOREACH_MACRO_COMPLEX(M) \
	M(StringStringMap, PT_MAP_STRING_STRING)

#define PROPERTY_TYPE_FOREACH_MACRO(M) PROPERTY_TYPE_FOREACH_MACRO_SIMPLE(M) PROPERTY_TYPE_FOREACH_MACRO_COMPLEX(M)

#define ENUMERATE_ID(dummy, ID) , ID
enum PropertyType {PT_VOID = 0 PROPERTY_TYPE_FOREACH_MACRO(ENUMERATE_ID) };
#undef ENUMERATE_ID

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QWidget>
#include <QByteArray>

enum LinkOption {
	LO_NONE = 0,
	LO_UPDATE_ALL = 1, //if the property is changed (through the config manager), update all displaying objects
	LO_DIRECT_OVERRIDE = 2 //if one object is changed, update property (if not set, the property is updated if a majority of objects is changed)
};
Q_DECLARE_FLAGS(LinkOptions, LinkOption)


struct ManagedProperty {
	QString name;
	void *storage;
	PropertyType type;
	QVariant def;
	ptrdiff_t widgetOffset;

	ManagedProperty();
#define CONSTRUCTOR(TYPE, dummy) \
	ManagedProperty(TYPE* storage, QVariant def = QVariant(), ptrdiff_t widgetOffset = 0); \
	static ManagedProperty fromValue(TYPE value);
	PROPERTY_TYPE_FOREACH_MACRO(CONSTRUCTOR)
#undef CONSTRUCTOR

	QVariant valueToQVariant() const;
	void valueFromQVariant(const QVariant v);
	void writeToObject(QObject *w) const;
	bool readFromObject(const QObject *w);
	void deallocate();
};


class ConfigManagerInterface
{
public:
	//registers an option with the given name, type and default value, stored at the given pointer
	//this has to be called before the configmanager reads the settings, and the option (*storage) will
	//automatically be read/written from the ini file.
	virtual void registerOption(const QString &name, void *storage, PropertyType type, QVariant def) = 0;
#define VIRTUAL_REGISTER_OPTION(TYPE, dummy) \
	virtual void registerOption(const QString& name, TYPE* storage, QVariant def=QVariant()) = 0;
	PROPERTY_TYPE_FOREACH_MACRO(VIRTUAL_REGISTER_OPTION)
#undef VIRTUAL_REGISTER_OPTION
	//set an option as variant (don't use it in c++, since it is not type-safe)
	virtual void setOption(const QString &name, const QVariant &value) = 0;
	//get an option as variant (don't use it in c++, since it is not type-safe)
	virtual QVariant getOption(const QString &name, const QVariant &defaultValue = QVariant()) const = 0;
	//check if an option exists
	virtual bool existsOption(const QString &name) const = 0;
	//shows the value of an registered option in the passed widget
	//if the dialog containing widget is accepted (and not rejected), the value from the widget will be written to the option
	virtual void linkOptionToDialogWidget(const void *optionStorage, QWidget *widget) = 0;
	//Displays the option in the object.
	//Each option can be linked to several objects;
	//If the object representation changes => (If fullsync => the option and all linked objects are changed
	//                                         If !fullsync => the option is changed to the value of the majority of the objects)
	//Setting a link changes the object value to the current option value
    virtual void linkOptionToObject(const void *optionStorage, QObject *widget, LinkOptions options = nullptr) = 0;

	virtual void updateAllLinkedObjects(const void *optionStorage) = 0;

	virtual QString parseDir(QString s) const = 0;
	virtual QStringList parseDirList(const QString &s) const = 0;
	virtual QString reverseParseDir(QString s) const = 0;
	virtual QString reverseParseDir(const QStringList &s) const = 0;

	static ConfigManagerInterface *getInstance();
};

#define CONFIG_DECLARE_OPTION_WITH_OBJECT(config, type, name, defaultvalue, configname, object) static type name; config->registerOption(configname, &name, defaultvalue); config->linkOptionToObject(&name, object);

#endif // CONFIGMANAGERINTERFACE_H
