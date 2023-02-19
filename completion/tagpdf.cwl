# tagpdf package
# Matthew Bertucci 2023/02/15 for v0.98d

#include:pdfmanagement-testphase

#keyvals:\usepackage/tagpdf#c
luamode
genericmode
#endkeyvals

\tagpdfsetup{keyvals}

#keyvals:\tagpdfsetup
activate-all#true,false
activate=%<tag%>
activate-mc#true,false
activate-struct#true,false
no-struct-dest#true,false
activate-tree#true,false
add-new-tag=%<tag/role%>
add-new-tag={%<keyvals%>}
interwordspace=#true,on,false,off
log=#none,v,vv,vvv,all
newattribute={%<name%>}{%<content%>}
show-spaces#true,false
paratagging#true,false
paratagging-show#true,false
paratag=%<string%>
tabsorder=#row,column,structure,none
tagunmarked#true,false
uncompress
#endkeyvals

\tagtool{keyvals}

#keyvals:\tagtool
para#true,false
paratag=%<string%>
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
\tagpdfparaOn
\tagpdfparaOff

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

\ShowTagging{keyvals}

#keyvals:\ShowTagging
mc-data=%<integer%>
mc-current
struct-stack=#log,show
#endkeyvals

# not documented
\tagpdfsuppressmarks{arg}#*
