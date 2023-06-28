# termsim package
# Matthew Bertucci 1/9/2021 for v1.1.1

#include:xtemplate
#include:l3keys2e
#include:fontawesome5
#include:varwidth
#include:amssymb
#include:xcolor
#include:etoolbox
#include:minted
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:tcolorboxlibrarybreakable
#include:tikzlibraryshapes.geometric

\begin{terminal}{title%text}#V
\begin{terminal}[options%keyvals]{title%text}#V
\end{terminal}
\begin{terminal*}[options%keyvals][comments%text]{title%text}#V
\end{terminal*}

\termfile{title%text}{file}
\termfile[options%keyvals]{title%text}{file}
\termfile*[options%keyvals][comments%text]{title%text}{file}

\termset{options%keyvals}

#keyvals:\begin{terminal},\begin{terminal*},\termfile,\termfile*,\termset
minted#true,false
os=#win10,mac,ubuntu
theme=#dark,light,white
shstyle=%<style%>
shsize=%<font size command%>
commentf=%<format commands%>
shstretch=%<factor%>
#endkeyvals

mpurple#B
mgray#B
ogray#B
oorange#B
termimal#B
linux#B
windows#B
cvgrayc#B
cvgray#B
cvgrayb#B
cvblue#B
zhanqing#B
chengse#B
AppleRed#B
AppleYellow#B
AppleGreen#B
AppleGray#B
WinGray#B
WinBlue#B

\UbuntuMin#*
\UbuntuClose#*
\UbuntuMax#*
\WindowsLogo#*
