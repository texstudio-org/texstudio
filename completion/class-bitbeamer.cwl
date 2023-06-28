# bitbeamer class
# Matthew Bertucci 2022/08/14 for v3.0.0

#include:l3keys2e
#include:class-ctexbeamer
#include:xeCJKfntef
#include:tikz

#keyvals:\documentclass/bitbeamer#c
titlegraphic=%<imagefile%>
framelogo=%<imagefile%>
# options passed to ctexbeamer class
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
onlytextwidth
pgf={%<pgf options%>}
hyperref={%<hyperref options%>}
color={%<color options%>}
xcolor={%<xcolor options%>}
aspectratio=#2013,1610,169,149,141,54,43,32,%<xxxx%>
#endkeyvals

\CJKhl{color}{text}