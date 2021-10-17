#ifndef Header_GrammarCheck_Config
#define Header_GrammarCheck_Config

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
	QString languageToolPath, languageToolArguments, languageToolJavaPath;
	QString languageToolIgnoredRules;

	QString specialIds1, specialIds2, specialIds3, specialIds4;

    QString appDir,configDir;
};

Q_DECLARE_METATYPE(GrammarCheckerConfig)

#endif // GRAMMARCHECK_CONFIG_H
