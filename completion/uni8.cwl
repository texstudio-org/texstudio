# uni8 package
# Matthew Bertucci 1/28/2022 for v0.03

#keyvals:\usepackage/uni8#c
fontspec
fontspec=#yes,no
inputenc=#utf8,utf8x,latin1,latin2
font=#cm,times,old-times
#endkeyvals

#include:inputenc
#include:lmodern
#include:babel
#include:soulutf8

#ifOption:font=times
#include:mathptmx
#include:tgtermes
#include:tgheros
#include:tgcursor
#endif
#ifOption:font=tg
#include:mathptmx
#include:tgtermes
#include:tgheros
#include:tgcursor
#endif

#ifOption:font=old-times
#include:mathptmx
#endif
#ifOption:font=oldtimes
#include:mathptmx
#endif

#ifOption:fontspec
#include:fontspec
#endif
#ifOption:fontspec=yes
#include:fontspec
#endif

\UnivFixPaperSize#*
\uline{text}#*