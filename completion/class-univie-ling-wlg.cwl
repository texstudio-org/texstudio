# univie-ling-wlg class
# Matthew Bertucci 2023/01/27 for v.2.2

#include:class-scrartcl
#include:cochineal
#include:sourcesanspro
#include:DejaVuSansMono
#include:url
#include:microtype
#include:scalefnt
#include:textcase
#include:ragged2e
#include:translator
#include:doclicense
#include:etoc
#include:scrlayer-scrpage
#include:csquotes
#include:totpages
#include:refcount
#include:xcolor
#include:graphicx
#include:hyperref
#include:pdfpages
#include:enumitem
#include:covington
#include:caption
#include:booktabs
#include:multirow
#include:varioref
#include:prettyref

#keyvals:\documentclass/univie-ling-wlg#c
biblatex#true,false
covington#true,false
expertfonts#true,false
titlepage=#none,specialprint,issue
preprint#true,false
peerrev#true,false
type=#paper,review
draftmark=#true,false,firstpage
#endkeyvals

#ifOption:biblatex
#include:biblatex
# loads style=univie-ling option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
issueeditor#true,false
#endkeyvals
\mkbibdateunified{arg1}{arg2}{arg3}#*
#endif
#ifOption:biblatex=true
#include:biblatex
# loads style=univie-ling option of biblatex
#keyvals:\usepackage/biblatex#c,\ExecuteBibliographyOptions#c
issueeditor#true,false
#endkeyvals
\mkbibdateunified{arg1}{arg2}{arg3}#*
#endif

#ifOption:expertfonts
#include:MinionPro
#include:MyriadPro
#endif
#ifOption:expertfonts=true
#include:MinionPro
#include:MyriadPro
#endif

#ifOption:draftmark
#include:draftwatermark
#endif
#ifOption:draftmark=true
#include:draftwatermark
#endif
#ifOption:draftmark=firstpage
#include:draftwatermark
#endif

\aff*[m|f]{affiliation%text}
\aff*{affiliation%text}
\aff[m|f]{affiliation%text}
\aff{affiliation%text}
\AfterInputencOrAtEndPreamble{code}#*
\author[short names]{names}
\backmatter
\computelastpage#*
\Concept{text}
\condbreak{length}#*
\edboardAL{name}
\edboardGL{name}
\edboardHL{name}
\Expression{text}
\footnumwidth#*
\frontmatter
\impressum#*
\includefinalpaper[options%keyvals]{file}#i
\includefinalpaper{file}#i
\issue{number}{year}
\issueeditors{names}
\issuesubtitle{text}
\issuetitle{text}
\keywords{word1,word2,...%text}
\lastpageref#*
\ljobname#*
\mainmatter
\makeissuetitle
\maxfn#*
\Meaning{text}
\motto[source]{text}
\motto{text}
\olddots#S
\startpage{number}
\startpageref#*
\techboard{name}
\thestartpage#*
\title[short title%text]{text}
\urlprefix#*
\versal{text}
\wlgurl#*

#keyvals:\includefinalpaper
author=%<name%>
title=%<text%>
subtitle=%<text%>
#endkeyvals
