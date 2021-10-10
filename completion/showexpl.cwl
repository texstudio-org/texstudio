# showexpl package
# Matthew Bertucci 10/5/2021 for v0.3s

#include:attachfile
#include:refcount
#include:listings
#include:graphicx
#include:varwidth
#include:float

\LTXinputExample{file}#i
\LTXinputExample[options%keyvals]{file}#i
\begin{LTXexample}
\begin{LTXexample}[options%keyvals]
\end{LTXexample}

#keyvals:\LTXinputExample,\begin{LTXexample}
attachfile#true,false
codefile=%<file name%>
graphic=%<file%>
hsep=##L
justification=
overhang=##L
pos=#t,b,l,r,o,i
preset=%<code%>
rangeaccept#true,false
rframe=
varwidth#true,false
vsep=##L
wide#true,false
width=##L
scaled
scaled=
caption={%<text%>}
captionpos=#t,b,tb,bt
label=##l
backgroundcolor=#%color
float
float=#t,b,tb,bt
linerange={%<first1-last1,first2-last2,...%>}
texcs=
texcsstyle=
language=
escapechar=
#endkeyvals

#keyvals:\lstset,\LTXinputExample,\begin{LTXexample}
explpreset={%<listings keyvals%>}
#endkeyvals

\ResultBox#*
\ResultBoxSep#*
\ResultBoxRule#*