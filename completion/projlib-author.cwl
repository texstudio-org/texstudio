# projlib-author package
# Matthew Bertucci 2022/07/04 for 2022/07/03 release

#include:regexpatch

#keyvals:\usepackage/projlib-author#c
amsfashion
#endkeyvals

#ifOption:amsfashion
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:amsfashion=true
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams-fashion
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams-fashion=true
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams fashion
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif
#ifOption:ams fashion=true
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
#endif

\institute{institute}
\address{address}
\curraddr{address}
\email{email%URL}#U
