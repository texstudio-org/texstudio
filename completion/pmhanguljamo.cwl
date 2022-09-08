# pmhanguljamo package
# Matthew Bertucci 2022/09/08 for v0.5.1

#include:xparse
#include:l3keys2e

#keyvals:\usepackage/pmhanguljamo#c
RRK
rrk
pmfont=%<font name%>
pmfontfeature=%<font feature%>
#endkeyvals

\jamoword{words}
\begin{jamotext}
\end{jamotext}
\jmcc{single jamo}
\jamoul{ulem csname}{jamo text}
\jamotextcmd{arg}#*
\ColonMark#*
\SemiColonMark#*
\SlashMark#*
\CntrdotMark#*
\usepmfont
\unusepmfont
\setpmhangulfont{font name}
\setpmhangulfont{font name}[font features]
\setpmhangulfont[font features]{font name}#*
