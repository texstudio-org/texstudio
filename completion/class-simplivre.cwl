# simplivre class
# Matthew Bertucci 2023/07/14

#include:class-book
#include:silence
#include:geometry
#include:minimalist
#include:projlib-font
#include:fontspec
#include:ctex
#include:unicode-math
#include:tikz-cd
#include:nowidow
#include:embrac
#include:graphicx
#include:wrapfig
#include:float
#include:caption

#keyvals:\documentclass/simplivre#c
draft
fast
classical
useindent
a4paper
b5paper
oneside
twoside
11pt
12pt
# options passed to minimalist package
title in boldface#true,false
title in scshape#true,false
runin#true,false
nothms#true,false
nothmnum#true,false
thmnum
thmnum=%<counter%>
theorem style=%<style%>
complex name#true,false
simple name#true,false
no preset names#true,false
regionalref#true,false
originalref#true,false
Chinese
TChinese
English
German
Italian
Portuguese
Brazilian
Spanish
Japanese
Russian
# options passed to projlib-font
useosf
lmodern
palatino
times
garamond
noto
biolinum
#endkeyvals

#ifOption:draft
#include:draftwatermark
#endif
#ifOption:draft=true
#include:draftwatermark
#endif
#ifOption:fast
#include:draftwatermark
#endif
#ifOption:fast=true
#include:draftwatermark
#endif

#ifOption:classical
\desculine#*
\seculine#*
\simpleqedsymbol#*
\subseculine#*
#endif
#ifOption:classical=true
\desculine#*
\seculine#*
\simpleqedsymbol#*
\subseculine#*
#endif

#ifOption:useindent=false
#include:parskip
#endif

#ifOption:lmodern
#include:amssymb
#include:lmodern
#endif
#ifOption:lmodern=true
#include:amssymb
#include:lmodern
#endif
#ifOption:latin-modern
#include:amssymb
#include:lmodern
#endif
#ifOption:latin-modern=true
#include:amssymb
#include:lmodern
#endif
#ifOption:latin modern
#include:amssymb
#include:lmodern
#endif
#ifOption:latin modern=true
#include:amssymb
#include:lmodern
#endif

#ifOption:garamond
#include:newtxmath
#include:ebgaramond-maths
#include:ebgaramond
#endif
#ifOption:garamond=true
#include:newtxmath
#include:ebgaramond-maths
#include:ebgaramond
#endif

#ifOption:noto
#include:anyfontsize
#include:notomath
#endif
#ifOption:noto=true
#include:anyfontsize
#include:notomath
#endif

#ifOption:biolinum
#include:eulervm
#include:mathastext
#endif
#ifOption:biolinum=true
#include:eulervm
#include:mathastext
#endif

\xlongequal{sup}#m
\xlongequal[sub]{sup}#m
\xtwoheadrightarrow{sup}#m
\xtwoheadrightarrow[sub]{sup}#m
\xtwoheadleftarrow{sup}#m
\xtwoheadleftarrow[sub]{sup}#m
\xrightrightarrows{arg}#m
\xrightrightarrows[opt]{arg}#m
\xleftleftarrows{arg}#m
\xleftleftarrows[opt]{arg}#m

\IfPrintModeTF{true-code}{false-code}#*
\IfPrintModeT{true-code}#*
\IfPrintModeF{false-code}#*

\limstrut#*
\standarddashv#S
\standardvdash#S
\raisesymbol{arg1}{arg2}#*

# from japanese option of babel (autoloaded)
\captionsjapanese#*
\datejapanese#*
\extrasjapanese#*
\noextrasjapanese#*

# from russian option of babel (autoloaded)
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#*m
\ch#*m
\tg#*m
\ctg#*m
\arctg#*m
\arcctg#*m
\th#*m
\cth#*m
\cosec#*m
\Prob#*m
\Variance#*m
\NOD#*m
\nod#*m
\NOK#*m
\nok#*m
\Proj#*m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsrussian#*
\daterussian#*
\extrasrussian#*
\noextrasrussian#*
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\tocname#*
\authorname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
