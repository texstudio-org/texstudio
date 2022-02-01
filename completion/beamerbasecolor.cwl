# beamerbasecolor package
# Matthew Bertucci 1/30/2022 for v3.65

\setbeamercolor{beamer-color name}{options}
\setbeamercolor*{beamer-color name}{options}

#keyvals:\setbeamercolor,\setbeamercolor*
fg=#%color
bg=#%color
parent={%<parent beamer colors%>}
use=%<beamer color%>
#endkeyvals

\ifbeamercolorempty{beamer-color name}{if undefined}{if defined}
\ifbeamercolorempty[fg or bg%keyvals]{beamer-color name}{if undefined}{if defined}
\usebeamercolor{beamer-color name}
\usebeamercolor[fg or bg%keyvals]{beamer-color name}
\usebeamercolor*{beamer-color name}
\usebeamercolor*[fg or bg%keyvals]{beamer-color name}

#keyvals:\ifbeamercolorempty,\usebeamercolor,\usebeamercolor*
fg
bg
#endkeyvals

fg#B
bg#B

\begin{beamercolorbox}{beamer color}
\begin{beamercolorbox}[options%keyvals]{beamer color}
\end{beamercolorbox}

#keyvals:\begin{beamercolorbox}
wd=##L
dp=##L
ht=##L
left
right
center
leftskip=##L
rightskip=##L
sep=##L
colsep=##L
colsep*=##L
shadow#true,false
rounded#true,false
ignorebg
vmode
#endkeyvals

\donotcoloroutermaths#*
\donotcolorouterdisplaymaths#*