# hologo package
# Matthew Bertucci 2025/11/13 for v1.16

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
ApLaTeX
ApTeX
AmSLaTeX
AmSTeX
biber
BibTeX
BibTeX8
ConTeXt
DVIPDFMx
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
pLaTeX
pTeX
SageTeX
SLiTeX
teTeX
TeX
TeX4ht
TeXLive
TTH
upLaTeX
upTeX
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
bibsf=%<font commands%>
rm=%<font commands%>
sc=%<font commands%>
sf=%<font commands%>
sy=%<font commands%>
logo=%<font commands%>
#endkeyvals

\hologoVariant{name}{variant}#*
\HologoVariant{name}{variant}#*
\hologoList#*
\hologoEntry{logo}{variant}{since}#*

# not documented
\HologoRobust{arg}#S
\hologoRobust{arg}#S
\HologoVariantRobust{arg1}{arg2}#S
\hologoVariantRobust{arg1}{arg2}#S