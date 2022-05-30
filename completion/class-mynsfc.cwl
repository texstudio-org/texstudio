# mynsfc class
# Matthew Bertucci 2022/05/19 for v1.30

#include:kvoptions
#include:class-ctexart
#include:xeCJK
#include:geometry
#include:titlesec
#include:marvosym
#include:amsmath
#include:amssymb
#include:paralist
#include:graphicx
#include:caption
#include:subcaption
#include:xcolor
#include:calc
#include:hyperref
#include:biblatex
# loads style=ieee option of biblatex
#include:xpatch

#keyvals:\documentclass/mynsfc#c
subfig#true,false
boldtoc#true,false
tocfont=%<font name%>
toccolor=%<HTML color%>
#endkeyvals

#ifOption:subfig
#include:subfig
#endif
#ifOption:subfig=true
#include:subfig
#endif

\boldnames#*
\cemph{text}
\initauthors{arg}
\oldsection{title}#S
\tocformat#*

# from style=ieee option of biblatex
\mkpagegrouped{text}#*
\mkonepagegrouped{text}#*