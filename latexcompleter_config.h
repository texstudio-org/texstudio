#ifndef LATEXCOMPLETERCONFIG_H
#define LATEXCOMPLETERCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

#include "modifiedQObject.h"

#include "usermacro.h"


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

	QList<Macro> userMacros;

	void setFiles(const QStringList & newFiles);
	const QStringList& getLoadedFiles();

	QString importedCwlBaseDir;
private:
	QStringList files;
};



//implementation lies in latexcompleter.cpp

#endif // LATEXCOMPLETERCONFIG_H
