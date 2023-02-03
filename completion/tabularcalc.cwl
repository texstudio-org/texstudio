# tabularcalc package
# Matthew Bertucci 1/25/2022 for v0.2

#include:fp
#include:xstring
#include:numprint

#keyvals:\usepackage/tabularcalc#c
fixFPpow
#endkeyvals

\htablecalc{%<cell (0,0)%>}{%<var=val1,val2,...%>}{%<label%>}{%<formula%>}
\htablecalc[%<N%>]{%<cell (0,0)%>}{%<var=val1,val2,...%>}{%<label1%>}{%<formula1%>}%<...{labelN}{formulaN}%>
\tclistsep#*
\vtablecalc{%<cell (0,0)%>}{%<var=val1,val2,...%>}{%<label%>}{%<formula%>}
\vtablecalc[%<N%>]{%<cell (0,0)%>}{%<var=val1,val2,...%>}{%<label1%>}{%<formula1%>}%<...{labelN}{formulaN}%>
\tcnoshowmark#*
\tcatbeginrow#*
# use %definition below so args can contain tabular commands
\tcsethrule{line 0%definition}{line 1%definition}{other lines%definition}
\tcresethrule
\tcsetcoltype{type 1}{type 2}
\tcsetcoltype[right lines]{type 1}{type 2}
\tcresetcoltype
\defcellcode{row number}{col number}{code}#*
\edefcellcode{row number}{col number}{code}#*
\tcresetcellcode#*
\tcprintvalue{number}#*
\tcprintresult{number}{arg}#*
\tcprintroundresult{precision}#*
\tcprintroundresult*{precision}#*
\tcprintroundvalue{precision}#*
\tcwritetofile{filename%file}
\tccol#*
\tclin#*
\tabularcalcversion#S
\tabularcalcdate#S
\tabularcalcfrenchdate#S
\tabularcalcenglishdate#S
