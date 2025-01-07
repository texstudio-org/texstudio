# scripture package
# Matthew Bertucci 2025/01/06 for v2.1

\ch{chapter number}
\ch[letter]{chapter number}
\ch*{chapter number}
\ch*[letter]{chapter number}
\extraskip
\heading{section heading%text}
\added{words%text}
\name{divine name}
\LORD
\GOD
\nofirstverse
\nohang
\nopilcrow
\redletteron
\redletteroff
\scripturecurrentchapter
\scripturecurrentverse
\scripturestyle{name%specialDef}{options%keyvals}#s#%scripturestyle
\scripturestyle*{name}{options%keyvals}
\selah
\scripturesetup{options%keyvals}
\textright{text}
\textscripture{quotation%text}
\textscripture[reference]{quotation%text}
\textscripture[reference][options%keyvals]{quotation%text}
\vs{verse number}

\begin{center}[options%keyvals]
\begin{flushright}[options%keyvals]
\begin{hanging}
\begin{hanging}[options%keyvals]
\end{hanging}
\begin{midparachap}
\begin{midparachap}[options%keyvals]
\end{midparachap}
\begin{narrow}
\begin{narrow}[options%keyvals]
\end{narrow}
\begin{poetry}
\begin{poetry}[options%keyvals]
\end{poetry}
\begin{scripture}
\begin{scripture}[reference]
\begin{scripture}[reference][options%keyvals]
\end{scripture}

#keyvals:\usepackage/scripture#c,\scripturesetup,\scripturestyle,\scripturestyle*,\textscripture,\begin{scripture}
aboveskip=##L
added/font=%<font commands%>
added/format=%<macro%>
after=%<code%>
befire=%<code%>
belowskip=##L
chapter/align=#left,right
chapter/colour=#%color
chapter/color=#%color
chapter/drop#true,false
chapter/font=%<font commands%>
chapter/format=%<macro%>
chapter/hide#true,false
chapter/nodrop#true,false
chapter/para#true,false
chapter/para/aboveskip=##L
chapter/para/belowskip=##L
chapter/para/indent#true,false
chapter/sep=##L
chapter/show#true,false
chapter/showverse#true,false
chapter/smash#true,false
chapter/valign=#bottom,middle,top
chapter/xchar=%<character%>
colour=#%color
color=#%color
compact#true,false
defaults
extraskip=##L
font=%<font commands%>
heading/aboveskip=##L
heading/afterindent#true,false
heading/align=#left,right,center
heading/belowskip=##L
heading/font=%<font commands%>
heading/format=%<macro%>
heading/hide#true,false
heading/show#true,false
inline#true,false
inline/begin=%<code%>
inline/end=%<code%>
inline/reference/format=%<macro%>
inline/reference/sep=##L
inline/version/delim=%<delim%>
inline/version/format=%<macro%>
indent#true,false
language=%<language name%>
language/variant=%<language variant name%>
leftmargin=##L
name/font=%<font commands%>
name/format=%<macro%>
noindent#true,false
parindent=##L
parskip=##L
pilcrow#true,false
pilcrow/sep=##L
redletter#true,false
redletter/colour=#%color
redletter/color=#%color
reference/align=#inline,left,right
reference/colour=#%color
reference/color=#%color
reference/font=%<font commands%>
reference/format=%<macro%>
reference/newline
reference/position=#start,end
reference/sep=##L
reference/start/inline#true,false
reference/start/newline#true,false
reference/start/sep=##L
reference/start/vsep=##L
rightmargin=##L
selah/font=%<font commands%>
selah/format=%<macro%>
selah/sep=##L
selah/text=%<text%>
style=#%scripturestyle
textright/sep=##L
verse/colour=#%color
verse/color=#%color
verse/first#true,false
verse/firstformat=%<macro%>
verse/firstsep=##L
verse/font=%<font commands%>
verse/format=%<macro%>
verse/hide#true,false
verse/para#true,false
verse/para/indent=##L
verse/sep=##L
verse/show#true,false
version=%<version%>
version/delim=%<delim%>
version/format=%<macro%>
version/position=#withref,end
center/aboveskip=##L
center/belowskip=##L
center/leftmargin=##L
center/rightmargin=##L
flushright/aboveskip=##L
flushright/belowskip=##L
flushright/leftmargin=##L
flushright/rightmargin=##L
hanging/aboveskip=##L
hanging/belowskip=##L
hanging/chapter/indent#true,false
hanging/hang=##L
hanging/leftmargin=##L
hanging/rightmargin=##L
hanging/verse/left#true,false
hanging/verse/right#true,false
hanging/verse/sep=##L
midparachap/hideverse#true,false
midparachap/showverse#true,false
narrow/aboveskip=##L
narrow/belowskip=##L
narrow/leftmargin=##L
narrow/rightmargin=##L
poetry/aboveskip=##L
poetry/belowskip=##L
poetry/bigindent=##L
poetry/indent=##L
poetry/leftmargin=##L
poetry/rightmargin=##L
poetry/verse/left#true,false
poetry/verse/right#true,false
poetry/verse/sep=##L
#endkeyvals

#keyvals:\begin{center},\begin{flushright},\begin{hanging},\begin{narrow},\begin{poetry}
aboveskip=##L
belowskip=##L
leftmargin=##L
rightmargin=##L
#endkeyvals

#keyvals:\begin{hanging}
hang=##L
#endkeyvals

#keyvals:\begin{midparachap}
hideverse#true,false
showverse#true,false
#endkeyvals

#keyvals:\begin{poetry}
bigindent=##L
indent=##L
#endkeyvals
