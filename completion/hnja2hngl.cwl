# hnja2hngl package
# ponte-vecchio 2023-01-17 for v1.2

#include:grruby

#keyvals:\usepackage/hnja2hngl#c
grruby=false
#endkeyvals

\readhanja{%<hanja%>}#n
\readhanja{%<hanja%>}[%<number%>]#n
\readhanjaword{%<hanja%>}#n
\rwhanja{%<hanja%>}#n
\AssignReading{%<hanja%>}{%<reading%>}#*
\rpSetReading{%<hanja=reading%>}#*
\grrwhanja{%<hanja%>}#n
\rwhanjachar{%<hanja%>}#n
\rpRead{%<options%>}#n
\rpRead{%<options%>}[%<hanja=reading%>]#n
\viewCodePoint{%<unicode char%>}
\viewCodePoint*{%<unicode char%>}
\showReadings{%<hanja%>}#n

#keyvals:\rpRead#c
comma
para
at
period
#endkeyvals

\hnjahnglpkgdate#S
\hnjahnglpkgversion#S
