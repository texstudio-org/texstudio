# studenthandouts package
# Matthew Bertucci 2/12/2022 for v1.0

#include:changepage
#include:ifthen
#include:fmtcount
#include:tocloft
#include:geometry
#include:fancyhdr

#keyvals:\usepackage/studenthandouts#c
blanks
noblanks
#endkeyvals

\sethandouttitle{title%text}
\importhandout{unit number}{handout number}
\importall
\importnone
\importonlyunits{unit numbers}
\importallunits
\importonlyhandouts{handout numbers}
\importallhandouts

\thehandoutsdirectory
\thehandoutslabel
\thehandoutscredit

\setunittitle{unit number}{unit title%text}

\thehandoutsgeometry

\thehandoutnumber
\thehandouttitle
\thehandoutfulltitle
\thehandoutpage
\theunitnumber
\theunittitle
\theunitfulltitle
\thehandoutslabel
\thehandoutscredit
\allhandoutinfo

\gnewcommand{cmd}{def}#*d
\gnewcommand{cmd}[args]{def}#*d
\gnewcommand{cmd}[args][default]{def}#*d
\grenewcommand{cmd}{def}#*
\grenewcommand{cmd}[args]{def}#*
\grenewcommand{cmd}[args][default]{def}#*
