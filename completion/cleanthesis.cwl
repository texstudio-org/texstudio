# cleanthesis package
# Matthew Bertucci 1/8/2021 for v0.4.0

#include:xkeyval
#include:xcolor
# xcolor loaded with dvipsnames option
#include:fontenc
# fontenc loaded with T1 option
#include:lmodern
#include:charter
#include:microtype
#include:setspace
#include:graphicx
#include:tabularx
#include:enumitem
#include:blindtext
#include:textcomp
#include:hyperref
#include:scrlayer-scrpage
#include:caption
#include:csquotes
#include:tocloft

#ifOption:sansserif
#include:tgheros
#endif
#ifOption:sansserif=true
#include:tgheros
#endif

#ifOption:configurebiblatex
#include:biblatex
# biblatex loaded with natbib option
#include:natbib
#endif
#ifOption:configurebiblatex=true
#include:biblatex
# biblatex loaded with natbib option
#include:natbib
#endif

#ifOption:configurelistings
#include:listings
#endif
#ifOption:configurelistings=true
#include:listings
#endif

#keyvals:\usepackage/cleanthesis#c
hangfigurecaption#true,false
hangsection#true,false
hangsubsection#true,false
sansserif#true,false
configurelistings#true,false
figuresep=#none,colon,period,space,quad,endash
colorize=#full,reduced,bw
colortheme=#bluemagenta,bluegreen
quotesstyle=%<csquotes style options%>
configurebiblatex#true,false
bibsys=#biber,bibtex
bibfile=%<file name%>
bibstyle=%<biblatex style options%>
bibsorting=#nty,nyt,nyvt,anyt,anyvt,ynt,ydnt,none,debug
#endkeyvals

ctcolorfooterpage#B
ctcolorfooterline#B
ctcolorfootermark#B
ctcolorfootertitle#B
ctcolortitle#B
ctcolorpartnum#B
ctcolorpartline#B
ctcolorparttext#B
ctcolorchapternum#B
ctcolorchapterline#B
ctcolorsection#B
ctcolorsubsection#B
ctcolorparagraph#B
ctcolorfloatlabel#B
ctcolorlistlabel#B
ctcolormain#B
ctcoloraccessory#B
ctcolorblack#B
ctcolorgray#B
ctcolorgraylight#B
ctcolorgraylighter#B
color_todo#B

\cthesissetcolor{model}{color1}{color2}#*
\cthesissetcolorbluemagenta#*
\cthesissetcolorbluegreen#*

\begin{my_list}#*
\end{my_list}#*
\begin{my_list_num}#*
\end{my_list_num}#*
\begin{my_list_item}#*
\end{my_list_item}#*
\begin{ct_version_list}#*
\end{ct_version_list}#*
\begin{ct_version_list_sub}#*
\end{ct_version_list_sub}#*
\begin{my_list_desc}#*
\end{my_list_desc}#*

\lensectionnumber#*
\ctfooterline#*
\ctfooterrightpagenumber#*
\ctfooterleftpagenumber#*

\TODO{text%todo}#D

\tabref{label}#*r
\tableref{label}#*r
\tref{label}#*r
\treft{label}#*r
\textref{label}#*r
\textreft{label}#*r
\fref{label}#*r
\frefadd{label}{text}#*r
\figref{label}#*r
\figrefadd{label}{text}#*r
\figreft{label}#*r
\figrefaddt{label}{text}#*r
\seepage{label}#*r

\ctSetFont{arg1}{arg2}{arg3}#*
\helv#*
\book#*
\tgherosfont#*
\thesispartlabelfont#*
\thesispartfont#*
\thesischapterfont#*
\thesissectionfont#*
\thesissubsectionfont#*
\thesisparagraphfont#*
\ctfontfooterpagenumber#*
\ctfontfootertext#*
\ctchapternumber{arg}#*
\ctchaptertitle{text}#*

\hugequote#*
\cleanchapterquote{text1}{text2}{text3}#*
\begin{thesis_quotation}#*
\end{thesis_quotation}#*
\cthesisorigin{text}#*

# from dvipsnames option of xcolor
Apricot#B
Aquamarine#B
Bittersweet#B
Black#B
Blue#B
BlueGreen#B
BlueViolet#B
BrickRed#B
Brown#B
BurntOrange#B
CadetBlue#B
CarnationPink#B
Cerulean#B
CornflowerBlue#B
Cyan#B
Dandelion#B
DarkOrchid#B
Emerald#B
ForestGreen#B
Fuchsia#B
Goldenrod#B
Gray#B
Green#B
GreenYellow#B
JungleGreen#B
Lavender#B
LimeGreen#B
Magenta#B
Mahogany#B
Maroon#B
Melon#B
MidnightBlue#B
Mulberry#B
NavyBlue#B
OliveGreen#B
Orange#B
OrangeRed#B
Orchid#B
Peach#B
Periwinkle#B
PineGreen#B
Plum#B
ProcessBlue#B
Purple#B
RawSienna#B
Red#B
RedOrange#B
RedViolet#B
Rhodamine#B
RoyalBlue#B
RoyalPurple#B
RubineRed#B
Salmon#B
SeaGreen#B
Sepia#B
SkyBlue#B
SpringGreen#B
Tan#B
TealBlue#B
Thistle#B
Turquoise#B
Violet#B
VioletRed#B
White#B
WildStrawberry#B
Yellow#B
YellowGreen#B
YellowOrange#B

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