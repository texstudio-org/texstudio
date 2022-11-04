# hep-paper package
# Matthew Bertucci 2022/11/03 for v2.1

#include:kvoptions
#include:hep-font
#include:hep-math-font
#include:geometry
#include:hep-text
#include:hep-math
#include:hep-float
#include:hep-title
#include:pdftexcmds
#include:hep-bibliography
#include:hep-reference
#include:hep-acronym

#keyvals:\usepackage/hep-paper#c
paper=#a0,a1,a2,a3,a4,a5,a6,b0,b1,b2,b3,b4,b5,b6,c0,c1,c2,c3,c4,c5,c6,ansia,ansib,ansic,ansid,ansie,letter,executive,legal
font=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt
lang=%<language%>
serif#true,false
sansserif#true,false
lining#true,false
oldstyle#true,false
parindent#true,false
parskip#true,false
symbols=#ams,true,minion,false
defaults#true,false
title#true,false
physics#true,false
style=#authoryear,authortitle,alphabetic,numeric,alphabetic-verb,authortitle-comp,authortitle-ibid,authortitle-icomp,authortitle-tcomp,authortitle-terse,authortitle-ticomp,authoryear-comp,authoryear-ibid,authoryear-icomp,debug,draft,numeric-comp,numeric-verb,reading,verbose,verbose-ibid,verbose-inote,verbose-note,verbose-trad1,verbose-trad2,verbose-trad3
glossaries#true,false
references#true,false
beamer#true,false
revtex#true,false
jhep#true,false
jcap#true,false
pos#true,false
springer#true,false
amsart#true,false
eqnarray#true,false
manualplacement#true,false
#endkeyvals

#ifOption:parskip
#include:parskip
\useparskip
\useparindent
#endif
#ifOption:parskip=true
#include:parskip
\useparskip
\useparindent
#endif

#ifOption:revtex
#include:ragged2e
#endif
#ifOption:revtex=true
#include:ragged2e
#endif

#ifOption:amsart
#include:xpatch
#endif
#ifOption:amsart=true
#include:xpatch
#endif