# spbmark package
# Matthew Bertucci 8/6/2021

\super[vshift%l][height,depth%l](code){content}[hshift%l]
\super*[vshift%l][height,depth%l](code){content}[hshift%l]
\sp[vshift%l][height,depth%l](code){content}[hshift%l]#*
\sp*[vshift%l][height,depth%l](code){content}[hshift%l]#*
\sub[vshift%l][height,depth%l](code){content}[hshift%l]
\sub*[vshift%l][height,depth%l](code){content}[hshift%l]
\sb[vshift%l][height,depth%l](code){content}[hshift%l]#*
\sb*[vshift%l][height,depth%l](code){content}[hshift%l]#*
\supersub[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)
\supersub*[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)
\spb[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)#*
\spb*[vsep%l](align){sup content}{sub content}[hshift%l](sup code,sub code)#*

\spb@textsuperscript@save{content}#*
\spb@textsubscript@save{content}#*
\spb@sp@save{content}#*
\spb@sb@save{content}#*

\spbset{keyvals}

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