# tikzPackets package
# Matthew Bertucci 12/24/2021 for v1.0

#include:tikz
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:pbox

\packetsInit
\packetsPrintBitScale{last bit value}
\packetsBitFont#*
\packetsPrintBitNumber#*

\packetsPutField{num of bits}{name}
\packetsPutField[TikZ keys%keyvals]{num of bits}{display name}
\packetsPutField{num of bits}[node name]{display name}#*
\packetsPutField[TikZ keys%keyvals]{num of bits}[node name]{display name}

#keyvals:\packetsPutField#c
## coordinate systems
x=%<<dimen> or <coord>%>
y=%<<dimen> or <coord>%>
z=%<<dimen> or <coord>%>
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
# referencing nodes
remember picture#true,false
overlay#true,false
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
protocolsField
#endkeyvals

\packetsPrintRangeOnLeft{first bit}{last bit}
\packetsPrintRangeOnLeft[node name]{first bit}{last bit}#*
\packetsPrintRangeOnRight{first bit}{last bit}
\packetsPrintRangeOnRight[node name]{first bit}{last bit}#*

\packetsNextLine
\packetsEndLine{first bit}{last bit}
\packetsLastNode
\packetsFirstNodeInLastLine
\packetsBitWidth
