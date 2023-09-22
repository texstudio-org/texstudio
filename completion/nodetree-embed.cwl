# nodetree-embed package
# Matthew Bertucci 2023/09/11 for v2.3.0

#include:luatex
#include:xcolor
#include:mdframed
#include:fontspec
#include:kvoptions

\NodetreeSet{options%keyvals}
\nodetreeset{options%keyvals}#S

\begin{NodetreeEmbedView}
\begin{NodetreeEmbedView}[options%keyvals]
\end{NodetreeEmbedView}

\begin{NodetreeEmbedEnv}
\begin{NodetreeEmbedEnv}[options%keyvals]
\end{NodetreeEmbedEnv}

\NodetreeEmbedCmd{TeX markup}
\NodetreeEmbedCmd[options%keyvals]{TeX markup}
\NodetreeEmbedInput{file}#i
\NodetreeEmbedInput[options%keyvals]{file}#i
\nodetreeterminalemulator{file}#Si
\nodetreeterminalemulator[options%keyvals]{file}#Si

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
firstline=%<integer%>
lastline=%<integer%>
showmarkup#true,false
#endkeyvals

\NodetreeSetOption[option%keyvals]{value}
\nodetreeoption[option%keyvals]{value}#S
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
firstline
lastline
showmarkup
#endkeyvals

\NodetreeReset
\nodetreereset#S
\NodetreeRegisterCallback{callbacks}
\nodetreeregister{callbacks}#S
\NodetreeUnregisterCallback{callbacks}
\nodetreeunregister{callbacks}#S

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
