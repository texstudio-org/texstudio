# gckanbun package
# Matthew Bertucci 2025/11/12 for v2.0.0

#include:ifluatex
#include:ifuptex
#include:keyval

#keyvals:\usepackage/gckanbun#c
prefix=%<prefix%>
#endkeyvals

\gckanbunruby{text1}{text2}
\振り{text1}{text2}
\gckanbunokurigana{text}
\送り{text}
\gckanbunkaeriten{text}
\返り{text}

\IchiRe
\JyouRe
\KouRe
\TenRe
\KanHyphen

#ifOption:prefix=
\ruby{text1}{text2}
\okurigana{text}
\kaeriten{text}
#endif

#ifOption:prefix=kanbun
\kanbunruby{text1}{text2}
\kanbunokurigana{text}
\kanbunkaeriten{text}
#endif

\zw#S
\zh#S