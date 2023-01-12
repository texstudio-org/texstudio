# pst-solides3d package
# Matthew Bertucci 2/23/2022 for v4.34a

#include:pstricks
#include:pst-node
#include:pst-xkey
#include:multido

### << Commands >> ###

\axesIIID(x1,y1,z1)(x2,y2,z2)
\axesIIID[options%keyvals](x1,y1,z1)(x2,y2,z2)
\psSolid[object=%<name%>]
\psSolid[object=%<name%>,%<options%>]
\psSolid[object=%<name%>](x,y,z)
\psSolid[object=%<name%>,%<options%>](x,y,z)
\psSolid[options%keyvals](x,y,z)#S
\codejps{jps code}
\defFunction{name%specialDef}(var){x}{y}{z}#s#%pstsolides3dfunc
\defFunction[options%keyvals]{name%specialDef}(var){x}{y}{z}#s#%pstsolides3dfunc
\psSurface(xmin,ymin)(xmax,ymax){surface definition%definition}
\psSurface[options%keyvals](xmin,ymin)(xmax,ymax){surface definition%definition}
\psImplicitSurface[options%keyvals]
\psImplicitSurface[options%keyvals](x,y,z)
\composeSolid
\psPoint(x,y,z){name}
\psLineIIID(%<x0,y0,z0%>)(%<x1,y1,z1%>)%<...(xN,yN,zN)%>
\psLineIIID[%<options%>](%<x0,y0,z0%>)(%<x1,y1,z1%>)%<...(xN,yN,zN)%>
\psPolygonIIID(%<x0,y0,z0%>)(%<x1,y1,z1%>)%<...(xN,yN,zN)%>
\psPolygonIIID[%<options%>](%<x0,y0,z0%>)(%<x1,y1,z1%>)%<...(xN,yN,zN)%>
\psTransformPoint(x,y,z)(vx,vy,vz){name}
\psTransformPoint[options%keyvals](x,y,z)(vx,vy,vz){name}
\psProjection[object=%<name%>]
\psProjection[object=%<name%>,%<options%>]
\psProjection[object=%<name%>](x,y,z)
\psProjection[object=%<name%>,%<options%>](x,y,z)
\psProjection[options%keyvals](x,y,z)#S
\psResetSolidKeys#*
\gridIIID(x1,y1)(x2,y2)
\gridIIID[options%keyvals](x1,y1)(x2,y2)
\psImage[file=%<imagefile%>]
\psImage[file=%<imagefile%>,%<options%>]
\psImage[file=%<imagefile%>](x,y)
\psImage[file=%<imagefile%>,%<options%>](x,y)
\psImage[options%keyvals](x,y)#S
\Normale(radius,longitude,latitude)#*
\addtosolideslistobject{name}

### << Keyvals >> ###
#keyvals:\axesIIID#c
arrowinset=%<number%>
arrowsize=##L
axisemph=%<font commands%>
axisnames={%<x,y,z%>}
labelsep=##L
linecolor=#%color
linewidth=##L
mathLabel#true,false
showOrigin#true,false
#endkeyvals

#keyvals:\psSolid#c
object=#point,line,vector,plan,grille,cube,cylindre,cylindrecreux,cone,conecreux,tronccone,troncconecreux,sphere,calottesphere,calottespherecreuse,tore,tetrahedron,octahedron,dodecahedron,icosahedron,anneau,prisme,prismecreux,parallelepiped,face,polygonregulier,ruban,surface,surface*,surfaceparametree,pie,fusion,geode,load,offfile,objfile,datfile,new,courbe,vecteur,vecteur3d
a=%<length%>
action=#none,draw,draw*,draw**,writesolid,writeobj,writeoff
affinage=#0,1,2,3,all
affinagecoeff=%<factor%>
affinagerm
args=%<args spec%>
axe=%<x y z%>
b=%<length%>
base=%<base spec%>
biface
c=%<length%>
chanfrein
chanfreincoeff=%<factor%>
color1=%<xcolor color%>
color2=%<xcolor color%>
color3=%<xcolor color%>
color4=%<xcolor color%>
deactivatecolor
decal=%<integer%>
definition=#solidgetsommet,solidcentreface,isobarycentre3d,barycentre3d,hompoint3d,sympoint3d,translatepoint3d,scaleOpoint3d,rotateOpoint3d,orthoprojplane3d,milieu3d,addv3d,vecteur3d,addv3d,subv3d,mulv3d,vectprod3d,normalize3d,equation,normalpoint,solidface
dualreg#true,false
faces={%<faces spec%>}
fcol=%<n1 (col1) n2 (col2) ...%>
fcolor=#%color
file=%<file name%>
fillcolor=#%color
fontsize=##L
function=#%pstsolides3dfunc
grid#true,false
h=%<height%>
hollow#true,false
hue=%<hue spec%>
incolor=#%color
inhue=%<hue spec%>
inouthue=%<hue spec%>
intersectioncolor=%<(color1) (color2) ...%>
intersectionlinewidth=%<w1 w2 ...%>
intersectionplan={[%<eq1%>] %<[eq2] ...%>}
intersectiontype=#0,-1
lightintensity=%<number%>
lightsrc=%<x y z%>
linecolor=#%color
linestyle=%<style%>
linewidth=##L
load=%<name%>
mode=#0,1,2,3,4
name=%<name%>
ngrid=%<<n> or <n1 n2>%>
normal=%<x y z%>
num=#0,1,2,3,all
numfaces=#0,1,2,3,all,%<PS code%>
opacity=%<factor%>
origine=%<x y z%>
phi=%<degrees%>
plangrid
planmarks
plansection={%<plan1 plan2 ...%>}
plansepare={[%<a b c d%>]}
QZ=%<number%>
R=%<outer radius%>
r=%<radius%>
r0=%<radius0%>
r1=%<radius1%>
range=%<xmin xmax%>
resolution=%<resolution%>
rm=%<face1 face2 face3%>
RotSequence=%<sequence%>
RotX=%<degrees%>
RotY=%<degrees%>
RotZ=%<degrees%>
section=
show=#0,1,2,3,all
showbase
showBase
sommets=%<data%>
theta=%<degrees%>
transform={%<transform%>}
trunc=#0,1,2,3,all
trunccoeff=%<factor%>
unit=%<number%>
visibility#true,false
#endkeyvals

#keyvals:\psSurface#c,\psImplicitSurface#c
algebraic
axesboxed
base=%<base spec%>
color1=%<xcolor color%>
color2=%<xcolor color%>
color3=%<xcolor color%>
color4=%<xcolor color%>
deactivatecolor
fcol=%<n1 (col1) n2 (col2) ...%>
fillcolor=#%color
grid#true,false
hue=%<hue spec%>
incolor=#%color
inhue=%<hue spec%>
inouthue=%<hue spec%>
intersectionplan={[%<eq1%>] %<[eq2] ...%>}
intersectiontype=#0,-1
intersectioncolor=%<(color1) (color2) ...%>
intersectionlinewidth=%<w1 w2 ...%>
lightintensity=%<number%>
lightsrc=%<x y z%>
linecolor=#%color
linewidth=##L
ngrid=%<<n> or <n1 n2>%>
opacity=%<factor%>
QZ=%<number%>
spotX=%<pos%>
spotY=%<pos%>
spotZ=%<pos%>
xytranslate=%<x y%>
Zmax=%<number%>
Zmin=%<number%>
#endkeyvals

#keyvals:\psImplicitSurface#c
ImplFunction=%<F(x,y,z)%>
XMinMax=%<min max step%>
YMinMax=%<min max step%>
ZMinMax=%<min max step%>
#endkeyvals

#keyvals:\psLineIIID#c,\psPolygonIIID#c
doubleline#true,false
linearc=%<number%>
linecolor=#%color
linewidth=##L
#endkeyvals

#keyvals:\psPolygonIIID#c
fillstyle=#solid,vlines,hlines,crosshatch
#endkeyvals

#keyvals:\psTransformPoint#c
RotX=%<degrees%>
RotY=%<degrees%>
RotZ=%<degrees%>
#endkeyvals

#keyvals:\psProjection#c
definition=#milieu,parallelopoint,translatepoint,rotatepoint,hompoint,orthoproj,projx,projy,sympoint,axesympoint,cpoint,xdpoint,ydpoint,interdroite,interdroitecercle,vecteur,orthovecteur,normalize,addv,subv,mulv,horizontale,verticale,paral,perp,mediatrice,bissectrice,axesymdroite,rotatedroite,translatedroite,ABcercle,diamcercle,translatepol,rotatepol,hompol,sympol,axesympol
args=%<args spec%>
fillcolor=#%color
fillstyle=#solid,vlines,hlines,crosshatch
fontsize=##L
function=%<function%>
hatchcolor=#%color
isolatin#true,false
linecolor=#%color
linestyle=%<style%>
name=%<name%>
normal=%<x y z%>
object=#texte,cercle,point,vecteur,polygone,line,droite,rightangle,courbe,courbeR2
path={%<PS code%>}
phi=%<degrees%>
plan=%<plan type%>
pos=%<pos%>
PSfont=%<font name%>
range=%<xmin xmax%>
resolution=%<resolution%>
text=%<text%>
visibility#true,false
#endkeyvals

#keyvals:\gridIIID#c
axisemph=%<font commands%>
linecolor=#%color
spotX=%<pos%>
spotY=%<pos%>
spotZ=%<pos%>
stepX=%<number%>
stepY=%<number%>
stepZ=%<number%>
ticklength=##L
Zmax=%<number%>
Zmin=%<number%>
#endkeyvals

#keyvals:\psImage#c
divisions=%<integer%>
file=%<imagefile%>
normal=%<x y z%>
origine=%<x y z%>
phi=%<degrees%>
unitPicture=%<number%>
#endkeyvals

\PSTSOLIDESIIIDLoaded#S
GreenYellow#B
Yellow#B
Goldenrod#B
Dandelion#B
Apricotq#B
Peach#B
Melon#B
YellowOrange#B
Orange#B
BurntOrange#B
Bittersweet#B
RedOrange#B
Mahogany#B
Maroon#B
BrickRed#B
Red#B
OrangeRed#B
RubineRed#B
WildStrawberry#B
Salmon#B
CarnationPink#B
Magenta#B
VioletRed#B
Rhodamine#B
Mulberry#B
RedViolet#B
Fuchsia#B
Lavender#B
Thistle#B
Orchid#B
DarkOrchid#B
Purple#B
Plum#B
Violet#B
RoyalPurple#B
BlueViolet#B
Periwinkle#B
CadetBlue#B
CornflowerBlue#B
MidnightBlue#B
NavyBlue#B
RoyalBlue#B
Blue#B
Cerulean#B
Cyan#B
ProcessBlue#B
SkyBlue#B
Turquoise#B
TealBlue#B
Aquamarine#B
BlueGreen#B
Emerald#B
JungleGreen#B
SeaGreen#B
Green#B
ForestGreen#B
PineGreen#B
LimeGreen#B
YellowGreen#B
SpringGreen#B
OliveGreen#B
RawSienna#B
Sepia#B
Brown#B
Tan#B
Gray#B
Black#B
White#B