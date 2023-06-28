# sdapslayout package
# Matthew Bertucci 12/18/2021 for v0.1

#include:sdapsbase
#include:sdapsarray

\begin{choicearray}
\begin{choicearray}[options%keyvals]
\end{choicearray}

\begin{optionarray}
\begin{optionarray}[options%keyvals]
\end{optionarray}

#keyvals:\begin{choicearray},\begin{optionarray}
align=
noalign#true,false
horizontal#true,false
layouter=#default,rotated
angle=%<angle%>
vertical#true,false
type=#multichoice,singlechoice
multichoice
singlechoice
#endkeyvals

#keyvals:\begin{choicearray}
type=#multichoice,singlechoice
multichoice
singlechoice
#endkeyvals

\choice{text}
\choice[options%keyvals]{text}

#keyvals:\choice
text=%<text%>
var=%<variable%>
val=%<value%>
#endkeyvals

\question{text}
\question[options%keyvals]{text}

#keyvals:\question
text=%<text%>
var=%<variable%>
range=%<list%>
#endkeyvals

\begin{rangearray}
\begin{rangearray}[options%keyvals]
\end{rangearray}

#keyvals:\begin{rangearray}
count=%<integer%>
align=%<string%>
other
#endkeyvals

\range{question%text}{lower%text}{upper%text}{other%text}
\range[options%keyvals]{question%text}{lower%text}{upper%text}{other%text}

#keyvals:\range
text=%<text%>
var=%<variable%>
upper=%<text%>
lower=%<text%>
other
#endkeyvals