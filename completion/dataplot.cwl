# dataplot package
# Matthew Bertucci 2025/03/06 for v3.0

#include:tikz
#include:tikzlibraryplotmarks
#include:tikzlibrarycalc
#include:datatool

#keyvals:\usepackage/dataplot#c
# options passed to datatool
delimiter=%<char%>
separator=%<char%>
default-name=%<db name%>
new-value-expand#true,false
new-value-trim#true,false
store-datum#true,false
# options passed to datatool-base
math=#l3fp,lua,fp,pgfmath
lang-warn#true,false
nolocale
locales={%<locales list%>}
lang={%<locales list%>}
verbose#true,false
initial-purify=#early,late
auto-reformat-types={%<list of types%>}
lists={%<keyvals%>}
compare={%<keyvals%>}
numeric={%<keyvals%>}
datetime={%<keyvals%>}
#endkeyvals

#ifOption:math=fp
#include:fp
#endif

#ifOption:math=pgfmath
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#endif

#keyvals:\DTLsetup
plot={%<keyvals%>}
#endkeyvals

\DTLplot{db list%special}{keyvals}
\DTLplot[condition]{db list%special}{keyvals}

#keyvals:\DTLplot
x=%<db key%>
y=%<db key%>
extra-assign={%<assign list%>}
include-if=%<definition%>
include-if-fn=%<cmd%>
width=##L
height=##L
bounds={%<min-x,min-y,max-x,max-y%>}
min-x=%<decimal%>
minx=%<decimal%>
min-y=%<decimal%>
miny=%<decimal%>
max-x=%<decimal%>
maxx=%<decimal%>
max-y=%<decimal%>
maxy=%<decimal%>
legend=#none,north,northeast,east,southeast,south,southwest,west,northwest,custom
legend-labels={%<text1,text2,...%>}
legendlabels={%<text1,text2,...%>}
legend-offset={%<x-dim,y-dim%>}
style=#both,lines,markers
style-resets={%<settings%>}
group-styles={%<settings%>}
colors={%<color1,color2,...%>}
line-colors={%<color1,color2,...%>}
linecolors={%<color1,color2,...%>}
lines={%<linestyle1,linestyle2,...%>}
mark-colors={%<color1,color2,...%>}
markcolors={%<color1,color2,...%>}
marks={%<mark1,mark2,...%>}
axes=#both,x,y,none
omit-zero-lable=#both,auto,x,y,false
side-axes#true,false
x-axis-style={%<TikZ keys%>}
y-axis-style={%<TikZ keys%>}
axis-style={%<TikZ keys%>}
extend-x-axis={%<lower extent,upper extent%>}
extend-y-axis={%<lower extent,upper extent%>}
extend-axes={%<lower extent,upper extent%>}
box#true,false
box-ticks=#none,match-axes,in,out
grid#true,false
major-grid-style={%<TikZ keys%>}
minor-grid-style={%<TikZ keys%>}
xlabel=%<text%>
x-label=%<text%>
ylabel=%<text%>
y-label=%<text%>
min-x-label=%<text%>
min-x-label-style={%<TikZ keys%>}
max-x-label=%<text%>
max-x-label-style={%<TikZ keys%>}
min-y-label=%<text%>
min-y-label-style={%<TikZ keys%>}
max-y-label=%<text%>
max-y-label-style={%<TikZ keys%>}
round=%<integer%>
round-x=%<integer%>
round-y=%<integer%>
ticks#true,false
tics#true,false
minor-ticks#true,false
minortick#true,false
tick-label-style={%<TikZ keys%>}
tic-label-style={%<TikZ keys%>}
tick-label-offset=##L
tick-dir=#in,out
ticdir=#in,out
tick-gap=%<value%>
ticgap=%<value%>
x-ticks#true,false
xtics#true,false
x-tick-label-style={%<TikZ keys%>}
x-tic-label-style={%<TikZ keys%>}
x-minor-ticks#true,false
xminortics#true,false
x-tick-dir=#in,out
xticdir=#in,out
x-tick-gap=%<value%>
xticgap=%<value%>
x-tick-labels={%<text1,text2,...%>}
xticlabels={%<text1,text2,...%>}
x-tick-points={%<decimal1,decimal2,...%>}
xticpoints={%<decimal1,decimal2,...%>}
y-ticks#true,false
ytics#true,false
y-tick-label-style={%<TikZ keys%>}
y-tic-label-style={%<TikZ keys%>}
y-minor-ticks#true,false
yminortics#true,false
y-tick-dir=#in,out
yticdir=#in,out
y-tick-gap=%<value%>
yticgap=%<value%>
y-tick-labels={%<text1,text2,...%>}
yticlabels={%<text1,text2,...%>}
y-tick-points={%<decimal1,decimal2,...%>}
yticpoints={%<decimal1,decimal2,...%>}
#endkeyvals

## Supplementary Plot Commands ##
\DTLplotatbegintikz#*
\DTLplotatendtikz#*
\DTLminX#*
\DTLminY#*
\DTLmaxX#*
\DTLmaxY#*
\DTLaddtoplotlegend{marker}{line style}{text}#*
\DTLformatlegend{legend code}#*
\DTLcustomlegend{legend code}#*
\DTLplotlegendname{db%special}#*
\DTLplotlegendname[db index]{db%special}#*
\DTLplotlegendsetname{db%special}{text}#*
\DTLplotlegendnamesep#*
\DTLplotlegendxy{db%special}{x key}{y key}#*
\DTLplotlegendxy{db%special}{x key}[y index]{y key}#*
\DTLplotlegendxy{db%special}[x index]{x key}{y key}#*
\DTLplotlegendxy{db%special}[x index]{x key}[y index]{y key}#*
\DTLplotlegendxy[db index]{db%special}{x key}{y key}#*
\DTLplotlegendxy[db index]{db%special}{x key}[y index]{y key}#*
\DTLplotlegendxy[db index]{db%special}[x index]{x key}{y key}#*
\DTLplotlegendxy[db index]{db%special}[x index]{x key}[y index]{y key}#*
\DTLplotlegendx{db%special}{x key}#*
\DTLplotlegendx{db%special}[x index]{x key}#*
\DTLplotlegendx[db index]{db%special}{x key}#*
\DTLplotlegendx[db index]{db%special}[x index]{x key}#*
\DTLplotlegendsetxlabel{x key}{text}#*
\DTLplotlegendxysep#*
\DTLplotlegendy{db%special}{y key}#*
\DTLplotlegendy{db%special}[y index]{y key}#*
\DTLplotlegendy[db index]{db%special}{y key}#*
\DTLplotlegendy[db index]{db%special}[y index]{y key}#*
\DTLplotlegendsetylabel{y key}{text}#*

## Conditionals ##
\ifDTLbox#*
\DTLboxfalse#*
\DTLboxtrue#*
\ifDTLgrid#*
\DTLgridfalse#*
\DTLgridtrue#*
\ifDTLshowlines#*
\DTLshowlinesfalse#*
\DTLshowlinestrue#*
\ifDTLshowmarkers#*
\DTLshowmarkersfalse#*
\DTLshowmarkerstrue#*
\ifDTLxaxis#*
\DTLxaxisfalse#*
\DTLxaxistrue#*
\ifDTLxminortics#*
\DTLxminorticsfalse#*
\DTLxminorticstrue#*
\ifDTLxticsin#*
\DTLxticsinfalse#*
\DTLxticsintrue#*
\ifDTLxtics#*
\DTLxticsfalse#*
\DTLxticstrue#*
\ifDTLyaxis#*
\DTLyaxisfalse#*
\DTLyaxistrue#*
\ifDTLyminortics#*
\DTLyminorticsfalse#*
\DTLyminorticstrue#*
\ifDTLyticsin#*
\DTLyticsinfalse#*
\DTLyticsintrue#*
\ifDTLytics#*
\DTLyticsfalse#*
\DTLyticstrue#*

## Lengths ##
\DTLlegendxoffset#*L
\DTLlegendyoffset#*L
\DTLminminortickgap#*L
\DTLminorticklength#*L
\DTLmintickgap#*L
\DTLplotheight#*L
\DTLplotwidth#*L
\DTLticklabeloffset#*L
\DTLticklength#*L

## Counters ##
\theDTLplotroundXvar#*
\theDTLplotroundYvar#*

## Macros ##
\DTLplotlinecolors#*
\DTLplotlines#*
\DTLplotmarkcolors#*
\DTLplotmarks#*
\DTLplotdisplayticklabel{text}#*
\DTLplotdisplayXticklabel{text}
\DTLplotdisplayYticklabel{text}
\DTLXAxisStyle#*
\DTLYAxisStyle#*
\DTLmajorgridstyle#*
\DTLminorgridstyle#*

## Adding to a Plot Stream at the Start or End ##
\dtlplothandlermark{mark code}#*
\DTLplotstream{db%special}{x key}{y key}#*
\DTLplotstream[condition]{db%special}{x key}{y key}#*