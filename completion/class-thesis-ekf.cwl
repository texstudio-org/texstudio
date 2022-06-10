# thesis-ekf class
# Matthew Bertucci 2022/06/07 for v4.2

#include:kvoptions
#include:class-report
#include:iftex
#include:cmap
#include:setspace
#include:hyperref
#include:geometry
#include:lmodern
#include:fixcmex
#include:etoolbox
#include:graphicx
#include:upquote

#keyvals:\documentclass/thesis-ekf#c
twoside
colorlinks
times#true,false
upint#true,false
logodown#true,false
tocnopagenum#true,false
reverseorder#true,false
centeredchapter#true,false
warning#true,false
10pt
11pt
12pt
fontsize=##L
institutesep=##L
logosep=##L
titlesep=##L
authorsep=##L
hminsep=##L
authorxmargin=##L
captionsep=##L
collcaptionsep=##L
authoralign=#left,center,right
supervisoralign=#left,center,right
institutefont=%<font commands%>
logofont=%<font commands%>
titlefont=%<font commands%>
authorfont=%<font commands%>
captionfont=%<font commands%>
cityfont=%<font commands%>
datefont=%<font commands%>
datesep=%<separator%>
#endkeyvals

#ifOption:colorlinks
#include:color
#endif

#ifOption:upint
#include:cmupint
#endif
#ifOption:upint=true
#include:cmupint
#endif

#ifOption:times
#include:newtxtext
#include:newtxmath
#endif
#ifOption:times=true
#include:newtxtext
#include:newtxmath
#endif

\authorcaption{text}
\city{city}
\collaborator
\collaborator[text]
\institute{institute%text}
\logo{kép vagy szöveg}
\supervisor{name}
\supervisorcaption{text}