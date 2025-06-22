# rerunfilecheck package
# Matthew Bertucci 2025/06/21 for v1.11

#include:kvoptions
#include:infwarerr
#include:pdftexcmds
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
