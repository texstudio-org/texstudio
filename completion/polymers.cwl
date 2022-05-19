# polymers package
# Matthew Bertucci 2022/05/18 for v5.01

#include:chemstr
#include:aliphat
#include:carom

\leftPolymer{delimiter%formula}{leftsubs}
\leftpolymer{leftsubs}
\leftSqrpolymer{leftsubs}
\leftsqrpolymer{leftsubs}
\lsqrdelimiter{arg1}
\mpolymer{polymer unit}{subscript%formula}
\polyethylene[auxlist]{centatmlist}{subslist}
\polyethylene{centatmlist}{subslist}
\polystyrene[auxlist]{centatmlist}{subslist}{phsubslist}
\polystyrene{centatmlist}{subslist}{phsubslist}
\rightPolymer{delimiter%formula}{rightsubs}{subscript%formula}
\rightpolymer{rightsubs}{subscript%formula}
\rightSqrpolymer{rightsubs}{subscript%formula}
\rightsqrpolymer{rightsubs}{subscript%formula}
\sbond
\Sqrpolymer{polymer unit}{subscript%formula}
\sqrpolymer{polymer unit}{subscript%formula}

# not documented
\EastPbond#S
\leftpmdelim#S
\leftPMdelim{arg1}#S
\leftsqrPolymer{arg1}{arg2}#S
\numrepeated#S
\rightpmdelim{arg1}#S
\rightPMdelim{arg1}{arg2}#S
\rightsqrPolymer{arg1}{arg2}{arg3}#S
\rsqrdelimiter{arg1}#S
\WestPbond#S