# bxcjkjatype package
# Matthew Bertucci 2022/07/17 for v0.3

#include:keyval
#include:CJK
#include:CJKutf8
#include:CJKspace
#include:CJKpunct
#include:etoolbox

#keyvals:\usepackage/bxcjkjatype#c
whole
wholeCJK*
wholeCJK
nowhole
everypage
noeverypage
ipaex-type1
oneweight
nooneweight
autotilde
noautotilde
CJKpunct
noCJKpunct
CJKspace
noCJKspace
boldbyembolden
noboldbyembolden
substmingoth
nosubstmingoth
ms
ipa
ipaex
ms-hg
ipa-hg
moga-mobo
moga-maruberi
kozuka-pro
kozuka-pr6
kozuka-pr6n
hiragino-pro
hiragino-pron
morisawa-pro
morisawa-pr6n
scale=%<factor%>
vertical=#none,false,sub,main,true
ttfname=%<pattern%>
#endkeyvals

#ifOption:vertical=sub
#include:CJKvert
#endif
#ifOption:vertical=main
#include:CJKvert
#endif
#ifOption:vertical=true
#include:CJKvert
#endif

\setminchofont{font-file}
\setminchofont[id]{font-file}
\setgothicfont{font-file}
\setgothicfont[id]{font-file}
\setmarugothicfont{font-file}
\setmarugothicfont[id]{font-file}
\setmediumminchofont{font-file}
\setmediumminchofont[id]{font-file}
\setboldminchofont{font-file}
\setboldminchofont[id]{font-file}
\setmediumgothicfont{font-file}
\setmediumgothicfont[id]{font-file}
\setboldgothicfont{font-file}
\setboldgothicfont[id]{font-file}
\setxboldgothicfont{font-file}
\setxboldgothicfont[id]{font-file}
\setoneweightgothicfont{font-file}
\setoneweightgothicfont[id]{font-file}

\begin{uCJK}
\end{uCJK}
\begin{uCJK*}
\end{uCJK*}

\setCJKfamilydefault{family}
\CJKecglue
\>#*
\UTF{hex-number}
\CJKforce{characters}
\CJKunforce{characters}

\mcdefault#*
\gtdefault#*
\mgdefault#*
\mcfamily
\gtfamily
\mgfamily

\CJKboldbyembolden
\CJKnoboldbyembolden

# not functional
\setlightminchofont{font-file}#*
\setlightminchofont[id]{font-file}#*

# not documented
\bxcjkjatypeHyperrefPatchDone#*
\CJKforced{character}#*
\ebdefault#*
\ebseries#*
\Entry{arg1}{arg2}#S
\EveryCJKUse{code}#*
\FirstCJKUse{code}#*
\FONT#S
\unicode#S
\usecmapforalphabet#*