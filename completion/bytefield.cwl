# bytefield package
# Matthew Bertucci 11/10/2021 for v2.7

#include:calc
#include:keyval

\begin{bytefield}{bit-width}#\tabular
\begin{bytefield}[options%keyvals]{bit-width}#\tabular
\end{bytefield}

\bitbox{width}{text}#/bytefield
\bitbox[sides]{width}{text}#/bytefield
\bitbox{width}[options%keyvals]{text}#/bytefield
\bitbox[sides]{width}[options%keyvals]{text}#/bytefield

\wordbox{width}{text}#/bytefield
\wordbox[sides]{width}{text}#/bytefield
\wordbox{width}[options%keyvals]{text}#/bytefield
\wordbox[sides]{width}[options%keyvals]{text}#/bytefield

\bitboxes{width}{tokens}#/bytefield
\bitboxes[sides]{width}{tokens}#/bytefield
\bitboxes{width}[options%keyvals]{tokens}#/bytefield
\bitboxes[sides]{width}[options%keyvals]{tokens}#/bytefield
\bitboxes*{width}{tokens}#/bytefield
\bitboxes*[sides]{width}{tokens}#/bytefield
\bitboxes*{width}[options%keyvals]{tokens}#/bytefield
\bitboxes*[sides]{width}[options%keyvals]{tokens}#/bytefield

\bitheader{bit-positions}#/bytefield
\bitheader[options%keyvals]{bit-positions}#/bytefield

#keyvals:\bitheader
bitformatting={%<commands%>}
endianness=#little,big
lsb=%<integer%>
#endkeyvals

\begin{rightwordgroup}{text}#/bytefield
\begin{rightwordgroup}[options%keyvals]{text}#/bytefield
\end{rightwordgroup}#/bytefield
\begin{leftwordgroup}{text}#/bytefield
\begin{leftwordgroup}[options%keyvals]{text}#/bytefield
\end{leftwordgroup}#/bytefield

#keyvals:\begin{rightwordgroup},\begin{leftwordgroup}
curlystyle=%<command%>
leftcurlystyle=%<command%>
rightcurlystyle=%<command%>
#endkeyvals

\skippedwords#/bytefield

\bytefieldsetup{options%keyvals}

#keyvals:\bytefieldsetup,\begin{bytefield},\bitbox,\wordbox,\bitboxes,\bitboxes*
bitwidth=##L
bitheight=##L
endianness=#little,big
bitformatting={%<commands%>}
boxformatting={%<commands%>}
bgcolor=#%color
leftcurly=%<delimiter%>
rightcurly=%<delimiter%>
leftcurlyspace=##L
rightcurlyspace=##L
curlyspace=##L
leftlabelspace=##L
rightlabelspace=##L
labelspace=##L
leftcurlyshrinkage=##L
rightcurlyshrinkage=##L
curlyshrinkage=##L
leftcurlystyle=%<command%>
rightcurlystyle=%<command%>
curlystyle=%<command%>
lsb=%<integer%>
perword=%<command%>
#endkeyvals

\amp#*
\bitwidth#*
\byteheight#*
\curlyshrinkage#*
\curlyspace#*
\labelspace#*
\heightunits#*
\widthunits#*