# splitbib package
# Matthew Bertucci 2025/12/11 for v1.17

#keyvals:\usepackage/splitbib#c
strict
nonstrict
reorder
keeporder
export
noexport
newchap
newsec
nonewchap
nonewsec
#endkeyvals

\begin{category}{title%text}
\begin{category}[prefix]{title%text}
\end{category}

\SBentries{keylist}#c
\SBentries[prefix]{keylist}#c

\SBtitlestyle{style}
\SBsubtitlestyle{style}

\NMSBsortlt{arg1}#S
\NMSBsort{arg1}{arg2}#S
\SBabovesepwidth#*
\SBalias{name}#*
\SBbelowsepwidth#*
\SBcomment{text}#*
\SBmiscprefix#*
\SBmisctitle#*
\SBsubtitlefont{arg}#*
\SBsubtitle{arg1}{arg2}#*
\SBtitlefont{arg}#*
\SBtitle{arg}#*
\theSBresetdepth#S