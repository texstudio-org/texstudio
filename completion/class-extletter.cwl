# extletter class
# Matthew Bertucci 1/18/2021 for v1.0

#include:exscale

#keyvals:\documentclass/extletter#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
twoside
oneside
draft
final
leqno
fleqn
#endkeyvals

\begin{letter}{name}
\end{letter}
\address{returnaddress}
\signature{yourname}
\opening{text}
\closing{text}
\cc{text}
\encl{text}
\name{text}
\ps{text}
\location{address}
\telephone{number}
\subject{text}

\ccname#*
\enclname#*
\fromaddress#*
\fromlocation#*
\fromname#*
\fromsig#*
\headtoname#*
\indentedwidth#*
\labelcount#*
\longindentation#*
\mlabel{return address}{to address}#*
\pagename#*
\returnaddress#*
\startbreaks#*
\startlabels#*
\stopbreaks#*
\stopletter#*
\telephonenum#*
\toaddress#*
\toname#*