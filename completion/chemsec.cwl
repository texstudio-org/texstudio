# chemsec class
# Matthew Bertucci 2/7/2022 for v1.12

#include:ifthen

#keyvals:\usepackage/chemsec#c
debug
draft
#endkeyvals

\DefineChemical{key%specialDef}{name}{sub-label}#s#%chemseckey

\ChemCite{key%keyvals}
\ChemFCite{key%keyvals}
\ChemSCite{key%keyvals}
\ChemMFCite{key%keyvals}
\ChemMSCite{key%keyvals}
\NoCite{key%keyvals}

#keyvals:\ChemCite#c,\ChemFCite#c,\ChemSCite#c,\ChemMFCite#c,\ChemMSCite#c,\NoCite#c
%chemseckey
#endkeyvals

\ChemFullLabelStyle{full name}{main label}{sub label}#*
\ChemLabelStyle{label}#*
\ChemMainCounterStyle{counter}#*
\ChemShortLabelStyle{main label}{sub label}#*
\ChemSubCounterStyle{counter}#*