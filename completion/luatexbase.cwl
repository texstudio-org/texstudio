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
\SetCatcodeRange{start}{end}{catcode}#*
\BeginCatcodeRegime %<<catcode table>%>#*
\EndCatcodeRegime#*
\PushCatcodeTableNumStack#*
\PopCatcodeTableNumStack#*
\newluatexcatcodetable{catcodetable%cmd}#*d
\setluatexcatcodetable#*
\RequireLuaModule{file}#*
\RequireLuaModule{file}[info]#*
\newluatexattribute%<<16-bit number>%>=%<32-bit number>%>#*
\setluatexattribute{attribute}{value}#*
\unsetluatexattribute{attribute}#*
\luatexattributedef%<\csname%>=%<<16-bit number>%>#*
\luatexattributedef{cmd}#Sd
\luatexcatcodetable%<<15-bit number>%>#*
\luatexluaescapestring{TeX code}#*
\luatexlatelua{lua code}#*
\luatexoutputbox = %<<integer>%>#*
\luatexscantextokens#*
