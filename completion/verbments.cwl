# vcell package
# Matthew Bertucci 1/22/2022 for v1.0.2

#include:xkeyval
#include:fancyvrb
#include:framed
#include:xcolor
#include:calc

\begin{pyglist}#V
\begin{pyglist}[options%keyvals]#V
\end{pyglist}

\plset{options%keyvals}

\listofpyglistings
\listofpyglistingsname{name%text}

#keyvals:\begin{pyglist},\plset
abovecaptionskip=##L
belowcaptionskip=##L
bgcolor=#%color
caption={%<text%>}
captionbgcolor=#%color
captionfont=%<font commands%>
encoding=%<encoding%>
fontsize=
fvset={%<fancyvrb options%>}
gobble=%<integer%>
language=%<language%>
label=##l
listingname=%<name%>
listingnamefont=%<font commands%>
mathescape#true,false
numbers=#none,left,right
numbersep=##L
showspaces#true,false
style=%<Pygments style%>
texcl#true,false
#endkeyvals