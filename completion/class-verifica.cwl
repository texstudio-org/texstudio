# verifica class
# Matthew Bertucci 2022/06/12 for v1.3

#include:enumitem
# loads shortlabels and inline options of enumitem
#include:graphicx
#include:mathtools
#include:amssymb
#include:geometry
#include:nccmath
#include:multido
#include:setspace
#include:multicol
#include:gensymb
#include:newunicodechar
#include:textcomp
#include:tabto
#include:tabularx
#include:lineno
#include:eurosym
#include:bm

#keyvals:\documentclass/verifica#c
10pt
11pt
12pt
14pt
default
itembullet
intestazionerighe
intestazionesemplice
senzagrazie
#endkeyvals

#ifOption:14pt
#include:class-extarticle
#endif

#ifOption:senzagrazie
#include:cmbright
#endif

\begin{esercizi}
\begin{esercizi}[options%keyvals]
\end{esercizi}
\begin{test}
\begin{test}[options%keyvals]
\end{test}
\begin{test-orizz}
\begin{test-orizz}[options%keyvals]
\end{test-orizz}
\begin{test-orizz-newline}
\begin{test-orizz-newline}[options%keyvals]
\end{test-orizz-newline}
\begin{test-vf}#*
\begin{test-vf}[options%keyvals]#*
\end{test-vf}#*
\begin{test-verofalso}
\begin{test-verofalso}[options%keyvals]
\end{test-verofalso}

\abs{arg}#m
\arc{arg}#m
\biglabelbox{content}
\CalcNumber{arg1}{arg2}#*
\classe{classe}
\data{data}
\ddfrac{num}{den}#m
\Del#m
\del#m
\denfrac{num}{den}#m
\disciplina{disciplina}
\dotrule{length}
\dotword{word}
\dss{math}#m
\eps#m
\fattorevf{fattore}
\intestazione
\intestazionedefault#*
\intestazionerighe
\intestazionesemplice
\istituto{istituto}
\labelbox{content}
\labeltest{labeltype}
\lineanome
\N#m
\numfrac{num}{den}#m
\punti[testo aggiuntivo%text]{punteggio}
\punti{punteggio}
\puntiadestra
\puntiman[testo aggiuntivo%text]{punteggio}
\puntiman{punteggio}
\puntipt
\Q#m
\R#m
\Repeat{arg}#*
\restorephi#*
\restoretheta#*
\riga{numero di righe}
\tempo{tempo}
\themylines#S
\thenumrighe#S
\tipologia{tipologia}
\totpunti
\totpunti[calcolo]
\tsa
\tso
\unitx{units%formula}
\vartotpunti
\vartotpunti[calcolo]
\verofalso[factor]{text}#*
\verofalso{text}#*
\vf
\vfitem{testo%text}
\Z#m

#keyvals:\begin{test-vf},\begin{test-verofalso}
fattorevf=%<fattore%>
#endkeyvals

#keyvals:\begin{esercizi},\begin{test},\begin{test-orizz},\begin{test-orizz-newline},\begin{test-vf},\begin{test-verofalso}
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

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