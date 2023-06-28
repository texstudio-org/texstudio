# spbmark package
# Matthew Bertucci 3/7/2022 for v1.4

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

\llastwd
\clastwd
\rlastwd

\supersub{super}{sub}
\supersub[keyvals]{super}{sub}
\supersub[keyvals][height,depth]{super}{sub}#*
\supersub{super}{sub}[keyvals%plain]#*

\superwd
\subwd
\maxwd

\spb{super}{sub}#*
\spb[keyvals]{super}{sub}#*
\spb[keyvals][height,depth]{super}{sub}#*
\spb{super}{sub}[keyvals%plain]#*

\defspbstyle{style name}{keyvals}
\spbifmath{math code%formula}{text code}
\spbshortkv{short opt%specialDef}{keyval%keyvals}#s#%spbshortkv

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

#keyvals:\spbset,\super,\sub,\supersub,\sp,\sb,\textsuperscript,\textsubscript,\spbshortkv
vmove=##L
hmove=##L
cmd={%<format cmds%>}
cmd+={%<format cmds%>}
height=##L
depth=##L
style=%<style name%>
mode=#text,math,match
vsep={%<super move,sub move%>}
halign=#l,c,r
#endkeyvals

#keyvals:\spbset,\super,\sub,\supersub,\sp,\sb,\textsuperscript,\textsubscript
%spbshortkv
#endkeyvals

#keyvals:\spbset,\spbshortkv
spvmove=##L
sphmove=##L
sbvmove=##L
sbhmove=##L
nohmove
novmove
spcmd={%<format cmds%>}
spcmd+={%<format cmds%>}
sbcmd={%<format cmds%>}
sbcmd+={%<format cmds%>}
spheight=##L
spdepth=##L
sbheight=##L
sbdepth=##L
spbhmove=##L
spbcmd={%<super cmds,sub cmds%>}
spbcmd+={%<super cmds,sub cmds%>}
spbheight=##L
spbdepth=##L
#endkeyvals

\fnmarkfont#*
