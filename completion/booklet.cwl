# booklet package
# Matthew Bertucci 4/12/2022 for v0.7b

#include:bkltprnt

#keyvals:\usepackage/booklet#c
print
noprint
four
eight
sixteen
thirtytwo
twouparticle
largetypeblock
1to1
landscape
#endkeyvals

\checkforlandscape#*
\magstepminus%<<number>%>
\pagespersignature{number}
\thesigcount#*
\thesignature#*
\ifprintoption
\printoptiontrue#*
\printoptionfalse#*
\ifuselandscape
\uselandscapetrue#*
\uselandscapefalse#*
\ifsidebyside
\sidebysidetrue#*
\sidebysidefalse#*
\pageseplength#*
\pagesepoffset#*
\pagesepwidth#*