# jlreq-trimmarks package
# Matthew Bertucci 2022/11/28 for release 2022/11/28

#include:l3keys2e
#include:jlreq-helpers

#keyvals:\usepackage/jlreq-trimmarks#c
platex
uplatex
lualatex
dvipdfmx
dvips
dviout
trimmarks_paper=%<paper type%>
trimmarks_paper={%<width,height%>}
trimmarks_paper=%<paper type%>+{%<width,height%>}
landscape
show
show={%<trimmarks, banner, digital, and/or no%>}
bleed_margin={%<top=<length>,bottom=<length>,gutter=<length>,fore-edge=<length>%>}
#endkeyvals

\jlreqtrimmarkssetup{options%keyvals}

#keyvals:\jlreqtrimmarkssetup#c
banner={%<specs%>}
trimmarks_width=##L
color=#%color
trimmarks_pattern={%<options%>}
#endkeyvals
