# verifiche package
# Matthew Bertucci 2022/09/19 for v6.0

#include:xkeyval 
#include:amsmath
#include:amssymb
#include:pgffor
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:siunitx
#include:graphicx
#include:xcolor
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshapes.geometric
#include:tikzlibrarypatterns
#include:tikzlibrarypositioning
#include:tikzlibraryangles
#include:tikzlibraryquotes
#include:booktabs
#include:ulem

#keyvals:\usepackage/verifiche#c
solutions
noinstitute
noinstruction
noduration
noasyear
nocandidatename
notesttype
nosubtitle
nonumbered
noexercisept
color=#%color
red
blue
#endkeyvals

\institute{nome dell’istituto%text}
\asyear{anno scolastico}
\asyear[preambolo%text]{anno scolastico}
\testtype{tipo di compito%text}
\instruction{istruzioni%text}
\duration{durata%text}
\duration[preambolo%text]{durata%text}
\durationfont{text}#*
\subtitle{testo del sottotitolo%text}
\subtitlefont{text}#*
\printheading

#keyvals:\pagestyle#c
mainverifiche
verifiche
#endkeyvals

\begin{esercizio}
\begin{esercizio}[options%keyvals]
\end{esercizio}
\begin{esercizio*}
\begin{esercizio*}[options%keyvals]
\end{esercizio*}

#keyvals:\begin{esercizio},\begin{esercizio*}
label=%<text%>
diff=%<number%>
pt=%<number%>
partialpt
#endkeyvals

\partialpt{number}

\begin{soluzione}
\begin{soluzione}[options%keyvals]
\end{soluzione}

#keyvals:\begin{soluzione}
label=%<text%>
#endkeyvals

\inlinesol{testo%text}
\completetext{testo%text}
\completetext[dim%l]{testo%text}
\truefalse{V|F}
\checkmarker#*

\begin{closedquestion}
\begin{closedquestion}[options%keyvals]
\end{closedquestion}
\begin{closedquestion*}
\begin{closedquestion*}[options%keyvals]
\end{closedquestion*}
\begin{crocette}#*
\begin{crocette}[options%keyvals]#*
\end{crocette}#*
\begin{crocette*}#*
\begin{crocette*}[options%keyvals]#*
\end{crocette*}#*

#keyvals:\begin{closedquestion},\begin{closedquestion*},\begin{crocette},\begin{crocette*}
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

\checked
\openquestion{soluzione%text}
\openquestion[options%keyvals]{soluzione%text}

#keyvals:\openquestion
type=#lines,squares
width=##L
height=##L
spacedim=##L
linecolor=#%color
#endkeyvals

\finderror{testo sbagliato%text}{testo giusto%text}
\textandimage{rx material%text}{dx material%text}
\textandimage[leftwidth%l]{rx material%text}{dx material%text}
\textandimage[leftwidth%l][rightwidth%l]{rx material%text}{dx material%text}
\makecolumn{width}{text}
\columnseparation#*
\headerfont{text}#*
\institutefont{text}#*
\asyearfont{text}#*
\testtypefont{text}#*
\instructionfont{text}#*
\solutionfont
\instructiondelimiter#*
\headercandidatenamelabel#*
\headerclasslabel#*
\headerdatelabel#*
\candidatenamerulerlength#*
\classrulerlength#*
\daterulerlength#*
\exerciselabel#*
\ptprefix{prefix}
\ptrulerlength#*
\partialptprefix{prefix}
\ptlabel{plural}
\ptlabel[singular]{plural}
\partialptlabel{plural}
\partialptlabel[singular]{plural}
\diffsymb#*
\ptdelimiters{coppia di caratteri}
\partialptdelimiters{coppia di caratteri}
\closedquestionitem#*
\solutionlabel#*

\begin{multitest}[n]
\end{multitest}
\themultitestcounter#*

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c,\begin{closedquestion},\begin{closedquestion*},\begin{crocette},\begin{crocette*}
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

# not in main documentation
\convertreftonum{arg}#*
\diffstar#S
\espoint#S
\evenfoot#S
\exercisemargin#*
\exercisetitle#*
\italiandictiornary#*
\openquestionheight#*
\openquestionlinecolor#*
\openquestionwidth#*
\pointes#S
\savepointsaux#*
\solutionscolor#*
\spacedim#*
\sumpartialpt#*
\tempeserciziolabel#S
\theexercisenumber#*
\thepartialpoints#*
\ifsol#S
\soltrue#S
\solfalse#S
\ifinstitute#S
\institutetrue#S
\institutefalse#S
\ifinstruction#S
\instructiontrue#S
\instructionfalse#S
\ifduration#S
\durationtrue#S
\durationfalse#S
\ifasyear#S
\asyeartrue#S
\asyearfalse#S
\ifsolutionscolor#S
\solutionscolortrue#S
\solutionscolorfalse#S
\ifcandidatename#S
\candidatenametrue#S
\candidatenamefalse#S
\iftesttype#S
\testtypetrue#S
\testtypefalse#S
\ifsubtitle#S
\subtitletrue#S
\subtitlefalse#S
\ifshowinstructiondelimiter#S
\showinstructiondelimitertrue#S
\showinstructiondelimiterfalse#S
\ifprintedheading#S
\printedheadingtrue#S
\printedheadingfalse#S
\ifexercisesnumbered#S
\exercisesnumberedtrue#S
\exercisesnumberedfalse#S
\ifshowmarginexercise#S
\showmarginexercisetrue#S
\showmarginexercisefalse#S
\ifshowexercisept#S
\showexercisepttrue#S
\showexerciseptfalse#S
\ifopenquestionlines#S
\openquestionlinestrue#S
\openquestionlinesfalse#S
\ifopenquestionsquared#S
\openquestionsquaredtrue#S
\openquestionsquaredfalse#S
