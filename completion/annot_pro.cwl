# annot_pro package
# Matthew Bertucci 2022/05/13 for v1.4

#include:xkeyval
#include:trig
#include:hyperref
#include:calc
#include:aeb_mlink
#include:taborder

#keyvals:\usepackage/annot_pro#c
preview
useA10Icons
!useA10Icons
richtext
scandoc
!scandoc
dblevel=%<number%>
#endkeyvals

#ifOption:richtext
#include:richtext
#endif
#ifOption:useTextBox
#include:richtext
#endif

\annotpro{content%text}
\annotpro[options%keyvals]{content%text}
\annotpro*{content%text}
\annotpro*[options%keyvals]{content%text}

\setAnnotOptions{options%keyvals}

#keyvals:\annotpro,\annotpro*,\setAnnotOptions
type=#text,stamp,fileattachment,textbox,highlight,underline,squiggly,strikeout
name=%<name%>
title={%<text%>}
subject={%<text%>}
color=#%color
readonly#true,false
hidden#true,false
opacity=%<factor%>
internalID=%<name%>
margin
margintext=%<text%>
margprior=%<\cmd%>
presets=
open#true,false
nohspace
novspace
nospace
width=##L
height=##L
rotate=%<degrees%>
scale=%<factor%>
widthTo=##L
heightTo=##L
customStamp=
ap=
file=%<file path%>
bgcolor=#%color
bcolor=#%color
borderstyle=#none,solid,dash1,dash2,dash3,dash4,dash5,dash6,cloud1,cloud2
borderwidth=#.5,1,2,3,4,6,8,10
crackat=%<number%>
hyph#true,false
crackinsat=%<LaTeX markup%>
copycontent#true,false
objdef=
taborder=
#endkeyvals

\margintextformat{format cmds}
\apmargintextformat#*

\begin{textboxpara}
\end{textboxpara}

\apContText#*
\currentAnnotName#*

# not documented
\apmargintext#*
\defaultStampHeight#*
\defaultStampWidth#*
\getargsiii{arg1}{arg2}{arg3}#*
\ifpreview#*
\ifuseAAXdim#*
\isrichtextkey{arg1}{arg2}{arg3}{arg4}{arg5}#*
\isstrikeout#*
\makeStamp{arg1}{arg2}{arg3}#*
\mldblevel#*
\mlignore#*
\previewfalse#*
\previewtrue#*
\pStamp{arg1}#*
\QuadPoints#*
\stampHeight{arg1}#*
\stampWidth{arg1}#*
\standardStampHeight#*
\standardStampWidth#*
\useAAXdimfalse#*
\useAAXdimtrue#*