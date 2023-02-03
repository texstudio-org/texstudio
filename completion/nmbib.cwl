# nmbib package
# Matthew Bertucci 3/21/2022 for v1.04

#include:natbib

# all options passed to natbib
#keyvals:\usepackage/nmbib#c
round
square
curly
angle
semicolon
colon
comma
authoryear
numbers
super
sort
sort&compress
compress
longnamesfirst
sectionbib
nonamebreak
merge
elide
mcite
#endkeyvals

\multibibliography{bibfile1,bibfile2,...}
\multibibliography{bib file}#S
\multibibliographystyle{type%keyvals}{style}
\citealn{keylist}#C
\citeall{keylist}#C
\citeall*{keylist}#C
\printbibliography{type%keyvals}
\nmbibRedirectLinks{source type%keyvals}{target type}
\nmbibLink{keylist}{type%keyvals}{text}



\timelinerefname#*
\sequencerefname#*
\authorsrefname#*
\timelinebibname#*
\sequencebibname#*
\authorsbibname#*
\multibibliographyfilename{type%keyvals}{filename%file}#*
\nmbibBasetype{type%keyvals}#*
\nmbibSetCiteall{pattern}#*
\nmbibKEY#*
\nmbibNAME#*
\nmbibDATE#*
\nmbibNUM#*
\nmbibSetBiblabel{type%keyvals}{pattern}#*
\nmbibYearSuffixOff#*
\nmbibYearSuffixOn#*
\nmbibcitenumber{arg1}{arg2}#S

#keyvals:\multibibliographystyle,\printbibliography,\nmbibRedirectLinks,\nmbibLink,\multibibliographyfilename,\nmbibBasetype,\nmbibSetBiblabel
timeline
sequence
authors
#endkeyvals
