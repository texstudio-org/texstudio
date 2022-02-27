# showexpl package
# Matthew Bertucci 10/5/2021 for v0.3s

#include:refcount
#include:listings
#include:graphicx
#include:varwidth
#include:float

#keyvals:\usepackage/showexpl#c
final
draft
attachfiles
# options passed to listings
savemem
noaspects
lgrind
procnames
hyper
formats
#endkeyvals

#ifOption:attachfiles
#include:attachfile
#endif

\LTXinputExample{file}#i
\LTXinputExample[options%keyvals]{file}#i
\begin{LTXexample}
\begin{LTXexample}[options%keyvals]
\end{LTXexample}

#keyvals:\LTXinputExample,\begin{LTXexample},\lstset
attachfile#true,false
codefile=%<file name%>
explpreset={%<listings keyvals%>}
graphic=%<file%>
hsep=##L
justification=%<command%>
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
scaled=%<factor%>
caption={%<text%>}
captionpos=#t,b,tb,bt
label=##l
backgroundcolor=#%color
float
float=#t,b,tb,bt
linerange={%<first1-last1,first2-last2,...%>}
texcs=
texcsstyle=%<style%>
language=%<language%>
escapechar=%<character%>
basicstyle=%<style commands%>
numbers=#none,left,right
keepspaces#true,false
#endkeyvals

\ResultBox#*
\ResultBoxSep#*
\ResultBoxRule#*
\theltxexample#*
\MakePercentIgnore#*
\MakePercentComment#*

# from listings options
#ifOption:procnames
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
procnamekeys={%<keywords%>}
moreprocnamekeys={%<keywords%>}
deleteprocnamekeys={%<keywords%>}
procnamestyle=%<style%>
indexprocnames#true,false
#endkeyvals
#endif

#ifOption:hyper
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
hyperref={%<identifiers%>}
morehyperref={%<identifiers%>}
deletehyperref={%<identifiers%>}
hyperanchor=
hyperlink=
#endkeyvals
#endif

#ifOption:lgrind
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
lgrindef=%<language%>
#endkeyvals
\lstlgrindeffile
#endif

#ifOption:formats
\lstdefineformat{name}{format}
#endif
