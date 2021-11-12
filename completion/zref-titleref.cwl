# zref-titleref package
# Matthew Bertucci 11/10/2021 for v2.32

#include:zref-base
#include:gettitlestring
#include:keyval

\ztitleref{label}#r

\ztitlerefsetup{options%keyvals}

#keyvals:\ztitlerefsetup
title=
stripperiod#true,false
expand#true,false
cleanup={%<code%>}
#endkeyvals

#keyvals:\zref#c
title
#endkeyvals