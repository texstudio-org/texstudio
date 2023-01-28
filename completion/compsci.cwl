# compsci package
# Matthew Bertucci 2022/06/20 for v1.2

#include:abbrevs
#include:alltt
#include:lips
#include:moredefs
#include:relsize
#include:shortvrb
#include:slemph
#include:titles
#include:url
#include:verbatim

#keyvals:\usepackage/compsci#c
hyperlatex
#endkeyvals

\env{envname}
\bst{bibstyle}
\package{package}
\cat{category}
\class{class}
\file{file}
\ext{extension}
\caveat{warning text%text}
\begin{warning}
\end{warning}
\todo{text%todo}#D
\begin{todoenv}
\end{todoenv}
\code{verbatim text%definition}
\typeset{text}
\begin{typesetexample}
\end{typesetexample}
\begin{codeexample}#V
\end{codeexample}
\begin{codeexample*}#V
\end{codeexample*}
\begin{codeexamplex}#V
\end{codeexamplex}
\begin{bothexample}
\end{bothexample}
\begin{bothexample*}
\end{bothexample*}
\begin{splitexample}
\end{splitexample}
\begin{splitexample*}
\end{splitexample*}
\email{email%URL}#U
\option{option}
\program{program}
\cs{cmd}
\cmd{cmd}
\cname{csname}
\marg{arg}
\oarg{arg}
\meta{arg}
\newprogram{cmd}{initial}#d
\newprogram{cmd}{initial}[subsequent]#d
\ProcessDTXFile{file name%file}
\JusTLoaDInformatioN#S
\AddToCheckSum{number}
\BibTeX

# not documented
\filename#*
\IfCitations{arg}#*
\IfJustLoadInformation{arg}#*
\MakePercentComment#*
\MakePercentIgnore#*
\RestorECitationS#S
\RestoreDoXVarS#S
\SaveDoXVarS#S
\TMFontProgram#*

# from compsci.cfg
\Frankenstein
\monster
\ALaTeX
\ctan
\kpse
\gemacs
\auctex
\nts
\MakeIndex
\etex
\LaTeXiii
\idvi
