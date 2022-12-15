# iodhbwm class
# Matthew Bertucci 2022/07/02 for v1.2.2

#include:etoolbox
#include:pgfopts
#include:scrlfile
#include:xstring
#include:class-scrreprt
#include:babel
#include:csquotes
#include:lmodern
#include:microtype
#include:scrhack
#include:setspace
#include:mathtools
#include:graphicx
#include:tcolorbox
#include:tcolorboxlibrarymost
#include:tabularx
#include:booktabs
#include:xcolor
# loads table and dvipsnames options of xcolor
#include:geometry
#include:scrlayer-scrpage
#include:siunitx
#include:cleveref
#include:hyperref
#include:auxhook
#include:caption

#keyvals:\documentclass/iodhbwm#c
load-preamble#true,false
load-dhbw-templates#true,false
add-tocs-to-toc#true,false
language=%<language%>
mainlanguage=%<language%>
print-#true,false
print
auto-intro-pages=#none,custom,default,all
add-bibliography#true,false
add-bibliography-
bib-file=%<bib file%>
biblatex/style=%<style%>
biblatex/bibstyle=%<bibstyle%>
biblatex/citestyle=%<citestyle%>
debug#true,false
#endkeyvals

#ifOption:language=english
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif
#ifOption:mainlanguage=english
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

#ifOption:language=ngerman
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif
#ifOption:mainlanguage=ngerman
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:load-dhbw-templates
#include:iodhbwm-templates
#endif
#ifOption:load-dhbw-templates=true
#include:iodhbwm-templates
#endif

#ifOption:add-bibliography
#include:biblatex
#endif
#ifOption:add-bibliography=true
#include:biblatex
#endif
#ifOption:add-bibliography-
#include:biblatex
#endif

#ifOption:debug
#include:blindtext
#include:lipsum
#endif
#ifOption:debug=true
#include:blindtext
#include:lipsum
#endif

DHBW-red#B
DHBW-blue#B
DHBW-darkblue#B
DHBW-light#B
DHBW-light-gray#B
DHBW-font#B
DHBW-dark-font#B

# from table option of xcolor
#include:colortbl

# from dvipsnames option of xcolor
Apricot#B
Aquamarine#B
Bittersweet#B
Black#B
Blue#B
BlueGreen#B
BlueViolet#B
BrickRed#B
Brown#B
BurntOrange#B
CadetBlue#B
CarnationPink#B
Cerulean#B
CornflowerBlue#B
Cyan#B
Dandelion#B
DarkOrchid#B
Emerald#B
ForestGreen#B
Fuchsia#B
Goldenrod#B
Gray#B
Green#B
GreenYellow#B
JungleGreen#B
Lavender#B
LimeGreen#B
Magenta#B
Mahogany#B
Maroon#B
Melon#B
MidnightBlue#B
Mulberry#B
NavyBlue#B
OliveGreen#B
Orange#B
OrangeRed#B
Orchid#B
Peach#B
Periwinkle#B
PineGreen#B
Plum#B
ProcessBlue#B
Purple#B
RawSienna#B
Red#B
RedOrange#B
RedViolet#B
Rhodamine#B
RoyalBlue#B
RoyalPurple#B
RubineRed#B
Salmon#B
SeaGreen#B
Sepia#B
SkyBlue#B
SpringGreen#B
Tan#B
TealBlue#B
Thistle#B
Turquoise#B
Violet#B
VioletRed#B
White#B
WildStrawberry#B
Yellow#B
YellowGreen#B
YellowOrange#B
