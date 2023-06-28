# hf-tikz package
# Matthew Bertucci 10/24/2021 for v0.3a

#include:tikz
#include:tikzlibraryshadings
#include:etoolbox

#keyvals:\usepackage/hf-tikz#c
nofill
customcolors
shade
beamer
norndcorners
markings
#endkeyvals

\tikzmarkin{marker-id}
\tikzmarkin{marker-id}(x1,y1)(x2,y2)
\tikzmarkin[options%keyvals]{marker-id}
\tikzmarkend{marker-id}

#keyvals:\tikzmarkin#c,\tikzset#c
left offset=
right offset=
above offset=
below offset=
below right offset=
above left offset=
top color=
top color=#%color
bottom color=#%color
left color=#%color
right color=#%color
outer color=#%color
inner color=#%color
disable rounded corners#true,false
#endkeyvals

#ifOption:beamer
\tikzmarkin<%<overlay specs%>>{%<marker-id%>}
\thejumping#*
#endif

#ifOption:customcolors
\hfsetfillcolor{color}
\hfsetbordercolor{color}
#keyvals:\tikzmarkin#c,\tikzset#c
set fill color=#%color
set border color=#%color
#endkeyvals
#endif

#ifOption:markings
#keyvals:\tikzmarkin#c,\tikzset#c
mark at=%<position%>
use marker id=%<id number%>
show markers
marker size=##L
marker color=#%color
#endkeyvals
\ifshowmarkers#*
\showmarkerstrue#*
\showmarkersfalse#*
#endif

#keyvals:\tikzset#c
offset definition/.style={%<style specs%>}
#endkeyvals

fancybrown#B
fancyviolet#B
\fcol#*
\bcol#*
\savepointas{name}{point}#*
\oldsavepointas{name}{point}#S
\pgfsyspdfmark{arg1}{arg2}{arg3}#*
\oldpgfsyspdfmark{arg1}{arg2}{arg3}#S
