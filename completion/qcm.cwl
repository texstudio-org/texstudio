# qcm package
# Matthew Bertucci 2/5/2022 for v2.1

#include:ifthen
#include:calc
#include:verbatim
#include:tabularx

#keyvals:\usepackage/qcm#c
english
french
francais
nocorrection
correction
#endkeyvals

\headerfont{font commands}
\X{symbol}
\pbs{arg}#*
\questionspace
\answerstitle{text}
\answerstitlefont{font commands}
\answernumberfont{font commands}
\thequestion
\begin{question}{question text%text}
\end{question}
\truesymbol{symbol}
\falsesymbol{symbol}
\true
\false
\correctionstyle{font commands}
\makeform
\makemask
\begin{correction}
\end{correction}