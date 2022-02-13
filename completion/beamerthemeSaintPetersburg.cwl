# SaintPetersburg beamertheme
# Matthew Bertucci 2/10/2022

#include:graphicx
#include:tikz

#keyvals:\usetheme/SaintPetersburg#c
poster
nologo
#endkeyvals

\spbuInsertField{beamer-color}#*
\othergraphic{graphics code}
\insertothergraphic#*
\leftcolumnwidth{width}
\insertleftcolumnwidth#*
\rightcolumnwidth{width}
\insertrightcolumnwidth#*
\middlecolumnwidth{width}
\insertmiddlecolumnwidth#*

# from SaintPetersburg colortheme
spbuTerracotta#B
spbuGray#B
spbuWhite1#B
spbuWhite2#B
spbuWhite3#B
spbuWhiteRed2#B
spbuWhiteRed3#B
spbuRed#B
spbuDarkGray#B
spbuDarkGray2#B

# from SaintPetersburg fonttheme
#include:FiraMono
#include:opensans
#include:ifxetex
\cyrillicfont#*
\cyrillicfontrm#*
\cyrillicfontsf#*
\cyrillicfonttt#*