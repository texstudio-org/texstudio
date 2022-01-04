# zwpagelayout package
# Matthew Bertucci 1/4/2022 for v1.4d

#include:iftex
#include:kvoptions

#ifOption:color
#include:color
#endif
#ifOption:color=true
#include:color
#endif
#ifOption:redefineblack
#include:color
#endif
#ifOption:redefineblack=true
#include:color
#endif
#ifOption:redefinetocmyk
#include:color

#endif
#ifOption:redefinetocmyk=true
#include:color
#endif
#ifOption:overprint
#include:color
#endif
#ifOption:overprint=true
#include:color
#endif

#keyvals:\usepackage/zwpagelayout#c
driver=#unknown,pdftex,xetex,dvips,other,dvipdfm,xdvipdfmx
AllowWidthHeightSwitching
papersize={%<width,height%>}
a0
a1
a2
a3
a4
a5
a6
a7
a8
a9
a10
b0
b1
b2
b3
b4
b5
b6
b7
b8
b9
b10
c0
c1
c2
c3
c4
c5
c6
c7
c8
c9
c10
executive
legal
letter
Portrait
Landscape
noBboxes
margins=##L
topmargin=##L
botmargin=##L
leftmargin=##L
rightmargin=##L
textwidth=##L
textheight=##L
headheight=##L
headsep=##L
footskip=##L
topskip=##L
strictheight#true,false
adjustfootskip#true,false
adjustheadsep#true,false
ReflectHorizontally
ReflectVertically
onlycropmarks#true,false
cropmarks#true,false
nocropmarks#true,false
croplength=##L
cropgap=##L
cropframe#true,false
nocropframe#true,false
cropstyle=#default,leaflet
croptitle=%<text%>
cropseparator=%<macro%>
pagenumberfirst#true,false
pagenumberlast#true,false
usepagenumbers#true,false
nopagenumbers#true,false
nobleedclip#true,false
spine=##L
xspine=##L
flap=##L
trim=##L
xtrim=##L
ytrim=##L
leafcount=%<integer%>
foldcorr=##L
fold=#2,3left,3right,Z,4
color#true,false
colormodel=%<model%>
cropcolor=%<color spec%>
colors={{%<name1:spec1%>}%<,...%>}
overprint#true,false
redefineblack#true,false
redefinetocmyk#true,false
title=%<text%>
author=%<author%>
subject=%<subject%>
keywords=%<keywords%>
nopdfinfo
pdfminorversion=%<version%>
pdfx
OutputCondition=
OutputConditionIdentifier=
ICCfile=%<file name%>
#endkeyvals

\noBboxes

cmykblack#B
cmykread#B
cmykgreen#B
cmykblue#B

\OverprintXeTeXExtGState#*
\SetOverprint
\SetKnockout
\textoverprint{text}
\textknockout{text}

grblack#B
rgbred#B
rgbgreen#B
rgbblue#B

\SetPDFminorversion{version}

\Vcorr
\vb
\vb[number]

\NewOddPage
\NewOddPage[style]
\NewOddPage*
\NewOddPage*[style]
\SetOddPageMessage{text}
\NewEvenPage
\NewEvenPage[style]
\NewEvenPage*
\NewEvenPage*[style]
\SetEvenPageMessage{text}

\CropFlap
\CropSpine
\CropXSpine
\CropXtrim
\CropYtrim
\UserWidth
\UserLeftMargin
\UserRightMargin
\UserBotMargin
\UserTopMargin
\thePageNumber

\ifcaseZWdriver#*
\ZWifdriver{driver}{code}#*

# not documented
\ZWsetkeys{family}{keyvals}#*
\PDFbkslash#S
\SetTeXingDate{date}#S
\TimeOfTeXing#S
\ZWpercent#S