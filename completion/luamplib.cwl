# luamplib package
# Matthew Bertucci 2024/06/11 for v2.32.0

#include:luatex

\begin{mplibcode}
\begin{mplibcode}[instance name]
\end{mplibcode}
\mplibcode#S
\mplibcode[instance name]#S
\endmplibcode#S
\mplibforcehmode
\mplibnoforcehmode
\mpfig
\mpfig*
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

# not documented
\domplibcolor{color}{arg}#S
\ltxdomplibcode{arg}#S
\ltxdomplibcodeindeed{arg}#S
\mplibdocancelnocache{arg}#S
\mplibdocode{arg}#S
\mplibdoeveryendmplib[instance name]{MetaPost code}#S
\mplibdoeveryendmplib{MetaPost code}#S
\mplibdoeverymplib{MetaPost code}#S
\mplibdomainmpfig#S
\mplibdomakenocache{arg}#S
\mplibdoprempfig#S
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
