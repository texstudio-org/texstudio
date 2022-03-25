# pst-shell package
# Matthew Bertucci 3/4/2022 for v0.03

#include:pstricks
#include:pst-solides3d

\psShell[options%keyvals]
\psShell[options%keyvals](x,y,z)

#keyvals:\psShell
A=%<number%>
a=%<number%>
action=#none,draw,draw*,draw**,writesolid,writeobj,writeoff
alpha=%<degrees%>
b=%<number%>
base=%<base spec%>
beta=%<degrees%>
D=%<number%>
deactivatecolor
fcol=%<n1 (col1) n2 (col2) ...%>
file=%<file name%>
fillcolor=#%color
hue=%<hue spec%>
incolor=#%color
L=%<number%>
lightsrc=%<x y z%>
linecolor=#%color
linewidth=##L
mu=%<degrees%>
N=%<number%>
ngrid=%<n1 n2%>
Omega=%<degrees%>
P=%<number%>
phi=%<degrees%>
precode=%<PS code%>
rm=%<face1 face2 ...%>
RotX=%<degrees%>
RotY=%<degrees%>
RotZ=%<degrees%>
style=#Achatina,Ammonite,Argonauta,Codakia,Conus,Epiteonium,Escalaria,Helcion,Lyria,Natalina,Nautilus,Oxystele,Planorbis,Tonna,Turritella
unit=%<number%>
W1=%<number%>
W2=%<number%>
writedata#true,false
#endkeyvals

\PSTSHELLLoaded#S