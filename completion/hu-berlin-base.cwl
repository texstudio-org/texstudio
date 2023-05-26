# hu-berlin-base package
# Matthew Bertucci 2023/05/21 for v1.1.2

#include:luatex
#include:ifluatex
#include:babel
# loads english and ngerman options of babel
#include:graphicx
#include:fontspec
#include:marvosym
#include:xcolor

hu-berlin-blue#B
hu-berlin-green#B
hu-berlin-grey#B
hu-berlin-brown#B
hu-berlin-red#B

\Version#S

# from ngerman option of babel
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

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#S
\britishhyphenmins#S
\americanhyphenmins#S