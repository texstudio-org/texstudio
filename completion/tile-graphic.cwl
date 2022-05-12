# tile-graphic package
# Matthew Bertucci 2022/05/10 for v1.0.1

#include:xkeyval
#include:shellesc
#include:web
#include:graphicx
#include:multido

#keyvals:\usepackage/tile-graphic#c
wrttofiles
!wrttofiles
packagefiles
!packagefiles
pdfcreator=#pdflatex,lualatex,xelatex,ps2pdf,distiller
#endkeyvals

\setTileParams{rows}{cols}{imagefile}#g
\setTileParams[options%keyvals]{rows}{cols}{imagefile}#g

#keyvals:\setTileParams
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

\tileTheGraphic
\fullPathToSource{path%definition}

\afterPkgCreationHook{commands}#*
\afterTileCreationHook{commands}#*
\bpHttile#*
\bpWdtile#*
\compileTileFiles#*
\definePath{cmd}{path%definition}#*d
\dvipsappArgs{arg}#*
\ifpassthruTG#*
\iftgfolder#*
\IWTD{arg}#*
\latexappArgs{arg}#*
\nCols#*
\nFilesCreated#*
\nRows#*
\oX#S
\oY#S
\packagesuffix{suffix}#*
\passthruTGfalse#*
\passthruTGtrue#*
\pathToPic#*
\pkgappArgs{arg}#*
\syscopy{arg}#*
\sysdel{arg}#*
\sysmove{arg}#*
\tgBaseName#*
\tgfolderfalse#*
\tgfoldertrue#*
\tgInFolder#*
\tgInputContent#*
\tgTileBaseIndx#*
\tileappArgs{arg}#*
\WriteBookmarks#*
\wrtTileCuts#*
\wrttiledoc#*