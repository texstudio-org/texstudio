# zref-xr package
# Matthew Bertucci 11/10/2021 for v2.32

#include:zref-base
#include:keyval
#include:kvoptions

\zexternaldocument{file}
\zexternaldocument[prefix]{file}[url]
\zexternaldocument*{file}
\zexternaldocument*[prefix]{file}[url]

\zxrsetup{options%keyvals}

#keyvals:\zxrsetup
ext=%<extension%>
tozreflabel#true,false
urluse#true,false
verbose#true,false
#endkeyvals

#keyvals:\zref#c
url
urluse
externaldocument
anchor
theotype
title
#endkeyvals