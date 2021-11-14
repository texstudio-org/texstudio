# tkz-orm package
# Matthew Bertucci 11/11/2021 for v0.1.4

#include:tikz

constraintcolor#B
ormconstraintcolor#B
ormdeonticcolor#B
ormimpliedcolor#B

#keyvals:\node#c
entity
value
power
power=
sequence
sequence=
roles
roles=%<number%>
role
role=%<number%>
vroles
vroles=%<number%>
vrole
vrole=%<number%>
relation
relationship
plays
#endkeyvals

#keyvals:\begin{tikzpicture}#c
every entity/.style={%<TikZ options%>}
every value/.style={%<TikZ options%>}
every object/.style={%<TikZ options%>}
every predicate/.style={%<TikZ options%>}
every relationship/.style={%<TikZ options%>}
every constraint/.style={%<TikZ options%>}
edge from parent/.style=#subtype,suptype
orm
orm-spacious
every orm line
#endkeyvals

\entity#/tikzpicture
\entity[options%keyvals]#/tikzpicture
\value#/tikzpicture
\value[options%keyvals]#/tikzpicture
\unary#/tikzpicture
\unary[options%keyvals]#/tikzpicture
\role#/tikzpicture
\role[options%keyvals]#/tikzpicture
\binary#/tikzpicture
\binary[options%keyvals]#/tikzpicture
\roles#/tikzpicture
\roles[options%keyvals]#/tikzpicture
\ternary#/tikzpicture
\ternary[options%keyvals]#/tikzpicture
\vunary#/tikzpicture
\vunary[options%keyvals]#/tikzpicture
\vrole#/tikzpicture
\vrole[options%keyvals]#/tikzpicture
\vbinary#/tikzpicture
\vbinary[options%keyvals]#/tikzpicture
\vroles#/tikzpicture
\vroles[options%keyvals]#/tikzpicture
\vternary#/tikzpicture
\vternary[options%keyvals]#/tikzpicture
\plays#/tikzpicture
\plays[options%keyvals]#/tikzpicture
\limits
\limits[options%keyvals]
\limitsto#/tikzpicture
\limitsto[options%keyvals]#/tikzpicture
\rules#/tikzpicture

#keyvals:\entity#c,\value#c,\unary#c,\role#c,\binary#c,\roles#c,\ternary#c,\vunary#c,\vrole#c,\vbinary#c,\vroles#c,\vternary#c,\plays#c,\limits#c,\limitsto#c
## line
dash pattern=%<dash pattern%>
dash phase=%<dash phase%>
dash=%<dash pattern%> phase %<dash phase%>
solid
dotted
dashed
dash dot
line width=##L
very thin
thin
semithick
thick
very thick
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
help lines
## node: shape, text, and position
anchor=
inner sep=##L
inner xsep=##L
inner ysep=##L
outer sep=##L
outer xsep=##L
outer ysep=##L
minimum height=##L
minimum width=##L
minimum size=##L
shape aspect=
text=%color
node font=
font=
text width=##L
align=#left,flush left,right,flush right,center,flush center,justify
text height=##L
text depth=##L
anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
above=
below=
right=
left=
above=of %<node%>
below=of %<node%>
right=of %<node%>
left=of %<node%>
above left
above right
below left
below right
centered
pos=
midway
near start
near end
very near start
very near end
at start
at end
label=%<angle%>:%<text%>
## transformation
shift=%<coordinate%>
xshift=##L
yshift=##L
scale=%<scale%>
xscale=%<scale%>
yscale=%<scale%>
xslant=%<factor%>
yslant=%<factor%>
rotate=%<degree%>
rotate around={%<degree%>:coordinate}
### every xxx
every picture
every scope
every node
## others
->
<-
name path=
name=
sharp corners
rounded corners=##L
outline
color=#%color
#endkeyvals

#keyvals:\node#c,\entity#c,\value#c,\unary#c,\role#c,\binary#c,\roles#c,\ternary#c,\vunary#c,\vrole#c,\vbinary#c,\vroles#c,\vternary#c,\plays#c
role name
index=
unique
unique=
skip unique=
uniqueness bar
skipped uniqueness bar
constraint dot
cdot
constraint=#x,exclusive,unique,equal,mandatory,total required,or,preferred unique,subset,xor,partition,external,supset,irreflexive,antisymmetric,symmetric,intransitive,asymmetric,acyclic,purely reflexive,reflexive,strongly intransitive,acyclic intransitive,symmetric irreflexive,transitive,text
rule=%<mark%>
duplicated
implied
zoomed
mandatory
mdot-idot
odot-iodot
#endkeyvals

#keyvals:\draw#c
limits
limits to
subtype
suptype
subinterface
supinterface
both required
both mandatory
relation
relationship
uniqueness bar
skipped uniqueness bar
implied
#endkeyvals

\constraintdeclare{name}{path code}
\constraintdeclarealias{alias name}{existing name}
\constraintdeclareasnode{name}{TikZ code}#*

#keyvals:\begin{scope}#c
duplicated model
implied model
#endkeyvals

\ormtext
\ormbf
\ormc
\ormsup{text}
\ormsub{text}
\ormind{text}
\ormbraces{text}
\ormvalues{text}
\ormleft{text}
\ormup{text}

\tkzorm#*
\ormarrowup#*
\ormarrowdown#*
\ormarrowleft#*
\ormarrowright#*