# autonum package
# Matthew Bertucci 2022/07/20 for v0.3.11

#include:etoolbox
#include:etextools
#include:amsmath
#include:textpos
#include:letltxmacro

\begin{equation+}#\math
\end{equation+}

\csxdefall{csname}{replacement}#*
\csxdefaux{csname}{replacement}#*
\ifcsedef{csname}{true}{false}#*
\meaningx%<\cmd%>#*
\newcommandsequence{csname}{def}#*
\newcommandsequence{csname}[args]{def}#*
\newcommandsequence{csname}[args][default]{def}#*
\renewcommandsequence{csname}{def}#*
\renewcommandsequence{csname}[args]{def}#*
\renewcommandsequence{csname}[args][default]{def}#*
\skipInPDFTOC{arg}#*
\vanishprotect{arg}#*
\CsLetLtxMacro{csname}{cmd}#*
\LetCsLtxMacro{cmd}{csname}#*d
\CsLetCsLtxMacro{csname}{csname}#*
\GlobalCsLetLtxMacro{csname}{cmd}#*
\GlobalLetCsLtxMacro{cmd}{csname}#*d
\GlobalCsLetCsLtxMacro{csname}{csname}#*