# codedescribe package
# Matthew Bertucci 2023/05/12 for v1.0

#include:xcolor
#include:codelisting

#keyvals:\usepackage/codedescribe#c
nolisting
#endkeyvals

\setcodefmt{fmt-keys%keyvals}

#keyvals:\setcodefmt
meta=#%color
marg=#%color
arg=#%color
oarg=#%color
parg=#%color
xarg=#%color
code=#%color
macro=#%color
function=#%color
syntax=#%color
key=#%color
keys=#%color
keyval=#%color
value=#%color
defaultval=#%color
option=#%color
env=#%color
pkg=#%color
pack=#%color
allcolors=#%color
font=%<font commands%>
fontsize=%<size command%>
fontshape=%<shape command%>
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

#keyvals:\begin{codedescribe},\begin{describelist},\begin{describelist*},\typesetobj,\tsobj,\typesetargs,\tsargs,\typesetverb,\tsverb
meta
arg
marg
oarg
parg
xarg
code
macro
function
syntax
key
keys
keyval
value
defaultval
option
env
pkg
pack
#endkeyvals

#keyvals:\begin{codedescribe}
rulecolor=%<color%>
new=%<date%>
update=%<date%>
note=%<text%>
#endkeyvals

#keyvals:\typesetobj,\tsobj
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

# not documented
\PkgInfo{arg1}{arg2}#S