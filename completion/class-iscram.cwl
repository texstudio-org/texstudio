# iscram class
# Matthew Bertucci 4/19/2022 for v1.1.0

#include:etoolbox
#include:pgfopts
#include:geometry
#include:microtype
#include:newtxtext
#include:newtxmath
#include:titlesec
# loads pagestyles option of titlesec
#include:float
#include:caption
#include:booktabs
#include:biblatex
#include:nowidow
#include:url
#include:xcolor
#include:hyperref

\iscramset{options%keyvals}

#keyvals:\documentclass/iscram#c,\iscramset
draft
anonymous
first alone
title=%<title%>
short title=%<short title%>
author={short name=%<short name%>,full name=%<full name%>,affiliation=%<affiliation%>}
footer/line 1=%<text%>
footer/line 2=%<text%>
footer/line 3=%<text%>
iscram 2017 footer
WiPe Paper 2017=%<track name%>
CoRe Paper 2017=%<track name%>
iscram 2018 footer
WiPe Paper 2018=%<track name%>
CoRe Paper 2018=%<track name%>
#endkeyvals

\abstract{text}
\keywords{keywords%text}
\titleorig{text}#S

# from pagestyles option of titlesec
#include:titleps