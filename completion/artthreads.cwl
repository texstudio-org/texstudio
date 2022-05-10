# artthreads package
# Matthew Bertucci 2022/05/10 for v1.3.1

#include:xkeyval
#include:fitr

#keyvals:\usepackage/artthreads#c
pdftex
luatex
dvips
dvipsone
dvipdfm
dvipdfmx
xetex
preview
!preview
viewMagWin
!viewMagWin
#endkeyvals

\setThreadInfo{options%keyvals}

#keyvals:\setThreadInfo
title=%<text%>
author=%<text%>
subject=%<text%>
keywords={%<word1,word2,...%>}
#endkeyvals

\bArticle{options%keyvals}
\cArticle{options%keyvals}

#keyvals:\bArticle,\cArticle
width=##L
height=##L
lift=##L
shift=##L
#endkeyvals

\setAddToBorder{options%keyvals}

#keyvals:\setAddToBorder
addtow=##L
addtoh=##L
#endkeyvals

\shArticlesPaneActn
\sArticlesPaneActn
\shArticlesPaneReadActn
\sArticlesPaneReadActn

\Thread{thread title%text}

\toggleArticlePane{width}{height}
\toggleArticlePane[modifications]{width}{height}
\toggleArticlePaneRead{width}{height}
\toggleArticlePaneRead[modifications]{width}{height}
\showArticlePane{width}{height}
\showArticlePane[modifications]{width}{height}
\showArticlePaneRead{width}{height}
\showArticlePaneRead[modifications]{width}{height}

\readArticle{text}
\threadTitle
\threadAuthor
\threadKeywords
\threadSubject

\tooltipTogglePaneRead{text}
\tooltipShowPaneRead{text}

# not documented
\bArtErrMsg#S
\chkThreadName
\CntArt#*
\CntArtInfo#*
\ifnewarticle#*
\isThrTtl#S
\newarticlefalse#*
\newarticletrue#*
\readArtPresets#*
\readThreadMsg#S