# fancyvrb package
# neeraavi 12 Apr 2007
# muzimuzhi 15 Mar 2020, fancyvrb v3.5
# muzimuzhi 25 Mar 2020
# Matthew Bertucci 27 Sep 2021 for v3.8

#include:keyval

\Verb{verbatimSymbol}#S
\Verb|%<code%>|
\Verb*{verbatimSymbol}#S
\Verb*|%<code%>|
\VerbatimFootnotes
\DefineShortVerb{\%<character%>}
\UndefineShortVerb{\%<character%>}

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
\FancyVerbFormatLine#*
\theFancyVerbLine#*
\FancyVerbStartString#*
\FancyVerbStopString#*

\DefineVerbatimEnvironment{envname}{env type}{options%keyvals}#N
\RecustomVerbatimEnvironment{envname}{env type}{options%keyvals}
\CustomVerbatimCommand{command}{cmd type}{options%keyvals}#d
\RecustomVerbatimCommand{command}{cmd type}{options%keyvals}

# saving and restoring verbatim text and envs
\SaveVerb{name}{verbatimSymbol}#S
\SaveVerb{name}|%<code%>|
\SaveVerb[aftersave=%|]{name}|%<code%>|
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
\VerbatimInput{file}
\VerbatimInput[options%keyvals]{file}
\BVerbatimInput{file}
\BVerbatimInput[options%keyvals]{file}
\LVerbatimInput{file}
\LVerbatimInput[options%keyvals]{file}
\begin{VerbatimOut}{file name}#V
\end{VerbatimOut}

#keyvals:\begin{Verbatim},\begin{Verbatim*},\begin{BVerbatim},\begin{BVerbatim*},\begin{LVerbatim},\begin{LVerbatim*},\fvset,\DefineVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\UseVerb,\begin{SaveVerbatim},\UseVerbatim,\BUseVerbatim,\LUseVerbatim,\VerbatimInput,\BVerbatimInput,\LLVerbatimInput
commentchar=%<single char%>
gobble=%<integer%>
formatcom=%<command%>
fontfamily=
fontsize=
fontshape=
fontseries=
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label=
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=#auto,last,integer
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=##L
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes=
defineactive=
reflabel=##l
#endkeyvals

#keyvals:\begin{BVerbatim},\begin{BVerbatim*},\fvset,\DefineVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\BUseVerbatim,\BVerbatimInput
boxwidth=##L
baseline=#b,c,t
#endkeyvals
