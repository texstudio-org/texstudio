# spreadtab package
# Matthew Bertucci 10/25/2021 for v0.5

#include:xstring
#include:fp

#keyvals:\usepackage/spreadtab#c
fp
xfp
#endkeyvals

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

\STusefp#*
\STusexfp#*
\STtextcell#*
\STnumericfieldmarker#*
\STtransposecar#*
\STprintnum{arg}#*
\STeval{variable%cmd}{expression}#*d
\STround{variable%cmd}{value}{digits}#*d
\STclip{variable%cmd}{value}#*d
\STtrunc{variable%cmd}{value}{digits}#*d
\STadd{variable%cmd}{value1}{value2}#*d
\STmul{variable%cmd}{value1}{value2}#*d
\STdiv{variable%cmd}{value1}{value2}#*d
\STseed#*
\STrandom{variable%cmd}#*d
\STifzero{value}#*
\STifgt{value1}{value2}#*
\STiflt{value1}{value2}#*
\STifeq{value1}{value2}#*
\STifint{value}#*
\STifneg{value}#*
\STaddcol#*
\STaddrow#*
\STrounddigit#S
\STdatetonum{cmd}{jj}{mm}{aa}#*d
\STdisplaytab#*
\STname#S
\STver#S
\STdate#S
