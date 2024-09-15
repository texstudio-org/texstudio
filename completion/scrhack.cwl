# scrhack package
# Matthew Bertucci 2024/09/05 for v3.42

#include:scrlogo

#keyvals:\usepackage/scrhack#c
float#true,false
floatrow#true,false
lscape#true,false
setspace#true,false
standardsections#true,false
#endkeyvals

#ifOption:float
#include:floatbytocbasic
#endif
#ifOption:float=true
#include:floatbytocbasic
#endif

#ifOption:floatrow
#include:floatrowbytocbasic
#endif
#ifOption:floatrow=true
#include:floatrowbytocbasic
#endif

#ifOption:lscape
#include:lscapeenhanced
#endif
#ifOption:lscape=true
#include:lscapeenhanced
#endif

#ifOption:setspace
#include:setspaceenhanced
#endif
#ifOption:setspace=true
#include:setspaceenhanced
#endif

#ifOption:standardsections
#include:standardsectioning
#endif
#ifOption:standardsections=true
#include:standardsectioning
#endif
