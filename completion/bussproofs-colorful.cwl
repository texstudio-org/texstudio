# bussproofs-colorful package
# Matthew Bertucci 2026/02/02 for v1.0

#include:bussproofs
#include:xcolor
#include:kvoptions

#keyvals:\usepackage/bussproofs-colorful#c
nodecolor=#%color
linecolor=#%color
labelcolor=#%color
patchnodes#true,false
patchlines#true,false
patchlabels#true,false
debug#true,false
theme=#classic,dark,pastel,highcontrast
#endkeyvals

\begin{ProofColors}
\begin{ProofColors}[options%keyvals]
\end{ProofColors}

#keyvals:\begin{ProofColors}
node=#%color
line=#%color
label=#%color
theme=#classic,dark,pastel,highcontrast
#endkeyvals

\SetNodeColor{color}
\SetLineColor{color}
\SetLabelColor{color}
\ResetProofColors

\LoadProofTheme{theme%keyvals}

#keyvals:\LoadProofTheme
classic
dark
pastel
highcontrast
#endkeyvals