# unicodefonttable package
# Matthew Bertucci 10/23/2021 for v1.0e

#include:xcolor
#include:xparse
#include:l3keys2e
#include:longtable
#include:booktabs
#include:caption
#include:fontspec

\displayfonttable{font name}{font features}
\displayfonttable[options%keyvals]{font name}{font features}
\displayfonttable*{font name}{font features}
\displayfonttable*[options%keyvals]{font name}{font features}

\fonttablesetup{options%keyvals}

#keyvals:\displayfonttable,\displayfonttable*,\fonttablesetup
header#true,false
noheader#true,false
title-format=
title-format-cont=
display-block=#titles,rules,none
hex-digits=#block,foot,head,head+foot,none
hex-digits-font=
color=#%color
statistics#true,false
nostatistics#true,false
statistics-font=
statistics-format=
glyph-width=##L
missing-glyph=
missing-glyph-font=
missing-glyph-color=#%color
compare-with=%<font name%>
compare-color=#%color
compare-bgcolor=#%color
statistics-compare-format=
range-start=%<slot%>
range-end=%<slot%>
#endkeyvals

\fonttableglyphcount

\unicodefonttabledate#S
\unicodefonttableversion#S