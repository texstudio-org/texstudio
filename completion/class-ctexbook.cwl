# ctexbook class
# Matthew Bertucci 4/24/2022 for v2.5.8

# does not actually load ctex, but defines all the same commands
#include:ctex
#include:class-book

#keyvals:\documentclass/ctexbook#c
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
sub3section
sub4section
scheme=#chinese,plain
linespread=%<number%>
fontset=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
# options passed to book class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\partmark{code}#*
\CTEXnumberline{number}#*