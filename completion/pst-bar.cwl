# pst-bar package
# Matthew Bertucci 2/25/2022 for v0.92

#include:pstricks
#include:pst-plot
#include:pst-xkey

\readpsbardata{macro%cmd}{filename%file}#d
\readpsbardata[options%keyvals]{macro%cmd}{filename%file}#d

#keyvals:\readpsbardata#c
header#true,false
#endkeyvals

\psbarchart{data macro}
\psbarchart[options%keyvals]{data macro}

#keyvals:\psbarchart#c
chartstyle=#cluster,stack,block
barstyle={%<style list%>}
barcolsep=%<factor%>
barsep=%<factor%>
barlabelrot=%<degrees%>
orientation=#vertical,horizontal
#endkeyvals

\newpsbarstyle{name}{definition}

\psbarlabel{label}#*
\psbarlabelsep#*

\psbarscale(scale){PostScript code}

\setbarstyle{style}#*
\trimb#S
\trimc#S
\PSTBarLoaded#S
