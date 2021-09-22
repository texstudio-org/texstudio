# spbmark package
# Matthew Bertucci 9/21/2021 for v1.1c

\super{content}
\super[vshift%l][height,depth](code){content}[hshift%l]
\super*{content}
\super*[vshift%l][height,depth](code){content}[hshift%l]
\sp{content}#*
\sp[vshift%l][height,depth](code){content}[hshift%l]#*
\sp*{content}#*
\sp*[vshift%l][height,depth](code){content}[hshift%l]#*
\sub{content}
\sub[vshift%l][height,depth](code){content}[hshift%l]
\sub*{content}
\sub*[vshift%l][height,depth](code){content}[hshift%l]
\sb{content}#*
\sb[vshift%l][height,depth](code){content}[hshift%l]#*
\sb*{content}#*
\sb*[vshift%l][height,depth](code){content}[hshift%l]#*
\supersub{sup}{sub}
\supersub[vsep%l](align){sup}{sub}[hshift%l](sup code,sub code)
\supersub*{sup}{sub}
\supersub*[vsep%l](align){sup}{sub}[hshift%l](sup code,sub code)
\spb{sup}{sub}#*
\spb[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)#*
\spb*{sup}{sub}#*
\spb*[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)#*

\spb@textsuperscript@save{content}#*
\spb@textsubscript@save{content}#*
\spb@sp@save{content}#*
\spb@sb@save{content}#*

\spbset{options%keyvals}

#keyvals:\spbset
super-vshift=##L
super-hshift=##L
sub-vshift=##L
sub-hshift=##L
super-format=%<{code}%>
sub-format=%<{code}%>
supersub-hshift=##L
supersub-format=%<{super code,sub code}%>
supersubsep=##L
supersubalign=#l,c,r
#endkeyvals
