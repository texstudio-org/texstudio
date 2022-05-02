# bxpapersize package
# Matthew Bertucci 2022/04/30 for v2.6

#include:xkeyval
#include:atbegshi
#include:ifpdf
#include:ifxetex
#include:ifluatex
#include:ifvtex
#include:ifptex

#keyvals:\usepackage/bxpapersize#c
disabled
nodvidriver
autodvidriver
olddvips
#endkeyvals

\papersizesetup{options%keyvals}
\bxpapersizesetup{options%keyvals}#*

#keyvals:\papersizesetup#c,\bxpapersizesetup#c,\usepackage/bxpapersize#c
active#true,false
priority=#low,middle,default,high
truedimen
landscape
size=#real,real*,box,box*,a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,legalpaper,executivepaper,screen,%<width*height%>
#endkeyvals

\bxDebug{text}#S