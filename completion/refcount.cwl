# refcount package
# Matthew Bertucci 10/5/2021 for v3.6

#include:ltxcmds
#include:infwarerr

\setcounterref{counter}{label}#r
\addtocounterref{counter}{label}#r
\setcounterpageref{counter}{label}#r
\addtocounterpageref{counter}{label}#r
\getrefnumber{label}#r
\getpagerefnumber{label}#r
\setrefcountdefault{value}
\getrefbykeydefault{label}{key%keyvals}{default}#r

#keyvals:\getrefbykeydefault
page
title
name
anchor
url
#endkeyvals

\refused{label}#*r
\IfRefUndefinedExpandable{label}{then}{else}#*
\IfRefUndefinedBabel{label}{then}{else}#*