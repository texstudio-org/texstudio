# bibunits package
# Matthew Bertucci 3/9/2022 for v2.4

#keyvals:\usepackage/bibunits#c
globalcitecopy
labelstoglobalaux
sectionbib
subsectionbib
#endkeyvals

\begin{bibunit}
\begin{bibunit}[style%keyvals]
\end{bibunit}
\bibliographyunit
\bibliographyunit[unit]
\cite*{bibid}#c
\nocite*{bibid}#c
\putbib
\putbib[bib file]
\defaultbibliography{bib file}
\defaultbibliographystyle{style%keyvals}
\bibliography*{bib file}
\bibliographystyle*{style%keyvals}

#keyvals:\begin{bibunit}#c,\defaultbibliographystyle#c,\bibliographystyle*#c
abbrv
acm
alpha
apalike
ieeetr
plain
siam
unsrt
#endkeyvals

\iflabelstoglobalaux#S
\labelstoglobalauxtrue#S
\labelstoglobalauxfalse#S
\ifglobalcitecopy#S
\globalcitecopytrue#S
\globalcitecopyfalse#S
\stdthebibliography#S
\remequivalent#S
\from#S
\given#S
\plugh#S
\hgulp#S