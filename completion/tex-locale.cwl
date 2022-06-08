# tex-locale package
# Matthew Bertucci 2022/01/22 for v1.0

#include:etoolbox
#include:xfor
#include:tracklang
#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:texosquery
#include:fontenc

#keyvals:\usepackage/tex-locale#c
main=%<tag%>
other={%<tag list%>}
symbols=#textcomp,fontawesome,none
support=#none,auto,babel,polyglossia,cjk
fontenc=#none,auto,%<encoding%>
inputenc=#none,auto,%<encoding%>
datetime=#false,iso,text,num,locale
iso
date=#full,long,medium,short
time=#full,long,medium,short
timedate#true,false
currency=#official,unofficial,sym,tex
#endkeyvals

#ifOption:symbols=fontawesome
#include:fontawesome
#endif

#ifOption:support=babel
#include:babel
#endif
#ifOption:support=polyglossia
#include:polyglossia
#endif
#ifOption:support=cjk
#include:CJK
#endif

#ifOption:fontenc=T1
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
#endif

#ifOption:inputenc=auto
#include:inputenc
#endif
#ifOption:inputenc=utf8
#include:inputenc
#endif
#ifOption:inputenc=utf8x
#include:inputenc
#include:ucs
#endif

#ifOption:datetime=iso
#include:datetime2
#endif
#ifOption:datetime=text
#include:datetime2
#endif
#ifOption:datetime=num
#include:datetime2
#endif
#ifOption:datetime=numeric
#include:datetime2
#endif
#ifOption:iso
#include:datetime2
#endif

### 1 Introduction ###

## 1.1 Using the package without the shell escape ##
\LocaleQueryFile
\LocaleStyQueryFile

## 1.2 Encoding ##
\localeprequery
\localepostquery

### 2 Generic Use ###

\LocaleMain
\LocaleOther
\selectlocale{locale}

## 2.1 General Information ##
\LocaleOSname
\LocaleOSversion
\LocaleOSarch
\LocaleOScodeset
\LocaleQueryCodesetParam
\LocaleOStag
\LocaleNowStamp
\LocaleMainFile
\LocaleFileMod

## 2.2 Attributes ##
\LocaleSetAttribute{label}{attribute}{value}
\LocaleGetAttribute{label}{attribute}
\LocaleSetDialectAttribute{dialect}{attribute}{value}
\LocaleGetDialectAttribute{dialect}{attribute}
\LocaleSetRegionAttribute{region code}{attribute}{value}
\LocaleGetRegionAttribute{region code}{attribute}
\LocaleSetCurrencyAttribute{currency code}{attribute}{value}
\LocaleGetCurrencyAttribute{currency code}{attribute}
\localeshowattribute{label}{attribute}
\localeshowdialectattribute{dialect}{attribute}
\localeshowregionattribute{region code}{attribute}
\localeshowcurrencyattribute{currency code}{attribute}
\LocaleAddToAttributeList{label}{attribute}{item}
\LocaleXpAddToAttributeList{label}{attribute}{item}
\LocaleIfInAttributeList{label}{attribute}{item}{true}{false}
\LocaleIfXpInAttributeList{label}{attribute}{item}{true}{false}
\LocaleForEachInAttributeList{label}{attribute}{cmd}{body}#d
\LocaleAddToDialectAttributeList{label}{attribute}{item}
\LocaleXpAddToDialectAttributeList{label}{attribute}{item}
\LocaleIfInDialectAttributeList{label}{attribute}{item}{true}{false}
\LocaleIfXpInDialectAttributeList{label}{attribute}{item}{true}{false}
\LocaleForEachInDialectAttributeList{label}{attribute}{cmd}{body}#d
\LocaleAddToRegionAttributeList{label}{attribute}{item}
\LocaleXpAddToRegionAttributeList{label}{attribute}{item}
\LocaleIfInRegionAttributeList{label}{attribute}{item}{true}{false}
\LocaleIfXpInRegionAttributeList{label}{attribute}{item}{true}{false}
\LocaleForEachInRegionAttributeList{label}{attribute}{cmd}{body}#d
\LocaleAddToCurrencyAttributeList{label}{attribute}{item}
\LocaleXpAddToCurrencyAttributeList{label}{attribute}{item}
\LocaleIfInCurrencyAttributeList{label}{attribute}{item}{true}{false}
\LocaleIfXpInCurrencyAttributeList{label}{attribute}{item}{true}{false}
\LocaleForEachInCurrencyAttributeList{label}{attribute}{cmd}{body}#d

## 2.3 Patterns ##
\LocaleGetDialectAttribute{dialect}{attribute}
\localenumfmt{pattern}{decimal}
\localenumfmtneg{text}
\localenumfmtzero{text}
\localenumfmtpos{text}
\localeint{value}
\localedec{decimal}
\localecur{decimal}
\localeper{decimal}
\LocaleIfDateTimePatternsSupported{true}{false}
\LocaleDateTimeInfo
\LocaleApplyDateTimePattern{dialect}{attribute}{data}

## 2.4 Locale Information ##
\LocaleMainDialect
\LocaleMainRegion
\LocaleLanguageTag{dialect}
\LocaleLanguageName{dialect}
\LocaleLanguageNativeName{dialect}
\LocaleRegionName{dialect}
\LocaleRegionNativeName{dialect}
\LocaleVariantName{dialect}
\LocaleVariantNativeName{dialect}
\LocaleIfHasLanguageName{dialect}{true}{false}
\LocaleIfHasRegionName{dialect}{true}{false}
\LocaleIfHasVariantName{dialect}{true}{false}

## 2.5 Dates and Times ##
\localedatetimefmt{date-time text}
\LocaleFullDate{dialect}
\LocaleLongDate{dialect}
\LocaleMediumDate{dialect}
\LocaleShortDate{dialect}
\dtmMondayIndex
\dtmTuesdayIndex
\dtmWednesdayIndex
\dtmThursdayIndex
\dtmFridayIndex
\dtmSaturdayIndex
\dtmSundayIndex
\LocaleDayName{dialect}{index}
\LocaleShortDayName{dialect}{index}
\LocaleStandaloneDayName{dialect}{index}
\LocaleStandaloneShortDayName{dialect}{index}
\LocaleFirstDayIndex{dialect}
\LocaleDayIndexFromZeroMonToOneSun{index}
\LocaleDayIndexFromZeroMonToOneMon{index}
\LocaleDayIndexFromOneSunToZeroMon{index}
\LocaleDayIndexFromOneMonToZeroMon{index}
\LocaleDayIndexFromRegion{dialect}{index}
\LocaleDayIndexToRegion{dialect}{index}
\LocaleMonthName{dialect}{index}
\LocaleShortMonthName{dialect}{index}
\LocaleStandaloneMonthName{dialect}{index}
\LocaleStandaloneShortMonthName{dialect}{index}
\LocaleFullTime{dialect}
\LocaleLongTime{dialect}
\LocaleMediumTime{dialect}
\LocaleShortTime{dialect}
\LocaleFullDateTime{dialect}
\LocaleLongDateTime{dialect}
\LocaleMediumDateTime{dialect}
\LocaleShortDateTime{dialect}

## 2.6 Numbers ##
\LocaleNumericGroupSep{dialect}
\LocaleIfNumericUsesGroup{dialect}{true}{false}
\LocaleNumericDecimalSep{dialect}
\LocaleNumericMonetarySep{dialect}
\LocaleNumericExponent{dialect}
\LocaleNumericPercent{dialect}
\LocaleNumericPermill{dialect}
\LocaleCurrencyLabel{dialect}
\LocaleCurrencyRegionalLabel{dialect}
\LocaleCurrencySymbol{dialect}
\LocaleCurrencyTeXSymbol{dialect}

## 2.7 Current Locale ##
\CurrentLocaleLanguageName
\CurrentLocaleLanguageNativeName
\CurrentLocaleRegionName
\CurrentLocaleRegionNativeName
\CurrentLocaleVariantName
\CurrentLocaleVariantNativeName
\CurrentLocaleFirstDayIndex
\CurrentLocaleDayIndexFromRegion{index}
\CurrentLocaleDayName{index}
\CurrentLocaleShortDayName{index}
\CurrentLocaleStandaloneDayName{index}
\CurrentLocaleStandaloneShortDayName{index}
\CurrentLocaleMonthName{index}
\CurrentLocaleShortMonthName{index}
\CurrentLocaleStandaloneMonthName{index}
\CurrentLocaleStandaloneShortMonthName{index}
\CurrentLocaleDate
\localedatechoice{full}{long}{medium}{short}
\CurrentLocaleTime
\localetimechoice{full}{long}{medium}{short}
\CurrentLocaleDateTime
\CurrentLocaleFullDate
\CurrentLocaleLongDate
\CurrentLocaleMediumDate
\CurrentLocaleShortDate
\CurrentLocaleFullTime
\CurrentLocaleLongTime
\CurrentLocaleMediumTime
\CurrentLocaleShortTime
\CurrentLocaleFullDateTime
\CurrentLocaleLongDateTime
\CurrentLocaleMediumDateTime
\CurrentLocaleShortDateTime
\CurrentLocaleCurrency
\localecurrchoice{label}{regional}{symbol}{TeX}
\CurrentLocaleNumericGroupSep
\CurrentLocaleIfNumericUsesGroup{true}{false}
\CurrentLocaleDecimalSep
\CurrentLocaleMonetarySep
\CurrentLocaleExponent
\CurrentLocalePercent
\CurrentLocalePermill
\CurrentLocaleIntegerPattern
\CurrentLocaleDecimalPattern
\CurrentLocaleCurrencyPattern
\CurrentLocalePercentPattern
\CurrentLocaleApplyDateTimePattern

### 3 LaTeX Use ###
\LocaleSupportPackageCase{babel}{polyglossia}{neither}

### miscellaneous ###
\LocaleAppToAttribute{label}{attribute}{value}#*
\LocaleAppToCurrencyAttribute{currency code}{attribute}{value}#*
\LocaleAppToDialectAttribute{dialect}{attribute}{value}#*
\LocaleAppToRegionAttribute{region code}{attribute}{value}#*
\LocaleGetAttributeOrDefValue{label}{attribute}{default}#*
\LocaleGetCurrencyAttributeOrDefValue{currency code}{attribute}{default}#*
\LocaleGetDialectAttributeOrDefValue{dialect}{attribute}{default}#*
\LocaleGetRegionAttributeOrDefValue{region code}{attribute}{default}#*
\LocaleIfAttributeEqCsName{label}{attribute}{csname}{true}{false}#*
\LocaleIfAttributeEqCs{label}{attribute}{cmd}{true}{false}#*
\LocaleIfAttributeEqNum{label}{attribute}{num}{true}{false}#*
\LocaleIfCurrencyAttributeEqCsName{currency code}{attribute}{csname}{true}{false}#*
\LocaleIfCurrencyAttributeEqCs{currency code}{attribute}{cmd}{true}{false}#*
\LocaleIfCurrencyAttributeEqNum{currency code}{attribute}{num}{true}{false}#*
\LocaleIfDialectAttributeEqCsName{dialect}{attribute}{csname}{true}{false}#*
\LocaleIfDialectAttributeEqCs{dialect}{attribute}{cmd}{true}{false}#*
\LocaleIfDialectAttributeEqNum{dialect}{attribute}{num}{true}{false}#*
\LocaleIfHasAttribute{label}{attribute}{true}{false}#*
\LocaleIfHasCurrencyAttribute{currency code}{attribute}{true}{false}#*
\LocaleIfHasCurrencyNonEmptyAttribute{currency code}{attribute}{true}{false}#*
\LocaleIfHasDialectAttribute{dialect}{attribute}{true}{false}#*
\LocaleIfHasDialectNonEmptyAttribute{dialect}{attribute}{true}{false}#*
\LocaleIfHasNonEmptyAttribute{label}{attribute}{true}{false}#*
\LocaleIfHasRegionAttribute{region code}{attribute}{true}{false}#*
\LocaleIfHasRegionNonEmptyAttribute{region code}{attribute}{true}{false}#*
\LocaleIfRegionAttributeEqCsName{region code}{attribute}{csname}{true}{false}#*
\LocaleIfRegionAttributeEqCs{region code}{attribute}{cmd}{true}{false}#*
\LocaleIfRegionAttributeEqNum{region code}{attribute}{num}{true}{false}#*
\LocaleIfSameAttributeValues{label}{attribute1}{attribute2}{true}{false}#*
\LocaleIfSameCurrencyAttributeValues{currency code}{attribute1}{attribute2}{true}{false}#*
\LocaleIfSameDialectAttributeValues{dialect}{attribute1}{attribute2}{true}{false}#*
\LocaleIfSameRegionAttributeValues{region code}{attribute1}{attribute2}{true}{false}#*
\LocaleLetAttribute{label}{attribute}{cmd}#*
\LocaleLetCurrencyAttribute{currency code}{attribute}{cmd}#*
\LocaleLetDialectAttribute{dialect}{attribute}{cmd}#*
\LocaleLetRegionAttribute{region code}{attribute}{cmd}#*
\LocaleProvideAttribute{label}{attribute}{value}#*
\LocaleProvideCurrencyAttribute{currency code}{attribute}{value}#*
\LocaleProvideDialectAttribute{dialect}{attribute}{value}#*
\LocaleProvideRegionAttribute{region code}{attribute}{value}#*
\LocaleXpAppToAttribute{label}{attribute}{value}#*
\LocaleXpAppToCurrencyAttribute{currency code}{attribute}{value}#*
\LocaleXpAppToDialectAttribute{dialect}{attribute}{value}#*
\LocaleXpAppToRegionAttribute{region code}{attribute}{value}#*
\localenopolypunct{arg}#*
\texosqueryfmtpatEEEE{index}#*
\texosqueryfmtpatEEE{index}#*
\texosqueryfmtpatLLLL{index}#*
\texosqueryfmtpatLLL{index}#*
\texosqueryfmtpatMMMM{index}#*
\texosqueryfmtpatMMM{index}#*
\texosquerytimezonefmt{arg}#*
