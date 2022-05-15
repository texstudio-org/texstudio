# accsupp package
# Matthew Bertucci 2022/05/14 for v0.6

#include:pdfescape
#include:iftex
#include:kvoptions

#keyvals:\usepackage/accsupp#c
pdftex
luatex
dvips
dvipdfm
#endkeyvals

\BeginAccSupp{options%keyvals}
\AccSuppSetup{options%keyvals}

#keyvals:\BeginAccSupp,\AccSuppSetup
ActualText=%<text%>
Alt=%<text%>
E=%<text%>
Lang=%<language%>
method=#plain,escape,hex,pdfstringdef
unicode
space#true,false
spacefont=%<font name%>
spacechar=%<slot%>
#endkeyvals

\EndAccSupp{options%keyvals}

#keyvals:\BeginAccSupp,\AccSuppSetup,\EndAccSupp
pdfliteral=%<keyword%>
#endkeyvals

\ActualTextDriverDefault#*
