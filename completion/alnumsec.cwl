# alnumsec package
# Matthew Bertucci 4/4/2022 for v0.03

#include:ifthen

#keyvals:\usepackage/alnumsec#c
usehighlevels
#endkeyvals

\alnumsecstyle{specifiers}
\alnumsectionlevels{level}{list of section csnames}
\otherseparators{level}

\surroundRoman{before}{after}
\surroundRoman[before2]{before1}{after1}#*
\surroundRoman[before2][after2]{before1}{after1}#*
\surroundroman{before}{after}
\surroundroman[before2]{before1}{after1}#*
\surroundroman[before2][after2]{before1}{after1}#*
\surroundarabic{before}{after}
\surroundarabic[before2]{before1}{after1}#*
\surroundarabic[before2][after2]{before1}{after1}#*
\surroundLetter{before}{after}
\surroundLetter[before2]{before1}{after1}#*
\surroundLetter[before2][after2]{before1}{after1}#*
\surroundletter{before}{after}
\surroundletter[before2]{before1}{after1}#*
\surroundletter[before2][after2]{before1}{after1}#*
\surroundgreek{before}{after}
\surroundgreek[before2]{before1}{after1}#*
\surroundgreek[before2][after2]{before1}{after1}#*
\surrounddoubleletter{before}{after}
\surrounddoubleletter[before2]{before1}{after1}#*
\surrounddoubleletter[before2][after2]{before1}{after1}#*
\surrounddoublegreek{before}{after}
\surrounddoublegreek[before2]{before1}{after1}#*
\surrounddoublegreek[before2][after2]{before1}{after1}#*

\ifusepreviouslevels#*
\usepreviouslevelstrue#*
\usepreviouslevelsfalse#*