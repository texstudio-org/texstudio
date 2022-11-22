# datavisualization tikzlibrary
# 2022/11/20 for v3.1.9a

#include:tikzlibrarybackgrounds
# loads datavisualization pgfmodule, which loads oo pgfmodule and fpu pgflibrary
#include:tikzlibraryfpu

\datavisualization %<〈data spec〉%>;
\datavisualization[options%keyvals] %<〈data spec〉%>;
\tikzdatavisualizationset{options%keyvals}

#keyvals:\datavisualization#c,\tikzdatavisualizationset#c
data point={%<options%>}
before survey=%<code%>
at start survey=%<code%>
at end survey=%<code%>
after survey=%<code%>
before visualization=%<code%>
at start visualization=%<code%>
at end visualization=%<code%>
after visualization=%<code%>
new object={%<options%>}
class=%<class name%>
when=%<phase name%>
store=%<key name%>
before creation=%<code%>
after creation=%<code%>
arg1=%<value%>
arg2=%<value%>
arg3=%<value%>
arg4=%<value%>
arg5=%<value%>
arg6=%<value%>
arg7=%<value%>
arg8=%<value%>
arg1 from key=%<key%>
arg2 from key=%<key%>
arg3 from key=%<key%>
arg4 from key=%<key%>
arg5 from key=%<key%>
arg6 from key=%<key%>
arg7 from key=%<key%>
arg8 from key=%<key%>
arg1 handle from key=%<key%>
arg2 handle from key=%<key%>
arg3 handle from key=%<key%>
arg4 handle from key=%<key%>
arg5 handle from key=%<key%>
arg6 handle from key=%<key%>
arg7 handle from key=%<key%>
arg8 handle from key=%<key%>
new axis base=%<axis name%>
all axes={%<options%>}
new Cartesian axis=%<name%>
scientific axes
scientific axes={%<options%>}
every scientific axes/.style={%<options%>}
school book axes
school book axes={%<options%>}
xy Cartesian
xy axes={%<options%>}
xyz Cartesian cabinet
xyz axes={%<options%>}
uv Cartesian 
uv axes={%<options%>}
uvw Cartesian cabinet
uvw axes={%<options%>}
step=%<value%>
minor steps between steps
minor steps between steps=%<number%>
phase=%<value%>
about=%<number%>
about strategy=%<list%>
standard about strategy
euro about strategy
half about strategy
decimal about strategy
quarter about strategy
int about strategy
many
some
few
none
major={%<options%>}
minor={%<options%>}
subminor={%<options%>}
common={%<options%>}
at=%<list%>
major at=%<list%>
minor at=%<list%>
subminor at=%<list%>
also at=%<list%>
major also at=%<list%>
minor also at=%<list%>
subminor also at=%<list%>
style={%<TikZ options%>}
styling
node style={%<TikZ options%>}
node styling
grid layer/.style={%<options%>}
every grid/.style={%<options%>}
every major grid/.style={%<options%>}
every minor grid/.style={%<options%>}
every subminor grid/.style={%<options%>}
every ticks/.style={%<options%>}
every major ticks/.style={%<options%>}
every minor ticks/.style={%<options%>}
every subminor ticks/.style={%<options%>}
tick layer/.style={%<options%>}
tick node layer/.style={%<options%>}
options at=%<value%> as [%<options%>]
no tick text at=%<value%>
tick prefix=%<text%>
tick suffix=%<text%>
tick unit=%<math text%>
tick typesetter=%<value%>
tick text low even padding=##L
tick text low odd padding=##L
tick text high even padding=##L
tick text high odd padding=##L
tick text odd padding=##L
tick text even padding=##L
tick text padding=##L
stack=##L
stack'=##L
compute step=%<code%>
low=#min,max,padded min,padded max
high=#min,max,padded min,padded max
padded
axis layer/.style={%<options%>}
every axis/.style={%<options%>}
direction axis=%<axis name%>
tick length=##L
tick text at low#true,false
tick text at high#true,false
no tick text
new axis system={%<name%>}{%<setup%>}{%<default opts%>}{%<application opts%>}
every visualizer/.style={%<options%>}
visualize as line
visualize as line=%<visualizer name%>
visualize as smooth line
visualize as smooth line=%<visualizer name%>
visualize as scatter
visualize as scatter=%<visualizer name%>
new visualizer={%<name%>}{%<options%>}{%<legend entry options%>}
style sheet=#vary thickness,vary dashing,vary thickness and dashing,cross marks,strong colors,vary hue,shades of blue,shades of red,gray scale,
every data set label/.append style={%<options%>}
every label in data/.append style={%<options%>}
new legend
new legend=%<legend name%>
legend={%<options%>}
every label in legend/.style={%<options%>}
new legend entry={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every data/.style={%<options%>}
#endkeyvals

\tikzdvdeclarestylesheetcolorseries{name}{color model}{init color}{step}#*
\tikzpointandanchordirection{code1}{code2}#S
\tikzdvvisualizercounter#S

# from datavisualization pgfmodule (only documented cmds listed here; all others in pgfcore.cwl)
\pgfdatapoint#*
\pgfdata#*
\pgfdata{inline data}#*
\pgfdata[options%keyvals]#*
\pgfdata[options%keyvals]{inline data}#*

#keyvals:\pgfdata#c
read from file=%<file name%>
inline
format=#TeX code,named,table
every data
new set=%<name%>
store in set=%<name%>
use set=%<name%>
#endkeyvals

\pgfdeclaredataformat{name}{catcode code}{start code}{line args}{line code}{emptyline code}{end code}#*
\pgfdvdeclarestylesheet{name}{keyvals}#*

# from oo pgfmodule
\pgfooclass{class name}{body}#*
\pgfooclass(list of superclasses){class name}{body}#*
\pgfoonew %<\cmd%>=new %<〈class name〉%>(%<〈constructor args〉%>)#*
\pgfoonew{%<attribute%>}=new %<〈class name〉%>(%<constructor args%>)#*
\pgfoonew{cmd}#Sd
\pgfoogc#*
\method %<〈method name〉%>(%<parameter list%>){%<method body%>}#*
\pgfoothis#*
\pgfoosuper(%<class,object handle%>).%<〈method name〉%>(%<args%>)#*
\attribute %<〈attribute name〉%>#*
\attribute %<〈attribute name〉%>=%<〈initial value〉%>#*
\pgfooset{attribute}{value}#*
\pgfooeset{attribute}{value}#*
\pgfooappend{attribute}{value}#*
\pgfooprefix{attribute}{value}#*
\pgfoolet{attribute}{macro%cmd}#*d
\pgfoovalueof{attribute}#*
\pgfooget{attribute}{macro%cmd}#*d
\pgfooobj{id}#*