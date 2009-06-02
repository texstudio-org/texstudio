#ifndef LATEXCOMPLETERCONFIG_H
#define LATEXCOMPLETERCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

class LatexCompleterConfig
{
public:
	bool enabled;
	enum CaseSensitive {CCS_CASE_INSENSITIVE, CCS_CASE_SENSITIVE, CCS_FIRST_CHARACTER_CASE_SENSITIVE};
	CaseSensitive caseSensitive; 
	bool completeCommonPrefix; //auto tab press	
	QStringList words;
	void loadFiles(const QStringList & newFiles);
	const QStringList& getLoadedFiles();
private:
	QStringList files;
};

//implementation lies in latexcompleter.cpp

#endif // LATEXCOMPLETERCONFIG_H
