# yquant package
# Matthew Bertucci 2022/12/25 for v0.7.2

#include:etoolbox
#include:tikz
#include:trimspaces
#include:xkeyval
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.pathmorphing

#keyvals:\usepackage/yquant#c
compat=#newest,0.3,0.4,0.6
#endkeyvals

\ifyquantdebug#S
\yquantdebugtrue#S
\yquantdebugfalse#S

\useyquantlanguage{language%keyvals}

#keyvals:\useyquantlanguage#c
groups
qasm
#endkeyvals

# from yquant-tools.tex
\listA#S
\listB#S
\ifsuccess#S

# from yquant-shapes.tex
\clippathhorz{path code}#*
\clippathvert{path code}#*
\clippath{path code}#*
\inheritclippath[from=%<shape%>]#*
\pgfshapeclippath{shape}{options}#*
\pgfreferencednodename#*
\oldpgflinewidth#S
\pgfshapeclippathresult#*
\pgfshapeclippathhorzresult#*
\pgfshapeclippathvertresult#*
\stext#S
\main#S
\ifhorz{true}{false}#*
\pgfdecorationsegmentfromto#*

# from yquant-config.tex
\ifyquanthorz{if horz}{if vert}

# from yquant-registers.tex
\len
\reg
\idx
\regidx
\ifinmulti#*
\ifallowmain#*
\registers{registers}
\newlist#S

# from yquant-env.tex
\ifyquantmeasuring#*
\yquantmeasuringtrue#*
\yquantmeasuringfalse#*
\redolist#S
\max#S
\firstinout#S
\lastinout#S
\outerlevel#S
\outery#S
\multidata#S
\missing#S
\divisor#S
\add#S
\inc#S
\yquant#S
\endyquant#S
\begin{yquant}
\begin{yquant}[options%keyvals]
\end{yquant}
\begin{yquant*}
\begin{yquant*}[options%keyvals]
\end{yquant*}
\yquantset{options%keyvals}
\yquantsecondpass{code}
\yquantesecondpass{code}
\yquantescape{code}
\yquanteescape{code}
\yquantimportcommand{file}#*i
\yquantimportpath#*
\yquantimport{file}#i
\yquantimport[options%keyvals]{file}#i
\yquantimport*{file}#i
\yquantimport*[options%keyvals]{file}#i

# from yquant-langhelper.tex
\cmd#S
\keyscmd#S
\keysset#S
\keyscheck#S
\params#S
\ifvalid#*

# from yquant-circuit.tex
\wirexpos#*
\wirexprevpos#*
\wiretype#*
\wirelast#*
\Ifnum
\Ifcase
\Or
\Else
\Fi
\Unless
\The

# from yquant-prepare.tex
\outermap#S
\nodename#S
\upd#S
\last#S
\newx#S

# from yquant-draw.tex
\process#S
\nonaffectedpgfshapeclippathhorzresult#*
\wirestyle#*
\wireclipping#*

# from yquant-lang.tex
\yquantdefinegate{name}{content}
\yquantdefinegate{name}[style]{content}
\yquantredefinegate{name}{content}
\yquantredefinegate{name}[style]{content}
\yquantdefinebox{name}{content}
\yquantdefinebox{name}[style]{content}
\yquantdefinemultibox{name}{content}
\yquantdefinemultibox{name}[style]{content}
\yquantredefinebox{name}{content}
\yquantredefinebox{name}[style]{content}
\yquantredefinemultibox{name}{content}
\yquantredefinemultibox{name}[style]{content}

## << keyvals >> ##
#keyvals:\begin{yquant}#c,\begin{yquant*}#c,\yquantset#c,\yquantimport#c,\yquantimport*#c,\begin{yquantgroup}#c,\begin{yquantgroup*}#c
#  Circuit layout #
register/minimum height=##L
register/minimum depth=##L
register/minimum left=##L
register/minimum right=##L
register/minimum before=##L
register/minimum after=##L
register/separation=##L
operator/minimum width=##L
operator/minimum extent=##L
operator/separation=##L
operator/multi warning#true,false
drawing mode=#quality,size
default background
default fill
# Register creation #
register/default name=%<name%>
register/default lazy name=%<name%>
every label/.style={%<TikZ keys%>}
every label/.append style={%<TikZ keys%>}
every initial label/.style={%<TikZ keys%>}
every qubit label/.style={%<TikZ keys%>}
every cbit label/.style={%<TikZ keys%>}
every qubits label/.style={%<TikZ keys%>}
every multi label/.style={%<TikZ keys%>}
every input label/.style={%<TikZ keys%>}
# Register outputs #
every output/.append style={%<TikZ keys%>}
every qubit output/.append style={%<TikZ keys%>}
every cbit output/.append style={%<TikZ keys%>}
every qubits output/.append style={%<TikZ keys%>}
every multi output/.append style={%<TikZ keys%>}
# General styling #
every circuit/.style={%<TikZ keys%>}
every wire/.style={%<TikZ keys%>}
every qubit wire/.style={%<TikZ keys%>}
every cbit wire /.style={%<TikZ keys%>}
every qubits wire/.style={%<TikZ keys%>}
every control line/.style={%<TikZ keys%>}
every control/.append style={%<TikZ keys%>}
every positive control/.append style={%<TikZ keys%>}
every negative control/.append style={%<TikZ keys%>}
every operator/.prefix style={%<TikZ keys%>}
every multi line/.style={%<TikZ keys%>}
this operator/.style={%<TikZ keys%>}
this control/.style={%<TikZ keys%>}
operator style={%<TikZ keys%>}
control style={%<TikZ keys%>}
style={%<TikZ keys%>}
operator/multi as single/.style={%<TikZ keys%>}
operator/if multi={%<TikZ keys%>}
circuit/seamless#true,false
circuit/orientation=#horizontal,vertical
horizontal
vertical
vertical=%<degrees%>
every post measurement control=#indirect,direct
# Styles for operators #
operators/every barrier/.style={%<TikZ keys%>}
operators/every barrier/.append style={%<TikZ keys%>}
operators/every box/.append style={%<TikZ keys%>}
operators/every custom gate/.append style={%<TikZ keys%>}
operators/every dmeter/.append style={%<TikZ keys%>}
operators/every h/.append style={%<TikZ keys%>}
operators/every inspect/.append style={%<TikZ keys%>}
operators/every iswap/.style={%<TikZ keys%>}
operators/every measure/.append style={%<TikZ keys%>}
operators/every measure meter/.append style={%<TikZ keys%>}
operators/every not/.append style={%<TikZ keys%>}
operators/every pauli/.append style={%<TikZ keys%>}
operators/every phase/.append style={%<TikZ keys%>}
operators/every rectangular box/.append style={%<TikZ keys%>}
operators/every slash/.append style={%<TikZ keys%>}
operators/every subcircuit/.append style={%<TikZ keys%>}
operators/every subcircuit box/.append style={%<TikZ keys%>}
subcircuit box style={%<TikZ keys%>}
operators/this subcircuit box
this subcircuit box style={%<TikZ keys%>}
operators/subcircuit/frameless
operators/subcircuit/name mangling=#prefix or discard,prefix or transparent,transparent,discard
operators/subcircuit/name mangling reset#true,false
operators/subcircuit/seamless
operators/every swap/.style={%<TikZ keys%>}
operators/every text/.style={%<TikZ keys%>}
operators/every wave/.style={%<TikZ keys%>}
operators/every x/.style={%<TikZ keys%>}
operators/every xx/.style={%<TikZ keys%>}
operators/every y/.style={%<TikZ keys%>}
operators/every z/.style={%<TikZ keys%>}
operators/every zz/.style={%<TikZ keys%>}
# not documented
every nobit output/.style={%<TikZ keys%>}
#endkeyvals

# from yquantlanguage-groups.sty v0.7 (loaded with \useyquantlanguage{groups})
\begin{yquantgroup}
\begin{yquantgroup}[options%keyvals]
\end{yquantgroup}
\begin{yquantgroup*}
\begin{yquantgroup*}[options%keyvals]
\end{yquantgroup*}
\circuit{content}
\circuit[style]{content}
\equals
\equals[content]
\equals*
\equals*[content]
\shiftright
\shiftright[where]
\shiftright*
\shiftright*[where]

#keyvals:\yquantset#c,\begin{yquantgroup}#c,\begin{yquantgroup*}#c
group/every group/.style={%<TikZ keys%>}
group/line separation=##L
group/aligned#true,false
operators/every group circuit/.style={%<TikZ keys%>}
operators/every group equals/.style={%<TikZ keys%>}
#endkeyvals

#keyvals:\begin{yquantgroup}#c,\begin{yquantgroup*}#c
preamble={%<TikZ keys%>}
#endkeyvals

# from yquantlanguage-qasm.sty v0.6 (loaded with \useyquantlanguage{qasm})
\begin{qasm}
\end{qasm}
\m
\txt
\meter
\dmeter
\dmeterwide
\qasmimport{file}#i
\targets#S
\controls#S
\qasmname{arg}#*

#keyvals:\yquantset#c
operators/every s/.style={%<TikZ keys%>}
operators/every t/.style={%<TikZ keys%>}
operators/every utwo/.style={%<TikZ keys%>}
zero=%<code%>
register/default qubit name=%<code%>
register/default qubit name value=%<code%>
#endkeyvals
