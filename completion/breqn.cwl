# breqn package
# Matthew Bertucci 10/25/2021 for v0.98k

#include:amsmath
#include:graphicx
#include:flexisym
#include:keyval
#include:calc

\begin{dmath}#\math
\begin{dmath}[options%keyvals]#\math
\end{dmath}
\begin{dmath*}#\math
\begin{dmath*}[options%keyvals]#\math
\end{dmath*}
\begin{dseries}
\begin{dseries}[options%keyvals]
\end{dseries}
\begin{dseries*}
\begin{dseries*}[options%keyvals]
\end{dseries*}
\begin{dgroup}
\begin{dgroup}[options%keyvals]
\end{dgroup}
\begin{dgroup*}
\begin{dgroup*}[options%keyvals]
\end{dgroup*}
\begin{darray}#\math,array
\begin{darray}[options%keyvals]#\math,array
\end{darray}
\begin{darray*}#\math,array
\begin{darray*}[options%keyvals]#\math,array
\end{darray*}
\begin{dsuspend}
\end{dsuspend}
\breqnsetup{options%keyvals}

#keyvals:\begin{dmath},\begin{dmath*},\begin{dseries},\begin{dseries*},\begin{dgroup},\begin{dgroup*},\begin{darray},\begin{darray*},\breqnsetup
style=%<cmds%>
number=%<text%>
labelprefix=%<prefix%>
label=##l
indentstep=##L
compact
compact=%<number%>
spread=##L
frame
frame=##L
framesep=##L
breakdepth=%<number%>
shiftnumber
holdnumber
density=
layout=
shortskiplimit=##L
background=#%color
color=#%color
center
nocenter
#endkeyvals

#keyvals:\begin{dgroup},\begin{dgroup*}
noalign
brace
#endkeyvals

#keyvals:\begin{darray},\begin{darray*}
cols={%<col specs%>}
#endkeyvals

\condition{text}
\condition[punctuation mark]{text}
\condition*{formula}
\hiderel{rel symbol}#m
\intertext{text}

\breqnpopcats#*
\conditionpunct#*
\conditionsep#*
\darraycolsep#*
\debugwr{text}#*
\DeclareTwang{symbol}{number}#*
\discretionarytimes#*m
\Dmedmuskip#*
\dquad#*
\Dthickmuskip#*
\eqbinoffset#*
\eqbreakdepth#*
\eqcolor#*
\eqdelimoffset#*
\eqfontsize#*
\eqframe{width}{height}#*
\eqindent#*
\eqindentstep#*
\eqinfo#*
\eqinterlinepenalty#*
\eqleftskip#*
\eqlineskip#*
\eqlineskiplimit#*
\eqlinespacing#*
\eqmargin#*
\eqnumcolor#*
\eqnumfont#*
\eqnumform#*
\eqnumplace#*
\eqnumsep#*
\eqnumside#*
\eqnumsize#*
\eqpunct#*
\eqrightskip#*
\eqstyle#*
\intereqpenalty#*
\intereqskip#*
\listwidth#*
\mathaxis#*
\maxint#*
\nref{label}#*
\postmath#*
\prebinoppenalty#*
\premath#*
\prerelpenalty#*
\replicate{token list}#*
\theparentequation#*