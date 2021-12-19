# spbmark package
# Matthew Bertucci 12/18/2021 for v1.2B

#include:xparse
#include:l3keys2e

#keyvals:\usepackage/spbmark#c
text#true,false
math#true,false
foot#true,false
both
all
#endkeyvals

\super{content}
\super[keyvals]{content}
\super[keyvals][height,depth]{content}#*
\super{content}[keyvals%plain]#*
\sub{content}
\sub[keyvals]{content}
\sub[keyvals][height,depth]{content}#*
\sub{content}[keyvals%plain]#*
\supersub{super}{sub}
\supersub[keyvals]{super}{sub}
\supersub[keyvals][height,depth]{super}{sub}#*
\supersub{super}{sub}[keyvals%plain]#*
\spb{super}{sub}#*
\spb[keyvals]{super}{sub}#*
\spb[keyvals][height,depth]{super}{sub}#*
\spb{super}{sub}[keyvals%plain]#*

#ifOption:math
\sp{content}
\sp[keyvals]{content}
\sp[keyvals][height,depth]{content}#*
\sp{content}[keyvals%plain]#*
\sb{content}
\sb[keyvals]{content}
\sb[keyvals][height,depth]{content}#*
\sb{content}[keyvals%plain]#*
#endif
#ifOption:math=true
\sp{content}
\sp[keyvals]{content}
\sp[keyvals][height,depth]{content}#*
\sp{content}[keyvals%plain]#*
\sb{content}
\sb[keyvals]{content}
\sb[keyvals][height,depth]{content}#*
\sb{content}[keyvals%plain]#*
#endif

#ifOption:text
\textsuperscript{content}
\textsuperscript[keyvals]{content}
\textsuperscript[keyvals][height,depth]{content}#*
\textsuperscript{content}[keyvals%plain]#*
\textsubscript{content}
\textsubscript[keyvals]{content}
\textsubscript[keyvals][height,depth]{content}#*
\textsubscript{content}[keyvals%plain]#*
#endif
#ifOption:text=true
\textsuperscript{content}
\textsuperscript[keyvals]{content}
\textsuperscript[keyvals][height,depth]{content}#*
\textsuperscript{content}[keyvals%plain]#*
\textsubscript{content}
\textsubscript[keyvals]{content}
\textsubscript[keyvals][height,depth]{content}#*
\textsubscript{content}[keyvals%plain]#*
#endif

#ifOption:both
\sp{content}
\sp[keyvals]{content}
\sp[keyvals][height,depth]{content}#*
\sp{content}[keyvals%plain]#*
\sb{content}
\sb[keyvals]{content}
\sb[keyvals][height,depth]{content}#*
\sb{content}[keyvals%plain]#*
\textsuperscript{content}
\textsuperscript[keyvals]{content}
\textsuperscript[keyvals][height,depth]{content}#*
\textsuperscript{content}[keyvals%plain]#*
\textsubscript{content}
\textsubscript[keyvals]{content}
\textsubscript[keyvals][height,depth]{content}#*
\textsubscript{content}[keyvals%plain]#*
#endif

#ifOption:all
\sp{content}
\sp[keyvals]{content}
\sp[keyvals][height,depth]{content}#*
\sp{content}[keyvals%plain]#*
\sb{content}
\sb[keyvals]{content}
\sb[keyvals][height,depth]{content}#*
\sb{content}[keyvals%plain]#*
\textsuperscript{content}
\textsuperscript[keyvals]{content}
\textsuperscript[keyvals][height,depth]{content}#*
\textsuperscript{content}[keyvals%plain]#*
\textsubscript{content}
\textsubscript[keyvals]{content}
\textsubscript[keyvals][height,depth]{content}#*
\textsubscript{content}[keyvals%plain]#*
#endif

\spbset{options%keyvals}

#keyvals:\spbset,\super,\sub,\supersub,\sp,\sb,\textsuperscript,\textsubscript
vshift=##L
hshift=##L
cmd={%<format cmds%>}
mode=#text,math,match
#endkeyvals

#keyvals:\spbset
spvshift=##L
sphshift=##L
sbvshift=##L
sbhshift=##L
nohshift
novshift
spcmd={%<format cmds%>}
sbcmd={%<format cmds%>}
spbhshift=##L
spbcmd={%<super cmds,sub cmds%>}
#endkeyvals

#keyvals:\spbset,\supersub,\spb
vsep=##L
halign=#l,c,r
#endkeyvals
