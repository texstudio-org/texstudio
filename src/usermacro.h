#ifndef Header_UserMacro
#define Header_UserMacro

#include "mostQtHeaders.h"

class QLanguageDefinition;
class QLanguageFactory;
class LatexDocument;


class Macro
{
public:
	enum SpecialTrigger { ST_NO_TRIGGER = 0,
	                      ST_REGEX = 1, ST_TXS_START = 2,
	                      ST_NEW_FILE = 4, ST_NEW_FROM_TEMPLATE = 8, ST_LOAD_FILE = 0x10, ST_LOAD_THIS_FILE = 0x20,
	                      ST_FILE_SAVED = 0x40, ST_FILE_CLOSED = 0x80, ST_MASTER_CHANGED = 0x100,
	                      ST_AFTER_TYPESET = 0x200, ST_AFTER_COMMAND_RUN = 0x400
	                    };
	enum Type { Snippet, Environment, Script };

	Q_DECLARE_FLAGS(SpecialTriggers, SpecialTrigger)
	Macro();
	Macro(const QString &nname, const Macro::Type ntype, const QString &ntag, const QString &nabbrev, const QString &ntrigger);
	Macro(const QString &nname, const QString &typedTag, const QString &nabbrev=QString(), const QString &ntrigger=QString());
	Macro(const QStringList &fieldList);

	static Macro fromTypedTag(const QString &typedTag);

    QString name, abbrev,description,menu;
	Type type;
	QString trigger;
    QRegularExpression triggerRegex;
	bool triggerLookBehind;

	QStringList toStringList() const;

	QString snippet() const;
	QString script() const;
    QString shortcut() const;

    bool isEmpty() const;

    void setShortcut(const QString &sc);
    void setTrigger(const QString &newTrigger);

	QString typedTag() const;
    void setTypedTag(const QString &m_tag);
	static QString parseTypedTag(QString typedTag, Macro::Type &retType);

	void parseTriggerLanguage(QLanguageFactory *langFactory);
	bool isActiveForTrigger(SpecialTrigger trigger) const;
	bool isActiveForLanguage(QLanguageDefinition *lang) const;
	bool isActiveForFormat(int format) const;

    bool load(const QString &fileName);
    bool loadFromText(const QString &text);
    bool save(const QString &fileName) const;

	LatexDocument *document;

private:
	void init(const QString &nname, Macro::Type ntype, const QString &ntag, const QString &nabbrev, const QString &ntrigger);
	void initTriggerFormats();

	QString tag;
	SpecialTriggers triggers;

	QString triggerLanguage;
	QList<QLanguageDefinition *> triggerLanguages;

	QString triggerFormatsUnprocessed;
	QList<int> triggerFormats;
	QString triggerFormatExcludesUnprocessed;
	QList<int> triggerFormatExcludes;

    QString m_shortcut;
};

Q_DECLARE_METATYPE(Macro);

class MacroExecContext {
public:
	MacroExecContext() { triggerId = Macro::ST_NO_TRIGGER; }
	MacroExecContext(int triggerType) { this->triggerId = triggerType; }
	MacroExecContext(int triggerType, QStringList triggerMatches) { this->triggerId = triggerType; this->triggerMatches = triggerMatches; }

	int triggerId;
	QStringList triggerMatches;
};

#endif // USERMACRO_H
