# minted package
# modified by Tim Hoffmann 2014-03-24
# modified by Elias Kirchgässner 2016-07-27
# modified by muzimuzhi 2020 Feb 15, minted v2.5

#include:keyval
#include:kvoptions
#include:fvextra
#include:calc
#include:shellesc
#include:ifplatform
#include:pdftexcmds
#include:etoolbox
#include:xstring
#include:lineno
#include:framed
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
cache#true,false
cachedir=%<directory%>
finalizecache#true,false
frozencache#true,false
draft#true,false
final#true,false
kpsewhich#true,false
langlinenos#true,false
newfloat#true,false
outputdir=%<directory%>
#endkeyvals

\begin{minted}[options%keyvals]#S
\begin{minted}{language}#MV
\begin{minted}[options%keyvals]{language}#M
\end{minted}
\mint{%<language%>}{%<code%>}
\mint{%<language%>}|%<code%>|
\mint[%<options%>]{%<language%>}{%<code%>}
\mint[%<options%>]{%<language%>}|%<code%>|
\mint{language}{verbatimSymbol}#S
\mintinline{%<language%>}{%<code%>}
\mintinline{%<language%>}|%<code%>|
\mintinline[%<options%>]{%<language%>}{%<code%>}
\mintinline[%<options%>]{%<language%>}|%<code%>|
\mintinline{language}{verbatimSymbol}#S
\inputminted{language}{file}#i
\inputminted[options%keyvals]{language}{file}#i
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
\newminted[envname]{language}{options%keyvals}
\newmint{language}{options%keyvals}
\newmint[macro name]{language}{options%keyvals}
\newmintinline{language}{options%keyvals}
\newmintinline[macro name]{language}{options%keyvals}
\newmintedfile{language}{options%keyvals}
\newmintedfile[macro name]{language}{options%keyvals}

# Keys that include \mintinline
#keyvals:\begin{minted},\mint,\mintinline,\inputminted,\setminted,\setmintedinline,\newminted,\newmint,\newmintinline,\newmintedfile
autogobble#true,false
baselinestretch=##L
beameroverlays#true,false
breakbytoken#true,false
breakbytokenanywhere#true,false
breaklines#true,false
bgcolor=#%color
codetagify=%<string list%>
curlyquotes#true,false
encoding=%<encoding%>
escapeinside=%<two chars%>
firstline=%<int%>
firstnumber=#auto,last,%<integer%>
fontfamily=%<family name%>
fontseries=%<series name%>
fontsize=%<size command%>
fontshape=%<shape name%>
formatcom=%<command%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
funcnamehighlighting#true,false
gobble=%<int%>
highlightcolor=#%color
highlightlines=%<list of lineno ranges%>
keywordcase=#lower,upper,capitalize
label=%<string%>
labelposition=#none,topline,bottomline,all
lastline=%<int%>
linenos#true,false
numberfirstline#true,false
numbers=#left,right,both,none
mathescape#true,false
numberblanklines#true,false
numbersep=##L
obeytabs#true,false
outencoding=%<encoding%>
python3#true,false
resetmargins#true,false
rulecolor=#%color
samepage#true,false
showspaces#true,false
showtabs#true,false
space=%<command%>
spacecolor=#%color
startinline#true,false
style=%<pytments style%>
stepnumber=%<int%>
stepnumberfromfirst#true,false
stepnumberoffsetvalues#true,false
stripall#true,false
stripnl#true,false
tab=%<commnd%>
tabcolor=#%color
tabsize=%<int%>
texcl#true,false
texcomments#true,false
xleftmargin=##L
xrightmargin=##L
#endkeyvals

# Keys that exclude \mintinline
#keyvals:\begin{minted},\mint,\inputminted,\setminted,\newminted,\newmint,\newmintedfile
breakafter=%<string%>
breakaftergroup#true,false
breakaftersymbolpre=%<string%>
breakaftersymbolpost=%<string%>
breakanywhere#true,false
breakanywheresymbolpre=%<string%>
breakanywheresymbolpost=%<string%>
breakautoinden#true,false
breakbefore=%<string%>
breakbeforegroup#true,false
breakbeforesymbolpre=%<string%>
breakbeforesymbolpost=%<string%>
breakindent=##L
breakindentnchars=%<int%>
breaksymbol=%<string%>
breaksymbolleft=%<string%>
breaksymbolright=%<string%>
breaksymbolindent=##L
breaksymbolindentnchars=%<int%>
breaksymbolindentleft=##L
breaksymbolindentleftnchars=%<int%>
breaksymbolindentritht=##L
breaksymbolindentrightnchars=%<int%>
breaksymbolsep=##L
breaksymbolsepnchars=%<int%>
breaksymbolsepleft=##L
breaksymbolsepleftnchars=%<int%>
breaksymbolsepright=##L
breaksymbolseprightnchars=%<int%>
#endkeyvals

\DeleteFile{file}#*
\DeleteFile[directory]{file}#*
\MintedPygmentize#*
