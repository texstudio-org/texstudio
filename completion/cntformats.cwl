# cntformats package
# Matthew Bertucci 12/26/2021 for v0.7

#include:cnltx-base
#include:etoolbox

\AddCounterPattern{counter}{pattern}#*
\AddCounterPattern[module]{counter}{pattern}#*
\AddCounterPattern*{counter}{pattern}#*
\AddCounterPattern*[module]{counter}{pattern}#*
\NewCounterPattern{counter}{pattern}#*
\NewCounterPattern[module]{counter}{pattern}#*
\NewCounterPattern*{counter}{pattern}#*
\NewCounterPattern*[module]{counter}{pattern}#*
\ReadCounterFrom{counter}{internal cmd}#*
\ReadCounterFrom[module]{counter}{internal cmd}#*
\ReadCounterPattern{pattern}#*
\ReadCounterPattern[module]{pattern}#*
\ReadCounterPatternFrom{pattern macro}#*
\ReadCounterPatternFrom[module]{pattern macro}#*
\SaveCounterPattern{cmd a%cmd}{cmd b%cmd}{pattern}#*d
\SaveCounterPattern[module]{cmd a%cmd}{cmd b%cmd}{pattern}#*d
\eSaveCounterPattern{cmd a%cmd}{cmd b%cmd}{pattern}#*d
\eSaveCounterPattern[module]{cmd a%cmd}{cmd b%cmd}{pattern}#*d
\SaveCounterPatternFrom{cmd a%cmd}{cmd b%cmd}{pattern macro}#*d
\SaveCounterPatternFrom[module]{cmd a%cmd}{cmd b%cmd}{pattern macro}#*d
\eSaveCounterPatternFrom{cmd a%cmd}{cmd b%cmd}{pattern macro}#*d
\eSaveCounterPatternFrom[module]{cmd a%cmd}{cmd b%cmd}{pattern macro}#*d
\NewPatternFormat{pattern}{format}#*