# harvard package
# Matthew Bertucci 2026/09/30 for v2.0.5

#include:ifthen

#keyvals:\usepackage/harvard#c
full
abbr
default
agsmcite
dcucite
round
curly
angle
square
none
#endkeyvals

\citeasnoun{bibid}#C
\citeasnoun[add. text%text]{bibid}#C
\possessivecite{bibid}#C
\possessivecite[add. text%text]{bibid}#C
\citeaffixed{bibid}{prefix%text}#C
\citeaffixed[add. text%text]{bibid}{prefix%text}#C

\citationmode{mode%keyvals}

#keyvals:\citationmode
full
abbr
default
#endkeyvals

\citeyear{bibid}#C
\citeyear[add. text%text]{bibid}#C
\citename{bibid}#C
\citename[add. text%text]{bibid}#C

\citationstyle{style%keyvals}

#keyvals:\citationstyle
agsm
dcu
#endkeyvals

\harvardparenthesis{type%keyvals}
\harvardyearparenthesis{type%keyvals}

#keyvals:\harvardparenthesis,\harvardyearparenthesis
round
curly
angle
square
none
#endkeyvals

\harvardleft#*
\harvardright#*
\harvardand#*

\harvarditem{full citation}{year}{citekey}#*
\harvarditem[abbr citation]{full citation}{year}{citekey}#*

# not documented
\harvardcite{arg1}{arg2}{arg3}{arg4}#S
\harvardpreambledefs{arg1}#S
\harvardpreambletext#S
\harvardurl{arg1}#S
\harvardyearleft#S
\harvardyearright#S