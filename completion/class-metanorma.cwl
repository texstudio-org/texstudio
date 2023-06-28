# metanorma class
# Matthew Bertucci 2/19/2022 for v0.5.0

#include:graphicx
#include:hyperref
#include:amsmath
#include:subcaption
#include:enumitem
#include:verbatim
#include:ulem
#include:mdframed
# mdframed loaded with framemethod=TikZ option
#include:tikz

\set{attribute%specialDef}{value}#s#%metanormaattribute
\get{attribute%keyvals}

#keyvals:\get#c
%metanormaattribute
#endkeyvals

\mn{keyvals}

#keyvals:\mn#c
heading=%<heading%>
level=%<level%>
obligation=#informative,normative
language=%<lang code%>
script=%<script name%>
reviewer="%<name%>"
from=%<anchor%>
to=%<anchor%>
date=%<date%>
#endkeyvals

\alt{term%text}
\deprecated{term%text}
\domain{domain%text}

\begin{example}
\end{example}
\begin{note}
\end{note}
\begin{source}
\end{source}

\mncite{key}#c
\mncite[add. text%text]{key}#c
\mncite{key}[localities]#c
\mncite[add. text%text]{key}[localities]#c

\begin{key}
\end{key}

\begin{requirement}
\end{requirement}
\begin{recommendation}
\end{recommendation}
\begin{permission}
\end{permission}

\begin{specification}
\end{specification}
\begin{measurement-target}
\end{measurement-target}
\begin{verification}
\end{verification}
\begin{import}
\end{import}

\begin{tip}
\end{tip}
\begin{important}
\end{important}
\begin{caution}
\end{caution}
\begin{warning}
\end{warning}

# not documented
\att{arg}#S
\att[opt]{arg}#S
\lxRDFa{arg}#S
\lxRDFa[opt]{arg}#S
\lxRDF{arg}#S
\lxRDF[opt]{arg}#S