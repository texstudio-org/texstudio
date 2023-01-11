# lecturer package
# Matthew Bertucci 11/7/2021 for v1.0

#include:yax

\slide
\slide[attributes%keyvals]
\endslide

#keyvals:\slide
pdftitle=%<string%>
bookmark#true,false
bookmarklevel=%<number%>
bookmarkstyle=%<bookmark options%>
anchor=%<name%>
width=##L
height=##L
hsize=##L
left=##L
right=##L
vsize=##L
top=##L
bottom=##L
baselineskip=##L
topskip=##L
parskip=##L
parindent=##L
hpos=#ff,fr,rf,rr
vpos=#top,center,bottom
scale#true,false
everyslide=%<code%>
areas=%<list of areas%>
areas*=%<list of areas%>
background=#%color
foreground=#%color
image=%<image%>
font=%<font command%>
transition=%<named transition%>
#endkeyvals

\step
\step[attributes%keyvals]

#keyvals:\step
pdftitle=%<string%>
on=%<list of steps%>
off=%<list of steps%>
handout#true,false
visible#true,false
left=##L
right=##L
vskip=##L
everyvstep=%<code%>
hskip=##L
everyhstep=%<code%>
group#true,false
font=%<font command%>
color=#%color
transition=%<named transition%>
#endkeyvals

\slideno
\slidenumber

\presentationonly{material}
\handoutonly{material}
\presentationorhandout{presentation}{handout}

\setslide{list of slides}
\setstep{list of steps}

\showgrid{increment%l}
\showgrid{increment%l}[color]#*
\showgrid{increment%l}[color][line width]#*
\showgrid[left,top]{increment%l}#*
\showgrid[left,top]{increment%l}[color]#*
\showgrid[left,top]{increment%l}[color][line width]
\hidegrids

\position{area}{material}
\position{area}[left,top]{material}

\setarea{list of areas}

\createbookmark{level}{text}
\createbookmark[options%keyvals]{level}{text}
\createbookmark{level}[anchor]{text}
\createbookmark[options%keyvals]{level}[anchor]{text}

#keyvals:\createbookmark#c
bold
italic
bolditalic
open
closed
nosubmenutext
#endkeyvals

\showbookmarks{text}
\showbookmarks[optional style%keyvals]{text}

\anchor{name}

\goto{name}{text}
\goto[optional style%keyvals]{name}{text}
\gotoA{name}{text}
\gotoA[optional style%keyvals]{name}{text}
\gotoB{name}{text}
\gotoB[optional style%keyvals]{name}{text}A
\firstslide{text}
\firstslide[optional style%keyvals]{text}
\lastslide{text}
\lastslide[optional style%keyvals]{text}
\prevslide{text}
\prevslide[optional style%keyvals]{text}
\nextslide{text}
\nextslide[optional style%keyvals]{text}
\prevstep{text}
\prevstep[optional style%keyvals]{text}
\nextstep{text}
\nextstep[optional style%keyvals]{text}
\showorhide{actions}{text}
\showorhide[optional style%keyvals]{actions}{text}

#keyvals:\showbookmarks,\goto,\gotoA,\gotoB,\firstslide,\lastslide,\prevslide,\nextslide,\prevstep,\nextstep,\showorhide
flash
push
none
#endkeyvals

\newcolor{name%specialDef}{color model}{values}#s#%color
\newcolor{name%specialDef}{color model}[opacity]{values}#s#%color
black#B
white#B
red#B
green#B
blue#B
cyan#B
magenta#B
yellow#B
\usecolor{color}

\newshade{name%specialDef}#s#%color

\newimage{name}{file}
\newimage{name}[width,height]{file}
\useimage{name}

\newsymbol{cmd}{drawing}#d
\newsymbol{cmd}[settings%keyvals]{drawing}#d

#keyvals:\newsymbol#c
left=##L
right=##L
top=##L
bottom=##L
padding=##L
#endkeyvals

\symbolwidth{symbol cmd}
\symbolheight{symbol cmd}
\symboldepth{symbol cmd}

\newtransition{name}

\addtopageobject{code}
\addtoeachpageobject{code}
\addtopageresources{code}

\addproperties{name}{object number}
\addshading{name}{object number}
\addgstate{name}{object number}
\addOCG{object number}
\addvisibleOCG{object number}