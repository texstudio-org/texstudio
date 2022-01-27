# embedall package
# Matthew Bertucci 11/10/2021 for v2.0

#include:embedfile
#include:filehook
#include:currfile
#include:etoolbox

#keyvals:\usepackage/embedall#c
all
notall
main
input
include
graphicx
csvsimple
compat
#endkeyvals

#ifOption:compat
#include:letltxmacro
#endif

\embedsource
\embedsource[options%keyvals]

\embedinput{file}#*
\embedinput[options%keyvals]{file}#*

#keyvals:\embedsource#c,\embedinput#c
filespec=
ucfilespec=
filesystem=
mimetype=
desc=%<description%>
afrelationship=%<PDF name%>
stringmethod=#psd,escape
id=
#endkeyvals
