# l3doc class
# Matthew Bertucci 11/26/2021

#include:expl3
#include:calc
#include:doc
#include:array
#include:alphalph
#include:amsmath
#include:amssymb
#include:booktabs
#include:color
#include:colortbl
#include:hologo
#include:enumitem
#include:pifont
#include:textcomp
#include:trace
#include:csquotes
#include:fancyvrb
#include:underscore
#include:verbatim
#include:fontenc
#include:lmodern
#include:hypdoc

#keyvals:\documentclass/l3doc#c
full
onlydoc
check
nocheck
checktest
nochecktest
kernel
stdmodule
cm-default
lm-default
cs-break-off
cs-break-nohyphen
show-notes
hide-notes
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\pdfstringnewline#*

\IniTeX
\Lua
\LuaTeX
\pdfTeX
\XeTeX
\pTeX
\upTeX
\epTeX
\eupTeX
\ConTeXt

\cmd{macro%cmd}
\cmd[options%keyvals]{macro%cmd}
\cs{csname%plain}
\cs[options%keyvals]{csname%plain}
\tn{arg}
\tn[options%keyvals]{arg}

#keyvals:\cmd#c,\cs#c,\tn#c
index=
module=
no-index#true,false
replace#true,false
#endkeyvals

\Arg{arg}
\marg{arg}
\oarg{arg}
\parg{arg}
\file{file}
\env{envname}
\pkg{package}
\cls{class}

\EnableDocumentation
\EnableImplementation
\DisableDocumentation
\DisableImplementation

\begin{documentation}
\end{documentation}
\begin{implementation}
\end{implementation}

\begin{variable}{variable%cmd}
\begin{variable}[options]{variable%cmd}
\end{variable}
\begin{function}{function%cmd}
\begin{function}[options]{function%cmd}
\end{function}
\begin{macro}{macro%cmd}
\begin{macro}[options]{macro%cmd}
\end{macro}
\begin{syntax}
\end{syntax}
\begin{texnote}
\end{texnote}
\begin{arguments}
\end{arguments}

\CodedocExplain
\CodedocExplainEXP
\CodedocExplainREXP
\CodedocExplainTF

\testfile{arg}#*
\testfile*{arg}#*
\MacroLongFont#*

\TestFiles{arg}
\UnitTested{arg}
\TestMissing{arg}

\DescribeOption{option}
\SpecialOptionIndex{option}

\manual#*
\dbend
\begin{danger}
\end{danger}
\begin{ddanger}
\end{ddanger}

\NB{arg1%text}{arg2%text}
\begin{NOTE}{arg%text}#V
\end{NOTE}

\begin{TemplateInterfaceDescription}{template}
\end{TemplateInterfaceDescription}
\begin{TemplateDescription}{template}{object type}
\end{TemplateDescription}
\TemplateArgument{arg1}{arg2}
\TemplateSemantics
\TemplateKey{arg1}{arg2}{arg3}{arg4}
\begin{InstanceDescription}{arg1}{arg2}{arg3}
\begin{InstanceDescription}[opt]{arg1}{arg2}{arg3}
\end{InstanceDescription}
\InstanceKey{arg1}{arg2}
\InstanceSemantics

\DocInputAgain#*
\DocInclude{file}#i

\filesep#*
\docincludeaux#*
\filekey#*

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
