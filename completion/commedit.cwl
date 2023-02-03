# commedit package
# Matthew Bertucci 4/22/2022 for v1.02

#include:etoolbox
#include:everyshi
#include:graphicx

\begin{commeditPreamble}{filename%file}
\end{commeditPreamble}
\commentscolskip#*
\commentscolwidth#*
\commentscolTheight#*
\commentscolSheight#*
\basepageboxwidth#*
\basepageargs{includegraphics options%keyvals}
\commentsOddPageSetup{num leftcols}{num shortcols}{num rightcols}
\commentsEvenPageSetup{num leftcols}{num shortcols}{num rightcols}
\commentsContinuationPageSetup{num cols}
\commentsHook{code}
\commentsraggedbottom
\commentsflushbottom
\begin{commeditComments}
\end{commeditComments}
\begin{commeditText}
\end{commeditText}
\ifCommentedEdition#*
\CommentedEditiontrue#*
\CommentedEditionfalse#*
\begin{commentsBox}#*
\end{commentsBox}#*
\typesetComments{text}#*
\typesetContinuation#*

#keyvals:\basepageargs
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals
