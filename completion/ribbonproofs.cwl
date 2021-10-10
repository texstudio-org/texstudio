# ribbonproofs package
# Matthew Bertucci 10/8/2021 for v1.0

#include:xcolor
#include:tikz
#include:xstring
#include:etextools

\begin{ribbonproof}#\math
\begin{ribbonproof}[options%keyvals]#\math
\end{ribbonproof}

#keyvals:\begin{ribbonproof}
extra height=%<integer%>
start ribbons={%<ribbon1,ribbon2,...%>}
start boxes={%<box1,box2,...%>}
draw grid#true,false
#endkeyvals

\com{text}#/ribbonproof
\com[options%keyvals]{text}#/ribbonproof
\jus{text}#/ribbonproof
\jus[options%keyvals]{text}#/ribbonproof
\startblock{text}#/ribbonproof
\startblock[options%keyvals]{text}#/ribbonproof
\finishblock{text}#/ribbonproof
\finishblock[options%keyvals]{text}#/ribbonproof

#keyvals:\com,\jus,\startblock,\finishblock
height=%<integer%>
finish ribbons={%<name1,name2,...%>}
start ribbons={%<ribbon1,ribbon2,...%>}
finish boxes={%<name1,name2,...%>}
start boxes={%<box1,box2,...%>}
extra left=%<integer%>
extra right=%<integer%>
#endkeyvals

#keyvals:\startblock
fit ribbons={%<name1,name2,...%>}
fit boxes={%<name1,name2,...%>}
#endkeyvals

\ribbonpagebreak#/ribbonproof

\continueblock{text}#/ribbonproof
\continueblock[options%keyvals]{text}#/ribbonproof

#keyvals:\continueblock
height=%<integer%>
start ribbons={%<ribbon1,ribbon2,...%>}
start boxes={%<box1,box2,...%>}
jagged
repeat labels
#endkeyvals

\moveribbons{ribbon1,ribbon2,...}#/ribbonproof
\swapribbons{name1,name2,...}{name'1,name'2,...}#/ribbonproof
\moveboxes{box1,box2,...}#/ribbonproof
\extendboxes{box1,box2,...}#/ribbonproof

\jusColor#*
\comColor#*
\ribColor#*
\varribColor#*
\ribTextColor#*
\boxTextColor#*
\guideTextColor#*
\defaultStepHeight#*
\defaultRowHeight#*
\ribTextVOffset#*
\boxTextVOffset#*
\boxTextHOffset#*
\guideTextVOffset#*
\roundingRadius#*
\boxRoundingRadius#*
\blockLineWidth#*
\boxLineWidth#*
\shadowHeight#*
\shadowColor#*
\zigzagHeight#*
\zigzagLength#*
\twistiness#*