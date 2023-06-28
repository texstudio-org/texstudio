# sdapsclassic class
# Matthew Bertucci 12/18/2021 for v0.1

#include:class-scrartcl
#include:sdapsbase
#include:sdapslayout
#include:verbatim
#include:scrkbase
#include:geometry
#include:ifthen
#include:fontenc
#include:color
#include:amssymb
#include:refcount
#include:lastpage
#include:environ
#include:scrlayer-scrpage
#include:url
#include:hyperref
#include:graphicx
#include:sectsty
#include:tabularx
#include:babel
#include:translator

\begin{questionnaire}
\begin{questionnaire}[options%keyvals]
\end{questionnaire}

#keyvals:\begin{questionnaire}
noinfo
#endkeyvals

\addinfo{key%plain}{value}
\sdapsinfo#*
\sdapspagemark#*

\checkbox
\checkbox*
\checkedbox
\checkedbox*
\filledbox
\filledbox*
\correctedbox
\correctedbox*

\singlemark{question%text}{lower%text}{upper%text}
\singlemark[options%keyvals]{question%text}{lower%text}{upper%text}
\singlemarkother{question%text}{lower%text}{upper%text}
\singlemarkother[options%keyvals]{question%text}{lower%text}{upper%text}

#keyvals:\singlemark,\singlemarkother
var=%<variable%>
count=%<integer%>
#endkeyvals

\textbox{height}{question}
\textbox[options%keyvals]{height}{question}
\textbox*{height}{question}
\textbox*[options%keyvals]{height}{question}

#keyvals:\textbox,\textbox*
text=%<text%>
var=%<variable%>
#endkeyvals

\begin{choicequestion}{text}
\begin{choicequestion}[options%keyvals]{text}
\end{choicequestion}

#keyvals:\begin{choicequestion}
cols=%<integer%>
colsep=##L
rowsep=##L
var=%<variable%>
text=%<text%>
type=#multichoice,singlechoice
multichoice
singlechoice
#endkeyvals

\choiceitem{text}
\choiceitem[options%keyvals]{text}
\choicemulticolitem{cols}{text}
\choicemulticolitem[options%keyvals]{cols}{text}

#keyvals:\choiceitem,\choicemulticolitem
var=%<variable%>
val=%<value%>
text=%<text%>
#endkeyvals

\choiceitemtext{height}{cols}{text}
\choiceitemtext[options%keyvals]{height}{cols}{text}

#keyvals:\choiceitemtext
var=%<variable%>
text=%<text%>
#endkeyvals

\begin{optionquestion}{text}
\begin{optionquestion}[options%keyvals]{text}
\end{optionquestion}

#keyvals:\begin{optionquestion}
cols=%<integer%>
colsep=##L
rowsep=##L
var=%<variable%>
text=%<text%>
#endkeyvals

\begin{info}
\end{info}

\begin{markgroup}{text}
\begin{markgroup}[options%keyvals]{text}
\end{markgroup}

#keyvals:\begin{markgroup}
count=%<integer%>
align=%<string%>
other
#endkeyvals

\markline{question}{lower}{upper}
\markline[options%keyvals]{question}{lower}{upper}

\begin{choicegroup}{text}
\begin{choicegroup}[options%keyvals]{text}
\end{choicegroup}

\begin{optiongroup}{text}
\begin{optiongroup}[options%keyvals]{text}
\end{optiongroup}

#keyvals:\begin{choicegroup},\begin{optiongroup}
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

#keyvals:\begin{choicegroup}
type=#multichoice,singlechoice
multichoice
singlechoice
#endkeyvals

\groupaddchoice{text}#*
\groupaddchoice[options%keyvals]{text}#*

#keyvals:\groupaddchoice
text=%<text%>
var=%<variable%>
val=%<value%>
#endkeyvals

\choiceline{text}#*
\choiceline[options%keyvals]{text}#*

#keyvals:\choiceline
text=%<text%>
var=%<variable%>
range=%<list%>
#endkeyvals

\qid#*
\sectbox{arg}#*
\themarkcheckboxcount#*

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
