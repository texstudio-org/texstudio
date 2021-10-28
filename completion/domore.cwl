# dowith package
# Matthew Bertucci 10/27/2021 for v0.3

\DoWith{%<repeat%>}%<<arg1><arg2>...<argN>%>\StopDoing#*
\DoWithMore{%<repeat%>}%<<arg1><arg2>...<argN>%>\StopDoing#*
\StopDoing#*
\setdo[digit]{do%definition}#*
\setdo[digit][default]{do%definition}#*
\DoSeparateWith{%<repeat%>}{%<sep%>}%<<arg1><arg2>...<argN>%>\StopDoing#*
\DoSeparateWithMore{%<repeat%>}{%<sep%>}%<<arg1><arg2>...<argN>%>\StopDoing#*
\DoWithAllOf{%<repeat%>}{%<<arg1><arg2>...<argN>%>}#*
\DoWithAllIn{repeat}{list macro}#*

### from \input plainpkg
\withcsname%<<cmd>%>#*
\ifltx#*
\PushCatMakeLetter\%<<char>%>#*
\PopLetterCat\%<<char>%>#*
\PushCatMakeLetterAt#*
\PopLetterCatAt#*
\plainpkginfo#S