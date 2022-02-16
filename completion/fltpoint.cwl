# fltpoint package
# Matthew Bertucci 10/29/2021 for v1.1b

#keyvals:\usepackage/fltpoint#c
comma
point
#endkeyvals

\fpAdd{cmd}{num1}{num2}#d
\fpSub{cmd}{num1}{num2}#d
\fpMul{cmd}{num1}{num2}#d
\fpDiv{cmd}{num1}{num2}#d
\fpNeg{cmd}{number}#d
\fpAbs{cmd}{number}#d
\fpRound{cmd}{number}{precision}#d
\fpRegSet{reg-name}{number}
\fpRegGet{reg-name}{cmd}#d
\fpRegAdd{reg-name1}{reg-name2}
\fpRegSub{reg-name1}{reg-name2}
\fpRegMul{reg-name1}{reg-name2}
\fpRegDiv{reg-name1}{reg-name2}
\fpRegAbs{reg-name}
\fpRegNeg{reg-name}
\fpRegRound{reg name}{precision}
\fpRegCopy{reg-name1}{reg-name2}
\fpAccuracy{number}
\fpDecimalSign{character}
\fpThousandSep{character}

\iloop{arg}#*
\irepeat#*
\iiterate#*
\ibody#*
\inext#*
\xloop{arg}#*
\xrepeat#*
\xiterate#*
\xbody#*
\xnext#*
