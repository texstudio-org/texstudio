# optikz package
# Matthew Bertucci 2026/03/04 for v1.1.0

#include:amssymb
#include:tikz
#include:xcolor
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

optikzblue#B
optikzred#B
optikzyellow#B

\BScrystal at %<(x,y)%>;
\BScrystal[%<keyvals%>] at %<(x,y)%>;
\TFP at %<(x,y)%>;
\TFP[%<keyvals%>] at %<(x,y)%>;
\camera at %<(x,y)%>;
\camera[%<keyvals%>] at %<(x,y)%>;
\concavelens at %<(x,y)%>;
\concavelens[%<keyvals%>] at %<(x,y)%>;
\convexlens at %<(x,y)%>;
\convexlens[%<keyvals%>] at %<(x,y)%>;
\convexmirror at %<(x,y)%>;
\convexmirror[%<keyvals%>] at %<(x,y)%>;
\curvedmirror at %<(x,y)%>;
\curvedmirror[%<keyvals%>] at %<(x,y)%>;
\diode at %<(x,y)%>;
\diode[%<keyvals%>] at %<(x,y)%>;
\drawbeam[keyvals]{pos1}{pos2}{angle1}{angle2}
\drawbeam{pos1}{pos2}{angle1}{angle2}
\drawrainbow[keyvals]{pos1}{pos2}{angle1}{angle2}
\drawrainbow{pos1}{pos2}{angle1}{angle2}
\faradayrotator at %<(x,y)%>;
\faradayrotator[%<keyvals%>] at %<(x,y)%>;
\grating at %<(x,y)%>;
\grating[%<keyvals%>] at %<(x,y)%>;
\largemirror at %<(x,y)%>;
\largemirror[%<keyvals%>] at %<(x,y)%>;
\laser at %<(x,y)%>;
\laser[%<keyvals%>] at %<(x,y)%>;
\laserdir
\mirror at %<(x,y)%>;
\mirror[%<keyvals%>] at %<(x,y)%>;
\objective at %<(x,y)%>;
\objective[%<keyvals%>] at %<(x,y)%>;
\optikzanglethreepoints{pos1}{pos2}{pos3}{command}#d
\optikzangletwopoints{pos1}{pos2}{command}#d
\parabola at %<(x,y)%>;
\parabola[%<keyvals%>] at %<(x,y)%>;
\planconvexlens at %<(x,y)%>;
\planconvexlens[%<keyvals%>] at %<(x,y)%>;
\pockelscell at %<(x,y)%>;
\pockelscell[%<keyvals%>] at %<(x,y)%>;
\redefinecolor{color}{spec}
\resetcolor{color}
\smallmirror at %<(x,y)%>;
\smallmirror[%<keyvals%>] at %<(x,y)%>;
\spectrometer at %<(x,y)%>;
\spectrometer[%<keyvals%>] at %<(x,y)%>;
\splitter at %<(x,y)%>;
\splitter[%<keyvals%>] at %<(x,y)%>;
\tinysplitter at %<(x,y)%>;
\tinysplitter[%<keyvals%>] at %<(x,y)%>;
\wedge at %<(x,y)%>;
\wedge[%<keyvals%>] at %<(x,y)%>;

\beamgeometry{arg1}{arg2}{arg3}{arg4}{arg5}#S
\DeclareOpticalElement{name}{macro}#S
\optikzangle#S
\optikzcolor#S
\optikzname#S
\optikzshift#S
\optikzstrip#S
\optikzthickness#S
\optikzwedge#S
\optikzwidth#S
\savecolor{color}#S
\softresetcolor{color}#S