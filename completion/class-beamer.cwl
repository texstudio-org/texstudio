# tbraun 11/5/2006
# added most/all beamer commands
# be sure to use an up to date kile svn version, only that will work properly with the strange syntax here
# 11/24/2006 added missing commands, thanks to  Marco Bertolini
#
# denisbitouze, 2017-01-13
# 2017-01-13: Dependencies to packages added.
#
# Matthew Bertucci 2022-01-30, cwls modified/added to reflect subpackage dependencies
# updated 2023/05/15 for v3.70

# Dependency Tree:
# beamer.cls
# ├── beamerbasemodes.sty
# │   ├── etoolbox.sty
# │   └── beamerbasedecode.sty
# ├── ifpdf.sty
# ├── beamerbaseoptions.sty
# │   └── keyval.sty
# ├── geometry.sty
# ├── pgfcore.sty
# ├── xxcolor.sty
# ├── atbegshi.sty
# ├── hyperref.sty
# └── beamerbaserequires.sty
#     ├── beamerbasecompatibility.sty
#     ├── beamerbasefont.sty
#     │   ├── amssymb.sty
#     │   └── sansmathaccent.sty
#     ├── beamerbasetranslator.sty
#     │   └── translator.sty
#     ├── beamerbasemisc.sty
#     ├── beamerbasetwoscreens.sty
#     ├── beamerbaseoverlay.sty
#     ├── beamerbasetitle.sty
#     ├── beamerbasesection.sty
#     ├── beamerbaseframe.sty
#     ├── beamerbaseverbatim.sty
#     ├── beamerbaseframesize.sty
#     ├── beamerbaseframecomponents.sty
#     ├── beamerbasecolor.sty
#     ├── beamerbasenotes.sty
#     ├── beamerbasetoc.sty
#     ├── beamerbasetemplates.sty
#     │   └── beamerbaseauxtemplates.sty
#     │       └── beamerbaseboxes.sty
#     ├── beamerbaselocalstructure.sty
#     │   └── enumerate.sty
#     ├── beamerbasenavigation.sty
#     ├── beamerbasetheorems.sty
#     │   ├── amsmath.sty
#     │   └── amsthm.sty
#     └── beamerbasethemes.sty

#include:beamerbasemodes
#include:ifpdf
#include:beamerbaseoptions
#include:geometry
#include:pgfcore
#include:xxcolor
#include:atbegshi
#include:hyperref
#include:beamerbaserequires

#keyvals:\documentclass/beamer#c
usepdftitle#true,false
envcountsect
notheorems
noamsthm
compress
t
c
leqno
fleqn
handout
trans
pdftex
nativepdf
pdfmark
dvips
dviwindo
dvipsone
vtex
ps2pdf
ignorenonframetext
noamssymb
bigger
smaller
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
draft
CJK
cjk
onlytextwidth
pgf={%<pgf options%>}
hyperref={%<hyperref options%>}
color={%<color options%>}
xcolor={%<xcolor options%>}
ucs
utf8x
utf8
aspectratio=#2013,1610,169,149,141,54,43,32,%<xxxx%>
#endkeyvals

#ifOption:ucs
#include:ucs
#endif

#ifOption:utf8x
#include:inputenc
# inputenc loaded with utf8x option, which loads ucs
#include:ucs
#endif

#ifOption:utf8
#include:inputenc
#endif

\headdp#*L
\footheight#*L
\sidebarheight#*L
\mathfamilydefault#S
\insertaspectratio#*
