#ifndef GRAMMARCHECK_CONFIG_H
#define GRAMMARCHECK_CONFIG_H

#include "QVariant"

class GrammarCheckerConfig
{
public:
	bool longRangeRepetitionCheck;
	int maxRepetitionDelta;
	int maxRepetitionLongRangeDelta, maxRepetitionLongRangeMinWordLength;
	bool badWordCheck;
	
	QString wordlistsDir;
	
	//LanguageTool	
	QString languageToolURL;
	bool languageToolAutorun;
	QString languageToolPath, languageToolJavaPath;
	QString languageToolIgnoredRules;
	
	QString specialIds1, specialIds2, specialIds3, specialIds4; 
};

Q_DECLARE_METATYPE(GrammarCheckerConfig)

#endif // GRAMMARCHECK_CONFIG_H
