# gnuplottex package
# Matthew Bertucci 2/5/2022 for v0.9.5

#include:graphicx
#include:moreverb
#include:keyval
#include:ifthen
#include:catchfile

#keyvals:\usepackage/gnuplottex#c
shell
noshell
miktex
siunitx
cleanup
subfolder
#endkeyvals

\begin{gnuplot}
\begin{gnuplot}[options%keyvals]
\end{gnuplot}

\gnuplotloadfile{file}
\gnuplotloadfile[options%keyvals]{file}

#keyvals:\begin{gnuplot},\gnuplotloadfile
scale=%<factor%>
terminal=#latex,epslatex,jpeg,cairolatex,eepic,emtex,tikz
terminaloptions=%<terminal options%>
#endkeyvals

\ifShellEscape#*
\ShellEscapetrue#*
\ShellEscapefalse#*
\ifmiktex#*
\miktextrue#*
\miktexfalse#*
\ifusesiunitx#*
\usesiunitxtrue#*
\usesiunitxfalse#*
\ifcleanup#*
\cleanuptrue#*
\cleanupfalse#*
\ifusesubfolder#*
\usesubfoldertrue#*
\usesubfolderfalse#*

\tmpfile#S
\subfolder#S
\thefignum#S
\figname#S
\usesiunitxingnuplot#*
\gnuplotverbatimwrite{arg}#S
\endgnuplotverbatimwrite#S
\BeforeStream#S
\gnuplotterminal#*
\gnuplotterminaloptions#*
\gnuplotscale#*
\gnuplotCutFile#*
\extension#S
\gnuplotgraphicsprocess#*
\gnuplotgraphicsinclude#*
\gnuplotloadfilewrite{arg1}{arg2}#*
