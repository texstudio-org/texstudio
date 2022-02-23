# dot2texi package
# Matthew Bertucci 2/22/2022 for v3.0p1

#include:moreverb
#include:xkeyval

#keyvals:\usepackage/dot2texi
shell
noshell
forceshell
miktex
pgf
tikz
pstricks
autosize
dot
neato
circo
fdp
twopi
outputdir=%<directory%>
debug
#endkeyvals

\setoutputdir{directory%definition}

\begin{dot2tex}
\begin{dot2tex}[options%keyvals]
\end{dot2tex}

#keyvals:\begin{dot2tex}
shell
noshell
dot
neato
circo
fdp
twopi
prog=#dot,neato,circo,fdp,twopi
pgf
tikz
pstricks
format=#tikz,pgf,pstricks
styleonly
codeonly
autosize
noautosize
straightedges
tikzedgelabels
mathmode
graphstyle={%<TikZ options%>}
scale=%<factor%>
outputdir=%<directory%>
file=%<file name%>
options={%<dot2tex options%>}
#endkeyvals

\BeforeStream#*
\dottotexCutFile#*
\dottotexgraphicsinclude#*
\dottotexgraphicsprocess#*
\begin{dottotexverbatimwrite}{file}#*
\end{dottotexverbatimwrite}#*
\dottotexverbatimwrite{file}#S
\enddottotexverbatimwrite#S