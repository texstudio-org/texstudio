# piton package
# Matthew Bertucci 2024/05/24 for v3.0b

#include:l3keys2e
#include:luatexbase
#include:luacode
#include:xcolor

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
\PitonInputFileTF{file}{true code}{false code}
\PitonInputFileTF[options%keyvals]{file}{true code}{false code}
\PitonInputFileT{file}{true code}
\PitonInputFileT[options%keyvals]{file}{true code}
\PitonInputFileF{file}{false code}
\PitonInputFileF[options%keyvals]{file}{false code}
# beamer only
\PitonInputFile<overlay spec>{file}#*
\PitonInputFile<overlay spec>[options%keyvals]{file}#*
\PitonInputFileTF<overlay spec>{file}{true code}{false code}#*
\PitonInputFileTF<overlay spec>[options%keyvals]{file}{true code}{false code}#*
\PitonInputFileT<overlay spec>{file}{true code}#*
\PitonInputFileT<overlay spec>[options%keyvals]{file}{true code}#*
\PitonInputFileF<overlay spec>{file}{false code}#*
\PitonInputFileF<overlay spec>[options%keyvals]{file}{false code}#*

#keyvals:\PitonInputFile,\PitonInputFileTF,\PitonInputFileT,\PitonInputFileF
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
path={%<list of paths%>}
#endkeyvals

# keys for \begin{Piton} only
#keyvals:\begin{Piton}
line-numbers/start
#endkeyvals

# keys for both \PitonOptions and \begin{Piton}
#keyvals:\PitonOptions,\begin{Piton}
language=#Python,OCaml,C,SQL,minimal,%newpitonlang
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
split-on-empty-lines#true,false
split-separation=%<code%>
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
Directive=%<formatting%>
# not documented
FormattingType=%<formatting%>
Comment.Math=%<formatting%>
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
Tag=%<formatting%>
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
Directive
# not documented
FormattingType
Comment.Math
Discard
Identifier
Keyword2
Keyword3
Keyword4
Keyword5
Keyword6
Keyword7
Keyword8
Keyword9
ParseAgain.noCR
ParseAgain
Prompt
Tag
#endkeyvals

\PitonClearUserFunctions
\PitonClearUserFunctions[languages]

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N

\NewPitonLanguage{language}{keyvals}#s#%newpitonlang

#keyvals:\NewPitonLanguage
morekeywords={%<list of keywords%>}
morekeywords=[%<number%>]{%<list of keywords%>}
otherkeywords={%<keywords%>}
sensitive#true,false
keywordsprefix=%<prefix%>
moretexcs={%<list of csnames%>}
moretexcs=[%<class number%>]{%<list of csnames%>}
morestring=%<delimiter%>
morestring=[%<b|d|m|s%>]%<delimiter%>
morecomment=%<delimiter(s)%>
morecomment=[%<i|l|s|n%>]%<delimiter(s)%>
moredelim=[%<type%>][%<style%>]%<delimiters%>
moredelim=*[%<type%>][%<style%>]%<delimiters%>
moredelim=**[%<type%>][%<style%>]%<delimiters%>
moredirectives={%<list of compiler directives%>}
tag=%<<char1><char2>%>
alsodigit={%<character sequence%>}
alsoletter={%<character sequence%>}
alsoother={%<character sequence%>}
#endkeyvals

\SetPitonIdentifier{id1,id2,...}{code}
\SetPitonIdentifier[language]{id1,id2,...}{code}

\PitonFileVersion#S
\PitonFileDate#S
