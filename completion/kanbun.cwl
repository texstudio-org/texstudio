# kanbun package
# Matthew Bertucci 2022/04/29 for v1.2

#include:l3keys2e
#include:ifluatex

\setkanbun{options%keyvals}

#keyvals:\usepackage/kanbun#c,\setkanbun
scale=%<ratio%>
fontcmd=%<font command%>
rubyfontcmd=%<font command%>
unit=##L
yokoaki=%<ratio%>
tateaki=%<ratio%>
okuriintrusion=%<ratio%>
kumi=#aki,beta
aki
beta
#endkeyvals

\kanjiunit{}{%<left punct%>}{%<kanji%>}{%<other punct%>}{%<kaeriten%>}{}
\kanjiunit{\furiokuri{%<right furigana%>}{%<right okurigana%>}}{%<left punct%>}{%<kanji%>}{%<other punct%>}{%<kaeriten%>}{}
\kanjiunit{}{%<left punct%>}{%<kanji%>}{%<other punct%>}{%<kaeriten%>}{\furiokuri{%<left furigana%>}{%<left okurigana%>}}
\kanjiunit{\furiokuri{%<right furigana%>}{%<right okurigana%>}}{%<left punct%>}{%<kanji%>}{%<other punct%>}{%<kaeriten%>}{\furiokuri{%<left furigana%>}{%<left okurigana%>}}
\furiokuri{furigana}{okurigana}
\kanbunfont
\multifuriokuri{furigana}{okurigana}
\multifuriokuri[raise]{furigana}{okurigana}

\Kanbun
\EndKanbun
\printkanbun
\printkanbuncode
\printkanbunnopar
\printkanbunnoparcode

\begin{kanjipar}#*
\end{kanjipar}#*
\createcatcodes#*
\kaeriten{arg}#*
\matchkana{arg}#*
\Space#*