# knufakelogo package
# ponte-vecchio 2023-01-17 for v0.92

#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryintersections
#include:tikzlibrarydecorations.text

KNUblack#B
KNUblue#B
KNUgray#B
KNUgreen#B
KNUwhite#B

\KNUfakelogo{%<scale%>}
\KNUfakelogo[%<options%>]{%<scale%>}
\KNUfakelogo*[%<options%>]{%<scale%>}(%<SW coor%>)(%<NE coor%>)
\KNUfakelogoBlue{%<scale%>}
\KNUfakelogoBlue[%<options%>]{%<scale%>}
\KNUfakelogoBlue*[%<options%>]{%<scale%>}(%<SW coor%>)(%<NE coor%>)
\KNUfakelogoGreen{%<scale%>}
\KNUfakelogoGreen[%<options%>]{%<scale%>}
\KNUfakelogoGreen*[%<options%>]{%<scale%>}(%<SW coor%>)(%<NE coor%>)
\KNUfakelogoBlack{%<scale%>}
\KNUfakelogoBlack[%<options%>]{%<scale%>}
\KNUfakelogoBlack*[%<options%>]{%<scale%>}(%<SW coor%>)(%<NE coor%>)

\KNUfakelogoColor{%<scale%>}{%<inner circ colour%>}{%<outer ring colour%>}
\KNUfakelogoColor[%<options%>]{%<scale%>}{%<inner circ colour%>}[%<inner text colour%>][%<outer text colour%>]{%<outer ring colour%>}
\KNUfakelogoColor*[%<options%>]{%<scale%>}{%<bg and inner colour%>}[%<inner text  colour%>][%<outer text/ring colour%>](%<SW coordinate%>)(%<NE coordinate%>)

#keyvals:\KNUfakelogo#c,\KNUfakelogoBlue#c,\KNUfakelogoGreen#c,\KNUfakelogoBlack#c,\KNUfakelogoColor#c
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
#endkeyvals

# not documented
\begin{KNUfakeLogoBlackENV}#S
\begin{KNUfakeLogoBlueENV}#S
\begin{KNUfakeLogoColorENV}#S
\begin{KNUfakeLogoENV}#S
\begin{KNUfakeLogoGreenENV}#S
\end{KNUfakeLogoBlackENV}#S
\end{KNUfakeLogoBlueENV}#S
\end{KNUfakeLogoColorENV}#S
\end{KNUfakeLogoENV}#S
\end{KNUfakeLogoGreenENV}#S
\KBOX#S
\KCIRCLE#S
\KFILL#S
\KNU#S
\KNUdef#S
\KNUeng#S
\KNUengfont#S
\KNUko#S
\KNUkor#S
\KNUkorfont#S
\KNUkorsize#S
\KNUmainfont#S
\KNUmainsize#S
\KNUyearfont#S
\KROOF#S
\KTEXT#S
\KWHITE#S
