# datapie package
# Matthew Bertucci 2025/03/06 for v3.0

#include:datatool
#include:tikz

#keyvals:\usepackage/datapie#c
color
gray
rotateinner
norotateinner
rotateouter
norotateouter
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
pie={%<keyvals%>}
#endkeyvals

\DTLpiechart{settings%keyvals}{db%special}{assign list}
\DTLpiechart[condition]{settings%keyvals}{db%special}{assign list}

#keyvals:\DTLpiechart
variable=%<\var%>
include-if=%<definition%>
include-if-fn=%<cmd%>
cutaway={%<num1,num2,...%>}
cutaway={%<range1,range2,...%>}
cutawayratio=%<factor%>
cutaway-ratio=%<factor%>
cutawayoffset=##L
cutaway-offset=##L
outline-width=##L
outline-color=#%color
radius=##L
radius*=##L
segment-colors={%<color1,color2,...%>}
segment-default-colors
segment-default-gray
start=%<angle%>
innerlabel=%<text%>
inner-label=%<text%>
innerratio=%<factor%>
inner-ratio=%<factor%>
inneroffset=##L
inner-offset=##L
outerlabel=%<text%>
outer-label=%<text%>
outeroffset=##L
outer-offset=##L
rotateinner#true,false
rotate-inner#true,false
rotateouter#true,false
rotate-outer#true,false
round=%<integer%>
outerratio=%<factor%>
outer-ratio=%<factor%>
#endkeyvals

\DTLpievariable#*
\DTLpiepercent#*
\theDTLpieroundvar#*
\DTLdisplayinnerlabel{text}#*
\DTLdisplayouterlabel{text}#*
\DTLsetpiesegmentcolor{index}{color}#*
\DTLdopiesegmentcolor{index}#*
\DTLgetpiesegmentcolor{index}#*
\DTLdocurrentpiesegmentcolor#*
\DTLpieoutlinecolor#*
\DTLpieoutlinewidth#*L
\DTLpieatsegment{index}{total}{start angle}{mid angle}{end angle}{shift angle}{shift offset}{inner offset}{outer offset}#*
\DTLpieatbegintikz#*
\DTLpieatendtikz#*

# not documented
\DTLcolorpiechartfalse#S
\DTLcolorpiecharttrue#S
\DTLcutawayratio#S
\DTLinnerratio#S
\DTLouterratio#S
\DTLradius#S
\DTLrotateinnerfalse#S
\DTLrotateinnertrue#S
\DTLrotateouterfalse#S
\DTLrotateoutertrue#S
\DTLstartangle#S
\ifDTLcolorpiechart#S
\ifDTLrotateinner#S
\ifDTLrotateouter#S