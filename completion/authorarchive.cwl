# authorarchive package
# Matthew Bertucci 2023/02/10 for v1.3.0

#include:ifthen
#include:enumitem
# enumitem loaded with inline option
#include:orcidlink
#include:eso-pic
#include:intopdf
#include:kvoptions
#include:hyperref
#include:calc
#include:qrcode
#include:etoolbox
#include:lastpage

\authorsetup{option%keyvals}

#keyvals:\usepackage/authorarchive#c,\authorsetup
bibtexdir=%<directory%>
baseurl=%<URL%>
suffix=%<string%>
publisher=%<text%>
year=%<year%>
key=%<string%>
doi=%<DOI%>
doiText=%<text%>
publisherurl=%<URL%>
startpage=%<start page%>
publication=%<text%>
ACM#true,false
acmart#true,false
ENTCS#true,false
IEEE#true,false
LNCS#true,false
LNI#true,false
nocopyright#true,false
nourl#true,false
nobib#true,false
orcidicon#true,false
#endkeyvals

\authorcrfont#*
\authorat{text}#*
\authorwidth{width}#*
\BibTeX

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}
