# scsnowman package
# Matthew Bertucci 8/12/2021

#include:tikz

\scsnowman
\scsnowman[options%keyvals]
\scsnowmandefault{keyvals}

#keyvals:\scsnowman,\scsnowmandefault
scale=
adjustbaseline#true,false
body
body=#%color
eyes
eyes=#%color
mouth
mouth=#%color
nose
nose=#%color
sweat
sweat=#%color
arms
arms=#%color
hat
hat=#%color
muffler
muffler=#%color
buttons
buttons=#%color
snow
snow=#%color
note
note=#%color
broom
broom=#%color
shape=
mouthshape=#smile,tight,frown
mikan=#%color
leaf=#%color
#endkeyvals

\usescsnowmanlibrary{filename}

\makeitemsnowman#*
\makeitemother#*
\makeqedsnowman#*
\makeqedother#*
\scsnowmannumeral{number}#*