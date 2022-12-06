# tikz-3dplot package
# Matthew Bertucci 12/30/2021

#include:pgf
#include:ifthen
# tikz must be loaded first
#include:tikzlibrarycalc
#include:tikzlibrary3d

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c,\tdplotdrawarc#c,\tdplotdrawpolytopearc#c
tdplot_main_coords
tdplot_rotated_coords
tdplot_screen_coords
#endkeyvals

\tdplotsetmaincoords{θ}{φ}
\tdplotsetrotatedcoords{α}{β}{γ}
\tdplotsetrotatedcoordsorigin{point}
\tdplotresetrotatedcoordsorigin
\tdplotsetthetaplanecoords{φ}
\tdplotsetrotatedthetaplanecoords{φ}
\tdplotsetcoord{point}{r}{θ}{φ}
\tdplottransformmainrot{x}{y}{z}
\tdplotresx
\tdplotresy
\tdplotresz
\tdplotresphi
\tdplotrestheta
\tdplottransformrotmain{x}{y}{z}
\tdplottransformmainscreen{x}{y}{z}
\tdplotgetpolarcoords{x}{y}{z}
\tdplotcrossprod(x1,y1,z1)(x2,y2,z2)
\tdplotdefinepoints(vx,vy,vz)(x1,y1,z1)(x2,y2,z2)
\tdplotdrawarc{center}{r}{angle start}{angle end}{label options}{label}
\tdplotdrawarc[options%keyvals]{center}{r}{angle start}{angle end}{label options}{label}
\tdplotdrawpolytopearc{r}{label options}{label}
\tdplotdrawpolytopearc[options%keyvals]{r}{label options}{label}
\tdplotvertexx
\tdplotvertexy
\tdplotvertexz
\tdplotax
\tdplotay
\tdplotaz
\tdplotbx
\tdplotby
\tdplotbz
\tdplotsphericalsurfaceplot{θ-steps}{φ-steps}{function}{line color}{fill color}{x axis}{y axis}{z axis}
\tdplotsphericalsurfaceplot[fill style%keyvals]{θ-steps}{φ-steps}{function}{line color}{fill color}{x axis}{y axis}{z axis}
#keyvals:\tdplotsphericalsurfaceplot#c
parametricfill
#endkeyvals
\tdplottheta
\tdplotphi
\tdplotr
\tdplotsetpolarplotrange{θ1}{θ2}{φ1}{φ2}
\tdplotresetpolarplotrange
\tdplotshowargcolorguide{x pos}{y pos}{x size}{y size}
\tdplotsinandcos{sin macro%cmd}{cos macro%cmd}{θ}#d
\tdplotmult{macro%cmd}{multiplicand}{multiplicator}#d
\tdplotdiv{macro%cmd}{dividend}{divisor}#d

tdplotfillcolor#B
\tdplotlowerphi#*
\tdplotupperphi#*
\tdplotlowertheta#*
\tdplotuppertheta#*
\tdplotcalctransformmainrot#*
\tdplotcalctransformrotmain#*
\tdplotcalctransformmainscreen#*
\tdplotcheckdiff{val1}{val2}{tolerance}{true}{false}#*
\tdplotdosurfaceplot{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#*
\tdplotsimplesetcoord{arg1}{arg2}{arg3}{arg4}#*
\tdplotmaintheta#*
\tdplotmainphi#*
\sintheta#S
\sinphi#S
\stsp#S
\stcp#S
\ctsp#S
\ctcp#S
\raarot#S
\rabrot#S
\racrot#S
\rbarot#S
\rbbrot#S
\rbcrot#S
\rcarot#S
\rcbrot#S
\rccrot#S
\sinalpha#S
\sinbeta#S
\singamma#S
\cosalpha#S
\cosbeta#S
\cosgamma#S
\sasb#S
\sbsg#S
\sasg#S
\sasbsg#S
\sacb#S
\sacg#S
\sacbsg#S
\sacbcg#S
\casb#S
\cacb#S
\cacg#S
\casg#S
\cacbsg#S
\cacbcg#S
\raaeul#S
\rabeul#S
\raceul#S
\rbaeul#S
\rbbeul#S
\rbceul#S
\rcaeul#S
\rcbeul#S
\rcceul#S
\tdplotalpha#*
\tdplotbeta#*
\tdplotgamma#*
\raaeaa#S
\rabeba#S
\raceca#S
\raaeab#S
\rabebb#S
\racecb#S
\raaeac#S
\rabebc#S
\racecc#S
\rbaeaa#S
\rbbeba#S
\rbceca#S
\rbaeab#S
\rbbebb#S
\rbcecb#S
\rbaeac#S
\rbbebc#S
\rbcecc#S
\raarc#S
\rabrc#S
\racrc#S
\rbarc#S
\rbbrc#S
\rbcrc#S
\sinthetavec#S
\costhetavec#S
\stcpv#S
\stspv#S
\sinphivec#S
\cosphivec#S
\tdplottemp#S
\ax#S
\ay#S
\az#S
\bx#S
\by#S
\bz#S
\tdplotstartphi#*
\origviewthetastep#S
\origviewphistep#S
\originalphi#S
\originaltheta#S
\tdplotsuperfudge#*
\viewphistart#S
\viewphistep#S
\viewphiinc#S
\viewphiend#S
\viewthetastep#S
\viewthetastart#S
\viewthetaend#S
\viewthetainc#S
\nextphi#S
\curlongitude#S
\curlatitude#S
\curphi#S
\logictest#S
\phaseshift#S
\colorarg#S
\tdplotx#*
\tdploty#*
\tdplothuestep#*
\tdplotxsize#*
\tdplotysize#*
\tdplotyscale#*
\tdplotstarty#*
\tdplotstopy#*
\tdplotstartx#*
\tdplotstopx#*
\vxcalc#S
\vycalc#S
\vzcalc#S
\vcalc#S
\vxycalc#S

#keyvals:\tdplotdrawarc#c,\tdplotdrawpolytopearc#c
## coordinate systems
x=%<<dimen> or <coord>%>
y=%<<dimen> or <coord>%>
z=%<<dimen> or <coord>%>
## intersections library
name path=%<path%>
name path global=%<path%>
name intersections={%<options%>}
turn
current point is local#true,false
## paths
name=%<name%>
append after command=%<path%>
prefix after command=%<path%>
rounded corners
rounded corners=##L
sharp corners
x radius=%<<num> or <dimen>%>
y radius=%<<num> or <dimen>%>
radius=##L
at=%<coord%>
start angle=%<degrees%>
end angle=%<degrees%>
delta angle=%<degrees%>
step=%<<num> or <dimen> or <coord>%>
xstep=%<<num> or <dimen>%>
ystep=%<<num> or <dimen>%>
help lines
bend=%<coord%>
bend pos=%<fraction%>
parabola height=##L
bend at start
bend at end
to path=%<path%>
save path=%<macro%>
use path=%<macro%>
## actions on paths
color=#%color
%color
draw
draw=#%color
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
dash pattern=%<dash pattern%>
dash phase=%<dash phase%>
dash=%<dash pattern%> phase %<dash phase%>
dash expand off
solid
dotted
densely dotted
loosely dotted
dashed
densely dashed
loosely dashed
dash dot
densely dash dot
loosely dash dot
dash dot dot
densely dash dot dot 
loosely dash dot dot
double
double=#%color
double distance=##L
double distance between line centers=##L
double equal sign distance
fill
fill=#%color
pattern
pattern=%<name%>
pattern color=#%color
nonzero rule
even odd rule
shade
shading=#axis,radial,ball
shading angle=%<degrees%>
## arrows
arrows=%<start spec%>-%<end spec%>
->
<-
<->
tips
tips=#true,proper,on draw,on proper draw,never,false
>=%<end arrow spec%>
shorten <=##L
shorten >=##L
## nodes: shape, text, and position
inner sep=##L
inner xsep=##L
inner ysep=##L
outer sep=%<<dimen> or auto%>
outer xsep=##L
outer ysep=##L
minimum height=##L
minimum width=##L
minimum size=##L
shape aspect=%<aspect ratio%>
shape border uses incircle#true,false
shape border rotate=%<degrees%>
text=#%color
node font=%<font commands%>
font=%<font commands%>
text width=##L
align=#left,flush left,right,flush right,center,flush center,justify
text height=##L
text depth=##L
anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
above
above=##L
below
below=##L
right
right=##L
left
left=##L
above left
above right
below left
below right
centered
# positioning library
on grid#true,false
node distance=##L
base left=
base right=
mid left=
mid right=
above=of %<node%>
below=of %<node%>
right=of %<node%>
left=of %<node%>
# transformations
transform shape
transform shape nonlinear#true,false
# placing nodes explicitly
pos=%<fraction%>
auto
auto=#left,right,false
swap
sloped
allow upside down#true,false
midway
near start
near end
very near start
very near end
at start
at end
label=%<angle%>:%<text%>
label=[%<options%>]%<angle%>:%<text%>
label position=%<degrees%>
absolute#true,false
label distance=##L
pin=%<angle%>:%<text%>
pin=[%<options%>]%<angle%>:%<text%>
pin distance=##L
pin edge={%<options%>}
# quotes library
node quotes mean=%<replacement%>
# referencing nodes
remember picture#true,false
overlay#true,false
# graphs library
every new ->
every new --
every new <->
every new <-
every new -!-
new set=%<set name%>
set=%<set name%>
# making trees grow
growth parent anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
growth function=%<macro%>
edge from parent path=%<path%>
# transparency
draw opacity=%<value%>
opacity=%<value%>
transparent
ultra nearly transparent
very nearly transparent 
nearly transparent
semitransparent
nearly opaque 
very nearly opaque
ultra nearly opaque
opaque
fill opacity=%<value%>
text opacity=%<value%>
# fadings library
path fading
path fading=%<name%>
fit fading#true,false
fading transform={%<options%>}
fading angle=%<degrees%>
scope fading=%<name%>
# decorations library
decoration={%<options%>}
decorate#true,false
## transformations
shift={%<coordinate%>}
shift only
xshift=##L
yshift=##L
scale=%<scale%>
xscale=%<scale%>
yscale=%<scale%>
xslant=%<factor%>
yslant=%<factor%>
rotate=%<degrees%>
rotate around={%<degree%>:%<coordinate%>}
rotate around x=%<degrees%>
rotate around y=%<degrees%>
rotate around z=%<degrees%>
cm={%<a,b,c,d,coord%>}
reset cm
transform canvas={%<options%>}
# topaths library
out=%<degrees%>
in=%<degrees%>
relative#true,false
bend left
bend left=%<degrees%>
bend right
bend right=%<degrees%>
bend angle=%<degrees%>
looseness=%<number%>
out looseness=%<number%>
in looseness=%<number%>
min distance=##L
max distance=##L
out min distance=##L
out max distance=##L
in min distance=##L
in max distance=##L
distance=##L
out distance=##L
in distance=##L
out control=%<coord%>
in control=%<coord%>
controls=%<coord1%> and %<coord2%>
## others
%tikzstyle
# path specific keys
use as bounding box
clip
preaction={%<options%>}
postaction={%<options%>}
late options={%<options%>}
pic actions
#endkeyvals
