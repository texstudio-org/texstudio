# multidef package
# Matthew Bertucci 11/18/2021 for v1.10

#include:trimspaces
#include:xkeyval

\multidef{definition}{csname list}#d
\multidef[options%keyvals]{definition}{csname list}#d

#keyvals:\multidef
arg=%<num of args%>
noerr
nowarn
prefix=%<prefix%>
p=%<prefix%>
suffix=%<suffix%>
s=%<suffix%>
long#true,false
global#true,false
robust#true,false
#endkeyvals