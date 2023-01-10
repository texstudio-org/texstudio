# fvextra package
# Matthew Bertucci 2022/12/01 for v1.5

#include:etoolbox
#include:fancyvrb
#include:upquote
#include:textcomp
#include:lineno

#keyvals:\Verb,\Verb*,\DefineShortVerb,\begin{Verbatim},\begin{Verbatim*},\begin{BVerbatim},\begin{BVerbatim*},\begin{LVerbatim},\begin{LVerbatim*},\fvset,\DefineVerbatimEnvironment,\CustomVerbatimEnvironment,\RecustomVerbatimEnvironment,\CustomVerbatimCommand,\RecustomVerbatimCommand,\SaveVerb,\SaveVerb*,\UseVerb,\UseVerb*,\begin{SaveVerbatim},\UseVerbatim,\BUseVerbatim,\LUseVerbatim,\VerbatimInput,\BVerbatimInput,\LLVerbatimInput,\fvinlineset,\EscVerb,\EscVerb*,\RobustVerb,\RobustVerb*,\RobustUseVerb,\RobustUseVerb*,\RobustEscVerb,\RobustEscVerb*
beameroverlays#true,false
curlyquotes#true,false
extra#true,false
fontencoding=%<encoding%>
highlightcolor=#%color
highlightlines={%<line ranges%>}
linenos#true,false
mathescape#true,false
numberfirstline#true,false
numbers=#none,left,right,both
retokenize#true,false
space=%<macro%>
spacecolor=#%color
stepnumberfromfirst#true,false
stepnumberoffsetvalues#true,false
tab=%<macro%>
tabcolor=#%color
breakafter=%<string%>
breakafterinrun#true,false
breakaftersymbolpre=%<string%>
breakaftersymbolpost=%<string%>
breakanywhere#true,false
breakanywheresymbolpre=%<string%>
breakanywheresymbolpost=%<string%>
breakautoindent#true,false
breakbefore=%<string%>
breakbeforeinrun#true,false
breakbeforesymbolpre=%<string%>
breakbeforesymbolpost=%<string%>
breakindent=##L
breakindentnchars=%<integer%>
breaklines#true,false
breaknonspaceingroup#true,false
breaksymbol=%<string%>
breaksymbolleft=%<string%>
breaksymbolright=%<string%>
breaksymbolindent=##L
breaksymbolindentnchars=%<integer%>
breaksymbolindentleft=##L
breaksymbolindentleftnchars=%<integer%>
breaksymbolindentright=##L
breaksymbolindentrightnchars=%<integer%>
breaksymbolsep=##L
breaksymbolsepnchars=%<integer%>
breaksymbolsepleft=##L
breaksymbolsepleftnchars=%<integer%>
breaksymbolsepright=##L
breaksymbolseprightnchars=%<integer%>
breakbytoken#true,false
breakbytokenanywhere#true,false
#endkeyvals

\fvinlineset{options%keyvals}

# keys from fancyvrb for fvextra commands
#keyvals:\fvinlineset,\EscVerb,\EscVerb*,\RobustVerb,\RobustVerb*,\RobustUseVerb,\RobustUseVerb*,\RobustEscVerb,\RobustEscVerb*
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
vspace=##L
listparameters={%<code%>}
#endkeyvals

# the aftersave key also makes sense in \fvinlineset
#keyvals:\fvinlineset
aftersave={%<code%>}
#endkeyvals

\FancyVerbFormatInline{text%plain}#*
\FancyVerbFormatText#*

\EscVerb{backslash-escaped text}
\EscVerb[options%keyvals]{backslash-escaped text}
\EscVerb*{backslash-escaped text}#*
\EscVerb*[options%keyvals]{backslash-escaped text}#*

\begin{VerbEnv}#V
\begin{VerbEnv}[options%keyvals]#V
\end{VerbEnv}

\FancyVerbBreakStart#*
\FancyVerbBreakStop#*
\FancyVerbBreakAnywhereBreak#*
\FancyVerbBreakBeforeBreak#*
\FancyVerbBreakAfterBreak#*
\FancyVerbBreakByTokenAnywhereBreak#*

\VerbatimPygments{literal macro%cmd}{actual macro%cmd}#*

FancyVerbHighlightColor#B

\FVExtraDoSpecials#*
\FVExtraReadOArgBeforeVArg{arg}#*
\FVExtraReadOArgBeforeVArg[opt]{arg}#*
\FVExtraReadOArgBeforeVEnv{arg}#*
\FVExtraReadOArgBeforeVEnv[opt]{arg}#*
\FVExtraReadVArg{arg}#*
\FVExtrapdfstringdef{arg1}{arg2}#*
\FVExtrapdfstringdefDisableCommands#*
\FVExtraAlwaysUnexpanded{arg}#*
\FVExtraRobustCommand{arg1}{arg2}#*
\FVExtraUnexpandedReadStarOArgMArg{arg}#*
\FVExtraUseVerbUnexpandedReadStarOArgMArg{arg}#*
\FVExtraUnexpandedReadStarOArgBVArg{arg}#*
\FVExtraUnexpandedReadStarOArgBEscVArg{arg}#*
\FVExtraPDFStringEscapeChar{arg}#*
\FVExtraPDFStringEscapeChars{arg}#*
\FVExtraVerbatimDetokenize{arg}#*
\FVExtraPDFStringVerbatimDetokenize{arg}#*
\FVExtraEscapedVerbatimDetokenize{arg}#*
\FVExtraPDFStringEscapedVerbatimDetokenize{arg}#*
\FVExtraDetokenizeVArg{arg1}{arg2}#*
\FVExtraDetokenizeEscVArg{arg1}{arg2}#*
\FVExtraDetokenizeREscVArg{arg1}{arg2}#*
\FVExtraRetokenizeVArg{macro%cmd}{code}{chars}#*d
\FVExtraUnexpandedReadStarOArgMArgBVArg{arg}#*
\RobustVerb[options%keyvals]{verbatimSymbol}#S
\RobustVerb|%<code%>|#*
\RobustVerb[%<options%>]|%<code%>|#*
\RobustVerb*[options%keyvals]{verbatimSymbol}#S
\RobustVerb*|%<code%>|#*
\RobustVerb*[%<options%>]|%<code%>|#*
\RobustUseVerb{name}#*
\RobustUseVerb[options%keyvals]{name}#*
\RobustUseVerb*{name}#*
\RobustUseVerb*[options%keyvals]{name}#*
\RobustEscVerb{backslash-escaped text}#*
\RobustEscVerb[options%keyvals]{backslash-escaped text}#*
\RobustEscVerb*{backslash-escaped text}#*
\RobustEscVerb*[options%keyvals]{backslash-escaped text}#*
\FancyVerbMathSpace#*
\FancyVerbFillColor#*
\FancyVerbMathEscape#*
\FancyVerbBeamerOverlays#*
\FancyVerbCurlyQuotes#*
\FancyVerbHighlightColor#*
\FancyVerbHighlightLine{arg}#*
\FancyVerbHighlightLineNormal{arg}#*
\FancyVerbHighlightLineFirst{arg}#*
\FancyVerbHighlightLineMiddle{arg}#*
\FancyVerbHighlightLineLast{arg}#*
\FancyVerbHighlightLineSingle{arg}#*
\FancyVerbBreakSymbolLeft#*
\FancyVerbBreakSymbolRight#*
\FancyVerbBreakSymbolLeftLogic{arg}#*
\theFancyVerbLineBreakLast#*
\FancyVerbBreakSymbolRightLogic{arg}#*
\FancyVerbBreakAnywhereSymbolPre#*
\FancyVerbBreakAnywhereSymbolPost#*
\FancyVerbBreakBeforeSymbolPre#*
\FancyVerbBreakBeforeSymbolPost#*
\FancyVerbBreakAfterSymbolPre#*
\FancyVerbBreakAfterSymbolPost#*
