# pgf package
# Benito van der Zander, 14 May 2011, init contribute
# Matthew Bertucci updated 12/1/2021 for v3.1.9a

# pgf.sty
# ├── pgfrcs.sty
# ├── pgfcore.sty
# ├── pgfmoduleshapes.code.tex
# └── pgfmoduleplot.code.tex

#include:pgfrcs
#include:pgfcore

#keyvals:\usepackage/pgf#c
draft
version=#0.65,0.96,1.18,latest
#endkeyvals

# plot pgfmodule
\pgfplotstreamstart#*
\pgfplotstreampoint{point}#*
\pgfplotstreampointoutlier{point}#*
\pgfplotstreampointundefined#*
\pgfplotstreamnewdataset#*
\pgfplotstreamspecial{text}#*
\pgfplotstreamend#*
\pgfdeclareplothandler{macro%cmd}{args}{options%keyvals}#*d
#keyvals:\pgfdeclareplothandler#c
start=%<code%>
end=%<code%>
point=%<code%>
jump=%<code%>
special=%<code%>
point macro=%<macro%>
special macro=%<macro%>
start macro=%<macro%>
end macro=%<macro%>
jump macro=%<macro%>
#endkeyvals
\pgfsetlinetofirstplotpoint#*
\pgfsetmovetofirstplotpoint#*
\pgfplothandlerlineto#*
\pgfplothandlerpolygon#*
\pgfplothandlerdiscard#*
\pgfplothandlerrecord{macro%cmd}#*d
\pgfplotxyfile{file}#*
\pgfplotxyzfile{file}#*
\pgfplotgnuplot{gnuplot function}#*
\pgfplotgnuplot[prefix]{gnuplot function}#*
\pgfplotfunction{variable%cmd}{sample list}{point}#*d

# shapes pgfmodule
\pgfnodeparttextbox#*
\pgfmultipartnode{shape}{anchor}{name}{path usage cmd}#*
\pgfnode{shape}{anchor}{label text}{name}{path usage cmd}#*
\pgfpositionnodelater{macro}#*
\pgfpositionnodelatername#*
\pgfpositionnodelaterminx#*
\pgfpositionnodelatermaxx#*
\pgfpositionnodelaterminy#*
\pgfpositionnodelatermaxy#*
\ifpgflatenodepositioning#*
\pgflatenodepositioningtrue#*
\pgflatenodepositioningfalse#*
\pgfpositionnodelaterbox#*
\pgfpositionnodenow{coordinate}#*
\pgffakenode{node name}#*
\pgfnodepostsetupcode{node name}{code}#*
\pgfnodealias{new name}{existing name}#*
\pgfnoderename{new name}{existing name}#*
\pgfcoordinate{name}{coordinate}#*
\pgfdeclaregenericanchor{anchor}{code}#*
\pgfpointanchor{node}{anchor}#*
\pgfpointshapeborder{node}{point}#*
\pgfgetnodeparts{macro}{shape name}#*d
\pgfdeclareshape{shape name}{shape spec}#*
\centerpoint#S
\ifpgfshapeborderusesincircle#*
\pgfshapeborderusesincircletrue#*
\pgfshapeborderusesincirclefalse#*
\northeast#S
\southwest#S
\radius#S
\nodeparts{list of node parts}#*
\savedanchor{cmd}{code}#*d
\saveddimen{cmd}{code}#*d
\savedmacro{cmd}{code}#*d
\addtosavedmacro{macro}#*
\anchor{name}{code}#*
\deferredanchor{name}{code}#*
\anchorborder{code}#*
\backgroundpath{code}#*
\foregroundpath{code}#*
\behindbackgroundpath{code}#*
\beforebackgroundpath{code}#*
\behindforegroundpath{code}#*
\beforeforegroundpath{code}#*
\inheritsavedanchors#*
\inheritsavedanchors[from={%<shape name%>}]#*
\inheritbehindbackgroundpath#*
\inheritbehindbackgroundpath[from={%<shape name%>}]#*
\inheritbackgroundpath#*
\inheritbackgroundpath[from={%<shape name%>}]#*
\inheritbeforebackgroundpath#*
\inheritbeforebackgroundpath[from={%<shape name%>}]#*
\inheritbehindforegroundpath#*
\inheritbehindforegroundpath[from={%<shape name%>}]#*
\inheritforegroundpath#*
\inheritforegroundpath[from={%<shape name%>}]#*
\inheritbeforeforegroundpath#*
\inheritbeforeforegroundpath[from={%<shape name%>}]#*
\inheritanchor#*
\inheritanchor[from={%<shape name%>}]{name}#*
\inheritanchorborder#*
\inheritanchorborder[from={%<shape name%>}]#*
