# simpler-wick package
# Matthew Bertucci 11/18/2021 for v23

#include:tikz
#include:pgfopts
#include:tikzlibrarycalc
#include:tikzlibraryexternal

\wick{arg}#m
\wick[options%keyvals]{arg}#m
\c

#keyvals:\wick
sep=##L
offset=##L
#endkeyvals
