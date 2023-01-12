# bpchem package
# Matthew Bertucci 3/18/2022 for v1.1

#include:xspace

#keyvals:\usepackage/bpchem
cbgreek
#endkeyvals

\BPChem{compound}
\IUPAC{compound%definition}

\CNlabel{label%specialDef}#s#%bpchemlabel
\CNlabelnoref{label%specialDef}#s#%bpchemlabel
\CNref{label%keyvals}
\CNlabelsub{label%specialDef}{sublabel}#s#%bpchemlabel
\CNlabelsubnoref{label%specialDef}{sublabel}#s#%bpchemlabel
\CNrefsub{label%keyvals}

#keyvals:\CNref#c,\CNrefsub#c
%bpchemlabel
#endkeyvals

\HNMR
\CNMR
\cis
\trans
\bpalpha
\bpbeta
\bpDelta
\hapto{number}

# not documented
\allowhyphens#*
\BPCadjustsub#*
\BPCadjustsuper#*
\BPCdelta#*
\BPClensub#*
\BPClensuper#*
\BPCSetup#*
\BPCSetupCat#*
\BPCsub{arg}#*
\BPCsubbs{arg}#*
\BPCsuper{arg}#*
\BPCsuperbs{arg}#*
\BreakHyph#*
\DoBPChem{arg}#*
\DoIUPAC{arg}#*
\dreh{arg}#*
\ifusecbgreek#*
\lookforsub#*
\lookforsuper#*
\MB#*
\MultiBreak#*
\next#*
\Prep#*
\talpha#*
\tbeta#*
\theBPCno#*
\theBPCnoa#*
\usecbgreekfalse#*
\usecbgreektrue#*