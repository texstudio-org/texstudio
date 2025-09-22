# Arguelles beamertheme
# Matthew Bertucci 2025/09/21 for v2.5.0

#include:ifluatex
#include:ifxetex
#include:fontenc
# loads T1 option of fontenc
#include:Alegreya
#include:AlegreyaSans
#include:eulervm
#include:mathalpha
# loads bb=px option of mathalpha
#include:microtype
#include:fontawesome5
#include:opencolor
#include:enumitem
#include:parskip
#include:tikz
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:tikzlibrarycalc

#keyvals:\usetheme/Arguelles#c
sans
frameno
splitnav
noalegre
#endkeyvals

#ifOption:splitnav
#include:etoolbox
#endif

\mediumfont
\Section{title}#L2
\End

# from Arguelles innertheme
\insertevent#*
\event{event%text}
\insertemail#*
\email{email%URL}#U
\inserthomepage#*
\homepage{URL}#U
\insertgithub#*
\github{username}
\fillpicture{imagefile}#g

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from bb=px option of mathalpha
\mathbb{text%plain}#m
\mathbbb{text%plain}#m
