# genealogytree package
# Matthew Bertucci 2023/03/09 for v2.3.0

#include:tcolorbox
#include:tcolorboxlibraryskins
#include:tcolorboxlibraryfitting
#include:tcolorboxlibraryexternal
#include:tikzlibraryfit

\gtruselibrary{library list%keyvals}

#keyvals:\usepackage/genealogytree#c,\gtruselibrary#c
debug
templates
fanchart
all
#endkeyvals

#ifOption:debug
#include:array
#include:tabularx
#include:tcolorboxlibrarybreakable
#endif

### 3 Genealogy Tree Macros ###

## 3.1 Creating a Genealogy Tree ##
\genealogytree{tree contents}
\genealogytree[options%keyvals]{tree contents}
\genealogytreeinput{file}#i
\genealogytreeinput[options%keyvals]{file}#i

\begin{genealogypicture}
\begin{genealogypicture}[options%keyvals]
\end{genealogypicture}
\begin{exgenealogypicture}{name}
\begin{exgenealogypicture}{name}[options]
\begin{exgenealogypicture}[externalization options%keyvals]{name}#*
\begin{exgenealogypicture}[externalization options%keyvals]{name}[options]
\end{exgenealogypicture}
#keyvals:\begin{exgenealogypicture}#c
runner=%<file name%>
prefix=%<text%>
externalize#true,false
force remake#true,false
!
-
name=%<name%>
safety=##L
environment=%<env%>
environment with percent#true,false
minipage
minipage=##L
plain
compiler=%<text%>
runs=%<number%>
input source on error#true,false
preclass={%<code%>}
PassOptionsToPackage={%<options%>}{%<package%>}
PassOptionsToClass={%<options%>}{%<class%>}
clear preclass
preamble={%<code%>}
preamble tcbset={%<tcolorbox options%>}
clear preamble
#endkeyvals

## 3.2 Using Tree Options ##
\gtrset{options%keyvals}
\gtrkeysappto{hook}{options%keyvals}#*
\gtrkeysgappto{hook}{options%keyvals}#*
\gtrnodetype#*
\gtrnodeid#*
\gtrnodenumber#*
\gtrnodefamily#*
\gtrnodelevel#*

## 3.3 Accessing Information inside Nodes ##
\gtrifnodeid{true}{false}#*
\gtrifgnode{true}{false}#*
\gtrifcnode{true}{false}#*
\gtrifpnode{true}{false}#*
\gtrifroot{true}{false}#*
\gtrifleaf{true}{false}#*
\gtrifchild{true}{false}#*
\gtrifparent{true}{false}#*
\gtrifleafchild{true}{false}#*
\gtrifleafparent{true}{false}#*

## 3.4 Auxiliary Tools ##
\gtrautosizebox{width}{height}{contents}
\gtrautosizebox*{width}{height}{contents}

\begin{autosizetikzpicture}{width}{height}
\begin{autosizetikzpicture}[options%keyvals]{width}{height}
\end{autosizetikzpicture}
\begin{autosizetikzpicture*}{width}{height}
\begin{autosizetikzpicture*}[options%keyvals]{width}{height}
\end{autosizetikzpicture*}

#keyvals:\begin{autosizetikzpicture}#c,\begin{autosizetikzpicture*}#c
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
# matrix keys
column sep=##L
row sep=##L
every cell={%<row%>}{%<column%>}
cells={%<options%>}
nodes={%<options%>}
column %<n%>/.style={%<options%>}
every odd column/.style={%<options%>}
every even column/.style={%<options%>}
row %<m%>/.style={%<options%>}
every odd row/.style={%<options%>}
every even row/.style={%<options%>}
row %<m%> column %<n%>/.style={%<options%>}
execute at begin cell=%<code%>
execute at end cell=%<code%>
execute at empty cell=%<code%>
matrix anchor=%<anchor%>
ampersand replacement=%<macro%>
# tikzpicture specific keys
baseline
baseline=%<<dimen> or <coord> or default%>
execute at begin picture=%<code%>
execute at end picture=%<code%>
every scope/.style={%<options%>}
every path/.style={%<options%>}
every circle/.style={%<options%>}
every to/.style={%<options%>}
every node/.style={%<options%>}
every lower node part/.style={%<options%>}
every label/.style={%<options%>}
every pin/.style={%<options%>}
every pin edge/.style={%<options%>}
every label quotes/.style={%<options%>}
every pin quotes/.style={%<options%>}
every edge/.style={%<options%>}
every edge quotes/.style={%<options%>}
every pic/.style={%<options%>}
every pic quotes/.style={%<options%>}
every new ->/.style={%<options%>}
every new --/.style={%<options%>}
every new <->/.style={%<options%>}
every new <-/.style={%<options%>}
every new -!-/.style={%<options%>}
every matrix/.style={%<options%>}
every outer matrix/.style={%<options%>}
every child/.style={%<options%>}
every child node/.style={%<options%>}
every plot/.style={%<options%>}
every mark/.style={%<options%>}
every loop/.style={%<options%>}
execute at begin to=%<code%>
execute at end to=%<code%>
execute at begin node=%<code%>
execute at end node=%<code%>
trim left
trim left=%<<dimen> or <coord> or default%>
trim right
trim right=%<<dimen> or <coord> or default%>
tri lowlevel#true,false
name prefix=%<text%>
name suffix=%<text%>
badness warnings for centered text#true,false
node halign header=%<macro%>
quotes mean label
quotes mean pin
level/.style={%<options%>}
level %<n%>/.style={%<options%>}
level distance=##L
sibling distance=##L
edge from parent/.style={%<options%>}
# plots of functions
variable=%<macro%>
samples=%<number%>
domain=%<start%>:%<end%>
samples at=%<samples list%>
parametric#true,false
range=%<start%>:%<end%>
yrange=%<start%>:%<end%>
xrange=%<start%>:%<end%>
id=%<id%>
prefix
raw gnuplot
mark=%<mark%>
mark repeat=%<number%>
mark phase=%<number%>
mark indices=%<list%>
mark size=##L
mark options={%<options%>}
no marks
no markers
sharp plot
smooth
tension=%<value%>
smooth cycle
const plot
const plot mark left
const plot mark right
const plot mark mid
jump mark left
jump mark right
jump mark mid
ycomb
xcomb
polar comb
ybar
xbar
ybar interval
xbar interval
only marks
# blend modes
blend mode=#normal,multiply,screen,overlay,darken,lighten,color dodge,color burn,hard light,soft light,difference,exclusion,hue,saturation,color,luminosity
blend group=#normal,multiply,screen,overlay,darken,lighten,color dodge,color burn,hard light,soft light,difference,exclusion,hue,saturation,color,luminosity
# plothandlers library
bar width=##L
bar shift=##L
bar interval shift=%<factor%>
bar interval width=%<scale%>
matrix/inner style order={%<list%>}
# pic specific keys
pic type=%<type%>
pics/code=%<code%>
pics/foreground code=%<code%>
pics/background code=%<code%>
pic text=%<text%>
pic text options={%<options%>}
#endkeyvals

### 5 Option Setting ###

## 5.5 Node Options ##
\gtrsetoptionsfornode{id list}{options%keyvals}

## 5.6 Family Options ##
\gtrsetoptionsforfamily{id list}{options%keyvals}

## 5.7 Subtree Options ##
\gtrsetoptionsforsubtree{id list}{options%keyvals}

## 5.11 Ignoring Input ##
\gtrignorenode{id list}#*
\gtrignoresubtree{id list}#*

### 6 Node Data (Content) Processing ###

## 6.3 Creating a Customized Non-Interpreting Processor ##
\gtrBoxContent#*
\gtrNodeMinWidth#*
\gtrNodeMaxWidth#*
\gtrNodeMinHeight#*
\gtrNodeMaxHeight#*
\gtrNodeBoxOptions#*

### 7 Database Processing ###

## 7.3 Data Keys ##
\gtrDBname#*
\gtrDBshortname#*
\gtrDBsex#*
\gtrDBcomment#*
\gtrDBprofession#*
\gtrDBimage#*
\gtrDBimageopt#*
\gtrDBviewport#*
\gtrDBuuid#*
\gtrDBkekule#*
\gtrDBrelation#*
\gtrDBrelationship#*
\gtrDBage#*

## 7.4 Input Format for Dates ##
\gtrParseDate{name}{date}

## 7.5 Formatting the Node Data ##
\gtrDeclareDatabaseFormat{format}{option code}{content code}
\gtrPrintDatabase

## 7.6 Formatting Names ##
\gtrPrintName
\pref{given name}#*
\surn{surname}#*
\nick{nickname}#*

## 7.7 Formatting Dates ##
\gtrPrintDate{name}
\gtrifdatedefined{name}{true}{false}#*

## 7.8 Formatting Places ##
\gtrPrintPlace{name}
\gtrifplacedefined{name}{true}{false}#*

## 7.9 Formatting Events ##
\gtrPrintEvent{name}
\gtrifeventdefined{name}{true}{false}#*
\gtrPrintEventPrefix{name}

## 7.10 Formatting Lists of Events ##
\begin{gtrprintlist}{first}{middle}{last}{empty}
\end{gtrprintlist}
\gtrlistseparator
\begin{gtreventlist}
\end{gtreventlist}

## 7.11 Formatting Comments ##
\gtrPrintComment
\gtrifcommentdefined{true}{false}#*

## 7.12 Formatting Professions ##
\gtrPrintProfession
\gtrifprofessiondefined{true}{false}#*

## 7.13 Formatting Lists of Information ##
\begin{gtrinfolist}
\end{gtrinfolist}

## 7.14 Formatting Sex ##
\gtrPrintSex
\gtriffemale{true}{false}#*
\gtrifmale{true}{false}#*

## 7.15 Formatting Images ##
\gtrifimagedefined{true}{false}#*
\gtrincludeDBimage{options}

## 7.16 Formatting Ages ##
\gtrPrintAge
\gtrifagedefined{true}{false}#*

### 8 Edges ###

## 8.1 Edge Settings ##
\gtredgeset{edge options%keyvals}
#keyvals:\gtredgeset#c
perpendicular
rounded
rounded=##L
swing
swing=##L
mesh
mesh={%<options%>}
custom={%<down%>}{%<up%>}{%<left%>}{%<right%>}
none
foreground={%<TikZ options%>}
no foreground
background={%<TikZ options%>}
no background
anchoring=#periphery,center
hide single leg#true,false
xshift=##L
yshift=##L
#endkeyvals

### 9 Genealogy Symbols ###

## 9.1 Symbol Color Settings ##
\gtrSymbolsSetCreate{color}
\gtrSymbolsSetCreateSelected{color}{list}
\gtrSymbolsSetDraw{color}

## 9.2 List of Symbols ##
\gtrsymBorn
\gtrsymBornoutofwedlock
\gtrsymStillborn
\gtrsymDiedonbirthday
\gtrsymBaptized
\gtrsymEngaged
\gtrsymMarried
\gtrsymDivorced
\gtrsymPartnership
\gtrsymDied
\gtrsymKilled
\gtrsymBuried
\gtrsymFuneralurn
\gtrsymFloruit
\gtrsymFemale
\gtrsymMale
\gtrsymNeuter

## 9.3 Legend to Symbols ##
\gtrSymbolsRecordReset
\gtrSymbolsFullLegend
\gtrSymbolsFullLegend[language%keyvals]
\gtrSymbolsLegend
\gtrSymbolsLegend[language%keyvals]

### 10 Language and Text Settings ###

## 10.1 Preamble Settings ##
\gtrlanguagename#*

\gtrloadlanguage{list of languages%keyvals}
#keyvals:\gtrSymbolsFullLegend#c,\gtrSymbolsLegend#c,\gtrloadlanguage#c
catalan
chinese
danish
dutch
english
french
german
german-german
german-austrian
italian
portuguese
spanish
swedish
#endkeyvals

### 11 Debugging: Library debug ###

## 11.1 Parser Debugging ##
\gtrparserdebug{graph content}#*
\gtrparserdebug[options%keyvals]{graph content}#*
\gtrparserdebuginput{file}#*i
\gtrparserdebuginput[options%keyvals]{file}#*i

## 11.2 Processor Debugging ##
\gtrprocessordebug{graph content}#*
\gtrprocessordebug[options%keyvals]{graph content}#*
\gtrprocessordebuginput{file}#*i
\gtrprocessordebuginput[options%keyvals]{file}#*i

## 11.3 Graphical Debugging ##
\gtrdebugdrawcontour{options%keyvals}{path options}#*
#keyvals:\gtrdebugdrawcontour#c
family number=%<number%>
family id=%<id%>
contour=#west,east,both,none
#endkeyvals

### 12 Templates: Library templates ###

## 12.25 Auxiliary Control Sequences ##
\gtrparent%<<num>%>#*
\gtrDrawSymbolicPortrait#*

### 13 Fancharts: Library fancharts ###

## 13.1 Fan Chart Diagrams ##
\gtrfanchart{tree contents}
\gtrfanchart[options%keyvals]{tree contents}
\gtrfanchartinput{file}#i
\gtrfanchartinput[options%keyvals]{file}#i
#keyvals:\gtrfanchart#c,\gtrfanchartinput#c,\gtrset#c
## 13.2 Geometry Options ##
fanchart radii={%<radius1,radius2,...%>}
fanchart inner offset={%<offset1,offset2,...%>}
fanchart outer offset={%<offset1,offset2,...%>}
fanchart minor angle=%<angle%>
fanchart major angle=%<angle%>
fanchart angles=%<minor angle%>:%<major angle%>
fanchart open full
fanchart open up
fanchart open up=%<angle%>
fanchart open down
fanchart open down=%<angle%>
fanchart open left
fanchart open left=%<angle%>
fanchart open right
fanchart open right=%<angle%>
fanchart open for=%<width%> x %<height%>
fanchart reset bounds#true,false
fanchart bounds border=##L
## 13.3 Segment Text Options ##
fanchart landscape from level=%<number%>
fanchart text portrait=#inwards,outwards,auto
fanchart text landscape=#clockwise,counterclockwise,auto
## 13.4 Color and Style Options ##
fanchart boundary color=#%color
fanchart boundary width=##L
fanchart root style={%<TikZ options%>}
fanchart root malefemale
fanchart segment style={%<TikZ options%>}
fanchart segment malefemale
fanchart segment relation
fanchart segment wave
fanchart segment colorwheel
fanchart segment radial
fanchart marker style={%<TikZ options%>}
fanchart marker malefemale
fanchart marker relation
fanchart marker wave
fanchart marker colorwheel
fanchart marker radial
fanchart complemented segment style={%<TikZ options%>}
fanchart complemented marker style={%<TikZ options%>}
fanchart segment style for levels={%<level list%>}{%<TikZ options%>}
fanchart marker style for levels={%<level list%>}{%<TikZ options%>}
fanchart segment style for ids={%<id list%>}{%<TikZ options%>}
fanchart marker style for ids={%<id list%>}{%<TikZ options%>}
fanchart male style={%<TikZ options%>}
fanchart female style={%<TikZ options%>}
fanchart neuter style={%<TikZ options%>}
fanchart ancestor style={%<TikZ options%>}
fanchart descendant style={%<TikZ options%>}
fanchart sibling style={%<TikZ options%>}
fanchart unrelated style={%<TikZ options%>}
## 13.5 Templates ##
fanchart template=#spartan,malefemale sober,malefemale relation,colorwheel sober,colorwheel serious,colorwheel malefemale,colorwheel rich,colorwheel opulent,wave sober,wave serious,wave malefemale,wave rich,wave opulent,radial sober,radial serious,radial malefemale,radial rich,radial opulent
## 13.6 Advanced Customization ##
fanchart-segment-definition={%<code%>}
fanchart-marker-definition={%<code%>}
fanchart-segment-code={%<code%>}
fanchart-root-code={%<code%>}
#endkeyvals

## 13.6 Advanced Customization ##
\gtrcomplemented#*

### 16 Stack Macros ###

## 16.1 Creating a Stack ##
\gtrnewstack{name}#*
\gtrstacksize{name}#*

## 16.2 Push to a Stack ##
\gtrstackpush{name}{content}#*

## 16.3 Pop from a Stack ##
\gtrstackpop{name}#*
\gtrstackpopto{name}{macro%cmd}#*d

## 16.4 Peek into a Stack ##
\gtrstackpeek{name}#*
\gtrstackpeekto{name}{macro%cmd}#*d

## 16.5 Creating Stack Shortcuts ##
\gtrmakestack{name}#*

### < Keys > ###

#keyvals:\genealogytree#c,\genealogytreeinput#c,\begin{genealogypicture}#c,\gtrset#c,\gtrkeysappto#c,\gtrkeysgappto#c,\gtrsetoptionsfornode#c,\gtrsetoptionsforfamily#c,\gtrsetoptionsforsubtree#c,\gtrparserdebug#c,\gtrparserdebuginput#c,\gtrprocessordebug#c,\gtrprocessordebuginput#c,\gtrfanchart#c,\gtrfanchartinput#c
### 5 Option Setting ###
## 5.2 Graph Growth Setting (Time Flow) ##                                     
timeflow=#down,up,left,right
## 5.3 Graph Geometry ##
level distance=##L
level size=##L
node size=##L
node size from=%<<minlength>%> to %<<maxlength>%>
child distance in parent graph=##L
child distance in child graph=##L
child distance=##L
parent distance in parent graph=##L
parent distance in child graph=##L
parent distance=##L
further distance=##L
## 5.4 Identifiers ##
id=%<name%>
id prefix=%<text%>
id suffix=%<text%>
## 5.5 Node Options ##
options for node={%<id list%>}{%<options%>}
node={%<options%>}
distance=##L
pivot
pivot=#none,child,parent,both
box={%<options%>}
box clear
node box={%<options%>}
family box={%<options%>}
subtree box={%<options%>}
turn
turn=#off,right,upsidedown,left
male
female
neuter
tikz={%<TikZ options%>}
## 5.6 Family Options ##
options for family={%<id list%>}{%<options%>}
family={%<options%>}
pivot shift=##L
## 5.7 Subtree Options ##
options for subtree={%<id list%>}{%<options%>}
subtree={%<options%>}
## 5.8 Level Options ##
level=%<number%>
level %<n%>/.style={%<options%>}
## 5.9 Tree Positioning Options ##
proband level=%<number%>
tree offset=##L
after parser={%<code%>}
set position=%<<node>%> at %<<position>%>
adjust position=%<<node> <direction>%> of %<<position>%> distance %<<distance>%>
adjust position=%<<node> <direction>%> of %<<position>%> distance %<<distance>%> shift %<<shift>%>
adjust node=%<<node> <direction>%> of %<<ref node>%> distance %<<distance>%>
adjust node=%<<node> <direction>%> of %<<ref node>%> distance %<<distance>%> shift %<<shift>%>
## 5.10 TikZ and Tcolorbox Options ##
tikzpicture={%<TikZ options%>}
tikzset={%<TikZ options%>}
after tree={%<TikZ code%>}
tcbset={%<tcolorbox options%>}
fit to family=%<id%>
fit to subtree=%<id%>
## 5.11 Ignoring Input ##
ignore#true,false
ignore node={%<id list%>}
ignore subtree={%<id list%>}
ignore level=%<number%>
ignore parent childs
## 5.12 Inserting Input ##
insert after node={%<id%>}{%<input data%>}
insert after family={%<id%>}{%<input data%>}
insert at begin family={%<id%>}{%<input data%>}
insert at end family={%<id%>}{%<input data%>}
## 5.13 Phantom Nodes and Subtrees ##
phantom
phantom=##L
phantom*
phantom*=##L
## 5.14 Childless Families ##
insert for childless families={%<input data%>}
insert phantom for childless families
insert for childless families level limit=%<level%>
## 5.15 Autofill Parent Graphs (Ancestors) ##
autofill parents unspecific
autofill parents unspecific=%<level%>
autofill parents unspecific*
autofill parents unspecific*=%<level%>
complemented/.style={%<options%>}
complemented family/.style={%<options%>}
complemented phantom
autofill parents male female
autofill parents male female=%<level%>
autofill parents male female*
autofill parents male female*=%<level%>
autofill parents female male
autofill parents female male=%<level%>
autofill parents female male*
autofill parents female male*=%<level%>
autofill parents none
## 5.16 Special and Auxiliary Options ##
reset
code={%<code%>}
keysfrom=%<macro%>

### 6 Node Data (Content) Processing ###
## 6.1 Setting a Node Data Processing and Processor ##
node processor=%<macro%>
processing=#fit,tcolorbox,tcbox,tcbox*,tikznode,database
## 6.4 Content Interpreters ##
content interpreter=%<macro%>
content interpreter code={%<code%>}
content interpreter content={%<code%>}
no content interpreter
deletion content interpreter 
database content interpreter
id content interpreter
content interpreter id and content={%<id%>}{%<code%>}
## 7.5 Formatting the Node Data ##
database format=#full,full marriage above,full marriage below,full no marriage,medium,medium marriage above,medium marriage below,medium no marriage,short,short marriage above,short marriage below,short no marriage,name,symbol,empty,marriage
## 7.6 Formatting Names ##
pref code={%<code%>}
surn code={%<code%>}
nick code={%<code%>}
name=#full,short
name font={%<code%>}
empty name text={%<text%>}
name code={%<code%>}
## 7.7 Formatting Dates ##
date format=#typical,dd.mm.yyyy,d.m.yyyy,d.M.yyyy,d.month yyyy,dd.mon.yyyy,d.mon.yyyy,dd mon.yyyy,d mon.yyyy,dd/mm/yyyy,d/m/yyyy,d/m yyyy,d/M/yyyy,dd/month/yyyy,d/month/yyyy,dd/mon/yyyy,d/mon/yyyy,dd/mm yyyy,dd mm yyyy,d M yyyy,d month yyyy,dd mon yyyy,d mon yyyy,dd-mm-yyyy,d-m-yyyy,d-M-yyyy,dd-month-yyyy,d-month-yyyy,dd-mon-yyyy,d-mon-yyyy,ddmonyyyy,yyyy.mm.dd,yyyy.m.d,yyyy.m.d.,yyyy.M.d.,yyyy.month d.,yyyy.mon.d.,yyyy/mm/dd,yyyy/m/d,yyyy d/m,yyyy mm dd,yyyy month d,yyyy mon dd,yyyy-mm-dd,yyyy-mon-dd,yyyy-mon-d,yyyymondd,yyyymmdd,mm.dd.yyyy,m.d.yyyy,mm/dd/yyyy,m/d/yyyy,mm-dd-yyyy,m-d-yyyy,month d yyyy,mon.d yyyy,mon d yyyy,yyyy
date code={%<code%>}
calendar text for=%<<calendar>%> is %<{%<prefix%>}{%<postfix%>}
calendar print=#all,none,all but AD
date range full={%<pre%>}{%<mid%>}{%<app%>}
date range before={%<pre%>}{%<app%>}
date range after={%<pre%>}{%<app%>}
date range separator={%<text%>}
## 7.8 Formatting Places ##
place text={%<pre%>}{%<app%>}
## 7.9 Formatting Events ##
event prefix/birth=%<text%>
event prefix/birth/out of wedlock=%<text%>
event prefix/birth/stillborn=%<text%>
event prefix/birth/died=%<text%>
event prefix/baptism=%<text%>
event prefix/engagement=%<text%>
event prefix/marriage=%<text%>
event prefix/marriage/other=%<text%>
event prefix/divorce=%<text%>
event prefix/floruit=%<text%>
event prefix/death=%<text%>
event prefix/death/killed=%<text%>
event prefix/burial=%<text%>
event prefix/burial/cremated=%<text%>
event format=#prefix date place,prefix date,date
event text={%<pre%>}{%<sep date%>}{%<sep place%>}{%<app%>}
event code={%<code%>}
## 7.10 Formatting Lists of Events ##
list separators={%<first%>}{%<middle%>}{%<last%>}{%<empty%>}
list separators hang
list separators hang=##L
## 7.11 Formatting Comments ##
comment code={%<code%>}
## 7.12 Formatting Professions ##
profession code={%<code%>}
## 7.13 Formatting Lists of Information ##
info separators={%<first%>}{%<middle%>}{%<last%>}{%<empty%>}
## 7.15 Formatting Images ##
if image defined={%<true%>}{%<false%>}
image prefix=%<text%>
fill zoom DBimage
fill overzoom DBimage
## 7.16 Formatting Ages ##
age code={%<code%>}

### 8 Edges ###
## 8.1 Edge Settings ##
edges={%<edge options%>}
family edges={%<edge options%>}
edges for family={%<family%>}{%<edge options%>}
subtree edges={%<edge options%>}
edges for subtree={%<subtree%>}{%<edge options%>}
## 8.2 Edge Types ##
edge/perpendicular
edge/rounded
edge/rounded=##L
edge/swing
edge/swing=##L
edge/mesh
edge/mesh={%<options%>}
edge/custom={%<down%>}{%<up%>}{%<left%>}{%<right%>}
edge/none
## 8.3 Edge Parameters ##
edge/foreground={%<TikZ options%>}
edge/no foreground
edge/background={%<TikZ options%>}
edge/no background
edge/anchoring=#periphery,center
edge/hide single leg#true,false
edge/xshift=##L
edge/yshift=##L
## 8.4 Edge Labels ##
label={%<text%>}
label options={%<TikZ options%>}
family label={%<text%>}
subtree label={%<text%>}
## 8.5 Edge Labels Database ##
family database={%<data keys%>}
label database options={%<options%>}
ignore family database
use family database
## 8.6 Adding and Removing Nodes from Edge Drawing ##
add child=%<<child>%> to %<<family>%>
add parent=%<<parent>%> to %<<family>%>
remove child=%<<child>%> from %<<family>%>
remove parent=%<<parent>%> from %<<family>%>
disconnect
disconnect=#child,parent,both
## 8.7 Extra Edges ##
extra edges={%<parents%>}{%<children%>}{%<edge options%>}
family extra edges={%<parents%>}{%<children%>}{%<edge options%>}
extra edges for family={%<family%>}{%<parents%>}{%<children%>}{%<edge options%>}
extra edges for families={%<family list%>}{%<edge options%>}
extra edges prepend={%<parents%>}{%<children%>}{%<edge options%>}
family extra edges prepend={%<parents%>}{%<children%>}{%<edge options%>}
extra edges prepend for family={%<family%>}{%<parents%>}{%<children%>}{%<edge options%>}
extra edges prepend for families={%<family list%>}{%<edge options%>}
## 8.8 Edge Shifting ##
edges shift=##L
edges up by=%<<number>%> of %<<parts>%>
edges down by=%<<number>%> of %<<parts>%>
edges up
edges down
reset edge level shift
switch edge level shift
nullify edge level shift

### 9 Genealogy Symbols ###
## 9.3 Legend to Symbols ##
symbols record reset
symlang/Born=%<text%>
symlang/Bornoutofwedlock=%<text%>
symlang/Stillborn=%<text%>
symlang/Diedonbirthday=%<text%>
symlang/Baptized=%<text%>
symlang/Engaged=%<text%>
symlang/Married=%<text%>
symlang/Divorced=%<text%>
symlang/Partnership=%<text%>
symlang/Died=%<text%>
symlang/Killed=%<text%>
symlang/Buried=%<text%>
symlang/Funeralurn=%<text%>
symlang/Floruit=%<text%>
symlang/Female=%<text%>
symlang/Male=%<text%>
symlang/Neuter=%<text%>

### 10 Language and Text Settings ###
## 10.1 Preamble Settings ##
language=#catalan,chinese,danish,dutch,english,french,german,german-german,german-austrian,italian,portuguese,spanish,swedish

### 11 Debugging: Library debug ###
## 11.4 Show Information ##
show=%<text%>
show id
show level
show number
show family
show type

### 12 Templates: Library templates ###
## Using Templates ##
template=#formal graph,signpost,symbol nodes,tiny boxes,tiny circles,directory,database pole,database pole reduced,database poleportrait,database poleportrait reduced,database portrait,database portrait reduced,database traditional,database traditional reduced,database sideways,database sideways reduced,database sidewaysportrait,database sidewaysportrait reduced,database relationship,ahnentafel 3,ahnentafel 4,ahnentafel 5,a4paper 3,a4paper 4,a3paper 5,letterpaper 3,letterpaper 4,display 16:9 3,display 16:9 4,display 16:9 5,display 16:10 3,display 16:10 4,display 16:10 5
template horizontal border=##L
template vertical border=##L
#endkeyvals

#keyvals:\tcbset
male/.style={%<options%>}
female/.style={%<options%>}
neuter/.style={%<options%>}
#endkeyvals

#keyvals:\tikzset#c
genealogytree edges scope/.style={%<options%>}
genealogytree extra edges scope/.style={%<options%>}
#endkeyvals

gtr_Blue_1#B
gtr_Blue_2#B
gtr_Blue_3#B
gtr_Blue_4#B
gtr_Blue_5#B
gtr_Blue_6#B
gtr_Bright_Red#B
gtr_Female_Background#B
gtr_Female_Frame#B
gtr_Male_Background#B
gtr_Male_Frame#B
gtr_Neuter_Background#B
gtr_Neuter_Frame#B
gtr_Peach_Back#B
gtr_Peach_Frame#B
gtr_Yellow_Back#B
gtr_Yellow_Frame#B

\gtrpkgprefix#S
gtrfanchartboundary#B
gtrsymbol#B
