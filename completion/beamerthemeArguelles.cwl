# Arguelles beamertheme
# Matthew Bertucci 2023/10/31 for v2.3.0

#include:inputenc
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
mp
#endkeyvals

#ifOption:splitnav
#include:etoolbox
#endif

#ifOption:mp
#include:ulem
#include:booktabs
#include:dcolumn
#include:makecell
#include:colortbl
#include:cancel
#include:pgfplots
#include:csvsimple
#include:pgfplotslibraryfillbetween
#include:pgfplotslibrarygroupplots
#include:pgfplotslibrarystatistics
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
