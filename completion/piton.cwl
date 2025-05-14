# piton package
# Matthew Bertucci 2025/05/14 for v4.5

#include:luacode
#include:xcolor
#include:amstext

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
raw-detected-commands={%<csname1,csname2,...%>}
detected-beamer-commands={%<csname1,csname2,...%>}
detected-beamer-environments={%<envname1,envname2,...%>}
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
auto-gobble
background-color=#%color
break-lines
break-lines-in-Piton
break-lines-in-piton
break-numbers-anywhere
break-strings-anywhere
continuation-symbol-on-indentation=%<symbol%>
continuation-symbol=%<symbol%>
end-of-broken-line=%<symbol%>
env-gobble
env-used-by-split=%<envname%>
font-command=%<font commands%>
gobble
gobble=%<integer%>
indent-broken-lines
join=%<file%>
language=#Python,OCaml,C,SQL,minimal,verbatim,%newpitonlang
left-margin=##L
line-numbers
line-numbers/format=%<font commands%>
line-numbers/label-empty-lines#true,false
line-numbers/resume
line-numbers/sep=##L
line-numbers/skip-empty-lines#true,false
line-numbers={%<options%>}
path-write=%<path%>
print#true,false
prompt-background-color=#%color
show-spaces
show-spaces-in-strings
split-on-empty-lines#true,false
split-separation=%<code%>
splittable
splittable-on-empty-lines#true,false
splittable=%<integer%>
tab-size=%<integer%>
tabs-auto-gobble
width=##L
write=%<file%>
#endkeyvals

\SetPitonStyle{options%keyvals}
\SetPitonStyle[language]{options%keyvals}

#keyvals:\SetPitonStyle
Comment.LaTeX=%<formatting%>
Comment=%<formatting%>
Directive=%<formatting%>
Exception=%<formatting%>
InitialValues=%<formatting%>
Interpol.Inside=%<formatting%>
Keyword.Constant=%<formatting%>
Keyword.Governing=%<formatting%>
Keyword=%<formatting%>
Name.Builtin=%<formatting%>
Name.Class=%<formatting%>
Name.Constructor=%<formatting%>
Name.Decorator=%<formatting%>
Name.Field=%<formatting%>
Name.Function=%<formatting%>
Name.Module=%<formatting%>
Name.Namespace=%<formatting%>
Name.Table=%<formatting%>
Name.Type=%<formatting%>
Number=%<formatting%>
Operator.Word=%<formatting%>
Operator=%<formatting%>
Preproc=%<formatting%>
String.Doc.Internal=%<formatting%>
String.Doc=%<formatting%>
String.Interpol=%<formatting%>
String.Long=%<formatting%>
String.Short=%<formatting%>
String=%<formatting%>
TypeParameter=%<formatting%>
UserFunction=%<formatting%>
# not documented
Comment.Math=%<formatting%>
Discard=%<formatting%>
FormattingType=%<formatting%>
Identifier.Internal=%<formatting%>
Identifier=%<formatting%>
Keyword2=%<formatting%>
Keyword3=%<formatting%>
Keyword4=%<formatting%>
Keyword5=%<formatting%>
Keyword6=%<formatting%>
Keyword7=%<formatting%>
Keyword8=%<formatting%>
Keyword9=%<formatting%>
Number.Internal=%<formatting%>
Prompt=%<formatting%>
String.Long.Internal=%<formatting%>
String.Short.Internal=%<formatting%>
Tag=%<formatting%>
TypeExpression=%<formatting%>
#endkeyvals

\PitonStyle{style%keyvals}{text%plain}

#keyvals:\PitonStyle
Comment
Comment.LaTeX
Directive
Exception
InitialValues
Interpol.Inside
Keyword
Keyword.Constant
Keyword.Governing
Name.Builtin
Name.Class
Name.Constructor
Name.Decorator
Name.Field
Name.Function
Name.Module
Name.Namespace
Name.Table
Name.Type
Number
Operator
Operator.Word
Preproc
String
String.Doc
String.Doc.Internal
String.Interpol
String.Long
String.Short
TypeParameter
UserFunction
# not documented
Comment.Math
Discard
FormattingType
Identifier
Identifier.Internal
Keyword2
Keyword3
Keyword4
Keyword5
Keyword6
Keyword7
Keyword8
Keyword9
Number.Internal
Prompt
String.Long.Internal
String.Short.Internal
Tag
TypeExpression
#endkeyvals

\PitonClearUserFunctions
\PitonClearUserFunctions[languages]

\NewPitonEnvironment{envname}{xargs}{begdef}{enddef}#N
\DeclarePitonEnvironment{envname}{xargs}{begdef}{enddef}#N
\RenewPitonEnvironment{envname}{xargs}{begdef}{enddef}
\ProvidePitonEnvironment{envname}{xargs}{begdef}{enddef}#N

\NewPitonLanguage{language}{keyvals}#s#%newpitonlang

#keyvals:\NewPitonLanguage
alsodigit={%<character sequence%>}
alsoletter={%<character sequence%>}
alsoother={%<character sequence%>}
keywordsprefix=%<prefix%>
morecomment=%<delimiter(s)%>
morecomment=[%<i|l|s|n%>]%<delimiter(s)%>
moredelim=**[%<type%>][%<style%>]%<delimiters%>
moredelim=*[%<type%>][%<style%>]%<delimiters%>
moredelim=[%<type%>][%<style%>]%<delimiters%>
moredirectives={%<list of compiler directives%>}
morekeywords=[%<number%>]{%<list of keywords%>}
morekeywords={%<list of keywords%>}
morestring=%<delimiter%>
morestring=[%<b|d|m|s%>]%<delimiter%>
moretexcs=[%<class number%>]{%<list of csnames%>}
moretexcs={%<list of csnames%>}
otherkeywords={%<keywords%>}
sensitive#true,false
tag=%<<char1><char2>%>
#endkeyvals

\SetPitonIdentifier{id1,id2,...}{code}
\SetPitonIdentifier[language]{id1,id2,...}{code}

\PitonDetectedCommands#S
\PitonRawDetectedCommands#S
\PitonBeamerCommands#S
\PitonBeamerEnvironments#S
\PitonFileVersion#S
\PitonFileDate#S
