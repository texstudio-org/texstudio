# calculatoritems package
# Matthew Bertucci 2025/05/25 for v0.1.3

#include:amssymb
#include:xstring
#include:settobox
#include:ifthen
#include:calc
#include:simplekv
#include:tcolorbox
#include:circledtext
#include:tikzlibrarycalc
#include:tcolorboxlibraryskins
#include:inlinegraphicx

#keyvals:\usepackage/calculatoritems#c
xelua
noamssymb
#endkeyvals

#ifOption:xelua
#include:fontspec
#include:listofitems
\CalcKeyCasioCW{%<key1+key2+...%>}
\CalcKeyCasioFX{%<key1+key2+...%>}
\CalcKeyNwks*{%<key1+key2+...%>}
\CalcKeyNwks{%<key1+key2+...%>}
\CalcKeyTIfr{%<key1+key2+...%>}
\CalcKeyTI{%<key1+key2+...%>}
\fontkeyCASIOcw
\fontkeyCASIOfx
\fontkeyNWKS
\fontkeyTI
\fontkeyTIfr
#endif

\CalcItemMenu[keyvals]{content%text}
\CalcItemMenu{content%text}
\CalcKey[keyvals]{text}
\CalcKey{text}
\casiodots
\fontCASIOA
\fontCASIOB
\fontHP
\fontKEY
\fontNWKS
\fontTI
\inckeycalc*[keyvals]{model}{key%plain}
\inckeycalc*[keyvals]{model}{key%plain}[extension]
\inckeycalc*{model}{key%plain}
\inckeycalc*{model}{key%plain}[extension]
\inckeycalc[keyvals]{model}{key%plain}
\inckeycalc[keyvals]{model}{key%plain}[extension]
\inckeycalc{model}{key%plain}
\inckeycalc{model}{key%plain}[extension]
\nwkstri
\tidots