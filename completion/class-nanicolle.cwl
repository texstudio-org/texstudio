# nanicolle class
# Matthew Bertucci 2022/05/06 for v2.03y

#include:class-ctexart
#include:graphicx
#include:geometry
#include:multicol
#include:xstring
#include:listofitems
#include:color
#include:calc

#keyvals:\documentclass/nanicolle#c
rulerhead
colbarcode
detbarcode
nomap
autoduplicate
internal
#endkeyvals

#ifOption:rulerhead
#include:rulerbox
#endif

#ifOption:colbarcode
#include:makebarcode
#endif

#ifOption:detbarcode
#include:qrcode
#endif

\heading{text}
\subheading{text}
\collect
\identify
\Collect
\Identify

# not documented
\Altitude#*
\ChnName#*
\ColDate#*
\ColNum#*
\Collector#*
\DBH#*
\DateIdentification#*
\Descr#*
\Family#*
\Habitat#*
\Height#*
\Identifier#*
\IdentifierStd#*
\LatName#*
\Latitude#*
\LifeForm#*
\Location#*
\Longitude#*
\NumDup#*
\PhotoNum#*
\RecNum#*
\Remark#*
\aster#*
\degree#*
\detchinesestyle#*
\detcommonnamestyle#*
\detlatinstyle#*
\headerstyle#*
\headingstyle#*
\herbariumcode{arg}#*
\identifierstyle#*
\mapdef{name}{file}{longmin}{longmax}{latmin}{latmax}#*
\mapseries{name}#*
\printbarcode#*
\printform#*
\printheadings#*
\printmap#*
\printqrcode#*
\strsubs{stringA}{stringB}#*