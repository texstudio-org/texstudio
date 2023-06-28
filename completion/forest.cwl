# forest package
# Matthew Bertucci 2022/07/06 for v2.1.5

#include:tikz
#include:tikzlibraryshapes
#include:tikzlibraryfit
#include:tikzlibrarycalc
# loads intersections pgflibrary
#include:pgfopts
#include:etoolbox
#include:elocalloc
#include:environ
#include:inlinedef

#keyvals:\usepackage/forest#c
external
linguistics
#endkeyvals

#ifOption:external
#include:tikzlibraryexternal
#endif

#ifOption:linguistics
\standardnodestrut#*
\standardnodestrutbox#*
\text{text}
#endif

\begin{forest}#\pictureHighlight
\begin{forest}(config%keyvals)#*
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
declare boolean register=%<register name%>
declare dimen register=%<register name%>
declare dimen={%<dimen name%>}{%<default value%>}
declare keylist={%<option name%>}{%<default value%>}
declare toks register=%<register name%>
declare toks={%<option name%>}{%<default value%>}
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
compat={%<compat keylist%>}
tikzcshack#true,false
tikzinstallkeys#true,false
debug=#nodewalks,dynamics,process
#endkeyvals

\forestcompat{compat keylist}#*

\forestoption{option}
\foresteoption{option}
\forestregister{register}
\foresteregister{register}

\bracketset{bracket options%keyvals}

#keyvals:\bracketset#c
opening bracket=%<character%>
closing bracket=%<character%>
action character=%<character%>
#endkeyvals

\bracketResume

\forestStandardNode[node]{code}{calibration}{export}#*

# not documented
\apptotoks{arg1}{arg2}#*
\bracketEndParsingHook#*
\bracketParse{arg1}{arg2}#*
\eapptotoks{arg1}{arg2}#*
\epretotoks{arg1}{arg2}#*
\etotoks{arg1}{arg2}#*
\ExpandIfF{arg1}{arg2}#*
\ExpandIfT{arg1}{arg2}#*
\ExpandIfTF{arg1}{arg2}{arg3}#*
\expandnumberarg{arg1}{arg2}#*
\expandthreenumberargs{arg1}{arg2}{arg3}{arg4}#*
\expandtwonumberargs{arg1}{arg2}{arg3}#*
\forestanchortotikzanchor{arg1}{arg2}#*
\forestdebugdynamicsfalse#S
\forestdebugdynamicstrue#S
\forestdebugfalse#S
\forestdebugnodewalksfalse#S
\forestdebugnodewalkstrue#S
\forestdebugprocessfalse#S
\forestdebugprocesstrue#S
\forestdebugtempfalse#S
\forestdebugtemptrue#S
\forestdebugtrue#S
\forestdebugtypeouttree(arg)#*
\forestdebugtypeouttree(arg)[opt]#*
\forestdebugtypeouttreenodeinfo#*
\forestdebugtypeouttrees#*
\forestdebugtypeouttrees[opt]#*
\forestdebugtypeouttreesprefix#*
\forestdebugtypeouttreessuffix#*
\forestloopbreak#*
\forestloopBreak{arg}#*
\forestloopcount#*
\forestloopCount{arg}#*
\forestmathadd{arg1}{arg2}#*
\forestmathdivide{arg1}{arg2}#*
\forestmatheq{arg1}{arg2}#*
\forestmathfalse#*
\forestmathgt{arg1}{arg2}#*
\forestmathlt{arg1}{arg2}#*
\forestmathmax#*
\forestmathmin#*
\forestmathmultiply{arg1}{arg2}#*
\forestmathparse{arg}#*
\forestmathresult#*
\forestmathresulttype#*
\forestmathsetcount{arg1}{arg2}#*
\forestmathsetlength{arg1}{arg2}#*
\forestmathsetlengthmacro{arg1}{arg2}#*
\forestmathsetmacro{arg1}{arg2}#*
\forestmathsettypefrom{arg}#*
\forestmathtrue#*
\forestmathtruncatemacro{arg1}{arg2}#*
\forestmathzero#*
\forestnovalue#*
\forestoappto{arg1}{arg2}#*
\forestOappto{arg1}{arg2}{arg3}#*
\forestOeappto{arg1}{arg2}{arg3}#*
\forestOepreto{arg1}{arg2}{arg3}#*
\forestoeset{arg1}{arg2}#*
\forestOeset{arg1}{arg2}{arg3}#*
\forestoget{arg1}{arg2}#*
\forestOget{arg1}{arg2}{arg3}#*
\forestoifdefined{arg1}{arg2}{arg3}#*
\forestOifdefined{arg1}{arg2}{arg3}{arg4}#*
\forestoinit{arg}#*
\forestolet{arg1}{arg2}#*
\forestOlet{arg1}{arg2}{arg3}#*
\forestoleto{arg1}{arg2}#*
\forestOleto{arg1}{arg2}{arg3}#*
\forestoletO{arg1}{arg2}{arg3}#*
\forestOletO{arg1}{arg2}{arg3}{arg4}#*
\forestom{arg}#*
\forestOm{arg1}{arg2}#*
\forestOpreto{arg1}{arg2}{arg3}#*
\forestoset{arg1}{arg2}#*
\forestOset{arg1}{arg2}{arg3}#*
\forestov{arg}#*
\forestOv{arg1}{arg2}#*
\forestove{arg}#*
\forestOve{arg1}{arg2}#*
\forestrappto{arg1}{arg2}#*
\forestreset{arg1}{arg2}#*
\forestrget{arg1}{arg2}#*
\forestrifdefined{arg1}{arg2}{arg3}#*
\forestrlet{arg1}{arg2}#*
\forestrm{arg1}#*
\forestRNOget{arg1}{arg2}#*
\forestrpreto{arg1}{arg2}#*
\forestrset{arg1}{arg2}#*
\forestrv{arg1}#*
\forestrve{arg1}#*
\foresttemp#S
\foresttikzcshackfalse#S
\foresttikzcshacktrue#S
\gapptotoks{arg1}{arg2}#*
\gpretotoks{arg1}{arg2}#*
\ifforestdebug#S
\ifforestdebugdynamics#S
\ifforestdebugnodewalks#S
\ifforestdebugprocess#S
\ifforestdebugtemp#S
\ifforesttikzcshack#S
\InlineNoDef{arg}#*
\lapptotoks{arg1}{arg2}#*
\makehashother#*
\NewInlineCommand[args]{cmd}{def}#*d
\NewInlineCommand{cmd}{def}#*d
\newloop{cmd}#*d
\newsafeloop{name}#*
\newsafeRKloop{name}#*
\pretotoks{arg1}{arg2}#*
\ProvidesForestLibrary{name}#*
\ProvidesForestLibrary{name}[release info]#*
\safeloop#*
\safeloopn#*
\saferepeat#*
\safeRKloop#*
\safeRKloopn#*
\safeRKrepeat#*
\xapptotoks{arg1}{arg2}#*
\xpretotoks{arg1}{arg2}#*
