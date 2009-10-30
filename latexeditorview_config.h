#ifndef LATEXEDITORVIEWCONFIG_H
#define LATEXEDITORVIEWCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

class LatexEditorViewConfig
{
public:
	bool wordwrap, parenmatch;
	bool autoindent, weakindent;
	int showlinemultiples;
	bool folding, showlinestate, showcursorstate, realtimeChecking;	
	bool inlineSpellChecking, inlineCitationChecking, inlineReferenceChecking;
	QFont editorFont;
	bool displayModifyTime;
	bool closeSearchAndReplace;
	bool useLineForSearch;

	void readSettings(QSettings& settings);
	void saveSettings(QSettings& settings);
private:
};

#endif
