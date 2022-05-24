# bookmark package
# Matthew Bertucci 2022/05/24 for v1.29

#include:hyperref

#keyvals:\usepackage/bookmark#c
draft
final
atend
pdftex
dvips
dvipdfm
dvipdfmx
xetex
vtex
#endkeyvals

\bookmarksetup{options%keyvals}
\bookmarksetupnext{options%keyvals}
\bookmark{title%text}
\bookmark[options%keyvals]{title%text}
\bookmarkdefinestyle{name}{options%keyvals}

#keyvals:\bookmarksetup,\bookmarksetupnext,\bookmark,\bookmarkdefinestyle,\usepackage/bookmark#c
bold#true,false
italic#true,false
color=%<color%>
color=[%<model%>]{%<color spec%>}
dest=%<destination name%>
page=%<number%>
view={%<view specs%>}
named=#FirstPage,LastPage,NextPage,PrevPage
gotor=%<file%>
uri={%<uri%>}
rawaction=%<action spec%>
level=%<integer%>
rellevel=%<integer%>
keeplevel#true,false
startatroot#true,false
style=%<style name%>
addtohook=%<code%>
depth=%<integer%>
open#true,false
openlevel=%<integer%>
numbered#true,false
#endkeyvals

\bookmarkget{option%keyvals}

#keyvals:\bookmarkget
bold
italic
open
depth
dest
color
gotor
level
named
openlevel
page
rawaction
uri
view
text
#endkeyvals

#ifOption:atend
\BookmarkAtEnd{code}
#endif

\BookmarkDriverDefault#*
\calc{expression}#*
