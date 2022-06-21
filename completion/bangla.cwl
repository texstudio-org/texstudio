# bangla package
# Matthew Bertucci 2022/06/20 for v2.0

#include:fontspec
#include:etoolbox
#include:polyglossia
#include:CharisSIL

#keyvals:\usepackage/bangla#c
kalpurush
shimanto
notosansbengali
notoserifbengali
#endkeyvals

\banglatext{bangla text}
\banglabold{bangla text}
\banglaitalic{bangla text}
\banglatranslit{bangla text}
\banglaipa{bangla text}

\banglapage
\banglasection
\banglaenumerate
\banglaequation
\banglatable
\banglafigure
\banglaallcounters

\bengalinum{counter}
\bengalialpha{counter}

# not documented
\begin{isoindictranse}#*
\end{isoindictranse}#*
\banglaipafont#*
\bdnhbold#*
\bdnhitalic#*
\bdnhtext#*
\bdnhtranslitfont#*
\doindictrans#*
\fooA#S
\indictrans{text%plain}#*
\translitfont{text%plain}#*
\xgenerateTransliteration#S
\xxgenerateTransliteration#S
\xxxgenerateTransliteration{arg}#S
\zzrow{arg1}{arg2}#S
\zztable{arg}#S