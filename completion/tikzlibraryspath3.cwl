# spath3 tikzlibrary
# 2022/11/24 for v2.7

#include:spath3

#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
spath/adjust and close globally=%<path%>
spath/adjust and close=%<path%>
spath/append no move=%<name%>
spath/append reverse no move=%<name%>
spath/append reverse=%<name%>
spath/append=%<name%>
spath/clone globally={%<target%>}{%<source%>}
spath/clone={%<target%>}{%<source%>}
spath/close globally with curve={%<path%>}{%<splice path%>}
spath/close globally with={%<path%>}{%<splice path%>}
spath/close globally=%<path%>
spath/close with curve={%<path%>}{%<splice path%>}
spath/close with={%<path%>}{%<splice path%>}
spath/close=%<path%>
spath/join with={%<path%>}{%<path, options%>}
spath/open globally=%<path%>
spath/open=%<path%>
spath/reverse globally=%<name%>
spath/reverse=%<name%>
spath/save global=%<name%>
spath/save=%<name%>
spath/shorten at both ends={%<path%>}{%<length%>}
spath/shorten at end={%<path%>}{%<length%>}
spath/shorten at start={%<path%>}{%<length%>}
spath/shorten globally at both ends={%<path%>}{%<length%>}
spath/shorten globally at end={%<path%>}{%<length%>}
spath/shorten globally at start={%<path%>}{%<length%>}
spath/show current path
spath/show=%<name%>
spath/split at into={%<start path%>}{%<end path%>}{%<path%>}{%<parameter%>}
spath/split at keep end={%<path%>}{%<parameter%>}
spath/split at keep middle={%<path%>}{%<parameter%>}{%<parameter%>}
spath/split at keep start={%<path%>}{%<parameter%>}
spath/split at={%<path%>}{%<parameter%>}
spath/split globally at into={%<start path%>}{%<end path%>}{%<path%>}{%<parameter%>}
spath/split globally at keep end={%<path%>}{%<parameter%>}
spath/split globally at keep middle={%<path%>}{%<parameter%>}{%<parameter%>}
spath/split globally at keep start={%<path%>}{%<parameter%>}
spath/split globally at={%<path%>}{%<parameter%>}
spath/to=%<name%>
spath/transform global={%<name%>}{%<transformations%>}
spath/transform={%<name%>}{%<transformations%>}
spath/translate globally={%<name%>}{%<x-dimen%>}{%<y-dimen%>}
spath/translate={%<name%>}{%<x-dimen%>}{%<y-dimen%>}
spath/use=%<name%>
spath/use={%<name,options%>}
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c
spath/transform to={%<path%>}{%<parameter%>}
spath/upright transform to={%<path%>}{%<parameter%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\scoped#c
spath/get components of globally={%<path%>}{%<macro%>}
spath/get components of={%<path%>}{%<macro%>}
spath/global knot={%<path%>}{%<gap%>}{%<components%>}
spath/insert gaps after components={%<path%>}{%<gap%>}
spath/insert gaps after components={%<path%>}{%<gap%>}{%<components%>}
spath/insert gaps after segments={%<path%>}{%<gap%>}
spath/insert gaps after segments={%<path%>}{%<gap%>}{%<segments%>}
spath/insert gaps globally after components={%<path%>}{%<gap%>}
spath/insert gaps globally after components={%<path%>}{%<gap%>}{%<components%>}
spath/insert gaps globally after segments={%<path%>}{%<gap%>}
spath/insert gaps globally after segments={%<path%>}{%<gap%>}{%<segments%>}
spath/join components globally upright with={%<path%>}{%<splice path%>}
spath/join components globally upright with={%<path%>}{%<splice path%>}{%<list%>}
spath/join components globally with curve={%<path%>}
spath/join components globally with curve={%<path%>}{%<list%>}
spath/join components globally with={%<path%>}{%<splice path%>}
spath/join components globally with={%<path%>}{%<splice path%>}{%<list%>}
spath/join components globally={%<path%>}{%<components%>}
spath/join components upright with={%<path%>}{%<splice path%>}
spath/join components upright with={%<path%>}{%<splice path%>}{%<list%>}
spath/join components with curve={%<path%>}
spath/join components with curve={%<path%>}{%<list%>}
spath/join components with={%<path%>}{%<splice path%>}
spath/join components with={%<path%>}{%<splice path%>}{%<list%>}
spath/join components={%<path%>}{%<components%>}
spath/knot={%<path%>}{%<gap%>}{%<components%>}
spath/remove components globally={%<path%>}{%<list%>}
spath/remove components={%<path%>}{%<list%>}
spath/remove empty components globally=%<path%>
spath/remove empty components=%<path%>
spath/render components=%<path%>
spath/replace lines globally=%<path%>
spath/replace lines=%<path%>
spath/span global={%<name%>}{%<start point%>}{%<end point%>}
spath/span={%<name%>}{%<start point%>}{%<end point%>}
spath/split at intersections with={%<first%>}{%<second%>}
spath/split at intersections={%<first%>}{%<second%>}
spath/split at self intersections=%<path%>
spath/split globally at intersections with={%<first%>}{%<second%>}
spath/split globally at intersections={%<first%>}{%<second%>}
spath/split globally at self intersections=%<path%>
spath/spot weld globally=%<path%>
spath/spot weld=%<path%>
#endkeyvals

\getComponentOf{macro%cmd}{number}#d