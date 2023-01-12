# luatexja-preset package
# Matthew Bertucci 2022/07/04 for v20220703.0

#include:expl3
#include:l3keys2e
#include:luatexja
#include:luatexja-fontspec

#keyvals:\usepackage/luatexja-preset#c
fontspec
nfssonly
nodeluxe
deluxe
expert
bold
jis90
jis2004
jfm_yoko=%<jfm%>
jfm_tate=%<jfm%>
jis
kozuka-pro
kozuka-pr6
kozuka-pr6n
hiragino-pro
hiragino-pron
bizud
morisawa-pro
morisawa-pr6n
yu-win
yu-win10
yu-osx
moga-mobo
moga-mobo-ex
ume
sourcehan
sourcehan-jp
noto-otc
noto-otf
noto-jp
haranoaji
noembed
ipa
ipaex
ms
ipa-hg
ipaex-hg
ms-hg
# options passed to luatexja-fontspec
match
scale=%<factor%>
# options passed to fontspec
tuenc
euenc
math
no-math
config
no-config
quiet
silent
#endkeyvals

#ifOption:deluxe
\ebdefault#*
\ebseries
\gtebfamily
\ltdefault#*
\ltseries
\mgfamily
\texteb{text}
\textlt{text}
\textmg{text}
#endif

#ifOption:expert
\rubyfamily
#endif

\ltjnewpreset{name%specialDef}{specification%keyvals}#s#%luatexjapreset
\ltjnewpreset*{name%specialDef}{specification%keyvals}#s#%luatexjapreset
\ltjapplypreset{name%keyvals}

#keyvals:\ltjnewpreset#c,\ltjnewpreset*#c
mc-l=%<font%>
mc-m=%<font%>
mc-b=%<font%>
mc-bx=%<font%>
gt-m=%<font%>
gt-b=%<font%>
gt-bx=%<font%>
gt-eb=%<font%>
mg-m=%<font%>
mc=%<font%>
gt=%<font%>
#endkeyvals

#keyvals:\ltjnewpreset#c,\ltjnewpreset*#c,\ltjapplypreset#c
%luatexjapreset
# general presets
kozuka-pro
kozuka-pr6
kozuka-pr6n
hiragino-pro
hiragino-pron
bizud
morisawa-pro
morisawa-pr6n
yu-win
yu-win10
yu-osx
moga-mobo
moga-mobo-ex
ume
sourcehan
sourcehan-jp
noto-otc
noto-otf
haranoaji
noembed
ipa
ipaex
ms
ipa-hg
ipaex-hg
ms-hg
#endkeyvals
