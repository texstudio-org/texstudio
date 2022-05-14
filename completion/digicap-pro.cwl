# digicap-pro package
# Matthew Bertucci 2022/05/13 for v1.3

#include:eforms
#include:graphicx
#include:graphicxbox
#include:opacity-pro

#keyvals:\usepackage/digicap-pro#c
display1
#endkeyvals

\digiCap{imagefile}{caption%text}#g
\digiCap{imagefile}[design keyvals]{caption%text}#g
\digiCap[pos keyvals%keyvals]{imagefile}{caption%text}#g
\digiCap[pos keyvals%keyvals]{imagefile}[design keyvals]{caption%text}#g
\digiCap*{imagefile}{caption%text}#g
\digiCap*{imagefile}[design keyvals]{caption%text}#g
\digiCap*[pos keyvals%keyvals]{imagefile}{caption%text}#g
\digiCap*[pos keyvals%keyvals]{imagefile}[design keyvals]{caption%text}#g

#keyvals:\digiCap,\digiCap*,\dcFirstOpt
outerboxsep=##L
vcaption=#b,c,t
hcaption=#l,c,r
inclgraphicx={%<\includegraphics keys%>}
rollovername=%<name%>
#endkeyvals

\graphicHeight
\graphicWidth

\opcolorbox{text}
\opcolorbox[options%keyvals]{text}

#keyvals:\opcolorbox,\dcSecondOpt
borderwidth=##L
fboxsep=##L
width=##L
bordercolor=#%color
bgcolor=#%color
borderop=%<factor%>
bgop=%<factor%>
textop=%<factor%>
borderblendmode=%<mode%>
bgblendmode=%<mode%>
#endkeyvals

nocolor#B

#ifOption:display1
\PicsThisDoc{{%<name1%>}{%<path1%>}{%<title1%>}{%<caption1%>}%<...%>}
\presentationOrder{name1,name2,...}
\digiDisplaySpace{height}{width}
\insertCaptions
\insertThumbs{rows}{columns}
\dcFirstOpt{pos keyvals%keyvals}
\dcFirstOpt[name]{pos keyvals%keyvals}
\dcSecondOpt{design keyvals%keyvals}
\dcSecondOpt[name]{design keyvals%keyvals}
\useRollovers
\noRollovers
\longCapFmt{format cmds}
\shortCapFmt{format cmds}
\setThumbAppearances{keyvals}
\setThumbAppearances[name]{keyvals}
#keyvals:\setThumbAppearances
normalop=%<factor%>
rolloverop=%<factor%>
downop=%<factor%>
boundarywidth
rgbcolor=%<r g b%>
cmykcolor=%<c m y k%>
#endkeyvals
\setWidthOfThumbs{width}
\addvspacetorows{length}
\digiDSWidth#*
\digiDSHeight#*
\insertPhotos#*
\normalAppr{arg}#*
\downAppr{arg}#*
\rolloverAppr{arg}#*
#endif

# not documented
\digiCapsPresets{arg}#*
\hiddenPresets#*