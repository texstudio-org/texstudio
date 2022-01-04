# xpinyin package
# Matthew Bertucci 12/30/2021 for v2.9

#include:xparse
#include:l3keys2e
#include:CJKutf8

\begin{pinyinscope}
\begin{pinyinscope}[options%keyvals]
\end{pinyinscope}

\xpinyin{character}{pinyin}
\xpinyin[options%keyvals]{character}{pinyin}
\xpinyin*{text}
\xpinyin*[options%keyvals]{text}

\pinyin{pinyin}
\pinyin[options%keyvals]{pinyin}

\setpinyin{characters}{pinyin}

\xpinyinsetup{options%keyvals}

#keyvals:\begin{pinyinscope},\xpinyin,\pinyin,\xpinyinsetup
ratio=%<number%>
vsep=##L
hsep=##L
pysep=%<glue%>
font=%<font%>
format=%<format%>
multiple=%<format%>
footnote#true,false
#endkeyvals

\disablepinyin
\enablepinyin