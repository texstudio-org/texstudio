# xpinyin package
# Matthew Bertucci 2026/09/30 for v3.2

#include:CJKutf8

#keyvals:\usepackage/xpinyin#c
query
#endkeyvals

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
scheme=#literal,official
tone=#mark,number,none,v
#endkeyvals

\disablepinyin
\disablepinyin*
\enablepinyin

\xpinyinvalue{character}
\xpinyinvalue*{character}
\xpinyininitial{character}
\xpinyininitial*{character}
\xpinyinshengmu{character}
\xpinyinyunmu{character}