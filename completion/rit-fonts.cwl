# rit-fonts package
# Matthew Bertucci 2023/07/17 for v0.9

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:polyglossia

#keyvals:\usepackage/rit-fonts#c
path=%<file path%>
extn=%<extension%>
RM=%<font name%>
SF=%<font name%>
ScaleRM=%<factor%>
ScaleSF=%<factor%>
ScaleDS=%<factor%>
ScaleHW=%<factor%>
osf
oldstyle
lf
lining
df={%<font features%>}
#endkeyvals

\Ezhuthu
\Joy
\Karuna
\Keraleeyam
\Kutty
\Meera
\Panmana
\Rachana
\Sundar
\Uroob

# not documented
\Fileversion#S
\Filedate#S
\thefontpath#S
\FontPath#S
\fontpath{path%definition}#S
\malayalamfont#S