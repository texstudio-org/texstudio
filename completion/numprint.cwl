# numprint package
# Matthew Bertucci 9/21/2021 for v1.39

#include:array

\numprint{number}
\numprint[unit]{number}

#ifOption:np
\np{number}
\np[unit]{number}
#endif

\cntprint{counter}
\cntprint[unit]{counter}
\lenprint{length}
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

\npunitcommand{arg}#*

\npdefunit{unitname}{unit}{scale}#*

\selectlanguage{language}#*

\npmakebox{text}#*
\npmakebox[dummy text][justification]{text}#*

#ifOption:boldmath
\npboldmath#*
#endif

\npafternum{arg}#*

\npunit{unit}#*

\npdigits{before}{after}#*
\npexponentdigits{before}#*
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
