# algxpar package
# Matthew Bertucci 11/5/2021 for v0.91

#include:algorithmicx
#include:algpseudocode
#include:ragged2e
#include:listings
#include:amsmath
#include:amssymb
#include:xcolor
#include:tcolorbox
#include:fancyvrb

\Description#/algorithmic
\Input#/algorithmic
\Output#/algorithmic
\Commentl{text}#/algorithmic
\CommentIn{text}#/algorithmic
\Statep{text}#/algorithmic
\Statep[comment]{text}#/algorithmic
\If[comment]{condition}#/algorithmic
\ElsIf[comment]{condition}#/algorithmic
\Switch{selector}#/algorithmic
\Switch[comment]{selector}#/algorithmic
\EndSwitch#/algorithmic
\Case{value}#/algorithmic
\Case[comment]{value}#/algorithmic
\EndCase#/algorithmic
\Otherwise#/algorithmic
\EndOtherwise#/algorithmic
\While[comment]{condition}#/algorithmic
\Until[comment]{condition}#/algorithmic
\For[comment]{condition}#/algorithmic
\ForAll[comment]{condition}#/algorithmic
\ForEach{condition}#/algorithmic
\ForEach[comment]{condition}#/algorithmic

\True
\False
\Nil
\Id{id}
\TextString{text}
\VisibleSpace
\Read
\Write
\Set{id}{value}
\Setl{id}{value}
\Range{start}{end}
\Range[step]{start}{end}
\To
\DownTo
\Step

\NewLine
\begin{DefineCode}{name}
\end{DefineCode}
\UseCode{name}#/algorithmic
\ShowCode{name}
\ShowCode[options%keyvals]{name}

#keyvals:\begin{Verbatim},\begin{Verbatim*},\begin{BVerbatim},\begin{BVerbatim*},\begin{LVerbatim},\begin{LVerbatim*},\fvset,\DefineVerbatimEnvironment,\CustomVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\UseVerb,\begin{SaveVerbatim},\UseVerbatim,\BUseVerbatim,\LUseVerbatim,\VerbatimInput,\BVerbatimInput,\LLVerbatimInput
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