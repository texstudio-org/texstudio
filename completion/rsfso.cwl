# rsfso package
# Matthew Bertucci 8/27/2021 for v1.02

#include:xkeyval

#keyvals:\usepackage/rsfso#c
scaled=%<factor%>
scr#true,false
#endkeyvals

#ifOption:scr
\mathscr{arg}#m
#endif
#ifOption:scr=true
\mathscr{arg}#m
#endif
