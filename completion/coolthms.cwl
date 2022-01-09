# coolthms package
# Matthew Bertucci 1/8/2021 for v1.2

#include:amssymb
#include:hyperref
#include:etoolbox
#include:scrbase
#include:letltxmacro
#include:ifthen
#include:xargs
#include:kvoptions
#include:ntheorem
# ntheorem loaded with thmmarks option
#include:cleveref

#keyvals:\usepackage/coolthms#c
proofname=%<text%>
proofsymbol=%<symbol%>
proofcaptionstyle=%<font commands%>
proofindent=##L
separator=%<symbol%>
indent=##L
minskip=##L
maxskip=##L
externalchapters#true,false
#endkeyvals

\definetheorem{envname}{thm name}#N
\definetheorem[numbered like]{envname}{thm name}#N
\definetheorem{envname}{thm name}[counter within]#N
\definetheorem[numbered like]{envname}{thm name}[counter within]#*N
\definetheorem{envname}[thm plural name]{thm name}#*N

\Label{key}#l

\theoremmarkup[header font][body font][symbol][indent][separator][numbering]

\begin{proof}
\end{proof}

\proofname#*

# from thmmarks option of ntheorem
\theoremsymbol{symbol}