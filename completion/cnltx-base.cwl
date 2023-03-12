# cnltx-base package
# Matthew Bertucci 10/18/2021 for v0.15

#include:pgfopts
#include:etoolbox
#include:ltxcmds
#include:pdftexcmds
#include:trimspaces
#include:xcolor

\iftest{test directive}{true}{false}#*
\nottest{test directive}{not true}{not false}#*
\expandtwice{code}#*
\cnltxat#*
\cnltxletterat#*
\cnltxotherat#*
\cnltxbang#*
\cnltxequal#*

\setcnltx{options%keyvals}

#keyvals:\setcnltx#c
color-scheme=%<color scheme name%>
set-trail-punct={%<punctuation marks%>}
#endkeyvals

\DeclareCounterRepresentation{cmd}{definition}#d
\newcounterrepresentation{cmd}{definition}#d
\providecounterrepresentation{cmd}{definition}#d
\renewcounterrepresentation{cmd}{definition}

\newexpandablecmd{cmd}{definition}#*d
\newexpandablecmd{cmd}[args]{definition}#*d
\newexpandablecmd{cmd}[args][default]{definition}#*d
\newexpandablecmd*{cmd}{definition}#*d
\newexpandablecmd*{cmd}[args]{definition}#*d
\newexpandablecmd*{cmd}[args][default]{definition}#*d
\renewexpandablecmd{cmd}{definition}#*
\renewexpandablecmd{cmd}[args]{definition}#*
\renewexpandablecmd{cmd}[args][default]{definition}#*
\renewexpandablecmd*{cmd}{definition}#*
\renewexpandablecmd*{cmd}[args]{definition}#*
\renewexpandablecmd*{cmd}[args][default]{definition}#*
\provideexpandablecmd{cmd}{definition}#*d
\provideexpandablecmd{cmd}[args]{definition}#*d
\provideexpandablecmd{cmd}[args][default]{definition}#*d
\provideexpandablecmd*{cmd}{definition}#*d
\provideexpandablecmd*{cmd}[args]{definition}#*d
\provideexpandablecmd*{cmd}[args][default]{definition}#*d

cnltxbrown#B
cnltxblue#B
cnltxred#B
cnltxgreen#B
cnltxgray#B
cnltxyellow#B
cnltxformalblue#B
cnltxformalred#B
cs#B
option#B
module#B
comment#B
beginend#B
env#B
argument#B
meta#B
cnltx#B
cnltxbg#B
link#B
versionnote#B
bibentry#B
bibentryfield#B
expandable#B
unexpandable#B
makeidxkey#B
makeidxstring#B

\definecolorscheme{name}{color assignments}
