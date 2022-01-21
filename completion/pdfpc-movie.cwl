# pdfpc-movie package
# Matthew Bertucci 1/20/2022 for v1.0

#include:etoolbox
#include:hyperref
#include:pgfkeys

\pdfpcmovie{poster material}{file}#i
\pdfpcmovie[options%keyvals]{poster material}{file}#i

#keyvals:\pdfpcmovie
width=##L
height=##L
depth=##L
autostart
loop
noprogress
start=%<integer%>
stop=%<integer%>
#endkeyvals