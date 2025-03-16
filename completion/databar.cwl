# databar package
# Matthew Bertucci 2025/03/06 for v3.0

#include:dataplot
#include:datatool
#include:tikz

#keyvals:\usepackage/databar#c
color
gray
verticalbars#true,false
vertical
horizontal
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
bar={%<keyvals%>}
#endkeyvals

\DTLbarchart{settings%keyvals}{db%special}{assign list}
\DTLbarchart[condition]{settings%keyvals}{db%special}{assign list}
\DTLmultibarchart{settings%keyvals}{db%special}{assign list}
\DTLmultibarchart[condition]{settings%keyvals}{db%special}{assign list}

#keyvals:\DTLbarchart
variable=%<\var%>
upperbarlabel=%<text%>
upper-bar-label=%<text%>
#endkeyvals

#keyvals:\DTLmultibarchart
variables={%<\var1,\var2,...%>}
groupgap=##L
group-gap=##L
multibarlabels={%<text1,text2,...%>}
multi-bar-labels={%<text1,text2,...%>}
uppermultibarlabels={%<text1,text2,...%>}
upper-multi-bar-labels={%<text1,text2,...%>}
group-label-align=%<value%>
#endkeyvals

#keyvals:\DTLbarchart,\DTLmultibarchart
init=%<code%>
pre-init=%<code%>
include-if=%<definition%>
include-if-in=%<cmd%>
verticalbars#true,false
vertical
horizontal
lower-label-style=#opposite,same,above,below
upper-label-align={%<+ve align%>}
upper-label-align=[%<-ve align%>]{%<+ve align%>}
length=##L
barwidth=##L
bar-width=##L
bargap=##L
bar-gap=##L
color-style=#default,single,cycle
bar-colors={%<color1,color2,...%>}
bar-default-colors
bar-default-gray
negative-bar-colors={%<color1,color2,...%>}
negative-color-style=#default,single,cycle
outline-width=##L
outline-color=#%color
barlabel=%<text%>
bar-label=%<text%>
label-offset=##L
upper-label-offset=##L
axes=#both,x,y,none
y-axis#true,false
yaxis#true,false
y-ticks#true,false
ytics#true,false
round=%<integer%>
y-tick-round=%<integer%>
ytic-round=%<integer%>
ylabel=%<text%>
ylabel-position=#center,zero,min,max
max=%<decimal%>
maxdepth=%<decimal%>
max-depth=%<decimal%>
y-tick-gap=##L
yticgap=##L
y-tick-points={%<decimal1,decimal2,...%>}
yticpoints={%<decimal1,decimal2,...%>}
y-tick-labels={%<text1,text2,...%>}
yticlabels={%<text1,text2,...%>}
y-tic-label-align=%<value%>
ytic-label-align=%<value%>
y-tick-label-align=%<value%>
#endkeyvals

\ifDTLverticalbars#*
\DTLverticalbarstrue#*
\DTLverticalbarsfalse#*
\DTLbarchartlength#*
\DTLbarmax#*
\DTLnegextent#*
\DTLBarXAxisStyle#*
\DTLBarYAxisStyle#*
\DTLBarStyle#*
\theDTLbarroundvar#*
\DTLbarvariable#*
\DTLbarvalue#*
\DTLbarindex#*
\DTLbargroupindex#*
\DTLbarwidth#*
\DTLbarlabeloffset#*
\DTLbarXlabelalign#*
\DTLbarXneglabelalign#*
\DTLbarXupperlabelalign#*
\DTLbarXnegupperlabelalign#*
\DTLbarsetupperlabelalign{+ve align}#*
\DTLbarsetupperlabelalign[-ve align]{+ve align}#*
\DTLbargrouplabelalign#*
\DTLbarYticklabelalign#*
\DTLbardisplayYticklabel{text}#*
\DTLdisplaylowerbarlabel{text}#*
\DTLdisplaybargrouplabel{text}#*
\DTLdisplaylowermultibarlabel{text}#*
\DTLdisplayupperbarlabel{text}#*
\DTLdisplayuppermultibarlabel{text}#*
\DTLbaroutlinecolor#*
\DTLbaroutlinewidth#*
\DTLsetbarcolor{index}{color}#*
\DTLclearbarcolors#*
\DTLsetnegbarcolor{index}{color}#*
\DTLclearnegbarcolors#*
\DTLgetbarcolor{index}#*
\DTLgetnegbarcolor{index}#*
\DTLdobarcolor{index}#*
\DTLdocurrentbarcolor#*
\DTLeverybarhook#*
\DTLeveryprebarhook#*
\DTLstartpt#*
\DTLmidpt#*
\DTLendpt#*
\DTLeverybargrouphook#*
\DTLbaratbegintikz#*
\DTLbaratendtikz#*
\DTLbarchartwidth#*
\DTLbargroupwidth#*
\DTLtotalbars#*
\DTLbartotalvariables#*
\DTLtotalbargroups#*

# misc
\ifDTLbarxaxis#*
\DTLbarxaxistrue#*
\DTLbarxaxisfalse#*
\ifDTLbaryaxis#*
\DTLbaryaxistrue#*
\DTLbaryaxisfalse#*
\ifDTLbarytics#*
\DTLbaryticstrue#*
\DTLbaryticsfalse#*

# not documented
\ifDTLcolorbarchart#S
\DTLcolorbarcharttrue#S
\DTLcolorbarchartfalse#S