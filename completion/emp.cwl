# emp package
# Matthew Bertucci 2/22/2022 for v1.00

#include:graphics
#include:verbatim

#keyvals:\usepackage/emp#c
# options passed to graphics
unknownkeysallowed
draft
final
hiresbb
demo
setpagesize
nosetpagesize
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
xetex
pdftex
luatex
dvisvgm
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
debugshow
hiderotate
hidescale
#endkeyvals

\begin{empfile}
\begin{empfile}[METAPOST file%file]
\end{empfile}
\begin{emp}(width,height)
\begin{emp}[name](width,height)
\end{emp}
\empuse{name}
\begin{empdef}(width,height)
\begin{empdef}[name](width,height)
\end{empdef}
\begin{empcmds}
\end{empcmds}
\begin{empgraph}(width,height)
\begin{empgraph}[name](width,height)
\end{empgraph}
\empTeX{LaTeX prelude%definition}
\empaddtoTeX{LaTeX code%definition}
\empprelude{METAPOST prelude%definition}
\empaddtoprelude{METAPOST code%definition}
\empwrite{METAPOST code%definition}

\theempfig#*
\theempfile#*

\RCS{arg1}{arg2}#S
\endRCS#S
\empfile#S
\empfile[METAPOST file%file]#S
\endempfile#S
\emp(width,height)#S
\emp[name](width,height)#S
\endemp#S
\empdef(width,height)#S
\empdef[name](width,height)#S
\endempdef#S
\empcmds#S
\endempcmds#S
\empgraph(width,height)#S
\empgraph[name](width,height)#S
\endempgraph#S
\filedate#S
\filemaintainer#S
\filename#S
\filerevision#S
\fileversion#S
