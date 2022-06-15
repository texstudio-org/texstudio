# skills package
# Matthew Bertucci 2022/06/11 for v1.0.0

#include:iftex
#include:kvoptions
#include:glossaries
#include:tabularx
#include:etoolbox
#include:marginnote

#keyvals:\usepackage/skills#c
makenoidxglossaries
donotmakenoidxglossaries
counter=%<counter%>
#endkeyvals

\skilldef{label}{reference}{description%text}#l
\begin{skillquestions}
\begin{skillquestions}[skill1,skill2,...]
\begin{skillquestions}[labellist]#Sr
\end{skillquestions}
\skillquestion
\skillquestion[skill1,skill2,...]
\skillquestion[labellist]#Sr
\skillquestion[skill1,skill2,...][points]
\skillquestion[labellist][points]#Sr
\skills{skill1,skill2,...}
\skills{labellist}#Sr
\globalskills{skill1,skill2,...}
\globalskills{labellist}#Sr
\skillstable
\skillstable[sort type%keyvals]
#keyvals:\skillstable
word
letter
standard
use
def
nocase
case
#endkeyvals
\putglobalskills#*
\skillssep#*
\skillsinmargin
\skillsinleftmargin
\skillsinrightmargin
\noskillsinmargin
\noskillsinrightmargin
\skillsinmarginvadjust{length}
\bracketedskills
\nobracketedskills
\boxedskills
\noboxedskills
\onlyskills
\notonlyskills
\skillsenclosement{opening}{closing}
\skilllevelname#*

# not documented
\FrenchLocalization#*
\PrintingSkillsConfiguration#*
\defaultskillsclosing#*
\defaultskillsenclosement#*
\defaultskillsopening#*
\globalskill{arg}#*
\globalskill[opt]{arg}#*
\glsgobblenumber{arg}#*
\multiskills{arg1}#*
\nextitem#S
\skillcounter#*
\skillsclosing#*
\skillsopening#*
\skill{label}#*r