# dataplot package
# Matthew Bertucci 2022/06/07 for v2.32

#include:xkeyval
#include:tikz
#include:tikzlibraryplotmarks
#include:tikzlibrarycalc
#include:datatool

\DTLplot{db list%special}{settings%keyvals}
\DTLplot[condition]{db list%special}{settings%keyvals}

#keyvals:\DTLplot
x=%<db key%>
y=%<db key%>
markcolors={%<color1,color2,...%>}
linecolors={%<color1,color2,...%>}
colors={%<color1,color2,...%>}
marks={%<mark1,mark2,...%>}
lines={%<linestyle1,linestyle2,...%>}
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
bounds={%<min-x,min-y,max-x,max-y%>}
minx=%<decimal%>
miny=%<decimal%>
maxx=%<decimal%>
maxy=%<decimal%>
xticpoints={%<decimal1,decimal2,...%>}
xticgap=##L
yticpoints={%<decimal1,decimal2,...%>}
yticgap=##L
grid#true,false
xticlabels={%<text1,text2,...%>}
yticlabels={%<text1,text2,...%>}
xlabel=%<text%>
ylabel=%<text%>
legend=#none,north,northeast,east,southeast,south,southwest,west,northwest
legendlabels={%<text1,text2,...%>}
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

# not in main documentation
\DTLboxfalse#*
\DTLboxtrue#*
\DTLgridfalse#*
\DTLgridtrue#*
\DTLmaxX#*
\DTLmaxY#*
\DTLminminortickgap#*
\DTLminX#*
\DTLminY#*
\DTLshowlinesfalse#*
\DTLshowlinestrue#*
\DTLshowmarkersfalse#*
\DTLshowmarkerstrue#*
\DTLxaxisfalse#*
\DTLxaxistrue#*
\DTLxminorticsfalse#*
\DTLxminorticstrue#*
\DTLxticsfalse#*
\DTLxticsinfalse#*
\DTLxticsintrue#*
\DTLxticstrue#*
\DTLyaxisfalse#*
\DTLyaxistrue#*
\DTLyminorticsfalse#*
\DTLyminorticstrue#*
\DTLyticsfalse#*
\DTLyticsinfalse#*
\DTLyticsintrue#*
\DTLyticstrue#*
\ifDTLbox#*
\ifDTLgrid#*
\ifDTLshowlines#*
\ifDTLshowmarkers#*
\ifDTLxaxis#*
\ifDTLxminortics#*
\ifDTLxtics#*
\ifDTLxticsin#*
\ifDTLyaxis#*
\ifDTLyminortics#*
\ifDTLytics#*
\ifDTLyticsin#*
\theDTLplotroundXvar#*
\theDTLplotroundYvar#*
