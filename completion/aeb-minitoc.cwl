# aeb-minitoc package
# Matthew Bertucci 2022/05/10 for v1.9

#keyvals:\usepackage/aeb-minitoc#c
nominitocs
!nominitocs
#endkeyvals

\TOPLevel{level%keyvals}
\BTMLevel{level%keyvals}
\TOCLevels{top level%keyvals}{btm level}
\insertminitoc
\insertminitoc[label]#r
\mtoclabel{label}#l
\begin{minitocfmt}{command}#d
\end{minitocfmt}
\declaretocfmt{level%keyvals}{various}
\mtocgobble{arg}
\miniorfulltoc{fmt}{toc-sec-heading%text}
\FmtTOCEntry
\NoFmtTOCEntry
\mtocCL{contentsline%text}{entry-cnt}
\mtocref{label}#r
\ifMiniTocListings#*
\MiniTocListingsfalse#*
\MiniTocListingstrue#*

#keyvals:\TOPLevel#c,\BTMLevel#c,\TOCLevels#c,\declaretocfmt#c
chapter
section
subsection
subsubsection
paragraph
subparagraph
#endkeyvals

#keyvals:\declaretocfmt#c
chapter*
section*
subsection*
subsubsection*
paragraph*
subparagraph*
#endkeyvals

# not documented
\BTMLevelNum#S
\csarg{arg1}{arg2}#S
\insertminitocNOT{arg}#*
\numBoxWidth{length}#*
\NUMLevel#S
\SECNUM#S
\TOCEntryNum#S
\TOPLevelNum#S