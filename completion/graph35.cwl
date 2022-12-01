# graph35 package
# Matthew Bertucci 2022/11/30 for v0.1.3

#include:etoolbox
#include:pixelart0
#include:tikz
#include:tikzlibrarycalc
#include:pgfkeys
#include:etoolbox
#include:amssymb
#include:amsbsy
#include:sansmath
#include:letterspace
#include:pgfopts
#include:graph35-pixelart
#include:graph35-keys

#keyvals:\usepackage/graph35#c
color=#real,blackandwhite
#endkeyvals

\setgraphcolor{color setting%keyvals}

#keyvals:\setgraphcolor#c
real
blackandwhite
#endkeyvals

graph35ACON#B
graph35ACONBORDER#B
graph35ALPHA#B
graph35ALPHABORDER#B
graph35SHIFT#B
graph35SHIFTBORDER#B
graph35SCREEN#B
graph35SCREENBG#B
graph35CASE#B
graph35CASEBORDER#B
graph35EXE#B
graph35EXEBORDER#B
graph35NUMBER#B
graph35NUMBERBORDER#B
graph35KEYTEXT#B
graph35ALPHATEXT#B
graph35SHIFTTEXT#B

\calculator{model}
\calculator[options%keyvals]{model}

#keyvals:\calculator
color=#real,blackandwhite,default
scale=%<factor%>
#endkeyvals

\tikzcalculator{model}

\key{key%plain}
\key[options%keyvals]{key%plain}
\tikzkey{key%plain}{coordinates}
\tikzkey[options%keyvals]{key%plain}{coordinates}

#keyvals:\key,\tikzkey
color=#real,blackandwhite,default
scale=%<factor%>
shift#true,false
alpha#true,false
prefix=%<anchor prefix%>
suffix=%<anchor suffix%>
#endkeyvals

\menu{icon}{shortcut}
\tikzmenu{icon}{shortcut}{coordinates}
\tikzmenu[options%keyvals]{icon}{shortcut}{coordinates}

\function{function}
\tikzfunction{function}{coordinates}
\tikzfunction[options%keyvals]{function}{coordinates}

\battery{state}
\tikzbattery{state}{coordinates}
\tikzbattery[options%keyvals]{state}{coordinates}

#keyvals:\tikzmenu,\tikzfunction,\tikzbattery
color=#%color
scale=%<factor%>
raise=##L
#endkeyvals

\boolvalue{boolean}#S
