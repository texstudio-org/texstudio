# datapie package
# Matthew Bertucci 2022/06/07 for v2.32

#include:xkeyval
#include:datatool
#include:tikz

#keyvals:\usepackage/datapie#c
color
gray
rotateinner
norotateinner
rotateouter
norotateouter
#endkeyvals

\DTLpiechart{settings%keyvals}{db%special}{values}
\DTLpiechart[condition]{settings%keyvals}{db%special}{values}

#keyvals:\DTLpiechart
variable=%<\var%>
start=%<angle%>
radius=##L
innerratio=%<factor%>
outerratio=%<factor%>
cutawayratio=%<factor%>
inneroffset=##L
outeroffset=##L
cutawayoffset=##L
cutaway={%<num1,num2,...%>}
cutaway={%<range1,range2,...%>}
innerlabel=%<text%>
outerlabel=%<text%>
rotateinner#true,false
rotateouter#true,false
#endkeyvals

\DTLpievariable#*
\DTLpiepercent#*
\DTLdisplayinnerlabel{text}#*
\DTLdisplayouterlabel{text}#*
\DTLsetpiesegmentcolor{index}{color}
\DTLdopiesegmentcolor{index}
\DTLdocurrentpiesegmentcolor
\DTLpieoutlinecolor#*
\DTLpieoutlinewidth#*
\DTLpieatbegintikz
\DTLpieatendtikz

# not in main documentation
\DTLcolorpiechartfalse#*
\DTLcolorpiecharttrue#*
\DTLcutawayratio#*
\DTLgetpiesegmentcolor{index}#*
\DTLinnerratio#*
\DTLouterratio#*
\DTLradius#*
\DTLrotateinnerfalse#*
\DTLrotateinnertrue#*
\DTLrotateouterfalse#*
\DTLrotateoutertrue#*
\DTLstartangle#*
\ifDTLcolorpiechart#*
\ifDTLrotateinner#*
\ifDTLrotateouter#*
\theDTLpieroundvar#*
