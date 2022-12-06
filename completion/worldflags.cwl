# worldflags package
# Matthew Bertucci 8/12/2021

#include:ifthen
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshadows
#include:tikzlibraryshapes
#include:tikzlibraryshapes.symbols
#include:tikzlibrarypositioning
#include:tikzlibrarymath
#include:xcolor
#include:xkeyval

\worldflag[options%keyvals]{flag code}
\flagsdefault[options%keyvals] 

#keyvals:\worldflag,\flagsdefault
width=##L
length=##L
framewidth=##L
framecolor=#%color
stretch=%<number%>
grid
noemblem
emblem
emblemdefault
#endkeyvals

#keyvals:\flagsdefault
rotate=%<degrees%>
turn=%<degrees%>
hang=%<degrees%>
#endkeyvals

\begin{flagdescription}{aspectratio}#*
\end{flagdescription}#*
\framecode{code}#*
\flagwidth#*
\flaglength#*
\flagframe#*
\framecolor#*
\stretchfactor#*
\hstripesII{color1%color}{color2%color}#*
\hstripesIII{color1%color}{color2%color}{color3%color}#*
\hstripesIV{color1%color}{color2%color}{color3%color}{color4%color}#*
\vstripesII{color1%color}{color2%color}#*
\vstripesIII{color1%color}{color2%color}{color3%color}#*
\hbar{color}{ycoord}{width}#*
\vbar{color}{xcoord}{width}#*
\chevron{color}{xcoord}#*
\starV{color}{coord}{radius}{angle}#*
\starVI{color}{coord}{radius}{angle}#*
\starn{color}{coord}{outer radius}{inner radius}{angle}#*
\moon{color}{coord1}{radius1}{coord2}{radius2}#*
\unionjack{xcoord1}{ycoord1}{xcoord2}{ycoord2}#*
gridcolor#B
