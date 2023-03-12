# styledcmd package
# Matthew Bertucci 2022/12/13 for v2.0

#include:lt3rawobjects

\newstyledcmd{cmd}{style name}{definition}#d
\newstyledcmd{cmd}{style name}[args]{definition}#d
\renewstyledcmd{cmd}{style name}{definition}
\renewstyledcmd{cmd}{style name}[args]{definition}
\providestyledcmd{cmd}{style name}{definition}#d
\providestyledcmd{cmd}{style name}[args]{definition}#d
\setGlobalStyle{cmd}{new style name}
\NewDocStyledCMD{cmd}{style name}{xargs}{definition}#d
\RenewDocStyledCMD{cmd}{style name}{xargs}{definition}
\ProvideDocStyledCMD{cmd}{style name}{xargs}{definition}#d
\newstyledcmdExp{cmd}{style name}{definition}#d
\newstyledcmdExp{cmd}{style name}[args]{definition}#d
\renewstyledcmdExp{cmd}{style name}{definition}
\renewstyledcmdExp{cmd}{style name}[args]{definition}
\providestyledcmdExp{cmd}{style name}{definition}#d
\providestyledcmdExp{cmd}{style name}[args]{definition}#d
\AddCMDToGroup{group name}{cmd1,cmd2,...}
\SetGroupStyle{group name}{style name}

# deprecated
\styBeginGroup{group name}#S
\styEndGroup#S
\styBeginStyle{format name}#S
\styEndStyle#S
\newGstyledcmd{cmd}{definition}#Sd
\newGstyledcmd{cmd}[args]{definition}#Sd
\NewGDocStyledCMD{cmd}{xargs}{definition}#Sd
\setGroupStyle{group name}{new default style}#S
