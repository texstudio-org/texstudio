# savetrees package
# Matthew Bertucci 3/4/2022 for v2.4

#include:xkeyval
#include:ifpdf
#include:ifluatex
#include:titlesec
#include:geometry
#include:calc
#include:microtype

#keyvals:\usepackage/savetrees#c
subtle
moderate
extreme
all=#tight,normal
bibbreaks=#tight,normal
paragraphs=#tight,normal
floats=#tight,normal
mathspacing=#tight,normal
wordspacing=#tight,normal
tracking=#tight,normal
bibnotes=#tight,normal
charwidths=#tight,normal
mathdisplays=#tight,normal
leading=#tight,normal
indent=#tight,normal
lists=#tight,normal
bibliography=#tight,normal
title=#tight,normal
sections=#tight,normal
margins=#tight,normal
charwidthfraction=%<fraction%>
leadingfraction=%<fraction%>
marginwidth=##L
parindent=##L
trackingfraction=%<fraction%>
wordspacingfraction=%<fraction%>
#endkeyvals

\markeverypar{commands}#*
\savetreesbibnote{note}#*