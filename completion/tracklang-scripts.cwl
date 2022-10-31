# tracklang-scripts package
# Matthew Bertucci 2022/10/30 for v1.6

#include:tracklang

\TrackLangScriptMap{letter code}{numeric code}{script name}{direction}{parent script}#*
\TrackLangScriptAlphaToNumeric{alpha code}#*
\TrackLangScriptIfKnownAlpha{alpha code}{true}{false}#*
\TrackLangScriptNumericToAlpha{numeric code}#*
\TrackLangScriptIfKnownNumeric{numeric code}{true}{false}#*
\TrackLangScriptAlphaToName{alpha code}#*
\TrackLangScriptAlphaToDir{alpha code}#*
\TrackLangScriptSetParent{alpha code}{parent alpha code}#*
\TrackLangScriptGetParent{alpha code}#*
\TrackLangScriptIfHasParent{alpha code}{true}{false}#*
