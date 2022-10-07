# membranecomputing package
# Matthew Bertucci 2022/10/07 for v0.2.1

#include:ifthen
#include:xstring

#keyvals:\usepackage/membranecomputing#c
blackboard
traditional
#endkeyvals

### Basic notations ###
\wa
\ia
\ls
\ms
\im{index%formula}
\rs{index%formula}
\ps{index%formula}
\vE
\neuron{index%formula}
\compartment{index%formula}
\agent{index%formula}
\degree
\syn
\iin
\iout
\yes
\no

### Languages and computability theory ###
\REG
\mcREG#S
\LIN
\mcLIN#S
\CF
\CS
\RE
\mcRE#S
\compSet{arg%formula}

### Families of membrane systems ###
\AM{arg%formula}
\AM[sup%formula]{arg%formula}
\mcAM{arg%formula}#S
\mcAM[sup%formula]{arg%formula}#S
\AMO{arg%formula}
\mcTC[optarg%formula]{arg%formula}#S
\TC[optarg%formula]{arg%formula}
\TDC{arg%formula}
\TSC{arg%formula}
\CC[optarg%formula]{arg%formula}
\CDC{arg%formula}
\CSC{arg%formula}
\TEC[optarg%formula]{arg%formula}
\TDEC{arg%formula}
\TSEC{arg%formula}
\CEC[optarg%formula]{arg%formula}
\CDEC{arg%formula}
\CSEC{arg%formula}
\Pfamily{name%formula}{sup%formula}{sub%formula}{arg%formula}

### Computational complexity theory ###
\PMC{sub%formula}
\PMC[sup%formula]{sub%formula}
\PSPACEMC{sub%formula}
\PSPACEMC[sup%formula]{sub%formula}
\EXPMC{sub%formula}
\EXPMC[sup%formula]{sub%formula}
\EXPSPACEMC{sub%formula}
\EXPSPACEMC[sup%formula]{sub%formula}
\complClass{name%formula}{sup%formula}{sub%formula}

### P systems ###
\psystem{memb struc}{parameters%keyvals}{sub%formula}{degree}
\psystem[input option]{memb struc}{parameters%keyvals}{sub%formula}{degree}

#keyvals:\psystem
transition
activemembranes
symportantiport
spiking
kernel
colony
#endkeyvals

\psystemT
\rpsystemT
\psystemAM
\rpsystemAM
\psystemSA
\rpsystemSA
\SNpsystem
\rSNpsystem
\kpsystem
\rkpsystem
\pcolony
\rpcolony

### Rules ###
\mcrule{parameters%keyvals}{num1}{num2}{rulespecs1%formula}{rulespec2%formula}
\mcrule[notation]{parameters%keyvals}{num1}{num2}{rulespecs1%formula}{rulespec2%formula}
#keyvals:\mcrule
rewriting
single
multiple
paren
spike
#endkeyvals
\rewriting{arg1%formula}{arg2%formula}
\rewritingT
\evolution{arg1%formula}{arg2%formula}{sub%formula}{sup%formula}
\evolutionT
\evolutionP{arg1%formula}{arg2%formula}{sub%formula}{sup%formula}
\evolutionPT
\pevolution{arg1%formula}{arg2%formula}{sub%formula}
\pevolutionT
\pevolutionP{arg1%formula}{arg2%formula}{sub%formula}
\pevolutionPT
\antiport{arg1%formula}{index1%formula}{arg2%formula}{index2%formula}
\antiportT
\symportT
\antiportP{arg1%formula}{index1%formula}{arg2%formula}{index2%formula}
\antiportPT
\symportPT
\sendin{arg1%formula}{arg2%formula}{sub%formula}{sup1%formula}{sup2%formula}
\sendinT
\sendinP{arg1%formula}{arg2%formula}{sub%formula}{sup1%formula}{sup2%formula}
\sendinPT
\psendin{arg1%formula}{arg2%formula}{sub%formula}
\psendinT
\psendinP{arg1%formula}{arg2%formula}{sub%formula}
\psendinPT
\sendout{arg1%formula}{arg2%formula}{sub%formula}{sup1%formula}{sup2%formula}
\sendoutT
\sendoutP{arg1%formula}{arg2%formula}{sub%formula}{sup1%formula}{sup2%formula}
\sendoutPT
\psendout{arg1%formula}{arg2%formula}{sub%formula}
\psendoutT
\psendoutP{arg1%formula}{arg2%formula}{sub%formula}
\psendoutPT
\dissolution{arg1%formula}{arg2%formula}{sub%formula}{sup%formula}
\dissolutionT
\dissolutionP{arg1%formula}{arg2%formula}{sub%formula}{sup%formula}
\dissolutionPT
\pdissolution{arg1%formula}{arg2%formula}{sub%formula}
\pdissolutionT
\pdissolutionP{arg1%formula}{arg2%formula}{sub%formula}
\pdissolutionPT
\division{arg1%formula}{arg2%formula}{arg3%formula}{sub%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\divisionT
\divisionP{arg1%formula}{arg2%formula}{arg3%formula}{sub%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\divisionPT
\pdivision{arg1%formula}{arg2%formula}{arg3%formula}{sub%formula}
\pdivisionT
\pdivisionP{arg1%formula}{arg2%formula}{arg3%formula}{sub%formula}
\pdivisionPT
\separation{arg%formula}{sub%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\separationT
\separationP{arg%formula}{sub%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\separationPT
\pseparation{arg%formula}{sub%formula}
\pseparationT
\pseparationP{arg%formula}{sub%formula}
\pseparationPT
\creation{arg1%formula}{arg2%formula}{arg3%formula}{sub1%formula}{sub2%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\creationT
\creationP{arg1%formula}{arg2%formula}{arg3%formula}{sub1%formula}{sub2%formula}{sup1%formula}{sup2%formula}{sup3%formula}
\creationPT
\pcreation{arg1%formula}{arg2%formula}{arg3%formula}{sub1%formula}{sub2%formula}
\pcreationT
\pcreationP{arg1%formula}{arg2%formula}{arg3%formula}{sub1%formula}{sub2%formula}
\pcreationPT
\spiking{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}
\spikingT
\forgettingT
\spikingP{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}
\spikingPT
\forgettingPT
\krewriting{arg1%formula}{arg2%formula}{arg3%formula}
\krewritingT
\krewritingP{arg1%formula}{arg2%formula}{arg3%formula}
\krewritingPT
\linkcreation{arg1%formula}{arg2%formula}{sub1%formula}{sub2%formula}{arg3%formula}
\linkcreationT
\linkcreationP{arg1%formula}{arg2%formula}{sub1%formula}{sub2%formula}{arg3%formula}
\linkcreationPT
\linkdestruction{arg1%formula}{arg2%formula}{sub1%formula}{sub2%formula}{arg3%formula}
\linkdestructionT
\linkdestructionP{arg1%formula}{arg2%formula}{sub1%formula}{sub2%formula}{arg3%formula}
\linkdestructionPT
\tissueevolcomm{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}{sub1%formula}{sub2%formula}
\tissueevolcommT
\tissueevolsympT
\tissueevolcommP{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}{sub1%formula}{sub2%formula}
\tissueevolcommPT
\tissueevolsympPT
\evolcomm{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}{sub1%formula}{sub2%formula}
\evolcommT
\evolsyminT
\evolsymoutT
\evolcommP{arg1%formula}{arg2%formula}{arg3%formula}{arg4%formula}{sub1%formula}{sub2%formula}
\evolcommPT
\evolsyminPT
\evolsymoutPT
