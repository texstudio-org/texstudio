# fancylabel package
# Matthew Bertucci 1/8/2021 for v1.1

#include:xkeyval
#include:xifthen
#include:suffix

#keyvals:\usepackage/fancylabel#c
families={%<list of families%>}
IgnoreFamilies#true,false
numbering=#continuous,ondemand,referenced
level=#sub,same
sort#true,false
compress#true,false
CompressLink=%<separator%>
CompressTwo#true,false
ListLastSublabelOnly#true,false
ListSeparator=%<separator%>
ListLastLabelSeparator=%<separator%>
ListLastRefSeparator=%<separator%>
DisableFamilyCheck#true,false
#endkeyvals

\fancylabel{marker%labeldef}#l
\fancylabel[family]{marker%labeldef}#l
\fancylabel*{marker%labeldef}#l
\fancylabel*[family]{marker%labeldef}#l

\fancysublabel{marker%labeldef}{submarker}#l
\fancysublabel[family]{marker%labeldef}{submarker}#l
\fancysublabel*{marker%labeldef}{submarker}#l
\fancysublabel*[family]{marker%labeldef}{submarker}#l

\fancyref{marker%ref}#r
\fancyref[family]{marker%ref}#r
\fancyref*{marker%ref}#r
\fancyref*[family]{marker%ref}#r

\fancysubref{marker%ref}{submarker}#r
\fancysubref[family]{marker%ref}{submarker}#r
\fancysubref-{marker%ref}{submarker}#r
\fancysubref-[family]{marker%ref}{submarker}#r
\fancysubref*{marker%ref}{submarker}#r
\fancysubref*[family]{marker%ref}{submarker}#r

\fancylabelformatdefault#*
\fancysublabelformatdefault#*
\fancyonlysublabelformatdefault#*
\fancylabelNewLabelEvent#*
\fancylabelShowLabelEvent#*
\fancylabelShowRefEvent#*
\thefancylabel#*
\thefancysublabel#*

# not documented
\fancylabelResetCounter{arg}#S
\fancylabelthisformat#S