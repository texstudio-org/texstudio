# tikz-feynhand package
# Matthew Bertucci 12/26/2021 for v1.1.0

#include:tikz
#include:pgfopts
#include:tikzlibrarygraphs

## from tikzlibraryfeynhand.code.tex
#include:tikzlibrarycalc
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibraryexternal
#include:tikzlibrarypatterns
#include:tikzlibrarypositioning
#include:tikzlibraryshapes.geometric

\tikzfeynhandset{options%keyvals}

\begin{feynhand}
\end{feynhand}
\feynhand#S
\endfeynhand#S

\vertex
\vertex[options%keyvals]

#keyvals:\vertex,\tikzfeynhandset
particle
dot
ringdot
squaredot
crossdot
blob
ringblob
grayblob
NWblob
NEblob
%color
#endkeyvals

\propagator#*
\propagator[options%keyvals]#*
\propag
\propag[options%keyvals]

#keyvals:\propagator,\propag,\tikzfeynhandset
plain
top
fer
fermion
antfer
anti fermion
pho
photon
bos
boson
chabos
charged boson
antbos
anti charged boson
glu
gluon
sca
scalar
chasca
charged scalar
antsca
anti charged scalar
gho
ghost
chagho
charged ghost
antgho
anti charged ghost
maj
majorana
antmaj
anti majorana
momentum={%<[options] label%>}
momentum'={%<[options] label%>}
reversed momentum={%<[options] label%>}
reversed momentum'={%<[options] label%>}
mom={%<[options] label%>}
mom'={%<[options] label%>}
revmom={%<[options] label%>}
revmom'={%<[options] label%>}
insertion={%<[options] fraction%>}
slash={%<[options] fraction%>}
backslash={%<[options] fraction%>}
with arrow=%<fraction%>
with reversed arrow=%<fraction%>
%color
#endkeyvals

\iftikzfeynhandallowemptynode#*
\tikzfeynhandallowemptynodetrue#*
\tikzfeynhandallowemptynodefalse#*
\iftikzfeynhandvertex#*
\tikzfeynhandvertextrue#*
\tikzfeynhandvertexfalse#*

## from tikzfeynhand.keys.code.tex
\feynhanddotsize#*
\feynhandblobsize#*
\feynhandlinesize#*
\feynhandarrowsize#*
\feynhandtopsep#*
\feynhandtopsepcolor#*
