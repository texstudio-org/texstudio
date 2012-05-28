#ifndef LATEXCOMPLETERCONFIG_H
#define LATEXCOMPLETERCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

#include "modifiedQObject.h"

class QLanguageDefinition;

struct Macro{
	enum SpecialTrigger { ST_TXS_START = 1};
	Q_DECLARE_FLAGS(SpecialTriggers, SpecialTrigger)
	
	Macro();
	Macro(const QString& nname, const QString& ntag, const QString& nabbrev, const QString& ntrigger);
	QString name, tag, abbrev;
	QString trigger;
	QRegExp triggerRegex;
	bool triggerLookBehind;
	
	
	QString triggerLanguage;
	QList<QLanguageDefinition*> triggerLanguages;
	SpecialTriggers triggers;
};


class LatexCompleterConfig
{
public:
	bool enabled; //auto completion enabled (manual completion e.g ctrl+space can always be used)
	enum CaseSensitive {CCS_CASE_INSENSITIVE, CCS_CASE_SENSITIVE, CCS_FIRST_CHARACTER_CASE_SENSITIVE};
	CaseSensitive caseSensitive; 
	bool completeCommonPrefix; //auto tab press	
	bool eowCompletes; //if a EOW character key is pressed, the current word is completed and the character added
	bool tooltipHelp; // enable ToolTip-Help during completion
	bool usePlaceholders;
	int tabRelFontSizePercent;
	enum PreferedCompletionTab {CPC_TYPICAL,CPC_MOSTUSED,CPC_ALL};
	PreferedCompletionTab preferedCompletionTab;
	QStringList words;
	QMultiMap<uint,QPair<int,int> > usage;

	QList<Macro> userMacro;

	void setFiles(const QStringList & newFiles);
	const QStringList& getLoadedFiles();

	QString importedCwlBaseDir;
private:
	QStringList files;
};



//implementation lies in latexcompleter.cpp

#endif // LATEXCOMPLETERCONFIG_H
