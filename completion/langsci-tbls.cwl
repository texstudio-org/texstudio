# langsci-tbls package
# Matthew Bertucci 3/22/2022 for release 2021-01-06

#include:etoolbox
#include:tcolorbox
#include:tcolorboxlibrarybreakable
#include:tcolorboxlibraryskins

#keyvals:\usepackage/langsci-tbls#c
mdframed
tcolorbox
#endkeyvals

\begin{tblslineshorizontal}{title%text}
\begin{tblslineshorizontal}{title%text}[width]
\begin{tblslineshorizontal}{title%text}[width][color]
\end{tblslineshorizontal}
\begin{tblsfilled}{title%text}
\begin{tblsfilled}{title%text}[color]
\end{tblsfilled}
\begin{tblsframed}{title%text}
\begin{tblsframed}{title%text}[width]
\begin{tblsframed}{title%text}[width][color]
\end{tblsframed}
\begin{tblsfilledsymbol}{title%text}{PDF file%file}
\begin{tblsfilledsymbol}{title%text}[color]{PDF file%file}
\end{tblsfilledsymbol}
\begin{tblsframedsymbol}{title%text}{PDF file%file}
\begin{tblsframedsymbol}{title%text}[color]{PDF file%file}
\begin{tblsframedsymbol}{title%text}[color][width]{PDF file%file}
\end{tblsframedsymbol}

#ifOption:mdframed
#include:mdframed
\langscisymbol#*
\trennlinie#*
\tblsboxcolor#*
\tblslinecolour#*
\tblsfillcolour#*
\tblssy{symbol}{title%text}{text}
\tblssy[color]{symbol}{title%text}{text}
\tblsli{linewidth%l}{title%text}{text}
\tblsli[color]{linewidth%l}{title%text}{text}
\tblsfi{title%text}{text}
\tblsfi[color]{title%text}{text}
\tblsfr{symbol}{title%text}{text}
\tblsfr[color]{symbol}{title%text}{text}
\tblsfd{color}{linewidth%l}{title%text}{content%text}
#endif
