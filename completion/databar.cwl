# databar package
# Matthew Bertucci 10/31/2021 for v2.32

#include:xkeyval
#include:dataplot
#include:datatool
#include:tikz

\DTLbarchart{settings%keyvals}{db%special}{values}
\DTLbarchart[condition]{settings%keyvals}{db%special}{values}
\DTLmultibarchart{settings%keyvals}{db%special}{values}
\DTLmultibarchart[condition]{settings%keyvals}{db%special}{values}

#keyvals:\DTLbarchart
variable=
upperbarlabel=
#endkeyvals

#keyvals:\DTLmultibarchart
variables=
multibarlabels=
uppermultibarlabels=
groupgap=##L
#endkeyvals

#keyvals:\DTLbarchart,\DTLmultibarchart
max=
length=##L
maxdepth=
axes=#both,x,y,none
barlabel=
yticpoints=
yticgap=##L
yticlabels=
ylabel=
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
\ifDTLverticalbars#*
\DTLverticalbarstrue#*
\DTLverticalbarsfalse#*
\DTLbarXlabelalign#*
\DTLbarYlabelalign#*
\DTLbardisplayYticklabel{text}#*
\DTLdisplaylowerbarlabel{text}#*
\DTLdisplaylowermultibarlabel{text}#*
\DTLdisplayupperbarlabel{text}#*
\DTLdisplayuppermultibarlabel{text}#*
\DTLbarchartwidth#*
\DTLnegextent#*
\DTLbarmax#*