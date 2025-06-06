# langsci-avm package
# Matthew Bertucci 2025/04/29 for v0.4.0

#include:array

#keyvals:\usepackage/langsci-avm#c
tikz
lfg
#endkeyvals

#ifOption:tikz
#include:tikz
#keyvals:\avm,\avmsetup,\avmdefinestyle
pic
picname=%<name%>
#endkeyvals
#endif

#ifOption:lfg
#include:etoolbox
#include:unicode-math
#endif

\avm{structure}
\avm[options%keyvals]{structure}

\lframe
\rframe

\tag{identifier}
\type{type}
\type*{type}
\id{id}{structure}
\punk{attribute}{type}
\+#S
\shuffle

\avmsetup{options%keyvals}

\avmdefinestyle{name}{settings%keyvals}
\avmdefinecommand{name}{settings%keyvals}
\avmdefinecommand{name}[label]{settings%keyvals}

\begin{scope}{options%keyvals}
\end{scope}

#keyvals:\avm,\avmsetup,\avmdefinestyle,\begin{scope}
framewidth=##L
framesep=##L
id align=%<token%>
id position=#south-west,south-east
style=%<name%>
align#true,false
stretch=%<factor%>
columnsep=##L
vectorsep=##L
delimfactor=%<factor%>
delimfall=##L
extraskip=##L
attributes=%<font settings%>
values=%<font settings%>
types=%<font settings%>
tags=%<format settings%>
switch=%<token%>
customise=%<settings%>
#endkeyvals
