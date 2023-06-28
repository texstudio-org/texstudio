# ddphonism package
# Matthew Bertucci 10/1/2021 for v0.2

#include:etoolbox
#include:pgfkeys
#include:tikz
#include:xstring

\dmatrix{number list}
\dmatrix[options%keyvals]{number list}

#keyvals:\dmatrix
sep=
vsep=
hsep=
lines
outside lines
inside lines
vlines
hlines
no tikz
#endkeyvals

\ddiagram{number list}
\ddiagram[options%keyvals]{number list}

#keyvals:\ddiagram
name=
up=
arrow shift=
no numbers
no arrow
xshift=
yshift=
no tikz
#endkeyvals

\ddihedral{number list}
\ddihedral[options%keyvals]{number list}

#keyvals:\ddihedral
t=
s=
c=
v=
no italics
new t=
new s=
new c=
new v=
no tikz
#endkeyvals

\darrows{number list}
\darrows[options%keyvals]{number list}

#keyvals:\darrows
no tikz
#endkeyvals

\drow{number list}
\drow[options%keyvals]{number list}

#keyvals:\drow
sep=##L
#endkeyvals