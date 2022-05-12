# rangen package
# Matthew Bertucci 2022/05/10 for v1.4

#include:lcg

#keyvals:\usepackage/rangen#c
testmode
# options passed to lcg
counter=%<counter%>
first=%<integer%>
last=%<integer%>
seed=%<integer%>
quiet
#endkeyvals

\RandomZ{cmd}{int1}{int2}#d
\RandomZ[options%keyvals]{cmd}{int1}{int2}#d
\nOf{%<\name%>}
\dOf{%<\name%>}
\fmt{%<\name%>}
\ds{%<\name%>}
\RandomQ{cmd}{num1}{num2}#d
\RandomQ{cmd}[max denom]{num1}{num2}#d
\RandomZ[options%keyvals]{cmd}{num1}{num2}#d
\RandomZ[options%keyvals]{cmd}[max denom]{num1}{num2}#d
\RandomR{cmd}{int1}{int2}#d
\RandomR[options%keyvals]{cmd}{int1}{int2}#d

#keyvals:\RandomZ,\RandomQ,\RandomR
ne=%<integer(s)%>
#endkeyvals

#keyvals:\RandomR
round=%<integer%>
showzeros#true,false
#endkeyvals

\RNGpowerOfTen#*
\nDivisionsPowerOfTen{integer}
\RandomL{cmd}{n1,n2,...}#d
\RandomL[options%keyvals]{cmd}{n1,n2,...}#d
\RandomI{cmd}{integer}#d
\RandomP{cmd}{list of literals%definition}#d
\RandomP[options%keyvals]{cmd}{list of literals%definition}#d
\iOf{%<\name%>}

#keyvals:\RandomL,\RandomP
index=%<integer%>
#endkeyvals

\RandomS{cmd}#d
\RandomS[dec]{cmd}#d
\cfmt{%<\name%>}
\efmt{%<\name%>}
\cds{%<\name%>}
\eds{%<\name%>}
\typeOf{%<\name%>}

\defineZ{cmd}{integer}#d
\defineQ{cmd}{numerator}{denominator}#d
\defineR{cmd}{number}#d

\reduceFrac{numerator}{denominator}
\rfNumer
\rfDenom
\gcd{int1}{int2}
\thegcd
\lcm{int1}{int2}
\thelcm

\RNGprintf{string}
\defineDepQJS{cmd}{numerator}{denominator}{script%definition}#d
\js{%<\name%>}
\begin{writeRVsTo}{quizzes|exercises}
\end{writeRVsTo}

\RNGadd{%<\name1%>}{%<\name2%>}
\zZero
\zOne
\zMinusOne
\rPI
\rE

# not documented
\amodb{arg1}{arg2}#*
\cntNumDec{arg1}{arg2}#*
\convertRatTo{arg1}{arg2}{arg3}#*
\decPls#*
\loopCnt#*
\maxLoopLimit#*
\reseedEachRun#*
\retnmod#*
\rndnDec#*
\rndPower#*
\RNGparseRat{arg1}#*
\RNGround{arg1}{arg2}{arg3}#*
\seedCnt#*
\simplifyCurrentQ#*
\simplifyCurrentR#*
\syncronizeQs{arg1}#*
\theseDigits#*
\thisseed#*
\typeCodeForq#*
\typeCodeForr#*
\typeCodeForz#*
\updateQ{arg1}{arg2}{arg3}#*
\updateZ{arg1}{arg2}#*
\varType#*