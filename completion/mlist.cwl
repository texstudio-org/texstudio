# mlist package
# Matthew Bertucci 1/8/2021 for v0.6a

#include:ifmtarg
#include:xkeyval

\newvect{macro%cmd}{text%plain}#d
\newvect{macro%cmd}{text%plain}[options%keyvals]#d
\newmatr{macro%cmd}{text%plain}#d
\newmatr{macro%cmd}{text%plain}[options%keyvals]#d
\newfunc{macro%cmd}{text%plain}#d
\newfunc{macro%cmd}{text%plain}[options%keyvals]#d
\newmset{macro%cmd}{text%plain}#d
\newmset{macro%cmd}{text%plain}[options%keyvals]#d

\setR#m
\setC#m
\setN#m
\setZ#m

\vect{text%plain}#m
\vect{text%plain}{indices}#m
\matr{text%plain}#m
\matr{text%plain}{entries}#m
\func{text%plain}#m
\func{text%plain}{arg}#m
\mset{text%plain}#m
\mset{text%plain}{dims}#m

\MID#m
\LAST#m

\newmlist{macro%cmd}#d
\newmlist{macro%cmd}[options%keyvals]#d
\renewmlist{macro%cmd}
\renewmlist{macro%cmd}[options%keyvals]

\mlistsetup{options%keyvals}

#keyvals:\newvect,\newmatr,\newfunc,\newmset,\newmlist,\renewmlist,\mlistsetup
headcmd=%<macro%>
elemcmd=%<macro%>
headhook=%<code%>
wrap={%<open%>}{%<close%>}
wrapone
wrapone={%<open%>}{%<close%>}
wrapcmd=%<macro%>
wraponecmd=%<macro%>
sep=%<code%>
sepsep=%<code%>
symbol=%<symbol%>
index={%<indeices%>}
elem={%<args%>}
dot=%<code%>
dots=%<code%>
#endkeyvals

\mlistsub{arg}{sub}#*
\mlistsup{arg}{sup}#*
\mlistelem{arg1}{arg2}#*
\mlisthead{arg}#*
\mlistnowrap{arg1}{arg2}#*
\mlistparen{arg1}{arg2}#*
\mlistbrack{arg1}{arg2}#*
\mlistbrace{arg1}{arg2}#*
\mlistangle{arg1}{arg2}#*
\mlistheadparen{arg1}{arg2}#*
\mlistheadbrack{arg1}{arg2}#*
\mlistheadbrace{arg1}{arg2}#*
\mlistheadangle{arg1}{arg2}#*
