# logpap package
# Matthew Bertucci 2022/07/20 for v0.6

#include:calc
#include:color

\LPSet{options%keyvals}

#keyvals:\LPSet
ticksupright
noticksupright
twoninex
notwoninex
twoniney
notwoniney
fsnx
nofsnx
fsny
nofsny
tenlower
notenlower
text
notext
dimensions
nodimensions
#endkeyvals

\loglinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}
\loglinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name]
\loglinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name][y-name]
\linlogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}
\linlogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name]
\linlogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name][y-name]
\loglogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}
\loglogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name]
\loglogpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name][y-name]
\linlinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}
\linlinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name]
\linlinpap(width,height)(x-decs,y-decs){log-start}{y-shift,y-step}[x-name][y-name]

\DefineLPLabelColor{color command}
\DefineLPLabelDist{length}
\DefineLPLabelFont{font commands}
\DefineLPLineColor{color command}
\DefineLPMedLineThickness{length}
\DefineLPMedTickLen{length}
\DefineLPMinLineDist{length}
\DefineLPmu{symbol}
\DefineLPText{text}
\DefineLPThickLineThickness{length}
\DefineLPThickTickLen{length}
\DefineLPThinLineThickness{length}

\filedate#S
\fileversion#S