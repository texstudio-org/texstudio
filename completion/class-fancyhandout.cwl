# fancyhandout package
# Matthew Bertucci 2022-02-10 for release 2018-01-22

#include:etoolbox
#include:geometry
#include:csquotes
#include:enumitem
#include:fancyhdr
#include:xcolor

#keyvals:\documentclass/fancyhandout#c
letter
oneside
10pt
11pt
12pt
rmfont
#endkeyvals

\title[short title%text]{title%text}
\subtitle{subtitle%text}
\subtitle[short subtitle%text]{subtitle%text}
\author[short author]{author}
\institute{institute%text}
\institute[short institute%text]{institute%text}
\date[short date]{date}

\inserttitle#*
\insertshorttitle#*
\insertsubtitle#*
\insertshortsubtitle#*
\insertauthor#*
\insertshortauthor#*
\insertinstitute#*
\insertshortinstitute#*
\insertdate#*
\insertshortdate#*

fancyhandoutblue#B
fancyhandoutmaincolor#B
fancyhandoutsecondarycolor#B
fancyhandoutsectlinecolor#B
fancyhandoutsubsectlinecolor#B
fancyhandouttboxlinecolor#B
fancyhandouttboxfillcolor#B

\fancysection{title}#*L2
\fancysubsection{title}#*L3
\fancysubsubsection{title}#*L4
\phantomsection#*
\origtableofcontents#S