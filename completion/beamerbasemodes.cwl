# beamerbasemodes package
# Matthew Bertucci 1/30/2022 for v3.65

#include:etoolbox
#include:beamerbasedecode

\mode<mode specification>{text}#M
\mode{text}#M
\mode<mode specification>
\mode*

\includeslide{label name}
\includeslide[options%keyvals]{label name}

\setjobnamebeamerversion{filename without extension%file}

\thebeamerpauses#*
\jobnamebeamerversion#*
