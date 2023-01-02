# xebaposter class
# Matthew Bertucci 4/14/2022 for v2.51

#include:xkeyval
#include:calc
#include:xcolor
#include:ifxetex
#include:tikz
#include:pgf
#include:ifthen
#include:fontenc
# loads T1 option of fontenc
#include:geometry
#include:pgfpages
#include:tikzlibrarydecorations
#include:tikzlibraryfadings
#include:tikzlibrarycalc

#keyvals:\documentclass/xebaposter#c
landscape
portrait
paperwidth=##L
paperheight=##L
archA
archB
archC
archD
archE
archE1
archE2
archE3
a0paper
a1paper
a2paper
a3paper
a4paper
a5paper
a6paper
b0paper
b1paper
b2paper
b3paper
b4paper
b5paper
b6paper
ansiapaper
ansibpaper
ansicpaper
ansidpaper
ansiepaper
letterpaper
legalpaper
executivepaper
screen
fontscale=%<factor%>
margin=##L
movebody=##L
debug
table
showframe
persian
latin
#endkeyvals

#ifOption:table
#include:colortbl
#endif

\begin{poster}{settings%keyvals}{eyecatcher}{title%text}{author}{logo}
\end{poster}

\begin{posterbox}{title}#L2
\begin{posterbox}[options%keyvals]{title}#L2
\end{posterbox}

#keyvals:\begin{poster}
grid#true,false
eyecatcher#true,false
headerheight=##L
columns=%<number%>
colspacing=##L
bgColorOne=#%color
bgColorTwo=#%color
background=#shadeLR,shadeTB,plain,user,none
#endkeyvals

#keyvals:\begin{poster},\begin{posterbox},\headerbox
cornerradius=##L
boxheaderheight=##L
boxpadding=##L
textborder=#none,bars,coils,triangles,rectangle,rounded,roundedleft,roundedright,roundedsmall,faded
boxshade=#shadelr,shaderl,shadetb,plain,none
headershade=#shadelr,shaderl,shadetb,shadetbinverse,plain
headershape=#rectangle,rounded,smallrounded,roundedleft,roundedright
headerborder=#open,closed,none
borderColor=#%color
headerColorOne=#%color
headerColorTwo=#%color
headerFontColor=#%color
boxColorOne=#%color
boxColorTwo=#%color
headerfont=%<font commands%>
textfont=%<font commands%>
linewidth=##L
below=%<box name%>
above=%<box name%>
aligned=%<box name%>
bottomaligned=%<box name%>
column=%<number%>
row=%<number%>
span=%<number%>
height=##L
name=%<name%>
#endkeyvals

\background{graphics code}

# not documented
\boxheight#*
\boxstartx#*
\boxstarty#*
\boxwidth#*
\colheight#*
\colwidth#*
\gridpos#*
\headerbox{title}{options%keyvals}{content%text}#*L1
\headerheight#*
\xebaposterBoxDrawBackground{color}{color}#*
\xebaposterBoxDrawBorder{color}#*
\xebaposterBoxGetShape#*
\xebaposterHeaderDrawBackground{color}{color}{color}#*
\xebaposterHeaderDrawBorder{color}#*
\xebaposterHeaderDrawText{color}#*
\xebaposterHeaderGetShape#*
\xebaposterHeaderSetShade{color}{color}{color}#*
\xebaposterPosterDrawBackground{color}{color}#*
\debug{text}#S

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
