#ifndef GRAMMARCHECK_CONFIG_H
#define GRAMMARCHECK_CONFIG_H

#include "QVariant"

class GrammarCheckerConfig
{
public:
	bool longRangeRepetitionCheck;
	int maxRepetitionDelta;
	
	QString wordlistsDir;
	
	//LanguageTool	
	QString languageToolURL;
	bool languageToolAutorun;
	QString languageToolPath, languageToolJavaPath;
	QString languageToolIgnoredRules;
};

Q_DECLARE_METATYPE(GrammarCheckerConfig)

#endif // GRAMMARCHECK_CONFIG_H
