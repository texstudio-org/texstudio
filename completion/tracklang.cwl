# tracklang package
# Matthew Bertucci 2025/03/04 for v1.6.5

#keyvals:\usepackage/tracklang#c
%<language%>
verbose
noverbose
warn
nowarn
#endkeyvals

\AddTrackedCountryIsoCode{root language}#*
\AddTrackedDialect{dialect label}{root language label}#*
\AddTrackedIsoLanguage{code type}{code}{language}#*
\AddTrackedLanguage{root language label}#*
\AddTrackedLanguageIsoCodes{root language label}#*
\AddTrackedRegion{country code}{dialect}#*
\AnyTrackedLanguages{true}{false}#*
\AnyTrackedRegions{true}{false}#*
\CurrentTrackedDialect#*
\CurrentTrackedDialectAdditional#*
\CurrentTrackedDialectModifier#*
\CurrentTrackedDialectScript#*
\CurrentTrackedDialectSubLang#*
\CurrentTrackedDialectSubLang#*
\CurrentTrackedDialectVariant#*
\CurrentTrackedIsoCode#*
\CurrentTrackedLanguage#*
\CurrentTrackedLanguageTag#*
\CurrentTrackedRegion#*
\CurrentTrackedTag#*
\ForEachTrackedDialect{cmd}{body}#*d
\ForEachTrackedLanguage{cmd}{body}#*d
\ForEachTrackedRegion{cmd}{body}#*d
\GetTrackedDialectAdditional{dialect}#*
\GetTrackedDialectFromLanguageTag{tag}{cmd}#*d
\GetTrackedDialectModifier{dialect}#*
\GetTrackedDialectScript{dialect}#*
\GetTrackedDialectSubLang{dialect}#*
\GetTrackedDialectVariant{dialect}#*
\GetTrackedLanguageTag{dialect}#*
\IfHasTrackedDialectAdditional{dialect}{true}{false}#*
\IfHasTrackedDialectModifier{dialect}{true}{false}#*
\IfHasTrackedDialectScript{dialect}{true}{false}#*
\IfHasTrackedDialectSubLang{dialect}{true}{false}#*
\IfHasTrackedDialectVariant{dialect}{true}{false}#*
\IfTrackedDialect{dialect-label}{true}{false}#*
\IfTrackedDialectIsScriptCs{dialect}{cs}{true}{false}#*
\IfTrackedIsoCode{code type}{code}{true}{false}#*
\IfTrackedLanguage{language-label}{true}{false}#*
\IfTrackedLanguageFileExists{dialect}{prefix}{suffix}{true}{false}#*
\IfTrackedLanguageFileExistsOmitDialectLabel{dialect}{prefix}{suffix}{true}{false}#*
\IfTrackedLanguageFileExistsOmitDialectLabelOmitOnlyRegion{dialect}{prefix}{suffix}{true}{false}#*
\IfTrackedLanguageFileExistsOmitOnlyRegion{dialect}{prefix}{suffix}{true}{false}#*
\IfTrackedLanguageHasIsoCode{code type}{label}{true}{false}#*
\SetCurrentTrackedDialect{dialect}#*
\SetTrackedDialectAdditional{dialect}{value}#*
\SetTrackedDialectLabelMap{tracklang-label}{hook-label}#*
\SetTrackedDialectModifier{dialect}{value}#*
\SetTrackedDialectScript{dialect}{value}#*
\SetTrackedDialectSubLang{dialect}{value}#*
\SetTrackedDialectVariant{dialect}{value}#*
\ThreeLetterExtIsoLanguageCode#*
\ThreeLetterIsoLanguageCode#*
\TrackedDialectClosestSubMatch#*
\TrackedDialectsFromLanguage{root language label}#*
\TrackedIsoCodeFromLanguage{code type}{label}#*
\TrackedLanguageFromDialect{dialect}#*
\TrackedLanguageFromIsoCode{code type}{code}#*
\TrackIfKnownLanguage{tag}{success code}{fail code}#*
\TrackLangAddExtraRegionFile{file}#*i
\TrackLangAddExtraScriptFile{file}#*i
\TrackLangAddToCaptions{code}#*
\TrackLangAddToHook{code}{type}#*
\TrackLangDeclareDialectOption{dialect}{root lang}{3166-1 code}{modifier}{variant}{map}{script}#*
\TrackLangDeclareLanguageOption{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
\TrackLangEncodingName#*
\TrackLangEnv#*
\TrackLangEnvCodeSet#*
\TrackLangEnvLang#*
\TrackLangEnvModifier#*
\TrackLangEnvTerritory#*
\TrackLangFromEnv#*
\TrackLangGetDefaultScript{language}#*
\TrackLangGetKnownCountry{language}#*
\TrackLangGetKnownIsoThreeLetterLang{language}#*
\TrackLangGetKnownIsoThreeLetterLangB{language}#*
\TrackLangGetKnownIsoTwoLetterLang{language}#*
\TrackLangGetKnownLangFromIso{ISO code}#*
\TrackLangIfAlphaNumericChar{tag}{true}{false}#*
\TrackLangIfHasDefaultScript{language}{true}{false}#*
\TrackLangIfHasKnownCountry{language}{true}{false}#*
\TrackLangIfKnownIsoThreeLetterLang{language}{true}{false}#*
\TrackLangIfKnownIsoThreeLetterLangB{language}{true}{false}#*
\TrackLangIfKnownIsoTwoLetterLang{language}{true}{false}#*
\TrackLangIfKnownLang{language}{true}{false}#*
\TrackLangIfKnownLangFromIso{ISO code}{true}{false}#*
\TrackLangIfLanguageTag{tag}{true}{false}#*
\TrackLangIfRegionTag{tag}{true}{false}#*
\TrackLangIfScriptTag{tag}{true}{false}#*
\TrackLangIfVariantTag{tag}{true}{false}#*
\TrackLangLastTrackedDialect#*
\TrackLangNewLanguage{%<language%>}{%<639-1 code%>}{%<639-2 (T)%>}{%<639-2 (B)%>}{%<639-3%>}{%<3166-1%>}{%<default script%>}#*
\TrackLangParseFromEnv#*
\TrackLangProvidePredefinedDialect{dialect}{language}{3166-1 code}{modifier}{variant}{map}{script}#*
\TrackLangProvidePredefinedLanguage{language label}#*
\TrackLangProvidesResource{tag}{version info}#*
\TrackLangQueryEnv#*
\TrackLangQueryOtherEnv{env-name}#*
\TrackLangRedefHook{code}{type}#*
\TrackLangRequestResource{tag}{not found code}#*
\TrackLangRequireDialect[load code]{pkgname}{dialect}#*
\TrackLangRequireDialect{pkgname}{dialect}#*
\TrackLangRequireDialectOmitDialectLabel[load code]{pkgname}{dialect}#*
\TrackLangRequireDialectOmitDialectLabel{pkgname}{dialect}#*
\TrackLangRequireDialectOmitDialectLabelOmitOnlyRegion[load code]{pkgname}{dialect}#*
\TrackLangRequireDialectOmitDialectLabelOmitOnlyRegion{pkgname}{dialect}#*
\TrackLangRequireDialectOmitOnlyRegion[load code]{pkgname}{dialect}#*
\TrackLangRequireDialectOmitOnlyRegion{pkgname}{dialect}#*
\TrackLangRequireDialectPrefix#*
\TrackLangRequireResource{tag}#*
\TrackLangRequireResourceOrDo{tag}{code1}{code2}#*
\TrackLangShowWarningsfalse#*
\TrackLangShowWarningstrue#*
\TrackLanguageTag{tag}#*
\TrackLocale{locale}#*
\TrackPredefinedDialect{dialect label}#*
\TrackPredefinedDialect{dialect}#*
\TwoLetterIsoCountryCode#*
\TwoLetterIsoLanguageCode#*

# not in main documentation
\CurrentTrackedIsoCodeI#S
\CurrentTrackedIsoCodeII#S
\CurrentTrackedIsoCodeIII#S
\GetTrackedDialectFromMapping{language hook}#S
\GetTrackedDialectToMapping{tracklang label}#S
\IfHookHasMappingFromTrackedDialect{hook label}{true}{false}#S
\IfTrackedDialectHasMapping{tracklang label}{true}{false}#S
\LetTrackLangOption{option}{synonym}#S
\LetTrackLangSynonym{option}{synonym}#S
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
