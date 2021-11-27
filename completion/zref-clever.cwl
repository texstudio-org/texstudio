# zref-clever package
# Matthew Bertucci 11/26/2021 for v0.1.0-alpha

#include:zref-base
#include:zref-user
#include:zref-abspage
#include:l3keys2e
#include:ifdraft
#include:zref-hyperref
#ifOption:titleref
#include:zref-titleref
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
range#true,false
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
refpre=
refpos=
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
refpre=
refpos=
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
refpre=
refpos=
type=%<type%>
case=#N,A,D,G
gender=#f,m,n
Name-sg=
name-sg=
Name-pl=
name-pl=
Name-sg-ab=
name-sg-ab=
Name-pl-ab=
name-pl-ab=
#endkeyvals
