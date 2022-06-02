# commado package
# Matthew Bertucci 2022/05/31 for v0.11

\DoWithCSL{cmd}{list}

### from \input plainpkg
\withcsname%<<cmd>%>#*
\ifltx#*
\PushCatMakeLetter\%<<char>%>#*
\PopLetterCat\%<<char>%>#*
\PushCatMakeLetterAt#*
\PopLetterCatAt#*
\plainpkginfo#S