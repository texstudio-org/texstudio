# page-canons package
# Matthew Bertucci 2026/05/22 for v3.9.3

#include:iftex
#include:ifoddpage
#include:geometry

\pagecanonsetup{keyvals}

#keyvals:\usepackage/page-canons#c,\pagecanonsetup
canon=#vdg,vdh,tufte,ateliers,grid,false
vdhN=#3,6,9,12,15
ateliersstyle=#ordinary,neater,luxury
gridN=%<integer%>
gridinner=%<integer%>
gridouter=%<integer%>
gridtop=%<integer%>
gridbottom=%<integer%>
margins=#symmetric,antisymmetric,right,left
gutterval=##L
guttermode=#geometry,satzspiegel
showframe
landscape
debug
size=%<fontsize name%>
justification=#default,raggedright,raggedleft,centered,justified
notespread=%<factor%>
numbering=#global,persection,perchapter,perpage
nomarginalia
marginsize#true,false
marginnotesize=%<fontsize name%>
sidenotesize=%<fontsize name%>
marginjustify#true,false
marginnotejustify=#default,raggedright,raggedleft,centered,justified
sidenotejustify=#default,raggedright,raggedleft,centered,justified
paper=%<type%>
#endkeyvals

\begin{fullwidth}
\begin{fullwidth}[options%keyvals]
\end{fullwidth}

#keyvals:\begin{fullwidth}
skip
justification
#endkeyvals

\pagecanonmargins
\marginnote{text}
\marginnote{text}[dimen]
\sidenote{text}
\sidenote{text}[dimen]
\sidenote[n]{text}
\sidenote[n]{text}[dimen]
\sidenotetext{text}
\sidenotetext{text}[dimen]
\sidenotemark
\sidenotemark[n]
\canonssidenotemarkformat{n}
\canonssidenotelabelformat{n}
\canonsswitchmargin
\canonsresetmargin

\marginandtext#L
\marginandsep#L
\textandsep#L
\fullwidthoverhang#L
\overflowingheadlen#L

\marginfont#*
\canonsmarginfont#*