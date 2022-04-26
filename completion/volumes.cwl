# volumes package
# Matthew Bertucci 4/25/2022 for v1.0

#include:nowtoaux

#keyvals:\usepackage/volumes#c
manual
tocall
lofall
lotall
#endkeyvals

\allvolumescommand{commands}
\alwaysinclude{file}#i
\ifnumber{arg}{true}{false}#*
\onlyvolume
\onlyvolume[number]
\thenumberofvolumes#*
\thevolume#*
\voladdtolof{text}
\voladdtolot{text}
\voladdtotoc{text}
\volume
\volumecommand{number}{commands}
\volumelist#*
\volumename{text}
\volumeone#*
\volumethree#*
\volumetwo#*