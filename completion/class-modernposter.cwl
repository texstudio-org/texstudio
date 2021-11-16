# modernposter class
# Matthew Bertucci 11/14/2021 for v1.03.1

#include:class-a0poster
#include:xcolor
#include:pgfkeys
#include:pgfopts
#include:relsize
#include:tikz
#include:enumitem
#include:fontawesome
#include:sfmath
#include:etoolbox
#include:hyperref
#include:environ
#include:FiraSans

#ifOption:helvet
#include:helvet
#endif

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

\posterbox{title%plain}{contents%text}
\doubleposterbox{title1%plain}{contents1%text}{title2%plain}{contents2%text}
\doubleposterbox[height]{title1%plain}{contents1%text}{title2%plain}{contents2%text}

\oldparboxrestore#S
\faiconold#S

\email{address}

\thenumcols#*