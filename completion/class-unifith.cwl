# unifith class
# Matthew Bertucci 2022/07/02 for v1.6

#include:xkeyval
#include:class-book
#include:geometry
#include:ifxetex
#include:fontspec
#include:caption
#include:graphicx
#include:color
#include:booktabs
#include:amsmath
#include:etoolbox
#include:fancyhdr
#include:hyperref

#keyvals:\documentclass/unifith#c
a4paper
a5paper
b5paper
layout=#a5paper,b5paper
draft
oneside
twoside
binding=##L
noexaminfo
nodefaultfont
romandiff
fem
#endkeyvals

## Commands for the title page
\subtitle{text}
\alttitle{text}
\IDnumber{number}
\course{course%text}
\cycle{cycle}
\courseorganizer
\courseorganizer{name}
\AcademicYear{year}
\submitdate{year}#S
\advisor{name}
\coadvisor{name}
\customcoadvisorlabel{text}
\director{name}
\customdirectorlabel{text}
\examdate{date}
\examiner{name}
\examiner[role]{name}
\thesistype{type%text}
\ISBN{ISBN}
\copyyear{year}
\copyrightstatement{text}
\versiondate{date}
\website{URL}#U
\authoremail{email%URL}#U
\reviewer{name}
\reviewerlabel{text}

## Other commands and environments
\dedication{text}
\begin{abstract}
\begin{abstract}[title%text]
\end{abstract}
\begin{acknowledgments}
\begin{acknowledgments}[title%text]
\end{acknowledgments}

## Other useful commands
\eu
\iu
\der{func}{vars}#m
\pder{func}{vars}#m
\rb{subscript}
\rp{superscript}
\tb{subscript}
\tp{superscript}
\un{units%formula}
\g
\degree#*
\C
\celsius#*
\A
\angstrom#*
\micro
\ohm
\di#m
\x#m