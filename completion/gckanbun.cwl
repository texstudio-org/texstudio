# gckanbun package
# Matthew Bertucci 2026/01/05 for v2.2.0

#include:ifluatex
#include:ifuptex
#include:keyval
#include:etoolbox

#keyvals:\usepackage/gckanbun#c
prefix=%<prefix%>
#endkeyvals

\gckanbunruby{text1}{text2}
\gckanbunruby[options%keyvals]{text1}{text2}
\振り{text1}{text2}
\振り[options%keyvals]{text1}{text2}
\gckanbunokurigana{text}
\gckanbunokurigana[options%keyvals]{text}
\送り{text}
\送り[options%keyvals]{text}
\gckanbunkaeriten{text}
\gckanbunkaeriten[options%keyvals]{text}
\返り{text}
\返り[options%keyvals]{text}

#keyvals:\gckanbunruby,\振り
intrusion=#pre,post,both
#endkeyvals

#keyvals:\gckanbunokurigana,\送り,\gckanbunkaeriten,\返り
intrusion=#post,both
#endkeyvals

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

\GCKTateOn
\GCKTateOff

\zw#S
\zh#S