# includeRnw package
# Matthew Bertucci 1/9/2021 for v0.1.0

#include:kvoptions
#include:pdftexcmds

#keyvals:\usepackage/includeRnw#c
halt
build#true,false
new#true,false
knithead#true,false
noknithead
texenv
classicenv#true,false
#endkeyvals

\includeRnw{file}
\includeRnw[options%keyvals]{file}

#keyvals:\includeRnw
h
f
#endkeyvals

\rnwInputDirectory{directory%URL}
\rnwKnittedSuffix{text%plain}
\rnwKnitlogFile{file}
\rnwKnitheadName{file}

\incl{file}#*i
\includeRnwVer#S
\bs#*
\doublebs#*
\fourbs#*
\givenopt#*
\inspw{arg}#*
\insp{arg}#*
\knitOutfile#*
\purgeOutDir#*
