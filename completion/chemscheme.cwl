# chemscheme package
# Matthew Bertucci 3/18/2022 for v2.0m

#include:kvoptions
#include:psfrag
#include:floatrow
#include:chemcompounds

#keyvals:\usepackage/chemscheme#c
chemcompounds
bpchem
floatrow
tracking=#bpchem,chemcompounds
floats=#float,floatrow,memoir
#endkeyvals

#ifOption:bpchem
#include:bpchem
\schemerefsub{label%keyvals}{sublabel}
\schemerefsub[marker]{label%keyvals}{sublabel}
\chemschemerefsub{marker}{label%keyvals}{sublabel}#*
#keyvals:\schemeref#c,\chemschemeref#c,\schemerefsub#c,\chemschemerefsub#c
%bpchemlabel
#endkeyvals
#endif

#ifOption:tracking=bpchem
#include:bpchem
\schemerefsub{label}{sublabel}
\schemerefsub[marker]{label}{sublabel}
\chemschemerefsub{marker}{label}{sublabel}#*
#keyvals:\schemeref#c,\chemschemeref#c,\schemerefsub#c,\chemschemerefsub#c
%bpchemlabel
#endkeyvals
#endif

\begin{scheme}
\begin{scheme}[placement]
\end{scheme}

\schemename#*
\listofschemes
\listschemename#*

\schemeref{label%keyvals}
\schemeref[marker]{label%keyvals}
\chemschemeref{marker}{label%keyvals}#*

#keyvals:\schemeref#c,\chemschemeref#c
%compound
#endkeyvals

\schemerefmarker#*
\schemerefformat#*

\floatcontentscenter
\floatcontentscentre#*
\floatcontentsleft
\floatcontentsright