# newfile package
# Matthew Bertucci 10/4/2021 for v1.0b

#include:verbatim

\newoutputstream{stream}#*
\newinputstream{stream}#*
\openoutputfile{file}{stream}#*
\closeoutputstream{stream}#*
\begin{writeverbatim}{stream}#*V
\end{writeverbatim}#*
\addtostream{stream}{text}#*
\openinputfile{file}{stream}#*
\closeinputstream{stream}#*
\readstream{stream}#*
\readaline{stream}#*
\readverbatim{stream}#*
\streamvfont{font cmds}#*
\numbervstream#*
\marginnumbervstream#*
\streamvnumfont{font cmds}#*
\plainvstream#*