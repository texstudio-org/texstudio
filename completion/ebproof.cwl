# ebproof package
# Matthew Bertucci 9/27/2021 for v2.1.1

\begin{prooftree}#\math
\begin{prooftree}[options%keyvals]#\math
\end{prooftree}
\begin{prooftree*}#\math
\begin{prooftree*}[options%keyvals]#\math
\end{prooftree*}

\hypo{text}#/prooftree,prooftree*
\hypo[options%keyvals]{text}#/prooftree,prooftree*
\infer%<arity%>{%<text%>}#/prooftree,prooftree*
\infer%<arity%>[%<label%>]{%<text%>}#/prooftree,prooftree*
\infer[%<options%>]%<arity%>{%<text%>}#/prooftree,prooftree*
\infer[%<options%>]%<arity%>[%<label%>]{%<text%>}#/prooftree,prooftree*
\ellipsis{label}{text}#/prooftree,prooftree*
\rewrite{code}#/prooftree,prooftree*
\treebox#/prooftree,prooftree*
\treemark{name}#/prooftree,prooftree*
\delims{left}{right}#/prooftree,prooftree*
\overlay#/prooftree,prooftree*

\ebproofset{options%keyvals}
\set{options%keyvals}#/prooftree,prooftree*
\ebproofnewstyle{name}{options%keyvals}
\inserttext

#keyvals:\ebproofset#c,\begin{prooftree}#c,\begin{prooftree*}#c,\ebproofnewstyle#c
proof style=#upwards,downwards
center#true,false
#endkeyvals

#keyvals:\ebproofset#c,\set#c,\begin{prooftree}#c,\begin{prooftree*}#c,\hypo#c,\infer#c,\ebproofnewstyle#c
separation=##L
rule margin=##L
rule style=
rule thickness=##L
rule separation=##L
rule dash length=##L
rule dash space=##L
rule code=%<code%>
template=%<code%>
left template=%<code%>
right template=%<code%>
left label=
right label=
left label template=%<code%>
right label template=%<code%>
label separation=##L
#endkeyvals

#keyvals:\infer#c
simple
no rule
double
dashed
#endkeyvals

\ebproofnewrulestyle{name}{options%keyvals}

#keyvals:\ebproofnewrulestyle#c
rule margin=##L
rule style=
rule thickness=##L
rule separation=##L
rule dash length=##L
rule dash space=##L
rule code=%<code%>
#endkeyvals