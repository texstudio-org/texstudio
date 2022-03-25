# focus beamertheme
# Matthew Bertucci 3/12/2022 for v3.3.0

# Dependency Tree:
# beamerthemefocus.sty
# ├── fontenc.sty (with T1 option)
# ├── FiraSans.sty
# ├── FiraMono.sty
# ├── firamath-otf.sty
# ├── beamercolorthemefocus.sty
# ├── beamerfontthemefocus.sty
# ├── beamerinnerthemefocus.sty
# │   └── tikz.sty
# └── beamerouterthemefocus.sty
#     ├── appendixnumberbeamer.sty
#     ├── bookmark.sty
#     ├── etoolbox.sty
#     └── tikz.sty

#include:fontenc
#include:FiraSans
#include:FiraMono
#include:firamath-otf
#include:appendixnumberbeamer
#include:bookmark
#include:etoolbox
#include:tikz

#keyvals:\usetheme/focus
numbering=#progressbar,fullbar,minimal,none
totalframenumbering=#yes,no
nofirafonts
#endkeyvals

# from beamercolorthemefocus.sty
main#B
background#B
alert#B
example#B

# from beamerfontthemefocus.sty
# no user commands

# from beamerinnerthemefocus.sty
# no user commands

# from beamerouterthemefocus.sty
\bkmtranslateto#*
\bkmtranslate{arg}#*
\therealframenumber#*
\no#*
\footlineinfo{text}

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
