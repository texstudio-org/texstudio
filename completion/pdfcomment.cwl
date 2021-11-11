# pdfcomment package
# Matthew Bertucci 11/8/2021 for v2.4a

#include:xkeyval
#include:etoolbox
#include:luatex85
#include:datetime2
#include:zref-savepos
#include:refcount
#include:ifthen
#include:calc
#include:marginnote
#include:ifpdf
#include:ifluatex
#include:soulpos
#include:hyperref

\begin{pdfsidelinecomment}
\begin{pdfsidelinecomment}[options%keyvals]
\end{pdfsidelinecomment}

#keyvals:\begin{pdfsidelinecomment}
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
color=%<color%>
icolor=%<color%>
opacity=
linewidth=##L
linebegin={%<arrow type%>}
lineend={%<arrow type%>}
linesep=##L
borderstyle=#solid,dashed
dashstyle={%<thickness%> %<space%>}
caption=#none,inline,top
captionhoffset=##L
captionvoffset=##L
disable#true,false
date=%<date%>
timezone=%<timezone%>
#endkeyvals

\pdfcomment{comment%text}
\pdfcomment[options%keyvals]{comment%text}

\pdfmargincomment{comment%text}
\pdfmargincomment[options%keyvals]{comment%text}

\textHT{text}#*
\textLF{text}#*
\textCR{text}#*

#keyvals:\pdfcomment,\pdfmargincomment
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
icon=#Comment,Key,Note,Help,NewParagraph,Paragraph,Insert,Check,Circle,Cross,Star,RightArrow,RightPointer,UpArrow,UpLeftArrow,CrossHairs
color=%<color%>
opacity=
open#true,false
hspace=##L
voffset=##L
hoffset=##L
disable#true,false
date=%<date%>
timezone=%<timezone%>
id=
deadline=%<deadline%>
#endkeyvals

\pdfmarkupcomment{markup text%text}{comment%text}
\pdfmarkupcomment[options%keyvals]{markup text%text}{comment%text}

#keyvals:\pdfmarkupcomment
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
color=%<color%>
opacity=
markup=#Highlight,Underline,Squiggly,StrikeOut
mathstyle=
disable#true,false
date=%<date%>
timezone=%<timezone%>
id=
open#true,false
#endkeyvals

\pdffreetextcomment{comment%text}
\pdffreetextcomment[options%keyvals]{comment%text}

#keyvals:\pdffreetextcomment
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
color=%<color%>
font=%<font name%>
fontsize=##L
fontcolor=%<color%>
opacity=
line={%<coordinates%>}
linewidth=##L
lineend={%<arrow type%>}
borderstyle=#solid,dashed
dashstyle={%<thickness%> %<space%>}
bse=#none,cloudy
bsei=%<number%>
type=#freetext,callout,typewriter
height=##L
width=##L
voffset=##L
hoffset=##L
disable#true,false
date=%<date%>
timezone=%<timezone%>
justification=#left,right
#endkeyvals

\pdfsquarecomment{comment%text}
\pdfsquarecomment[options%keyvals]{comment%text}

\pdfcirclecomment{comment%text}
\pdfcirclecomment[options%keyvals]{comment%text}

#keyvals:\pdfsquarecomment,\pdfcirclecomment
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
color=%<color%>
icolor=%<color%>
opacity=
linewidth=##L
borderstyle=#solid,dashed
dashstyle={%<thickness%> %<space%>}
bse=#none,cloudy
bsei=%<number%>
height=##L
width=##L
voffset=##L
hoffset=##L
disable#true,false
date=%<date%>
timezone=%<timezone%>
justification=#left,right
#endkeyvals

\pdflinecomment{comment%text}
\pdflinecomment[options%keyvals]{comment%text}

#keyvals:\pdflinecomment
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
type=#line,polyline,polygon
color=%<color%>
icolor=%<color%>
opacity=
caption=#none,inline,top
captionhoffset=##L
captionvoffset=##L
linewidth=##L
linebegin={%<arrow type%>}
lineend={%<arrow type%>}
line={%<coordinates%>}
bse=#none,cloudy
bsei=%<number%>
borderstyle=#solid,dashed
dashstyle={%<thickness%> %<space%>}
disable#true,false
date=%<date%>
timezone=%<timezone%>
#endkeyvals

\pdftooltip{object}{comment%text}
\pdftooltip[options%keyvals]{object}{comment%text}

#keyvals:\pdftooltip
disable#true,false
mathstyle=
#endkeyvals

\pdfcommentsetup{options%keyvals}

#keyvals:\pdfcommentsetup
local={%<local options%>}
final
draft
dvipdfmx
version=%<number%>
avatar=%<avatar%>
#endkeyvals

\listofpdfcomments
\listofpdfcomments[options%keyvals]

#keyvals:\listofpdfcomments
liststyle=#AuthorSubject,AuthorSubjectDeadline,SubjectAuthorComment,SubjectAuthorCommentDeadline,AuthorComment,AuthorCommentDeadline,SubjectComment,SubjectCommentDeadline,Comment,CommentDeadline
heading={%<heading%>}
#endkeyvals

\setliststyle{name}
\defineliststyle{name}{definition}
\defineavatar{name}{options%keyvals}
\definestyle{name}{options%keyvals}

#keyvals:\defineavatar,\definestyle,\pdfcommentsetup
avatar=%<avatar%>
style=%<style%>
subject=%<subject%>
author=%<author%>
color=%<color%>
icolor=%<color%>
opacity=
linewidth=##L
linebegin={%<arrow type%>}
lineend={%<arrow type%>}
linesep=##L
borderstyle=#solid,dashed
dashstyle={%<thickness%> %<space%>}
caption=#none,inline,top
captionhoffset=##L
captionvoffset=##L
disable#true,false
date=%<date%>
timezone=%<timezone%>
deadline=%<deadline%>
open#true,false
hspace=##L
type=
font=%<font name%>
fontsize=##L
fontcolor=%<color%>
line={%<coordinates%>}
bse=#none,cloudy
bsei=%<number%>
voffset=##L
hoffset=##L
width
height
markup=#Highlight,Underline,Squiggly,StrikeOut
mathstyle=
printSOfinal#true,false
icon=#Comment,Key,Note,Help,NewParagraph,Paragraph,Insert,Check,Circle,Cross,Star,RightArrow,RightPointer,UpArrow,UpLeftArrow,CrossHairs
#endkeyvals