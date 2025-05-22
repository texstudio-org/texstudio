# ddphonism package
# Matthew Bertucci 2025/05/13 for v0.3

#include:tikz
#include:tikzlibrarymatrix

\dmatrix{number list}
\dmatrix[options%keyvals]{number list}

#keyvals:\dmatrix
sep=%<number%>
vsep=%<number%>
hsep=%<number%>
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
name=%<text%>
up=%<integer%>
arrow shift=%<number%>
no numbers
no arrow
xshift=%<number%>
yshift=%<number%>
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
