# zref-clever package
# Matthew Bertucci 2/8/2022 for v0.2.1-alpha

#include:zref-base
#include:zref-user
#include:zref-abspage
#include:l3keys2e
#include:ifdraft
#include:zref-hyperref
#ifOption:titleref
#include:zref-titleref
#endif
#ifOption:vario
#include:zref-vario
#endif
#ifOption:check
#include:zref-check
#endif

\zcref{labellist}#r
\zcref[options%keyvals]{labellist}#r
\zcref*{labellist}#r
\zcref*[options%keyvals]{labellist}#r

\zcpageref{labellist}#r
\zcpageref[options%keyvals]{labellist}#r
\zcpageref*{labellist}#r
\zcpageref*[options%keyvals]{labellist}#r

\zcsetup{options%keyvals}

#keyvals:\zcref,\zcref*,\zcpageref,\zcpageref*,\zcsetup,\usepackage/zref-clever#c
ref=#default,page,thecounter,title
page
typeset=#ref,name,both
noname
noref
sort#true,false
nosort
typesort={%<type list%>}
notypesort
comp#true,false
nocomp
endrange=#ref,stripprefix,pagecomp,pagecomp2
range#true,false
rangetopair#true,false
cap#true,false
nocap
capfirst
abbrev#true,false
noabbrev
noabbrevfirst
S
hyperref=#auto,true,false
nameinlink=#true,false,single,tsingle
preposinlink#true,false
lang=%<language%>
d=%<declension case%>
nudge=#true,false,ifdraft,iffinal
nudgeif=#multitype,comptosing,gender,all
nonudge
sg
g=
font=%<cmds%>
titleref
vario
note=%<text%>
check={%<checks%>}
countertype={%<<counter>%> = %<<type> list%>}
counterresetters={%<counter list%>}
counterresetby={%<<counter=encl counter> list%>}
currentcounter
#endkeyvals

#keyvals:\zcsetup,\usepackage/zref-clever#c
currentcounter=%<counter%>
nocompat={%<module list%>}
#endkeyvals

#keyvals:\zcref,\zcref*,\zcpageref,\zcpageref*,\zcsetup
check={%<checks%>}
tpairsep=
tlistsep=
tlastsep=
notesep=
namesep=
pairsep=
listsep=
lastsep=
rangesep=
preref=
postref=
namefont=
reffont=
#endkeyvals

#keyvals:\zcsetup,\usepackage/zref-clever#c
check
#endkeyvals

\zcRefTypeSetup{type}{options%keyvals}

#keyvals:\zcRefTypeSetup
namesep=
pairsep=
listsep=
lastsep=
rangesep=
preref=
postref=
Name-sg=
name-sg=
Name-pl=
name-pl=
Name-sg-ab=
name-sg-ab=
Name-pl-ab=
name-pl-ab=
namefont=
reffont=
cap#true,false
abbrev#true,false
endrange=#ref,stripprefix,pagecomp,pagecomp2
rangetopair#true,false
#endkeyvals

\zcDeclareLanguage{language}
\zcDeclareLanguage[options%keyvals]{language}

#keyvals:\zcDeclareLanguage
declension={%<cases list%>}
gender={%<gender list%>}
allcaps
#endkeyvals

\zcDeclareLanguageAlias{language alias}{aliased language}

\zcLanguageSetup{language}{options%keyvals}

#keyvals:\zcLanguageSetup#c
tpairsep=
tlistsep=
tlastsep=
notesep=
namesep=
pairsep=
listsep=
lastsep=
rangesep=
preref=
postref=
type=%<type%>
case=#N,A,D,G
gender={%<gender list%>}
Name-sg=
name-sg=
Name-pl=
name-pl=
Name-sg-ab=
name-sg-ab=
Name-pl-ab=
name-pl-ab=
cap#true,false
abbrev#true,false
#endkeyvals
