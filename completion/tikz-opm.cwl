# tikz-opm package
# Matthew Bertucci 2/15/2022 for v0.1.1

#include:tikz
# loads shapes.geometric, calc, and positioning tikzlibraries
# and shapes.multipart and arrows pgflibraries
#include:makeshape
#include:amsmath

\defaulttriangleanchors#*
\defaulttrianglelengths#*
\opmInstance{arg1}{arg2}#*
\trianglepath#*

#keyvals:\node#c
opmobject
opmprocess
opmaggregation
opmexhibition
opmgeneralization
opminstantiation
opmstate
#endkeyvals