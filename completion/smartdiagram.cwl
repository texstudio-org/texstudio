# smartdiagram package
# Matthew Bertucci 10/24/2021 for v0.3b

#include:tikz
#include:etoolbox
#include:xstring

\smartdiagram[type%keyvals]{list of items}
\smartdiagramanimated[type%keyvals]{list of items}

#keyvals:\smartdiagram,\smartdiagramanimated,\smartdiagramadd
circular diagram
circular diagram:clockwise
flow diagram
flow diagram:horizontal
descriptive diagram
priority descriptive diagram
bubble diagram
constellation diagram
connected constellation diagram
sequence diagram
#endkeyvals

\usesmartdiagramlibrary{library}

#keyvals:\usesmartdiagramlibrary#c
additions
#endkeyvals

\smartdiagramadd[type%keyvals]{list of items}{list of additions}#*
\smartdiagramconnect{arrow options}{start module/end module}#*

\smartdiagramset{options%keyvals}

#keyvals:\smartdiagramset#c
set color list={%<color1,color2,...%>}
uniform color list=
use predefined color list
insert decoration=
arrow line width=##L
arrow tip=
arrow style=
uniform arrow color#true,false
arrow color=#%color
module minimum width=##L
module minimum height=##L
module y sep=##L
module x sep=##L
module shape=
text width=##L
font=%<cmd%>
border color=#%color
text color=#%color
circular distance=##L
back arrow distance=##L
back arrow disabled#true,false
circular final arrow disabled#true,false
descriptive items y sep=##L
description title width=##L
description title text width=##L
description text width=##L
description title font=%<cmd%>
description font=%<cmd%>
description width=##L
priority arrow width=##L
priority arrow head extend=##L
priority tick size=##L
priority arrow height advance=##L
bubble center node size=##L
bubble center node font=%<cmd%>
bubble center node color=#%color
distance center/other bubbles=##L
distance text center bubble=##L
bubble fill opacity=
bubble node size=##L
bubble text opacity=
bubble node font=%<cmd%>
planet size=##L
planet color=#%color
planet font=%<cmd%>
distance planet-connection=##L
distance planet-text=##L
planet text width=##L
satellite size=##L
satellite font=%<cmd%>
satellite fill opacity=
satellite text opacity=
satellite text width=##L
distance satellite-connection=##L
connection line width=##L
distance planet-satellite=##L
uniform connection color#true,false
connection color=#%color
sequence item height=##L
sequence item width=##L
sequence item border color=#%color
sequence item border size=##L
sequence item font size=##L
sequence item fill opacity=
sequence item text opacity=
sequence item text width=##L
sequence item text color=#%color
uniform sequence color#true,false
sequence item uniform color=#%color
additions={%<specs%>}
#endkeyvals