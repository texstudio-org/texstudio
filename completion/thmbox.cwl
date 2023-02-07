# thmbox package
# Matthew Bertucci 2023/02/06 for v2.0

#include:keyval

#keyvals:\usepackage/thmbox#c
nothm
nocut
nounderline
#endkeyvals

\thmboxoptions{options%keyvals}

\begin{thmbox}{title%text}
\begin{thmbox}[options%keyvals]{title%text}
\end{thmbox}

\begin{leftbar}
\begin{leftbar}[options%keyvals]
\end{leftbar}

\newtheorem[options%keyvals]{envname}{caption}#N
\newtheorem[options%keyvals]{envname}{caption}[within]#N

#keyvals:\thmboxoptions#c,\begin{thmbox}#c,\begin{leftbar}#c,\newtheorem#c
style=#S,M,L
S
M
L
cut#true,false
underline#true,false
headstyle=%<code%>
titlestyle=%<code%>
bodystyle=%<code%>
leftmargin=##L
rightmargin=##L
hskip=##L
vskip=##L
thickness=##L
#endkeyvals

\begin{proof}
\begin{proof}[postfix]
\end{proof}

\begin{example}
\begin{example}[label text]
\end{example}

\examplename#*
\proofname#*

\newboxtheorem{envname}{caption}#SN
\newboxtheorem[options]{envname}{caption}#SN
