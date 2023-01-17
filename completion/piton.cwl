# piton package
# Matthew Bertucci 2023/01/16 for v1.2

#include:l3keys2e
#include:luatexbase
#include:luacode

#keyvals:\usepackage/piton#c
comment-latex=%<string%>
math-comments#true,false
escape-inside=%<two-chars%>
footnote
footnotehyper
beamer#true,false
#endkeyvals

#ifOption:footnote
#include:footnote
#endif
#ifOption:footnote=true
#include:footnote
#endif

#ifOption:footnotehyper
#include:footnotehyper
#endif
#ifOption:footnotehyper=true
#include:footnotehyper
#endif

\piton{code%definition}
\begin{Piton}#V
\end{Piton}

\PitonInputFile{file}#i
\PitonInputFile[options%keyvals]{file}#i

#keyvals:\PitonInputFile
first-line=%<integer%>
last-line=%<integer%>
#endkeyvals

\PitonOptions{options%keyvals}

#keyvals:\PitonOptions
gobble=%<integer%>
auto-gobble
tabs-auto-gobble
line-numbers
all-line-numbers
resume
splittable
splittable=%<integer%>
background-color=#%color
slim#true,false
left-margin=##L
tab-size=%<integer%>
show-spaces
show-spaces-in-strings
break-lines-in-Piton
break-lines-in-piton
break-lines
indent-broken-lines
end-of-broken-line=%<symbol%>
continuation-symbol=%<symbol%>
continuation-symbol-on-indentation=%<symbol%>
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
Beamer=%<formatting%>
#endkeyvals

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N

# not documented
\PitonStyle{arg}#*
\myfiledate#S
\myfileversion#S
