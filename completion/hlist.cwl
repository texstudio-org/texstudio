# hlist package
# muzimuzhi/3 Nov 2019, hlist v0.11

#include:simplekv

\begin{hlist}{num of colums}
\end{hlist}
\hitem
\hitem>
\hitem*
\hitem*>
\hitem(num)

\sethlist{keyvals}
\setdefaulthlist{keyvals}

#keyvals:\sethlist,\setdefaulthlist
pre skip=##L
post skip=##L
left margin=##L
col sep=##L
item offset=##L
label sep=##L
label width=##L
label align=#left,right,center
label=%<code%>
pre label=%<code%>
post label=%<code%>
item sep=##L
resume#true,false
autoindent#true,false
pre item=%<code%>
post item=%<code%>
show label#true,false
list parindent=##L
show frame#true,false
#endkeyvals
