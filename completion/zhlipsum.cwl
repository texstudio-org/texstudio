# OsbertWang/2019-10-4 for zhlipsum v1.1.1
# updated by Matthew Bertucci 2022-04-18 for v1.2.0

#include:l3keys2e

#keyvals:\usepackage/zhlipsum#c
encoding=#utf8,gbk,big5
#endkeyvals

\zhlipsum
\zhlipsum[paragraph]
\zhlipsum[paragraph][keyvals]

\zhlipsum*
\zhlipsum*[paragraph]
\zhlipsum*[paragraph][keyvals]

#keyvals:\zhlipsum,\zhlipsum*
name=#simp,trad,nanshanjing,xiangyu,zhufu,aspirin
before=%<content%>
after=%<content%>
inter=%<content%>
#endkeyvals

\newzhlipsum{name}{paragraphs list%text}
