# hep-text package
# Matthew Bertucci 2022/11/03 for v1.1

#include:kvoptions
#include:babel
#include:csquotes
#include:soulutf8
#include:pdftexcmds
#include:foreign
# foreign loaded with all option
#include:relsize
#include:enumitem
# enumitem loaded with inline option

#keyvals:\usepackage/hep-text#c
lang=%<language%>
#endkeyvals

\vs
\no{number}
\software{name}
\software[version]{name}
\online{URL}{text%plain}#U
\email{email%URL}#U
\prefix{prefix}{word%text}
\subsubparagraph
\begin{inlinelist}
\begin{inlinelist}[options%keyvals]
\end{inlinelist}
\begin{enumdescript}
\begin{enumdescript}[options%keyvals]
\end{enumdescript}

#keyvals:\begin{inlinelist}#c,\begin{enumdescript}#c
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

\begin{enumdesc}#S
\end{enumdesc}#S

# from all option of foreign
\addendum
\Addendum
\adhoc
\Adhoc
\aposteriori
\Aposteriori
\apriori
\Apriori
\caveat
\Caveat
\circa
\Circa
\curriculum
\Curriculum
\erratum
\Erratum
\ibidem
\Ibidem
\idem
\Idem
\sic
\Sic
\viceversa
\Viceversa
\vitae
\Vitae
\ala
\Ala
\visavis
\Visavis
\ansatz
\Ansatz
\gedanken
\Gedanken
\cf
\eg
\etal
\etc
\etseq
\ibid
\ie
\loccit
\opcit
\viz
\Cf
\Eg
\Etal
\Etc
\Etseq
\Ibid
\Ie
\Loccit
\Opcit
\Viz

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
