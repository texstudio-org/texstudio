# typearea package
# Matthew Bertucci 2022/05/18 for v3.36

#include:scrkbase
#include:scrlogo

#keyvals:\KOMAoptions#c
BCOR=%<correction%>
DIV=#areaset,calc,classic,current,default,last
twoside=#true,on,yes,false,off,no,semi
twocolumn=#true,on,yes,false,off,no
headinclude=#true,on,yes,false,off,no
footinclude=#true,on,yes,false,off,no
mpinclude=#true,on,yes,false,off,no
headlines=%<number of lines%>
headheight=##L
footlines=%<number of lines%>
footheight=##L
paper=#letter,legal,executive,A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,landscape,seascape,portrait
pagesize
pagesize=#auto,automedia,false,no,off,dvipdfmx,dvips,pdftex,luatex
headsepline=#true,on,yes,false,off,no
footsepline=#true,on,yes,false,off,no
areasetadvanced=#true,on,yes,false,off,no
usegeometry
#endkeyvals

\PaperNameToSize{name}#*
\ProvideUnknownPaperSizeError{type}{code}#*
\isopaper{number}#*
\isopaper[letter]{number}#*

\AfterCalculatingTypearea{code}
\AfterCalculatingTypearea*{code}
\activateareas
\typearea{DIV}
\typearea[BCOR]{DIV}
\recalctypearea
\storeareas{command}#d
\BeforeRestoreareas{code}
\BeforeRestoreareas*{code}
\AfterRestoreareas{code}
\AfterRestoreareas*{code}
\areaset{width}{height}
\areaset[BCOR]{width}{height}
\AfterSettingArea{code}
\AfterSettingArea*{code}
\footheight#*L

# deprecated
\SetDIVList#S
\SetXDIVList#S
