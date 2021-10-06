# ctable package
# Matthew Bertucci 10/1/2021 for v2.0

#include:ifpdf
#include:etoolbox
#include:xcolor
#include:array
#include:tabularx
#include:booktabs
#include:rotating
#include:transparent

\setupctable{options%keyvals}
\ctable{preamble}{tnote cmds}{table}
\ctable[options%keyvals]{preamble}{tnote cmds}{table}

#keyvals:\setupctable,\ctable
bgopacity=
botcap
captionskip=##L
center
continued
continued=
doinside=%<code%>
figure
footerwidth=##L
framebg=%<r g b%>
framefg=%<r g b%>
framerule=##L
framesep=##L
left
maxwidth=##L
mincapwidth=##L
nonotespar
nosideways
nostar
nosuper
notespar
pos=
right
sidecap
sideways
star
super
table
topcap
width=##L
#endkeyvals

#keyvals:\setupctable
captionsleft
captionsright
captionsinside
#endkeyvals

#keyvals:\ctable
caption=%<text%>
cap=%<short caption text%>
label=##l
#endkeyvals

\tnote{footnote text}
\tnote[label]{footnote text}
\tmark
\tmark[label]
\NN
\FL
\ML
\LL