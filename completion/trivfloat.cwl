# trivfloat package
# Matthew Bertucci 11/29/2021 for v1.4

#include:float

#keyvals:\usepackage/trivfloat#c
floatrow#true,false
#endkeyvals

#ifOption:floatrow
#include:floatrow
#endif
#ifOption:floatrow=true
#include:floatrow
#endif

\trivfloat{envname%envname}#N
