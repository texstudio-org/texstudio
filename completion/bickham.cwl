# bickham package
# Matthew Bertucci 1/13/2022 for v1.1

#include:xkeyval

#keyvals:\usepackage/bickham#c
scaled=%<factor%>
scr
sb
#endkeyvals

#ifOption:scr
\mathscr{text%plain}#m
\mathbscr{text%plain}#m
#endif

\mathbcal{text%plain}#m