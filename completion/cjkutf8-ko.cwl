# cjkutf8-ko package
# Matthew Bertucci 2022/05/03 for v2.2

#include:CJKutf8
#include:cjkutf8-nanummjhanja
#include:cjkutf8-josa
#include:kolabels-utf

#keyvals:\usepackage/cjkutf8-ko#c
hangul
hanja
usecjkt1font
usedotemph
nojosa
truetype
mj=%<font%>
gt=%<font%>
#endkeyvals

#ifOption:usedotemph
#include:ulem
#include:CJKfntef
\dotemph{text}
\dotemphchar#*
\dotemphraise#*
#endif

#ifOption:hangul
#include:konames-utf
#endif

\CJKscale{factor}
\lowerCJKchar{length}
\lowercjkchar{length}#S

# not documented
\CJKpostmathglue#*
\HangulGlue#*
\HangulPenalty#*
\cancelCJKscale#*
\cancellowerCJKchar#*
\cancellowercjkchar#S