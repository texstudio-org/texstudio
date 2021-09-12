# dynkin-diagrams package
# Matthew Bertucci 9/10/2021 for v3.1415926535897932

#include:tikz
#include:xparse
#include:xstring
#include:etoolbox
#include:expl3
#include:pgfkeys
#include:pgfopts
#include:amsmath
#include:amssymb
#include:mathtools

\dynkin{%<letter%>}{%<rank%>}
\dynkin[%<options%>]{%<letter%>}{%<rank%>}
##\dynkin[%<options%>]{%<letter%>}[%<twisted rank%>]{%<rank%>}#*
\begin{dynkinDiagram}{%<letter%>}{%<rank%>}#\picture
\begin{dynkinDiagram}[%<options%>]{%<letter%>}{%<rank%>}#\picture
\begin{dynkinDiagram}[%<options%>]{%<letter%>}[%<twisted rank%>]{%<rank%>}#*\picture
\end{dynkinDiagram}
\pgfkeys{keyvals}#S
\dynkinName[%<options%>]{%<letter%>}{%<rank%>}#*

#keyvals:\dynkin#c,\begin{dynkinDiagram}#c,\pgfkeys#c,\tikzset#c,\dynkinName#c
*/.style={%<style specs%>}
affine mark=#o,O,*,t,x,X
arrow shape/.style={%<style specs%>}
arrow style={%<style specs%>}
arrow width=##L
arrows#true,false
backwards
bird arrow
Bourbaki arrow
ceref
Coxeter
double edges
double fold
double fold left
double fold right
double left
double right
edge label/.style={%<style specs%>}
edge length=##L
edge/.style={%<style specs%>}
extended
fold
fold left
fold left style/.style={%<style specs%>}
fold radius=##L
fold right
fold right style/.style={%<style specs%>}
fold style/.style={%<style specs%>}
gonality=
horizontal shift=##L
indefinite edge/.style={%<style specs%>}
indefinite-edge=
indefinite-edge-ratio=
involution/.style={%<style specs%>}
involutions=
Kac
Kac arrows
label
label depth=
label directions=
label height=
label macro*/.code={%<code%>}
label macro*=
label macro/.code={%<code%>}
label macro=
label* direction=
labels*={%<label list%>}
labels={%<label list%>}
make indefinite edge/.list={%<i1-j1,i2-j2,...%>}
make indefinite edge={%<i-j%>}
mark=#o,O,*,t,x,X
name=
o/.append style={%<style specs%>}
o/.style={%<style specs%>}
O/.style={%<style specs%>}
odd
ordering=#Kac,Dynkin,Adams,Bourbaki,Carter
parabolic=%<integer%>
ply=#0,1,2,3,4
reverse arrows
root radius=##L
scale=
t/.style={%<style specs%>}
text style/.style={%<style specs%>}
text style={%<style specs%>}
upside down
vertical shift=##L
x/.style={%<style specs%>}
X/.style={%<style specs%>}
#endkeyvals

#keyvals:\pgfkeys#c,\tikzset#c
/Dynkin diagram
#endkeyvals

\dynkinFold{start}{end}#/dynkinDiagram
\dynkinFold[options%keyvals]{start}{end}#/dynkinDiagram

#keyvals:\dynkinFold#c
bend right=
#endkeyvals

\drlap{arg}
\dynkinBrace[label%plain]{start}{end}#/dynkinDiagram
\dynkinBrace*[label%plain]{start}{end}#/dynkinDiagram
\dynkinRootMark{symbol}#*/dynkinDiagram
\dynkinOrder#*
\dynkinQuadrupleEdge{start}{end}#/dynkinDiagram
\dynkinTripleEdge{start}{end}#/dynkinDiagram
\dynkinQuadrupleEdge{start}{end}#/dynkinDiagram
\dynkinDefiniteDoubleEdge{start}{end}#/dynkinDiagram
\dynkinSouth#*/dynkinDiagram