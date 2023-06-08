# mode: multicol.sty
# dani/2006-02-18
# updated 2023/06/08 for v1.9f

#keyvals:\usepackage/multicol#c
errorshow
infoshow
balancingshow
markshow
debugshow
grid
colaction
#endkeyvals

\begin{multicols*}{n}
\begin{multicols*}{n}[preface]
\begin{multicols*}{n}[preface][skip]
\begin{multicols}{n}
\begin{multicols}{n}[preface]
\begin{multicols}{n}[preface][skip]
\columnbreak
\columnseprulecolor#*
\docolaction{first}{middle}{last}
\end{multicols*}
\end{multicols}
\flushcolumns
\LRmulticolcolumns#*
\maxbalancingoverflow#*
\multicolbaselineskip#*
\multicolmindepthstring#*
\multicolpretolerance#*
\multicolsep#*
\multicoltolerance#*
\newcolumn
\postmulticols#*
\premulticols#*
\raggedcolumns
\RLmulticolcolumns#*
\setemergencystretch{num of cols}{hsize}#*
\vfilmaxdepth#*
