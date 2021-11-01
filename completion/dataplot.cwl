# dataplot package
# Matthew Bertucci 10/31/2021 for v2.32

#include:xkeyval
#include:tikz
#include:datatool

\DTLplot{db list%special}{settings%keyvals}
\DTLplot[condition]{db list%special}{settings%keyvals}

#keyvals:\DTLplot
x=
y=
markcolors=
linecolors=
colors=
marks=
lines=
width=##L
height=##L
style=#both,lines,markers
axes=#both,x,y,none
box#true,false
xtics#true,false
ytics#true,false
xminortics#true,false
yminortics#true,false
xticdir=#in,out
yticdir=#in,out
ticdir=#in,out
bounds={%<min x,min y,max x,max y%>}
minx=
miny=
maxx=
maxy=
xticpoints=
xticgap=##L
yticpoints=
yticgap=##L
grid#true,false
xticlabels=
yticlabels=
xlabel=
ylabel=
legend=#none,north,northeast,east,southeast,south,southwest,west,northwest
legendlabels=
#endkeyvals

\DTLplotatbegintikz
\DTLplotatendtikz
\dtlplothandlermark{pgf code}
\DTLaddtoplotlegend{marker}{line style}{text}
\DTLplotwidth#*
\DTLplotheight#*
\DTLticklength#*
\DTLminorticklength#*
\DTLticklabeloffset#*
\DTLmintickgap#*
\DTLlegendxoffset#*
\DTLlegendyoffset#*
\DTLplotmarks#*
\DTLplotmarkcolors#*
\DTLplotlines#*
\DTLplotlinecolors#*
\DTLXAxisStyle#*
\DTLYAxisStyle#*
\DTLmajorgridstyle#*
\DTLminorgridstyle#*
\DTLformatlegend{legend}#*

\DTLplotstream{db%special}{x key}{y key}
\DTLplotstream[condition]{db%special}{x key}{y key}