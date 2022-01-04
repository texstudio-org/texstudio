# errata package
# Matthew Bertucci 12/30/2021 for v0.3

#include:keyval

#keyvals:\usepackage/errata#c
show
hide
margins
foots
record
#endkeyvals

\ifmargins#*
\marginstrue#*
\marginsfalse#*
\iffoots#*
\footstrue#*
\footsfalse#*
\ifrecord#*
\recordtrue#*
\recordfalse#*

\erratumAdd{explanation%text}{new text%text}
\erratumAdd[options%keyvals]{explanation%text}{new text%text}
\erratumDelete{explanation%text}{deleted text%text}
\erratumDelete[options%keyvals]{explanation%text}{deleted text%text}
\erratumReplace{explanation%text}{old text%text}{new text%text}
\erratumReplace[options%keyvals]{explanation%text}{old text%text}{new text%text}

\begin{erratum}
\begin{erratum}[options%keyvals]
\end{erratum}

\erratumItem{reference}{explanation%text}
\begin{errata}
\end{errata}

\printerrata{file}
\PrintErrata{file}

\eAdd{text}
\eDelete{text}
\eReplace{text}

\ErratumRef#*
\theerratum#*
\ednotemessage#*