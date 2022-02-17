# guitartabs class
# Matthew Bertucci 2/15/2022

#include:inputenc
#include:geometry
#include:xifthen
#include:tikz
#include:musixtex
#include:harmony
#include:intcalc

# options passed to article class
#keyvals:\documentclass/guitartabs#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\artistname{name}
\albumtitle{title%text}
\songname{name}
\maketabheader
\thetabstrings#*
\thetabbars#*
\thetabcstring#*
\thetabcbar#*
\thetabcn#*
\thetabcdn#*
\theflag#*
\begin{tabline}{bars}{ts-upper}{ts-lower}{tuning}
\end{tabline}
\gtuning#*
\timesigtop#*
\timesigbot#*
\tabwidth#*
\ypostimetop#*
\ypostimebot#*
\nextbar
\note{numerator}{denominator}{string}{fret}
\xpos#S
\notel{numerator}{denominator}{string}{fret}{length}
\restwhole{numerator}{denominator}
\resthalf{numerator}{denominator}
\restquarter{numerator}{denominator}
\resteighth{numerator}{denominator}
\restsixteenth{numerator}{denominator}