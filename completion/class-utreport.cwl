# treport class
# Matthew Bertucci 2022/07/21 for v1.8f

#include:uplatex
#include:plext

#keyvals:\documentclass/utreport#c
a4paper
a5paper
b4paper
b5paper
a4j
a5j
b4j
b5j
a4p
a5p
b4p
b5p
10pt
11pt
12pt
landscape
tombow
tombo
mentuke
tate
oneside
twoside
onecolumn
twocolumn
titlepage
notitlepage
openright
openleft
openany
leqno
fleqn
openbib
disablejfam
mathrmmc
draft
final
#endkeyvals

\bibname#n
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chapter{title}#L1
\chaptermark{code}#*
\Cjascale
\heisei#*
\if西暦#*
\postchaptername#*
\postpartname#*
\prechaptername#*
\prepartname#*
\和暦
\西暦
\西暦false#*
\西暦true#*

# deprecated
\mc#S
\gt#S
