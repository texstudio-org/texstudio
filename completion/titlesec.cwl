# Package titlesec
# http://ctan.org/tex-archive/macros/latex/contrib/titlesec
# By astroscion: 2012-02-15
# muzimuzhi, 5 Jun 2020, 22 Jun 2020
# Matthew Bertucci 8/16/2021

#ifOption:pagestyles
#include:titleps
#endif

\titlelabel{label-format}
\thetitle
\titleformat*{command%plain}{format}
\titleformat{command%plain}[shape]{format}{label}{sep%l}{before-code}[after-code]
\chaptertitlename
\titlespacing{command%plain}{left%l}{before-sep%l}{after-sep%l}
\titlespacing{command%plain}{left%l}{before-sep%l}{after-sep%l}[right-sep%l]
\titlespacing*{command%plain}{left%l}{before-sep%l}{after-sep%l}
\titlespacing*{command%plain}{left%l}{before-sep%l}{after-sep%l}[right-sep%l]
\beforetitleunit#*
\aftertitleunit#*
\filright
\filcenter
\filleft
\fillast
\filinner
\filouter
\wordsep
\bottomtitlespace#*
\nostruts#*
\titleline[align]{horizontal material}
\titlerule[height]
\titlerule*[width]{text}
\titlewidth#*
\titlewidthfirst#*
\titlewidthlast#*
\iftitlemeasuring{true}{false}
\assignpagestyle{command%plain}{pagestyle}
\sectionbreak
\subsectionbreak
\subsubsectionbreak
\paragraphbreak
\subparagraphbreak
\subsubparagraphbreak
\chaptertolists
\titleclass{name}{class%plain}
\titleclass{name}{class%plain}[super-level-cmd]
\titleclass{name}[start-level-num]{class%plain}
