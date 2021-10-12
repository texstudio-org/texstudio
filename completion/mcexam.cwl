# mcexam package
# Matthew Bertucci 10/4/2021 for v0.5

#include:enumitem
#include:environ
#include:etoolbox
#include:longtable
#include:newfile
#include:pgffor
#include:xstring

\mctheversion#*

\mcexamoptions{options%keyvals}

#keyvals:\mcexamoptions
output=#concept,exam,key,answers,analysis
numberofversions=%<integer%>
version=%<integer%>
seed=%<integer%>
randomizequestions#true,false
randomizeanswers#true,false
writeRfile#true,false
#endkeyvals

\begin{mcquestions}
\end{mcquestions}
\question#/mcquestions
\question[option%keyvals]#/mcquestions

#keyvals:\question
follow
#endkeyvals

\begin{mcanswerslist}#/mcquestions
\begin{mcanswerslist}[option%keyvals]#/mcquestions
\end{mcanswerslist}#/mcquestions
\begin{mcanswers}#/mcquestions
\begin{mcanswers}[option%keyvals]#/mcquestions
\end{mcanswers}#/mcquestions
\answer#/mcanswerslist,mcanswers
\answer[mark]#/mcanswerslist,mcanswers
\answer{n}{answer}#/mcanswerslist,mcanswers
\answer[mark]{n}{answer}#/mcanswerslist,mcanswers
\answernum{n}#/mcanswers

#keyvals:\begin{mcanswerslist}#c,\begin{mcanswers}#c
permuteall
ordinal
fixlast
permutenone
#endkeyvals

\begin{mcquestioninstruction}#/mcquestions
\end{mcquestioninstruction}#/mcquestions
\begin{mcexplanation}#/mcquestions
\end{mcexplanation}#/mcquestions
\begin{mcnotes}#/mcquestions
\end{mcnotes}#/mcquestions

\mcifoutput{output type%keyvals}{text}
\mcifoutput[versions]{output type%keyvals}{text}

#keyvals:\mcifoutput
concept
exam
key
answers
analysis
#endkeyvals

#ifOption:writeRfile=true
\begin{mcquestions}[R file ext]
#endif

#ifOption:writeRfile
\begin{mcquestions}[R file ext]
#endif

\mcsetupConcept{keyvals}
\mcsetupExam{keyvals}
\mcsetupKey{keyvals}
\mcsetupAnswers{keyvals}
\mcsetupAnalysis{keyvals}

#keyvals:\mcsetupConcept,\mcsetupExam,\mcsetupKey,\mcsetupAnswers,\mcsetupAnalysis
showPerVersion#true,false
showQuestionPermutationtable#true,false
showQuestionsAnalysis#true,false
showQuestionList#true,false
showCorrectAnswers#true,false
showAnswerPoints#true,false
showExplanation#true,false
showAnswerPermutationTable#true,false
showAnswersAnalysis#true,false
showNotes#true,false
showKeytable#true,false
#endkeyvals

\mcversionlabelfmt#*
\mcquestionlabelfmt#*
\mcanswerlabelfmt#*