# nycbullets package
# Matthew Bertucci 2026/10/07 for v1.0

#include:fontspec

\nycbullet{key%plain}
\nycbullet[options%keyvals]{key%plain}
\nycbulletsetup{options%keyvals}

#keyvals:\nycbullet,\nycbulletsetup
set=%<name%>
scale=%<factor%>
raise=##L
color#true,false
renderer=#node,harfbuzz
#endkeyvals

\nycbulletfont[set]