# luamplib package
# Matthew Bertucci 2025/05/15 for v2.37.3

#include:luatex

\begin{mplibcode}
\begin{mplibcode}[instance name,options%keyvals]
\end{mplibcode}
\mplibcode#S
\mplibcode[instance name]#S
\endmplibcode#S
\mplibforcehmode
\mplibnoforcehmode
\mpfig
\mpfig[options%keyvals]
\mpfig*
\mpfig*[options%keyvals]
\endmpfig
\mpfiginstancename#*
\mpliblegacybehavior{choice%keyvals}
\MPwidth
\MPheight
\MPllx
\MPlly
\MPurx
\MPury
\everymplib{MetaPost code%definition}
\everymplib[instance name]{MetaPost code%definition}
\everyendmplib{MetaPost code%definition}
\everyendmplib[instance name]{MetaPost code%definition}
\mpdim{dimen%l}
\mpcolor{color}
\mplibnumbersystem{type%keyvals}
\mplibmakenocache{file1,file2,...%file}
\mplibcancelnocache{file1,file2,...%file}
\mplibcachedir{directory path%definition}
\mplibtextextlabel{choice%keyvals}
\mplibcodeinherit{choice%keyvals}
\currentmpinstancename
\mplibglobaltextext{choice%keyvals}
\mplibverbatim{choice%keyvals}
\mplibshowlog{choice%keyvals}
\begin{mppattern}{name}
\begin{mppattern}{name}[options%keyvals]
\end{mppattern}
\mppattern{name}#S
\mppattern{name}[options]#S
\endmppattern#S
\mplibsetformat{format name%keyvals}
\usemplibgroup{name}
\usemplibgroup[options%keyvals]{name}
\begin{mplibgroup}{name}
\begin{mplibgroup}{name}[options%keyvals]
\end{mplibgroup}
\mplibgroup{name}#S
\mplibgroup{name}[options]#S
\endmplibgroup#S

#keyvals:\begin{mplibcode}#c,\mpfig#c,\mpfig*#c,\usemplibgroup#c
alt=%<alt text%>
actualtext=%<text%>
artifact
text
off
tag=%<tag name%>
adjust-BBox=%<llx lly urx ury%>
tagging-setup={%<keyvals%>}
instance=%<instance name%>
#endkeyvals

#keyvals:\mpliblegacybehavior#c,\mplibtextextlabel#c,\mplibcodeinherit#c,\mplibglobaltextext#c,\mplibverbatim#c,\mplibshowlog#c
enable
disable
#endkeyvals

#keyvals:\mplibnumbersystem#c
scaled
double
decimal
#endkeyvals

#keyvals:\begin{mppattern}
xstep=%<number%>
ystep=%<number%>
xshift=%<number%>
yshift=%<number%>
bbox="%<llx lly urx ury%>"
matrix="%<xx xy yx yy%>"
resources=%<PDF resources%>
colored#true,false
#endkeyvals

#keyvals:\mplibsetformat#c
plain
metafun
#endkeyvals

#keyvals:\begin{mplibgroup}
asgroup=%<string%>
bbox="%<llx lly urx ury%>"
matrix="%<xx xy yx yy%>"
resources=%<PDF resources%>
#endkeyvals

# not documented
\domplibcolor{color}{arg}#S
\ltxdomplibcodeindeed{arg}#S
\ltxdomplibcode{arg}#S
\luamplibateveryshipout{arg}#S
\luamplibatfirstshipout{arg}#S
\luamplibatnextshipout{arg}#S
\luamplibnotagtextboxset{arg1}{arg2}#S
\luamplibtagasgroupput#S
\luamplibtagasgroupset#S
\luamplibtagtextboxset{arg1}{arg2}#S
\mplibactualtext{arg}#S
\mplibalttext{arg}#S
\mplibdocancelnocache{arg}#S
\mplibdocode{arg}#S
\mplibdoeveryendmplib[instance name]{MetaPost code}#S
\mplibdoeveryendmplib{MetaPost code}#S
\mplibdoeverymplib{MetaPost code}#S
\mplibdomainmpfig#S
\mplibdomakenocache{arg}#S
\mplibdoprempfig#S
\mplibgobbleoptsmpfig[arg]#S
\mplibgroupbranch#S
\mplibgroupgetnexttok#S
\mplibgroupmain#S
\mplibgroupopts#S
\mplibgroupskipspace#S
\mplibmainmpfig#S
\mplibmpfigbranch#S
\mplibpatternbranch#S
\mplibpatterngetnexttok#S
\mplibpatternmain#S
\mplibpatternname#S
\mplibpatternopts#S
\mplibpatternskipspace#S
\mplibprempfig{arg}#S
\mplibputtextbox{arg}#S
\mplibscratchbox#S
\mplibsetupcatcodes#S
\mplibstarttoPDF{llx}{lly}{urx}{ury}#S
\mplibstoptoPDF#S
\mplibtextext{font}{size}{text}{hskip}{raise}#S
\mplibtmptoks{arg}#S
\mplibtoPDF{pdfliteral}#S
\usemplibgroupmain{arg}#S
