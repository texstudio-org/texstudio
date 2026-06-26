# ctexbook class
# Matthew Bertucci 2026/06/25 for v2.6.0

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
fontset=#adobe,fandol,founder,hanyi,mac,macnew,macold,ubuntu,windows,none
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
experiment/font-size-system=#word,letterpress,%<自定义名称%>
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