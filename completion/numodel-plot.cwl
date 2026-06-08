# numodel-plot package
# Matthew Bertucci 2026/06/08 for v0.7.0

#include:siunitx
#include:pgfplots
#include:pgfplotslibraryfillbetween

\calcplotdims
\drawplot{axis code}
\numodelplotsetup{options%keyvals}
\qtyPlain[options%keyvals]{number}{unit%specialMultiArg}
\qtyPlain{number}{unit%specialMultiArg}
\xcm#*
\xcmmax#*
\xlabelqty#*
\xlabelunit#*
\xmax#*
\xmin#*
\xtickdistance#*
\ycm#*
\ycmmax#*
\ylabelqty#*
\ylabelunit#*
\ymax#*
\ymin#*
\ytickdistance#*

# not documented
\pznmpAppendXScaleTicks{arg}#S
\pznmpAppendYScaleTicks{arg}#S
\pznmpSuppressXScaleLabel#S
\pznmpSuppressYScaleLabel#S
\pzuIfUnitNonEngTF{arg1}{arg2}{arg3}#S
\xlabelbuild#S
\ylabelbuild#S