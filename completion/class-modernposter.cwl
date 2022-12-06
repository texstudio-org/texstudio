# modernposter class
# Matthew Bertucci 11/14/2021 for v1.03.1

#include:class-a0poster
#include:xcolor
#include:pgfkeys
#include:pgfopts
#include:relsize
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarybackgrounds
#include:tikzlibraryshapes.misc
#include:enumitem
#include:fontawesome
#include:sfmath
#include:etoolbox
#include:hyperref
#include:environ
#include:FiraSans

#keyvals:\documentclass/modernposter#c
hlcolor=%<HTML color%>
logo=%<imagefile%>
helvet
#endkeyvals

#ifOption:helvet
#include:helvet
#endif

mDarkTeal#B
mDarkBrown#B
hlcol#B
\highlight{text}

\colheight#*
\colwidth#*
\coltextwidth#*
\colsep#*
\boxheight#*
\boxlinewidth#*

\begin{postercolumn}
\end{postercolumn}

\posterbox{title%text}{contents%text}
\doubleposterbox{title1%text}{contents1%text}{title2%text}{contents2%text}
\doubleposterbox[height]{title1%text}{contents1%text}{title2%text}{contents2%text}

\oldparboxrestore#S
\faiconold{arg}#S

\email{email%URL}#U

\thenumcols#*
