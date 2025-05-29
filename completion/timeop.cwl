# timeop package
# Matthew Bertucci 2025/05/25 for v0.1.1

#include:amsmath
#include:xstring
#include:xintexpr
#include:listofitems
#include:simplekv
#include:tcolorbox
#include:tcolorboxlibraryskins

#keyvals:\usepackage/timeop#c
noamsmath
#endkeyvals

\boxhms{color}
\hmtos{hour,minute}
\hmtos{hour,minute}[\macro]
\hmstos{hour,minute,second}
\hmstos{hour,minute,second}[\macro]
\stohms{second}
\stohms{second}[\macro]
\stohms[keyvals]{second}
\stohms[keyvals]{second}[\macro]
\simpletimeop{h1,m1,s1}{h2,m2,s2}{h3,m3,s3}
\simpletimeop[keyvals]{h1,m1,s1}{h2,m2,s2}{h3,m3,s3}
\calctimeop{h1,m1,s1}{h2,m2,s2}
\calctimeop[keyvals]{h1,m1,s1}{h2,m2,s2}