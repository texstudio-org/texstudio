# notespages package
# Matthew Bertucci 11/3/2021 for v0.8.1

#include:xkeyval

\setnotespages{options%keyvals}
\notespage
\notespage[options%keyvals]
\notespages
\notespages[options%keyvals]
\notesfill
\notesfill[options%keyvals]

#keyvals:\setnotespages,\notespage,\notespages,\notesfill,\usepackage/notespages#c
allowfloats#true,false
notesstyle=#plain,lines,vlines,grid,text
hparts=%<integer%>
vparts=%<integer%>
usenotesareaheight#true,false
titlestyle=#none,text,section,subsection,subsubsection,minisec
titletext={%<text%>}
titleskip=##L
titlenotesfill#true,false
notestext={%<text%>}
notestextalign=#right,left,center,none
empty
vacant
default
#endkeyvals

#keyvals:\setnotespages,\notespage,\notespages,\definenotesoption,\nppatchchapter,\usepackage/notespages#c
startnotes=#newpage,clearpage
pagestyle=#empty,plain,headings,myheadings,current
mark=#both,right,left,keep
marktext={%<text%>}
markuppercase#true,false
#endkeyvals

#keyvals:\setnotespages,\notespages,\definenotesoption,\nppatchchapter,\usepackage/notespages#c
multiple=%<integer%>
minpages=%<integer%>
endpages=%<integer%>
#endkeyvals

#keyvals:\setnotespages,\notesfill,\definenotesoption,\nppatchchapter,\usepackage/notespages#c
fillminspace=##L
fillmaxspace=##L
filltopskip=##L
filltopfill#true,false
#endkeyvals

\definenotesoption{name}{options%keyvals}#*
\definenotesstyle{name}{commands}#*
\remainingtextheight#*
\notesareatext#*
\definetitlestyle{name}{commands}#*
\notestitletext#*
\nppatchchapter{options%keyvals}#*
\npunpatchchapter#*
\npnotesname#*
\npnotestext#*
NotesHColor#B
NotesVColor#B
NotesTextColor#B
