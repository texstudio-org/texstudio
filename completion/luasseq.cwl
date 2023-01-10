# luasseq package
# Matthew Bertucci 2023/01/10 for v2023/01/10

#include:luatex
#include:calc
#include:ifthen
#include:pgf
#include:pifont
#include:xkeyval

#keyvals:\usepackage/luasseq#c
debug#true,false
#endkeyvals

\begin{sseq}{x-range}{y-range}
\begin{sseq}[options%keyvals]{x-range}{y-range}
\end{sseq}

#keyvals:\begin{sseq}
grid=#none,crossword,go,dots,chess
gridstroke=##L
gapsize=##L
xgapsize=##L
ygapsize=##L
entrysize=##L
labels=#none,numbers,{%<x1;x2;...%>}
xlabels=#none,numbers,{%<x1;x2;...%>}
ylabels=#none,numbers,{%<x1;x2;...%>}
labelstep=%<integer%>
xlabelstep=%<integer%>
ylabelstep=%<integer%>
leak=##L
xleak=##L
yleak=##L
arrows=%<arrow type%>
packing=#auto,horizontal,vertical,diagonal
#endkeyvals

\ssmoveto{x}{y}
\ssmove{x}{y}

\ssdrop{mathcode%formula}
\ssdrop[options%keyvals]{mathcode%formula}
\ssdropbull{mathcode%formula}#*
\ssdropboxed{mathcode%formula}#*
\ssdropcircled{mathcode%formula}#*

#keyvals:\ssdrop,\ssdropextension
circled
boxed
color=#%color
name=%<name%>
#endkeyvals

\ssname{name}
\ssgoto{name}
\ssbeginprefixcontext
\ssendprefixcontext
\ssprefix{prefix}
\ssresetprefix
\ssabsgoto

\ssdroplabel{label}
\ssdroplabel[options%keyvals]{label}

#keyvals:\ssdroplabel
color=#%color
pos=#U,LU,L,LD,D,RD,R,RU
U
LU
L
LD
D
RD
R
RU
#endkeyvals

\ssdropextension
\ssdropextension[options%keyvals]

\ssstroke
\ssstroke[options%keyvals]
\sscurve{curve value}#*
\ssdashedstroke#*
\ssdashedcurve{curve value}#*
\ssdottedstroke#*
\ssdottedcurve{curve value}#*
\ssarrowhead
\ssarrowhead[arrow style]
\ssinversearrowhead
\ssinversearrowhead[arrow style]
\ssline{x}{y}
\ssline[options%keyvals]{x}{y}
\sscurvedline{curve value}{x}{y}#*
\ssdashedline{x}{y}#*
\sscurveddashedline{curve value}{x}{y}#*
\ssarrow{x}{y}
\ssarrow[options%keyvals]{x}{y}
\sscurvedarrow{curve value}{x}{y}#*
\ssdashedarrow{x}{y}#*
\sscurveddashedarrow{curve value}{x}{y}#*
\ssvoidline{x}{y}#*
\ssvoidline[options%keyvals]{x}{y}#*
\ssvoidarrow{x}{y}#*
\ssinversevoidarrow{x}{y}#*

#keyvals:\ssstroke,\ssline,\ssarrow,\ssvoidline
color=#%color
curve=%<value%>
dashed
dashed=%<dashing type%>
dotted
dotted=%<dashing type%>
arrowfrom
arrowfrom=%<dashing type%>
arrowto
arrowto=%<dashing type%>
void
#endkeyvals

\ssbullstring{x}{y}{n}
\ssinfbullstring{x}{y}{n}
\ssgrayout
\ssgrayout[color]

\ssconncolor#*
\sslabelcolor#*
\ssplacecolor#*
\sseqxstart#*
\sseqystart#*
\sseqbox#*
\ssplace{x}{y}{mathcode%formula}#*
\ssplaceboxed{x}{y}{mathcode%formula}#*
\ssplacecircled{x}{y}{mathcode%formula}#*
\for#S

sseqgr#B
sslightgr#B
ssred#B
ssblack#B
