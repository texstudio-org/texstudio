# gckanbun package
# Matthew Bertucci 2022/04/29 for v1.2

#include:ifluatex
#include:ifuptex
#include:keyval

#keyvals:\usepackage/gckanbun#c
prefix=%<prefix%>
#endkeyvals

\gckanbunruby{text1}{text2}
\gckanbunokurigana{text}
\gckanbunkaeriten{text}

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