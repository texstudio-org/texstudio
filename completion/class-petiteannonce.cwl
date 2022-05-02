# petiteannonce class
# Matthew Bertucci 4/18/2022 for v1.001

#include:graphicx
#include:keyval

#keyvals:\documentclass/petiteannonce#c
10pt
11pt
12pt
margin=##L
#endkeyvals

\petiteannonce{phone number}{text}
\petiteannonce[options%keyvals]{phone number}{text}

#keyvals:\petiteannonce
cols=%<integer%>
count=%<integer%>
cutvspace=##L
skip=%<integer%>
telcolsep=##L
telrulewidth=##L
telvspace=##L
textvspace=##L
texthspace=##L
width=##L
#endkeyvals

\petiteannoncewidth{factor}
\petiteannonceaddtowidth{dimen%l}