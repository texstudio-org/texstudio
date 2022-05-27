# xepersian-multiplechoice package
# Matthew Bertucci 2022/05/26 for v0.2

#include:pifont
#include:fullpage
#include:ifthen
#include:calc
#include:verbatim
#include:tabularx

#keyvals:\usepackage/xepersian-multiplechoice#c
nocorrection
correction
#endkeyvals

\begin{question}{text}
\end{question}
\begin{correction}
\end{correction}

\answernumberfont{font commands}
\answerstitle{text}
\answerstitlefont{font commands}
\correctionstyle{font commands}
\false
\falsesymbol{symbol}
\headerfont{font commands}
\makeform
\makemask
\pbs{arg}#*
\questionsepspace
\questionspace
\questiontitle{text}
\questiontitlefont{font commands}
\questiontitlespace
\thequestion
\true
\truesymbol{symbol}
\X{symbol}