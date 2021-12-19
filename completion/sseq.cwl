# sseq package
# Matthew Bertucci 12/12/2021 for v1.01

#include:ifthen
#include:calc
#include:pifont
#include:pgf
#include:xkeyval
# loads decorations.pathmorphing pgflibrary

#keyvals:\usepackage/sseq#c
color
nocolor
debug
#endkeyvals

\begin{sseq}{x-range}{y-range}
\begin{sseq}[options%keyvals]{x-range}{y-range}
\end{sseq}

#keyvals:\begin{sseq}
grid=#none,crossword,go,dots,chess
entrysize=##L
labels=%<labels%>
xlabels=%<labels%>
ylabels=%<labels%>
labelstep=%<integer%>
xlabelstep=%<integer%>
ylabelstep=%<integer%>
gapsize=##L
xgapsize=##L
ygapsize=##L
gridstroke=##L
leak=##L
xleak=##L
yleak=##L
arrows=%<arrow type%>
#endkeyvals

\sseqpacking
\sspacksmart
\sspackhorizontal
\sspackvertical
\sspackdiagonal

\ssmoveto{x}{y}#/sseq
\ssmove{x}{y}#/sseq

\ssdrop{math%formula}#/sseq
\ssdrop[options%keyvals]{math%formula}#/sseq

#keyvals:\ssdrop
circled
boxed
color=#%color
name=%<name%>
#endkeyvals

\ssname{name}#/sseq
\ssgoto{name}#/sseq
\ssprefix{prefix}#/sseq
\ssresetprefix#/sseq
\ssabsgoto{name}#/sseq

\ssdroplabel{label}#/sseq
\ssdroplabel[options%keyvals]{label}#/sseq

#keyvals:\ssdroplabel
U
LU
RU
L
R
LD
RD
D
color=#%color
#endkeyvals

\ssdropextension#/sseq

\ssstroke#/sseq
\ssstroke[options%keyvals]#/sseq

#keyvals:\ssstroke,\ssline,\ssarrow
color=#%color
curve=%<value%>
dashed
dashed=%<dash type%>
dotted
dotted=%<dash type%>
arrowfrom
arrowfrom=%<arrow style%>
arrowto
arrowto=%<arrow style%>
void
#endkeyvals

\ssarrowhead#/sseq
\ssarrowhead[arrow style]#/sseq
\ssinversearrowhead#/sseq
\ssinversearrowhead[arrow style]#/sseq

\ssline{x}{y}#/sseq
\ssline[options%keyvals]{x}{y}#/sseq
\ssarrow{x}{y}#/sseq
\ssarrow[options%keyvals]{x}{y}#/sseq
\ssbullstring{x}{y}{n}#/sseq
\ssinfbullstring{x}{y}{n}#/sseq

\ssdropbull#*/sseq
\ssdropboxed{math%formula}#*/sseq
\ssdropcircled{math%formula}#*/sseq
\sscurve{value}#*/sseq
\ssdashedstroke#*/sseq
\ssdashedcurve{value}#*/sseq
\ssdottedstroke#*/sseq
\ssdottedcurve{value}#*/sseq
\sscurvedline{value}{x}{y}#*/sseq
\ssdashedline{x}{y}#*/sseq
\sscurveddashedline{value}{x}{y}#*/sseq
\sscurvedarrow{value}{x}{y}#*/sseq
\ssdashedarrow{x}{y}#*/sseq
\sscurveddashedarrow{value}{x}{y}#*/sseq
\ssvoidline{x}{y}#*/sseq
\ssvoidarrow{x}{y}#*/sseq
\ssinversevoidarrow{x}{y}#*/sseq
\ssplaceboxed{arg1}{arg2}{math%formula}#*/sseq
\ssplacecircled{arg1}{arg2}{math%formula}#*/sseq
\ssplace{arg1}{arg2}{math%formula}#*/sseq

\currprefix#*
\dropvarname{arg1}{arg2}#*
\extractcoords#*
\ifcurroutofrange#*
\ifoutofrange#*
\outofrangetrue#*
\outofrangefalse#*
\ifnodrop{arg1}{arg2}#*
\ifuniquedrop{arg1}{arg2}#*
\ntimes{arg1}{arg2}#*
\putxyq{code}#*
\putxy{code}#*
\setcnt#*
\ssassertsource#*
\ssconncolor#*
\ssdroperrormsg{arg1}{arg2}#*#*
\sseqbullcnt#*
\sseqconcludeconnection#*
\sseqconncommand#*
\sseqgridstyle#*
\sseqpack{arg1}{arg2}#*
\sseqrearrange{arg1}{arg2}{arg3}{arg4}{arg5}#*
\sseqsavecnti#*
\sseqsavecntii#*
\sseqsavecntiii#*
\sseqsavecntiv#*
\sseqsavecntix#*
\sseqsavecnto#*
\sseqsavecntv#*
\sseqsavecntvi#*
\sseqsavecntvii#*
\sseqsavecntviii#*
\sseqstacking{x}{y}{n}#*
\sseqwritecolor{color}#*
\sseqxlabel#*
\sseqylabel#*
\ssfinishpos#*
\ssglobalname{name}#*
\ssgridchess{arg1}{arg2}#*
\ssgridcrossword{arg1}{arg2}#*
\ssgriddots{arg1}{arg2}#*
\ssgridgo{arg1}{arg2}#*
\ssgridnone{arg1}{arg2}#*
\sslabelcolor#*
\ssplacecolor#*
\ssprepareline{arg1}{arg2}#*
\sssetglobalname{name}#*

\act#S
\for#S
\lst#S
\temp#S
\tempcmd#S
\tempoutercmd#S
\temptwo#S
\tmpcnt#S
\tmpname#S
\tmpval#S

## from decorations pgfmodule, loaded by decorations.pathmorphing pgflibrary
\pgfdecoratedcompleteddistance#*
\pgfdecoratedremainingdistance#*
\pgfdecoratedinputsegmentcompleteddistance#*
\pgfdecoratedinputsegmentremainingdistance#*
\pgfdecorationsegmentamplitude#*
\pgfdecorationsegmentlength#*
\pgfdecorationsegmentangle#*
\pgfdecorationsegmentaspect#*
\pgfmetadecorationsegmentamplitude#*
\pgfmetadecorationsegmentlength#*
\ifpgfdecoratepathhascorners#*
\pgfdecoratepathhascornerstrue#*
\pgfdecoratepathhascornersfalse#*
\pgfdeclaredecoration{name}{initial state}{states}#*
\state{name}{code}#*
\state{name}[options%keyvals]{code}#*
#keyvals:\state#c
switch if less than=%<dimen%> to %<new state%>
switch if input segment less than=%<dimen%> to %<new state%>
width=##L
repeat state=%<repetitions%>
next state=%<new state%>
if input segment is closepath={%<options%>}
auto end on length=##L
auto corner on length=##L
persistent precomputation=%<precode%>
persistent postcomputation=%<postcode%>
#endkeyvals
\pgfifdecoration{name}{if code}{else code}#*
\pgfdeclaremetadecoration{name}{initial state}{states}#*
\pgfifmetadecoration{name}{if code}{else code}#*
\decoration{name}#*
\beforedecoration{before code}#*
\afterdecoration{after code}#*
\pgfmetadecoratedpathlength#*
\pgfmetadecoratedcompleteddistance#*
\pgfmetadecoratedinputsegmentcompleteddistance#*
\pgfmetadecoratedinputsegmentremainingdistance#*
\pgfdecoratebeforecode#*
\pgfdecorateaftercode#*
\pgfdecoratepath{name}{path commands}#*
\pgfdecoratecurrentpath{name}#*
\begin{pgfdecoration}{name}#*
\end{pgfdecoration}#*
\pgfdecoration{name}#S
\endpgfdecoration#S
\pgfdecorationpath#*
\pgfdecoratedpath#*
\pgfdecorateexistingpath#*
\pgfdecoratedpathlength#*
\pgfpointdecoratedpathfirst#*
\pgfpointdecoratedpathlast#*
\pgfpointdecoratedinputsegmentfirst#*
\pgfpointdecoratedinputsegmentlast#*
\pgfsetdecorationsegmenttransformation{code}#*
\pgfmetadecoratedremainingdistance#*
\pgfpointmetadecoratedpathfirst#*
\pgfpointmetadecoratedpathlast#*
\pgfdecoratedinputsegmentlength#*
\pgfdecoratedangle#*
\pgfdecoratedinputsegmentstartangle#*
\pgfdecoratedinputsegmentendangle#*
\pgfdecorationcurrentinputsegment#*
\pgfdecorationnextinputsegmentobject#*
\pgfdecorationinputsegmentmoveto#*
\pgfdecorationinputsegmentlineto#*
\pgfdecorationinputsegmentcurveto#*
\pgfdecorationinputsegmentclosepath#*
\pgfdecorationinputsegmentlast#*
\ifpgfdecoraterectangleclockwise#*
\pgfdecoraterectangleclockwisetrue#*
\pgfdecoraterectangleclockwisefalse#*
\begin{pgfmetadecoration}{name}#*
\end{pgfmetadecoration}#*
\pgfmetadecoration{name}#S
\endpgfmetadecoration#S