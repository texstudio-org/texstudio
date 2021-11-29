# stackengine package
# Matthew Bertucci 11/27/2021 for v4.11

#include:etoolbox
#include:listofitems
#include:calc

#keyvals:\usepackage/stackengine#c
usestackEOL
oldsyntax
#endkeyvals

\Sstackgap
\Lstackgap
\setstackgap{S or L}{gap%l}
\stackgap
\stackalignment
\quietstack
\useanchorwidth
\stacktype
\stackMath
\lstackMath
\stackText
\lstackText
\strutlongstacks{T or F}
\strutshortanchors{T or F}
\setstackEOL{end-of-line character}
\stackengine{gap%l}{anchor}{item}{O or U}{align%keyvals}{quiet-bool}{anchorwidth-bool}{type}
\stackon{anchor}{item}
\stackon[length]{anchor}{item}
\stackunder{anchor}{item}
\stackunder[length]{anchor}{item}
\Shortstack{item1 ... itemN anchor}
\Shortstack[align%keyvals]{item1 ... itemN anchor}
\Longstack{item1 ... itemN anchor}
\Longstack[align%keyvals]{item1 ... itemN anchor}
\Shortunderstack{anchor item1 ... itemN}
\Shortunderstack[align%keyvals]{anchor item1 ... itemN}
\Longunderstack{anchor item1 ... itemN}
\Longunderstack[align%keyvals]{anchor item1 ... itemN}
\tllap[length]{item}
\tllap{item}
\tclap[length]{item}
\tclap{item}
\trlap[length]{item}
\trlap{item}
\bllap[length]{item}
\bllap{item}
\bclap[length]{item}
\bclap{item}
\brlap[length]{item}
\brlap{item}
\toplap{direction%keyvals}{item}
\toplap[length]{direction%keyvals}{item}
\bottomlap{direction%keyvals}{item}
\bottomlap[length]{direction%keyvals}{item}
\stackanchor{top item}{bottom item}
\stackanchor[gap%l]{top item}{bottom item}
\Centerstack{item1 ... itemN}
\Centerstack[align%keyvals]{item1 ... itemN}
\Vectorstack{item1 ... itemN%formula}
\Vectorstack[align%keyvals]{item1 ... itemN%formula}
\parenVectorstack{item1 ... itemN}#m
\parenVectorstack[align%keyvals]{item1 ... itemN}#m
\bracketVectorstack{item1 ... itemN}#m
\bracketVectorstack[align%keyvals]{item1 ... itemN}#m
\braceVectorstack{item1 ... itemN}#m
\braceVectorstack[align%keyvals]{item1 ... itemN}#m
\vertVectorstack{item1 ... itemN}#m
\vertVectorstack[align%keyvals]{item1 ... itemN}#m
\ensurestackMath{formula}
\abovebaseline{item}
\abovebaseline[gap%l]{item}
\belowbaseline{item}
\belowbaseline[gap%l]{item}
\stackinset{Halign%keyvals}{Hoffset%l}{Valign}{Voffset}{inset item}{anchor item}
\addstackgap{item}
\addstackgap[gap%l]{item}
\hsmash{item}
\savestack{macro%cmd}{stacking operation}#d

#keyvals:\stackengine#c,\Shortstack#c,\Longstack#c,\Shortunderstack#c,\Longunderstack#c,\toplap#c,\bottomlap#c,\Centerstack#c,\Vectorstack#c,\parenVectorstack#c,\bracketVectorstack#c,\braceVectorstack#c,\vertVectorstack#c,\stackinset#c
l
c
r
#endkeyvals

\stackengineversionnumber#S
\removebs{arg}#S
\stackedbox#S

# deprecated
\bottominset#S
\topinset#S