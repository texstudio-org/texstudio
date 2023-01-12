# beamerbaseoptions package
# Matthew Bertucci 1/30/2022 for v3.65

#include:keyval

\ProcessOptionsBeamer#*
\ExecuteOptionsBeamer{options}#*
\DeclareOptionBeamer{option}{definition}#*
\DeclareOptionBeamer{option}[default]{definition}#*
\defbeameroption{option%specialDef}{definition}#s#%beameroption
\setbeameroption{options%keyvals}

#keyvals:\setbeameroption#c
%beameroption
#endkeyvals