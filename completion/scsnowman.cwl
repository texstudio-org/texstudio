# scsnowman package
# Matthew Bertucci 2023/02/14 for v1.3b

#include:tikz
#include:keyval

\scsnowman
\scsnowman[options%keyvals]
\scsnowmandefault{keyvals}
\scsnowmannumeral{number}
\scsnowmannumeral[options%keyvals]{number}

#keyvals:\scsnowman#c,\scsnowmandefault#c,\scsnowmannumeral#c
scale=%<factor%>
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

\usescsnowmanlibrary{library%file}

\makeitemsnowman#*
\makeitemother#*
\makeqedsnowman#*
\makeqedother#*

#keyvals:\pagenumbering#c
enumsnowman
#endkeyvals

# not documented
\enumsnowman{arg}#S
\makedocumentsnowman#S
\scsnowmanNumeral{arg1}{arg2}#S
