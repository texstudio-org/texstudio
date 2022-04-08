# screenplay-pkg package
# Matthew Bertucci 4/7/2022 for v1.1

#include:ifthen
#include:setspace

\begin{screenplay}
\end{screenplay}

\fadein
\intslug{description%text}
\intslug[time]{description%text}
\extslug{description%text}
\extslug[time]{description%text}
\intextslug{description%text}
\intextslug[time]{description%text}
\extintslug{description%text}
\extintslug[time]{description%text}
\begin{dialogue}{character name}
\begin{dialogue}[directions%text]{character name}
\end{dialogue}
\paren{text}
\dialbreak{character name}
\dialbreak[directions%text]{character name}
\begin{titleover}
\end{titleover}
\titbreak
\centertitle{text}
\centretitle{text}#*
\intercut
\pov
\revert
\fadeout
\theend

\screenspacing{spacing}
\screenfont{font commands}

\contd#*
\dialfix#*
\dialgutter#*
\dialnametab#*
\dialtab#*
\dialwidth#*
\exttext#*
\fadeintext#*
\fadeouttext#*
\intercuttext#*
\inttext#*
\more#*
\parentab#*
\parenwidth#*
\placesep#*
\punctchar#*
\sccenter{text}#*
\sccentre{text}#*
\sepintext#*
\scflushright{text}#*
\slugspace#*
\slug{pretext}{description%text}#*
\slug[time]{pretext}{description%text}#*
\thirty#*
\titleovertext#*
\widthgutter#*