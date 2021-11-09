# ghsystem package
# Matthew Bertucci 11/7/2021 for v4.8c

#include:chemmacros
#include:translations
#include:siunitx
#include:graphicx
#include:longtable
#include:ifpdf

\ghssetup{options%keyvals}

\ghs{type}{number}
\ghs[options%keyvals]{type}{number}
\ghs*{type}{number}
\ghs*[options%keyvals]{type}{number}

#keyvals:\ghssetup,\ghs,\ghs*,\ghslistall
hide#true,false
space=%<space cmd%>
fill-in#true,false
exposure={%<text%>}
effect={%<text%>}
organs={%<text%>}
substance={%<text%>}
text={%<text%>}
dots={%<text%>}
C-temperature={%<num%>}
F-temperature={%<num%>}
kg-mass={%<num%>}
lbs-mass={%<num%>}
#endkeyvals

\ghspic{name}
\ghspic[options%keyvals]{name}

#keyvals:\ghssetup,\ghspic
scale=%<factor%>
includegraphics={%<includegraphics keyval%>}
pic-type=#eps,pdf,jpg,png
#endkeyvals

#keyvals:\ghssetup
language=
#endkeyvals

\ghslistall
\ghslistall[options%keyvals]

#keyvals:\ghssetup,\ghslistall
table-head-number={%<text%>}
table-head-text={%<text%>}
table-next-page={%<text%>}
table-caption={%<text%>}
table-caption-short={%<text%>}
table-label={%<text%>}
table-row-sep=##L
table-rules=#default,booktabs,none
table-top-head-rule=#default,booktabs,none
table-head-rule=#default,booktabs,none
table-foot-rule=#default,booktabs,none
table-last-foot-rule=#default,booktabs,none
#endkeyvals

\GHSfahrenheit#*
\GHScelsius#*
\GHSkilogram#*
\GHSpounds#*