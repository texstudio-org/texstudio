# BFH beamertheme
# Matthew Bertucci 2/12/2022 for v2.0.0

#keyvals:\usetheme/BFH#c
logofile=%<file%>
authorontitle#true,false
#endkeyvals

\version{version}
\insertversion#*
\versionformat{text%plain}#*

# from BFH fonttheme
#include:bfhfonts

# from BFH outertheme
#include:l3keys2e

# from BFH innertheme
#include:trimclip
#include:bfhlogo
\partnerlogo{graphics code}
\insertpartnerlogo#*
\titlegraphic*{text}
\inserttitleVcenter{text}
\lecturepage#*

# from BFH colortheme
#include:bfhcolors