# codebox package
# Matthew Bertucci 1/6/2022 for v1.0.3

#include:xtemplate
#include:l3keys2e
#include:fontawesome5
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:tcolorboxlibrarybreakable
#include:tcolorboxlibraryminted
#include:tcolorboxlibrarylistings
#include:tikzlibraryshapes.geometric
#include:varwidth
#include:xcolor
#include:etoolbox

\begin{codebox}{title%text}#V
\begin{codebox}[options%keyvals]{title%text}#V
\end{codebox}
\begin{codebox*}{title%text}#V
\begin{codebox*}[options%keyvals]{title%text}#V
\end{codebox*}

\codefile{title%text}{file}
\codefile[options%keyvals]{title%text}{file}
\codefile*{title%text}{file}
\codefile*[options%keyvals]{title%text}{file}

\begin{codeview}{title%text}#V
\begin{codeview}[options%keyvals]{title%text}#V
\end{codeview}
\begin{codeview*}{title%text}#V
\begin{codeview*}[options%keyvals]{title%text}#V
\end{codeview*}

\cvfile{title%text}{file}
\cvfile[options%keyvals]{title%text}{file}
\cvfile*{title%text}{file}
\cvfile*[options%keyvals]{title%text}{file}

\codeset{options%keyvals}

#keyvals:\begin{codebox},\begin{codebox*},\codefile,\codefile*,\begin{codeview},\begin{codeview*},\cvfile,\cvfile*
minted#true,false
lang=%<source code lang%>
pretitle=%<title prefix%>
codestyle=%<highlight style%>
codesize=%<fontsize macro%>
comments=%<text%>
commentf=%<format macros%>
codestretch=%<factor%>
linenumsep=%<number%>
#endkeyvals

#keyvals:\begin{codeview},\begin{codeview*},\cvfile,\cvfile*
label=##l
#endkeyvals

\thecvcounter

cvgrayc#B
cvgray#B
cvgrayb#B
cvblue#B
chengse#B
