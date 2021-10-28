# actcodes package
# Matthew Bertucci 10/27/2021 for v0.2a

\MakeActiveAss%<<assign-function>\<char><assign-args>%>#*
\MakeActive\%<<char>%>#*
\MakeActiveDef\%<<char><parameters>%>{%<replace%>}#*
\MakeActiveLet\%<<char><cmd>%>#*
\MakeOther\%<<char>%>#*
\MakeActiveOther\%<<char>%>#*

### from \input plainpkg
\withcsname%<<cmd>%>#*
\ifltx#*
\PushCatMakeLetter\%<<char>%>#*
\PopLetterCat\%<<char>%>#*
\PushCatMakeLetterAt#*
\PopLetterCatAt#*
\plainpkginfo#S