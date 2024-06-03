# tagpdf package
# Matthew Bertucci 2024/06/02 for v0.99b

#include:pdfmanagement-testphase

#keyvals:\usepackage/tagpdf#c
luamode
genericmode
disabledelayedshipout
#endkeyvals

\tagpdfsetup{keyvals}

#keyvals:\tagpdfsetup
activate=%<tag%>
activate/all#true,false
activate/mc#true,false
activate/spaces#true,false
activate/struct#true,false
activate/struct-dest#true,false
activate/tagunmarked#true,false
activate/tree#true,false
role/mathml-tags#true,false
role/new-tag=%<tag/role%>
role/new-attribute={%<name%>}{%<content%>}
role/map-tags=#false,pdf
debug/show
debug/show=#para,paraOff,spaces,spacesOff
debug/log=#none,v,vv,vvv,all
debug/uncompress
viewer/pane/mathml#true,false
viewer/pane/mathsource#true,false
viewer/startstructure=%<number%>
page/tabsorder=#row,column,structure,none
page/exclude-header-footer=#false,pagination
para/tagging#true,false
para/tag=%<tag%>
para/maintag=%<tag%>
para/flattened#true,false
math/alt/use#true,false
math/mathml/write-dummy=%<code%>
math/mathml/sources=%<comma list%>
math/mathml/AF#true,false
math/tex/AF#true,false
table/tagging=
table/header-rows=%<comma list%>
text/lang=%<lang%>
#endkeyvals

\tagtool{keyvals}

#keyvals:\tagtool
para/tagging#true,false
para/maintag=%<tag%>
para/tag=%<tag%>
para/flattened#true,false
#endkeyvals

\tagmcbegin{keyvals}

#keyvals:\tagmcbegin
tag=%<tag%>
artifact=#pagination,pagination/header,pagination/footer,layout,page,background,notype
stash#true,false
label=%<name%>
alt=%<text%>
actualtext=%<text%>
raw=%<PDF code%>
#endkeyvals

\tagmcend
\tagmcuse
\tagmcifinTF{true code}{false code}

\tagstructbegin{keyvals}

#keyvals:\tagstructbegin
tag=%<tag%>
stash#true,false
label=%<name%>
parent=%<structure number%>
alt=%<text%>
actualtext=%<text%>
attribute={%<attr1,attr2,...%>}
attribute-class={%<attr1,attr2,...%>}
title=%<text%>
title-o=%<text%>
AF=%<object%>
root-AF=%<object%>
AFinline=%<text%>
AFinline-o=%<text%>
texsource=%<text%>
lang=%<lang id%>
ref=%<label1,label2,...%>}
E=%<text%>
#endkeyvals

\tagstructend
\tagstructuse{label}

\tagstop
\tagstart

\ShowTagging{keyvals}

#keyvals:\ShowTagging
mc-data=%<integer%>
mc-current
struct-stack=#log,show
debug/structures
#endkeyvals

# not documented
\tagpdfsuppressmarks{arg}#*
