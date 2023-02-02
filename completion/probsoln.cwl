# probsoln package
# Matthew Bertucci 2022/05/21 for v3.05

#include:ifthen
#include:amsmath
#include:etoolbox
#include:xkeyval

#keyvals:\usepackage/probsoln#c
answers
noanswers
draft
final
usedefaultargs
nousedefaultargs
#endkeyvals

\begin{defproblem}{label}
\begin{defproblem}[args]{label}
\begin{defproblem}[args][default]{label}
\end{defproblem}
\begin{onlyproblem}
\end{onlyproblem}
\begin{onlysolution}
\end{onlysolution}
\begin{solution}
\end{solution}
\begin{textenum}
\end{textenum}
\begin{PSNitem}#*
\end{PSNitem}#*

\ClearUsedFile{file}
\correctitem
\correctitemformat{label}#*
\doforrandN{n}{cmd}{file list}{text}#d
\draftproblemlabel{data set}{label}#*
\DTLifinlist{element}{list}{true case}{false case}#*
\ExcludePreviousFile[num of years]{file}
\ExcludePreviousFile{file}
\firstpassfalse#*
\firstpasstrue#*
\foreachdataset{cmd}{body}#d
\foreachproblem[data set]{body}
\foreachproblem{body}
\foreachsolution[data set]{body}
\foreachsolution{body}
\GetStartYear
\hideanswers
\iffirstpass#*
\ifshowanswers
\ifusedefaultprobargs#*
\incorrectitem
\incorrectitemformat{label}#*
\loadallproblems[data set]{file}#i
\loadallproblems{file}#i
\loadexceptproblems[data set]{label1,label2,...}{file}#i
\loadexceptproblems{label1,label2,...}{file}#i
\loadrandomexcept[data set]{n}{file}{label1,label2,...}#i
\loadrandomexcept{n}{file}{label1,label2,...}#i
\loadrandomproblems[data set]{n}{file}#i
\loadrandomproblems{n}{file}#i
\loadselectedproblems[data set]{label1,label2,...}{file}#i
\loadselectedproblems{label1,label2,...}{file}#i
\moveproblem{label}{source}{target}#*
\newproblem*[args][default]{label}{definition%text}
\newproblem*[args]{label}{definition%text}
\newproblem*{label}{definition%text}
\newproblem[args][default]{label}{problem%text}{solution%text}
\newproblem[args]{label}{problem%text}{solution%text}
\newproblem{label}{problem%text}{solution%text}
\previousproblem{label}{data set}{year}#*
\ProbSolnFragileExt#*
\ProbSolnFragileFile#*
\PSNgetrandseed{register}
\PSNrand#*
\PSNrandom{register}{n}
\PSNrandseed{n}
\PSNuseoldrandom#*
\random{counter}{min}{max}
\selectallproblems{file}#i
\selectrandomly{file}{n}
\setprobargs[data set]{label}{args}#*
\setprobargs{label}{args}#*
\SetStartMonth{n}
\SetStartYear{year}
\SetUsedFileName{file name%file}
\showanswers
\showanswersfalse#*
\showanswerstrue#*
\shuffle{arg}{num}#*
\solutionname#*
\thisproblem
\thisproblemargs#*
\thisproblemlabel
\usedefaultprobargsfalse#*
\usedefaultprobargstrue#*
\usedproblem{arg1}{arg2}{arg3}#*
\useproblem[%<data set%>]{%<label%>}{%<arg1%>}%<...{argN}%>
\useproblem{%<label%>}{%<arg1%>}%<...{argN}%>
