# xdufont package
# Matthew Bertucci 2023/01/28 for v4.3.0.0

#include:expl3
#include:xparse
#include:l3keys2e
#include:xeCJK
#include:unicode-math

\xdusetup{options%keyvals}

#keyvals:\xdusetup#c
style={%<keyvals%>}
style/cjk-font=#adobe,fandol,founder,sinotype,win,none
style/cjk-fake-bold=%<伪粗体粗细程度%>
style/cjk-fake-slant=%<伪斜体倾斜程度%>
style/latin-font=#tac,tacn,thcs,gyre,none
style/latin-sans-scale=#upper,lower,off
style/latin-mono-scale=#upper,lower,off
style/math-font=#asana,cambria,cm,concrete,erewhon,euler,fira,garamond,gfsneohellenic,kp,libertinus,lm,newcm,stix2,stix,xcharter,xits,bonum,dejavu,pagella,schola,termes,none
style/unicode-math={%<unicode-math宏包选项%>}
style/font-type=#font,file
style/font-path={%<路径%>}
#endkeyvals
