# databar package
# Matthew Bertucci 2022/06/07 for v2.32

#include:xkeyval
#include:dataplot
#include:datatool
#include:tikz

#keyvals:\usepackage/databar#c
color
gray
vertical
horizontal
#endkeyvals

\DTLbarchart{settings%keyvals}{db%special}{values}
\DTLbarchart[condition]{settings%keyvals}{db%special}{values}
\DTLmultibarchart{settings%keyvals}{db%special}{values}
\DTLmultibarchart[condition]{settings%keyvals}{db%special}{values}

#keyvals:\DTLbarchart
variable=%<\var%>
upperbarlabel=%<text%>
#endkeyvals

#keyvals:\DTLmultibarchart
variables={%<\var1,\var2,...%>}
multibarlabels={%<text1,text2,...%>}
uppermultibarlabels={%<text1,text2,...%>}
groupgap=##L
#endkeyvals

#keyvals:\DTLbarchart,\DTLmultibarchart
max=%<decimal%>
length=##L
maxdepth=%<decimal%>
axes=#both,x,y,none
barlabel=%<text%>
yticpoints={%<decimal1,decimal2,...%>}
yticgap=##L
yticlabels={%<text1,text2,...%>}
ylabel=%<text%>
verticalbars#true,false
barwidth=##L
#endkeyvals

\DTLbarchartlength#*
\DTLbarwidth#*
\DTLbarlabeloffset#*
\DTLsetbarcolor{index}{color}
\DTLdobarcolor{index}
\DTLbaroutlinecolor#*
\DTLbaroutlinewidth#*
\DTLbaratbegintikz
\DTLbaratendtikz
\DTLeverybarhook#*
\DTLstartpt#*
\DTLmidpt#*
\DTLendpt#*
\ifDTLverticalbars#*
\DTLverticalbarstrue#*
\DTLverticalbarsfalse#*
\ifDTLcolorbarchart#*
\DTLcolorbarcharttrue#*
\DTLcolorbarchartfalse#*
\ifDTLbarxaxis#*
\DTLbarxaxistrue#*
\DTLbarxaxisfalse#*
\ifDTLbaryaxis#*
\DTLbaryaxistrue#*
\DTLbaryaxisfalse#*
\ifDTLbarytics#*
\DTLbaryticstrue#*
\DTLbaryticsfalse#*
\DTLbarXlabelalign#*
\DTLbarYticklabelalign#*
\DTLbardisplayYticklabel{text}#*
\DTLdisplaylowerbarlabel{text}#*
\DTLdisplaylowermultibarlabel{text}#*
\DTLdisplayupperbarlabel{text}#*
\DTLdisplayuppermultibarlabel{text}#*
\DTLbarchartwidth#*
\DTLbargroupwidth#*
\DTLnegextent#*
\DTLbarmax#*

# not in main documentation
\DTLbarvariable#*
\DTLBarXAxisStyle#*
\DTLBarYAxisStyle#*
\DTLdocurrentbarcolor#*
\DTLgetbarcolor{index}#*
\theDTLbarroundvar#*
