# tpms-l class
# Matthew Bertucci 2022/08/20 for v2.20

#include:class-amsart

#keyvals:\documentclass/tpms-l#c
editor
# options passed to amsart class
10pt
11pt
12pt
8pt
9pt
a4paper
centertags
draft
e-only
final
fleqn
landscape
leqno
letterpaper
noamsfonts
nomath
notitlepage
onecolumn
oneside
portrait
reqno
tbtags
titlepage
twocolumn
twoside
#endkeyvals

\ifeditorial#S
\editorialtrue#S
\editorialfalse#S
\englishvolinfo#*
\datereceivedname#*
\dateacceptedname#*
\dateaccepted{date}#*
\UDC{UDC number}