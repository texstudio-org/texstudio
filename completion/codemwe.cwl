# codemwe package
# Matthew Bertucci 2026/10/24 for v1.1.0

#include:tcolorbox
# loads many option of tcolorbox
#include:tcolorboxlibrarymany
#include:fancyvrb
#include:graphicx
#include:minted

\begin{example}{content%text}
\begin{example}[options%keyvals]{content%text}
\end{example}
\begin{example*}{content%text}
\begin{example*}[options%keyvals]{content%text}
\end{example*}

\begin{texcode}#V
\begin{texcode}[options%keyvals]#V
\end{texcode}
\begin{ccode}#V
\begin{ccode}[options%keyvals]#V
\end{ccode}

\codemweset{options%keyvals}
\codemweNewBox{envname}#N
\codemweNewBox{envname}[options%keyvals]#N
\codemweNewLang{name}{text list%text}
\codemweNewBackend{name}{file ext}{comment char}{compilable}
\codemweNewBackend{name}{file ext}{comment char}{compilable}[minted lang]

\begin{mwebox}#*
\end{mwebox}#*
\begin{mwebox*}#*
\end{mwebox*}#*
\begin{mweparbox}#*
\end{mweparbox}#*
\begin{mweparbox*}#*
\end{mweparbox*}#*
\begin{syntaxbox}#*
\end{syntaxbox}#*
\begin{syntaxbox*}#*
\end{syntaxbox*}#*