# xpiano package
# Matthew Bertucci 9/13/2021 for v1.0

#include:expl3
#include:xparse
#include:xcolor

\keyboard{notes}
\keyboard[options%keyvals]{notes}
\keyboardsetup{options%keyvals}
\Keyboard%<[note1][note2]...%>

#keyvals:\keyboard,\keyboardsetup
color=#%color
single#true,false
ext#true,false
size=##L
height=
ratio=
numbers#true,false
font=
numbercolor=#%color
10=
11=
#endkeyvals

pianodefault#B