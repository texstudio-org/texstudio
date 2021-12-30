# pas-cv package
# Matthew Bertucci 12/28/2021 for v1.03

#include:fp
#include:multido
#include:tikz
#include:xkeyval
#include:xstring

\begin{crossgrid}
\begin{crossgrid}[options%keyvals]
\end{crossgrid}

#keyvals:\begin{crossgrid}
h=%<nombre de colonnes%>
v=%<nombre de lignes%>
pas=%<scale%>
#endkeyvals

\blackcase{x}{y}
\blackcases{x1/y1,x2/y2,...}

\word{x}{y}{MOT}
\word[options%keyvals]{x}{y}{MOT}
\words{x1/y1/MOT1,x2/y2.MOT2,...}
\words[options%keyvals]{x1/y1/MOT1,x2/y2.MOT2,...}

#keyvals:\word,\words
h#true,false
v#true,false
#endkeyvals

\gridcross{MOT1*MOT2,MOT3*MOT4,...}

\printDef{h|v}{la définition%text}
\printDef[s]{%<h|v%>}{%<la définition%>}

\symbsep#*
\symbnext#*
\cRM{text}#*
\newlist#*
\theL#*
\thecntdef#*

\debutX#S
\debutY#S
\namecase#S
\num#S
\pos#S
\posX#S
\posY#S
\pr#S