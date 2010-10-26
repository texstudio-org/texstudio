#ifndef LATEXEDITORVIEWCONFIG_H
#define LATEXEDITORVIEWCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

class LatexEditorViewConfig
{
public:
	bool wordwrap, hardwordwrap, parenmatch, parenComplete;
	bool autoindent, weakindent;
	bool indentWithSpaces;
	bool showWhitespace;
	int tabStop;
	int showlinemultiples;
	bool folding, showlinestate, showcursorstate, realtimeChecking;	
	bool inlineSpellChecking, inlineCitationChecking, inlineReferenceChecking, inlineSyntaxChecking;
	QString fontFamily;
	int lineWidth;
	int fontSize;
	bool displayModifyTime;
	bool closeSearchAndReplace;
	bool useLineForSearch;
	static QString translateEditOperation(int key);
	static QList<int> possibleEditOperations();
	bool mouseWheelZoom;
	bool hackDisableFixedPitch, hackDisableWidthCache;

private:
};

#endif
