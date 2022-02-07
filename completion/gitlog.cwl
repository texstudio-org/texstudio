# gitlog package
# Matthew Bertucci 2/5/2022 for v0.0beta

#include:etoolbox
#include:kvoptions
#include:biblatex

#keyvals:\usepackage/gitlog#c
title=%<log title%>
date#true,false
nodate
write#true,false
nowrite
bibfile=%<file name%>
github=%<repository path%>
bitbucket=%<repository path%>
#endkeyvals

\printGitLog