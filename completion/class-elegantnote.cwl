# elegantnote class
# Matthew Bertucci 2022/05/02 for v2.40

#include:kvoptions
#include:etoolbox
#include:calc
#include:amsmath
#include:amsthm
#include:iftex
#include:newtxtext
#include:helvet
#include:ctex
#include:biblatex
#include:appendix
#include:indentfirst
#include:anyfontsize
#include:graphicx
#include:booktabs
#include:xcolor
#include:hyperref
#include:xpatch
#include:hologo
#include:silence
#include:caption
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:footmisc
#include:titlesec
#include:geometry
#include:extsizes
#include:fancyhdr
#include:tikz
#include:tikzlibraryshadows
#include:listings
#include:lstautogobble

#keyvals:\documentclass/elegantnote#c
color=#green,cyan,blue,sakura,black,brown
device=#pc,pad,kindle,normal,screen
lang=#cn,en
mode=#geye,hazy,sepia
chinesefont=#ctexfont,founder,nofont
citestyle=%<style%>
bibstyle=%<style%>
bibend=#biber,bibtex
fontsize=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt
math=#newtx,mtpro2,cm
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
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

\institute{institute%text}
\keywords{keywords%text}
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
\eitemi#*
\eitemii#*
\eitemiii#*
\ekv{keyvals}#*
\IfEmpty{arg}#*
\ifempty{arg}#*
\updatetext#*
\versiontext#*

brown#B
eblue#B
ecolor#B
ecyan#B
egreen#B
epubblue#B
frenchplum#B
geyecolor
lightgrey#B
sakura#B
winered#B

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
