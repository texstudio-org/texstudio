# hangulmath package
# Matthew Bertucci 2026/10/16 for v0.7

#include:iftex
#include:fontspec
#include:amstext
#include:graphicx

#keyvals:\usepackage/hangulmath#c
font=%<font%>
opfont=%<font%>
metrics=%<file%>
scale=%<factor%>
sidebearing=%<em%>
#endkeyvals

\hangulmathfont{font}
\hangulmathopfont{font}
\hangulopscale{display}{text%plain}

\hangulsum{symbol}#m
\hangulint{symbol}#m
\hangullim{symbol}#m

\hangulsym{name}#m

\aeh#m
\ah#m
\bieup#m
\chieut#m
\digeut#m
\eh#m
\eoh#m
\euh#m
\euih#m
\giyeok#m
\hieut#m
\ieung#m
\ih#m
\jieut#m
\kieuk#m
\mieum#m
\nieun#m
\oeh#m
\oh#m
\pieup#m
\rieul#m
\siot#m
\ssangbieup#m
\ssangdigeut#m
\ssanggiyeok#m
\ssangjieut#m
\ssangsiot#m
\tieut#m
\uaeh#m
\uah#m
\ueh#m
\ueoh#m
\uh#m
\uih#m
\yaeh#m
\yah#m
\yeh#m
\yeoh#m
\yoh#m
\yuh#m