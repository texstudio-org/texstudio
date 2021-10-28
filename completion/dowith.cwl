# dowith package
# Matthew Bertucci 10/27/2021 for v0.3

\DoWith{%<cmd%>}%<<arg1><arg2>...<argN>%>\StopDoing#*
\DoDoWith%<<arg1><arg2>...<argN>%>\StopDoing#*
\StopDoing#*
\setdo{definition}#*
\letdo%<<cmd>%>#*
\DoWithAllOf{%<cmd%>}{%<<arg1><arg2>...<argN>%>}#*
\DoDoWithAllOf{%<<arg1><arg2>...<argN>%>}#*
\DoWithAllIn{cmd}{list macro}#*
\DoDoWithAllIn{list macro}#*
\InitializeListMacro{list macro}#*
\ReInitializeListMacro{list macro}#*
\ToListMacroAdd{list macro}{cmd-or}#*
\TestListMacroForToken{list macro}{cmd}#*
\FromTokenListMacroRemove{list macro}{cmd}#*
\InTokenListMacroProvide{list macro}{cmd}#*
\filename#S
\fileinfo#S
\filedate#S
\fileversion#S

### from \input plainpkg
\withcsname%<<cmd>%>#*
\ifltx#*
\PushCatMakeLetter\%<<char>%>#*
\PopLetterCat\%<<char>%>#*
\PushCatMakeLetterAt#*
\PopLetterCatAt#*
\plainpkginfo#S
