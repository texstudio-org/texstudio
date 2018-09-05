# CWL for the pgfplotstable.sty package

#include:pgfplots
#include:array

\pgfplotstableclear{table}
\pgfplotstablecol#*
\pgfplotstablecolname#*
\pgfplotstablecols#*
\pgfplotstablecreatecol[options]{row count}{table}
\pgfplotstableforeachcolumn#*
\pgfplotstableforeachcolumnelement#*
\pgfplotstablegetcolsof{file}#*
\pgfplotstablegetcolumnnamebyindex{col index}#*
\pgfplotstablegetelem{row}{column}#*
\pgfplotstablegetrowsof{file}#*
\pgfplotstablegetrowsof{table}#*
\pgfplotstablemodifyeachcolumnelement{col name}#*
\pgfplotstablename#*
\pgfplotstablenew[options]{row count}{table%cmd}#d
\pgfplotstablenew*[options]{row count}{table%cmd}#d
\pgfplotstableread{file}{table%cmd}#d
\pgfplotstableread{inline table}{table%cmd}#d
\pgfplotstablerow#*
\pgfplotstablerows#*
\pgfplotstablesave[options]{table}{output-file name}
\pgfplotstablesave[options]{file}{output-file name}
\pgfplotstableset{key-value-options}
\pgfplotstablesort[options]{resulttable%cmd}{table}#d
\pgfplotstabletranspose[options]{resulttable%cmd}{table}#d
\pgfplotstabletypeset[options]{file}
\pgfplotstabletypesetfile[options]{file}
\pgfplotstablevertcat{table}{table}
