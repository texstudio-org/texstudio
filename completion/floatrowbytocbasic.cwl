# floatrowbytocbasic package
# Matthew Bertucci 2023/08/16 for v1.0

#include:tocbasic
#include:floatrow
#include:xpatch

\DeclareFloatType{envname}{options%keyvals}#N
\ProvideFloatType{envname}{options%keyvals}#N
\RedeclareFloatType{envname}{options%keyvals}

#keyvals:\DeclareFloatType,\ProvideFloatType,\RedeclareFloatType
placement=%<combination of t,b,h,p%>
name=%<name%>
fileext=%<ext%>
within=%<counter%>
relatedcapstyle=#yes,no
#endkeyvals