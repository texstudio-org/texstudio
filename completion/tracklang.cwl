# tracklang package
# Matthew Bertucci 2022/10/30 for v1.6

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
\TrackLangQueryOtherEnv{env-name}#*
\TrackLangParseFromEnv#*
\AnyTrackedLanguages{true}{false}#*
\GetTrackedDialectFromLanguageTag{tag}{cmd}#*d
\TrackedDialectClosestSubMatch#*
\ForEachTrackedDialect{cmd}{body}#*d
\ForEachTrackedLanguage{cmd}{body}#*d
\IfTrackedLanguage{language-label}{true}{false}#*
\IfTrackedDialect{dialect-label}{true}{false}#*
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
\TrackLangGetDefaultScript{language}#*
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
\CurrentTrackedDialectSubLang#*
\CurrentTrackedDialectAdditional#*
\CurrentTrackedLanguageTag#*
\CurrentTrackedDialectScript#*
\TrackLangProvidesResource{tag}{version info}#*
\TrackLangRequireResource{tag}#*
\TrackLangRequireResourceOrDo{tag}{code1}{code2}#*
\TrackLangRequestResource{tag}{not found code}#*
\TrackLangAddToHook{code}{type}#*
\TrackLangAddToCaptions{code}#*
\TrackLangRedefHook{code}{type}#*
\TrackLangAddExtraScriptFile{file}#*i
\TrackLangAddExtraRegionFile{file}#*i
\TrackPredefinedDialect{dialect}#*
\SetCurrentTrackedDialect{dialect}#*
\TrackLangNewLanguage{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
\AddTrackedDialect{dialect label}{root language label}#*
\AddTrackedLanguage{root language label}#*
\TrackLangLastTrackedDialect#*
\TrackLangProvidePredefinedLanguage{language label}#*
\TrackLangProvidePredefinedDialect{dialect}{language}{3166-1 code}{modifier}{variant}{map}{script}#*
\SetTrackedDialectLabelMap{tracklang-label}{hook-label}#*
\AddTrackedLanguageIsoCodes{root language label}#*
\SetTrackedDialectModifier{dialect}{value}#*
\SetTrackedDialectScript{dialect}{value}#*
\SetTrackedDialectVariant{dialect}{value}#*
\SetTrackedDialectSubLang{dialect}{value}#*
\SetTrackedDialectAdditional{dialect}{value}#*

\AddTrackedCountryIsoCode{root language}#*
\AddTrackedIsoLanguage{code type}{code}{language}#*
\CurrentTrackedDialectSubLang#*
\TrackLangDeclareDialectOption{dialect}{root lang}{3166-1 code}{modifier}{variant}{map}{script}#*
\TrackLangDeclareLanguageOption{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
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

# not in main documentation
\CurrentTrackedIsoCodeI#*
\CurrentTrackedIsoCodeII#*
\CurrentTrackedIsoCodeIII#*
\GetTrackedDialectFromMapping{language hook}#*
\GetTrackedDialectToMapping{tracklang label}#*
\IfHookHasMappingFromTrackedDialect{hook label}{true}{false}#*
\IfTrackedDialectHasMapping{tracklang label}{true}{false}#*
\LetTrackLangOption{option}{synonym}#*
\LetTrackLangSynonym{option}{synonym}#*
\tracklangparseenvatmod#S
\tracklangparsemod#S
\tracklangtmp#S

# from tracklang-region-codes.tex (not automatically loaded)
\TrackLangAlphaIIToNumericRegion{alpha-2 code}#S
\TrackLangNumericToAlphaIIRegion{numeric code}#S
\TrackLangIfKnownAlphaIIRegion{alpha-2 code}{true}{false}#S
\TrackLangIfKnownNumericRegion{numeric code}{true}{false}#S
\TrackLangAlphaIIIToNumericRegion{alpha-3 code}#S
\TrackLangNumericToAlphaIIIRegion{numeric code}#S
\TrackLangIfKnownAlphaIIIRegion{alpha-3 code}{true}{false}#S
\TrackLangRegionMap{numeric code}{alpha-2 code}{alpha-3 code}#S
