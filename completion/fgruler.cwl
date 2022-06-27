# fgruler package
# Matthew Bertucci 2022/06/27 for v1.5

#include:kvoptions
#include:etoolbox
#include:xcolor
#include:graphicx
#include:eso-pic

\setfgruler{options%keyvals}
\fgruler*{type}
\fgruler*[options%keyvals]{type}

#keyvals:\usepackage/fgruler#c,\setfgruler,\fgruler*
unit=#cm,in
type=#upperleft,upperright,lowerleft,lowerright,upperleftT,upperrightT,lowerleftT,lowerrightT,alledges,alledges*,alledgesT,alledgesT*,none,user
hshift=##L
vshift=##L
color=#%color
numsep=##L
markthick=##L
numfont=%<font commands%>
showframe#true,false
nonefgrulers
#endkeyvals

\fgruler{type%keyvals}{hshift%l}{vshift%l}
\fgruler[unit]{type%keyvals}{hshift%l}{vshift%l}

#keyvals:\fgruler,\squareruler,\squareruler*
upperleft
upperright
lowerleft
lowerright
#endkeyvals

\ruler{type%keyvals}{length}
\ruler[unit]{type%keyvals}{length}
\ruler*{type%keyvals}{length}
\ruler*[unit]{type%keyvals}{length}

#keyvals:\ruler,\ruler*
downright
downleft
upright
upleft
rightdown
rightup
leftdown
leftup
taperight
tapeleft
#endkeyvals

\squareruler{type%keyvals}{width}{height}
\squareruler[unit]{type%keyvals}{width}{height}
\squareruler*{type%keyvals}{width}{height}
\squareruler*[unit]{type%keyvals}{width}{height}

\rulerparams{markthick%l}{numfont}{color}{marklength%l}{numsep%l}
\rulerparamsfromfg
\rulernorotatenum
\rulerrotatenum
\fgrulerstartnum{number}
\fgrulerstartnumh{number}
\fgrulerstartnumv{number}
\fgrulernoborderline
\fgrulerborderline
\fgrulercaptioncm{caption%text}
\fgrulercaptionin{caption%text}
\fgrulerdefnum{definition}
\fgrulerratiocm{ratio1}{ratio2}
\fgrulerratioin{ratio1}{ratio2}{ratio3}{ratio4}
\fgrulerthickcm{thick1%l}{thick2%l}{thick3%l}
\fgrulerthickin{thick1%l}{thick2%l}{thick3%l}{thick4%l}{thick5%l}
\fgrulercolorcm{color1}{color2}{color3}
\fgrulercolorin{color1}{color2}{color3}{color4}{color5}
\fgrulerreset
\fgrulerdefuser{code}
\fgrulerdefusercm{code}#*
\fgrulerdefuserin{code}#*
\fgrulertype{unit}{type}
\thefgrulernum
