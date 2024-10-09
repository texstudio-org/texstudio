# udiss class
# Matthew Bertucci 2024/10/02 for v0.1

#include:class-memoir
#include:expkv-def
#include:expkv-opt
#include:iftex
#include:babel
#include:iflang
#include:unicode-math
#include:graphicx
#include:xcolor
#include:csquotes
#include:hyperref
#include:hyperxmp

#ifOption:license=CC-BY-SA
#include:doclicense
#endif

#keyvals:\documentclass/udiss#c
title={%<text%>}
author={%<author%>}
pronouns={%<pronouns%>}
subtitle={%<text%>}
shorttitle={%<text%>}
stream={%<stream%>}
discipline={%<discipline%>}
degree={%<degree%>}
supervisor={%<supervisor%>}
university={%<university%>}
department={%<department%>}
logo=%<imagefile%>
logo*=%<code%>
language={%<babel language names%>}
ldfbabel={%<babel ldf language names%>}
nofontwarning#true,false
license=#all-rights-reserved,CC-BY-SA,GFDL
copyright-yrs=%<years%>
localcopyright=%<word%>
placeholders
lot#true,false
lof#true,false
declaration#true,false
declarationtxt=%<text%>
decllocal=%<word%>
blind#true,false
framed-title#true,false
print#true,false
norefcolors#true,false
udisslinkclr=#%color
udissurlclr=#%color
udissciteclr=#%color
oldstylenumoff#true,false
oldone#true,false
fulfilment=%<text%>
explicitext#true,false
ignorefsoff#true,false
rmfeatures={%<font features%>}
sffeatures={%<font features%>}
ttfeatures={%<font features%>}
mathfeatures={%<font features%>}
rmfntext=#ttf,otf
sffntext=#ttf,otf
ttfntext=#ttf,otf
mathfntext=#ttf,otf
logowidth=%<factor%>
logoheight=%<factor%>
#endkeyvals

\pronouns{pronouns%text}
\subtitle{text}
\shorttitle{text}
\stream{stream%text}
\discipline{discipline%text}
\degree{degree%text}
\supervisor{supervisor}
\university{university}
\department{department}
\logo{imagefile}#g
\logo*{code}
\dissertationstyle{style}