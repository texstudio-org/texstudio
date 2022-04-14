# CoverPage package
# Matthew Bertucci 4/11/2022 for v1.01

#include:keyval
#include:textcomp
#include:url
#include:verbatim

#keyvals:\usepackage/CoverPage#c
german
english
twoside
nobib
#endkeyvals

\CoverPageSetup{options%keyvals}

#keyvals:\CoverPageSetup
title=%<text%>
author=%<text%>
institute=%<text%>
insource=%<text%>
copyright=%<text%>
year=%<year%>
publisher=#Springer,Kluwer,SPIE,IEEE
booktitle=%<text%>
journal=%<text%>
#endkeyvals

\BibTeX
\CPTitleFont#*
\CPAuthorFont#*
\CPInstituteFont#*
\CPInSourceFont#*
\CPCopyrightFont#*
\CoverPageHeader#*
\CoverPageBody#*
\CoverPageFooter#*
\CoverPageFooterLogo#*
\CPProcessBibEntry#*
\CPPublisherCheck#*
\CoverPageFooterInfo#*