# abbrevs package
# Matthew Bertucci 2022/06/20 for v1.4

#include:moredefs
#include:slemph

\nospacelist#*
\newabbrev{cmd}{initial%text}#d
\newabbrev{cmd}{initial%text}[subsequent%text]#d
\newname{cmd}{initial%text}#d
\newname{cmd}{initial%text}[subsequent%text]#d
\newbook{cmd}{initial%text}#d
\newbook{cmd}{initial%text}[subsequent%text]#d
\newwork{cmd}{bib key}{initial%text}#d
\newwork{cmd}{bib key}{initial%text}[subsequent%text]#d
\PM
\AM
\BC
\AD
\acromake{csname}{initial text%text}{final text%text}
\ACRcnta#*
\ACRcntb#*
\AcromakePageref#*
\ResetAbbrevs{category list}#*
\NewAbbrevCategory{category name}#*
\TMFontAll#*
\TMHookAll#*
\TMResetAll#*
\TMFontGeneric#*
\TMFontName#*
\TMFontBook#*
\TMFontWork#*
\TMHookGeneric#*
\TMHookName#*
\TMHookBook#*
\TMHookWork#*
\TMResetGeneric#*
\TMResetName#*
\TMResetBook#*
\TMResetWork#*
\NewUserAbbrevDefiner{cmd}{category}#*d
\NewUserAbbrevDefiner{cmd}{category}[definer]#*d
\TMDefineAbbrevStandard{cmd}{initial}#*
\TMDefineAbbrevStandard{cmd}{initial}[subsequent]#*
\TMInitialSuffix#*
\TMSubsequentSuffix#*
\DateMark{arg}#*
\ifTMInhibitSwitching#*
\TMInhibitSwitchingtrue#*
\TMInhibitSwitchingfalse#*
\ifTMAlwaysLong#*
\TMAlwaysLongtrue#*
\TMAlwaysLongfalse#*

# not in main documentation
\DateMarkSize#*
\TMAcromakeDefiner{category}{csname}{acronym}{fulltext}#*
\TMAcromakeSecondarySuffix#*
\TMCurrentMacro#*
\TMCurrentMacroRootname#*
\TMHookAcromake#*
\TMHookAcromakeHook#*
\TMNewAbbrevAcromake{csname-root}{csname-suffix}{category}{body}#*
\TMNewAbbrevPlain{cmd}{category}{body}#*
\TMNewAbbrevSwitcher{definer}{category}{csname}{initial}{subsequent}#*
\TMNewAbbrevSwitcherAcromake{definer}{category}{csname}{initial}{subsequent}#*