# bitreport class
# Matthew Bertucci 2022/12/04 for v3.2.0

#include:l3keys2e
#include:class-ctexart
#include:xeCJK
#include:geometry
#include:fancyhdr
#include:setspace
#include:caption
#include:booktabs
#include:pdfpages

#keyvals:\documentclass/bitreport#c
type=undergraduate_proposal
#endkeyvals

\BITSetup{键值对%keyvals}

#keyvals:\BITSetup#c
cover={%<键值列表%>}
cover/date=%<任意字符串%>
cover/dilimiter=%<任意字符串%>
cover/autoWidth#true,false
cover/autoWidthPadding=##L
cover/labelMaxWidth=##L
cover/valueMaxWidth=##L
cover/labelAlign=#c,l,r
cover/valueAlign=#c,l,r
cover/underlineThickness=##L
cover/underlineOffset=##L
info={%<键值列表%>}
info/title=%<字符串%>
info/school=%<字符串%>
info/major=%<字符串%>
info/class=%<字符串%>
info/author=%<字符串%>
info/studentId=%<字符串%>
info/supervisor=%<字符串%>
info/externalSupervisor=%<字符串%>
misc={%<键值列表%>}
misc/reviewTable=%<.pdf file%>
#endkeyvals

\MakeCover
\MakeReviewTable
