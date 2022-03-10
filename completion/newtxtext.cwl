# newtxtext package
# Matthew Bertucci 3/9/2022 for v1.71

#include:iftex
#include:xkeyval
#include:etoolbox
#include:textcomp
#include:xstring
#include:ifthen
#include:scalefnt
#include:mweight
#include:fontaxes

#keyvals:\usepackage/newtxtext#c
type1#true,false
type1text#true,false
otfmath#true,false
nofontspec#true,false
defaultfeatures={%<fontspec options%>}
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
tabular#true,false
t#true,false
proportional#true,false
p#true,false
scaled=%<factor%>
defaultsups#true,false
largesc#true,false
nohelv#true,false
nott#true,false
helvratio=%<factor%>
spcfactor=%<factor%>
spacing=##L
stretch=##L
shrink=##L
oldSS
slashedzero
theoremfont
thmslshape
thmlining
trueslanted
scosf
tighter
looser
#endkeyvals

\defigures#*
\destyle
\infigures
\instyle#*
\lfstyle
\liningnums{text}
\nufigures#*
\nustyle
\oldstylenums{text}
\osfstyle
\proportionalnums{text}
\sufigures#*
\sustyle
\tabularnums{text}
\textde{text}
\textdenominator{text}#*
\textfrac[whole part]{numerator}{denominator}
\textfrac{numerator}{denominator}
\textinf{text}
\textinferior{text}#*
\textlf{text}
\textnu{text}
\textnumerator{text}#*
\textosf{text}
\textsu{text}
\textsuperior{text}#*
\textth{text}
\textthit{text}#*
\texttlf{text}
\texttosf{text}
\thdefault#*
\thfamily
\tlfstyle
\tosfstyle
\useosf#*
\useproportional#*

\fileversion#S
\filedate#S

# from binhex.tex
\binary{number}#*
\nbinary{size}{number}#*
\hex{number}#*
\nhex{size}{number}#*
\oct{number}#*
\noct{size}{number}#*
\tetra{number}#*
\ntetra{size}{number}#*
\nbinbased{logbase}{size}{number}#*
