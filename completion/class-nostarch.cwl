# nostarch class
# Matthew Bertucci 2023/05/11 for v2.1

#include:class-book
#include:xcolor
# loads table option of xcolor
#include:iftex
#include:ifpdf
#include:longtable
#include:fancyhdr
#include:fancyvrb
#include:booktabs
#include:graphicx
#include:listings
#include:caption
#include:makeidx
#include:upquote
#include:pifont
#include:textcomp
#include:xcolor
#include:lmodern
#include:nameref
#include:float
#include:amssymb
#include:etoolbox
#include:setspace
#include:marginnote
#include:url
#include:mdframed
# loads framemethod=TikZ option of mdframed
#include:soul
#include:fontenc
# loads T1 option of fontenc
#include:ragged2e

#keyvals:\documentclass/nostarch#c
cfonts
nocfonts
fontsdir
nofontsdir
8pt
9pt
10pt
11pt
12pt
#endkeyvals

\begin{cipblock}
\end{cipblock}
\begin{Code}
\begin{Code}[options%keyvals]
\end{Code}
\begin{copyrightpage}
\end{copyrightpage}
\begin{dedicationpage}
\end{dedicationpage}
\begin{note}
\end{note}

\brieftableofcontents
\chapterart{graphics code}
\chapterartfile{imagefile}#g
\colophon
\makehalftitle
\NextCaptionWidth{length}
\nostarchlocation{location}
\nostarchlogo{imagefile}#g
\sectionnumberwidth#L
\subsectionnumberwidth#L
\subtitle{text}
\tbfont
\thfont
\updatespage

#keyvals:\begin{Code}
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

# not documented
nspgray#B
\begin{codewide}#*
\begin{codewide}[options]#*
\end{codewide}#*
\begin{custombox}{text}#*
\end{custombox}#*
\begin{customboxcontinued}#*
\end{customboxcontinued}#*
\begin{figurewide}#*
\begin{figurewide}[placement]#*
\end{figurewide}#*
\begin{nspbox}{text}#*
\end{nspbox}#*
\begin{nspboxcontinued}#*
\end{nspboxcontinued}#*
\begin{plainlist}#*
\end{plainlist}#*
\begin{tablewide}#*
\begin{tablewide}[placement]#*
\end{tablewide}#*
\begin{tabularwide}{cols}#*\tabular
\end{tabularwide}

\apptoc#S
\bettertilde#S
\boldsectionnumberwidth#*
\boxlst{text}#*
\briefcontentsname#*
\captionlst{text}#*
\chapterwithquote#*
\codewingding{number}#*
\colophonname#*
\continued#*
\Cscale#S
\dgdefault#S
\dogma#*
\fauxschelper#S
\fauxschelphelp{arg1}{arg2}#S
\futuraboldc#*
\futuraboldcoblique#*
\futurabook#*
\futuraheavy#*
\futuraoblique#*
\Hscale#S
\indexgroup{text}#*
\keycap{arg}#S
\marginwingding{number}#*
\menuarrow#S
\projecthead{text}#*
\slashslash#S
\sobox#S
\sochapter#S
\sonote#S
\sotitle#S
\tablelst{text}#*
\term{text}#*
\theproject#S
\timesnewroman#*
\turnoffbigpara#*
\updatesname#*
\Vscale#S
\wingding{number}#*

# from table option of xcolor
#include:colortbl

# from framemethod=TikZ option of mdframed
#include:tikz

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
