# ccaption package
# Matthew Bertucci 11/24/2021 for v3.2c

#keyvals:\usepackage/ccaption#c
subfigure20
subfigure
caption2
titles
#endkeyvals

\captiondelim{delim}
\captionnamefont{font}
\captiontitlefont{font}
\captionstyle{style}
\centerlastline
\flushleftright
\hangcaption
\indentcaption{length}
\normalcaption
\changecaptionwidth
\normalcaptionwidth
\captionwidth{width}
\precaption{text}
\postcaption{text}
\contcaption{text}
\legend{text}
\abovelegendskip#*
\belowlegendskip#*
\namedlegend{title%text}
\namedlegend[short title]{title%text}
\newfixedcaption{command}{env}#*d
\newfixedcaption[cap-command]{command}{env}#*d
\renewfixedcaption{command}{env}#*
\renewfixedcaption[cap-command]{command}{env}#*
\providefixedcaption{command}{env}#*d
\providefixedcaption[cap-command]{command}{env}#*d
\bitwonumcaption{short1%text}{long1%text}{name}{short2%text}{long2%text}
\bitwonumcaption[label]{short1%text}{long1%text}{name}{short2%text}{long2%text}#l
\bionenumcaption{short1%text}{long1%text}{name}{short2%text}{long2%text}
\bionenumcaption[label]{short1%text}{long1%text}{name}{short2%text}{long2%text}#l
\bicaption{short1%text}{long1%text}{name}{short2%text}{long2%text}
\bicaption[label]{short1%text}{long1%text}{name}{short2%text}{long2%text}#l
\bicontcaption{long1%text}{name}{long2%text}
\midbicaption{text}
\longbitwonumcaption{short1%text}{long1%text}{name}{short2%text}{long2%text}
\longbionenumcaption{short1%text}{long1%text}{name}{short2%text}{long2%text}
\longbicaption{short1%text}{long1%text}{name}{long2%text}

#ifOption:subfigure
\contsubtop{text}
\contsubtop[subcaption]{text}
\contsubtop[list entry][subcaption]{text}
\contsubbottom{text}
\contsubbottom[subcaption]{text}
\contsubbottom[list entry][subcaption]{text}
\subconcluded
\subtop{text}
\subtop[subcaption]{text}
\subbottom{text}
\subbottom[subcaption]{text}
\newsubfloat{envname}#*
\contsubfigure{text}
\contsubfigure[subcaption]{text}
\contsubtable{text}
\contsubtable[subcaption]{text}
#endif

#ifOption:subfigure20
\contsubtop{text}
\contsubbottom{text}
\subconcluded
\subtop{text}
\subbottom{text}
\newsubfloat{envname}#*
\contsubfigure{text}
\contsubtable{text}
#endif

\newfloatlist{envname}{ext}{listname}{capname}#*N
\newfloatlist[within]{envname}{ext}{listname}{capname}#*N
\newfloatentry{counter}{ext}{level-1}#*
\newfloatentry[within]{counter}{ext}{level-1}#*
\setnewfloatindents{envname}{indent%l}{numwidth%l}#*
\newfloatpagesoff{envname}#*
\newfloatpageson{envname}#*

\cftdot#*
\cftdotfill{arg}#*
\cftdotsep#*
