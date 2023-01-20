# jiwonlipsum package
# ponte-vecchio 2023-01-17 for v0.6

#keyvals:\usepackage/jiwonlipsum#c
nopar
numbers
#endkeyvals

\jiwon
\jiwon[%<num/char%>]
\jiwon[%<num%>-%<num%>]
\jiwondef{%<cmd%>}{%<jiwon no.%>}#d

#ifOption:numbers
\jiwonparnumberon
\jiwonparnumberoff
#endif