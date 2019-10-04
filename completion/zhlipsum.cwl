# OsbertWang/2019-10-4 for zhlipsum v1.1.1

#include:expl3
#include:l3keys2e
#include:xparse

\zhlipsum
\zhlipsum[keyvals]
\zhlipsum[num]
\zhlipsum[num][keyvals]

\zhlipsum*
\zhlipsum*[keyvals]
\zhlipsum*[num]
\zhlipsum*[num][keyvals]

#keyvals:\zhlipsum
name=#simp,trad,nanshanjing,xiangyu,zhufu,aspirin
before=
after=
inter=
#endkeyvals

\newzhlipsum{name}{paragrph}