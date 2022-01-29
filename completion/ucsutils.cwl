# ucsutils package
# Matthew Bertucci 1/28/2022 for v2.2

#include:ucs
#include:keyval

#keyvals:\usepackage/ucsutils#c
UnicodeEmbedFont
univerb
unistring
#endkeyvals

#ifOption:univerb
\UnicodeEmbedFont{options%keyvals}
#keyvals:\UnicodeEmbedFont
encoding=%<encoding%>
start=%<position%>
fontstart=%<position%>
num=%<number%>
option=%<Unicode option%>
#endkeyvals
#endif

#ifOption:univerb
\univerb|%<text%>|
\univerb{verbatimSymbol}#S
#endif

#ifOption:unistring
\unistring{string%definition}
#endif