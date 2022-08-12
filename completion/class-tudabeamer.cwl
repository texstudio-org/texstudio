# tudabeamer class
# Matthew Bertucci 2022/08/12 for v3.27

#include:l3keys2e
#include:URspecialopts
#include:class-beamer
#include:beamerthemeTUDa

#keyvals:\documentclass/tudabeamer#c
accentcolor=#%color
colorframetitle#true,false
logo#true,false
pdfa#true,false
logofile=%<imagefile%>
serif#true,false
sans-serif#true,false
department=mecheng
departmentlogofile=%<imagefile%>
# options passed to beamer class
usepdftitle#true,false
envcountsect
notheorems
noamsthm
compress
t
c
leqno
fleqn
handout
trans
pdftex
nativepdf
pdfmark
dvips
dviwindo
dvipsone
vtex
ps2pdf
ignorenonframetext
noamssymb
bigger
smaller
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
draft
CJK
cjk
onlytextwidth
pgf={%<pgf options%>}
hyperref={%<hyperref options%>}
color={%<color options%>}
xcolor={%<xcolor options%>}
ucs
utf8x
utf8
aspectratio=#2013,1610,169,149,141,54,43,32,%<xxxx%>
#endkeyvals

#ifOption:pdfa
#include:scrlfile
#include:pdfx
#endif
#ifOption:pdfa=true
#include:scrlfile
#include:pdfx
#endif

#ifOption:department=mecheng
TUDa-Primary1#B
TUDa-Primary2#B
TUDa-Secondary1#B
TUDa-Secondary2#B
TUDa-Secondary3#B
TUDa-Secondary4#B
TUDa-Secondary5#B
TUDa-Secondary6#B
TUDa-Arrow#B
#endif

#ifOption:ucs
#include:ucs
#endif

#ifOption:utf8x
#include:inputenc
# inputenc loaded with utf8x option, which loads ucs
#include:ucs
#endif

#ifOption:utf8
#include:inputenc
#endif

\department{department%text}
\insertdepartment#*
\insertshortdepartment#*
\insertshortdepartment[options]#*
\Metadata{keyvals}