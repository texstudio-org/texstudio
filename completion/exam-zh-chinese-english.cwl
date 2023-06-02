# exam-zh-chinese-english package
# Matthew Bertucci 2023/06/02 for v0.1.25

#include:tcolorbox
#include:tcolorboxlibrarymost
#include:varwidth

#keyvals:\examsetup,\ExamPrintAnswerSet
select={%<键值列表%>}
select/mark-symbol=%<symbol%>
select/show-mark#true,false
select/mark-position=#top,above,below,bottom,left,right
select/mark-xshift=##L
select/mark-yshift=##L
select/separator=%<symbol%>
select/pre-content=%<content%>
select/post-content=%<content%>
lineto={%<键值列表%>}
lineto/xsep=##L
lineto/ysep=##L
lineto/name=%<name%>
material={%<键值列表%>}
material/title=%<标题%>
material/title-format=%<格式%>
material/author=%<作者%>
material/author-format=%<格式%>
material/title-author-sep=##L
material/format=%<格式%>
material/source=%<来源出处%>
material/source-format=%<格式%>
material/top-sep=##L
material/bottom-sep=##L
material/title-material-sep=##L
poem={%<键值列表%>}
poem/title=%<标题%>
poem/title-format=%<格式%>
poem/author=%<作者%>
poem/author-format=%<格式%>
poem/title-author-sep=##L
poem/format=%<格式%>
poem/align=#l,c,r
poem/top-sep=##L
poem/bottom-sep=##L
poem/title-poem-sep=##L
poem/type=#minipage,chinese
poem/zhu-circlednumber-base=#tikz,font
#endkeyvals

\begin{select}
\begin{select}[键值列表%keyvals]
\end{select}

#keyvals:\begin{select}
mark-symbol=%<symbol%>
show-mark#true,false
mark-position=#top,above,below,bottom,left,right
mark-xshift=##L
mark-yshift=##L
separator=%<symbol%>
pre-content=%<content%>
post-content=%<content%>
#endkeyvals

\begin{lineto}
\begin{lineto}[键值列表%keyvals]
\end{lineto}
\linelistset{list}
\linelistset[键值列表%keyvals]{list}
\lineconnect{list}
\lineconnect[TikZ keys]{list}

#keyvals:\begin{lineto},\linelistset
xsep=##L
ysep=##L
name=%<name%>
#endkeyvals

\begin{material}
\begin{material}[键值列表%keyvals]
\end{material}

#keyvals:\begin{material}
title=%<标题%>
title-format=%<格式%>
author=%<作者%>
author-format=%<格式%>
title-author-sep=##L
format=%<格式%>
source=%<来源出处%>
source-format=%<格式%>
top-sep=##L
bottom-sep=##L
title-material-sep=##L
#endkeyvals

\begin{poem}
\begin{poem}[键值列表%keyvals]
\end{poem}

#keyvals:\begin{poem}
title=%<标题%>
title-format=%<格式%>
author=%<作者%>
author-format=%<格式%>
title-author-sep=##L
format=%<格式%>
align=#l,c,r
top-sep=##L
bottom-sep=##L
title-poem-sep=##L
type=#minipage,chinese
zhu-circlednumber-base=#tikz,font
#endkeyvals

\zhu{注释%text}
\zhu[数]{注释%text}

\begin{writingbox}
\begin{writingbox}[tcolorbox keys]
\end{writingbox}
