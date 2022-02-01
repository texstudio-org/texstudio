# beamerbaselocalstructure package
# Matthew Bertucci 1/30/2022 for v3.65

#include:enumerate

\frametitle{title}#L7
\frametitle[short title]{title}
\frametitle<overlay specification>{title}
\frametitle<overlay specification>[short title]{title}
\insertframetitle#*
\insertshortframetitle#*
\insertshortframetitle[options%keyvals]#*

\framesubtitle{title}#L8
\framesubtitle<overlay specification>{title}
\insertframesubtitle#*

\begin{alertenv}
\begin{alertenv}<overlay specification>
\end{alertenv}
\begin{structureenv}
\begin{structureenv}<overlay specification>
\end{structureenv}

\alert{highlighted text%text}
\alert<overlay specification>{highlighted text%text}
\structure{text}
\structure<overlay specification>{text}

\begin{block}{title%text}
\begin{block}<action specification>{title%text}
\begin{block}{title%text}<action specification>#*
\end{block}
\insertblocktitle#*

\begin{alertblock}{title%text}
\begin{alertblock}<action specification>{title%text}
\begin{alertblock}{title%text}<action specification>
\end{alertblock}

\begin{exampleblock}{title%text}
\begin{exampleblock}<action specification>{title%text}<overlay specification>
\end{exampleblock}

\begin{enumerate}[<default overlay specification>][mini template]\item
\begin{enumerate}[mini template]\item
\insertenumlabel#*
\insertsubenumlabel#*
\insertsubsubenumlabel#*

\begin{itemize}[<default overlay specification>]\item

\begin{description}[<default overlay specification>][long text%text]\item
\begin{description}[long text%text]\item
\insertdescriptionitem#*

\begin{abstract}<action specification>
\begin{verse}<action specification>
\begin{quotation}<action specification>
\begin{quote}<action specification>

\bibitem<overlay specification>[citation text]{citekey}
\bibitem<overlay specification>{citekey}
\insertbiblabel#*

\insertcaptionname#*
\insertcaptionnumber#*
\insertcaption#*