# easybook class
# Matthew Bertucci 4/24/2022 for v1.66

#include:l3keys2e
#include:class-ctexbook
#include:easybase
#include:newtxmath
#include:bm

#keyvals:\documentclass/easybook#c
draft
newline
scheme=#chinese,plain
enmode
paper=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
config=%<配置文件列表%>
floatpage#true,false
theorem#true,false
cjkfont=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
font=#noto,times,times*,ebgaramond,libertine,palatino,auto
mathfont=#times,noto,notosans,nc,stix2,charter,ebgaramond,libertine,none
class=#book,article
book
article
# options passed to ctexbook class
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