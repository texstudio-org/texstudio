# unicodefonttable package
# Matthew Bertucci 2022/11/13 for v1.0g

#include:xcolor
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
title-format=%<code%>
title-format-cont=%<code%>
display-block=#titles,rules,none
hex-digits=#block,foot,head,head+foot,none
hex-digits-font=%<font commands%>
hex-digits-row-format=%<code%>
color=#%color
statistics#true,false
nostatistics#true,false
statistics-font=%<font commands%>
statistics-format=%<code%>
glyph-width=##L
missing-glyph=%<code%>
missing-glyph-font=%<font commands%>
missing-glyph-color=#%color
compare-with=%<font name%>
compare-color=#%color
compare-bgcolor=#%color
statistics-compare-format=%<code%>
range-start=%<slot%>
range-end=%<slot%>
#endkeyvals

\fonttableglyphcount

\unicodefonttabledate#S
\unicodefonttableversion#S
