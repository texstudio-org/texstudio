# accsupp package
# Matthew Bertucci 10/18/2021 for v0.6

#include:pdfescape
#include:iftex
#include:kvoptions

\BeginAccSupp{options%keyvals}
\AccSuppSetup{options%keyvals}

#keyvals:\BeginAccSupp,\AccSuppSetup
ActualText=%<text%>
Alt=
E=
Lang=%<language%>
method=#plain,escape,hex,pdfstringdef
unicode
space#true,false
spacefont=
spacechar=
#endkeyvals

\EndAccSupp{options%keyvals}

#keyvals:\BeginAccSupp,\AccSuppSetup,\EndAccSupp
pdfliteral=
#endkeyvals

\ActualTextDriverDefault#*