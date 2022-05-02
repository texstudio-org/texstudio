# fancyvrb package
# neeraavi 12 Apr 2007
# muzimuzhi 15 Mar 2020, fancyvrb v3.5
# muzimuzhi 25 Mar 2020
# Matthew Bertucci 13 Mar 2022 for v4.2

#include:keyval

\Verb[options%keyvals]{verbatimSymbol}#S
\Verb|%<code%>|
\Verb[%<options%>]|%<code%>|
\Verb*[options%keyvals]{verbatimSymbol}#S
\Verb*|%<code%>|
\Verb*[%<options%>]|%<code%>|
\VerbatimFootnotes
\DefineShortVerb{\%<character%>}
\UndefineShortVerb{\%<character%>}
# following two lines tell highlighter not to mark args as incorrect
\DefineShortVerb{definition}#S
\UndefineShortVerb{definition}#S

\begin{Verbatim}#V
\begin{Verbatim}[options%keyvals]#V
\end{Verbatim}
\begin{Verbatim*}#V
\begin{Verbatim*}[options%keyvals]#V
\end{Verbatim*}
\begin{BVerbatim}#V
\begin{BVerbatim}[options%keyvals]#V
\end{BVerbatim}
\begin{BVerbatim*}#V
\begin{BVerbatim*}[options%keyvals]#V
\end{BVerbatim*}
\begin{LVerbatim}#V
\begin{LVerbatim}[options%keyvals]#V
\end{LVerbatim}
\begin{LVerbatim*}#V
\begin{LVerbatim*}[options%keyvals]#V
\end{LVerbatim*}
\fvset{options%keyvals}

\DefineVerbatimEnvironment{envname}{env type}{options%keyvals}#N
\CustomVerbatimEnvironment{envname}{env type}{options%keyvals}#*N
\RecustomVerbatimEnvironment{envname}{env type}{options%keyvals}#N
\CustomVerbatimCommand{command}{cmd type}{options%keyvals}#d
\RecustomVerbatimCommand{command}{cmd type}{options%keyvals}

# saving and restoring verbatim text and envs
\SaveVerb[options%keyvals]{name}{verbatimSymbol}#S
\SaveVerb{%<name%>}|%<code%>|
\SaveVerb[%<options%>]{%<name%>}|%<code%>|
\SaveVerb*[options%keyvals]{name}{verbatimSymbol}#S
\SaveVerb*{%<name%>}|%<code%>|#*
\SaveVerb*[%<options%>]{%<name%>}|%<code%>|#*
#keyvals:\SaveVerb,\SaveVerb*,\fvset
aftersave={%<code%>}
#endkeyvals
\UseVerb{name}
\UseVerb[options%keyvals]{name}
\UseVerb*{name}
\UseVerb*[options%keyvals]{name}
\begin{SaveVerbatim}{name}#V
\begin{SaveVerbatim}[options%keyvals]{name}
\end{SaveVerbatim}
\UseVerbatim{name}
\UseVerbatim[options%keyvals]{name}
\UseVerbatim*{name}
\UseVerbatim*[options%keyvals]{name}
\BUseVerbatim{name}
\BUseVerbatim[options%keyvals]{name}
\BUseVerbatim*{name}
\BUseVerbatim*[options%keyvals]{name}
\LUseVerbatim{name}
\LUseVerbatim[options%keyvals]{name}
\LUseVerbatim*{name}
\LUseVerbatim*[options%keyvals]{name}

# writing and reading verbatim files
\VerbatimInput{file}#i
\VerbatimInput[options%keyvals]{file}#i
\BVerbatimInput{file}#i
\BVerbatimInput[options%keyvals]{file}#i
\LVerbatimInput{file}#i
\LVerbatimInput[options%keyvals]{file}#i
\begin{VerbatimOut}{file name}#V
\end{VerbatimOut}

#keyvals:\Verb,\Verb*,\begin{Verbatim},\begin{Verbatim*},\begin{BVerbatim},\begin{BVerbatim*},\begin{LVerbatim},\begin{LVerbatim*},\fvset,\DefineVerbatimEnvironment,\CustomVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\SaveVerb,\SaveVerb*,\UseVerb,\UseVerb*,\begin{SaveVerbatim},\UseVerbatim,\BUseVerbatim,\LUseVerbatim,\VerbatimInput,\BVerbatimInput,\LLVerbatimInput
commentchar=%<single char%>
gobble=%<integer%>
formatcom=%<commands%>
formatcom*=%<commands%>
fontfamily=%<family%>
fontsize=%<size macro%>
fontshape=%<shape%>
fontseries=%<series%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label=%<label text%>
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=%<auto|last|<integer>%>
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=%<factor%>
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes={%<code%>}
codes*={%<code%>}
defineactive={%<code%>}
defineactive*={%<code%>}
reflabel=##l
fileext=%<extension%>
#endkeyvals

#keyvals:\begin{BVerbatim},\begin{BVerbatim*},\fvset,\DefineVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\BUseVerbatim,\BVerbatimInput
boxwidth=##L
baseline=#b,c,t
#endkeyvals

\FancyVerbFormatLine#*
\theFancyVerbLine#*
\FancyVerbStartString#*
\FancyVerbStopString#*
\VerbatimEnvironment#*
\FancyVerbCodes#*
\FancyVerbVspace#*
\FancyVerbStartNum#*
\FancyVerbStopNum#*
\FancyVerbGetLine#*
\FancyVerbDefineActive#*
\FancyVerbFormatCom#*
\FancyVerbSpace#*
\FancyVerbTabSize#*
\FancyVerbTab#*
\FancyVerbRuleColor#*
\SaveMVerb#*
\FancyVerbGetVerb#*
\SaveGVerb#*
\UseMVerb#*
\pUseMVerb#*
\FancyVerbAfterSave#*
