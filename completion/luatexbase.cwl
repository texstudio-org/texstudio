# luatexbase package
# Matthew Bertucci 8/14/2021 for v1.3

#include:luatex
#include:ctablestack

\CatcodeTableIniTeX#*
\CatcodeTableString#*
\CatcodeTableLaTeX#*
\CatcodeTableLaTeXAtLetter#*
\CatcodeTableOther#*
\CatcodeTableExpl#*
\SetCatcodeRange#*
\BeginCatcodeRegime{catcode table}#*
\EndCatcodeRegime#*
\PushCatcodeTableNumStack#*
\PopCatcodeTableNumStack#*
\newluatexcatcodetable#*
\setluatexcatcodetable#*
\RequireLuaModule{file}#*
\RequireLuaModule{file}[info]#*
\newluatexattribute#*
\setluatexattribute#*
\unsetluatexattribute#*
\luatexattributedef#*
\luatexcatcodetable#*
\luatexluaescapestring#*
\luatexlatelua#*
\luatexoutputbox#*
\luatexscantextokens#*