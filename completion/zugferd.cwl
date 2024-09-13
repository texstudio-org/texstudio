# zugferd package
# Matthew Bertucci 2024/09/13 for v0.8

#include:siunitx

#keyvals:\usepackage/zugferd#c
format=#xrechnung,xrechnung3.0,xrechnung2.3,basic
zugferd#true,false
write-xml#true,false
xml-file=%<filename%>
auto-exemption#true,false
#endkeyvals

\SetZUGFeRDData{keyvals}
\SetZUGFeRDData*{keyvals}
\SetZugferdData{keyvals}#S
\SetZugferdData*{keyvals}#S

\InsertZUGFeRDData{data-selection}
\InsertZUGFeRDData[special mode option]{data-selection}
\InsertZugferdData{data-selection}#S
\InsertZugferdData[special mode option]{data-selection}#S

\begin{ZUGFeRD}#*
\end{ZUGFeRD}#*
\startWritingZUGFeRDxml#*
\stopWritingZUGFeRDxml#*
\setupZUGFeRDStrings{property}{settings}#*