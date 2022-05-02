# parallel package
# Matthew Bertucci 11/17/2021

#keyvals:\usepackage/parallel#c
Verbose
OldStyleNums
RaiseNums
ItalicNums
RomanNums
SeparatedFootnotes
#endkeyvals

\begin{Parallel}{left-width%l}{right-width%l}
\begin{Parallel}[options%keyvals]{left-width%l}{right-width%l}
\end{Parallel}

#keyvals:\begin{Parallel}
c
v
p
#endkeyvals

\ParallelLText{text}
\ParallelRText{text}
\ParallelPar

\ParallelLWidth#*
\ParallelRWidth#*
\ParallelTextWidth#*
\ParallelLeftMargin#*
\ParallelUserMidSkip#*
\ParallelMainMidSkip#*
\ParallelLBox#*
\ParallelRBox#*
\ParallelBoxVar#*
\ParallelLTok#*
\ParallelRTok#*
\ParallelBoolVar#*
\ParallelBoolMid#*
\ParallelWhichBox#*
\ParallelMainMode#*
\ParallelFNMode#*
\ParallelLFNCounter#*
\ParallelRFNCounter#*
\ParallelMaxFN#*
\ParallelFNNumMode#*

\ParallelMessage{text}#*
\ParallelLFootnote{text}#*
\ParallelRFootnote{text}#*
\begin{ParallelFNEnviron}#*
\end{ParallelFNEnviron}#*
\ParallelShowFNList#*
\ParallelParOnePage#*
\ParallelParTwoPages#*
\ParallelAfterText#*
\ParallelCheckOpenBrace#*
\ParallelAtEnd#*
\ParallelDot#*
