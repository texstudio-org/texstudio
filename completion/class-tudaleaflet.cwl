# tudaleaflet class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:class-leaflet
#include:scrextend
#include:scrlayer
#include:tudarules
#include:tudafonts

#keyvals:\documentclass/tudaleaflet#c
color=#%color
accentcolor=#%color
textaccentcolor=#%color
identbarcolor=#%color
logofile=%<Dateipfad%>
colorback#true,false
colorbacktitle#true,false
colorbacksubtitle#true,false
sponsor=#title,lastfoot,manual
#endkeyvals

\sectionlinesformat{text}#*
\raggedtitle
\AddSponsor{logo}
\sponsors{logo code}
\footergraphics{graphics code}
\titleimage{graphics code}
\addTitleBox{text}
\addTitleBoxLogo{imagefile}#g
\addTitleBoxLogo{graphics code}
\insertSponsors