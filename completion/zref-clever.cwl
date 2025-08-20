# zref-clever package
# Matthew Bertucci 2025/08/11 for v0.5.1

#include:zref-base
#include:zref-user
#include:zref-abspage
#include:ifdraft
#include:zref-hyperref

\zcref{labellist}#r
\zcref[options%keyvals]{labellist}#r
\zcref*{labellist}#r
\zcref*[options%keyvals]{labellist}#r

\zcpageref{labellist}#r
\zcpageref[options%keyvals]{labellist}#r
\zcpageref*{labellist}#r
\zcpageref*[options%keyvals]{labellist}#r

\zcsetup{options%keyvals}

#keyvals:\zcref,\zcref*,\zcpageref,\zcpageref*,\zcsetup
# standard keys
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
capfirst#true,false
abbrev#true,false
noabbrev
noabbrevfirst
S
hyperref=#auto,true,false
nameinlink=#true,false,single,tsingle
lang=%<language%>
v=%<variant%>
nudge=#true,false,ifdraft,iffinal
nudgeif=#multitype,comptosing,gender,all
nonudge
sg
g=
font=%<font commands%>
note=%<text%>
check={%<checks%>}
countertype={%<<counter>%> = %<<type> list%>}
reftype=%<type%>
counterresetters={%<counter list%>}
counterresetby={%<<counter=encl counter> list%>}
currentcounter=%<counter%>
labelhook#true,false
# "general" keys
tpairsep={%<separator%>}
tlistsep={%<separator%>}
tlastsep={%<separator%>}
notesep={%<separator%>}
namesep={%<separator%>}
pairsep={%<separator%>}
listsep={%<separator%>}
lastsep={%<separator%>}
rangesep={%<separator%>}
refbounds={%<preref*,preref,postref,postref*%>}
namefont=%<name%>
reffont=%<name%>
refbounds-first={%<preref*,preref,postref,postref*%>}
refbounds-first-sg={%<preref*,preref,postref,postref*%>}
refbounds-first-pb={%<preref*,preref,postref,postref*%>}
refbounds-first-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid={%<preref*,preref,postref,postref*%>}
refbounds-mid-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid-re={%<preref*,preref,postref,postref*%>}
refbounds-last={%<preref*,preref,postref,postref*%>}
refbounds-last-pe={%<preref*,preref,postref,postref*%>}
refbounds-last-re={%<preref*,preref,postref,postref*%>}
+refbounds-first={%<preref*,preref,postref,postref*%>}
+refbounds-mid={%<preref*,preref,postref,postref*%>}
+refbounds-last={%<preref*,preref,postref,postref*%>}
+refbounds-rb={%<preref*,preref,postref,postref*%>}
+refbounds-re={%<preref*,preref,postref,postref*%>}
+refbounds={%<preref*,preref,postref,postref*%>}
#endkeyvals

#keyvals:\zcsetup
# preamble-only keys
nocompat
nocompat={%<module list%>}
#endkeyvals

\zcRefTypeSetup{type}{options%keyvals}

#keyvals:\zcRefTypeSetup
namesep={%<separator%>}
pairsep={%<separator%>}
listsep={%<separator%>}
lastsep={%<separator%>}
rangesep={%<separator%>}
refbounds={%<preref*,preref,postref,postref*%>}
Name-sg=%<name%>
name-sg=%<name%>
Name-pl=%<name%>
name-pl=%<name%>
Name-sg-ab=%<name%>
name-sg-ab=%<name%>
Name-pl-ab=%<name%>
name-pl-ab=%<name%>
namefont=%<font commands%>
reffont=%<font commands%>
cap#true,false
abbrev#true,false
endrange=#ref,stripprefix,pagecomp,pagecomp2
rangetopair#true,false
refbounds-first={%<preref*,preref,postref,postref*%>}
refbounds-first-sg={%<preref*,preref,postref,postref*%>}
refbounds-first-pb={%<preref*,preref,postref,postref*%>}
refbounds-first-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid={%<preref*,preref,postref,postref*%>}
refbounds-mid-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid-re={%<preref*,preref,postref,postref*%>}
refbounds-last={%<preref*,preref,postref,postref*%>}
refbounds-last-pe={%<preref*,preref,postref,postref*%>}
refbounds-last-re={%<preref*,preref,postref,postref*%>}
+refbounds-first={%<preref*,preref,postref,postref*%>}
+refbounds-mid={%<preref*,preref,postref,postref*%>}
+refbounds-last={%<preref*,preref,postref,postref*%>}
+refbounds-rb={%<preref*,preref,postref,postref*%>}
+refbounds-re={%<preref*,preref,postref,postref*%>}
+refbounds={%<preref*,preref,postref,postref*%>}
#endkeyvals

\zcDeclareLanguage{language}
\zcDeclareLanguage[options%keyvals]{language}

#keyvals:\zcDeclareLanguage
variants={%<variant list%>}
gender={%<gender list%>}
allcaps
#endkeyvals

\zcDeclareLanguageAlias{language alias}{aliased language}

\zcLanguageSetup{language}{options%keyvals}

#keyvals:\zcLanguageSetup
tpairsep={%<separator%>}
tlistsep={%<separator%>}
tlastsep={%<separator%>}
notesep={%<separator%>}
namesep={%<separator%>}
pairsep={%<separator%>}
listsep={%<separator%>}
lastsep={%<separator%>}
rangesep={%<separator%>}
refbounds={%<preref*,preref,postref,postref*%>}
Name-sg=%<name%>
name-sg=%<name%>
Name-pl=%<name%>
name-pl=%<name%>
Name-sg-ab=%<name%>
name-sg-ab=%<name%>
Name-pl-ab=%<name%>
name-pl-ab=%<name%>
namefont=%<font commands%>
reffont=%<font commands%>
cap#true,false
abbrev#true,false
endrange=#ref,stripprefix,pagecomp,pagecomp2
rangetopair#true,false
refbounds-first={%<preref*,preref,postref,postref*%>}
refbounds-first-sg={%<preref*,preref,postref,postref*%>}
refbounds-first-pb={%<preref*,preref,postref,postref*%>}
refbounds-first-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid={%<preref*,preref,postref,postref*%>}
refbounds-mid-rb={%<preref*,preref,postref,postref*%>}
refbounds-mid-re={%<preref*,preref,postref,postref*%>}
refbounds-last={%<preref*,preref,postref,postref*%>}
refbounds-last-pe={%<preref*,preref,postref,postref*%>}
refbounds-last-re={%<preref*,preref,postref,postref*%>}
+refbounds-first={%<preref*,preref,postref,postref*%>}
+refbounds-mid={%<preref*,preref,postref,postref*%>}
+refbounds-last={%<preref*,preref,postref,postref*%>}
+refbounds-rb={%<preref*,preref,postref,postref*%>}
+refbounds-re={%<preref*,preref,postref,postref*%>}
+refbounds={%<preref*,preref,postref,postref*%>}
# language-specific keys
type=%<type%>
variant=#N,A,D,G
gender={%<gender list%>}
#endkeyvals

