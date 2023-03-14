# hletter class
# Matthew Bertucci 2023/03/13 for v4.2

#include:hsetup

#keyvals:\documentclass/hletter#c
private
signit
bruni
test
english
german
french
# options passed to letter class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
twoside
oneside
draft
final
leqno
fleqn
#endkeyvals

\closingtwo{text}
\opening[add. text%text]{text}
\reference{text}
\sign[height%l]{imagefile}#g
\sign{imagefile}#g

# not documented
\hletfalse#S
\hlettrue#S
\ifhlet#S
\reftext#*
\signatureheight#*
\signatureimage#*