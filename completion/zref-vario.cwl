# zref-vario package
# Matthew Bertucci 2/7/2022 for v0.1.1-alpha

#include:varioref
#include:zref-clever

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