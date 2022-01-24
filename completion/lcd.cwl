# lcd package
# Matthew Bertucci 1/22/2022 for v0.3

\DefineLCDchar{name}{binary code}
\LCDcolors{textcolor}{bgcolor}
\LCDcolors[framecolor]{textcolor}{bgcolor}
\LCDcolors[color]{color}{color}#S
\LCD{%<N%>}{%<num of chars%>}|%<line1%>|%< ... |lineN|%>
\LCDframe
\LCDnoframe
\textLCD{%<num of chars%>}|%<text%>|
\textLCD[%<shift%>]{%<num of chars%>}|%<text%>|
\textLCDcorr#*
\LCDunitlength#*
\filedate#S
\fileversion#S