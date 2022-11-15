# BFH beamertheme
# Matthew Bertucci 2022/11/15 for v2.1.4

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
\separatorpage{type}#*
\separatorpage*{type}#*

# from BFH colortheme
#include:bfhcolors
