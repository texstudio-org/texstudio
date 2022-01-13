# newtx package
# Matthew Bertucci 1/13/2022 for v1.704

# this package just loads newtxtext and newtxmath
# but we need a new cwl to account for the options

#include:newtxtext
#include:newtxmath

#keyvals:\usepackage/newtx#c
# options specific to the bundled package
otfmath#true,false
# options from newtxtext
type1#true,false
nofontspec#true,false
no-math#true,false
defaultfeatures={%<fontspec options%>}
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
tabular#true,false
t#true,false
proportional#true,false
p#true,false
scaled=%<factor%>
scale=%<factor%>
defaultsups#true,false
largesc#true,false
nohelv#true,false
nott#true,false
helvratio=%<factor%>
spcfactor=%<factor%>
spacing=##L
stretch=##L
shrink=##L
oldSS
slashedzero
theoremfont
thmslshape
thmlining
trueslanted
scosf
tighter
looser
# options from newtxmath (does not know the font-choice options)
subscriptcorrectionfile=%<file%>
nosubscriptcorrection
subscriptcorrection
timesmathacc
varbb
vvarbb
nosymbolsc
noamssymbols
amssymbols
uprightscript
uprightGreek
slantedGreek
altnu
largelibfigs
liby
frenchmath
nonewtxmathopt
upint
smallerops
useBImacros
varg
varvw
noOT1
amsthm
#endkeyvals

\ifntxotfmath#S
\ntxotfmathtrue#S
\ntxotfmathfalse#S

#ifOption:amsthm
#include:amsthm
#endif

#ifOption:useBImacros
\BIA#m
\BIB#m
\BIC#m
\BID#m
\BIE#m
\BIF#m
\BIG#m
\BIH#m
\BII#m
\BIJ#m
\BIK#m
\BIL#m
\BIM#m
\BIN#m
\BIO#m
\BIP#m
\BIQ#m
\BIR#m
\BIS#m
\BIT#m
\BIU#m
\BIV#m
\BIW#m
\BIX#m
\BIY#m
\BIZ#m
\BIa#m
\BIb#m
\BIc#m
\BId#m
\BIe#m
\BIf#m
\BIg#m
\BIh#m
\BIi#m
\BIj#m
\BIk#m
\BIl#m
\BIm#m
\BIn#m
\BIo#m
\BIp#m
\BIq#m
\BIr#m
\BIs#m
\BIt#m
\BIu#m
\BIv#m
\BIw#m
\BIx#m
\BIy#m
\BIz#m
#endif