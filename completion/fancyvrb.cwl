# fancyvrb package
# neeraavi 12 Apr 2007
# muzimuzhi 15 Mar 2020, fancyvrb v3.5
# muzimuzhi 25 Mar 2020

#include:keyval

\Verb{verbatimSymbol}#S
\Verb|%<code%>|
\Verb*{verbatimSymbol}#S
\Verb*|%<code%>|
\VerbatimFootnotes
\DefineShortVerb{verb char}
\UndefineShortVerb{verb char}

\begin{Verbatim}#V
\begin{Verbatim}[options%keyvals]
\end{Verbatim}
\begin{Verbatim*}#V
\begin{Verbatim*}[options%keyvals]
\end{Verbatim*}
\begin{BVerbatim}#V
\begin{BVerbatim}[options%keyvals]
\end{BVerbatim}
\begin{BVerbatim*}#V
\begin{BVerbatim*}[options%keyvals]
\end{BVerbatim*}
\begin{LVerbatim}#V
\begin{LVerbatim}[options%keyvals]
\end{LVerbatim}
\begin{LVerbatim*}#V
\begin{LVerbatim*}[options%keyvals]
\end{LVerbatim*}
\fvset{options%keyvals}
\FancyVerbFormatLine#*
\theFancyVerbLine#*

\DefineVerbatimEnvironment{envname}{env type}{options%keyvals}
\RecustomVerbatimEnvironment{envname}{env type}{options%keyvals}
\CustomVerbatimCommand{command}{cmd type}{options%keyvals}
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

#keyvals:\begin{Verbatim},\begin{Verbatim*},\begin{BVerbatim},\begin{BVerbatim*},\begin{LVerbatim},\begin{LVerbatim*},\fvset,\DefineVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\UseVerb,\begin{SaveVerbatim},\UseVerbatim,\BUseVerbatim,\LUseVerbatim,\VerbatimInput,\BVerbatimInput,\LLVerbatimInput,\begin{VerbatimOut}
boxwidth
baseline=#b,c,t
commentchar=%<single char%>
gobble
formatcom
formatcom*
fontfamily
fontsize
fontshape
fontseries
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=#auto,last,integer
stepnumber
numberblanklines#true,false
firstline
lastline
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize
baselinestretch
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes
defineactive
#endkeyvals
