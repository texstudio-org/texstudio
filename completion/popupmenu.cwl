# popupmenu package
# Matthew Bertucci 2/8/2022 for v1.2

#include:xkeyval
#include:eforms

#keyvals:\usepackage/popupmenu#c
tracking
!tracking
#endkeyvals

\begin{popupmenu}{name%text}
\end{popupmenu}
\item{keyvals}
\begin{submenu}{keyvals}
\end{submenu}

#keyvals:\item,\begin{submenu}
title=%<string%>
marked#true,false
#endkeyvals

#keyvals:\item
enabled#true,false
return=%<string%>
#endkeyvals

\puUseMenus{menu array names}
\popUpMenu(name)
\puProcessMenu(name)

\urlPath{path%URL}
\Esc
\cs{csname}

\itemindex#*
\submenuLevel#*
\csiv#S
\msarg#S
\msargEx#S
\puUseTheseMenus#*
\puMenuCmds#*
\puNone#*
\puTracking#*
\iftrackingPU#*
\trackingPUfalse#*
\trackingPUtrue#*