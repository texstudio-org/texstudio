# arabxetex package
# Matthew Bertucci 4/9/2022 for v1.2.1

#include:xetex
#include:amsmath
#include:fontspec
#include:bidi

#keyvals:\usepackage/arabxetex#c
fullvoc
voc
novoc
trans
utf
mirrorpunct
#endkeyvals

\textarab{text%definition}
\textarab[option%keyvals]{text%definition}
\textfarsi{text%definition}
\textfarsi[option%keyvals]{text%definition}
\texturdu{text%definition}
\texturdu[option%keyvals]{text%definition}
\textsindhi{text%definition}
\textsindhi[option%keyvals]{text%definition}
\textpashto{text%definition}
\textpashto[option%keyvals]{text%definition}
\textottoman{text%definition}
\textottoman[option%keyvals]{text%definition}
\textkurdish{text%definition}
\textkurdish[option%keyvals]{text%definition}
\textkashmiri{text%definition}
\textkashmiri[option%keyvals]{text%definition}
\textmalay{text%definition}
\textmalay[option%keyvals]{text%definition}
\textuighur{text%definition}
\textuighur[option%keyvals]{text%definition}
\textmaghribi{text%definition}
\textmaghribi[option%keyvals]{text%definition}

\begin{arab}
\begin{arab}[option%keyvals]
\end{arab}
\begin{farsi}
\begin{farsi}[option%keyvals]
\end{farsi}
\begin{urdu}
\begin{urdu}[option%keyvals]
\end{urdu}
\begin{sindhi}
\begin{sindhi}[option%keyvals]
\end{sindhi}
\begin{pashto}
\begin{pashto}[option%keyvals]
\end{pashto}
\begin{ottoman}
\begin{ottoman}[option%keyvals]
\end{ottoman}
\begin{kurdish}
\begin{kurdish}[option%keyvals]
\end{kurdish}
\begin{kashmiri}
\begin{kashmiri}[option%keyvals]
\end{kashmiri}
\begin{malay}
\begin{malay}[option%keyvals]
\end{malay}
\begin{uighur}
\begin{uighur}[option%keyvals]
\end{uighur}
\begin{maghribi}
\begin{maghribi}[option%keyvals]
\end{maghribi}

#keyvals:\textarab,\textfarsi,\texturdu,\textsindhi,\textpashto,\textottoman,\textkurdish,\textkashmiri,\textmalay,\textuighur,\textmaghribi,\begin{arab},\begin{farsi},\begin{urdu},\begin{sindhi},\begin{pashto},\begin{ottoman},\begin{kurdish},\begin{kashmiri},\begin{malay},\begin{uighur},\begin{maghribi}
novoc
voc
fullvoc
trans
utf
#endkeyvals

\textLR{text}
\aemph{text%definition}

\arabicfont

\SetTranslitConvention{type%keyvals}
#keyvals:\SetTranslitConvention#c
dmg
loc
#endkeyvals

\SetTranslitStyle{style commands}
\UC

# aliases
\textarabic{text%definition}#*
\textarabic[option%keyvals]{text%definition}#*
\begin{Arabic}#*
\begin{Arabic}[option]#*
\end{Arabic}#*
\textjawi{text%definition}#*
\textjawi[option%keyvals]{text%definition}#*
\begin{jawi}#*
\begin{jawi}[option]#*
\end{jawi}#*
\textpersian{text%definition}#*
\textpersian[option%keyvals]{text%definition}#*
\begin{persion}#*
\begin{persion}[option]#*
\end{persion}#*
\textturk{text%definition}#*
\textturk[option%keyvals]{text%definition}#*
\begin{turk}#*
\begin{turk}[option]#*
\end{turk}#*

# deprecated
\SetAllahWithAlif#S
\SetAllahWithoutAlif#S