# pixelart package
# Matthew Bertucci 2022/11/18 for v1.0.0

#include:iftex
#include:luacode
#include:tikz
#include:tikzlibrarypatterns

#keyvals:\usepackage/pixelart#c
draft
#endkeyvals

\pixelart{pixels}
\pixelart[options%keyvals]{pixels}
\tikzpixelart{coord}{pixels}
\tikzpixelart[options%keyvals]{coord}{pixels}
\setpixelartdefault{options%keyvals}

\pixelartlogo#*
\pixelartlogo[options%keyvals]#*
\pixelartheart#*
\pixelartheart[options%keyvals]#*
\pixelartname#*
\pixelartname[options%keyvals]#*
\pixelartlogobw#*
\pixelartlogobw[options%keyvals]#*
\pixelartheartbw#*
\pixelartheartbw[options%keyvals]#*
\pixelartnamebw#*
\pixelartnamebw[options%keyvals]#*

#keyvals:\pixelart,\tikzpixelart,\setpixelartdefault,\pixelartlogo,\pixelartheart,\pixelartname,\pixelartlogobw,\pixelartheartbw,\pixelartnamebw
colors=%<options%>
draft#true,false
margin=##L
squares
squares={%<options%>}
stack
style=%<keyword%>
tikz={%<TikZ keys%>}
#endkeyvals

\newpixelartcolors{name}{keyvals}
\renewpixelartcolors{name}{keyvals}

\setpixelartdebugon
\setpixelartdebugoff
