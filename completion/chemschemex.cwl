# chemschemex package
# Matthew Bertucci 4/7/2022 for v1.2

#include:xkeyval
#include:etoolbox
#include:xargs
#include:xifthen
#include:suffix
#include:fancylabel
#include:graphicx
#include:tikz
#include:tikzlibraryshapes.multipart
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarypositioning

#keyvals:\usepackage/chemschemex#c
image={%<\includegraphics options%>}
labelseparator=%<separator%>
arrowadvance=##L
#endkeyvals

\customstruct{caption%text}{object%text}
\customstruct[capt TikZ keys]{caption%text}{object%text}
\customstruct[capt TikZ keys][obj TikZ keys]{caption%text}{object%text}
\CSXimage{imagefile}#g
\CSXimage[options%keyvals]{imagefile}#g
\struct{imagefile}#g
\struct[caption%text]{imagefile}#g
\struct[caption%text][family]{imagefile}#g
\struct[caption%text][family][options%keyvals]{imagefile}#g
\struct[caption%text][family][options%keyvals][capt TikZ keys]{imagefile}#g
\struct[caption%text][family][options%keyvals][capt TikZ keys][obj TikZ keys]{imagefile}#g
\struct*{imagefile}#g
\struct*[caption%text]{imagefile}#g
\struct*[caption%text][family]{imagefile}#g
\struct*[caption%text][family][options%keyvals]{imagefile}#g
\struct*[caption%text][family][options%keyvals][capt TikZ keys]{imagefile}#g
\struct*[caption%text][family][options%keyvals][capt TikZ keys][obj TikZ keys]{imagefile}#g
\struct-{imagefile}#g
\struct-[caption%text]{imagefile}#g
\struct-[caption%text][options%keyvals]{imagefile}#g
\struct-[caption%text][options%keyvals][capt TikZ keys]{imagefile}#g
\struct-[caption%text][options%keyvals][capt TikZ keys][obj TikZ keys]{imagefile}#g
\structalt{imagefile}{alt imagefile%file}#g
\structalt[caption%text]{imagefile}{alt imagefile%file}#g
\structalt[caption%text][family]{imagefile}{alt imagefile%file}#g
\structalt[caption%text][family][options%keyvals]{imagefile}{alt imagefile%file}#g
\structalt[caption%text][family][options%keyvals][capt TikZ keys]{imagefile}{alt imagefile%file}#g
\structalt[caption%text][family][options%keyvals][capt TikZ keys][obj TikZ keys]{imagefile}{alt imagefile%file}#g
\structalt*{imagefile}{alt imagefile%file}#g
\structalt*[caption%text]{imagefile}{alt imagefile%file}#g
\structalt*[caption%text][family]{imagefile}{alt imagefile%file}#g
\structalt*[caption%text][family][options%keyvals]{imagefile}{alt imagefile%file}#g
\structalt*[caption%text][family][options%keyvals][capt TikZ keys]{imagefile}{alt imagefile%file}#g
\structalt*[caption%text][family][options%keyvals][capt TikZ keys][obj TikZ keys]{imagefile}{alt imagefile%file}#g
\newstruct{imagefile}{structname}{Structname}{abbr}#g
\newstruct[sublabels]{imagefile}{structname}{Structname}{abbr}#g
\Struct{sublabels}{imagefile}#g
\Struct[family]{sublabels}{imagefile}#g
\Struct[family][options%keyvals]{sublabels}{imagefile}#g
\Struct[family][options%keyvals][capt TikZ keys]{sublabels}{imagefile}#g
\Struct[family][options%keyvals][capt TikZ keys][obj TikZ keys]{sublabels}{imagefile}#g
\Struct*{sublabels}{imagefile}#g
\Struct*[family]{sublabels}{imagefile}#g
\Struct*[family][options%keyvals]{sublabels}{imagefile}#g
\Struct*[family][options%keyvals][capt TikZ keys]{sublabels}{imagefile}#g
\Struct*[family][options%keyvals][capt TikZ keys][obj TikZ keys]{sublabels}{imagefile}#g
\Structalt{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt[family]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt[family][options%keyvals]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt[family][options%keyvals][capt TikZ keys]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt[family][options%keyvals][capt TikZ keys][obj TikZ keys]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt*{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt*[family]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt*[family][options%keyvals]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt*[family][options%keyvals][capt TikZ keys]{sublabels}{imagefile}{alt imagefile%file}#g
\Structalt*[family][options%keyvals][capt TikZ keys][obj TikZ keys]{sublabels}{imagefile}{alt imagefile%file}#g
\structname{img}
\Structname{img}
\structabbr{img}
\begin{Chemscheme}
\end{Chemscheme}
\ChemschemeNextRow
\ChemschemeNextRow[rowsep%l]
\CSXcommands{TikZ code}
\structref{img}
\structref[family]{img}
\structref*{img}
\structref*[family]{img}
\structsubref{img}{sublabels}
\structsubref[family]{img}{sublabels}
\structsubref*{img}{sublabels}
\structsubref*[family]{img}{sublabels}
\structsubref-{img}{sublabels}
\structsubref-[family]{img}{sublabels}
\CSXstructref{text}#*
\customarrow{TikZ keys}{upper caption%text}{lower caption%text}
\customarrow[length]{TikZ keys}{upper caption%text}{lower caption%text}
\RightArrow{upper caption%text}{lower caption%text}
\RightArrow[length]{upper caption%text}{lower caption%text}
\LeftArrow{upper caption%text}{lower caption%text}
\LeftArrow[length]{upper caption%text}{lower caption%text}
\LeftRightArrow{upper caption%text}{lower caption%text}
\LeftRightArrow[length]{upper caption%text}{lower caption%text}
\DoubleRightArrow{upper caption%text}{lower caption%text}
\DoubleRightArrow[length]{upper caption%text}{lower caption%text}
\DoubleLeftArrow{upper caption%text}{lower caption%text}
\DoubleLeftArrow[length]{upper caption%text}{lower caption%text}
\DoubleLeftRightArrow{upper caption%text}{lower caption%text}
\DoubleLeftRightArrow[length]{upper caption%text}{lower caption%text}
\RightupHarpoon{upper caption%text}{lower caption%text}
\RightupHarpoon[length]{upper caption%text}{lower caption%text}
\RightdownHarpoon{upper caption%text}{lower caption%text}
\RightdownHarpoon[length]{upper caption%text}{lower caption%text}
\LeftupHarpoon{upper caption%text}{lower caption%text}
\LeftupHarpoon[length]{upper caption%text}{lower caption%text}
\LeftdownHarpoon{upper caption%text}{lower caption%text}
\LeftdownHarpoon[length]{upper caption%text}{lower caption%text}
\LeftupRightupHarpoon{upper caption%text}{lower caption%text}
\LeftupRightupHarpoon[length]{upper caption%text}{lower caption%text}
\LeftupRightdownHarpoon{upper caption%text}{lower caption%text}
\LeftupRightdownHarpoon[length]{upper caption%text}{lower caption%text}
\LeftdownRightupHarpoon{upper caption%text}{lower caption%text}
\LeftdownRightupHarpoon[length]{upper caption%text}{lower caption%text}
\LeftdownRightdownHarpoon{upper caption%text}{lower caption%text}
\LeftdownRightdownHarpoon[length]{upper caption%text}{lower caption%text}
\Equilibrium{upper caption%text}{lower caption%text}
\Equilibrium[length]{upper caption%text}{lower caption%text}
\RightEquilibrium{upper caption%text}{lower caption%text}
\RightEquilibrium[length]{upper caption%text}{lower caption%text}
\LeftEquilibrium{upper caption%text}{lower caption%text}
\LeftEquilibrium[length]{upper caption%text}{lower caption%text}
\RRightEquilibrium{upper caption%text}{lower caption%text}
\RRightEquilibrium[length]{upper caption%text}{lower caption%text}
\LLeftEquilibrium{upper caption%text}{lower caption%text}
\LLeftEquilibrium[length]{upper caption%text}{lower caption%text}
\TwoRightArrow{upper caption%text}{lower caption%text}
\TwoRightArrow[length]{upper caption%text}{lower caption%text}
\TTwoRightArrow{upper caption%text}{lower caption%text}
\TTwoRightArrow[length]{upper caption%text}{lower caption%text}
\TwoLeftArrow{upper caption%text}{lower caption%text}
\TwoLeftArrow[length]{upper caption%text}{lower caption%text}
\TTwoLeftArrow{upper caption%text}{lower caption%text}
\TTwoLeftArrow[length]{upper caption%text}{lower caption%text}
\ThreeRightArrow{upper caption%text}{lower caption%text}
\ThreeRightArrow[length]{upper caption%text}{lower caption%text}
\TThreeRightArrow{upper caption%text}{lower caption%text}
\TThreeRightArrow[length]{upper caption%text}{lower caption%text}
\ThreeLeftArrow{upper caption%text}{lower caption%text}
\ThreeLeftArrow[length]{upper caption%text}{lower caption%text}
\TThreeLeftArrow{upper caption%text}{lower caption%text}
\TThreeLeftArrow[length]{upper caption%text}{lower caption%text}
\CSXdeclarearrow{command}{TikZ keys}#d
\CSXdeclarearrowbundle{csname}{TikZ keys}
\structplus
\structminus

#keyvals:\CSXimage,\struct,\struct*,\struct-,\structalt,\structalt*,\Struct,\Struct*,\Structalt,\Structalt*
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

# not documented
\CSXarrowadvance#*
\CSXarrowlength#*
\CSXcaption#*
\CSXgeneratecaption{arg1}{arg2}{arg3}{arg4}#*
\CSXimagewidth#*
\CSXlabelsep#*
\CSXlabelwidth#*
\CSXmaxlabelwidth#*
\CSXmaxtextwidth#*
\CSXtextwidth#*
\fancylabelformatCSX#*
\fancyonlysublabelformatCSX#*
\fancysublabelformatCSX#*
\lastx#*
\theCSXcaption#*
\theCSXscheme#*
\theCSXstruct#*
\theCSXstructinarrow#*
