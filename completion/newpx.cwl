# newpx package
# Matthew Bertucci 2023/08/22 for v1.533

#include:fontenc
#include:fontaxes
#include:ifthen
#include:iftex
#include:etoolbox
#include:scalefnt
#include:trimspaces
#include:kvoptions
#include:xstring
#include:newpxmath
#include:newpxtext

#keyvals:\usepackage/newpx#c
# passed to newpxmath
varg
subscriptcorrectionfile=%<file%>
nosubscriptcorrection
subscriptcorrection
bigdelims
varbb
vvarbb
nosymbolsc
cmintegrals
cmbraces
noamssymbols
amssymbols
uprightscript
uprightGreek
slantedGreek
frenchmath
upint
smallerops
amsthm
noOT1
fracspacing
curlybraces
# passed to newpxtext
no-math#true,false
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
tabular#true,false
t#true,false
proportional#true,false
p#true,false
scaled=%<factor%>
defaultsups#true,false
largesc#true,false
nohelv#true,false
helvratio=%<factor%>
spcfactor=%<factor%>
spacing=##L
stretch=##L
shrink=##L
oldSS
notextnu
slashedzero
theoremfont
thmlining
trueslanted
scosf
tighter
looser
supscaled=%<factor%>
supsraised=##L
supspaced=##L
#endkeyvals

#ifOption:amsthm
#include:amsthm
#endif
