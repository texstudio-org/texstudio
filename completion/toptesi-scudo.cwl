# toptesi-scudo package
# Matthew Bertucci 4/21/2022 for v6.4.06

#include:amsmath
#include:amssymb
#include:amsthm
#include:lscape
#include:setspace
#include:calc
#include:ifthen
#include:caption
#include:subcaption
#include:tabularx
#include:booktabs
#include:multirow
#include:siunitx
#include:float
#include:nomencl
#include:csquotes
#include:biblatex
# loads natbib option of biblatex
#include:imakeidx
#include:indentfirst

#keyvals:\documentclass/toptesi#c
mybibliostyle
#endkeyvals

\begin{ThesisTitlePage}
\end{ThesisTitlePage}

\CClicence{text}
\CycleNumber{number}
\diff#m
\Disclaimer{text}
\eu
\ExaminationDate{date}
\ExaminerList{list of examiners}
\fivestars#*
\gei
\ifmybibstyle#*
\iu
\ju
\keywords{keywords%text}
\mybibstylefalse#*
\mybibstyletrue#*
\Ndissertation{dissertation name%text}
\Ndoctoralprogram{doctoral program%text}
\Nexaminationcommittee{heading%text}
\Nlocation{location}
\NSupervisor{singular%text}{plural%text}
\PhDschoolLogo[height]{imagefile}#g
\PhDschoolLogo{imagefile}#g
\printloghi#*
\printnomencl#*
\printnomencl[space]#*
\ProgramName{name%text}
\setlogodistance{distance%l}
\Signature{signature}
\subject{subject%text}
\subtitle{text}
\SupervisorList{list of supervisors}
\SupervisorNumber{number}

# from natbib option of biblatex
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}