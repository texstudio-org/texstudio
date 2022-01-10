# hologo package
# Matthew Bertucci 1/10/2022 for v1.15

#include:ltxcmds
#include:infwarerr
#include:kvsetkeys
#include:kvdefinekeys
#include:pdftexcmds
#include:iftex
#include:kvoptions

\hologo{logo%keyvals}
\Hologo{logo%keyvals}

#keyvals:\hologo#c,\Hologo#c
(La)TeX
AmSLaTeX
AmSTeX
biber
BibTeX
BibTeX
BibTeX
BibTeX8
ConTeXt
ConTeXt
ConTeXt
emTeX
eTeX
ExTeX
HanTheThanh
iniTeX
KOMAScript
La
LaTeX
LaTeX2e
LaTeX3
LaTeXe
LaTeXML
LaTeXTeX
LuaLaTeX
LuaTeX
LyX
METAFONT
MetaFun
METAPOST
MetaPost
MiKTeX
NTS
OzMF
OzMP
OzTeX
OzTtH
PCTeX
pdfTeX
pdfLaTeX
PiC
PiCTeX
plainTeX
plainTeX
plainTeX
plainTeX
SageTeX
SLiTeX
SLiTeX
SLiTeX
SLiTeX
SliTeX
SliTeX
SliTeX
SliTeX
teTeX
TeX
TeX4ht
TTH
virTeX
VTeX
Xe
XeLaTeX
XeTeX
#endkeyvals

\hologoSetup{options%keyvals}
\hologoLogoSetup{logo}{options%keyvals}

#keyvals:\hologoSetup,\hologoLogoSetup
break#true,false
hyphenbreak#true,false
spacebreak#true,false
discretionarybreak#true,false
#endkeyvals

#keyvals:\hologoLogoSetup
variant=%<string%>
#endkeyvals

\hologoDriverSetup{options%keyvals}

#keyvals:\hologoDriverSetup
pdftex
luatex
dvipdfm
dvipdfmx
dvips
dvipsone
xdvi
xetex
vtex
driverfallback=%<driver%>
#endkeyvals

\hologoFontSetup{options%keyvals}
\hologoLogoFontSetup{logo}{options%keyvals}

#keyvals:\hologoFontSetup,\hologoLogoFontSetup
general=%<font commands%>
bibsf
rm
sc
sf
sy
logo
#endkeyvals

\hologoVariant{name}{variant}#*
\HologoVariant{name}{variant}#*
\hologoList#*
\hologoEntry{logo}{variant}{since}#*
