#include "usermacro.h"
#include "smallUsefulFunctions.h"
#include "qformatscheme.h"
#include "qlanguagefactory.h"
#include "qdocument.h"

Macro::Macro() : triggerLookBehind(false), document(0) {
}

Macro::Macro(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger):document(0) {
	init(nname, ntag, nabbrev, ntrigger);
}

Macro::Macro(const QStringList &fieldList):document(0) {
	if (fieldList.count() >= 4) {
		init(fieldList[0], fieldList[1], fieldList[2], fieldList[3]);
	}
}

void Macro::init(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger) {
	name = nname;
	tag = ntag;
	abbrev = nabbrev;
	trigger = ntrigger;
	triggerLookBehind = false;
	QString realtrigger = trigger;
	triggers = 0;
	if (realtrigger.trimmed().startsWith("?")) {
		QStringList sl = realtrigger.split("|");
		realtrigger.clear();
		foreach (const QString& x, sl) {
			QString t = x.trimmed();
			if (t == "?txs-start") triggers |= ST_TXS_START;
			else if (t == "?new-file") triggers |= ST_NEW_FILE;
			else if (t == "?new-from-template") triggers |= ST_NEW_FROM_TEMPLATE;
			else if (t == "?load-file") triggers |= ST_LOAD_FILE;
			else if (t == "?load-this-file") triggers |= ST_LOAD_THIS_FILE;
			else if (t == "?save-file") triggers |= ST_FILE_SAVED;
			else if (t == "?close-file") triggers |= ST_FILE_CLOSED;
			else if (t == "?master-changed") triggers |= ST_MASTER_CHANGED;
			else if (t == "?after-typeset") triggers |= ST_AFTER_TYPESET;
			else if (t == "?after-command-run") triggers |= ST_AFTER_COMMAND_RUN;
			else if (realtrigger.isEmpty()) realtrigger = t;
			else realtrigger = realtrigger + "|" + t;
		}
	}
	if (realtrigger.isEmpty()) return;

	triggers |= ST_REGEX;

	int lastLen;
	do {
		lastLen = realtrigger.length();
		if (realtrigger.startsWith("(?language:")) {
			const int langlen = strlen("(?language:");
			int paren = 1, bracket = 0, i=langlen;
			for (; i < realtrigger.length() && paren; i++) {
				switch (realtrigger[i].unicode()) {
				case '(': if (!bracket) paren++; break;
				case ')': if (!bracket) paren--; break;
				case '[': bracket = 1; break;
				case ']': bracket = 0; break;
				case '\\': i++; break;
				}
			}
			triggerLanguage = realtrigger.mid(langlen, i - langlen - 1);
			triggerLanguage.replace("latex", "\\(La\\)TeX");
			realtrigger.remove(0,i);
		}

		if (realtrigger.startsWith("(?highlighted-as:")) {
			int start = realtrigger.indexOf(':') + 1; 
			int closing = realtrigger.indexOf(")");
			triggerFormatsUnprocessed = realtrigger.mid(start, closing - start).replace(',', '|').replace(" ",""); //handle later, when the formats are loaded
			realtrigger.remove(0, closing+1);
		}
		if (realtrigger.startsWith("(?not-highlighted-as:")) {
			int start = realtrigger.indexOf(':') + 1; 
			int closing = realtrigger.indexOf(")");
			triggerFormatExcludesUnprocessed = realtrigger.mid(start, closing - start).replace(',', '|').replace(" ",""); //handle later, when the formats are loaded
			realtrigger.remove(0, closing+1);
		}
		
	} while (lastLen != realtrigger.length());

	if (realtrigger.startsWith("(?<=")) {
		triggerLookBehind = true;
		realtrigger.remove(1,3); //qregexp doesn't support look behind, but we can emulate it by removing the first capture
	}
	triggerRegex = QRegExp("(?:"+realtrigger+")$"); // (?: non capturing)
}

void Macro::initTriggerFormats() {
	QFormatScheme *fs = QDocument::defaultFormatScheme();
	REQUIRE(fs);
	qDebug() << triggerFormatsUnprocessed;
	qDebug() << triggerFormatExcludesUnprocessed;
	foreach (const QString& formatName,	triggerFormatsUnprocessed.split('|')) {
		if (fs->exists(formatName)) {
			triggerFormats << fs->id(formatName);
		}
	}
	triggerFormatsUnprocessed.clear();
	foreach (const QString& formatName,	triggerFormatExcludesUnprocessed.split('|')) {
		if (fs->exists(formatName)) {
			triggerFormatExcludes << fs->id(formatName);
		}
	}
	triggerFormatExcludesUnprocessed.clear();
	
}

QStringList Macro::toStringList() const {
	return QStringList() << name << tag << abbrev << trigger;
}

void Macro::parseTriggerLanguage(QLanguageFactory *langFactory) {
	if (triggerLanguage.isEmpty()) return;
	triggerLanguages.clear();
	QRegExp tempRE(triggerLanguage, Qt::CaseInsensitive);
	foreach (const QString &lang, langFactory->languages()) {
		if (tempRE.exactMatch(lang))
			triggerLanguages << langFactory->languageData(lang).d;
	}
}

bool Macro::isActiveForTrigger(Macro::SpecialTrigger trigger) const {
	return (triggers & trigger);
}

bool Macro::isActiveForLanguage(QLanguageDefinition *lang) const {
	// if no trigger language is specified, the macro is active for all languages.
	return triggerLanguage.isEmpty() || triggerLanguages.contains(lang);
}

bool Macro::isActiveForFormat(int format) const {
	if (!triggerFormatsUnprocessed.isEmpty() || !triggerFormatExcludesUnprocessed.isEmpty()) (const_cast<Macro*>(this))->initTriggerFormats();
	// if no trigger format is specified, the macro is active for all formats.
	qDebug() << "inc" << triggerFormats;
	qDebug() << "exc" << triggerFormatExcludes;
	return (triggerFormats.isEmpty() || triggerFormats.contains(format)) && (!triggerFormatExcludes.contains(format));
}

