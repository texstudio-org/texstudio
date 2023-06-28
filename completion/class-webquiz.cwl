# webquiz class
# Matthew Bertucci 1/12/2021 for v5.2

#include:etoolbox
#include:pgfopts
#include:pgffor
#include:amsfonts
#include:amsmath
#include:bbding
#include:tikz

#keyvals:\documentclass/webquiz#c
fixedorder
randomorder
hidesidemenu
sidemenu
language=%<language%>
onepage
separatepages
pst2pdf
separatepages
showsidemenu
theme=#blue,darkblue,darkred,default,earthy,fresh,light,lively,muted,sleek,spring,vibrant
tikz
#endkeyvals

\begin{question}
\end{question}
\begin{choice}
\end{choice}
\begin{discussion}
\end{discussion}
\begin{quizindex}
\end{quizindex}

\answer{correct answer%text}
\answer[comparison type%keyvals]{correct answer%text}
\answer*{correct answer%text}
\answer*[comparison type%keyvals]{correct answer%text}

#keyvals:\answer,\answer*
complex
integer
lowercase
number
string
#endkeyvals

\whenRight
\whenWrong

\begin{choice}
\begin{choice}[options%keyvals]
\end{choice}

#keyvals:\begin{choice}
single
multiple
columns=%<integer%>
#endkeyvals

\correct
\incorrect
\feedback

\begin{dicussion}
\begin{dicussion}[short heading%text]
\begin{dicussion}[short heading%text][heading%text]
\end{dicussion}

\dref{label}#r
\dref[text]{label}#r
\dref*{label}#r
\dref*[text]{label}#r
\qref{label}#r
\qref[text]{label}#r
\qref*{label}#r
\qref*[text]{label}#r
\Qref{question number}
\Qref[text]{question number}
\Qref*{question number}
\Qref*[text]{question number}

\begin{quizindex}
\end{quizindex}

\quiz{title%text}
\quiz[URL]{title%text}#U
\quiz*{title%text}
\quiz*[URL]{title%text}#U

\BreadCrumbs{navigation spec%URL}
\BreadCrumb{breadcrumb}
\Department{department%text}
\DepartmentURL{URL}#U
\Institution{institution%text}
\InstitutionURL{URL}#U
\QuizzesURL{URL}#U
\UnitCode{unit code}
\UnitName{unit name%text}
\UnitURL{URL}#U

\DisplayAsImage{csname}
\DisplayAsImage[options]{csname}

\thechoice#*
\thediscussion#*
\thequestion#*
\thequiz#*

# from webquiz-ini.code.tex
\webquiz{key%plain}#*
\AddIniFileKeyValue{arg}#*
\AddIniFileValue{key%plain}{value}#*
\inifile#*
\apar#S
\AddEntry{key%plain}#*