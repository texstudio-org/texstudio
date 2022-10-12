# piton package
# Matthew Bertucci 2022/10/08 for v0.7

#include:l3keys2e
#include:luatexbase
#include:luacode

#keyvals:\usepackage/piton#c
escape-inside=%<two-chars%>
#endkeyvals

\piton{code%definition}
\begin{Piton}#V
\end{Piton}
\PitonInputFile{file}#i

\PitonOptions{options%keyvals}

#keyvals:\PitonOptions
gobble=%<integer%>
auto-gobble
line-numbers
all-line-numbers
resume
splittable
background-color=#%color
#endkeyvals

\SetPitonStyle{options%keyvals}

#keyvals:\SetPitonStyle
Number=%<formatting%>
String.Short=%<formatting%>
String.Long=%<formatting%>
String=%<formatting%>
String.Doc=%<formatting%>
String.Interpol=%<formatting%>
Operator=%<formatting%>
Operator.Word=%<formatting%>
Name.Builtin=%<formatting%>
Name.Function=%<formatting%>
Name.Decorator=%<formatting%>
Name.Namespace=%<formatting%>
Name.Class=%<formatting%>
Exception=%<formatting%>
Comment=%<formatting%>
Comment.LaTeX=%<formatting%>
Keyword.Constant=%<formatting%>
Keyword=%<formatting%>
# not documented
FormattingType=%<formatting%>
Dict.Value=%<formatting%>
Interpol.Inside=%<formatting%>
Comment.Math=%<formatting%>
InitialValues=%<formatting%>
Name.Type=%<formatting%>
Post.Function=%<formatting%>
#endkeyvals

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N

# not documented
\pitonEOL#*
\PitonStyle{arg}#*
\myfiledate#S
\myfileversion#S
