# tikz-palattice package
# Matthew Bertucci 4/14/2022 for v2.3

#include:tikz
#include:ifthen
#include:siunitx
#include:xargs
#include:etoolbox
#include:iflang
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibrarychains

\begin{lattice}#\pictureHighlight
\begin{lattice}[scale]
\begin{lattice}[scale][TikZ options]
\end{lattice}

\drift{length%plain}
\drift{length%plain}[name]
\dipole{name}{arc length}{bending angle}
\dipole{name}{arc length}{bending angle}[type%keyvals]
\dipole{name}{arc length}{bending angle}[type%keyvals][thickness]
#keyvals:\dipole
s
r
br
#endkeyvals
\quadrupole{name}{length%plain}
\quadrupole{name}{length%plain}[thickness]
\sextupole{name}{length%plain}
\sextupole{name}{length%plain}[thickness]
\corrector{name}{length%plain}
\corrector{name}{length%plain}[thickness]
\kicker{name}{length%plain}
\kicker{name}{length%plain}[thickness]
\cavity{name}{length%plain}
\cavity{name}{length%plain}[thickness]
\solenoid{name}{length%plain}
\solenoid{name}{length%plain}[thickness]
\beamdump{name}{length%plain}
\beamdump{name}{length%plain}[thickness]
\source{name}{length%plain}
\source{name}{length%plain}[thickness]
\screen{name}
\screen{name}[length%plain]
\valve{name}
\valve{name}[length%plain]
\marker{name}
\marker{name}[length%plain]
\start{coordinate}
\rotate{degrees}
\setangle{degrees}
\goto{coordinate}
\drawrule{coordinate}
\drawrule{coordinate}[tick distance]
\drawrule{coordinate}[tick distance][scale]
\drawrule{coordinate}[tick distance][scale][height%plain]
\legend{coordinate}
\legend{coordinate}[scale]
\completelegend{coordinate}
\completelegend{coordinate}[scale]
\setlegendtext{type%keyvals}{text}
\addlegendentry{text}{TikZ options}
\turnlabels
\northlabels
\southlabels
\rotatelabels{degrees}
\rotatelabels{degrees}[anchor]
\begin{labeldistance}{distance}
\end{labeldistance}
\setlabeldistance{distance}
\resetlabeldistance
\setlabelfont{fontsize cmd}
\setlinecolor{type%keyvals}{color}
\resetlinecolor{type%keyvals}
\setelementcolor{type%keyvals}{color}
\resetelementcolor{type%keyvals}
\setlabelcolor{color}
\begin{fade}
\begin{fade}[opacity]
\end{fade}
\savecoordinate{name}
\savecoordinate{name}[position]

#keyvals:\setlegendtext#c,\setlinecolor#c,\resetlinecolor#c,\setelementcolor#c,\resetelementcolor#c
dipole
quadrupole
sextupole
kicker
corrector
solenoid
cavity
source
screen
valve
#endkeyvals

# not documented
\angleinc#*
\corners#*
\declarecoords#*
\dist#S
\elementheight#*
\elementlabel{name}#*
\elementwidth#*
\emptycustomlegendkeys#*
\h#S
\iang#S
\iinc#*
\jinc#*
\labelanchor#*
\labelang#*
\labelcolor#*
\labeldist#*
\labelfont#*
\labelrot#*
\len#S
\markerlen#*
\marklabelang#*
\mylist#S
\points#S
\ra#S
\rectangleelement{name}{length%plain}{thickness}{type}#*
\ri#S
\saveang#S
\savelabeldist#*
\savescal#S
\scal#*
\straightlength#S
\updatelabelanchor#*
\updatemarkerlabelanchor#*
\winkel#S
