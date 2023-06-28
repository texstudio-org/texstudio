# sidenotesplus package
# Matthew Bertucci 2022/05/21 for v1.00

#include:marginnote
#include:caption
#include:calc
#include:etoolbox
#include:l3keys2e
#include:ifoddpage
#include:mparhack
#include:xspace
#include:changepage

#keyvals:\usepackage/sidenotesplus#c
mark=#alph,Alph,arabic,roman,Roman,fnsymbol
font=#rm,sf
size=#footnote,normal,small,script
shape=#up,it,sl
ragged
Ragged
classic
sepdiff=##L
alerton
#endkeyvals

#ifOption:Ragged
#include:ragged2e
#endif

\sidenote{content%text}
\sidenote|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenote|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidenote*{content%text}
\sidenote*|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenote*|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}

\sidenotetext{content%text}
\sidenotetext|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenotetext|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidenotetext*{content%text}
\sidenotetext*|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenotetext*|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidenotetextbefore{content%text}
\sidenotetextbefore|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenotetextbefore|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidenotetextbefore*{content%text}
\sidenotetextbefore*|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidenotetextbefore*|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidenotemark#*
\sidenotemark(%<mark%>)#*
\sidenotemark(%<mark%>)!%<color%>!#*
\sidenotemark*#*
\sidenotemark*(%<mark%>)#*
\sidenotemark*(%<mark%>)!%<color%>!#*
\sidealert{content%text}
\sidealert|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidealert|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidealert*{content%text}
\sidealert*|%<float offset%>|<%<fixed offset%>>{%<content%>}
\sidealert*|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>!{%<content%>}
\sidepar
\sidecaption{text}
\sidecaption[short text%text]{text}
\sidecaption<offset>[short text%text]{text}
\sidecaption*{text}
\sidecaption*[short text%text]{text}
\sidecaption*<offset>[short text%text]{text}
\raggedinner
\raggedouter
\begin{marginfigure}
\begin{marginfigure}|%<float offset%>|
\begin{marginfigure}<%<fixed offset%>>
\begin{marginfigure}|%<float offset%>|<%<fixed offset%>>
\end{marginfigure}
\begin{margintable}
\begin{margintable}|%<float offset%>|
\begin{margintable}<%<fixed offset%>>
\begin{margintable}|%<float offset%>|<%<fixed offset%>>
\end{margintable}
\margincaption{text}
\margincaption[short text%text]{text}
\margincaption*{text}
\margincaption*[short text%text]{text}
\begin{text*}
\begin{text*}[width factor]
\end{text*}
\sidecite{bibid}#C
\sidecite[postnote]{bibid}#*C
\sidecite[prenote][postnote]{bibid}#*C
\sidecite|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>![%<prenote%>][%<postnote%>]{%<bibid%>}
\sidecitet{bibid}#C
\sidecitet[postnote]{bibid}#*C
\sidecitet[prenote][postnote]{bibid}#*C
\sidecitet|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>![%<prenote%>][%<postnote%>]{%<bibid%>}
\sidecitet*{bibid}#C
\sidecitet*[postnote]{bibid}#*C
\sidecitet*[prenote][postnote]{bibid}#*C
\sidecitet*|%<float offset%>|<%<fixed offset%>>(%<mark%>)!%<color%>![%<prenote%>][%<postnote%>]{%<bibid%>}

# not in main documentation
\snptest#*
\IfNoValueOrEmptyTF{arg}{-NoValue-Code}{ValueCode}
\thesidenote#*
\thesidealert#*
\oldmarginpar#S
\IfsTF{arg}{-NoValue-Code}{ValueCode}
\istwosided{true code}{false code}
\marginparsepodd#*
\marginparsepeven#*
\patcherr#S
\patchok#S
\patch#S
