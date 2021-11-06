# rerunfilecheck package
# Matthew Bertucci 11/5/2021 for v1.9

#include:kvoptions
#include:infwarerr
#include:pdftexcmds
#include:atveryend
#include:uniquecounter

\RerunFileCheckSetup{options%keyvals}#*
#keyvals:\RerunFileCheckSetup
mainaux
partaux
starttoc
index
glossary
aux
#endkeyvals

\RerunFileCheck{file}{file closing action}{rerun warning}#*