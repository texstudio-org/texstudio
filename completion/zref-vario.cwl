# zref-vario package
# Matthew Bertucci 2023/01/01 for v0.1.6

#include:varioref
#include:zref-clever

\zvsetup{options%keyvals}

#keyvals:\zvsetup
pageprop=%<property%>
#endkeyvals

\zvref{label}#r
\zvref[options%keyvals]{label}#r
\zvref*{label}#r
\zvref*[options%keyvals]{label}#r

\zvpageref{label}#r
\zvpageref[options%keyvals]{label}#r
\zvpageref*{label}#r
\zvpageref*[options%keyvals]{label}#r

\zvrefrange{fromlabel%ref}{tolabel%ref}
\zvrefrange[options%keyvals]{fromlabel%ref}{tolabel%ref}
\zvrefrange*{fromlabel%ref}{tolabel%ref}
\zvrefrange*[options%keyvals]{fromlabel%ref}{tolabel%ref}

\zvpagerefrange{fromlabel%ref}{tolabel%ref}
\zvpagerefrange[options%keyvals]{fromlabel%ref}{tolabel%ref}
\zvpagerefrange*{fromlabel%ref}{tolabel%ref}
\zvpagerefrange*[options%keyvals]{fromlabel%ref}{tolabel%ref}

\zfullref{label}#r
\zfullref[options%keyvals]{label}#r
\zfullref*{label}#r
\zfullref*[options%keyvals]{label}#r

\zreftextfaraway{label}#*r
\zreftextfaraway[options%keyvals]{label}#*r
\zreftextfaraway*{label}#*r
\zreftextfaraway*[options%keyvals]{label}#*r

#keyvals:\zvref,\zvref*,\zvpageref,\zvpageref*,\zvrefrange,\zvrefrange*,\zvpagerefrange,\zvpagerefrange*,\zfullref,\zfullref*,\zreftextfaraway,\zreftextfaraway*
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
d=%<declension case%>
nudge=#true,false,ifdraft,iffinal
nudgeif=#multitype,comptosing,gender,all
nonudge
sg
g=
font=%<font commands%>
note=%<text%>
check={%<checks%>}
vcheck={%<checks%>}
countertype={%<<counter>%> = %<<type> list%>}
counterresetters={%<counter list%>}
counterresetby={%<<counter=encl counter> list%>}
currentcounter=%<counter%>
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
#endkeyvals

#keyvals:\zvref,\zvref*,\zvpageref,\zvpageref*,\zvrefrange,\zvrefrange*,\zvpagerefrange,\zvpagerefrange*
vcurrent
vother
#endkeyvals

\zvLanguageSetup{language}{options%keyvals}

#keyvals:\zvLanguageSetup
reftextfaceafter=
reftextfacebefore=
reftextafter=
reftextbefore=
reftextcurrent=
reftextfaraway=
reftextpagerange=
reftextlabelrange=
vrefformat=
vrefrangeformat=
fullrefformat=
#endkeyvals

\zvhyperlink{text}
