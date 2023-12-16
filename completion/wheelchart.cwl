# wheelchart package
# Matthew Bertucci 2023/12/05 for v2.0

#include:tikz
#include:tikzlibrarycalc

\wheelchart{wheelchart data}
\wheelchart[options%keyvals]{wheelchart data}

#keyvals:\wheelchart#c
after slices={%<code%>}
anchor xsep=%<degrees%>
anchor ysep=%<degrees%>
arc={%<TikZ keys%>}
arc around text#true,false
arc data={%<text%>}
arc data align=#center,left,right
arc data angle pos=%<value%>
arc data angle shift=%<degrees%>
arc data dir=%<value%>
arc data pos=%<value%>
arc data sep=%<value%>
arc data style={%<TikZ keys%>}
arc first half={%<TikZ keys%>}
arc pos=%<value%>
arc second half={%<TikZ keys%>}
arc sep=%<value%>
at=%<point%>
before slices={%<code%>}
caption={%<text%>}
caption left={%<text%>}
caption left sep=%<value%>
caption left style={%<TikZ keys%>}
caption sep=%<value%>
caption style={%<TikZ keys%>}
contour={%<TikZ keys%>}
counterclockwise#true,false
data={%<text%>}
data angle pos=%<value%>
data angle shift=%<degrees%>
data pos=%<value%>
data sep=%<value%>
data style={%<TikZ keys%>}
discrete#true,false
discrete factor=%<value%>
discrete partitioning=#angle,radius
discrete pic={%<code%>}
discrete sort=#angle,radius
discrete space at borders#true,false
domain=%<start%>:%<end%>
etoc code={%<code%>}
etoc count total pages=%<number%>
etoc level=%<level%>
etoc name=%<name%>
etoc use name=%<name%>
expand list=#false,once,true
expand list items=#false,once,true
explode
explode=%<factor%>
for loop end={%<code%>}
for loop start={%<code%>}
gap
gap=%<factor%>
gap max angle=%<degrees%>
gap polar
gap polar=%<degrees%>
gap radius
gap radius=%<value%>
header={%<list%>}
header prefix=%<prefix%>
inner data={%<text%>}
inner data angle pos=%<value%>
inner data angle shift=%<degrees%>
inner data pos=%<value%>
inner data sep=%<value%>
inner data style={%<TikZ keys%>}
inner plot={%<code%>}
inner plot style={%<TikZ keys%>}
inner radius=%<value%>
legend={%<code%>}
legend entry={%<code%>}
legend only#true,false
legend row={%<code%>}
lines
lines=%<value%>
lines angle pos=%<value%>
lines angle shift=%<degrees%>
lines ext
lines ext=%<value%>
lines ext bottom dir=#left,right
lines ext dir=#left,right
lines ext dirsep=%<degrees%>
lines ext fixed#true,false
lines ext fixed left=%<value%>
lines ext fixed right=%<value%>
lines ext left anchor=%<anchor%>
lines ext right anchor=%<anchor%>
lines ext top dir=#left,right
lines pos=%<value%>
lines sep=%<value%>
lines style={%<TikZ keys%>}
middle={%<text%>}
middle fill={%<TikZ keys%>}
middle style={%<TikZ keys%>}
name=%<name%>
outer plot={%<code%>}
outer plot style={%<TikZ keys%>}
outer radius=%<value%>
parse=#pgfmath,l3fp
perc precision=%<integer%>
pie#true,false
plot={%<code%>}
plot style={%<TikZ keys%>}
radius={%<inner radius%>}{%<outer radius%>}
samples=%<number%>
separator columns=%<delimiter%>
separator rows=%<delimiter%>
slices={%<path%>}
slices angle pos=%<value%>
slices angle shift=%<degrees%>
slices arc={%<value1%>}{%<value2%>}
slices arc inner end#true,false
slices arc inner end start#true,false
slices arc inner start#true,false
slices arc inner start end#true,false
slices arc match={%<arg1%>}{%<num1%>}{%<num2%>}{%<num3%>}{%<arg2%>}{%<arg3%>}{%<arg4%>}
slices arc outer end#true,false
slices arc outer end start#true,false
slices arc outer start#true,false
slices arc outer start end#true,false
slices arrow={%<value1%>}{%<value2%>}
slices end arc={%<value1%>}{%<value2%>}
slices end arrow={%<value1%>}{%<value2%>}
slices end to={%<value1%>}{%<value2%>}
slices inner angle reduce=%<degrees%>
slices inner angle shift=%<degrees%>
slices inner arc={%<value1%>}{%<value2%>}
slices inner arc tangent#true,false
slices inner arrow={%<value1%>}{%<value2%>}
slices inner end angle shift=%<degrees%>
slices inner start angle shift=%<degrees%>
slices inner to={%<value1%>}{%<value2%>}
slices outer angle reduce=%<degrees%>
slices outer angle shift=%<degrees%>
slices outer arc={%<value1%>}{%<value2%>}
slices outer arc tangent#true,false
slices outer arrow={%<value1%>}{%<value2%>}
slices outer end angle shift=%<degrees%>
slices outer start angle shift=%<degrees%>
slices outer to={%<value1%>}{%<value2%>}
slices pos=%<value%>
slices scope={%<TikZ keys%>}
slices sep=%<value%>
slices start arc={%<value1%>}{%<value2%>}
slices start arrow={%<value1%>}{%<value2%>}
slices start to={%<value1%>}{%<value2%>}
slices style={%<TikZ keys%>}
slices to={%<value1%>}{%<value2%>}
slice{%<range%>}={%<TikZ keys%>}
start angle=%<degrees%>
start half
start half=%<degrees%>
title={%<text%>}
title left={%<text%>}
title left sep=%<value%>
title left style={%<TikZ keys%>}
title sep=%<value%>
title style={%<TikZ keys%>}
total angle=%<degrees%>
total count=%<integer%>
triangle proportional area={%<width%>}{%<height%>}
triangle proportional height={%<width%>}{%<height%>}
value=%<value%>
WClist%<name%>={%<list%>}
wheel data={%<text%>}
wheel data angle pos=%<value%>
wheel data angle shift=%<degrees%>
wheel data pos=%<value%>
wheel data sep=%<value%>
wheel data style={%<TikZ keys%>}
wheel lines={%<TikZ keys%>}
xbar={%<width%>}{%<height%>}
ybar={%<width%>}{%<height%>}
#endkeyvals

\WCcount
\WCcountdiscrete
\WCdataangle
\WCetocthelinkedname#*
\WCetocthelinkednumber#*
\WCetocthelinkedpage#*
\WCetocthename#*
\WCetocthenumber#*
\WCetocthenumberofpages#*
\WCetocthepage#*
\WClegend
\WCmidangle
\WCperc
\WCpercentage
\WCpercentagerounded
\WCtotalcount
\WCtotalnum

\WCvarA#*
\WCvarB#*
\WCvarC#*
\WCvarD#*
\WCvarE#*
\WCvarF#*
\WCvarG#*
\WCvarH#*
\WCvarI#*
\WCvarJ#*
\WCvarK#*
\WCvarL#*
\WCvarM#*
\WCvarN#*
\WCvarO#*
\WCvarP#*
\WCvarQ#*
\WCvarR#*
\WCvarS#*
\WCvarT#*
\WCvarU#*
\WCvarV#*
\WCvarW#*
\WCvarX#*
\WCvarY#*
\WCvarZ#*
