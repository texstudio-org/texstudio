# buctcover class
# Matthew Bertucci 2022/07/14 for release 2022/06/21

#include:ifxetex
#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:geometry
#include:xeCJKfntef
#include:array
#include:graphicx
#include:calc
#include:tikz
#include:xifthen
#include:hyperref
#include:textpos

#keyvals:\documentclass/buctcover#c
type=#bachelor,master,doctor
#endkeyvals

\coversetup{options%keyvals}

#keyvals:\coversetup
class={%<class%>}
studentid={%<id number%>}
titleA={%<text%>}
titleB={%<text%>}
major={%<专业%>}
author={%<中文名%>}
supervisor={%<导师姓名, 教授%>}
date={%<YYYY-MM-DD%>}
#endkeyvals

\makecover
\makecover[pdf file%file]

\xingkai#*
\zhkai#*
\xbsong#*
\dbsong#* 
