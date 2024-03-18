# piton package
# Matthew Bertucci 2024/03/18 for v2.6b

#include:l3keys2e
#include:luatexbase
#include:luacode

#keyvals:\usepackage/piton#c
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
\begin{Piton}[options%keyvals]#V
\end{Piton}
# beamer only (breaks keyval completion so commented out)
#\begin{Piton}<overlay spec>#*V
#\begin{Piton}<overlay spec>[options%keyvals]#*V

\PitonInputFile{file}
\PitonInputFile[options%keyvals]{file}
# beamer only
\PitonInputFile<overlay spec>{file}#*
\PitonInputFile<overlay spec>[options%keyvals]{file}#*

#keyvals:\PitonInputFile
first-line=%<integer%>
last-line=%<integer%>
begin-range=%<content%>
end-range=%<content%>
range=%<content%>
marker/include-lines
#endkeyvals

\PitonOptions{options%keyvals}

# keys for \PitonOptions only
#keyvals:\PitonOptions
comment-latex=%<string%>
math-comments#true,false
detected-commands={%<csname1,csname2,...%>}
line-numbers/absolute
marker={%<options%>}
marker/beginning=%<spec%>
marker/end=%<spec%>
begin-escape=%<character%>
end-escape=%<character%>
begin-escape-math=%<character%>
end-escape-math=%<character%>
path=%<file path%>
#endkeyvals

# keys for \begin{Piton} only
#keyvals:\begin{Piton}
line-numbers/start
#endkeyvals

# keys for both \PitonOptions and \begin{Piton}
#keyvals:\PitonOptions,\begin{Piton}
language=#Python,OCaml,C,SQL,minimal
gobble=%<integer%>
auto-gobble
tabs-auto-gobble
env-gobble
line-numbers
line-numbers={%<options%>}
line-numbers/skip-empty-lines#true,false
line-numbers/label-empty-lines#true,false
line-numbers/resume
line-numbers/sep=##L
splittable
splittable=%<integer%>
background-color=#%color
prompt-background-color=#%color
width=##L
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
write=%<file%>
path-write=%<path%>
#endkeyvals

\SetPitonStyle{options%keyvals}
\SetPitonStyle[language]{options%keyvals}

#keyvals:\SetPitonStyle
Number=%<formatting%>
String.Short=%<formatting%>
String.Long=%<formatting%>
String=%<formatting%>
String.Doc=%<formatting%>
String.Interpol=%<formatting%>
Interpol.Inside=%<formatting%>
Operator=%<formatting%>
Operator.Word=%<formatting%>
Name.Builtin=%<formatting%>
Name.Decorator=%<formatting%>
Name.Namespace=%<formatting%>
Name.Class=%<formatting%>
Name.Function=%<formatting%>
UserFunction=%<formatting%>
Exception=%<formatting%>
InitialValues=%<formatting%>
Comment=%<formatting%>
Comment.LaTeX=%<formatting%>
Keyword.Constant=%<formatting%>
Keyword=%<formatting%>
Name.Type=%<formatting%>
Name.Field=%<formatting%>
Name.Constructor=%<formatting%>
Name.Module=%<formatting%>
TypeParameter=%<formatting%>
Preproc=%<formatting%>
Name.Table=%<formatting%>
# not documented
FormattingType=%<formatting%>
Comment.Math=%<formatting%>
directive=%<formatting%>
Discard=%<formatting%>
Identifier=%<formatting%>
Keyword2=%<formatting%>
Keyword3=%<formatting%>
Keyword4=%<formatting%>
Keyword5=%<formatting%>
Keyword6=%<formatting%>
Keyword7=%<formatting%>
Keyword8=%<formatting%>
Keyword9=%<formatting%>
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
Interpol.Inside
Operator
Operator.Word
Name.Builtin
Name.Decorator
Name.Namespace
Name.Class
Name.Function
UserFunction
Exception
InitialValues
Comment
Comment.LaTeX
Keyword.Constant
Keyword
Name.Type
Name.Field
Name.Constructor
Name.Module
TypeParameter
Preproc
Name.Table
# not documented
FormattingType
Comment.Math
Identifier
ParseAgain.noCR
ParseAgain
Prompt
#endkeyvals

\PitonClearUserFunctions
\PitonClearUserFunctions[languages]

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N

\SetPitonIdentifier{id1,id2,...}{code}
\SetPitonIdentifier[language]{id1,id2,...}{code}

\NewPitonLanguage{arg1}{arg2}#S
\PitonFileVersion#S
\PitonFileDate#S
