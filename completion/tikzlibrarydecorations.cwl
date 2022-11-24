# decorations tikzlibrary
# 2022/11/20 for v3.1.9a

# loads decorations pgfmodule

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
decoration={%<options%>}
decorate#true,false
#endkeyvals

# from decorations pgfmodule (only documented cmds listed here; all others in pgfcore.cwl)
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
\pgfdeclaremetadecoration{name}{initial state}{states}#*
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
\begin{pgfmetadecoration}{name}#*
\end{pgfmetadecoration}#*