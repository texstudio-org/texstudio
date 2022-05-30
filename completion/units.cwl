# units.sty
# A. Weder 2010/07/10
# http://www.ctan.org/tex-archive/macros/latex/contrib/units/
# Version: 1998-08-04

#include:ifthen
#include:nicefrac

#keyvals:\usepackage/units#c
tight
loose
nice
ugly
#endkeyvals

\unit[value]{dimension}
\unit{dimension}
\unitfrac[%<value%:translatable%>]{%<num%:translatable%>}{%<den%:translatable%>}
\unitfrac{%<num%:translatable%>}{%<den%:translatable%>}
