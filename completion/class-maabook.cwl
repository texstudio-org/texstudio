# maabook class
# Matthew Bertucci 2022/08/22 for v1.06

#include:ifxetex
#include:ifpdf
#include:amsgen
#include:upref
#include:amscip
#include:graphicx
#include:amsmath
#include:xspace
#include:amsthm

#keyvals:\documentclass/maabook#c
letterpaper
a4paper
5.5x8.5
6x9
7x10
draft
proofing
final
openright
openany
cmr
mathtimes
stix2
cambria
brill
10pt
11pt
#endkeyvals

#ifOption:proofing
#include:shaderef
#endif

#ifOption:mathtimes
#include:mtpro2
#endif

#ifOption:stix2
#include:stix2
#endif

\affiliation{arg}#S
\alsoname#*
\backmatter
\begin{xcb}
\bibintro#*
\bibliofont#*
\bibname#*
\bysame#*
\calclayout#*
\captionindent#*
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chapter{title}#L1
\chaptername#*
\chapterrunhead{name}{number}{title}#*
\citeform{text}#*
\copyrightholder#*
\copyrightinfo{year}{holder}#*
\copyrightyear#*
\dedicatory{text}
\DOI{DOI}#*
\end{xcb}
\evdef{cmd}{def}#*d
\forcehyphenbreak#*
\forcelinebreak#*
\frontmatter
\fullwidthdisplay#*
\indexchap{text}#*
\indexintro#*
\initMAAenummargins{arg1}{arg2}{arg3}{arg4}#*
\keywords{text}
\keywordsname#*
\larger#*
\larger[value]#*
\mainmatter
\makededication#*
\makehalftitle#*
\markleft{lefthead%text}#*
\maxcaptionwidth#*
\MR{MR number}#*
\MRhref{arg}#*
\nonbreakingspace#*
\normalparindent#*
\normaltopskip#*
\partrunhead{name}{number}{title}#*
\printindex#*
\sectionrunhead{name}{number}{title}#*
\see{text}{page number}#*
\seealso{text}{page number}#*
\seename#*
\seeonly{text}{page number}#*
\seeonlyname#*
\seriesinfo{publkey}{volumeid}{volumeno}#*
\SMALL#*
\Small#*
\smaller#*
\smaller[value]#*
\subjclass[year]{text}
\subjclass{text}
\subjclassname#*
\subtitle{text}
\thechapter#*
\Tiny#*
\title[short title]{text}
\tocappendix{epithet}{number}{topic}#*
\tocchapter{epithet}{number}{topic}#*
\tochyphenbreak#*
\toclinebreak#*
\tocparagraph{epithet}{number}{topic}#*
\tocpart{epithet}{number}{topic}#*
\tocsection{epithet}{number}{topic}#*
\tocsubparagraph{epithet}{number}{topic}#*
\tocsubsection{epithet}{number}{topic}#*
\tocsubsubsection{epithet}{number}{topic}#*
\URL{URL}#*U
\URLhref{arg}#*