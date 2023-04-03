# citation-style-language package
# Matthew Bertucci 2023/04/03 for v0.4.0

#include:filehook
#include:url

\cslsetup{options%keyvals}

#keyvals:\cslsetup,\usepackage/citation-style-language#c
regression-test#true,false
style=#american-chemical-society,american-medical-association,american-political-science-association,american-sociological-association,apa,chicago-author-date,chicago-fullnote-bibliography,chicago-note-bibliography,elsevier-harvard,harvard-cite-them-right,ieee,modern-humanities-research-association,modern-language-association,nature,vancouver
class=
locale=%<language code%>
backref=#true,page,section,false
bib-font=%<font commands%>
bib-entry-page-break#true,false
bib-item-sep=%<<length> or <glue>%>
bib-hang=##L
hanging-indent#true,false
prefix-separator=%<separator%>
suffix-separator=%<separator%>
line-spacing=%<number%>
entry-spacing=%<number%>
#endkeyvals

\addbibresource{bib file}
\addbibresource[options]{bib file}#*

\cite[options%keyvals]{keylist}
\parencite{keylist}#*
\parencite[options%keyvals]{keylist}#*
\citep{keylist}#*
\citep[options%keyvals]{keylist}#*
\textcite{keylist}
\textcite[options%keyvals]{keylist}
\citet{keylist}#*
\citet[options%keyvals]{keylist}#*
\footcite{keylist}
\footcite[options%keyvals]{keylist}
\cites{%<key1%>}{%<key2%>}%<...{keyN}%>
\cites[%<options%>]{%<key1%>}[%<options%>]{%<key2%>}%<...[options]{keyN}%>
\citeauthor{keylist}

#keyvals:\cite,\parencite,\citep,\textcite,\citet,\cites
prefix=%<text%>
suffix=%<text%>
act=%<number%>
appendix=%<number%>
article=%<number%>
book=%<number%>
canon=%<number%>
chapter=%<number%>
column=%<number%>
elocation=%<number%>
equation=%<number%>
figure=%<number%>
folio=%<number%>
infix=%<text%>
issue=%<number%>
line=%<number%>
note=%<number%>
opus=%<number%>
page=%<number%>
paragraph=%<number%>
part=%<number%>
rule=%<number%>
scene=%<number%>
section=%<number%>
sub-verbo=%<number%>
supplement=%<number%>
table=%<number%>
timestamp=%<number%>
title=%<number%>
verse=%<number%>
version=%<number%>
volume=%<number%>
#endkeyvals

\printbibliography
\printbibliography[options]#*

# not documented
\DeclareBibliographyCategory{arg}#*
\addtocategory{arg1}{arg2}#*
