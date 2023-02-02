# luamplib package
# Matthew Bertucci 3/28/2022 for v2.23.0

#include:luatex

\begin{mplibcode}
\begin{mplibcode}[instance name]
\end{mplibcode}
\mplibcode#S
\mplibcode[instance name]#S
\endmplibcode#S
\mplibforcehmode
\mplibnoforcehmode
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

#keyvals:\mplibsetformat#c
plain
metafun
#endkeyvals

# not documented
\domplibcolor{color}{arg}#*
\ltxdomplibcode{arg}#*
\ltxdomplibcodeindeed{arg}#*
\mplibdocancelnocache{arg}#*
\mplibdocode{arg}#*
\mplibdoeveryendmplib[instance name]{MetaPost code}#*
\mplibdoeveryendmplib{MetaPost code}#*
\mplibdoeverymplib{MetaPost code}#*
\mplibdomakenocache{arg}#*
\mplibputtextbox{arg}#*
\mplibscratchbox#*
\mplibsetupcatcodes#*
\mplibstarttoPDF{llx}{lly}{urx}{ury}#*
\mplibstoptoPDF#*
\mplibtextext{font}{size}{text}{hskip}{raise}#*
\mplibtmptoks{arg}#*
\mplibtoPDF{pdfliteral}#*
