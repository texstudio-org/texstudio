# verbatimbox package
# Matthew Bertucci 2023/08/09 for v3.2

#include:verbatim
#include:readarray

\begin{verbbox}#V
\begin{verbbox}[pre-commands]#V
\end{verbbox}
\begin{myverbbox}{token%cmd}#d\verbatim
\begin{myverbbox}[pre-commands]{token%cmd}#d\verbatim
\end{myverbbox}
\verbfilebox{file}
\verbfilebox[pre-commands]{file}
\theverbbox
\theverbbox[t]%|
\boxtopsep#*
\boxbottomsep#*
\addvbuffer{object}
\addvbuffer[length]{object}
\begin{verbnobox}#V
\begin{verbnobox}[pre-commands]#V
\end{verbnobox}
\verbfilenobox{file}
\verbfilenobox[pre-commands]{file}

# not documented
\begin{origverbbox}#SV
\begin{origverbbox}[pre-commands]#SV
\end{origverbbox}#S
\savedverbbox#S
\theVerbboxLineNo#S
\verbatimboxVersionNumber#S
