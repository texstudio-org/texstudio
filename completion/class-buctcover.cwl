# buctcover class
# Matthew Bertucci 2022/07/14 for release 2021/04/24

#include:ifxetex
#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:geometry
#include:array
#include:graphicx
#include:calc
#include:hyperref

#keyvals:\documentclass/buctcover#c
type=#master,doctor
#endkeyvals

\coversetup{options%keyvals}

#keyvals:\coversetup
studentid={%<id number%>}
titleA={%<text%>}
titleB={%<text%>}
major={%<专业%>}
author={%<中文名%>}
supervisor={%<导师姓名, 教授%>}
date={%<YYYY-MM-DD%>}
#endkeyvals

\makecover
\makecover[pdf file]

\xingkai#*
\zhkai#*
\xbsong#*
\dbsong#* 