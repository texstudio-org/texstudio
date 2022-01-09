# vector package
# Matthew Bertucci 1/8/2021 for v1.0

#include:calc
#include:ifthen

#keyvals:\usepackage/vector#c
wavy
#endkeyvals

\bvec{arg}
\buvec{arg}
\svec{arg}
\suvec{arg}
\uvec{arg}
\uuvec{arg}
\firstelement{start index}
\irvec{arg}
\irvec[end index]{arg}
\icvec{arg}#m
\icvec[end index]{arg}#m
\rvec{arg}{start index}{end index}
\cvec{arg}{start index}{end index}#m

#ifOption:wavy
\undertilde{arg}#m
#endif