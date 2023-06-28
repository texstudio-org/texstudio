# TUDa beamertheme
# Matthew Bertucci 2/12/2022 for v3.22

#include:l3keys2e

#keyvals:\usetheme/TUDa#c
accentcolor=#%color
colortitle#true,false
colorbacktitle#true,false
colorframetitle#true,false
colorback#true,false
logo=
#endkeyvals

\filedate#S
\fileversion#S

# from TUDa fonttheme
#include:tudafonts

# from TUDa outertheme
#include:tudarules
#include:graphicx
\insertsmalllogo#*
\logo*{logo text%text}
\setupTUDaFrame{options%keyvals}
#keyvals:\setupTUDaFrame
logo#true,false
logofile=%<file%>
colorframetitle#true,false
centerframetitle#true,false
framebgcolor=#%color
singleframebgcolor=#%color
headsepline#true,false
#endkeyvals

# from TUDa innertheme
#include:trimclip
\titlegraphic*{text}

# from TUDa colortheme
#include:tudacolors