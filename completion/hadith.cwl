# hadith package
# Matthew Bertucci 2026/08/04 for v1.1.0

#include:ifxetex
#include:biditools
#include:xkeyval
#include:xstring

#keyvals:\usepackage/hadith#c
bukhari
muslim
abudawud
tirmidhi
nasai
ibnmajah
malik
ahmad
darimi
all
sixbooks
nonumber
ornbraces
compact
showgrade
showtrans
#endkeyvals

\hadith
\hadith*
\hadith*[collection]
\hadith*[collection][number]
\hadith[collection]
\hadith[collection][number]
\hadithabudawud
\hadithabudawud[number]
\hadithahmad
\hadithahmad[number]
\hadithbukhari
\hadithbukhari[number]
\hadithcite
\hadithcite[collection]
\hadithcite[collection][number]
\hadithdarimi
\hadithdarimi[number]
\hadithibnmajah
\hadithibnmajah[number]
\hadithmalik
\hadithmalik[number]
\hadithmuslim
\hadithmuslim[number]
\hadithname{collection}
\hadithnasai
\hadithnasai[number]
\hadithrange
\hadithrange[collection]
\hadithrange[collection][range]
\hadithsection{collection}{number}
\hadithtirmidhi
\hadithtirmidhi[number]

\hadithchapterfile{collection}{book num}{filename}{first}{last}#S
\hadithcollectionname{arg1}{arg2}#S
\hadithdefcmd{collection}{number key}{text}#S
\hadithgrade{arg}#S
\hadithno{number}#S
\hadithsectionname{arg1}{arg2}{arg3}#S
\hadithsectionrange{arg1}{arg2}{arg3}{arg4}#S
\hadithtrans{arg}#S

\hadithdate#S
\hadithversion#S