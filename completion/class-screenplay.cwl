# screenplay class
# Matthew Bertucci 4/7/2022 for v1.6

#include:ifthen
#include:geometry
#include:courier

\realauthor{name}
\address{address}
\agent{name}
\coverpage
\nicholl

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
\centretitle{text}
\intercut
\pov
\revert
\fadeout
\theend

\addrseplen#*
\addrwidth#*
\byskip#*
\bytext#*
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
\sccentre{text}#*
\sepintext#*
\scflushright{text}#*
\slugspace#*
\slug{pretext}{description%text}#*
\slug[time]{pretext}{description%text}#*
\thirty#*
\titheadskip#*
\titleovertext#*
\titskip#*
\widthgutter#*