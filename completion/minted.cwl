# minted package
# modified by Tim Hoffmann 2014-03-24
# modified by Elias Kirchgässner 2016-07-27
# modified by muzimuzhi 2020 Feb 15, minted v2.5
# modified by Matthew Bertucci 2025 May 15, v3.7.0

#include:catchfile
#include:etoolbox
#include:fvextra
#include:latex2pydata
#include:pdftexcmds
#include:pgfkeys
#include:pgfopts
#include:shellesc
#include:xcolor
#include:float

#ifOption:newfloat
#include:newfloat
#endif
#ifOption:newfloat=true
#include:newfloat
#endif

#keyvals:\usepackage/minted#c
chapter
section
cache#true,false
cachedir=%<directory%>
debug#true,false
frozencache#true,false
highlightmode=#fastfirst,fast,immediate
inputlexerlinenos#true,false
lexerlinenos#true,false
newfloat#true,false
placeholder#true,false
verbatim#true,false
#endkeyvals

\begin{minted}[options%keyvals]#S
\begin{minted}{language}#MV
\begin{minted}[options%keyvals]{language}#M
\end{minted}
\mint[keys]{language}{verbatimSymbol}#S
##\mint{%<language%>}{%<code%>}#M
\mint{%<language%>}|%<code%>|#M
##\mint[%<options%>]{%<language%>}{%<code%>}#M
\mint[%<options%>]{%<language%>}|%<code%>|#M
\mintinline[keys]{language}{verbatimSymbol}#S
##\mintinline{%<language%>}{%<code%>}#M
\mintinline{%<language%>}|%<code%>|#M
##\mintinline[%<options%>]{%<language%>}{%<code%>}#M
\mintinline[%<options%>]{%<language%>}|%<code%>|#M
\inputminted{language}{file}
\inputminted[options%keyvals]{language}{file}
\usemintedstyle{pygments style}#*
\usemintedstyle[language]{pygments style}#*
\setminted{options%keyvals}
\setminted[language]{options%keyvals}
\setmintedinline{options%keyvals}
\setmintedinline[language]{options%keyvals}

\begin{listing}
\begin{listing}[placement]
\end{listing}
\listoflistings
\listingscaption#*
\listoflistingscaption#*

\newminted{language}{options%keyvals}
\newminted[envname]{language}{options%keyvals}#N
\newmint{language}{options%keyvals}
\newmint[macro name]{language}{options%keyvals}
\newmintinline{language}{options%keyvals}
\newmintinline[macro name]{language}{options%keyvals}
\newmintedfile{language}{options%keyvals}
\newmintedfile[macro name]{language}{options%keyvals}

#keyvals:\begin{minted},\mint,\mintinline,\inputminted,\setminted,\setmintedinline,\newminted,\newmint,\newmintinline,\newmintedfile
autogobble#true,false
baselinestretch=##L
beameroverlays#true,false
bgcolor=#%color
bgcolorpadding=##L
bgcolorvphantom=%<macro%>
breakafter=%<string%>
breakafterinrun#true,false
breakaftersymbolpost=%<string%>
breakaftersymbolpre=%<string%>
breakanywhere#true,false
breakanywhereinlinestretch=##L
breakanywheresymbolpost=%<string%>
breakanywheresymbolpre=%<string%>
breakautoindent#true,false
breakbefore=%<string%>
breakbeforeinrun#true,false
breakbeforesymbolpost=%<string%>
breakbeforesymbolpre=%<string%>
breakbytoken#true,false
breakbytokenanywhere#true,false
breakindent=##L
breakindentnchars=%<integer%>
breaklines#true,false
breaksymbol=%<string%>
breaksymbolindent=##L
breaksymbolindentnchars=%<integer%>
breaksymbolindentleft=##L
breaksymbolindentleftnchars=%<int%>
breaksymbolindentritht=##L
breaksymbolindentrightnchars=%<int%>
breaksymbolleft=%<string%>
breaksymbolright=%<string%>
breaksymbolsep=##L
breaksymbolsepnchars=%<int%>
breaksymbolsepleft=##L
breaksymbolsepleftnchars=%<int%>
breaksymbolsepright=##L
breaksymbolseprightnchars=%<int%>
codetagify=%<string list%>
curlyquotes#true,false
encoding=%<encoding%>
envname=%<string%>
escapeinside=%<two chars%>
extrakeywords={%<word1,word2,...%>}
extrakeywordsconstant={%<word1,word2,...%>}
extrakeywordsdeclaration={%<word1,word2,...%>}
extrakeywordsnamespace={%<word1,word2,...%>}
extrakeywordspseudo={%<word1,word2,...%>}
extrakeywordsreserved={%<word1,word2,...%>}
extrakeywordstype={%<word1,word2,...%>}
firstline=%<integer%>
firstnumber=#auto,last,%<integer%>
fontencoding=%<font encoding%>
fontfamily=%<family name%>
fontseries=%<series name%>
fontshape=%<shape name%>
fontsize=%<size command%>
formatcom=%<command%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
funcnamehighlighting#true,false
gobble=%<integer%>
gobblefilter=%<integer%>
highlightcolor=#%color
highlightlines=%<list of lineno ranges%>
ignorelexererrors#true,false
keywordcase=#lower,upper,capitalize,none
label=%<string%>
labelposition=#none,topline,bottomline,all
lastline=%<integer%>
linenos#true,false
listparameters=%<macro%>
literalenvname=%<string%>
literatecomment=%<macro%>
mathescape#true,false
numberblanklines#true,false
numberfirstline#true,false
numbers=#left,right,both,none
numbersep=##L
obeytabs#true,false
python3#true,false
rangeregex=%<macro%>
rangeregexmatchnumber=%<integer%>
rangeregexdotall#true,false
rangeregexmultiline#true,false
rangestartafterstring=%<macro%>
rangestartstring=%<macro%>
rangestopbeforestring=%<macro%>
rangestopstring=%<macro%>
reflabel=##l
resetmargins#true,false
rulecolor=#%color
samepage#true,false
showspaces#true,false
showtabs#true,false
space=%<macro%>
spacecolor=#%color
startinline#true,false
stepnumber=%<integer%>
stepnumberfromfirst#true,false
stepnumberoffsetvalues#true,false
stripall#true,false
stripnl#true,false
style=%<pygments style%>
tab=%<macro%>
tabcolor=#%color
tabsize=%<integer%>
texcl#true,false
texcomments#true,false
tokenmerge#true,false
vspace=##L
xleftmargin=##L
xrightmargin=##L
#endkeyvals

\MintedJobnameMdfive#S
\MintedCacheIndexFilename#S
\MintedConfigFilename#S
\MintedDataFilename#S
\MintedErrlogFilename#S
\MintedMessageFilename#S
\mintedoldcachechecksum#S
\mintedpgfkeyscreate{option category}{keyvals}#S
\mintedpgfkeyscreate[processor]{option category}{keyvals}#S
\mintedpyoptvalueof{arg}#S
\mintedtexoptvalueof{arg}#S
\PYGZsq#S
\PYGZhy#S
\RobustMintInline{arg}#S
\RobustMintInline[opt]{arg}#S
\RobustMintInlineProcess{arg1}{arg2}{arg3}#S
\RobustMint{arg}#S
\RobustMint[opt]{arg}#S
\RobustMintProcess{arg1}{arg2}{arg3}#S
\RobustNewMint#S
\RobustNewMintInline#S
