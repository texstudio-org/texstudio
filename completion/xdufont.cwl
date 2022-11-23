# xdufont package
# Matthew Bertucci 2022/11/23 for v2.14.1.3

#include:expl3
#include:xparse
#include:l3keys2e
#include:xeCJK
#include:unicode-math

\xdusetup{options%keyvals}

#keyvals:\xdusetup#c
style={%<keyvals%>}
style/cjk-font=#win,adobe,founder,sinotype,fandol,none
style/cjk-fake-bold=%<伪粗体粗细程度%>
style/cjk-fake-slant=%<伪斜体倾斜程度%>
style/latin-font=#tac,tacn,thcs,gyre,none
style/math-font=#asana,cambria,cm,fira,garamond,lm,libertinus,stix,bonum,dejavu,pagella,schola,termes,xits,erewhon,none
style/unicode-math={%<unicode-math宏包选项%>}
style/font-type=#font,file
style/font-path={%<路径%>}
#endkeyvals
