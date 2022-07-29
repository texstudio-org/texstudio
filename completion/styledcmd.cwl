# styledcmd package
# Matthew Bertucci 9/7/2021 for v1.1

#include:expl3
#include:xparse

\newstyledcmd{cmd}{format name}{definition}#d
\newstyledcmd{cmd}{format name}[args]{definition}#d
\renewstyledcmd{cmd}{format name}{definition}#d
\renewstyledcmd{cmd}{format name}[args]{definition}#d
\providestyledcmd{cmd}{format name}{definition}#d
\providestyledcmd{cmd}{format name}[args]{definition}#d
\setGlobalStyle{cmd}{new format name}
\NewDocStyledCMD{cmd}{format name}{xargs}{definition}#d
\RenewDocStyledCMD{cmd}{format name}{xargs}{definition}#d
\ProvideDocStyledCMD{cmd}{format name}{xargs}{definition}#d
\styBeginGroup{group name}#*
\styEndGroup#*
\styBeginStyle{format name}#*
\styEndStyle#*
\newGstyledcmd{cmd}{definition}#*d
\newGstyledcmd{cmd}[args]{definition}#*d
\NewGDocStyledCMD{cmd}{xargs}{definition}#*d
\setGroupStyle{group name}{new default style}#*
