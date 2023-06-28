# xpinyin package
# Matthew Bertucci 2022/07/26 for v3.1

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
