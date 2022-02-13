# hackthefootline package
# Matthew Bertucci 2022-02-10 for release 2018-01-29

#include:ifthen
#include:pgfkeys
#include:appendixnumberbeamer
#include:etoolbox
#include:calc
#include:numprint

#keyvals:\usepackage/hackthefootline#c
onecol
twocols
threecols
countappendixframes
nofun
#endkeyvals

\htfconfig{keyvals}

#keyvals:\htfconfig
cols=#one,two,three,none
title=#short,long,none
authinst=#onlyauthor,onlyinst,instpths,authpths,both,none
date=#short,long,none
framenrs=#counter,fraction,percent,none
atsep=#colon,comma,space
#endkeyvals

\htfcheckauthor#*
\htfcheckinstit#*
\htfcheckboth#*
\htfchecknone#*
\htfframenrboxwidth#*
\htfprogress#*
\htfprintmessage#*
\htfupdateprogress#*

# deprecated
\htfObsoleteCMD#S
\htfnotitle#S
\htfshorttitle#S
\htflongtitle#S
\htfnoauthinst#S
\htfonlyauthor#S
\htfonlyinstitute#S
\htfinstitutepths#S
\htfauthorpths#S
\htfauthinst#S
\htfnodate#S
\htfshortdate#S
\htflongdate#S
\htfnoframenrs#S
\htfcounterframenrs#S
\htffractionframenrs#S
\htfpercentframenrs#S
\htfcolonsep#S
\htfcommasep#S
\htfsepspace#S