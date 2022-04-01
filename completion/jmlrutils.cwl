# jmlrutils package
# Matthew Bertucci 3/25/2022 for v1.30

#include:etoolbox
#include:amsmath

#keyvals:\usepackage/jmlrutils#c
maths
nomaths
math
nomath
theorems
notheorems
cleveref
nocleveref
subfloats
nosubfloats
#endkeyvals

#ifOption:cleveref
#include:aliascnt
#include:cleveref
#endif

\algocfconts{label}{caption%text}{content%text}#l
\algorithmref{labellist}#r
\algorithmrefname#*
\algorithmsrefname#*
\altdescriptionlabel{label}#*
\appendixref{labellist}#r
\appendixrefname#*
\appendixsrefname#*
\axiomref{labellist}#r
\axiomrefname#*
\axiomsrefname#*
\begin{algorithm}
\begin{algorithm}[placement]
\begin{altdescription}{widest label}
\begin{axiom}
\begin{axiom}[heading%text]
\begin{conjecture}
\begin{conjecture}[heading%text]
\begin{corollary}
\begin{corollary}[heading%text]
\begin{definition}
\begin{definition}[heading%text]
\begin{enumerate*}
\begin{example}
\begin{example}[heading%text]
\begin{lemma}
\begin{lemma}[heading%text]
\begin{proof}
\begin{proposition}
\begin{proposition}[heading%text]
\begin{remark}
\begin{remark}[heading%text]
\begin{theorem}
\begin{theorem}[heading%text]
\conjectureref{labellist}#r
\conjecturerefname#*
\conjecturesrefname#*
\corollaryref{labellist}#r
\corollaryrefname#*
\corollarysrefname#*
\definitionref{labellist}#r
\definitionrefname#*
\definitionsrefname#*
\end{algorithm}
\end{altdescription}
\end{axiom}
\end{conjecture}
\end{corollary}
\end{definition}
\end{enumerate*}
\end{example}
\end{lemma}
\end{proof}
\end{proposition}
\end{remark}
\end{theorem}
\equationref{labellist}#r
\equationrefname#*
\equationsrefname#*
\exampleref{labellist}#r
\examplerefname#*
\examplesrefname#*
\figureconts{label}{caption%text}{content%text}#l
\figureref{labellist}#r
\figurerefname#*
\figuresrefname#*
\floatconts{label}{caption%text}{content%text}#l
\ifjmlrcleveref#*
\ifjmlrutilsmaths#*
\ifjmlrutilssubfloats#*
\ifjmlrutilstheorems#*
\iftablecaptiontop#*
\includeteximage[options%keyvals]{imagefile}#g
\includeteximage{imagefile}#g
\jmlralgorule#*
\jmlrBlackBox#*
\jmlrclevereffalse#*
\jmlrclevereftrue#*
\jmlrminsubcaptionwidth#*
\jmlrprehyperref#*
\jmlrQED#*
\jmlrutilsmathsfalse#*
\jmlrutilsmathstrue#*
\jmlrutilssubfloatsfalse#*
\jmlrutilssubfloatstrue#*
\jmlrutilstheoremsfalse#*
\jmlrutilstheoremstrue#*
\lemmaref{labellist}#r
\lemmarefname#*
\lemmasrefname#*
\mailto{email address%URL}#U
\newtheorem*{envname}{caption}#N
\objectref{labellist}{singular name}{plural name}{before}{after}#*r
\orgvec{arg}#m
\partref{labellist}#r
\partrefname#*
\partsrefname#*
\proofname#*
\remarkref{labellist}#r
\remarkrefname#*
\remarksrefname#*
\sectionref{labellist}#r
\sectionrefname#*
\sectionsrefname#*
\set{text%plain}
\subfigref{labellist}#r
\subfigure[title%text][valign%keyvals]{contents%text}
\subfigure[title%text]{contents%text}
\subfigure{contents%text}
\subfigurelabel{text%plain}#*
\subtable[title%text][valign%keyvals]{contents%text}
\subtable[title%text]{contents%text}
\subtable{contents%text}
\subtablelabel{text%plain}#*
\subtabref{labellist}#r
\tablecaptiontopfalse#*
\tablecaptiontoptrue#*
\tableconts{label}{caption%text}{content%text}#l
\tableref{labellist}#r
\tablerefname#*
\tablesrefname#*
\theaxiom#*
\theconjecture#*
\thecorollary#*
\thedefinition#*
\theexample#*
\thelemma#*
\theorembodyfont{font declarations}
\theoremheaderfont{font declarations}
\theorempostheader{text}
\theoremref{labellist}#r
\theoremrefname#*
\theoremsep{separation code}
\theoremsrefname#*
\theproposition#*
\theremark#*
\thesubfigure#*
\thesubtable#*
\thetheorem#*

#keyvals:\includeteximage
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

#keyvals:\subfigure,\subtable
t
c
b
#endkeyvals

# deprecated
\BlackBox#S