# nodetree package
# Matthew Bertucci 2/8/2022 for v2.2

#include:luatex
#include:kvoptions

\NodetreeSet{options%keyvals}
\nodetreeset{options%keyvals}#S

#keyvals:\usepackage/nodetree#c,\NodetreeSet,\nodetreeset
channel=%<output channel%>
callback={%<callbacks%>}
verbosity=%<integer%>
color=#colored,no
unit=#pt,pc,in,bp,cm,mm,dd,cc,sp,ex,em
decimalplaces=%<integer%>
#endkeyvals

\NodetreeSetOption[option%keyvals]{value}
\nodetreeoption[option%keyvals]{value}#S
\NodetreeResetOption{option%keyvals}

#keyvals:\NodetreeSetOption,\nodetreeoption,\NodetreeResetOption
channel
callback
verbosity
color
unit
decimalplaces
#endkeyvals

\NodetreeReset
\nodetreereset#S
\NodetreeRegisterCallback{callbacks}
\nodetreeregister{callbacks}#S
\NodetreeUnregisterCallback{callbacks}
\nodetreeunregister{callbacks}#S
