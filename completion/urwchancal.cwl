# urwchancal package
# Matthew Bertucci 1/13/2022 for v1

#include:xkeyval

#keyvals:\usepackage/urwchancal#c
scaled=%<factor%>
mathscr#true,false
#endkeyvals

#ifOption:mathscr
\mathscr{text%plain}#m
#endif
#ifOption:mathscr=true
\mathscr{text%plain}#m
#endif
