# numprint package
# Matthew Bertucci 6/16/2021

#include:array

\numprint[unit]{number}

#ifOption:np
\np[unit]{number}
#endif

\cntprint[unit]{counter}
\lenprint[unit%keyvals]{length}

#keyvals:\lenprint#c
pt
bp
in
ft
mm
cm
m
km
#endkeyvals

\npfourdigitsep#*
\npfourdigitnosep#*

\npaddmissingzero#*
\npnoaddmissingzero#*

\npaddplus#*
\npnoaddplus#*

\npaddplusexponent#*
\npnoaddplusexponent#*

\nprounddigits{digits}
\nproundexpdigits{digits}
\npnoround#*
\npnoroundexp#*

\nplpadding[character]{digits}#*
\npnolpadding#*

\npreplacenull{replacement}#*
\npprintnull#*

\npunitcommand#*

\npdefunit{unitname}{unit}{scale}#*

\selectlanguage{language}#*

\npmakebox[text1][justification]{text2}#*

#ifOption:boldmath
\npboldmath#*
#endif

\npafternum{arg}#*

\npunit{unit}#*

\npdigits{before}{after}#*
\npexponentdigits[after]{before}#*
\npnodigits#*
\npnoexponentdigits#*

\npthousandsep{separator}#*
\npthousandthpartsep{separator}#*
\npdecimalsign{sign}#*
\npproductsign{sign}#*

\npunitseparator{separator}#*
\npdegreeseparator{separator}#*
\npcelsiusseparator{separator}#*
\nppercentseparator{separator}#*

#ifOption:autolanguage
\npstyledefault
\npstyleenglish
\npstylegerman
\npaddtolanguage{lang1}{lang2}
#endif
