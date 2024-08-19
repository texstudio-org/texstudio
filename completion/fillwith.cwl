# fillwith package
# Matthew Bertucci 2024/08/13 for v0.3

#include:svn-prov
#include:xcolor

\fillwith
\fillwith[options%keyvals]
\fillwith*
\fillwith*[options%keyvals]
\fillwithrules
\fillwithrules[options%keyvals]
\fillwithrules*
\fillwithrules*[options%keyvals]
\fillwithdottedlines
\fillwithdottedlines[options%keyvals]
\fillwithdottedlines*
\fillwithdottedlines*[options%keyvals]
\fillwithnolines
\fillwithnolines[options%keyvals]
\fillwithnolines*
\fillwithnolines*[options%keyvals]
\fillwithset{options%keyvals}

#keyvals:\fillwith#c,\fillwith*#c,\fillwithrules#c,\fillwithrules*#c,\fillwithdottedlines#c,\fillwithdottedlines*#c,\fillwithnolines#c,\fillwithnolines*#c,\usepackage/fillwith#c,\fillwithset#c
color=#%color
dottedcolor=#%color
#endkeyvals

#keyvals:\fillwith#c,\fillwith*#c,\fillwithrules#c,\fillwithrules*#c,\fillwithdottedlines#c,\fillwithdottedlines*#c,\fillwithnolines#c,\fillwithnolines*#c,\fillwithset#c
cont#true,false
fillwith ht=%<number%>
goal ht=##L
no font=%<font commands%>
#endkeyvals

#keyvals:\fillwith#c,\fillwith*#c,\fillwithset#c
style=#rule,dots,line,lines,rules
#endkeyvals