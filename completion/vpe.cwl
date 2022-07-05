# vpe package
# Matthew Bertucci 2022/07/04 for v0.1

#include:keyval

#keyvals:\usepackage/vpe#c
debug
#endkeyvals

\vpesetup{options%keyvals}

#keyvals:\usepackage/vpe#c,\vpesetup#c
active
inactive
dupes
nodupes
linux
unix
win
dos
system=#linux,win
form
noform
acroform
noacroform
command=%<script%>
progname=%<program%>
application=%<application%>
parameters=%<parameters%>
width=%<integer%>
height=%<integer%>
depth=%<integer%>
color=%<r g b%>
border=%<r g b%>
flag=%<flag%>
attr=%<attr%>
everyhbox
noeveryhbox
#endkeyvals

#ifOption:form
#include:color
#include:pifont
#endif
#ifOption:form=true
#include:color
#include:pifont
#endif

\VPE#*
\vpeentry{arg1}{arg2}#*
\vpesystem{arg1}#*