#ifndef USERMACRO_H
#define USERMACRO_H

#include "mostQtHeaders.h"

class QLanguageDefinition;
class QLanguageFactory;
class LatexDocument;

class Macro {
public:
	enum SpecialTrigger { ST_NO_TRIGGER = 0,
					   ST_REGEX = 1, ST_TXS_START = 2,
		               ST_NEW_FILE = 4, ST_NEW_FROM_TEMPLATE = 8, ST_LOAD_FILE = 0x10, ST_LOAD_THIS_FILE = 0x20, 
		               ST_FILE_SAVED = 0x40, ST_FILE_CLOSED = 0x80, ST_MASTER_CHANGED = 0x100, 
		               ST_AFTER_TYPESET = 0x200, ST_AFTER_COMMAND_RUN = 0x400
		               };
	Q_DECLARE_FLAGS(SpecialTriggers, SpecialTrigger)
	Macro();
	Macro(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger);
	Macro(const QStringList &fieldList);
	QString name, tag, abbrev;
	QString trigger;
	QRegExp triggerRegex;
	bool triggerLookBehind;
	
	QStringList toStringList() const;
	
	void parseTriggerLanguage(QLanguageFactory *langFactory);
	bool isActiveForTrigger(SpecialTrigger trigger) const;
	bool isActiveForLanguage(QLanguageDefinition *lang) const;
	bool isActiveForFormat(int format) const;
	
	LatexDocument* document;
private:
	void init(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger);
	void initTriggerFormats();

	SpecialTriggers triggers;

	QString triggerLanguage;
	QList<QLanguageDefinition*> triggerLanguages;

	QString triggerFormatsUnprocessed;
	QList<int> triggerFormats;
};

#endif // USERMACRO_H
