# biblatex-ext-oa package
# Matthew Bertucci 4/23/2022 for v0.15

#include:etoolbox

#keyvals:\usepackage/biblatex-ext-oa#c
enable#true,false
symbolpackage=#false,pict2e,l3draw,tikz
symbol=#plos,oanet
doiapi#true,false
#endkeyvals

#ifOption:symbolpackage=pict2e
#include:biblatex-ext-oasymb-pict2e
#endif

#ifOption:symbolpackage=l3draw
#include:biblatex-ext-oasymb-l3draw
#endif

#ifOption:symbolpackage=tikz
#include:biblatex-ext-oasymb-tikz
#endif

#ifOption:doapi
#include:biblatex-ext-oa-doiapi
#endif

\LoadOASymbolPackage{package%keyvals}#u
\LoadOASymbolPackage[symbol]{package%keyvals}#u

#keyvals:\LoadOASymbolPackage#c
pict2e
l3draw
tikz
#endkeyvals

#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
openaccess=#auto,doiapi,forcedoiapi,true,false,none,%<open access field%>
#endkeyvals

\DeclareOpenAccessFieldUrl{field}{URL spec%URL}
\DeclareOpenAccessFieldUrl[openness]{field}{URL spec%URL}
\UndeclareOpenAccessFieldUrl{field}
\DeclareOpenAccessEprintUrl{eprint type}{URL spec%URL}
\DeclareOpenAccessEprintUrl[openness]{eprint type}{URL spec%URL}
\DeclareOpenAccessEprintAlias{alias}{eprint type}
\UndeclareOpenAccessEprintUrl{eprint type}
\DeclareOpenAccessUrlFieldPriority{field1,field2,...}