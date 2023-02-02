# doctools package
# Matthew Bertucci 11/14/2021 for v0.1

#include:kvoptions
#include:pdftexcmds
#include:etoolbox
#include:xstring
#include:kvsetkeys
#include:cmap
#include:listings
#include:xcolor
#include:colortbl
#include:xspace
#include:url

\marg{abc}
\oarg{arg}
\bs
\command{cmd}
\cs{csname}
\arg{arg}
\environment{envname}
\env{envname}
\package{package}
\ltxclass{class}
\option{option}
\parameter{parameter}
\person{person}
\AfterLastParam
\Default{arg}
\Example{arg}
\latex
\begin{Optionlist}#\tabular
\end{Optionlist}
\begin{latexcode}#V
\end{latexcode}
\printCodeFromFile{last line}{file}
\printCodeFromFile[first line]{last line}{file}
\labelfile{file path/name%file}
\file{file path/name%file}

\thelstFirstLine#*
\thelstLastLine#*
\PrintFileName{file}#*
\thefile#*
\theHfile#*
