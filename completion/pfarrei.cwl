# pfarrei package
# Matthew Bertucci 2022/07/21 for r36

#include:ifpdf
#include:pdfpages
#include:keyval

#keyvals:\usepackage/pfarrei#c
booklet
#endkeyvals

\AvToAiv
\AvToAiv[Original-Datei]
\ifbooklet{Dann-Code}{Sonst-Code}
\begin{bookletfrontpage}
\end{bookletfrontpage}
\bookletfrontpagestyle
\motto{Motto%text}
\titlepicture{Bild}
\parish{Gemeinde}
\makebooklettitlepage
\begin{bookletbackpage}
\end{bookletbackpage}
\begin{bookletemptypage}
\end{bookletemptypage}
\bookletbackpagestyle
\bookletemptypagestyle
\begin{samedoublepage}
\end{samedoublepage}
\setupprayer{Optionen%keyvals}
\begin{prayer}
\begin{prayer}[Optionen%keyvals]
\end{prayer}
\noresponder

#keyvals:\setupprayer,\begin{prayer}
leader=%<Vorbeter%>
responder=%<Antwortende(r)%>
response=%<Antwort%>
#endkeyvals

# not documented
\bookletbackpagebox#*
\bookletemptypagebox#*
\bookletfrontpagebox#*
\bookletpagebox#*
\bookletpagestyle#*
\endbookletpagebox#*
\pfarreirevision#S
\pfarreirevisiondate#S
\printbookletbackpage#*
\printbookletpagebox#*
\printbookletpagebox[opt]#*
\revision#S
\revisiondate#S

# not for user
\bookletpage#S
\endbookletpage#S