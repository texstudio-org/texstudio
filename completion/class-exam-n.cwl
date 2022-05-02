# exam-n class
# Matthew Bertucci 4/21/2022 for v1.1.4

#include:babel
# loads english option of babel
#include:amsmath
#include:color
#include:ifpdf
#include:fancyhdr

#keyvals:\documentclass/exam-n#c
compose
draft
final
psfonts
cmfonts
mathptm
mathtime
mtpro2
serif
sansserif
showsolutions
noshowsolutions
pageperquestion
nopageperquestion
perquestionmarks
noperquestionmarks
showmarktotals
noshowmarktotals
twoside
oneside
fleqn
sloppydescription
mono
colour
largefont
hugefont
A1
#endkeyvals

#ifOption:mathptm
#include:mathptm
#include:times
#endif

#ifOption:mathtime
#include:fontenc
#include:mathtime
#include:times
# loads LY1 option of fontenc and mathtime
\DH#n
\dh#n
\guillemotleft#n
\guillemotright#n
\guilsinglleft#n
\guilsinglright#n
\k{arg}#n
\quotedblbase#n
\quotesinglbase#n
\textdivide#n
\textlogicalnot#n
\textmultiply#n
\textplusminus#n
\textquotedbl#n
\textquotedblbase#n
\textquotesinglbase#n
\textspace#n
\TH#n
\th#n
#endif

#ifOption:mtpro2
#include:mtpro2
#include:textcomp
#include:fontenc
# loads T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n
#endif

#ifOption:sansserif
#include:helvet
#endif

\ifbigfont#*
\bigfonttrue#*
\bigfontfalse#*
\begin{question}{marks}
\begin{question}[question number]{marks}
\end{question}
#ifOption:noperquestionmarks
\begin{question}
\begin{question}[question number]
#endif
\QuestionNumberChecksOff
\begin{solution}
\end{solution}
\begin{questiondata}
\end{questiondata}
\begin{mcq}
\end{mcq}
\answer
\multiplechoiceanswers{n}
\includequestion{file}#i
\includequestion[question number]{file}#i
\partmarks{number}
\partmarks*{number}
\comment{text}
\shout{text}
\leftnudge{length}
\questionpreamble{content%text}
\exambanner{text}
\universitycoursecode{text%plain}
\schoolcoursecode{text%plain}
\degreedescriptions{text}
\coursetitle{text}
\paperident{text%plain}
\examdate{date}
\examtime{time}
\rubric{text}
\norubric
\baserubric#*
\numquestions{number}
\BSc
\MSci
\MSc
\MA
\MEng
\BEng
\dd#m
\ddd#m
\Diffl{arg}{var}#m
\Diffl[ord]{arg}{var}#m
\Diffl*{arg}{var}#m
\Diffl*[ord]{arg}{var}#m
\Partial{arg}{var}#m
\Partial[ord]{arg}{var}#m
\Partial*{arg}{var}#m
\Partial*[ord]{arg}{var}#m
\Partial
\e#m
\au
\lambdabar#m
\units{units%formula}
\constantssheet{content%text}#*
\OverrideFormatting{formatting commands}
\FormatPartMarks#*
\FormatPartNumber#*
\StylePartNumber#*
\FormatQuestionNumber#*

# not documented
\CheckTotalQuestions#*
\ClosingText#*
\formatcontinuations{text}#*
\highlighted{text}#*
\marginsize#*
\markgoal#*
\marktotal#*
\theanswerpartnumber#*
\thepartnumber#*
\thequestionnumber#*
\UniLogo{length}#*
\WriteLastPageLabel#*

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*