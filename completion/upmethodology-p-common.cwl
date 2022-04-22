# upmethodology-p-common package
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:ifthen
#include:xspace
#include:xcolor
#include:ifpdf

\UPMVERSION#S
\UPMVERSIONTEST#S
\arakhneorg
\upmcurrentlang
\ifupmlang{language}{code}
\Ifnotempty{arg}{code}
\Ifempty{arg}{code}
\Ifelseempty{arg}{code}
\newpageintoc
\ifupmbookformat#*
\upmbookformattrue#*
\upmbookformatfalse#*
\ifupmreportformat#*
\upmreportformattrue#*
\upmreportformatfalse#*
\ifupmarticleformat#*
\upmarticleformattrue#*
\upmarticleformatfalse#*
\setpdfcolor{color}