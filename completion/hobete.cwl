# hobete package
# Matthew Bertucci 2/12/2022

#include:l3keys2e
#include:xfrac
#include:tikz
#include:beamerthemehohenheim

#keyvals:\usepackage/hobete#c
poster#true,false
framelist front=%<code%>
framelist back=%<code%>
#endkeyvals

\hoversion#*
\insertmylogo#*
\mylogo{graphics code}
\sectionpage
\sectionpage[options%keyvals]
#keyvals:\sectionpage#c
plain#true,false
#endkeyvals
\oldframetitle#S
\printframelist
\HohenheimLogoKlein{imagefile}#*
\HohenheimLogoLang{imagefile}#*
\inserthotpwolang#*
\inserthotpwokurz{content%text}#*
\inserthotp{content%text}#*
\HohenheimFancyTitle{text}#*

#ifOption:poster=true
\thetgpostercount#*
\begin{posterblock}{title%text}
\end{posterblock}
\begin{outerretainblock}
\end{outerretainblock}
\insertemail#*
\posteremail{email%URL}#U
\insertwebsite#*
\posterwebsite{URL}#U
#endif