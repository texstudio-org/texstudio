# systeme package
# Matthew Bertucci 9/8/2021 for v0.34

#include:xstring

\systeme{eq1,eq2,...%formula}
\systeme[alignment_chars%formula]{eq1,eq2,...%formula}

\syslineskipcoeff{value}#*
\sysdelim{delim1%formula}{delim2%formula}#*
\sysequivsign{sign%formula}{substitution%formula}#*
\sysaddeqsign{sign%formula}#*
\sysremoveeqsign{sign%formula}#*
\syseqsep{character%formula}#*
\sysalign{%<l|c|r%>,%<l|c|r%>}#*
\syssignspace{dimen%l}#*
\syseqspace{dimen%l}#*
\sysextracolsign{sign%formula}#*
\syscodeextracol{start code}{end code}#*
\sysautonum{expression%formula}#*
\sysautonum*{expression%formula}#*
\SYSeqnum#*
\sysreseteqnum#*
\syssubstitute{%<symbol1%>%<symbol2%>%<{term1}{term2}...%>}#*
\sysnosubstitute#*
\+#*