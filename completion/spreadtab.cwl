# spreadtab package
# Matthew Bertucci 2025/02/27 for v0.6

#include:xstring
#include:simplekv

\begin{spreadtab}{{envname}{preamble}}#\array
\end{spreadtab}

\STeol{macro}
\STcopy{>x,vy}{formula}#t
\STsetdecimalsep{character}
\STautoround{number of digits}
\STautoround*{number of digits}
\hhline{colspec}#t
\toprule#t
\toprule[line width%l]#t
\midrule#t
\midrule[line width%l]#t
\bottomrule#t
\bottomrule[line width%l]#t
\cmidrule{a-b}#t
\cmidrule(trim){a-b}#t
\cmidrule[line width%l](trim){a-b}#t
\morecmidrules#t
\specialrule{line width%l}{above space}{below space}#t
\addlinespace#t
\addlinespace[vspace]#t
\SThiderow#t
\SThidecol#t
\STsavecell{cmd}{reference}#d
\STsetdisplaymarks{left-delim}{right-delim}
\STtag{name}
\STmakegtag{name}
\STmessage{bool%keyvals}
#keyvals:\STmessage
true
false
#endkeyvals
\STdebug{option%keyvals}
#keyvals:\STdebug
formula
text
code
#endkeyvals

\STtextcell#*
\STtransposecar#*
\STprintnum{arg}#*
\STaddcol#*
\STaddrow#*
\STrounddigit#S
\STdatetonum{cmd}{jj}{mm}{aa}#*d
\STdisplaytab#*
\STname#S
\STver#S
\STdate#S
