# juliamono package
# Matthew Bertucci 2025/05/13 for v0.01

#include:iftex
#include:xkeyval
#include:fontspec

#keyvals:\usepackage/juliamono#c
TT={%<fontspec features%>}
DefaultFeatures={%<fontspec features%>}
Black#true,false
ExtraBold#true,false
Light#true,false
Medium#true,false
Semi#true,false
calt#true,false
zero#true,false
Scale=%<factor%>
FakeStretch=%<factor%>
#endkeyvals

\JuliaMonoBlack
\JuliaMonoExtraBold
\JuliaMonoLight
\JuliaMonoMedium
\JuliaMonoSemi
\JuliaSetCalt
\JuliaUnsetCalt
\LCV{num1}{num2}
\LSS{num1}{num2}
\Lcv{num1}{num2}{text}
\Lss{num1}{num2}{text}