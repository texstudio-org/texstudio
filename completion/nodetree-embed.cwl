# nodetree-embed package
# Matthew Bertucci 2/8/2022 for v2.2

#include:luatex
#include:xcolor
#include:mdframed
#include:expl3
#include:xparse
#include:fontspec
#include:kvoptions

\NodetreeSet{options%keyvals}

\begin{NodetreeEmbedView}
\begin{NodetreeEmbedView}[options%keyvals]
\end{NodetreeEmbedView}

\begin{NodetreeEmbedEnv}
\begin{NodetreeEmbedEnv}[options%keyvals]
\end{NodetreeEmbedEnv}

\NodetreeEmbedCmd{TeX markup}
\NodetreeEmbedCmd[options%keyvals]{TeX markup}
\NodetreeEmbedInput{file}#*
\NodetreeEmbedInput[options%keyvals]{file}#*
\nodetreeterminalemulator{file}#*i
\nodetreeterminalemulator[options%keyvals]{file}#*i

#keyvals:\usepackage/nodetree-embed#c,\NodetreeSet,\begin{NodetreeEmbedView},\begin{NodetreeEmbedEnv},\NodetreeEmbedCmd,\NodetreeEmbedInput,\nodetreeterminalemulator
channel=%<output channel%>
callback={%<callbacks%>}
verbosity=%<integer%>
color=#colored,no
unit=#pt,pc,in,bp,cm,mm,dd,cc,sp,ex,em
decimalplaces=%<integer%>
theme=#bwdark,bwlight,monokaisoda
thememode=#dark,light
font=%<font name%>
fontsize=%<fontsize cmd%>
showmarkup#true,false
#endkeyvals

\NodetreeSetOption[option%keyvals]{value}
\nodetreeoption[option%keyvals]{value}#*
\NodetreeResetOption{option%keyvals}

#keyvals:\NodetreeSetOption,\nodetreeoption,\NodetreeResetOption
channel
callback
verbosity
color
unit
decimalplaces
theme
thememode
font
fontsize
showmarkup
#endkeyvals

\NodetreeReset
\nodetreereset#*
\NodetreeRegisterCallback{callbacks}
\nodetreeregister{callbacks}#*
\NodetreeUnregisterCallback{callbacks}
\nodetreeunregister{callbacks}#*

NTEblack#B
NTEred#B
NTEgreen#B
NTEyellow#B
NTEblue#B
NTEmagenta#B
NTEcyan#B
NTEwhite#B
NTEblackbright#B
NTEredbright#B
NTEgreenbright#B
NTEyellowbright#B
NTEbluebright#B
NTEmagentabright#B
NTEcyanbright#B
NTEwhitebright#B
NTEbackground#B
NTEfont#B