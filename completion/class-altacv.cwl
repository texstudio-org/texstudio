# Created by Jonathan Herbert
# edited 2023/02/08 by Matthew Bertucci for v1.6.5

#include:class-extarticle
#include:etoolbox
#include:pdfx
#include:accsupp
#include:geometry
#include:fontawesome5
#include:ifxetex
#include:ifluatex
#include:scrlfile
#include:fontspec
#include:xcolor
#include:tikz
#include:tcolorbox
#include:tcolorboxlibraryskins
#include:enumitem
# loads inline option of enumitem
#include:graphicx
#include:trimclip
#include:dashrule
#include:multirow
#include:tabularx
#include:changepage
#include:afterpage
#include:pgffor
#include:biblatex

#keyvals:\documentclass/altacv#c
normalphoto
ragged2e
withhyper
# options passed to extarticle
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
draft
final
leqno
fleqn
openbib
#endkeyvals

#ifOption:ragged2e
#include:ragged2e
# loads newcommands option of ragged2e
\LaTeXcentering#*
\LaTeXraggedleft#*
\LaTeXraggedright#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushleft}#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushright}#*
\begin{LaTeXcenter}#*
\end{LaTeXcenter}#*
#endif

\itemmarker
\ratingmarker
\divider
\emailsymbol
\mailaddresssymbol
\phonesymbol
\homepagesymbol
\twittersymbol
\linkedinsymbol
\githubsymbol
\orcidsymbol
\locationsymbol
\printinfo{%<symbol%>}{%<detail%>}
\printinfo{%<symbol%>}{%<detail%>}[%<hyperlink prefix%>]
\name{%<name%>}
\tagline{%<information%>}
\photo{size}{imagefile}#g
\photoR{size}{imagefile}#g
\photoL{size}{imagefile}#g
\email{email%URL}#U
\mailaddress{%<mail address%>}
\phone{%<phone number%>}
\homepage{homepage address%URL}#U
\twitter{%<twitter username%>}
\linkedin{%<linkedin username%>}
\github{%<github username%>}
\orcid{%<orcid number%>}
\location{%<location%>}
\personalinfo{%<information%>}
\makecvheader
\cvsection{title}#L2
\cvsection[sidebar file%file]{title}#L2
\cvsubsection{title}#L3
\cvachievement{icon}{name%text}{description%text}
\cvevent{title%text}{company or institution}{time period}{location}
\cvtag{%<name%>}
\cvskill{%<name%>}{%<value%>}
\wheelchart{outer radius}{inner radius}{value/width/color/detail,...}
\cvref{%<name%>}{%<email%>}{%<mailing address%>}
\begin{cvcolumn}{width}
\end{cvcolumn}
\addsidebar{file}#i
\addsidebar[vspace]{file}#i
\addnextpagesidebar{file}#i
\addnextpagesidebar[vspace]{file}#i
\begin{fullwidth}
\end{fullwidth}
\ifxetexorluatex
\xetexorluatextrue#S
\xetexorluatexfalse#S
\mynames{name1,name2,...}
\utffriendlydetokenize{arg}#S
\NewInfoField{fieldname}{symbol}
\NewInfoField{fieldname}{symbol}[hyperlink prefix]
\NewInfoField*{fieldname}{symbol}
\NewInfoField*{fieldname}{symbol}[hyperlink prefix]
\namefont#*
\taglinefont#*
\personalinfofont#*
\cvsectionfont#*
\cvsubsectionfont#*

accent#B
emphasis#B
heading#B
headingrule#B
subheading#B
body#B
name#B
tagline#B

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
