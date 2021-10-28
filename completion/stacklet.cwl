# stacklet package
# Matthew Bertucci 10/27/2021 for v0.3a

\PushCatMakeLetter\%<<char>%>#*
\PopLetterCat\%<<char>%>#*
\PushCatMakeLetterAt#*
\PopLetterCatAt#*

### from \input plainpkg
\withcsname%<<cmd>%>#*
\ifltx#*
\plainpkginfo#S