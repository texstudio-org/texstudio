# tikzfill package
# Matthew Bertucci 2022/07/21 for v1.0

#include:tikz
# loads fill.image, fill.hexagon, and fill.rhombus tikzlibraries

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
## from fill.image tikzlibrary ##
fill plain image=%<file name%>
fill plain image*={%<graphics options%>}{%<file name%>}
fill plain picture={%<graphical code%>}
fill stretch image=%<file name%>
fill stretch image*={%<graphics options%>}{%<file name%>}
fill stretch picture={%<graphical code%>}
fill overzoom image=%<file name%>
fill overzoom image*={%<graphics options%>}{%<file name%>}
fill overzoom picture={%<graphical code%>}
fill zoom image=%<file name%>
fill zoom image*={%<graphics options%>}{%<file name%>}
fill zoom picture={%<graphical code%>}
fill shrink image=%<file name%>
fill shrink image*={%<graphics options%>}{%<file name%>}
fill shrink picture={%<graphical code%>}
fill tile image=%<file name%>
fill tile image*={%<graphics options%>}{%<file name%>}
fill tile picture={%<graphical code%>}
fill image opacity=%<fraction%>
fill image scale=%<fraction%>
fill image options={%<graphics options%>}
## from fill.hexagon tikzlibrary ##
pattern hexagon={%<pattern keys%>}
pattern hexagon grid={%<pattern keys%>}
pattern hexagon cycle={%<pattern keys%>}
## from fill.rhombus tikzlibrary ##
pattern rhombus={%<pattern keys%>}
#endkeyvals