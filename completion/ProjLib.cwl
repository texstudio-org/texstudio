# ProjLib package
# Matthew Bertucci 2022/04/04 for 2022/03/28 release

#include:l3keys2e
#include:projlib-language
#include:projlib-datetime
#include:projlib-draft
#include:projlib-font
#include:projlib-logo
#include:projlib-math
#include:projlib-paper
#include:projlib-theorem

#keyvals:\usepackage/ProjLib#c
author#true,false
amsfashion#true,false
titlepage#true,false
# options passed to projlib-language
English
French
German
Italian
Portuguese
Brazilian
Spanish
Chinese
TChinese
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
# options passed to projlib-datetime
plain
year-month-day
month-day-year
day-month-year
year-month
month-day
month-year
day-month
# options passed to projlib-paper
preview mode#true,false
paper style=#yellow,parchment,green,light-gray,gray,nord,dark
yellow paper#true,false
parchment paper#true,false
green paper#true,false
light gray paper#true,false
gray paper#true,false
nord paper#true,false
dark paper#true,false
# options passed to projlib-theorem
nothms#true,false
nothmnum#true,false
thmnum
thmnum=%<counter%>
theorem style=%<style%>
complex name#true,false
simple name#true,false
no preset names#true,false
#endkeyvals

#ifOption:author
#include:projlib-author
#endif
#ifOption:author=true
#include:projlib-author
#endif
#ifOption:authorblock
#include:projlib-author
#endif
#ifOption:authorblock=true
#include:projlib-author
#endif
#ifOption:author-block
#include:projlib-author
#endif
#ifOption:author-block=true
#include:projlib-author
#endif
#ifOption:author block
#include:projlib-author
#endif
#ifOption:author block=true
#include:projlib-author
#endif

#ifOption:amsfashion
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:amsfashion=true
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams-fashion
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams-fashion=true
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams fashion
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams fashion=true
#include:projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif

#ifOption:titlepage
#include:projlib-titlepage
#endif
#ifOption:titlepage=true
#include:projlib-titlepage
#endif
#ifOption:title-page
#include:projlib-titlepage
#endif
#ifOption:title-page=true
#include:projlib-titlepage
#endif
#ifOption:title page
#include:projlib-titlepage
#endif
#ifOption:title page=true
#include:projlib-titlepage
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

#ifOption:palatino
#include:mathpazo
#include:newpxtext
#endif
#ifOption:palatino=true
#include:mathpazo
#include:newpxtext
#endif

#ifOption:times
#include:newtxtext
#include:newtxmath
#endif
#ifOption:times=true
#include:newtxtext
#include:newtxmath
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
#include:biolinum
#include:mathastext
#endif
#ifOption:biolinum=true
#include:eulervm
#include:biolinum
#include:mathastext
#endif

#ifOption:Japanese
\captionsjapanese#*
\datejapanese#*
\extrasjapanese#*
\noextrasjapanese#*
#endif

#ifOption:Russian
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
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
#endif
