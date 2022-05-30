# oblivoir class
# Matthew Bertucci 2022/05/05 for v3.1.5

#include:xkeyval
#include:xparse
#include:iftex

# options not listed here are in oblivoir-xl.cwl
#keyvals:\documentclass/oblivoir#c
cjk
dhucs
fontspec={%<fontspec options%>}
hyperref={%<hyperref options%>}
xcolor={%<xcolor options%>}
#endkeyvals

\ifLuaOrXeTeX#*
\LuaOrXeTeXtrue#*
\LuaOrXeTeXfalse#*

## Loads oblivoir-xl.cls if xelatex or lualatex, oblivoir-utf.cls otherwise.
## Since cwl can't detect engine, default here to oblivoir-xl
#include:oblivoir-xl
## comment previous line and uncomment following line if you want pdflatex version
## #include:oblivoir-utf

#ifOption:moreverb
#include:moreverb
#endif

#ifOption:lwarp
#include:lwarp
#include:xob-lwarp
#endif

#ifOption:amsmath
#include:amsmath
#include:xob-amssymb
#endif

#ifOption:bookmark
#include:bookmark
#endif

#ifOption:nokorean
#include:ob-nokoreanappendix
#endif

#ifOption:ms
\MSNormalSize
#endif

#ifOption:polyglossia
#include:polyglossia
#include:xparse
\sethangulfont{font name}
\sethangulfont{font name}[font features]
\hangulfont#*
\hangulfonttt#*
#endif