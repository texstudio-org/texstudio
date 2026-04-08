# tokstools package
# Matthew Bertucci 2026/03/31 for v0.1

#include:simplekv

\printtoks{tokens}
\printtoks[keyvals]{tokens}

#keyvals:\printtoks
expand arg=%<integer%>
code=%<code%>
intertoks=##L
printcharcode#true,false
printcatcode#true,false
hexcharcode#true,false
baselinecoeff=%<factor%>
vlines#true,false
boxed#true,false
#endkeyvals

\toksdo{patterns}{tokens}
\toksdo[keyvals]{patterns}{tokens}

#keyvals:\toksdo
expand arg=%<integer%>
collect#true,false
assign=%<code%>
#endkeyvals

\tokslen
\selfindex
\selfcharcode
\selfcatcode
\addtok{code}
\deltok
\setcharcode{expr}
\setcatcode{expr}
\self

\tokscount{patterns}{tokens}
\tokscount[keyvals]{patterns}{tokens}

#keyvals:\tokscount
expand arg=%<integer%>
assign=%<code%>
assign match=%<code%>
#endkeyvals

\defpattern%<\command%>{%<patterns%>}
\defpattern{cmd}{patterns}#Sd

\ifpegmatch{patterns}{tokens}{true code}{false code}
\ifpegmatch[keyvals]{patterns}{tokens}{true code}{false code}

#keyvals:\ifpegmatch
expand arg=%<integer%>
mode=#0,1,2
capture name=%<name%>
assign prematch=%<code%>
assign match=%<code%>
assign postmatch=%<code%>
#endkeyvals

\matchtoks
\remaintoks
\prematchtoks
\matchposition

\pegcount{patterns}{tokens}
\pegcount[keyvals]{patterns}{tokens}

#keyvals:\pegcount
expand arg=%<integer%>
assign=%<code%>
assign positions=%<code%>
name=%<name%>
#endkeyvals

\tokscapture{index}

\pegreplace{patterns}{tokens}{replacement}
\pegreplace[keyvals]{patterns}{tokens}{replacement}

#keyvals:\pegreplace
expand arg=%<integer%>
all#true,false
assign=%<code%>
#endkeyvals

\R#S
\s#S

\tktlname#S
\tktlver#S
\tktldate#S