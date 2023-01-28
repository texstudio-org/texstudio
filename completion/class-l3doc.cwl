# l3doc class
# Matthew Bertucci 2022/12/18 for v2022/12/17

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
# loads T1 option of fontenc
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

\eTeX
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
\cs{csname}
\cs[options%keyvals]{csname}
\tn{csname}
\tn[options%keyvals]{csname}

#keyvals:\cmd#c,\cs#c,\tn#c
index=%<name%>
no-index#true,false
module=%<module%>
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

\begin{function}{function%cmd}
\begin{function}[type%keyvals]{function%cmd}
\end{function}

#keyvals:\begin{function}#c
EXP
rEXP
TF
pTF
noTF
#endkeyvals

\begin{variable}{variable%cmd}
\begin{variable}[options%keyvals]{variable%cmd}
\end{variable}
\begin{macro}{macro1,macro2,...%cmd}
\begin{macro}[options%keyvals]{macro1,macro2,...%cmd}
\end{macro}

#keyvals:\begin{variable}#c,\begin{macro}#c
int
TF
pTF
noTF
verb
#endkeyvals

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

\testfile#*
\testfile*#*
\MacroLongFont#*

\TestFiles{list of files%file}
\UnitTested
\TestMissing{explanation%text}

\DescribeOption{option}
\DescribeOption[options]{option}#*
\begin{optionenv}{option}#*
\begin{optionenv}[options]{option}#*
\end{optionenv}#*
\PrintDescribeOption{option}#*
\PrintOptionName{option}#*

\manual#*
\dbend
\begin{danger}
\end{danger}
\begin{ddanger}
\end{ddanger}

\NB{tag%text}{comments%text}
\begin{NOTE}{tag%text}#V
\end{NOTE}

\begin{TemplateInterfaceDescription}{template type name}
\end{TemplateInterfaceDescription}
\begin{TemplateDescription}{template type name}{name}
\end{TemplateDescription}
\TemplateArgument{arg no}{meaning}
\TemplateSemantics
\TemplateKey{key name}{type}{description%text}{default value}
\begin{InstanceDescription}{template type name}{instance name}{template name}
\begin{InstanceDescription}[text for key colwidth]{template type name}{instance name}{template name}
\end{InstanceDescription}
\InstanceKey{key name}{value}
\InstanceSemantics

\DocInputAgain#*
\DocInclude{file}#i
\currentfile#*
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
