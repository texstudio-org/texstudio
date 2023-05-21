# codedescribe package
# Matthew Bertucci 2023/05/17 for v1.1

#include:xcolor
#include:pifont
#include:codelisting

#keyvals:\usepackage/codedescribe#c
nolisting
#endkeyvals

\defgroupfmt{format-group}{format-keys%keyvals}
\defobjectfmt{obj-type}{format-group}{format-keys%keyvals}

#keyvals:\defgroupfmt#c,\defobjectfmt#c
meta
xmeta
verb
xverb
code
nofmt
slshape
itshape
noshape
lbracket=%<symbol%>
rbracket=%<symbol%>
color=#%color
#endkeyvals

\begin{codedescribe}{csv-list}
\begin{codedescribe}[obj-type%keyvals]{csv-list}
\end{codedescribe}

\begin{codesyntax}
\end{codesyntax}

\begin{describelist}{obj-type%keyvals}
\begin{describelist}[item-indent]{obj-type%keyvals}
\end{describelist}
\begin{describelist*}{obj-type%keyvals}
\begin{describelist*}[item-indent]{obj-type%keyvals}
\end{describelist*}
\describe{item-name}{item-description%text}

\typesetobj{csv-list}#*
\typesetobj[obj-type%keyvals]{csv-list}#*
\tsobj{csv-list}
\tsobj[obj-type%keyvals]{csv-list}
\typesetargs{csv-list}#*
\typesetargs[obj-type%keyvals]{csv-list}#*
\tsargs{csv-list}
\tsargs[obj-type%keyvals]{csv-list}
\typesetmacro{macro-list}{csv-list}#*
\typesetmacro{macro-list}[oargs-list]{margs-list}#*
\tsmacro{macro-list%definition}{csv-list}
\tsmacro{macro-list%definition}[oargs-list]{margs-list}
\typesetmeta{name}#*
\tsmeta{name}
\typesetverb{verbatim text%definition}#*
\typesetverb[obj-type%keyvals]{verbatim text%definition}#*
\tsverb{verbatim text%definition}
\tsverb[obj-type%keyvals]{verbatim text%definition}
\typesetmarginnote{note%text}#*
\tsmarginnote{note%text}

\begin{tsremark}
\begin{tsremark}[NB]
\end{tsremark}

#keyvals:\begin{codedescribe}#c,\begin{describelist}#c,\begin{describelist*}#c,\typesetobj#c,\tsobj#c,\typesetargs#c,\tsargs#c,\typesetverb#c,\tsverb#c
arg
meta
verb
xverb
marg
oarg
parg
xarg
code
macro
function
syntax
keyval
key
keys
value
option
defaultval
env
pkg
pack
#endkeyvals

#keyvals:\begin{codedescribe}#c
rulecolor=%<color%>
new=%<date%>
update=%<date%>
note=%<text%>
EXP
rEXP
#endkeyvals

#keyvals:\typesetobj#c,\tsobj#c
sep=%<separator%>
#endkeyvals

\typesettitle{title-keys%keyvals}#*
\tstitle{title-keys%keyvals}

#keyvals:\typesettitle,\tstitle
title=%<text%>
author=%<name%>
date=%<date%>
#endkeyvals

\begin{typesetabstract}#*
\end{typesetabstract}#*
\begin{tsabstract}
\end{tsabstract}

\typesetdate#*
\tsdate

# not documented
\PkgInfo{arg1}{arg2}#S
