# thumby package
# Matthew Bertucci 1/28/2022 for v0.1

#include:tikz
#include:perltex
#include:bophook

#keyvals:\usepackage/thumb#c
minitoc
box
filledbox
oval
filledoval
#endkeyvals

\thumbyNumberFormat{format}
\thumbySides{one or two}
\thumbyBackground{color}
\thumbyForeground{color}
\thumbyPageHeight{points}
\thumbyThumbWidth{points}
\thumbySetup
\thumbyTotalChapters{number}

\thumbychapnum#*
\thumbyprintthumb{number}{left or right}#*
\thumbyprintthumbleft{number}#*
\thumbyprintthumbright{number}#*