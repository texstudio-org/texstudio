# linenoamsmath package
# Matthew Bertucci 2/2/2022 for v1.2

#include:amsmath
#include:lineno
#include:etoolbox

# all options passed to lineno
#keyvals:\usepackage/linenoamsmath#c
addpageno
mathrefs
edtable
longtable
nolongtablepatch
left
right
switch
switch*
columnwise
pagewise
running
modulo
modulo*
mathlines
#endkeyvals

#ifOption:addpageno
#include:vplref
#endif

#ifOption:mathrefs
#include:ednmath0
#endif

#ifOption:edtable
#include:edtable
#endif

#ifOption:longtable
#include:edtable
#include:longtable
#include:ltabptch
#endif

#ifOption:nolongtablepatch
#include:edtable
#include:longtable
#endif