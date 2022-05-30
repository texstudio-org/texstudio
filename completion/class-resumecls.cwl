# resumecls class
# Matthew Bertucci 2022/05/02 for v0.4.1

#include:class-ctexart
#include:xeCJK
#include:geometry
#include:hyperref
#include:tabularx
#include:color
#include:fancyhdr
#include:natbib

#keyvals:\documentclass/resumecls#c
color
# options passed to ctexart class
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
# options passed to article class
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
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\heading{text}
\entry{indent%l}{cols}{content%text}
\name{name}
\organization{organization%text}
\address{address%text}
\mobile{number}
\mail{email%URL}#U
\homepage{URL}#U
\leftfooter{text}
\rightfooter{text}
\ifrclscolor#*
\rclscolortrue#*
\rclscolorfalse#*
\rclsaddress#*
\rclshomepage#*
\rclsleftfooter#*
\rclsmail#*
\rclsmobile#*
\rclsname#*
\rclsorganization#*
\rclsrightfooter#*
heading#B