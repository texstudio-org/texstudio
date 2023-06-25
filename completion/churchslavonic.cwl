# churchslavonic package
# Matthew Bertucci 2023/06/25 for v0.2.4

#keyvals:\usepackage/churchslavonic#c
# options passed to cu-kinovar package
color
gray
bw
# options passed to cu-kruk package
autocolormarks
noautocolormarks
#endkeyvals

#include:ifluatex
#include:cu-num
#include:cu-calendar
#include:cu-util
#include:cu-kinovar
#include:cu-kruk

\cuMarginMark{text}

\cuMarginMarkSkip#*
\cuMarginMarkText{text}#*

# from gloss-churchslavonic.ldf
\textchurchslavonic[options%keyvals]{text}
\textchurchslavonic{text}
\begin{churchslavonic}[options%keyvals]
\begin{churchslavonic}
\end{churchslavonic}

#keyvals:\setdefaultlanguage/churchslavonic#c,\setmainlanguage/churchslavonic#c,\setotherlanguage/churchslavonic#c,\textlang/churchslavonic#c,\textchurchslavonic#c,\begin{lang}/churchslavonic#c,\begin{churchslavonic}#c,\selectlanguage/churchslavonic#c,\foreignlanguage/churchslavonic#c,\begin{otherlanguage}/churchslavonic#c,\begin{otherlanguage*}/churchslavonic#c,\resetdefaultlanguage/churchslavonic#c,\setlanguagealias/churchslavonic#c,\setlanguagealias*/churchslavonic#c,\pghyphenation/churchslavonic#c,\setlanghyphenmins/churchslavonic#c
spelling=#modern,traditional
numerals=#latin,cyrillic
babelshorthands#true,false
#endkeyvals

\captionschurchslavonic#*
\datechurchslavonic#*
\Azbuk{counter}#*
\azbuk{counter}#*
\sh#*m
\ch#*m
\tg#*m
\arctg#*m
\arcctg#*m
\th#*m
\ctg#*m
\cth#*m
\cosec#*m
\Prob#*m
\Variance#*m
\nod#*m
\nok#*m
\NOD#*m
\NOK#*m
\Proj#*m
