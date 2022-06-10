# tracklang package
# Matthew Bertucci 2022/01/22 for v1.5

#keyvals:\usepackage/tracklang#c
%<language%>
#endkeyvals

\TrackPredefinedDialect{dialect label}#*
\TrackLocale{locale}#*
\TrackLanguageTag{tag}#*
\TrackIfKnownLanguage{tag}{success code}{fail code}#*
\TrackLangFromEnv#*
\TrackLangShowWarningsfalse#*
\TrackLangShowWarningstrue#*
\TrackLangEnv#*
\TrackLangEnvLang#*
\TrackLangEnvTerritory#*
\TrackLangEnvCodeSet#*
\TrackLangEnvModifier#*
\TrackLangQueryEnv#*
\TrackLangQueryOtherEnv{name}#*
\TrackLangParseFromEnv#*

\AnyTrackedLanguages{true}{false}#*
\GetTrackedDialectFromLanguageTag{tag}{cmd}#*d
\TrackedDialectClosestSubMatch#*
\ForEachTrackedDialect{cmd}{code}#*d
\ForEachTrackedLanguage{cmd}{code}#*d
\IfTrackedLanguage{label}{true}{false}#*
\IfTrackedDialect{label}{true}{false}#*
\TrackedLanguageFromDialect{dialect}#*
\TrackedDialectsFromLanguage{root language label}#*
\IfTrackedLanguageHasIsoCode{code type}{label}{true}{false}#*
\IfTrackedIsoCode{code type}{code}{true}{false}#*
\TrackedLanguageFromIsoCode{code type}{code}#*
\TrackedIsoCodeFromLanguage{code type}{label}#*
\TwoLetterIsoCountryCode#*
\TwoLetterIsoLanguageCode#*
\ThreeLetterIsoLanguageCode#*
\ThreeLetterExtIsoLanguageCode#*
\GetTrackedLanguageTag{dialect}#*
\GetTrackedDialectModifier{dialect}#*
\IfHasTrackedDialectModifier{dialect}{true}{false}#*
\GetTrackedDialectVariant{dialect}#*
\IfHasTrackedDialectVariant{dialect}{true}{false}#*
\GetTrackedDialectScript{dialect}#*
\IfHasTrackedDialectScript{dialect}{true}{false}#*
\IfTrackedDialectIsScriptCs{dialect}{cs}{true}{false}#*
\GetTrackedDialectSubLang{dialect}#*
\IfHasTrackedDialectSubLang{dialect}{true}{false}#*
\GetTrackedDialectAdditional{dialect}#*
\IfHasTrackedDialectAdditional{dialect}{true}{false}#*
\IfTrackedLanguageFileExists{dialect}{prefix}{suffix}{true}{false}#*
\CurrentTrackedTag#*
\TrackLangRequireDialect{pkgname}{dialect}#*
\TrackLangRequireDialect[load code]{pkgname}{dialect}#*
\TrackLangRequireDialectPrefix#*
\CurrentTrackedDialect#*
\CurrentTrackedLanguage#*
\CurrentTrackedRegion#*
\CurrentTrackedIsoCode#*
\CurrentTrackedDialectModifier#*
\CurrentTrackedDialectVariant#*
\CurrentTrackedDialectSubTag#*
\CurrentTrackedDialectAdditional#*
\CurrentTrackedLanguageTag#*
\CurrentTrackedDialectScript#*
\TrackLangProvidesResource{tag}#*
\TrackLangProvidesResource{tag}[version info]#*
\TrackLangRequireResource{localeid2}#*
\TrackLangRequireResourceOrDo{localeid2}{code1}{code2}#*
\TrackLangRequestResource{localeid2}{not found code}#*
\TrackLangAddToHook{code}{type}#*
\TrackLangAddToCaptions{code}#*
\TrackLangRedefHook{code}{type}#*

\TrackPredefinedDialect{dialect}#*
\SetCurrentTrackedDialect{dialect}#*
\TrackLangAddExtraScriptFile{filename}#*
\TrackLangAddExtraRegionFile{filename}#*
\TrackLangNewLanguage{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
\AddTrackedLanguage{root language label}#*
\TrackLangProvidePredefinedLanguage{label}#*
\TrackLangProvidePredefinedDialect{dialect}{language}{region}{modifier}{variant}{map}{script}#*
\AddTrackedDialect{dialect}{root language label}#*
\TrackLangLastTrackedDialect#*
\SetTrackedDialectLabelMap{from}{to}#*
\AddTrackedLanguageIsoCodes{root language}#*
\SetTrackedDialectModifier{dialect}{value}#*
\SetTrackedDialectScript{dialect}{value}#*
\SetTrackedDialectVariant{dialect}{value}#*
\SetTrackedDialectSubLang{dialect}{value}#*
\SetTrackedDialectAdditional{dialect}{value}#*

\AddTrackedCountryIsoCode{root language}#*
\AddTrackedIsoLanguage{code type}{code}{language}#*
\CurrentTrackedDialectSubLang#*
\CurrentTrackedIsoCodeI#*
\CurrentTrackedIsoCodeII#*
\CurrentTrackedIsoCodeIII#*
\GetTrackedDialectFromMapping{language hook}#*
\GetTrackedDialectToMapping{tracklang label}#*
\IfHookHasMappingFromTrackedDialect{hook label}{true}{false}#*
\IfTrackedDialectHasMapping{tracklang label}{true}{false}#*
\LetTrackLangOption{option}{synonym}#*
\LetTrackLangSynonym{option}{synonym}#*
\TrackLangDeclareDialectOption{dialect}{root lang}{3166-1 code}{modifier}{variant}{map}{script}#*
\TrackLangDeclareLanguageOption{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
\TrackLangGetDefaultScript{language}#*
\TrackLangGetKnownCountry{language}#*
\TrackLangGetKnownIsoThreeLetterLangB{language}#*
\TrackLangGetKnownIsoThreeLetterLang{language}#*
\TrackLangGetKnownIsoTwoLetterLang{language}#*
\TrackLangGetKnownLangFromIso{ISO code}#*
\TrackLangIfAlphaNumericChar{tag}{true}{false}#*
\TrackLangIfHasDefaultScript{language}{true}{false}#*
\TrackLangIfHasKnownCountry{language}{true}{false}#*
\TrackLangIfKnownIsoThreeLetterLangB{language}{true}{false}#*
\TrackLangIfKnownIsoThreeLetterLang{language}{true}{false}#*
\TrackLangIfKnownIsoTwoLetterLang{language}{true}{false}#*
\TrackLangIfKnownLangFromIso{ISO code}{true}{false}#*
\TrackLangIfKnownLang{language}{true}{false}#*
\TrackLangIfLanguageTag{tag}{true}{false}#*
\TrackLangIfRegionTag{tag}{true}{false}#*
\TrackLangIfScriptTag{tag}{true}{false}#*
\TrackLangIfVariantTag{tag}{true}{false}#*
\tracklangparseenvatmod#S
\tracklangparsemod#S
\tracklangtmp#S

# from tracklang-region-codes.tex (not automatically loaded)
\TrackLangRegionMap{numeric code}{alpha-2 code}{alpha-3 code}#S
\TrackLangAlphaIIToNumericRegion{alpha-2 code}#S
\TrackLangNumericToAlphaIIRegion{numeric code}#S
\TrackLangIfKnownAlphaIIRegion{alpha-2 code}{true}{false}#S
\TrackLangIfKnownNumericRegion{numeric code}{true}{false}#S
\TrackLangAlphaIIIToNumericRegion{alpha-3 code}#S
\TrackLangNumericToAlphaIIIRegion{numeric code}#S
\TrackLangIfKnownAlphaIIIRegion{alpha-3 code}{true}{false}#S
