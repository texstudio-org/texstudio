# The mathtools package was created by Morten Hogholm and Lars Madsen daleif@imf.au.dk
# This file was created by Carlos Eduardo Valencia Urbina (2014-08-08). It contains most of the current commands of the mathtools package.
# URL: http://www.ctan.org/pkg/mathtools
# thatlittleboy/2018-05-07 edited
# Edited by Rishi Advani (2020-12-06)
# updated 2022-07-02 for v1.29

#include:keyval
#include:calc
#include:mhsetup
#include:amsmath
#include:graphicx

#keyvals:\usepackage/mathtools#c
fixamsmath
donotfixamsmathbugs
allowspaces
disallowspaces
legacycolonsymbols
# options passed to amsmath
intlimits
nointlimits
sumlimits
nosumlimits
namelimits
nonamelimits
leqno
reqno
centertags
tbtags
cmex10
fleqn
alignedleftspaceyes
alignedleftspaceno
alignedleftspaceyesifneg
#endkeyvals

\mathtoolsset{%<options%>}
#keyvals:\mathtoolsset
showonlyrefs#true,false
showmanualtags#true,false
original-intertext#true,false
original-shortintertext#true,false
mathic#true,false
above-intertext-sep=##L
below-intertext-sep=##L
above-shortintertext-sep=##L
below-shortintertext-sep=##L
smallmatrix-align=#c,l,r
smallmatrix-inner-space=
firstline-afterskip=##L
lastline-preskip=##L
multlined-width=##L
multlined-pos=#c,b,t
centercolon#true,false
prescript-sup-format=%<cmd%>
prescript-sub-format=%<cmd%>
prescript-arg-format=%<cmd%>
shortvdotsadjustabove=##L
shortvdotsadjustbelow=##L
#endkeyvals

\mathllap[mathstyle]{math}#*m
\mathllap{math}#m
\mathrlap[mathstyle]{math}#*m
\mathrlap{math}#m
\mathmbox{math}#m
\mathclap[mathstyle]{math}#*m
\mathclap{math}#m
\clap{text}#m
\mathmakebox[width][pos]{math}#m
\mathmakebox[width]{math}#*m
\mathmakebox{math}#m
\cramped[mathstyle]{math}#*m
\cramped{math}#m
\crampedllap[mathstyle]{math}#*m
\crampedllap{math}#m
\crampedrlap[mathstyle]{math}#*m
\crampedrlap{math}#m
\crampedclap[mathstyle]{math}#*m
\crampedclap{math}#m
\begin{crampedsubarray}{col}#m
\end{crampedsubarray}#m
\crampedsubstack{arg}#m

\smashoperator[pos%keyvals]{operator with limits}#m
\smashoperator{operator with limits}#m
#keyvals:\smashoperator
l
r
lr
rl
#endkeyvals

\adjustlimits{operator1}_{limit1}{operator2}_{limit2}#m
\SwapAboveDisplaySkip#m
\newtagform{name}[inner format]{left}{right}#n
\newtagform{name}{left}{right}#n
\renewtagform{name}[inner format]{left}{right}#n
\renewtagform{name}{left}{right}#n
\usetagform{name}#n
\refeq{label}#r
\noeqref{labellist}#r
\xleftrightarrow{sup}#m
\xleftrightarrow[sub]{sup}#m
\xLeftarrow{sup}#m
\xLeftarrow[sub]{sup}#m
\xhookleftarrow{sup}#m
\xhookleftarrow[sub]{sup}#m
\xmapsto{sup}#m
\xmapsto[sub]{sup}#m
\xRightarrow{sup}#m
\xRightarrow[sub]{sup}#m
\xLeftrightarrow{sup}#m
\xLeftrightarrow[sub]{sup}#m
\xhookrightarrow{sup}#m
\xhookrightarrow[sub]{sup}#m
\xrightharpoondown{sup}#m
\xrightharpoondown[sub]{sup}#m
\xleftharpoondown{sup}#m
\xleftharpoondown[sub]{sup}#m
\xrightleftharpoons{sup}#m
\xrightleftharpoons[sub]{sup}#m
\xrightharpoonup{sup}#m
\xrightharpoonup[sub]{sup}#m
\xleftharpoonup{sup}#m
\xleftharpoonup[sub]{sup}#m
\xleftrightharpoons{sup}#m
\xleftrightharpoons[sub]{sup}#m
\xlongrightarrow{sup}#m
\xlongrightarrow[sub]{sup}#m
\xlongleftarrow{sup}#m
\xlongleftarrow[sub]{sup}#m
\underbracket[rule thickness][bracket height]{arg}#m
\underbracket[rule thickness]{arg}#*m
\underbracket{arg}#m
\overbracket[rule thickness][bracket height]{arg}#m
\overbracket[rule thickness]{arg}#*m
\overbracket{arg}#m
\underbrace{arg}#m
\overbrace{arg}#m
\LaTeXunderbrace{arg}#*m
\LaTeXoverbrace{arg}#*m
\begin{dcases}#m\array
\begin{dcases*}#m\array
\begin{rcases}#m\array
\begin{rcases*}#m\array
\begin{drcases}#m\array
\begin{drcases*}#m\array
\begin{cases*}#m\array
\begin{matrix*}[col]#m\array
\begin{pmatrix*}[col]#m\array
\begin{bmatrix*}[col]#m\array
\begin{Bmatrix*}[col]#m\array
\begin{vmatrix*}[col]#m\array
\begin{Vmatrix*}[col]#m\array
\begin{smallmatrix*}[col]#m\array
\begin{psmallmatrix}#m\array
\begin{psmallmatrix*}[col]#m\array
\begin{bsmallmatrix}#m\array
\begin{bsmallmatrix*}[col]#m\array
\begin{Bsmallmatrix}#m\array
\begin{Bsmallmatrix*}[col]#m\array
\begin{vsmallmatrix}#m\array
\begin{vsmallmatrix*}[col]#m\array
\begin{Vsmallmatrix}#m\array
\begin{Vsmallmatrix*}[col]#m\array
\begin{spreadlines}{dimen}
\begin{lgathered}[pos]#m\array
\begin{rgathered}[pos]#m\array
\end{dcases}
\end{dcases*}
\end{rcases}
\end{rcases*}
\end{drcases}
\end{drcases*}
\end{cases*}
\end{matrix*}
\end{pmatrix*}
\end{bmatrix*}
\end{Bmatrix*}
\end{vmatrix*}
\end{Vmatrix*}
\end{smallmatrix*}
\end{psmallmatrix}
\end{psmallmatrix*}
\end{bsmallmatrix}
\end{bsmallmatrix*}
\end{Bsmallmatrix}
\end{Bsmallmatrix*}
\end{vsmallmatrix}
\end{vsmallmatrix*}
\end{Vsmallmatrix}
\end{Vsmallmatrix*}
\end{spreadlines}
\end{lgathered}
\end{rgathered}
\newgathered{envname}{pre line}{post line}{after}#N
\renewgathered{envname}{pre line}{post line}{after}#N
\begin{multlined}#m
\begin{multlined}[pos][width]#m
\end{multlined}
\MultlinedHook#*
\shoveleft{arg}#m
\shoveleft[dimen]{arg}#m
\shoveright{arg}#m
\shoveright[dimen]{arg}#m
\MoveEqLeft#m
\MoveEqLeft[number]#m
\Aboxed{left hand side & right hand side}#m
\MakeAboxedCommand%<\Aboxedname\boxmacro%>
\MakeAboxedCommand{cmd}#Sd
\ArrowBetweenLines#/alignat,alignat*
\ArrowBetweenLines[symbol]#/alignat,alignat*
\ArrowBetweenLines*#/alignat,alignat*
\ArrowBetweenLines*[symbol]#/alignat,alignat*
\vdotswithin{symbol}#m
\shortvdotswithin{symbol}#m
\shortvdotswithin*{symbol}#m
\MTFlushSpaceAbove#m
\MTFlushSpaceBelow#m
\origjot#*
\shortintertext{text}#m
\intertext{text}#m
\DeclarePairedDelimiter{cmd}{left delim%formula}{right delim%formula}#nd
\DeclarePairedDelimiterX{cmd}[args]{left delim%formula}{right delim%formula}{body%formula}#nd
\DeclarePairedDelimiterXPP{cmd}[args]{pre code%formula}{left delim%formula}{right delim%formula}{post code%formula}{body%formula}#nd

\reDeclarePairedDelimiterInnerWrapper{cmd}{star option%keyvals}{code%definition}
#keyvals:\reDeclarePairedDelimiterInnerWrapper
star
nostarnonscaled
nostarscaled
#endkeyvals

\lparen#m
\rparen#m
\vcentcolon#m
\ordinarycolon#m
\coloneqq#m
\eqqcolon#m
\colonapprox#m
\dblcolon#m
\Coloneqq#m
\Eqqcolon#m
\Colonapprox#m
\coloneq#m
\eqcolon#m
\colonsim#m
\Coloneq#m
\Eqcolon#m
\Colonsim#m
\approxcolon#m
\Approxcolon#m
\simcolon#m
\Simcolon#m
\colondash#m
\Colondash#m
\dashcolon#m
\Dashcolon#m
\nuparrow#m
\ndownarrow#m
\bigtimes#m
\prescript{sup}{sub}{arg}#m
\splitfrac{numer}{denom}#m
\splitdfrac{numer}{denom}#m
\xmathstrut{increase}#m
\xmathstrut[depth increase]{increase}#m
\newcases{envname}{sep}{preamble}{left}{right}#*N
\renewcases{envname}{sep}{preamble}{left}{right}#*N
\upbracketfill{arg1}{arg2}#S
\upbracketend{arg1}{arg2}#S
\downbracketfill{arg1}{arg2}#S
\downbracketend{arg1}{arg2}#S
