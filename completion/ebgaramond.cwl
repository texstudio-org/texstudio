# ebgaramond package
# Matthew Bertucci 2022/09/16 for v2022/09/10

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:textcomp
#include:fontenc
#include:fontaxes
#include:mweights

#keyvals:\usepackage/ebgaramond#c
scaled=%<factor%>
type1
lining
nf
lf
oldstyle
osf
tabular
t
proportional
p
medium
m
semibold
sb
extrabold
eb
#endkeyvals

\ebgaramond
\oldstylenums{text}
\liningnums{text}
\tabularnums{text}
\proportionalnums{text}
\sufigures
\textsu{text}
\infigures
\textinf{text}
\swshape
\textsw{text}
\initials
\textin{letter%keyvals}
#keyvals:\textin
A
D
F
G
L
N
O
Q
T
X
#endkeyvals
\ebgaramondlgr#*
