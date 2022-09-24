# ppt-slides package
# Matthew Bertucci 2022/09/24 for v0.1.5

#include:pgfopts
#include:xcolor
#include:ifthen
#include:href-ul
#include:pagecolor
#include:varwidth
#include:qrcode
#include:tikz
#include:tikzpagenodes
#include:enumitem
# loads inline option of enumitem
#include:crumbs
#include:tabularx
#include:seqsplit

#keyvals:\usepackage/ppt-slides#c
template=9x6
scheme=#light,dark,light-mono,dark-mono
directory=%<directory%>
nominutes
#endkeyvals

#ifOption:template
# from ppt-9x6.tex
#include:geometry
#include:textpos
#include:libertine
#include:microtype
#include:anyfontsize
#include:multicol
#include:fontsize
#include:changepage
#include:soul
#include:lastpage
#include:fancyhdr
\pptLeft{text}
\pptRight{text}
#endif
#ifOption:template=9x6
# from ppt-9x6.tex
#include:geometry
#include:textpos
#include:libertine
#include:microtype
#include:anyfontsize
#include:multicol
#include:fontsize
#include:changepage
#include:soul
#include:lastpage
#include:fancyhdr
\pptLeft{text}
\pptRight{text}
#endif

\pptMiddle{text}
\pptBanner{text}
\pptBanner[color]{text}
\pptChapter{title}#L1
\pptChapter[short title]{title}#L1
\pptSection{title}#L2
\pptSection[short title]{title}#L2
\pptHeader{text}
\pptTitle{title%text}{subtitle%text}
\pptTOC#S
\pptToc
\pptToc[text]
\param#S
\pptQuote{imagefile}{quote%text}{author}#g
\pptPic{width factor}{imagefile}#g
\pptPin{text}#*
\pptPin[right|left]{text}#*
\pptThought{text}
\pptSnippet{file}#*i
\pptSnippet[before code]{file}#*i
\pptQR{URL}#U
\pptQR[height]{URL}#U
\pptPinQR{URL}#*U
\pptPinQR[right|left]{URL}#*U
\begin{pptWideOne}
\end{pptWideOne}
\begin{pptWide}{numCols}
\end{pptWide}

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}
