# flabels package
# Matthew Bertucci 2023/03/14 for v1.0

#keyvals:\usepackage/flabels#c
leitz
fullheight
narrow
color
a4paper
nice
nohole
#endkeyvals

#ifOption:color
#include:color
\setbgcompany{color}
\setfgcompany{color}
\setbglabel{color}
\setfglabel{color}
#endif

\narrowlabels
\widelabels
\fullheight
\normalheight
\company{name}
\thenumberauxlines#*
\auxlinedistance{length}
\companylabelheight
\ylowercompany
\yuppercompany

\extratopmargin{length}
\hspaceinterlabel
\labeltextmargin

\emptylabel{number}
\labeltext{text}