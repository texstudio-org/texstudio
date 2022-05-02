# elegantpaper class
# Matthew Bertucci 2022/05/02 for v0.10

#include:kvoptions
#include:etoolbox
#include:calc
#include:hyperref
#include:geometry
#include:amsthm
#include:amsmath
#include:amssymb
#include:indentfirst
#include:booktabs
#include:multicol
#include:multirow
#include:xcolor
#include:graphicx
#include:fancyvrb
#include:abstract
#include:hologo
#include:caption
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:iftex
#include:newtxtext
#include:helvet
#include:biblatex
#include:appendix
#include:footmisc
#include:listings

#keyvals:\documentclass/elegantpaper#c
lang=#cn,en
math=#newtx,mtpro2,cm
citestyle=%<style%>
bibstyle=%<style%>
bibend=#biber,bibtex
chinesefont=#ctexfont,founder,nofont
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:lang=cn
#include:ctex
#include:xeCJK
\songti
\heiti
\kaishu
\fangsong
#endif
#ifOption:cn
#include:ctex
#include:xeCJK
\songti
\heiti
\kaishu
\fangsong
#endif

#ifOption:math=mtpro2
#include:mtpro2
#endif
#ifOption:mtpro2
#include:mtpro2
#endif

#ifOption:math=newtx
#include:newtxmath
#include:esint
\prodop#*m
\sumop#*m
#endif
#ifOption:newtx
#include:newtxmath
#include:esint
\prodop#*m
\sumop#*m
#endif

\email{email%URL}#U
\figref{label}#r
\institute{institute%text}
\keywords{keywords%text}
\tabref{label}#r
\version{version}

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{conjecture}
\begin{conjecture}[heading%text]
\end{conjecture}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{note}
\begin{note}[heading%text]
\end{note}
\begin{case}
\begin{case}[heading%text]
\end{case}

\cfs#*
\citshape#*
\cnormal#*
\ebibname#*
\ekv{keyvals}#*
\IfEmpty{arg}#*
\updatetext#*
\versiontext#*

winered#B
lightgrey#B
commentcolor#B
frenchplum#B

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

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