# randexam class
# Matthew Bertucci 2024/02/19 for v2024E

#include:functional
#include:etoolbox
#include:geometry
#include:amsmath
#include:array
#include:calc
#include:comment
#include:enumitem
# loads inline option of enumitem
#include:environ
#include:fancyhdr
#include:zref-user
#include:zref-lastpage
#include:tabularx
#include:xcolor
#include:tabularray
#include:tabularraylibrarydiagbox

# loaded by default
#include:mathdesign

#keyvals:\documentclass/randexam#c
plain
a3paper
a3input
oneside
random
noanswer
evaluator
mathdesign
freealign
medmath
moremath
math=#many,most,all
ctex
solidot
sourcehan
chinese
seed=%<integer%>
language=%<language%>
#endkeyvals

#ifOption:a3paper
#include:pdfpages
#endif
#ifOption:a3input
#include:pdfpages
#endif

#ifOption:freealign
#include:freealign
#endif

#ifOption:random
#include:pgf
#include:pgffor
#endif

#ifOption:mathdesign=false
#include:amssymb
#endif

#ifOption:medmath
#include:medmath
#endif

#ifOption:moremath
#include:mathtools
#include:extarrows
\diff#m
\dx#m
\dy#m
\dz#m
\du#m
\dv#m
\dr#m
\ds#m
\dt#m
\dS#m
\pd#m
\pdf#m
\pdg#m
\pdh#m
\pdl#m
\pdn#m
\pdu#m
\pdv#m
\pdx#m
\pdy#m
\pdz#m
\pdF#m
\pdL#m
\pdP#m
\pdQ#m
\pdR#m
\widebar{arg}#m
\va#m
\vb#m
\vc#m
\vd#m
\ve#m
\vi#m
\vj#m
\vk#m
\vn#m
\vs#m
\vv#m
\wfrac{numerator}{denominator}#m
\wfrac[space]{numerator}{denominator}#m
\wdfrac{numerator}{denominator}#m
\wdfrac[space]{numerator}{denominator}#m
\wtfrac{numerator}{denominator}#m
\wtfrac[space]{numerator}{denominator}#m
\leftwhitearrow#m
\rightwhitearrow#m
\upwhitearrow#m
\downwhitearrow#m
\e
\R
\arccot#m
\Corr#m
\Cov#m
\diag#m
\grad#m
\Prj#m
\tr#m
\Var#m
\diver#m
\division#m
\ov{arg}#m
\lb#m
\rb#m
\T#m
#endif

#ifOption:math
#include:freealign
#endif
#ifOption:math=many
#include:freealign
#endif

#ifOption:math=most
#include:freealign
#include:medmath
#endif

#ifOption:math=all
#include:freealign
#include:medmath
#include:diagbox
#include:mathtools
#include:extarrows
\diagboxtwo{left}{right}#t
\diagboxtwo[options%keyvals]{left}{right}#t
\diagboxthree{left}{middle}{right}#t
\diagboxthree[options%keyvals]{left}{middle}{right}#t
\diff#m
\dx#m
\dy#m
\dz#m
\du#m
\dv#m
\dr#m
\ds#m
\dt#m
\dS#m
\pd#m
\pdf#m
\pdg#m
\pdh#m
\pdl#m
\pdn#m
\pdu#m
\pdv#m
\pdx#m
\pdy#m
\pdz#m
\pdF#m
\pdL#m
\pdP#m
\pdQ#m
\pdR#m
\widebar{arg}#m
\va#m
\vb#m
\vc#m
\vd#m
\ve#m
\vi#m
\vj#m
\vk#m
\vn#m
\vs#m
\vv#m
\wfrac{numerator}{denominator}#m
\wfrac[space]{numerator}{denominator}#m
\wdfrac{numerator}{denominator}#m
\wdfrac[space]{numerator}{denominator}#m
\wtfrac{numerator}{denominator}#m
\wtfrac[space]{numerator}{denominator}#m
\leftwhitearrow#m
\rightwhitearrow#m
\upwhitearrow#m
\downwhitearrow#m
\e
\R
\arccot#m
\Corr#m
\Cov#m
\diag#m
\grad#m
\Prj#m
\tr#m
\Var#m
\diver#m
\division#m
\ov{arg}#m
\lb#m
\rb#m
\T#m
#endif

#ifOption:ctex
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif

#ifOption:language=chinese
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif
#ifOption:chinese
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif
#ifOption:chinese=many
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif
#ifOption:chinese=most
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif
#ifOption:chinese=all
#include:ctex
#include:CJKnumb
#include:CJKfntef
#include:iftex
#include:xeCJKfntef
#endif

\begin{abcd}
\end{abcd}
\begin{abcd*}
\end{abcd*}
\begin{question}
\begin{question}[points=%<number%>]
\end{question}
\begin{solution}
\end{solution}

\answer{text}
\answertable
\answertable[keyvals]
\DeclareExamTemplate{element}{name}{code}
\DeclareExamTheme{theme name}{code}
\DeclareExamTranslation{language}{keyvals}
\examdata{text}
\ExamFillCdot
\ExamFillUline
\ExamFillUlinePhantom{text}
\ExamFillUlineText{text}
\exampart{title%text}
\exampart{title%text}[note%text]
\examtitle{keyvals}
\fillin{text}
\fillout{text}
\gradetable
\gradetable[keyvals]
\IfExamBoolF{bool name}{false code}
\IfExamBoolT{bool name}{true code}
\IfExamBoolTF{bool name}{true code}{false code}
\IfExamLanguageEqF{language}{false code}
\IfExamLanguageEqT{language}{true code}
\IfExamLanguageEqTF{language}{true code}{false code}
\IfExamValueEmptyF{module}{key%plain}{false code}
\IfExamValueEmptyT{module}{key%plain}{true code}
\IfExamValueEmptyTF{module}{key%plain}{true code}{false code}
\IfExamValueExistF{module}{key%plain}{false code}
\IfExamValueExistT{module}{key%plain}{true code}
\IfExamValueExistTF{module}{key%plain}{true code}{false code}
\NewExamBool{bool name}
\pickin{A|B|C|D}
\pickout{A|B|C|D}
\points{number}
\SelectExamTemplate{element}{name}
\SelectExamTheme{theme name}
\SelectExamTranslation{language}
\SetExamBoolFalse{bool name}
\SetExamBoolTrue{bool name}
\SetExamOption{options%keyvals}
\SetExamTranslation{keyvals}
\SetExamValue{module}{keyvals}
\TheExamCounter{module}
\tickout{T|F|t|f}
\UseExamTemplate{element}{name}
\UseExamTranslation{key%plain}
\UseExamValue{module}{key%plain}

#keyvals:\SetExamOption
noanswer
random
seed=%<integer%>
#endkeyvals

# not documented
\allquestions#S
\begin{abcd*real}#S
\begin{abcdreal}#S
\begin{questionreal}#S
\begin{solutionreal}#S
\DeclareExamValue{arg1}{arg2}#S
\end{abcd*real}#S
\end{abcdreal}#S
\end{questionreal}#S
\end{solutionreal}#S
\hanglength#S
\hangtext#S
\ignorepars#S
\lastquestion#S
\MakeExamNameNumber{arg1}{arg2}#S
\MakeExamStruct{arg}#S
\minwidthbox{arg1}{arg2}#S
\oldbigskip#S
\oldmedskip#S
\oldnewpage#S
\oldsmallskip#S
\oldvfill#S
\pickinfixed{arg}#S
\pickinreal{arg}#S
\pickoutfixed{arg}#S
\pickoutreal{arg}#S
\pointorpoints{arg}#S
\pointseqno{arg}#S
\pointstag{arg}#S
\pointstext{arg}#S
\printquestions#S
\questionpointstext{arg}#S
\solutionpointstext{arg}#S
\thechoice#S
\theexampart#S
\thequestion#S
\thequestionreal#S
\thetotalquestions#S
\tickin{arg}#S
\underbox{arg1}{arg2}#S
\underparbox{arg1}{arg2}#S
\underspace{arg}#S

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
