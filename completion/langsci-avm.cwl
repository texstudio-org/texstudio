# langsci-avm package
# Matthew Bertucci 11/18/2021 for v0.2.1

#include:xparse
#include:array

\avm{structure}
\avm[options%keyvals]{structure}

\avmsetup{options%keyvals}

\avmdefinestyle{name}{settings%keyvals}
\avmdefinecommand{name}{settings%keyvals}
\avmdefinecommand{name}[label]{settings%keyvals}

#keyvals:\avm,\avmsetup,\avmdefinestyle
style=%<name%>
stretch=%<factor%>
columnsep=##L
delimfactor=%<factor%>
delimfall=##L
extraskip=##L
attributes=%<font settings%>
values=%<font settings%>
apptovalues=%<code%>
types=%<font settings%>
tags=%<format settings%>
switch=%<token%>
customise=%<settings%>
#endkeyvals

\tag{identifier}
\type{type}
\type*{type}
\punk{attribute}{type}
\shuffle
\+#S