# snaptodo package
# Matthew Bertucci 11/27/2021

#include:tikzpagenodes

\snaptodo{text%todo}#D
\snaptodo[options%keyvals]{text%todo}#D

\snaptodoset{options%keyvals}

#keyvals:\snaptodo,\snaptodoset
call chain/.style={%<TikZ styles%>}
margin block/.style={%<TikZ styles%>}
block sep=##L
chain sep=##L
chain bias=##L
block rise=##L
#endkeyvals