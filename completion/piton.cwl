# piton package
# Matthew Bertucci 2023/04/04 for v1.5

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
# beamer only
\begin{Piton}<overlay spec>#*V

\PitonInputFile{file}
\PitonInputFile[options%keyvals]{file}
# beamer only
\PitonInputFile<overlay spec>{file}#*
\PitonInputFile<overlay spec>[options%keyvals]{file}#*

#keyvals:\PitonInputFile
first-line=%<integer%>
last-line=%<integer%>
#endkeyvals

\PitonOptions{options%keyvals}

#keyvals:\PitonOptions
language=%<language%>
gobble=%<integer%>
auto-gobble
tabs-auto-gobble
line-numbers
all-line-numbers
numbers-sep=##L
resume
identifiers={%<names={<name1>,<name2>,...},style=<instructions>%>}
splittable
splittable=%<integer%>
background-color=#%color
prompt-background-color=#%color
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
Name.UserFunction=%<formatting%>
Interpol.Inside=%<formatting%>
Comment.Math=%<formatting%>
InitialValues=%<formatting%>
TypeParameter=%<formatting%>
Name.Type=%<formatting%>
Identifier=%<formatting%>
ParseAgain.noCR=%<formatting%>
ParseAgain=%<formatting%>
Prompt=%<formatting%>
#endkeyvals

\PitonStyle{style%keyvals}{text%plain}

#keyvals:\PitonStyle
Number
String.Short
String.Long
String
String.Doc
String.Interpol
Operator
Operator.Word
Name.Builtin
Name.Function
Name.Decorator
Name.Namespace
Name.Class
Exception
Comment
Comment.LaTeX
Keyword.Constant
Keyword
# not documented
FormattingType
Dict.Value
Interpol.Inside
Comment.Math
InitialValues
TypeParameter
Name.Type
Identifier
ParseAgain.noCR
ParseAgain
Prompt
#endkeyvals

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N

\PitonClearUserFunctions#*
\myfiledate#S
\myfileversion#S
