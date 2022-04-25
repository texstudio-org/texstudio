# ctexbeamer class
# Matthew Bertucci 4/24/2022 for v2.5.8

# does not actually load ctex, but defines all the same commands
#include:ctex
#include:class-beamer

#keyvals:\documentclass/ctexbeamer#c
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
scheme=#chinese,plain
linespread=%<number%>
fontset=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
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