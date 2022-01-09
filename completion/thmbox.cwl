# thmbox package
# Matthew Bertucci 1/8/2021 for v2.0

#include:keyval

#keyvals:\usepackage/thmbox#c
nothm
style=#S,M,L
cut#true,false
underline#true,false
headstyle=%<code%>
titlestyle=%<code%>
bodystyle=%<code%>
leftmargin=##L
hskip=##L
thickness=##L
#endkeyvals

\thmboxoptions#*

\begin{thmbox}{title%text}
\begin{thmbox}[style%keyvals]{title%text}
\end{thmbox}

\begin{leftbar}
\begin{leftbar}[style%keyvals]
\end{leftbar}

\newtheorem[style%keyvals]{envname}{caption}#N

#keyvals:\begin{thmbox},\begin{leftbar},\newtheorem
S
M
L
#endkeyvals

\begin{proof}
\begin{proof}[postfix]
\end{proof}

\begin{example}
\begin{example}[label text]
\end{example}

\newboxtheorem{envname}{caption}#*N