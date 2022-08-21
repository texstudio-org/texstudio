# citation-style-language package
# Matthew Bertucci 2022/08/20 for v0.2.0

#include:expl3
#include:xparse
#include:l3keys2e
#include:filehook
#include:url

\cslsetup{options%keyvals}

#keyvals:\cslsetup,\usepackage/citation-style-language#c
style=#american-chemical-society,american-medical-association,american-political-science-association,american-sociological-association,apa,chicago-author-date,chicago-fullnote-bibliography,chicago-note-bibliography,elsevier-harvard,harvard-cite-them-right,ieee,modern-humanities-research-association,modern-language-association,nature,vancouver
locale=%<language code%>
bib-font=%<font commands%>
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
\cites{%<key1%>}{%<key2%>}%<...{keyN}%>
\cites[%<options%>]{%<key1%>}[%<options%>]{%<key2%>}%<...[options]{keyN}%>

#keyvals:\cite,\cites
prefix=%<prefix%>
suffix=%<suffix%>
act=%<number%>
appendix=%<number%>
article-locator=%<number%>
book=%<number%>
canon=%<number%>
chapter=%<number%>
column=%<number%>
elocation=%<number%>
equation=%<number%>
figure=%<number%>
folio=%<number%>
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
title-locator=%<number%>
verse=%<number%>
version=%<number%>
volume=%<number%>
#endkeyvals

\printbibliography
\printbibliography[options]#*
