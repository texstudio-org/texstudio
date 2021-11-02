# datapie package
# Matthew Bertucci 10/31/2021 for v2.32

#include:xkeyval
#include:datatool
#include:tikz

\DTLpiechart{settings%keyvals}{db%special}{values}
\DTLpiechart[condition]{settings%keyvals}{db%special}{values}

#keyvals:\DTLpiechart
variable=
start=%<angle%>
radius=##L
innerratio=
outerratio=
cutawayratio=
inneroffset=##L
outeroffset=##L
cutawayoffset=##L
cutawayoffset=
cutaway=
innerlabel=
outerlabel=
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