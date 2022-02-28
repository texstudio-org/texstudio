# pst-rputover package
# Matthew Bertucci 2/23/2022 for v1.0

#include:pstricks
#include:pst-node
#include:pst-xkey

\rputover(x0,y0)(x1,y1){stuff}
\rputover{angle}(x0,y0){stuff}
\rputover{angle}(x0,y0)(x1,y1){stuff}
\rputover[options%keyvals](x0,y0)(x1,y1){stuff}
\rputover[options%keyvals]{angle}(x0,y0){stuff}
\rputover[options%keyvals]{angle}(x0,y0)(x1,y1){stuff}

#keyvals:\rputover#c,\pclineover#c,\pcarrowC#c
autoangle#true,false
inverscl#true,false
boxpos=%<pos%>
fboxsep=##L
npos=%<number%>
#endkeyvals

\coverable{stuff}
\coverable[options%keyvals]{stuff}

#keyvals:\coverable#c
inverscl#true,false
#endkeyvals

\pclineover(x0,y0)(x1,y1){stuff}
\pclineover[options%keyvals](x0,y0)(x1,y1){stuff}

#keyvals:\pclineover#c,\pcarrowC#c
absnodesep=
angleadd=%<degrees%>
arrows=%<arrows%>
offset=##L
#endkeyvals

\pcarrowC(x0,y0)(x1,y1){stuff}
\pcarrowC[options%keyvals](x0,y0)(x1,y1){stuff}

#keyvals:\pcarrowC#c
addbars=%<bars%>
baroffset=##L
Cbarwidth=##L
tbarsize=##L
#endkeyvals

\PSTRPUTOVERLoaded#S