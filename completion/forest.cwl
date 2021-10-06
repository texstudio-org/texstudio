# forest package
# Matthew Bertucci 10/2/2021 for v2.1.5

#include:tikz
#include:pgfopts
#include:etoolbox
#include:elocalloc
#include:environ
#include:xparse
#include:inlinedef

\begin{forest}#\picture
\begin{forest}(config%keyvals)#*\picture
\end{forest}
\Forest{tree}
\Forest(config%keyvals){tree}#*
\Forest*{tree}
\Forest*(config%keyvals){tree}#*

#keyvals:\begin{forest}#c,\Forest#c,\Forest*#c
stages=%<keylist%>
#endkeyvals

\forestset{specs%keyvals}

#keyvals:\forestset#c
+form/.style={%<specs%>}
+format/.style={%<specs%>}
afterthought/.style={%<style%>}
also margin/.style={%<style%>}
anchors/.style={%<specs%>}
associate/.style={%<specs%>}
Autoforward register={%<register%>}{%<style def%>}
Autoforward={%<option%>}{%<style def%>}
background tree/.style={%<specs%>}
box/.style={%<specs%>}
compute xy stage/.style={%<specs%>}
decision edge label/.style n args={%<args%>}{%<specs%>}
decision tree/.style={%<specs%>}
decision/.style={%<specs%>}
declare boolean register=
declare dimen register=
declare dimen={%<dimen name%>}{%<value%>}
declare keylist=
declare toks register=
declare toks=
default preamble={%<specs%>}
define long step/.append code={%<code%>}
define long step={%<name%>}{%<options%>}{%<nodewalk%>}
definition color/.initial=#%color
definition/.style={%<specs%>}
detokenize/.style={%<specs%>}
dot/.default=##L
dot/.style={%<specs%>}
draw anchors/.default=
draw anchors/.style n args={%<args%>}{%<specs%>}
draw brackets compact/.code={%<code%>}
draw brackets wide/.code={%<code%>}
draw brackets/.style={%<specs%>}
draw tree stage/.style={%<specs%>}
el/.style={%<specs%>}
empty/.style={%<style%>}
encircle/.style={%<specs%>}
enumerate/.style={%<specs%>}
environment/.style={%<style%>}
every index begin/.style={%<specs%>}
every index end/.style={%<specs%>}
example color/.initial=#%color
example/.style={%<specs%>}
fen/.style={%<specs%>}
folder/.style={%<specs%>}
forked edge/.style={%<specs%>}
forked edge’/.style={%<specs%>}
forked edges/.default=
forked edges/.style={%<specs%>}
form/.style={%<specs%>}
form+/.style={%<specs%>}
format/.style={%<specs%>}
format’/.style={%<specs%>}
format+/.style={%<specs%>}
govern/.style={%<specs%>}
GP1/.default=
GP1/.style 2 args={%<specs%>}
handler/.style={%<style%>}
head/.style={%<specs%>}
hyper/.style={%<specs%>}
important/.style={%<specs%>}
index library/.style={%<style%>}
item/.style={%<specs%>}
macro/.style={%<specs%>}
margin/.style={%<style%>}
mark/.style={%<specs%>}
meta/.style={%<style%>}
myGP1/.style={%<specs%>}
nice empty nodes/.style={%<specs%>}
no p-govern/.style={%<specs%>}
normal color/.initial=#%color
normal/.style={%<specs%>}
option value/.style={%<style%>}
path/.style={%<style%>}
pgfkey/.style={%<style%>}
p-govern/.style={%<specs%>}
print in color/.default=
print in color/.style={%<specs%>}
random tree/.style n args={%<args%>}{%<specs%>}
roof/.style={%<specs%>}
show boundary/.style={%<style%>}
sn edges/.style={%<specs%>}
spread/.style={%<specs%>}
stages/.style={%<specs%>}
test/.style n args={%<args%>}{%<specs%>}
tt/.style={%<specs%>}
typeset nodes stage/.style={%<specs%>}
xlist/.default=
xlist/.style={%<specs%>}
#endkeyvals

\useforestlibrary{libraries}
\useforestlibrary[options%keyvals]{libraries}
\useforestlibrary*{libraries}
\useforestlibrary*[options%keyvals]{libraries}
\forestapplylibrarydefaults{libraries}

#keyvals:\useforestlibrary,\useforestlibrary*
external#true,false
compat=
tikzcshack#true,false
tikzinstallkeys#true,false
debug=#nodewalks,dynamics,process
#endkeyvals

\forestcompat{arg}#*

\forestoption{option}
\foresteoption{option}
\forestregister{register}
\foresteregister{register}

\bracketset{bracket options%keyvals}

#keyvals:\bracketset
opening bracket=%<character%>
closing bracket=%<character%>
action character=%<character%>
#endkeyvals

\bracketResume

\forestStandardNode[node]{code}{calibration}{export}#*

#ifOption:external
\tikzexternalize
\tikzexternalenable
\tikzexternaldisable
#endif