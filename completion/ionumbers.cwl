# ionumbers package
# Matthew Bertucci 10/7/2021 for v0.3.3

#include:keyval

\ionumbersstyle{options%keyvals}

#keyvals:\ionumbersstyle
comma=#ignore,decimal,thousands,default
point=#ignore,decimal,thousands,default
thousands=#none,point,comma,punctpoint,punctcomma,apostrophe,phantom,space,default
decimal=#none,point,comma,punctpoint,punctcomma,apostrophe,phantom,space,default
thousandths=#none,point,comma,punctpoint,punctcomma,apostrophe,phantom,space,default
exponent=#none,original,ite,itE,rme,rmE,timestento,cdottento,wedge,default
autothousands#true,false
autothousandths#true,false
grplenthousands=%<number%>
grplenthousandths=%<number%>
#endkeyvals

\ionumbersresetstyle

\newionumbersthousands{value}{definition}#*
\newionumbersdecimal{value}{definition}#*
\newionumbersthousandths{value}{definition}#*
\newionumbersexponent{value}{definition}#*
\renewionumbersthousands{value}{definition}#*
\renewionumbersdecimal{value}{definition}#*
\renewionumbersthousandths{value}{definition}#*
\renewionumbersexponent{value}{definition}#*

\ionumbers
\endionumbers
\ionumbersoff{content}