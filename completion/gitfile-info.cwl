# gitfile-info package
# Matthew Bertucci 2/5/2022 for v0.5

#include:ifthen
#include:currfile
#include:hyperref
#include:tcolorbox
#include:tcolorboxlibraryfitting
#include:tcolorboxlibraryskins
#include:tcolorboxlibrarybreakable

\gfiGetDay
\gfiGetMonth
\gfiGetYear
\gfiGetHour
\gfiGetMin
\gfiGetAuthorName
\gfiGetAuthorMail
\gfiGetDate
\gfiGetCommit
\gfiGetCommitAbr

\gfiInfo[hash length]
\gfiInfo[hash length][date format]
\gfiInfo[hash length][date format][author format]
\gfiInfo[hash length][date format][author format][tcolorbox]

\begin{gfiInfoBox}
\end{gfiInfoBox}

\gfiInclude{file}#i
\gfiInput{file}#i

\gfiSetDate{day}{month}{year}{hour}{minute}{long form}
\gfiSetAuthor{name}{email%URL}#U
\gfiSetCommit{hash}{hash-abr}

\gfiCurrentConfig#*
\gfiInitInc{file}#*
\gfiInitJob#*
