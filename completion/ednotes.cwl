# ednotes package
# Matthew Bertucci 2022/05/21 for v1.3a

#include:manyfoot
#include:lineno

#keyvals:\usepackage/ednotes#c
Aplain
Bpara
Bplain
Cpara
Cplain
Dpara
Dplain
Epara
Eplain
edmacpara
countoccurrences
para*
perpage
mathnotes
# options passed to lineno
addpageno
edtable
longtable
nolongtablepatch
left
right
switch
switch*
columnwise
pagewise
running
modulo
modulo*
mathlines
#endkeyvals

#ifOption:Bpara
\FootnotetextB{marker}{text}
\footinsB#*
\Bnote{lemma%text}{note%text}
\Bnotelabel{label}#l
#endif

#ifOption:Bplain
\FootnotetextB{marker}{text}
\footinsB#*
\Bnote{lemma%text}{note%text}
\Bnotelabel{label}#l
#endif

#ifOption:Cpara
\FootnotetextC{marker}{text}
\footinsC#*
\Cnote{lemma%text}{note%text}
\Cnotelabel{label}#l
#endif

#ifOption:Cplain
\FootnotetextC{marker}{text}
\footinsC#*
\Cnote{lemma%text}{note%text}
\Cnotelabel{label}#l
#endif

#ifOption:Dpara
\FootnotetextD{marker}{text}
\footinsD#*
\Dnote{lemma%text}{note%text}
\Dnotelabel{label}#l
#endif

#ifOption:Dplain
\FootnotetextD{marker}{text}
\footinsD#*
\Dnote{lemma%text}{note%text}
\Dnotelabel{label}#l
#endif

#ifOption:Epara
\FootnotetextE{marker}{text}
\footinsE#*
\Enote{lemma%text}{note%text}
\Enotelabel{label}#l
#endif

#ifOption:Eplain
\FootnotetextE{marker}{text}
\footinsE#*
\Enote{lemma%text}{note%text}
\Enotelabel{label}#l
#endif

#ifOption:edmacpara
#include:mfparptc
#endif

#ifOption:countoccurrences
#include:edcntwd0
#endif

#ifOption:perpage
#include:perpage
#endif

#ifOption:mathnotes
#include:ednmath0
#endif

# from options passed to lineno
#ifOption:addpageno
#include:vplref
#endif

#ifOption:mathrefs
#include:ednmath0
#endif

#ifOption:edtable
#include:edtable
#endif

#ifOption:longtable
#include:edtable
#include:longtable
#include:ltabptch
#endif

#ifOption:nolongtablepatch
#include:edtable
#include:longtable
#endif

# package commands
\FootnotetextA{marker}{text}
\footinsA#*
\Anote{lemma%text}{note%text}
\Anotelabel{label}#l
\donote{label}{note%text}#r
\<#S
\>#S
\pause{label%specialDef}#s#%pauselabel
\pause{label}<ellipsis>
\resume{label%keyvals}
#keyvals:\resume#c
%pauselabel
#endkeyvals
\textsymmdots
\lemmaellipsis
\notinnote{code%text}
\addlemmaexpands{code}
\IfLemmaTag{in lemma tag%text}{in main text%text}
\nopunct#*
\linesfmt{text}#*
\showlemmaexpands
\sameline{text}#*
\differentlines{text1}{text2}#*
\pageandline{text1}{text2}#*
\repeatref{text}#*
\lemmafmt{text}#*
\notefmt{text}#*
\PrecedeLevelWith{level}{code%text}
\IfTypesetting{for typesetting%text}{for expanding%text}
\RobustTestOpt
\NewEdnotesCommand{cmd}[args][default]{def}#d
\NewEdnotesCommand{cmd}[args]{def}#d
\NewEdnotesCommand{cmd}{def}#d
\NewEdnotesCommand*{cmd}[args][default]{def}#d
\NewEdnotesCommand*{cmd}[args]{def}#d
\NewEdnotesCommand*{cmd}{def}#d
\warningpagebreak#*