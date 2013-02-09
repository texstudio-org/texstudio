#ifndef USERMACRO_H
#define USERMACRO_H

class QLanguageDefinition;
class LatexDocument;

struct Macro{
	enum SpecialTrigger { ST_REGEX = 1, ST_TXS_START = 2, 
		               ST_NEW_FILE = 4, ST_NEW_FROM_TEMPLATE = 8, ST_LOAD_FILE = 0x10, ST_LOAD_THIS_FILE = 0x20, 
		               ST_FILE_SAVED = 0x40, ST_FILE_CLOSED = 0x80, ST_MASTER_CHANGED = 0x100, 
		               ST_AFTER_TYPESET = 0x200, ST_AFTER_COMMAND_RUN = 0x400
		               };
	Q_DECLARE_FLAGS(SpecialTriggers, SpecialTrigger)
	
	Macro();
	Macro(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger);
	Macro(const QStringList &fieldList);
	void init(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger);
	QString name, tag, abbrev;
	QString trigger;
	QRegExp triggerRegex;
	bool triggerLookBehind;
	
	QStringList toStringList() const;
	
	QString triggerLanguage;
	QList<QLanguageDefinition*> triggerLanguages;
	SpecialTriggers triggers;	
	
	QString triggerFormatsUnprocessed;
	QList<int> triggerFormats;
	void initTriggerFormats();

	LatexDocument* document;
};

#endif // USERMACRO_H
