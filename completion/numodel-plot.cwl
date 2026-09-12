# numodel-plot package
# Matthew Bertucci 2026/09/08 for v0.9.1

#include:siunitx
#include:pgfplots
#include:pdfrender
#include:pgfplotslibraryfillbetween

\calcplotdims
\drawplot{axis code}
\numodelplotsetup{options%keyvals}
\pzuIfUnitNonEngTF{unit}{true code}{false code}#*
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

numodelhalo#B

# not documented
\pznmpAppendXScaleTicks{arg}#S
\pznmpAppendYScaleTicks{arg}#S
\pznmpSuppressXScaleLabel#S
\pznmpSuppressYScaleLabel#S
\xlabelbuild#S
\ylabelbuild#S