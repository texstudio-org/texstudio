# preview package
# Matthew Bertucci 2022/08/20 for v13.1

#include:luatex85

#keyvals:\usepackage/preview#c
active
noconfig
psfixbb
dvips
pdftex
xetex
displaymath
floats
textmath
graphics
sections
delayed
auctex
showlabels
tightpage
lyx
counters
footnotes
tracingall
showbox
#endkeyvals

#ifOption:tightpage
\PreviewBorder
\PreviewBbAdjust
#endif

\begin{preview}
\end{preview}
\begin{nopreview}
\end{nopreview}
\PreviewMacro{macro}
\PreviewMacro[arg spec]{macro}
\PreviewMacro*{macro}
\PreviewMacro*[arg spec][default]{macro}
\PreviewEnvironment{envname}
\PreviewEnvironment[arg spec]{envname}
\PreviewEnvironment*{envname}
\PreviewEnvironment*[arg spec][default]{envname}
\PreviewSnarfEnvironment{envname}
\PreviewSnarfEnvironment[arg spec]{envname}
\PreviewOpen
\PreviewClose
\ifPreview
