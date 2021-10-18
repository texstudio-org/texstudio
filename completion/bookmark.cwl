# bookmark package
# Matthew Bertucci 10/17/2021 for v1.29

#include:hyperref

\bookmarksetup{options%keyvals}
\bookmarksetupnext{options%keyvals}
\bookmark{title%text}
\bookmark[options%keyvals]{title%text}
\bookmarkdefinestyle{name}{options%keyvals}

#keyvals:\bookmarksetup,\bookmarksetupnext,\bookmark,\bookmarkdefinestyle
bold#true,false
italic#true,false
color=
dest=%<destination name%>
page=%<number%>
view={%<view specs%>}
named=#FirstPage,LastPage,NextPage,PrevPage
gotor=%<file%>
uri=
rawaction=
level=%<integer%>
rellevel=%<integer%>
keeplevel#true,false
startatroot#true,false
style=
addtohook=%<code%>
depth=
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